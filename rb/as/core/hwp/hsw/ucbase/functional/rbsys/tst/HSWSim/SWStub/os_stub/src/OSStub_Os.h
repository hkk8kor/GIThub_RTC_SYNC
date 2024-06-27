#ifndef OSSTUB_OS_H__
#define OSSTUB_OS_H__

/**
 * @ingroup RBSYSStub
 * @{
 *
 * @file OSStub_Os.h
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "OSStub_Os_Config.h"

#define OSSIM_MAX_DYNAMIC_PROCESS_LIST_SIZE 10 /// extend if required

extern uint8 RBAPLPLANT_AsicPlantMode_u8;
extern int OSSim_AbortProcessing;

#if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_OFF )
  extern uint32 ossim_priv_500usec_cnt;
#endif

/*******************************************************
* Definition of Structs and Enums and typedefs
********************************************************/

typedef struct OSSim_PseudoTickCounter_t
{
  int IsInitialized;

  uint32 PseudoIncrement_1_ticks;
  uint32 PseudoIncrement_SlowDown_ticks;

  uint32 SlowDownBorder_ticks;

  uint32 Window_ticks;

  uint32 InitTaskOffset_ticks;
  int    InitTaskOffset_IsSet;

} OSSim_PseudoTickCounter_t;

/// The OSSim internal definition of a task.
typedef struct OsSimTask
{
  const PRC_PTR*                      pProcessTable;
  OSSim_ProcessMeasurePoint*          pProcessMeasPoints;
  uint32*                             pTaskCounter;
  RBSYS_TaskType                      rbsysTaskType;
  const char*                         TaskName;
  void*                               pTimeMeasureReference;

  OSSimEventCallback* pPreCB;
  OSSimEventCallback* pPostCB;

  int IgnoreOnBaseOsReplace;///< Defines that the task has no BaseOS
  ///< replacement.

  int SkipCounter; ///< always zero - except single tasks shall be executed
  ///< Then counter reflects number of "out-of-default-order" task executions.
  ///< and OSSim will skip the executions and reduce the SkipCounter for
  ///< following single appearances of task in ossim_DefaultExecTable.

} OsSimTask;

typedef struct OSSim_InitFlags
{
  /// Order should be aligned with original FSWStartup (23-Apr-2021)
  int EclkIsSetup;                 /* step 0 */
  int PreReprogCheckCompleted;     /* step 1 */
  int PrePlantCheckCompleted;      /* step 2 */
  int SWStubPreTaskInit;           /* step 3 */
  int InitTaskCompleted;           /* step 4 */
  int SWStubPostTaskInit;          /* step 5 */

  int InitCompleted;          //< set, if complete Init is done.
  int InitCalled;            //< set, if Init is called at least once.
} OSSim_InitFlags;

typedef struct OSSim_TaskQuery
{
  uint32                    CounterEnd;
  uint32*                   TaskCounterRef;
  OsSimTask*                pOSSimCurrentTask;
  TaskType                  CurrentTaskType;
  /// storage of currentTask for queries via Os_GetTaskID()
  OsSimTask*                LastTask;
  unsigned int              LastProcId;
  int                       IsStillInTask;
  int                       IsStillInProc;
} OSSim_TaskQuery;

typedef struct OSSim_SystemData
{
  int                       MillisecondsLeftToExecute; //< variable storing the value of remaining msecs to be executed.
  int                       MicrosecondsLeftToExecute; //< variable storing the value of remaining usecs to be executed.
  int                       Instantiated; // << defines whether the operating system was instantiated
  int                       ExecNextCounter;
  OSSim_InitFlags           InitFlags;
  OSSim_TaskQuery           TaskQuery;
} OSSim_SystemData;


/*******************************************************
* Definition of CallBacks
********************************************************/

// Interfaces that should be provided on Component Side
//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  extern OSSimEventCallback OSSim_FixedEvent_Post0p5ms;
//#endif
extern OSSimEventCallback OSSim_FixedEvent_Post120ms;
extern OSSimEventCallback OSSim_FixedEvent_Post1ms;
extern OSSimEventCallback OSSim_FixedEvent_PostTaskIdle;
extern OSSimEventCallback OSSim_FixedEvent_PreTaskIdle;
extern OSSimEventCallback OSSim_DummyCallBackLocation;

// Pre and Post events
extern OSSimEventCallback OSSim_EventPre1ms;
extern OSSimEventCallback OSSim_EventPost1ms;
extern OSSimEventCallback OSSim_EventPost120ms;
extern OSSimEventCallback OSSim_EventPostEachTask;

extern StatusType OSSim_GetTaskID(TaskRefType TaskID);

extern void OSSim_DefaultProcedureExecuter(Procedure proc); 

#endif