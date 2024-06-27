/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - lock handling
 *
 * This module provides the lock handling (common lock and core-local interrupt lock) for the TPSW framework
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* realized interfaces */
#include "RBTPSW_TPSWCapsule.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_LocksImpl.h"
#include "RBSYS_LocksImplIntern.h"
#include "Os.h"
#include "RBSYS_CpuInfo.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);


#if (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF)


#if (RBFS_MCORE == RBFS_MCORE_OFF)
lockstr_t RBTPSW_SingleCoreDummyCommonLock;
#endif



/************************************************************************/
/** Lock private APIs                                                  **/
/** RBTPSW_EnterLock_intern() / RBTPSW_ExitLock_intern() must not      **/
/** be used.                                                           **/
/** In the single core case, all locks will be handled as int locks.   **/
/************************************************************************/
#if(RBFS_MCORE == RBFS_MCORE_ON)
static inline void RBTPSW_EnterLock_intern(const lockstr_t* lock)
{
    if (lock == RBTPSW_LOCKCONFIG_COMMONLOCK_PRV)
    {
        RBSYS_SchM_Enter_GlobLock();
    }
    else
    {
        // Todo:
        //   - No nest lock call here
        //   - Plausi for common lock/nonest lock. --> calling order.
        // RBSYS_EnterNonestLock(lock);
    }
}

static inline void RBTPSW_ExitLock_intern(const lockstr_t* lock)
{
    if (lock == RBTPSW_LOCKCONFIG_COMMONLOCK_PRV)
    {
        RBSYS_SchM_Exit_GlobLock();
    }
    else
    {
        // todo: No nest lock call here
        // RBSYS_ExitNonestLock(lock);
    }
}
#endif




/********************************************************************/
/** CORE LOCAL INTERRUPT LOCK                                      **/
/** RBTPSW_EnterCorelocalIntlock() / RBTPSW_ExitCorelocalIntlock() **/
/********************************************************************/
void RBTPSW_EnterCorelocalIntlock(void)
{
    rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;

    /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation,
     * so no code before this allowed!
     * needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      PrevMode = RBTPSW_SetTrusted();
    }

    #if(RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    {
      CoreIdType CoreId;
      boolean enabled;
      boolean isSupressed;

      /* use RBSYS API to get core ID, this is possible, as we are already in trusted mode*/
      CoreId = (CoreIdType) RBSYS_getCoreID();

      /* if the timer is currently enabled (SetTimeLimit has been called) and supression flag  *
       * is not set (timer interrupt is not supressed) then the lock must not be entered, as   *
       * the timer interrupt must be able to trigger its ISR. This check also allows a non     *
       * time-protected callee to hold locks, even if its caller is time-protected.            */

      enabled = RBTPSW_Context[CoreId].timing.enabled;
      isSupressed = RBTPSW_Context[CoreId].timing.supprFlag;

      if (enabled && !isSupressed) {
          /* force aborting TPSW */
          RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCK_WITH_TP, RBTPSW_Context[CoreId].fncall, CoreId);
          /* no matter in which mode this function was entered, locks are not allowed in a time protected TPSW, so kill the TPSW with an MPU error */
          RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
          RBTPSW_DummyTrusted = 0xDEADBEEFU;
          RBSYS_SYNCM();
      }
    }

    #endif

    RBSYS_SchM_Enter_CoreLocalLock();

    /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
      RBTPSW_SetTrust(PrevMode);
    }
}

void RBTPSW_ExitCorelocalIntlock(void)
{
    rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;
    CoreIdType CoreId;

    /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation,
     * so no code before this allowed!
     * needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      PrevMode = RBTPSW_SetTrusted();
    }

    /* use RBSYS API to get core ID, this is possible, as we are already in trusted mode*/
    CoreId = (CoreIdType) RBSYS_getCoreID();

    /* if the function was called from user mode, check that exit lock was not called more often than enter lock*/
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
        if (RBSYS_getIntlockNestCnt(CoreId) == 0)
        {
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCKACTIVE, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:          */
            /*  - int lock counter will be reset in exception handler    */
            /*  - OS resets PSW.ID bit after long jump in CallTrustedFn  */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }
    }
    RBSYS_SchM_Exit_CoreLocalLock();

    /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
      RBTPSW_SetTrust(PrevMode);
    }
}



