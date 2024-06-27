#ifndef RBSYS_TASKINFO_H__
#define RBSYS_TASKINFO_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Task counter and constants
 *
 * This interface provides relevant info from the dynamic framework like task counters,
 * task activation timestamps, slacktimes and system load.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_OsServices.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_ON,
                          RBFS_SysTask0p5ms_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysResettableSlackTimesSupport,
                          RBFS_SysResettableSlackTimesSupport_ON,
                          RBFS_SysResettableSlackTimesSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysFlxrTask,
                          RBFS_SysFlxrTask_ON,
                          RBFS_SysFlxrTask_OFF);


/*********************************************************************************/
/* task counters                                                                 */
/*********************************************************************************/
#if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
  RBMESG_DefineMESGType_u32(RBMESG_Task0p5msCnt_u32);
  RBMESG_DeclareMESG(RBMESG_Task0p5msCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_Task0p5msCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_Task0p5msCompletedCnt_u32);
#endif

RBMESG_DefineMESGType_u32(RBMESG_Task1msCnt_u32);
RBMESG_DeclareMESG(RBMESG_Task1msCnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_Task1msCompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_Task1msCompletedCnt_u32);

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1Cnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1Cnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1CompletedCnt_u32);

#if (RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON)
  RBMESG_DefineMESGType_u32(RBMESG_TaskFlexrayCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskFlexrayCnt_u32);
#endif

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1LowCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1LowCnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1LowCompletedCnt_u32);

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2Cnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2Cnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2CompletedCnt_u32);

#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2pCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2pCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2pCompletedCnt_u32);
#endif

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4Cnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4Cnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4CompletedCnt_u32);

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx8Cnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx8Cnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx8CompletedCnt_u32);

RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx24Cnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx24Cnt_u32);
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx24CompletedCnt_u32);

#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx200BackgroundCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx200BackgroundCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4pLowCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4pLowCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskEventCtrlExtPrio1Cnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskEventCtrlExtPrio1CompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskEventCtrlExtPrio2Cnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskEventCtrlExtPrio2CompletedCnt_u32);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1GuestCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx1GuestCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2GuestCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx2GuestCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4GuestCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx4GuestCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx10GuestCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx10GuestCompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx20GuestCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx20GuestCompletedCnt_u32);
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx10Cnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx10Cnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx10CompletedCnt_u32);

  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx20Cnt_u32);
  RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx20Cnt_u32);
  RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlx20CompletedCnt_u32);
#endif



/*********************************************************************************/
/* messages for first task activation                                            */
/*********************************************************************************/

/* export first 500us task start time stamp if 500us task is activated, otherwise 1ms time stamp*/
RBMESG_DefineMESGType_u32(RBMESG_Task1msFirstTickCtr);
RBMESG_DeclareMESG(RBMESG_Task1msFirstTickCtr);

/* export first x1 task start time stamp */
RBMESG_DefineMESGType_u32(RBMESG_TaskBaseCtrlFirstTickCtr);
RBMESG_DeclareMESG(RBMESG_TaskBaseCtrlFirstTickCtr);



/*********************************************************************************/
/* export the message cycle times - C_BaseCtrlTaskms_UL is set via config header */
/*********************************************************************************/
#define C_BaseCtrlTaskCycx1_UL  ((unsigned)(C_BaseCtrlTaskms_UL))
#define C_BaseCtrlTaskCycx2_UL  ((unsigned)(2*C_BaseCtrlTaskms_UL))
#define C_BaseCtrlTaskCycx4_UL  ((unsigned)(4*C_BaseCtrlTaskms_UL))
#define C_BaseCtrlTaskCycx8_UL  ((unsigned)(8*C_BaseCtrlTaskms_UL))
#define C_BaseCtrlTaskCycx24_UL ((unsigned)(24*C_BaseCtrlTaskms_UL))
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  #define C_BaseCtrlTaskCycx10_UL ((unsigned)(10*C_BaseCtrlTaskms_UL))
  #define C_BaseCtrlTaskCycx20_UL ((unsigned)(20*C_BaseCtrlTaskms_UL))
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
  #define C_BaseCtrlTaskCycx10_UL  ((unsigned)(10*C_BaseCtrlTaskms_UL))
  #define C_BaseCtrlTaskCycx20_UL  ((unsigned)(20*C_BaseCtrlTaskms_UL))
#endif



/**
 * @brief RBSYS_get_task_activation_ts
 *
 * @param [in] task  Specified task from type RBSYS_TaskType where corresponding timestamp is required
 *
 * @return last activation time of given task
 */
extern uint32 RBSYS_get_task_activation_ts(RBSYS_TaskType task);



/**
 * @brief RBSYS_getSlackTime
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24
 *
 * @note Shall be called within corresponding task cycle since values are updated accordingly
 *
 * @return slack time in timer ticks (see RBSYS_TIMERTICKS_PER_US)
 */
