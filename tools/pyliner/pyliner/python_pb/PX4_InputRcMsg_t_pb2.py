# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_PX4_InputRcMsg_t.proto

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
  name='_py_PX4_InputRcMsg_t.proto',
  package='',
  serialized_pb=_b('\n\x1a_py_PX4_InputRcMsg_t.proto\"\x8b\x02\n\x13PX4_InputRcMsg_t_pb\x12\x19\n\x11RcTotalFrameCount\x18\x01 \x02(\r\x12\x0e\n\x06RcLost\x18\x02 \x02(\x08\x12\x14\n\x0c\x43hannelCount\x18\x03 \x02(\r\x12\x12\n\nLastSignal\x18\x04 \x02(\x04\x12\x12\n\nRcFailsafe\x18\x05 \x02(\x08\x12\x11\n\tTimestamp\x18\x06 \x02(\x04\x12\x13\n\x0bInputSource\x18\x07 \x02(\r\x12\x11\n\tTlmHeader\x18\x08 \x03(\r\x12\x0e\n\x06Values\x18\t \x03(\r\x12\x18\n\x10RcPpmFrameLength\x18\n \x02(\r\x12\x18\n\x10RcLostFrameCount\x18\x0b \x02(\r\x12\x0c\n\x04RSSI\x18\x0c \x02(\x05')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_PX4_INPUTRCMSG_T_PB = _descriptor.Descriptor(
  name='PX4_InputRcMsg_t_pb',
  full_name='PX4_InputRcMsg_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='RcTotalFrameCount', full_name='PX4_InputRcMsg_t_pb.RcTotalFrameCount', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcLost', full_name='PX4_InputRcMsg_t_pb.RcLost', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ChannelCount', full_name='PX4_InputRcMsg_t_pb.ChannelCount', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastSignal', full_name='PX4_InputRcMsg_t_pb.LastSignal', index=3,
      number=4, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcFailsafe', full_name='PX4_InputRcMsg_t_pb.RcFailsafe', index=4,
      number=5, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='PX4_InputRcMsg_t_pb.Timestamp', index=5,
      number=6, type=4, cpp_type=4, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='InputSource', full_name='PX4_InputRcMsg_t_pb.InputSource', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TlmHeader', full_name='PX4_InputRcMsg_t_pb.TlmHeader', index=7,
      number=8, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Values', full_name='PX4_InputRcMsg_t_pb.Values', index=8,
      number=9, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcPpmFrameLength', full_name='PX4_InputRcMsg_t_pb.RcPpmFrameLength', index=9,
      number=10, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RcLostFrameCount', full_name='PX4_InputRcMsg_t_pb.RcLostFrameCount', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RSSI', full_name='PX4_InputRcMsg_t_pb.RSSI', index=11,
      number=12, type=5, cpp_type=1, label=2,
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
  serialized_start=31,
  serialized_end=298,
)

DESCRIPTOR.message_types_by_name['PX4_InputRcMsg_t_pb'] = _PX4_INPUTRCMSG_T_PB

PX4_InputRcMsg_t_pb = _reflection.GeneratedProtocolMessageType('PX4_InputRcMsg_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _PX4_INPUTRCMSG_T_PB,
  __module__ = '_py_PX4_InputRcMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:PX4_InputRcMsg_t_pb)
  ))
_sym_db.RegisterMessage(PX4_InputRcMsg_t_pb)


# @@protoc_insertion_point(module_scope)
