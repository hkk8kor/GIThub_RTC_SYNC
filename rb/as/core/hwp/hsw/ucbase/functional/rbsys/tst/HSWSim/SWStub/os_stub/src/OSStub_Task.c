
#include "Os.h" ///< realize

#include "OSStub_Task.h"

#include "RBTexec_Config.h" ///< RBFS_TexecUsedIn now moved in default case
///< to here.

#if( RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim )
  #include "HwModel_DebugLogging.h" ///< for hwm_warning
#endif

OSSim_TaskBorderStopper TaskBorderStopper;

/// dummies ... not used by sim-OS.
#define STUB_TASK_DEFINITION(name) \
  static void Os_Entry_##name(void){}\
  \
  const Os_TaskType name##_task_var = {\
      .id=(unsigned int)(&Os_Entry_##name),\
      .sim_type=0xDEADBEEFu,\
      .task_func = &Os_Entry_##name\
      };\
  const Os_TaskType* const name = &name##_task_var

#define STUB_TREF( name )\
        &name##_task_var

STUB_TASK_DEFINITION( ost_Taskx1h    );
STUB_TASK_DEFINITION( ost_Taskx1l    );
STUB_TASK_DEFINITION( ost_Taskx2     );
#if( RBFS_MCORE == RBFS_MCORE_ON )
  STUB_TASK_DEFINITION( ost_Taskx2p    );
#endif
STUB_TASK_DEFINITION( ost_Taskx4     );
STUB_TASK_DEFINITION( ost_Taskx8     );
STUB_TASK_DEFINITION( ost_Taskx24    );
STUB_TASK_DEFINITION( ost_TaskIdle   );
#if( RBFS_MCORE == RBFS_MCORE_ON )
  STUB_TASK_DEFINITION( ost_TaskIdleP   );
#endif
STUB_TASK_DEFINITION( ost_TaskInit   );
#if( RBFS_MCORE == RBFS_MCORE_ON )
  STUB_TASK_DEFINITION( ost_TaskInitP   );
#endif
//#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  STUB_TASK_DEFINITION( ost_Task0p5ms  );
//#endif
STUB_TASK_DEFINITION( ost_Task1ms    );
#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  STUB_TASK_DEFINITION( ost_FlexrayTask);
#endif

STUB_TASK_DEFINITION( ost_PrePlantCheck  );
STUB_TASK_DEFINITION( ost_PreReprogCheck );

STUB_TASK_DEFINITION( ost_TaskInitBaseOS );
#if( RBFS_MCORE == RBFS_MCORE_ON )
  STUB_TASK_DEFINITION( ost_TaskInitPBaseOS );
#endif
#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  STUB_TASK_DEFINITION( ost_Task0p5msBaseOS);
#endif
STUB_TASK_DEFINITION( ost_Task1msBaseOS  );
STUB_TASK_DEFINITION( ost_Taskx1hBaseOS  );
STUB_TASK_DEFINITION( ost_Taskx1lBaseOS  );
STUB_TASK_DEFINITION( ost_Taskx2BaseOS   );
#if( RBFS_MCORE == RBFS_MCORE_ON )
  STUB_TASK_DEFINITION( ost_Taskx2pBaseOS  );
#endif
STUB_TASK_DEFINITION( ost_Taskx4BaseOS   );
STUB_TASK_DEFINITION( ost_Taskx8BaseOS   );
STUB_TASK_DEFINITION( ost_Taskx24BaseOS  );

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  STUB_TASK_DEFINITION( ost_TaskEventExtPrio1 );
  STUB_TASK_DEFINITION( ost_TaskEventExtPrio2 );
  STUB_TASK_DEFINITION( ost_TaskBaseCtrlCycx4pLow );
  STUB_TASK_DEFINITION( ost_TaskBaseCtrlCycx200Background );
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  STUB_TASK_DEFINITION( ost_Taskx1Guest );
  STUB_TASK_DEFINITION( ost_Taskx2Guest );
  STUB_TASK_DEFINITION( ost_Taskx4Guest );
  STUB_TASK_DEFINITION( ost_Taskx10Guest );
  STUB_TASK_DEFINITION( ost_Taskx20Guest );
