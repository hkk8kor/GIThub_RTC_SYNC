/*
 * This is Os.h, auto-generated for:
 *   Project: rtaos_ccas_stellar_mcore_sc1
 *   Target:  Stellar-R52-GHS
 *   Variant: SR6P6
 *   Version: 5.0.4
 *   [$UKS 648]
 */
 
#ifndef OS_H
#define OS_H
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
/*
 * Note that only documented OS APIs are considered to be public.
 * Functions and data in OS header files that are not documented should not be used in
 * non-OS code.
 */
/* File version information [BSW00402] */
#define OS_MODULE_ID (1U)
#define OS_VENDOR_ID (11U)

/// for OS_AR_MAJOR_VERSION etc.
#include "RBSYS_OsAutosarVersion.h"

#define OS_SW_MAJOR_VERSION (12U)
#define OS_SW_MINOR_VERSION (1U)
#define OS_SW_PATCH_VERSION (0U)
#define OS_TARGET_PORT "StellarR52GHS"
#define OS_TARGET_PORT_StellarR52GHS
#define OS_TARGET_MAJOR_VERSION (5U)
#define OS_TARGET_MINOR_VERSION (0U)
#define OS_TARGET_PATCH_VERSION (4U)

#include <Std_Types.h>  /* [$UKS 649] : Includes Std_Types.h */
#ifndef STD_TYPES_H
  #error "STD_TYPES_H is not defined. This should appear in Std_Types.h (AUTOSAR requirement STD014). Is Std_Types.h in the include path? (try --samples:[Includes]overwrite -ISamples\Includes)"
#endif
#ifndef OS_APPL_CODE
  #define OS_APPL_CODE /* Used prior to AUTOSAR 4 */
#endif
#ifndef OS_CALLOUT_CODE
  #define OS_CALLOUT_CODE OS_APPL_CODE  /* [$UKS 1325] [$UKS 1326] OS_CALLOUT_CODE should be defined in AUTOSAR R4.1, but may not be present in earlier versions */
#endif
#ifndef OS_VAR_CLEARED
  #define OS_VAR_CLEARED OS_VAR_POWER_ON_INIT /* OS_VAR_CLEARED is used for RTA-OS 5.4 */
#endif
#ifndef OS_VAR_NO_INIT
  #define OS_VAR_NO_INIT OS_VAR_NOINIT /* OS_VAR_NO_INIT is used from AUTOSAR 4.1 */
#endif

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CAT1_ISR, CAT1_TRAP, OS_MAIN, OS_CLZ, OS_GETSP, OS_GETCPSR, OS_SETCPSR, OS_SVC, OS_PTRDIFF, Os_AwaitStartup) */
/* CAT1_ISR, CAT1_TRAP, OS_MAIN, OS_CLZ, OS_GETSP, OS_GETCPSR, OS_SETCPSR, OS_SVC, OS_PTRDIFF, Os_AwaitStartup */
#define CAT1_ISR(x) void x(void) /* [$TgtCore 55] */
#define CAT1_TRAP(x) void x(void) /* [$TgtCore 55] */

#define Os_AwaitStartup() Os_StartCoreGate() /* [$TgtStellarR52GHS 171] */

typedef int Os_main_int;
#define OS_MAIN() extern void inner_main(void); extern Os_main_int main(void); Os_main_int main(void) { Os_CacheCoreID( ); Os_AwaitStartup( ); inner_main( );  for (;;) { } } void inner_main(void)  /* [$TgtCore 56] */
#define OS_VOLATILE volatile


/* RTA-OS must not make use of compiler header files */
/* Pull in the compiler intrinsic functions originally from arm_ghs.h and
 * ghs_barrier.h */


#ifdef _lint  /* Declaring memory-mapped peripherals and intrinsics */
  extern uint32 OS_GETSP(void); /*lint -esym(752,OS_GETSP) allow to be unreferenced */
  extern void   OS_NOP(void);   /*lint -esym(752,OS_NOP) allow to be unreferenced */
  extern void OS_ISB(void);             /*lint -esym(752,OS_ISB) allow to be unreferenced */
  extern void OS_DSB(void);             /*lint -esym(752,OS_DSB) allow to be unreferenced */
  extern void OS_DMB(void);             /*lint -esym(752,OS_DMB) allow to be unreferenced */
  extern uint32 OS_CLZ(uint32 val);     /*lint -esym(752,OS_CLZ) allow to be unreferenced */
  extern uint32 OS_GETCPSR(void);       /*lint -esym(752,OS_GETCPSR) allow to be unreferenced */
  extern uint32 OS_READ_COPROC(sint32 coproc, sint32 opcode1, sint32 CRn, sint32 CRm, sint32 opcode2); /*lint -esym(752,OS_READ_COPROC) allow to be unreferenced */
  extern uint32 OS_R52_GICD_CTLR; /*lint -esym(752,OS_R52_GICD_CTLR) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_WAKER; /*lint -esym(752,OS_R52_GICR0_WAKER) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_WAKER; /*lint -esym(752,OS_R52_GICR1_WAKER) allow to be unreferenced */
  extern uint32 OS_R52_GICD_IGROUPR[]; /*lint -esym(752,OS_R52_GICD_IGROUPR) allow to be unreferenced */
  extern uint32 OS_R52_GICD_ISENABLER[]; /*lint -esym(752,OS_R52_GICD_ISENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICD_ICENABLER[]; /*lint -esym(752,OS_R52_GICD_ICENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICD_ISPENDR[]; /*lint -esym(752,OS_R52_GICD_ISPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICD_ICPENDR[]; /*lint -esym(752,OS_R52_GICD_ICPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICD_IPRIORITYR[]; /*lint -esym(752,OS_R52_GICD_IPRIORITYR) allow to be unreferenced */
  extern uint32 OS_R52_GICD_ICFGR[]; /*lint -esym(752,OS_R52_GICD_ICFGR) allow to be unreferenced */
  extern uint64 OS_R52_GICD_IROUTER[]; /*lint -esym(752,OS_R52_GICD_IROUTER) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_IGROUPR[]; /*lint -esym(752,OS_R52_GICR0_IGROUPR) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_ISENABLER[]; /*lint -esym(752,OS_R52_GICR0_ISENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_ICENABLER[]; /*lint -esym(752,OS_R52_GICR0_ICENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_ISPENDR[]; /*lint -esym(752,OS_R52_GICR0_ISPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_ICPENDR[]; /*lint -esym(752,OS_R52_GICR0_ICPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_IPRIORITYR[]; /*lint -esym(752,OS_R52_GICR0_IPRIORITYR) allow to be unreferenced */
  extern uint32 OS_R52_GICR0_ICFGR[]; /*lint -esym(752,OS_R52_GICR0_ICFGR) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_IGROUPR[]; /*lint -esym(752,OS_R52_GICR1_IGROUPR) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_ISENABLER[]; /*lint -esym(752,OS_R52_GICR1_ISENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_ICENABLER[]; /*lint -esym(752,OS_R52_GICR1_ICENABLER) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_ISPENDR[]; /*lint -esym(752,OS_R52_GICR1_ISPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_ICPENDR[]; /*lint -esym(752,OS_R52_GICR1_ICPENDR) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_IPRIORITYR[]; /*lint -esym(752,OS_R52_GICR1_IPRIORITYR) allow to be unreferenced */
  extern uint32 OS_R52_GICR1_ICFGR[]; /*lint -esym(752,OS_R52_GICR1_ICFGR) allow to be unreferenced */
  extern uint32 OS_R52_SGPPIREQ31_0[]; /*lint -esym(752,OS_R52_SGPPIREQ31_0) allow to be unreferenced */
  extern uint32 OS_R52_SGPPIREQ63_32[]; /*lint -esym(752,OS_R52_SGPPIREQ63_32) allow to be unreferenced */
  extern uint32 OS_R52_SGPPISETPEND31_0[]; /*lint -esym(752,OS_R52_SGPPISETPEND31_0) allow to be unreferenced */
  extern uint32 OS_R52_SGPPISETPEND63_32[]; /*lint -esym(752,OS_R52_SGPPISETPEND63_32) allow to be unreferenced */
  extern uint32 OS_R52_SGPPICLRPEND31_0[]; /*lint -esym(752,OS_R52_SGPPICLRPEND31_0) allow to be unreferenced */
  extern uint32 OS_R52_SGPPICLRPEND63_32[]; /*lint -esym(752,OS_R52_SGPPICLRPEND63_32) allow to be unreferenced */
  extern uint32 OS_R52_SGPPIENABLE31_0[]; /*lint -esym(752,OS_R52_SGPPIENABLE31_0) allow to be unreferenced */
  extern uint32 OS_R52_SGPPIENABLE63_32[]; /*lint -esym(752,OS_R52_SGPPIENABLE63_32) allow to be unreferenced */
  extern uint32 OS_R52_SGPPISELn[]; /*lint -esym(752,OS_R52_SGPPISELn) allow to be unreferenced */
  extern uint32 OS_R52_SGPPICFGn[]; /*lint -esym(752,OS_R52_SGPPICFGn) allow to be unreferenced */
