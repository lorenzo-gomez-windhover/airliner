/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:16 2016. */

#include "safety.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t px4_safety_pb_fields[4] = {
    PB_FIELD(  1, UINT64  , REQUIRED, STATIC  , FIRST, px4_safety_pb, timestamp, timestamp, 0),
    PB_FIELD(  2, BOOL    , REQUIRED, STATIC  , OTHER, px4_safety_pb, safety_switch_available, timestamp, 0),
    PB_FIELD(  3, BOOL    , REQUIRED, STATIC  , OTHER, px4_safety_pb, safety_off, safety_switch_available, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */
