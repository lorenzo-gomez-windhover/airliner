# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_GPS_Header_t.proto

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
  name='_py_GPS_Header_t.proto',
  package='',
  serialized_pb=_b('\n\x16_py_GPS_Header_t.proto\"Z\n\x0fGPS_Header_t_pb\x12\r\n\x05\x63lass\x18\x01 \x02(\r\x12\x0e\n\x06length\x18\x02 \x02(\r\x12\r\n\x05sync2\x18\x03 \x02(\r\x12\n\n\x02id\x18\x04 \x02(\r\x12\r\n\x05sync1\x18\x05 \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_GPS_HEADER_T_PB = _descriptor.Descriptor(
  name='GPS_Header_t_pb',
  full_name='GPS_Header_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='class', full_name='GPS_Header_t_pb.class', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='length', full_name='GPS_Header_t_pb.length', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sync2', full_name='GPS_Header_t_pb.sync2', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='id', full_name='GPS_Header_t_pb.id', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sync1', full_name='GPS_Header_t_pb.sync1', index=4,
      number=5, type=13, cpp_type=3, label=2,
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
  serialized_start=26,
  serialized_end=116,
)

DESCRIPTOR.message_types_by_name['GPS_Header_t_pb'] = _GPS_HEADER_T_PB

GPS_Header_t_pb = _reflection.GeneratedProtocolMessageType('GPS_Header_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _GPS_HEADER_T_PB,
  __module__ = '_py_GPS_Header_t_pb2'
  # @@protoc_insertion_point(class_scope:GPS_Header_t_pb)
  ))
_sym_db.RegisterMessage(GPS_Header_t_pb)


# @@protoc_insertion_point(module_scope)
