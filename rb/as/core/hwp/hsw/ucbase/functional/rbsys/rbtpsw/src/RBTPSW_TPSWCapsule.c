/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule
 *
 * This module provides services to encapsulate a third party software (TPSW) into our braking system ECUs
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"

/* realized interfaces */
#include "RBTPSW_TPSWCapsule.h"
#include "Os.h"                               // realizes OS callbacks ProtectionHook, Os_Cbk_SetMemoryAccess

/* used interfaces */
#include "RBLCF_MemoryMap.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_LocksImpl.h"
#include "RBSYS_uCResetCtrl.h"
#include "../../rtaos/src/RBSYS_OsConfig.h"
#include "RBTPSW_TPSWCapsule_MPUDriver.h"
#include "RBSYS_CoreInit.h"
#include "RBSYS_CoreMpu.h"
#include "RBSYS_ExceptionHandler.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);

#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)

/*******************************************************************
 RBTPSW_STD_TRUSTED_APP: Standard trusted application (public).
********************************************************************/
RBTPSW_TRUSTED_APPLICATION_CONFIG(RBTPSW_STD_TRUSTED_APP)



/*******************************************************************
 RBTPSW_STD_UNTRUSTED_APP: Standard untrusted application (private).
 Used for cross core kill mechanism.
********************************************************************/
RBTPSW_UNTRUSTED_APPLICATION_CONFIG(RBTPSW_STD_UNTRUSTED_APP)

RBTPSW_DEFINE_MPUTABLE(RBTPSW_STD_UNTRUSTED_APP) = {
    RBTPSW_MPUCONFIG_ENDMARKER // no memory required
};

RBTPSW_DEFINE_LOCKTABLE(RBTPSW_STD_UNTRUSTED_APP, 1) = {
    RBTPSW_LOCKCONFIG_ENDMARKER // no locks required
};

RBTPSW_DEF_FUNC_NORET_0PARAM(RBTPSW_STD_UNTRUSTED_APP, 0, 0, RBTPSW_NO_TIMELIMIT, RBTPSW_CrossCoreKill) // stack consumption of RBTPSW_CrossCoreKill() is 0 as it is empty
/* RBTPSW_CrossCoreKill_Proc() is called by the cross core kill tasks.  */
/* It calls the untrusted RBTPSW_CrossCoreKill() func in order to force */
/* the reprogramming of the mpu channel and consequently force a        */
/* cascading abort.                                                     */
void RBTPSW_CrossCoreKill(void)
{
    /*  Do nothing.
        Only used to perform a cross core TPSW kill. This is done by using the cascading mechanism.
        Kill task is triggered when a tpsw call on another core detects an abort.
        The basic mechanism is that the kill task has the highest prio on the core.
        Therefore it preempts any application running in task context (ISR not considered)
        --> MPU is restored after RBTPSW_CrossCoreKill() which disables flash access for the faulty app.
    */
}

/** RBTPSW_CrossCoreKill_Proc: called by the tasks TaskTPSWKillCore0/1 **/
void RBTPSW_CrossCoreKill_Proc(void)
{
    RBTPSW_CALL(RBTPSW_CrossCoreKill());
}


/** RBTPSW_FillSwAbortDebugInfo() fills the debug structure when **/
/** a TPSW must be killed by Sw abort.                           **/
void RBTPSW_FillSwAbortDebugInfo(RBTPSW_App_t* app, uint32 userinfo, rbtpsw_corefnptr_t corefn, CoreIdType CoreId)
{
    // briefly switch to trusted mode in order to update the app debug info.
    rbtpsw_cpuMode_t PrevMode = RBTPSW_SetTrusted();

    app->status = NOT_ACTIVE;
    app->debuginfo[CoreId].CallCoreFnPtr = corefn;
    app->debuginfo[CoreId].userinfo = userinfo;
    app->debuginfo[CoreId].debug_status = DEBUG_SW_ABORTED;

    RBTPSW_SetTrust(PrevMode);
}



static inline void RBTPSW_UntrustedFunc(TrustedFunctionParameterRefType FunctionParams);


// Dummy variable used to kill an untrusted application when a sw-error is detected.
// Ensure immediate reaction with syncm.
volatile uint32 RBTPSW_DummyTrusted;

/* RBTPSW_Context[]
    - holds last TPSW for which Os_Cbk_SetMemoryAccess has been called
      needed because GetApplicationID() returns ESPapp always when using fcn-level protection
    - holds last core function for which Os_Cbk_SetMemoryAccess has been called
    - timing protection state */
RBTPSW_Context_t RBTPSW_Context[OS_NUM_CORES];



/****************************************************************************************/
/** RBTPSW_IsLockAllowed_internal() scans over the app specific lock table (LockTable) **/
/** to detect if lock is allowed.                                                      **/
/****************************************************************************************/
uint32 RBTPSW_IsLockAllowed_internal(lockstr_t* const* LockTable, const lockstr_t* lock)
{
    uint32 i = 0;
    uint8 matching = 0;

    while (LockTable[i] != RBTPSW_LOCKCONFIG_ENDMARKER)
    {
        if(
              (LockTable[i] == lock)
           && (LockTable[i] == RBTPSW_LOCKCONFIG_COMMONLOCK) // this is because we currently only common lock. To be removed when nonest locks are supported.
          )
        {
            matching = 1;
            break;
        }

        i++;
    }

    return matching;
}

/** must be called in every core at PreOs. **/
void RBTPSW_Init(void)
{
    #if(RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
      RBTPSW_InitTimer();
    #endif
}


FUNC(void, OS_APPL_CODE) TRUSTED_UntrustedFuncCore0(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
    (void)FunctionIndex;
    RBTPSW_UntrustedFunc(FunctionParams);
}

FUNC(void, OS_APPL_CODE) TRUSTED_UntrustedFuncCore1(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams)
{
    (void)FunctionIndex;
    RBTPSW_UntrustedFunc(FunctionParams);
}

static inline void RBTPSW_UntrustedFunc(TrustedFunctionParameterRefType FunctionParams)
{
    rbtpsw_corefnptr_t callee;

    callee = ((rbtpsw_fncall_context_t*)FunctionParams)->corefn;
    callee(((rbtpsw_fncall_context_t*)FunctionParams)->params);
}


/***********************************************************/
/** Force a push on the stack.                            **/
/** Checks if the sp is still in a TPSW "valid" RAM area. **/
/** MUST be used before each user->supervisor transition. **/
/** It will only have an effect in user mode.             **/
/***********************************************************/

// Force write a 32 bits value at any address (tpsw internal)
__noinline static void RBTPSW_ForceWriteAddr_intern(volatile uint32* addr)
{
    *addr = 0xDEADBEEFU;
    RBSYS_SYNCM();
}

/**********************************************************************************/
/** This function is called when a new untrusted function shall be called.       **/
/** If locks are active and...                                                   **/
/**     if caller TPSW was in trusted mode: abort calling new untrusted function **/
/**     if caller TPSW was in untrusted mode: kill the caller TPSW               **/
/** Must only be called from RBTPSW_Caller_* in trusted mode.                    **/
/**********************************************************************************/
uint32 RBTPSW_IntLockChecks(const rbtpsw_fncall_context_t *l_context, CoreIdType CoreId, rbtpsw_cpuMode_t PrevMode)
{
    uint32 result = RBTPSW_FALSE;

    /* verify that API is called in trusted mode, untrusted mode is not allowed */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      (void) RBTPSW_SetTrusted();
      /* force aborting TPSW */
      RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_INVALID_API, RBTPSW_Context[CoreId].fncall, CoreId);
      /* kill the TPSW with an MPU error */
      RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
      RBTPSW_DummyTrusted = 0xDEADBEEFU;
      RBSYS_SYNCM();
    }

    /* Call is only allowed without int and spin locks (OS api CTF called internally) */
    if (RBTPSW_AreCoreLockActive(CoreId) == RBTPSW_TRUE)
    {
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
        {
            // kill the caller, register the caller function.
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCKACTIVE, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:                 */
            /*  - int lock counter will be reset in exception handler           */
            /*  - OS resets PSW.ID bit and PMR after long jump in CallTrustedFn */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }
        else
        {
            /* in this special case, kill the callee and register the callee function.                         *
             * no cross core kill is needed here, as this would be a static bosch (T -> UT) integration error. */
            RBTPSW_FillSwAbortDebugInfo(l_context->application, RBTPSW_USERINFO_LOCKACTIVE_TRUSTED, l_context->corefn, CoreId);
        }
    }
    else
    {
        result = RBTPSW_TRUE;
    }

    return result;
}

