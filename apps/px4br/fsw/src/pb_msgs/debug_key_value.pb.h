/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Sat Oct 29 18:11:51 2016. */

#ifndef PB_DEBUG_KEY_VALUE_PB_H_INCLUDED
#define PB_DEBUG_KEY_VALUE_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Struct definitions */
typedef struct _px4_debug_key_value_pb {
    uint64_t timestamp;
    uint32_t timestamp_ms;
    float value;
    char key[10];
/* @@protoc_insertion_point(struct:px4_debug_key_value_pb) */
} px4_debug_key_value_pb;

/* Default values for struct fields */

/* Initializer values for message structs */
#define px4_debug_key_value_pb_init_default      {0, 0, 0, ""}
#define px4_debug_key_value_pb_init_zero         {0, 0, 0, ""}

/* Field tags (for use in manual encoding/decoding) */
#define px4_debug_key_value_pb_timestamp_tag     1
#define px4_debug_key_value_pb_timestamp_ms_tag  2
#define px4_debug_key_value_pb_value_tag         3
#define px4_debug_key_value_pb_key_tag           4

/* Struct field encoding specification for nanopb */
extern const pb_field_t px4_debug_key_value_pb_fields[5];

/* Maximum encoded size of messages (where known) */
#define px4_debug_key_value_pb_size              34

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define DEBUG_KEY_VALUE_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif