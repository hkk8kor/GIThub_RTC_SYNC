#ifndef RBTPSW_MYTPSWCAPSULE_H__
#define RBTPSW_MYTPSWCAPSULE_H__

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
#include "RBTPSW_TPSWCapsule.h"
#include "RBTPSW_MyTPSW1.h"
#include "RBTPSW_MyTPSW2.h"
#include "RBTPSW_MyTPSW3.h"
#include "RBTPSW_MyTPSW4.h"
#include "RBTPSW_MyTPSWx.h"
#include "Os.h"


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


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)


#define ANY_LOCK      ((lockstr_t*)0x12345678)
#define ANY_LOCK_2    ((lockstr_t*)0x87654320)



extern uint32 TrustedData;

void TRUSTED_MoveSP(const void* stackP);
void* TRUSTED_GetSP(void);

CoreIdType TRUSTED_GetCoreId(void);
void RBTPSW_BackgroundTestApp_BgTestCases(void);

extern uint32 RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter;

/* RBTPSW_BURAM_tests_t::flags values */
/* Indicates that content of TPSW BURAM is valid */
#define RBTPSW_BURAM_FLAGS_TESTSTATE_DATA_VALID             (1u << 0)
/* Indicates that current testcase expects a board reset */
#define RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_EXPECTED         (1u << 1)
/* Indicate that the last reset was because of an assert */
#define RBTPSW_BURAM_FLAGS_TESTSTATE_RESET_ASSERT           (1u << 2)

static inline void WaitingFunction(Os_StopwatchTickType duration)
{
    Os_StopwatchTickType diff;
    Os_StopwatchTickType start = GetExecutionTime();

    do
    {
        diff = GetExecutionTime() - start;
    } while(diff < duration);
}

typedef void (*func_p)(void);

#define RBTPSW_EXPECTEDRESULT_DONTCARE ((uint32)0xFFFFFFFF)
extern void RBTPSW_SetExpectedResult(uint32 tpswNum, rbtpsw_appstatus_t appStatus, uint32 feic, uint32 userInfo, uint32 osStatus, rbtpsw_debugappstatus_t debugStatus, uint32 core);
extern void RBTPSW_SetExpectedResultToNoReaction(void);
extern void RBTPSW_SetExpectedResultToReset(void);

extern uint8 RBTPSW_TestExecutionProcCore;
#if (RBFS_MCORE == RBFS_MCORE_ON)
extern uint8 RBTPSW_MultiProcCore;
#endif

//Called to schedule RBTPSW_MyTPSWCapsule_TestExecution_Proc and RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc on correct cores in x2 and x2p tasks
void RBTPSW_MyTPSWCapsule_CoreScheduler_Proc(void);
// called in x2 on the core where the 1ms task runs.
void RBTPSW_MyTPSWCapsule_TestExecution_Proc(void);
// called in x8. Also cleans up after each the test
void RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
// called in x2 on the core opposite of RBTPSW_MyTPSWCapsule_TestExecution_Proc. Only executed on multi core uCs
void RBTPSW_MyTPSWCapsule_MultiCoreWaiting_Proc(void);
#endif


// This macro resets a TPSW. This is only done for testing purpose.
// In a real project, A TPSW APPLICATION CANNOT BE REACTIVATED WHEN IT WAS KILLED.
#define MYTPSW_RESET_APP_DEBUG(app, core)\
    { \
    /* "volatile" because of compiler/cchecker complains about setting variable multiple times */ \
    volatile rbtpsw_debuginfo_t * debuginfo_p = (volatile rbtpsw_debuginfo_t *)&RBTPSWAppCfg_##app.debuginfo[core]; \
    debuginfo_p->userinfo = 0;\
    debuginfo_p->FaultAdr = 0;\
    debuginfo_p->CallCoreFnPtr = (rbtpsw_corefnptr_t)NULL;\
    debuginfo_p->rh850_mei = 0;\
    debuginfo_p->rh850_mea = 0;\
    debuginfo_p->rh850_feic = 0;\
    debuginfo_p->rh850_fepsw = 0;\
    debuginfo_p->debug_status = DEBUG_ACTIVE;\
    debuginfo_p->os_status = 0; \
    }

#if (RBFS_MCORE == RBFS_MCORE_ON)
    #define MYTPSW_RESET_APP(app)\
        RBTPSWAppCfg_##app.status = ACTIVE;\
        RBTPSWAppCfg_##app.PlausiCheckDone = 0;\
        RBTPSWAppCfg_##app.ei_fault = 0;\
        MYTPSW_RESET_APP_DEBUG(app, 0);\
        MYTPSW_RESET_APP_DEBUG(app, 1)
#else
    #define MYTPSW_RESET_APP(app)\
        RBTPSWAppCfg_##app.status = ACTIVE;\
        RBTPSWAppCfg_##app.PlausiCheckDone = 0;\
        RBTPSWAppCfg_##app.ei_fault = 0;\
        MYTPSW_RESET_APP_DEBUG(app, 0)
#endif

extern uint32 MYTPSW_SupprFlagErrorCounter;
#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    extern void MYTPSW_CHECK_SF(boolean x);
#else
    #define MYTPSW_CHECK_SF(x)
#endif

/************* MYTPSW1 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW1)

RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW1_ActiveWaitingPreemptedCore)
#if (RBFS_MCORE == RBFS_MCORE_ON)
    RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW1_ActiveWaitingMultiCore)
#endif

#define TPSW1_TestExecution_STACK 1200
RBTPSW_DECL_FUNC_NORET_2PARAM(TPSW1_TestExecution, void*, sp_before, uint32, TestId)
/*************************************************/




/************* MYTPSW2 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW2)

RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_TestWrapper)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_Mytest_BadCaseUTUTwithIntLock)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_UTStackCheckTestAbove)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_UTStackCheckTestBelow)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_WriteAccessTpsw1)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_BreakSpToValidRam)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_FuncWithHugeStack)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_BreakSpToInvalidRam)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_CommonLockSpBroken)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_EmptyFunction)

RBTPSW_DECL_FUNC_RET_1PARAM(mytest_t, TPSW2_struct_ST, mytest_t, structure)

RBTPSW_DECL_FUNC_NORET_1PARAM(TPSW2_1Param_V, uint32, p1)
RBTPSW_DECL_FUNC_NORET_2PARAM(TPSW2_2Param_V, uint32, p1, uint32, p2)
RBTPSW_DECL_FUNC_NORET_3PARAM(TPSW2_3Param_V, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DECL_FUNC_NORET_4PARAM(TPSW2_4Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DECL_FUNC_NORET_5PARAM(TPSW2_5Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DECL_FUNC_NORET_6PARAM(TPSW2_6Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DECL_FUNC_NORET_7PARAM(TPSW2_7Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DECL_FUNC_NORET_8PARAM(TPSW2_8Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DECL_FUNC_NORET_9PARAM(TPSW2_9Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DECL_FUNC_NORET_9PARAM(TPSW2_9Param_U8_V, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DECL_FUNC_RET_0PARAM(uint32, TPSW2_0Param_UL)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_1Param_UL, uint32, p1)
RBTPSW_DECL_FUNC_RET_2PARAM(uint32, TPSW2_2Param_UL, uint32, p1, uint32, p2)
RBTPSW_DECL_FUNC_RET_3PARAM(uint32, TPSW2_3Param_UL, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DECL_FUNC_RET_4PARAM(uint32, TPSW2_4Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DECL_FUNC_RET_5PARAM(uint32, TPSW2_5Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DECL_FUNC_RET_6PARAM(uint32, TPSW2_6Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DECL_FUNC_RET_7PARAM(uint32, TPSW2_7Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DECL_FUNC_RET_8PARAM(uint32, TPSW2_8Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, TPSW2_9Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, TPSW2_9Param_U8, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DECL_FUNC_RET_3PARAM(int32_t, TPSW2_CPYPTR_UL, uint8_t *, p_in, uint8_t *, p_out, uint8_t *, p_inout)
RBTPSW_DECL_FUNC_RET_6PARAM(int32_t, TPSW2_CPYARRAY_BYLENGTH_UL, uint32, length_in, mytest_t *, array_in, uint32, length_out, mytest_t *, array_out, uint32, length_inout, mytest_t *, array_inout)
RBTPSW_DECL_FUNC_RET_3PARAM(int32_t, TPSW2_CPYARRAY_FIRSTELEM_UL, uint32 *, array_in, uint32 *, array_out, uint32 *, array_inout)
RBTPSW_DECL_FUNC_RET_3PARAM(int32_t, TPSW2_CPYARRAY_0TERM_UL, uint8_t *, array_in, uint8_t *, array_out, uint8_t *, array_inout)
RBTPSW_DECL_FUNC_NORET_2PARAM(TPSW2_GetPower2, uint32*, length_ptr, uint32*, array)

RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_TimingAndMpuAbort, uint32, x)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_MpuExc_Lock, uint32, x)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_TimingAndMpuAbort_Tp, uint32, x)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_WaitingFunction_TP, uint32 , time_val)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW2_WaitingFunction_NoTP, uint32 , time_val)
#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
  RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW1_TPSW2_Before_Timing_Exc, uint32 , y)
  RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_TPNoTP_LockTest)
  RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_NoTP_LockTest)
  RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW2_TP_LockTest)
#endif
/*************************************************/




