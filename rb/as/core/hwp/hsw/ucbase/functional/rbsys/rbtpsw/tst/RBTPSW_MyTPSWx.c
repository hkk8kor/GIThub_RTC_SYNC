/**
 * @ingroup 'SW-group'
 * @{
 *
 * \file
 * \brief 'Short description of this module, up to 80 characters
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"
#include "RBSYS_uCRegisters.h"  // peripheral labels


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSWx.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

void TPSW5_DummyFunc (void) {}
void TPSW6_DummyFunc (void) {}
void TPSW7_DummyFunc (void) {}
void TPSW8_DummyFunc (void) {}
void TPSW9_DummyFunc (void) {}
void TPSW10_DummyFunc(void) {}

/* Good Case - With Return */

uint32 BackgroundTestApp_Ret_1_GoodCase_WaitingFunction(uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_2_GoodCase_WaitingFunction(uint32 param1, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_3_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_4_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_5_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_6_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_7_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_8_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_9_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 param8, uint32 limit)
{
    return 0;
}

uint32 BackgroundTestApp_Ret_0_GoodCase_WaitingFunction(void)
{
    return 0;
}

/* Good Case - No Return */
void BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction(uint32 limit)
{

}


void BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction(uint32 param1, uint32 limit)
{

}

void BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 limit)
{

}

void BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 limit)
{

}

void BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 limit)
{

}

void BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 limit)
{

}

void BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 limit)
{

}

void BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 limit)
{

}

void BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 param8, uint32 limit)
{

}

void BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction(void)
{

}


uint32 BackgroundTestApp_WaitingFunction(Os_StopwatchTickType duration)
{
    WaitingFunction(duration);
    return 0;
}

uint32 BackgroundTestApp_WaitingFunction_DynLimit(Os_StopwatchTickType duration)
{
    WaitingFunction(duration);
    return 0;
}

/* Bad Case - With Return */
uint32 BackgroundTestApp_Ret_1_BadCase_WaitingFunction(uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_1_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_2_BadCase_WaitingFunction(uint32 param1, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_2_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_3_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_3_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_4_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_4_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_5_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_5_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_6_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_6_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_7_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_7_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_8_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_8_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_9_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 param8, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_Ret_9_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

uint32 BackgroundTestApp_Ret_0_BadCase_WaitingFunction(void)
{
    WaitingFunction(BackgroundTestApp_Ret_0_BADCASE_WAITINGFUNCTION_TIMELIMIT);
    return 0;
}

/* Bad Case - No Return */
void BackgroundTestApp_NoRet_1_BadCase_WaitingFunction(uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_1_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_2_BadCase_WaitingFunction(uint32 param1, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_2_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_3_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_3_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_4_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_4_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_5_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_5_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_6_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_6_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_7_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_7_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_8_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_8_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_9_BadCase_WaitingFunction(uint32 param1, uint32 param2, uint32 param3, uint32 param4, uint32 param5, uint32 param6, uint32 param7, uint32 param8, uint32 limit)
{
    WaitingFunction(BackgroundTestApp_NoRet_9_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

void BackgroundTestApp_NoRet_0_BadCase_WaitingFunction(void)
{
    WaitingFunction(BackgroundTestApp_NoRet_0_BADCASE_WAITINGFUNCTION_TIMELIMIT);
}

#endif

/** @} */
/* End ingroup 'SW-group' */
