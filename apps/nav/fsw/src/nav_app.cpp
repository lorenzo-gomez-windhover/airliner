/************************************************************************
** Includes
*************************************************************************/
#include <string.h>

#include "cfe.h"

#include "nav_app.h"
#include "nav_msg.h"
#include "nav_version.h"


#include "nav_take_off.h"


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Instantiate the application object.                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV oNAV;



/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Default constructor.                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV::NAV()
{

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Destructor constructor.                                         */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
NAV::~NAV()
{

}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize event tables.                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitEvent()
{
    int32  iStatus=CFE_SUCCESS;

    /* Register the table with CFE */
    iStatus = CFE_EVS_Register(0, 0, CFE_EVS_BINARY_FILTER);
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to register with EVS (0x%08lX)\n", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Message Pipes                                        */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitPipe()
{
    int32  iStatus=CFE_SUCCESS;

    /* Init schedule pipe and subscribe to wakeup messages */
    iStatus = CFE_SB_CreatePipe(&SchPipeId,
    		NAV_SCH_PIPE_DEPTH,
			NAV_SCH_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = CFE_SB_SubscribeEx(NAV_WAKEUP_MID, SchPipeId, CFE_SB_Default_Qos, NAV_WAKEUP_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
            		"Sch Pipe failed to subscribe to NAV_WAKEUP_MID. (0x%08lX)",
                    iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(NAV_SEND_HK_MID, SchPipeId, CFE_SB_Default_Qos, NAV_SEND_HK_MID_MAX_MSG_COUNT);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to NAV_SEND_HK_MID. (0x%08X)",
					 (unsigned int)iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_HOME_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_HOME_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_SENSOR_COMBINED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_SENSOR_COMBINED_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_MISSION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_MISSION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GPS_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_GPS_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_GLOBAL_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_GLOBAL_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_STATUS_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_STATUS_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LAND_DETECTED_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_LAND_DETECTED_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_LOCAL_POSITION_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_LOCAL_POSITION_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }

        iStatus = CFE_SB_SubscribeEx(PX4_VEHICLE_COMMAND_MID, SchPipeId, CFE_SB_Default_Qos, 1);
        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
					 "CMD Pipe failed to subscribe to PX4_VEHICLE_COMMAND_MID. (0x%08lX)",
					 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create SCH pipe (0x%08lX)",
			 iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

    /* Init command pipe and subscribe to command messages */
    iStatus = CFE_SB_CreatePipe(&CmdPipeId,
    		NAV_CMD_PIPE_DEPTH,
			NAV_CMD_PIPE_NAME);
    if (iStatus == CFE_SUCCESS)
    {
        /* Subscribe to command messages */
        iStatus = CFE_SB_Subscribe(NAV_CMD_MID, CmdPipeId);

        if (iStatus != CFE_SUCCESS)
        {
            (void) CFE_EVS_SendEvent(NAV_SUBSCRIBE_ERR_EID, CFE_EVS_ERROR,
				 "CMD Pipe failed to subscribe to NAV_CMD_MID. (0x%08lX)",
				 iStatus);
            goto NAV_InitPipe_Exit_Tag;
        }
    }
    else
    {
        (void) CFE_EVS_SendEvent(NAV_PIPE_INIT_ERR_EID, CFE_EVS_ERROR,
			 "Failed to create CMD pipe (0x%08lX)",
			 iStatus);
        goto NAV_InitPipe_Exit_Tag;
    }

NAV_InitPipe_Exit_Tag:
    return iStatus;
}
    

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Initialize Global Variables                                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::InitData()
{
	/* Init housekeeping message. */
    CFE_SB_InitMsg(&HkTlm,
    		NAV_HK_TLM_MID, sizeof(HkTlm), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&VehicleLandDetectedMsg,
		PX4_VEHICLE_LAND_DETECTED_MID, sizeof(PX4_VehicleLandDetectedMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&FenceMsg,
		PX4_FENCE_MID, sizeof(PX4_FenceMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&ActuatorControls3Msg,
		PX4_ACTUATOR_CONTROLS_3_MID, sizeof(PX4_ActuatorControlsMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&MissionResultMsg,
		PX4_MISSION_RESULT_MID, sizeof(PX4_MissionResultMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&GeofenceResultMsg,
		PX4_GEOFENCE_RESULT_MID, sizeof(PX4_GeofenceResultMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&PositionSetpointTripletMsg,
		PX4_POSITION_SETPOINT_TRIPLET_MID, sizeof(PX4_PositionSetpointTripletMsg_t), TRUE);

	/* Init output messages */
	CFE_SB_InitMsg(&VehicleCommandMsgOut,
		PX4_POSITION_SETPOINT_TRIPLET_MID, sizeof(PX4_VehicleCommandMsg_t), TRUE);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV initialization                                              */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 NAV::InitApp()
{
    int32  iStatus   = CFE_SUCCESS;
    int8   hasEvents = 0;

    iStatus = InitEvent();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to init events (0x%08lX)\n", iStatus);
        goto NAV_InitApp_Exit_Tag;
    }
    else
    {
        hasEvents = 1;
    }

    iStatus = InitPipe();
    if (iStatus != CFE_SUCCESS)
    {
        goto NAV_InitApp_Exit_Tag;
    }

    InitData();

    iStatus = InitConfigTbl();
    if (iStatus != CFE_SUCCESS)
    {
        goto NAV_InitApp_Exit_Tag;
    }

NAV_InitApp_Exit_Tag:
    if (iStatus == CFE_SUCCESS)
    {
        (void) CFE_EVS_SendEvent(NAV_INIT_INF_EID, CFE_EVS_INFORMATION,
                                 "Initialized.  Version %d.%d.%d.%d",
								 NAV_MAJOR_VERSION,
								 NAV_MINOR_VERSION,
								 NAV_REVISION,
								 NAV_MISSION_REV);
    }
    else
    {
        if (hasEvents == 1)
        {
            (void) CFE_ES_WriteToSysLog("NAV - Application failed to initialize\n");
        }
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Receive and Process Messages                                    */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

int32 NAV::RcvSchPipeMsg(int32 iBlocking)
{
    int32           iStatus=CFE_SUCCESS;
    CFE_SB_Msg_t*   MsgPtr=NULL;
    CFE_SB_MsgId_t  MsgId;

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Wait for WakeUp messages from scheduler */
    iStatus = CFE_SB_RcvMsg(&MsgPtr, SchPipeId, iBlocking);

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    if (iStatus == CFE_SUCCESS)
    {
        MsgId = CFE_SB_GetMsgId(MsgPtr);
        switch (MsgId)
        {
            case NAV_WAKEUP_MID:
                /* TODO:  Do something here. */
            	//Execute();
                break;

            case NAV_SEND_HK_MID:
            	Execute();
                ProcessCmdPipe();
                ReportHousekeeping();
                break;

            case PX4_HOME_POSITION_MID:
                memcpy(&CVT.HomePositionMsg, MsgPtr, sizeof(CVT.HomePositionMsg));
                break;

            case PX4_SENSOR_COMBINED_MID:
                memcpy(&CVT.SensorCombinedMsg, MsgPtr, sizeof(CVT.SensorCombinedMsg));
                break;

            case PX4_MISSION_MID:
                memcpy(&CVT.MissionMsg, MsgPtr, sizeof(CVT.MissionMsg));
                break;

            case PX4_VEHICLE_GPS_POSITION_MID:
                memcpy(&CVT.VehicleGpsPositionMsg, MsgPtr, sizeof(CVT.VehicleGpsPositionMsg));
                break;

            case PX4_VEHICLE_GLOBAL_POSITION_MID:
                memcpy(&CVT.VehicleGlobalPosition, MsgPtr, sizeof(CVT.VehicleGlobalPosition));
                break;

            case PX4_VEHICLE_STATUS_MID:
                memcpy(&CVT.VehicleStatusMsg, MsgPtr, sizeof(CVT.VehicleStatusMsg));
                break;

            case PX4_VEHICLE_LAND_DETECTED_MID:
                memcpy(&CVT.VehicleLandDetectedMsg, MsgPtr, sizeof(CVT.VehicleLandDetectedMsg));
                break;

            case PX4_VEHICLE_LOCAL_POSITION_MID:
                memcpy(&CVT.VehicleLocalPositionMsg, MsgPtr, sizeof(CVT.VehicleLocalPositionMsg));
                break;

            case PX4_VEHICLE_COMMAND_MID:
                memcpy(&CVT.VehicleCommandMsg, MsgPtr, sizeof(CVT.VehicleCommandMsg));
                break;

            default:
                (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
                     "Recvd invalid SCH msgId (0x%04X)", MsgId);
        }
    }
    else if (iStatus == CFE_SB_NO_MESSAGE)
    {
        /* TODO: If there's no incoming message, you can do something here, or 
         * nothing.  Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else if (iStatus == CFE_SB_TIME_OUT)
    {
        /* TODO: If there's no incoming message within a specified time (via the
         * iBlocking arg, you can do something here, or nothing.  
         * Note, this section is dead code only if the iBlocking arg
         * is CFE_SB_PEND_FOREVER. */
        iStatus = CFE_SUCCESS;
    }
    else
    {
        (void) CFE_EVS_SendEvent(NAV_RCVMSG_ERR_EID, CFE_EVS_ERROR,
			  "SCH pipe read error (0x%08lX).", iStatus);
    }

    return iStatus;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process Incoming Commands                                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ProcessCmdPipe()
{
    int32 iStatus = CFE_SUCCESS;
    CFE_SB_Msg_t*   CmdMsgPtr=NULL;
    CFE_SB_MsgId_t  CmdMsgId;

    /* Process command messages until the pipe is empty */
    while (1)
    {
        iStatus = CFE_SB_RcvMsg(&CmdMsgPtr, CmdPipeId, CFE_SB_POLL);
        if(iStatus == CFE_SUCCESS)
        {
            CmdMsgId = CFE_SB_GetMsgId(CmdMsgPtr);
            switch (CmdMsgId)
            {
                case NAV_CMD_MID:
                    ProcessAppCmds(CmdMsgPtr);
                    //OS_printf("command msg pointer %ld ",CmdMsgPtr);
                    break;

                default:
                    /* Bump the command error counter for an unknown command.
                     * (This should only occur if it was subscribed to with this
                     *  pipe, but not handled in this switch-case.) */
                    HkTlm.usCmdErrCnt++;
                    (void) CFE_EVS_SendEvent(NAV_MSGID_ERR_EID, CFE_EVS_ERROR,
                                      "Recvd invalid CMD msgId (0x%04X)", (unsigned short)CmdMsgId);
                    break;
            }
        }
        else if (iStatus == CFE_SB_NO_MESSAGE)
        {
            break;
        }
        else
        {
            (void) CFE_EVS_SendEvent(NAV_RCVMSG_ERR_EID, CFE_EVS_ERROR,
                  "CMD pipe read error (0x%08lX)", iStatus);
            break;
        }
    }
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Process NAV Commands                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ProcessAppCmds(CFE_SB_Msg_t* MsgPtr)
{
    uint32  uiCmdCode=0;

    if (MsgPtr != NULL)
    {
        uiCmdCode = CFE_SB_GetCmdCode(MsgPtr);
        switch (uiCmdCode)
        {
            case NAV_NOOP_CC:
                HkTlm.usCmdCnt++;
                (void) CFE_EVS_SendEvent(NAV_CMD_NOOP_EID, CFE_EVS_INFORMATION,
					"Recvd NOOP. Version %d.%d.%d.%d",
					NAV_MAJOR_VERSION,
					NAV_MINOR_VERSION,
					NAV_REVISION,
					NAV_MISSION_REV);
                break;

            case NAV_RESET_CC:
                HkTlm.usCmdCnt = 0;
                HkTlm.usCmdErrCnt = 0;
                break;

            default:
                HkTlm.usCmdErrCnt++;
                (void) CFE_EVS_SendEvent(NAV_CC_ERR_EID, CFE_EVS_ERROR,
                                  "Recvd invalid command code (%u)", (unsigned int)uiCmdCode);
                break;
        }
    }
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Send NAV Housekeeping                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NAV::ReportHousekeeping()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&HkTlm);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&HkTlm);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Publish Output Data                                             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::SendVehicleLandDetectedMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleLandDetectedMsg);
}

void NAV::SendFenceMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&FenceMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&FenceMsg);
}

void NAV::SendActuatorControls3Msg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&ActuatorControls3Msg);
}

void NAV::SendMissionResultMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&MissionResultMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&MissionResultMsg);
}

void NAV::SendGeofenceResultMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&GeofenceResultMsg);
}

void NAV::SendPositionSetpointTripletMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&PositionSetpointTripletMsg);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&PositionSetpointTripletMsg);
}

