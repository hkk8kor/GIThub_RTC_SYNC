#ifndef RBTPSW_TPSWCAPSULE_PRIV_H__
#define RBTPSW_TPSWCAPSULE_PRIV_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Privat (internal) API for the TPSW framework itself
 *
 * RBTPSW capsule provides services to encapsulate a third party software (TPSW) for integration into
 * our braking system in a way that memory accesses of a TPSW are restricted.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "Os.h"
#include "Os_Trust.h"
#include "RBSYS_LocksImpl.h"
#include "../../src/RBSYS_LocksImplIntern.h"
#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )
    #include "../../src/RBSYS_CoreInit.h"
#endif

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_ON,
                          RBFS_HSWSimulation_OFF);

#if (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF)
/************************************************************************/
/** RBTPSW Typedefs                                                    **/
/************************************************************************/

#define RBTPSW_TRUE         1u
#define RBTPSW_FALSE        0u

// starts a void-void TPSW function and returns the TPSW application state
#define RBTPSW_START_intern(fn)       ((void)RBTPSW_Caller_##fn(), RBTPSW_APP_##fn->status)

// calls any TPSW function
#define RBTPSW_CALL_intern(fn)        RBTPSW_Caller_##fn


// note that the address 0xFFFFFFFFU is part of the rh850 p-bus area.
// Anyway, the address is not 4-byte aligned and therefore not valid as a start/end address.
#define RBTPSW_MAXRAMADDRESS (0xFFFFFFFFU)

typedef enum {
    RBTPSW_CPUMODE_UNTRUSTED = 0,
    RBTPSW_CPUMODE_TRUSTED   = 1
} rbtpsw_cpuMode_t;

typedef struct {
    rbtpsw_cpuMode_t cpuMode;
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    boolean supprFlag;
    #endif
} rbtpsw_CpuContext_t;

// Enum to hold status of a TPSW application.
typedef enum {
   ACTIVE = 0,
   NOT_ACTIVE
} rbtpsw_appstatus_t;

typedef enum {
   DEBUG_ACTIVE = 0,
   DEBUG_EXC_ABORTED,
   DEBUG_SW_ABORTED,
   DEBUG_TIMING_ABORTED
} rbtpsw_debugappstatus_t;

/* used to differenciate trusted and untrusted application via sizeof */
typedef uint8 trusted_app_t;
typedef uint16 untrusted_app_t;

// MPU configuration elements (addresses must be 32 bits aligned)
typedef struct {
   uint32 Startadr;
   uint32 Endadr;
} rbtpsw_mpu_cfg_t;

typedef void(*rbtpsw_corefnptr_t)(void*p);

/* values for userinfo in rbtpsw_debuginfo_t in case TPSW was aborted by SW or Enhanced Isolation */
#define RBTPSW_USERINFO_LOCKACTIVE         1  /* --> interrupt locked during TPSW calls */
#define RBTPSW_USERINFO_PLAUSIBILITY       2  /* --> invalid MPU table or lock table  */
#define RBTPSW_USERINFO_STACKOUTOFRANGE    3  /* --> third party stack exceeds global stack size. Detected when MPU is set. */
#define RBTPSW_USERINFO_WRONGLOCK          4  /* --> lock doesn't belong to the app */
#define RBTPSW_USERINFO_LOCKACTIVE_TRUSTED 5  /* --> interrupt locked during TPSW calls from TRUSTED */
#define RBTPSW_USERINFO_LOCK_WITH_TP       6  /* --> int locks when timing protection enabled and not supressed */
#define RBTPSW_USERINFO_INVALID_API        7  /* --> invalid API call */
#define RBTPSW_USERINFO_KILLED_VIA_EI      9  /* --> the TPSW was killed because Enhanced Isolation detected a fault */

