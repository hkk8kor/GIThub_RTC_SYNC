#ifndef RBTPSW_TPSWCAPSULE_H__
#define RBTPSW_TPSWCAPSULE_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief API for the TPSW capsule
 *
 * RBTPSW capsule provides services to encapsulate a third party software (TPSW) for integration into
 * our branking system in a way that memory accesses of a TPSW are restricted.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "../../src/RBSYS_LocksImplIntern.h"
#include "../src/RBTPSW_TPSWCapsule_Priv.h"
#include "RBSYS_Intrinsics.h"
#include <string.h> // for memcpy()
#include "RBSYS_CpuInfo.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)

/************************************************************************/
/** Extern declaration for TPSW processes handled via mergeproc        **/
/************************************************************************/
/* must be called on every core, before StartOs() */
extern void RBTPSW_Init(void);

/* process must be called by kill task */
extern void RBTPSW_CrossCoreKill_Proc(void);

/********************************************************************/
/** CORE LOCAL INTERRUPT LOCK                                      **/
/** RBTPSW_EnterCorelocalIntlock() / RBTPSW_ExitCorelocalIntlock() **/
/********************************************************************/
extern void RBTPSW_EnterCorelocalIntlock(void);
extern void RBTPSW_ExitCorelocalIntlock(void);

/********************************************************************/
/** COMMON LOCK or NONEST LOCK                                     **/
/** RBTPSW_EnterLock() / RBTPSW_ExitLock()                         **/
/** Only locks from the TPSW app specific lock table are allowed.  **/
/********************************************************************/
extern void RBTPSW_EnterLock(const lockstr_t* lock);
extern void RBTPSW_ExitLock(const lockstr_t* lock);




/************************************************************************/
/** RBTPSW_Switch2PrivMode() / RBTPSW_RestoreMode()                    **/
/** Switch to and restore privileged mode.                             **/
/**                                                                    **/
/** RBTPSW_Switch2PrivMode() makes a plausibility check of the stack   **/
/** (via Enhanced Isolation) and checks if the locks are taken. If     **/
/** something gets wrong, the TPSW App will be killed by software.     **/
/**                                                                    **/
/** RBTPSW_RestoreMode(PreviousMode) restores the previous mode        **/
/** returned by RBTPSW_Switch2PrivMode()                               **/
/**                                                                    **/
/** It is not allowed to call RBTPSW_Switch2PrivMode() /               **/
/** RBTPSW_RestoreMode() under lock.                                   **/
/************************************************************************/
static inline rbtpsw_CpuContext_t RBTPSW_Switch2PrivMode(void)
{
    CoreIdType CoreId;
    rbtpsw_CpuContext_t context;
    rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;

    /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation,
     * so no code before this allowed!
     * needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */
    if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)
    {
      PrevMode = RBTPSW_SetTrusted();
    }

    /* use RBSYS API to get core ID, this is possible, as we are already in trusted mode */
    CoreId = (CoreIdType) RBSYS_getCoreID();

    /* Is only done if function was entered in user mode. In privileged mode, no int lock check is done. */
    if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
        if (RBTPSW_AreCoreLockActive(CoreId) != RBTPSW_FALSE)
        {
            RBTPSW_FillSwAbortDebugInfo(RBTPSW_Context[CoreId].app, RBTPSW_USERINFO_LOCKACTIVE, RBTPSW_Context[CoreId].fncall, CoreId);

            /* force aborting TPSW, write access has no effect:          */
            /*  - int lock counter will be reset in exception handler.   */
            /*  - OS resets PSW.ID bit after long jump in CallTrustedFn  */
            RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); // backwards compatible to Os_Trust 1.1 - using that version, RBTPSW_SetTrust will toggle the CPU mode, regardless of parameter. At this point, it will always toggle from Trusted to Untrusted.
            RBTPSW_DummyTrusted = 0xDEADBEEFU;
            RBSYS_SYNCM();
        }
    }

    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    /*
        The suppression flag mechanism is implemented to avoid the timing protection isr to be fired in privileged mode.
        Between RBTPSW_SetTrusted() and RBTPSW_SuppressTimerInt() there is a small time window in which the time
        limit expires and the timing limit could be fired. This is ok as the ProtectionLog() will long jmp back to the
        CTF in a safe state.
    */
    context.supprFlag = RBTPSW_SuppressTimerInt(CoreId);
    #endif
    context.cpuMode = PrevMode;

    return context;
}
static inline void RBTPSW_RestoreMode(rbtpsw_CpuContext_t context)
{
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    CoreIdType CoreId = RBTPSW_GetCoreID_Prv();

    RBTPSW_RestoreSf(CoreId, context.supprFlag);
    #endif
    /*
        The suppression flag mechanism is implemented to avoid the timing protection isr to be fired in privileged mode.
        Between RBTPSW_RestoreSf() and RBTPSW_SetTrust() there is a small time window in which the time
        limit expires and the timing limit could be fired. This is ok as the ProtectionLog() will long jmp back to the
        CTF in a safe state.
    */
    RBTPSW_SetTrust(context.cpuMode);
}




/************************************************************************/
/** RBTPSW Macros                                                      **/
/************************************************************************/



/********* LOCK TABLE **************/
#define RBTPSW_DEFINE_LOCKTABLE(TPSWNAME, size) const uint32 TPSWNAME##_LockTableSize = (size);\
                                                lockstr_t* TPSWNAME##_LockTable[size]
