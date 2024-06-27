#ifndef OS_CFG_H__
#define OS_CFG_H__

#include "RBSYS_Config.h"
#include "RBSYSStub_Tasks.h" ///< c_Task...

#include "Os.h" ///< for Os_TaskType

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  #define OS_NUM_TASKS    (18)
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define OS_NUM_TASKS    (19)
#else
  #define OS_NUM_TASKS    (14)
#endif
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    #define OS_NUM_ISRS     (14)
  #else
    #define OS_NUM_ISRS     (13)
  #endif
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #define OS_NUM_ISRS     (15)
#endif

#define OS_RTE_RESOURCE_CORE0 (&OSStub_Core[0U])
#define OS_RTE_RESOURCE_CORE1 (&OSStub_Core[1U])

#if (RBFS_MCORE == RBFS_MCORE_ON)
  // real OS only defines core IDs in multi core configs, for single core configs it is stubbed in RBSYS
  #define OS_CORE_FOR_ISRSWINT0 OS_CORE_ID_0
#endif

/// change to Os_TaskType references for Task.
/// In the past: HSWSim-OSStub was incorrectly treating the ProcessLists as
///              Task-References.
/// HINT: The old c_Taskx1h etc. were the "process lists". this was incorrect.
///

/// need to be address of actual const variable, otherwise
/// const pointer const is no const reference for compiler.
#define osConstRefTask(task)      (&(ost_##task##_task_var))
#define extConstTaskVarDef(task)  extern const Os_TaskType ost_##task##_task_var;

extConstTaskVarDef( Taskx1h     )
extConstTaskVarDef( Taskx1l     )
extConstTaskVarDef( Taskx2      )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  extConstTaskVarDef( Taskx2p     )
#endif
extConstTaskVarDef( Taskx4      )
extConstTaskVarDef( Taskx8      )
extConstTaskVarDef( Taskx24     )
extConstTaskVarDef( TaskIdle    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  extConstTaskVarDef( TaskIdleP   )
#endif
extConstTaskVarDef( TaskInit    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  extConstTaskVarDef( TaskInitP    )
#endif
//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  extConstTaskVarDef( Task0p5ms   )
//#endif
extConstTaskVarDef( Task1ms     ) /// Os_TaskType reference
extConstTaskVarDef( FlexrayTask )

extConstTaskVarDef( PrePlantCheck )
extConstTaskVarDef( PreReprogCheck)

extConstTaskVarDef( TaskInitBaseOS  )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  extConstTaskVarDef( TaskInitPBaseOS )
#endif
#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  extConstTaskVarDef( Task0p5msBaseOS )
#endif
extConstTaskVarDef( Task1msBaseOS   )
extConstTaskVarDef( Taskx1hBaseOS   )
extConstTaskVarDef( Taskx1lBaseOS   )
extConstTaskVarDef( Taskx2BaseOS    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  extConstTaskVarDef( Taskx2pBaseOS   )
#endif
extConstTaskVarDef( Taskx4BaseOS    )
extConstTaskVarDef( Taskx8BaseOS    )
extConstTaskVarDef( Taskx24BaseOS   )

/// vmps
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  extConstTaskVarDef( TaskEventExtPrio1 )
  extConstTaskVarDef( TaskEventExtPrio2 )
  extConstTaskVarDef( TaskBaseCtrlCycx4pLow )
  extConstTaskVarDef( TaskBaseCtrlCycx200Background )
#endif

/// dummy for unused stuff.
extConstTaskVarDef( TaskDummy )

/// tasks not defined/used yet.
#define TaskTPSWKillCore0             osConstRefTask( TaskDummy )
#define TaskTPSWKillCore1             osConstRefTask( TaskDummy )

/** Task Stubs - stub Dyn.c definitions and OSStub.c definitions
    Reason: Make SYSStub more independent from changing RBSYS_Config.h. */
#define TaskBaseCtrlCycx1High         osConstRefTask( Taskx1h     )
#define TaskBaseCtrlCycx1Low          osConstRefTask( Taskx1l     )
#define TaskBaseCtrlCycx2             osConstRefTask( Taskx2      )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  #define TaskBaseCtrlCycx2p            osConstRefTask( Taskx2p     )
#endif
#define TaskBaseCtrlCycx4             osConstRefTask( Taskx4      )
#define TaskBaseCtrlCycx8             osConstRefTask( Taskx8      )
#define TaskBaseCtrlCycx24            osConstRefTask( Taskx24     )
#define TaskIdle                      osConstRefTask( TaskIdle    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  #define TaskIdleP                     osConstRefTask( TaskIdleP   )
#endif
#define TaskInit                      osConstRefTask( TaskInit    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  #define TaskInitP                     osConstRefTask( TaskInitP   )
#endif
//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  #define Task0p5ms                     osConstRefTask( Task0p5ms   )
//#endif
#define Task1ms                       osConstRefTask( Task1ms     ) /// Os_TaskType reference
#define TaskFlexray                   osConstRefTask( FlexrayTask )

#define PrePlantCheck                 osConstRefTask( PrePlantCheck )
#define PreReprogCheck                osConstRefTask( PreReprogCheck)

#define TaskInitBaseOS                osConstRefTask( TaskInitBaseOS  )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  #define TaskInitPBaseOS               osConstRefTask( TaskInitPBaseOS )
#endif
#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  #define Task0p5ms_BaseOS              osConstRefTask( Task0p5msBaseOS )
#endif
#define Task1ms_BaseOS                osConstRefTask( Task1msBaseOS   )
#define TaskBaseCtrlCycx1High_BaseOS  osConstRefTask( Taskx1hBaseOS   )
#define TaskBaseCtrlCycx1Low_BaseOS   osConstRefTask( Taskx1lBaseOS   )
#define TaskBaseCtrlCycx2_BaseOS      osConstRefTask( Taskx2BaseOS    )
#if(RBFS_MCORE == RBFS_MCORE_ON)
  #define TaskBaseCtrlCycx2p_BaseOS     osConstRefTask( Taskx2pBaseOS   )
#endif
#define TaskBaseCtrlCycx4_BaseOS      osConstRefTask( Taskx4BaseOS    )
#define TaskBaseCtrlCycx8_BaseOS      osConstRefTask( Taskx8BaseOS    )
#define TaskBaseCtrlCycx24_BaseOS     osConstRefTask( Taskx24BaseOS   )

//vmps
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  /// ??? Double definition failure in VMPS-Builds -> disabled
  /// R.Flechsig 20-oct-2022
  // #define TaskEventCtrlExtPrio1         osConstRefTask( TaskEventExtPrio1 )
  // #define TaskEventCtrlExtPrio2         osConstRefTask( TaskEventExtPrio2 )
  #define TaskEventCtrlExtPrio1         osConstRefTask( TaskBaseCtrlCycx4pLow )
  #define TaskEventCtrlExtPrio2         osConstRefTask( TaskBaseCtrlCycx200Background )
#endif

#endif ///< mig
