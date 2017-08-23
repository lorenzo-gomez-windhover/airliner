
#include "to_app_custom_test.h"
#include "to_custom_test_utils.h"
#include "to_platform_stubs.h"

#include "uttest.h"
#include "ut_osapi_stubs.h"
#include "ut_cfe_sb_stubs.h"
#include "ut_cfe_sb_hooks.h"
#include "ut_cfe_es_stubs.h"
#include "ut_cfe_es_hooks.h"
#include "ut_cfe_evs_stubs.h"
#include "ut_cfe_evs_hooks.h"
#include "ut_cfe_time_stubs.h"
#include "ut_cfe_psp_memutils_stubs.h"
#include "ut_cfe_tbl_stubs.h"
#include "ut_cfe_fs_stubs.h"
#include "ut_cfe_time_stubs.h"


/**************************************************************************
 * Tests for TO_Custom_Init()
 **************************************************************************/
/**
 * Test TO_Custom_Init() fail TO_Channel_OpenChannel()
 */
void TO_Custom_Init_OpenChannelFail(void)
{
    int32 result = 0;
    int32 expected = 1;
    
    TO_App_Return.TO_Channel_OpenChannel_Return = 1;
    
    /* Execute the function being tested */
    result = TO_Custom_Init();
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_Custom_Init() did not return an expected value");
}


/**
 * Test TO_Custom_Init() fail TO_OutputChannel_Enable()
 */
void TO_Custom_Init_EnableChannelFail(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint8 ChannelID = 0;
    
    /* Set channel 0 to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    
    /* Set socket call in TO_OutputChannel_Enable to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = -1;
    
    /* Execute the function being tested */
    result = TO_Custom_Init();
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_Custom_Init() did not return an expected value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                "TO_Custom_Init() did not set correct mode");
}


/**
 * Test TO_Custom_Init() nothing enabled
 */
void TO_Custom_Init_NothingEnabled(void)
{
    int32 result = -1;
    int32 expected = 0;

    /* Execute the function being tested */
    result = TO_Custom_Init();
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_Custom_Init() did not return an expected value");
}


/**
 * Test TO_Custom_Init() nominal
 */
void TO_Custom_Init_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint8 ChannelID = 0;
    uint16 testPort = 5000;
    char *testIP = "test";
    
    char returnString[128];
    snprintf(returnString, 128, "UDP telemetry output enabled channel %u to %s:%u", 
            ChannelID, testIP, testPort);
    
    /* Set channel 0 to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    /* Set values for IP and port to help verify the raised event */
    strncpy(TO_AppCustomData.Channel[ChannelID].IP, testIP, INET_ADDRSTRLEN);
    TO_AppCustomData.Channel[ChannelID].DstPort = testPort;
    
    /* Execute the function being tested */
    result = TO_Custom_Init();
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_Custom_Init() did not return an expected value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_ENABLED, 
                "TO_Custom_Init() did not set correct mode");
    UtAssert_EventSent(TO_TLMOUTENA_INF_EID, CFE_EVS_INFORMATION, returnString, 
                "TO_Custom_Init() failed to raise an event");
}


/**************************************************************************
 * Tests for TO_OutputChannel_CustomBuildupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomBuildupAll() nominal
 * NOTE: Function is not currently implemented.
 */
void Test_TO_OutputChannel_CustomBuildupAll_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint32 index = 0;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_CustomBuildupAll(index);
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_OutputChannel_CustomBuildupAll() failed nominal");
}


/**************************************************************************
 * Tests for TO_OutputChannel_Enable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Enable() null destination address
 */
void Test_TO_OutputChannel_Enable_NullDestinationAddress(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    /* Null destination address */
    char *DestinationAddress = 0;
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "Destination address for channel %u is null.", 0);
    
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() invalid channel id
 */
void Test_TO_OutputChannel_Enable_InvalidID(void)
{
    int32 result = 0;
    int32 expected = -1;
    /* Set invalid channel ID */
    uint8 ChannelID = (TO_MAX_CHANNELS);
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "ChannelID (%u) invalid.", (TO_MAX_CHANNELS));
    
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTENA_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail socket creation
 */
void Test_TO_OutputChannel_Enable_SocketFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    int32 expectedErrno = 5;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "TLM socket errno: %i on channel %u", expectedErrno, ChannelID);
    
    /* Set socket call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = -1;
    
    /* Set errno for socket call */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno = 1;
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Errno_Value = expectedErrno;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Socket == -1,
                "TO_OutputChannel_Enable() failed to return an error");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                "TO_OutputChannel_Enable() did not set correct mode");
    UtAssert_EventSent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail bind
 */
void Test_TO_OutputChannel_Enable_BindFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    int32 expectedErrno = 5;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    char returnString[128];
    snprintf(returnString, 128, "TLM bind errno: %i on channel %u", expectedErrno, ChannelID);
    
    /* Set socket call to pass */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = 1;
    
    /* Set bind call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Return = -1;
    
    /* Set errno for bind call */
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno = 1;
    TO_Platform_Stubs_Returns.TO_Wrap_Bind_Errno_Value = expectedErrno;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                "TO_OutputChannel_Enable() did not set correct mode");
    UtAssert_EventSent(TO_TLMOUTSOCKET_ERR_EID, CFE_EVS_ERROR, returnString, 
                "TO_OutputChannel_Enable() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Enable() fail create child task
 */
void Test_TO_OutputChannel_Enable_CreateChildTaskFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    /* Set create child task to fail */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_CREATECHILDTASK_INDEX, -1, 1);
    
    /* Set socket call to pass */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = 1;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==0,"Event Count = 0");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_ENABLED, 
                "TO_OutputChannel_Enable() did not set correct mode");
}


/**
 * Test TO_OutputChannel_Enable() nominal
 */
void Test_TO_OutputChannel_Enable_Nominal(void)
{
    int32 result = -1;
    int32 expected = CFE_SUCCESS;
    uint8 ChannelID = 0;
    /* Set test destination address */
    char *DestinationAddress = "test";
    uint16 DestinationPort = 0;
    
    /* Set create child task to return success */
    Ut_CFE_ES_SetReturnCode(UT_CFE_ES_CREATECHILDTASK_INDEX, CFE_SUCCESS, 1);
    
    /* Set socket call to pass */
    TO_Platform_Stubs_Returns.TO_Wrap_Socket_Return = 1;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Enable(ChannelID, DestinationAddress, DestinationPort);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==0,"Event Count = 0");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_ENABLED, 
                "TO_OutputChannel_Enable() did not set correct mode");
}


/**************************************************************************
 * Tests for TO_OutputChannel_Send()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Send() invalid channel id
 */
void Test_TO_OutputChannel_Send_InvalidID(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint8 ChannelID = (TO_MAX_CHANNELS);
    char *testBuffer = "test";
    
    /* Execute the function being tested */
    result = TO_OutputChannel_Send(ChannelID, testBuffer, sizeof(testBuffer));
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==0,"Event Count = 0");
    UtAssert_True (result == expected, 
                "TO_OutputChannel_Enable() did not return the correct value");
}


/**
 * Test TO_OutputChannel_Send() sendto fail
 */
void Test_TO_OutputChannel_Send_SendToFail(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    char *testBuffer = "test";
    
    /* Set test channel to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    
    /* Set sendto call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Return = -1;
    /* Set errno for sendto call */
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno = 1;
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno_Value = 8;
    
    /* Call the function under test */
    result = TO_OutputChannel_Send(ChannelID, testBuffer, sizeof(testBuffer));

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(TO_AppCustomData.Channel[ChannelID].Mode == TO_CHANNEL_DISABLED, 
                "TO_OutputChannel_Send() did not set mode to disabled");
    UtAssert_True(result == expected,
                "TO_OutputChannel_Send() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTSTOP_ERR_EID, CFE_EVS_ERROR, "", 
                "TO_OutputChannel_Send() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Send() sendto fail message too long
 */
void Test_TO_OutputChannel_Send_SendToTooLong(void)
{
    int32 result = 0;
    int32 expected = -1;
    uint8 ChannelID = 0;
    char *testBuffer = "test";
    
    /* Set test channel to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    
    /* Set sendto call to fail */
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Return = -1;
    /* Set errno for sendto call */
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno = 1;
    /* Set errno message too long */
    TO_Platform_Stubs_Returns.TO_Wrap_SendTo_Errno_Value = 90;
    
    /* Call the function under test */
    result = TO_OutputChannel_Send(ChannelID, testBuffer, sizeof(testBuffer));

    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_True(result == expected,
            "TO_OutputChannel_Send() did not return the correct value");
    UtAssert_EventSent(TO_TLMOUTSTOP_ERR_EID, CFE_EVS_ERROR, "", 
            "TO_OutputChannel_Send() failed to raise an event");
}


/**
 * Test TO_OutputChannel_Send() nominal
 */
void Test_TO_OutputChannel_Send_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint8 ChannelID = 0;
    char *testBuffer = "test";
    
    /* Set test channel to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    
    /* Call the function under test */
    result = TO_OutputChannel_Send(ChannelID, testBuffer, sizeof(testBuffer));

    UtAssert_True(result == expected,
            "TO_OutputChannel_Send() did not return the correct value");
}


 /**************************************************************************
 * Tests for TO_OutputChannel_ChannelHandler()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ChannelHandler() fail OS_QueueGet
 */
void TO_OutputChannel_ChannelHandle_QueueGetFail(void)
{
    uint8 ChannelID = 0;
    
    /* Set test channel to enabled */
    TO_AppCustomData.Channel[ChannelID].Mode = TO_CHANNEL_ENABLED;
    
    /* Set all status returns after the first call to disabled 
     * NOTE: calls to TO_Channel_State sets the channel mode to
     * TO_CHANNEL_DISABLED disabled after the first call
     */
    TO_App_Return.TO_Channel_State_Return = TO_CHANNEL_OPENED;
    TO_App_Return.TO_Channel_State_Return1 = TO_CHANNEL_CLOSED;
    
    /* Set OS_QueueGet to fail with OS_ERROR */
    Ut_OSAPI_SetReturnCode(UT_OSAPI_QUEUEGET_INDEX, OS_ERROR, 1);
    
    /* Call the function under test */
    TO_OutputChannel_ChannelHandler(ChannelID);
    
    /* Verify results */
    UtAssert_True(Ut_CFE_EVS_GetEventQueueDepth()==1,"Event Count = 1");
    UtAssert_EventSent(TO_TLM_LISTEN_ERR_EID, CFE_EVS_ERROR, "", 
            "TO_OutputChannel_Send() failed to raise an event");
}


 /**************************************************************************
 * Tests for TO_OutputChannel_ProcessNewCustomCmds()
 **************************************************************************/
/**
 * Test TO_OutputChannel_ProcessNewCustomCmds()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_OnboardChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_OnboardChannelTask()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_GroundChannelTask()
 **************************************************************************/
/**
 * Test TO_OutputChannel_GroundChannelTask()
 */

 /**************************************************************************
 * Tests for TO_OutputChannel_CustomTeardownAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomTeardownAll() nominal
 * NOTE: Function is not currently implemented.
 */
 void Test_TO_OutputChannel_CustomTeardownAll_Nominal(void)
{
    int32 result = -1;
    int32 expected = 0;
    uint32 index = 0;
    
    /* Execute the function being tested */
    result = TO_OutputChannel_CustomTeardownAll(index);
    
    /* Verify results */
    UtAssert_True (result == expected, 
                "TO_OutputChannel_CustomBuildupAll() failed nominal");
}
 /**************************************************************************
 * Tests for TO_OutputChannel_CustomCleanupAll()
 **************************************************************************/
/**
 * Test TO_OutputChannel_CustomCleanupAll()
 */
 
 /**************************************************************************
 * Tests for TO_OutputChannel_Disable()
 **************************************************************************/
/**
 * Test TO_OutputChannel_Disable()
 */

void TO_Custom_App_Test_AddTestCases(void)
{
    UtTest_Add(TO_Custom_Init_OpenChannelFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_Custom_Init_OpenChannelFail");
    UtTest_Add(TO_Custom_Init_EnableChannelFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_Custom_Init_EnableChannelFail");               
    UtTest_Add(TO_Custom_Init_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_Custom_Init_Nominal"); 
    UtTest_Add(TO_Custom_Init_NothingEnabled, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_Custom_Init_NothingEnabled"); 
    UtTest_Add(Test_TO_OutputChannel_CustomBuildupAll_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_CustomBuildupAll_Nominal");
    UtTest_Add(Test_TO_OutputChannel_Enable_NullDestinationAddress, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_NullDestinationAddress");
    UtTest_Add(Test_TO_OutputChannel_Enable_InvalidID, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_InvalidID");
    UtTest_Add(Test_TO_OutputChannel_Enable_SocketFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_SocketFail");
    UtTest_Add(Test_TO_OutputChannel_Enable_BindFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_BindFail");
    UtTest_Add(Test_TO_OutputChannel_Enable_CreateChildTaskFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_CreateChildTaskFail");
    UtTest_Add(Test_TO_OutputChannel_Enable_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Enable_Nominal");
    UtTest_Add(Test_TO_OutputChannel_Send_InvalidID, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Send_InvalidID");
    UtTest_Add(Test_TO_OutputChannel_Send_SendToFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Send_SendToFail");
    UtTest_Add(Test_TO_OutputChannel_Send_SendToTooLong, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Send_SendToTooLong");
    UtTest_Add(Test_TO_OutputChannel_Send_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_Send_Nominal");
    UtTest_Add(TO_OutputChannel_ChannelHandle_QueueGetFail, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "TO_OutputChannel_ChannelHandle_QueueGetFail");



    UtTest_Add(Test_TO_OutputChannel_CustomTeardownAll_Nominal, 
                TO_Custom_Test_Setup, TO_Custom_Test_TearDown,
               "Test_TO_OutputChannel_CustomTeardownAll_Nominal");
}
