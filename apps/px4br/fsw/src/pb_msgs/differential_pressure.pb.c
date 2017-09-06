/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:09 2016. */

#include "differential_pressure.pb.h"

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t px4_differential_pressure_pb_fields[7] = {
    PB_FIELD(  1, UINT64  , REQUIRED, STATIC  , FIRST, px4_differential_pressure_pb, timestamp, timestamp, 0),
    PB_FIELD(  2, UINT64  , REQUIRED, STATIC  , OTHER, px4_differential_pressure_pb, error_count, timestamp, 0),
    PB_FIELD(  3, FLOAT   , REQUIRED, STATIC  , OTHER, px4_differential_pressure_pb, differential_pressure_raw_pa, error_count, 0),
    PB_FIELD(  4, FLOAT   , REQUIRED, STATIC  , OTHER, px4_differential_pressure_pb, differential_pressure_filtered_pa, differential_pressure_raw_pa, 0),
    PB_FIELD(  5, FLOAT   , REQUIRED, STATIC  , OTHER, px4_differential_pressure_pb, max_differential_pressure_pa, differential_pressure_filtered_pa, 0),
    PB_FIELD(  6, FLOAT   , REQUIRED, STATIC  , OTHER, px4_differential_pressure_pb, temperature, max_differential_pressure_pa, 0),
    PB_LAST_FIELD
};


/* @@protoc_insertion_point(eof) */
