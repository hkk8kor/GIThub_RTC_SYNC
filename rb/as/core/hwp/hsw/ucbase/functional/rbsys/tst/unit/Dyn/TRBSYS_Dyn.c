#include "SwTest_Global.h"         // for SWT functionality

#include "RBSYS_Config.h"          ///< for RBFS_MCORE, RBFS_SysTask0p5ms

#include "TRBSYS_Dyn_Adaptor.h"    // Attention: TRBSYS_Dyn_Adaptor.h must be included before TRBSYS_Os.h

#include "TRBSYS_Os.h"
#include "TRBSYS_LocksImplIntern.h"
#include "TRBSYS_Os_ConfigInterrupts.h"
#include "csw/RBSYS_TaskInfo.h"    // ensure include of original RBSYS header instead of CoreStub
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "TRBSYS_Idle.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "RBSYS_TimerOsConfig.h"
#include "TRBSYS_TimerOsConfig.h"
#include "RBSYS_TaskStats.h"
#include "TRBSYS_TaskStats.h"
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_OsServices.h"
#include "TRBSYS_TestInjection.h"
#include "TRBSYS_rba_Runtime.h"
#include "TRBSYS_TestInjection.h"
#include "RBSYS_StartupTimingIntern.h"
#include "TRBSYS_ExceptionHandler.h"
#include "TRBSYS_LocksHelper.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"
#include "RBSYS_ErrorHooks.h"

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )


/**
 * \Reference
 *  TaskInit, RBMESG_RBSYSBaseOSActive, Gen_SWCS_HSW_uC_Base_SYS-269, Gen_SWCS_HSW_uC_Base_SYS-352
 *
 * \Purpose
 *  Ensure in case of Control mode or BaseOS mode the corresponding process list
 *
 * \Sequence
 *  1) call TaskInit once in Control mode
 *  2) call TaskInit once in BaseOS mode (set RBMESG_RBSYSBaseOSActive)
 *
 * \ExpectedResult
 *  1) Process list must be the one from Control mode
 *  2) Process list must be the one from BaseOS mode
 */
SWTEST void TRBSYS_TaskInit_prclist(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

  // Control Mode
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, FALSE);
  TRBSYS_RunTaskStandalone(TaskInit);

  SWT_EvalEq((uint32)GetPrivate_prclist_taskinit(), (uint32)GetPrivate_c_TaskInit());
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  SWT_EvalEq((uint32)GetPrivate_prclist_task0p5ms(), (uint32)GetPrivate_c_Task0p5ms());
#endif
  SWT_EvalEq((uint32)GetPrivate_prclist_task1ms(), (uint32)GetPrivate_c_Task1ms());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1h(), (uint32)GetPrivate_c_Taskx1h());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1l(), (uint32)GetPrivate_c_Taskx1l());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2(), (uint32)GetPrivate_c_Taskx2());
#if (RBFS_MCORE == RBFS_MCORE_ON)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2p(), (uint32)GetPrivate_c_Taskx2p());
#endif
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4(), (uint32)GetPrivate_c_Taskx4());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx8(), (uint32)GetPrivate_c_Taskx8());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx24(), (uint32)GetPrivate_c_Taskx24());
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4pl(), (uint32)GetPrivate_c_Taskx4pl());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx200bg(), (uint32)GetPrivate_c_Taskx200bg());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskExtPrio1(), (uint32)GetPrivate_c_TaskExtPrio1());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskExtPrio2(), (uint32)GetPrivate_c_TaskExtPrio2());
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1guest(), (uint32)GetPrivate_c_Taskx1Guest());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2guest(), (uint32)GetPrivate_c_Taskx2Guest());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4guest(), (uint32)GetPrivate_c_Taskx4Guest());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx10guest(), (uint32)GetPrivate_c_Taskx10Guest());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx20guest(), (uint32)GetPrivate_c_Taskx20Guest());
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx10(), (uint32)GetPrivate_c_Taskx10());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx20(), (uint32)GetPrivate_c_Taskx20());
#endif


  // BaseOS Mode
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);
  TRBSYS_RunTaskStandalone(TaskInit);

  SWT_EvalEq((uint32)GetPrivate_prclist_taskinit(), (uint32)GetPrivate_c_TaskInitBaseOS());
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  SWT_EvalEq((uint32)GetPrivate_prclist_task0p5ms(), (uint32)GetPrivate_c_Task0p5msBaseOS());
#endif
  SWT_EvalEq((uint32)GetPrivate_prclist_task1ms(), (uint32)GetPrivate_c_Task1msBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1h(), (uint32)GetPrivate_c_Taskx1hBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1l(), (uint32)GetPrivate_c_Taskx1lBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2(), (uint32)GetPrivate_c_Taskx2BaseOS());
#if (RBFS_MCORE == RBFS_MCORE_ON)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2p(), (uint32)GetPrivate_c_Taskx2pBaseOS());
#endif
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4(), (uint32)GetPrivate_c_Taskx4BaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx8(), (uint32)GetPrivate_c_Taskx8BaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx24(), (uint32)GetPrivate_c_Taskx24BaseOS());
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4pl(), (uint32)GetPrivate_c_Taskx4plBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx200bg(), (uint32)GetPrivate_c_Taskx200bgBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskExtPrio1(), (uint32)GetPrivate_c_TaskExtPrio1BaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskExtPrio2(), (uint32)GetPrivate_c_TaskExtPrio2BaseOS());
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx1guest(), (uint32)GetPrivate_c_Taskx1GuestBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx2guest(), (uint32)GetPrivate_c_Taskx2GuestBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx4guest(), (uint32)GetPrivate_c_Taskx4GuestBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx10guest(), (uint32)GetPrivate_c_Taskx10GuestBaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx20guest(), (uint32)GetPrivate_c_Taskx20GuestBaseOS());
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx10(), (uint32)GetPrivate_c_Taskx10BaseOS());
  SWT_EvalEq((uint32)GetPrivate_prclist_taskx20(), (uint32)GetPrivate_c_Taskx20BaseOS());
#endif
}


/* Dummy test functions within a corresponding process table */
static uint32 TRBSYS_UnitTestFunc1_cnt = 0;
static void TRBSYS_UnitTestFunc1(void)
{
  TRBSYS_UnitTestFunc1_cnt++;
}

static uint32 TRBSYS_UnitTestFunc2_cnt = 0;
static void TRBSYS_UnitTestFunc2(void)
{
  TRBSYS_UnitTestFunc2_cnt++;
}

static const PRC_PTR TRBSYS_UnitTestTable[] =
{
  &TRBSYS_UnitTestFunc1,
  &TRBSYS_UnitTestFunc2,
  NULL
};

static const PRC_PTR *TRBSYS_UnitTestTablePtr = TRBSYS_UnitTestTable;


/**
 * \Reference
 *  taskbody_prc_calls
 *
 * \Purpose
 *  Ensure call for each process within the correpsonding table
 *
 * \Sequence
 *  Call function "taskbody_prc_calls" with correpsonding parameter
 *  mapping to a process test table
 *
 * \ExpectedResult
 *  Each function within the process table must be called once
 */
SWTEST void TRBSYS_taskbody_prc_calls(void)
{
  CallPrivate_taskbody_prc_calls(TRBSYS_UnitTestTablePtr);

  SWT_EvalEq(TRBSYS_UnitTestFunc1_cnt, 1);
  SWT_EvalEq(TRBSYS_UnitTestFunc2_cnt, 1);
}


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  /**
  * \Reference
  *  TaskInit, RBSYS_PRC_ResetMaxLockTime_Init, Gen_SWCS_HSW_uC_Base_SYS-220
  *
  * \Purpose
  *  Ensure that maximum lock time is cleared after finishing all processes within init task
  *
  * \Sequence
  *  1) Call TaskInit once in Control mode
  *  2) Call TaskInit once in BaseOS mode (set RBMESG_RBSYSBaseOSActive)
  *
  * \ExpectedResult
  *  Function RBSYS_PRC_ResetMaxLockTime_Init must be called once in Control mode and also once in BaseOS mode
  */
  SWTEST void TRBSYS_TaskInit_ResetMaxLockTime(void)
  {
    RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

    // Control Mode
    RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, FALSE);
    TRBSYS_RunTaskStandalone(TaskInit);
    SWT_EvalEq(TRBSYS_ResetMaxLock_cnt , 1);

    // BaseOS Mode
    RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);
    TRBSYS_RunTaskStandalone(TaskInit);
    SWT_EvalEq(TRBSYS_ResetMaxLock_cnt , 2);
  }
#endif


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  TaskInit, RBSYS_EnableIRQ_SWINT0, Gen_SWCS_HSW_uC_Base_SYS-276
   *
   * \Purpose
   *  Ensure that software interrupt 0 used for BERT is enabled in case of MCORE
   *
   * \Sequence
   *  Call TaskInit
   *
   * \ExpectedResult
   *  Function RBSYS_EnableIRQ_SWINT0 must be called once
   */
  SWTEST void TRBSYS_EnableIRQ_SWINT0(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    TRBSYS_RunTaskStandalone(TaskInit);
    SWT_EvalEq(TRBSYS_Os_Enable_ISRSWINT0_CallCnt , 0);
    TRBSYS_setCoreID(RBSYS_CORE_ID_1);
    TRBSYS_RunTaskStandalone(TaskInitP);
    SWT_EvalEq(TRBSYS_Os_Enable_ISRSWINT0_CallCnt , 1);
  }
#endif


/**
 * \Reference
 *  TaskInit, TaskInitP, RBSYS_SetupOsTimer, RBSYS_EnableOsTimerIRQs, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Ensure configuration and enabling of timer interrupt within TaskInit (running on core0) and TaskInitP ((running on core1)
 *
 * \Sequence
 *  1st: Call TaskInit
 *  2nd: Call TaskInitP
 *
 * \ExpectedResult
 *  Ensure call of function RBSYS_SetupOsTimer from Core0 only
 *  Ensure call of function RBSYS_EnableOsTimerIRQs from both cores
 *  Ensure that "RBSYS_SyncBarrier(RBSYS_OsTimerSetupFinished)" is called between
 *   "RBSYS_SetupOsTimer" and "RBSYS_EnableOsTimerIRQs" (realized inside stub "TRBSYS_TimerOsConfig.c")
 *  Ensure that RBSYS_SetInitTaskTimestamp is called
 */
extern uint32 RBSYS_InitTaskTimestamp[RBSYS_MaxNumberOfInitTaskTimestamps];
SWTEST void TRBSYS_TaskInit_OsTimer(void)
{

  unsigned int coreID = RBSYS_CORE_ID_0;
  TRBSYS_setCoreID(coreID);

  SWT_EvalEq(TRBSYS_SetupOsTimer_cnt[coreID], 0);
  SWT_EvalEq(TRBSYS_EnableOsTimerIRQs_cnt[coreID], 0);

  TRBSYS_setRealtimeTickCtr(0x42424242);

  TRBSYS_RunTaskStandalone(TaskInit);

  SWT_EvalEq(RBSYS_InitTaskTimestamp[RBSYS_TimestampInitTask], 0x42424242);

  SWT_EvalEq(TRBSYS_SetupOsTimer_cnt[coreID], 1);
  SWT_EvalEq(TRBSYS_EnableOsTimerIRQs_cnt[coreID], 1);
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    SWT_Eval(TRBSYS_SyncBarrier4SetupOsTimer[coreID]);
    SWT_Eval(TRBSYS_SyncBarrier4EnableOsTimerIRQs[coreID]);
  #endif


  #if (RBFS_MCORE == RBFS_MCORE_ON)
    coreID = RBSYS_CORE_ID_1;
    TRBSYS_setCoreID(coreID);

    SWT_EvalEq(TRBSYS_SetupOsTimer_cnt[coreID], 0);
    SWT_EvalEq(TRBSYS_EnableOsTimerIRQs_cnt[coreID], 0);

    TRBSYS_setRealtimeTickCtr(0x12345678);

    TRBSYS_RunTaskChained(TaskInitP);

    SWT_EvalEq(RBSYS_InitTaskTimestamp[RBSYS_TimestampInitTaskP], 0x12345678);

    SWT_Eval(!TRBSYS_SyncBarrier4SetupOsTimer[coreID]);
    SWT_EvalEq(TRBSYS_SetupOsTimer_cnt[coreID], 0);

    SWT_Eval(TRBSYS_SyncBarrier4EnableOsTimerIRQs[coreID]);
    SWT_EvalEq(TRBSYS_EnableOsTimerIRQs_cnt[coreID], 1);
  #endif

}


#if (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF)
  /**
   * \Reference
   *  TerminateTask, Gen_SWCS_HSW_uC_Base_SYS-214
   *
   * \Purpose
   *  Ensure that OS API TerminateTask is called at end of each active and inactive task in case TPSW capsule (SC3 or SC4) is active
   *
   * \Sequence
   *  - Call each task in Control mode
   *  - Call each task in BaseOS mode (set RBMESG_RBSYSBaseOSActive)
   *
   * \ExpectedResult
   *  Function TerminateTask must be called in Control mode at end of each task once
   */
  SWTEST void TRBSYS_TerminateTask(void)
  {
    int i;
    RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

    // Control mode
    RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, FALSE);
    TRBSYS_RunTaskStandalone(TaskInit);
    for (i = 0; i<OS_NUM_TASKS; i++)
    {
      TRBSYS_TerminateTask_cnt = 0;
      TRBSYS_RunTaskStandalone(Os_const_tasks[i]);
      SWT_EvalEq(TRBSYS_TerminateTask_cnt, 1);
    }

    // BaseOs mode
    RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);
    TRBSYS_RunTaskStandalone(TaskInit);
    for (i = 0; i<OS_NUM_TASKS; i++)
    {
      TRBSYS_TerminateTask_cnt = 0;
      TRBSYS_RunTaskStandalone(Os_const_tasks[i]);
      SWT_EvalEq(TRBSYS_TerminateTask_cnt, 1);
    }
  }
#endif


/**
 * \Reference
 *  RBMESG_Task0p5msCnt_u32. RBMESG_Task0p5msCompletedCnt_u32, RBMESG_Task1msCnt_u32, RBMESG_Task1msCompletedCnt_u32,
 *  RBMESG_TaskBaseCtrlx1LowCnt_u32, RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32, RBMESG_TaskBaseCtrlx2Cnt_u32, RBMESG_TaskBaseCtrlx2CompletedCnt_u32,
 *  RBMESG_TaskBaseCtrlx2pCnt_u32, RBMESG_TaskBaseCtrlx2pCompletedCnt_u32, RBMESG_TaskBaseCtrlx4Cnt_u32, RBMESG_TaskBaseCtrlx4CompletedCnt_u32
 *  RBMESG_TaskBaseCtrlx8Cnt_u32, RBMESG_TaskBaseCtrlx8CompletedCnt_u32, RBMESG_TaskBaseCtrlx24Cnt_u32, RBMESG_TaskBaseCtrlx24CompletedCnt_u32,
 *  Gen_SWCS_HSW_uC_Base_SYS-215, Gen_SWCS_HSW_uC_Base_SYS-216, Gen_SWCS_HSW_uC_Base_SYS-295, Gen_SWCS_HSW_uC_Base_SYS-352
 *
 * \Purpose
 *  Ensure corresponding task activation via task chain and increment of task counters
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  1. Activate 0.5ms task [RBFS_SysTask0p5ms_ON]
 *  2. Activate 1ms task [RBFS_SysTask0p5ms_OFF]
 *  3. Call x1High task
 *
 * \ExpectedResult
 *  1. chained activation of 1ms task must happen every 2nd time beginning with 1, 3, ... and the task counters must be incremented accordingly
 *  2. task counter of 1ms must be incremented on every activation
 *  3. complete task chain must be verified via corresponding increment of the task counters
 */