#endif

//dummy, see Os_Cfg.h - examples: TaskTPSWKillCore0, TaskTPSWKillCore1
STUB_TASK_DEFINITION( ost_TaskDummy );

/// The OSSim_Task definition encapsulates RBSYS-Task and adds
/// further details to the RBSYS/OS-Task [string-name], callback hooks etc.

#if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
  #define Exec0p5msTask     &OSSim_Task0p5ms
  OsSimTask OSSim_Task0p5ms =
  { .pProcessTable        = c_Task0p5ms,  \
    .pProcessMeasPoints   = c_Task0p5ms_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_Task0p5msCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Task0p5ms),  \
    .TaskName             = "Task0p5ms",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_FixedEvent_Post0p5ms, \
  };
#else
  uint32 ossim_priv_500usec_cnt;

  /// [ossim_private_500usec_execution]
  /// also if RBSYS "API"-wise doesn't schedule 500usec processes,
  /// we still hook 500usec-private task to avoid variation at all
  /// these locations in simulation.
  /// - SWT may still run 500usec time quantum
  /// - still measurement is hooked into 500usec slice
  /// - and some other stuff is always done in OSSim_FixedEvent_Post0p5ms.

  #define ExecDummy0p5msTask     &OSSim_Task0p5ms_priv
  static const PRC_PTR c_Task0p5ms_priv[] ={NULL};
  OsSimTask OSSim_Task0p5ms_priv =
  { .pProcessTable        = c_Task0p5ms_priv,  \
    .pProcessMeasPoints   = NULL, \
    .pTaskCounter         = (uint32*) &(ossim_priv_500usec_cnt),  \
    .rbsysTaskType        = NULL,  \
    .TaskName             = "500usec-exec-private",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_FixedEvent_Post0p5ms, \
  };

#endif

#define Exec1msTask       &OSSim_Task1ms
OsSimTask OSSim_Task1ms =
{ .pProcessTable        = c_Task1ms,  \
  .pProcessMeasPoints   = c_Task1ms_pmp, \
  .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_Task1msCnt_u32),  \
  .rbsysTaskType        = STUB_TREF(ost_Task1ms),/*RBSYS_TaskType_Task1ms,  */\
  .TaskName             = "Task1ms",  \
  .pPreCB               = &OSSim_EventPre1ms, \
  .pPostCB              = &OSSim_EventPost1ms, \
};

#define ExecIdleTask      &OSSim_TaskIdle
static uint32 taskCntIdle = 0;
OsSimTask OSSim_TaskIdle =
{
  .pProcessTable         = c_TaskIdle,  \
  .pProcessMeasPoints   =  c_TaskIdle_pmp, \
  .pTaskCounter          = &taskCntIdle,  \
  .TaskName              = "TaskIdle",  \
  .pPreCB                = &OSSim_FixedEvent_PreTaskIdle, \
  .pPostCB               = &OSSim_FixedEvent_PostTaskIdle, \
  .IgnoreOnBaseOsReplace = TRUE, \
};

OsSimTask OSSim_TaskPreReprogCheck =
{
  .pProcessTable         = c_PreReprogCheck,  \
  .pProcessMeasPoints    = NULL, \
  .pTaskCounter          = NULL,  \
  .TaskName              = "PreReprogCheck",  \
  .pPreCB                = &OSSim_DummyCallBackLocation, \
  .pPostCB               = &OSSim_DummyCallBackLocation, \
  .IgnoreOnBaseOsReplace = TRUE, \
};

#define ExecPrePlantCheck &OSSim_TaskPrePlantCheck
OsSimTask  OSSim_TaskPrePlantCheck =
{
  .pProcessTable         = c_PrePlantCheck,  \
  .pProcessMeasPoints    = c_PrePlantCheck_pmp, \
  .pTaskCounter          = NULL,  \
  .TaskName              = "PrePlantCheck",  \
  .pPreCB                = &OSSim_DummyCallBackLocation, \
  .pPostCB               = &OSSim_DummyCallBackLocation, \
  .IgnoreOnBaseOsReplace = TRUE, \
};