/************* MYTPSW3 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW3)

RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteReg)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteRegAndSpGpTp)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_WriteStmRegOk)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_WriteStmRegNotOk)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_InterruptLockSpBroken)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_BreakStack)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteGp)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteTp)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteEp)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_OverwriteLp)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW3_StackSizeCheck)

RBTPSW_DECL_FUNC_NORET_1PARAM(TPSW3_WaitingFunction, Os_StopwatchTickType, duration)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_WaitingFunction_Switch2Trust, const TPSW3_WaitingFunction_Switch2Trust_t*, p)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_WaitingFunction_UTnoTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_TimingAndMpuAbort, uint32, x)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_TimingAndMpuAbort_Tp, uint32, x)

RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_TPSW2_WaitingFunction_UTTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_TPSW2_WaitingFunction_UTTP_NoTp, const TPSW3_WaitingFunction_Switch2Trust_t*, p)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TPSW3_WaitingFunction_UTTP, const TPSW3_WaitingFunction_Switch2Trust_t*, p)

/*************************************************/




/************* MYTPSW4 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW4)

RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW4_OutOfRange)

#define RBTPSW_PARAM_MANIP_PRE_TPSW4_P2CONST_Param
#define RBTPSW_PARAM_MANIP_POST_TPSW4_P2CONST_Param
#define RBTPSW_PARAM_MANIP_PRE_TPSW4_CONSTP2VAR_Param
#define RBTPSW_PARAM_MANIP_POST_TPSW4_CONSTP2VAR_Param
#define RBTPSW_PARAM_MANIP_PRE_TPSW4_CONSTP2CONST_Param
#define RBTPSW_PARAM_MANIP_POST_TPSW4_CONSTP2CONST_Param
RBTPSW_DECL_FUNC_NORET_1PARAM(TPSW4_P2CONST_Param     , P2CONST(uint32, , )     , param)
RBTPSW_DECL_FUNC_NORET_1PARAM(TPSW4_CONSTP2VAR_Param  , CONSTP2VAR(uint32, , )  , param)
RBTPSW_DECL_FUNC_NORET_1PARAM(TPSW4_CONSTP2CONST_Param, CONSTP2CONST(uint32, , ), param)
/*************************************************/




/************* MYTPSW5 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW5)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW5_DummyFunc)
/*************************************************/




/************* MYTPSW6 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW6)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW6_DummyFunc)
/*************************************************/




/************* MYTPSW7 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW7)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW7_DummyFunc)
/*************************************************/




/************* MYTPSW8 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW8)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW8_DummyFunc)
/*************************************************/




/************* MYTPSW9 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW9)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW9_DummyFunc)
/*************************************************/




/************* MYTPSW10 ***************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW10)
RBTPSW_DECL_FUNC_NORET_0PARAM(TPSW10_DummyFunc)
/*************************************************/




/************* BackgroundTestApp ***********************************/
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(BackgroundTestApp)

/* Good Case - With Return */
RBTPSW_DECL_FUNC_RET_0PARAM(uint32, BackgroundTestApp_Ret_0_GoodCase_WaitingFunction)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, BackgroundTestApp_Ret_1_GoodCase_WaitingFunction, uint32, limit)
RBTPSW_DECL_FUNC_RET_2PARAM(uint32, BackgroundTestApp_Ret_2_GoodCase_WaitingFunction, uint32, param1, uint32, limit)
RBTPSW_DECL_FUNC_RET_3PARAM(uint32, BackgroundTestApp_Ret_3_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit )
RBTPSW_DECL_FUNC_RET_4PARAM(uint32, BackgroundTestApp_Ret_4_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit )
RBTPSW_DECL_FUNC_RET_5PARAM(uint32, BackgroundTestApp_Ret_5_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit )
RBTPSW_DECL_FUNC_RET_6PARAM(uint32, BackgroundTestApp_Ret_6_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit )
RBTPSW_DECL_FUNC_RET_7PARAM(uint32, BackgroundTestApp_Ret_7_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit )
RBTPSW_DECL_FUNC_RET_8PARAM(uint32, BackgroundTestApp_Ret_8_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit )
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, BackgroundTestApp_Ret_9_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit )

/* Good Case - No Return */
RBTPSW_DECL_FUNC_NORET_0PARAM(BackgroundTestApp_NoRet_0_GoodCase_WaitingFunction)
RBTPSW_DECL_FUNC_NORET_1PARAM(BackgroundTestApp_NoRet_1_GoodCase_WaitingFunction, uint32, limit)
RBTPSW_DECL_FUNC_NORET_2PARAM(BackgroundTestApp_NoRet_2_GoodCase_WaitingFunction, uint32, param1, uint32, limit)
RBTPSW_DECL_FUNC_NORET_3PARAM(BackgroundTestApp_NoRet_3_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit )
RBTPSW_DECL_FUNC_NORET_4PARAM(BackgroundTestApp_NoRet_4_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit )
RBTPSW_DECL_FUNC_NORET_5PARAM(BackgroundTestApp_NoRet_5_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit )
RBTPSW_DECL_FUNC_NORET_6PARAM(BackgroundTestApp_NoRet_6_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit )
RBTPSW_DECL_FUNC_NORET_7PARAM(BackgroundTestApp_NoRet_7_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit )
RBTPSW_DECL_FUNC_NORET_8PARAM(BackgroundTestApp_NoRet_8_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit )
RBTPSW_DECL_FUNC_NORET_9PARAM(BackgroundTestApp_NoRet_9_GoodCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit )

RBTPSW_DECL_FUNC_RET_1PARAM(uint32, BackgroundTestApp_WaitingFunction, Os_StopwatchTickType, duration)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, BackgroundTestApp_WaitingFunction_DynLimit, Os_StopwatchTickType, duration)


/*Bad Case - with Return*/
RBTPSW_DECL_FUNC_RET_0PARAM(uint32, BackgroundTestApp_Ret_0_BadCase_WaitingFunction)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, BackgroundTestApp_Ret_1_BadCase_WaitingFunction, uint32, limit)
RBTPSW_DECL_FUNC_RET_2PARAM(uint32, BackgroundTestApp_Ret_2_BadCase_WaitingFunction, uint32, param1, uint32, limit)
RBTPSW_DECL_FUNC_RET_3PARAM(uint32, BackgroundTestApp_Ret_3_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit )
RBTPSW_DECL_FUNC_RET_4PARAM(uint32, BackgroundTestApp_Ret_4_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit )
RBTPSW_DECL_FUNC_RET_5PARAM(uint32, BackgroundTestApp_Ret_5_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit )
RBTPSW_DECL_FUNC_RET_6PARAM(uint32, BackgroundTestApp_Ret_6_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit )
RBTPSW_DECL_FUNC_RET_7PARAM(uint32, BackgroundTestApp_Ret_7_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit )
RBTPSW_DECL_FUNC_RET_8PARAM(uint32, BackgroundTestApp_Ret_8_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit )
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, BackgroundTestApp_Ret_9_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit )

/* Bad Case - No Return */
RBTPSW_DECL_FUNC_NORET_0PARAM(BackgroundTestApp_NoRet_0_BadCase_WaitingFunction)
RBTPSW_DECL_FUNC_NORET_1PARAM(BackgroundTestApp_NoRet_1_BadCase_WaitingFunction, uint32, limit)
RBTPSW_DECL_FUNC_NORET_2PARAM(BackgroundTestApp_NoRet_2_BadCase_WaitingFunction, uint32, param1, uint32, limit)
RBTPSW_DECL_FUNC_NORET_3PARAM(BackgroundTestApp_NoRet_3_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, limit )
RBTPSW_DECL_FUNC_NORET_4PARAM(BackgroundTestApp_NoRet_4_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, limit )
RBTPSW_DECL_FUNC_NORET_5PARAM(BackgroundTestApp_NoRet_5_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, limit )
RBTPSW_DECL_FUNC_NORET_6PARAM(BackgroundTestApp_NoRet_6_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, limit )
RBTPSW_DECL_FUNC_NORET_7PARAM(BackgroundTestApp_NoRet_7_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, limit )
RBTPSW_DECL_FUNC_NORET_8PARAM(BackgroundTestApp_NoRet_8_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, limit )
RBTPSW_DECL_FUNC_NORET_9PARAM(BackgroundTestApp_NoRet_9_BadCase_WaitingFunction, uint32, param1, uint32, param2, uint32, param3, uint32, param4, uint32, param5, uint32, param6, uint32, param7, uint32, param8, uint32, limit )

