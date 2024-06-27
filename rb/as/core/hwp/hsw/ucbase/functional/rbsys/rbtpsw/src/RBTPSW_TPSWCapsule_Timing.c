/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - timing protection
 *
 * This module provides timing protection services to encapsulate a third party software (TPSW) into our braking system ECUs
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"
#include "RB_MathHelpers.h"


/* realized interfaces */
#include "RBTPSW_TPSWCapsule.h"
#include "RBTPSW_TPSWCapsule_TimerDriver.h"
#include "Os.h"                                   // realizes OS callbacks Os_Cbk_SetTimeLimit, Os_Cbk_SuspendTimeLimit


/* used interfaces */
#include <assert.h>
#include "RB_MathHelpers.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);


#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC3)

/* dummy stubs not required in case of SC3 but still available due to same OS config between SC3 and SC4 */
FUNC(Os_TimeLimitType, OS_CALLOUT_CODE) Os_Cbk_SuspendTimeLimit(void){
    assert(0); // callback shall never be called in SC3 configuration
    return 0;
}
FUNC(void, OS_CALLOUT_CODE) Os_Cbk_SetTimeLimit(Os_TimeLimitType Limit){
    assert(0); // callback shall never be called in SC3 configuration
}

#elif (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)

/*** RBTPSW_InitTimer() ********************************
* Must be called on each core. Done via RBTPSW_Init().
********************************************************/
void RBTPSW_InitTimer(void)
{
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();

    RBTPSW_TimerDriver_DisableInt(CoreId);
}


/*** RBTPSW_SuppressTimerInt() **************************
* Sets the suppression flag and disables the timer isr.
* Must be called from trusted mode.
********************************************************/
boolean RBTPSW_SuppressTimerInt(CoreIdType CoreId)
{
    boolean prevSF;
    volatile RBTPSW_Timing_t* timing = &RBTPSW_Context[CoreId].timing;

    RBSYS_SchM_Enter_CoreLocalLock();
    {
        prevSF = timing->supprFlag;
        timing->supprFlag = TRUE;
        RBTPSW_TimerDriver_DisableInt(CoreId);
    }
    RBSYS_SchM_Exit_CoreLocalLock();

    return prevSF;
}

/*** RBTPSW_ReactivateTimerInt() ************************
* Resets the suppression flag and enables the timer isr.
* Only done if the timer timing protection is active.
* Must be called from trusted mode.
********************************************************/
boolean RBTPSW_ReactivateTimerInt(CoreIdType CoreId)
{
    boolean prevSF;
    volatile RBTPSW_Timing_t* timing = &RBTPSW_Context[CoreId].timing;

    RBSYS_SchM_Enter_CoreLocalLock();
    {
        prevSF = timing->supprFlag;

        timing->supprFlag = FALSE;

        /* Only reactivate isr if timer was enabled. Use cases:
         *  - Call of Switch2Priv() / RestoreMode() in trusted context
         *  - Call of UT (no TP) to T
         *  - Back from UT (no TP) to T
         */
        if (timing->enabled)
        {
            RBTPSW_TimerDriver_EnableInt(CoreId);
        }
    }
    RBSYS_SchM_Exit_CoreLocalLock();

    return prevSF;
}

/*** RBTPSW_RestoreSf() ********************************
* Restores the last mode.
* Must be called from trusted mode.
********************************************************/
void RBTPSW_RestoreSf(CoreIdType CoreId, boolean PrevSf)
{
    if(PrevSf == TRUE)
    {
        (void)RBTPSW_SuppressTimerInt(CoreId);
    }
    else
    {
        (void)RBTPSW_ReactivateTimerInt(CoreId);
    }
}

