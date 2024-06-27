
#include "RBSYSStub_EntryPoint.h" // interface definitions

#include "RBSYS_PlantStartupCtrl.h"

#include "OSStub_RBSYS_directed.h" ///< ossim_priv_500usec_cnt

/* messages for startup flow and OS mode decision */
RBMESG_DefineMESG(RBMESG_RBSYSPlantModeRequest);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSPlantModeRequest*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/
RBMESG_DefineMESG(RBMESG_RBSYSBaseOSRequestbySW_u32);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/
RBMESG_DefineMESG(RBMESG_RBSYSBaseOSbySW);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSbySW*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/
RBMESG_DefineMESG(RBMESG_RBSYSBaseOSActive);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSBaseOSActive*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/
RBMESG_DefineMESG(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/


uint32 SYSSim_TickCtr = 0; // used in RBSYS_SystemTimer.h

uint32 RBSYSStub_GetTicks(void)
{
  return SYSSim_TickCtr;
}

#if (RBFS_TaskSync == RBFS_TaskSync_ON)
  #include "RBSYS_TimerOsConfig.h"
  sint32 RBSYS_STMControlTicks(sint32 delta_ticks)
  {
    // currently SyncTimer Adaption functionality is not required in Sim
    return 0;
  }
#endif


void RBSYSStub_StartupPreOSStart(void)
{
  // TODO: InitPhase not yet available.

  OSSim_StartOS(OSDEFAULTAPPMODE);
}

uint32 RBSYSStub_GetTickDeltaAsUsec(uint32 delta)
{
  return delta / RBSYS_TIMERTICKS_PER_US;
}

uint32 RBSYSStub_GetMS(void)
{
  return RBMESG_RBMESG_Task1msCnt_u32;
}

uint32 RBSYSStub_GetUS(void)
{
  #if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
    return RBMESG_RBMESG_Task0p5msCnt_u32 * 500;
  #else
    return ossim_priv_500usec_cnt * 500;
  #endif
}

uint32* RBSYSStub_Get500usecCnt_ref(void)
{
  #if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
    return &RBMESG_RBMESG_Task0p5msCnt_u32;
  #else
    return &ossim_priv_500usec_cnt;
  #endif
}


#include "OSStub_Internal.h"

uint32* RBSYS_getSynctimeTickCtrStub(void)
{
  OSSim_PseudoTickCounter_PseudoIncrement();

  SYSSim_TickCtr = OSSim_PseudoTickCounter_GetTicks();

  return &SYSSim_TickCtr;  // pointer needed as APPLIF dereferences RBSYS_SystemTimerSynctimeCnt

  #if 0
  // just cut everything bigger than uint32
  uint32 hw_ticks = (uint32) ((uint64)RBMESG_RBMESG_Task0p5msCnt_u32 * 500 * RBSYS_TIMERTICKS_PER_US);

  // just simulate in that way, that each call is 1us difference
  SYSSim_TickCtr += RBSYS_TIMERTICKS_PER_US;

  // only if hwtime is even progressed further we should pull the time
  // up to new base.
  // problem might appear if function is called more than 500 times within a single
  // 500usec-Task. (don't know any solution: reducing increment won't solve issue 100%)
  if( SYSSim_TickCtr < hw_ticks )
  {
    // ensure it is not just an overflow
    uint32 hw_tick_next = hw_ticks + 500 * RBSYS_TIMERTICKS_PER_US;

    if( hw_tick_next > hw_ticks )//< no overflow
      SYSSim_TickCtr = hw_ticks;
  }

  return SYSSim_TickCtr;
  #if 0
    return (STM0CNT1);
  #endif

  #endif
}



#include "Statistics/RBSYS_TaskStats.h"

RBSYS_TaskStatsTASK_t RBSYS_taskstats_tasks[OS_NUM_TASKS];

/// Flechsig: hacky include required, because TPSW-API-Macros
///       finally result in "src intern header inline functions".
#include "../../src/RBSYS_LocksImplIntern.h"

static RBSYS_coreintlock_t RBSYS_coreintlock_core0;
#if (RBFS_MCORE == RBFS_MCORE_ON)
static RBSYS_coreintlock_t RBSYS_coreintlock_core1;
#endif

RBSYS_coreintlock_t* const RBSYS_coreintlockinfo[RB_NUM_CORES] = {
          &RBSYS_coreintlock_core0
     #if (RBFS_MCORE == RBFS_MCORE_ON)
        , &RBSYS_coreintlock_core1
     #endif
};

#include "RBSYS_StartupTimingExtern.h"

uint32 RBSYS_StartupTimeStampInMicroSecs(RBSYS_StartupTimestamps_t phase)
{
  return 42;///< just any value
}

#include "RBTPSW_TPSWCapsule_Priv.h" ///< RBTPSW_Context_t

#if (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF)

#include "RBTPSW_TPSWCapsule.h" ///< realize

/// @todo: Perhaps makes sense to move TPSW stubs to different c-file.
void RBTPSW_EnterLock(const lockstr_t* lock){}
void RBTPSW_ExitLock(const lockstr_t* lock) {}


RBTPSW_Context_t RBTPSW_Context[OS_NUM_CORES];

volatile uint32 RBTPSW_DummyTrusted;


#if(RBFS_MCORE == RBFS_MCORE_ON)
    volatile lockstr_t RBSYS_common_lock;
#endif

void RBTPSW_FillSwAbortDebugInfo(RBTPSW_App_t* app,
                                  uint32 userinfo,
                                  rbtpsw_corefnptr_t corefn,
                                  CoreIdType CoreId)
{
  /// nothing yet.
}

uint32 RBTPSW_IntLockChecks(const rbtpsw_fncall_context_t *l_context,
                            CoreIdType CoreId,
                            rbtpsw_cpuMode_t PrevMode)
{
  /// nothing yet.
  return 0;
}

/*******************************************************************
 RBTPSW_STD_TRUSTED_APP: Standard trusted application (public).
********************************************************************/
RBTPSW_TRUSTED_APPLICATION_CONFIG(RBTPSW_STD_TRUSTED_APP)



/*******************************************************************
 RBTPSW_STD_UNTRUSTED_APP: Standard untrusted application (private).
 Used for cross core kill mechanism.
********************************************************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(RBTPSW_STD_UNTRUSTED_APP)

RBTPSW_DEFINE_MPUTABLE(RBTPSW_STD_UNTRUSTED_APP) = {
    RBTPSW_MPUCONFIG_ENDMARKER // no memory required
};

RBTPSW_DEFINE_LOCKTABLE(RBTPSW_STD_UNTRUSTED_APP, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER // no locks required
};

#endif ///< tpsw on

/// just include to detect any compilation error directly within stub header.
#include "RBSYS_BBFSW_StartupServices.h"

volatile RBSYS_BURAM_BB_FSW_INTERFACE_t RBSYS_BURAM_BB_FSW_INTERFACE;

#include "RBSYS_OSServices.h"

#if 0

#define RBSYSSTUB_TASK_TYPE(task_var, task_id)  \
  \
  static const Os_TaskType rbsysstub_##task_var = {.id = (task_id)};\
         const RBSYS_TaskType task_var = &rbsysstub_##task_var;

RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskInit             , 1)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskInitP            , 2)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_Task0p5ms            , 3)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_Task1ms              , 4)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx1High, 5)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskFlexray          , 6)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx1Low , 7)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx2    , 8)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx2p   , 9)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx4    , 10)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx8    , 11)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_TaskBaseCtrlCycx24   , 12)
RBSYSSTUB_TASK_TYPE(RBSYS_TaskType_Invalid              , 0)

#endif


/// new with HSM (RBSYS_GuardConfig.h)

#include "RBSYS_GuardConfig.h" ///< realize


/// Os.h stubs ********************************************************** OS.h *
/// Os.h stubs ********************************************************** OS.h *
/// Os.h stubs ********************************************************** OS.h *
FUNC(StatusType, OS_CODE) Os_GetTaskState(TaskType TaskID,
                                          TaskStateRefType State) /* [$UKS 89] */
{
  *State = RUNNING;
  return E_OK;
}
