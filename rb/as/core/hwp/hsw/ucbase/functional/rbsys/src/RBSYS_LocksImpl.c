/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Lock implementation
 *
 * This module provides the spinlock and core-local interrupt lock implementation incl.
 * the corresponding lock monitoring functions.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "RBLCF_MemoryRemap.h"
#include "RB_MemoryBarrier.h"

/* Os stub for single core (Needed for Scalability Class SC3+4 OS)   */
#if((RBFS_MCORE == RBFS_MCORE_OFF) && (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES))
  #include "Os.h" //< OS_VOLATILE
#endif
#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #include "RBSYS_CoreInit.h"
#endif
//#include <assert.h>   -> Attention: Assert could not be used here due to call cycle


/* realized interfaces */
#include "RBSYS_LocksImpl.h"  // first include LocksImpl then ImplIntern!
#include "RBSYS_LocksImplIntern.h"
#include "RBSYS_Subsystem.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_LockTimeMonitoring,
                          RBFS_LockTimeMonitoring_Enabled,
                          RBFS_LockTimeMonitoring_Disabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

  /*
    ********** IMPORTANT *************
    **
    **   SuspendAllInterrupts are not allowed to be used in Gen9.3!!
    **   => not safe for Multi-Core systems => only the SYS lock API has to be used
    **
    ********** IMPORTANT *************
  */

  /* Os stub for single core (Needed for Scalability Class SC3+4 OS)   */
  #if((RBFS_MCORE == RBFS_MCORE_OFF) && (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES))
    OS_VOLATILE uint32 Os_DisableAllCount;
    OS_VOLATILE uint32 Os_SuspendAllCount;
    OS_VOLATILE uint32 Os_SuspendOSCount;
  #endif

  RBSECTION_START_LRAM0_BSS_CLEAR
  static RBSYS_coreintlock_t RBSYS_coreintlock_core0;
  #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
    static RBSYS_lockstats_t RBSYS_lockinfo_core0;
  #endif
  RBSECTION_END_LRAM0_BSS_CLEAR

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    RBSECTION_START_LRAM1_BSS_CLEAR
    static RBSYS_coreintlock_t RBSYS_coreintlock_core1;
    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      static RBSYS_lockstats_t RBSYS_lockinfo_core1;
    #endif
    RBSECTION_END_LRAM1_BSS_CLEAR
  #endif

  #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
    /*[[MEASUREMENT_TYPEDEF*/
    /*TYPE=RBSYS_lockstats_t*/
    /*NAME=RBSYS_lockinfo_core0*/
    /*MTEVENT=c_MT_Default_Task_x2*/
    /*]]MEASUREMENT_TYPEDEF*/

    /*[[MEASUREMENT_TYPEDEF*/
    /*TYPE=RBSYS_lockstats_t*/
    /*NAME=RBSYS_lockinfo_core1*/
    /*MTEVENT=c_MT_Default_Task_x2*/
    /*]]MEASUREMENT_TYPEDEF*/

    RBSYS_lockstats_t* const RBSYS_lockstatsinfo[RB_NUM_CORES] = {
                                                    &RBSYS_lockinfo_core0
                                                #if (RBFS_MCORE == RBFS_MCORE_ON)
                                                  , &RBSYS_lockinfo_core1
                                                #endif
                                                  };
  #endif


  RBSYS_coreintlock_t* const RBSYS_coreintlockinfo[RB_NUM_CORES] = {
                                                  &RBSYS_coreintlock_core0
                                              #if (RBFS_MCORE == RBFS_MCORE_ON)
                                                , &RBSYS_coreintlock_core1
                                              #endif
                                                };




  /* suspend and resume logic taken from OS lib */
  static inline void RBSYS_SuspendLocIntsIntern(void) {
    uint32 coreid = RBSYS_getCoreID();
    RBSYS_coreintlock_t* intlockinfo = RBSYS_coreintlockinfo[coreid];
    if (intlockinfo->suspend_cnt == 0)
    {
      unsigned int prev_imask;

      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        prev_imask = RBSYS_STSR(RBSYS_PMR_REGID, RBSYS_PMR_SELID);
        RBSYS_memory_changed();
        // PMR shall only be updated if Interrupts are disabled (see P1x UM "System Register Hazards")
        RBSYS_DI();
        RBSYS_LDSR(RBSYS_PMR_REGID, RBSYS_PMR_SELID, (unsigned int)0xFFFFu);
        RBSYS_EI();
        RBSYS_memory_changed();
      #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        prev_imask = RBSYS_STSR(RBSYS_PLMR_REGID, RBSYS_PLMR_SELID);
        RBSYS_LDSR(RBSYS_PLMR_REGID, RBSYS_PLMR_SELID, 0u);
      #elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        prev_imask = RBSYS_MRC(15,0,4,6,0) & 0xFFu; //< read ICC_PMR
        RBSYS_DI();
        RBSYS_MCR(15,0,0/* any interrupt */,4,6,0); //< mask all maskable interrupts (todo: am I masking NMIs as well?)
        RBSYS_DSB();
        RBSYS_EI();
        RBSYS_memory_changed(); //< todo: is this barrier required? DMB/DSB required?
      #else
        assert(0 && "Interrupt Locking is not supported for this uC family");
      #endif

      intlockinfo->suspend_prev_imask = prev_imask;
    }
    intlockinfo->suspend_cnt++;
  }

  static inline void RBSYS_ResumeLocIntsIntern(void) {
    uint32 coreid = RBSYS_getCoreID();
    RBSYS_coreintlock_t* intlockinfo = RBSYS_coreintlockinfo[coreid];
    intlockinfo->suspend_cnt--;
    if (intlockinfo->suspend_cnt == 0)
    {
      RBSYS_memory_changed();

      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        /* PMR shall only be updated if Interrupts are disabled -> garantueed by executing of RBSYS_SuspendLocIntsIntern
        * before (implementation taken over from RTAOS). */
        RBSYS_LDSR(RBSYS_PMR_REGID, RBSYS_PMR_SELID, (unsigned int)intlockinfo->suspend_prev_imask);
      #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_LDSR(RBSYS_PLMR_REGID, RBSYS_PLMR_SELID, (unsigned int)intlockinfo->suspend_prev_imask);
      #elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        RBSYS_MCR(15,0,(unsigned int)intlockinfo->suspend_prev_imask,4,6,0);
      #else
        assert(0 && "Interrupt Locking is not supported for this uC family");
      #endif

      #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
        RBSYS_SYNCI();
      #endif
      RBSYS_memory_changed();
    }
  }


  #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
    /* Reset core local interrupt lock counter
    *
    * Attention: Function only allowed to be called by tpsw framework in case of killing third party sw
    *
    * @param coreid   current core where interrupt lock counter will be cleared
    *
    * @return void
    */
    void RBSYS_ResetLocIntsCounter(uint32 coreid)
    {
      RBSYS_coreintlockinfo[coreid]->suspend_cnt = 0;
    }


    /* Reset lock counter
    *
    * Reset the lock only if the lock was taken by the current core, where the tpsw application
    * to be killed is still running.
    *
    * Attention: Function only allowed to be called by tpsw framework in case of killing third party sw.
    *
    * @param loc      global lock structure
    * @param coreid   must be the corresponding core id
    *
    * @return void
    */
    void RBSYS_ResetNestLocCounter(volatile lockstr_t* loc, uint32 coreid)
    {
      if(loc->core_cnt[coreid] != 0)
      {
        loc->core_cnt[coreid] = 0;
        loc->lock = 0;
        // no syncm here, as we anyhow kill inconsistently
      }
    }
  #endif

  /**
  * Suspend core local interrupt lock implementation
  *
  * Attention: Only core local interrupts are locked here, therefore no consistency across cores guaranteed.
  * So this is only allowed for special usecases, otherwise common lock must be used!
  */
  static inline void RBSYS_EnterCorelocalIntlock_impl(void)
  {
    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      uint32 lp = (uint32)RBSYS_getLinkPointer();
      unsigned int core_id = RBSYS_getCoreID();
      uint32 prev_cnt = RBSYS_getIntlockNestCnt(core_id);
    #endif

    RBSYS_SuspendLocIntsIntern();

    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      if (prev_cnt == 0)
      {
        RBSYS_lockstats_t* lockinfo = RBSYS_lockstatsinfo[core_id];
        lockinfo->tmp_locktime = RBSYS_getRealtimeTickCtr();
        lockinfo->tmp_lockadr = lp;
      }
    #endif
  }

  /**
  * Resume core local interrupt lock implementation
  */
  static inline void RBSYS_ExitCorelocalIntlock_impl(void)
  {
    #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
      unsigned int core_id = RBSYS_getCoreID();
      uint32 prev_cnt = RBSYS_getIntlockNestCnt(core_id);

      if (prev_cnt == 1)
      {
        RBSYS_lockstats_t* lockinfo = RBSYS_lockstatsinfo[core_id];
        uint32 new_time = RBSYS_getRealtimeTickCtr() - lockinfo->tmp_locktime;

        if (new_time > lockinfo->max_locktime)
        {
          lockinfo->max_locktime = new_time;
          lockinfo->max_lockadr = lockinfo->tmp_lockadr;
        }
      }
    #endif

    RBSYS_ResumeLocIntsIntern();
  }


  /** Map internal core local interrupt lock to real implementation without inline here to have one
  *  dedicated jump -> required for link pointer (=>RBSYS_getLinkPointer()) as debug data */
  __attribute__((noinline)) void RBSYS_EnterCorelocalIntlock_intern(void)
  {
    RBSYS_EnterCorelocalIntlock_impl();
  }

  __attribute__((noinline)) void RBSYS_ExitCorelocalIntlock_intern(void)
  {
    RBSYS_ExitCorelocalIntlock_impl();
  }


  #if (RBFS_MCORE == RBFS_MCORE_ON)

    // ToDo:
    // - global/common lock variable should be placed in a separate 32 byte section => other writes destroy the link, see Software User Manual
    // - ensure 32 byte alignment in case several nonest locks are used
    volatile lockstr_t RBSYS_common_lock;

    // Todo Unicon: RBSYS_common_lock should be placed in a separate 64bit section of CRAM/SYSRAM. Exclusive Monitors granularity is 8Bytes.

    static inline boolean RBSYS_LockGetIntern(volatile int* lockadr) {
      boolean successful = FALSE;
      #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
        // A type cast is needed as old GHS compiler versions do not support volatile qualifier in below intrinsics, see task 726910
        if (RBSYS_LDL_W(RBSYS_CAST2LDLSTC_TYPE(lockadr)) == 0) { // reads lock value & creates link, write to link if not already locked
          if (RBSYS_STC_W(1, RBSYS_CAST2LDLSTC_TYPE(lockadr)) != 0) { // returns 1 if link was still valid, 0 otherwise
            successful = TRUE;
          }
        }
      #else
        if(RBSYS_LDREX((const int*)lockadr) == 0){      //< if Lock is not acquired yet, generate entry in Monitor
          if(RBSYS_STREX(1, (int*)lockadr) == 0){       //< STREX returns 0 on success!
            successful = TRUE;
          }
        }
      #endif

      // removed below snooze instruction in case of unsuccessful lock to avoid further spinning
      // on this core in case of subsequent locks on the other core
      // if (!successful) {
      // RBSYS_snooze();
      // }

      RBSYS_memory_changed();
      RB_FullHardwareMemoryBarrier();
      RBSYS_memory_changed();

      return successful; // returns whether the lock was acquired successfully
    }

    static inline void RBSYS_LockRelIntern(volatile int* lockadr)
    {
      RBSYS_memory_changed();
      RB_FullHardwareMemoryBarrier(); //< ensure that all write accesses to the critical section are finished before signaling "SpinLock released"
      RBSYS_memory_changed();

      #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
        *lockadr = 0;
      #else
        *lockadr = 0;
        RBSYS_CLREX(); //< clear Monitor entry, todo: required? context change considered? 
        // -> not required as this will only clear the local monitor and the write to lockadr (STR instead of STREX) will automatically remove the exlusive access
      #endif
    }


    static void RBSYS_getLock(volatile lockstr_t* loc)
    {
      unsigned int core_id = RBSYS_getCoreID();

      if (loc->core_cnt[core_id] != 0)
      {
      }  // already got the lock -> self nesting (core_local)
      else
      {
        boolean lock_acquired;
        do
        {
          RBSYS_SuspendLocIntsIntern();
          lock_acquired = RBSYS_LockGetIntern(&loc->lock);
          if (lock_acquired == FALSE)
          {
            RBSYS_ResumeLocIntsIntern();
          }
        }while(lock_acquired == FALSE);
      }
      loc->core_cnt[core_id]++;
    }

    static void RBSYS_releaseLock(volatile lockstr_t* loc)
    {
      unsigned int core_id = RBSYS_getCoreID();

      loc->core_cnt[core_id]--;
      if (loc->core_cnt[core_id] == 0)
      {
        RBSYS_LockRelIntern(&loc->lock);
        RBSYS_ResumeLocIntsIntern();
      }
    }
  #endif  // (RBFS_MCORE == RBFS_MCORE_ON)




  /** Map common lock to real implementation without inline here to have one
  *  dedicated jump -> required for link pointer (=>RBSYS_getLinkPointer()) as debug data */

  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    /* single core interrupt lock */
    __attribute__((noinline)) void RBSYS_EnterCommonLock_intern(void)
    {
      RBSYS_EnterCorelocalIntlock_impl();
    }
  #else
    /* multi core common lock (includes core-specific interrupt lock) */
    __attribute__((noinline)) void RBSYS_EnterCommonLock_intern(void)
    {
      volatile lockstr_t* loc = &RBSYS_common_lock;

      #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
        uint32 lp = (uint32)RBSYS_getLinkPointer();
        uint32 prev_cnt = RBSYS_getLockNestCnt(loc);
      #endif

      RBSYS_getLock(loc);

      #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
        if (prev_cnt == 0)
        {
          RBSYS_lockstats_t* lockinfo = RBSYS_lockstatsinfo[RBSYS_getCoreID()];
          lockinfo->tmp_locktime = RBSYS_getRealtimeTickCtr();
          lockinfo->tmp_lockadr = lp;
        }
      #endif
    }
  #endif


  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    /* single core interrupt lock */
    __attribute__((noinline)) void RBSYS_ExitCommonLock_intern(void)
    {
      RBSYS_ExitCorelocalIntlock_impl();
    }
  #else
    /* multi core common lock (includes core-specific interrupt lock) */
    __attribute__((noinline)) void RBSYS_ExitCommonLock_intern(void)
    {
      volatile lockstr_t* loc = &RBSYS_common_lock;
      
      #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
        uint32 core_id = RBSYS_getCoreID();
        uint32 prev_cnt = RBSYS_getLockNestCnt_perCore(loc, core_id);

        if (prev_cnt == 1)
        {
          RBSYS_lockstats_t* lockinfo = RBSYS_lockstatsinfo[core_id];
          uint32 new_time = RBSYS_getRealtimeTickCtr() - lockinfo->tmp_locktime;

          if (new_time > lockinfo->max_locktime)
          {
            lockinfo->max_locktime = new_time;
            lockinfo->max_lockadr = lockinfo->tmp_lockadr;
          }
        }
      #endif

      RBSYS_releaseLock(loc);
    }
  #endif




  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    /* suspend single core interrupt lock */
    void RBSYS_EnterCommonLockSysfast_intern(void)
    {
      RBSYS_SuspendLocIntsIntern();
    }
  #else
    /* get multi core common lock (includes suspend core-specific interrupt lock) */
    void RBSYS_EnterCommonLockSysfast_intern(void)
    {
      volatile lockstr_t* loc = &RBSYS_common_lock;
      RBSYS_getLock(loc);
    }
  #endif


  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    /* resume single core interrupt lock */
    void RBSYS_ExitCommonLockSysfast_intern(void)
    {
      RBSYS_ResumeLocIntsIntern();
    }
  #else
    /* release multi core common lock (includes resume of core-specific interrupt lock) */
    void RBSYS_ExitCommonLockSysfast_intern(void)
    {
      volatile lockstr_t* loc = &RBSYS_common_lock;
      RBSYS_releaseLock(loc);
    }
  #endif




  /**
  * Suspend fast implementation of core local interrupt lock
  *
  * Attention: Only core local interrupts are locked here, therefore no consistency across cores guaranteed.
  * So this is only allowed for special usecases, otherwise common lock must be used!
  */
  void RBSYS_EnterCorelocalIntlockSysfast_intern(void)
  {
    RBSYS_SuspendLocIntsIntern();
  }


  /**
  * Resume fast implementation of core local interrupt lock
  */
  void RBSYS_ExitCorelocalIntlockSysfast_intern(void)
  {
    RBSYS_ResumeLocIntsIntern();
  }

