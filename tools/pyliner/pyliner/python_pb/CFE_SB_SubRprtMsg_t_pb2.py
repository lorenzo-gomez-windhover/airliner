# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_CFE_SB_SubRprtMsg_t.proto

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
  name='_py_CFE_SB_SubRprtMsg_t.proto',
  package='',
  serialized_pb=_b('\n\x1d_py_CFE_SB_SubRprtMsg_t.proto\"m\n\x1e\x43\x46\x45_SB_SubRprtMsg_Payload_t_pb\x12\x0c\n\x04Pipe\x18\x01 \x02(\t\x12\r\n\x05MsgId\x18\x02 \x02(\r\x12\x1d\n\x03Qos\x18\x03 \x02(\x0b\x32\x10.CFE_SB_Qos_t_pb\x12\x0f\n\x07SubType\x18\x04 \x02(\r\"8\n\x0f\x43\x46\x45_SB_Qos_t_pb\x12\x10\n\x08Priority\x18\x01 \x02(\r\x12\x13\n\x0bReliability\x18\x02 \x02(\r\"Y\n\x12\x43\x46\x45_SB_TlmHdr_t_pb\x12\x1f\n\x03Pri\x18\x01 \x02(\x0b\x32\x12.CCSDS_PriHdr_t_pb\x12\"\n\x03Sec\x18\x02 \x02(\x0b\x32\x15.CCSDS_TlmSecHdr_t_pb\"$\n\x14\x43\x43SDS_TlmSecHdr_t_pb\x12\x0c\n\x04Time\x18\x01 \x03(\r\"G\n\x11\x43\x43SDS_PriHdr_t_pb\x12\x0e\n\x06Length\x18\x01 \x03(\r\x12\x10\n\x08Sequence\x18\x02 \x03(\r\x12\x10\n\x08StreamId\x18\x03 \x03(\r\"l\n\x16\x43\x46\x45_SB_SubRprtMsg_t_pb\x12 \n\x03Hdr\x18\x01 \x02(\x0b\x32\x13.CFE_SB_TlmHdr_t_pb\x12\x30\n\x07Payload\x18\x02 \x02(\x0b\x32\x1f.CFE_SB_SubRprtMsg_Payload_t_pb')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CFE_SB_SUBRPRTMSG_PAYLOAD_T_PB = _descriptor.Descriptor(
  name='CFE_SB_SubRprtMsg_Payload_t_pb',
  full_name='CFE_SB_SubRprtMsg_Payload_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Pipe', full_name='CFE_SB_SubRprtMsg_Payload_t_pb.Pipe', index=0,
      number=1, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MsgId', full_name='CFE_SB_SubRprtMsg_Payload_t_pb.MsgId', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Qos', full_name='CFE_SB_SubRprtMsg_Payload_t_pb.Qos', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='SubType', full_name='CFE_SB_SubRprtMsg_Payload_t_pb.SubType', index=3,
      number=4, type=13, cpp_type=3, label=2,
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
  serialized_start=33,
  serialized_end=142,
)


_CFE_SB_QOS_T_PB = _descriptor.Descriptor(
  name='CFE_SB_Qos_t_pb',
  full_name='CFE_SB_Qos_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Priority', full_name='CFE_SB_Qos_t_pb.Priority', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Reliability', full_name='CFE_SB_Qos_t_pb.Reliability', index=1,
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
  serialized_start=144,
  serialized_end=200,
)


_CFE_SB_TLMHDR_T_PB = _descriptor.Descriptor(
  name='CFE_SB_TlmHdr_t_pb',
  full_name='CFE_SB_TlmHdr_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Pri', full_name='CFE_SB_TlmHdr_t_pb.Pri', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Sec', full_name='CFE_SB_TlmHdr_t_pb.Sec', index=1,
      number=2, type=11, cpp_type=10, label=2,
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
  serialized_start=202,
  serialized_end=291,
)


_CCSDS_TLMSECHDR_T_PB = _descriptor.Descriptor(
  name='CCSDS_TlmSecHdr_t_pb',
  full_name='CCSDS_TlmSecHdr_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Time', full_name='CCSDS_TlmSecHdr_t_pb.Time', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=293,
  serialized_end=329,
)