#define RBTPSW_LOCKCONFIG_COMMONLOCK      RBTPSW_LOCKCONFIG_COMMONLOCK_PRV
#define RBTPSW_LOCKCONFIG_ENDMARKER       RBTPSW_LOCKCONFIG_ENDMARKER_PRV

/* RBTPSW_LOCKCONFIG_COMMONLOCK and RBTPSW_LOCKCONFIG_ENDMARKER can only be used in the rbtpsw lock table.
    - DO NOT USE DIRECTLY THE RB LOCK FUNCTIONS in the untrusted software!
    - Nonest locks are currently not supported. Don't configure any other lock than the provided common lock RBTPSW_LOCKCONFIG_COMMONLOCK.
    - The table must end with the end marker.
    - The table must not be empty (at least end marker)
    - The table must contain only one end marker
   If these conditions are not met, the untrusted software will be killed.

Example:
    RBTPSW_DEFINE_LOCKTABLE(MYTPSW2, 2) = {
        RBTPSW_LOCKCONFIG_COMMONLOCK,
        RBTPSW_LOCKCONFIG_ENDMARKER
    };

In your code:
    RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
    ...
    RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
*/


/********* MPU TABLE **************/
#define RBTPSW_DEFINE_MPUTABLE(TPSWNAME) const rbtpsw_mpu_cfg_t TPSWNAME##_MPUTable[]
#define RBTPSW_MPUCONFIG_ENDMARKER             {(RBTPSW_MAXRAMADDRESS),            (RBTPSW_MAXRAMADDRESS)}
#define RBTPSW_MPUCONFIG_BYADDRESS(start, end) {(uint32)(start),                     (uint32)(end)}
#define RBTPSW_MPUCONFIG_FROMLCF(LcfEntryName) {(uint32)&RBTPSW_LINKERSYMBOL_##LcfEntryName##_start, (uint32)&RBTPSW_LINKERSYMBOL_##LcfEntryName##_end}
#define RBTPSW_DECLARE_MPUTABLE_LCFENTRY(LcfEntryName)\
    extern uint32 RBTPSW_LINKERSYMBOL_##LcfEntryName##_start;\
    extern uint32 RBTPSW_LINKERSYMBOL_##LcfEntryName##_end;

/* Example:
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_GLOBAL_LCF)
RBTPSW_DECLARE_MPUTABLE_LCFENTRY(MYTPSW2_LOCAL0_LCF)
RBTPSW_DEFINE_MPUTABLE(MYTPSW2) = {
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW2_GLOBAL_LCF),
    RBTPSW_MPUCONFIG_FROMLCF(MYTPSW2_LOCAL0_LCF),
    RBTPSW_MPUCONFIG_BYADDRESS(StartAddress, EndAddress),
    RBTPSW_MPUCONFIG_ENDMARKER
};
*/


/********* TRUSTED APP **************/
#define RBTPSW_DECLARE_TRUSTED_APPLICATION(TPSWNAME)\
    extern RBTPSW_App_t RBTPSWAppCfg_##TPSWNAME;\
    /* used to differenciate trusted and untrusted via sizeof and compiler optimization */\
    typedef trusted_app_t TPSWAppTrustLvl_##TPSWNAME##_t;

#define RBTPSW_TRUSTED_APPLICATION_CONFIG(TPSWNAME)\
    RBTPSW_App_t RBTPSWAppCfg_##TPSWNAME = {\
                                          ACTIVE,\
                                          RBTPSW_INITIAL_DBG_TABLE,\
                                          RBTPSW_NO_MPUTABLE_PRV,\
                                          RBTPSW_NO_LOCKTABLE_PRV,\
                                          (const uint32*)NULL,\
                                          0,\
                                          0\
                                      };
/* Example:
RBTPSW_DECLARE_TRUSTED_APPLICATION(MY_TRUSPED_APP)  // to be placed in your header

RBTPSW_TRUSTED_APPLICATION_CONFIG(MY_TRUSPED_APP)  // to be placed in your c module (TPSW capsule)
*/


/********* UNTRUSTED APP **************/
#define RBTPSW_DECLARE_UNTRUSTED_APPLICATION(TPSWNAME)\
    extern const rbtpsw_mpu_cfg_t TPSWNAME##_MPUTable[];\
    extern lockstr_t* TPSWNAME##_LockTable[];\
    extern const uint32 TPSWNAME##_LockTableSize;\
    extern RBTPSW_App_t RBTPSWAppCfg_##TPSWNAME;\
    /* used to differenciate trusted and untrusted via sizeof and compiler optimization */\
    typedef untrusted_app_t TPSWAppTrustLvl_##TPSWNAME##_t;

#define RBTPSW_UNTRUSTED_APPLICATION_CONFIG(TPSWNAME)\
    RBTPSW_App_t RBTPSWAppCfg_##TPSWNAME = {\
                                          ACTIVE,\
                                          RBTPSW_INITIAL_DBG_TABLE,\
                                          TPSWNAME##_MPUTable,\
                                          TPSWNAME##_LockTable,\
                                          &TPSWNAME##_LockTableSize,\
                                          0,\
                                          0\
                                      };
/* Example:
In the header file:
    RBTPSW_DECLARE_UNTRUSTED_APPLICATION(MYTPSW2)
In the source file:
    RBTPSW_UNTRUSTED_APPLICATION_CONFIG(MYTPSW2)
*/


