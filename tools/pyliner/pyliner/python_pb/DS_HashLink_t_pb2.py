# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_DS_HashLink_t.proto

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
  name='_py_DS_HashLink_t.proto',
  package='',
  serialized_pb=_b('\n\x17_py_DS_HashLink_t.proto\"?\n\rDS_HashTag_pb\x12\r\n\x05Index\x18\x01 \x02(\r\x12\x0c\n\x04Next\x18\x02 \x02(\r\x12\x11\n\tMessageID\x18\x03 \x02(\r\"3\n\x10\x44S_HashLink_t_pb\x12\x1f\n\x07typedef\x18\x01 \x02(\x0b\x32\x0e.DS_HashTag_pb')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_DS_HASHTAG_PB = _descriptor.Descriptor(
  name='DS_HashTag_pb',
  full_name='DS_HashTag_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Index', full_name='DS_HashTag_pb.Index', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Next', full_name='DS_HashTag_pb.Next', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MessageID', full_name='DS_HashTag_pb.MessageID', index=2,
      number=3, type=13, cpp_type=3, label=2,
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
  serialized_start=27,
  serialized_end=90,
)


_DS_HASHLINK_T_PB = _descriptor.Descriptor(
  name='DS_HashLink_t_pb',
  full_name='DS_HashLink_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='typedef', full_name='DS_HashLink_t_pb.typedef', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
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
  serialized_start=92,
  serialized_end=143,
)

_DS_HASHLINK_T_PB.fields_by_name['typedef'].message_type = _DS_HASHTAG_PB
DESCRIPTOR.message_types_by_name['DS_HashTag_pb'] = _DS_HASHTAG_PB
DESCRIPTOR.message_types_by_name['DS_HashLink_t_pb'] = _DS_HASHLINK_T_PB

DS_HashTag_pb = _reflection.GeneratedProtocolMessageType('DS_HashTag_pb', (_message.Message,), dict(
  DESCRIPTOR = _DS_HASHTAG_PB,
  __module__ = '_py_DS_HashLink_t_pb2'
  # @@protoc_insertion_point(class_scope:DS_HashTag_pb)
  ))
_sym_db.RegisterMessage(DS_HashTag_pb)

DS_HashLink_t_pb = _reflection.GeneratedProtocolMessageType('DS_HashLink_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _DS_HASHLINK_T_PB,
  __module__ = '_py_DS_HashLink_t_pb2'
  # @@protoc_insertion_point(class_scope:DS_HashLink_t_pb)
  ))
_sym_db.RegisterMessage(DS_HashLink_t_pb)


# @@protoc_insertion_point(module_scope)
