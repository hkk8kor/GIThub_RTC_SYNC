/*
 * This is Os.h, auto-generated for:
 *   Project: rtaos_ccas_mcore_sc4_vmps
 *   Target:  RH850GHS
 *   Variant: P1HC
 *   Version: 5.0.36
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
#define OS_TARGET_PORT "RH850GHS"
#define OS_TARGET_PORT_RH850GHS
#define OS_TARGET_MAJOR_VERSION (5U)
#define OS_TARGET_MINOR_VERSION (0U)
#define OS_TARGET_PATCH_VERSION (36U)

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
/* Use the intrinsic function from the GHS header files */
/* [$Satisfies $TargetGHS 422] */
#ifndef _lint /* Do not run lint/MISRA checking on 3rd party header files */
  #include <v800_ghs.h>
  #include <ghs_barrier.h>
#endif /* !_lint */

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CAT1_ISR, OS_MAIN, OS_BARRIER, OS_CLR, OS_DBTAG, OS_DI, OS_EI, OS_LDL_W, OS_LDSR, OS_NOP, OS_SCH1L, OS_SCH0L, OS_SET, OS_SNOOZE, OS_STSR, OS_SYNCE, OS_SYNCI, OS_SYNCM, OS_SYNCP, OS_STC_W, OS_TRAP) */
/* CAT1_ISR, OS_MAIN, OS_BARRIER, OS_CLR, OS_DBTAG, OS_DI, OS_EI, OS_LDL_W,
   OS_LDSR, OS_NOP, OS_SCH1L, OS_SCH0L, OS_SET, OS_SNOOZE, OS_STSR, OS_SYNCE,
   OS_SYNCI, OS_SYNCM, OS_SYNCP, OS_STC_W, OS_TRAP */

#define OS_MAIN() extern void main(void); void main(void) /* [$Satisfies $TgtCore 56] */

/* Call before StartOS() to initialize the INTC EICn priority settings.  Also
 * enables interrupts (PSW.ID bit) after setting the INTC priority threshold to
 * lock out Category 2 ISRs until after initialization. */
/* Support functions used in the macros in the header file Os_Trust.h so must
 * be user visible */
/* Lint/MISRA checking has a problem with the compiler intrinsic functions so
 * obscure this when lint checking */
 #ifdef _lint
 /* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_trap) */
#define Os_trap()
 #else
/* [$Satisfies $TargetCS 111][$Satisfies $TargetGHS 159][$Satisfies $TargetWR 107] */
/* Uses OS_BARRIER to prevent code re-ordering */
/* [$Satisfies $TargetGHS 243] */
#define Os_trap() {OS_BARRIER(); OS_TRAP(0U); OS_SYNCE(); OS_BARRIER();}
 #endif /* _lint */



#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif


/* [$Satisfies $TargetCS 170][$Satisfies $TargetGHS 125][$Satisfies $TargetWR 161]
 * [$Satisfies $TargetCS 172][$Satisfies $TargetGHS 127][$Satisfies $TargetWR 163] */
/* [$Satisfies $TgtCore 55] */

/* [MISRA 2004 Rule 1.3] */ /*lint -estring(9023, CAT1_ISR) */
/* Relates to CAT1_ISR macro */
/* [MISRA 2004 Rule 20.1000000000000] */ /*lint -estring(9024, CAT1_ISR) */
/* Relates to CAT1_ISR macro */

#define CAT1_ISR(x)\
__inline static void Os_inline_##x(void);\
void x(void) {\
  OS_VOLATILE uint32 prev_isr = OS_CAT1_TRACKER_##x;\
  OS_CAT1_TRACKER_##x = OS_CAT1_ID_##x;\
  Os_inline_##x();\
  OS_CAT1_TRACKER_##x = prev_isr;\
}\
static void Os_inline_##x(void)