/**********************************************************/


/************* RBTPSW_STD_TRUSTED_APP ************/
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_1Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_2Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_3Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_4Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_5Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_6Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_7Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_8Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_9Param_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_9Param_U8_V
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_0Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_1Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_2Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_3Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_4Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_5Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_6Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_7Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_8Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_9Param_UL
#define RBTPSW_PARAM_MANIP_PRE_TRUSTED_9Param_U8

#define RBTPSW_PARAM_MANIP_POST_TRUSTED_1Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_2Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_3Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_4Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_5Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_6Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_7Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_8Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_9Param_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_9Param_U8_V
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_0Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_1Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_2Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_3Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_4Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_5Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_6Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_7Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_8Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_9Param_UL
#define RBTPSW_PARAM_MANIP_POST_TRUSTED_9Param_U8

RBTPSW_DECL_FUNC_NORET_1PARAM(TRUSTED_1Param_V, uint32, p1)
RBTPSW_DECL_FUNC_NORET_2PARAM(TRUSTED_2Param_V, uint32, p1, uint32, p2)
RBTPSW_DECL_FUNC_NORET_3PARAM(TRUSTED_3Param_V, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DECL_FUNC_NORET_4PARAM(TRUSTED_4Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DECL_FUNC_NORET_5PARAM(TRUSTED_5Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DECL_FUNC_NORET_6PARAM(TRUSTED_6Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DECL_FUNC_NORET_7PARAM(TRUSTED_7Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DECL_FUNC_NORET_8PARAM(TRUSTED_8Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DECL_FUNC_NORET_9PARAM(TRUSTED_9Param_V, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DECL_FUNC_NORET_9PARAM(TRUSTED_9Param_U8_V, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DECL_FUNC_RET_0PARAM(uint32, TRUSTED_0Param_UL)
RBTPSW_DECL_FUNC_RET_1PARAM(uint32, TRUSTED_1Param_UL, uint32, p1)
RBTPSW_DECL_FUNC_RET_2PARAM(uint32, TRUSTED_2Param_UL, uint32, p1, uint32, p2)
RBTPSW_DECL_FUNC_RET_3PARAM(uint32, TRUSTED_3Param_UL, uint32, p1, uint32, p2, uint32, p3)
RBTPSW_DECL_FUNC_RET_4PARAM(uint32, TRUSTED_4Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4)
RBTPSW_DECL_FUNC_RET_5PARAM(uint32, TRUSTED_5Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5)
RBTPSW_DECL_FUNC_RET_6PARAM(uint32, TRUSTED_6Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6)
RBTPSW_DECL_FUNC_RET_7PARAM(uint32, TRUSTED_7Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7)
RBTPSW_DECL_FUNC_RET_8PARAM(uint32, TRUSTED_8Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8)
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, TRUSTED_9Param_UL, uint32, p1, uint32, p2, uint32, p3, uint32, p4, uint32, p5, uint32, p6, uint32, p7, uint32, p8, uint32, p9)
RBTPSW_DECL_FUNC_RET_9PARAM(uint32, TRUSTED_9Param_U8, uint8, p1, uint8, p2, uint8, p3, uint8, p4, uint8, p5, uint8, p6, uint8, p7, uint8, p8, uint8, p9)

RBTPSW_DECL_FUNC_NORET_0PARAM(TRUSTED_T_UT_CallWithLocks)

RBTPSW_DECL_FUNC_RET_0PARAM(uint32*, TRUSTED_getStackStart)
RBTPSW_DECL_FUNC_RET_0PARAM(uint32*, TRUSTED_getStackEnd)
/*************************************************/

/*
 * MPU Table Declarations
 */
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW1_LCF)
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW3_GLOBAL_LCF)

#endif


/** @} */
/* End ingroup 'SW-group' */

#endif /* End of multiple include protection */