/*** Os_Cbk_SetTimeLimit() ******************************
* Called by the Os at:
*   - function start (CTF)
*   - function end (restoration of inner CTF)
*   - isr / task end (Os_Wrapper, Dispatch)
* ==> Called at Os level (isr locked).
********************************************************/
FUNC(void, OS_CALLOUT_CODE) Os_Cbk_SetTimeLimit(Os_TimeLimitType Limit)
{
    sint32 copyLimit = (sint32)Limit;      // Rule 17.8 A function parameter should not be modified
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    volatile RBTPSW_Timing_t* timing = &RBTPSW_Context[CoreId].timing;
    uint32 now = RBTPSW_TimerDriver_GetCounter();

    timing->enabled = TRUE;
    RBTPSW_TimerDriver_DisableInt(CoreId);

    // If the limit is negative, this means that the budget was completely consumed.
    // Set it to 0, so that the timer isr will be triggered immediately.
    copyLimit = RB_Max_s32(copyLimit, (sint32)0);       // copyLimit = (copyLimit > 0 ) ? copyLimit : 0

    /* Ensure that timer will not match accidentally by:
        * setting match to now - 1
        * clearing isr request and pending bit */
    RBTPSW_TimerDriver_SetCompareAbs(CoreId, now - 1);
    RBTPSW_TimerDriver_ClearIsrReq(CoreId);
    RBTPSW_TimerDriver_ClearPendingBit(CoreId);

    RBTPSW_TimerDriver_SetCompareRel(CoreId, (uint32)copyLimit);

    if(timing->supprFlag == FALSE)
    {
        RBTPSW_TimerDriver_EnableInt(CoreId);
    }
}

/*** Os_Cbk_SuspendTimeLimit() ******************************
* Called by the Os at:
*   - function end (CTF)
*   - function start (restoration of inner CTF)
*   - isr / task start (Os_Wrapper, Dispatch)
* ==> Called at Os level (isr locked).
********************************************************/
FUNC(Os_TimeLimitType, OS_CALLOUT_CODE) Os_Cbk_SuspendTimeLimit(void)
{
    Os_TimeLimitType remaining; // signed type
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    volatile RBTPSW_Timing_t* timing = &RBTPSW_Context[CoreId].timing;
    uint32 match;
    uint32 now;

    RBTPSW_TimerDriver_DisableInt(CoreId);

    timing->enabled = FALSE;

    match = RBTPSW_TimerDriver_GetCompare(CoreId);
    now = RBTPSW_TimerDriver_GetCounter();

    // RB_UnsignedDiffToSigned can be used, as the difference between match and now
    // is between INT32_MIN and INT32_MAX by design.
    remaining = RB_UnsignedDiffToSigned(match, now);

    /* The remaining time can be negative if the budget expires during Os code
       because the timer interrupt is locked. In that case, set the remaining
       time to zero, as the OS is doing for faulty timing functions. */
    if (remaining < 0)
    {
        remaining = 0;
    }

    return (Os_TimeLimitType)remaining;
}

/*** RBTPSW_TimingHandler() ******************************
* Handler called for timing protection timer isr.
********************************************************/
void RBTPSW_TimingHandler(void)
{
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();

    /* Clear the just triggered isr and disable it. */
    RBTPSW_TimerDriver_DisableInt(CoreId);
    RBTPSW_TimerDriver_ClearPendingBit(CoreId);

    {
        const RBTPSW_App_t* app = RBTPSW_Context[CoreId].app;
        /* The timing handler will always be triggered for an untrusted function with timing protection.
         * It will never be triggered for:
         *   - trusted functions
         *   - untrusted functions without timing protection (suppr flag)
         *   - code under Switch2Priv() / Restore() (suppr flag)
         *
         * RBTPSW_Context[CoreId].app contains the current running UT app and is filled in SetMemAccess() .
         * As SetMemAccess() and SetTimeLimit() callbacks are called atomically in CTF, app will always have a valid value. */

        if(app->status == ACTIVE)
        {
            /* Only call Os_TimingFaultDetected() if the current application was not already killed for any other reason than timing.
             * This will avoid multiple longjmp() calls for one function which performs a double fault (e.g. mpu and timing). */

            /* This call will never return as it uses longjmp(). */
            Os_TimingFaultDetected();
        }
    }

    /* If the app was already killed we ignore this isr and continue. */
}

#endif


/** @} */
/* End ingroup RBTPSW */