void NAV::SendVehicleCommandMsg()
{
    CFE_SB_TimeStampMsg((CFE_SB_Msg_t*)&VehicleCommandMsgOut);
    CFE_SB_SendMsg((CFE_SB_Msg_t*)&VehicleCommandMsgOut);
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Verify Command Length                                           */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
boolean NAV::VerifyCmdLength(CFE_SB_Msg_t* MsgPtr,
                           uint16 usExpectedLen)
{
    boolean bResult  = TRUE;
    uint16  usMsgLen = 0;

    if (MsgPtr != NULL)
    {
        usMsgLen = CFE_SB_GetTotalMsgLength(MsgPtr);

        if (usExpectedLen != usMsgLen)
        {
            bResult = FALSE;
            CFE_SB_MsgId_t MsgId = CFE_SB_GetMsgId(MsgPtr);
            uint16 usCmdCode = CFE_SB_GetCmdCode(MsgPtr);

            (void) CFE_EVS_SendEvent(NAV_MSGLEN_ERR_EID, CFE_EVS_ERROR,
                              "Rcvd invalid msgLen: msgId=0x%08X, cmdCode=%d, "
                              "msgLen=%d, expectedLen=%d",
                              MsgId, usCmdCode, usMsgLen, usExpectedLen);
            HkTlm.usCmdErrCnt++;
        }
    }

    return bResult;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV Application C style main entry point.                       */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
extern "C" void NAV_AppMain()
{
    oNAV.AppMain();
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* NAV Application C++ style main entry point.                     */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void NAV::AppMain()
{
    /* Register the application with Executive Services */
    uiRunStatus = CFE_ES_APP_RUN;

    int32 iStatus = CFE_ES_RegisterApp();
    if (iStatus != CFE_SUCCESS)
    {
        (void) CFE_ES_WriteToSysLog("NAV - Failed to register the app (0x%08lX)\n", iStatus);
    }

    /* Start Performance Log entry */
    CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);

    /* Perform application initializations */
    if (iStatus == CFE_SUCCESS)
    {
        iStatus = InitApp();
    }

    if (iStatus == CFE_SUCCESS)
    {
        /* Do not perform performance monitoring on startup sync */
        CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);
        CFE_ES_WaitForStartupSync(NAV_STARTUP_TIMEOUT_MSEC);
        CFE_ES_PerfLogEntry(NAV_MAIN_TASK_PERF_ID);
    }
    else
    {
        uiRunStatus = CFE_ES_APP_ERROR;
    }

    /* Application main loop */
    while (CFE_ES_RunLoop(&uiRunStatus) == TRUE)
    {
        RcvSchPipeMsg(NAV_SCH_PIPE_PEND_TIME);

        iStatus = AcquireConfigPointers();
        if(iStatus != CFE_SUCCESS)
        {
            /* We apparently tried to load a new table but failed.  Terminate the application. */
            uiRunStatus = CFE_ES_APP_ERROR;
        }
    }

    /* Stop Performance Log entry */
    CFE_ES_PerfLogExit(NAV_MAIN_TASK_PERF_ID);

    /* Exit the application */
    CFE_ES_ExitApp(uiRunStatus);
}
int NAV::Execute(){

	// TODO: check global position availability

	boolean global_pos_available_once = false;

	if (CVT.VehicleGlobalPosition.Timestamp==0){
		return 0;
	}




	//time stamp messages
	const uint64 now = PX4LIB_GetPX4TimeUs();
	CVT.VehicleCommandMsg.Timestamp = now;
	PositionSetpointTripletMsg.Timestamp = now;


	//action on command receipt
	if(CVT.VehicleCommandMsg.Command == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_DO_REPOSITION && CVT.VehicleCommandMsg.Command!=one_level_deep_memory){
		//EVENT: DO REPOSITION

		//get required pointers to out bound messages


		//store current position as previous and goal as next
		PositionSetpointTripletMsg.Previous.Yaw = CVT.VehicleGlobalPosition.Yaw;
		PositionSetpointTripletMsg.Previous.Lat = CVT.VehicleGlobalPosition.Lat;
		PositionSetpointTripletMsg.Previous.Lon = CVT.VehicleGlobalPosition.Lon;
		PositionSetpointTripletMsg.Previous.Alt = CVT.VehicleGlobalPosition.Alt;

		//store new current position
		PositionSetpointTripletMsg.Current.LoiterRadius = nav_params.nav_loiter_rad;
		PositionSetpointTripletMsg.Current.LoiterDirection = 1;
		PositionSetpointTripletMsg.Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_LOITER;


		//assign yaw to current position set point
		if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param4)){
			PositionSetpointTripletMsg.Current.Yaw = CVT.VehicleCommandMsg.Param4;
		}else{
			PositionSetpointTripletMsg.Current.Yaw = NAN;
		}

		//assign latitude and longitude to current set point
		if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)){
			PositionSetpointTripletMsg.Current.Lat = (CVT.VehicleCommandMsg.Param5 < 1000) ? CVT.VehicleCommandMsg.Param5 : CVT.VehicleCommandMsg.Param5 /(double) 1e7;
			PositionSetpointTripletMsg.Current.Lon = (CVT.VehicleCommandMsg.Param6 < 1000) ? CVT.VehicleCommandMsg.Param6 : CVT.VehicleCommandMsg.Param6 /(double) 1e7;

		}else{
			PositionSetpointTripletMsg.Current.Lat = CVT.VehicleGlobalPosition.Lat;
			PositionSetpointTripletMsg.Current.Lon = CVT.VehicleGlobalPosition.Lon;
		}

		//assign altitude to current set point
		if (PX4_ISFINITE(CVT.VehicleCommandMsg.Param7)){
			PositionSetpointTripletMsg.Current.Alt = CVT.VehicleCommandMsg.Param7;
		}else{
			PositionSetpointTripletMsg.Current.Alt = CVT.VehicleGlobalPosition.Alt;
		}

		//assign set point triplet validity
		PositionSetpointTripletMsg.Previous.Valid = true;
		PositionSetpointTripletMsg.Current.Valid = true;
		PositionSetpointTripletMsg.Next.Valid = false;
		OS_printf("LOITER DETECTED");
		VehicleCommandMsgOut = CVT.VehicleCommandMsg;
		SendVehicleCommandMsg();
		SendPositionSetpointTripletMsg();


		one_level_deep_memory = CVT.VehicleCommandMsg.Command;

	}
	else if(CVT.VehicleCommandMsg.Command == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF && CVT.VehicleCommandMsg.Command!=one_level_deep_memory){
		//EVENT: TAKEOFF
		//store current position as previous and goal as next
		PositionSetpointTripletMsg.Previous.Yaw = CVT.VehicleGlobalPosition.Yaw;
		PositionSetpointTripletMsg.Previous.Lat = CVT.VehicleGlobalPosition.Lat;
		PositionSetpointTripletMsg.Previous.Lon = CVT.VehicleGlobalPosition.Lon;
		PositionSetpointTripletMsg.Previous.Alt = CVT.VehicleGlobalPosition.Alt;

		//store new current position
		PositionSetpointTripletMsg.Current.LoiterRadius = nav_params.nav_loiter_rad;
		PositionSetpointTripletMsg.Current.LoiterDirection = 1;
		PositionSetpointTripletMsg.Current.Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;

		//check if home position is valid, set current yaw and previous valid accordingly
		if (CVT.HomePositionMsg.Timestamp>0){
			PositionSetpointTripletMsg.Current.Yaw = CVT.VehicleCommandMsg.Param4;
			PositionSetpointTripletMsg.Previous.Valid = true;
		}else{
			PositionSetpointTripletMsg.Current.Yaw = CVT.VehicleLocalPositionMsg.Yaw;
			PositionSetpointTripletMsg.Previous.Valid = false;
		}

		// check if param5 and param6 is finite, set Latitude, Longitude, Altitude and current and next position set point validity
		if(PX4_ISFINITE(CVT.VehicleCommandMsg.Param5) && PX4_ISFINITE(CVT.VehicleCommandMsg.Param6)){
			PositionSetpointTripletMsg.Current.Lat = (CVT.VehicleCommandMsg.Param5 < 1000) ? CVT.VehicleCommandMsg.Param5 : CVT.VehicleCommandMsg.Param5 /(double) 1e7;
			PositionSetpointTripletMsg.Current.Lon = (CVT.VehicleCommandMsg.Param6 < 1000) ? CVT.VehicleCommandMsg.Param6 : CVT.VehicleCommandMsg.Param6 /(double) 1e7;
		}else{
			PositionSetpointTripletMsg.Current.Lat = NAN;
			PositionSetpointTripletMsg.Current.Lon = NAN;
		}
		//assign set point triplet validity
		PositionSetpointTripletMsg.Current.Alt = CVT.VehicleCommandMsg.Param7;
		PositionSetpointTripletMsg.Current.Valid = true;
		PositionSetpointTripletMsg.Next.Valid = false;

		//OS_printf("TAKEOFF REACHED____");
//		OS_printf("TAKEOFF DETECTED");
//		VehicleCommandMsgOut = CVT.VehicleCommandMsg;
//		SendVehicleCommandMsg();
//		SendPositionSetpointTripletMsg();

		//store recently seen command in memory
		one_level_deep_memory = CVT.VehicleCommandMsg.Command;


	}
	else if(CVT.VehicleCommandMsg.Command == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND && CVT.VehicleCommandMsg.Command!=one_level_deep_memory){
		OS_printf("LAND DETECTED");

		VehicleCommandMsgOut = CVT.VehicleCommandMsg;
		SendVehicleCommandMsg();
		SendPositionSetpointTripletMsg();

		one_level_deep_memory = CVT.VehicleCommandMsg.Command;
	}

	//naviagation modes
	switch(CVT.VehicleStatusMsg.NavState){

	case PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF:

		OS_printf("got loiter state %f\n",PositionSetpointTripletMsg.Previous.Alt );
		OS_printf("got loiter state %lld\n",PositionSetpointTripletMsg.Previous.Lat );
		OS_printf("got loiter state %lld\n",PositionSetpointTripletMsg.Previous.Lon );
		OS_printf("got loiter state %llu\n",CVT.VehicleGlobalPosition.Timestamp );
		Takeoff();
		OS_printf("TAKEOFF DETECTED");
//		VehicleCommandMsgOut = CVT.VehicleCommandMsg;
//		SendVehicleCommandMsg();
		SendPositionSetpointTripletMsg();
		break;




	}








	return 0;








}

//
void NAV::Takeoff(){
	//initialize pointers to messages
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr = &PositionSetpointTripletMsg;
	PX4_VehicleGlobalPositionMsg_t *VehicleGlobalPosition_ptr = &CVT.VehicleGlobalPosition;
	float AbsoluteAltitude = 0.0f;
	float MinPitch = 0.0f;
	float MinAbsoluteAltitude;


	//use home position if valid
	boolean hpv = HomePositionValid();
	if(hpv){
		MinAbsoluteAltitude = VehicleGlobalPosition_ptr->Alt + nav_params.nav_mis_takeoff_alt;
		OS_printf("VAL %f/n",MinAbsoluteAltitude);
	}
	else{
		MinAbsoluteAltitude = nav_params.nav_mis_takeoff_alt;
	}



	//use altitude if it is already set.
	//if home position is invalid use MinAbsoluteAltitude
	if (PositionSetpointTriplet_ptr->Current.Valid && PX4_ISFINITE(PositionSetpointTriplet_ptr->Current.Alt) && hpv){
		AbsoluteAltitude = PositionSetpointTriplet_ptr->Current.Alt;

		// if set altitude is less than minimum clearance raise it to that level and throw a warning
		if(AbsoluteAltitude < MinAbsoluteAltitude){
			AbsoluteAltitude = MinAbsoluteAltitude;
			OS_printf("WARN: Set altitude lower than minimum clearance./n");
		}
	}
	else{
		// raise to minimum clearance
		AbsoluteAltitude = MinAbsoluteAltitude;
		OS_printf("WARN: Set altitude lower than minimum clearance./n");
	}



	//if new altitude is lower than current altitude, don't go down.
	if(AbsoluteAltitude < VehicleGlobalPosition_ptr->Alt){
		AbsoluteAltitude = VehicleGlobalPosition_ptr->Alt;
		OS_printf("WARN: Already higher than take off altitude./n");
	}


	//set mission item to takeoff
	mission_item.NavCmd = PX4_NavigationState_t::PX4_NAVIGATION_STATE_AUTO_TAKEOFF;

	// use current position
	mission_item.Lat = VehicleGlobalPosition_ptr->Lat;
	mission_item.Lon = VehicleGlobalPosition_ptr->Lon;
	mission_item.Yaw = VehicleGlobalPosition_ptr->Yaw;
	mission_item.Altitude = AbsoluteAltitude;
	mission_item.AltitudeIsRelative = false;
	mission_item.LoiterRadius = nav_params.nav_loiter_rad;
	mission_item.PitchMin = MinPitch;
	mission_item.AutoContinue = false;
	mission_item.Origin = NAV_Origin_t::ORIGIN_ONBOARD;

	//set mission result message
	PX4_MissionResultMsg_t *MissionResultMsg_ptr = &MissionResultMsg;
	MissionResultMsg_ptr->Reached = false;
	MissionResultMsg_ptr->Finished = false;

	//record mission update event in boolean
	MissionResultUpdated = true;

	//reset mission item reached
	WaypointPositionReached = false;
	WaypointYawReached = false;
	TimeFirstInsideOrbit = 0;
	TimeWpReached = 0;

	//convert mission item to current set point
	PX4_PositionSetpointTripletMsg_t *PositionSetpointTriplet_ptr2 = &PositionSetpointTripletMsg;
	ConvertMissionItemToCurrentSetpoint(&PositionSetpointTriplet_ptr2->Current,&mission_item );
	PositionSetpointTriplet_ptr2 -> Previous.Valid = false;
	PositionSetpointTriplet_ptr2 -> Current.YawValid = true;
	PositionSetpointTriplet_ptr2 -> Next.Valid = false;

	if(PositionSetpointTriplet_ptr -> Current.Valid){
		if (PX4_ISFINITE(PositionSetpointTriplet_ptr -> Current.Yaw)) {
			PositionSetpointTriplet_ptr2 -> Current.Yaw = PositionSetpointTriplet_ptr -> Current.Yaw;
		}

		if (PX4_ISFINITE(PositionSetpointTriplet_ptr -> Current.Lat) && PX4_ISFINITE(PositionSetpointTriplet_ptr -> Current.Lon)) {
			PositionSetpointTriplet_ptr2 -> Current.Lat = PositionSetpointTriplet_ptr -> Current.Lat;
			PositionSetpointTriplet_ptr2 -> Current.Lon = PositionSetpointTriplet_ptr -> Current.Lon;
		}

		// mark this as done
		//memset(rep, 0, sizeof(*rep));
	}







}