static void RBTPSW_CleanUpLocksAfterViolation(RBTPSW_App_t* app)
{
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    /* Reset all locks. */

    // reset core local interrupt counters
    RBSYS_ResetLocIntsCounter(CoreId);

    /* Reset core local locks counters from the app specific lock table.      */
    /* Single core case: this is not needed as spin lock behaves as int lock. */
    /*                   Job is done by RBSYS_ResetLocIntsCounter().          */
    #if(RBFS_MCORE == RBFS_MCORE_ON)
    {
        uint32 i;
        uint32 size = *app->lock_conf_size;
        lockstr_t * const * LockTable = app->lock_conf;

        for(i=0; i<size; i++)
        {
            if(LockTable[i] != RBTPSW_LOCKCONFIG_ENDMARKER)
            {
                RBSYS_ResetNestLocCounter(LockTable[i], CoreId);
            }
            else
            {
                break;
            }
        }
    }
    #endif
}


/**************************************************************************
 * Possible sources for ProtectionHook():
 *   + Os_TimingFaultDetected() -> ProtectionLog() -> ProtectionHook()
 *   + Os_abort() -> ProtectionLog() -> ProtectionHook()
 *       - 0x90/0x91 (MIP/MDP): FE exception (direct through os vector)
 *       - 0xA0 (PIE): FE exception          (direct through os vector)
 *       - 0x60 (RIE): FE exception          (through rb exception handler)
 *       - 0xC0 (MAE): FE exception          (through rb exception handler)
 *       - 0x71 (FPP): as this is an EI interrupt, the Os_abort cannot be called directly from there.
 *                     It will be triggered by locking the flash for execution and returning with eiret.
 *                     After returning, a MPU exc will triggered immediately.
 ****************************************************************************/
