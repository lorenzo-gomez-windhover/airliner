# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_CS_HkPacket_t.proto

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
  name='_py_CS_HkPacket_t.proto',
  package='',
  serialized_pb=_b('\n\x17_py_CS_HkPacket_t.proto\"\xdc\x05\n\x10\x43S_HkPacket_t_pb\x12#\n\x1bLastOneShotMaxBytesPerCycle\x18\x01 \x02(\r\x12\x17\n\x0f\x43\x66\x65\x43oreBaseline\x18\x02 \x02(\r\x12\x1a\n\x12LastOneShotAddress\x18\x03 \x02(\r\x12\x1b\n\x13LastOneShotChecksum\x18\x04 \x02(\r\x12\x16\n\x0e\x45\x65promBaseline\x18\x05 \x02(\r\x12\x12\n\nOSBaseline\x18\x06 \x02(\r\x12\x1a\n\x12\x45\x65promCSErrCounter\x18\x07 \x02(\r\x12\x17\n\x0fLastOneShotSize\x18\x08 \x02(\r\x12\x15\n\rEepromCSState\x18\t \x02(\r\x12\x13\n\x0bPassCounter\x18\n \x02(\r\x12\x1a\n\x12TablesCSErrCounter\x18\x0b \x02(\r\x12\x11\n\tTlmHeader\x18\x0c \x03(\r\x12\x16\n\x0e\x43\x66\x65\x43oreCSState\x18\r \x02(\r\x12\x1b\n\x13\x43\x66\x65\x43oreCSErrCounter\x18\x0e \x02(\r\x12\x16\n\x0eOSCSErrCounter\x18\x0f \x02(\r\x12\x15\n\rTablesCSState\x18\x10 \x02(\r\x12\x1b\n\x13RecomputeInProgress\x18\x11 \x02(\r\x12\x12\n\nCmdCounter\x18\x12 \x02(\r\x12\x11\n\tOSCSState\x18\x13 \x02(\r\x12\x17\n\x0f\x41ppCSErrCounter\x18\x14 \x02(\r\x12\x15\n\rMemoryCSState\x18\x15 \x02(\r\x12\x1b\n\x13\x43urrentEntryInTable\x18\x16 \x02(\r\x12\x19\n\x11OneShotInProgress\x18\x17 \x02(\r\x12\x15\n\rCmdErrCounter\x18\x18 \x02(\r\x12\x15\n\rChecksumState\x18\x19 \x02(\r\x12\x16\n\x0e\x43urrentCSTable\x18\x1a \x02(\r\x12\x12\n\nAppCSState\x18\x1b \x02(\r\x12\x1a\n\x12MemoryCSErrCounter\x18\x1c \x02(\r\x12\x0f\n\x07\x46iller8\x18\x1d \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CS_HKPACKET_T_PB = _descriptor.Descriptor(
  name='CS_HkPacket_t_pb',
  full_name='CS_HkPacket_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='LastOneShotMaxBytesPerCycle', full_name='CS_HkPacket_t_pb.LastOneShotMaxBytesPerCycle', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CfeCoreBaseline', full_name='CS_HkPacket_t_pb.CfeCoreBaseline', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastOneShotAddress', full_name='CS_HkPacket_t_pb.LastOneShotAddress', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastOneShotChecksum', full_name='CS_HkPacket_t_pb.LastOneShotChecksum', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EepromBaseline', full_name='CS_HkPacket_t_pb.EepromBaseline', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OSBaseline', full_name='CS_HkPacket_t_pb.OSBaseline', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EepromCSErrCounter', full_name='CS_HkPacket_t_pb.EepromCSErrCounter', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastOneShotSize', full_name='CS_HkPacket_t_pb.LastOneShotSize', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EepromCSState', full_name='CS_HkPacket_t_pb.EepromCSState', index=8,
      number=9, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='PassCounter', full_name='CS_HkPacket_t_pb.PassCounter', index=9,
      number=10, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TablesCSErrCounter', full_name='CS_HkPacket_t_pb.TablesCSErrCounter', index=10,
      number=11, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TlmHeader', full_name='CS_HkPacket_t_pb.TlmHeader', index=11,
      number=12, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CfeCoreCSState', full_name='CS_HkPacket_t_pb.CfeCoreCSState', index=12,
      number=13, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CfeCoreCSErrCounter', full_name='CS_HkPacket_t_pb.CfeCoreCSErrCounter', index=13,
      number=14, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OSCSErrCounter', full_name='CS_HkPacket_t_pb.OSCSErrCounter', index=14,
      number=15, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TablesCSState', full_name='CS_HkPacket_t_pb.TablesCSState', index=15,
      number=16, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='RecomputeInProgress', full_name='CS_HkPacket_t_pb.RecomputeInProgress', index=16,
      number=17, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CmdCounter', full_name='CS_HkPacket_t_pb.CmdCounter', index=17,
      number=18, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OSCSState', full_name='CS_HkPacket_t_pb.OSCSState', index=18,
      number=19, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AppCSErrCounter', full_name='CS_HkPacket_t_pb.AppCSErrCounter', index=19,
      number=20, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MemoryCSState', full_name='CS_HkPacket_t_pb.MemoryCSState', index=20,
      number=21, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CurrentEntryInTable', full_name='CS_HkPacket_t_pb.CurrentEntryInTable', index=21,
      number=22, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OneShotInProgress', full_name='CS_HkPacket_t_pb.OneShotInProgress', index=22,
      number=23, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CmdErrCounter', full_name='CS_HkPacket_t_pb.CmdErrCounter', index=23,
      number=24, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ChecksumState', full_name='CS_HkPacket_t_pb.ChecksumState', index=24,
      number=25, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CurrentCSTable', full_name='CS_HkPacket_t_pb.CurrentCSTable', index=25,
      number=26, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='AppCSState', full_name='CS_HkPacket_t_pb.AppCSState', index=26,
      number=27, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='MemoryCSErrCounter', full_name='CS_HkPacket_t_pb.MemoryCSErrCounter', index=27,
      number=28, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Filler8', full_name='CS_HkPacket_t_pb.Filler8', index=28,
      number=29, type=13, cpp_type=3, label=2,
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
  serialized_start=28,
  serialized_end=760,
)

DESCRIPTOR.message_types_by_name['CS_HkPacket_t_pb'] = _CS_HKPACKET_T_PB

CS_HkPacket_t_pb = _reflection.GeneratedProtocolMessageType('CS_HkPacket_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CS_HKPACKET_T_PB,
  __module__ = '_py_CS_HkPacket_t_pb2'
  # @@protoc_insertion_point(class_scope:CS_HkPacket_t_pb)
  ))
_sym_db.RegisterMessage(CS_HkPacket_t_pb)


# @@protoc_insertion_point(module_scope)
