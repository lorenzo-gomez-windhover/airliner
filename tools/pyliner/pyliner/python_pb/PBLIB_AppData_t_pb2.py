# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_PBLIB_AppData_t.proto

import sys
_b=sys.version_info[0]<3 and (lambda x:x) or (lambda x:x.encode('latin1'))
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import symbol_database as _symbol_database
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)

_sym_db = _symbol_database.Default()




DESCRIPTOR = _descriptor.FileDescriptor(
  name='_py_PBLIB_AppData_t.proto',
  package='',
  serialized_pb=_b('\n\x19_py_PBLIB_AppData_t.proto\"E\n\x12PBLIB_RegData_t_pb\x12\x0f\n\x07\x63mdCode\x18\x01 \x02(\r\x12\r\n\x05msgId\x18\x02 \x02(\r\x12\x0f\n\x07msgName\x18\x03 \x02(\t\"W\n\x12PBLIB_AppData_t_pb\x12,\n\x0fRegisteredFuncs\x18\x01 \x03(\x0b\x32\x13.PBLIB_RegData_t_pb\x12\x13\n\x0bRegTblMutex\x18\x02 \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PBLIB_REGDATA_T_PB = _descriptor.Descriptor(
  name='PBLIB_RegData_t_pb',
  full_name='PBLIB_RegData_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='cmdCode', full_name='PBLIB_RegData_t_pb.cmdCode', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msgId', full_name='PBLIB_RegData_t_pb.msgId', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='msgName', full_name='PBLIB_RegData_t_pb.msgName', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=29,
  serialized_end=98,
)


_PBLIB_APPDATA_T_PB = _descriptor.Descriptor(
  name='PBLIB_AppData_t_pb',
  full_name='PBLIB_AppData_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='RegisteredFuncs', full_name='PBLIB_AppData_t_pb.RegisteredFuncs', index=0,
      number=1, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RegTblMutex', full_name='PBLIB_AppData_t_pb.RegTblMutex', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  oneofs=[
  ],
  serialized_start=100,
  serialized_end=187,
)

_PBLIB_APPDATA_T_PB.fields_by_name['RegisteredFuncs'].message_type = _PBLIB_REGDATA_T_PB
DESCRIPTOR.message_types_by_name['PBLIB_RegData_t_pb'] = _PBLIB_REGDATA_T_PB
DESCRIPTOR.message_types_by_name['PBLIB_AppData_t_pb'] = _PBLIB_APPDATA_T_PB

PBLIB_RegData_t_pb = _reflection.GeneratedProtocolMessageType('PBLIB_RegData_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PBLIB_REGDATA_T_PB,
  __module__ = '_py_PBLIB_AppData_t_pb2'
  # @@protoc_insertion_point(class_scope:PBLIB_RegData_t_pb)
  ))
_sym_db.RegisterMessage(PBLIB_RegData_t_pb)

PBLIB_AppData_t_pb = _reflection.GeneratedProtocolMessageType('PBLIB_AppData_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PBLIB_APPDATA_T_PB,
  __module__ = '_py_PBLIB_AppData_t_pb2'
  # @@protoc_insertion_point(class_scope:PBLIB_AppData_t_pb)
  ))
_sym_db.RegisterMessage(PBLIB_AppData_t_pb)


# @@protoc_insertion_point(module_scope)