#define ExecInitTask      &OSSim_TaskInit
OsSimTask OSSim_TaskInit =
{
  .pProcessTable         = c_TaskInit,  \
  .pProcessMeasPoints    = c_TaskInit_pmp, \
  .pTaskCounter          = NULL,  \
  .rbsysTaskType         = STUB_TREF(ost_TaskInit),  \
  .TaskName              = "TaskInit",  \
  .pPreCB                = &OSSim_DummyCallBackLocation, \
  .pPostCB               = &OSSim_DummyCallBackLocation, \
  .IgnoreOnBaseOsReplace = TRUE, \
};

#define ExecInitTaskBaseOS &OSSim_TaskInitBaseOS
OsSimTask OSSim_TaskInitBaseOS =
{
  .pProcessTable         = c_TaskInitBaseOS,  \
  .pProcessMeasPoints    = c_TaskInit_pmp, \
  .pTaskCounter          = NULL,  \
  .rbsysTaskType         = STUB_TREF(ost_TaskInit),  \
  .TaskName              = "TaskInitBaseOS",  \
  .pPreCB                = &OSSim_DummyCallBackLocation, \
  .pPostCB               = &OSSim_DummyCallBackLocation, \
};

#define ExecX1High &OSSim_TaskX1High
OsSimTask OSSim_TaskX1High =
{
  .pProcessTable        = c_Taskx1h,  \
  .pProcessMeasPoints    = c_Taskx1h_pmp, \
  .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx1Cnt_u32),  \
  .rbsysTaskType        = STUB_TREF(ost_Taskx1h),  \
  .TaskName             = "TaskX1High",  \
  .pPreCB               = &OSSim_DummyCallBackLocation, \
  .pPostCB              = &OSSim_DummyCallBackLocation, \
};

#define ExecX1Low  &OSSim_TaskX1Low
OsSimTask OSSim_TaskX1Low =
{
  .pProcessTable        = c_Taskx1l,  \
  .pProcessMeasPoints   = c_Taskx1l_pmp,  \
  .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx1LowCnt_u32),  \
  .rbsysTaskType        = STUB_TREF(ost_Taskx1l),  \
  .TaskName             = "TaskX1Low",  \
  .pPreCB               = &OSSim_DummyCallBackLocation, \
  .pPostCB              = &OSSim_DummyCallBackLocation, \
};

#define ExecX2Task &OSSim_TaskX2
OsSimTask OSSim_TaskX2 =
{
  .pProcessTable        = c_Taskx2,  \
  .pProcessMeasPoints   = c_Taskx2_pmp,  \
  .pTaskCounter         = (uint32 *) &(RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32),  \
  .rbsysTaskType        = STUB_TREF(ost_Taskx2),  \
  .TaskName             = "TaskX2",  \
  .pPreCB               = &OSSim_DummyCallBackLocation, \
  .pPostCB              = &OSSim_DummyCallBackLocation, \
};

#define ExecX4Task &OSSim_TaskX4
OsSimTask OSSim_TaskX4 =
{
  .pProcessTable        = c_Taskx4,  \
  .pProcessMeasPoints   = c_Taskx4_pmp,  \
  .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx4Cnt_u32),  \
  .rbsysTaskType        = STUB_TREF(ost_Taskx4),  \
  .TaskName             = "TaskX4",  \
  .pPreCB               = &OSSim_DummyCallBackLocation, \
  .pPostCB              = &OSSim_DummyCallBackLocation, \
};

#if( RBFS_MCORE == RBFS_MCORE_ON )
  #define ExecX2TaskP &OSSim_TaskX2P
  OsSimTask OSSim_TaskX2P =
  {
    .pProcessTable      = c_Taskx2p,  \
    .pProcessMeasPoints = c_Taskx2p_pmp,  \
    .pTaskCounter       = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx2pCnt_u32),  \
    .rbsysTaskType      = STUB_TREF(ost_Taskx2p),  \
    .TaskName           = "TaskX2P",  \
    .pPreCB             = &OSSim_DummyCallBackLocation, \
    .pPostCB            = &OSSim_DummyCallBackLocation, \
  };
#endif

#define ExecX8Task  &OSSim_TaskX8
OsSimTask OSSim_TaskX8 =
{
  .pProcessTable      = c_Taskx8,  \
  .pProcessMeasPoints = c_Taskx8_pmp,  \
  .pTaskCounter       = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx8Cnt_u32),  \
  .rbsysTaskType      = STUB_TREF(ost_Taskx8),  \
  .TaskName           = "TaskX8",  \
  .pPreCB             = &OSSim_DummyCallBackLocation, \
  .pPostCB            = &OSSim_DummyCallBackLocation, \
};

#define ExecX24Task &OSSim_TaskX24
OsSimTask OSSim_TaskX24 =
{
  .pProcessTable      = c_Taskx24,  \
  .pProcessMeasPoints = c_Taskx24_pmp,  \
  .pTaskCounter       = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx24Cnt_u32),  \
  .rbsysTaskType      = STUB_TREF(ost_Taskx24),  \
  .TaskName           = "TaskX24",  \
  .pPreCB             = &OSSim_DummyCallBackLocation, \
  .pPostCB            = &OSSim_FixedEvent_Post120ms, \
};

#define ExecTaskInitializeSystem &OSSim_TaskInitializeSystem
OsSimTask OSSim_TaskInitializeSystem =
{
  .pProcessTable    = /*(const PRC_PTR*) &*/OSSim_Initialize,  \
  .pTaskCounter     = NULL,  \
  .rbsysTaskType    = NULL,  \
  .TaskName         = "Instantiate",  \
  .pPreCB           = &OSSim_DummyCallBackLocation, \
  .pPostCB          = &OSSim_DummyCallBackLocation, \
};

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define ExecX1GuestTask &OSSim_TaskX1Guest
  OsSimTask OSSim_TaskX1Guest =
  {
    .pProcessTable        = c_Taskx1Guest,  \
    .pProcessMeasPoints    = c_Taskx1Guest_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx1GuestCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Taskx1Guest),  \
    .TaskName             = "TaskX1Guest",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_DummyCallBackLocation, \
  };
  #define ExecX2GuestTask &OSSim_TaskX2Guest
  OsSimTask OSSim_TaskX2Guest =
  {
    .pProcessTable        = c_Taskx2Guest,  \
    .pProcessMeasPoints    = c_Taskx2Guest_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx2GuestCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Taskx2Guest),  \
    .TaskName             = "TaskX2Guest",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_DummyCallBackLocation, \
  };
  #define ExecX4GuestTask &OSSim_TaskX4Guest
  OsSimTask OSSim_TaskX4Guest =
  {
    .pProcessTable        = c_Taskx4Guest,  \
    .pProcessMeasPoints    = c_Taskx4Guest_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx4GuestCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Taskx4Guest),  \
    .TaskName             = "TaskX4Guest",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_DummyCallBackLocation, \
  };
  #define ExecX10GuestTask &OSSim_TaskX10Guest
  OsSimTask OSSim_TaskX10Guest =
  {
    .pProcessTable        = c_Taskx10Guest,  \
    .pProcessMeasPoints    = c_Taskx10Guest_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx10GuestCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Taskx10Guest),  \
    .TaskName             = "TaskX10Guest",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_DummyCallBackLocation, \
  };
  #define ExecX20GuestTask &OSSim_TaskX20Guest
  OsSimTask OSSim_TaskX20Guest =
  {
    .pProcessTable        = c_Taskx20Guest,  \
    .pProcessMeasPoints    = c_Taskx20Guest_pmp, \
    .pTaskCounter         = (uint32*) &(RBMESG_RBMESG_TaskBaseCtrlx20GuestCnt_u32),  \
    .rbsysTaskType        = STUB_TREF(ost_Taskx20Guest),  \
    .TaskName             = "TaskX20Guest",  \
    .pPreCB               = &OSSim_DummyCallBackLocation, \
    .pPostCB              = &OSSim_DummyCallBackLocation, \
  };
#endif

#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  #define ExecFastTasks1ms Exec0p5msTask,\
                           Exec1msTask,\
                           Exec0p5msTask