#else
  #ifndef __ARM_IS
    extern void *__get_stack_pointer(void);
    extern unsigned int __MRC(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);
    extern unsigned long long __MRRC(__ghs_c_int__ coproc, __ghs_c_int__ opcode, __ghs_c_int__ CRm);
    extern void __MCR(__ghs_c_int__ coproc, __ghs_c_int__ opcode1, unsigned int Rd, __ghs_c_int__ CRn, __ghs_c_int__ CRm, __ghs_c_int__ opcode2);
    extern void __MCRR(__ghs_c_int__ coproc, __ghs_c_int__ opcode, unsigned long long Rd, __ghs_c_int__ CRm);
    extern void __NOP(void);
    extern void __EI(void);
    extern void __DI(void);
    extern void __ISB(void);
    extern void __DSB(void);
    extern void __DMB(void);
    extern unsigned int __CLZ32(unsigned int Rm); /* __ARMPURESAFE */
    extern unsigned int __GETSR(void);
    extern void __SETSR(unsigned int Rm);
    extern void __SVC(__ghs_c_int__ code);
  #endif
  #define OS_GETSP() ((Os_StackValueType)__get_stack_pointer())
  #define OS_NOP() __NOP()
  #define OS_ISB() __ISB();
  #define OS_DSB() __DSB();
  #define OS_DMB() __DMB();
  #define OS_CLZ(val) __CLZ32((uint32)(val))
  #define OS_GETCPSR() __GETSR()
  #define OS_READ_COPROC(id, op1, crn, crm, op2) __MRC((id), (op1), (crn), (crm), (op2))

  #define OS_R52_GICD_CTLR *((volatile uint32 *)(0x6d600000U))
  #define OS_R52_GICR0_WAKER *((volatile uint32 *)(0x6d700014U))
  #define OS_R52_GICR1_WAKER *((volatile uint32 *)(0x6d720014U))
  #define OS_R52_GICD_IGROUPR ((volatile uint32 *)(0x6d600080U))
  #define OS_R52_GICD_ISENABLER ((volatile uint32 *)(0x6d600100U))
  #define OS_R52_GICD_ICENABLER ((volatile uint32 *)(0x6d600180U))
  #define OS_R52_GICD_ISPENDR ((volatile uint32 *)(0x6d600200U))
  #define OS_R52_GICD_ICPENDR ((volatile uint32 *)(0x6d600280U))
  #define OS_R52_GICD_IPRIORITYR ((volatile uint32 *)(0x6d600400U))
  #define OS_R52_GICD_ICFGR ((volatile uint32 *)(0x6d600c00U))
  #define OS_R52_GICD_IROUTER ((volatile uint64 *)(0x6d606000U))
  #define OS_R52_GICR0_IGROUPR ((volatile uint32 *)(0x6d710080U))
  #define OS_R52_GICR0_ISENABLER ((volatile uint32 *)(0x6d710100U))
  #define OS_R52_GICR0_ICENABLER ((volatile uint32 *)(0x6d710180U))
  #define OS_R52_GICR0_ISPENDR ((volatile uint32 *)(0x6d710200U))
  #define OS_R52_GICR0_ICPENDR ((volatile uint32 *)(0x6d710280U))
  #define OS_R52_GICR0_IPRIORITYR ((volatile uint32 *)(0x6d710400U))
  #define OS_R52_GICR0_ICFGR ((volatile uint32 *)(0x6d710c00U))
  #define OS_R52_GICR1_IGROUPR ((volatile uint32 *)(0x6d730080U))
  #define OS_R52_GICR1_ISENABLER ((volatile uint32 *)(0x6d730100U))
  #define OS_R52_GICR1_ICENABLER ((volatile uint32 *)(0x6d730180U))
  #define OS_R52_GICR1_ISPENDR ((volatile uint32 *)(0x6d730200U))
  #define OS_R52_GICR1_ICPENDR ((volatile uint32 *)(0x6d730280U))
  #define OS_R52_GICR1_IPRIORITYR ((volatile uint32 *)(0x6d730400U))
  #define OS_R52_GICR1_ICFGR ((volatile uint32 *)(0x6d730c00U))
  #define OS_R52_SGPPIREQ31_0 ((volatile uint32 *)(0x6c200000U))
  #define OS_R52_SGPPIREQ63_32 ((volatile uint32 *)(0x6c200004U))
  #define OS_R52_SGPPISETPEND31_0 ((volatile uint32 *)(0x6c200008U))
  #define OS_R52_SGPPISETPEND63_32 ((volatile uint32 *)(0x6c20000cU))
  #define OS_R52_SGPPICLRPEND31_0 ((volatile uint32 *)(0x6c200010U))
  #define OS_R52_SGPPICLRPEND63_32 ((volatile uint32 *)(0x6c200014U))
  #define OS_R52_SGPPIENABLE31_0 ((volatile uint32 *)(0x6c200018U))
  #define OS_R52_SGPPIENABLE63_32 ((volatile uint32 *)(0x6c20001cU))
  #define OS_R52_SGPPISELn ((volatile uint32 *)(0x6c200020U))
  #define OS_R52_SGPPICFGn ((volatile uint32 *)(0x6c2000e0U))
#endif

extern void Os_InitializeVectorTable(void); /* Call before StartOS() to initialize the interrupt vectors */



extern FUNC(StatusType, OS_CALLOUT_CODE) Os_Cbk_StartCore(uint16 CoreID);


extern FUNC(void, OS_CODE) Os_CacheCoreID(void);
extern FUNC(void, OS_CODE) Os_StartCoreGate(void);



#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif
typedef struct {
  uint32 store[10U];
} Os_JumpBufType[1];
extern sint32 Os_setjmp(Os_JumpBufType buf);
extern void Os_longjmp(Os_JumpBufType buf);
#pragma unknown_control_flow(Os_setjmp)

#ifndef OS_CONST
  #error "OS_CONST is not defined. This normally appears in Compiler_Cfg.h or Os_Compiler_Cfg.h"
#endif
#ifndef OS_CONST_FAST
  #define OS_CONST_FAST OS_CONST
#endif

#define OS_MEMMAP_DECLARATIONS (FALSE)
#define OS_MEMMAP_DEFINITIONS  (FALSE)

typedef unsigned int Os_ResourceCountType;
typedef uint32 Os_StackTraceType;
typedef uint32 Os_StackValueType;
typedef uint32 Os_StackSizeType;
#ifdef _lint /* Lint should check intention, not assembler */
  extern void Os_adjust_stack(uint32 val);
#else
extern void Os_adjust_stack(uint32 val);
asm void Os_adjust_stack(uint32 val) {
% reg val
  add sp, sp, val
}
#endif

typedef void (*Os_VoidVoidFunctionType)(void);
typedef Os_VoidVoidFunctionType Os_TaskEntryFunctionType; /* backwards compatible */
typedef Os_VoidVoidFunctionType Os_IsrEntryFunctionType; /* backwards compatible */
typedef P2VAR(Std_VersionInfoType, TYPEDEF, OS_VAR) Std_VersionInfoRefType;

typedef enum {OS_BUDGET = 0U, OS_ECC_START, OS_ECC_RESUME, OS_ECC_WAIT} Os_StackOverrunType; /* [$UKS 1236] [$UKS 1228] [$UKS 1235] */

#define OS_NOAPPMODE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)  /* [$UKS 381] [$UKS 383] */
#define OS_STANDARD_STATUS  /* [$UKS 7] [$UKS 760] */
#define OS_ORTI_BUILD
#define OS_SCALABILITY_CLASS_1 /* [$UKS 762] [$UKS 763] [$UKS 764] [$UKS 765] */

/* OSApplications */
typedef unsigned int ApplicationType; /* [$UKS 411] */
#define INVALID_OSAPPLICATION ((ApplicationType)2U)  /* [$UKS 413] */

typedef void (*Os_AppErrorHookFunctionType)(StatusType Error); /* [$UKS 450] */
typedef uint32 Os_tmaskType; /* [$UKS 2047] */
typedef struct Os_ApplicationConfigurationType_s {
  ApplicationType app_id;
  uint8 access;
} Os_ApplicationConfigurationType;

typedef uint8 Os_CoreStateType;
typedef uint16 AreaIdType; /* [$UKS 2053] */
typedef CONSTP2CONST(uint8, TYPEDEF, OS_CONST) Os_ucharConstRefType;
typedef CONSTP2CONST(uint8, TYPEDEF, OS_CONST) Os_uint8ConstRefType;
typedef CONSTP2VAR(uint8, TYPEDEF, OS_VAR) Os_uint8RefType;
typedef CONSTP2CONST(uint16, TYPEDEF, OS_CONST) Os_uint16ConstRefType;
typedef CONSTP2VAR(uint16, TYPEDEF, OS_VAR) Os_uint16RefType;
typedef CONSTP2CONST(uint32, TYPEDEF, OS_CONST) Os_uint32ConstRefType;
typedef CONSTP2VAR(uint32, TYPEDEF, OS_VAR) Os_uint32RefType;
typedef unsigned long long Os_PeripheralAddressType; /* [$UKS 2229] */
typedef struct {
  AreaIdType id;
  uint8 access;
  Os_PeripheralAddressType start;
  Os_PeripheralAddressType end;
} Os_PeripheralAreaType;

/* Timing */
typedef unsigned long TickType; /* [$UKS 276] */
typedef signed long SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType; /* [$UKS 277] */
typedef uint32 PhysicalTimeType; /* [$UKS  842] */
typedef unsigned long Os_StopwatchTickType; /* [$UKS 535] */
typedef P2VAR(Os_StopwatchTickType, TYPEDEF, OS_VAR) Os_StopwatchTickRefType;
typedef signed long Os_TimeLimitType;

typedef enum {PRO_IGNORE = 0U, PRO_TERMINATETASKISR, PRO_TERMINATEAPPL, PRO_TERMINATEAPPL_RESTART, PRO_SHUTDOWN} ProtectionReturnType; /* [$UKS 589] [$UKS 590] [$UKS 591] */

typedef uint32 IdleModeType; /* [$UKS 1910] */
#define IDLE_NO_HALT ((IdleModeType)0U)
#define OS_CURRENT_IDLEMODE Os_CurrentIdleMode /* [$UKS 1914] */
typedef uint32 Os_Lockable;
typedef P2CONST(void, TYPEDEF, OS_VAR) Os_LockerRefType;
typedef uint16 CoreIdType;  /* [$UKS 1608] */
typedef uint16 SpinlockIdType;  /* [$UKS 1605] */
#define INVALID_SPINLOCK ((SpinlockIdType)0) /* [$UKS 1606] */
typedef enum {TRYTOGETSPINLOCK_SUCCESS = 0U, TRYTOGETSPINLOCK_NOSUCCESS} TryToGetSpinlockType; /* [$UKS 1607] */
typedef P2VAR(TryToGetSpinlockType, TYPEDEF, OS_VAR) Os_TryToGetSpinlockRefType;
struct Os_ControlledCoreType_s;
typedef struct Os_SpinlockDynType_s {
  OS_VOLATILE Os_Lockable lock;
  SpinlockIdType predecessor;
} Os_SpinlockDynType;
typedef struct Os_SpinlockType_s {
  uint8 access;
  SpinlockIdType successor;
} Os_SpinlockType;
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  typedef unsigned char StatusType; /* [$UKS 468] */
  #define E_OK ((StatusType)0U)
