#include "SwTest_Global.h"                    // for SWT functionality

#include "RBSYS_Config.h"                    ///< for RBFS_TargetDevice
#include "TRBSYS_SystemTimer.h"
#include "TRBSYS_uCRegisters.h"

#include "RBSYS_uCModuleEnable.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"
#include "RBSYS_ErrorHooks.h"
#include "TRBSYS_TestInjection.h"
#include "TRBSYS_LocksHelper.h"


#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

/**************************************************************/
/*****          Peripheral Reset for CAN                  *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_CAN_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CAN module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_CAN_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CAN_NoError(void)
{
  RBSYS_CAN_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM3, 0x0);
    SWT_EvalEqX(SWLRESS3, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_RSCFD, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_RSCFD, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_CAN_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CAN module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for MCAN: Reset execution is being processed
 *  Call function RBSYS_CAN_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CAN_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS3 = 1;
  #else
    SYSCTRLSWMRESS_RSCFD = 3;
  #endif

  RBSYS_CAN_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM3);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RSCFD);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_CAN_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CAN module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_CAN_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CAN_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);
  

  RBSYS_CAN_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM3);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RSCFD);
    #endif
  #endif
}

/**************************************************************/
/*****          Peripheral Reset for Flexray              *****/
/**************************************************************/

/* For Renesas devices D1 and D2, there are no module standby registers avalable */
#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))


/**
 * \Reference
 *  RBSYS_FlexRay_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  FlexRay module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_FlexRay_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Flexray_NoError(void)
{
  RBSYS_FlexRay_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM4, 0x0);
    SWT_EvalEqX(SWLRESS4, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_FLXA, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_FLXA, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_FlexRay_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  FlexRay module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for FlexRay: Reset execution is being processed
 *  Call function RBSYS_FlexRay_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Flexray_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS4 = 1;
  #else
    SYSCTRLSWMRESS_FLXA = 3;
  #endif

  RBSYS_FlexRay_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM4);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_FLXA);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_FlexRay_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  Flexray module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_FlexRay_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Flexray_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_FlexRay_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM4);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_FLXA);
    #endif
  #endif
}

#endif

/**************************************************************/
/*****          Peripheral Reset for GTM                  *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_GTM_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  GTM module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_GTM_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_GTM_NoError(void)
{
  RBSYS_GTM_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM5, 0x0);
    SWT_EvalEqX(SWLRESS5, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_GTM, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_GTM, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_GTM_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  GTM module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for GTM: Reset execution is being processed
 *  Call function RBSYS_GTM_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_GTM_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS5 = 1;
  #else
    SYSCTRLSWMRESS_GTM = 1;
  #endif

  RBSYS_GTM_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM5);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_GTM);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_GTM_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  GTM module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_GTM_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_GTM_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_GTM_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM5);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_GTM);
    #endif
  #endif
}


/**************************************************************/
/*****          Peripheral Reset for Ethernet             *****/
/**************************************************************/

/* For Renesas devices D1 and D2, there are no module standby registers avalable */
#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))


/**
 * \Reference
 *  RBSYS_Ethernet_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  Ethernet module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_Ethernet_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Ethernet_NoError(void)
{
  RBSYS_Ethernet_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM6, 0x0);
    SWT_EvalEqX(SWLRESS6, 0x0);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SWT_EvalEqX(SYSCTRLMSR_ETNB, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ETNB, 0x0);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SWT_EvalEqX(SYSCTRLMSR_ETND, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ETND, 0x0);

    SWT_EvalEqX(SYSCTRLMSR_ETNF, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ETNF, 0x0);
  #endif
  //note U2C Family has 2 different types of Ethernet, so the amount of function calls is different
  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 2);
  #else
    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  #endif

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_Ethernet_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  Ethernet module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for Ethernet: Reset execution is being processed
 *  Call function RBSYS_Ethernet_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Ethernet_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS6 = 1;
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SYSCTRLSWMRESS_ETNB = 3;
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SYSCTRLSWMRESS_ETND = 3;
    SYSCTRLSWMRESS_ETNF = 3;
  #endif

  RBSYS_Ethernet_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM6);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETNB);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETNF);
      SWT_EvalEqX(DemStub_GetNumOfReportErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook),2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETND);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_Ethernet_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  Ethernet module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_Ethernet_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_Ethernet_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_Ethernet_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  
  // note: U2C Family has 2 dedicated Ethernet peripherals -> double the amount of fnc calls
  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 2);
  #else
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  #endif

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM6);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETNB);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETN_T1S);
      SWT_EvalEqX(DemStub_GetNumOfReportErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook),2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ETN);
    #endif
  #endif
}

#endif

/**************************************************************/
/*****          Peripheral Reset for SENT                 *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_SENT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  SENT module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_SENT_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_SENT_NoError(void)
{
  RBSYS_SENT_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM7, 0x0);
    SWT_EvalEqX(SWLRESS7, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_RSENT, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_RSENT, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_SENT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  SENT module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for SENT: Reset execution is being processed
 *  Call function RBSYS_SENT_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_SENT_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS7 = 1;
  #else
    SYSCTRLSWMRESS_RSENT = 0xFFu;
  #endif

  RBSYS_SENT_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM7);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RSENT);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_SENT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  SENT module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_SENT_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_SENT_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_SENT_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM7);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RSENT);
    #endif
  #endif
}


/**************************************************************/
/*****          Peripheral Reset for HSUSRT               *****/
/**************************************************************/