SWTEST void TRBSYS_TaskChain(void)
{
  int i;

  #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
    RBMESG_DefineMESGDef(RBMESG_Task0p5msCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_Task0p5msCompletedCnt_u32);
  #endif

  RBMESG_DefineMESGDef(RBMESG_Task1msCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_Task1msCompletedCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1LowCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2pCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
  #endif

  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx8Cnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx24Cnt_u32);
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10Cnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20Cnt_u32);
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
  #endif

  TRBSYS_RunTaskStandalone(TaskInit);

  for (i = 0; i < 500; i++)
  {
    // run ISR that triggers 0.5ms/1ms task chain
    Os_Entry_ISRSTM04();
    #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
      // ensure activation of 0.5ms task
      SWT_EvalEq(Task0p5ms->task, i+1);
      RBMESG_RcvMESGDef(RBMESG_Task0p5msCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_Task0p5msCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_Task0p5msCompletedCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_Task0p5msCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(Task0p5ms), l_RBMESG_Task0p5msCnt_u32);

      // ensure chained activation of 1ms task
      SWT_EvalEq(Task1ms->task, i/2+1);
      RBMESG_RcvMESGDef(RBMESG_Task1msCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_Task1msCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_Task1msCompletedCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_Task1msCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(Task1ms), l_RBMESG_Task1msCnt_u32);
    #else
      // ensure 0.5ms task is not activated
      SWT_EvalEq(Task0p5ms->task, 0);

      // ensure activation of 1ms task
      SWT_EvalEq(Task1ms->task, i+1);
      RBMESG_RcvMESGDef(RBMESG_Task1msCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_Task1msCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_Task1msCompletedCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_Task1msCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(Task1ms), l_RBMESG_Task1msCnt_u32);
    #endif

    // run ISR that triggers TaskBaseCtrl task chain
    Os_Entry_ISRSTM05();

    // ensure activation of x1High task
    SWT_EvalEq(TaskBaseCtrlCycx1High->task, i+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
    SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);
    SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1CompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx1High), l_RBMESG_TaskBaseCtrlx1Cnt_u32 );


    // ensure chained activation of x1Low task
    SWT_EvalEq(TaskBaseCtrlCycx1Low->task, i+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1LowCnt_u32);
    SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1LowCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);
    SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx1Low), l_RBMESG_TaskBaseCtrlx1LowCnt_u32);


    // ensure chained activation of x2 task
    SWT_EvalEq(TaskBaseCtrlCycx2->task, i/2+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);
    SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);
    SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2CompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx2), l_RBMESG_TaskBaseCtrlx2Cnt_u32);

    #if (RBFS_MCORE == RBFS_MCORE_ON)
      // ensure chained activation of x2p task
      SWT_EvalEq(TaskBaseCtrlCycx2p->task, i/2+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2pCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2pCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx2p), l_RBMESG_TaskBaseCtrlx2pCnt_u32);
    #else
      // ensure x2p task is not activated
      SWT_EvalEq(TaskBaseCtrlCycx2p->task, 0);
    #endif

    // ensure chained activation of x4 task
    SWT_EvalEq(TaskBaseCtrlCycx4->task, i/4+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);
    SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);
    SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4CompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx4), l_RBMESG_TaskBaseCtrlx4Cnt_u32);

    // ensure chained activation of x8 task
    SWT_EvalEq(TaskBaseCtrlCycx8->task, i/8+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx8Cnt_u32);
    SWT_EvalEq(i/8+1, l_RBMESG_TaskBaseCtrlx8Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);
    SWT_EvalEq(i/8+1, l_RBMESG_TaskBaseCtrlx8CompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx8), l_RBMESG_TaskBaseCtrlx8Cnt_u32);

    // ensure chained activation of x24 task
    SWT_EvalEq(TaskBaseCtrlCycx24->task, i/24+1);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx24Cnt_u32);
    SWT_EvalEq(i/24+1, l_RBMESG_TaskBaseCtrlx24Cnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);
    SWT_EvalEq(i/24+1, l_RBMESG_TaskBaseCtrlx24CompletedCnt_u32);
    SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx24), l_RBMESG_TaskBaseCtrlx24Cnt_u32);

    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
      #if (RBFS_MCORE == RBFS_MCORE_ON) // x2p will trigger x200bg
        // ensure chained activation of x4pLow task
        SWT_EvalEq(TaskBaseCtrlCycx4pLow->task, i/4+1);
        RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
        SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4pLowCnt_u32);
        RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);
        SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);
        SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx4pLow), l_RBMESG_TaskBaseCtrlx4pLowCnt_u32);

        // ensure chained activation of x200 background task
        SWT_EvalEq(TaskBaseCtrlCycx200Background->task, i/200+1);
        RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
        SWT_EvalEq(i/200+1, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
        RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);
        SWT_EvalEq(i/200+1, l_RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);
        SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx200Background), l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      #endif

      // activate event based task "TaskEventCtrlExtPrio1"
      TRBSYS_RunTaskChained(TaskEventCtrlExtPrio1);
      SWT_EvalEq(TaskEventCtrlExtPrio1->task, i+1);
      RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskEventCtrlExtPrio1), l_RBMESG_TaskEventCtrlExtPrio1Cnt_u32);

      // activate event based task "TaskEventCtrlExtPrio2"
      TRBSYS_RunTaskChained(TaskEventCtrlExtPrio2);
      SWT_EvalEq(TaskEventCtrlExtPrio2->task, i+1);
      RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskEventCtrlExtPrio2), l_RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
    #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
      // ensure activation of TaskBaseCtrlCycx1Guest
      SWT_EvalEq(TaskBaseCtrlCycx1Guest->task, i+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1GuestCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx1Guest), l_RBMESG_TaskBaseCtrlx1GuestCnt_u32);

      // ensure activation of TaskBaseCtrlCycx2Guest
      SWT_EvalEq(TaskBaseCtrlCycx2Guest->task, i/2+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2GuestCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);
      SWT_EvalEq(i/2+1, l_RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx2Guest), l_RBMESG_TaskBaseCtrlx2GuestCnt_u32);

      // ensure activation of TaskBaseCtrlCycx4Guest
      SWT_EvalEq(TaskBaseCtrlCycx4Guest->task, i/4+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
      SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4GuestCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);
      SWT_EvalEq(i/4+1, l_RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx4Guest), l_RBMESG_TaskBaseCtrlx4GuestCnt_u32);

      // ensure activation of xTaskBaseCtrlCycx10Guest
      SWT_EvalEq(TaskBaseCtrlCycx10Guest->task, i/10+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
      SWT_EvalEq(i/10+1, l_RBMESG_TaskBaseCtrlx10GuestCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);
      SWT_EvalEq(i/10+1, l_RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx10Guest), l_RBMESG_TaskBaseCtrlx10GuestCnt_u32);

      // ensure activation of xTaskBaseCtrlCycx20Guest
      SWT_EvalEq(TaskBaseCtrlCycx20Guest->task, i/20+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
      SWT_EvalEq(i/20+1, l_RBMESG_TaskBaseCtrlx20GuestCnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
      SWT_EvalEq(i/20+1, l_RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx20Guest), l_RBMESG_TaskBaseCtrlx20GuestCnt_u32);
    #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      // ensure activation of xTaskBaseCtrlCycx10
      SWT_EvalEq(TaskBaseCtrlCycx10->task, i/10+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10Cnt_u32);
      SWT_EvalEq(i/10+1, l_RBMESG_TaskBaseCtrlx10Cnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);
      SWT_EvalEq(i/10+1, l_RBMESG_TaskBaseCtrlx10CompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx10), l_RBMESG_TaskBaseCtrlx10Cnt_u32);

      // ensure activation of xTaskBaseCtrlCycx20
      SWT_EvalEq(TaskBaseCtrlCycx20->task, i/20+1);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20Cnt_u32);
      SWT_EvalEq(i/20+1, l_RBMESG_TaskBaseCtrlx20Cnt_u32);
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
      SWT_EvalEq(i/20+1, l_RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
      SWT_EvalEq(TRBSYS_get_current_taskcnt(TaskBaseCtrlCycx20), l_RBMESG_TaskBaseCtrlx20Cnt_u32);
    #endif
  }
}