#endif /* STATUSTYPEDEFINED */
#define E_OS_ACCESS ((StatusType)1U)
#define E_OS_CALLEVEL ((StatusType)2U)
#define E_OS_ID ((StatusType)3U)
#define E_OS_LIMIT ((StatusType)4U)
#define E_OS_NOFUNC ((StatusType)5U)
#define E_OS_RESOURCE ((StatusType)6U)
#define E_OS_STATE ((StatusType)7U)
#define E_OS_VALUE ((StatusType)8U)
#define E_OS_SERVICEID ((StatusType)9U)
#define E_OS_ILLEGAL_ADDRESS ((StatusType)10U)
#define E_OS_MISSINGEND ((StatusType)11U)
#define E_OS_DISABLEDINT ((StatusType)12U)
#define E_OS_STACKFAULT ((StatusType)13U)
#define E_OS_PROTECTION_MEMORY ((StatusType)14U)
#define E_OS_PROTECTION_TIME ((StatusType)15U)
#define E_OS_PROTECTION_ARRIVAL ((StatusType)16U)
#define E_OS_PROTECTION_LOCKED ((StatusType)17U)
#define E_OS_PROTECTION_EXCEPTION ((StatusType)18U)
#define E_OS_CORE ((StatusType)19U)
#define E_OS_SPINLOCK ((StatusType)20U)
#define E_OS_INTERFERENCE_DEADLOCK ((StatusType)21U)
#define E_OS_NESTING_DEADLOCK ((StatusType)22U)
#define E_OS_PARAM_POINTER ((StatusType)23U)
#define E_OS_SYS_NO_RESTART ((StatusType)24U)
#define E_OS_SYS_RESTART ((StatusType)25U)
#define E_OS_SYS_OVERRUN ((StatusType)26U)
#define E_OS_SYS_XCORE_QFULL ((StatusType)27U)
#define E_OS_SYS_ERROR_LIMIT ((StatusType)28U)
typedef P2VAR(StatusType, TYPEDEF, OS_VAR) Os_StatusRefType;

/* AppModes */
typedef unsigned int AppModeType; /* [$UKS 382] */
#define DONOTCARE ((AppModeType)0U) /* [$UKS 1612] */

/* Memory Partitioning */
typedef unsigned int AccessType;  /* [$UKS 594] */
#define OS_ACCESS_READ    (1U)
#define OS_ACCESS_WRITE   (2U)
#define OS_ACCESS_EXECUTE (4U)
#define OS_ACCESS_STACK   (8U)
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OSMEMORY_IS_READABLE, OSMEMORY_IS_WRITEABLE, OSMEMORY_IS_EXECUTABLE, OSMEMORY_IS_STACKSPACE) */
#define OSMEMORY_IS_READABLE(x)   (0U != ((x) & OS_ACCESS_READ))    /* [$UKS 597] */
#define OSMEMORY_IS_WRITEABLE(x)  (0U != ((x) & OS_ACCESS_WRITE))   /* [$UKS 598] */
#define OSMEMORY_IS_EXECUTABLE(x) (0U != ((x) & OS_ACCESS_EXECUTE)) /* [$UKS 599] */
#define OSMEMORY_IS_STACKSPACE(x) (0U != ((x) & OS_ACCESS_STACK))   /* [$UKS 600] */
typedef P2CONST(uint8, TYPEDEF, OS_VAR) MemoryStartAddressType; /* [$UKS 971] */
typedef unsigned long MemorySizeType; /* [$UKS 972] */

typedef enum {RESTART = 1U, NO_RESTART} RestartType;  /* [$UKS 414] */
typedef enum {APPLICATION_ACCESSIBLE = 0U, APPLICATION_RESTARTING, APPLICATION_TERMINATED} ApplicationStateType;  /* [$UKS 1314] */
typedef P2VAR(ApplicationStateType, TYPEDEF, OS_VAR) ApplicationStateRefType;  /* [$UKS 1315] */
typedef enum {ACCESS = 0U, NO_ACCESS} ObjectAccessType;  /* [$UKS 415] */
typedef enum {OBJECT_TASK = 0U, OBJECT_ISR, OBJECT_ALARM, OBJECT_RESOURCE, OBJECT_COUNTER, OBJECT_SCHEDULETABLE} ObjectTypeType;  /* [$UKS 416] */
typedef CONSTP2CONST(void, TYPEDEF, OS_VAR) Os_AnyType;

typedef unsigned int TrustedFunctionIndexType; /* [$UKS 969] */
typedef P2VAR(void, TYPEDEF, OS_VAR) TrustedFunctionParameterRefType; /* [$UKS 970] */
#define INVALID_FUNCTION ((TrustedFunctionIndexType)-1)
typedef void (*Os_FunctionEntryType)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
typedef struct Os_TrustedFunctionType_s {
  Os_FunctionEntryType function;  /* [$UKS 1268] */
  CoreIdType core_id;
  CONSTP2CONST(Os_ApplicationConfigurationType, OS_CONST, OS_CONST) application;
} Os_TrustedFunctionType;

typedef uint16 Os_IdleType; /* [$UKS 2147] */
#define OS_CORE_CURRENT (255U) /* [$UKS 1869] */
/* Metering */
typedef struct Os_MeterInfoType_s {
  Os_StopwatchTickType elapsed;
  Os_StopwatchTickType previous;
  Os_StopwatchTickType max;
   Os_StopwatchTickType cumulative;
} Os_MeterInfoType;
typedef P2VAR(Os_MeterInfoType, TYPEDEF, OS_VAR) Os_MeterInfoRefType;
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareEvent) */
#define DeclareEvent(x) /* [$UKS 143] */ /*lint -e(19) : DeclareEvent has no content */
typedef uint8 EventMaskType;  /* [$UKS 141] */
typedef P2VAR(EventMaskType, TYPEDEF, OS_VAR) EventMaskRefType; /* [$UKS 142] */


/* ISRs [$UKS 94] */
typedef uint32 Os_imaskType;

typedef struct Os_ISRDynType_s {
  Os_MeterInfoType meter;
} Os_ISRDynType;
typedef struct Os_ISRType_s {
  Os_VoidVoidFunctionType entry_function;
  CONSTP2VAR(Os_ISRDynType, OS_VAR, OS_CONST) dynamic;
  Os_imaskType imask;
  uint32 index;
  uint8 access;
  ApplicationType application;
} Os_ISRType;
typedef P2CONST(Os_ISRType, TYPEDEF, OS_VAR) ISRType;  /* [$UKS 107] */
#define INVALID_ISR ((ISRType)0)  /* [$UKS 108] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_ISRTYPE_TO_INDEX) */
#define OS_ISRTYPE_TO_INDEX(isrtype) ((isrtype)->index) /* [$UKS 2185] */

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_INDEX_TO_ISRTYPE) */
#define OS_INDEX_TO_ISRTYPE(index) ((ISRType)&Os_const_isrs[(index)])
typedef P2VAR(ISRType, TYPEDEF, OS_VAR) ISRRefType;

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, ISR, DeclareISR) */
#ifndef ISR
  /* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, ISR) */
#define ISR(x) void Os_Entry_##x(void) /* [$UKS 106] [$UKS 98] */
#endif
#define DeclareISR(x) /* [$UKS  1185] */ /*lint -e(19) : DeclareISR has no content */
#define OS_IPL (5U)

/* Tasks */
typedef unsigned long Os_bitmask;
typedef Os_bitmask Os_pset0Type;
typedef Os_bitmask Os_pset1Type;
typedef union {
  Os_pset0Type p0;
  Os_pset1Type p1;
} Os_psetType; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */

typedef union {
  Os_bitmask t0;
  Os_bitmask t1;
} Os_tpmaskType; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
typedef unsigned int Os_ActivationCountType;

typedef struct Os_TaskDynType_s {
  Os_StopwatchTickType last_activation;
  Os_MeterInfoType meter;
  boolean seen_activation;
  Os_ActivationCountType activation_count;
} Os_TaskDynType;

typedef struct Os_TaskType_s {
  CONSTP2VAR(Os_TaskDynType, OS_VAR, OS_CONST) dynamic;
  Os_VoidVoidFunctionType entry_function;
  Os_psetType pset;
  Os_tpmaskType base_tpmask;
  Os_tpmaskType tpmask;
  CoreIdType core_id;
  uint32 index;
  Os_ActivationCountType activation_count;
  uint8 access;
  ApplicationType application;
} Os_TaskType;
typedef P2CONST(Os_TaskType, TYPEDEF, OS_VAR) TaskType;  /* [$UKS 55] */
#define INVALID_TASK  ((TaskType)0) /* [$UKS 92] */
#define OS_INVALID_TPL (0xFFFFU)  /* [$UKS 2014] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TASKTYPE_TO_INDEX) */
#define OS_TASKTYPE_TO_INDEX(tasktype) ((tasktype)->index) /* [$UKS 2185] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_INDEX_TO_TASKTYPE) */
#define OS_INDEX_TO_TASKTYPE(index) ((TaskType)(Os_const_tasks[(index)]))
typedef P2VAR(TaskType, TYPEDEF, OS_VAR) TaskRefType; /* [$UKS 56] */
enum Os_TaskStateType {SUSPENDED = 0U, READY, WAITING, RUNNING};  /* [$UKS 43] [$UKS 47] */
typedef enum Os_TaskStateType TaskStateType;  /* [$UKS 57] */
typedef P2VAR(TaskStateType, TYPEDEF, OS_VAR) TaskStateRefType; /* [$UKS 58] */


/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, TASK, DeclareTask) */
#ifndef TASK
  /* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, TASK) */
#define TASK(x) void Os_Entry_##x(void) /* [$UKS 50] */
#endif
#define DeclareTask(x) /* [$UKS 60] */ /*lint -e(19) : DeclareTask has no content */

/* Resources */
typedef struct Os_ResourceDynType_s {
  TaskType locker;  /* [$UKS 614] */
  union {
    Os_tpmaskType tpmask;
    Os_imaskType imask;
  } saved_priority; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
} Os_ResourceDynType;
typedef struct Os_ResourceType_s {
  CONSTP2VAR(Os_ResourceDynType, OS_VAR, OS_CONST) dynamic;
  Os_tpmaskType tpmask;
  Os_imaskType imask;
  uint8 access;
} Os_ResourceType;
typedef P2CONST(Os_ResourceType, TYPEDEF, OS_CONST) ResourceType;  /* [$UKS 202] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareResource) */
#define DeclareResource(x) /* [$UKS 203] */ /*lint -e(19) : DeclareResource has no content */

/* Alarms */
typedef struct {
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
} AlarmBaseType;  /* [$UKS 278] */
typedef P2VAR(AlarmBaseType, TYPEDEF, OS_VAR) AlarmBaseRefType; /* [$UKS 279] */
typedef struct Os_AlarmDynType_s {
  boolean running;
  TickType match;
  TickType period;
} Os_AlarmDynType;
typedef struct Os_AlarmType_s {
  uint8 config;
  uint8 access;
  ApplicationType application;
} Os_AlarmType;
typedef unsigned int AlarmType;  /* [$UKS 280] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareAlarm, ALARMCALLBACK) */
#define DeclareAlarm(x) /* [$UKS 281] */ /*lint -e(19) : DeclareAlarm has no content */

