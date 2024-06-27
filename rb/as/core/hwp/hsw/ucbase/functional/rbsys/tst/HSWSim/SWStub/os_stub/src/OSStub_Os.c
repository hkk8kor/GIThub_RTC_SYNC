
/******************************************************************************/
/* SYSTEM_INFO:                                                               */
/* SYSTEM_INFO_END:                                                           */
/******************************************************************************/

/******************************************************************************/
/* SUPPORTED_SWITCH_SETTINGS:                                                 */
/* FS_HSim_AE, FS_HSim_HSW                                                    */
/* SUPPORTED_SWITCH_SETTINGS_END:                                             */
/******************************************************************************/

/**
 * @ingroup OSStub
 * @{
 *
 * \file
 * \brief Simulation stub of the operating system
 *
 * Basic static implementation of the "operating system" for simulation.
 *
 * @see @Task{CSCRM00405148}: HSWSim/AESim simulation support
 *
 * \author Harald Scherer (CC/ECC6)  \date 2012
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "TestEnironment_OSStub_Os.h"
#include "OSStub_Os.h"
#include "OSStub_Task.h"
#include "OSStub_RBSYS_directed.h" ///< [ossim_private_500usec_execution]
#include "../../../../../rtaos/src/RBSYS_OsConfig.h"
#include "SWStub_Config.h" ///< RBFS_OSSimTimeMeasure_On

#include "RBTexec_Config.h" ///< RBFS_TexecUsedIn now moved to SWT in default

//#define HWMLOG_ENABLED
#include "HwModel_DebugLogging.h" // hwmlog macro

#if ( RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim )
  #include "HwModel_Timing.h"
  #include "HwModel_Scheduler.h"  ///< HwModel_TimeTrigger()
  #include "HwModels/Hwm_TestEnvironment.h" ///< HwEnv_IsSoftwareExecutionAllowed
#endif

/*******************************************************
* Variables
********************************************************/
//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  static ossim_ProcessContainer OSSim_Post0p5ms_ProcessContainer[OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE];
//#endif
static ossim_ProcessContainer OSSim_Post120ms_ProcessContainer[OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE];

static OSSim_SystemData OSSim_Data;
static OSSim_SystemData* pOSSim_Data = &OSSim_Data;

uint32 RBSYSStub_TaskActivation_ticks;///< used by RBSYS_get_task_activation_ts()

/* OS-Resources for the core (always dual-core) for RTE projects. */
Os_ResourceType OSStub_Core[2];

static int OSSim_IdleTask_SpeedUp_AdditionalCalls; // = 0
/* Stop processing of tasks if variable is set */
int OSSim_AbortProcessing;


/// tpsw interface
int OSSim_IsTrustedMode = TRUE;
static int OSSim_IsBaseOsForced;


/**********************************************************
* Defines - HWMLOG and OSSimTimeMeasure
**********************************************************/


#if( defined(HWMLOG_ENABLED) )
static uint64 startt,endt,deltat;
static void ossim_prelog(unsigned int proc_id)
{
  hwmlog("Executing process %d\n",proc_id);
  startt = rdtsc();
}
#else
  #define ossim_prelog(x) /* dead */
#endif

#if( defined(HWMLOG_ENABLED) )
static void ossim_postlog(void)
{
  endt   = rdtsc();
  deltat = endt-startt;
  hwmlog("   -> Needed %d ticks\n",deltat);
  if( deltat > 100000 )
  {
    hwmlog("   -> BIG TICK <-\n");
  }
}
#else
  #define ossim_postlog() /*dead*/
#endif

#if( RBFS_OSSimTimeMeasure == RBFS_OSSimTimeMeasure_On )
  /// start task measurement macro
  #define OSSIM_MEAS_TASK_START(task) \
      do{\
        task->pTimeMeasureReference = \
          ossimTime_execTask_start_(task->pTimeMeasureReference\
                                  ,task->TaskName);\
        ossim_TaskStart_always(task);\
      }while(0)

  /// end task measurement macro
  #define OSSIM_MEAS_TASK_END(task) \
      do{\
        ossimTime_execTask_end_(task->pTimeMeasureReference);\
        ossim_TaskEnd_always(task);\
      }while(0)

  /// start process measurement macro
  #define OSSIM_MEAS_PROC_START(task,proc_id)  \
      do{\
        OSSim_ProcessMeasurePoint* process_pmp = task->pProcessMeasPoints;\
        if( process_pmp != NULL )\
          ossimTime_execProc_start_( &process_pmp[proc_id],\
                                process_pmp[proc_id].Name,\
                                task->TaskName);\
        ossim_ProcStart_always(proc_id);\
      }while(0)

  /// end process measurement macro
  #define OSSIM_MEAS_PROC_END(task,proc_id) \
      do{\
        OSSim_ProcessMeasurePoint* process_pmp = task->pProcessMeasPoints;\
        if( process_pmp != NULL )\
          ossimTime_execProc_end_(&process_pmp[proc_id]);\
        ossim_ProcEnd_always(proc_id);\
      }while(0)
#else
  #define OSSIM_MEAS_TASK_START(task)         ossim_TaskStart_always(task)
  #define OSSIM_MEAS_TASK_END(task)           ossim_TaskEnd_always(task)
  #define OSSIM_MEAS_PROC_START(task,proc_id) ossim_ProcStart_always(proc_id)
  #define OSSIM_MEAS_PROC_END(task,proc_id)   ossim_ProcEnd_always(proc_id)
#endif


/*******************************************************
* Static functions - Only RBFS_TexecUsedIn_Sim
********************************************************/