#else
  #define ExecFastTasks1ms ExecDummy0p5msTask,\
                           Exec1msTask,\
                           ExecDummy0p5msTask
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define ExecX1Tasks ExecX1High,\
                      ExecX1GuestTask
#else
  #define ExecX1Tasks ExecX1High
#endif

#if(RBFS_MCORE == RBFS_MCORE_OFF)
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    #define ExecX2Tasks ExecX2Task,\
                        ExecX2GuestTask
  #else
    #define ExecX2Tasks ExecX2Task
  #endif
#else
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    #define ExecX2Tasks ExecX2Task,\
                        ExecX2TaskP,\
                        ExecX2GuestTask
  #else
    #define ExecX2Tasks ExecX2Task,\
                        ExecX2TaskP
  #endif
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define ExecX4Tasks ExecX4Task,\
                      ExecX4GuestTask
#else
  #define ExecX4Tasks ExecX4Task
#endif

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define CombinedExec10ms \
    ExecFastTasks1ms  ,\
    ExecX1Tasks       ,\
    ExecFastTasks1ms  ,\
    ExecX1Low         ,\
    ExecFastTasks1ms  ,\
    ExecX2Tasks       ,\
    ExecFastTasks1ms  ,\
    ExecFastTasks1ms  ,\
    ExecIdleTask      ,\
    /*5ms elapsed*/    \
    ExecFastTasks1ms  ,\
    ExecX1Tasks       ,\
    ExecFastTasks1ms  ,\
    ExecIdleTask      ,\
    ExecX1Low         ,\
    ExecFastTasks1ms  ,\
    ExecFastTasks1ms  ,\
    ExecFastTasks1ms   \
    /*10ms elapsed*/
#endif

/// a pseudo random pattern
#define CombinedExec20ms \
  ExecFastTasks1ms  ,\
  ExecX1Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecX1Low         ,\
  ExecFastTasks1ms  ,\
  ExecX2Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecFastTasks1ms  ,\
  ExecIdleTask      ,\
  /*5ms elapsed*/    \
  ExecFastTasks1ms  ,\
  ExecX1Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecIdleTask      ,\
  ExecX1Low         ,\
  ExecFastTasks1ms  ,\
  ExecFastTasks1ms  ,\
  ExecFastTasks1ms  ,\
  /*10ms elapsed*/   \
  ExecFastTasks1ms  ,\
  ExecX1Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecX1Low         ,\
  ExecFastTasks1ms  ,\
  ExecX2Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecIdleTask      ,\
  ExecFastTasks1ms  ,\
  /*15ms elapsed*/   \
  ExecX4Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecX1Tasks       ,\
  ExecFastTasks1ms  ,\
  ExecIdleTask      ,\
  ExecX1Low         ,\
  ExecFastTasks1ms  ,\
  ExecFastTasks1ms  ,\
  ExecFastTasks1ms  ,\
  ExecIdleTask
  /*20ms elapsed */

//60% Load Task Scheme and updated times for x2,x4,x8 and x24
#define Combined_Exec20ms_60PTaskJitter \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecIdleTask      ,/*Idle*/  \
  /*5ms elapsed*/              \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecFastTasks1ms  ,/*1*/     \
  /*10ms elapsed*/             \
  ExecX4Tasks       ,/*x4Task*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecX1Low         ,/*x1Low*/ \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX2Tasks       ,/*x2Task*/\
  /*15ms elapsed*/             \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask       /*Idle*/
  /*20ms elapsed */

//80% Load Task Scheme
/// a pseudo random pattern
#define Combined_Exec20ms_80PTaskJitter \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecIdleTask      ,/*Idle*/  \
  ExecX2Tasks       ,/*x2Task*/\
  /*5ms elapsed*/              \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecX4Tasks       ,/*x4Task*/\
  /*10ms elapsed*/             \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*4*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecX2Tasks       ,/*x2Task*/\
  /*15ms elapsed*/             \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecIdleTask       /*Idle*/
  /*20ms elapsed */