/* Debug information for a TPSW application. Only filled when aborted of SW killed. */
typedef struct {
  uint32                  userinfo;      /* user info when tpsw killed by software or EI                          */
  uint32                  FaultAdr;      /* RH850 FEPC register content: PC when exception occurred               */
  rbtpsw_corefnptr_t      CallCoreFnPtr; /* RBTPSW_FnCall_Core_XXX in which the failure occurred                  */
  uint32                  rh850_mei;     /* MEI: Memory error information                                         */
  uint32                  rh850_mea;     /* MEA: Memory error address                                             */
  uint32                  rh850_feic;    /* FEIC(bits 0..15): exception which caused abort:                       */
                                         /*                   0x90/0x91(MIP/MDP), 0xA0(PIE), 0x60(RIE), 0xC0(MAE) */
  uint32                  rh850_fepsw;   /* FEPSW: state of the PSW at error                                      */
  uint32                  rh850_fpsr;    /* FPSR:  Floating-point operation setting/status                        */
  uint32                  rh850_fpepc;   /* FPEPC: Floating-point operation exception program counter             */
                                         /* Floating point registers are only relevant if the mpu exception was   */
                                         /* triggered by an fpu exception.                                        */
  uint8                   os_status;     /* detailed os status                                                    */
  rbtpsw_debugappstatus_t debug_status;
} rbtpsw_debuginfo_t;

// initialization of the rbtpsw_debuginfo_t structure
#if(RBFS_MCORE == RBFS_MCORE_ON)
    #define RBTPSW_INITIAL_DBG_TABLE  { {0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, DEBUG_ACTIVE},\
                                        {0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, DEBUG_ACTIVE} }
#else
    #define RBTPSW_INITIAL_DBG_TABLE  { {0, 0, NULL, 0, 0, 0, 0, 0, 0, 0, DEBUG_ACTIVE} }
#endif

 /* RBTPSW_STACK_CST_OVERHEAD contains:
     - Os stack consumption
       Used in Os_untrusted_function_alignment_handler() which is called after SetMemAccess() callback
       which sets up the stack mpu: 20 bytes in os version <= 5.0.6; 12 bytes with improved alignment handler.
       Selected max = 20.
     - Stack of switch2priv() --> used in the core function
     - Safety addon
     Hint: this also ensures that there is enough stack for Os_Abort in case of an MPU exception,
           abort stack is configured in Os_Cbk_GetAbortStack,
           TPSW stack fits into system stack as checked by Os_Cbk_SetMemoryAccess so also suffices for abort stack */
#define RBTPSW_STACK_CST_OVERHEAD   (20 /* Os stack consumption */ + \
                                     sizeof(CoreIdType) + sizeof(lockstr_t**) + sizeof(rbtpsw_CpuContext_t) + sizeof(rbtpsw_cpuMode_t) /* stack of switch2priv() */ + \
                                     32 /* Safety addon */ )

#define RBTPSW_NO_LOCKTABLE_PRV    ((lockstr_t**)NULL)
#define RBTPSW_NO_MPUTABLE_PRV     ((const rbtpsw_mpu_cfg_t*)NULL)


typedef struct {
  volatile rbtpsw_appstatus_t status; // volatile variable as we have a multicore system
  rbtpsw_debuginfo_t debuginfo[OS_NUM_CORES];
  const rbtpsw_mpu_cfg_t* mpu_conf;
  lockstr_t** lock_conf;
  const uint32* lock_conf_size;
  uint8 PlausiCheckDone;
  uint8 ei_fault; // signals that Enhanced Isolation has encountered an error and the TPSW app will be killed
} RBTPSW_App_t;

typedef struct
{
    rbtpsw_corefnptr_t corefn;
    uint32 stacksize;
    RBTPSW_App_t* application;
    void *params;
} rbtpsw_fncall_context_t;

typedef struct {
    boolean enabled;
    boolean supprFlag;
} RBTPSW_Timing_t;

#define RBTPWS_SUPPRESSIONFLAG_MASK 0x80000000

