from collections import OrderedDict
import sys
import json


def setup_serialization_dict(apps):
    """ Generate the base dictionary that will be populated by this 
    script with expected fields """
    base_dict = {}
    base_dict["Airliner"] = {}
    base_dict["autogen_version"] = ""
    base_dict["_extensions"] = ["jinja2.ext.do", "jinja2.ext.loopcontrols"]    
    base_dict["Airliner"]["apps"] = {}

    for app in apps:
        base_dict["Airliner"]["apps"][app] = {}
        base_dict["Airliner"]["apps"][app]["app_name"] = app
        base_dict["Airliner"]["apps"][app]["app_ops_name"] = app
        base_dict["Airliner"]["apps"][app]["proto_msgs"] = {}
        base_dict["Airliner"]["apps"][app]["operations"] = {}

    return base_dict
    
def get_pb_name(sym_name):
    """ Get the pb name for this symbol """
    return sym_name + "_pb"

def get_pb_type(sym):
    """ Given a symbol, return the protobuf type equivalent """
    primitives = ["int", "float", "char", "double"]
    type_map = {
        "uint8":   "uint32",
        "uint16":  "uint32",
        "uint32":  "uint32",
        "uint64":  "uint64",
        "int8":    "int32",
        "int16":   "int32",
        "int32":   "int32",
        "int64":   "int64",
        "char":    "string",
        "boolean": "bool",
        "float":   "float",
        "double":   "double",
    }
    global explain
    
    if sym["real_type"] in type_map:
        return type_map[sym["real_type"]]
    elif is_enum(sym["real_type"]):
        return "uint32"
    elif sym["real_type"] in explain["symbols"] and "real_type" in explain["symbols"][sym["real_type"]] and explain["symbols"][sym["real_type"]]["real_type"] in type_map:
        print explain["symbols"][sym["real_type"]]["real_type"]
        type_map[explain["symbols"][sym["real_type"]]["real_type"]]
    else:
        if "base_type" in sym:
            base = sym["base_type"].split(' ')[-1]
            if base in primitives:
                if base == "int":
                    unsigned = "unsigned" in sym["base_type"]
                    if sym["bit_size"] <= 32:
                        return "uint32" if unsigned else "int32"
                    else:
                        return "uint64" if unsigned else "int64"
                else: # TODO this may need to be smarter
                    return type_map[base]
                
        
        return get_pb_name(sym["real_type"])

def fix_fields(sym):
    """ Iterate over all fields in a symbol with a depth first search
    to convert to expected format of serialization autogenerator """
    
    if "fields" not in sym:
        return sym

    # Iterate over all fields in this symbol
    fields = {}
    for field in sym["fields"]:
        name = field["name"]

        # Check if this field is another symbol
        if "fields" in field:
            # Recur into lowest level of nested fields and fix bottom up
            field = fix_fields(field)

        # Set new dict key equal to this field
        fields[name] = field

        # Set name TODO this shouldn't really be needed
        fields[name]["airliner_name"] = name
        
        # Remove unused keys from field
        del fields[name]["name"]            
        if "type" in fields[name]:
            del fields[name]["type"]
#        if "bit_size" in fields[name]:
#            del fields[name]["bit_size"]
#        if "bit_offset" in fields[name]:
#            del fields[name]["bit_offset"]

        
        # Set proper airliner and ptotobuf types for this field
        if "real_type" in fields[name]:
            if fields[name]["real_type"][0] == '*':
                fields[name]["airliner_type"] = "uint32"
                fields[name]["pb_type"] = "uint32"
            else:
                fields[name]["airliner_type"] = fields[name]["real_type"]
                fields[name]["pb_type"] = get_pb_type(fields[name])
            del fields[name]["real_type"]

        # Check base type if this is a pointer
        if "base_type" in fields[name]:
            if fields[name]["base_type"][0] == '*':
                fields[name]["airliner_type"] = "uint32"
                fields[name]["pb_type"] = "uint32"
            del fields[name]["base_type"]
        
        # Set array length
        if "array" in fields[name]:
            fields[name]["array_length"] = fields[name]["count"]
            fields[name]["pb_field_rule"] = "repeated"
            del fields[name]["count"]
            del fields[name]["array"]
        else:
            fields[name]["array_length"] = 0
            fields[name]["pb_field_rule"] = "required"
        
    sym["fields"] = fields
    return sym
        