/**
 * @brief Lock monitoring
 *
 * Lock monitoring contain core specific following checks:
 *  - unbalanced locks
 *  - maximum locktime
 *
 * Note: Process has to run on every core!
 *
 * @returns void
 */
void RBSYS_PRC_LockMonitoring(void)
{
  RBSYS_checkUnbalancedLock((uint32)&RBSYS_PRC_LockMonitoring);

  #if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
    RBSYS_checkLocktime();
  #endif
}


#if( RBFS_LockTimeMonitoring == RBFS_LockTimeMonitoring_Enabled )
  /**
  * @brief Reset longest lock time
  *
  * This function resets longest lock time and corresponding lock address.
  * It should be called only after init phase to ignore all locks during startup.
  * Refer Defect Fix : 753681.
  *
  * Note: Process has to run before the SPG_RBAPPLIF_TraceMT_CM_BOS_Init!
  * @returns void
  */
  void RBSYS_PRC_ResetMaxLockTime_Init(void)
  {
    int i;
    for (i=0; i<(RB_NUM_CORES); i++)
    {
      RBSYS_lockstatsinfo[i]->max_lockadr = 0;
      RBSYS_lockstatsinfo[i]->max_locktime = 0;
      RBSYS_lockstatsinfo[i]->tmp_lockadr = 0;
      RBSYS_lockstatsinfo[i]->tmp_locktime = 0;
    }
  }
#endif


/** @} */
/* End ingroup RBSYS */