void NAV::ConvertMissionItemToCurrentSetpoint(PX4_PositionSetpoint_t *ps, NAV_MissionItem_t *mi){

	if (!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_WAYPOINT ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_UNLIM ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LOITER_TIME ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_LAND ||
			!mi->NavCmd == PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF) {
		return;
	}
	PX4_HomePositionMsg_t *HomePositionMsg_ptr = GetHomePosition();

	ps->Lat = mi->Lat;
	ps->Lon = mi->Lon;
	ps->Alt = mi->AltitudeIsRelative ? mi->Altitude + HomePositionMsg_ptr->Alt : mi->Altitude;
	ps->Yaw = mi->Yaw;
	ps->LoiterRadius = (fabsf(mi->LoiterRadius) > NAV_EPSILON_POSITION) ? fabsf(mi->LoiterRadius) :	nav_params.nav_loiter_rad;
	ps->LoiterDirection = (mi->LoiterRadius > 0) ? 1 : -1;
	ps->AcceptanceRadius = mi->AcceptanceRadius;
	ps->DisableMcYawControl = mi->DisableMcYaw;

	ps->CruisingSpeed = GetCruisingSpeed();
	ps->CruisingThrottle = GetCruisingThrottle();

	switch(mi->NavCmd){
	case PX4_VehicleCmd_t::PX4_VEHICLE_CMD_NAV_TAKEOFF:
     	PX4_VehicleStatusMsg_t* gvs = GetVehicleStatusMsg();
     	PX4_VehicleLandDetectedMsg_t* gvld =  GetVehicleLandDetectedMsg();
		if(gvs->ArmingState == PX4_ArmingState_t::PX4_ARMING_STATE_ARMED &&
				!(gvld->Landed)){
			ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_POSITION;
		}
		else{
			ps->Type = PX4_SetpointType_t::PX4_SETPOINT_TYPE_TAKEOFF;
			// set pitch and ensure that the hold time is zero
			ps->PitchMin = mi->PitchMin;
		}
		break;
	}

}



boolean NAV::HomePositionValid(){
	PX4_HomePositionMsg_t* ghp = GetHomePosition();
	return (ghp->Timestamp>0);
}


float NAV::GetDefaultAcceptedRadius(){
	return nav_params.nav_acc_rad;
}

//this function also needs to set this variable in params table
void NAV::SetAcceptedRadius(float mission_radius){
	nav_params.nav_acc_rad = mission_radius;
}

float NAV::GetAltitudeAcceptedRadius(){
	return nav_params.nav_mc_alt_rad;
}
float NAV::GetCruisingThrottle(){
	if (MissionThrottle > FLT_EPSILON) {
			return MissionThrottle;

	}
	else{
			return -1.0f;
	}
}

float NAV::GetCruisingSpeed(){
	boolean is_planned = IsPlannedMission();
	if(is_planned && MissionCruisingSpeed > 0.0f){
		return MissionCruisingSpeed;
	}
	else{
		return -1.0f;
	}

}