def fix_required(symbol):
    """ Iterate over all fields of a symbol and correctly add any nested symbols to the
    appropriate required_pb_msgs of given symbol. Performs a breadth first search on a symbol """
    
    if "fields" not in symbol:
        return {}
        
    def fix(sym, req_pb={}, parent=None):
        try: # TODO: Remove this
        
            # Check if this is another symbol
            if "fields" not in sym:
                # If not we have reached a primitive and should just return our current req_pb dictionary
                return req_pb

            # Iterate over all fields in this symbol
            for field, data in sym["fields"].iteritems():
                # Don't do anything to or recur into fields which are not other symbols
                if "fields" not in data:
                    continue
                
                # Verify this is a valid symbol with types set
                if "airliner_type" in data and "pb_type" in data:
                    sym_type = data["airliner_type"]
                    pb_type = data["pb_type"]
                else:
                    print "Warning: " + str(sym) + " does not contain type information."
                    continue
                
                # Check if this is a pointer
                if sym_type == "uint32" and pb_type == "uint32":
                    del data["fields"]
                    continue
                
                # If parent is set we have already recurred into a nested symbol
                if parent:
                    # Check if the current symbol has already been added to the parent's required types dictionary
                    if pb_type in parent["required_pb_msgs"]:
                        # This symbol has been added so we just need to add this symbol to the parent field map. 
                        # We need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                        parent["required_pb_msgs"][pb_type]["parent_field"][field] = 0
                    else:            
                        # Add the required pb message
                        parent["required_pb_msgs"][pb_type] = {}
                        parent["required_pb_msgs"][pb_type]["airliner_msg"] = sym_type
                        parent["required_pb_msgs"][pb_type]["parent_field"] = {field:0}
                        parent["required_pb_msgs"][pb_type]["fields"] = data["fields"]
                        parent["required_pb_msgs"][pb_type]["required_pb_msgs"] = {}
                        
                    # Recur into next level of nested fields and fix top down
                    req_pb = fix(data, req_pb, parent["required_pb_msgs"][pb_type])
                    
                else:
                    # If this required pb message already exists, add our current field to the parent field dict in req_pb
                    if req_pb and pb_type in req_pb:
                        # This symbol has been added so we just need to add this symbol to the parent field map. 
                        # We need the value to be populated because jinja struggles with arrays, so we use a dictionary instead.
                        req_pb[pb_type]["parent_field"][field] = 0
                    else:
                        # Add required pb message
                        req_pb[pb_type] = {}
                        req_pb[pb_type]["airliner_msg"] = sym_type
                        req_pb[pb_type]["parent_field"] = {field:0}
                        req_pb[pb_type]["fields"] = data["fields"]
                        req_pb[pb_type]["required_pb_msgs"] = {}
    
                    # Recur into next level of nested fields and fix top down
                    req_pb = fix(data, req_pb, req_pb[pb_type])

                # Remove fields from struct field
                del data["fields"]
                
        except Exception as e:
            print "\n"
            print repr(e)
            print field
            print data
            print "\n"
            print req_pb
            
            
        return req_pb

    return fix(symbol, OrderedDict())
                
def is_enum(sym):
    """ Check if the passed symbol is an enumeration so its protobuf type can 
    be set appropriately. """
    
    # TODO this should probably be smarter
    global explain
    if explain and sym in explain["symbols"]:
        if explain["symbols"][sym]["bit_size"] == 32 and "fields" not in explain["symbols"][sym]:
            return True
    return False

def valid_symbol(sym, data):
    """ Check if the passes symbol is a valid symbol """
    if "fields" not in data:
        return False
    elif "_pb" in sym:
        return False

    return True        
                
explain = {}
with open("symbols.json", "r") as explain_json:
    explain = json.load(explain_json)

# Parse app names
apps = [app.split('.')[0] for app in explain["files"]]
apps.append("PX4")
apps.append("CFE")
serial_input = setup_serialization_dict(apps)

# Reformat data into expected form
for symbol, data in explain["symbols"].iteritems():
    # Skip empty struct definitions - we don't care about those here
    if not valid_symbol(symbol, data):
        continue
    
    # Lookup app name for this message so it can be placed correctly. TODO find a better way
    app_name = symbol.split("_")[0]
    if app_name not in apps:
        continue

    # Fix fields so key is message name
    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol] = fix_fields(data)
    
    # Remove unused keys
    if "type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["type"]
    if "base_type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["base_type"]
    if "real_type" in serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]:
        del serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["real_type"]

    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["operational_names"] = {}

    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["proto_msg"] = get_pb_name(symbol)
    serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]["required_pb_msgs"] = fix_required(data)


    serial_input["Airliner"]["apps"][app_name]["operations"][symbol] = {}
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_msg"] = symbol
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_cc"] = -1
    serial_input["Airliner"]["apps"][app_name]["operations"][symbol]["airliner_mid"] = ""
    #print serial_input["Airliner"]["apps"][app_name]["proto_msgs"][symbol]
    #print "\n\n\n\n"
       
        
with open("cookiecutter.json", "w") as cc:
    output = serial_input#OrderedDict(sorted(serial_input.items(), key = lambda x: serial_input['Airliner']['apps'][x]))
    json.dump(output, cc, indent=4)