FUNC(ProtectionReturnType, OS_CALLOUT_CODE) ProtectionHook(StatusType FatalError)
{
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    RBTPSW_App_t* app = RBTPSW_Context[CoreId].app;
    rbtpsw_debuginfo_t* debug = &(app->debuginfo[CoreId]);
    rbtpsw_corefnptr_t corefnptr = RBTPSW_Context[CoreId].fncall;

    /* No need to restore/update the RBTPSW_Context[CoreId].timing structure
     * and the timer channels here. This was:
     *   - already done in the ProtectionLog() by Cbk_Suspend() in case of timing protection error
     *    OR
     *   - this will be done after the longjmp() in ctf by Cbk_Suspend() */

    if(FatalError == E_OS_PROTECTION_TIME)
    {
        if(app->status == ACTIVE)
        {
            app->status = NOT_ACTIVE;

            debug->debug_status  = DEBUG_TIMING_ABORTED;
            debug->CallCoreFnPtr = corefnptr;            /* RBTPSW_FnCall_Core_XXX in which the failure occurred    */
            debug->userinfo      = 0;                    /* user info when tpsw killed by software                  */
            debug->os_status     = (uint8)FatalError;    /* detailed os status                                      */
        }
    }
    else
    {
        uint32 fepsw = RBSYS_STSR(3, 0);

        // check if user mode (FEPSW.UM (bit 30) == 1)
        if((fepsw & 0x40000000U) != 0U)
        {
            /* Only fill the debug structure once. This prevents to overwrite the struct when:
             *   - the tpsw was killed by software
             *   - a cascading abort occurs (multiple aborts for a faulty tpsw)
             */
            if(app->status == ACTIVE)
            {
                app->status = NOT_ACTIVE;

                debug->debug_status  = DEBUG_EXC_ABORTED;
                debug->CallCoreFnPtr = corefnptr;                /* RBTPSW_FnCall_Core_XXX in which the failure occurred          */
                debug->userinfo = (app->ei_fault == RBTPSW_TRUE) ? RBTPSW_USERINFO_KILLED_VIA_EI : 0u;  /* Contains 0, unless the */
                                                                 /* app was killed because Enhanced Isolation found a fault       */
                debug->os_status     = (uint8)FatalError;        /* Detailed OS status                                            */
                debug->FaultAdr      = RBSYS_STSR(2, 0);         /* RH850 FEPC register content: PC when exception occurred       */
                debug->rh850_mea     = RBSYS_STSR(6, 2);         /* MEA: Memory error address                                     */
                debug->rh850_mei     = RBSYS_STSR(8, 2);         /* MEI: Memory error information                                 */
                debug->rh850_fepsw   = RBSYS_STSR(3, 0);         /* FEPSW: state of the PSW at error                              */
                debug->rh850_feic    = RBSYS_STSR(14, 0);        /* FEIC(bits 0..15): exception which caused abort:               */
                                                                 /*                   0x90/0x91(MIP/MDP), 0xA0(PIE),              */
                                                                 /*                   0x60(RIE), 0xC0(MAE)                        */
                debug->rh850_fpsr    = RBSYS_STSR(6, 0);         /* FPSR:  Floating-point operation setting/status                */
                debug->rh850_fpepc   = RBSYS_STSR(7, 0);         /* FPEPC: Floating-point operation exception program counter     */
                                                                 /* Floating registers are only relevant if the mpu exception was */
                                                                 /* triggered by an fpu exception.                                */
            }
        }
        else // coming from supervisor mode
        {
            RBSYS_HandleSupervisorMpuViolation();
        }
    }

    RBTPSW_CleanUpLocksAfterViolation(app);

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    {
        /* Clear PSW.ID, PSW.EP and PSW.NP explicitly.
         * The P1x RTA-OS port does this implicitly in Os_abort(), the U2A port does not.
         * See RTA-OS RH850x2/GHS Port Guide V5.0.4, section 7.7.5 "Recovering from CPU Exceptions/Interrupts that call the ProtectionHook"
         */
        uint32 psw_value = RBSYS_STSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID);
        /* clear Clear PSW.ID (bit 5) , PSW.EP (bit 6) and PSW.NP (bit 7) */
        psw_value &= ~((1U<<5) | (1U<<6) | (1U<<7));
        RBSYS_LDSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID, psw_value);
    }
#endif

    /* Clear FEIC and EIIC to not pollute debug data of other failures.
     * For example if an InvalidInt is reported after an MPU exception, the MPU exception cause code could be in the debug data even though it was
     * not responsible for the InvalidInt. As the MPU exception handler can also call InvaldInt, it would not be clear how the InvalidInt was caused.
     */
    RBSYS_ClearEIIC();
    RBSYS_ClearFEIC();

    return PRO_TERMINATETASKISR;
}


/* RBTPSW_ConfigPlausiChecks() is called only once for each app.  */
/* It performs a plausi check on the mpu table configuration.     */
static inline void RBTPSW_ConfigPlausiChecks(RBTPSW_App_t* app, CoreIdType CoreId)
{
    uint32 i = 0u;
    uint32 failure = RBTPSW_FALSE;

    /* check mpu table */
    {
        /* check all entries of the mpu table */
        while ((app->mpu_conf[i].Startadr != RBTPSW_MAXRAMADDRESS) && (i < RBSYS_MPU_NUMBER_DATAREGIONS))
        {
            if (    ( (uint32)app->mpu_conf[i].Startadr >= (uint32)app->mpu_conf[i].Endadr)
                 || (((uint32)app->mpu_conf[i].Startadr & 0xFFFFFFFCUL) != (uint32)app->mpu_conf[i].Startadr) // Check alignment of start/end address. This will be not more checked during mpu channel programming.
                 || (((uint32)app->mpu_conf[i].Endadr & 0xFFFFFFFCUL)   != (uint32)app->mpu_conf[i].Endadr)   // Check alignment of start/end address. This will be not more checked during mpu channel programming.
               )
            {
                failure = RBTPSW_TRUE;
            }
            i++;
        }

        /* check the mpu table size */
        if ((i == RBSYS_MPU_NUMBER_DATAREGIONS) && (app->mpu_conf[i].Startadr != RBTPSW_MAXRAMADDRESS))
        {
            failure = RBTPSW_TRUE;
        }
    }

    /* check the lock table */
    {
        uint32 end_marker_count = 0u;
        uint32 size = *app->lock_conf_size;
        lockstr_t * const * LockTable = app->lock_conf;

        /* count end markers */
        for(i=0; i<size; i++)
        {
            if(LockTable[i] == RBTPSW_LOCKCONFIG_ENDMARKER)
            {
                end_marker_count++;
            }
        }

        /* check if the table:
             - is not empty
             - and ends with the end marker
             - and contains exactly one end marker */
        if((size == 0u) || (LockTable[size-1u] != RBTPSW_LOCKCONFIG_ENDMARKER) || (end_marker_count != 1u))
        {
            failure = RBTPSW_TRUE;
        }
    }

    if(failure != RBTPSW_FALSE)
    {
        RBTPSW_FillSwAbortDebugInfo(app, RBTPSW_USERINFO_PLAUSIBILITY, RBTPSW_Context[CoreId].fncall, CoreId);
    }
}