typedef void (*Os_AlarmCallbackType)(void);
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, ALARMCALLBACK) */
#define ALARMCALLBACK(x) FUNC(void, OS_CODE) Os_Cbk_Alarm_##x(void) /* [$UKS 274] */

/* Counters */
typedef struct {
  boolean Running;
  boolean Pending;
  TickType Delay;
} Os_CounterStatusType;  /* [$UKS 249] */
typedef P2VAR(Os_CounterStatusType, TYPEDEF, OS_VAR) Os_CounterStatusRefType; /* [$UKS 250] */

typedef TickType (*Os_HwCounterNowType)(void);  /* [$UKS 260] */
typedef void (*Os_HwCounterSetType)(TickType Value);  /* [$UKS 261] */
typedef void (*Os_HwCounterStateType)(Os_CounterStatusRefType State); /* [$UKS 262] */
typedef void (*Os_HwCounterCancelType)(void); /* [$UKS 263] */
typedef StatusType (*Os_CounterIncrAdvType)(void);
typedef void (*Os_CounterStartType)(Os_AnyType ctr, TickType requested, TickType relative, TickRefType match_value);

typedef struct Os_CounterDynType_s {
  union {
    struct s_swd { /* [$UKS 211] */
      TickType count;
    } sw;
  } type_dependent; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
} Os_CounterDynType;
typedef struct Os_CounterType_s {
  CONSTP2VAR(Os_CounterDynType, OS_VAR, OS_CONST) dynamic;
  Os_CounterIncrAdvType advincr;
  AlarmBaseType base;
  const void *core;
  uint8 access;
  ApplicationType application;
} Os_CounterType;
typedef P2CONST(Os_CounterType, TYPEDEF, OS_CONST) CounterType;  /* [$UKS 223] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareCounter) */
#define DeclareCounter(x) /* [$UKS  1183] */ /*lint -e(19) : DeclareCounter has no content */

/* ScheduleTables */
enum Os_ScheduleTableStatusType {SCHEDULETABLE_STOPPED = 0U, SCHEDULETABLE_NEXT, SCHEDULETABLE_WAITING, SCHEDULETABLE_RUNNING, SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS};
typedef enum Os_ScheduleTableStatusType ScheduleTableStatusType; /* [$UKS 327] */
typedef P2VAR(ScheduleTableStatusType, TYPEDEF, OS_VAR) ScheduleTableStatusRefType;  /* [$UKS 328] */
typedef enum {OS_SYNC_NONE, OS_SYNC_IMPLICIT, OS_SYNC_EXPLICIT} Os_ScheduleTableSyncType;
typedef enum {OS_SYNC_ASYNC, OS_SYNC_ADVANCING, OS_SYNC_RETARDING, OS_SYNC_INSYNC} Os_ScheduleTableSyncStateType;

struct Os_ScheduleTableDynType_s;
typedef struct Os_ScheduleTableType_s {
  CONSTP2VAR(struct Os_ScheduleTableDynType_s, OS_VAR, OS_CONST) dynamic;
  CounterType counter;
  boolean repeat;
  uint8 config;
  uint8 initial;
  uint8 access;
  ApplicationType application;
} Os_ScheduleTableType;
typedef P2CONST(Os_ScheduleTableType, TYPEDEF, OS_CONST) ScheduleTableType;  /* [$UKS 326] */
typedef P2VAR(ScheduleTableType, TYPEDEF, OS_VAR) ScheduleTableRefType;
typedef struct Os_ScheduleTableDynType_s {
  TickType match;
  ScheduleTableType next;
  ScheduleTableStatusType state;
  uint8 config;
} Os_ScheduleTableDynType;

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareScheduleTable) */
#define DeclareScheduleTable(x) /* [$UKS 1184] */ /*lint -e(19) : DeclareScheduleTable has no content */