#if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)

  static inline void* ossimTime_execTask_start_(void* taskMeasurementReference,
                                        const char* task_name)
  {
    return HWTime_Measure_Start( taskMeasurementReference, task_name );
  }
  static inline void ossimTime_execTask_end_(void* taskMeasurementReference)
  {
    HWTime_Measure_End( taskMeasurementReference );
  }
  static inline void ossimTime_execProc_start_(OSSim_ProcessMeasurePoint* proc,
                                        const char* proc_name,
                                        const char* task_name)
  {
    proc->MeasureReference =
        HWTime_Measure_StartGr( proc->MeasureReference,
                                proc_name, task_name );
  }
  static inline void ossimTime_execProc_end_(OSSim_ProcessMeasurePoint* proc)
  {
    HWTime_Measure_End( proc->MeasureReference );
  }
  static int OSSim_RBSYSIsResetToBaseOs_GetAndReset(void)
  {
    int isResetToBaseOS;

    RBSYS_restoreBaseOSRequestFromBackupRAM();

    isResetToBaseOS = (RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32
                          == RBSYS_BaseOSRequest);

    /// according implementation in RBAPLPLANT it seems that RBSYS clears
    /// BackupRAM entry after it is once used.
    RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32 = RBSYS_DefaultOSRequest;
    RBSYS_saveBaseOSRequestToBackupRAM();

    return isResetToBaseOS;
  }

  static int OSSim_IsBaseOSRequested (void)
  {
      int isResetToBaseOS = OSSim_RBSYSIsResetToBaseOs_GetAndReset();

      /// 3 ways currently:
      /// - Detected from HW-Setup by APLPLANT during PrePlantCheck
      /// - Simulation forced directly to OSSim
      /// - requested before SW-Reset from RBSYS
      return (RBAPLPLANT_AsicPlantMode_u8 && RBMESG_RBMESG_RBSYSPlantModeRequest)
          || OSSim_IsBaseOsForced
          || isResetToBaseOS;
  }

#endif


/*******************************************************
* Static functions
********************************************************/


/// Indicates whether a ProcAbort is just activated or still active.
static int OSSim_ProcAbort_IsActive;
/// Tells the ProcId to continue after once ProcAbort got active.
static int OSSim_ProcAbort_ContinueProcId;
/// On ProcAbort indicates, whether the abort was "before" process was
/// called. Depending on that _ContinueProcId is set.
static int OSSim_ProcAbort_WasPreProcessCall;

/// if after ProcAbortHandler got active the system is run again,
/// we need to skip the "pre-Task" counter incrementing.
static int OSSim_ProcAbortHandler_ExecuteNextTask_MayUsualStart(void)
{
  return !OSSim_ProcAbort_IsActive;
  /// OSSim_ProcAbort_IsActive will then be reset in
  /// OSSim_ProcAbortHandler_ExecTask_CheckContinue()
}

/// avoid if ProcAbortHandler got active, that the post task exec
/// is done (like switching to next task, issueing post-task callback etc.)
static int OSSim_ProcAbortHandler_ExecuteNextTask_MayContinue(void)
{
  return !OSSim_ProcAbort_IsActive;
}

static void OSSim_ProcAbortHandler_ExecTask_CheckContinue(unsigned int* pproc_id)
{
  if(OSSim_ProcAbort_IsActive)
  {
    *pproc_id = OSSim_ProcAbort_ContinueProcId;

    OSSim_ProcAbort_IsActive          = FALSE;
    OSSim_ProcAbort_WasPreProcessCall = FALSE;
  }
}

static int OSSim_ProcAbortHandler_ExecTask_ShallStop(unsigned int proc_id)
{
  if( OSSim_ProcAbort_IsActive )
  {
    if( OSSim_ProcAbort_WasPreProcessCall )
    {
      OSSim_ProcAbort_ContinueProcId = proc_id;
    }
    else
    {
      OSSim_ProcAbort_ContinueProcId = proc_id+1;
    }
    return TRUE;///< stop the loop and leave this function
  }

  return FALSE;
}

static OSSim_PseudoTickCounter_t* ossim_PTickCntr_Get(void)
{
  static OSSim_PseudoTickCounter_t ossim_PseudoTickCounter;

  if( !ossim_PseudoTickCounter.IsInitialized )
  {
    /// during TaskInit and at beginning
    /// of 500usec window increment by 10usec for each call.
    ossim_PseudoTickCounter.PseudoIncrement_1_ticks = RBSYS_TIMERTICKS_PER_US * 10;
    ossim_PseudoTickCounter.PseudoIncrement_SlowDown_ticks = 1;
      ///< 1 tick per call

    ossim_PseudoTickCounter.SlowDownBorder_ticks = UINT32_MAX;
      ///< initialize to disable SlowDownBorder at first.

    ossim_PseudoTickCounter.IsInitialized = TRUE;
  }

  return &ossim_PseudoTickCounter;
}

static void ossim_TaskStart_always(OsSimTask* task)
{
  OSSim_Data.TaskQuery.LastTask      = task;
  OSSim_Data.TaskQuery.IsStillInTask = TRUE;
}

static void ossim_TaskEnd_always(OsSimTask* task)
{
  // OSSim_Data.TaskQuery.LastTask      = task;///< keep lastTask untouched for "info".
  OSSim_Data.TaskQuery.IsStillInTask = FALSE;
}

static void ossim_ProcStart_always(unsigned int proc_id)
{
  OSSim_Data.TaskQuery.LastProcId    = proc_id;
  OSSim_Data.TaskQuery.IsStillInProc = TRUE;
}

static void ossim_ProcEnd_always(unsigned int proc_id)
{
  // OSSim_Data.TaskQuery.LastTask      = proc_id;///< keep lastProcId untouched for "info".
  OSSim_Data.TaskQuery.IsStillInProc = FALSE;
}


#if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)

  static int ossim_ShallInformHwModelsAboutInitTask(void)
  {
    /// just inform hardware time that InitTask is over
    /// so that HwModel know, why after Init in CS999 there is more time
    /// elapsed than SWT_RunSystem() was called.
    ///
    /// Currently only used in B6ASIC_CS999 case.
    /// To avoid backward compatibility issues and support new MICB6-WD-Handler.
    return RBFS_B6ASIC == RBFS_B6ASIC_CS999;
  }
#endif

/// function called in smalles OS window.
/// current 500usec task time window
static void OSSim_PseudoTickCounter_Rebound(void)
{
  uint32 hw_ticks = (uint32) ((uint64)RBSYSStub_GetUS()
                              * RBSYS_TIMERTICKS_PER_US);

  OSSim_PseudoTickCounter_t* cntr = ossim_PTickCntr_Get();

  /// split into multiple sub windows for different "increment" speed
  /// to allow huge number of "PseudoIncrement" calls.
  if( hw_ticks == 0 )///< during TaskInit allow huge amount of pseudo-increments
  {
    cntr->SlowDownBorder_ticks = UINT32_MAX;
  }
  else
  {
    if( !cntr->InitTaskOffset_IsSet )
    {
      /// store the current value to be able to always add init-task offset
      /// later on.
      cntr->InitTaskOffset_ticks = cntr->Window_ticks;

      cntr->InitTaskOffset_IsSet = TRUE;

      #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      if( ossim_ShallInformHwModelsAboutInitTask() )
        /// just inform hardware time that InitTask is over
        /// so that HwModel know, why after Init in CS999 there is more time
        /// elapsed than SWT_RunSystem() was called.
        HWTimeMaster_SetInfo_InitTaskOver();
      #endif

    }

    /// set slowDownBorder at half of 500usec time window
    /// overflow not handled
    cntr->SlowDownBorder_ticks = hw_ticks + 250 * RBSYS_TIMERTICKS_PER_US;

    cntr->Window_ticks = hw_ticks;
  }
}

static int OSSim_FixedCallBack_Dummy(void)
{
  return OSSim_AbortProcessing;
}

//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  static int OSSim_FixedCallback_Post0p5ms(void)
  {
    int i = 0;
    while( i < OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE  && OSSim_Post0p5ms_ProcessContainer[i].Process != NULL)
    {
      OSSim_Post0p5ms_ProcessContainer[i].Process();
      i++;
    }

    //RBLcSigConn_RefreshMeasurementVars(); <- will be added by SoftEcu on need.
    OSSim_PseudoTickCounter_Rebound();

    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      /// inform the HwModels TimeMaster that time is elapsed.
      HWTimeMaster_AddElapsed_us( 500 );
    #endif

    /// Performs measurement for 0.5 milliseconds
    HSWSim_Measure500us_ForOSSim();

    return OSSim_AbortProcessing;
  }
//#endif

static int OSSim_FixedCallback_Post120ms(void)
{
  int i = 0;
  while(i < OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE && OSSim_Post120ms_ProcessContainer[i].Process != NULL)
  {
    OSSim_Post120ms_ProcessContainer[i].Process();
    i++;
  }

  return OSSim_AbortProcessing;
}

static int OSSim_FixedCallback_Idle(void)
{
  return OSSim_AbortProcessing;
}

static int OSSim_FixedCallback_Post1ms(void)
{
  OSSim_Data.MillisecondsLeftToExecute--;
  return OSSim_Data.MillisecondsLeftToExecute <= 0
    /// if SwReset is requested by Software or HwReset requested by HwModel
    || ResetHandler_IsResetRequested();
}


// Calls backs that are required in order to perform SWT_RunSystem action
//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  OSSimEventCallback OSSim_FixedEvent_Post0p5ms    = &OSSim_FixedCallback_Post0p5ms;
//#endif
OSSimEventCallback OSSim_FixedEvent_Post120ms    = &OSSim_FixedCallback_Post120ms;
OSSimEventCallback OSSim_FixedEvent_Post1ms      = &OSSim_FixedCallback_Post1ms;
OSSimEventCallback OSSim_FixedEvent_PostTaskIdle = &OSSim_FixedCallback_Idle;
OSSimEventCallback OSSim_FixedEvent_PreTaskIdle  = &OSSim_FixedCallback_Idle;
OSSimEventCallback OSSim_DummyCallBackLocation   = &OSSim_FixedCallBack_Dummy;

/// these events allow overriding (one time)
OSSimEventCallback OSSim_EventPre1ms             = &OSSim_FixedCallBack_Dummy;
OSSimEventCallback OSSim_EventPost1ms            = &OSSim_FixedCallBack_Dummy;
OSSimEventCallback OSSim_EventPost120ms          = &OSSim_FixedCallBack_Dummy;
OSSimEventCallback OSSim_EventPostEachTask       = &OSSim_FixedCallBack_Dummy;


static void OSSim_ResetSystemData(void)
{
  OSSim_EventPostEachTask    = &OSSim_FixedCallBack_Dummy;
  OSSim_EventPost1ms         = &OSSim_FixedCallBack_Dummy;
  OSSim_AbortProcessing      = FALSE;

  // Runtime state
  OSSim_Data.MicrosecondsLeftToExecute   = 0;
  OSSim_Data.MillisecondsLeftToExecute   = 0;
  OSSim_Data.TaskQuery.CounterEnd        = 0;
  OSSim_Data.TaskQuery.pOSSimCurrentTask = NULL;
  OSSim_Data.TaskQuery.TaskCounterRef    = NULL;
}

static void OSSim_ExecuteTask_ProcessList(OsSimTask* task)
{
  unsigned int proc_id = 0;

  const PRC_PTR* proc_table               = task->pProcessTable;
  const char*    task_name                = task->TaskName;

  /// store for querying from outside. - seems like TaskType is just
  /// a pointer to process table.
  OSSim_Data.TaskQuery.CurrentTaskType = task->rbsysTaskType;
  OSSIM_MEAS_TASK_START(task);

  assert(proc_table);

  if(OSSim_AbortProcessing)
  {
    return;// avoid calling further processes.
  }

  OSSim_ProcAbortHandler_ExecTask_CheckContinue( &proc_id );

  hwmlog("ExecTask <%s - nxt=%d>...\n",task_name,execNextCnt);

  RBSYSStub_TaskActivation_ticks = RBSYS_getRealtimeTickCtr();///< used by some users to calc some time delta.

  /* Loop through Processes */
  while (proc_table[proc_id] != (PRC_PTR)0)
  {
    ossim_prelog(proc_id);
    OSSIM_MEAS_PROC_START(task,proc_id);

    /// process getting finally executed.
    OSSim_ProcessExecuter(proc_table[proc_id]);

    OSSIM_MEAS_PROC_END(task,proc_id);
    ossim_postlog();

    if(OSSim_ProcAbortHandler_ExecTask_ShallStop(proc_id))
    {
      OSSim_AbortProcessing = TRUE;
      break;
    }

    proc_id++;
  }

    hwmlog("ExecTask Leaving ...\n");
    OSSIM_MEAS_TASK_END(task);
}

static int OSSim_ExecuteTask_WithPreAndPostCallbacks(OsSimTask* task)
{
  int mayExecutePost = FALSE;

  if(OSSim_ProcAbortHandler_ExecuteNextTask_MayUsualStart())
  {
    // call the PreCallback - before executing Task's Process Table
    OSSim_AbortProcessing = (*task->pPreCB)();

    (*task->pTaskCounter)++; //< important: real OS also increments counter BEFORE calling task.
  }

  // executing Task's Process Table
  OSSim_ExecuteTask_ProcessList(task);

  if(OSSim_ProcAbortHandler_ExecuteNextTask_MayContinue())
  {
    // call the PostCallback
    OSSim_AbortProcessing = (*task->pPostCB)();

    OSSim_AbortProcessing = OSSim_EventPostEachTask() || OSSim_AbortProcessing;

    // inform HW about elapsed time (to allow Interrupts etc.)

    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      HwModel_TimeTrigger();
    #endif

    mayExecutePost = TRUE;
  }

  return mayExecutePost;
}

static void OSSim_CreateInstance(void)
{
  if (!OSSim_Data.Instantiated)
  {
    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Unit)
      OSSim_ExecuteTask_ProcessList(&OSSim_TaskInitializeSystem);
    #endif
    OSSim_Data.Instantiated = TRUE;
  }
}

static void OSSim_CallInitTask(AppModeType mode)
{
  if (mode == OSDEFAULTAPPMODE)
  {
    OSSim_ExecuteTask_ProcessList(&OSSim_TaskInit);
  }
  else if (mode == AppModeBaseOS)
  {
    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      /* printf("Running BaseOS init task ... \n"); */
      RBMESG_SendMESG(RBMESG_RBSYSBaseOSActive, TRUE);

      OSSim_ExecuteTask_ProcessList( &OSSim_TaskInitBaseOS );

      /// in BaseOS another table is active.
      OSSim_ReplaceTasksByBaseOsTasks( OSSim_DefaultTasks );
    #endif
  }
  else
  {
    /** @assert Unsupported AppModeType in OS simulation */
    assert(0);
  }
}

static void OSSim_StartOSCheckAndRunInit(AppModeType mode)
{
  // os can now be stopped and restarted, without resets in between.
  // this means, that init may not be called again, if there was no reset.
  // InitCalled is automatically resetted by any kind of reset, if there
  // was one in between.
  if(!OSSim_Data.InitFlags.InitCompleted)
  {
    OSSim_Data.InitFlags.InitCalled = TRUE;

    /// inform measurement about reset.
    HSWSim_Measure_OsReset();

    /// real RBSYS also intializes in "main()" the ECLK.

    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)

      if( ossim_ShallInformHwModelsAboutInitTask() )
        HWTimeMaster_SetInfo_SoftwareRestart();

      /// setup ECLK towards system ASIC (order like in real FSWStartup)
      if(!OSSim_Data.InitFlags.EclkIsSetup)
      {
        RBSYS_SetupECP(RBSYS_ECLK_DEFAULT_KHZ);
        OSSim_Data.InitFlags.EclkIsSetup = TRUE;
      }
    #endif

    if(!OSSim_Data.InitFlags.PreReprogCheckCompleted)
    {
      OSSim_ExecuteTask_ProcessList(&OSSim_TaskPreReprogCheck);
      OSSim_Data.InitFlags.PreReprogCheckCompleted = !OSSim_AbortProcessing;
    }

    if( !OSSim_Data.InitFlags.PrePlantCheckCompleted )
    {
      OSSim_ExecuteTask_ProcessList(&OSSim_TaskPrePlantCheck);
      OSSim_Data.InitFlags.PrePlantCheckCompleted = !OSSim_AbortProcessing;
    }

    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      if( !OSSim_AbortProcessing && !OSSim_Data.InitFlags.SWStubPreTaskInit )
      {
        SWStub_InitPreTaskInit();
        OSSim_Data.InitFlags.SWStubPreTaskInit = TRUE;
      }

      if ( OSSim_IsBaseOSRequested() )
      {
          mode = AppModeBaseOS;
      }
    #endif

    RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Init);
    if( !OSSim_AbortProcessing && !OSSim_Data.InitFlags.InitTaskCompleted )
    {
      OSSim_CallInitTask(mode);
      OSSim_Data.InitFlags.InitTaskCompleted = !OSSim_AbortProcessing;

      /// if there is mode change before next call to OSSim_StartOS()
      /// that will have funny impacts (some processes from mode X
      /// are called and afterwards the process-table of other mode Y
      /// is continued at same locaation ...
      /// no handling here right now.
    }
    RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_Cyclic);

    if( !OSSim_AbortProcessing && !OSSim_Data.InitFlags.SWStubPostTaskInit )
    {
      #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
        SWStub_InitPostTaskInit();
      #endif

      /// as in reality: one measurepoint at start of Init-Task
      HSWSim_Measure500us_ForOSSim();

      // create instante and initialize hardware models
      OSSim_CreateInstance();

      // flags are "identical" but for readability keep both.
      OSSim_Data.InitFlags.SWStubPostTaskInit = TRUE;
      OSSim_Data.InitFlags.InitCompleted = TRUE;
    }
  }
}

static void OSSim_ExecuteNextTask(void)
{
  int mayExecutePost;
  OSSim_Data.TaskQuery.pOSSimCurrentTask = OSSim_DefaultExecTable[OSSim_Data.ExecNextCounter];

  if(OSSim_StopTask_CheckAndHandlePre(OSSim_Data.TaskQuery.pOSSimCurrentTask, &OSSim_AbortProcessing))
    return;

  if(OSSim_Data.TaskQuery.pOSSimCurrentTask->SkipCounter == 0)
  {
    mayExecutePost = OSSim_ExecuteTask_WithPreAndPostCallbacks(OSSim_Data.TaskQuery.pOSSimCurrentTask);
  }
  else
  {
    /// task have been executed "out-of-default-order" therefore we
    /// skip it here the exact same amount of times.
    OSSim_Data.TaskQuery.pOSSimCurrentTask->SkipCounter--;
    mayExecutePost = TRUE;
  }

  if(mayExecutePost)
  {
    OSSim_Data.ExecNextCounter++;

    /// check if end of 120ms cycle is reached
    if((OSSim_DefaultExecTable[OSSim_Data.ExecNextCounter])->pProcessTable == NULL)
    {
      OSSim_Data.ExecNextCounter = 0;
    }
  }

  OSSim_StopTask_CheckAndHandlePost(OSSim_Data.TaskQuery.pOSSimCurrentTask, &OSSim_AbortProcessing);
}

static void OSSim_Process120msCycle(void)
{
  do {
    /// OSSim_Data.ExecNextCounter is incremented within this function.
    OSSim_ExecuteNextTask();

    // Is endless loop if not stopped via OSSim_AbortProcessing.
    if( OSSim_AbortProcessing )
    {
      return;
    }

  } while(OSSim_Data.ExecNextCounter != 0);
}

static OsSimTask* ossim_OSSimTaskFromTaskCounter(uint32* taskCounter)
{
  int i = 0;

  OsSimTask** table = OSSim_DefaultTasks;
  OsSimTask* task = table[i];

  /// [ossim_private_500usec_execution]
  #if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_OFF )
    /// priv-500usec task is intentionally not in OSSim_DefaultTasks[]
    /// hence we have to manually check.
    if( taskCounter == &ossim_priv_500usec_cnt )
      return &OSSim_Task0p5ms_priv;
  #endif

  while( task->pProcessTable != NULL )
  {
    if( task->pTaskCounter == taskCounter )
      break;

    i++;
    task = table[i];
  }

  if( task->pProcessTable == NULL )
  {
    assert( 0 && "Given taskCounter not found in OSSim_DefaultTasks table.");
    task = NULL;
  }

  return task;
}

static int OSSim_PostTaskExec(void)
{
  return ((*OSSim_Data.TaskQuery.TaskCounterRef) >= OSSim_Data.TaskQuery.CounterEnd)
    /// if SwReset is requested by Software or HwReset requested by HwModel
    || ResetHandler_IsResetRequested();
}

static int OSSim_IsTaskExecutionConditionNotMet(void)
{
  /// ProcAbortHandler may not be used in parallel.
  /// Because we would probably continue at wrong Process of given task.
  ///
  /// If this is really needed, ProcAbortHandler has to be extended
  /// to also store the Task which was aborted last time.
  assert( !OSSim_ProcAbort_IsActive );

  return OSSim_ProcAbort_IsActive;
}

static void OSSim_ExecuteOnce_IdleTask(void)
{
  OSSim_ExecuteTask_ProcessList(&OSSim_TaskIdle);
}

static int OSSim_IsInTask(OsSimTask* task, Procedure proc)
{
  unsigned int proc_id = 0;

  const PRC_PTR* proc_table = task->pProcessTable;

  while (proc_table[proc_id] != (PRC_PTR)0)
  {
    if( proc_table[proc_id] == proc )
      return TRUE;

    proc_id++;
  }

  return FALSE;
}

static int OSSim_postIdle_SpeedUpCallback(void)
{
  int i;

  for( i = 0; i < OSSim_IdleTask_SpeedUp_AdditionalCalls; i++ )
  {
    OSSim_ExecuteOnce_IdleTask();
  }

  return 0;///< never stop/influence OS task processing.
}

//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  static void OSSim_RunMicrosecondsPost0p5msTask(void)
  {
    OSSim_Data.MicrosecondsLeftToExecute -= 500;

    if( OSSim_Data.MicrosecondsLeftToExecute <= 0 )
    {
      OSSim_Data.MicrosecondsLeftToExecute = 0;
      OSSim_AbortProcessing = TRUE;///< abort execution
    }

    /// hardware model requested reset.
    if( ResetHandler_IsResetRequested() )
    {
      OSSim_AbortProcessing = TRUE;
    }
  }
//#endif


/**********************************************************
* External functions
**********************************************************/


void OSSim_SetProcessExecuter(OSSimProcessExecuter executer)
{
  OSSim_ProcessExecuter = executer;
}

void OSSim_ResetProcessExecuter(void)
{
  OSSim_ProcessExecuter = &OSSim_DefaultProcedureExecuter;
}

int OSSim_ResetProcessExecuterThis(OSSimProcessExecuter exec)
{
  if( OSSim_ProcessExecuter == &OSSim_DefaultProcedureExecuter )
    return 0;
  else if( OSSim_ProcessExecuter == exec )
  {
    OSSim_ResetProcessExecuter();
    return 1;
  }
  else
  {
    /// do not reset
    return 2;
  }
}

OSSimProcessExecuter OSSim_GetProcessExecuter(void)
{
  if( OSSim_ProcessExecuter == &OSSim_DefaultProcedureExecuter )
    return NULL;

  return OSSim_ProcessExecuter;
}

/* Run and Execute Section */
int OSSim_RunInMS(int milliSecondsToExecute)
{
  OSSim_ResetSystemData();

  OSSim_Data.MillisecondsLeftToExecute = milliSecondsToExecute;
  OSSim_EventPost1ms = &OSSim_FixedCallback_Post1ms;

  OSSim_StartOS(OSDEFAULTAPPMODE);

  return OSSim_Data.MillisecondsLeftToExecute;
}

int OSSim_RunTask(uint32* pTaskCounter, int times)
{
  OSSim_ResetSystemData();

  OSSim_EventPostEachTask = &OSSim_PostTaskExec;
  OSSim_Data.TaskQuery.CounterEnd = (*pTaskCounter) + times;
  OSSim_Data.TaskQuery.TaskCounterRef = pTaskCounter;

  OSSim_StartOS(OSDEFAULTAPPMODE);

  return OSSim_Data.TaskQuery.CounterEnd-(*pTaskCounter);
}

int OSSim_RunInitTask(AppModeType mode)
{
  OSSim_StartOSCheckAndRunInit(mode);
  return 0;///< not used.
}

int OSSim_RunTillTaskBorder(uint32* pTaskCounter, int shallStopBefore)
{
  int couldExecute = TRUE;

  OsSimTask* task;

  /// there is no interference of RunTillTaskBorder to ProcAbortHandler.
  /// If later on OSSim_ExecuteSingleTaskOnce() is used, which has a problem
  /// with ProcAbortHandler, it will be signalled there.

  if(couldExecute)
  {
    OSSim_ResetSystemData();

    task = ossim_OSSimTaskFromTaskCounter(pTaskCounter);

    couldExecute = task != NULL;
  }

  if(couldExecute)
  {
    TaskBorderStopper.IsActive = TRUE;
    TaskBorderStopper.Parameter.StopAtTask = task;
    TaskBorderStopper.Parameter.StopBefore = shallStopBefore;
    /// defensive programming
    TaskBorderStopper.Feedback.StoppedAtTask = NULL;
    TaskBorderStopper.Feedback.StoppedBefore = !shallStopBefore;

    /// In a 120ms slice all tasks should have appeared at least once.
    /// Two times to ensure, that not any tasked could be missed by jittering.
    TaskBorderStopper.Feedback.Remaining_ms = OSSim_RunInMS( 120 * 2 );

    /// disable task stopper.
    TaskBorderStopper.IsActive = FALSE;

    /// if OS internall signalled that it stopped at correct task.
    couldExecute = TaskBorderStopper.Feedback.StoppedAtTask == task
                && TaskBorderStopper.Feedback.StoppedBefore == shallStopBefore
                && TaskBorderStopper.Feedback.Remaining_ms > 0;
  }

  return couldExecute;
}

void OSSim_StartOS(AppModeType mode)
{
  hwmlog("OSSim_StartOS reached ...\n");

  OSSim_StartOSCheckAndRunInit(mode);

  hwmlog("OS CyclicMode reached ...\n");

  /* TODO: interrupt handling not yet supported */
  hwmlog("OsCyclicStart ...\n");

  while(!OSSim_AbortProcessing)
  {
    OSSim_Process120msCycle();

    hwmlog("Os running ...\n");
    OSSim_EventPost120ms();
  }

  hwmlog("OsShutdown ...\n");
}

int OSSim_ExecuteSingleTaskOnce(uint32* pTaskCounter)
{
  /// If software not running because of 'hardware not allowing'.
  /// Like Undervoltage or Sleep.
  /// Right now, this is not, yet. included here, but could easily be done.
  /// API is just prepared for it.
  ///
  /// Another current limitation is the ProcAbortHandler. Which
  /// cannot be used in parallel to single task execution at the moment.
  /// See OSSim_IsTaskExecutionConditionNotMet() for more details.
  int couldExecute = TRUE;

  OsSimTask* task;

  if(OSSim_IsTaskExecutionConditionNotMet())
  {
    couldExecute = FALSE;
  }

  if( couldExecute )
  {
    OSSim_ResetSystemData();
    task = ossim_OSSimTaskFromTaskCounter(pTaskCounter);
    couldExecute = task != NULL;
  }

  if(couldExecute)
  {
    /// If Init not called, run it now.
    /// If Init was already called, below function does nothing but
    /// checking the flag.
    OSSim_StartOSCheckAndRunInit(OSDEFAULTAPPMODE);

    /// for now ignore the "mayExecutePost" return, perhaps
    /// if ProcAbortHandler shall be supported in parallel to SingleTaskExec.
    (void) OSSim_ExecuteTask_WithPreAndPostCallbacks(task);

    task->SkipCounter++;
  }

  return couldExecute;
}

/* Others */

int OSSim_IsInitCompleted(void)
{
  return OSSim_Data.InitFlags.InitCompleted;
}

void OSSim_ActivateProcAbort(int wasPreProcessCall)
{
  OSSim_ProcAbort_IsActive = TRUE;
  ///< Resetting will automatically happen with next ExecuteNextTask()
  ///< or ExecTask().
  OSSim_ProcAbort_WasPreProcessCall = wasPreProcessCall;
}

void OSSim2Texec_RescuePDMStuff(void)
{
  OSSim_ExecuteOnce_IdleTask();
}

int OSSim_IsKnownProcess(Procedure proc)
{
  int i = 0;

  OsSimTask* current_task = OSSim_DefaultTasks[i];

  while( current_task->pProcessTable != NULL )
  {
    if( OSSim_IsInTask(current_task, proc) )
      return 1000000 + (int) current_task->rbsysTaskType;

    i++;
    current_task = OSSim_DefaultTasks[i];
  }

  return 0;
}

int OSSim_GetIdleTaskSpeed(void)
{
  if( OSSim_FixedEvent_PostTaskIdle == &OSSim_postIdle_SpeedUpCallback )
    return OSSim_IdleTask_SpeedUp_AdditionalCalls;
  else
    return 1;
}

void OSSim_SpeedUpIdleTask(int timesFasterThanUsual)
{
  /* design possibilities (I see, R.Flechsig 29-Mar-2016):
    A- insert "post/pre-idle-task" callback and call in addition
    B- replace complete "idle-task" (list of processes) by a "x-times bigger list".

    B- is a bigger redesign to achieve a "x-times" bigger list (without re-allocation of memory)
    A- is much simpler to realize -> see below
  */

  if( timesFasterThanUsual > 1 )///< "0" and "1" shall lead to "usual" behavior.
  {
    OSSim_FixedEvent_PostTaskIdle = &OSSim_postIdle_SpeedUpCallback;
    OSSim_IdleTask_SpeedUp_AdditionalCalls = timesFasterThanUsual - 1;
  }
  else
  {
    OSSim_FixedEvent_PostTaskIdle = &OSSim_FixedCallBack_Dummy;
    OSSim_IdleTask_SpeedUp_AdditionalCalls = 0;
  }
}

StatusType OSSim_GetTaskID(TaskRefType TaskID) {
  /// identification just works via pointer to the current
  /// active process table.

  *TaskID = OSSim_Data.TaskQuery.CurrentTaskType;
  return E_OK;
}

StatusType Os_GetTaskID(TaskRefType TaskID)
{
  // Wrapper for backward compatibility
  return OSSim_GetTaskID(TaskID);
}

StatusType ActivateTask_impl(const void* proc_table, const char* task_name)
{
  StatusType ret = E_OK;
  const Os_TaskType* ptask = (const Os_TaskType*) proc_table;

  if( OSSim_IsTaskExecutionConditionNotMet() )
  {
    ret = E_NOT_OK;
  }
  else
  {
    #if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
    if( proc_table == (void*)TaskFlexray )
    {
      OsSimTask task;
      memset(&task,0,sizeof(task));

      task.pProcessTable = (const PRC_PTR*) proc_table;
      task.TaskName      = task_name;

      OSSim_ExecuteTask_ProcessList( &task );
    }
    else
    #endif
    if( ptask->sim_type == 0xDEADBEEFu && ptask->task_func != NULL )
    {
      ptask->task_func();
    }
    else
    {
      ret = E_NOT_OK;
      assert(0 && "Only TaskFlexray supported in ActivateTask_impl()");
    }
  }

  return ret;
}

uint32 OSSim_PseudoTickCounter_GetTicks(void)
{
  return ossim_PTickCntr_Get()->Window_ticks +
    ossim_PTickCntr_Get()->InitTaskOffset_ticks;
}

void OSSim_PseudoTickCounter_PseudoIncrement(void)
{
  OSSim_PseudoTickCounter_t* cntr = ossim_PTickCntr_Get();

  uint32 delta_ticks;

  if( cntr->Window_ticks < cntr->SlowDownBorder_ticks )
  {
    delta_ticks = cntr->PseudoIncrement_1_ticks;
  }
  else
  {
    delta_ticks = cntr->PseudoIncrement_SlowDown_ticks;
  }

  cntr->Window_ticks += delta_ticks;

  #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
    ///< HWModel still not available for SWTMeas

    /// due to new MICB6-WD-Handler(CS999) we have to inform HwModel
    /// about elapsed time, even in init-task.
    if( !OSSim_IsInitCompleted() && ossim_ShallInformHwModelsAboutInitTask() )
    {
      HWTimeMaster_AddElapsed_us( (delta_ticks +
                                  /*improved rounding*/RBSYS_TIMERTICKS_PER_US/2)
                                 / RBSYS_TIMERTICKS_PER_US );
    }
  #endif
}


/* Proc list interface - TODO: Move to  OSStub_DynamicProcessList.h */

//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  int OSSim_RemovePost0p5msProcess(Procedure proc)
  {
    return ossim_RemoveProcess( OSSim_Post0p5ms_ProcessContainer,
                                OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE,
                                proc );
  }

  int OSSim_AddPost0p5msProcess(Procedure proc)
  {
    return ossim_AddProcess(OSSim_Post0p5ms_ProcessContainer,
                            OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE,
                            proc);
  }

  int OSSim_AddPost0p5msLastProcess(Procedure proc)
  {
    return ossim_AddProcessX( OSSim_Post0p5ms_ProcessContainer,
                              OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE,
                              proc,
                              NULL/*before*/,
                              NULL/*after*/,
                              ossim_PSLV_Last );
  }
//#endif

int OSSim_RemovePost120msProcess(Procedure proc)
{
  return ossim_RemoveProcess( OSSim_Post120ms_ProcessContainer,
                              OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE,
                              proc );
}

int OSSim_AddPost120msProcess(Procedure proc)
{
  return ossim_AddProcess(OSSim_Post120ms_ProcessContainer,
                          OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE,
                          proc);
}