/*********************************************************************************************
* Os_Cbk_SetMemoryAccess()
* Called from CallTrustedFunction() only. This is to be checked after each Os configuration update.
* Always called at Os level.
***********************************************************************************************/
FUNC(void, OS_CALLOUT_CODE) Os_Cbk_SetMemoryAccess(Os_UntrustedContextRefType ApplicationContext)
{
    /* This callback performs the following actions:
        - set-up MPU for stack
        - set-up MPU for bss/data
        - disallow flash execution in case tpsw is aborted */

    /* The passed ApplicationContext belongs always to an untrusted application. */
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    const rbtpsw_fncall_context_t* fncall_ctx = (rbtpsw_fncall_context_t*)ApplicationContext->FunctionParams;
    RBTPSW_App_t* app = fncall_ctx->application;
    uint32 sp, sp_end;

    /* save the current app/func running per core */
    RBTPSW_Context[CoreId].app = app;
    RBTPSW_Context[CoreId].fncall = fncall_ctx->corefn;

    /* plausibility -> check flag */
    if(app->PlausiCheckDone == 0)
    {
        RBTPSW_ConfigPlausiChecks(app, CoreId);

        /* call only once */
        app->PlausiCheckDone = 1;
    }

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /* Force stack repositioning on Renesas P1x.
     * Actually not required by hw mpu channel granularity. Only to ensure using the Os_Termination() function
     * which does not use any preserved register after switch to priv and before longjmp(). This is done with
     * the current RH850 port, only in case of stack repositioning.
     * Todo: check if this is still necessary or wanted */
    sp = (uint32) ApplicationContext->Address - 8;
    ApplicationContext->AlignedAddress = (MemoryStartAddressType) sp;
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    /* Renesas U2A: RTA-OS U2A target port does currently not support AlignedAddress ("stack repositioning")
     * no stack repositioning on U2A -> SP for MPU region calculation is identical to current SP */
    sp = (uint32) ApplicationContext->Address;
#endif

    /* get end address of the stack (must be 4 bytes aligned for RH850) */
    sp_end = sp - ((fncall_ctx->stacksize + 4)&0xFFFFFFFCUL);

    /* check if new end of stack is out of global stack
     * it only checks the address and does not use the value it points to */
    if(RBTPSW_IsAdrWithinStack(CoreId, sp_end) == RBTPSW_FALSE)
    {
        /* Set app status to aborted. Shall be evaluated at MPU channels cfg. */
        RBTPSW_FillSwAbortDebugInfo(app, RBTPSW_USERINFO_STACKOUTOFRANGE, RBTPSW_Context[CoreId].fncall, CoreId);
    }

    RBTPSW_ConfigMpu(fncall_ctx, sp, sp_end, CoreId);
}


/*********************************************************************************************
 * If Enhanced Isolation is enabled, Os_Cbk_IsUntrustedTrapOK() checks the validity of a
 * trap occuring while untrusted code is being executed.
 *
 * Return values can a) allow the trap behavior to continue (PRO_IGNORE), b) terminate the
 * calling code without executing the trap (PRO_TERMINATETASKISR), c) same as b) but also
 * terminate the tasks and ISRs belonging to the owning OS app (PRO_TERMINATEAPPL) and d)
 * which is the same as c) but activates the restart task (PRO_TERMINATEAPPL_RESTART).
***********************************************************************************************/
FUNC(ProtectionReturnType, OS_APPL_CODE) Os_Cbk_IsUntrustedTrapOK(MemoryStartAddressType Os_ret_addr, uint32 Os_CauseCode)
{
    /* allow all traps */
    return PRO_IGNORE;
}


