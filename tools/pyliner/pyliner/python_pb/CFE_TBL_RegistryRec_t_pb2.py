# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_CFE_TBL_RegistryRec_t.proto

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
  name='_py_CFE_TBL_RegistryRec_t.proto',
  package='',
  serialized_pb=_b('\n\x1f_py_CFE_TBL_RegistryRec_t.proto\"\xa8\x01\n\x15\x43\x46\x45_TBL_LoadBuff_t_pb\x12\x1a\n\x12\x46ileCreateTimeSecs\x18\x01 \x02(\r\x12\x1d\n\x15\x46ileCreateTimeSubSecs\x18\x02 \x02(\r\x12\x0b\n\x03\x43rc\x18\x03 \x02(\r\x12\x11\n\tBufferPtr\x18\x04 \x02(\r\x12\r\n\x05Taken\x18\x05 \x02(\x08\x12\x11\n\tValidated\x18\x06 \x02(\x08\x12\x12\n\nDataSource\x18\x07 \x02(\t\"<\n\x15\x43\x46\x45_TIME_SysTime_t_pb\x12\x0f\n\x07Seconds\x18\x01 \x02(\r\x12\x12\n\nSubseconds\x18\x02 \x02(\r\"\xf2\x04\n\x18\x43\x46\x45_TBL_RegistryRec_t_pb\x12\x19\n\x11NotificationMsgId\x18\x01 \x02(\r\x12\x10\n\x08\x44umpOnly\x18\x02 \x02(\x08\x12\x13\n\x0b\x44\x62lBuffered\x18\x03 \x02(\x08\x12\x11\n\tCDSHandle\x18\x04 \x02(\r\x12\x1d\n\x15ValidateInactiveIndex\x18\x05 \x02(\x05\x12\x17\n\x0fTableLoadedOnce\x18\x06 \x02(\x08\x12\x19\n\x11\x41\x63tiveBufferIndex\x18\x07 \x02(\r\x12\x12\n\nOwnerAppId\x18\x08 \x02(\r\x12\x0c\n\x04Name\x18\t \x02(\t\x12\x16\n\x0eLoadInProgress\x18\n \x02(\x05\x12\x18\n\x10\x44umpControlIndex\x18\x0b \x02(\x05\x12\x19\n\x11ValidationFuncPtr\x18\x0c \x02(\r\x12\x15\n\rCriticalTable\x18\r \x02(\x08\x12\x13\n\x0bLoadPending\x18\x0e \x02(\x08\x12\x13\n\x0bUserDefAddr\x18\x0f \x02(\x08\x12\x16\n\x0eLastFileLoaded\x18\x10 \x02(\t\x12\x19\n\x11NotificationParam\x18\x11 \x02(\r\x12\x1b\n\x13ValidateActiveIndex\x18\x12 \x02(\x05\x12\x13\n\x0bNotifyByMsg\x18\x13 \x02(\x08\x12\x16\n\x0eNotificationCC\x18\x14 \x02(\r\x12\x18\n\x10HeadOfAccessList\x18\x15 \x02(\x05\x12\x30\n\x10TimeOfLastUpdate\x18\x16 \x02(\x0b\x32\x16.CFE_TIME_SysTime_t_pb\x12\'\n\x07\x42uffers\x18\x17 \x03(\x0b\x32\x16.CFE_TBL_LoadBuff_t_pb\x12\x0c\n\x04Size\x18\x18 \x02(\r')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_CFE_TBL_LOADBUFF_T_PB = _descriptor.Descriptor(
  name='CFE_TBL_LoadBuff_t_pb',
  full_name='CFE_TBL_LoadBuff_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='FileCreateTimeSecs', full_name='CFE_TBL_LoadBuff_t_pb.FileCreateTimeSecs', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='FileCreateTimeSubSecs', full_name='CFE_TBL_LoadBuff_t_pb.FileCreateTimeSubSecs', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Crc', full_name='CFE_TBL_LoadBuff_t_pb.Crc', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='BufferPtr', full_name='CFE_TBL_LoadBuff_t_pb.BufferPtr', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Taken', full_name='CFE_TBL_LoadBuff_t_pb.Taken', index=4,
      number=5, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Validated', full_name='CFE_TBL_LoadBuff_t_pb.Validated', index=5,
      number=6, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DataSource', full_name='CFE_TBL_LoadBuff_t_pb.DataSource', index=6,
      number=7, type=9, cpp_type=9, label=2,
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
  serialized_start=36,
  serialized_end=204,
)


_CFE_TIME_SYSTIME_T_PB = _descriptor.Descriptor(
  name='CFE_TIME_SysTime_t_pb',
  full_name='CFE_TIME_SysTime_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Seconds', full_name='CFE_TIME_SysTime_t_pb.Seconds', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Subseconds', full_name='CFE_TIME_SysTime_t_pb.Subseconds', index=1,
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
  serialized_start=206,
  serialized_end=266,
)