typedef struct {
    /** Holds last TPSW for which Os_Cbk_SetMemoryAccess has been called.
        Needed because GetApplicationID() returns trusted application always
        when using fcn-level protection. **/
    RBTPSW_App_t* app;

    /** Holds last core function for which Os_Cbk_SetMemoryAccess has been
        called. **/
    rbtpsw_corefnptr_t fncall;

    /** Holds the state of the timing feature:
         - timer enabled
         - suppression flag (delays the timer interrupt) **/
    volatile RBTPSW_Timing_t timing;
} RBTPSW_Context_t;



/************************************************************************/
/** Private externs                                                    **/
/************************************************************************/

/* Trusted global variable for force killing TPSWs by Sw Abort. */
extern volatile uint32 RBTPSW_DummyTrusted;

/* RBTPSW_Context[]
    - holds last TPSW for which Os_Cbk_SetMemoryAccess has been called
      needed because GetApplicationID() returns ESPapp always when using fcn-level protection
    - holds last core function for which Os_Cbk_SetMemoryAccess has been called
    - timing protection state */
extern RBTPSW_Context_t RBTPSW_Context[OS_NUM_CORES];

/* RBTPSW_FillSwAbortDebugInfo() fills the debug structure when */
/* a TPSW must be killed by Sw abort.                           */
void RBTPSW_FillSwAbortDebugInfo(RBTPSW_App_t* app, uint32 userinfo, rbtpsw_corefnptr_t corefn, CoreIdType CoreId);

/* RBTPSW_AreCoreLockActive() checks if locks are taken on the local core. */
static inline uint32 RBTPSW_AreCoreLockActive(CoreIdType CoreId);

/* RBTPSW_IsLockAllowed_internal() scans over the app specific lock table (LockTable) */
/* to detect if lock is allowed                                                       */
extern uint32 RBTPSW_IsLockAllowed_internal(lockstr_t* const * LockTable, const lockstr_t* lock);


void RBTPSW_TimingHandler(void);
void RBTPSW_InitTimer(void);


boolean RBTPSW_SuppressTimerInt(CoreIdType CoreId);
boolean RBTPSW_ReactivateTimerInt(CoreIdType CoreId);
void  RBTPSW_RestoreSf(CoreIdType CoreId, boolean PrevSf);


#define RBTPSW_HUGE_LIMIT_TICKS         0x7FFFFFFF  // 0x7FFFFFFF ticks = 26,8 seconds @ 80MHz

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    #define RBTPSW_SUPPRESSTIMERINT(CoreId)                             RBTPSW_SuppressTimerInt(CoreId)
    #define RBTPSW_RESTORESF(CoreId, prevSF)                            RBTPSW_RestoreSf(CoreId, prevSF)

    // for values bigger than 26,8 seconds (@80MHz):
    // limit time limit to 0x7FFFFFFF. Last bit used for saving the suppression flag.
    #define RBTPSW_US_TO_TICKS(timeLimit)                               ( ((timeLimit) >= RBSYS_convertTimerTicksToUsec(RBTPSW_HUGE_LIMIT_TICKS)) ? (RBTPSW_HUGE_LIMIT_TICKS) : (signed)RBSYS_convertUsecToTimerTicks(timeLimit) )

#else
    #define RBTPSW_SUPPRESSTIMERINT(CoreId)                             (FALSE)
    #define RBTPSW_RESTORESF(CoreId, prevSF)                            ((void)(prevSF))

    // sc3: time limit is 0
    // --> The Os will deactivate timing callbacks
    #define RBTPSW_US_TO_TICKS(timeLimit)                               (0)
#endif



/*************************************************************************************/
/** RBTPSW_SDA_registerReset()                                                      **/
/** Resets the gp and tp pointers with the value initialized by RBSYS in the        **/
/** startup code.                                                                   **/
/*************************************************************************************/
static inline void RBTPSW_SDA_registerReset(void)
{
    #if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )
        RBSYS_SDA_registerInit();
    #endif
}



/*************************************************************************************/
/** GetCoreID() wrapper.                                                            **/
/** This function can only be used after typical register plausibility (stack ...). **/
/** Not possible tu use RBSYS_getCoreID() because there are no mode switch.         **/
/*************************************************************************************/
static inline CoreIdType RBTPSW_GetCoreID_Prv(void)
{
    #if(RBFS_MCORE == RBFS_MCORE_OFF)
    return((CoreIdType)RBSYS_CORE_ID_0);
    #else
    return(GetCoreID());
    #endif
}