const char* OSSim_GetLastTaskName(int* out_isStillIn)
{
  if( out_isStillIn != NULL )
    *out_isStillIn = OSSim_Data.TaskQuery.IsStillInTask;

  if( OSSim_Data.TaskQuery.LastTask != NULL )
    return OSSim_Data.TaskQuery.LastTask->TaskName;
  return "<no-last-task>";
}

#include "TRBShared_StringFunctions.h" ///< String_Equals

Procedure OSSim_GetProcessByName( const char* process_name )
{
  int i = 0;

  /// loop over all known tasks and search for the process.
  OsSimTask** pTaskTable = OSSim_DefaultTasks;

  while( !OSSim_TaskTable_IsEnd(pTaskTable, i) )
  {
    OsSimTask* task = pTaskTable[i];

    /// process names are only available in measurePoints struct.
    OSSim_ProcessMeasurePoint* process_pmp = task->pProcessMeasPoints;

    /// only measured tasks provide pmp, not all might have pmp.
    if( process_pmp != NULL )
    {
      int proc_id = 0;

      /// Loop through Processes
      while (task->pProcessTable[proc_id] != (PRC_PTR)0)
      {
        if( String_Equals( process_pmp[proc_id].Name
                         , process_name ) )
        {
          return task->pProcessTable[proc_id];
        }
        proc_id++;
      }/// while all processes in task.
    }/// if has pmp

    i++;
  }/// while all tasks.

  return NULL;
}
const char* OSSim_GetLastProcName(int* out_isStillIn)
{
  OSSim_ProcessMeasurePoint* process_pmp = NULL;

  if( OSSim_Data.TaskQuery.LastTask != NULL )
    process_pmp = OSSim_Data.TaskQuery.LastTask->pProcessMeasPoints;

  if( out_isStillIn != NULL )
    *out_isStillIn = OSSim_Data.TaskQuery.IsStillInTask;

  if( process_pmp != NULL )
    return process_pmp[OSSim_Data.TaskQuery.LastProcId].Name;

  return "<no-last-proc>";
}

CoreIdType GetCoreID(void)
{
  return OS_CORE_ID_MASTER;  // os interface
}

void Os_StartCore(CoreIdType CoreID, Os_StatusRefType Status)
{
  /// do noting
}

void Os_ShutdownAllCores(StatusType Error)
{
  /// do nothing
}

/// just simplification for easier testing
void OSSim_SetBaseOsRequested(void)
{
  OSSim_IsBaseOsForced = TRUE;
}

int OSSim_RunInMS_BaseOS(int milliSecondsToExecute)
{
  OSSim_ResetSystemData();

  OSSim_EventPost1ms = &OSSim_FixedCallback_Post1ms;
  OSSim_Data.MillisecondsLeftToExecute = milliSecondsToExecute;

  OSSim_StartOS(AppModeBaseOS);

  return OSSim_Data.MillisecondsLeftToExecute;
}

int OSSimHwDependent_Run_us(int microsecondsToExecute)
{
  /** OSSim is called, but told
    to only run, when hardware "allows".
    Performing resets is done here in SWTRunner,
    therefore OSSim need to return in case of
    requested resets.

    return is the remaining time.
  */

  OSSim_ResetSystemData();

  OSSim_Data.MicrosecondsLeftToExecute = microsecondsToExecute;

  #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
    /// switch HardwareModels to new mode, which is causing "OFF" supply dependent.
    HwEnv_EnableSupplyCircuitExecutionImpact(TRUE);
  #endif

  while( (OSSim_Data.MicrosecondsLeftToExecute > 0) && (!ResetHandler_IsResetRequested()))
  {
    int checkWakeSources = !OSSim_Data.InitFlags.InitCalled;
    ///< if softwareAlreadyRunning, HwEnv doesn't need to check "WakeSources".

    #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
      int isSwExecutionAllowed = HwEnv_IsSoftwareExecutionAllowed( checkWakeSources );
    #else
      int isSwExecutionAllowed = 1;
    #endif

    int wasSwResetOnly = ResetHandler_WasOnlySWReset_GetAndClear();

    if( isSwExecutionAllowed )
    {
      /// software + hardware running
      ///  .. run hardware ( HwModel_TimeTrigger() ) - already included in OSSim_StartOS()

      /// now we can simply execute software, hardware will be triggered as mentioned
      /// above and will set "ResetHandler-Requests" if something "software" execution relevant is changed.
      OSSim_AddPost0p5msProcess( &OSSim_RunMicrosecondsPost0p5msTask );

      OSSim_StartOS(OSDEFAULTAPPMODE);

      OSSim_RemovePost0p5msProcess( &OSSim_RunMicrosecondsPost0p5msTask );
    }
    else
    {
      #if (RBFS_TexecUsedIn == RBFS_TexecUsedIn_Sim)
        /// software not running
        uint32 next_hw_action_ms       = HwModel_GetTimeOfNextAction_ms();
        uint32 next_hw_action_delta_us = HWTime_GetDelta(HWTime_GetMS(), next_hw_action_ms) * 1000/*usec*/;

        /// only advance complete time, if really fitting into "requested" runtime.
        if( next_hw_action_delta_us <= OSSim_Data.MicrosecondsLeftToExecute )
        {
          HWTime_RunUntil_ms( next_hw_action_ms );
          OSSim_Data.MicrosecondsLeftToExecute -= next_hw_action_delta_us;
        }
        else /// no hardware action fitting into "requested" runtime.
        {
          HWTime_Run_us( OSSim_Data.MicrosecondsLeftToExecute );
          OSSim_Data.MicrosecondsLeftToExecute = 0;
        }

        HwModel_TimeTrigger();

        /// to have at least something on measurement
        /// Update 13-Feb-2018 : No value dumps during OFF-Time.
        // HSWSim_Measure500us_ForOSSim();
      #endif
    }
  }

  return OSSim_Data.MicrosecondsLeftToExecute;
}
