# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_GPS_NAV_TIMEUTC_t.proto

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
  name='_py_GPS_NAV_TIMEUTC_t.proto',
  package='',
  serialized_pb=_b('\n\x1b_py_GPS_NAV_TIMEUTC_t.proto\"\xa1\x01\n\x14GPS_NAV_TIMEUTC_t_pb\x12\x0c\n\x04hour\x18\x01 \x02(\r\x12\x0c\n\x04nano\x18\x02 \x02(\x05\x12\x0b\n\x03min\x18\x03 \x02(\r\x12\r\n\x05month\x18\x04 \x02(\r\x12\r\n\x05valid\x18\x05 \x02(\r\x12\x0b\n\x03sec\x18\x06 \x02(\r\x12\x0c\n\x04iTOW\x18\x07 \x02(\r\x12\x0c\n\x04year\x18\x08 \x02(\r\x12\x0c\n\x04tAcc\x18\t \x02(\r\x12\x0b\n\x03\x64\x61y\x18\n \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_GPS_NAV_TIMEUTC_T_PB = _descriptor.Descriptor(
  name='GPS_NAV_TIMEUTC_t_pb',
  full_name='GPS_NAV_TIMEUTC_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='hour', full_name='GPS_NAV_TIMEUTC_t_pb.hour', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='nano', full_name='GPS_NAV_TIMEUTC_t_pb.nano', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='min', full_name='GPS_NAV_TIMEUTC_t_pb.min', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='month', full_name='GPS_NAV_TIMEUTC_t_pb.month', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='valid', full_name='GPS_NAV_TIMEUTC_t_pb.valid', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='sec', full_name='GPS_NAV_TIMEUTC_t_pb.sec', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='iTOW', full_name='GPS_NAV_TIMEUTC_t_pb.iTOW', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='year', full_name='GPS_NAV_TIMEUTC_t_pb.year', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='tAcc', full_name='GPS_NAV_TIMEUTC_t_pb.tAcc', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='day', full_name='GPS_NAV_TIMEUTC_t_pb.day', index=9,
      number=10, type=13, cpp_type=3, label=2,
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
  serialized_start=32,
  serialized_end=193,
)

DESCRIPTOR.message_types_by_name['GPS_NAV_TIMEUTC_t_pb'] = _GPS_NAV_TIMEUTC_T_PB

GPS_NAV_TIMEUTC_t_pb = _reflection.GeneratedProtocolMessageType('GPS_NAV_TIMEUTC_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _GPS_NAV_TIMEUTC_T_PB,
  __module__ = '_py_GPS_NAV_TIMEUTC_t_pb2'
  # @@protoc_insertion_point(class_scope:GPS_NAV_TIMEUTC_t_pb)
  ))
_sym_db.RegisterMessage(GPS_NAV_TIMEUTC_t_pb)


# @@protoc_insertion_point(module_scope)