// all functions with times greater than 0x7FFFFFFF ticks (26,8 seconds @ 80MHz) will be processed without timing protection
#define RBTPSW_NO_TIMELIMIT      RBSYS_convertTimerTicksToUsec(RBTPSW_HUGE_LIMIT_TICKS)


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - no parameter                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_0PARAM(fnname) RBTPSW_DECL_FUNC_NORET_0PARAM_intern(fnname)
#define RBTPSW_DECL_FUNC_NORET_0PARAM_intern(fnname)\
    extern void RBTPSW_Caller_##fnname(void);\
    /* this is only needed for the TPSW_CALL API */\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(void); /* declaration to ensure that third party prototype fits to tpsw macros. */


#define RBTPSW_DEF_FUNC_NORET_0PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname) RBTPSW_DEF_FUNC_NORET_0PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname)
#define RBTPSW_DEF_FUNC_NORET_0PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(void)\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)();\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t)     /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)   /* stack of tpsw_UntrustedFunc      */\
                                    + (tpswstack)                  /* stack of the UT function         */\
                                    + (stackoverhead)              /* stack of PRE/POST manipulators   */\
                                    + RBTPSW_STACK_CST_OVERHEAD;   /* overhead (os + safety addon)     */\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      /* the core functionality is not needed if the FUNC is trusted but implementation is needed (empty) */\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        (fnname)();\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        /* RBTPSW_Switch2PrivMode is needed in orther to perform the stack and int lock plausi checks */\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_0PARAM(ret_t, fnname) RBTPSW_DECL_FUNC_RET_0PARAM_intern(ret_t, fnname)
#define RBTPSW_DECL_FUNC_RET_0PARAM_intern(ret_t, fnname)\
    typedef struct {\
        ret_t ret;\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(void);\
    /* this is only needed for the TPSW_CALL API */\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(void);

#define RBTPSW_DEF_FUNC_RET_0PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname) RBTPSW_DEF_FUNC_RET_0PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname)
#define RBTPSW_DEF_FUNC_RET_0PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(void)\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)();\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32)  /* stack of RBTPSW_FnCall_Core_xxx */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                            /* stack of tpsw_UntrustedFunc     */\
                                    + (tpswstack)                                                                           /* stack of the UT function        */\
                                    + (stackoverhead)                                                                       /* stack of PRE/POST manipulators  */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                            /* overhead (os + safety addon)    */\
                l_context.params = (void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      /* the core functionality is not needed if the FUNC is trusted but implementation is needed (empty) */\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        temp_ret = (fnname)();\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;



/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 1 parameter                                               */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_1PARAM(fnname, t1, p1) RBTPSW_DECL_FUNC_NORET_1PARAM_intern(fnname, t1, p1)
#define RBTPSW_DECL_FUNC_NORET_1PARAM_intern(fnname, t1, p1)\
    typedef struct {\
        t1 *(p1);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1));

#define RBTPSW_DEF_FUNC_NORET_1PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1) RBTPSW_DEF_FUNC_NORET_1PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1)
#define RBTPSW_DEF_FUNC_NORET_1PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)(p1);\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1)  /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                         /* stack of tpsw_UntrustedFunc      */\
                                    + (tpswstack)                                                                        /* stack of the UT function         */\
                                    + (stackoverhead)                                                                    /* stack of PRE/POST manipulators   */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                         /* overhead (os + safety addon)     */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)(p1);\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_1PARAM(ret_t, fnname, t1, p1) RBTPSW_DECL_FUNC_RET_1PARAM_intern(ret_t, fnname, t1, p1)
#define RBTPSW_DECL_FUNC_RET_1PARAM_intern(ret_t, fnname, t1, p1)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1));

#define RBTPSW_DEF_FUNC_RET_1PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1) RBTPSW_DEF_FUNC_RET_1PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1)
#define RBTPSW_DEF_FUNC_RET_1PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)(p1);\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                        /* stack of tpsw_UntrustedFunc      */\
                                    + (tpswstack)                                                                                       /* stack of the UT function         */\
                                    + (stackoverhead)                                                                                   /* stack of PRE/POST manipulators   */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                        /* overhead (os + safety addon)     */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)(p1);\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 2 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_2PARAM(fnname, t1, p1, t2, p2) RBTPSW_DECL_FUNC_NORET_2PARAM_intern(fnname, t1, p1, t2, p2)
#define RBTPSW_DECL_FUNC_NORET_2PARAM_intern(fnname, t1, p1, t2, p2)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2));

#define RBTPSW_DEF_FUNC_NORET_2PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2) RBTPSW_DEF_FUNC_NORET_2PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2)
#define RBTPSW_DEF_FUNC_NORET_2PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2)  /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_2PARAM(ret_t, fnname, t1, p1, t2, p2) RBTPSW_DECL_FUNC_RET_2PARAM_intern(ret_t, fnname, t1, p1, t2, p2)
#define RBTPSW_DECL_FUNC_RET_2PARAM_intern(ret_t, fnname, t1, p1, t2, p2)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2));