#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  /**
   * \Reference
   *  TaskBaseCtrlx4pLow
   *
   * \Purpose
   *  Verify activation of TaskBaseCtrlx4pLow
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call Os_Cbk_TaskEnd of Taskx4
   *
   * \ExpectedResult
   *  Ensure that TaskBaseCtrlx4pLow is activated at the end of TaskBaseCtrlx4
   */
  SWTEST void TRBSYS_TaskBaseCtrlx4pLow(void)
  {
    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);

    TRBSYS_RunTaskStandalone(TaskInit);
    SWT_EvalEq(0, l_RBMESG_TaskBaseCtrlx4pLowCnt_u32);

    Os_Cbk_TaskEnd(TaskBaseCtrlCycx4);

    RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
    SWT_EvalEq(1, l_RBMESG_TaskBaseCtrlx4pLowCnt_u32);
  }


  /**
   * \Reference
   *  TaskBaseCtrlx200Background
   *
   * \Purpose
   *  Verify activation of TaskBaseCtrlx200Background
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Activate TaskBaseCtrlCycx2p multiple times
   *
   * \ExpectedResult
   *  Ensure that TaskBaseCtrlx200Background is activated every hundredth time
   */
  SWTEST void TRBSYS_TaskBaseCtrlx200Background_Activation(void)
  {
    int i, j;

    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

    TRBSYS_RunTaskStandalone(TaskInit);

    for (i = 0; i < 4; i++)
    {
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(i, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

      // every first x2p from 100 shall activate x200bg
      TRBSYS_RunTaskChained(TaskBaseCtrlCycx2p);

      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

      for (j = 0; j < 99; j++)
      {
        TRBSYS_RunTaskChained(TaskBaseCtrlCycx2p);
      }

      // no further activation of x200bg
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(i+1, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    }

    SWT_EvalEq(0, GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation());
  }


  /**
   * \Reference
   *  TaskBaseCtrlx200Background
   *
   * \Purpose
   *  Verify skipped activation of TaskBaseCtrlx200Background
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Simulate still running TaskBaseCtrlx200Background
   *  Activate TaskBaseCtrlCycx2p multiple times
   *
   * \ExpectedResult
   *  Ensure that skip counter of TaskBaseCtrlx200Background is incremented every time instead of real activation
   */
  SWTEST void TRBSYS_TaskBaseCtrlx200Background_SkippedActivation(void)
  {
    int i, j;

    RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

    TRBSYS_RunTaskStandalone(TaskInit);
    TRBSYS_SetTaskState(TaskBaseCtrlCycx200Background, RUNNING);

    for (i = 0; i < 4; i++)
    {
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(0, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(i, GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation());

      TRBSYS_RunTaskChained(TaskBaseCtrlCycx2p);

      SWT_EvalEq(i+1, GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation());

      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(0, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);

      for (j = 0; j < 99; j++)
      {
        TRBSYS_RunTaskChained(TaskBaseCtrlCycx2p);
      }

      // no further activation of x200bg
      RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
      SWT_EvalEq(0, l_RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
    }

    SWT_EvalEq(4, GetPrivate_RBSYS_TASKcnt_x200bg_skippedActivation());

  }

#endif


/**
 * \Reference
 *  Os_Cbk_Idle, Gen_SWCS_HSW_uC_Base_SYS-224, Gen_SWCS_HSW_uC_Base_SYS-266
 *
 * \Purpose
 *  Verify OS callback for idle implementation
 *  Verify that TaskIdle is not running on same core as TaskIdleP
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call "Os_Cbk_Idle" from each core
 *
 * \ExpectedResult
 *  Return value of Os_Cbk_Idle must be TRUE
 *  Function "sys_general_idleloop" must be called per core as often as number of idle loops are configured
 *  Function "sys_delayed_idleloop" must be called per core as often as number of idle loops are configured
 *  Function "sys_idleloop_request_rerun" must be called as often as number of idle loops are configured
 *  Local variable "idle" must be configured differently for each core
 */
SWTEST void TRBSYS_Idle(void)
{
  boolean ret;
  unsigned int coreID = RBSYS_CORE_ID_0;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    PRC_PTR* IdleCfgCore0, *IdleCfgCore1;
  #endif
  TRBSYS_setCoreID(coreID);
  TRBSYS_RunTaskStandalone(TaskInit);

  ret = Os_Cbk_Idle();
  SWT_EvalEx(ret, "Os_Cbk_Idle return must be TRUE");
  SWT_EvalEq(sys_general_idleloop_cnt[coreID], 1);
  SWT_EvalEq(sys_delayed_idleloop_cnt[coreID], 1);
  SWT_EvalEq(sys_idleloop_request_rerun_cnt, 1);


  #if (RBFS_MCORE == RBFS_MCORE_ON)
    IdleCfgCore0 = TRBSYS_IdleCfg;

    coreID = RBSYS_CORE_ID_1;

    TRBSYS_setCoreID(coreID);
    ret = Os_Cbk_Idle();
    SWT_EvalEx(ret, "Os_Cbk_Idle return must be TRUE");
    SWT_EvalEq(sys_general_idleloop_cnt[coreID], 1);
    SWT_EvalEq(sys_delayed_idleloop_cnt[coreID], 1);
    SWT_EvalEq(sys_idleloop_request_rerun_cnt, 2*1);

    IdleCfgCore1 = TRBSYS_IdleCfg;
    SWT_Eval(IdleCfgCore0 != NULL);
    SWT_Eval(IdleCfgCore1 != NULL);
    SWT_Eval(IdleCfgCore0 != IdleCfgCore1);
  #endif
}


/**
 * \Reference
 *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation of 500us task (if available), otherwise task activation of 1ms
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM04
 *
 * \ExpectedResult
 *  ISR counter must be incremented by 1
 *  Global lock must be called once (enter + exit)
 *  Next timer compare value must be dependent on corresponding cycle time (500us or 1ms)
 *  Corresponding task (500us or 1ms) must be activated
 *  Compare match bit must be reset to get new interrupt with next match (only on P1x)
 */
SWTEST void TRBSYS_ISRSTM04(void)
{
  uint32 cmp_ts = 500;      // based on sync timer
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1A = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP00 = cmp_ts;
  #endif

  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_1ms(), 0);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM04();

  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_1ms(), 1);

  SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
  SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
      SWT_EvalEq(STM0CMP1A, cmp_ts + (CYCLETIME_0p5ms*RBSYS_TIMERTICKS_PER_US));
      SWT_EvalEq(Task0p5ms->task, 1);
    #else
      SWT_EvalEq(STM0CMP1A, cmp_ts + (CYCLETIME_1ms*RBSYS_TIMERTICKS_PER_US));
      SWT_EvalEq(Task1ms->task, 1);
    #endif

    SWT_EvalEq(STM0STC, 0x10);
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
      SWT_EvalEq(TPTMPE0TPTM0UCMP00, cmp_ts + (CYCLETIME_0p5ms*RBSYS_TIMERTICKS_PER_US));
      SWT_EvalEq(Task0p5ms->task, 1);
    #else
      SWT_EvalEq(TPTMPE0TPTM0UCMP00, cmp_ts + (CYCLETIME_1ms*RBSYS_TIMERTICKS_PER_US));
      SWT_EvalEq(Task1ms->task, 1);
    #endif
  #endif
}


/**
 * \Reference
 *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation of 500us task (if available), otherwise task activation of 1ms
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM04 multiple times
 *
 * \ExpectedResult
 *  If 500us task is available:
 *    - 500us task must be activated
 *  else
 *    - 1ms task must be activated
 */
SWTEST void TRBSYS_ISRSTM04_TaskActivation(void)
{
  int i;
  TRBSYS_RunTaskStandalone(TaskInit);

  for (i = 0; i < 10; i++)
  {
    Os_Entry_ISRSTM04();

    #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
      SWT_EvalEq(Task0p5ms->task, i+1);
    #else
      SWT_EvalEq(Task1ms->task, i+1);
    #endif
  }
}

#if( RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON )
/**
 * \Reference
 *  RBSYS_ActivateFlexrayTask
 *
 * \Purpose
 *  Verify task counter increment when triggering FlexrayTask
 *  Verify
 *
 * \Sequence
 *  Call RBSYS_ActivateFlexrayTask
 *  Verify that Task
 *
 * \ExpectedResult
 *  see test comments
 */
SWTEST void TRBSYS_TaskFlexray_Activation(void)
{
  RBMESG_DefineMESGDef(RBMESG_TaskFlexrayCnt_u32);

  TRBSYS_setRealtimeTickCtr(15);

  RBSYS_ActivateFlexrayTask();

  RBMESG_RcvMESGDef(RBMESG_TaskFlexrayCnt_u32);
  /* Task has to be triggered once, counter shall be incremented once */
  SWT_EvalEq(TaskFlexray->task, 1);
  SWT_EvalEq(l_RBMESG_TaskFlexrayCnt_u32, 1);
  /* Task activation timestamp has to be set */
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskFlexray)].ts_activation, 15);
}
#endif

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_OFF)
  #if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_OFF)
    /**
     * \Reference
     *  Os_Entry_Task0p5ms
     *
     * \Purpose
     *  Os_Entry_Task0p5ms exists but is empty and is not called if RBFS_TPSWCapsule_OFF and RBFS_SysTask0p5ms_OFF.
     *  Non empty but still inactive case is tested by TRBSYS_TerminateTask whith RBFS_TPSWCapsule_SC3/SC4.
     *
     * \Sequence
     *  Run Task0p5ms
     *
     * \ExpectedResult
     *  MISUSE, nothing is expected
     */
    SWTEST void TRBSYS_Task0p5ms_NOT_ACTIVE_MISUSE(void)
    {
      TRBSYS_RunTaskStandalone(Task0p5ms);
      SWT_Eval(TRUE);
    }
  #endif

  #if (RBFS_MCORE ==  RBFS_MCORE_OFF)
    /**
     * \Reference
     *  Os_Entry_TaskInitP, Os_Entry_TaskBaseCtrlCycx2p
     *
     * \Purpose
     *  Os_Entry_TaskInitP and Os_Entry_TaskBaseCtrlCycx2p exist but are empty and are not called if RBFS_TPSWCapsule_OFF and RBFS_MCORE_OFF.
     *  Non empty but still inactive case is tested by TRBSYS_TerminateTask whith RBFS_TPSWCapsule_SC3/SC4.
     *
     * \Sequence
     *  Run TaskInitP and TaskBaseCtrlCycx2p
     *
     * \ExpectedResult
     *  MISUSE, nothing is expected
     */
    SWTEST void TRBSYS_MCoreTasks_NOT_ACTIVE_MISUSE(void)
    {
      TRBSYS_RunTaskStandalone(TaskInitP);
      TRBSYS_RunTaskStandalone(TaskBaseCtrlCycx2p);
      SWT_Eval(TRUE);
    }
  #endif

  #if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_OFF)
    /**
     * \Reference
     *  Os_Entry_TaskFlexray
     *
     * \Purpose
     *  Os_Entry_TaskFlexray exists but is empty and is not called if RBFS_TPSWCapsule_OFF and RBFS_SysFlxrTask_OFF.
     *  Non empty but still inactive case is tested by TRBSYS_TerminateTask whith RBFS_TPSWCapsule_SC3/SC4.
     *
     * \Sequence
     *  Run TaskFlexray
     *
     * \ExpectedResult
     *  MISUSE, nothing is expected
     */
    SWTEST void TRBSYS_TaskFlexray_NOT_ACTIVE_MISUSE(void)
    {
      TRBSYS_RunTaskStandalone(TaskFlexray);
      SWT_Eval(TRUE);
    }
  #endif
