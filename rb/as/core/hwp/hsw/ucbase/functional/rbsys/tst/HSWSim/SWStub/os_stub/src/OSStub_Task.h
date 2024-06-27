#ifndef OSSTUB_TASK_H__
#define OSSTUB_TASK_H__

/**
 * @ingroup OSStub
 * @{
 *
 * @file OSStub_Task.h
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "OSStub_Os.h"


/*******************************************************
* Macros, Structs and variable
********************************************************/

typedef struct OSSim_TaskBorderStopper_Params
{
  OsSimTask* StopAtTask;
  int        StopBefore;
} OSSim_TaskBorderStopper_Params;

typedef struct OSSim_TaskBorderStopper_Feedback
{
  OsSimTask* StoppedAtTask;
  int        StoppedBefore;
  int        Remaining_ms;
} OSSim_TaskBorderStopper_Feedback;

typedef struct OSSim_TaskBorderStopper
{
  int IsActive; ///< general active flag.
  OSSim_TaskBorderStopper_Params    Parameter;
  OSSim_TaskBorderStopper_Feedback  Feedback;
} OSSim_TaskBorderStopper;

extern OSSim_TaskBorderStopper TaskBorderStopper;

#define OSSIM_PROC_MEAS_POINT_INIT(name)  {(#name),(NULL)}
#define OSSIM_PROC_MEAS_POINT_LIST_END    {(NULL),(NULL)}

// Defines the initialization process of the Operation System
// <COMPONENT>_RB_Config.h
extern PRC_PTR OSSim_Initialize[];

/*******************************************************
* Definition of Functions
********************************************************/

/// this is a list of task, if iterated through it it realizes a "valid"
/// scheduling. Same tasks will appear multiple times.
/// Creates a full 120 millisecond scheduling/slot.
extern OsSimTask* OSSim_DefaultExecTable[];
/// this just lists all known tasks.
/// each task appears just "once".
extern OsSimTask* OSSim_DefaultTasks[];

extern OsSimTask OSSim_TaskInitBaseOS;
extern OsSimTask OSSim_TaskInit;
extern OsSimTask OSSim_TaskIdle;
extern OsSimTask OSSim_TaskPreReprogCheck;
extern OsSimTask OSSim_TaskPrePlantCheck;
extern OsSimTask OSSim_TaskInitializeSystem;

#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_OFF)
  /// [ossim_private_500usec_execution]
  extern OsSimTask OSSim_Task0p5ms_priv;
#endif

extern void OSSim_SelectTaskPattern(OSSim_TaskPattern TaskPattern);

/// this will replace the "process-table" within the task.
/// it will not replace the "task" itself within the Task-Table!
extern void OSSim_ReplaceTasksByBaseOsTasks(OsSimTask* pExecTable[]);

/// common helper to easily identify end of table.
/// @note will only work if "i" is used in a loop.
///       will NOT work if you just give any huge number for "i".
extern int OSSim_TaskTable_IsEnd(OsSimTask* pTable[], int i);

extern void OSSim_StopTask_StopOS(OsSimTask* task, int stoppedBefore, int* abortProcessing);

extern int OSSim_StopTask_CheckAndHandlePre(OsSimTask* task, int* abortProcessing);

extern void OSSim_StopTask_CheckAndHandlePost(OsSimTask* task, int* abortProcessing);

extern int OSSim_RunTillTaskBorder(uint32* pTaskCounter, int shallStopBefore);

#endif