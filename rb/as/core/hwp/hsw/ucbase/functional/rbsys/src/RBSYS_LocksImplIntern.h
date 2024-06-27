#ifndef RBSYS_LOCKSIMPLINTERN_H__
#define RBSYS_LOCKSIMPLINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Lock implementation
 *
 * This interface provides lock structure definitions together with lock related helper functions.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

#include "RBSYS_CpuInfo.h"
#include "RBSYS_SystemTimer.h"
#include "Monitorings/RBSYS_ErrorHooks.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_LockTimeMonitoring,
                          RBFS_LockTimeMonitoring_Enabled,
                          RBFS_LockTimeMonitoring_Disabled);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

/* types of locks */
typedef enum {
  RBSYS_LockType_Local = 0,
  RBSYS_LockType_Common
}RBSYS_locktype_t;


/* common lock structure */
typedef volatile struct {
  int lock;  // global lock variable
  uint32 core_cnt[RB_NUM_CORES];
}lockstr_t;


/* core-specific interrupt lock structure*/
typedef struct
{
  uint32 suspend_cnt;
  uint32 suspend_prev_imask;
}RBSYS_coreintlock_t;


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  typedef struct  /*TOOL_SCAN*/
  {
    uint32 tmp_locktime;
    uint32 tmp_lockadr;
    uint32 max_locktime;
    uint32 max_lockadr;
  }RBSYS_lockstats_t;

  extern RBSYS_lockstats_t* const RBSYS_lockstatsinfo[RB_NUM_CORES];
#endif

extern RBSYS_coreintlock_t* const RBSYS_coreintlockinfo[RB_NUM_CORES];


extern void RBSYS_ResetMaxLock(void);

#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern volatile lockstr_t RBSYS_common_lock;
#endif

#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
  extern void RBSYS_ResetLocIntsCounter(uint32 coreid);
  extern void RBSYS_ResetNestLocCounter(volatile lockstr_t* loc, uint32 coreid);
#endif

/**
* @brief RBSYS_getCoreLocIntlockNestCnt
*
* @returns core local interrupt nesting counter: only for internal RBSYS usage
*/
static inline uint32 RBSYS_getCoreLocIntlockNestCnt(void)
{
  return RBSYS_coreintlockinfo[RBSYS_getCoreID()]->suspend_cnt;
}

/**
* Optimized internal API to get core local interrupt nesting counter
* in case core id already available.
*
* @param [in] coreid   must be the corresponding core id
*
* @returns core local interrupt nesting counter: only for internal RBSYS usage
*/
static inline uint32 RBSYS_getIntlockNestCnt(uint32 coreid)
{
  return RBSYS_coreintlockinfo[coreid]->suspend_cnt;
}


#if (RBFS_MCORE == RBFS_MCORE_ON)

  /**
  * @brief RBSYS_getLockNestCnt
  *
  * @param [in] loc  global lock structure
  *
  * @returns lock specific nesting counter: only for internal RBSYS usage
  */
  static inline uint32 RBSYS_getLockNestCnt(const lockstr_t* loc)
  {
    return loc->core_cnt[RBSYS_getCoreID()];
  }

  /**
  * Optimized internal API to get lock specific nesting counter
  * in case core id already available.
  *
  * @param [in] loc      global lock structure
  * @param [in] coreid   must be the corresponding core id
  *
  * @returns lock specific nesting counter: only for internal RBSYS usage
  */
  static inline uint32 RBSYS_getLockNestCnt_perCore(const lockstr_t* loc, uint32 coreid)
  {
    return loc->core_cnt[coreid];
  }

#endif


/**
* This function will check core specific for unbalanced locks.
* Locks must be released outside any process, which means core specific suspend_cnt and
* core specific lock nesting counter must be 0.
*
* @return void
*/
static inline void RBSYS_checkUnbalancedLock(uint32 adr)
{
  uint32 local_nest_cnt = RBSYS_getCoreLocIntlockNestCnt();
  uint32 debug_nest_cnt = local_nest_cnt;
  RBSYS_locktype_t lock_type = RBSYS_LockType_Local;
  uint32 core_id = RBSYS_getCoreID();

#if (RBFS_MCORE == RBFS_MCORE_ON)
  uint32 common_nest_cnt = RBSYS_getLockNestCnt(&RBSYS_common_lock);

  if ((local_nest_cnt != 0) || (common_nest_cnt != 0))
  {
    if(common_nest_cnt != 0)
    {
      lock_type = RBSYS_LockType_Common;
      debug_nest_cnt = common_nest_cnt;
    }
#else
  if (local_nest_cnt != 0)
  {
#endif
    // lock_type is casted to uint32 to be able to mask and shift its value
    RBSYS_setSYSErrorHook(RBSYS_Error_InvalidLockNesting, ( ((debug_nest_cnt    & 0xFu) << 28)
                                                          | (((uint32)lock_type & 0x3u) << 26)
                                                          | ((core_id           & 0x3u) << 24)
                                                          | ( adr & 0x00FFFFFFu)));   // unbalanced lock
  }
}


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  /**
  * This function will check core specific the maximum locktime.
  *
  * @return void
  */
  static inline void RBSYS_checkLocktime(void)
  {
    uint32 locktime = RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_locktime;

    if (locktime > RBSYS_convertUsecToTimerTicks(RBSYS_MAX_LOCKTIME_US))
    {
      RBSYS_setSYSErrorHook(RBSYS_Error_LockTooLong, RBSYS_lockstatsinfo[RBSYS_getCoreID()]->max_lockadr);  // too long locktime
    }
  }
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