#define RBTPSW_DEF_FUNC_RET_2PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2) RBTPSW_DEF_FUNC_RET_2PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2)
#define RBTPSW_DEF_FUNC_RET_2PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 3 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_3PARAM(fnname, t1, p1, t2, p2, t3, p3) RBTPSW_DECL_FUNC_NORET_3PARAM_intern(fnname, t1, p1, t2, p2, t3, p3)
#define RBTPSW_DECL_FUNC_NORET_3PARAM_intern(fnname, t1, p1, t2, p2, t3, p3)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3));

#define RBTPSW_DEF_FUNC_NORET_3PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3) RBTPSW_DEF_FUNC_NORET_3PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3)
#define RBTPSW_DEF_FUNC_NORET_3PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof (t3)    /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_3PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3) RBTPSW_DECL_FUNC_RET_3PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3)
#define RBTPSW_DECL_FUNC_RET_3PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3));

#define RBTPSW_DEF_FUNC_RET_3PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3) RBTPSW_DEF_FUNC_RET_3PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3)
#define RBTPSW_DEF_FUNC_RET_3PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 4 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_4PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4) RBTPSW_DECL_FUNC_NORET_4PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4)
#define RBTPSW_DECL_FUNC_NORET_4PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4));

#define RBTPSW_DEF_FUNC_NORET_4PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4) RBTPSW_DEF_FUNC_NORET_4PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4)
#define RBTPSW_DEF_FUNC_NORET_4PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof (t3) + sizeof (t4)  /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_4PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4) RBTPSW_DECL_FUNC_RET_4PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4)
#define RBTPSW_DECL_FUNC_RET_4PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4));

#define RBTPSW_DEF_FUNC_RET_4PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4) RBTPSW_DEF_FUNC_RET_4PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4)
#define RBTPSW_DEF_FUNC_RET_4PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 5 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_5PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5) RBTPSW_DECL_FUNC_NORET_5PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)
#define RBTPSW_DECL_FUNC_NORET_5PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5));

#define RBTPSW_DEF_FUNC_NORET_5PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5) RBTPSW_DEF_FUNC_NORET_5PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)
#define RBTPSW_DEF_FUNC_NORET_5PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4), (p5));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof (t3) + sizeof (t4)+ sizeof (t5)  /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4), (p5));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_5PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5) RBTPSW_DECL_FUNC_RET_5PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)
#define RBTPSW_DECL_FUNC_RET_5PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5));

#define RBTPSW_DEF_FUNC_RET_5PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5) RBTPSW_DEF_FUNC_RET_5PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)
#define RBTPSW_DEF_FUNC_RET_5PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4), (p5));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4), (p5));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 6 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_6PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6) RBTPSW_DECL_FUNC_NORET_6PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)
#define RBTPSW_DECL_FUNC_NORET_6PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6));

#define RBTPSW_DEF_FUNC_NORET_6PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6) RBTPSW_DEF_FUNC_NORET_6PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)
#define RBTPSW_DEF_FUNC_NORET_6PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4), (p5), (p6));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof (t3) + sizeof (t4)+ sizeof (t5) + sizeof (t6)  /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4), (p5), (p6));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_6PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6) RBTPSW_DECL_FUNC_RET_6PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)
#define RBTPSW_DECL_FUNC_RET_6PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6));

#define RBTPSW_DEF_FUNC_RET_6PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6) RBTPSW_DEF_FUNC_RET_6PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)
#define RBTPSW_DEF_FUNC_RET_6PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6)/* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)                                                                      /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                                                                                     /* stack of the UT function       */\
                                    + (stackoverhead)                                                                                 /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;                                                                      /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 7 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_7PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) RBTPSW_DECL_FUNC_NORET_7PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)
#define RBTPSW_DECL_FUNC_NORET_7PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7));

#define RBTPSW_DEF_FUNC_NORET_7PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) RBTPSW_DEF_FUNC_NORET_7PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)
#define RBTPSW_DEF_FUNC_NORET_7PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_7PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) RBTPSW_DECL_FUNC_RET_7PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)
#define RBTPSW_DECL_FUNC_RET_7PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7));

#define RBTPSW_DEF_FUNC_RET_7PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7) RBTPSW_DEF_FUNC_RET_7PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)
#define RBTPSW_DEF_FUNC_RET_7PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 8 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_8PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8) RBTPSW_DECL_FUNC_NORET_8PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)
#define RBTPSW_DECL_FUNC_NORET_8PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
        t8 *(p8);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8));

#define RBTPSW_DEF_FUNC_NORET_8PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8) RBTPSW_DEF_FUNC_NORET_8PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)
#define RBTPSW_DEF_FUNC_NORET_8PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_params.p8 = &(p8);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        t8 (p8) = *params->p8;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_8PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8) RBTPSW_DECL_FUNC_RET_8PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)
#define RBTPSW_DECL_FUNC_RET_8PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
        t8 *(p8);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8));

#define RBTPSW_DEF_FUNC_RET_8PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8) RBTPSW_DEF_FUNC_RET_8PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)
#define RBTPSW_DEF_FUNC_RET_8PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_params.p8 = &(p8);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        t8 (p8) = *params->p8;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


/***************************************************************/
/* Definition and declaration of a third party function        */
/* - without and with return value                             */
/* - 9 parameters                                              */
/***************************************************************/
#define RBTPSW_DECL_FUNC_NORET_9PARAM(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9) RBTPSW_DECL_FUNC_NORET_9PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)
#define RBTPSW_DECL_FUNC_NORET_9PARAM_intern(fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)\
    typedef struct {\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
        t8 *(p8);\
        t9 *(p9);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern void fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9));