/************************************************************************/
/** TRUSTED private APIs                                               **/
/************************************************************************/
// This function sets the cpu to trusted mode and returns the previous mode.
static inline rbtpsw_cpuMode_t RBTPSW_GetCpuMode(void)
{
    rbtpsw_cpuMode_t Mode;

    if(OS_RUNNING_CODE_IS_TRUSTED())
    {
        Mode = RBTPSW_CPUMODE_TRUSTED;
    }
    else
    {
        Mode = RBTPSW_CPUMODE_UNTRUSTED;
    }

    return Mode;
}

// This function sets the cpu to trusted mode and returns the previous mode.
static inline rbtpsw_cpuMode_t RBTPSW_SetTrusted(void)
{
    rbtpsw_cpuMode_t PrevMode = RBTPSW_GetCpuMode();

    // Since Os_trust.h 1.2 OS_SET_TRUSTED_MODE() forces CPU mode to TRUSTED.
    OS_SET_TRUSTED_MODE();

    return PrevMode;
}

// This function sets the cpu to the mode given as parameter.
static inline void RBTPSW_SetTrust(rbtpsw_cpuMode_t PrevMode)
{
    if(PrevMode == RBTPSW_CPUMODE_UNTRUSTED)
    {
        // Since Os_trust.h 1.2 OS_SET_UNTRUSTED_MODE() forces CPU mode to UNTRUSTED.
        OS_SET_UNTRUSTED_MODE();
    }
    else
    {
        // Since Os_trust.h 1.2 OS_SET_TRUSTED_MODE() forces CPU mode to TRUSTED.
        OS_SET_TRUSTED_MODE();
    }
}






/*******************************************************************************************************
 ** RBTPSW_AreCoreLockActive() checks if locks are taken on the local core.                           **
 *******************************************************************************************************/
static inline uint32 RBTPSW_AreCoreLockActive(CoreIdType CoreId)
{
    /* Strategy:                                                                      *
     *  - first: check the core local spin lock flag                                  *
     *  - second: check core local int lock counter                                   *
     *                                                                                *
     * Optimization:                                                                  *
     * Only need to check if the core local interrupts are locked. This will also     *
     * covers the common lock/nonest lock which are always under core local int lock. *
     *   ---> first  step can be skipped.                                             */

    return (RBSYS_getIntlockNestCnt(CoreId) == 0u) ? RBTPSW_FALSE : RBTPSW_TRUE;
}




/**********************************************************************************/
/** RBTPSW_IntLockChecks() implements following feature:                         **/
/**  - Kills the TPSW if locks are active                                        **/
/**********************************************************************************/
uint32 RBTPSW_IntLockChecks(const rbtpsw_fncall_context_t *l_context, CoreIdType CoreId, rbtpsw_cpuMode_t PrevMode);



/*****************************************************************/
/** inline functions for getting app status and debug struct    **/
/*****************************************************************/
static inline rbtpsw_debuginfo_t RBTPSW_GetDebugInfo_intern(const RBTPSW_App_t* app, CoreIdType CoreId)
{
  return app->debuginfo[CoreId];
}
static inline rbtpsw_appstatus_t RBTPSW_GetAppStatus_intern(const RBTPSW_App_t* app)
{
  return app->status;
}