/* For Renesas devices D1 and D2, there are no module standby registers avalable */
/* Only EVA Device of U2C support HSUSRT*/
#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2) \
    && (RBFS_uCFamily != RBFS_uCFamily_RenesasU2C) )


/**
 * \Reference
 *  RBSYS_HSUSRT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  HSUSRT module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_HSUSRT_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_HSUSRT_NoError(void)
{
  RBSYS_HSUSRT_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM8, 0x0);
    SWT_EvalEqX(SWLRESS8, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_RHSIF, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_RHSIF, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_HSUSRT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  HSUSRT module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for HSUSRT: Reset execution is being processed
 *  Call function RBSYS_HSUSRT_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_HSUSRT_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS8 = 1;
  #else
    SYSCTRLSWMRESS_RHSIF = 1;
  #endif

  RBSYS_HSUSRT_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM8);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RHSIF);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_HSUSRT_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  HSUSRT module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_HSUSRT_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_HSUSRT_ErrorWhileTimeout(void)
{
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None))
    #warning this functionality is only supported for K3ED Emulation Device, not on regular U2C Devices
  #else
    TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

    RBSYS_HSUSRT_SetToRunMode();

    SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

    #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
      SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM8);
      #else
        SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RHSIF);
      #endif
    #endif
  #endif 
}

#endif

/**************************************************************/
/*****          Peripheral Reset for CSIH                 *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_SPI_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CSIH module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_SPI_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CSIH_NoError(void)
{
  RBSYS_SPI_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM10, 0x0);
    SWT_EvalEqX(SWLRESS10, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_MSPI, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_MSPI, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_SPI_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CSIH module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for CSIH: Reset execution is being processed
 *  Call function RBSYS_SPI_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CSIH_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS10 = 1;
  #else
    SYSCTRLSWMRESS_MSPI = 0x3FFu;
  #endif

  RBSYS_SPI_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM10);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_MSPI);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_SPI_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  CSIH module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_SPI_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_CSIH_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_SPI_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM10);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_MSPI);
    #endif
  #endif
}


/**************************************************************/
/*****          Peripheral Reset for RLIN3                *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_RLIN3_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  RLIN3 module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_RLIN3_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_RLIN3_NoError(void)
{
  RBSYS_RLIN3_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM11, 0x0);
    SWT_EvalEqX(SWLRESS11, 0x0);
  #else
    SWT_EvalEqX(SYSCTRLMSR_RLIN3, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_RLIN3, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_RLIN3_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  RLIN3 module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for RLIN3: Reset execution is being processed
 *  Call function RBSYS_RLIN3_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_RLIN3_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS11 = 1;
  #else
    SYSCTRLSWMRESS_RLIN3 = 0xFFFFFFu;
  #endif

  RBSYS_RLIN3_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM11);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RLIN3);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_RLIN3_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  RLIN3 module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_RLIN3_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_RLIN3_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_RLIN3_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM11);
    #else
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_RLIN3);
    #endif
  #endif
}


/**************************************************************/
/*****          Peripheral Reset for ADC                  *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_ADC_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  ADC module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_ADC_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_ADC_NoError(void)
{
  RBSYS_ADC_SetToRunMode();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEqX(MSR_LM12, 0x0);
    SWT_EvalEqX(SWLRESS12, 0x0);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SWT_EvalEqX(SYSCTRLMSR_ADCJ_AWO, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ADCJ_AWO, 0x0);

    SWT_EvalEqX(SYSCTRLMSR_ADCJ_ISO, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ADCJ_ISO, 0x0);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SWT_EvalEqX(SYSCTRLMSR_ADCK_AWO, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ADCK_AWO, 0x0);

    SWT_EvalEqX(SYSCTRLMSR_ADCK_ISO, 0x0);
    SWT_EvalEqX(SYSCTRLSWMRESS_ADCK_ISO, 0x0);
  #endif

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  #else
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 2);
  #endif

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_ADC_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  ADC module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for ADC: Reset execution is being processed
 *  Call function RBSYS_ADC_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_ADC_ErrorWhileReset(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWLRESS12 = 1;
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SYSCTRLSWMRESS_ADCJ_AWO = 1;
    SYSCTRLSWMRESS_ADCJ_ISO = 3;
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SYSCTRLSWMRESS_ADCK_AWO = 1;
    SYSCTRLSWMRESS_ADCK_ISO = 3;
  #endif

  RBSYS_ADC_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM12);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEqX(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCJ_AWO);
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCJ_ISO);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      SWT_EvalEqX(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCK_AWO);
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCK_ISO);
    #endif
  #endif
}


/**
 * \Reference
 *  RBSYS_ADC_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  ADC module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_ADC_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_ADC_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_ADC_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);
  #else
    SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 2);
  #endif

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&MSR_LM12);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEqX(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCJ_AWO);
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCJ_ISO);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      SWT_EvalEqX(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 2);
      //SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCK_AWO);
      SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_ADCK_ISO);
    #endif
  #endif
}


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

/**************************************************************/
/*****          Peripheral Reset for TAUD0                *****/
/**************************************************************/