#define RBTPSW_DEF_FUNC_NORET_9PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9) RBTPSW_DEF_FUNC_NORET_9PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)
#define RBTPSW_DEF_FUNC_NORET_9PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    void RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9))\
    {\
        rbtpsw_fncall_context_t l_context;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8), (p9));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_params.p8 = &(p8);\
                l_params.p9 = &(p9);\
                l_context.stacksize = sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8) + sizeof(t9) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        const rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        t8 (p8) = *params->p8;\
        t9 (p9) = *params->p9;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8), (p9));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;


#define RBTPSW_DECL_FUNC_RET_9PARAM(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9) RBTPSW_DECL_FUNC_RET_9PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)
#define RBTPSW_DECL_FUNC_RET_9PARAM_intern(ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)\
    typedef struct {\
        ret_t ret;\
        t1 *(p1);\
        t2 *(p2);\
        t3 *(p3);\
        t4 *(p4);\
        t5 *(p5);\
        t6 *(p6);\
        t7 *(p7);\
        t8 *(p8);\
        t9 *(p9);\
    } rbtpsw_fncall_params_##fnname##_t;\
    extern ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9));\
    extern const RBTPSW_App_t* const RBTPSW_APP_##fnname;\
    extern ret_t fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9));

#define RBTPSW_DEF_FUNC_RET_9PARAM(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9) RBTPSW_DEF_FUNC_RET_9PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)
#define RBTPSW_DEF_FUNC_RET_9PARAM_intern(TPSWNAME, tpswstack, stackoverhead, timeLimit, ret_t, fnname, t1, p1, t2, p2, t3, p3, t4, p4, t5, p5, t6, p6, t7, p7, t8, p8, t9, p9)\
    static void RBTPSW_FnCall_Core_##fnname(void *cont);\
    ret_t RBTPSW_Caller_##fnname(t1 (p1), t2 (p2), t3 (p3), t4 (p4), t5 (p5), t6 (p6), t7 (p7), t8 (p8), t9 (p9))\
    {\
        rbtpsw_fncall_context_t l_context;\
        /* use cinit to initialize any return type */\
        static ret_t ret_null_initialized;\
        ret_t ret = ret_null_initialized;\
        rbtpsw_cpuMode_t PrevMode = RBTPSW_CPUMODE_TRUSTED;\
        /* in case of untrusted mode it is required to change to trusted mode as soon as possible for checking stack pointer and resetting global registers via enhanced isolation, */\
        /* so no code before this allowed! */\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (RBTPSW_GetCpuMode() == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
          PrevMode = RBTPSW_SetTrusted();\
        }\
        l_context.application = &RBTPSWAppCfg_##TPSWNAME;\
        l_context.corefn = &RBTPSW_FnCall_Core_##fnname;\
        if(l_context.application->status == ACTIVE)\
        {\
          CoreIdType CoreId;\
          CoreId = (CoreIdType) RBSYS_getCoreID();\
          if(RBTPSW_IntLockChecks(&l_context, CoreId, PrevMode) == RBTPSW_TRUE)\
          {\
            if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(trusted_app_t))\
            {\
                boolean prevSF;\
                prevSF = RBTPSW_SUPPRESSTIMERINT(CoreId);\
                ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8), (p9));\
                RBTPSW_RESTORESF(CoreId, prevSF);\
            }\
            else\
            {\
                rbtpsw_fncall_params_##fnname##_t l_params;\
                l_params.ret = ret_null_initialized;\
                l_params.p1 = &(p1);\
                l_params.p2 = &(p2);\
                l_params.p3 = &(p3);\
                l_params.p4 = &(p4);\
                l_params.p5 = &(p5);\
                l_params.p6 = &(p6);\
                l_params.p7 = &(p7);\
                l_params.p8 = &(p8);\
                l_params.p9 = &(p9);\
                l_context.stacksize = sizeof(ret_t) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_fncall_params_##fnname##_t*) + sizeof(uint32) + sizeof(t1) + sizeof(t2) + sizeof(t3) + sizeof(t4) + sizeof(t5) + sizeof(t6) + sizeof(t7) + sizeof(t8) + sizeof(t9) /* stack of RBTPSW_FnCall_Core_xxx  */\
                                    + sizeof(rbtpsw_corefnptr_t)    /* stack of tpsw_UntrustedFunc    */\
                                    + (tpswstack)                   /* stack of the UT function       */\
                                    + (stackoverhead)               /* stack of PRE/POST manipulators */\
                                    + RBTPSW_STACK_CST_OVERHEAD;    /* overhead (os + safety addon)   */\
                l_context.params=(void*)&l_params;\
                RBTPSW_CallTrustedFunction(CoreId, &l_context, RBTPSW_US_TO_TICKS(timeLimit)); /* calls ctf for the correct core and performs a cross core kill if needed. */\
                ret = l_params.ret;\
            }\
          }\
        }\
        /* needs to query cpu mode for backwards compatibility to Os_Trust 1.1 */\
        if (PrevMode == RBTPSW_CPUMODE_UNTRUSTED)\
        {\
            RBTPSW_SetTrust(PrevMode);\
        }\
        return ret;\
    }\
    static void RBTPSW_FnCall_Core_##fnname(void *cont)\
    {\
      if(sizeof(TPSWAppTrustLvl_##TPSWNAME##_t) == sizeof(untrusted_app_t))\
      {\
        ret_t temp_ret;\
        rbtpsw_CpuContext_t tprev;\
        /* The params pointer is stored twice before the UT call. */\
        /* After the function, a plausi check is performed in order to ensure the variable is still valid. */\
        /* Use cases:The tpsw corrupts the stack where the params local is stored. */\
        /* params->ret which is updated, therefore maybe out of tpsw area and we are writing in priv mode. */\
        rbtpsw_fncall_params_##fnname##_t *params = (rbtpsw_fncall_params_##fnname##_t*)cont;\
        volatile uint32 params_inv = ~((uint32)cont);\
        t1 (p1) = *params->p1;\
        t2 (p2) = *params->p2;\
        t3 (p3) = *params->p3;\
        t4 (p4) = *params->p4;\
        t5 (p5) = *params->p5;\
        t6 (p6) = *params->p6;\
        t7 (p7) = *params->p7;\
        t8 (p8) = *params->p8;\
        t9 (p9) = *params->p9;\
        RBTPSW_PARAM_MANIP_PRE_##fnname;\
        temp_ret = (fnname)((p1), (p2), (p3), (p4), (p5), (p6), (p7), (p8), (p9));\
        /* reset SDA registers here because global vars are accessed in advance to RBTPSW_Switch2PrivMode() */\
        RBTPSW_SDA_registerReset();\
        if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED); RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
        if((uint32)params != (~params_inv)){RBTPSW_DummyTrusted = 0xdeadbeefu;RBSYS_SYNCM(); /* Error: register was corrupted. Kill the app! */}\
        tprev = RBTPSW_Switch2PrivMode(); /* stack check and gp reset done implicitly here */ \
        RBTPSW_PARAM_MANIP_POST_##fnname;\
        params->ret = temp_ret;\
        RBTPSW_RestoreMode(tprev);\
      }\
    }\
    const RBTPSW_App_t* const RBTPSW_APP_##fnname = &RBTPSWAppCfg_##TPSWNAME;





/* Example:
In the header file:
    RBTPSW_DECL_FUNC_NORET_2PARAM(TPSW1_ExampleFunc, void*, param_p, uint32, param_u32)
In the source file:
    #define RBTPSW_PARAM_MANIP_PRE_TPSW1_ExampleFunc
    #define RBTPSW_PARAM_MANIP_POST_TPSW1_ExampleFunc
    RBTPSW_DEF_FUNC_NORET_2PARAM(MYTPSW1, TPSW1_ExampleFunc_STACK, 0, RBTPSW_NO_TIMELIMIT, TPSW1_ExampleFunc, void*, param_p, uint32, param_u32)

*/


/***************************************************************/
/* TPSW: copy of the parameters: CPYPTR                        */
/***************************************************************/
/* This manipulator is actually copies the in data to the callee stack.
   This is not required for typical in parameters but allows the callee use it as scratch.
   If callee doesn't need to write to it as scratch, the manipulator can stay empty (just pass the pointer as parameter). */
#define RBTPSW_PARAM_IN_CPYPTR_PRE(type, param) RBTPSW_PARAM_IN_CPYPTR_PRE_intern(type, param)
#define RBTPSW_PARAM_IN_CPYPTR_PRE_intern(type, param)\
            {\
                volatile uint32 l_cpy_ptr_inv_##param;\
                type param##_buffertemp;\
                type * param##_ptr_cpy;\
                param##_buffertemp = *(param);\
                param##_ptr_cpy = (param);\
                l_cpy_ptr_inv_##param = ~(uint32)(param);\
                (param) = &param##_buffertemp;

#define RBTPSW_PARAM_IN_CPYPTR_POST(type, param);\
            }

#define RBTPSW_PARAM_OUT_CPYPTR_PRE(type, param) RBTPSW_PARAM_OUT_CPYPTR_PRE_intern(type, param)
#define RBTPSW_PARAM_OUT_CPYPTR_PRE_intern(type, param)\
            {\
                volatile uint32 l_cpy_ptr_inv_##param;\
                type param##_buffertemp;\
                type * param##_ptr_cpy;\
                param##_ptr_cpy = (param);\
                l_cpy_ptr_inv_##param = ~(uint32)(param);\
                (param) = &param##_buffertemp;

#define RBTPSW_PARAM_OUT_CPYPTR_POST(type, param) RBTPSW_PARAM_OUT_CPYPTR_POST_intern(type, param)
#define RBTPSW_PARAM_OUT_CPYPTR_POST_intern(type, param)\
                if(l_cpy_ptr_inv_##param != ~(uint32)param##_ptr_cpy) {if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED);} RBTPSW_DummyTrusted = 0;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
                *param##_ptr_cpy = param##_buffertemp;\
            }

#define RBTPSW_PARAM_INOUT_CPYPTR_PRE(type, param)   RBTPSW_PARAM_IN_CPYPTR_PRE_intern(type, param)

#define RBTPSW_PARAM_INOUT_CPYPTR_POST(type, param)  RBTPSW_PARAM_OUT_CPYPTR_POST_intern(type, param)

#define RBTPSW_PARAM_CPYPTR_STACKADDER(type) (sizeof(type) + sizeof(type *))



/***************************************************************/
/* TPSW: copy of the parameters: CPYARRAY_BYLENGTH             */
/***************************************************************/
/* This manipulator is actually copies the in data to the callee stack.
   This is not required for typical in parameters but allows the callee use it as scratch.
   If callee doesn't need to write to it as scratch, the manipulator can stay empty (just pass the pointer as parameter). */
#define RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_PRE(type, ptr2first, maxlength, length) RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_PRE_intern(type, ptr2first, maxlength, length)
#define RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_PRE_intern(type, ptr2first, maxlength, length)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      uint32 l_length_##ptr2first = (length);\
      if(l_length_##ptr2first > (maxlength)) {l_length_##ptr2first = (maxlength);}\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;\
      (void)memcpy((void*)ptr2first##_data, (const void *)ptr2first##_cpy_ptr, sizeof(type)*l_length_##ptr2first);

#define RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_POST(type, ptr2first, maxlength, length);\
    }

#define RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_PRE(type, ptr2first, maxlength, length) RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_PRE_intern(type, ptr2first, maxlength, length)
#define RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_PRE_intern(type, ptr2first, maxlength, length)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      uint32 l_length_##ptr2first;\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;

#define RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST(type, ptr2first, maxlength, length) RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST_intern(type, ptr2first, maxlength, length)
#define RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST_intern(type, ptr2first, maxlength, length)\
      l_length_##ptr2first = (length);\
      if(l_length_##ptr2first > (maxlength)) {l_length_##ptr2first = (maxlength);}\
      if(l_cpy_ptr_inv_##ptr2first != ~(uint32)ptr2first##_cpy_ptr) {if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED);} RBTPSW_DummyTrusted = 0;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
      (void)memcpy((void*)ptr2first##_cpy_ptr, (const void *)ptr2first##_data, sizeof(type)*l_length_##ptr2first);\
    }

#define RBTPSW_PARAM_INOUT_CPYARRAY_BYLENGTH_PRE(type, ptr2first, maxlength, length)  RBTPSW_PARAM_IN_CPYARRAY_BYLENGTH_PRE_intern(type, ptr2first, maxlength, length)

#define RBTPSW_PARAM_INOUT_CPYARRAY_BYLENGTH_POST(type, ptr2first, maxlength, length) RBTPSW_PARAM_OUT_CPYARRAY_BYLENGTH_POST_intern(type, ptr2first, maxlength, length)

#define RBTPSW_PARAM_CPYARRAY_BYLENGTH_STACKADDER(type, maxlength) ( (sizeof(type)*(maxlength)) + sizeof(type *) + (3*sizeof(uint32)) )



/***************************************************************/
/* TPSW: copy of the parameters: CPYARRAY_FIRSTELEM            */
/***************************************************************/
/* This manipulator is actually copies the in data to the callee stack.
   This is not required for typical in parameters but allows the callee use it as scratch.
   If callee doesn't need to write to it as scratch, the manipulator can stay empty (just pass the pointer as parameter). */
#define RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_PRE(type, ptr2first, maxlength) RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_PRE_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_PRE_intern(type, ptr2first, maxlength)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      uint32 l_length_##ptr2first = (ptr2first)[0];\
      if(l_length_##ptr2first>((maxlength)-1)) {l_length_##ptr2first = (type)((maxlength)-1);}\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;\
      (void)memcpy((void*)ptr2first##_data, (const void *)ptr2first##_cpy_ptr, sizeof(type)*(l_length_##ptr2first + 1));

#define RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_POST(type, ptr2first, maxlength)\
    }

#define RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_PRE(type, ptr2first, maxlength) RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_PRE_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_PRE_intern(type, ptr2first, maxlength)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      uint32 l_length_##ptr2first;\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;

#define RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_POST(type, ptr2first, maxlength) RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_POST_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_POST_intern(type, ptr2first, maxlength)\
      l_length_##ptr2first = (ptr2first)[0];\
      if(l_cpy_ptr_inv_##ptr2first != ~(uint32)ptr2first##_cpy_ptr) {if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED);} RBTPSW_DummyTrusted = 0;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
      if(l_length_##ptr2first>((maxlength)-1)) {l_length_##ptr2first = (type)((maxlength)-1);}\
      (void)memcpy((void*)ptr2first##_cpy_ptr, (const void *)ptr2first##_data, sizeof(type)*(l_length_##ptr2first + 1));\
    }

#define RBTPSW_PARAM_INOUT_CPYARRAY_FIRSTELEM_PRE(type, ptr2first, maxlength)  RBTPSW_PARAM_IN_CPYARRAY_FIRSTELEM_PRE_intern(type, ptr2first, maxlength)

#define RBTPSW_PARAM_INOUT_CPYARRAY_FIRSTELEM_POST(type, ptr2first, maxlength) RBTPSW_PARAM_OUT_CPYARRAY_FIRSTELEM_POST_intern(type, ptr2first, maxlength)

#define RBTPSW_PARAM_CPYARRAY_FIRSTELEM_STACKADDER(type, maxlength) ( (sizeof(type)*(maxlength)) + sizeof(type *) + sizeof(uint32) )



/***************************************************************/
/* TPSW: copy of the parameters: CPYARRAY_0TERM                */
/***************************************************************/
/* This manipulator is actually copies the in data to the callee stack.
   This is not required for typical in parameters but allows the callee use it as scratch.
   If callee doesn't need to write to it as scratch, the manipulator can stay empty (just pass the pointer as parameter). */
#define RBTPSW_PARAM_IN_CPYARRAY_0TERM_PRE(type, ptr2first, maxlength) RBTPSW_PARAM_IN_CPYARRAY_0TERM_PRE_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_IN_CPYARRAY_0TERM_PRE_intern(type, ptr2first, maxlength)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      uint32 i_##ptr2first = 0;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;\
      while((ptr2first##_cpy_ptr[i_##ptr2first] != (type)0) && (i_##ptr2first<(maxlength))) {ptr2first##_data[i_##ptr2first]=ptr2first##_cpy_ptr[i_##ptr2first]; i_##ptr2first++;}\
      if(i_##ptr2first<(maxlength)) {ptr2first##_data[i_##ptr2first]=(type)0;}\

#define RBTPSW_PARAM_IN_CPYARRAY_0TERM_POST(type, ptr2first, maxlength)\
    }\

#define RBTPSW_PARAM_OUT_CPYARRAY_0TERM_PRE(type, ptr2first, maxlength)  RBTPSW_PARAM_OUT_CPYARRAY_0TERM_PRE_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_OUT_CPYARRAY_0TERM_PRE_intern(type, ptr2first, maxlength)\
    {\
      volatile uint32 l_cpy_ptr_inv_##ptr2first;\
      uint32 i_##ptr2first;\
      type * ptr2first##_cpy_ptr;\
      type ptr2first##_data[maxlength];\
      ptr2first##_cpy_ptr = (ptr2first);\
      l_cpy_ptr_inv_##ptr2first = ~(uint32)(ptr2first);\
      (ptr2first) = ptr2first##_data;

#define RBTPSW_PARAM_OUT_CPYARRAY_0TERM_POST(type, ptr2first, maxlength)  RBTPSW_PARAM_OUT_CPYARRAY_0TERM_POST_intern(type, ptr2first, maxlength)
#define RBTPSW_PARAM_OUT_CPYARRAY_0TERM_POST_intern(type, ptr2first, maxlength)\
      i_##ptr2first = 0;\
      if(l_cpy_ptr_inv_##ptr2first != ~(uint32)ptr2first##_cpy_ptr) {if(RBTPSW_GetCpuMode() != RBTPSW_CPUMODE_UNTRUSTED){RBTPSW_SetTrust(RBTPSW_CPUMODE_UNTRUSTED);} RBTPSW_DummyTrusted = 0;RBSYS_SYNCM(); /* Error: tpsw function returned in SV mode. Kill the app! */}\
      while((ptr2first##_data[i_##ptr2first] != (type)0) && (i_##ptr2first<(maxlength))) {ptr2first##_cpy_ptr[i_##ptr2first]=ptr2first##_data[i_##ptr2first]; i_##ptr2first++;}\
      if(i_##ptr2first<(maxlength)) {ptr2first##_cpy_ptr[i_##ptr2first]=(type)0;}\
    }\

#define RBTPSW_PARAM_INOUT_CPYARRAY_0TERM_PRE(type, ptr2first, maxlength)   RBTPSW_PARAM_IN_CPYARRAY_0TERM_PRE_intern(type, ptr2first, maxlength)

#define RBTPSW_PARAM_INOUT_CPYARRAY_0TERM_POST(type, ptr2first, maxlength)  RBTPSW_PARAM_OUT_CPYARRAY_0TERM_POST_intern(type, ptr2first, maxlength)

#define RBTPSW_PARAM_CPYARRAY_0TERM_STACKADDER(type, maxlength) ( (sizeof(type)*(maxlength)) + sizeof(type *) + sizeof(uint32) )




/***************************************************************/
/** TPSW status and debug info                                **/
/***************************************************************/
// Get the TPSW application status by function
#define RBTPSW_GetAppStatusByFunc(fn)  RBTPSW_GetAppStatus_intern(RBTPSW_APP_##fn)

// Get the TPSW application status
#define RBTPSW_GetAppStatus(TPSWNAME)  RBTPSW_GetAppStatus_intern(&RBTPSWAppCfg_##TPSWNAME)

// Get the debug core local structure. Core id can be taken from RBSYS macro RBSYS_CORE_ID_0 / RBSYS_CORE_ID_1
#define RBTPSW_GetDebugInfo(TPSWNAME, core)  RBTPSW_GetDebugInfo_intern(&RBTPSWAppCfg_##TPSWNAME, core)



/***************************************************************/
/** TPSW caller                                               **/
/***************************************************************/
// starts a void-void TPSW function and returns the TPSW application state
#define RBTPSW_START(fn)       RBTPSW_START_intern(fn)

// calls any TPSW function
#define RBTPSW_CALL(fn)        RBTPSW_CALL_intern(fn)



/***********************************************************************/
/** TPSW caller                                                       **/
/** (Un)trusted application to be used for defining (un)trusted FUNCs **/
/** in Gen9.3 context.                                                **/
/***********************************************************************/
RBTPSW_DECLARE_TRUSTED_APPLICATION(RBTPSW_STD_TRUSTED_APP)
RBTPSW_DECLARE_UNTRUSTED_APPLICATION(RBTPSW_STD_UNTRUSTED_APP)


/* Declaration for cross core kill mechanism */
RBTPSW_DECL_FUNC_NORET_0PARAM(RBTPSW_CrossCoreKill)

#endif  /* (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES) */



/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