#endif

/**
 * \Reference
 *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation time stamp of 1ms and 500us task (if available)
 *
 * \Sequence
 *  Initialize compare value of corresponding timer channel
 *  Initialize timers (realtime > synctime)
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM04
 *
 * \ExpectedResult
 *  Corresponding activation time stamp must be the ideal activation (compare value) plus the difference between realtime and synctime
 */
SWTEST void TRBSYS_ISRSTM04_ActivationTimeStamp_1(void)
{
  uint32 cmp_ts = 700;      // current compare value based on sync timer
  uint32 delta_1st = 25;    // difference between ideal task activation and real activation
  uint32 delta_2nd = 30;    // difference between realtime and synctime

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1A = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP00 = cmp_ts;
  #endif

  // realtime > synctime
  TRBSYS_setSynctimeTickCtr(cmp_ts + delta_1st);
  TRBSYS_setRealtimeTickCtr(cmp_ts + delta_1st + delta_2nd);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM04();

  #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
    SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task0p5ms)].ts_activation, cmp_ts + delta_2nd);
  #endif
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task1ms)].ts_activation, cmp_ts + delta_2nd);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation time stamp of 500us task (if available), otherwise of 1ms
 *
 * \Sequence
 *  Initialize compare value of corresponding timer channel
 *  Initialize timers (realtime < synctime)
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM04
 *
 * \ExpectedResult
 *  Corresponding activation time stamp must be the ideal activation (compare value) minus the difference between realtime and synctime
 */
SWTEST void TRBSYS_ISRSTM04_ActivationTimeStamp_2(void)
{
  uint32 cmp_ts = 700;      // current compare value based on sync timer
  uint32 delta_1st = 25;    // difference between ideal task activation and real activation
  uint32 delta_2nd = 30;    // difference between realtime and synctime

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1A = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP00 = cmp_ts;
  #endif

  // realtime < synctime
  TRBSYS_setSynctimeTickCtr(cmp_ts + delta_1st);
  TRBSYS_setRealtimeTickCtr(cmp_ts + delta_1st - delta_2nd);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM04();

  #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
    SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task0p5ms)].ts_activation, cmp_ts - delta_2nd);
  #endif
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task1ms)].ts_activation, cmp_ts - delta_2nd);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation time stamp of 500us task (if available), otherwise of 1ms
 *
 * \Sequence
 *  Initialize compare value of corresponding timer channel
 *  Initialize timers (realtime equal synctime)
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM04
 *
 * \ExpectedResult
 *  Corresponding activation time stamp must be the ideal activation (compare value)
 */
SWTEST void TRBSYS_ISRSTM04_ActivationTimeStamp_3(void)
{
  uint32 cmp_ts = 700;      // current compare value based on sync timer
  uint32 delta_1st = 25;    // difference between ideal task activation and real activation

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1A = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP00 = cmp_ts;
  #endif

  // realtime == synctime
  TRBSYS_setSynctimeTickCtr(cmp_ts + delta_1st);
  TRBSYS_setRealtimeTickCtr(cmp_ts + delta_1st);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM04();

  #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
    SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task0p5ms)].ts_activation, cmp_ts);
  #endif
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(Task1ms)].ts_activation, cmp_ts);
}


#if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  /**
   * \Reference
   *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-252
   *
   * \Purpose
   *  Verify deadline monitoring of 1ms task
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call ISR Os_Entry_ISRSTM04 while 1ms task still is in state ready
   *
   * \ExpectedResult
   *  TaskOverRunError must be set
   *  Corresponding debug data 0 must point to 1ms task
   */
  SWTEST void TRBSYS_ISRSTM04_TaskOverRun_1ms_ready(void)
  {
    TRBSYS_SetTaskState(Task1ms, READY);

    TRBSYS_RunTaskStandalone(TaskInit);
    Os_Entry_ISRSTM04();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(Task1ms))));
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_Task1ms);
  }


  /**
   * \Reference
   *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-252
   *
   * \Purpose
   *  Verify deadline monitoring of 1ms task
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call ISR Os_Entry_ISRSTM04 while 1ms task still is in state running
   *
   * \ExpectedResult
   *  TaskOverRunError must be set
   *  Corresponding debug data 0 must point to 1ms task
   */
  SWTEST void TRBSYS_ISRSTM04_TaskOverRun_1ms_running(void)
  {
    TRBSYS_SetTaskState(Task1ms, RUNNING);

    TRBSYS_RunTaskStandalone(TaskInit);
    Os_Entry_ISRSTM04();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(Task1ms))));
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_Task1ms);
  }


  /**
   * \Reference
   *  Os_Entry_ISRSTM04, Gen_SWCS_HSW_uC_Base_SYS-252
   *
   * \Purpose
   *  Verify deadline monitoring of 1ms task
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call ISR Os_Entry_ISRSTM04 while 1ms task is in state suspended
   *
   * \ExpectedResult
   *  TaskOverRunError must not be set
   *  Corresponding debug data 0 must still zero
   */
  SWTEST void TRBSYS_ISRSTM04_TaskOverRun_1ms_suspended(void)
  {
    TRBSYS_SetTaskState(Task1ms, SUSPENDED);

    TRBSYS_RunTaskStandalone(TaskInit);
    Os_Entry_ISRSTM04();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), FALSE);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), 0);
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), 0);
  }
