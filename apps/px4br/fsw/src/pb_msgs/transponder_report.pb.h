/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Sat Oct 29 18:17:59 2016. */

#ifndef PB_TRANSPONDER_REPORT_PB_H_INCLUDED
#define PB_TRANSPONDER_REPORT_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _px4_transponder_report_pb {
    uint64_t timestamp;
    double lat;
    double lon;
    uint32_t ICAO_address;
    float altitude;
    float heading;
    float hor_velocity;
    float ver_velocity;
    uint32_t flags;
    uint32_t squawk;
    uint32_t altitude_type;
    char callsign[9];
    uint32_t emitter_type;
    uint32_t tslc;
/* @@protoc_insertion_point(struct:px4_transponder_report_pb) */
} px4_transponder_report_pb;

/* Default values for struct fields */

/* Initializer values for message structs */
#define px4_transponder_report_pb_init_default   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 0}
#define px4_transponder_report_pb_init_zero      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, "", 0, 0}

/* Field tags (for use in manual encoding/decoding) */
#define px4_transponder_report_pb_timestamp_tag  1
#define px4_transponder_report_pb_lat_tag        2
#define px4_transponder_report_pb_lon_tag        3
#define px4_transponder_report_pb_ICAO_address_tag 4
#define px4_transponder_report_pb_altitude_tag   5
#define px4_transponder_report_pb_heading_tag    6
#define px4_transponder_report_pb_hor_velocity_tag 7
#define px4_transponder_report_pb_ver_velocity_tag 8
#define px4_transponder_report_pb_flags_tag      9
#define px4_transponder_report_pb_squawk_tag     10
#define px4_transponder_report_pb_altitude_type_tag 11
#define px4_transponder_report_pb_callsign_tag   12
#define px4_transponder_report_pb_emitter_type_tag 13
#define px4_transponder_report_pb_tslc_tag       14

/* Struct field encoding specification for nanopb */
extern const pb_field_t px4_transponder_report_pb_fields[15];

/* Maximum encoded size of messages (where known) */
#define px4_transponder_report_pb_size           96

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define TRANSPONDER_REPORT_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif