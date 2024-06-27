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
#include <string.h>
#include <assert.h>
#include "RBSYS_Intrinsics.h"
#include "RBLCF_MemoryMap.h"
#include "Os.h"
#include "Os_ConfigInterrupts.h"
#include "../src/RBTPSW_TPSWCapsule_TimerDriver.h"
#include "RBSYS_TaskInfo.h"
#include "RBTPSW_MyTPSW_RAMBackupService.h"
#include "RBSYS_CoreMpu.h"


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW1.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);



#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

/**
**********************************************************************************************
TEST STRATEGY:

 - process RBTPSW_MyTPSWCapsule_TestExecution_Proc() is called in the x2(p) task
   running on the core with the 1ms task
 - process RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc() is called in the x8 task
 - process RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc() is called in the x2(p) task not on
   the core with the 1ms task

Start of tests:
 1. RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc() starts and enters into
    an active waiting loop
 2. RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc() starts if running on a multi
    core system. It also enters an active waiting loop.
 3. RBTPSW_MyTPSWCapsule_TestExecution_Proc() starts TPSW1 and the
    TPSW2_TestWrapper if both RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc() and
    RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc() have entered the active waiting
    loop.  The actual test execution is performed in TPSW1_TestExecution() which
    is called by the TPSW2_TestWrapper().

End of test TPSW1:
 1. RBTPSW_MyTPSWCapsule_TestExecution_Proc() notifies
    RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc() and
    RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc() that the active waiting
    loops can be stopped.
 2. if TPSW1 was killed during the test (bad case), the active waiting loops will end
    when all cross core tasks are finished.
 3. The testresults are captured and an assert is raised if the test did not match the
    expected outcome

This strategy allows each test case to be executed in a cascading context (TPSW1 preempts
TPSW1 with higher priority). Moreover the test execution happens during TPSW1 runs in
parallel in another core. In this way following features can be tested when TPSW1 is killed:
 - cascading abort
 - cross core kill

TPSW2_TestCaseId: current test case id to be performed. It is automatically incremented at
each test period.

TPSW1_ForceTestId: overrides the TPSW2_TestCaseId and forces a test case to be executed.
**********************************************************************************************
**/

uint8 RBTPSW_TestExecutionProcCore = 0;
#if (RBFS_MCORE == RBFS_MCORE_ON)
uint8 RBTPSW_MultiProcCore = 0;
#endif

typedef enum {
    RBTPSW_TEST_STATUS_PASSED = 0,
    RBTPSW_TEST_STATUS_FAILED,
    RBTPSW_TEST_STATUS_FALSE_NEG,
    RBTPSW_TEST_STATUS_FALSE_POS,
    RBTPSW_TEST_STATUS_NO_RESET,
    RBTPSW_TEST_STATUS_FALSE_RESET,
}RBTPSW_TestResultStatus;

typedef struct {
    uint32 feic;
    uint32 userInfo;
    uint32 osStatus;
    rbtpsw_debugappstatus_t debugStatus;
}RBTPSW_AppResult;

typedef struct {
    RBTPSW_App_t* app;
    rbtpsw_appstatus_t expectedAppStatus;
    rbtpsw_appstatus_t actualAppStatus;
    struct {
        RBTPSW_TestResultStatus status;
        RBTPSW_AppResult expectedResult;
        RBTPSW_AppResult actualResult;
        struct {
            rbtpsw_corefnptr_t callCoreFnPtr;
            uint32             rh850_fepc;
            uint32             rh850_mei;
            uint32             rh850_mea;
            uint32             rh850_fepsw;
            uint32             rh850_fpsr;
            uint32             rh850_fpepc;
        } auxInfo;
    } coreResult[OS_NUM_CORES];
}RBTPSW_TestResult;

RBTPSW_TestResult RBTPSW_result[10] = {0};

#define TPSW_APP(NUM) (&RBTPSWAppCfg_MYTPSW##NUM)
static void RBTPSW_ResetExpectedResults(void)
{
    RBTPSW_BURAM_tests_t budata;

    //Setting everything to 0 works because that are the default values for all these fields
    memset(RBTPSW_result, 0, 10 * sizeof(RBTPSW_TestResult));
    RBTPSW_result[0].app = TPSW_APP(1);
    RBTPSW_result[1].app = TPSW_APP(2);
    RBTPSW_result[2].app = TPSW_APP(3);
    RBTPSW_result[3].app = TPSW_APP(4);
    RBTPSW_result[4].app = TPSW_APP(5);
    RBTPSW_result[5].app = TPSW_APP(6);
    RBTPSW_result[6].app = TPSW_APP(7);
    RBTPSW_result[7].app = TPSW_APP(8);
    RBTPSW_result[8].app = TPSW_APP(9);
    RBTPSW_result[9].app = TPSW_APP(10);


    budata.current_test_id = 0;
    budata.flags = 0;

    RBTPSW_setTPSWtestPersistentDataToBackupRAM(&budata);
}
#undef TPSW_APP

void RBTPSW_SetExpectedResult(uint32 tpswNum, rbtpsw_appstatus_t appStatus, uint32 feic, uint32 userInfo, uint32 osStatus, rbtpsw_debugappstatus_t debugStatus, uint32 core)
{
    RBTPSW_BURAM_tests_t budata;
    rbtpsw_CpuContext_t context = RBTPSW_Switch2PrivMode();
    assert(tpswNum < 11);
    assert(tpswNum > 0);

    budata.current_test_id = TPSW1_ForceTestId != 0 ? TPSW1_ForceTestId : TPSW2_TestCaseId;
    budata.flags = RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID;

    RBTPSW_setTPSWtestPersistentDataToBackupRAM(&budata);

    RBTPSW_result[tpswNum - 1].expectedAppStatus = appStatus;
    RBTPSW_result[tpswNum - 1].coreResult[core].expectedResult.feic = feic;
    RBTPSW_result[tpswNum - 1].coreResult[core].expectedResult.userInfo = userInfo;
    RBTPSW_result[tpswNum - 1].coreResult[core].expectedResult.osStatus = osStatus;
    RBTPSW_result[tpswNum - 1].coreResult[core].expectedResult.debugStatus = debugStatus;
    RBTPSW_RestoreMode(context);
}

void RBTPSW_SetExpectedResultToNoReaction(void)
{
    RBTPSW_BURAM_tests_t budata;
    rbtpsw_CpuContext_t context = RBTPSW_Switch2PrivMode();
    budata.current_test_id = TPSW1_ForceTestId != 0 ? TPSW1_ForceTestId : TPSW2_TestCaseId;
    budata.flags = RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID;

    RBTPSW_setTPSWtestPersistentDataToBackupRAM(&budata);
    RBTPSW_RestoreMode(context);
}

void RBTPSW_SetExpectedResultToReset(void)
{
    RBTPSW_BURAM_tests_t budata;
    rbtpsw_CpuContext_t context = RBTPSW_Switch2PrivMode();

    budata.current_test_id = TPSW1_ForceTestId != 0 ? TPSW1_ForceTestId : TPSW2_TestCaseId;
    budata.flags = RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID | RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_EXPECTED;

    RBTPSW_setTPSWtestPersistentDataToBackupRAM(&budata);
    RBTPSW_RestoreMode(context);
}

static void RBTPSW_BuramSetAssertFlag(void)
{
    RBTPSW_BURAM_tests_t budata;

    RBTPSW_getTPSWtestPersistentDataFromBackupRAM(&budata);
    budata.flags |= RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_ASSERT;
    RBTPSW_setTPSWtestPersistentDataToBackupRAM(&budata);
}

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
void MYTPSW_CHECK_SF(boolean x)
{
    if(RBTPSW_Context[RBTPSW_GetCoreID_Prv()].timing.supprFlag != (x))
    {
        rbtpsw_CpuContext_t prev = RBTPSW_Switch2PrivMode();
        MYTPSW_SupprFlagErrorCounter++;
        RBTPSW_RestoreMode(prev);
        TrustedData = 0; /*if possible kill app*/
    }
}
#endif

void TRUSTED_MoveSP(const void* stackP)
{
    asm("mov  r6, r3");
}

void* TRUSTED_GetSP(void)
{
    asm("mov  r3, r10");
    asm("jmp  [lp]");
    return NULL;
}

CoreIdType TRUSTED_GetCoreId(void)
{
    CoreIdType core;
    rbtpsw_CpuContext_t prev;

    prev = RBTPSW_Switch2PrivMode();
    core = RBTPSW_GetCoreID_Prv();
    RBTPSW_RestoreMode(prev);

    return core;
}

static volatile boolean triggerTest = false;
#if (RBFS_MCORE == RBFS_MCORE_ON)
static volatile boolean MultiCoreFinished = false;
#endif
static volatile boolean resultsFetched = false;

static uint32 RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime = 0;      // for Background test 01
uint32 RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter = 0;  // for Background test 02
static uint32 RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit = 0;

uint32 MYTPSW_SupprFlagErrorCounter = 0;

void RBTPSW_BackgroundTestApp_BgTestCases(void)
{
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        CoreIdType core;
    #endif
    rbtpsw_appstatus_t status;

    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        core = RBTPSW_GetCoreID_Prv();
    #endif

    /***************************************************
    * Background test 01
    * BackgroundTestApp_WaitingFunction() budget is 100us
    * Runtime of the function is varying from 0us to 100us:
    *  - if runtime < 100-15us --> good case
    *  - if runtime > 100-7us  --> bad case
    ***************************************************/
    {
        (void)RBTPSW_CALL(BackgroundTestApp_WaitingFunction(RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);

        if(RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime < RBSYS_convertUsecToTimerTicks(BackgroundTestApp_WAITINGFUNCTION_TIMELIMIT - 15))
        {
            if(status != ACTIVE)
            {
                RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
            }
        }
        else if(RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime > RBSYS_convertUsecToTimerTicks(BackgroundTestApp_WAITINGFUNCTION_TIMELIMIT - 7))
        {
            if(status != NOT_ACTIVE)
            {
                RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
            }
        }
        else
        {
            /* Intentionally empty. Avoiding MisraC2012-15.7. */
        }

        RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime += 2;
        if(RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime > RBSYS_convertUsecToTimerTicks(BackgroundTestApp_WAITINGFUNCTION_TIMELIMIT))
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ExecTime = 0;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    /***************************************************
    * Background test 02
    * BackgroundTestApp_WaitingFunction() budget is varying from 0us to 50us
    * Runtime of the function is 10us:
    *  - if limit > 10+15us --> good case
    *  - if limit < 10+7us  --> bad case
    ***************************************************/
    {
        (void)RBTPSW_CALL(BackgroundTestApp_WaitingFunction_DynLimit(RBSYS_convertUsecToTimerTicks(BackgroundTestApp_WAITINGFUNCTION_DYNLIMIT_RUNTIME)));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);

        if(BackgroundTestApp_WAITINGFUNCTION_DYNLIMIT_RUNTIME > (RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit+15))
        {
            if(status != ACTIVE)
            {
                RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
            }
        }
        else if(BackgroundTestApp_WAITINGFUNCTION_DYNLIMIT_RUNTIME < (RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit+7))
        {
            if(status != NOT_ACTIVE)
            {
                RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
            }
        }
        else
        {
            /* Intentionally empty. Avoiding MisraC2012-15.7. */
        }

        RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit += 1;
        if(RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit > 50)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit = 0;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    /***************************************************
    * Background test 03
    * Call good case timing protected function.
    * Set the compare register to now to trigger a dummy isr request.
    ***************************************************/
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_0_GoodCase_WaitingFunction());
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_1_GoodCase_WaitingFunction(0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_2_GoodCase_WaitingFunction(0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_3_GoodCase_WaitingFunction(0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_4_GoodCase_WaitingFunction(0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_5_GoodCase_WaitingFunction(0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_6_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_7_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_8_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_9_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0, 0));

        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction());
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction(0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction(0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction(0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction(0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction(0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0));
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    /***************************************************
    * Background test 04
    * Call Bad test case timing protected function.
    * Set the compare register to now to trigger a dummy isr request.
    ***************************************************/
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_0_BadCase_WaitingFunction());
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_1_BadCase_WaitingFunction(0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_2_BadCase_WaitingFunction(0,0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_3_BadCase_WaitingFunction(0,0,0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_4_BadCase_WaitingFunction(0,0,0,0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_5_BadCase_WaitingFunction(0, 0, 0,0,0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_6_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_7_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_8_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_Ret_9_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_0_BadCase_WaitingFunction());
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_1_BadCase_WaitingFunction(0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_2_BadCase_WaitingFunction(0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_3_BadCase_WaitingFunction(0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_4_BadCase_WaitingFunction(0, 0, 0, 0));
        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }

    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_5_BadCase_WaitingFunction(0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_6_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_7_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_8_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
    {
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        RBTPSW_TimerDriver_SetCompareRel(core, 0);
      #endif
        (void)RBTPSW_CALL(BackgroundTestApp_NoRet_9_BadCase_WaitingFunction(0, 0, 0, 0, 0, 0, 0, 0, 0));

        status = RBTPSW_GetAppStatus(BackgroundTestApp);
        if(status != NOT_ACTIVE)
        {
            RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter++;
        }

        MYTPSW_RESET_APP(BackgroundTestApp);
    }
}

//Called to schedule RBTPSW_MyTPSWCapsule_TestExecution_Proc() and RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc() on correct cores in x2 and x2p tasks
void RBTPSW_MyTPSWCapsule_CoreScheduler_Proc(void)
{
    uint8 core = RBSYS_getCoreID();
#if (RBFS_MCORE == RBFS_MCORE_ON)
    if (core == RBSYS_OS_CORE_FOR_Task1ms)
    {
        RBTPSW_TestExecutionProcCore = core;
        RBTPSW_MyTPSWCapsule_TestExecution_Proc();
    } else
    {
        RBTPSW_MultiProcCore = core;
        RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc();
    }
#else
    RBTPSW_TestExecutionProcCore = core;
    RBTPSW_MyTPSWCapsule_TestExecution_Proc();
#endif
}

static inline boolean RBTPSW_AppResultAsExpected(const RBTPSW_AppResult* expected, const RBTPSW_AppResult* actual)
{
    if ((expected->feic != RBTPSW_EXPECTEDRESULT_DONTCARE) && ((expected->feic & 0xFFFF) != (actual->feic & 0xFFFF))) //Only the lower 16bit should be compared
    {
        return false;
    }
    if ((expected->userInfo != RBTPSW_EXPECTEDRESULT_DONTCARE) && (expected->userInfo != actual->userInfo))
    {
        return false;
    }
    if ((expected->osStatus != RBTPSW_EXPECTEDRESULT_DONTCARE) && (expected->osStatus != actual->osStatus))
    {
        return false;
    }
    if (expected->debugStatus != actual->debugStatus)
    {
        return false;
    }
    return true;
}

//Return true if expected data does not match actual results occured
static boolean RBTPSW_CheckTestResultFailed(boolean fromReset)
{
    RBTPSW_BURAM_tests_t budata;
    uint32 i = 0;
    uint32 core = 0;
    boolean resetExpected = false;
    boolean reportFailure = false;

    //Check if a reset was expected
    RBTPSW_getTPSWtestPersistentDataFromBackupRAM(&budata);
    assert((budata.flags & RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID) != 0);
    resetExpected = (budata.flags & RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_EXPECTED) != 0;
    for ( i = 0; i < 10; i++)
    {
        RBTPSW_TestResult* testResult = &RBTPSW_result[i];

        RBTPSW_App_t* app = testResult->app;
        testResult->actualAppStatus   = RBTPSW_GetAppStatus_intern(app);
        for (core = 0; core < OS_NUM_CORES; core++)
        {
            rbtpsw_debuginfo_t debug = RBTPSW_GetDebugInfo_intern(app, core);
            testResult->coreResult[core].actualResult.feic        = debug.rh850_feic;
            testResult->coreResult[core].actualResult.userInfo    = debug.userinfo;
            testResult->coreResult[core].actualResult.osStatus    = debug.os_status;
            testResult->coreResult[core].actualResult.debugStatus = debug.debug_status;

            testResult->coreResult[core].auxInfo.callCoreFnPtr = debug.CallCoreFnPtr;
            testResult->coreResult[core].auxInfo.rh850_fepc    = debug.FaultAdr;
            testResult->coreResult[core].auxInfo.rh850_mei     = debug.rh850_mei;
            testResult->coreResult[core].auxInfo.rh850_mea     = debug.rh850_mea;
            testResult->coreResult[core].auxInfo.rh850_fepsw   = debug.rh850_fepsw;
            testResult->coreResult[core].auxInfo.rh850_fpsr    = debug.rh850_fpsr;
            testResult->coreResult[core].auxInfo.rh850_fpepc   = debug.rh850_fpepc;

            //Check possible reset states first as these overwrite mismatch status values
            if (resetExpected && !fromReset)
            {
                testResult->coreResult[core].status = RBTPSW_TEST_STATUS_NO_RESET;
                reportFailure = true;
            } else if (!resetExpected && fromReset)
            {
                testResult->coreResult[core].status = RBTPSW_TEST_STATUS_FALSE_RESET;
                reportFailure = true;
            } else if (resetExpected && fromReset)
            {
                //This case is handled explicitly as the data read from the TPSW app is not valid anymore after reset
                testResult->coreResult[core].status = RBTPSW_TEST_STATUS_PASSED;
            } else if ((testResult->expectedAppStatus != testResult->actualAppStatus)
                       || (!RBTPSW_AppResultAsExpected(&testResult->coreResult[core].expectedResult, &testResult->coreResult[core].actualResult)))
            {
                //Expected result does not match actual data so we save actual data for uCSim Testscripts
                if (testResult->expectedAppStatus == ACTIVE && testResult->actualAppStatus == NOT_ACTIVE)
                {
                    testResult->coreResult[core].status = RBTPSW_TEST_STATUS_FALSE_POS;
                } else if (testResult->expectedAppStatus == NOT_ACTIVE && testResult->actualAppStatus == ACTIVE)
                {
                    testResult->coreResult[core].status = RBTPSW_TEST_STATUS_FALSE_NEG;
                } else
                {
                    testResult->coreResult[core].status = RBTPSW_TEST_STATUS_FAILED;
                }
                reportFailure = true;
            }
        }
    }
    return reportFailure;
}

/* called in x2 on the core where the 1ms task runs. */
void RBTPSW_MyTPSWCapsule_TestExecution_Proc(void)
{

    if(triggerTest == true) {
        //Only if Preempted Proc is already waiting
        if(TPSW1_ActiveWaitingPreemptedCoreAck == true)
        {
#if (RBFS_MCORE == RBFS_MCORE_ON)
            //Sync with Multicore
            while (TPSW1_ActiveWaitingMultiCoreAck == false)
            {
                //do nothing
            }
#endif
            /* In case of TPSW2_TestCaseId is zero we have possibly a fresh startup of the system.
             * In this case the TPSW BURAM data is checked whether an expected reset has occurred.
             * If an expected reset occurred, restore Test data to continue test list processing. */
            if (TPSW2_TestCaseId == 0)
            {
                RBTPSW_BURAM_tests_t budata;

                /* Check BURAM for Reset-safe data which is to be evaluated */
                RBTPSW_getTPSWtestPersistentDataFromBackupRAM(&budata);

                if ((budata.flags & RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID) != 0)
                {
                    TPSW2_TestCaseId = budata.current_test_id;
                    //Check if reset is because of an assert and don't check result again if that is the case
                    if ((budata.flags & RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_ASSERT) == 0)
                    {
                        if (RBTPSW_CheckTestResultFailed(true))
                        {
                            RBTPSW_BuramSetAssertFlag();
                            assert(false && "TPSW Testcase failed"); //This can reset the uC
                        }
                    }
                }
            }
            triggerTest = false;
            resultsFetched = false;

            // Reset expected Results
            RBTPSW_ResetExpectedResults();

            RBTPSW_CALL(TPSW2_TestWrapper());

            #if (RBFS_MCORE == RBFS_MCORE_ON)
                while(!MultiCoreFinished){}; //Wait for multicore process to finish
            #endif

            if (RBTPSW_CheckTestResultFailed(false))
            {
                RBTPSW_BuramSetAssertFlag();
                assert(false && "TPSW Testcase failed"); //This can reset the uC
            }
            resultsFetched = true;
        }
    }
}

static TaskStateType TRUSTED_GetTaskState(TaskType TaskId)
{
    TaskStateType state;
    rbtpsw_CpuContext_t prev;

    prev = RBTPSW_Switch2PrivMode();
    (void)GetTaskState(TaskId, &state);
    RBTPSW_RestoreMode(prev);

    return state;
}

/* called in x8. Also cleans up after each the test*/
void RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc(void)
{
    TaskStateType taskStateKillCore0;
    TaskStateType taskStateKillCore1;
    boolean multiCoreFinished = true;

    triggerTest = true;
    TPSW1_ActiveWaiting = true;

    RBTPSW_CALL(TPSW1_ActiveWaitingPreemptedCore());

    TPSW1_ActiveWaitingPreemptedCoreAck = false;

    do
    {
        taskStateKillCore0 = TRUSTED_GetTaskState(TaskTPSWKillCore0);
        taskStateKillCore1 = TRUSTED_GetTaskState(TaskTPSWKillCore1);
        #if (RBFS_MCORE == RBFS_MCORE_ON)
            multiCoreFinished = MultiCoreFinished;
        #endif
    } while(taskStateKillCore0 != SUSPENDED
            || taskStateKillCore1 != SUSPENDED
            || multiCoreFinished == false
           );

    while(!resultsFetched){}; //Don't reset before all results are collected

    // TPSWs are reset here. This is only done for test purpose.
    // in a real project, A TPSW APPLICATION CANNOT BE REACTIVATED WHEN IT WAS KILLED.
    MYTPSW_RESET_APP(MYTPSW1);
    MYTPSW_RESET_APP(MYTPSW2);
    MYTPSW_RESET_APP(MYTPSW3);
    MYTPSW_RESET_APP(MYTPSW4);
    MYTPSW_RESET_APP(MYTPSW5);
    MYTPSW_RESET_APP(MYTPSW6);
    MYTPSW_RESET_APP(MYTPSW7);
    MYTPSW_RESET_APP(MYTPSW8);
    MYTPSW_RESET_APP(MYTPSW9);
    MYTPSW_RESET_APP(MYTPSW10);
    // BackgroundTestApp is reset in RBTPSW_BackgroundTestApp_BgTestCases()
}

/* called in x2 on the core opposite of RBTPSW_MyTPSWCapsule_TestExecution_Proc. Only executed on multi core uCs*/
#if (RBFS_MCORE == RBFS_MCORE_ON)
void RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc(void)
{
    boolean activeWaitingPreemptedCoreAck = TPSW1_ActiveWaitingPreemptedCoreAck;
    if (triggerTest == true && activeWaitingPreemptedCoreAck == true)
    {
        MultiCoreFinished = false;

        RBTPSW_CALL(TPSW1_ActiveWaitingMultiCore());

        TPSW1_ActiveWaitingMultiCoreAck = false;
        MultiCoreFinished = true;
    }
}
#endif

void TRUSTED_1Param_V(uint32 p1) { TPSW2_1Param_V(p1); }
void TRUSTED_2Param_V(uint32 p1, uint32 p2) { TPSW2_2Param_V(p1, p2); }
void TRUSTED_3Param_V(uint32 p1, uint32 p2, uint32 p3) { TPSW2_3Param_V(p1, p2, p3); }
void TRUSTED_4Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4) { TPSW2_4Param_V(p1, p2, p3, p4); }
void TRUSTED_5Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5) { TPSW2_5Param_V(p1, p2, p3, p4, p5); }
void TRUSTED_6Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6) { TPSW2_6Param_V(p1, p2, p3, p4, p5, p6); }
void TRUSTED_7Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7) { TPSW2_7Param_V(p1, p2, p3, p4, p5, p6, p7); }
void TRUSTED_8Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8) { TPSW2_8Param_V(p1, p2, p3, p4, p5, p6, p7, p8); }
void TRUSTED_9Param_V(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8, uint32 p9) { TPSW2_9Param_V(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
void TRUSTED_9Param_U8_V(uint8 p1, uint8 p2, uint8 p3, uint8 p4, uint8 p5, uint8 p6, uint8 p7, uint8 p8, uint8 p9) { TPSW2_9Param_U8_V(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
uint32 TRUSTED_0Param_UL(void) { return TPSW2_0Param_UL(); }
uint32 TRUSTED_1Param_UL(uint32 p1) { return TPSW2_1Param_UL(p1); }
uint32 TRUSTED_2Param_UL(uint32 p1, uint32 p2) { return TPSW2_2Param_UL(p1, p2); }
uint32 TRUSTED_3Param_UL(uint32 p1, uint32 p2, uint32 p3) { return TPSW2_3Param_UL(p1, p2, p3); }
uint32 TRUSTED_4Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4) { return TPSW2_4Param_UL(p1, p2, p3, p4); }
uint32 TRUSTED_5Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5) { return TPSW2_5Param_UL(p1, p2, p3, p4, p5); }
uint32 TRUSTED_6Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6) { return TPSW2_6Param_UL(p1, p2, p3, p4, p5, p6); }
uint32 TRUSTED_7Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7) { return TPSW2_7Param_UL(p1, p2, p3, p4, p5, p6, p7); }
uint32 TRUSTED_8Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8) { return TPSW2_8Param_UL(p1, p2, p3, p4, p5, p6, p7, p8); }
uint32 TRUSTED_9Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8, uint32 p9) { return TPSW2_9Param_UL(p1, p2, p3, p4, p5, p6, p7, p8, p9); }
uint32 TRUSTED_9Param_U8(uint8 p1, uint8 p2, uint8 p3, uint8 p4, uint8 p5, uint8 p6, uint8 p7, uint8 p8, uint8 p9) { return TPSW2_9Param_U8(p1, p2, p3, p4, p5, p6, p7, p8, p9); }

uint32 TrustedData;

void TRUSTED_T_UT_CallWithLocks(void)
{
  // test for core local lock (TPSW2 will be killed)
  RBSYS_EnterCorelocalIntlock();
  RBTPSW_CALL(TPSW2_1Param_V(1));
  RBSYS_ExitCorelocalIntlock();

  // test for common lock (TPSW3 will be killed)
  RBSYS_EnterCommonLock();
  RBTPSW_CALL(TPSW3_WriteStmRegOk());
  RBSYS_ExitCommonLock();
}

uint32* TRUSTED_getStackStart(void)
{
    uint32 *val;
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        val = (uint32*)RBSYS_STSR(24, 6);
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBSYS_LDSR(16, 5, RBSYS_MPU_REGION_STACK);
        val = (uint32*)RBSYS_STSR(20, 5);
    #else
        #error "Unsupported uC family"
    #endif
    return val;
}

uint32* TRUSTED_getStackEnd(void)
{
    uint32 *val;
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        val = (uint32*)RBSYS_STSR(25, 6);
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBSYS_LDSR(16, 5, RBSYS_MPU_REGION_STACK);
        val = (uint32*)RBSYS_STSR(21, 5);
    #else
        #error "Unsupported uC family"
    #endif
    return val;
}


/*************************************************/
/************* MYTPSW1 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW1)


RBTPSW_DEFINE_MPUTABLE(MYTPSW1) = {
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW1_LCF),
    RBTPSW_MPUCONFIG_ENDMARKER
};


#if (RBFS_MCORE == RBFS_MCORE_OFF)
    RBTPSW_DEFINE_LOCKTABLE(MYTPSW1, 3) = {
        RBTPSW_LOCKCONFIG_COMMONLOCK,
        ANY_LOCK_2,  // can not be used as only common lock supported
        RBTPSW_LOCKCONFIG_ENDMARKER
    };
#else
    RBTPSW_DEFINE_LOCKTABLE(MYTPSW1, 2) = {
        RBTPSW_LOCKCONFIG_COMMONLOCK,
        RBTPSW_LOCKCONFIG_ENDMARKER
    };
#endif

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW1, 1000, 0, 5000000            , TPSW1_ActiveWaitingPreemptedCore) // 5s timing budget
#if (RBFS_MCORE == RBFS_MCORE_ON)
    RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW1, 1000 , 0, RBTPSW_NO_TIMELIMIT, TPSW1_ActiveWaitingMultiCore)
#endif

#define RBTPSW_PARAM_MANIP_PRE_TPSW1_TestExecution
#define RBTPSW_PARAM_MANIP_POST_TPSW1_TestExecution
RBTPSW_DEF_FUNC_NORET_2PARAM(MYTPSW1, TPSW1_TestExecution_STACK, 0, RBTPSW_NO_TIMELIMIT, TPSW1_TestExecution, void*, sp_before, uint32, TestId)
/*************************************************/




/*************************************************/
/************* MYTPSW2 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW2)

RBTPSW_DEFINE_MPUTABLE(MYTPSW2) = {
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW2_GLOBAL_LCF),
#if (RBFS_MCORE == RBFS_MCORE_ON)
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW2_LOCAL0_LCF),
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW2_LOCAL1_LCF),
#endif
    RBTPSW_MPUCONFIG_BYADDRESS(0xFFCDE000UL, 0xFFFBB1F0UL), // open for SINTR0 register,
                                                            // include up to TPTMPE0TPTM0UCMP13 because of test case 126
                                                            // only 4 entries per MPU table allowed

    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW2, 2) = {
    RBTPSW_LOCKCONFIG_COMMONLOCK,
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 500,   0, 1500000,                TPSW2_TestWrapper)  // time limit = 1,5s
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 0,     0, RBTPSW_NO_TIMELIMIT, TPSW2_Mytest_BadCaseUTUTwithIntLock)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 0,     0, RBTPSW_NO_TIMELIMIT, TPSW2_UTStackCheckTestAbove)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 0,     0, RBTPSW_NO_TIMELIMIT, TPSW2_UTStackCheckTestBelow)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 8,     0, RBTPSW_NO_TIMELIMIT, TPSW2_WriteAccessTpsw1)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 8,     0, RBTPSW_NO_TIMELIMIT, TPSW2_BreakSpToValidRam)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 8,     0, RBTPSW_NO_TIMELIMIT, TPSW2_BreakSpToInvalidRam)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 20000, 0, RBTPSW_NO_TIMELIMIT, TPSW2_FuncWithHugeStack)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 0,     0, RBTPSW_NO_TIMELIMIT, TPSW2_CommonLockSpBroken)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 20,    0, RBTPSW_NO_TIMELIMIT, TPSW2_EmptyFunction)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_TimingAndMpuAbort
#define RBTPSW_PARAM_MANIP_POST_TPSW2_TimingAndMpuAbort
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 300, 0, TPSW2_TIMINGANDMPUABORT_TIMELIMIT, uint32, TPSW2_TimingAndMpuAbort, uint32, x)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_MpuExc_Lock
#define RBTPSW_PARAM_MANIP_POST_TPSW2_MpuExc_Lock
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 300, 0, TPSW2_MPUEXCP_TIMELIMIT, uint32, TPSW2_MpuExc_Lock, uint32, x)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_TimingAndMpuAbort_Tp
#define RBTPSW_PARAM_MANIP_POST_TPSW2_TimingAndMpuAbort_Tp
// allow 1sec budget
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 300, 0, 1000000, uint32, TPSW2_TimingAndMpuAbort_Tp, uint32, x)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_struct_ST
#define RBTPSW_PARAM_MANIP_POST_TPSW2_struct_ST
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 8, 0, RBTPSW_NO_TIMELIMIT, mytest_t, TPSW2_struct_ST, mytest_t, structure)

/* these functions are extremely small => stack is not needed */

/* no return value, 1 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_1Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_1Param_V
RBTPSW_DEF_FUNC_NORET_1PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_1Param_V, uint32, p1)

/* no return value, 2 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_2Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_2Param_V
RBTPSW_DEF_FUNC_NORET_2PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_2Param_V, uint32, p1, uint32, p2)

/* no return value, 3 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_3Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_3Param_V
RBTPSW_DEF_FUNC_NORET_3PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_3Param_V, uint32, p1, uint32, p2, uint32, p3)

/* no return value, 4 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_4Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_4Param_V
RBTPSW_DEF_FUNC_NORET_4PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_4Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4)

/* no return value, 5 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_5Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_5Param_V
RBTPSW_DEF_FUNC_NORET_5PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_5Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)

/* no return value, 6 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_6Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_6Param_V
RBTPSW_DEF_FUNC_NORET_6PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_6Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)

/* no return value, 7 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_7Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_7Param_V
RBTPSW_DEF_FUNC_NORET_7PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_7Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)

/* no return value, 8 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_8Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_8Param_V
RBTPSW_DEF_FUNC_NORET_8PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_8Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)

/* no return value, 9 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_9Param_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_9Param_V
RBTPSW_DEF_FUNC_NORET_9PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_9Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)

/* no return value, 9 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_9Param_U8_V
#define RBTPSW_PARAM_MANIP_POST_TPSW2_9Param_U8_V
RBTPSW_DEF_FUNC_NORET_9PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW2_9Param_U8_V, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)


/* return value, 0 param */
RBTPSW_DEF_FUNC_RET_0PARAM(MYTPSW2, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_0Param_UL)

/* return value, 1 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_1Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_1Param_UL
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 8, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_1Param_UL, uint32, p1)

/* return value, 2 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_2Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_2Param_UL
RBTPSW_DEF_FUNC_RET_2PARAM(MYTPSW2, 8, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_2Param_UL, uint32, p1, uint32, p2)

/* return value, 3 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_3Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_3Param_UL
RBTPSW_DEF_FUNC_RET_3PARAM(MYTPSW2, 8, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_3Param_UL, uint32, p1, uint32, p2, uint32, p3)

/* return value, 4 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_4Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_4Param_UL
RBTPSW_DEF_FUNC_RET_4PARAM(MYTPSW2, 8, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_4Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4)

/* return value, 5 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_5Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_5Param_UL
RBTPSW_DEF_FUNC_RET_5PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_5Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)

/* return value, 6 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_6Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_6Param_UL
RBTPSW_DEF_FUNC_RET_6PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_6Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)

/* return value, 7 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_7Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_7Param_UL
RBTPSW_DEF_FUNC_RET_7PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_7Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)

/* return value, 8 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_8Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_8Param_UL
RBTPSW_DEF_FUNC_RET_8PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_8Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)

/* return value, 9 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_9Param_UL
#define RBTPSW_PARAM_MANIP_POST_TPSW2_9Param_UL
RBTPSW_DEF_FUNC_RET_9PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_9Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)

/* return value, 9 param */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_9Param_U8
#define RBTPSW_PARAM_MANIP_POST_TPSW2_9Param_U8
RBTPSW_DEF_FUNC_RET_9PARAM(MYTPSW2, 16, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_9Param_U8, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

/****** Definitions of FUNC with manipulators. *******/

/* return value, cpy array by length */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_CPYARRAY_BYLENGTH_UL  RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_PRE    (mytest_t, array_in,    50, length_in)\
                                                                RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_PRE   (mytest_t, array_out,   50, length_out)\
                                                                RBTPSW_PARAM_INOUT_CPYARRAY_BYLENGTH_PRE (mytest_t, array_inout, 50, length_inout)
#define RBTPSW_PARAM_MANIP_POST_TPSW2_CPYARRAY_BYLENGTH_UL RBTPSW_PARAM_INOUT_CPYARRAY_BYLENGTH_POST(mytest_t, array_inout, 50, length_inout)\
                                                                RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST  (mytest_t, array_out,   50, length_out)\
                                                                RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_POST   (mytest_t, array_in,    50, length_in)
#define TPSW_STACKADDER_TPSW2_CPYARRAY_BYLENGTH_UL (3*RBTPSW_PARAM_CPYARRAY_BYLENGTH_STACKADDER    (mytest_t, 50))
RBTPSW_DEF_FUNC_RET_6PARAM(MYTPSW2, 24, TPSW_STACKADDER_TPSW2_CPYARRAY_BYLENGTH_UL, RBTPSW_NO_TIMELIMIT, int32_t, TPSW2_CPYARRAY_BYLENGTH_UL, uint32, length_in, mytest_t *, array_in, uint32, length_out, mytest_t *, array_out, uint32, length_inout, mytest_t *, array_inout)

/* return value, cpy array (length in first elem) */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_CPYARRAY_FIRSTELEM_UL  RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_PRE    (uint32, array_in,    50)\
                                                                 RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_PRE   (uint32, array_out,   50)\
                                                                 RBTPSW_PARAM_INOUT_CPYARRAY_FIRSTELEM_PRE (uint32, array_inout, 50)
#define RBTPSW_PARAM_MANIP_POST_TPSW2_CPYARRAY_FIRSTELEM_UL RBTPSW_PARAM_INOUT_CPYARRAY_FIRSTELEM_POST(uint32, array_inout, 50)\
                                                                 RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_POST  (uint32, array_out,   50)\
                                                                 RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_POST   (uint32, array_in,    50)
#define TPSW_STACKADDER_TPSW2_CPYARRAY_FIRSTELEM_UL (3*RBTPSW_PARAM_CPYARRAY_FIRSTELEM_STACKADDER    (uint32, 50))
RBTPSW_DEF_FUNC_RET_3PARAM(MYTPSW2, 16, TPSW_STACKADDER_TPSW2_CPYARRAY_FIRSTELEM_UL, RBTPSW_NO_TIMELIMIT, int32_t, TPSW2_CPYARRAY_FIRSTELEM_UL, uint32 *, array_in, uint32 *, array_out, uint32 *, array_inout)

/* return value, cpy 0 term array */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_CPYARRAY_0TERM_UL  RBTPSW_PARAM_IN_CPYARRAY_0TERM_PRE    (uint8_t, array_in,    50)\
                                                             RBTPSW_PARAM_OUT_CPYARRAY_0TERM_PRE   (uint8_t, array_out,   50)\
                                                             RBTPSW_PARAM_INOUT_CPYARRAY_0TERM_PRE (uint8_t, array_inout, 50)
#define RBTPSW_PARAM_MANIP_POST_TPSW2_CPYARRAY_0TERM_UL RBTPSW_PARAM_INOUT_CPYARRAY_0TERM_POST(uint8_t, array_inout, 50)\
                                                             RBTPSW_PARAM_OUT_CPYARRAY_0TERM_POST  (uint8_t, array_out,   50)\
                                                             RBTPSW_PARAM_IN_CPYARRAY_0TERM_POST   (uint8_t, array_in,    50)
#define TPSW_STACKADDER_TPSW2_CPYARRAY_0TERM_UL (3*RBTPSW_PARAM_CPYARRAY_0TERM_STACKADDER (uint8_t, 50))
RBTPSW_DEF_FUNC_RET_3PARAM(MYTPSW2, 16, TPSW_STACKADDER_TPSW2_CPYARRAY_0TERM_UL, RBTPSW_NO_TIMELIMIT, int32_t, TPSW2_CPYARRAY_0TERM_UL, uint8_t *, array_in, uint8_t *, array_out, uint8_t *, array_inout)

/* return value, cpy ptr */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_CPYPTR_UL  RBTPSW_PARAM_IN_CPYPTR_PRE    (uint8_t, p_in)\
                                                     RBTPSW_PARAM_OUT_CPYPTR_PRE   (uint8_t, p_out)\
                                                     RBTPSW_PARAM_INOUT_CPYPTR_PRE (uint8_t, p_inout)
#define RBTPSW_PARAM_MANIP_POST_TPSW2_CPYPTR_UL RBTPSW_PARAM_INOUT_CPYPTR_POST(uint8_t, p_inout)\
                                                     RBTPSW_PARAM_OUT_CPYPTR_POST  (uint8_t, p_out)\
                                                     RBTPSW_PARAM_IN_CPYPTR_POST   (uint8_t, p_in)
#define TPSW_STACKADDER_TPSW2_CPYPTR_UL (3*RBTPSW_PARAM_CPYPTR_STACKADDER (uint8_t))
RBTPSW_DEF_FUNC_RET_3PARAM(MYTPSW2, 0, TPSW_STACKADDER_TPSW2_CPYPTR_UL, RBTPSW_NO_TIMELIMIT, int32_t, TPSW2_CPYPTR_UL, uint8_t *, p_in, uint8_t *, p_out, uint8_t *, p_inout)

/* no return value, cpy ptr, cpy array by length */
#define RBTPSW_PARAM_MANIP_PRE_TPSW2_GetPower2   RBTPSW_PARAM_OUT_CPYPTR_PRE(uint32, length_ptr)\
                                                      RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_PRE(uint32, array, 10, (*length_ptr))
#define RBTPSW_PARAM_MANIP_POST_TPSW2_GetPower2  RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST(uint32, array, 10, (*length_ptr))\
                                                      RBTPSW_PARAM_OUT_CPYPTR_POST(uint32, length_ptr)
#define TPSW_STACKADDER_TPSW2_GetPower2          (RBTPSW_PARAM_CPYPTR_STACKADDER(uint32) + RBTPSW_PARAM_CPYARRAY_BYLENGTH_STACKADDER(uint32, 10))
RBTPSW_DEF_FUNC_NORET_2PARAM(MYTPSW2, 50, TPSW_STACKADDER_TPSW2_GetPower2, RBTPSW_NO_TIMELIMIT, TPSW2_GetPower2, uint32*, length_ptr, uint32*, array)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_WaitingFunction_TP
#define RBTPSW_PARAM_MANIP_POST_TPSW2_WaitingFunction_TP
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 120, 0, TPSW2_WaitingFunction_TP_TimeLimit, uint32, TPSW2_WaitingFunction_TP, uint32, time_val)

#define RBTPSW_PARAM_MANIP_PRE_TPSW2_WaitingFunction_NoTP
#define RBTPSW_PARAM_MANIP_POST_TPSW2_WaitingFunction_NoTP
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 100, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW2_WaitingFunction_NoTP, uint32 , time_val)

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
  #define RBTPSW_PARAM_MANIP_PRE_TPSW1_TPSW2_Before_Timing_Exc
  #define RBTPSW_PARAM_MANIP_POST_TPSW1_TPSW2_Before_Timing_Exc
  RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW2, 100, 0, TPSW2_WaitingFunction_TP_TimeLimit, uint32, TPSW1_TPSW2_Before_Timing_Exc, uint32 , y)

  RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 100, 0, 100, TPSW2_TPNoTP_LockTest)

  RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 100, 0, RBTPSW_NO_TIMELIMIT, TPSW2_NoTP_LockTest)

  RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW2, 100, 0, 100, TPSW2_TP_LockTest)
#endif
/*************************************************/




/*************************************************/
/************* MYTPSW3 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW3)


RBTPSW_DEFINE_MPUTABLE(MYTPSW3) = {
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW3_GLOBAL_LCF),
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        RBTPSW_MPUCONFIG_BYADDRESS(0xFFDD8000UL, 0xFFDD80C8UL), // open for STM0, until STM0CMP3C, STM0CMP3D not more allowed
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBTPSW_MPUCONFIG_BYADDRESS(0xFFFBB000UL, 0xFFFBB1CCUL), // open for TPTMPE0TOTM0, up to TPTMPE0TPTM0UCMP02, TPTM0UCMP02 included
    #endif
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW3, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteReg)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteRegAndSpGpTp)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_WriteStmRegOk)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_WriteStmRegNotOk)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 20,  0, RBTPSW_NO_TIMELIMIT, TPSW3_InterruptLockSpBroken)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 100, 0, RBTPSW_NO_TIMELIMIT, TPSW3_BreakStack)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteGp)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteTp)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteEp)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, 0,   0, RBTPSW_NO_TIMELIMIT, TPSW3_OverwriteLp)
RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW3, TPSW3_LOCAL_ARRAY, 0, RBTPSW_NO_TIMELIMIT, TPSW3_StackSizeCheck)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_TPSW3_WaitingFunction
RBTPSW_DEF_FUNC_NORET_1PARAM(MYTPSW3, 100, 0, TPSW3_WAITINGFUNCTION_TIMELIMIT, TPSW3_WaitingFunction, Os_StopwatchTickType, duration)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_WaitingFunction_Switch2Trust
#define RBTPSW_PARAM_MANIP_POST_TPSW3_WaitingFunction_Switch2Trust
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 120, 0, TPSW3_WaitingFunction_Switch2Trust_TimeLimit, uint32, TPSW3_WaitingFunction_Switch2Trust, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_WaitingFunction_UTnoTP
#define RBTPSW_PARAM_MANIP_POST_TPSW3_WaitingFunction_UTnoTP
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 300, 0, TPSW3_WaitingFunction_UTnoTP_TimeLimit, uint32, TPSW3_WaitingFunction_UTnoTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_TimingAndMpuAbort
#define RBTPSW_PARAM_MANIP_POST_TPSW3_TimingAndMpuAbort
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 100, 0, RBTPSW_NO_TIMELIMIT, uint32, TPSW3_TimingAndMpuAbort, uint32, x)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_TimingAndMpuAbort_Tp
#define RBTPSW_PARAM_MANIP_POST_TPSW3_TimingAndMpuAbort_Tp
// allow 1sec budget
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 100, 0, 1000000, uint32, TPSW3_TimingAndMpuAbort_Tp, uint32, x)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_TPSW2_WaitingFunction_UTTP
#define RBTPSW_PARAM_MANIP_POST_TPSW3_TPSW2_WaitingFunction_UTTP
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 300, 0, TPSW3_WaitingFunction_UTTP_TimeLimit, uint32, TPSW3_TPSW2_WaitingFunction_UTTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_WaitingFunction_UTTP
#define RBTPSW_PARAM_MANIP_POST_TPSW3_WaitingFunction_UTTP
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 300, 0, TPSW3_WaitingFunction_UTTP_TimeLimit, uint32, TPSW3_WaitingFunction_UTTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

#define RBTPSW_PARAM_MANIP_PRE_TPSW3_TPSW2_WaitingFunction_UTTP_NoTp
#define RBTPSW_PARAM_MANIP_POST_TPSW3_TPSW2_WaitingFunction_UTTP_NoTp
RBTPSW_DEF_FUNC_RET_1PARAM(MYTPSW3, 300, 0, TPSW3_WaitingFunction_UTTP_NoTp_TimeLimit, uint32, TPSW3_TPSW2_WaitingFunction_UTTP_NoTp, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

/*************************************************/




/*************************************************/
/************* MYTPSW4 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW4)

RBTPSW_DEFINE_MPUTABLE(MYTPSW4) = {
    RBTPSW_MPUCONFIG_BYADDRESS(&TPSW4_data[0], &TPSW4_data[TPSW4_DATASIZE-1]),
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW4, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW4, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW4_OutOfRange)
RBTPSW_DEF_FUNC_NORET_1PARAM(MYTPSW4, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW4_P2CONST_Param     , P2CONST(uint32, , )     , param)
RBTPSW_DEF_FUNC_NORET_1PARAM(MYTPSW4, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW4_CONSTP2VAR_Param  , CONSTP2VAR(uint32, , )  , param)
RBTPSW_DEF_FUNC_NORET_1PARAM(MYTPSW4, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW4_CONSTP2CONST_Param, CONSTP2CONST(uint32, , ), param)
/*************************************************/




/*************************************************/
/************* MYTPSW5 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW5)

RBTPSW_DEFINE_MPUTABLE(MYTPSW5) = {
    RBTPSW_MPUCONFIG_BYADDRESS(0x2000, 0x1000),   // bad case: start is greater than end address
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW5, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW5, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW5_DummyFunc)
/*************************************************/




/*************************************************/
/************* MYTPSW6 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW6)

RBTPSW_DEFINE_MPUTABLE(MYTPSW6) = {
    RBTPSW_MPUCONFIG_BYADDRESS(0x1001, 0x2000),   // bad case: unaligned start address
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW6, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW6, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW6_DummyFunc)
/*************************************************/




/*************************************************/
/************* MYTPSW7 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW7)

RBTPSW_DEFINE_MPUTABLE(MYTPSW7) = {
    RBTPSW_MPUCONFIG_BYADDRESS(0x1000, 0x2001),   // bad case: unaligned end address
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW7, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW7, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW7_DummyFunc)
/*************************************************/




/*************************************************/
/************* MYTPSW8 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW8)

RBTPSW_DEFINE_MPUTABLE(MYTPSW8) = {
    RBTPSW_MPUCONFIG_BYADDRESS(0x1000, 0x2000),
    RBTPSW_MPUCONFIG_BYADDRESS(0x3000, 0x4000),
    RBTPSW_MPUCONFIG_BYADDRESS(0x5000, 0x6000),
    RBTPSW_MPUCONFIG_BYADDRESS(0x7000, 0x8000),
    RBTPSW_MPUCONFIG_BYADDRESS(0x9000, 0xA000),  // bad case: more than 4 entries
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW8, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW8, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW8_DummyFunc)
/*************************************************/




/*************************************************/
/************* MYTPSW9 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW9)

RBTPSW_DEFINE_MPUTABLE(MYTPSW9) = {
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW9, 1) = {
    RBTPSW_LOCKCONFIG_COMMONLOCK
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW9, 0, 0, RBTPSW_NO_TIMELIMIT, TPSW9_DummyFunc)
/*************************************************/




/**************************************************/
/************* MYTPSW10 ***************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW10)

RBTPSW_DEFINE_MPUTABLE(MYTPSW10) = {
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(MYTPSW10, 2) = {
    RBTPSW_LOCKCONFIG_ENDMARKER,
    RBTPSW_LOCKCONFIG_COMMONLOCK
};

RBTPSW_DEF_FUNC_NORET_0PARAM(MYTPSW10, 0, 0, RBTPSW_NO_TIMELIMIT,  TPSW10_DummyFunc)
/*************************************************/




/**********************************************************
 ************* BackgroundTestApp **************************
 ** This application must be never killed, for good
 ** cases only!
 **********************************************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(BackgroundTestApp)

RBTPSW_DEFINE_MPUTABLE(BackgroundTestApp) = {
    RBTPSW_MPUCONFIG_ENDMARKER
};

RBTPSW_DEFINE_LOCKTABLE(BackgroundTestApp, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER
};

/* Good Case - With Return */

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_1_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_1_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_1PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_1_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_1_GoodCase_WaitingFunction, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_2_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_2_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_2PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_2_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_2_GoodCase_WaitingFunction, uint32, param1, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_3_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_3_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_3PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_3_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_3_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_4_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_4_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_4PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_4_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_4_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_5_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_5_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_5PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_5_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_5_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_6_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_6_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_6PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_6_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_6_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_7_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_7_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_7PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_7_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_7_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_8_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_8_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_8PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_8_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_8_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_9_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_9_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_9PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_9_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_9_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_0_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_0_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_0PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_0_GOODCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_0_GoodCase_WaitingFunction)

/* Good Case - No Return */

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_1PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_1_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_2PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_2_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction, uint32, param1, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_3PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_3_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_4PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_4_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_5PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_5_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_6PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_6_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_7PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_7_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_8PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_8_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_9PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_9_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_0PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_0_GOODCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_WaitingFunction
RBTPSW_DEF_FUNC_RET_1PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_WaitingFunction, Os_StopwatchTickType, duration)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_WaitingFunction_DynLimit
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_WaitingFunction_DynLimit
RBTPSW_DEF_FUNC_RET_1PARAM(BackgroundTestApp, 120, 0, RBTPSW_BackgroundTestApp_WaitingFunction_DynLimit_TimeLimit, uint32, BackgroundTestApp_WaitingFunction_DynLimit, Os_StopwatchTickType, duration)

/* Bad Case - With Return */

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_1_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_1_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_1PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_1_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_1_BadCase_WaitingFunction, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_2_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_2_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_2PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_2_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_2_BadCase_WaitingFunction, uint32, param1, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_3_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_3_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_3PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_3_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_3_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_4_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_4_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_4PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_4_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_4_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_5_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_5_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_5PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_5_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_5_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_6_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_6_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_6PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_6_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_6_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_7_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_7_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_7PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_7_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_7_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_8_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_8_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_8PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_8_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_8_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_9_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_9_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_9PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_9_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_9_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_Ret_0_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_Ret_0_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_RET_0PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_Ret_0_BADCASE_WAITINGFUNCTION_TIMELIMIT, uint32, BackgroundTestApp_Ret_0_BadCase_WaitingFunction)

/* Bad Case - No Return */

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_1_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_1_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_1PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_1_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_1_BadCase_WaitingFunction, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_2_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_2_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_2PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_2_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_2_BadCase_WaitingFunction, uint32, param1, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_3_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_3_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_3PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_3_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_3_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_4_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_4_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_4PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_4_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_4_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_5_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_5_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_5PARAM(BackgroundTestApp, 120, 0, 5, BackgroundTestApp_NoRet_5_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_6_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_6_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_6PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_6_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_6_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_7_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_7_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_7PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_7_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_7_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_8_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_8_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_8PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_8_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_8_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_9_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_9_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_9PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_9_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_9_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit)

#define RBTPSW_PARAM_MANIP_PRE_BackgroundTestApp_NoRet_0_BadCase_WaitingFunction
#define RBTPSW_PARAM_MANIP_POST_BackgroundTestApp_NoRet_0_BadCase_WaitingFunction
RBTPSW_DEF_FUNC_NORET_0PARAM(BackgroundTestApp, 120, 0, BackgroundTestApp_NoRet_0_BADCASE_WAITINGFUNCTION_TIMELIMIT, BackgroundTestApp_NoRet_0_BadCase_WaitingFunction)

/**********************************************************/




/**********************************************************/
/************* RBTPSW_STD_TRUSTED_APP *********************/
RBTPSW_DEF_FUNC_NORET_1PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_1Param_V, uint32, p1)
RBTPSW_DEF_FUNC_NORET_2PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_2Param_V, uint32, p1, uint32, p2)
RBTPSW_DEF_FUNC_NORET_3PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_3Param_V, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DEF_FUNC_NORET_4PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_4Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DEF_FUNC_NORET_5PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_5Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DEF_FUNC_NORET_6PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_6Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DEF_FUNC_NORET_7PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_7Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DEF_FUNC_NORET_8PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_8Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DEF_FUNC_NORET_9PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_9Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DEF_FUNC_NORET_9PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0,  RBTPSW_NO_TIMELIMIT, TRUSTED_9Param_U8_V, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DEF_FUNC_RET_0PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_0Param_UL)
RBTPSW_DEF_FUNC_RET_1PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_1Param_UL, uint32, p1)
RBTPSW_DEF_FUNC_RET_2PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_2Param_UL, uint32, p1, uint32, p2)
RBTPSW_DEF_FUNC_RET_3PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_3Param_UL, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DEF_FUNC_RET_4PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_4Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DEF_FUNC_RET_5PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_5Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DEF_FUNC_RET_6PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_6Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DEF_FUNC_RET_7PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_7Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DEF_FUNC_RET_8PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_8Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DEF_FUNC_RET_9PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_9Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DEF_FUNC_RET_9PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32, TRUSTED_9Param_U8, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DEF_FUNC_NORET_0PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, TRUSTED_T_UT_CallWithLocks)

RBTPSW_DEF_FUNC_RET_0PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32*, TRUSTED_getStackStart)
RBTPSW_DEF_FUNC_RET_0PARAM(RBTPSW_STD_TRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, uint32*, TRUSTED_getStackEnd)
/**********************************************************/







/*[[MEASUREMENT*/
/*NAME=TPSW2_TestCaseId*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*********************************************************************************/
/**************************** MYTPSW1        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif







/*********************************************************************************/
/**************************** MYTPSW2        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif








/*********************************************************************************/
/**************************** MYTPSW3        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif









/*********************************************************************************/
/**************************** MYTPSW4        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW4.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif











/*********************************************************************************/
/**************************** MYTPSW5        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW5.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif










/*********************************************************************************/
/**************************** MYTPSW6        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW6.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif









/*********************************************************************************/
/**************************** MYTPSW7        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW7.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif








/*********************************************************************************/
/**************************** MYTPSW8        *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.mpu_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.lock_conf*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.PlausiCheckDone*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[0].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_MCORE == RBFS_MCORE_ON)
/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].userinfo*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].FaultAdr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].CallCoreFnPtr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].rh850_mei*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].rh850_mea*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].rh850_feic*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].rh850_fepsw*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].os_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW8.debuginfo[1].debug_status*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif





/*********************************************************************************/
/**************************** FPP registers  *************************************/
/*********************************************************************************/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[0].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW1.debuginfo[1].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/




/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[0].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW2.debuginfo[1].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/




/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[0].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_fpsr*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBTPSWAppCfg_MYTPSW3.debuginfo[1].rh850_fpepc*/
/*COMMENT=1ms task*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


#endif

/** @} */
/* End ingroup 'SW-group' */
