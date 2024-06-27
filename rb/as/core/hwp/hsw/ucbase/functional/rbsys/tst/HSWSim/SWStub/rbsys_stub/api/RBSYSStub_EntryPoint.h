#ifndef RBSYSSTUB_ENTRYPOINT_H__
#define RBSYSSTUB_ENTRYPOINT_H__

#include "HSim_Global.h"
#include "RBSYS_TaskInfo.h"
#include "RBSYS_SystemTimer.h" ///< for SYSSim_TickCtr
#include "Os.h"

#define RBSYSSTUB_API_LEVEL 3
///< v3: 24-Apr-2024  - RBSYSStub_Get500usecCnt_ref()
///< v2: 14-Mar-2022  - OSSim_GetProcessByName()
///< v1: 25-Sept-2020 - SYSStub now in hsw.core and not updated with hsw.tools
///<                    API-Level from now required.

///<Enum to keep track of the defined task patterns
///<Must be equal to the enum defined in TEXEC_TestApi.h
typedef enum OSSim_TaskPattern
{
  OSSim_TaskPattern_Default = 0,
  OSSim_TaskPattern_60PJitter,
  OSSim_TaskPattern_80PJitter,
  OSSim_TaskPattern_100PJitter,

  /// have to be last element
  OSSim_TaskPattern_NumberOfDefinedTaskPatterns

}OSSim_TaskPattern;

/// @brief starts the task system
extern void RBSYSStub_StartupPreOSStart(void);

/// @todo move to OSStub_EntryPoint.h
/// known modes:
/// - AppModeBaseOS
/// - OSDEFAULTAPPMODE
extern void OSSim_StartOS(AppModeType mode);
/// @brief Allows texec to call only PDM relevant task (e.g. idle task)
/// reason: faster shutdown of software.
extern void OSSim2Texec_RescuePDMStuff(void);
/// @brief Run Init-Task only. If already executed nothing will happen.
/// @return always 0, not used currently.
extern int OSSim_RunInitTask(AppModeType mode);

/// @brief is aborting simulation after next 120ms slice.
/// If an "immediate" abort is necessary, overwrite the ProcessExecuter...
extern int OSSim_AbortProcessing;

/** @brief To be used by SWTEST, to run a specified amount of time.

  Function will first return, if time is elapsed or see below.

  For resets, while OS is nevertheless stopped, use TEXEC_HwReset and TeReset
  functions.

  @param millsec amount of time to run the simulated OS:
        @note if millsec is "0" or smaller (negative). OSSim will still run
              post next 1ms-Task and will exit afterwards.
              There is no protection for zero or negative inputs so far.

  @return
  If a hardware/software reset was requested during execution.
  The function will return the remaining millsecs to be executed,
  after performing the reset.

  If millsec elapsed completely function returns 0.

*/
extern int OSSim_RunInMS(int millsec);

/** @brief Will select the mentioned Task-Pattern from the list of defined TaskPatterns
 *  @param TaskPattern - Will Select the defined task patterns from below
 *          0 - SWT_OsTaskPattern_Default
 *          1 - SWT_OsTaskPattern_60PJitter
 *          2 - SWT_OsTaskPattern_80PJitter
 *          3 - SWT_OsTaskPattern_100PJitter */
extern void OSSim_SelectTaskPattern(OSSim_TaskPattern TaskPattern);

/** like OSSim_RunInMS, but with BaseOS task-table. */
extern int OSSim_RunInMS_BaseOS(int millsec);

/// just simplification for easier testing
extern void OSSim_SetBaseOsRequested(void);

/** Run function, which checks HW, whether software "may run" and consumes time.

  If resets need to be performed, this function will return
  and give the remaining time as return value.
  [Resets will happen outside this function, HW-Reset, SW-Reset etc.]

  If SW is not able to execute
  (supply insufficient or no wake source to wake-up)
  function will also/have to return "0" remaining time.
  [upper instance validates that at least a minimal time fraction
   is always consumed by this function]
*/
extern int OSSimHwDependent_Run_us(int usec);

/** @brief To be used by SWT, to run a specified amount of time.

  Function is similar to RunInMS, but RunInMS works per default
  with 1ms-TaskCounter.

  @return Similar to RunInMS. */
extern int OSSim_RunTask(uint32* pTaskCounter, int times);

/** @brief Executes the given task exactly once.

  @note In opposite to OSSim_RunTask() "other" tasks, WILL NOT be executed.
        Only the given task is scheduled.
        Target is to allow to cause some "different" task order than the
        "default one".

  @return FALSE : If software is not getting executed because of:
    - pTaskCounter invalid
    - Process-Abort-Handler is active (cannot be used at same time, currently)
    - software may not execute due to undervoltage/hardware sleep etc.
*/
extern int OSSim_ExecuteSingleTaskOnce( uint32* pTaskCounter );

/** @brief Executes tasks until specified task is matched and returns.

  @param shallStopBefore : TRUE  = Stops before task is executed.
                           FALSE = Stops after task is executed.

  @return FALSE : see reasons at OSSim_ExecuteSingleTaskOnce().
*/
extern int OSSim_RunTillTaskBorder( uint32* pTaskCounter, int shallStopBefore );

/** @brief Tells whether all Init-Stages are completed.

    That also means, that every following call to StartOS() will just
    run periodic tasks and not init stuff anymore.

    Example: PrePlantCheck, Init-Task, SWStub-Init etc.
*/
extern int OSSim_IsInitCompleted( void );

#include "OSStub_Procedure.h" ///< for Procedure-type.

/// @brief OSSim event type
/// @return Usually "OSSim_AbortProcessing" -> 0 means continue processing, !0 means abort processing.
///         Allows to stop OS simulation in event callback/handler.
typedef int   (*OSSimEventCallback)   (void);
typedef void  (*OSSimProcessExecuter) (Procedure);

/**< can be overwritten for special actions at this point in time. */
extern OSSimEventCallback   OSSim_EventPost500us;
extern OSSimEventCallback   OSSim_EventPre1ms;
extern OSSimEventCallback   OSSim_EventPost120ms;

/** @brief inject on "callbacks" before/after a process is called.
  This ProcessExecuter also then have the task to call the process itself.

  @note Current design: Will be automatically reset in case of SW-Resets.
*/
extern void OSSim_SetProcessExecuter(OSSimProcessExecuter executer);
/** @brief Resets a formerly set OSSimProcessExecuter.
*/
extern void OSSim_ResetProcessExecuter(void);
/** @brief Only resets ProcessExecutor, if it is the given one.
  @return 0 = nothing to reset / 1 = exec matched / 2 = another executer.
*/
extern int OSSim_ResetProcessExecuterThis(OSSimProcessExecuter exec);
/** @brief Returns current executor or NULL if not set.

  Use-Case: Check whether another ProcessExecuter is registered.
*/
extern OSSimProcessExecuter OSSim_GetProcessExecuter(void);

//#if(RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON) // always needed in HSWSim
  /** @brief Adds this procedure to dynamic process list of post-0p5ms.
    @return TRUE success.
  */
  extern int OSSim_AddPost0p5msProcess(Procedure proc);

  // is used by rbasSE_SetupOperatingSystem independent of RBFS_SysTask0p5ms
  /** @brief Adds this procedure and ensure that it is last in execution. */
  extern int OSSim_AddPost0p5msLastProcess(Procedure proc);

  /** @brief Removes this procedure from dynamic process list of post-0p5ms.
      @return TRUE success.
  */
  extern int OSSim_RemovePost0p5msProcess(Procedure proc);
//#endif

/** @brief Like OSSim_AddPost0p5msProcess() and Remove() but for 120ms.
  @{ */
extern int OSSim_AddPost120msProcess(Procedure proc)   ;
extern int OSSim_RemovePost120msProcess(Procedure proc);
  /** @} */

/** @brief Activates an abortion on process-execution level.
  Usually the aborts are done on Task-Level.
  Currently this is only supported if using an own/external "ProcessExecuter",
  therefore the "PrePost" information is required to know, whether "own/external"
  ProcessExecuter needs to be called again (pre) with same process or not (post).
*/
extern void OSSim_ActivateProcAbort(int wasPreProcessCall);

/** @brief Extends the times of Idle task calls by given timesFasterThanUsual.
  A value of "0" or "1" will reset to default / usual idle task calls.
*/
extern void OSSim_SpeedUpIdleTask(int timesFasterThanUsual);

/** @brief Returns current timesFasterThanUsual of IdleTask.
  Interface for testing. */
extern int OSSim_GetIdleTaskSpeed(void);

/** @brief Returns "not zero" if known, and zero if known.

  @return 1.000.000 + (int) RBSYS_TaskType found in.
*/
extern int OSSim_IsKnownProcess(Procedure proc) ;

/** @brief Return "process pointer" if process found, else NULL.
*/
extern Procedure OSSim_GetProcessByName( const char* process_name );

/** @brief Returns Task and Process as strings.

  @param out_isStillIn: tells whether only Task/Proc-Start was recorded
                        or whether Task/Proc-End was already recorded.
@{ */
extern const char* OSSim_GetLastTaskName(int* out_isStillIn);
extern const char* OSSim_GetLastProcName(int* out_isStillIn);
/** @} */

extern uint32 RBSYSStub_GetMS(void);
extern uint32 RBSYSStub_GetUS(void);

/** @brief 500usec-Counter reference.
  Reason: 500usec-Task is not always available in Task-Scheme.
          But OSSim/SYSStub still executes 500usec time quantities
          to reduce variation.
  Use Case: SWT uses this to detect if a 500usec slot is elapsed.
*/
extern uint32* RBSYSStub_Get500usecCnt_ref(void);

/** @brief Gets current SYSStub ticks, without any pseudo increments.
  @attention multiple calls to this function therefore do not change the
              ticks value (pseudo increments). This will only happen with
              official RBSYS-ticks APIs. */
extern uint32 RBSYSStub_GetTicks(void);

extern uint32 RBSYSStub_GetTickDeltaAsUsec(uint32 delta);


typedef struct{
  const char* Name;
  void*       MeasureReference;
}OSSim_ProcessMeasurePoint;
#define OSSIM_PROC_MEAS_POINT_INIT(name)  {(#name),(NULL)}
#define OSSIM_PROC_MEAS_POINT_LIST_END    {(NULL),(NULL)}

extern OSSim_ProcessMeasurePoint   c_PrePlantCheck_pmp[];
extern OSSim_ProcessMeasurePoint   c_TaskInit_pmp[];
extern OSSim_ProcessMeasurePoint   c_TaskIdle_pmp[];
#if(RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  extern OSSim_ProcessMeasurePoint   c_Task0p5ms_pmp[];
#endif
extern OSSim_ProcessMeasurePoint   c_Task1ms_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx1h_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx1l_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx2_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx4_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx8_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx24_pmp[];

#if(RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  extern OSSim_ProcessMeasurePoint   c_FlexrayTask_pmp[];
#endif

#if(RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  extern OSSim_ProcessMeasurePoint   c_Taskx1Guest_pmp[];
  extern OSSim_ProcessMeasurePoint   c_Taskx2Guest_pmp[];
  extern OSSim_ProcessMeasurePoint   c_Taskx4Guest_pmp[];
  extern OSSim_ProcessMeasurePoint   c_Taskx10Guest_pmp[];
  extern OSSim_ProcessMeasurePoint   c_Taskx20Guest_pmp[];
#endif

extern OSSim_ProcessMeasurePoint   c_TaskInitBaseOS_pmp[];
#if(RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  extern OSSim_ProcessMeasurePoint   c_Task0p5msBaseOS_pmp[];
#endif
extern OSSim_ProcessMeasurePoint   c_Task1msBaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx1hBaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx1lBaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx2BaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx4BaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx8BaseOS_pmp[];
extern OSSim_ProcessMeasurePoint   c_Taskx24BaseOS_pmp[];

#if(RBFS_MCORE == RBFS_MCORE_ON)
  extern OSSim_ProcessMeasurePoint   c_Taskx2p_pmp[];
  extern OSSim_ProcessMeasurePoint   c_Taskx2pBaseOS_pmp[];
#endif


#endif