void NAV::DisplayInputs(int n){
	OS_printf("NAV::DisplayInputs  *************\n");

	if(n==1 || n==10){
		OS_printf("  HomePositionMsg.Timestamp:           %llu\n", CVT.HomePositionMsg.Timestamp);
		OS_printf("  HomePositionMsg.Lat:            	  %lld\n", CVT.HomePositionMsg.Lat);
		OS_printf("  HomePositionMsg.Lon:                 %lld\n", CVT.HomePositionMsg.Lon);
		OS_printf("  HomePositionMsg.Alt:                 %f\n", CVT.HomePositionMsg.Alt);
		OS_printf("  HomePositionMsg.X:                   %f\n", CVT.HomePositionMsg.X);
		OS_printf("  HomePositionMsg.Y:                   %f\n", CVT.HomePositionMsg.Y);
		OS_printf("  HomePositionMsg.Z:                   %f\n", CVT.HomePositionMsg.Z);
		OS_printf("  HomePositionMsg.Yaw:                 %f\n", CVT.HomePositionMsg.Yaw);
		OS_printf("  HomePositionMsg.DirectionX:          %f\n", CVT.HomePositionMsg.DirectionX);
		OS_printf("  HomePositionMsg.DirectionY:          %f\n", CVT.HomePositionMsg.DirectionY);
		OS_printf("  HomePositionMsg.DirectionZ:          %f\n", CVT.HomePositionMsg.DirectionZ);
		OS_printf("\n");
	}

	if(n==2 || n==10){
		OS_printf("  SensorCombinedMsg.Timestamp:                %llu\n", CVT.SensorCombinedMsg.Timestamp);
		OS_printf("  SensorCombinedMsg.GyroRad[3]:               [%f,%f,%f]\n", CVT.SensorCombinedMsg.GyroRad[0],CVT.SensorCombinedMsg.GyroRad[1],CVT.SensorCombinedMsg.GyroRad[2]);
		OS_printf("  SensorCombinedMsg.GyroIntegralDt:           %f\n", CVT.SensorCombinedMsg.GyroIntegralDt);
		OS_printf("  SensorCombinedMsg.AccTimestampRelative:     %llu\n", CVT.SensorCombinedMsg.AccTimestampRelative);
		OS_printf("  SensorCombinedMsg.AccRelTimeInvalid:        %d\n", CVT.SensorCombinedMsg.AccRelTimeInvalid);
		OS_printf("  SensorCombinedMsg.Acc[3]:                   [%f,%f,%f]\n", CVT.SensorCombinedMsg.Acc[0],CVT.SensorCombinedMsg.Acc[1],CVT.SensorCombinedMsg.Acc[2]);
		OS_printf("  SensorCombinedMsg.AccIntegralDt:            %f\n", CVT.SensorCombinedMsg.AccIntegralDt);
		OS_printf("  SensorCombinedMsg.MagTimestampRelative:     %llu\n", CVT.SensorCombinedMsg.MagTimestampRelative);
		OS_printf("  SensorCombinedMsg.MagRelTimeInvalid:        %d\n", CVT.SensorCombinedMsg.MagRelTimeInvalid);
		OS_printf("  SensorCombinedMsg.Mag[3]:                   [%f,%f,%f]\n", CVT.SensorCombinedMsg.Mag[0],CVT.SensorCombinedMsg.Mag[1],CVT.SensorCombinedMsg.Mag[2]);
		OS_printf("  SensorCombinedMsg.BaroTimestampRelative:    %llu\n", CVT.SensorCombinedMsg.BaroTimestampRelative);
		OS_printf("  SensorCombinedMsg.BaroRelTimeInvalid:       %d\n", CVT.SensorCombinedMsg.BaroRelTimeInvalid);
		OS_printf("  SensorCombinedMsg.BaroAlt:                  %f\n", CVT.SensorCombinedMsg.BaroAlt);
		OS_printf("  SensorCombinedMsg.BaroTemp:                 %f\n", CVT.SensorCombinedMsg.BaroTemp);
		OS_printf("\n");
	}

	if(n==3 || n==10){
		OS_printf("  MissionMsg.Timestamp:            %llu\n", CVT.MissionMsg.Timestamp);
		OS_printf("  MissionMsg.DatamanID:            %llu\n", CVT.MissionMsg.DatamanID);
		OS_printf("  MissionMsg.Count:            	  %llu\n", CVT.MissionMsg.Count);
		OS_printf("  MissionMsg.CurrentSeq:           %llu\n", CVT.MissionMsg.CurrentSeq);
		OS_printf("\n");
	}

	if(n==4 || n==10){
		OS_printf("  VehicleGpsPositionMsg.Timestamp:            %llu\n", CVT.VehicleGpsPositionMsg.Timestamp);
		OS_printf("  VehicleGpsPositionMsg.TimeUtcUsec:          %llu\n", CVT.VehicleGpsPositionMsg.TimeUtcUsec);
		OS_printf("  VehicleGpsPositionMsg.Lat:            		 %ld\n", CVT.VehicleGpsPositionMsg.Lat);
		OS_printf("  VehicleGpsPositionMsg.Lon:                  %ld\n", CVT.VehicleGpsPositionMsg.Lon);
		OS_printf("  VehicleGpsPositionMsg.Alt:                  %ld\n", CVT.VehicleGpsPositionMsg.Alt);
		OS_printf("  VehicleGpsPositionMsg.AltEllipsoid:         %ld\n", CVT.VehicleGpsPositionMsg.AltEllipsoid);
		OS_printf("  VehicleGpsPositionMsg.SVariance:            %f\n", CVT.VehicleGpsPositionMsg.SVariance);
		OS_printf("  VehicleGpsPositionMsg.CVariance:            %f\n", CVT.VehicleGpsPositionMsg.CVariance);
		OS_printf("  VehicleGpsPositionMsg.EpH:                  %f\n", CVT.VehicleGpsPositionMsg.EpH);
		OS_printf("  VehicleGpsPositionMsg.EpV:                  %f\n", CVT.VehicleGpsPositionMsg.EpV);
		OS_printf("  VehicleGpsPositionMsg.HDOP:                 %f\n", CVT.VehicleGpsPositionMsg.HDOP);
		OS_printf("  VehicleGpsPositionMsg.VDOP:                 %f\n", CVT.VehicleGpsPositionMsg.VDOP);
		OS_printf("  VehicleGpsPositionMsg.NoisePerMs:           %ld\n", CVT.VehicleGpsPositionMsg.NoisePerMs);
		OS_printf("  VehicleGpsPositionMsg.JammingIndicator:     %ld\n", CVT.VehicleGpsPositionMsg.JammingIndicator);
		OS_printf("  VehicleGpsPositionMsg.Vel_m_s:              %f\n", CVT.VehicleGpsPositionMsg.Vel_m_s);
		OS_printf("  VehicleGpsPositionMsg.Vel_n_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_n_m_s);
		OS_printf("  VehicleGpsPositionMsg.Vel_e_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_e_m_s);
		OS_printf("  VehicleGpsPositionMsg.Vel_d_m_s:            %f\n", CVT.VehicleGpsPositionMsg.Vel_d_m_s);
		OS_printf("  VehicleGpsPositionMsg.COG:                  %f\n", CVT.VehicleGpsPositionMsg.COG);
		OS_printf("  VehicleGpsPositionMsg.TimestampTimeRelative:%ld\n", CVT.VehicleGpsPositionMsg.TimestampTimeRelative);
		OS_printf("  VehicleGpsPositionMsg.FixType:              %u\n", CVT.VehicleGpsPositionMsg.FixType);
		OS_printf("  VehicleGpsPositionMsg.VelNedValid:          %d\n", CVT.VehicleGpsPositionMsg.VelNedValid);
		OS_printf("  VehicleGpsPositionMsg.SatellitesUsed:       %u\n", CVT.VehicleGpsPositionMsg.SatellitesUsed);
		OS_printf("\n");
	}

	if(n==5 || n==10){
		OS_printf("  VehicleGlobalPosition.Timestamp:            %llu\n", CVT.VehicleGlobalPosition.Timestamp);
		OS_printf("  VehicleGlobalPosition.TimeUtcUsec:          %llu\n", CVT.VehicleGlobalPosition.TimeUtcUsec);
		OS_printf("  VehicleGlobalPosition.Lat:                  %lld\n", CVT.VehicleGlobalPosition.Lat);
		OS_printf("  VehicleGlobalPosition.Lon:                  %lld\n", CVT.VehicleGlobalPosition.Lon);
		OS_printf("  VehicleGlobalPosition.Alt:                  %f\n", CVT.VehicleGlobalPosition.Alt);
		OS_printf("  VehicleGlobalPosition.VelN:                 %f\n", CVT.VehicleGlobalPosition.VelN);
		OS_printf("  VehicleGlobalPosition.VelE:                 %f\n", CVT.VehicleGlobalPosition.VelE);
		OS_printf("  VehicleGlobalPosition.VelD:                 %f\n", CVT.VehicleGlobalPosition.VelD);
		OS_printf("  VehicleGlobalPosition.Yaw:                  %f\n", CVT.VehicleGlobalPosition.Yaw);
		OS_printf("  VehicleGlobalPosition.EpH:                  %f\n", CVT.VehicleGlobalPosition.EpH);
		OS_printf("  VehicleGlobalPosition.EpV:                  %f\n", CVT.VehicleGlobalPosition.EpV);
		OS_printf("  VehicleGlobalPosition.TerrainAlt:           %f\n", CVT.VehicleGlobalPosition.TerrainAlt);
		OS_printf("  VehicleGlobalPosition.PressureAlt:          %f\n", CVT.VehicleGlobalPosition.PressureAlt);
		OS_printf("  VehicleGlobalPosition.TerrainAltValid:      %d\n", CVT.VehicleGlobalPosition.TerrainAltValid);
		OS_printf("  VehicleGlobalPosition.DeadReckoning:        %d\n", CVT.VehicleGlobalPosition.DeadReckoning);
		OS_printf("\n");
	}

	if(n==6 || n==10){
		OS_printf("  VehicleStatusMsg.Timestamp:                    %llu\n", CVT.VehicleStatusMsg.Timestamp);
		OS_printf("  VehicleStatusMsg.SystemID:                     %u\n", CVT.VehicleStatusMsg.SystemID);
		OS_printf("  VehicleStatusMsg.ComponentID:                  %u\n", CVT.VehicleStatusMsg.ComponentID);
		OS_printf("  VehicleStatusMsg.OnboardControlSensorsPresent: %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsPresent);
		OS_printf("  VehicleStatusMsg.OnboardControlSensorsEnabled: %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsEnabled);
		OS_printf("  VehicleStatusMsg.OnboardControlSensorsHealth:  %u\n", CVT.VehicleStatusMsg.OnboardControlSensorsHealth);
		OS_printf("  VehicleStatusMsg.NavState:                     %u\n", CVT.VehicleStatusMsg.NavState);
		OS_printf("  VehicleStatusMsg.ArmingState:                  %u\n", CVT.VehicleStatusMsg.ArmingState);
		OS_printf("  VehicleStatusMsg.HilState:                     %u\n", CVT.VehicleStatusMsg.HilState);
		OS_printf("  VehicleStatusMsg.Failsafe:                     %u\n", CVT.VehicleStatusMsg.Failsafe);
		OS_printf("  VehicleStatusMsg.SystemType:                   %u\n", CVT.VehicleStatusMsg.SystemType);
		OS_printf("  VehicleStatusMsg.IsRotaryWing:                 %u\n", CVT.VehicleStatusMsg.IsRotaryWing);
		OS_printf("  VehicleStatusMsg.IsVtol:                       %u\n", CVT.VehicleStatusMsg.IsVtol);
		OS_printf("  VehicleStatusMsg.VtolFwPermanentStab:          %u\n", CVT.VehicleStatusMsg.VtolFwPermanentStab);
		OS_printf("  VehicleStatusMsg.InTransitionMode:             %u\n", CVT.VehicleStatusMsg.InTransitionMode);
		OS_printf("  VehicleStatusMsg.RcSignalLost:                 %u\n", CVT.VehicleStatusMsg.RcSignalLost);
		OS_printf("  VehicleStatusMsg.RcInputMode:                  %u\n", CVT.VehicleStatusMsg.RcInputMode);
		OS_printf("  VehicleStatusMsg.DataLinkLost:                 %u\n", CVT.VehicleStatusMsg.DataLinkLost);
		OS_printf("  VehicleStatusMsg.DataLinkLostCounter:          %u\n", CVT.VehicleStatusMsg.DataLinkLostCounter);
		OS_printf("  VehicleStatusMsg.EngineFailure:                %u\n", CVT.VehicleStatusMsg.EngineFailure);
		OS_printf("  VehicleStatusMsg.EngineFailureCmd:             %u\n", CVT.VehicleStatusMsg.EngineFailureCmd);
		OS_printf("  VehicleStatusMsg.MissionFailure:               %u\n", CVT.VehicleStatusMsg.MissionFailure);
		OS_printf("\n");
	}

	if(n==7 || n==10){
		OS_printf("  VehicleLandDetectedMsg.Timestamp:            %llu\n", CVT.VehicleLandDetectedMsg.Timestamp);
		OS_printf("  VehicleLandDetectedMsg.AltMax:               %f\n", CVT.VehicleLandDetectedMsg.AltMax);
		OS_printf("  VehicleLandDetectedMsg.Landed:               %d\n", CVT.VehicleLandDetectedMsg.Landed);
		OS_printf("  VehicleLandDetectedMsg.Freefall:             %d\n", CVT.VehicleLandDetectedMsg.Freefall);
		OS_printf("  VehicleLandDetectedMsg.GroundContact:        %d\n", CVT.VehicleLandDetectedMsg.GroundContact);
		OS_printf("\n");
	}

	if(n==8 || n==10){
		OS_printf("  VehicleLocalPositionMsg.Timestamp:               %llu\n", CVT.VehicleLocalPositionMsg.Timestamp);
		OS_printf("  VehicleLocalPositionMsg.RefTimestamp:            %llu\n", CVT.VehicleLocalPositionMsg.RefTimestamp);
		OS_printf("  VehicleLocalPositionMsg.RefLat:                  %lld\n", CVT.VehicleLocalPositionMsg.RefLat);
		OS_printf("  VehicleLocalPositionMsg.RefLon:                  %lld\n", CVT.VehicleLocalPositionMsg.RefLon);
		OS_printf("  VehicleLocalPositionMsg.SurfaceBottomTimestamp:  %llu\n", CVT.VehicleLocalPositionMsg.SurfaceBottomTimestamp);
		OS_printf("  VehicleLocalPositionMsg.X:                       %f\n", CVT.VehicleLocalPositionMsg.X);
		OS_printf("  VehicleLocalPositionMsg.Y:                       %f\n", CVT.VehicleLocalPositionMsg.Y);
		OS_printf("  VehicleLocalPositionMsg.Z:                       %f\n", CVT.VehicleLocalPositionMsg.Z);
		OS_printf("  VehicleLocalPositionMsg.Delta_XY[2]:             [%f,%f]\n", CVT.VehicleLocalPositionMsg.Delta_XY[0],CVT.VehicleLocalPositionMsg.Delta_XY[1]);
		OS_printf("  VehicleLocalPositionMsg.Delta_Z:            	  %f\n", CVT.VehicleLocalPositionMsg.Delta_Z);
		OS_printf("  VehicleLocalPositionMsg.VX:                      %f\n", CVT.VehicleLocalPositionMsg.VX);
		OS_printf("  VehicleLocalPositionMsg.VY:                      %f\n", CVT.VehicleLocalPositionMsg.VY);
		OS_printf("  VehicleLocalPositionMsg.VZ:                      %f\n", CVT.VehicleLocalPositionMsg.VZ);
		OS_printf("  VehicleLocalPositionMsg.Delta_VXY[2]:            [%f,%f]\n", CVT.VehicleLocalPositionMsg.Delta_VXY[0],CVT.VehicleLocalPositionMsg.Delta_VXY[1]);
		OS_printf("  VehicleLocalPositionMsg.Delta_VZ:                %f\n", CVT.VehicleLocalPositionMsg.Delta_VZ);
		OS_printf("  VehicleLocalPositionMsg.AX:                      %f\n", CVT.VehicleLocalPositionMsg.AX);
		OS_printf("  VehicleLocalPositionMsg.AY:                      %f\n", CVT.VehicleLocalPositionMsg.AY);
		OS_printf("  VehicleLocalPositionMsg.AZ:                      %f\n", CVT.VehicleLocalPositionMsg.AZ);
		OS_printf("  VehicleLocalPositionMsg.Yaw:                     %f\n", CVT.VehicleLocalPositionMsg.Yaw);
		OS_printf("  VehicleLocalPositionMsg.RefAlt:                  %f\n", CVT.VehicleLocalPositionMsg.RefAlt);
		OS_printf("  VehicleLocalPositionMsg.DistBottom:              %f\n", CVT.VehicleLocalPositionMsg.DistBottom);
		OS_printf("  VehicleLocalPositionMsg.DistBottomRate:          %f\n", CVT.VehicleLocalPositionMsg.DistBottomRate);
		OS_printf("  VehicleLocalPositionMsg.EpH:                     %f\n", CVT.VehicleLocalPositionMsg.EpH);
		OS_printf("  VehicleLocalPositionMsg.EpV:                     %f\n", CVT.VehicleLocalPositionMsg.EpV);
		OS_printf("  VehicleLocalPositionMsg.EvH:                     %f\n", CVT.VehicleLocalPositionMsg.EvH);
		OS_printf("  VehicleLocalPositionMsg.EvV:                     %f\n", CVT.VehicleLocalPositionMsg.EvV);
		OS_printf("  VehicleLocalPositionMsg.EstimatorType:           %u\n", CVT.VehicleLocalPositionMsg.EstimatorType);
		OS_printf("  VehicleLocalPositionMsg.XY_Valid:                %d\n", CVT.VehicleLocalPositionMsg.XY_Valid);
		OS_printf("  VehicleLocalPositionMsg.Z_Valid:                 %d\n", CVT.VehicleLocalPositionMsg.Z_Valid);
		OS_printf("  VehicleLocalPositionMsg.V_XY_Valid:              %d\n", CVT.VehicleLocalPositionMsg.V_XY_Valid);
		OS_printf("  VehicleLocalPositionMsg.V_Z_Valid:               %d\n", CVT.VehicleLocalPositionMsg.V_Z_Valid);
		OS_printf("  VehicleLocalPositionMsg.XY_ResetCounter:         %u\n", CVT.VehicleLocalPositionMsg.XY_ResetCounter);
		OS_printf("  VehicleLocalPositionMsg.Z_ResetCounter:          %u\n", CVT.VehicleLocalPositionMsg.Z_ResetCounter);
		OS_printf("  VehicleLocalPositionMsg.VXY_ResetCounter:        %u\n", CVT.VehicleLocalPositionMsg.VXY_ResetCounter);
		OS_printf("  VehicleLocalPositionMsg.VZ_ResetCounter:         %u\n", CVT.VehicleLocalPositionMsg.VZ_ResetCounter);
		OS_printf("  VehicleLocalPositionMsg.XY_Global:               %d\n", CVT.VehicleLocalPositionMsg.XY_Global);
		OS_printf("  VehicleLocalPositionMsg.Z_Global:                %d\n", CVT.VehicleLocalPositionMsg.Z_Global);
		OS_printf("  VehicleLocalPositionMsg.DistBottomValid:         %d\n", CVT.VehicleLocalPositionMsg.DistBottomValid);
		OS_printf("\n");
	}

	if(n==9 || n==10){
		OS_printf("  VehicleCommandMsg.Timestamp:         %llu\n", CVT.VehicleCommandMsg.Timestamp);
		OS_printf("  VehicleCommandMsg.Param5:            %lld\n", CVT.VehicleCommandMsg.Param5);
		OS_printf("  VehicleCommandMsg.Param6:            %lld\n", CVT.VehicleCommandMsg.Param6);
		OS_printf("  VehicleCommandMsg.Param1:            %f\n", CVT.VehicleCommandMsg.Param1);
		OS_printf("  VehicleCommandMsg.Param2:            %f\n", CVT.VehicleCommandMsg.Param2);
		OS_printf("  VehicleCommandMsg.Param3:            %f\n", CVT.VehicleCommandMsg.Param3);
		OS_printf("  VehicleCommandMsg.Param4:            %f\n", CVT.VehicleCommandMsg.Param4);
		OS_printf("  VehicleCommandMsg.Param7:            %f\n", CVT.VehicleCommandMsg.Param7);
		OS_printf("  VehicleCommandMsg.Command:           %d\n", CVT.VehicleCommandMsg.Command);
		OS_printf("  VehicleCommandMsg.TargetSystem:      %lu\n", CVT.VehicleCommandMsg.TargetSystem);
		OS_printf("  VehicleCommandMsg.TargetComponent:   %lu\n", CVT.VehicleCommandMsg.TargetComponent);
		OS_printf("  VehicleCommandMsg.SourceSystem:      %lu\n", CVT.VehicleCommandMsg.SourceSystem);
		OS_printf("  VehicleCommandMsg.SourceComponent:   %lu\n", CVT.VehicleCommandMsg.SourceComponent);
		OS_printf("  VehicleCommandMsg.Confirmation:      %u\n", CVT.VehicleCommandMsg.Confirmation);
		OS_printf("\n\n");
	}
}

void NAV::DisplayOutputs(int n){
	OS_printf("NAV::DisplayOutputs  *************\n");

	if(n==1 || n==10){
		OS_printf("  PositionSetpointTripletMsg.Timestamp:           %llu\n", PositionSetpointTripletMsg.Timestamp);
		OS_printf("   Previous - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Previous.Timestamp);
		OS_printf("   Previous - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Previous.Lat);
		OS_printf("   Previous - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Previous.Lon);
		OS_printf("   Previous - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Previous.X);
		OS_printf("   Previous - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Previous.Y);
		OS_printf("   Previous - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Previous.Z);
		OS_printf("   Previous - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Previous.VX);
		OS_printf("   Previous - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Previous.VY);
		OS_printf("   Previous - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Previous.VZ);
		OS_printf("   Previous - PositionSetpoint.Alt:            	  %f\n", PositionSetpointTripletMsg.Previous.Alt);
		OS_printf("   Previous - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Previous.Yaw);
		OS_printf("   Previous - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Previous.Yawspeed);
		OS_printf("   Previous - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Previous.LoiterRadius);
		OS_printf("   Previous - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Previous.PitchMin);
		OS_printf("   Previous - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Previous.AX);
		OS_printf("   Previous - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Previous.AY);
		OS_printf("   Previous - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Previous.AZ);
		OS_printf("   Previous - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Previous.AcceptanceRadius);
		OS_printf("   Previous - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Previous.CruisingSpeed);
		OS_printf("   Previous - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Previous.CruisingThrottle);
		OS_printf("   Previous - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Previous.Valid);
		OS_printf("   Previous - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Previous.Type);
		OS_printf("   Previous - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Previous.PositionValid);
		OS_printf("   Previous - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Previous.VelocityFrame);
		OS_printf("   Previous - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Previous.AltValid);
		OS_printf("   Previous - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Previous.YawValid);
		OS_printf("   Previous - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Previous.DisableMcYawControl);
		OS_printf("   Previous - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Previous.YawspeedValid);
		OS_printf("   Previous - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Previous.LoiterDirection);
		OS_printf("   Previous - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Previous.AccelerationValid);
		OS_printf("   Previous - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Previous.AccelerationIsForce);

		OS_printf("   Current - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Current.Timestamp);
		OS_printf("   Current - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Current.Lat);
		OS_printf("   Current - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Current.Lon);
		OS_printf("   Current - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Current.X);
		OS_printf("   Current - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Current.Y);
		OS_printf("   Current - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Current.Z);
		OS_printf("   Current - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Current.VX);
		OS_printf("   Current - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Current.VY);
		OS_printf("   Current - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Current.VZ);
		OS_printf("   Current - PositionSetpoint.Alt:            	 %f\n", PositionSetpointTripletMsg.Current.Alt);
		OS_printf("   Current - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Current.Yaw);
		OS_printf("   Current - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Current.Yawspeed);
		OS_printf("   Current - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Current.LoiterRadius);
		OS_printf("   Current - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Current.PitchMin);
		OS_printf("   Current - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Current.AX);
		OS_printf("   Current - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Current.AY);
		OS_printf("   Current - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Current.AZ);
		OS_printf("   Current - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Current.AcceptanceRadius);
		OS_printf("   Current - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Current.CruisingSpeed);
		OS_printf("   Current - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Current.CruisingThrottle);
		OS_printf("   Current - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Current.Valid);
		OS_printf("   Current - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Current.Type);
		OS_printf("   Current - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Current.PositionValid);
		OS_printf("   Current - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Current.VelocityFrame);
		OS_printf("   Current - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Current.AltValid);
		OS_printf("   Current - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Current.YawValid);
		OS_printf("   Current - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Current.DisableMcYawControl);
		OS_printf("   Current - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Current.YawspeedValid);
		OS_printf("   Current - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Current.LoiterDirection);
		OS_printf("   Current - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Current.AccelerationValid);
		OS_printf("   Current - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Current.AccelerationIsForce);

		OS_printf("   Next - PositionSetpoint.Timestamp:          %llu\n", PositionSetpointTripletMsg.Next.Timestamp);
		OS_printf("   Next - PositionSetpoint.Lat:                %lld\n", PositionSetpointTripletMsg.Next.Lat);
		OS_printf("   Next - PositionSetpoint.Lon:                %lld\n", PositionSetpointTripletMsg.Next.Lon);
		OS_printf("   Next - PositionSetpoint.X:                  %f\n", PositionSetpointTripletMsg.Next.X);
		OS_printf("   Next - PositionSetpoint.Y:                  %f\n", PositionSetpointTripletMsg.Next.Y);
		OS_printf("   Next - PositionSetpoint.Z:                  %f\n", PositionSetpointTripletMsg.Next.Z);
		OS_printf("   Next - PositionSetpoint.VX:                 %f\n", PositionSetpointTripletMsg.Next.VX);
		OS_printf("   Next - PositionSetpoint.VY:                 %f\n", PositionSetpointTripletMsg.Next.VY);
		OS_printf("   Next - PositionSetpoint.VZ:                 %f\n", PositionSetpointTripletMsg.Next.VZ);
		OS_printf("   Next - PositionSetpoint.Alt:            	  %f\n", PositionSetpointTripletMsg.Next.Alt);
		OS_printf("   Next - PositionSetpoint.Yaw:                %f\n", PositionSetpointTripletMsg.Next.Yaw);
		OS_printf("   Next - PositionSetpoint.Yawspeed:           %f\n", PositionSetpointTripletMsg.Next.Yawspeed);
		OS_printf("   Next - PositionSetpoint.LoiterRadius:       %f\n", PositionSetpointTripletMsg.Next.LoiterRadius);
		OS_printf("   Next - PositionSetpoint.PitchMin:           %f\n", PositionSetpointTripletMsg.Next.PitchMin);
		OS_printf("   Next - PositionSetpoint.AX:                 %f\n", PositionSetpointTripletMsg.Next.AX);
		OS_printf("   Next - PositionSetpoint.AY:                 %f\n", PositionSetpointTripletMsg.Next.AY);
		OS_printf("   Next - PositionSetpoint.AZ:                 %f\n", PositionSetpointTripletMsg.Next.AZ);
		OS_printf("   Next - PositionSetpoint.AcceptanceRadius:   %f\n", PositionSetpointTripletMsg.Next.AcceptanceRadius);
		OS_printf("   Next - PositionSetpoint.CruisingSpeed:      %f\n", PositionSetpointTripletMsg.Next.CruisingSpeed);
		OS_printf("   Next - PositionSetpoint.CruisingThrottle:   %f\n", PositionSetpointTripletMsg.Next.CruisingThrottle);
		OS_printf("   Next - PositionSetpoint.Valid:              %d\n", PositionSetpointTripletMsg.Next.Valid);
		OS_printf("   Next - PositionSetpoint.Type:               %d\n", PositionSetpointTripletMsg.Next.Type);
		OS_printf("   Next - PositionSetpoint.PositionValid:      %d\n", PositionSetpointTripletMsg.Next.PositionValid);
		OS_printf("   Next - PositionSetpoint.VelocityFrame:      %d\n", PositionSetpointTripletMsg.Next.VelocityFrame);
		OS_printf("   Next - PositionSetpoint.AltValid:           %d\n", PositionSetpointTripletMsg.Next.AltValid);
		OS_printf("   Next - PositionSetpoint.YawValid:           %d\n", PositionSetpointTripletMsg.Next.YawValid);
		OS_printf("   Next - PositionSetpoint.DisableMcYawControl:%d\n", PositionSetpointTripletMsg.Next.DisableMcYawControl);
		OS_printf("   Next - PositionSetpoint.YawspeedValid:      %d\n", PositionSetpointTripletMsg.Next.YawspeedValid);
		OS_printf("   Next - PositionSetpoint.LoiterDirection:    %d\n", PositionSetpointTripletMsg.Next.LoiterDirection);
		OS_printf("   Next - PositionSetpoint.AccelerationValid:  %d\n", PositionSetpointTripletMsg.Next.AccelerationValid);
		OS_printf("   Next - PositionSetpoint.AccelerationIsForce:%d\n", PositionSetpointTripletMsg.Next.AccelerationIsForce);
		OS_printf("\n");
	}


	if(n==2 || n==10){
		OS_printf("  GeofenceResultMsg.Timestamp:            %llu\n", GeofenceResultMsg.Timestamp);
		OS_printf("  GeofenceResultMsg.GeofenceViolated:     %d\n", GeofenceResultMsg.GeofenceViolated);
		OS_printf("  GeofenceResultMsg.GeofenceAction:       %d\n", GeofenceResultMsg.GeofenceAction);
		OS_printf("\n");
	}

	if(n==3 || n==10){
		OS_printf("  ActuatorControls3Msg.Timestamp:            %llu\n", ActuatorControls3Msg.Timestamp);
		OS_printf("  ActuatorControls3Msg.SampleTime:           %llu\n", ActuatorControls3Msg.SampleTime);
		for(int c=0;c<sizeof(ActuatorControls3Msg.Control);c++){
			OS_printf("  ActuatorControls3Msg.Control[%d]:          %f\n", c,ActuatorControls3Msg.Control[c]);
		}
		OS_printf("\n");
	}

	if(n==4 || n==10){
		OS_printf("  FenceMsg.Timestamp:                    %llu\n", FenceMsg.Timestamp);
		OS_printf("  FenceMsg.Count:                        %ld\n", FenceMsg.Count);
		for(int v=0;v<sizeof(FenceMsg.Vertices);v++){
			OS_printf("  FenceMsg.Vertices[%d].Lat:             %f\n", v,FenceMsg.Vertices[v].Lat);
			OS_printf("  FenceMsg.Vertices[%d].Lon:             %f\n", v,FenceMsg.Vertices[v].Lon);
		}
		OS_printf("\n");
	}

	if(n==5 || n==10){
		OS_printf("  VehicleLandDetectedMsg.Timestamp:            %llu\n", VehicleLandDetectedMsg.Timestamp);
		OS_printf("  VehicleLandDetectedMsg.AltMax:               %f\n", VehicleLandDetectedMsg.AltMax);
		OS_printf("  VehicleLandDetectedMsg.Landed:               %d\n", VehicleLandDetectedMsg.Landed);
		OS_printf("  VehicleLandDetectedMsg.Freefall:             %d\n", VehicleLandDetectedMsg.Freefall);
		OS_printf("  VehicleLandDetectedMsg.GroundContact:        %d\n", VehicleLandDetectedMsg.GroundContact);
		OS_printf("\n");
	}

	if(n==6 || n==10){
		OS_printf("  MissionResultMsg.Timestamp:               %llu\n", MissionResultMsg.Timestamp);
		OS_printf("  MissionResultMsg.InstanceCount:           %ld\n", MissionResultMsg.InstanceCount);
		OS_printf("  MissionResultMsg.SeqReached:              %ld\n", MissionResultMsg.SeqReached);
		OS_printf("  MissionResultMsg.ItemChangedIndex:        %ld\n", MissionResultMsg.ItemChangedIndex);
		OS_printf("  MissionResultMsg.ItemDoJumpRemaining:     %ld\n", MissionResultMsg.ItemDoJumpRemaining);
		OS_printf("  MissionResultMsg.Valid:                   %d\n", MissionResultMsg.Valid);
		OS_printf("  MissionResultMsg.Warning:                 %d\n", MissionResultMsg.Warning);
		OS_printf("  MissionResultMsg.Reached:                 %d\n", MissionResultMsg.Reached);
		OS_printf("  MissionResultMsg.Finished:                %d\n", MissionResultMsg.Finished);
		OS_printf("  MissionResultMsg.StayInFailsafe:          %d\n", MissionResultMsg.StayInFailsafe);
		OS_printf("  MissionResultMsg.FlightTermination:       %d\n", MissionResultMsg.FlightTermination);
		OS_printf("  MissionResultMsg.ItemDoJumpChanged:       %d\n", MissionResultMsg.ItemDoJumpChanged);
		OS_printf("  MissionResultMsg.MissionFailure:          %d\n", MissionResultMsg.MissionFailure);
		OS_printf("\n");
	}

	if(n==7 || n==10){
		OS_printf("  VehicleCommandMsgOut.Timestamp:         %llu\n", VehicleCommandMsgOut.Timestamp);
		OS_printf("  VehicleCommandMsgOut.Param5:            %lld\n", VehicleCommandMsgOut.Param5);
		OS_printf("  VehicleCommandMsgOut.Param6:            %lld\n", VehicleCommandMsgOut.Param6);
		OS_printf("  VehicleCommandMsgOut.Param1:            %f\n", VehicleCommandMsgOut.Param1);
		OS_printf("  VehicleCommandMsgOut.Param2:            %f\n", VehicleCommandMsgOut.Param2);
		OS_printf("  VehicleCommandMsgOut.Param3:            %f\n", VehicleCommandMsgOut.Param3);
		OS_printf("  VehicleCommandMsgOut.Param4:            %f\n", VehicleCommandMsgOut.Param4);
		OS_printf("  VehicleCommandMsgOut.Param7:            %f\n", VehicleCommandMsgOut.Param7);
		OS_printf("  VehicleCommandMsgOut.Command:           %d\n", VehicleCommandMsgOut.Command);
		OS_printf("  VehicleCommandMsgOut.TargetSystem:      %lu\n", VehicleCommandMsgOut.TargetSystem);
		OS_printf("  VehicleCommandMsgOut.TargetComponent:   %lu\n", VehicleCommandMsgOut.TargetComponent);
		OS_printf("  VehicleCommandMsgOut.SourceSystem:      %lu\n", VehicleCommandMsgOut.SourceSystem);
		OS_printf("  VehicleCommandMsgOut.SourceComponent:   %lu\n", VehicleCommandMsgOut.SourceComponent);
		OS_printf("  VehicleCommandMsgOut.Confirmation:      %u\n", VehicleCommandMsgOut.Confirmation);
		OS_printf("\n\n");
	}
}



/************************/
/*  End of File Comment */
/************************/