/********************************************************************/
/** COMMON LOCK or NONEST LOCK                                     **/
/** RBTPSW_EnterLock() / RBTPSW_Exit()                             **/
/** Only locks from the TPSW app specific lock table are allowed.  **/
/********************************************************************/
void RBTPSW_EnterLock(const lockstr_t* lock)
{
    rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;
    CoreIdType CoreId;

    /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation,
     * so no code before this allowed!
     * needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      PrevMode = RBTPSW_SetTrusted();
    }

    /* use RBSYS API to get core ID, this is possible, as we are already in trusted mode*/
    CoreId = (CoreIdType) RBSYS_getCoreID();

    #if(RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    {
      boolean enabled;
      boolean isSupressed;

      /* if the timer is currently enabled (SetTimeLimit has been called) and supression flag  *
       * is not set (timer interrupt is not supressed) then the lock must not be entered, as   *
       * the timer interrupt must be able to trigger its ISR. This check also allows a non     *
       * time-protected callee to hold locks, even if its caller is time-protected.            */
      enabled = RBTPSW_Context[CoreId].timing.enabled;
      isSupressed = RBTPSW_Context[CoreId].timing.supprFlag;

      if (enabled && !isSupressed) {
          /* force aborting TPSW */
          RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCK_WITH_TP, RBTPSW_Context[CoreId].fncall, CoreId);
          /* no matter in which mode this function was entered, locks are not allowed in a time protected TPSW, so kill the TPSW with an MPU error */
          RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
          RBTPSW_DummyTrusted = 0xDEADBEEFU;
          RBSYS_SYNCM();
      }
    }
    #endif

    /* is only done if entered the function in user mode */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
        /* check tpsw app specific lock table              */
        /* if: the given lock doesn't match with the table */
        /*   ==> ERROR                                     */

        /* the contents of the "lock" pointer must not be used (r/w) in a single core case */
        #if(RBFS_MCORE == RBFS_MCORE_ON)
        if (RBTPSW_IsLockAllowed_internal(RBTPSW_Context[CoreId].app->lock_conf, lock) == 0)
        #else
        if (RBTPSW_IsLockAllowed_internal(RBTPSW_Context[CoreId].app->lock_conf, NULL) == 0)
        #endif
        {
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_WRONGLOCK, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:          */
            /*  - int lock counter will be reset in exception handler    */
            /*  - OS resets PSW.ID bit after long jump in CallTrustedFn  */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }
    }

    #if(RBFS_MCORE == RBFS_MCORE_ON)
        RBTPSW_EnterLock_intern(lock);
    #else
        RBSYS_SchM_Enter_CoreLocalLock();
    #endif

    /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
      RBTPSW_SetTrust(PrevMode);
    }
}

void RBTPSW_ExitLock(const lockstr_t* lock)
{
    rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;
    CoreIdType CoreId;

    /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation,
     * so no code before this allowed!
     * needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      PrevMode = RBTPSW_SetTrusted();
    }

    /* use RBSYS API to get core ID, this is possible, as we are already in trusted mode*/
    CoreId = (CoreIdType) RBSYS_getCoreID();

    /* is only done if previous mode was user mode */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
        /* check tpsw app specific lock table              */
        /* if: the given lock doesn't match with the table */
        /*   ==> ERROR                                     */

        /* the contents of the "lock" pointer must not be used (r/w) in a single core case */
        #if(RBFS_MCORE == RBFS_MCORE_ON)
        if (RBTPSW_IsLockAllowed_internal(RBTPSW_Context[CoreId].app->lock_conf, lock) == 0)
        #else
        if (RBTPSW_IsLockAllowed_internal(RBTPSW_Context[CoreId].app->lock_conf, NULL) == 0)
        #endif
        {
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_WRONGLOCK, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:          */
            /*  - int lock counter will be reset in exception handler    */
            /*  - OS resets PSW.ID bit after long jump in CallTrustedFn  */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }

        /* Check if lock was entered in the current core before exiting.     */
        #if(RBFS_MCORE == RBFS_MCORE_ON)
        if (RBSYS_getLockNestCnt_perCore(lock, CoreId) == 0)
        #else
        /* Single core case: as spin lock behaves as int lock in single core */
        /* case, we need to check RBSYS_getIntlockNestCnt() here.            */
        if(RBSYS_getIntlockNestCnt(CoreId) == 0)
        #endif
        {
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCKACTIVE, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:          */
            /*  - int lock counter will be reset in exception handler    */
            /*  - OS resets PSW.ID bit after long jump in CallTrustedFn  */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }
    }

    #if(RBFS_MCORE == RBFS_MCORE_ON)
        RBTPSW_ExitLock_intern(lock);
    #else
        RBSYS_SchM_Exit_CoreLocalLock();
    #endif

    /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
      RBTPSW_SetTrust(PrevMode);
    }
}

#endif  /* (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF) */

/** @} */
/* End ingroup RBTPSW */
