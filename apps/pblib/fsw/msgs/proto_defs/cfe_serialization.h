/* This file was autogenerated from template version 0.0.0.1 and autogenerator version 0.0.0.1 */

#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_lib.h"
#include "cfe_es_msg.h"
#include "CFE_ES_HkPacket_t.pb.h"
#include "CFE_ES_SetMaxPRCount_t.pb.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32 CFE_ES_HkPacket_t_Enc(const CFE_ES_HkPacket_t *inObject, char *inOutBuffer, uint32 inSize);
uint32 CFE_ES_HkPacket_t_Dec(const char *inBuffer, uint32 inSize, CFE_ES_HkPacket_t *inOutObject);


uint32 CFE_ES_SetMaxPRCount_t_Enc(const CFE_ES_SetMaxPRCount_t *inObject, char *inOutBuffer, uint32 inSize);
uint32 CFE_ES_SetMaxPRCount_t_Dec(const char *inBuffer, uint32 inSize, CFE_ES_SetMaxPRCount_t *inOutObject);

#ifdef __cplusplus
} /* extern "C" */
#endif