#endif


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-248
 *
 * \Purpose
 *  Verify task activation of 5ms task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05
 *
 * \ExpectedResult
 *  ISR counter must be incremented by 1
 *  Global lock must be called once (enter + exit)
 *  5ms task must be activated
 *  Next timer compare value must be dependent on corresponding cycle time (5ms)
 *  Compare match bit must be reset to get new interrupt with next match (only on P1x)
 */
SWTEST void TRBSYS_ISRSTM05(void)
{
  uint32 cmp_ts = 400;      // based on sync timer
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1B = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP01 = cmp_ts;
  #endif

  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_x1(), 0);
  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_x1(), 1);

  SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 1);
  SWT_EvalEq(TRBSYS_GlobLock.nest_cnt, 0);

  SWT_EvalEq(TaskBaseCtrlCycx1High->task, 1);

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    SWT_EvalEq(STM0CMP1B, cmp_ts + (CYCLETIME_x1*RBSYS_TIMERTICKS_PER_US));
    SWT_EvalEq(STM0STC, 0x20);
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SWT_EvalEq(TPTMPE0TPTM0UCMP01, cmp_ts + (CYCLETIME_x1*RBSYS_TIMERTICKS_PER_US));
  #endif
}



/**
 * \Reference
 *  TaskTPSWKillCore0, Gen_SWCS_HSW_uC_Base_SYS-237
 *
 * \Purpose
 *  Check task body for pseudo task on highest prio used for killing untrusted application on other core
 *
 * \Sequence
 *  Call task TaskTPSWKillCore0
 *
 * \ExpectedResult
 *  Only task body exists (call of terminate task still verified via testcase TRBSYS_TerminateTask)
 */
SWTEST void TRBSYS_TaskTPSWKillCore0(void)
{
  Os_Entry_TaskTPSWKillCore0();
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  TaskTPSWKillCore1, Gen_SWCS_HSW_uC_Base_SYS-237
 *
 * \Purpose
 *  Check task body for pseudo task on highest prio used for killing untrusted application on other core
 *
 * \Sequence
 *  Call task TaskTPSWKillCore1
 *
 * \ExpectedResult
 *  Only task body exists (call of terminate task still verified via testcase TRBSYS_TerminateTask)
 */
SWTEST void TRBSYS_TaskTPSWKillCore1(void)
{
  Os_Entry_TaskTPSWKillCore1();
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verify task activation time stamp of all tasks related on the BaseCtrlCycle
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05
 *
 * \ExpectedResult
 *  Corresponding activation time stamp must be the ideal activation (compare value) plus the difference between realtime and synctime
 */
SWTEST void TRBSYS_ISRSTM05_ActivationTimeStamp(void)
{
  uint32 cmp_ts = 300;      // current compare value based on sync timer
  uint32 delta_1st = 25;    // difference between ideal task activation and real activation
  uint32 delta_2nd = 30;    // difference between realtime and synctime

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0CMP1B = cmp_ts;
  #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    TPTMPE0TPTM0UCMP01 = cmp_ts;
  #endif

  TRBSYS_setSynctimeTickCtr(cmp_ts + delta_1st);
  TRBSYS_setRealtimeTickCtr(cmp_ts + delta_1st + delta_2nd);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx1High)].ts_activation, cmp_ts + delta_2nd);
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx1Low)].ts_activation, cmp_ts + delta_2nd);
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx2)].ts_activation, cmp_ts + delta_2nd);
#if (RBFS_MCORE == RBFS_MCORE_ON)
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx2p)].ts_activation, cmp_ts + delta_2nd);
#endif
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx4)].ts_activation, cmp_ts + delta_2nd);
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx8)].ts_activation, cmp_ts + delta_2nd);
  SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(TaskBaseCtrlCycx24)].ts_activation, cmp_ts + delta_2nd);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x1 low task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x1 low task still is in state ready
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x1 low task
 *  In case the ISR is called the 2nd time (next activation chain started for x1 low) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x1low_ready(void)
{
  TRBSYS_SetTaskState(TaskBaseCtrlCycx1Low, READY);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx1Low))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx1Low);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x1 low task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x1 low task still is in state running
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x1 low task
 *  In case the ISR is called the 2nd time (next activation chain started for x1 low) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x1low_running(void)
{
  TRBSYS_SetTaskState(TaskBaseCtrlCycx1Low, RUNNING);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx1Low))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx1Low);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x2 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x2 task still is in state ready
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x2 task
 *  In case the ISR is called the 3rd time (next activation chain started for x2) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x2_ready(void)
{
  TRBSYS_SetTaskState(TaskBaseCtrlCycx2, READY);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx2);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x2 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x2 task still is in state running
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x2 task
 *  In case the ISR is called the 3rd time (next activation chain started for x2) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x2_running(void)
{
  TRBSYS_SetTaskState(TaskBaseCtrlCycx2, RUNNING);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx2);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
   *
   * \Purpose
   *  Verify deadline monitoring of x2p task
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call ISR Os_Entry_ISRSTM05 while x2p task still is in state ready
   *
   * \ExpectedResult
   *  TaskOverRunError must be set
   *  Corresponding debug data 0 must point to x2p task
   *  In case the ISR is called the 3rd time (next activation chain started for x2p) the task overrun must be a 2nd time detected
   */
  SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x2p_ready(void)
  {
    TRBSYS_SetTaskState(TaskBaseCtrlCycx2p, READY);

    TRBSYS_RunTaskStandalone(TaskInit);
    Os_Entry_ISRSTM05();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2p))));
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx2p);

    Os_Entry_ISRSTM05();
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

    Os_Entry_ISRSTM05();
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
  }


  /**
   * \Reference
   *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
   *
   * \Purpose
   *  Verify deadline monitoring of x2p task
   *
   * \Sequence
   *  Call TaskInit to initialize process list
   *  Call ISR Os_Entry_ISRSTM05 while x2p task still is in state running
   *
   * \ExpectedResult
   *  TaskOverRunError must be set
   *  Corresponding debug data 0 must point to x2p task
   *  In case the ISR is called the 3rd time (next activation chain started for x2p) the task overrun must be a 2nd time detected
   */
  SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x2p_running(void)
  {
    TRBSYS_SetTaskState(TaskBaseCtrlCycx2p, RUNNING);

    TRBSYS_RunTaskStandalone(TaskInit);
    Os_Entry_ISRSTM05();

    SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
    SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx2p))));
    SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx2p);

    Os_Entry_ISRSTM05();
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

    Os_Entry_ISRSTM05();
    SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
  }
#endif


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x4 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x4 task still is in state ready
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x4 task
 *  In case the ISR is called the 5th time (next activation chain started for x4) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x4_ready(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx4, READY);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx4))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx4);

  for (i = 0; i < 3; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x4 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x4 task still is in state running
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x4 task
 *  In case the ISR is called the 5th time (next activation chain started for x4) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x4_running(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx4, RUNNING);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx4))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx4);

  for (i = 0; i < 3; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x8 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x8 task still is in state ready
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x8 task
 *  In case the ISR is called the 9th time (next activation chain started for x8) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x8_ready(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx8, READY);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx8))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx8);

  for (i = 0; i < 7; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);

}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x8 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x8 task still is in state running
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x8 task
 *  In case the ISR is called the 9th time (next activation chain started for x8) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x8_running(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx8, RUNNING);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx8))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx8);

  for (i = 0; i < 7; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);

}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x24 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x24 task still is in state ready
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x24 task
 *  In case the ISR is called the 25th (next activation chain started for x24) time the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x24_ready(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx24, READY);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx24))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx24);

  for (i = 0; i < 23; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSTM05, Gen_SWCS_HSW_uC_Base_SYS-252
 *
 * \Purpose
 *  Verify deadline monitoring of x24 task
 *
 * \Sequence
 *  Call TaskInit to initialize process list
 *  Call ISR Os_Entry_ISRSTM05 while x24 task still is in state running
 *
 * \ExpectedResult
 *  TaskOverRunError must be set
 *  Corresponding debug data 0 must point to x24 task
 *  In case the ISR is called the 25th time (next activation chain started for x24) the task overrun must be a 2nd time detected
 */
SWTEST void TRBSYS_ISRSTM05_TaskOverRun_x24_running(void)
{
  int i = 0;
  TRBSYS_SetTaskState(TaskBaseCtrlCycx24, RUNNING);

  TRBSYS_RunTaskStandalone(TaskInit);
  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_TaskOverRun), TRUE);
  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_TaskOverRun), (1 << (OS_TASKTYPE_TO_INDEX(TaskBaseCtrlCycx24))));
  SWT_EvalEq(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_TaskOverRun), (uint32) &Os_Entry_TaskBaseCtrlCycx24);

  for (i = 0; i < 23; i++)
  {
    Os_Entry_ISRSTM05();
  }

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);

  Os_Entry_ISRSTM05();

  SWT_EvalEq(DemStub_GetNumOfReportFailedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 2);
}


