/* This file was autogenerated from template version 0.0.0.1 and autogenerator version 0.0.0.1 */

#include "pb.h"
#include "pb_encode.h"
#include "pb_decode.h"
#include "pb_lib.h"
#include "gps_hk.pb.h"
#include "px4_msgs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    uint8              TlmHeader[CFE_SB_TLM_HDR_SIZE];
    uint8              usCmdCnt;   
    uint8              usCmdErrCnt; 
    uint8              State;
    PX4_VehicleGpsPositionMsg_t VehicleGpsMsg;
} GPS_HkTlm_t;


uint32 GPS_HkTlm_t_Enc(const GPS_HkTlm_t *inObject, char *inOutBuffer, uint32 inSize);
uint32 GPS_HkTlm_t_Dec(const char *inBuffer, uint32 inSize, GPS_HkTlm_t *inOutObject);

#ifdef __cplusplus
} /* extern "C" */
#endif