_CCSDS_PRIHDR_T_PB = _descriptor.Descriptor(
  name='CCSDS_PriHdr_t_pb',
  full_name='CCSDS_PriHdr_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Length', full_name='CCSDS_PriHdr_t_pb.Length', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Sequence', full_name='CCSDS_PriHdr_t_pb.Sequence', index=1,
      number=2, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='StreamId', full_name='CCSDS_PriHdr_t_pb.StreamId', index=2,
      number=3, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
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
  serialized_start=331,
  serialized_end=402,
)


_CFE_SB_SUBRPRTMSG_T_PB = _descriptor.Descriptor(
  name='CFE_SB_SubRprtMsg_t_pb',
  full_name='CFE_SB_SubRprtMsg_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Hdr', full_name='CFE_SB_SubRprtMsg_t_pb.Hdr', index=0,
      number=1, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Payload', full_name='CFE_SB_SubRprtMsg_t_pb.Payload', index=1,
      number=2, type=11, cpp_type=10, label=2,
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
  serialized_start=404,
  serialized_end=512,
)

_CFE_SB_SUBRPRTMSG_PAYLOAD_T_PB.fields_by_name['Qos'].message_type = _CFE_SB_QOS_T_PB
_CFE_SB_TLMHDR_T_PB.fields_by_name['Pri'].message_type = _CCSDS_PRIHDR_T_PB
_CFE_SB_TLMHDR_T_PB.fields_by_name['Sec'].message_type = _CCSDS_TLMSECHDR_T_PB
_CFE_SB_SUBRPRTMSG_T_PB.fields_by_name['Hdr'].message_type = _CFE_SB_TLMHDR_T_PB
_CFE_SB_SUBRPRTMSG_T_PB.fields_by_name['Payload'].message_type = _CFE_SB_SUBRPRTMSG_PAYLOAD_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_SubRprtMsg_Payload_t_pb'] = _CFE_SB_SUBRPRTMSG_PAYLOAD_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_Qos_t_pb'] = _CFE_SB_QOS_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_TlmHdr_t_pb'] = _CFE_SB_TLMHDR_T_PB
DESCRIPTOR.message_types_by_name['CCSDS_TlmSecHdr_t_pb'] = _CCSDS_TLMSECHDR_T_PB
DESCRIPTOR.message_types_by_name['CCSDS_PriHdr_t_pb'] = _CCSDS_PRIHDR_T_PB
DESCRIPTOR.message_types_by_name['CFE_SB_SubRprtMsg_t_pb'] = _CFE_SB_SUBRPRTMSG_T_PB

CFE_SB_SubRprtMsg_Payload_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_SubRprtMsg_Payload_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_SUBRPRTMSG_PAYLOAD_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_SubRprtMsg_Payload_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_SubRprtMsg_Payload_t_pb)

CFE_SB_Qos_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_Qos_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_QOS_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_Qos_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_Qos_t_pb)

CFE_SB_TlmHdr_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_TlmHdr_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_TLMHDR_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_TlmHdr_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_TlmHdr_t_pb)

CCSDS_TlmSecHdr_t_pb = _reflection.GeneratedProtocolMessageType('CCSDS_TlmSecHdr_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CCSDS_TLMSECHDR_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CCSDS_TlmSecHdr_t_pb)
  ))
_sym_db.RegisterMessage(CCSDS_TlmSecHdr_t_pb)

CCSDS_PriHdr_t_pb = _reflection.GeneratedProtocolMessageType('CCSDS_PriHdr_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CCSDS_PRIHDR_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CCSDS_PriHdr_t_pb)
  ))
_sym_db.RegisterMessage(CCSDS_PriHdr_t_pb)

CFE_SB_SubRprtMsg_t_pb = _reflection.GeneratedProtocolMessageType('CFE_SB_SubRprtMsg_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_SB_SUBRPRTMSG_T_PB,
  __module__ = '_py_CFE_SB_SubRprtMsg_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_SB_SubRprtMsg_t_pb)
  ))
_sym_db.RegisterMessage(CFE_SB_SubRprtMsg_t_pb)


# @@protoc_insertion_point(module_scope)