//100% Load Task Scheme
/// a pseudo random pattern
#define Combined_Exec20ms_100PTaskJitter_Start \
  ExecFastTasks1ms  ,/*1*/     \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*4*/     \
  /*impossible to have only 4ms between x1h, because SYS-Jitter-Mon*/\
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*5ms elapsed*/              \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*10ms elapsed*/             \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*15ms elapsed*/             \
  ExecX4Tasks       ,/*x4Task*/\
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecIdleTask       /*Idle*/
  /*20ms elapsed */

//100% Load Task Scheme
/// a pseudo random pattern
#define Combined_Exec20ms_100PTaskJitter \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*5ms elapsed*/              \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*10ms elapsed*/             \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*15ms elapsed*/             \
  ExecX4Tasks       ,/*x4Task*/\
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  ExecIdleTask   /*Idle*/
  /*20ms elapsed */

#define Combined_Exec20ms_100PTaskJitter_End \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*5ms elapsed*/              \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*2*/     \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*10ms elapsed*/             \
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecX2Tasks       ,/*x2Task*/\
  ExecFastTasks1ms  ,/*3*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*4*/     \
  ExecFastTasks1ms  ,/*5*/     \
  ExecX1Low         ,/*x1Low*/ \
  /*15ms elapsed*/             \
  ExecX4Tasks       ,/*x4Task*/\
  ExecX1Tasks       ,/*x1High*/\
  ExecFastTasks1ms  ,/*1*/     \
  ExecFastTasks1ms  ,/*2*/     \
  ExecIdleTask      ,/*Idle*/  \
  ExecFastTasks1ms  ,/*3*/     \
  ExecFastTasks1ms  ,/*4*/     \
  /*one less, because this will be in _Start table */\
  ExecX1Low         ,/*x1Low*/ \
  ExecIdleTask       /*Idle*/
  /*20ms elapsed */

/// just used as terminator
OsSimTask EndTask =
{
  .pProcessTable = NULL,
};

#define ExecDefaultExecTable OSSim_DefaultExecTable
OsSimTask* OSSim_DefaultExecTable[] =
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  {
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX24Task,
    ExecX8Task,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,

    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX24Task,
    ExecX8Task,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,

    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX24Task,
    ExecX8Task,

    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,

    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX24Task,
    ExecX8Task,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,

    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX24Task,
    ExecX8Task,
    ExecX10GuestTask,
    CombinedExec10ms,
    CombinedExec10ms,
    ExecX4Tasks,
    CombinedExec10ms,
    ExecX20GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    ExecX8Task,
    CombinedExec10ms,
    ExecX10GuestTask,
    CombinedExec10ms,
    ExecX4Tasks,
    &EndTask
  };
#else
  {
    /* the complete 120ms slice */

    CombinedExec20ms,

    ExecX8Task      ,
    CombinedExec20ms,
    CombinedExec20ms,
    ExecX24Task     ,
    ExecX8Task      ,

    CombinedExec20ms,
    CombinedExec20ms,
    ExecX8Task      ,

    CombinedExec20ms,

    &EndTask
  };
#endif

// Execution table with 60%Task Jitter with respect to 1ms Tasks
OsSimTask* OSSim_60P_TaskJitter_ExecTable[] =
{
  /// Complete 120ms slice
  Combined_Exec20ms_60PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_60PTaskJitter,
  ExecX24Task     ,
  Combined_Exec20ms_60PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_60PTaskJitter,
  Combined_Exec20ms_60PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_60PTaskJitter,

  &EndTask
};

// Execution table with 80%Task Jitter with respect to 1ms Tasks
OsSimTask* OSSim_80P_TaskJitter_ExecTable[] =
{
  /// Complete 120ms slice
  Combined_Exec20ms_80PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_80PTaskJitter,
  Combined_Exec20ms_80PTaskJitter,
  ExecX24Task     ,
  ExecX8Task      ,
  Combined_Exec20ms_80PTaskJitter,
  Combined_Exec20ms_80PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_80PTaskJitter,

  &EndTask
};