/**
 * \Reference
 *  Os_Entry_ISRSWINT0, Gen_SWCS_HSW_uC_Base_SYS-276
 *
 * \Purpose
 *  Verify software interrupt 0 used for BERT
 *
 * \Sequence
 *  Call Os_Entry_ISRSWINT0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRSWINT0(void)
{
  Os_Entry_ISRSWINT0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_SWINT0(), 1);
}


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
/**
 * \Reference
 *  Os_Entry_ISRMTTCANI0, Gen_SWCS_HSW_uC_Base_SYS-279
 *
 * \Purpose
 *  Verify MTTCANI0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRMTTCANI0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRMTTCANI0(void)
{
  Os_Entry_ISRMTTCANI0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_MTTCANI0(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRMCAN0I0, Gen_SWCS_HSW_uC_Base_SYS-279
 *
 * \Purpose
 *  Verify MCAN0I0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRMCAN0I0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRMCAN0I0(void)
{
  Os_Entry_ISRMCAN0I0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_MCAN0I0(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRMCAN1I0, Gen_SWCS_HSW_uC_Base_SYS-279
 *
 * \Purpose
 *  Verify MCAN1I0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRMCAN1I0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRMCAN1I0(void)
{
  Os_Entry_ISRMCAN1I0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_MCAN1I0(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRMCAN2I0, Gen_SWCS_HSW_uC_Base_SYS-279
 *
 * \Purpose
 *  Verify MCAN2I0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRMCAN2I0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRMCAN2I0(void)
{
  Os_Entry_ISRMCAN2I0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_MCAN2I0(), 1);
}

#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

/**
 * \Reference
 *  Gen_SWCS_HSW_uC_Base_SYS-279
 *
 * \Purpose
 *  Verify RS-CAN ISRs
 *
 * \Sequence
 *  Call ISRs
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRCANs(void)
{
  Os_Entry_ISRCAN0REC();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN0REC(), 1);
  Os_Entry_ISRCAN0TRX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN0TRX(), 1);
  Os_Entry_ISRCAN1REC();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN1REC(), 1);
  Os_Entry_ISRCAN1TRX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN1TRX(), 1);
  Os_Entry_ISRCAN2REC();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN2REC(), 1);
  Os_Entry_ISRCAN2TRX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN2TRX(), 1);
  Os_Entry_ISRCAN6REC();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN6REC(), 1);
  Os_Entry_ISRCAN6TRX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN6TRX(), 1);
  Os_Entry_ISRCAN8REC();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN8REC(), 1);
  Os_Entry_ISRCAN8TRX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_CAN8TRX(), 1);
}
#endif


/**
 * \Reference
 *  Os_Entry_ISRFLX0LINE0, Gen_SWCS_HSW_uC_Base_SYS-280
 *
 * \Purpose
 *  Verify FLX0LINE0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRFLX0LINE0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRFLX0LINE0(void)
{
  Os_Entry_ISRFLX0LINE0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_FLX0LINE0(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRFLX1LINE0, Gen_SWCS_HSW_uC_Base_SYS-280
 *
 * \Purpose
 *  Verify FLX1LINE0 ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRFLX1LINE0
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRFLX1LINE0(void)
{
  Os_Entry_ISRFLX1LINE0();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_FLX1LINE0(), 1);
}


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
/**
 * \Reference
 *  Os_Entry_ISRRLIN30RX, Gen_SWCS_HSW_uC_Base_SYS-300
 *
 * \Purpose
 *  Verify RLIN3_0 interrupt 0 receive ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRRLIN30RX
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRRLIN30RX(void)
{
  Os_Entry_ISRRLIN30RX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_RLIN30RX(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRRLIN30STATUS, Gen_SWCS_HSW_uC_Base_SYS-300
 *
 * \Purpose
 *  Verify RLIN3_0 interrupt 0 status ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRRLIN30STATUS
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRRLIN30STATUS(void)
{
  Os_Entry_ISRRLIN30STATUS();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_RLIN30STATUS(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRRLIN31RX, Gen_SWCS_HSW_uC_Base_SYS-300
 *
 * \Purpose
 *  Verify RLIN3_1 interrupt 0 receive ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRRLIN31RX
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRRLIN31RX(void)
{
  Os_Entry_ISRRLIN31RX();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_RLIN31RX(), 1);
}


/**
 * \Reference
 *  Os_Entry_ISRRLIN31STATUS, Gen_SWCS_HSW_uC_Base_SYS-300
 *
 * \Purpose
 *  Verify RLIN3_1 interrupt 0 status ISR
 *
 * \Sequence
 *  Call Os_Entry_ISRRLIN31STATUS
 *
 * \ExpectedResult
 *  Corresponding ISR counter must be incremented
 */
SWTEST void TRBSYS_ISRRLIN31STATUS(void)
{
  Os_Entry_ISRRLIN31STATUS();
  SWT_EvalEq(GetPrivate_RBSYS_ISRcnt_RLIN31STATUS(), 1);
}
#endif


/**
 * \Reference
 *  Os_Cbk_TaskStart, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verify OS task start callback
 *
 * \Sequence
 *  Call for each configured task Os_Cbk_TaskStart
 *
 * \ExpectedResult
 *  Task start timestamp must be set for the corresponding task
 *  RBSYS_RuntimeMeasure_TaskStart for the corresponding task must be called
 */
SWTEST void TRBSYS_Os_Cbk_TaskStart(void)
{
  int i;

  for (i = 0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    int real_time = 100 + i;
    TRBSYS_setRealtimeTickCtr(real_time);

    Os_Cbk_TaskStart(task);

    SWT_EvalEq(TRBSYS_GetTaskStart_Counter(), i+1);
    SWT_EvalEq((uint32)TRBSYS_get_current_task(), (uint32)task);
    SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].ts_start, real_time);
  }
}


/**
 * \Reference
 *  Os_Cbk_TaskEnd, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verify OS task end callback
 *
 * \Sequence
 *  Call for each configured task Os_Cbk_TaskEnd
 *  Disable task chaining for VMPS
 *
 * \ExpectedResult
 *  Task end timestamp must be set for the corresponding task
 *  RBSYS_RuntimeMeasure_TaskEnd for the corresponding task must be called
 */
SWTEST void TRBSYS_Os_Cbk_TaskEnd(void)
{
  int i;

  for (i = 0; i<OS_NUM_TASKS; i++)
  {
    TaskType task = Os_const_tasks[i];
    int real_time = 100 + i;
    TRBSYS_setRealtimeTickCtr(real_time);

    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
      // disable task chaining (that Os_Cbk_TaskEnd activates other tasks is already tested by other test cases)
      TRBSYS_TaskChainingEnabled = FALSE;
      TRBSYS_TaskActivationDoneOnce = TRUE;
    #endif

    Os_Cbk_TaskEnd(task);

    SWT_EvalEq(TRBSYS_GetTaskEnd_Counter(), i+1);
    SWT_EvalEq((uint32)TRBSYS_get_current_task(), (uint32)task);
    SWT_EvalEq(RBSYS_taskstats_tasks[RBSYS_GetTaskIndex(task)].ts_end, real_time);
  }
}