/*********************************************************************************************
 * If Enhanced Isolation is enabled, Os_Cbk_RestoreGlobalRegisters() is called to restore
 * r4 (gp) and r5 (tp) registers, in case untrusted code corrupted them.
 *
 * Can be achieved via existing RBSYS function.
***********************************************************************************************/
FUNC(void, OS_CALLOUT_CODE) Os_Cbk_RestoreGlobalRegisters(void)
{
    /* restores base address for RAM SDA (gp) and ROM SDA (tp) */
    RBSYS_SDA_registerInit();
}


/*********************************************************************************************
 * If Enhanced Isolation is enabled, Os_Cbk_IsSystemTrapAllowed() is called whenever the
 * a trap 0 is executed - this means a Os_change() from user to kernel mode.
 *
 * The return value should be TRUE is the trap is allowed and FALSE if not.
***********************************************************************************************/
FUNC(boolean, OS_APPL_CODE)Os_Cbk_IsSystemTrapAllowed( MemoryStartAddressType Caller)
{
    /* the TPSW framework allows switch2priv mode to be called anywhere from UT code */
    return TRUE;
}


/*********************************************************************************************
 * If Enhanced Isolation is enabled, Os_Cbk_IsUntrustedCodeOK() is called to inspect the
 * current state of the CPU registers for the interrupted untrusted code. The registers
 * passed in the context block are r1, r3, r6-19, r30 and r31. r20 to r29 are permanent
 * registers and will not be destroyed over a function call.
 *
 * Return values can a) allow the code to continue after the ISR (PRO_IGNORE), b) terminate
 * the calling code after the interrupt (PRO_TERMINATETASKISR), c) same as b) but also
 * terminate the tasks and ISRs belonging to the owning OS app (PRO_TERMINATEAPPL) and d)
 * which is the same as c) but activates the restart task (PRO_TERMINATEAPPL_RESTART).
***********************************************************************************************/
#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
FUNC(ProtectionReturnType, OS_APPL_CODE) Os_Cbk_IsUntrustedCodeOK(const Os_EIContextBuffType * const Os_stack_context, Os_UntrustedContextRefType Os_EIApplicationContext)
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
//todo: will be aligned with P1x port with a future OS update
FUNC(ProtectionReturnType, OS_APPL_CODE) Os_Cbk_IsUntrustedCodeOK(Os_EIContextBuffType * Os_stack_context, Os_UntrustedContextRefType Os_EIApplicationContext)
#endif
{
    ProtectionReturnType ret;
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();
    const rbtpsw_fncall_context_t* fncall_ctx = (rbtpsw_fncall_context_t*)Os_EIApplicationContext->FunctionParams;
    uint32 sp = Os_stack_context->r3_val;

    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    uint32 startadr = (uint32)Os_EIApplicationContext->AlignedAddress;
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    uint32 startadr = (uint32)Os_EIApplicationContext->Address;
    #endif

    /* endadr is the address in MPUA. startadr is the address in MPLA. Both of these    *
     * addresses must be 4 byte aligned. This is calculated in RBTPSW_ConfigMpu.        */
    uint32 endadr = startadr - ((fncall_ctx->stacksize + 4)&0xFFFFFFFCUL);

    /* both addresses (MPUA and MPLA) are included in the range of the MPU checking */
    if ( (sp <= startadr) && (sp >= endadr) ) {
        ret = PRO_IGNORE;
    }
    else
    {
        RBTPSW_App_t* app = RBTPSW_Context[CoreId].app;

        /* signal that Enhanced Isolation detected a fault - app will be killed */
        fncall_ctx->application->ei_fault = RBTPSW_TRUE;
        ret = PRO_TERMINATETASKISR;

        RBTPSW_CleanUpLocksAfterViolation(app);
    }
    return ret;
}
#endif


/** @} */
/* End ingroup RBTPSW */