/* Service IDs [$UKS 476] */
typedef unsigned int OSServiceIdType;  /* [$UKS 475] */
#define OSServiceId_None ((OSServiceIdType)0U)
#define OSServiceId_ActivateTask ((OSServiceIdType)1)
#define OSServiceId_Os_AdvanceCounter ((OSServiceIdType)2)
#define OSServiceId_CancelAlarm ((OSServiceIdType)3)
#define OSServiceId_CallTrustedFunction ((OSServiceIdType)4)
#define OSServiceId_CheckISRMemoryAccess ((OSServiceIdType)5)
#define OSServiceId_CheckObjectAccess ((OSServiceIdType)6)
#define OSServiceId_CheckObjectOwnership ((OSServiceIdType)7)
#define OSServiceId_CheckTaskMemoryAccess ((OSServiceIdType)8)
#define OSServiceId_ChainTask ((OSServiceIdType)9)
#define OSServiceId_ClearEvent ((OSServiceIdType)10)
#define OSServiceId_ControlIdle ((OSServiceIdType)11)
#define OSServiceId_CurrentIdleMode ((OSServiceIdType)12)
#define OSServiceId_DisableAllInterrupts ((OSServiceIdType)13)
#define OSServiceId_EnableAllInterrupts ((OSServiceIdType)14)
#define OSServiceId_GetActiveApplicationMode ((OSServiceIdType)15)
#define OSServiceId_GetAlarm ((OSServiceIdType)16)
#define OSServiceId_GetAlarmBase ((OSServiceIdType)17)
#define OSServiceId_GetApplicationID ((OSServiceIdType)18)
#define OSServiceId_GetCurrentApplicationID ((OSServiceIdType)19)
#define OSServiceId_GetCounterValue ((OSServiceIdType)20)
#define OSServiceId_GetElapsedCounterValue ((OSServiceIdType)21)
#define OSServiceId_GetEvent ((OSServiceIdType)22)
#define OSServiceId_GetISRID ((OSServiceIdType)23)
#define OSServiceId_GetResource ((OSServiceIdType)24)
#define OSServiceId_GetScheduleTableStatus ((OSServiceIdType)25)
#define OSServiceId_GetTaskID ((OSServiceIdType)26)
#define OSServiceId_GetTaskState ((OSServiceIdType)27)
#define OSServiceId_GetVersionInfo ((OSServiceIdType)28)
#define OSServiceId_IncrementCounter ((OSServiceIdType)29)
#define OSServiceId_NextScheduleTable ((OSServiceIdType)30)
#define OSServiceId_Os_GetCurrentIMask ((OSServiceIdType)31)
#define OSServiceId_Os_GetCurrentTPL ((OSServiceIdType)32)
#define OSServiceId_Os_GetExecutionTime ((OSServiceIdType)33)
#define OSServiceId_Os_GetISRMaxExecutionTime ((OSServiceIdType)34)
#define OSServiceId_Os_GetTaskMaxExecutionTime ((OSServiceIdType)35)
#define OSServiceId_Os_ResetISRMaxExecutionTime ((OSServiceIdType)36)
#define OSServiceId_Os_ResetTaskMaxExecutionTime ((OSServiceIdType)37)
#define OSServiceId_Os_GetElapsedTime ((OSServiceIdType)38)
#define OSServiceId_Os_GetTaskElapsedTime ((OSServiceIdType)39)
#define OSServiceId_Os_GetISRElapsedTime ((OSServiceIdType)40)
#define OSServiceId_Os_GetIdleElapsedTime ((OSServiceIdType)41)
#define OSServiceId_Os_ResetTaskElapsedTime ((OSServiceIdType)42)
#define OSServiceId_Os_ResetISRElapsedTime ((OSServiceIdType)43)
#define OSServiceId_Os_ResetIdleElapsedTime ((OSServiceIdType)44)
#define OSServiceId_Os_GetStackSize ((OSServiceIdType)45)
#define OSServiceId_Os_GetStackUsage ((OSServiceIdType)46)
#define OSServiceId_Os_GetStackValue ((OSServiceIdType)47)
#define OSServiceId_Os_GetISRMaxStackUsage ((OSServiceIdType)48)
#define OSServiceId_Os_GetTaskMaxStackUsage ((OSServiceIdType)49)
#define OSServiceId_Os_ResetISRMaxStackUsage ((OSServiceIdType)50)
#define OSServiceId_Os_ResetTaskMaxStackUsage ((OSServiceIdType)51)
#define OSServiceId_ReleaseResource ((OSServiceIdType)52)
#define OSServiceId_ResumeAllInterrupts ((OSServiceIdType)53)
#define OSServiceId_ResumeOSInterrupts ((OSServiceIdType)54)
#define OSServiceId_Schedule ((OSServiceIdType)55)
#define OSServiceId_SetEvent ((OSServiceIdType)56)
#define OSServiceId_SetAbsAlarm ((OSServiceIdType)57)
#define OSServiceId_SetRelAlarm ((OSServiceIdType)58)
#define OSServiceId_ShutdownOS ((OSServiceIdType)59)
#define OSServiceId_StartOS ((OSServiceIdType)60)
#define OSServiceId_StartScheduleTableAbs ((OSServiceIdType)61)
#define OSServiceId_StartScheduleTableRel ((OSServiceIdType)62)
#define OSServiceId_StartScheduleTableSynchron ((OSServiceIdType)63)
#define OSServiceId_SyncScheduleTable ((OSServiceIdType)64)
#define OSServiceId_SyncScheduleTableRel ((OSServiceIdType)65)
#define OSServiceId_SetScheduleTableAsync ((OSServiceIdType)66)
#define OSServiceId_StopScheduleTable ((OSServiceIdType)67)
#define OSServiceId_SuspendAllInterrupts ((OSServiceIdType)68)
#define OSServiceId_SuspendOSInterrupts ((OSServiceIdType)69)
#define OSServiceId_TerminateTask ((OSServiceIdType)70)
#define OSServiceId_WaitEvent ((OSServiceIdType)71)
#define OSServiceId_EnableInterruptSource ((OSServiceIdType)72)
#define OSServiceId_DisableInterruptSource ((OSServiceIdType)73)
#define OSServiceId_ClearPendingInterrupt ((OSServiceIdType)74)
#define OSServiceId_ModifyPeripheral32 ((OSServiceIdType)75)
#define OSServiceId_ReadPeripheral32 ((OSServiceIdType)76)
#define OSServiceId_WritePeripheral32 ((OSServiceIdType)77)
#define OSServiceId_ModifyPeripheral16 ((OSServiceIdType)78)
#define OSServiceId_ReadPeripheral16 ((OSServiceIdType)79)
#define OSServiceId_WritePeripheral16 ((OSServiceIdType)80)
#define OSServiceId_Os_GetTaskActivationTime ((OSServiceIdType)81)
#define OSServiceId_ModifyPeripheral8 ((OSServiceIdType)82)
#define OSServiceId_ReadPeripheral8 ((OSServiceIdType)83)
#define OSServiceId_WritePeripheral8 ((OSServiceIdType)84)
#define OSServiceId_AllowAccess ((OSServiceIdType)85)
#define OSServiceId_GetApplicationState ((OSServiceIdType)86)
#define OSServiceId_GetNumberOfActivatedCores ((OSServiceIdType)87)
#define OSServiceId_ShutdownAllCores ((OSServiceIdType)88)
#define OSServiceId_StartCore ((OSServiceIdType)89)
#define OSServiceId_GetSpinlock ((OSServiceIdType)90)
#define OSServiceId_ReleaseSpinlock ((OSServiceIdType)91)
#define OSServiceId_TryToGetSpinlock ((OSServiceIdType)92)
/* OSError_ macros  [$UKS 462] [$UKS 478] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OSError_*) */
/*lint --emacro((9078), OSError_*) */ /*lint --emacro((923), OSError_*) */
/*lint --emacro((9030), OSError_TerminateApplication_RestartOption*) (depends on enum size) */ /*lint --emacro((9034), OSError_TerminateApplication_RestartOption*) (depends on enum size) */
#define OSError_ActivateTask_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_AdvanceCounter_CounterID() ((CounterType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_CancelAlarm_AlarmID() ((AlarmType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_CallTrustedFunction_FunctionIndex() ((TrustedFunctionIndexType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_CallTrustedFunction_FunctionParams() ((TrustedFunctionParameterRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ChainTask_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ClearEvent_Mask() ((EventMaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ControlIdle_CoreID() ((CoreIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ControlIdle_IdleMode() ((IdleModeType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetAlarm_AlarmID() ((AlarmType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetAlarm_Tick() ((TickRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetAlarmBase_AlarmID() ((AlarmType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetAlarmBase_Info() ((AlarmBaseRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetCounterValue_CounterID() ((CounterType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetCounterValue_Value() ((TickRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetElapsedCounterValue_CounterID() ((CounterType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetElapsedCounterValue_Value() ((TickRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetElapsedCounterValue_ElapsedValue() ((TickRefType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetEvent_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetEvent_Mask() ((EventMaskRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetResource_ResID() ((ResourceType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetScheduleTableStatus_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetScheduleTableStatus_ScheduleStatus() ((ScheduleTableStatusRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetTaskID_TaskID() ((TaskRefType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetTaskState_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetTaskState_State() ((TaskStateRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_IncrementCounter_CounterID() ((CounterType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_NextScheduleTable_ScheduleTableID_From() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_NextScheduleTable_ScheduleTableID_To() ((ScheduleTableType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetISRMaxExecutionTime_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetTaskMaxExecutionTime_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetISRMaxExecutionTime_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetTaskMaxExecutionTime_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetTaskElapsedTime_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetISRElapsedTime_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetIdleElapsedTime_IdleID() ((Os_IdleType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetTaskElapsedTime_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetISRElapsedTime_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetIdleElapsedTime_IdleID() ((Os_IdleType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetStackSize_Base() ((Os_StackValueType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetStackSize_Sample() ((Os_StackValueType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetISRMaxStackUsage_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetTaskMaxStackUsage_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetISRMaxStackUsage_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_ResetTaskMaxStackUsage_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReleaseResource_ResID() ((ResourceType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetEvent_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetEvent_Mask() ((EventMaskType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetAbsAlarm_AlarmID() ((AlarmType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetAbsAlarm_start() ((TickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetAbsAlarm_cycle() ((TickType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetRelAlarm_AlarmID() ((AlarmType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetRelAlarm_increment() ((TickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetRelAlarm_cycle() ((TickType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StartScheduleTableAbs_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StartScheduleTableAbs_Start() ((TickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StartScheduleTableRel_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StartScheduleTableRel_Offset() ((TickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StartScheduleTableSynchron_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SyncScheduleTable_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SyncScheduleTable_Value() ((TickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SyncScheduleTableRel_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SyncScheduleTableRel_RelativeValue() ((SignedTickType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_SetScheduleTableAsync_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_StopScheduleTable_ScheduleTableID() ((ScheduleTableType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WaitEvent_Mask() ((EventMaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_EnableInterruptSource_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_EnableInterruptSource_ClearPending() ((boolean)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_DisableInterruptSource_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ClearPendingInterrupt_ISRID() ((ISRType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral32_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral32_Address() ((Os_uint32RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral32_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral32_Address() ((Os_uint32ConstRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral32_ReadValue() ((Os_uint32RefType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral32_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral32_Address() ((Os_uint32RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral32_WriteValue() ((uint32)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral16_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral16_Address() ((Os_uint16RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral16_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral16_Address() ((Os_uint16ConstRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral16_ReadValue() ((Os_uint16RefType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral16_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral16_Address() ((Os_uint16RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral16_WriteValue() ((uint16)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetTaskActivationTime_TaskID() ((TaskType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_Os_GetTaskActivationTime_Value() ((Os_StopwatchTickRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral8_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ModifyPeripheral8_Address() ((Os_uint8RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral8_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral8_Address() ((Os_uint8ConstRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReadPeripheral8_ReadValue() ((Os_uint8RefType)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral8_Area() ((AreaIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral8_Address() ((Os_uint8RefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_WritePeripheral8_WriteValue() ((uint8)(Os_ErrorInformation.service_param3)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetApplicationState_Application() ((ApplicationType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetApplicationState_Value() ((ApplicationStateRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_GetSpinlock_SpinlockId() ((SpinlockIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_ReleaseSpinlock_SpinlockId() ((SpinlockIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_TryToGetSpinlock_SpinlockId() ((SpinlockIdType)(Os_ErrorInformation.service_param1)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
#define OSError_TryToGetSpinlock_Success() ((Os_TryToGetSpinlockRefType)(Os_ErrorInformation.service_param2)) /* [MISRA 2012 Rule 11.4/11.6] */ /*lint !e9078 !e923 !e9030 !e9087 !e931 !e826 !e571 !e9074 */
/* Error logging  */
typedef unsigned int Os_BiggestType; /* Used in error logging */
typedef unsigned int Os_BiggestCommonType;
typedef struct {
  OSServiceIdType service_id;
  Os_BiggestType  service_param1;
  Os_BiggestType  service_param2;
  Os_BiggestType  service_param3;
} Os_ErrorInformationType;
/* OSError_ macros  [$UKS 458] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OSErrorGetServiceId) */
#define OSErrorGetServiceId() (Os_ErrorInformation.service_id)  /* [$UKS 457] [$UKS 458] [$UKS 477] */
typedef unsigned int Os_OrtiIdType;

#ifndef OS_NAMESPACE_PURE
  #define GetVersionInfo Os_GetVersionInfo
  #define GetTaskActivationTime Os_GetTaskActivationTime
  #define GetExecutionTime Os_GetExecutionTime
  #define GetTaskMaxExecutionTime Os_GetTaskMaxExecutionTime
  #define GetISRMaxExecutionTime Os_GetISRMaxExecutionTime
  #define ResetTaskMaxExecutionTime Os_ResetTaskMaxExecutionTime
  #define ResetISRMaxExecutionTime Os_ResetISRMaxExecutionTime
  #define GetElapsedTime Os_GetElapsedTime
  #define GetTaskElapsedTime Os_GetTaskElapsedTime
  #define GetISRElapsedTime Os_GetISRElapsedTime
  #define GetIdleElapsedTime Os_GetIdleElapsedTime
  #define ResetIdleElapsedTime Os_ResetIdleElapsedTime
  #define ResetTaskElapsedTime Os_ResetTaskElapsedTime
  #define ResetISRElapsedTime Os_ResetISRElapsedTime
  #define GetStackUsage Os_GetStackUsage
  #define GetTaskMaxStackUsage Os_GetTaskMaxStackUsage
  #define GetISRMaxStackUsage Os_GetISRMaxStackUsage
  #define ResetTaskMaxStackUsage Os_ResetTaskMaxStackUsage
  #define ResetISRMaxStackUsage Os_ResetISRMaxStackUsage
  #define GetStackValue Os_GetStackValue
  #define GetStackSize Os_GetStackSize
  #define AdvanceCounter Os_AdvanceCounter
  #define Restart Os_Restart
  #define SetRestartPoint Os_SetRestartPoint