/**
 * \Reference
 *  RBSYS_TAUD0_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  TAUD0 module must be set to run mode
 *
 * \Sequence
 *  Call function RBSYS_TAUD0_SetToRunMode
 *
 * \ExpectedResult
 *  Corresponding Module Standby Register is cleared (0x0)
 *  Corresponding Software Limited Reset Status Register contains default value
 *  Core local lock must be called and released
 *  No failure set (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_TAUD0_NoError(void)
{
  RBSYS_TAUD0_SetToRunMode();

  SWT_EvalEqX(SYSCTRLMSR_TAUD, 0x0);
  SWT_EvalEqX(SYSCTRLSWMRESS_TAUD, 0x0);

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
  #endif
}


/**
 * \Reference
 *  RBSYS_TAUD0_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  TAUD0 module could not be set to run mode because it's in reset state
 *
 * \Sequence
 *  Set Software Limited Reset Status for TAUD0: Reset execution is being processed
 *  Call function RBSYS_TAUD0_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock is not called
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_TAUD0_ErrorWhileReset(void)
{
  SYSCTRLSWMRESS_TAUD = 1;

  RBSYS_TAUD0_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 0);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralReset);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_TAUD);
  #endif
}


/**
 * \Reference
 *  RBSYS_TAUD0_SetToRunMode, Gen_SWCS_HSW_uC_Base_SYS-251
 *
 * \Purpose
 *  TAUD0 module could not be set to run mode due to timeout
 *
 * \Sequence
 *  Set timeout (timer elapsed)
 *  Call function RBSYS_TAUD0_SetToRunMode
 *
 * \ExpectedResult
 *  Core local lock must be called and released
 *  Corresponding failure set only within application (verified via DebugData D0 and D1)
 */
SWTEST void TRBSYS_PeripheralReset_TAUD0_ErrorWhileTimeout(void)
{
  TRBSYS_InjectTicks = RBSYS_convertUsecToTimerTicks(31);

  RBSYS_TAUD0_SetToRunMode();

  SWT_EvalEq(TRBSYS_CoreLocalLock.nest_cnt, 0);
  SWT_EvalEq(TRBSYS_CoreLocalLock.fnc_call_cnt, 1);

  #if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_PeripheralResetTimeOut);
    SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), (uint32)&SYSCTRLMSR_TAUD);
  #endif
}

#endif



#else //( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
/**
    * \TestCaseName TRBSYS_Dummy
    *
    * \Reference
    * Dummy
    *
    *
    * \Purpose Dummy testcase for missing Stellar Unittests. To be removed once there are Stellar implementations.
    *
    * \Sequence
    *
    *
    * \ExpectedResult
    *
    */
  SWTEST void TRBSYS_Dummy(void)
  {
      SWT_EvalEx(TRUE, "Feature is not supported for Series yet.");
  }
#endif