# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: _py_LC_WRTEntry_t.proto

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
  name='_py_LC_WRTEntry_t.proto',
  package='',
  serialized_pb=_b('\n\x17_py_LC_WRTEntry_t.proto\"t\n\x15LC_WRTTransition_t_pb\x12\x0f\n\x07Padding\x18\x01 \x03(\r\x12)\n\tTimestamp\x18\x02 \x02(\x0b\x32\x16.CFE_TIME_SysTime_t_pb\x12\x10\n\x08\x44\x61taType\x18\x03 \x02(\r\x12\r\n\x05Value\x18\x04 \x02(\r\"<\n\x15\x43\x46\x45_TIME_SysTime_t_pb\x12\x0f\n\x07Seconds\x18\x01 \x02(\r\x12\x12\n\nSubseconds\x18\x02 \x02(\r\"\xa2\x02\n\x10LC_WRTEntry_t_pb\x12\x1b\n\x13\x43umulativeTrueCount\x18\x01 \x02(\r\x12\x18\n\x10\x43ountdownToStale\x18\x02 \x02(\r\x12/\n\x0fLastTrueToFalse\x18\x03 \x02(\x0b\x32\x16.LC_WRTTransition_t_pb\x12\x17\n\x0f\x45valuationCount\x18\x04 \x02(\r\x12\x13\n\x0bWatchResult\x18\x05 \x02(\r\x12\x1c\n\x14\x43onsecutiveTrueCount\x18\x06 \x02(\r\x12\x0f\n\x07Padding\x18\x07 \x03(\r\x12\x18\n\x10\x46\x61lseToTrueCount\x18\x08 \x02(\r\x12/\n\x0fLastFalseToTrue\x18\t \x02(\x0b\x32\x16.LC_WRTTransition_t_pb')
)
_sym_db.RegisterFileDescriptor(DESCRIPTOR)




_LC_WRTTRANSITION_T_PB = _descriptor.Descriptor(
  name='LC_WRTTransition_t_pb',
  full_name='LC_WRTTransition_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='Padding', full_name='LC_WRTTransition_t_pb.Padding', index=0,
      number=1, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Timestamp', full_name='LC_WRTTransition_t_pb.Timestamp', index=1,
      number=2, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='DataType', full_name='LC_WRTTransition_t_pb.DataType', index=2,
      number=3, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Value', full_name='LC_WRTTransition_t_pb.Value', index=3,
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
  serialized_start=27,
  serialized_end=143,
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
  serialized_start=145,
  serialized_end=205,
)


_LC_WRTENTRY_T_PB = _descriptor.Descriptor(
  name='LC_WRTEntry_t_pb',
  full_name='LC_WRTEntry_t_pb',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='CumulativeTrueCount', full_name='LC_WRTEntry_t_pb.CumulativeTrueCount', index=0,
      number=1, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='CountdownToStale', full_name='LC_WRTEntry_t_pb.CountdownToStale', index=1,
      number=2, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastTrueToFalse', full_name='LC_WRTEntry_t_pb.LastTrueToFalse', index=2,
      number=3, type=11, cpp_type=10, label=2,
      has_default_value=False, default_value=None,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='EvaluationCount', full_name='LC_WRTEntry_t_pb.EvaluationCount', index=3,
      number=4, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='WatchResult', full_name='LC_WRTEntry_t_pb.WatchResult', index=4,
      number=5, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='ConsecutiveTrueCount', full_name='LC_WRTEntry_t_pb.ConsecutiveTrueCount', index=5,
      number=6, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='Padding', full_name='LC_WRTEntry_t_pb.Padding', index=6,
      number=7, type=13, cpp_type=3, label=3,
      has_default_value=False, default_value=[],
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='FalseToTrueCount', full_name='LC_WRTEntry_t_pb.FalseToTrueCount', index=7,
      number=8, type=13, cpp_type=3, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='LastFalseToTrue', full_name='LC_WRTEntry_t_pb.LastFalseToTrue', index=8,
      number=9, type=11, cpp_type=10, label=2,
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
  serialized_start=208,
  serialized_end=498,
)

_LC_WRTTRANSITION_T_PB.fields_by_name['Timestamp'].message_type = _CFE_TIME_SYSTIME_T_PB
_LC_WRTENTRY_T_PB.fields_by_name['LastTrueToFalse'].message_type = _LC_WRTTRANSITION_T_PB
_LC_WRTENTRY_T_PB.fields_by_name['LastFalseToTrue'].message_type = _LC_WRTTRANSITION_T_PB
DESCRIPTOR.message_types_by_name['LC_WRTTransition_t_pb'] = _LC_WRTTRANSITION_T_PB
DESCRIPTOR.message_types_by_name['CFE_TIME_SysTime_t_pb'] = _CFE_TIME_SYSTIME_T_PB
DESCRIPTOR.message_types_by_name['LC_WRTEntry_t_pb'] = _LC_WRTENTRY_T_PB

LC_WRTTransition_t_pb = _reflection.GeneratedProtocolMessageType('LC_WRTTransition_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _LC_WRTTRANSITION_T_PB,
  __module__ = '_py_LC_WRTEntry_t_pb2'
  # @@protoc_insertion_point(class_scope:LC_WRTTransition_t_pb)
  ))
_sym_db.RegisterMessage(LC_WRTTransition_t_pb)

CFE_TIME_SysTime_t_pb = _reflection.GeneratedProtocolMessageType('CFE_TIME_SysTime_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _CFE_TIME_SYSTIME_T_PB,
  __module__ = '_py_LC_WRTEntry_t_pb2'
  # @@protoc_insertion_point(class_scope:CFE_TIME_SysTime_t_pb)
  ))
_sym_db.RegisterMessage(CFE_TIME_SysTime_t_pb)

LC_WRTEntry_t_pb = _reflection.GeneratedProtocolMessageType('LC_WRTEntry_t_pb', (_message.Message,), dict(
  DESCRIPTOR = _LC_WRTENTRY_T_PB,
  __module__ = '_py_LC_WRTEntry_t_pb2'
  # @@protoc_insertion_point(class_scope:LC_WRTEntry_t_pb)
  ))
_sym_db.RegisterMessage(LC_WRTEntry_t_pb)


# @@protoc_insertion_point(module_scope)