#endif
#define ActivateTask Os_ActivateTask
#define ActivateTaskAsyn (void)Os_ActivateTask
#define GetTaskID Os_GetTaskID
#define GetTaskState Os_GetTaskState
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Schedule) */
#define Schedule() /* [$UKS 1277] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, ChainTask) */
#define ChainTask(x)  Os_ChainTask(x); return /* [$UKS 79] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, TerminateTask) */
#define OS_FAST_TASK_TERMINATION
#define TerminateTask()  return
#define SetEvent Os_SetEvent
#define SetEventAsyn (void)Os_SetEvent
#define ClearEvent Os_ClearEvent
#define GetEvent Os_GetEvent
#define WaitEvent Os_WaitEvent
#define GetResource Os_GetResource
#define ReleaseResource Os_ReleaseResource
#define DisableAllInterrupts Os_DisableAllInterrupts
#define EnableAllInterrupts Os_EnableAllInterrupts
#define SuspendAllInterrupts Os_SuspendAllInterrupts
#define ResumeAllInterrupts Os_ResumeAllInterrupts
#define SuspendOSInterrupts Os_SuspendOSInterrupts
#define ResumeOSInterrupts Os_ResumeOSInterrupts
#define GetISRID Os_GetISRID
#define GetActiveApplicationMode Os_GetActiveApplicationMode
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CheckObjectOwnership, CheckObjectAccess) */
#define CheckObjectOwnership(x,y) Os_CheckObjectOwnership((x),(Os_AnyType)(y))
#define CheckObjectAccess(x,y,z) Os_CheckObjectAccess((x),(y),(Os_AnyType)(z))
#define GetApplicationID Os_GetApplicationID
#define GetCurrentApplicationID Os_GetCurrentApplicationID
#define CallTrustedFunction Os_CallTrustedFunction
#define GetApplicationState Os_GetApplicationState
#define AllowAccess Os_AllowAccess
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CheckTaskMemoryAccess, CheckISRMemoryAccess) */
#define CheckTaskMemoryAccess(x,y,z) Os_CheckTaskMemoryAccess((x),(MemoryStartAddressType)(y),(MemorySizeType)(z))
#define CheckISRMemoryAccess(x,y,z) Os_CheckISRMemoryAccess((x),(MemoryStartAddressType)(y),(MemorySizeType)(z))
#define GetCounterValue Os_GetCounterValue
#define GetElapsedCounterValue Os_GetElapsedCounterValue /* AUTOSAR 3.x */
#define GetElapsedValue Os_GetElapsedCounterValue  /* AUTOSAR 4.x */
#define IncrementCounter Os_IncrementCounter
#define GetAlarmBase Os_GetAlarmBase
#define CancelAlarm Os_CancelAlarm
#define GetAlarm Os_GetAlarm
#define SetRelAlarm Os_SetRelAlarm
#define SetAbsAlarm Os_SetAbsAlarm
#define StopScheduleTable Os_StopScheduleTable
#define StartScheduleTableRel Os_StartScheduleTableRel
#define StartScheduleTableAbs Os_StartScheduleTableAbs
#define StartScheduleTableSynchron Os_StartScheduleTableSynchron
#define SyncScheduleTable Os_SyncScheduleTable
#define SetScheduleTableAsync Os_SetScheduleTableAsync
#define GetScheduleTableStatus Os_GetScheduleTableStatus
#define NextScheduleTable Os_NextScheduleTable
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, StartOS) */
#define StartOS(x) {if (Os_StartOS(x)) {while(Os_Cbk_Idle()) {} /* [$UKS 161] */; for(;;) {OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();} /* [$UKS 16] */}}
#define ShutdownOS Os_ShutdownOS
#define ControlIdle Os_ControlIdle
#define ReadPeripheral8 Os_ReadPeripheral8
#define WritePeripheral8 Os_WritePeripheral8
#define ModifyPeripheral8 Os_ModifyPeripheral8
#define ReadPeripheral16 Os_ReadPeripheral16
#define WritePeripheral16 Os_WritePeripheral16
#define ModifyPeripheral16 Os_ModifyPeripheral16
#define ReadPeripheral32 Os_ReadPeripheral32
#define WritePeripheral32 Os_WritePeripheral32
#define ModifyPeripheral32 Os_ModifyPeripheral32
#define EnableInterruptSource Os_EnableInterruptSource
#define DisableInterruptSource Os_DisableInterruptSource
#define ClearPendingInterrupt Os_ClearPendingInterrupt
#define TotalNumberOfCores Os_TotalNumberOfCores
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, GetCoreID) */
#define GetCoreID() ((CoreIdType)/*lint --e(9034) [MISRA 2012 Dir 10.3] Depends on CoreIdType size */OS_READ_COPROC(15, 0, 13, 0, 3))  /* [$UKS 1619] [$UKS 1620] [$UKS 1621] */
#define GetNumberOfActivatedCores Os_GetNumberOfActivatedCores
#define ShutdownAllCores Os_ShutdownAllCores
#define StartCore Os_StartCore
#define StartNonAutosarCore Os_StartNonAutosarCore
#define GetSpinlock Os_GetSpinlock
#define TryToGetSpinlock Os_TryToGetSpinlock
#define ReleaseSpinlock Os_ReleaseSpinlock
typedef StatusType   Os_TraceStatusType;
typedef uint8 Os_TraceDataType;
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TRACE*, Os_Log*, Os_Set*, Os_Clear*, Os_Trigger*, OSTRACE_*) */

#ifndef OS_TRACE
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_*Trace*, Os_*Trigger*) */
  #define Os_EnableTraceClasses(x) /* empty */
  #define Os_DisableTraceClasses(x) /* empty */
  #define Os_EnableTraceCategories(x) /* empty */
  #define Os_DisableTraceCategories(x) /* empty */
  #define Os_StartFreeRunningTrace() /* empty */
  #define Os_StartBurstingTrace() /* empty */
  #define Os_StartTriggeringTrace() /* empty */
  #define Os_StopTrace() /* empty */
  #define Os_CheckTraceOutput() /* empty */
  #define Os_SetTraceRepeat(x) /* empty */
  #define Os_TraceCommInit() /* empty */
  #define Os_UploadTraceData() /* empty */
  #define Os_TraceDumpAsync(x) /* empty */
  #define Os_SetTriggerConditions(x,y) /* empty */
  #define Os_SetTriggerConditionsN(x,y) /* empty */
  #define Os_SetTriggerConditionsTII(x,y) /* empty */
  #define Os_SetTriggerWindow(x,y) /* empty */
  #define Os_TriggerNow() /* empty */
#endif /* OS_TRACE */

/* Triggering */
#define Os_ClearTrigger()              Os_SetTriggerConditions(OS_TRACE_TRIGGER, 0)               /* [$UKS 1042] [$UKS 1043] [$UKS 1044] */

#define OS_TRACE_TRIGGER_ANY (&Os_TraceDummy)
#define Os_Cat1_OS_TRACE_TRIGGER_ANY (0)
#define Os_Tr_OS_TRACE_TRIGGER_ANY (0)
#define Os_TriggerOnActivation(x)      Os_SetTriggerConditions(OS_TRACE_ACTIVATION,     (x)->id) /* [$UKS 1050] [$UKS 1051] [$UKS 1266] */
#define Os_TriggerOnChain(x)           Os_SetTriggerConditions(OS_TRACE_CHAINACTIVATION,(x)->id) /* [$UKS 1052] [$UKS 1053] [$UKS 1179] */
#define Os_TriggerOnTaskStart(x)       Os_SetTriggerConditions(OS_TRACE_TASKSTART,      (x)->id) /* [$UKS 1054] [$UKS 1055] [$UKS 1056] */
#define Os_TriggerOnTaskStop(x)        Os_SetTriggerConditions(OS_TRACE_TASKEND,        (x)->id) /* [$UKS 1057] [$UKS 1058] [$UKS 1059] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnCat1ISRStart) */
#define Os_TriggerOnCat1ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,(Os_Cat1_##x)) /* [$UKS 1066] [$UKS 1067] [$UKS 1068] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnCat1ISRStop) */
#define Os_TriggerOnCat1ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,  (Os_Cat1_##x)) /* [$UKS 1069] [$UKS 1070] [$UKS 1071] */
#define Os_TriggerOnCat2ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,      (x)->id) /* [$UKS 1072] [$UKS 1073] [$UKS 1074] */
#define Os_TriggerOnCat2ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,        (x)->id) /* [$UKS 1075] [$UKS 1076] [$UKS 1077] */
#define Os_TriggerOnGetResource(x)     Os_SetTriggerConditions(OS_TRACE_GETRESOURCE,    (x)->id) /* [$UKS 1082] [$UKS 1083] [$UKS 1084] */
#define Os_TriggerOnReleaseResource(x) Os_SetTriggerConditions(OS_TRACE_RELEASERESOURCE,(x)->id) /* [$UKS 1085] [$UKS 1086] [$UKS 1087] */
#define Os_TriggerOnSetEvent(x)        Os_SetTriggerConditions(OS_TRACE_SETEVENT,       (x)->id) /* [$UKS 1088] [$UKS 1089] [$UKS 1090] */
#define Os_TriggerOnTracepoint(x)      Os_SetTriggerConditionsTII(OS_TRACE_POINT,       (x))     /* [$UKS 1091] [$UKS 1092] */
#define Os_TriggerOnTaskTracepoint(x,y) Os_SetTriggerConditions(OS_TRACE_TASKPOINT+(x),(y)->id)  /* [$UKS 1093] [$UKS 1094] [$UKS 1095] */
#define Os_TriggerOnIntervalStart(x)   Os_SetTriggerConditionsTII(OS_TRACE_STARTINTERVAL,(x))    /* [$UKS 1096] [$UKS 1097] */
#define Os_TriggerOnIntervalEnd(x)     Os_SetTriggerConditionsTII(OS_TRACE_ENDINTERVAL,  (x))    /* [$UKS 1098] [$UKS 1099] */
#define Os_TriggerOnIntervalStop(x)    Os_TriggerOnIntervalEnd(x)                                /* [$UKS 1100] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnAlarmExpiry) */
#define Os_TriggerOnAlarmExpiry(x)     Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x)) /* [$UKS 1106] [$UKS 1107] [$UKS 1108] */
#define Os_TriggerOnError(x)           Os_SetTriggerConditionsN(OS_TRACE_ERROR, (x))             /* [$UKS 1109] [$UKS 1110] [$UKS 1181] */
#define Os_TriggerOnShutdown(x)        Os_SetTriggerConditionsN(OS_TRACE_SHUTDOWN, (x))          /* [$UKS 1111] [$UKS 1112] [$UKS 1199] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnScheduleTableExpiry) */
#define Os_TriggerOnScheduleTableExpiry(x) Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x))  /* [$UKS 1200] [$UKS 1201] [$UKS 1202] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnIncrementCounter) */
#define Os_TriggerOnIncrementCounter(x) Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x)) /* [$UKS 1203] [$UKS 1204] [$UKS 1208] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnAdvanceCounter) */
#define Os_TriggerOnAdvanceCounter(x)   Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x)) /* [$UKS 1205] [$UKS 1206] [$UKS 1207] */

