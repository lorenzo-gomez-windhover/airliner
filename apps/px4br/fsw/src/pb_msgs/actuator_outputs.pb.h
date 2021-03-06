/* Automatically generated nanopb header */
/* Generated by nanopb-0.3.6 at Wed Oct 26 00:46:06 2016. */

#ifndef PB_ACTUATOR_OUTPUTS_PB_H_INCLUDED
#define PB_ACTUATOR_OUTPUTS_PB_H_INCLUDED
#include <pb.h>

/* @@protoc_insertion_point(includes) */
#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Enum definitions */
typedef enum _px4_actuator_outputs_pb_ACTUATOR_OUTPUTS {
    px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ACTUATOR_OUTPUTS_NUM_ACTUATOR_OUTPUTS = 16,
    px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ACTUATOR_OUTPUTS_NUM_ACTUATOR_OUTPUTS_GROUP = 4
} px4_actuator_outputs_pb_ACTUATOR_OUTPUTS;
#define _px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_MIN px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ACTUATOR_OUTPUTS_NUM_ACTUATOR_OUTPUTS
#define _px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_MAX px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ACTUATOR_OUTPUTS_NUM_ACTUATOR_OUTPUTS_GROUP
#define _px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ARRAYSIZE ((px4_actuator_outputs_pb_ACTUATOR_OUTPUTS)(px4_actuator_outputs_pb_ACTUATOR_OUTPUTS_ACTUATOR_OUTPUTS_NUM_ACTUATOR_OUTPUTS_GROUP+1))

/* Struct definitions */
typedef struct _px4_actuator_outputs_pb {
    uint64_t timestamp;
    uint32_t noutputs;
    pb_size_t output_count;
    float output[16];
/* @@protoc_insertion_point(struct:px4_actuator_outputs_pb) */
} px4_actuator_outputs_pb;

/* Default values for struct fields */

/* Initializer values for message structs */
#define px4_actuator_outputs_pb_init_default     {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}
#define px4_actuator_outputs_pb_init_zero        {0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}}

/* Field tags (for use in manual encoding/decoding) */
#define px4_actuator_outputs_pb_timestamp_tag    1
#define px4_actuator_outputs_pb_noutputs_tag     2
#define px4_actuator_outputs_pb_output_tag       3

/* Struct field encoding specification for nanopb */
extern const pb_field_t px4_actuator_outputs_pb_fields[4];

/* Maximum encoded size of messages (where known) */
#define px4_actuator_outputs_pb_size             97

/* Message IDs (where set with "msgid" option) */
#ifdef PB_MSGID

#define ACTUATOR_OUTPUTS_MESSAGES \


#endif

#ifdef __cplusplus
} /* extern "C" */
#endif
/* @@protoc_insertion_point(eof) */

#endif