/**
 * \Reference
 *  Os_Cbk_ISRStart, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verify OS ISR start callback
 *
 * \Sequence
 *  Call for each configured ISR Os_Cbk_ISRStart
 *
 * \ExpectedResult
 *  ISR start timestamp must be set for the corresponding ISR
 *  RBSYS_RuntimeMeasure_IsrStart for the corresponding ISR must be called
 */
SWTEST void TRBSYS_Os_Cbk_ISRStart(void)
{
  int i;

  for (i = 0; i<OS_NUM_ISRS; i++)
  {
    ISRType isr = &Os_const_isrs[i];
    int real_time = 100 + i;
    TRBSYS_setRealtimeTickCtr(real_time);

    Os_Cbk_ISRStart(isr);

    SWT_EvalEq(TRBSYS_GetIsrStart_Counter(), i+1);
    SWT_EvalEq((uint32)TRBSYS_get_current_isr(), (uint32)isr);
    SWT_EvalEq(RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)].ts_start, real_time);
  }
}


/**
 * \Reference
 *  Os_Cbk_ISREnd, Gen_SWCS_HSW_uC_Base_SYS-221
 *
 * \Purpose
 *  Verify OS ISR end callback
 *
 * \Sequence
 *  Call for each configured ISR Os_Cbk_ISREnd
 *
 * \ExpectedResult
 *  ISR end timestamp must be set for the corresponding ISR
 *  RBSYS_RuntimeMeasure_IsrEnd for the corresponding ISR must be called
 */
SWTEST void TRBSYS_Os_Cbk_ISREnd(void)
{
  int i;

  for (i = 0; i<OS_NUM_ISRS; i++)
  {
    ISRType isr = &Os_const_isrs[i];
    int real_time = 200 + i;
    TRBSYS_setRealtimeTickCtr(real_time);

    Os_Cbk_ISREnd(isr);

    SWT_EvalEq(TRBSYS_GetIsrEnd_Counter(), i+1);
    SWT_EvalEq((uint32)TRBSYS_get_current_isr(), (uint32)isr);
    SWT_EvalEq(RBSYS_taskstats_isrs[OS_ISRTYPE_TO_INDEX(isr)].ts_end, real_time);
  }
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  Os_Cbk_CrosscoreISRStart, Gen_SWCS_HSW_uC_Base_SYS-221
   *
   * \Purpose
   *  Verify OS crosscore ISR start callback
   *
   * \Sequence
   *  Call for each core Os_Cbk_CrosscoreISRStart
   *
   * \ExpectedResult
   *  RBSYS_RuntimeMeasure_CrossCoreIntStart must be called	every time
   */
  SWTEST void TRBSYS_Os_Cbk_CrosscoreISRStart(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      Os_Cbk_CrosscoreISRStart(i);
      SWT_EvalEq(TRBSYS_GetCrossCoreIntStart_Counter(), i+1);
    }
  }


  /**
   * \Reference
   *  Os_Cbk_CrosscoreISREnd, Gen_SWCS_HSW_uC_Base_SYS-221
   *
   * \Purpose
   *  Verify OS crosscore ISR end callback
   *
   * \Sequence
   *  Call for each core Os_Cbk_CrosscoreISREnd
   *
   * \ExpectedResult
   *  RBSYS_RuntimeMeasure_CrossCoreIntEnd must be called	every time
   */
  SWTEST void TRBSYS_Os_Cbk_CrosscoreISREnd(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      Os_Cbk_CrosscoreISREnd(i);
      SWT_EvalEq(TRBSYS_GetCrossCoreIntEnd_Counter(), i+1);
    }
  }
#endif


/**
 * \Reference
 *  Os_CAT1_ISR_EXCHVTRAP
 *
 * \Purpose
 *  Verify OS Category 1 ISR for "hypervisor trap (HVTRAP)"
 *
 * \Sequence
 *  Call Os_CAT1_ISR_EXCHVTRAP
 *
 * \ExpectedResult
 *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
 */
SWTEST void TRBSYS_EXCHVTRAP(void)
{
  Os_CAT1_ISR_EXCHVTRAP();
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  Os_CAT1_ISR_EXCFETRAP
 *
 * \Purpose
 *  Verify OS Category 1 ISR for "FE-level software exception"
 *
 * \Sequence
 *  Call Os_CAT1_ISR_EXCFETRAP
 *
 * \ExpectedResult
 *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
 */
SWTEST void TRBSYS_EXCFETRAP(void)
{
  Os_CAT1_ISR_EXCFETRAP();
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  Os_CAT1_ISR_EXCUCPOP
 *
 * \Purpose
 *  Verify OS Category 1 ISR for "co-processor unusable exception"
 *
 * \Sequence
 *  Call Os_CAT1_ISR_EXCUCPOP
 *
 * \ExpectedResult
 *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
 */
SWTEST void TRBSYS_EXCUCPOP(void)
{
  Os_CAT1_ISR_EXCUCPOP();
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  Os_CAT1_ISR_EXCFENMI
 *
 * \Purpose
 *  Verify OS Category 1 ISR for "FE-level non maskable interrupt"
 *
 * \Sequence
 *  Call Os_CAT1_ISR_EXCFENMI
 *
 * \ExpectedResult
 *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
 */
SWTEST void TRBSYS_EXCFENMI(void)
{
  Os_CAT1_ISR_EXCFENMI();
  SWT_Eval(TRUE);
}

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_OFF)
  /**
   * \Reference
   *  Os_CAT1_ISR_EXCPIE
   *
   * \Purpose
   *  Verify OS Category 1 ISR for "Privileged instruction exception"
   *
   * \Sequence
   *  Call Os_CAT1_ISR_EXCPIE
   *
   * \ExpectedResult
   *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
   */
  SWTEST void TRBSYS_EXCPIE(void)
  {
    Os_CAT1_ISR_EXCPIE();
    SWT_Eval(TRUE);
  }


  /**
   * \Reference
   *  Os_CAT1_ISR_EXCMDP
   *
   * \Purpose
   *  Verify OS Category 1 ISR for "Memory protection exception"
   *
   * \Sequence
   *  Call Os_CAT1_ISR_EXCMDP
   *
   * \ExpectedResult
   *  Compl. content is merged in via MergeProc => therefore no real test on UT level possible (but still required for UT coverage)
   */
  SWTEST void TRBSYS_EXCMDP(void)
  {
    Os_CAT1_ISR_EXCMDP();
    SWT_EvalEq(TRBSYS_HandleSupervisorMpuViolation_CallCnt, 1);
  }
#endif



#if (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF)
   /**
   * \Reference
   *  Os_CAT1_ISR_ISRSTM06_SC4core0
   *
   * \Purpose
   *  Verify OS Category 1 ISR for "Timing protection (core 0)"
   *
   * \Sequence
   *  Call Os_CAT1_ISR_ISRSTM06_SC4core0
   *
   * \ExpectedResult
   *  If SC4 build: RBTPSW_TimingHandler is called
   *  else: InvalidInt was reported
   */
  SWTEST void TRBSYS_ISRSTM06_SC4core0(void)
  {
    Os_CAT1_ISR_ISRSTM06_SC4core0();
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
      SWT_EvalEq(TRBTPSW_TimingHandler_cnt, 1);
      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    #else
      SWT_EvalEq(TRBTPSW_TimingHandler_cnt, 0);
      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt);
    #endif
  }

   /**
   * \Reference
   *  Os_CAT1_ISR_ISRSTM07_SC4core1
   *
   * \Purpose
   *  Verify OS Category 1 ISR for "Timing protection (core 1)"
   *
   * \Sequence
   *  Call Os_CAT1_ISR_ISRSTM07_SC4core1
   *
   * \ExpectedResult
   *  If SC4 build: RBTPSW_TimingHandler is called
   *  else: InvalidInt was reported
   */
  SWTEST void TRBSYS_ISRSTM07_SC4core1(void)
  {
    Os_CAT1_ISR_ISRSTM07_SC4core1();
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
      SWT_EvalEq(TRBTPSW_TimingHandler_cnt, 1);
      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE);
    #else
      SWT_EvalEq(TRBTPSW_TimingHandler_cnt, 0);
      SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
      SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt);
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