extern uint32 RBSYS_getSlackTime(RBSYS_TaskType task);



/**
 * @brief RBSYS_getSlackTimeMin
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24
 *
 * @return the minimal value of slack time in timer ticks (see RBSYS_TIMERTICKS_PER_US)
 */
extern uint32 RBSYS_getSlackTimeMin(RBSYS_TaskType task);

typedef enum{
  RBSYS_RuntimeType_NetCurrent,
  RBSYS_RuntimeType_NetMax,
  RBSYS_RuntimeType_GrossCurrent,
  RBSYS_RuntimeType_GrossMax
}RBSYS_RuntimeType_t;

/**
 * @brief RBSYS_getTaskRuntime
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24

 * @param [in] type  Specified Runtime Type from type RBSYS_RuntimeType_t
 *
 *        Following RBSYS_RuntimeTypes are available:
 *        - RBSYS_RuntimeType_NetCurrent
 *        - RBSYS_RuntimeType_NetMax
 *        - RBSYS_RuntimeType_GrossCurrent
 *        - RBSYS_RuntimeType_GrossMax
 *
 * @return the value of runtime in timer ticks (see RBSYS_TIMERTICKS_PER_US)
 */
extern uint32 RBSYS_getTaskRuntime(RBSYS_TaskType task, RBSYS_RuntimeType_t type);


/**
 * @brief RBSYS_getIsrRuntime
 *
 * @param [in] isr  Specified ISR from type RBSYS_IsrType
 *
 *        Following RBSYS_IsrType elements are agreed:
 *        - see RBSYS_IsrType_* inside RBSYS_OsServices.h

 * @param [in] type  Specified Runtime Type from type RBSYS_RuntimeType_t
 *
 *        Following RBSYS_RuntimeTypes are available:
 *        - RBSYS_RuntimeType_NetCurrent
 *        - RBSYS_RuntimeType_NetMax
 *        - RBSYS_RuntimeType_GrossCurrent
 *        - RBSYS_RuntimeType_GrossMax
 *
 * @return the value of runtime in timer ticks (see RBSYS_TIMERTICKS_PER_US)
 */
extern uint32 RBSYS_getIsrRuntime(RBSYS_ISRType isr, RBSYS_RuntimeType_t type);


#if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
/** ResettableSlackTimeMin Limitations:
  *   At the moment, a "Get and Reset ResettableSlackTimeMin"-Procedure is not sychronized to the
  *   ResettableSlackTimeMin-Provider. That means, you may lose a minimum SlackTime value when resetting the
  *   ResettableSlackTimeMin. -> See Interface description of RBSYS_clearResettableSlackTimeMin,
  *   RBSYS_clearAllResettableSlackTimesMin
  */

/**
 * @brief RBSYS_getResettableSlackTimeMin
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24
 *
 * @return the minimal value of resettable slack time in timer ticks (see RBSYS_TIMERTICKS_PER_US)
 */
extern uint32 RBSYS_getResettableSlackTimeMin( RBSYS_TaskType task );

/**
 * @brief RBSYS_getTimestampResettableSlackTimeMin
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24
 *
 * @return the timestamp (task counter) of the value given by RBSYS_getResettableSlackTimeMin
 */
extern uint32 RBSYS_getTimestampResettableSlackTimeMin( RBSYS_TaskType task );


/**
 * @brief RBSYS_clearResettableSlackTimeMin
 *
 * @param [in] task  Specified task from type RBSYS_TaskType
 *
 *        Following RBSYS_TaskType elements are agreed:
 *        - RBSYS_TaskType_Task0p5ms
 *        - RBSYS_TaskType_Task1ms
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1High
 *        - RBSYS_TaskType_TaskFlexray
 *        - RBSYS_TaskType_TaskBaseCtrlCycx1Low
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2
 *        - RBSYS_TaskType_TaskBaseCtrlCycx2p
 *        - RBSYS_TaskType_TaskBaseCtrlCycx4
 *        - RBSYS_TaskType_TaskBaseCtrlCycx8
 *        - RBSYS_TaskType_TaskBaseCtrlCycx24
 *
 *    Resets the resettable slack time min of the given task
 *
 *    Attention: Make sure, that you are sychronized to SlackTime-Provider (SYS) by calling RBSYS_clearResettableSlackTimeMin
 *      only for the Task, you are running in. Otherwise, you may lose ResettableSlackTimeMin values which can result in
 *      a lower SlackTimeMin compared to ResettableSlackTimeMin.
 *
 * @return void
 */
extern void   RBSYS_clearResettableSlackTimeMin( RBSYS_TaskType task );

/**
 * @brief RBSYS_clearAllResettableSlackTimesMin
 *
 *    Resets the resettable slack time min of ALL tasks
 *
 *    Attention: Because the SlackTime-Provider (SYS) is not sychronized to the SlackTime-User, you may lose
 *      ResettableSlackTimeMin values when calling RBSYS_clearAllResettableSlackTimesMin. That means, SlackTimeMin
 *      could be lower than ResettableSlackTimeMin.
 *
 * @return void
 */
extern void   RBSYS_clearAllResettableSlackTimesMin( void );
#endif


/**
 * @brief RBSYS_getSystemLoadCore0
 *
 * @returns system load of core 0 (65536 stands for 100% => range 0x0=0% till 0xffff->99.9985%)
 */
extern uint16 RBSYS_getSystemLoadCore0(void);



#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * @brief RBSYS_getSystemLoadCore1
   *
   * @returns system load of core 1 (65536 stands for 100% => range 0x0=0% till 0xffff->99.9985%)
   */
  extern uint16 RBSYS_getSystemLoadCore1(void);
#endif



/* Functions to indicate in which cycle of the calling task, a lower task was activated. This
   may only be called from the task implemented for. E.g.
   RBSYS_IsTaskxXActivedInThisxYCycle: returns whether a task of X cycle was activated together with the currently running
   Y cycle which implies X has not yet run because Y is of higher priority and the
   function may only be called from task Y.
   Note that these functions cannot be provided in a generic way for all task
   because x24 task counter ratio to other counters do not match
   after counter overflow because 24 is not a divider of UINT32_MAX.
*/

static inline boolean RBSYS_IsTaskx2ActivedInThisx1Cycle(void)
{
  /* Get Task x1 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);

  /* Task x2 starts with every even cycle of x1, but x1 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx1Cnt_u32-1) % 2) == 0);
}

static inline boolean RBSYS_IsTaskx4ActivedInThisx1Cycle(void)
{
  /* Get Task x1 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);

  /* Task x4 starts with every fourth cycle of x1, but x1 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx1Cnt_u32-1) % 4) == 0);
}

static inline boolean RBSYS_IsTaskx8ActivedInThisx1Cycle(void)
{
  /* Get Task x1 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx1Cnt_u32);

  /* Task x8 starts with every eight cycle of x1, but x1 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx1Cnt_u32-1) % 8) == 0);
}

/* Note that a x24 version of this function cannot be offered in this way because it is not true after x1 counter
   overflows: 24 is not a divisor of 2 power 32 */

static inline boolean RBSYS_IsTaskx4ActivedInThisx2Cycle(void)
{
  /* Get Task x2 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);

  /* Task x4 starts with every even cycle of x2, but x2 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx2Cnt_u32-1) % 2) == 0);
}

static inline boolean RBSYS_IsTaskx8ActivedInThisx2Cycle(void)
{
  /* Get Task x2 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx2Cnt_u32);

  /* Task x8 starts with every fourth cycle of x2, but x2 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx2Cnt_u32-1) % 4) == 0);
}

static inline boolean RBSYS_IsTaskx8ActivedInThisx4Cycle(void)
{
  /* Get Task x4 counter */
  RBMESG_DefineMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);
  RBMESG_RcvMESGDef(RBMESG_TaskBaseCtrlx4Cnt_u32);

  /* Task x8 starts with every even cycle of x4, but x4 counter is already counted up by 1 at beginning of x1 task */
  return (boolean)(((l_RBMESG_TaskBaseCtrlx4Cnt_u32-1) % 2) == 0);
}


/** Functions to get slack time from different task base control cycles.
 *  Shall be called within corresponding task cycle since values are updated accordingly.
 *  Returns slack time in timer ticks (see RBSYS_TIMERTICKS_PER_US).
 *
 *  Hint: Below functions are deprecated and must be replaced by generic API 'RBSYS_getSlackTime'
 */
static inline uint32 RBSYS_getSlackTimeTaskBaseCtrlCycx1Low(void)
{
  return RBSYS_getSlackTime(RBSYS_TaskType_TaskBaseCtrlCycx1Low);
}

static inline uint32 RBSYS_getSlackTimeTaskBaseCtrlCycx2(void)
{
  return RBSYS_getSlackTime(RBSYS_TaskType_TaskBaseCtrlCycx2);
}

static inline uint32 RBSYS_getSlackTimeTaskBaseCtrlCycx4(void)
{
  return RBSYS_getSlackTime(RBSYS_TaskType_TaskBaseCtrlCycx4);
}

static inline uint32 RBSYS_getSlackTimeTaskBaseCtrlCycx8(void)
{
  return RBSYS_getSlackTime(RBSYS_TaskType_TaskBaseCtrlCycx8);
}

static inline uint32 RBSYS_getSlackTimeTaskBaseCtrlCycx24(void)
{
  return RBSYS_getSlackTime(RBSYS_TaskType_TaskBaseCtrlCycx24);
}

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