// Execution table with 100%Task Jitter with respect to 1ms Tasks
OsSimTask* OSSim_100P_TaskJitter_ExecTable[] =
{
  /// Complete 120ms slice
  Combined_Exec20ms_100PTaskJitter_Start,
  ExecX8Task      ,
  Combined_Exec20ms_100PTaskJitter,
  Combined_Exec20ms_100PTaskJitter,
  ExecX24Task     ,
  ExecX8Task      ,
  Combined_Exec20ms_100PTaskJitter,
  Combined_Exec20ms_100PTaskJitter,
  ExecX8Task      ,
  Combined_Exec20ms_100PTaskJitter_End,

  &EndTask
};

void OSSim_SelectTaskPattern(OSSim_TaskPattern TaskPattern)
{
  if(TaskPattern == OSSim_TaskPattern_Default)
  {
    //Clear the default variable before overwriting the new Task Patter
    memset(OSSim_DefaultExecTable,0,sizeof(OSSim_DefaultExecTable));
    //Copy the new Task Pattern table into default variable
    memcpy( OSSim_DefaultExecTable, OSSim_DefaultExecTable , sizeof( OSSim_DefaultExecTable ) );
  }
  else if(TaskPattern == OSSim_TaskPattern_60PJitter)
  {
    //Clear the default variable before overwriting the new Task Patter
    memset(OSSim_DefaultExecTable,0,sizeof(OSSim_DefaultExecTable));
    //Copy the new Task Pattern table into default variable
    memcpy( OSSim_DefaultExecTable, OSSim_60P_TaskJitter_ExecTable , sizeof( OSSim_60P_TaskJitter_ExecTable ) );
  }
  else if(TaskPattern == OSSim_TaskPattern_80PJitter)
  {
    //Clear the default variable before overwriting the new Task Patter
    memset(OSSim_DefaultExecTable,0,sizeof(OSSim_DefaultExecTable));
    //Copy the new Task Pattern table into default variable
    memcpy( OSSim_DefaultExecTable, OSSim_80P_TaskJitter_ExecTable , sizeof( OSSim_80P_TaskJitter_ExecTable ) );
  }
  else if(TaskPattern == OSSim_TaskPattern_100PJitter)
  {
    //Clear the default variable before overwriting the new Task Patter
    memset(OSSim_DefaultExecTable,0,sizeof(OSSim_DefaultExecTable));
    //Copy the new Task Pattern table into default variable
    memcpy( OSSim_DefaultExecTable, OSSim_100P_TaskJitter_ExecTable , sizeof( OSSim_100P_TaskJitter_ExecTable ) );
  }
}

/// order here is not important, just all tasks should appear once.
/// only "PUBLIC" tasks to appear here.
/// used for:
/// - replace tasks in BaseOs-Mode
/// - find task via task-counter (public api)
/// - find task via proceses (public api)
OsSimTask* OSSim_DefaultTasks[] =
{
  #if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
    &OSSim_Task0p5ms,
  #endif
  &OSSim_Task1ms,
  &OSSim_TaskX1High,
  &OSSim_TaskX1Low,
  &OSSim_TaskX2,
  #if( RBFS_MCORE == RBFS_MCORE_ON )
    &OSSim_TaskX2P,
  #endif
  &OSSim_TaskX4,
  &OSSim_TaskX8,
  &OSSim_TaskX24,
  &OSSim_TaskIdle,
  &OSSim_TaskInit,
  &OSSim_TaskPrePlantCheck,
  &OSSim_TaskPreReprogCheck,

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    &OSSim_TaskX1Guest,
    &OSSim_TaskX2Guest,
    &OSSim_TaskX4Guest,
    &OSSim_TaskX10Guest,
    &OSSim_TaskX20Guest,
  #endif

  &EndTask
};

int OSSim_TaskTable_IsEnd(OsSimTask* pTable[], int i)
{
  OsSimTask* task = pTable[i];

  return (task == NULL) || (task == &EndTask) || (task->pProcessTable == NULL);
}