#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
  #define EnableTraceClasses Os_EnableTraceClasses
  #define DisableTraceClasses Os_DisableTraceClasses
  #define EnableTraceCategories Os_EnableTraceCategories
  #define DisableTraceCategories Os_DisableTraceCategories
  #define StartFreeRunningTrace Os_StartFreeRunningTrace
  #define StartBurstingTrace Os_StartBurstingTrace
  #define StartTriggeringTrace Os_StartTriggeringTrace
  #define StopTrace Os_StopTrace
  #define CheckTraceOutput Os_CheckTraceOutput
  #define SetTraceRepeat Os_SetTraceRepeat
  #define SetTriggerConditions Os_SetTriggerConditions
  #define TraceCommInit Os_TraceCommInit
  #define TraceCommInitTarget Os_Cbk_TraceCommInitTarget
  #define TraceCommDataReady Os_Cbk_TraceCommDataReady
  #define UploadTraceData Os_UploadTraceData
  #define SetTriggerWindow Os_SetTriggerWindow
  #define ClearTrigger Os_ClearTrigger
  #define TriggerNow  Os_TriggerNow

  #define TriggerOnActivation Os_TriggerOnActivation
  #define TriggerOnChain Os_TriggerOnChain
  #define TriggerOnTaskStart Os_TriggerOnTaskStart
  #define TriggerOnTaskStop Os_TriggerOnTaskStop
  #define TriggerOnCat1ISRStart Os_TriggerOnCat1ISRStart
  #define TriggerOnCat1ISRStop Os_TriggerOnCat1ISRStop
  #define TriggerOnCat2ISRStart Os_TriggerOnCat2ISRStart
  #define TriggerOnCat2ISRStop Os_TriggerOnCat2ISRStop
  #define TriggerOnGetResource Os_TriggerOnGetResource
  #define TriggerOnReleaseResource Os_TriggerOnReleaseResource
  #define TriggerOnSetEvent Os_TriggerOnSetEvent
  #define TriggerOnTracepoint Os_TriggerOnTracepoint
  #define TriggerOnIntervalStart Os_TriggerOnIntervalStart
  #define TriggerOnIntervalEnd Os_TriggerOnIntervalEnd
  #define TriggerOnIntervalStop Os_TriggerOnIntervalStop
  #define TriggerOnTaskTracepoint Os_TriggerOnTaskTracepoint
  #define TriggerOnAlarmExpiry Os_TriggerOnAlarmExpiry
  #define TriggerOnScheduleTableExpiry Os_TriggerOnScheduleTableExpiry
  #define TriggerOnIncrementCounter Os_TriggerOnIncrementCounter
  #define TriggerOnAdvanceCounter Os_TriggerOnAdvanceCounter
  #define TriggerOnError Os_TriggerOnError
  #define TriggerOnShutdown Os_TriggerOnShutdown
#endif

