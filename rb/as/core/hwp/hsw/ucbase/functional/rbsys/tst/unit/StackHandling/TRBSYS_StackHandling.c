#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      ///< for RBFS_MCORE


#include "TRBSYS_StackHandling_Adaptor.h"
#include "RBSYS_Subsystem.h"
#include "trba_MultiStackTrace.h"
#include "TRBSYS_CpuInfo.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"



/**
 * \Reference
 *  RBSYS_PRC_StackCheckInit, Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose
 *  Verify function to initialize the StackMonitor on all cores
 *
 * \Sequence
 *  Call function RBSYS_PRC_StackCheckInit
 *
 * \ExpectedResult
 *  Cubas function "rba_MultiStackTrace_InitCoreLocalStacks" must be called once per core
 *  Goodcheck for failure word "RBSYS_setStackOverUnderFlowError" must be reported once
 */
SWTEST void TRBSYS_StackCheckInit(void)
{
  uint32 coreId;
  for(coreId = 0; coreId < RB_NUM_CORES; coreId++)
  {
    TRBSYS_setCoreID(coreId);
    RBSYS_PRC_StackCheckInit();
    SWT_EvalEq(TRBSYS_getInitCoreLocalStacksCounter(), 1+coreId);
  }
  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), 1);
}


/**
 * \Reference
 *  RBSYS_PRC_StackCheck, Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose
 *  Verify functionallity of stack monitor on all cores
 *
 * \Sequence
 *  Simulate fault free stack
 *  Call function RBSYS_PRC_StackCheck
 *
 * \ExpectedResult
 *  Cubas function "rba_MultiStackTrace_ScanAllStacks" must be called multiple times to get the free stack
 *  No stack fault must be available
 */
SWTEST void TRBSYS_StackCheck_NoError(void)
{
  uint32 coreId;
  uint32 expectedFreeSpace[] = {RB_STACK0_SIZE_FSW-GetPrivate_STACK_LIMITRED_BYTES(), RB_STACK1_SIZE_FSW-GetPrivate_STACK_LIMITRED_BYTES()};
  for(coreId = 0; coreId < RB_NUM_CORES; coreId++)
  {
    TRBSYS_setCoreID(coreId);
    TRBSYS_SetStackCheckType(TRBSYS_StackCheck_FaultFree);
    RBSYS_PRC_StackCheck();

    SWT_EvalGE(TRBSYS_getScanAllStacksCounter(), 1);
    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), FALSE);
    SWT_EvalEq(GetPrivate_RBSYS_Stack_freespace(coreId), expectedFreeSpace[coreId]);
  }
}


/**
 * \Reference
 *  RBSYS_PRC_StackCheck, Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose
 *  Verify functionallity of stack monitor on all cores for different fault types
 *
 * \Sequence
 *  Simulate stack fault
 *  Call function RBSYS_PRC_StackCheck
 *
 * \ExpectedResult
 *  Cubas function "rba_MultiStackTrace_ScanAllStacks" must be called multiple times to get the free stack
 *  Stack fault must be available with corresponding debug data
 */
SWTEST void TRBSYS_StackCheck_Error0(void)
{
  uint32 coreId, faultIdx;
  TRBSYS_StackCheckTest_t faultTypes[2][3] = {
    {TRBSYS_StackCheck_Core0_LowChkWord0, TRBSYS_StackCheck_Core0_LowChkWord1, TRBSYS_StackCheck_Core0_LowChkWord2},
    {TRBSYS_StackCheck_Core1_LowChkWord0, TRBSYS_StackCheck_Core1_LowChkWord1, TRBSYS_StackCheck_Core1_LowChkWord2}
  };
  uint32 expectedDebug0Values[2][3] = {
    {0x1,0x2,0x4},
    {0x8,0x10,0x20}
  };
  for(coreId = 0; coreId < RB_NUM_CORES; coreId++)
  {
    for(faultIdx = 0; faultIdx < 3; faultIdx++)
    {
      TRBSYS_SetStackCheckType(faultTypes[coreId][faultIdx]);
      RBSYS_PRC_StackCheck();

      SWT_EvalGE(TRBSYS_getScanAllStacksCounter(), 1);

      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), TRUE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), expectedDebug0Values[coreId][faultIdx]);
      SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), GetPrivate_RBSYS_Stack_freespace(coreId));
      SWT_EvalEq(GetPrivate_RBSYS_Stack_freespace(coreId), 0);
    }
  }
}


#if(RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  RBSYS_PRC_StackCheck, Gen_SWCS_HSW_uC_Base_SYS-217
   *
   * \Purpose
   *  Verify functionallity of stack monitor on core 0 and core1
   *
   * \Sequence
   *  Call function RBSYS_PRC_StackCheck
   *
   * \ExpectedResult
   *  Cubas function "rba_MultiStackTrace_ScanAllStacks" must be called multiple times to get the free stack
   *  Stack fault must be available with corresponding debug data (=> free stack space from core 0)
   */
  SWTEST void TRBSYS_StackCheck_Error0_Core0_Core1(void)
  {
    TRBSYS_SetStackCheckType(TRBSYS_StackCheck_Core0_and_Core1_LowChkWord0);
    RBSYS_PRC_StackCheck();

    SWT_EvalGE(TRBSYS_getScanAllStacksCounter(), 1);

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), 0x9);  // 1<<RBSYS_stack0check0 | 1<<RBSYS_stack1check0
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow), GetPrivate_RBSYS_Stack_freespace(0));
    SWT_EvalEq(GetPrivate_RBSYS_Stack_freespace(0), 0);
  }
#endif