/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(StatusType, OS_CALLOUT_CODE) Os_Cbk_StartCore(uint16 CoreID);
extern FUNC(StatusType, OS_CALLOUT_CODE) Os_Cbk_AwaitStartup(void);
extern FUNC(StatusType, OS_CALLOUT_CODE) Os_Cbk_StopCore(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CODE) Os_InitializeVectorTable(void);
/* [$Satisfies $TargetCS 113][$Satisfies $TargetGHS 161] */
extern FUNC(uint32, OS_CODE) Os_CPUMode(void);
extern FUNC(StatusType, OS_CODE) Os_AwaitStartup(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE_FAST
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* Support function in multi-core applications to determine the Core ID in an
 * untrusted function */
/* [$Satisfies $TargetCS 136][$Satisfies $TargetGHS 209][$Satisfies $TargetWR 130] */
extern FUNC(uint16, OS_CODE_FAST) Os_TgtCoreID(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE_FAST
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern OS_VOLATILE VAR(uint32, OS_VAR_NO_INIT) Os_StartCoreVar;
extern OS_VOLATILE VAR(uint32, OS_VAR_NO_INIT) Os_RunningCat1ISR0;
extern OS_VOLATILE VAR(uint32, OS_VAR_NO_INIT) Os_RunningCat1ISR1;
/* [$Satisfies $TargetGHS 316] */
/* The 'safe' stack pointer values used for 'Enhanced Isolation' */
extern VAR(void *, OS_VAR_NO_INIT) Os_EnhancedIsolationStack[2];
/* [$Satisfies $TargetGHS 267] */
/* The context buffer used for 'Enhanced Isolation' */
typedef struct {
  uint32 r30_val;
  uint32 r19_val;
  uint32 r18_val;
  uint32 r17_val;
  uint32 r16_val;
  uint32 r15_val;
  uint32 r14_val;
  uint32 r13_val;
  uint32 r12_val;
  uint32 r11_val;
  uint32 r10_val;
  uint32 r9_val;
  uint32 r8_val;
  uint32 r7_val;
  uint32 r6_val;
  uint32 r1_val;
  uint32 r31_val;
  uint32 r3_val;
} Os_EIContextBuffType;
/* MMRs defines and function prototypes used by the RTA-OS library code */
/* RH850 system register codes for use with __STSR/__LDSR intrinsics */
/* Can't combine both of the regID and the selID as used differently in loads and saves */
/* [$Satisfies $TargetCS 94][$Satisfies $TargetGHS 72][$Satisfies $TargetWR 92] */
#define OS_SELID_0 (0U)
/* Lint/MISRA checking has a problem with the compiler intrinsic functions so
 * obscure this when lint checking */
#ifdef _lint
  /*lint -esym(752,OS_SCH0L) allow to be unreferenced */
  /*lint -esym(752,OS_SCH1L) allow to be unreferenced */
  /*lint -esym(752,OS_SET) allow to be unreferenced */
  /*lint -esym(752,OS_CLR) allow to be unreferenced */
  /*lint -esym(752,OS_LDL_W) allow to be unreferenced */
  /*lint -esym(752,OS_STC_W) allow to be unreferenced */
  /*lint -esym(752,OS_LDSR) allow to be unreferenced */
  /*lint -esym(752,OS_STSR) allow to be unreferenced */
  /*lint -esym(752,OS_DI) allow to be unreferenced */
  /*lint -esym(752,OS_EI) allow to be unreferenced */
  /*lint -esym(752,OS_DBTAG) allow to be unreferenced */
  /*lint -esym(752,OS_SNOOZE) allow to be unreferenced */
  /*lint -esym(752,OS_SYNCE) allow to be unreferenced */
  /*lint -esym(752,OS_SYNCI) allow to be unreferenced */
  /*lint -esym(752,OS_SYNCM) allow to be unreferenced */
  /*lint -esym(752,OS_SYNCP) allow to be unreferenced */
  extern uint32 OS_SCH0L(uint32 val);
  extern uint32 OS_SCH1L(uint32 val);
  extern void OS_SET(OS_VOLATILE char *addr, uint32 bitnum);
  extern void OS_CLR(OS_VOLATILE char *addr, uint32 bitnum);
  extern sint32 OS_LDL_W(sint32 *addr);
  extern sint32 OS_STC_W(sint32 val, sint32 *addr);
  extern void OS_LDSR(uint16 regID, uint32 selID, uint32 val);
  extern uint32 OS_STSR(uint16 regID, uint32 selID);
  extern void OS_DI(void);
  extern void OS_EI(void);
  extern void OS_DBTAG(uint32 val);
  extern void OS_SNOOZE(void);
  extern void OS_SYNCE(void);
  extern void OS_SYNCI(void);
  extern void OS_SYNCM(void);
  extern void OS_SYNCP(void);
  /*lint -esym(752,OS_BARRIER) allow to be unreferenced */
  extern void OS_BARRIER(void);
  /*lint -esym(752,OS_NOP) allow to be unreferenced */
  /*lint -esym(752,os_trap) allow to be unreferenced */
  extern void OS_NOP(void);
  extern void os_trap(uint32 value);
#else /* _lint */
  #define OS_NOP() __asm("nop");
#ifndef __cplusplus
void os_trap(uint32 value);
static __asmleaf void os_trap(uint32 value)
{
%con value
  trap value
%error
  Macro has not expanded so it should result in error
}
#endif /* __cplusplus */
  /* Map onto the GHS compiler intrinsic functions. */
  #define OS_SCH0L(value) __SCH0L((uint32)(value))
  #define OS_SCH1L(value) __SCH1L((uint32)(value))
  #define OS_SET(addr, bit) __SET1((addr), (uint32)(bit))
  #define OS_CLR(addr, bit) __CLR1((addr), (uint32)(bit))
  #define OS_LDL_W(addr) __LDL_W(addr)
  #define OS_STC_W(val, addr) __STC_W((val), (addr))
  #define OS_LDSR(reg, bank, val) __LDSR((sint32)(reg), (sint32)(bank), (val))
  #define OS_STSR(reg, bank) __STSR((sint32)(reg), (sint32)(bank))
  #define OS_DI() __DI()
  #define OS_EI() __EI()
  #define OS_DBTAG(value) __DBTAG((uint32)(value))
  #define OS_SNOOZE() __SNOOZE()
  #define OS_SYNCE() __SYNCE()
  #define OS_SYNCI() __SYNCI()
  #define OS_SYNCM() __SYNCM()
  #define OS_SYNCP() __SYNCP()
  #define OS_BARRIER() __memory_changed()
  #define OS_TRAP(val) os_trap(val)
#endif /* _lint */
/* [$Satisfies $TgtCore 55] */
/* Lint/MISRA checking not applicable to asm so obscure this when lint checking */
#ifdef _lint
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_FETRAP_ENTRY, OS_FETRAP_LEAVE, OS_PRAGMA, OS_FETRAP_EXCEPTION) */
/* OS_FETRAP_ENTRY, OS_FETRAP_LEAVE, OS_PRAGMA, OS_FETRAP_EXCEPTION */
#else
/* The GHS compiler does not currently support FE interrupt handlers supply
 * defines to work round this deficiency from RH850 sample apps */
/* [$Satisfies $TargetGHS 45] */
/* [$Satisfies $TargetGHS 204] */
#pragma asm
#if (__V800_registermode==22)
    .set  regframe, 18
#endif
#if (__V800_registermode==26)
    .set  regframe, 20
#endif
#if (__V800_registermode==32)
    .set  regframe, 23
#endif
    .set  framesize, regframe*4
#pragma endasm
#ifndef __cplusplus
  void OS_FETRAP_ENTRY(void);
#endif /* __cplusplus */
static asm void OS_FETRAP_ENTRY(void)
{
    -- isr prolog
    -- 22 reg mode: save 15 registers + FEPSW + FEPC  + FPSR + FPEPC 
    -- 26 reg mode: save 17 registers + FEPSW + FEPC  + FPSR + FPEPC 
    -- 32 reg mode: save 20 registers + FEPSW + FEPC  + FPSR + FPEPC 
    prepare   {ep-lp}, regframe, sp
    sst.w     r1,  (framesize-4)[ep]
    stsr      FEPSW, r1, 0
    sst.w     r1,  (framesize-8)[ep]
    stsr      FEPC, r1, 0
    sst.w     r1,  (framesize-12)[ep]
    sst.w     r2,  (framesize-16)[ep]
    sst.w     gp,  (framesize-20)[ep]
    sst.w     r5,  (framesize-24)[ep]
    sst.w     r6,  (framesize-28)[ep]
    sst.w     r7,  (framesize-32)[ep]
    sst.w     r8,  (framesize-36)[ep]
    sst.w     r9,  (framesize-40)[ep]
    sst.w     r10, (framesize-44)[ep]
    sst.w     r11, (framesize-48)[ep]
    sst.w     r12, (framesize-52)[ep]
    sst.w     r13, (framesize-56)[ep]
    sst.w     r14, (framesize-60)[ep]
    stsr      FPSR, r1, 0
    sst.w     r1,  (framesize-64)[ep]
    stsr      FPEPC, r1, 0
    sst.w     r1,  (framesize-68)[ep]
#if (__V800_registermode==26)
    sst.w     r15, (framesize-72)[ep]
    sst.w     r16, (framesize-76)[ep]
#endif
#if (__V800_registermode==32)
    sst.w     r15, (framesize-72)[ep]
    sst.w     r16, (framesize-76)[ep]
    sst.w     r17, (framesize-80)[ep]
    sst.w     r18, (framesize-84)[ep]
    sst.w     r19, (framesize-88)[ep]
#endif
}
#ifndef __cplusplus
void OS_FETRAP_LEAVE(void);
#endif /* __cpluscplus */
static asm void OS_FETRAP_LEAVE(void)
{
    mov       sp, ep
#if (__V800_registermode==32)
    sld.w     (framesize-88)[ep], r19
    sld.w     (framesize-84)[ep], r18
    sld.w     (framesize-80)[ep], r17
    sld.w     (framesize-76)[ep], r16
    sld.w     (framesize-72)[ep], r15
#endif
#if (__V800_registermode==26)
    sld.w     (framesize-76)[ep], r16
    sld.w     (framesize-72)[ep], r15
#endif
    sld.w     (framesize-60)[ep], r14
    sld.w     (framesize-56)[ep], r13
    sld.w     (framesize-52)[ep], r12
    sld.w     (framesize-48)[ep], r11
    sld.w     (framesize-44)[ep], r10
    sld.w     (framesize-40)[ep], r9
    sld.w     (framesize-36)[ep], r8
    sld.w     (framesize-32)[ep], r7
    sld.w     (framesize-28)[ep], r6
    sld.w     (framesize-24)[ep], r5
    sld.w     (framesize-20)[ep], gp
    sld.w     (framesize-16)[ep], r2
    di
    sld.w     (framesize-68)[ep], r1
    ldsr      r1, FPEPC, 0
    sld.w     (framesize-64)[ep], r1
    ldsr      r1, FPSR, 0
    sld.w     (framesize-12)[ep], r1
    ldsr      r1, FEPC, 0
    sld.w     (framesize-8)[ep], r1
    ldsr      r1, FEPSW, 0
    sld.w     (framesize-4)[ep], r1
    dispose   regframe, {ep-lp}
    feret
}
#define OS_PRAGMA(x) _Pragma(#x)
#endif /* _lint */
/* Lint/MISRA checking not applicable to asm so obscure this when lint checking */
#ifdef _lint
 #define OS_FETRAP_EXCEPTION(name, isr)
#else
 #define OS_FETRAP_EXCEPTION(name, isr)   OS_PRAGMA( ghs noprologue)   void name( void) {     OS_FETRAP_ENTRY();     isr();     OS_FETRAP_LEAVE();   }
#endif /* _lint */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_LONGREG, OS_SHORTREG, OS_SBYTEREG) */
/* OS_LONGREG, OS_SHORTREG, OS_SBYTEREG */
#define OS_LONGREG(reg) ((*(OS_VOLATILE uint32 *) (reg)))
#define OS_SHORTREG(reg) ((*(OS_VOLATILE uint16 *) (reg)))
#define OS_SBYTEREG(reg) ((*(OS_VOLATILE char *) (reg)))
/* EIBD MMRs used to bind interrupts */
/* INTC2 EIBD - only available in multicore parts */
#define OS_EIBD32 OS_LONGREG(0xFFFFB880U)
#define OS_EIBD33 OS_LONGREG(0xFFFFB884U)
#define OS_EIBD34 OS_LONGREG(0xFFFFB888U)
#define OS_EIBD35 OS_LONGREG(0xFFFFB88CU)
#define OS_EIBD36 OS_LONGREG(0xFFFFB890U)
#define OS_EIBD37 OS_LONGREG(0xFFFFB894U)
#define OS_EIBD38 OS_LONGREG(0xFFFFB898U)
#define OS_EIBD39 OS_LONGREG(0xFFFFB89CU)
#define OS_EIBD40 OS_LONGREG(0xFFFFB8A0U)
#define OS_EIBD41 OS_LONGREG(0xFFFFB8A4U)
#define OS_EIBD42 OS_LONGREG(0xFFFFB8A8U)
#define OS_EIBD43 OS_LONGREG(0xFFFFB8ACU)
#define OS_EIBD44 OS_LONGREG(0xFFFFB8B0U)
#define OS_EIBD45 OS_LONGREG(0xFFFFB8B4U)
#define OS_EIBD46 OS_LONGREG(0xFFFFB8B8U)
#define OS_EIBD47 OS_LONGREG(0xFFFFB8BCU)
#define OS_EIBD48 OS_LONGREG(0xFFFFB8C0U)
#define OS_EIBD49 OS_LONGREG(0xFFFFB8C4U)
#define OS_EIBD50 OS_LONGREG(0xFFFFB8C8U)
#define OS_EIBD51 OS_LONGREG(0xFFFFB8CCU)
#define OS_EIBD52 OS_LONGREG(0xFFFFB8D0U)
#define OS_EIBD53 OS_LONGREG(0xFFFFB8D4U)
#define OS_EIBD54 OS_LONGREG(0xFFFFB8D8U)
#define OS_EIBD55 OS_LONGREG(0xFFFFB8DCU)
#define OS_EIBD56 OS_LONGREG(0xFFFFB8E0U)
#define OS_EIBD57 OS_LONGREG(0xFFFFB8E4U)
#define OS_EIBD58 OS_LONGREG(0xFFFFB8E8U)
#define OS_EIBD59 OS_LONGREG(0xFFFFB8ECU)
#define OS_EIBD60 OS_LONGREG(0xFFFFB8F0U)
#define OS_EIBD61 OS_LONGREG(0xFFFFB8F4U)
#define OS_EIBD62 OS_LONGREG(0xFFFFB8F8U)
#define OS_EIBD63 OS_LONGREG(0xFFFFB8FCU)
#define OS_EIBD64 OS_LONGREG(0xFFFFB900U)
#define OS_EIBD65 OS_LONGREG(0xFFFFB904U)
#define OS_EIBD66 OS_LONGREG(0xFFFFB908U)
#define OS_EIBD67 OS_LONGREG(0xFFFFB90CU)
#define OS_EIBD68 OS_LONGREG(0xFFFFB910U)
#define OS_EIBD69 OS_LONGREG(0xFFFFB914U)
#define OS_EIBD70 OS_LONGREG(0xFFFFB918U)
#define OS_EIBD71 OS_LONGREG(0xFFFFB91CU)
#define OS_EIBD72 OS_LONGREG(0xFFFFB920U)
#define OS_EIBD73 OS_LONGREG(0xFFFFB924U)
#define OS_EIBD74 OS_LONGREG(0xFFFFB928U)
#define OS_EIBD75 OS_LONGREG(0xFFFFB92CU)
#define OS_EIBD76 OS_LONGREG(0xFFFFB930U)
#define OS_EIBD77 OS_LONGREG(0xFFFFB934U)
#define OS_EIBD78 OS_LONGREG(0xFFFFB938U)
#define OS_EIBD79 OS_LONGREG(0xFFFFB93CU)
#define OS_EIBD80 OS_LONGREG(0xFFFFB940U)
#define OS_EIBD81 OS_LONGREG(0xFFFFB944U)
#define OS_EIBD82 OS_LONGREG(0xFFFFB948U)
#define OS_EIBD83 OS_LONGREG(0xFFFFB94CU)
#define OS_EIBD84 OS_LONGREG(0xFFFFB950U)
#define OS_EIBD85 OS_LONGREG(0xFFFFB954U)
#define OS_EIBD86 OS_LONGREG(0xFFFFB958U)
#define OS_EIBD87 OS_LONGREG(0xFFFFB95CU)
#define OS_EIBD88 OS_LONGREG(0xFFFFB960U)
#define OS_EIBD89 OS_LONGREG(0xFFFFB964U)
#define OS_EIBD90 OS_LONGREG(0xFFFFB968U)
#define OS_EIBD91 OS_LONGREG(0xFFFFB96CU)
#define OS_EIBD92 OS_LONGREG(0xFFFFB970U)
#define OS_EIBD93 OS_LONGREG(0xFFFFB974U)
#define OS_EIBD94 OS_LONGREG(0xFFFFB978U)
#define OS_EIBD95 OS_LONGREG(0xFFFFB97CU)
#define OS_EIBD96 OS_LONGREG(0xFFFFB980U)
#define OS_EIBD97 OS_LONGREG(0xFFFFB984U)
#define OS_EIBD98 OS_LONGREG(0xFFFFB988U)
#define OS_EIBD99 OS_LONGREG(0xFFFFB98CU)
#define OS_EIBD100 OS_LONGREG(0xFFFFB990U)
#define OS_EIBD101 OS_LONGREG(0xFFFFB994U)
#define OS_EIBD102 OS_LONGREG(0xFFFFB998U)
#define OS_EIBD103 OS_LONGREG(0xFFFFB99CU)
#define OS_EIBD104 OS_LONGREG(0xFFFFB9A0U)
#define OS_EIBD105 OS_LONGREG(0xFFFFB9A4U)
#define OS_EIBD106 OS_LONGREG(0xFFFFB9A8U)
#define OS_EIBD107 OS_LONGREG(0xFFFFB9ACU)
#define OS_EIBD108 OS_LONGREG(0xFFFFB9B0U)
#define OS_EIBD109 OS_LONGREG(0xFFFFB9B4U)
#define OS_EIBD110 OS_LONGREG(0xFFFFB9B8U)
#define OS_EIBD111 OS_LONGREG(0xFFFFB9BCU)
#define OS_EIBD112 OS_LONGREG(0xFFFFB9C0U)
#define OS_EIBD113 OS_LONGREG(0xFFFFB9C4U)
#define OS_EIBD114 OS_LONGREG(0xFFFFB9C8U)
#define OS_EIBD115 OS_LONGREG(0xFFFFB9CCU)
#define OS_EIBD116 OS_LONGREG(0xFFFFB9D0U)
#define OS_EIBD117 OS_LONGREG(0xFFFFB9D4U)
#define OS_EIBD118 OS_LONGREG(0xFFFFB9D8U)
#define OS_EIBD119 OS_LONGREG(0xFFFFB9DCU)
#define OS_EIBD120 OS_LONGREG(0xFFFFB9E0U)
#define OS_EIBD121 OS_LONGREG(0xFFFFB9E4U)
#define OS_EIBD122 OS_LONGREG(0xFFFFB9E8U)
#define OS_EIBD123 OS_LONGREG(0xFFFFB9ECU)
#define OS_EIBD124 OS_LONGREG(0xFFFFB9F0U)
#define OS_EIBD125 OS_LONGREG(0xFFFFB9F4U)
#define OS_EIBD126 OS_LONGREG(0xFFFFB9F8U)
#define OS_EIBD127 OS_LONGREG(0xFFFFB9FCU)
#define OS_EIBD128 OS_LONGREG(0xFFFFBA00U)
#define OS_EIBD129 OS_LONGREG(0xFFFFBA04U)
#define OS_EIBD130 OS_LONGREG(0xFFFFBA08U)
#define OS_EIBD131 OS_LONGREG(0xFFFFBA0CU)
#define OS_EIBD132 OS_LONGREG(0xFFFFBA10U)
#define OS_EIBD133 OS_LONGREG(0xFFFFBA14U)
#define OS_EIBD134 OS_LONGREG(0xFFFFBA18U)
#define OS_EIBD135 OS_LONGREG(0xFFFFBA1CU)
#define OS_EIBD136 OS_LONGREG(0xFFFFBA20U)
#define OS_EIBD137 OS_LONGREG(0xFFFFBA24U)
#define OS_EIBD138 OS_LONGREG(0xFFFFBA28U)
#define OS_EIBD139 OS_LONGREG(0xFFFFBA2CU)
#define OS_EIBD140 OS_LONGREG(0xFFFFBA30U)
#define OS_EIBD141 OS_LONGREG(0xFFFFBA34U)
#define OS_EIBD142 OS_LONGREG(0xFFFFBA38U)
#define OS_EIBD143 OS_LONGREG(0xFFFFBA3CU)
#define OS_EIBD144 OS_LONGREG(0xFFFFBA40U)
#define OS_EIBD145 OS_LONGREG(0xFFFFBA44U)
#define OS_EIBD146 OS_LONGREG(0xFFFFBA48U)
#define OS_EIBD147 OS_LONGREG(0xFFFFBA4CU)
#define OS_EIBD148 OS_LONGREG(0xFFFFBA50U)
#define OS_EIBD149 OS_LONGREG(0xFFFFBA54U)
#define OS_EIBD150 OS_LONGREG(0xFFFFBA58U)
#define OS_EIBD151 OS_LONGREG(0xFFFFBA5CU)
#define OS_EIBD152 OS_LONGREG(0xFFFFBA60U)
#define OS_EIBD153 OS_LONGREG(0xFFFFBA64U)
#define OS_EIBD154 OS_LONGREG(0xFFFFBA68U)
#define OS_EIBD155 OS_LONGREG(0xFFFFBA6CU)
#define OS_EIBD156 OS_LONGREG(0xFFFFBA70U)
#define OS_EIBD157 OS_LONGREG(0xFFFFBA74U)
#define OS_EIBD158 OS_LONGREG(0xFFFFBA78U)
#define OS_EIBD159 OS_LONGREG(0xFFFFBA7CU)
#define OS_EIBD160 OS_LONGREG(0xFFFFBA80U)
#define OS_EIBD161 OS_LONGREG(0xFFFFBA84U)
#define OS_EIBD162 OS_LONGREG(0xFFFFBA88U)
#define OS_EIBD163 OS_LONGREG(0xFFFFBA8CU)
#define OS_EIBD164 OS_LONGREG(0xFFFFBA90U)
#define OS_EIBD165 OS_LONGREG(0xFFFFBA94U)
#define OS_EIBD166 OS_LONGREG(0xFFFFBA98U)
#define OS_EIBD167 OS_LONGREG(0xFFFFBA9CU)
#define OS_EIBD168 OS_LONGREG(0xFFFFBAA0U)
#define OS_EIBD169 OS_LONGREG(0xFFFFBAA4U)
#define OS_EIBD170 OS_LONGREG(0xFFFFBAA8U)
#define OS_EIBD171 OS_LONGREG(0xFFFFBAACU)
#define OS_EIBD172 OS_LONGREG(0xFFFFBAB0U)
#define OS_EIBD173 OS_LONGREG(0xFFFFBAB4U)
#define OS_EIBD174 OS_LONGREG(0xFFFFBAB8U)
#define OS_EIBD175 OS_LONGREG(0xFFFFBABCU)
#define OS_EIBD176 OS_LONGREG(0xFFFFBAC0U)
#define OS_EIBD177 OS_LONGREG(0xFFFFBAC4U)
#define OS_EIBD178 OS_LONGREG(0xFFFFBAC8U)
#define OS_EIBD179 OS_LONGREG(0xFFFFBACCU)
#define OS_EIBD180 OS_LONGREG(0xFFFFBAD0U)
#define OS_EIBD181 OS_LONGREG(0xFFFFBAD4U)
#define OS_EIBD182 OS_LONGREG(0xFFFFBAD8U)
#define OS_EIBD183 OS_LONGREG(0xFFFFBADCU)
#define OS_EIBD184 OS_LONGREG(0xFFFFBAE0U)
#define OS_EIBD185 OS_LONGREG(0xFFFFBAE4U)
#define OS_EIBD186 OS_LONGREG(0xFFFFBAE8U)
#define OS_EIBD187 OS_LONGREG(0xFFFFBAECU)
#define OS_EIBD188 OS_LONGREG(0xFFFFBAF0U)
#define OS_EIBD189 OS_LONGREG(0xFFFFBAF4U)
#define OS_EIBD190 OS_LONGREG(0xFFFFBAF8U)
#define OS_EIBD191 OS_LONGREG(0xFFFFBAFCU)
#define OS_EIBD192 OS_LONGREG(0xFFFFBB00U)
#define OS_EIBD193 OS_LONGREG(0xFFFFBB04U)
#define OS_EIBD194 OS_LONGREG(0xFFFFBB08U)
#define OS_EIBD195 OS_LONGREG(0xFFFFBB0CU)
#define OS_EIBD196 OS_LONGREG(0xFFFFBB10U)
#define OS_EIBD197 OS_LONGREG(0xFFFFBB14U)
#define OS_EIBD198 OS_LONGREG(0xFFFFBB18U)
#define OS_EIBD199 OS_LONGREG(0xFFFFBB1CU)
#define OS_EIBD200 OS_LONGREG(0xFFFFBB20U)
#define OS_EIBD201 OS_LONGREG(0xFFFFBB24U)
#define OS_EIBD202 OS_LONGREG(0xFFFFBB28U)
#define OS_EIBD203 OS_LONGREG(0xFFFFBB2CU)
#define OS_EIBD204 OS_LONGREG(0xFFFFBB30U)
#define OS_EIBD205 OS_LONGREG(0xFFFFBB34U)
#define OS_EIBD206 OS_LONGREG(0xFFFFBB38U)
#define OS_EIBD207 OS_LONGREG(0xFFFFBB3CU)
#define OS_EIBD208 OS_LONGREG(0xFFFFBB40U)
#define OS_EIBD209 OS_LONGREG(0xFFFFBB44U)
#define OS_EIBD210 OS_LONGREG(0xFFFFBB48U)
#define OS_EIBD211 OS_LONGREG(0xFFFFBB4CU)
#define OS_EIBD212 OS_LONGREG(0xFFFFBB50U)
#define OS_EIBD213 OS_LONGREG(0xFFFFBB54U)
#define OS_EIBD214 OS_LONGREG(0xFFFFBB58U)
#define OS_EIBD215 OS_LONGREG(0xFFFFBB5CU)
#define OS_EIBD216 OS_LONGREG(0xFFFFBB60U)
#define OS_EIBD217 OS_LONGREG(0xFFFFBB64U)
#define OS_EIBD218 OS_LONGREG(0xFFFFBB68U)
#define OS_EIBD219 OS_LONGREG(0xFFFFBB6CU)
#define OS_EIBD220 OS_LONGREG(0xFFFFBB70U)
#define OS_EIBD221 OS_LONGREG(0xFFFFBB74U)
#define OS_EIBD222 OS_LONGREG(0xFFFFBB78U)
#define OS_EIBD223 OS_LONGREG(0xFFFFBB7CU)
#define OS_EIBD224 OS_LONGREG(0xFFFFBB80U)
#define OS_EIBD225 OS_LONGREG(0xFFFFBB84U)
#define OS_EIBD226 OS_LONGREG(0xFFFFBB88U)
#define OS_EIBD227 OS_LONGREG(0xFFFFBB8CU)
#define OS_EIBD228 OS_LONGREG(0xFFFFBB90U)
#define OS_EIBD229 OS_LONGREG(0xFFFFBB94U)
#define OS_EIBD230 OS_LONGREG(0xFFFFBB98U)
#define OS_EIBD231 OS_LONGREG(0xFFFFBB9CU)
#define OS_EIBD232 OS_LONGREG(0xFFFFBBA0U)
#define OS_EIBD233 OS_LONGREG(0xFFFFBBA4U)
#define OS_EIBD234 OS_LONGREG(0xFFFFBBA8U)
#define OS_EIBD235 OS_LONGREG(0xFFFFBBACU)
#define OS_EIBD236 OS_LONGREG(0xFFFFBBB0U)
#define OS_EIBD237 OS_LONGREG(0xFFFFBBB4U)
#define OS_EIBD238 OS_LONGREG(0xFFFFBBB8U)
#define OS_EIBD239 OS_LONGREG(0xFFFFBBBCU)
#define OS_EIBD240 OS_LONGREG(0xFFFFBBC0U)
#define OS_EIBD241 OS_LONGREG(0xFFFFBBC4U)
#define OS_EIBD242 OS_LONGREG(0xFFFFBBC8U)
#define OS_EIBD243 OS_LONGREG(0xFFFFBBCCU)
#define OS_EIBD244 OS_LONGREG(0xFFFFBBD0U)
#define OS_EIBD245 OS_LONGREG(0xFFFFBBD4U)
#define OS_EIBD246 OS_LONGREG(0xFFFFBBD8U)
#define OS_EIBD247 OS_LONGREG(0xFFFFBBDCU)
#define OS_EIBD248 OS_LONGREG(0xFFFFBBE0U)
#define OS_EIBD249 OS_LONGREG(0xFFFFBBE4U)
#define OS_EIBD250 OS_LONGREG(0xFFFFBBE8U)
#define OS_EIBD251 OS_LONGREG(0xFFFFBBECU)
#define OS_EIBD252 OS_LONGREG(0xFFFFBBF0U)
#define OS_EIBD253 OS_LONGREG(0xFFFFBBF4U)
#define OS_EIBD254 OS_LONGREG(0xFFFFBBF8U)
#define OS_EIBD255 OS_LONGREG(0xFFFFBBFCU)
#define OS_EIBD_PEID1 0x00000001U
#define OS_EIBD_PEID2 0x00000002U
#define OS_EIBD_PEID3 0x00000003U
#define OS_EIBD_GPID1 0x00000000U
#define OS_EIBD_GPID2 0x00010000U
#define OS_EIBD_GPID3 0x00010000U
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif
/* Lint/MISRA checking does not set the GHS register mode so when
 * testing lint/MISRA supply a specific version */
#ifdef _lint
typedef sint32 Os_jmp_buf[13];
#else
#if (__V800_registermode==22)
typedef sint32 Os_jmp_buf[11];
#endif
#if (__V800_registermode==26)
typedef sint32 Os_jmp_buf[13];
#endif
#if (__V800_registermode==32)
typedef sint32 Os_jmp_buf[16];
#endif
#endif /*_lint*/
extern __attribute__((noinline,noreturn)) void Os_longjmp(Os_jmp_buf env);
extern sint32 Os_setjmp(Os_jmp_buf env);

#ifndef OS_CONST
  #error "OS_CONST is not defined. This normally appears in Compiler_Cfg.h or Os_Compiler_Cfg.h"
#endif
#ifndef OS_CONST_FAST
  #define OS_CONST_FAST OS_CONST
#endif

#define OS_MEMMAP_DECLARATIONS (TRUE)
#define OS_MEMMAP_DEFINITIONS  (TRUE)

typedef unsigned int Os_ResourceCountType;
typedef uint32 Os_StackTraceType;
typedef uint32 Os_StackValueType;
typedef uint32 Os_StackSizeType;
/* Lint/MISRA checking has a problem with the compiler intrinsic functions
 * so when lint checking let these be seen as external functions */
#ifdef _lint
extern Os_StackValueType Os_GetSP(void);
#else
#ifndef __cplusplus
Os_StackValueType Os_GetSP(void);
#endif
static __asmleaf Os_StackValueType Os_GetSP(void)
{
%reg
  mov  r3, r10
%con
  mov  r3, r10
%mem
  mov  r3, r10
}
#endif /*_lint*/

typedef void (*Os_VoidVoidFunctionType)(void);
typedef Os_VoidVoidFunctionType Os_TaskEntryFunctionType; /* backwards compatible */
typedef Os_VoidVoidFunctionType Os_IsrEntryFunctionType; /* backwards compatible */
typedef P2VAR(Std_VersionInfoType, TYPEDEF, OS_VAR) Std_VersionInfoRefType;

typedef enum {OS_BUDGET = 0U, OS_ECC_START, OS_ECC_RESUME, OS_ECC_WAIT} Os_StackOverrunType; /* [$UKS 1236] [$UKS 1228] [$UKS 1235] */

#define OS_NOAPPMODE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)  /* [$UKS 381] [$UKS 383] */
#define OS_STANDARD_STATUS  /* [$UKS 7] [$UKS 760] */
#define OS_ORTI_BUILD
#define OS_SCALABILITY_CLASS_4 /* [$UKS 762] [$UKS 763] [$UKS 764] [$UKS 765] */

/* OSApplications */
typedef unsigned int ApplicationType; /* [$UKS 411] */
#define INVALID_OSAPPLICATION ((ApplicationType)4U)  /* [$UKS 413] */

typedef void (*Os_AppErrorHookFunctionType)(StatusType Error); /* [$UKS 450] */
#define OS_PSW (5U)
typedef uint32 Os_tmaskType; /* [$UKS 2047] */
typedef struct Os_ApplicationConfigurationType_s {
  ApplicationType app_id;
  uint8 access;
  Os_tmaskType tmask;
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
typedef unsigned int TickType; /* [$UKS 276] */
typedef signed int SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType; /* [$UKS 277] */
typedef uint32 PhysicalTimeType; /* [$UKS  842] */
typedef unsigned int Os_StopwatchTickType; /* [$UKS 535] */
typedef P2VAR(Os_StopwatchTickType, TYPEDEF, OS_VAR) Os_StopwatchTickRefType;
typedef signed int Os_TimeLimitType;
#define OS_TIMING_PROTECTION
#define OS_NO_TIME_LIMIT (-1)
struct Os_TimeTokenType_s;
typedef P2VAR(struct Os_TimeTokenType_s, TYPEDEF, OS_VAR) Os_TimeTokenRefType;
typedef struct Os_TimeTokenType_s {
  Os_TimeLimitType budget;
  Os_TimeLimitType remaining;
  Os_TimeTokenRefType prev;
  StatusType locktype;
} Os_TimeTokenType;

typedef enum {PRO_IGNORE = 0U, PRO_TERMINATETASKISR, PRO_TERMINATEAPPL, PRO_TERMINATEAPPL_RESTART, PRO_SHUTDOWN} ProtectionReturnType; /* [$UKS 589] [$UKS 590] [$UKS 591] */
typedef P2VAR(Os_jmp_buf, TYPEDEF, OS_VAR) Os_TerminatorType;

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
typedef unsigned int MemorySizeType; /* [$UKS 972] */

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
#define OS_PMR (11U)
#define OS_SELID_2 (2U)


typedef struct Os_ISRDynType_s {
  Os_MeterInfoType meter;
} Os_ISRDynType;
typedef void (*Os_IsrTerminatedFunctionType)(void);
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
#define OS_IPL (11U)

/* Tasks */
typedef unsigned int Os_bitmask;
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
  Os_jmp_buf terminate_jump_buf;
  Os_MeterInfoType meter;
  boolean seen_activation;
  Os_ActivationCountType activation_count;
  uint32 termination_state;
} Os_TaskDynType;

struct Os_TaskFifoControl_s;
typedef struct Os_TaskType_s {
  CONSTP2VAR(Os_TaskDynType, OS_VAR, OS_CONST) dynamic;
  Os_VoidVoidFunctionType entry_function;
  Os_psetType pset;
  Os_tpmaskType base_tpmask;
  Os_tpmaskType tpmask;
  CoreIdType core_id;
  uint32 index;
  Os_ActivationCountType activation_count;
  CONSTP2CONST(struct Os_TaskFifoControl_s, OS_CONST, OS_CONST) activation_fifo;
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

typedef struct Os_TaskFifoControl_s {
  CONSTP2VAR(TaskType, OS_VAR, OS_CONST) start;
  CONSTP2VAR(TaskType, OS_VAR, OS_CONST) end;
  const uint8_least dyn_index;
  const Os_tpmaskType base_tpmask;
} Os_TaskFifoControl;

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

typedef struct Os_UntrustedContextType_s {
  ApplicationType Application;
  CoreIdType CoreID;
  TaskType TaskID;
  ISRType ISRID;
  TrustedFunctionIndexType FunctionID;
  TrustedFunctionParameterRefType FunctionParams;
  MemoryStartAddressType Address;
  MemoryStartAddressType AlignedAddress;
  MemorySizeType Size;
  boolean Trusted;
} Os_UntrustedContextType;
typedef P2VAR(Os_UntrustedContextType, TYPEDEF, OS_VAR) Os_UntrustedContextRefType;
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
#define OSServiceId_Os_TimingFaultDetected ((OSServiceIdType)93)
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
#define Schedule() Os_ScheduleQ() /* Optimized quick-exit version */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, ChainTask) */
#define ChainTask Os_ChainTask
#define TerminateTask Os_TerminateTask
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
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CallTrustedFunction) */
#define CallTrustedFunction(x,y) Os_CallTrustedFunction((x),(y),OS_NO_TIME_LIMIT)
#define CallAndProtectFunction Os_CallTrustedFunction
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
#define StartOS(x) {Os_EnhancedIsolationStackReserve();if (Os_StartOS(x)) {while(Os_Cbk_Idle()) {} /* [$UKS 161] */; for(;;) {} /* [$UKS 16] */}}
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
#define GetCoreID() ((CoreIdType)/*lint --e(9034) [MISRA 2012 Dir 10.3] Depends on CoreIdType size */((0U == Os_CurrentAppMode) ?  ((OS_STSR(OS_HTCFG0, OS_SELID_2) >> OS_PEID_BIT1) & 1U) : Os_TgtCoreID()))  /* [$UKS 1619] [$UKS 1620] [$UKS 1621] */
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
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(Os_TraceStatusType, OS_CALLOUT_CODE) Os_Cbk_TraceCommInitTarget(void) /* [$UKS 1209]*/;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommDataReady(void) /* [$UKS 1212] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxStart(void) /* [$UKS 1214] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxByte(Os_TraceDataType val) /* [$UKS 1211] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxEnd(void) /* [$UKS 1213] */;
extern FUNC(boolean, OS_CALLOUT_CODE) Os_Cbk_TraceCommTxReady(void) /* [$UKS 1215] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

typedef struct Os_ControlledCoreType_s {
  Os_ErrorInformationType ErrorInformation;
  OS_VOLATILE Os_Lockable lock_taskaccess;
  OS_VOLATILE Os_psetType ReadyTasks ;
  OS_VOLATILE ISRType RunningISR;
  OS_VOLATILE TaskType RunningTask;
  OS_VOLATILE Os_tpmaskType RunningTPMask ;
  ApplicationType Application;
  Os_TimeTokenRefType CurrentTimeToken;
  OS_VOLATILE Os_TerminatorType CurrentTerminator;
  Os_MeterInfoRefType CurrentMeteredObject;
  Os_MeterInfoType IdleMeter;
  Os_UntrustedContextType ApplicationContext;
  uint8 AppAccess;
  OS_VOLATILE ApplicationType AppOverride;
  Os_StackSizeType GetStackValueAdjust;
  boolean InErrorHook;
  OS_VOLATILE TaskType ChainTaskRef;
  boolean InProtectionHook;
  boolean CoreIsActive;
} Os_ControlledCoreType;
#define Os_lock_taskaccess (os_current_controlled_core->lock_taskaccess)
#define Os_ReadyTasks /*lint --e(9018) A union type */ (os_current_controlled_core->ReadyTasks /*lint --e(9018) A union type */)
#define Os_RunningISR (os_current_controlled_core->RunningISR)
#define Os_RunningTask (os_current_controlled_core->RunningTask)
#define Os_RunningTPMask /*lint --e(9018) A union type */ (os_current_controlled_core->RunningTPMask /*lint --e(9018) A union type */)
#define Os_Application (os_current_controlled_core->Application)
#define Os_CurrentTimeToken (os_current_controlled_core->CurrentTimeToken)
#define Os_CurrentTerminator (os_current_controlled_core->CurrentTerminator)
#define Os_CurrentMeteredObject (os_current_controlled_core->CurrentMeteredObject)
#define Os_IdleMeter (os_current_controlled_core->IdleMeter)
#define Os_ApplicationContext (os_current_controlled_core->ApplicationContext)
#define Os_AppAccess (os_current_controlled_core->AppAccess)
#define Os_AppOverride (os_current_controlled_core->AppOverride)
#define Os_ErrorInformation (Os_const_coreconfiguration[((0U == Os_CurrentAppMode) ?  ((OS_STSR(OS_HTCFG0, OS_SELID_2) >> OS_PEID_BIT1) & 1U) : Os_TgtCoreID())].controlled->ErrorInformation)
typedef struct Os_AnyCoreType_s {
  OS_VOLATILE Os_imaskType DisableAllImask;
  OS_VOLATILE Os_imaskType SuspendAllImask;
  OS_VOLATILE Os_imaskType SuspendOSImask;
  OS_VOLATILE uint32 DisableAllCount;
  OS_VOLATILE uint32 SuspendAllCount;
  OS_VOLATILE uint32 SuspendOSCount;
  OS_VOLATILE Os_OrtiIdType OrtiApiID;
  StatusType OrtiLastError;
  StatusType LastProtectionFault;
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
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
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
extern FUNC(Os_TimeLimitType, OS_CALLOUT_CODE) Os_Cbk_SuspendTimeLimit(void);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_SetTimeLimit(Os_TimeLimitType Limit) /* [$UKS 957] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_SetMemoryAccess(Os_UntrustedContextRefType ApplicationContext) /* [$UKS 1273] */;
extern FUNC(boolean, OS_CALLOUT_CODE) Os_Cbk_GetSetProtection(boolean set) /* [$UKS 2052] */;
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskStart(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskEnd(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISRStart(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISREnd(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISRStart(ISRType isr);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISREnd(ISRType isr);
extern FUNC(ProtectionReturnType, OS_CALLOUT_CODE) Os_Cbk_IsUntrustedCodeOK(const Os_EIContextBuffType * const Os_stack_context, Os_UntrustedContextRefType Os_EIApplicationContext);
extern FUNC(ProtectionReturnType, OS_CALLOUT_CODE) Os_Cbk_IsUntrustedTrapOK(MemoryStartAddressType Os_ret_addr, uint32 Os_CauseCode);
extern FUNC(boolean, OS_CALLOUT_CODE) Os_Cbk_IsSystemTrapAllowed(MemoryStartAddressType Caller);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_RestoreGlobalRegisters(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* Redeclare function prototypes with compiler attributes *//*lint -esym(762,Os_RunCurrentTerminator, Os_RunCurrentTerminatorCI) */
/*lint -esym(9004,Os_RunCurrentTerminator, Os_RunCurrentTerminatorCI) */
#pragma ghs noprologue
extern __attribute__((noinline,noreturn)) FUNC(void, OS_CODE) Os_RunCurrentTerminator(void);
extern __attribute__((noinline,noreturn)) FUNC(void, OS_CODE) Os_RunCurrentTerminatorCI(void);
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
extern FUNC(void, OS_CODE) Os_TimingFaultDetected(void);
extern FUNC(StatusType, OS_CODE) Os_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams, Os_TimeLimitType TimeLimit) /* [$UKS 601] */;
extern FUNC(void, OS_CODE) Os_EnhancedIsolationStackReserve(void);
extern FUNC(boolean, OS_CODE) Os_EnhancedIsolationActionHandler(ProtectionReturnType action);
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral8(AreaIdType Area, Os_uint8ConstRefType Address, Os_uint8RefType ReadValue) /* [$UKS 2054] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral8(AreaIdType Area, Os_uint8RefType Address, uint8 WriteValue) /* [$UKS 2078] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral8(AreaIdType Area, Os_uint8RefType Address, uint8 Clearmask, uint8 Setmask) /* [$UKS 2102] */;
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral16(AreaIdType Area, Os_uint16ConstRefType Address, Os_uint16RefType ReadValue) /* [$UKS 2062] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral16(AreaIdType Area, Os_uint16RefType Address, uint16 WriteValue) /* [$UKS 2086] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral16(AreaIdType Area, Os_uint16RefType Address, uint16 Clearmask, uint16 Setmask) /* [$UKS 2110] */;
extern FUNC(StatusType, OS_CODE) Os_ReadPeripheral32(AreaIdType Area, Os_uint32ConstRefType Address, Os_uint32RefType ReadValue) /* [$UKS 2070] */;
extern FUNC(StatusType, OS_CODE) Os_WritePeripheral32(AreaIdType Area, Os_uint32RefType Address, uint32 WriteValue) /* [$UKS 2094] */;
extern FUNC(StatusType, OS_CODE) Os_ModifyPeripheral32(AreaIdType Area, Os_uint32RefType Address, uint32 Clearmask, uint32 Setmask) /* [$UKS 2118] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CONST_CORE0_LOCAL
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks0[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CONST_CORE0_LOCAL
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CONST_CORE1_LOCAL
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks1[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CONST_CORE1_LOCAL
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern CONST(CoreIdType, OS_CONST_FAST) Os_TotalNumberOfCores;
extern CONST(Os_CoreConfiguration, OS_CONST_FAST) Os_const_coreconfiguration[];
extern CONST(Os_ApplicationConfigurationType, OS_CONST_FAST) Os_const_applications[];
extern CONST(Os_ISRType, OS_CONST_FAST) Os_const_isrs[];
extern CONST(TaskType, OS_CONST_FAST) Os_const_tasks[];
extern CONST(Os_ResourceType, OS_CONST_FAST) Os_const_resources[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
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
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern OS_VOLATILE VAR(AppModeType, OS_VAR_CLEARED) Os_CurrentAppMode;
extern VAR(Os_AnyCoreType, OS_VAR_CLEARED) Os_AnyCoreInfo[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern VAR(StatusType, OS_VAR_NO_INIT) Os_ShutdownAllCores_Indicator;
extern VAR(ApplicationStateType, OS_VAR_NO_INIT) Os_dyn_appstate[];
extern OS_VOLATILE VAR(Os_Lockable, OS_VAR_NO_INIT) Os_lock_apperrorhook;
extern VAR(Os_TaskDynType, OS_VAR_NO_INIT) Os_dyn_tasks[];
extern VAR(Os_ISRDynType, OS_VAR_NO_INIT) Os_dyn_isrs[];
extern VAR(Os_ControlledCoreType, OS_VAR_NO_INIT) Os_ControlledCoreInfo[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

#include <Os_Cfg.h> /* [$UKS 649] */
#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* OS_H */