extern FUNC(Os_TraceStatusType, OS_CALLOUT_CODE) Os_Cbk_TraceCommInitTarget(void) /* [$UKS 1209]*/;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommDataReady(void) /* [$UKS 1212] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxStart(void) /* [$UKS 1214] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxByte(Os_TraceDataType val) /* [$UKS 1211] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxEnd(void) /* [$UKS 1213] */;
extern FUNC(boolean, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxReady(void) /* [$UKS 1215] */;



typedef struct Os_ControlledCoreType_s {
  Os_ErrorInformationType ErrorInformation;
  OS_VOLATILE Os_Lockable lock_taskaccess;
  OS_VOLATILE Os_psetType ReadyTasks ;
  OS_VOLATILE ISRType RunningISR;
  OS_VOLATILE TaskType RunningTask;
  OS_VOLATILE Os_tpmaskType RunningTPMask ;
  Os_MeterInfoRefType CurrentMeteredObject;
  Os_MeterInfoType IdleMeter;
  uint8 AppAccess;
  OS_VOLATILE ApplicationType AppOverride;
  Os_StackSizeType GetStackValueAdjust;
  boolean InErrorHook;
  OS_VOLATILE TaskType ChainTaskRef;
  boolean CoreIsActive;
} Os_ControlledCoreType;
#define Os_lock_taskaccess (os_current_controlled_core->lock_taskaccess)
#define Os_ReadyTasks /*lint --e(9018) A union type */ (os_current_controlled_core->ReadyTasks /*lint --e(9018) A union type */)
#define Os_RunningISR (os_current_controlled_core->RunningISR)
#define Os_RunningTask (os_current_controlled_core->RunningTask)
#define Os_RunningTPMask /*lint --e(9018) A union type */ (os_current_controlled_core->RunningTPMask /*lint --e(9018) A union type */)
#define Os_CurrentMeteredObject (os_current_controlled_core->CurrentMeteredObject)
#define Os_IdleMeter (os_current_controlled_core->IdleMeter)
#define Os_AppAccess (os_current_controlled_core->AppAccess)
#define Os_AppOverride (os_current_controlled_core->AppOverride)
#define Os_ErrorInformation (Os_const_coreconfiguration[OS_READ_COPROC(15, 0, 13, 0, 3)].controlled->ErrorInformation)
typedef struct Os_AnyCoreType_s {
  OS_VOLATILE Os_imaskType DisableAllImask;
  OS_VOLATILE Os_imaskType SuspendAllImask;
  OS_VOLATILE Os_imaskType SuspendOSImask;
  OS_VOLATILE uint32 DisableAllCount;
  OS_VOLATILE uint32 SuspendAllCount;
  OS_VOLATILE uint32 SuspendOSCount;
  OS_VOLATILE Os_OrtiIdType OrtiApiID;
  StatusType OrtiLastError;
} Os_AnyCoreType;
#define Os_DisableAllImask (os_current_core->DisableAllImask)
#define Os_SuspendAllImask (os_current_core->SuspendAllImask)
#define Os_SuspendOSImask (os_current_core->SuspendOSImask)
#define Os_DisableAllCount (os_current_core->DisableAllCount)
#define Os_SuspendAllCount (os_current_core->SuspendAllCount)
#define Os_SuspendOSCount (os_current_core->SuspendOSCount)
#define Os_OrtiApiID (os_current_core->OrtiApiID)
#define Os_OrtiLastError (os_current_core->OrtiLastError)
typedef struct Os_CoreConfiguration_s {
  CONSTP2VAR(Os_ControlledCoreType, OS_VAR, OS_CONST) controlled;
  CONSTP2VAR(Os_AnyCoreType, OS_VAR, OS_CONST) any;
  CONSTP2VAR(OS_VOLATILE Os_CoreStateType, OS_VAR, OS_CONST) state;
  Os_VoidVoidFunctionType dispatch;
  CoreIdType core_id;
} Os_CoreConfiguration;
#define Os_Dispatch (os_current_core_const->dispatch)

extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks0[];


extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks1[];


extern FUNC(void, OS_CALLOUT_CODE) ErrorHook(StatusType Error) /* [$UKS 479] [$UKS 1943] */;
extern FUNC(void, OS_CALLOUT_CODE) PreTaskHook(void) /* [$UKS 175] [$UKS 179]  [$UKS 1943] */;
extern FUNC(void, OS_CALLOUT_CODE) PostTaskHook(void) /* [$UKS 176] [$UKS 180] [$UKS 1943] */;
extern FUNC(ProtectionReturnType, OS_CALLOUT_CODE) ProtectionHook(StatusType FatalError) /* [$UKS 1943] */;
extern FUNC(void, OS_CALLOUT_CODE) StartupHook(void) /* [$UKS 24] [$UKS 1943] */;
extern FUNC(void, OS_CALLOUT_CODE) ShutdownHook(StatusType Error) /* [$UKS 18] [$UKS 1943] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_StackOverrunHook(Os_StackSizeType Overrun, Os_StackOverrunType Reason);
extern FUNC(AccessType, OS_CALLOUT_CODE) Os_Cbk_CheckMemoryAccess(ApplicationType Application, TaskType TaskID, ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
extern FUNC(boolean, OS_CALLOUT_CODE) Os_Cbk_Idle(void) /* [$UKS 161] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_InShutdown(void) /* internal use */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CheckStackDepth(CoreIdType Core_id, Os_StackSizeType Depth, Os_StackSizeType CurrentPos);
#ifndef Os_Cbk_GetStopwatch
 extern FUNC(Os_StopwatchTickType, OS_CALLOUT_CODE) Os_Cbk_GetStopwatch(void) /* [$UKS 536] */;
#endif
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TimeOverrunHook(Os_StopwatchTickType Overrun) /* [$UKS 537] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskStart(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskEnd(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISRStart(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISREnd(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISRStart(ISRType isr);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISREnd(ISRType isr);


extern OS_VOLATILE VAR(AppModeType, OS_VAR_CLEARED) Os_CurrentAppMode;
extern VAR(Os_AnyCoreType, OS_VAR_CLEARED) Os_AnyCoreInfo[];


extern VAR(StatusType, OS_VAR_NO_INIT) Os_ShutdownAllCores_Indicator;
extern VAR(ApplicationStateType, OS_VAR_NO_INIT) Os_dyn_appstate[];
extern VAR(Os_TaskDynType, OS_VAR_NO_INIT) Os_dyn_tasks[];
extern VAR(Os_ISRDynType, OS_VAR_NO_INIT) Os_dyn_isrs[];
extern VAR(Os_ControlledCoreType, OS_VAR_NO_INIT) Os_ControlledCoreInfo[];


extern CONST(CoreIdType, OS_CONST_FAST) Os_TotalNumberOfCores;
extern CONST(Os_CoreConfiguration, OS_CONST_FAST) Os_const_coreconfiguration[];
extern CONST(Os_ApplicationConfigurationType, OS_CONST_FAST) Os_const_applications[];
extern CONST(Os_ISRType, OS_CONST_FAST) Os_const_isrs[];
extern CONST(TaskType, OS_CONST_FAST) Os_const_tasks[];
extern CONST(Os_ResourceType, OS_CONST_FAST) Os_const_resources[];


extern CONSTP2VAR(OS_VOLATILE TaskType, OS_VAR, OS_CONST) Os_OrtiRunningTask0;
extern CONSTP2VAR(OS_VOLATILE ISRType,  OS_VAR, OS_CONST) Os_OrtiRunningISR0;
extern CONSTP2VAR(OS_VOLATILE Os_tpmaskType, OS_VAR, OS_CONST) Os_OrtiRunningTPMask0;
extern CONSTP2VAR(StatusType, OS_VAR, OS_CONST) Os_OrtiLastError0;
extern CONSTP2VAR(OS_VOLATILE Os_OrtiIdType, OS_VAR, OS_CONST) Os_OrtiApiID0;
extern CONSTP2VAR(OS_VOLATILE TaskType, OS_VAR, OS_CONST) Os_OrtiRunningTask1;
extern CONSTP2VAR(OS_VOLATILE ISRType,  OS_VAR, OS_CONST) Os_OrtiRunningISR1;
extern CONSTP2VAR(OS_VOLATILE Os_tpmaskType, OS_VAR, OS_CONST) Os_OrtiRunningTPMask1;
extern CONSTP2VAR(StatusType, OS_VAR, OS_CONST) Os_OrtiLastError1;
extern CONSTP2VAR(OS_VOLATILE Os_OrtiIdType, OS_VAR, OS_CONST) Os_OrtiApiID1;


extern FUNC(void, OS_CODE) Os_GetVersionInfo(Std_VersionInfoType *versioninfo) /* [$UKS 731] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetExecutionTime(void) /* [$UKS 538] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskMaxExecutionTime(TaskType TaskID) /* [$UKS 543] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRMaxExecutionTime(ISRType ISRID) /* [$UKS 548] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxExecutionTime(TaskType TaskID) /* [$UKS 553] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxExecutionTime(ISRType ISRID) /* [$UKS 555] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetElapsedTime(void) /* [$UKS 1855] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskElapsedTime(TaskType TaskID) /* [$UKS 1859] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRElapsedTime(ISRType ISRID) /* [$UKS 1863] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetIdleElapsedTime(Os_IdleType IdleID) /* [$UKS 1867] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskElapsedTime(TaskType TaskID) /* [$UKS 1871] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRElapsedTime(ISRType ISRID) /* [$UKS 1876] */;
extern FUNC(StatusType, OS_CODE) Os_ResetIdleElapsedTime(Os_IdleType IdleID) /* [$UKS 1881] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackUsage(void) /* [$UKS 1238] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetTaskMaxStackUsage(TaskType TaskID) /* [$UKS 1242] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetISRMaxStackUsage(ISRType ISRID) /* [$UKS 1247] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxStackUsage(TaskType TaskID) /* [$UKS 1252] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxStackUsage(ISRType ISRID) /* [$UKS 1257] */;
extern FUNC(Os_StackValueType, OS_CODE) Os_GetStackValue(void) /* [$UKS 1263] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackSize(Os_StackValueType Base, Os_StackValueType Sample) /* [$UKS 1264] */;
extern FUNC(StatusType, OS_CODE) Os_ActivateTask(TaskType TaskID) /* [$UKS 61] */;
extern FUNC(StatusType, OS_CODE) Os_GetTaskID(TaskRefType TaskID) /* [$UKS 86] */;
extern FUNC(StatusType, OS_CODE) Os_GetTaskState(TaskType TaskID, TaskStateRefType State) /* [$UKS 89] */;
extern FUNC(StatusType, OS_CODE) Os_Schedule(void) /* [$UKS 83] */;
extern FUNC(StatusType, OS_CODE) Os_SetEvent(TaskType TaskID, EventMaskType Mask) /* [$UKS 144] */;
extern FUNC(StatusType, OS_CODE) Os_ClearEvent(EventMaskType Mask) /* [$UKS 148] */;
extern FUNC(StatusType, OS_CODE) Os_GetEvent(TaskType TaskID, EventMaskRefType Mask) /* [$UKS 150] */;
extern FUNC(StatusType, OS_CODE) Os_WaitEvent(EventMaskType Mask) /* [$UKS 153] */;
extern FUNC(StatusType, OS_CODE) Os_GetResource(ResourceType ResID) /* [$UKS 204] */;
extern FUNC(StatusType, OS_CODE) Os_ReleaseResource(ResourceType ResID) /* [$UKS 207] */;
extern FUNC(void, OS_CODE) Os_DisableAllInterrupts(void) /* [$UKS 113] */;
extern FUNC(void, OS_CODE) Os_EnableAllInterrupts(void) /* [$UKS 110] */;
extern FUNC(void, OS_CODE) Os_SuspendAllInterrupts(void) /* [$UKS 121] */;
extern FUNC(void, OS_CODE) Os_ResumeAllInterrupts(void) /* [$UKS 116] */;
extern FUNC(void, OS_CODE) Os_SuspendOSInterrupts(void) /* [$UKS 128] */;
extern FUNC(void, OS_CODE) Os_ResumeOSInterrupts(void) /* [$UKS 124] */;
extern FUNC(ISRType, OS_CODE) Os_GetISRID(void) /* [$UKS 130] */;
extern FUNC(AppModeType, OS_CODE) Os_GetActiveApplicationMode(void) /* [$UKS 384] */;
extern FUNC(ApplicationType, OS_CODE) Os_CheckObjectOwnership(ObjectTypeType ObjectType, Os_AnyType Object) /* $UKS 438 */;
extern FUNC(ObjectAccessType, OS_CODE) Os_CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, Os_AnyType Object) /* $UKS 425 */;
extern FUNC(ApplicationType, OS_CODE) Os_GetApplicationID(void) /* [$UKS 417] */;
extern FUNC(ApplicationType, OS_CODE) Os_GetCurrentApplicationID(void) /* [$UKS 2004] */;
extern FUNC(StatusType, OS_CODE) Os_TerminateTask(void) /* [$UKS 66] */;
extern FUNC(AccessType, OS_CODE) Os_CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size) /* [$UKS 595] */;
extern FUNC(AccessType, OS_CODE) Os_CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size) /* [$UKS 596] */;
extern FUNC(StatusType, OS_CODE) Os_GetCounterValue(CounterType CounterID, TickRefType Value) /* [$UKS 226] */;
extern FUNC(StatusType, OS_CODE) Os_GetElapsedCounterValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue) /* [$UKS 231] */;
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter(CounterType CounterID) /* [$UKS 238] */;
extern FUNC(StatusType, OS_CODE) Os_AdvanceCounter(CounterType CounterID) /* [$UKS 858] */;
extern FUNC(StatusType, OS_CODE) Os_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info) /* [$UKS 282] */;
extern FUNC(StatusType, OS_CODE) Os_CancelAlarm(AlarmType AlarmID) /* [$UKS 300] */;
extern FUNC(StatusType, OS_CODE) Os_GetAlarm(AlarmType AlarmID, TickRefType Tick) /* [$UKS 285] */;
extern FUNC(StatusType, OS_CODE) Os_SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle) /* [$UKS 288] */;
extern FUNC(StatusType, OS_CODE) Os_SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle) /* [$UKS 294] */;
extern FUNC(StatusType, OS_CODE) Os_StopScheduleTable(ScheduleTableType ScheduleTableID) /* [$UKS 341] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset) /* [$UKS 329] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start) /* [$UKS 336] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableSynchron(ScheduleTableType ScheduleTableID) /* [$UKS 362] */;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value) /* [$UKS 368] */;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTableRel(ScheduleTableType ScheduleTableID, SignedTickType RelativeValue) /* [$UKS 1885] */;
extern FUNC(StatusType, OS_CODE) Os_SetScheduleTableAsync(ScheduleTableType ScheduleTableID) /* [$UKS 376] */;
extern FUNC(StatusType, OS_CODE) Os_GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus) /* [$UKS 354] */;
extern FUNC(StatusType, OS_CODE) Os_NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To) /* [$UKS 345] */;
extern FUNC(boolean, OS_CODE) Os_StartOS(AppModeType Mode) /* [$UKS 19] */;
extern FUNC(void, OS_CODE) Os_ShutdownOS(StatusType Error) /* [$UKS 20] */;
extern FUNC(void, OS_CODE) Os_ProtectionLog(StatusType os_status);
extern FUNC(StatusType, OS_CODE) Os_ControlIdle(CoreIdType CoreID, IdleModeType IdleMode) /* [$UKS 1911] */;
extern FUNC(IdleModeType, OS_CODE) Os_CurrentIdleMode(void);
extern FUNC(uint32, OS_CODE) Os_GetCurrentTPL(void) /* [$UKS 2012] */;
extern FUNC(Os_imaskType, OS_CODE) Os_GetCurrentIMask(void) /* [$UKS 2016] */;
extern FUNC(StatusType, OS_CODE) Os_EnableInterruptSource(ISRType ISRID, boolean ClearPending) /* [$UKS 2126] */;
extern FUNC(StatusType, OS_CODE) Os_DisableInterruptSource(ISRType ISRID) /* [$UKS 2133] */;
extern FUNC(StatusType, OS_CODE) Os_ClearPendingInterrupt(ISRType ISRID) /* [$UKS 2140] */;
extern FUNC(uint32, OS_CODE) Os_GetNumberOfActivatedCores(void) /* [$UKS 1622] */;
extern FUNC(void, OS_CODE) Os_ShutdownAllCores(StatusType Error) /* [$UKS 1518] */;
extern FUNC(void, OS_CODE) Os_StartCore(CoreIdType CoreID, Os_StatusRefType Status) /* [$UKS 1626] */;
extern FUNC(StatusType, OS_CODE) Os_GetSpinlock(SpinlockIdType SpinlockId) /* [$UKS 1649] */;
extern FUNC(StatusType, OS_CODE) Os_TryToGetSpinlock(SpinlockIdType SpinlockId, TryToGetSpinlockType* Success) /* [$UKS 1665] */;
extern FUNC(StatusType, OS_CODE) Os_ReleaseSpinlock(SpinlockIdType SpinlockId) /* [$UKS 1680] */;
extern FUNC(void, OS_CODE) Os_CrossCoreCheck(Os_ControlledCoreType *os_current_controlled_core, const Os_CoreConfiguration *os_current_core_const);
extern FUNC(StatusType, OS_CODE) Os_ScheduleQ(void);
extern FUNC(StatusType, OS_CODE) Os_ChainTask(TaskType TaskID) /* [$UKS 73] */;
extern FUNC(StatusType, OS_CODE) Os_GetTaskActivationTime(TaskType TaskID, Os_StopwatchTickRefType Value) /* [$UKS 1283] */;
extern FUNC(StatusType, OS_CODE) Os_GetApplicationState(ApplicationType Application, ApplicationStateRefType Value) /* [$UKS 1301] */;
extern FUNC(StatusType, OS_CODE) Os_AllowAccess(void) /* [$UKS 1305] */;
extern FUNC(StatusType, OS_CODE) Os_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams) /* [$UKS 601] */;
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral8(AreaIdType Area, Os_uint8ConstRefType Address, Os_uint8RefType ReadValue) /* [$UKS 2054] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral8(AreaIdType Area, Os_uint8RefType Address, uint8 WriteValue) /* [$UKS 2078] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral8(AreaIdType Area, Os_uint8RefType Address, uint8 Clearmask, uint8 Setmask) /* [$UKS 2102] */;
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral16(AreaIdType Area, Os_uint16ConstRefType Address, Os_uint16RefType ReadValue) /* [$UKS 2062] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral16(AreaIdType Area, Os_uint16RefType Address, uint16 WriteValue) /* [$UKS 2086] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral16(AreaIdType Area, Os_uint16RefType Address, uint16 Clearmask, uint16 Setmask) /* [$UKS 2110] */;
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral32(AreaIdType Area, Os_uint32ConstRefType Address, Os_uint32RefType ReadValue) /* [$UKS 2070] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral32(AreaIdType Area, Os_uint32RefType Address, uint32 WriteValue) /* [$UKS 2094] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral32(AreaIdType Area, Os_uint32RefType Address, uint32 Clearmask, uint32 Setmask) /* [$UKS 2118] */;




#include <Os_Cfg.h> /* [$UKS 649] */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OS_H */

