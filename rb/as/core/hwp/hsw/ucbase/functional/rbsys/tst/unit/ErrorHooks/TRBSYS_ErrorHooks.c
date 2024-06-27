#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_SysMaxTaskx1Jitter

/* used interfaces */
#include "TRBSYS_Os.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"

/* realized interfaces */
#include "Monitorings/RBSYS_ErrorHooks.h"




/**
 * \Reference
 *  ErrorHook, Gen_SWCS_HSW_uC_Base_SYS-214
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_OSErrorHook"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  adapt return value of OSErrorGetServiceId to OSServiceId_ActivateTask
 *  call ErrorHook callback with parameter E_OK
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
SWTEST void TRBSYS_OsErrorHook_1(void)
{
  TRBSYS_SetServiceId(OSServiceId_ActivateTask);

  ErrorHook(E_OK);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_OSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x10000);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x0);
}


/**
 * \Reference
 *  ErrorHook, Gen_SWCS_HSW_uC_Base_SYS-214
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_OSErrorHook"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  adapt return value of OSErrorGetServiceId to OSServiceId_Os_AdvanceCounter
 *  call ErrorHook callback with parameter E_OS_NOFUNC
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
SWTEST void TRBSYS_OsErrorHook_2(void)
{
  TRBSYS_SetServiceId(OSServiceId_Os_AdvanceCounter);

  ErrorHook(E_OS_NOFUNC);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_OSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x20005);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x0);
}


/**
 * \Reference
 *  ErrorHook, Gen_SWCS_HSW_uC_Base_SYS-214
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_OSErrorHook"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  adapt return value of OSErrorGetServiceId to OSServiceId_None
 *  call ErrorHook callback with parameter E_OS_LIMIT
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
 SWTEST void TRBSYS_OsErrorHook_3(void)
{
  TRBSYS_SetServiceId(OSServiceId_None);

  ErrorHook(E_OS_LIMIT);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_OSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x4);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x0);
}


/**
 * \Reference
 *  ErrorHook, Gen_SWCS_HSW_uC_Base_SYS-214
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_OSErrorHook"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  adapt return value of OSErrorGetServiceId to OSServiceId_ActivateTask
 *  call ErrorHook callback with parameter E_OS_LIMIT
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
SWTEST void TRBSYS_OsErrorHook_4(void)
{
  TRBSYS_SetServiceId(OSServiceId_ActivateTask);

  ErrorHook(E_OS_LIMIT);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_OSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_OSErrorHook), 0x10004);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_OSErrorHook), (uint32) &Os_Entry_TaskBaseCtrlCycx1High);
}


/**
 * \Reference
 *  RBSYS_setSYSErrorHook, RBSYS_IsSYSErrorHookFailureReported, Gen_SWCS_HSW_uC_Base_SYS-220
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_SYSErrorHook"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  call function RBSYS_IsSYSErrorHookFailureReported
 *  call function RBSYS_setSYSErrorHook with corresponding debug data
 *  call function RBSYS_IsSYSErrorHookFailureReported again
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 *  Function RBSYS_IsSYSErrorHookFailureReported returns FALSE before an error is reported, and TRUE afterwards
 */
SWTEST void TRBSYS_setSYSErrorHook(void)
{
  RBSYSError_t d0 = RBSYS_Error_PeripheralReset;
  uint32 d1 = 0x123;

  SWT_EvalEq(RBSYS_IsSYSErrorHookFailureReported(), FALSE);

  RBSYS_setSYSErrorHook(d0,d1);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), d0);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), d1);
  SWT_EvalEq(RBSYS_IsSYSErrorHookFailureReported(), TRUE);
}


/**
 * \Reference
 *  RBSYS_setStackOverUnderFlowError, Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_StackOverUnderFlow"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  call function RBSYS_setStackOverUnderFlowError with corresponding debug data
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
SWTEST void TRBSYS_setStackOverUnderFlowError(void)
{
  uint32 d0 = 0xABC;
  uint32 d1 = 0x123;

  RBSYS_setStackOverUnderFlowError(d0,d1);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), d0);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), d1);
}


/**
 * \Reference
 *  RBSYS_setTaskOverRunError, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  validate report function for RBSYS failure word "RBSYS_TaskOverRun"
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  call function RBSYS_setTaskOverRunError with corresponding debug data
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
 */
SWTEST void TRBSYS_setTaskOverRunError(void)
{
  uint32 d0 = 0x2AAA;
  uint32 d1 = (uint32) &Os_Entry_TaskTPSWKillCore1;

  RBSYS_setTaskOverRunError(d0);

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), d0);
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), d1);
}

#if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
    || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
    )
  /**
  * \Reference
  *  RBSYS_setTaskJitterError, Gen_SWCS_HSW_uC_Base_SYS-218
  *
  * \Purpose
  *  validate report function for RBSYS failure word "RBSYS_TaskJitter"
  *
  * \Sequence
  *  register RBSYS specific callout for SWT DEM stub
  *  call function RBSYS_setTaskJitterError with corresponding debug data
  *
  * \ExpectedResult
  *  DEM_EVENT_STATUS_FAILED is set for the corresponding failure words with corresponding debug data
  */
  SWTEST void TRBSYS_setTaskJitterError(void)
  {
    uint32 d0 = 400000;
    uint32 d1 = 20000;

    RBSYS_setTaskJitterError(d0,d1);

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskJitter), d0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskJitter), d1);
  }
#endif

static boolean TRBSYS_isPassed(Dem_EventIdType EventId)
{
  return DemStub_isTested(EventId) && !DemStub_isFailed(EventId);
}

/**
 * \Reference
 *  RBSYS_setGoodCheckRequest
 *
 * \Purpose
 *  validate central "good check request" hook for RBSYS related failure words
 *
 * \Sequence
 *  register RBSYS specific callout for SWT DEM stub
 *  call function RBSYS_setGoodCheckRequest with all RBSYS related failure words
 *
 * \ExpectedResult
 *  DEM_EVENT_STATUS_PASSED is set for the corresponding failure words
 */
SWTEST void TRBSYS_setGoodCheckRequest(void)
{
  #if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
      || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
      )
    // FW_RBSYS_TaskJitter
    RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_TaskJitter);
    SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskJitter), TRUE);
  #endif

  // FW_RBSYS_StackOverUnderFlow
  RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow);
  SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), TRUE);

  // FW_RBSYS_SYSErrorHook
  RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_SYSErrorHook);
  SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);

  // FW_RBSYS_OSErrorHook
  RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_OSErrorHook);
  SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_OSErrorHook), TRUE);

  // FW_RBSYS_TaskOverRun
  RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_TaskOverRun);
  SWT_EvalEq(TRBSYS_isPassed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
}
