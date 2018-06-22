/* This file was autogenerated from template version 0.0.0.1 and autogenerator version 0.0.0.1 */

#include "gps_registration.h"

#ifdef __cplusplus
extern "C" {
#endif

uint32 GPS_RegisterSerializationFuncs()
{
	int32 Status = CFE_SUCCESS;

	/* Register each message with PBL */
	Status = PBLIB_RegisterTlmMessage(0x0c54, "GPS_HkTlm_t");
	if (Status != CFE_SUCCESS)
	{
		goto GPS_RegisterSerializationFuncs_Exit_Tag;
	}
	
GPS_RegisterSerializationFuncs_Exit_Tag:
    return Status;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