_CFE_TBL_REGISTRYREC_T_PB = _descriptor.Descriptor(
  name='CFE_TBL_RegistryRec_t_pb',
  full_name='CFE_TBL_RegistryRec_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='NotificationMsgId', full_name='CFE_TBL_RegistryRec_t_pb.NotificationMsgId', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DumpOnly', full_name='CFE_TBL_RegistryRec_t_pb.DumpOnly', index=1,
      number=2, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DblBuffered', full_name='CFE_TBL_RegistryRec_t_pb.DblBuffered', index=2,
      number=3, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CDSHandle', full_name='CFE_TBL_RegistryRec_t_pb.CDSHandle', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ValidateInactiveIndex', full_name='CFE_TBL_RegistryRec_t_pb.ValidateInactiveIndex', index=4,
      number=5, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TableLoadedOnce', full_name='CFE_TBL_RegistryRec_t_pb.TableLoadedOnce', index=5,
      number=6, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ActiveBufferIndex', full_name='CFE_TBL_RegistryRec_t_pb.ActiveBufferIndex', index=6,
      number=7, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='OwnerAppId', full_name='CFE_TBL_RegistryRec_t_pb.OwnerAppId', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Name', full_name='CFE_TBL_RegistryRec_t_pb.Name', index=8,
      number=9, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LoadInProgress', full_name='CFE_TBL_RegistryRec_t_pb.LoadInProgress', index=9,
      number=10, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DumpControlIndex', full_name='CFE_TBL_RegistryRec_t_pb.DumpControlIndex', index=10,
      number=11, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ValidationFuncPtr', full_name='CFE_TBL_RegistryRec_t_pb.ValidationFuncPtr', index=11,
      number=12, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CriticalTable', full_name='CFE_TBL_RegistryRec_t_pb.CriticalTable', index=12,
      number=13, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LoadPending', full_name='CFE_TBL_RegistryRec_t_pb.LoadPending', index=13,
      number=14, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='UserDefAddr', full_name='CFE_TBL_RegistryRec_t_pb.UserDefAddr', index=14,
      number=15, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastFileLoaded', full_name='CFE_TBL_RegistryRec_t_pb.LastFileLoaded', index=15,
      number=16, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=_b("").decode('utf-8'),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='NotificationParam', full_name='CFE_TBL_RegistryRec_t_pb.NotificationParam', index=16,
      number=17, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ValidateActiveIndex', full_name='CFE_TBL_RegistryRec_t_pb.ValidateActiveIndex', index=17,
      number=18, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='NotifyByMsg', full_name='CFE_TBL_RegistryRec_t_pb.NotifyByMsg', index=18,
      number=19, type=8, cpp_type=7, label=2,
      has_default_value=False, default_value=False,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='NotificationCC', full_name='CFE_TBL_RegistryRec_t_pb.NotificationCC', index=19,
      number=20, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='HeadOfAccessList', full_name='CFE_TBL_RegistryRec_t_pb.HeadOfAccessList', index=20,
      number=21, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='TimeOfLastUpdate', full_name='CFE_TBL_RegistryRec_t_pb.TimeOfLastUpdate', index=21,
      number=22, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Buffers', full_name='CFE_TBL_RegistryRec_t_pb.Buffers', index=22,
      number=23, type=11, cpp_type=10, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Size', full_name='CFE_TBL_RegistryRec_t_pb.Size', index=23,
      number=24, type=13, cpp_type=3, label=2,
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
  serialized_start=269,
  serialized_end=895,
)

_CFE_TBL_REGISTRYREC_T_PB.fields_by_name['TimeOfLastUpdate'].message_type = _CFE_TIME_SYSTIME_T_PB
_CFE_TBL_REGISTRYREC_T_PB.fields_by_name['Buffers'].message_type = _CFE_TBL_LOADBUFF_T_PB
DESCRIPTOR.message_types_by_name['CFE_TBL_LoadBuff_t_pb'] = _CFE_TBL_LOADBUFF_T_PB
DESCRIPTOR.message_types_by_name['CFE_TIME_SysTime_t_pb'] = _CFE_TIME_SYSTIME_T_PB
DESCRIPTOR.message_types_by_name['CFE_TBL_RegistryRec_t_pb'] = _CFE_TBL_REGISTRYREC_T_PB

CFE_TBL_LoadBuff_t_pb = _reflection.GeneratedProtocolMessageType('CFE_TBL_LoadBuff_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_TBL_LOADBUFF_T_PB,
  __module__ = '_py_CFE_TBL_RegistryRec_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_TBL_LoadBuff_t_pb)
  ))
_sym_db.RegisterMessage(CFE_TBL_LoadBuff_t_pb)

CFE_TIME_SysTime_t_pb = _reflection.GeneratedProtocolMessageType('CFE_TIME_SysTime_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_TIME_SYSTIME_T_PB,
  __module__ = '_py_CFE_TBL_RegistryRec_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_TIME_SysTime_t_pb)
  ))
_sym_db.RegisterMessage(CFE_TIME_SysTime_t_pb)

CFE_TBL_RegistryRec_t_pb = _reflection.GeneratedProtocolMessageType('CFE_TBL_RegistryRec_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_TBL_REGISTRYREC_T_PB,
  __module__ = '_py_CFE_TBL_RegistryRec_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_TBL_RegistryRec_t_pb)
  ))
_sym_db.RegisterMessage(CFE_TBL_RegistryRec_t_pb)


# @@protoc_insertion_point(module_scope)