void OSSim_ReplaceTasksByBaseOsTasks(OsSimTask* pExecTable[])
{
  int i = 0;

  OsSimTask* pTask = pExecTable[i];

  while(pTask->pProcessTable != NULL)
  {
    #if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON )
      if( pTask->pProcessTable ==       c_Task0p5ms ) {
        pTask->pProcessTable =          c_Task0p5msBaseOS;
      }
      else
    #endif
    if( pTask->pProcessTable ==  c_Task1ms) {
      pTask->pProcessTable =          c_Task1msBaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx1h ) {
      pTask->pProcessTable =          c_Taskx1hBaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx1l ) {
      pTask->pProcessTable =          c_Taskx1lBaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx2 ) {
      pTask->pProcessTable =          c_Taskx2BaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx4 ) {
      pTask->pProcessTable =          c_Taskx4BaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx8 ) {
      pTask->pProcessTable =          c_Taskx8BaseOS;
    }
    else if( pTask->pProcessTable ==  c_Taskx24 ) {
      pTask->pProcessTable =          c_Taskx24BaseOS;
    }
    #if( RBFS_MCORE == RBFS_MCORE_ON )
      else if( pTask->pProcessTable ==  c_Taskx2p ) {
        pTask->pProcessTable =          c_Taskx2pBaseOS;
      }
    #endif

    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
      else if( pTask->pProcessTable ==  c_Taskx1Guest ) {
        pTask->pProcessTable =          c_Taskx1GuestBaseOS;
      }
      else if( pTask->pProcessTable ==  c_Taskx2Guest ) {
        pTask->pProcessTable =          c_Taskx2GuestBaseOS;
      }
      else if( pTask->pProcessTable ==  c_Taskx4Guest ) {
        pTask->pProcessTable =          c_Taskx4GuestBaseOS;
      }
      else if( pTask->pProcessTable ==  c_Taskx10Guest ) {
        pTask->pProcessTable =          c_Taskx10GuestBaseOS;
      }
      else if( pTask->pProcessTable ==  c_Taskx20Guest ) {
        pTask->pProcessTable =          c_Taskx20GuestBaseOS;
      }
    #endif

    /* remain untouched same in both mode, just to allow to use else-error below. */
    else if( pTask->IgnoreOnBaseOsReplace ) {
      /// nothing to do.
    }
    else
    {
      const char* task_name = "<unknown>";
      if( pTask->TaskName != NULL )
      {
        task_name = pTask->TaskName;
      }

      #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
        hwm_warning("BaseOS-Switch: Task %s, couldn't be resolved.", task_name);
        assert(0 && "BaseOS-Switch: Task couldn't be resolved");
      #endif
    }

    i++;
    pTask = pExecTable[i];
  }
}


#ifndef OSSim_InitializeSystem

  // Defines the initialization process of the Operation System
  // <COMPONENT>_RB_Config.h
  // #define OSSim_InitializeSystem
  PRC_PTR OSSim_Initialize[] = {
    NULL
  };

#endif

/*******************************************************
* Definition of Callbacks and Functions
********************************************************/

void OSSim_StopTask_StopOS(OsSimTask* task, int stoppedBefore, int* abortProcessing)
{
  OSSim_TaskBorderStopper_Feedback* fb = &(TaskBorderStopper.Feedback);
  fb->StoppedAtTask = task;
  fb->StoppedBefore = stoppedBefore;

  /// this forces the OS to return to caller.
  *abortProcessing = TRUE;
}

void OSSim_StopTask_CheckAndHandlePost(OsSimTask* task, int* abortProcessing)
{
  if(TaskBorderStopper.IsActive)
  {
    OSSim_TaskBorderStopper_Params* params = &(TaskBorderStopper.Parameter);

    if( params->StopAtTask == task && !params->StopBefore )
    {
      OSSim_StopTask_StopOS( task, FALSE /*before*/, abortProcessing);
    }
  }
}

int OSSim_StopTask_CheckAndHandlePre(OsSimTask* task, int* abortProcessing)
{
  if(TaskBorderStopper.IsActive)
  {
    OSSim_TaskBorderStopper_Params* params = &(TaskBorderStopper.Parameter);

    if( params->StopAtTask == task && params->StopBefore )
    {
      /// will set OSSim_AbortProcessing, which forces OS to stop all further.
      OSSim_StopTask_StopOS( task, TRUE /*before*/, abortProcessing);
    }
  }

  return *abortProcessing;
}