/*****************************************************************************************************/
/** RBTPSW_CallTrustedFunction() calls the Os untrusted function corresponding to the current core. **/
/** If the called TPSW was killed, trigger the cross core kill mechanism on the other core.         **/
/** Must be called from trusted mode.                                                               **/
/*****************************************************************************************************/
static inline void RBTPSW_CallTrustedFunction(CoreIdType CoreId, rbtpsw_fncall_context_t* context, Os_TimeLimitType TimeLimit)
{
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    boolean prevSF;
    #endif

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

    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    if((uint32)TimeLimit == RBTPSW_HUGE_LIMIT_TICKS)
    {
        prevSF = RBTPSW_SuppressTimerInt(CoreId);
    }
    else
    {
        prevSF = RBTPSW_ReactivateTimerInt(CoreId);
    }
    #endif

    #if(RBFS_MCORE == RBFS_MCORE_OFF)
    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    (void)CallAndProtectFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context, TimeLimit);
    #else
    (void)CallTrustedFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context);
    #endif
    /* If ei_fault is true, it means Enhanced Isolation detected a fault and terminated CallTrustedFunction       *
     * In order to reach ProtectionHook, the TPSW FUNC needs to be called again and Os_Cbk_SetMemoryAccess will   *
     * make sure to configure MPU to deny memory access, which will cause an exception and kill the TPSW cleanly. */
    if(context->application->ei_fault == RBTPSW_TRUE)
    {
        #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        (void)CallAndProtectFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context, TimeLimit);
        #else
        (void)CallTrustedFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context);
        #endif
    }
    #else
    if(CoreId == OS_CORE_ID_0)
    {
        #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        (void)CallAndProtectFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context, TimeLimit);
        #else
        (void)CallTrustedFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context);
        #endif
        /* If ei_fault is true, it means Enhanced Isolation detected a fault and terminated CallTrustedFunction       *
         * In order to reach ProtectionHook, the TPSW FUNC needs to be called again and Os_Cbk_SetMemoryAccess will   *
         * make sure to configure MPU to deny memory access, which will cause an exception and kill the TPSW cleanly. */
        if(context->application->ei_fault == RBTPSW_TRUE)
        {
            #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
            (void)CallAndProtectFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context, TimeLimit);
            #else
            (void)CallTrustedFunction(UntrustedFuncCore0, (TrustedFunctionParameterRefType)context);
            #endif
        }

        if(context->application->status != ACTIVE)
        {
            (void)ActivateTask(TaskTPSWKillCore1);
        }
    }
    else
    {
        #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        (void)CallAndProtectFunction(UntrustedFuncCore1, (TrustedFunctionParameterRefType)context, TimeLimit);
        #else
        (void)CallTrustedFunction(UntrustedFuncCore1, (TrustedFunctionParameterRefType)context);
        #endif
        /* If ei_fault is true, it means Enhanced Isolation detected a fault and terminated CallTrustedFunction       *
         * In order to reach ProtectionHook, the TPSW FUNC needs to be called again and Os_Cbk_SetMemoryAccess will   *
         * make sure to configure MPU to deny memory access, which will cause an exception and kill the TPSW cleanly. */
        if(context->application->ei_fault == RBTPSW_TRUE)
        {
            #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
            (void)CallAndProtectFunction(UntrustedFuncCore1, (TrustedFunctionParameterRefType)context, TimeLimit);
            #else
            (void)CallTrustedFunction(UntrustedFuncCore1, (TrustedFunctionParameterRefType)context);
            #endif
        }

        if(context->application->status != ACTIVE)
        {
            (void)ActivateTask(TaskTPSWKillCore0);
        }
    }
    #endif

    #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
    RBTPSW_RestoreSf(CoreId, prevSF);
    #endif
}


#define RBTPSW_LOCKCONFIG_ENDMARKER_PRV   ((lockstr_t*)NULL)
#if(RBFS_MCORE == RBFS_MCORE_ON)
    #define RBTPSW_LOCKCONFIG_COMMONLOCK_PRV  ((lockstr_t*)&RBSYS_common_lock)
#else
    /* RBSYS_common_lock not defined in single core.
       Use of a dummy variable to ensure that a miss-usage will have no consequence on critical data. */
    extern lockstr_t RBTPSW_SingleCoreDummyCommonLock;
    #define RBTPSW_LOCKCONFIG_COMMONLOCK_PRV  (&RBTPSW_SingleCoreDummyCommonLock)
#endif


#endif /* (RBFS_TPSWCapsule != RBFS_TPSWCapsule_OFF) */

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
