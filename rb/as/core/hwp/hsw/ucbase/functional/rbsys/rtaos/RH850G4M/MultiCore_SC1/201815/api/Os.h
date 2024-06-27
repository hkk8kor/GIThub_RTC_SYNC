/*
 * This is Os.h, auto-generated for:
 *   Project: rtaos_ccas_u2a_mcore_sc1
 *   Target:  RH850x2GHS
 *   Variant: U2A
 *   Version: 5.0.6
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
#define OS_TARGET_PORT "RH850x2GHS"
#define OS_TARGET_PORT_RH850x2GHS
#define OS_TARGET_MAJOR_VERSION (5U)
#define OS_TARGET_MINOR_VERSION (0U)
#define OS_TARGET_PATCH_VERSION (6U)

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
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CAT1_ISR, OS_CLR1, OS_DI, OS_EI, OS_LDSR, OS_MAIN, OS_SET1, OS_SNOOZE, OS_SYNCI, OS_SYNCM, OS_SYNCP, OS_TRAP) */
/* CAT1_ISR, OS_CLR1, OS_DI, OS_EI, OS_LDSR, OS_MAIN, OS_SET1, OS_SNOOZE, OS_SYNCI, OS_SYNCM, OS_SYNCP, OS_TRAP */
typedef int Os_main_int;

#define OS_MAIN() Os_main_int main(void)

/* Call before StartOS() to initialize the INTC EICn priority settings.  Also
 * enables interrupts (PSW.ID bit) after setting the INTC priority threshold to
 * lock out Category 2 ISRs until after initialization. */
/* We need OS_VOLATILE in this file before it gets defined by default. */
#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif

/* [$Satisfies $Targetx2GHS 58]
 * Trace32 ORTI support */
/* Only set up the intrinsic function if the GHS header has not already been
 * included. __V800_IS is defined by v800_ghs.h when included first.
 * __GHS_BARRIER_H is defined by ghs_barrier.h*/
/* Pull in the compiler intrinsic functions originally from ghs_barrier.h */
#ifndef __GHS_BARRIER_H
  extern void __memory_changed(void);
#endif /* !__GHS_BARRIER_H */

#ifndef __V800_IS
  /* [$Satisfies $Targetx2GHS 47]
   * Intrinsic functions copied here to avoid including v800_ghs.h */
  extern void __DI(void);
  extern void __EI(void);
  extern void __SNOOZE(void);
  extern void __SYNCI(void);
  extern void __SYNCM(void);
  extern void __SYNCP(void);

    /* Lint/MISRA checking has a problem with the compiler intrinsic functions so
   * obscure this when lint checking */
  /* Allow lint to ignore symbols not being referenced  since this is a common header file. */
  /*lint -estring(752, __CLR1, __SCH1L, __SET1, __STCW, __LDLW, __STSR, __LDSR, __memory_changed)*/
  #if defined(_lint) || defined(__cplusplus)
    extern void __CLR1(OS_VOLATILE char *addr, sint32 bitnum);
    extern sint32 __LDL_W(sint32 *addr);
    extern void __LDSR(sint32 regID, sint32 selID, uint32 val);
    extern uint32 __SCH1L(uint32 val);
    extern void __SET1(OS_VOLATILE char *addr, sint32 bitnum);
    extern sint32 __STC_W(sint32 val, sint32 *addr);
    extern uint32 __STSR(sint32 regID, sint32 selID);
  #else
    extern void __CLR1(OS_VOLATILE char *addr, int bitnum);
    extern int __LDL_W(int *addr);
    extern void __LDSR(int regID, int selID, unsigned int val);
    extern unsigned int __SCH1L(unsigned int val);
    extern void __SET1(OS_VOLATILE char *addr, int bitnum);
    extern unsigned int __STSR(int regID, int selID);
    extern int __STC_W(int val, int *addr);
  #endif /* _lint, __cplusplus */
#endif /* !__V800_IS */

#if defined(_lint) || defined(__cplusplus)
  extern void os_trap(uint32 value);
#else
  void os_trap(uint32 value);
__asm void os_trap(uint32 value)
{
%con value
  trap value
%error
  Macro has not expanded so it should result in error
}
#endif /* _lint, __cplusplus */

 /* The "macros" below are declared here, but are not used in all files so
  * we need to inform lint about this. These functions
  * replace macros, but do not hurt performance as they are always inlined. */
/* [$Satisfies $Targetx2GHS 65]
 *  __memory_changed() use */

/*lint -esym(752,__DI) allow to be unreferenced */
/*lint -esym(752,__EI) allow to be unreferenced */
/*lint -esym(752,__LDL_W) allow to be unreferenced */
/*lint -esym(752,__LDSR) allow to be unreferenced */
/*lint -esym(752,__SCH1L) allow to be unreferenced */
/*lint -esym(752,__STC_W) allow to be unreferenced */
/*lint -esym(752,__STSR) allow to be unreferenced */
/*lint -esym(752,__SNOOZE) allow to be unreferenced */
/*lint -esym(752,__SYNCI) allow to be unreferenced */
/*lint -esym(752,__SYNCM) allow to be unreferenced */
/*lint -esym(752,__SYNCP) allow to be unreferenced */
/*lint -esym(752,os_trap) allow to be unreferenced */

#define OS_CLR1(addr, bit)         __memory_changed(); __CLR1((addr), (bit)); __memory_changed()
#define OS_SET1(addr, bit)         __memory_changed(); __SET1((addr), (bit)); __memory_changed()
#define OS_LDSR(regID, selID, val) __memory_changed(); __LDSR((regID), (selID), (val)); __memory_changed()

#define OS_SNOOZE()                __memory_changed(); __SNOOZE(); __memory_changed()
#define OS_SYNCI()                 __memory_changed(); __SYNCI(); __memory_changed()
#define OS_SYNCM()                 __memory_changed(); __SYNCM(); __memory_changed()
#define OS_SYNCP()                 __memory_changed(); __SYNCP(); __memory_changed()
#define OS_DI()                    __memory_changed(); __DI(); __memory_changed()
#define OS_EI()                    __memory_changed(); __EI(); __memory_changed()
#define OS_TRAP(val)               os_trap(val)


/* Allow lint to ignore symbols not being referenced since this is a common header file.*/
/*lint -estring(528, OS_SCH1L, OS_STSR, OS_STCW, OS_LDLW)*/

/* The "unused" attribute informs the compiler compiler that it is all right for this
 * function or variable to have been defined but not referenced in the current translation
 * unit; that is, it suppresses the warnings usually given at end of scope for
 * unreferenced entities. This means that the GHS pragma is not required. */
static inline uint32 __attribute__((unused)) OS_SCH1L(uint32 val)
{
  uint32 ret;
  __memory_changed();
  ret = __SCH1L(val);
  __memory_changed();
  return ret;
}

#define OS_STSR(regID, selID) __STSR((regID), (selID))

static inline __attribute__((unused)) sint32 OS_STCW(sint32 val, sint32 *addr)
{
  sint32 ret;
  __memory_changed();
  ret = __STC_W(val, addr);
  __memory_changed();
  return ret;
}

static inline __attribute__((unused)) sint32 OS_LDLW(sint32 *addr)
{
  sint32 ret;
  __memory_changed();
  ret = __LDL_W(addr);
  __memory_changed();
  return ret;
}



#define OS_PSW_EBV (0x00008000U)
#define OS_PSW_NP (0x00000080U)
#define OS_PSW_EP (0x00000040U)
#define OS_PSW_ID (0x00000020U)

#define OS_EIPC_REGID (0)
#define OS_EIPC_SELID (0)

#define OS_FPSR_REGID (6)
#define OS_FPSR_SELID (0)

#define OS_FPEPC_REGID (7)
#define OS_FPEPC_SELID (0)

#define OS_CTPC_REGID (16)
#define OS_CTPC_SELID (0)

#define OS_EBASE_REGID (3)
#define OS_EBASE_SELID (1)

#define OS_EBASE_RINT (0x00000001U)

#define OS_INTBP_REGID (4)
#define OS_INTBP_SELID (1)

#define OS_INTCFG_REGID (13)
#define OS_INTCFG_SELID (2)

#define OS_INTCFG_ISPC (0x00000001U)

#define OS_PEID_REGID (0)
#define OS_PEID_SELID (2)

/* From in Os_Vectors.o */
/* Reference the interrupt vector table so that the base address can be set. */
/* Always use 32 bit addressing regardless of SDA setting */
#pragma ghs startdata
extern uint32 Os_interrupt_vectors[];
extern uint32 Os_EI_vectors[];

#pragma ghs enddata

/* INTC registers used by RTA-OS
 *
 * RTA-OS provides macros that allow an application to enable an interrupt,
 * disable an interrupt, clear a pending interrupt, set an interrupt as being
 * edge-sensitive, and set an interrupt as being level-sensitive. These can all
 * be called directly by the user and as a result the macros used by these
 * macros to access the relevant memory mapped registers provided by the INTC
 * must also be visible to the user.
 *
 * Only those memory mapped INTC registers that need to be user accessible are
 * defined here. Any register that is used exclusively by RTA-OS is defined
 * elsewhere.
 */
#ifdef _lint  /* Declaring memory-mapped peripherals */
  extern uint16 OS_INTC_EIC0; /*lint -esym(752,OS_INTC_EIC0) allow to be unreferenced */
  extern uint16 OS_INTC_EIC1; /*lint -esym(752,OS_INTC_EIC1) allow to be unreferenced */
  extern uint16 OS_INTC_EIC2; /*lint -esym(752,OS_INTC_EIC2) allow to be unreferenced */
  extern uint16 OS_INTC_EIC3; /*lint -esym(752,OS_INTC_EIC3) allow to be unreferenced */
  extern uint16 OS_INTC_EIC4; /*lint -esym(752,OS_INTC_EIC4) allow to be unreferenced */
  extern uint16 OS_INTC_EIC5; /*lint -esym(752,OS_INTC_EIC5) allow to be unreferenced */
  extern uint16 OS_INTC_EIC6; /*lint -esym(752,OS_INTC_EIC6) allow to be unreferenced */
  extern uint16 OS_INTC_EIC7; /*lint -esym(752,OS_INTC_EIC7) allow to be unreferenced */
  extern uint16 OS_INTC_EIC8; /*lint -esym(752,OS_INTC_EIC8) allow to be unreferenced */
  extern uint16 OS_INTC_EIC9; /*lint -esym(752,OS_INTC_EIC9) allow to be unreferenced */
  extern uint16 OS_INTC_EIC10; /*lint -esym(752,OS_INTC_EIC10) allow to be unreferenced */
  extern uint16 OS_INTC_EIC11; /*lint -esym(752,OS_INTC_EIC11) allow to be unreferenced */
  extern uint16 OS_INTC_EIC12; /*lint -esym(752,OS_INTC_EIC12) allow to be unreferenced */
  extern uint16 OS_INTC_EIC13; /*lint -esym(752,OS_INTC_EIC13) allow to be unreferenced */
  extern uint16 OS_INTC_EIC14; /*lint -esym(752,OS_INTC_EIC14) allow to be unreferenced */
  extern uint16 OS_INTC_EIC15; /*lint -esym(752,OS_INTC_EIC15) allow to be unreferenced */
  extern uint16 OS_INTC_EIC16; /*lint -esym(752,OS_INTC_EIC16) allow to be unreferenced */
  extern uint16 OS_INTC_EIC17; /*lint -esym(752,OS_INTC_EIC17) allow to be unreferenced */
  extern uint16 OS_INTC_EIC18; /*lint -esym(752,OS_INTC_EIC18) allow to be unreferenced */
  extern uint16 OS_INTC_EIC19; /*lint -esym(752,OS_INTC_EIC19) allow to be unreferenced */
  extern uint16 OS_INTC_EIC20; /*lint -esym(752,OS_INTC_EIC20) allow to be unreferenced */
  extern uint16 OS_INTC_EIC21; /*lint -esym(752,OS_INTC_EIC21) allow to be unreferenced */
  extern uint16 OS_INTC_EIC22; /*lint -esym(752,OS_INTC_EIC22) allow to be unreferenced */
  extern uint16 OS_INTC_EIC23; /*lint -esym(752,OS_INTC_EIC23) allow to be unreferenced */
  extern uint16 OS_INTC_EIC24; /*lint -esym(752,OS_INTC_EIC24) allow to be unreferenced */
  extern uint16 OS_INTC_EIC25; /*lint -esym(752,OS_INTC_EIC25) allow to be unreferenced */
  extern uint16 OS_INTC_EIC26; /*lint -esym(752,OS_INTC_EIC26) allow to be unreferenced */
  extern uint16 OS_INTC_EIC27; /*lint -esym(752,OS_INTC_EIC27) allow to be unreferenced */
  extern uint16 OS_INTC_EIC28; /*lint -esym(752,OS_INTC_EIC28) allow to be unreferenced */
  extern uint16 OS_INTC_EIC29; /*lint -esym(752,OS_INTC_EIC29) allow to be unreferenced */
  extern uint16 OS_INTC_EIC30; /*lint -esym(752,OS_INTC_EIC30) allow to be unreferenced */
  extern uint16 OS_INTC_EIC31; /*lint -esym(752,OS_INTC_EIC31) allow to be unreferenced */
  extern uint16 OS_INTC_EIC32; /*lint -esym(752,OS_INTC_EIC32) allow to be unreferenced */
  extern uint16 OS_INTC_EIC33; /*lint -esym(752,OS_INTC_EIC33) allow to be unreferenced */
  extern uint16 OS_INTC_EIC34; /*lint -esym(752,OS_INTC_EIC34) allow to be unreferenced */
  extern uint16 OS_INTC_EIC35; /*lint -esym(752,OS_INTC_EIC35) allow to be unreferenced */
  extern uint16 OS_INTC_EIC36; /*lint -esym(752,OS_INTC_EIC36) allow to be unreferenced */
  extern uint16 OS_INTC_EIC37; /*lint -esym(752,OS_INTC_EIC37) allow to be unreferenced */
  extern uint16 OS_INTC_EIC38; /*lint -esym(752,OS_INTC_EIC38) allow to be unreferenced */
  extern uint16 OS_INTC_EIC39; /*lint -esym(752,OS_INTC_EIC39) allow to be unreferenced */
  extern uint16 OS_INTC_EIC40; /*lint -esym(752,OS_INTC_EIC40) allow to be unreferenced */
  extern uint16 OS_INTC_EIC41; /*lint -esym(752,OS_INTC_EIC41) allow to be unreferenced */
  extern uint16 OS_INTC_EIC42; /*lint -esym(752,OS_INTC_EIC42) allow to be unreferenced */
  extern uint16 OS_INTC_EIC43; /*lint -esym(752,OS_INTC_EIC43) allow to be unreferenced */
  extern uint16 OS_INTC_EIC44; /*lint -esym(752,OS_INTC_EIC44) allow to be unreferenced */
  extern uint16 OS_INTC_EIC45; /*lint -esym(752,OS_INTC_EIC45) allow to be unreferenced */
  extern uint16 OS_INTC_EIC46; /*lint -esym(752,OS_INTC_EIC46) allow to be unreferenced */
  extern uint16 OS_INTC_EIC47; /*lint -esym(752,OS_INTC_EIC47) allow to be unreferenced */
  extern uint16 OS_INTC_EIC48; /*lint -esym(752,OS_INTC_EIC48) allow to be unreferenced */
  extern uint16 OS_INTC_EIC49; /*lint -esym(752,OS_INTC_EIC49) allow to be unreferenced */
  extern uint16 OS_INTC_EIC50; /*lint -esym(752,OS_INTC_EIC50) allow to be unreferenced */
  extern uint16 OS_INTC_EIC51; /*lint -esym(752,OS_INTC_EIC51) allow to be unreferenced */
  extern uint16 OS_INTC_EIC52; /*lint -esym(752,OS_INTC_EIC52) allow to be unreferenced */
  extern uint16 OS_INTC_EIC53; /*lint -esym(752,OS_INTC_EIC53) allow to be unreferenced */
  extern uint16 OS_INTC_EIC54; /*lint -esym(752,OS_INTC_EIC54) allow to be unreferenced */
  extern uint16 OS_INTC_EIC55; /*lint -esym(752,OS_INTC_EIC55) allow to be unreferenced */
  extern uint16 OS_INTC_EIC56; /*lint -esym(752,OS_INTC_EIC56) allow to be unreferenced */
  extern uint16 OS_INTC_EIC57; /*lint -esym(752,OS_INTC_EIC57) allow to be unreferenced */
  extern uint16 OS_INTC_EIC58; /*lint -esym(752,OS_INTC_EIC58) allow to be unreferenced */
  extern uint16 OS_INTC_EIC59; /*lint -esym(752,OS_INTC_EIC59) allow to be unreferenced */
  extern uint16 OS_INTC_EIC60; /*lint -esym(752,OS_INTC_EIC60) allow to be unreferenced */
  extern uint16 OS_INTC_EIC61; /*lint -esym(752,OS_INTC_EIC61) allow to be unreferenced */
  extern uint16 OS_INTC_EIC62; /*lint -esym(752,OS_INTC_EIC62) allow to be unreferenced */
  extern uint16 OS_INTC_EIC63; /*lint -esym(752,OS_INTC_EIC63) allow to be unreferenced */
  extern uint16 OS_INTC_EIC64; /*lint -esym(752,OS_INTC_EIC64) allow to be unreferenced */
  extern uint16 OS_INTC_EIC65; /*lint -esym(752,OS_INTC_EIC65) allow to be unreferenced */
  extern uint16 OS_INTC_EIC66; /*lint -esym(752,OS_INTC_EIC66) allow to be unreferenced */
  extern uint16 OS_INTC_EIC67; /*lint -esym(752,OS_INTC_EIC67) allow to be unreferenced */
  extern uint16 OS_INTC_EIC68; /*lint -esym(752,OS_INTC_EIC68) allow to be unreferenced */
  extern uint16 OS_INTC_EIC69; /*lint -esym(752,OS_INTC_EIC69) allow to be unreferenced */
  extern uint16 OS_INTC_EIC70; /*lint -esym(752,OS_INTC_EIC70) allow to be unreferenced */
  extern uint16 OS_INTC_EIC71; /*lint -esym(752,OS_INTC_EIC71) allow to be unreferenced */
  extern uint16 OS_INTC_EIC72; /*lint -esym(752,OS_INTC_EIC72) allow to be unreferenced */
  extern uint16 OS_INTC_EIC73; /*lint -esym(752,OS_INTC_EIC73) allow to be unreferenced */
  extern uint16 OS_INTC_EIC74; /*lint -esym(752,OS_INTC_EIC74) allow to be unreferenced */
  extern uint16 OS_INTC_EIC75; /*lint -esym(752,OS_INTC_EIC75) allow to be unreferenced */
  extern uint16 OS_INTC_EIC76; /*lint -esym(752,OS_INTC_EIC76) allow to be unreferenced */
  extern uint16 OS_INTC_EIC77; /*lint -esym(752,OS_INTC_EIC77) allow to be unreferenced */
  extern uint16 OS_INTC_EIC78; /*lint -esym(752,OS_INTC_EIC78) allow to be unreferenced */
  extern uint16 OS_INTC_EIC79; /*lint -esym(752,OS_INTC_EIC79) allow to be unreferenced */
  extern uint16 OS_INTC_EIC80; /*lint -esym(752,OS_INTC_EIC80) allow to be unreferenced */
  extern uint16 OS_INTC_EIC81; /*lint -esym(752,OS_INTC_EIC81) allow to be unreferenced */
  extern uint16 OS_INTC_EIC82; /*lint -esym(752,OS_INTC_EIC82) allow to be unreferenced */
  extern uint16 OS_INTC_EIC83; /*lint -esym(752,OS_INTC_EIC83) allow to be unreferenced */
  extern uint16 OS_INTC_EIC84; /*lint -esym(752,OS_INTC_EIC84) allow to be unreferenced */
  extern uint16 OS_INTC_EIC85; /*lint -esym(752,OS_INTC_EIC85) allow to be unreferenced */
  extern uint16 OS_INTC_EIC86; /*lint -esym(752,OS_INTC_EIC86) allow to be unreferenced */
  extern uint16 OS_INTC_EIC87; /*lint -esym(752,OS_INTC_EIC87) allow to be unreferenced */
  extern uint16 OS_INTC_EIC88; /*lint -esym(752,OS_INTC_EIC88) allow to be unreferenced */
  extern uint16 OS_INTC_EIC89; /*lint -esym(752,OS_INTC_EIC89) allow to be unreferenced */
  extern uint16 OS_INTC_EIC90; /*lint -esym(752,OS_INTC_EIC90) allow to be unreferenced */
  extern uint16 OS_INTC_EIC91; /*lint -esym(752,OS_INTC_EIC91) allow to be unreferenced */
  extern uint16 OS_INTC_EIC92; /*lint -esym(752,OS_INTC_EIC92) allow to be unreferenced */
  extern uint16 OS_INTC_EIC93; /*lint -esym(752,OS_INTC_EIC93) allow to be unreferenced */
  extern uint16 OS_INTC_EIC94; /*lint -esym(752,OS_INTC_EIC94) allow to be unreferenced */
  extern uint16 OS_INTC_EIC95; /*lint -esym(752,OS_INTC_EIC95) allow to be unreferenced */
  extern uint16 OS_INTC_EIC96; /*lint -esym(752,OS_INTC_EIC96) allow to be unreferenced */
  extern uint16 OS_INTC_EIC97; /*lint -esym(752,OS_INTC_EIC97) allow to be unreferenced */
  extern uint16 OS_INTC_EIC98; /*lint -esym(752,OS_INTC_EIC98) allow to be unreferenced */
  extern uint16 OS_INTC_EIC99; /*lint -esym(752,OS_INTC_EIC99) allow to be unreferenced */
  extern uint16 OS_INTC_EIC100; /*lint -esym(752,OS_INTC_EIC100) allow to be unreferenced */
  extern uint16 OS_INTC_EIC101; /*lint -esym(752,OS_INTC_EIC101) allow to be unreferenced */
  extern uint16 OS_INTC_EIC102; /*lint -esym(752,OS_INTC_EIC102) allow to be unreferenced */
  extern uint16 OS_INTC_EIC103; /*lint -esym(752,OS_INTC_EIC103) allow to be unreferenced */
  extern uint16 OS_INTC_EIC104; /*lint -esym(752,OS_INTC_EIC104) allow to be unreferenced */
  extern uint16 OS_INTC_EIC105; /*lint -esym(752,OS_INTC_EIC105) allow to be unreferenced */
  extern uint16 OS_INTC_EIC106; /*lint -esym(752,OS_INTC_EIC106) allow to be unreferenced */
  extern uint16 OS_INTC_EIC107; /*lint -esym(752,OS_INTC_EIC107) allow to be unreferenced */
  extern uint16 OS_INTC_EIC108; /*lint -esym(752,OS_INTC_EIC108) allow to be unreferenced */
  extern uint16 OS_INTC_EIC109; /*lint -esym(752,OS_INTC_EIC109) allow to be unreferenced */
  extern uint16 OS_INTC_EIC110; /*lint -esym(752,OS_INTC_EIC110) allow to be unreferenced */
  extern uint16 OS_INTC_EIC111; /*lint -esym(752,OS_INTC_EIC111) allow to be unreferenced */
  extern uint16 OS_INTC_EIC112; /*lint -esym(752,OS_INTC_EIC112) allow to be unreferenced */
  extern uint16 OS_INTC_EIC113; /*lint -esym(752,OS_INTC_EIC113) allow to be unreferenced */
  extern uint16 OS_INTC_EIC114; /*lint -esym(752,OS_INTC_EIC114) allow to be unreferenced */
  extern uint16 OS_INTC_EIC115; /*lint -esym(752,OS_INTC_EIC115) allow to be unreferenced */
  extern uint16 OS_INTC_EIC116; /*lint -esym(752,OS_INTC_EIC116) allow to be unreferenced */
  extern uint16 OS_INTC_EIC117; /*lint -esym(752,OS_INTC_EIC117) allow to be unreferenced */
  extern uint16 OS_INTC_EIC118; /*lint -esym(752,OS_INTC_EIC118) allow to be unreferenced */
  extern uint16 OS_INTC_EIC119; /*lint -esym(752,OS_INTC_EIC119) allow to be unreferenced */
  extern uint16 OS_INTC_EIC120; /*lint -esym(752,OS_INTC_EIC120) allow to be unreferenced */
  extern uint16 OS_INTC_EIC121; /*lint -esym(752,OS_INTC_EIC121) allow to be unreferenced */
  extern uint16 OS_INTC_EIC122; /*lint -esym(752,OS_INTC_EIC122) allow to be unreferenced */
  extern uint16 OS_INTC_EIC123; /*lint -esym(752,OS_INTC_EIC123) allow to be unreferenced */
  extern uint16 OS_INTC_EIC124; /*lint -esym(752,OS_INTC_EIC124) allow to be unreferenced */
  extern uint16 OS_INTC_EIC125; /*lint -esym(752,OS_INTC_EIC125) allow to be unreferenced */
  extern uint16 OS_INTC_EIC126; /*lint -esym(752,OS_INTC_EIC126) allow to be unreferenced */
  extern uint16 OS_INTC_EIC127; /*lint -esym(752,OS_INTC_EIC127) allow to be unreferenced */
  extern uint16 OS_INTC_EIC128; /*lint -esym(752,OS_INTC_EIC128) allow to be unreferenced */
  extern uint16 OS_INTC_EIC129; /*lint -esym(752,OS_INTC_EIC129) allow to be unreferenced */
  extern uint16 OS_INTC_EIC130; /*lint -esym(752,OS_INTC_EIC130) allow to be unreferenced */
  extern uint16 OS_INTC_EIC131; /*lint -esym(752,OS_INTC_EIC131) allow to be unreferenced */
  extern uint16 OS_INTC_EIC132; /*lint -esym(752,OS_INTC_EIC132) allow to be unreferenced */
  extern uint16 OS_INTC_EIC133; /*lint -esym(752,OS_INTC_EIC133) allow to be unreferenced */
  extern uint16 OS_INTC_EIC134; /*lint -esym(752,OS_INTC_EIC134) allow to be unreferenced */
  extern uint16 OS_INTC_EIC135; /*lint -esym(752,OS_INTC_EIC135) allow to be unreferenced */
  extern uint16 OS_INTC_EIC136; /*lint -esym(752,OS_INTC_EIC136) allow to be unreferenced */
  extern uint16 OS_INTC_EIC137; /*lint -esym(752,OS_INTC_EIC137) allow to be unreferenced */
  extern uint16 OS_INTC_EIC138; /*lint -esym(752,OS_INTC_EIC138) allow to be unreferenced */
  extern uint16 OS_INTC_EIC139; /*lint -esym(752,OS_INTC_EIC139) allow to be unreferenced */
  extern uint16 OS_INTC_EIC140; /*lint -esym(752,OS_INTC_EIC140) allow to be unreferenced */
  extern uint16 OS_INTC_EIC141; /*lint -esym(752,OS_INTC_EIC141) allow to be unreferenced */
  extern uint16 OS_INTC_EIC142; /*lint -esym(752,OS_INTC_EIC142) allow to be unreferenced */
  extern uint16 OS_INTC_EIC143; /*lint -esym(752,OS_INTC_EIC143) allow to be unreferenced */
  extern uint16 OS_INTC_EIC144; /*lint -esym(752,OS_INTC_EIC144) allow to be unreferenced */
  extern uint16 OS_INTC_EIC145; /*lint -esym(752,OS_INTC_EIC145) allow to be unreferenced */
  extern uint16 OS_INTC_EIC146; /*lint -esym(752,OS_INTC_EIC146) allow to be unreferenced */
  extern uint16 OS_INTC_EIC147; /*lint -esym(752,OS_INTC_EIC147) allow to be unreferenced */
  extern uint16 OS_INTC_EIC148; /*lint -esym(752,OS_INTC_EIC148) allow to be unreferenced */
  extern uint16 OS_INTC_EIC149; /*lint -esym(752,OS_INTC_EIC149) allow to be unreferenced */
  extern uint16 OS_INTC_EIC150; /*lint -esym(752,OS_INTC_EIC150) allow to be unreferenced */
  extern uint16 OS_INTC_EIC151; /*lint -esym(752,OS_INTC_EIC151) allow to be unreferenced */
  extern uint16 OS_INTC_EIC152; /*lint -esym(752,OS_INTC_EIC152) allow to be unreferenced */
  extern uint16 OS_INTC_EIC153; /*lint -esym(752,OS_INTC_EIC153) allow to be unreferenced */
  extern uint16 OS_INTC_EIC154; /*lint -esym(752,OS_INTC_EIC154) allow to be unreferenced */
  extern uint16 OS_INTC_EIC155; /*lint -esym(752,OS_INTC_EIC155) allow to be unreferenced */
  extern uint16 OS_INTC_EIC156; /*lint -esym(752,OS_INTC_EIC156) allow to be unreferenced */
  extern uint16 OS_INTC_EIC157; /*lint -esym(752,OS_INTC_EIC157) allow to be unreferenced */
  extern uint16 OS_INTC_EIC158; /*lint -esym(752,OS_INTC_EIC158) allow to be unreferenced */
  extern uint16 OS_INTC_EIC159; /*lint -esym(752,OS_INTC_EIC159) allow to be unreferenced */
  extern uint16 OS_INTC_EIC160; /*lint -esym(752,OS_INTC_EIC160) allow to be unreferenced */
  extern uint16 OS_INTC_EIC161; /*lint -esym(752,OS_INTC_EIC161) allow to be unreferenced */
  extern uint16 OS_INTC_EIC162; /*lint -esym(752,OS_INTC_EIC162) allow to be unreferenced */
  extern uint16 OS_INTC_EIC163; /*lint -esym(752,OS_INTC_EIC163) allow to be unreferenced */
  extern uint16 OS_INTC_EIC164; /*lint -esym(752,OS_INTC_EIC164) allow to be unreferenced */
  extern uint16 OS_INTC_EIC165; /*lint -esym(752,OS_INTC_EIC165) allow to be unreferenced */
  extern uint16 OS_INTC_EIC166; /*lint -esym(752,OS_INTC_EIC166) allow to be unreferenced */
  extern uint16 OS_INTC_EIC167; /*lint -esym(752,OS_INTC_EIC167) allow to be unreferenced */
  extern uint16 OS_INTC_EIC168; /*lint -esym(752,OS_INTC_EIC168) allow to be unreferenced */
  extern uint16 OS_INTC_EIC169; /*lint -esym(752,OS_INTC_EIC169) allow to be unreferenced */
  extern uint16 OS_INTC_EIC170; /*lint -esym(752,OS_INTC_EIC170) allow to be unreferenced */
  extern uint16 OS_INTC_EIC171; /*lint -esym(752,OS_INTC_EIC171) allow to be unreferenced */
  extern uint16 OS_INTC_EIC172; /*lint -esym(752,OS_INTC_EIC172) allow to be unreferenced */
  extern uint16 OS_INTC_EIC173; /*lint -esym(752,OS_INTC_EIC173) allow to be unreferenced */
  extern uint16 OS_INTC_EIC174; /*lint -esym(752,OS_INTC_EIC174) allow to be unreferenced */
  extern uint16 OS_INTC_EIC175; /*lint -esym(752,OS_INTC_EIC175) allow to be unreferenced */
  extern uint16 OS_INTC_EIC176; /*lint -esym(752,OS_INTC_EIC176) allow to be unreferenced */
  extern uint16 OS_INTC_EIC177; /*lint -esym(752,OS_INTC_EIC177) allow to be unreferenced */
  extern uint16 OS_INTC_EIC178; /*lint -esym(752,OS_INTC_EIC178) allow to be unreferenced */
  extern uint16 OS_INTC_EIC179; /*lint -esym(752,OS_INTC_EIC179) allow to be unreferenced */
  extern uint16 OS_INTC_EIC180; /*lint -esym(752,OS_INTC_EIC180) allow to be unreferenced */
  extern uint16 OS_INTC_EIC181; /*lint -esym(752,OS_INTC_EIC181) allow to be unreferenced */
  extern uint16 OS_INTC_EIC182; /*lint -esym(752,OS_INTC_EIC182) allow to be unreferenced */
  extern uint16 OS_INTC_EIC183; /*lint -esym(752,OS_INTC_EIC183) allow to be unreferenced */
  extern uint16 OS_INTC_EIC184; /*lint -esym(752,OS_INTC_EIC184) allow to be unreferenced */
  extern uint16 OS_INTC_EIC185; /*lint -esym(752,OS_INTC_EIC185) allow to be unreferenced */
  extern uint16 OS_INTC_EIC186; /*lint -esym(752,OS_INTC_EIC186) allow to be unreferenced */
  extern uint16 OS_INTC_EIC187; /*lint -esym(752,OS_INTC_EIC187) allow to be unreferenced */
  extern uint16 OS_INTC_EIC188; /*lint -esym(752,OS_INTC_EIC188) allow to be unreferenced */
  extern uint16 OS_INTC_EIC189; /*lint -esym(752,OS_INTC_EIC189) allow to be unreferenced */
  extern uint16 OS_INTC_EIC190; /*lint -esym(752,OS_INTC_EIC190) allow to be unreferenced */
  extern uint16 OS_INTC_EIC191; /*lint -esym(752,OS_INTC_EIC191) allow to be unreferenced */
  extern uint16 OS_INTC_EIC192; /*lint -esym(752,OS_INTC_EIC192) allow to be unreferenced */
  extern uint16 OS_INTC_EIC193; /*lint -esym(752,OS_INTC_EIC193) allow to be unreferenced */
  extern uint16 OS_INTC_EIC194; /*lint -esym(752,OS_INTC_EIC194) allow to be unreferenced */
  extern uint16 OS_INTC_EIC195; /*lint -esym(752,OS_INTC_EIC195) allow to be unreferenced */
  extern uint16 OS_INTC_EIC196; /*lint -esym(752,OS_INTC_EIC196) allow to be unreferenced */
  extern uint16 OS_INTC_EIC197; /*lint -esym(752,OS_INTC_EIC197) allow to be unreferenced */
  extern uint16 OS_INTC_EIC198; /*lint -esym(752,OS_INTC_EIC198) allow to be unreferenced */
  extern uint16 OS_INTC_EIC199; /*lint -esym(752,OS_INTC_EIC199) allow to be unreferenced */
  extern uint16 OS_INTC_EIC200; /*lint -esym(752,OS_INTC_EIC200) allow to be unreferenced */
  extern uint16 OS_INTC_EIC201; /*lint -esym(752,OS_INTC_EIC201) allow to be unreferenced */
  extern uint16 OS_INTC_EIC202; /*lint -esym(752,OS_INTC_EIC202) allow to be unreferenced */
  extern uint16 OS_INTC_EIC203; /*lint -esym(752,OS_INTC_EIC203) allow to be unreferenced */
  extern uint16 OS_INTC_EIC204; /*lint -esym(752,OS_INTC_EIC204) allow to be unreferenced */
  extern uint16 OS_INTC_EIC205; /*lint -esym(752,OS_INTC_EIC205) allow to be unreferenced */
  extern uint16 OS_INTC_EIC206; /*lint -esym(752,OS_INTC_EIC206) allow to be unreferenced */
  extern uint16 OS_INTC_EIC207; /*lint -esym(752,OS_INTC_EIC207) allow to be unreferenced */
  extern uint16 OS_INTC_EIC208; /*lint -esym(752,OS_INTC_EIC208) allow to be unreferenced */
  extern uint16 OS_INTC_EIC209; /*lint -esym(752,OS_INTC_EIC209) allow to be unreferenced */
  extern uint16 OS_INTC_EIC210; /*lint -esym(752,OS_INTC_EIC210) allow to be unreferenced */
  extern uint16 OS_INTC_EIC211; /*lint -esym(752,OS_INTC_EIC211) allow to be unreferenced */
  extern uint16 OS_INTC_EIC212; /*lint -esym(752,OS_INTC_EIC212) allow to be unreferenced */
  extern uint16 OS_INTC_EIC213; /*lint -esym(752,OS_INTC_EIC213) allow to be unreferenced */
  extern uint16 OS_INTC_EIC214; /*lint -esym(752,OS_INTC_EIC214) allow to be unreferenced */
  extern uint16 OS_INTC_EIC215; /*lint -esym(752,OS_INTC_EIC215) allow to be unreferenced */
  extern uint16 OS_INTC_EIC216; /*lint -esym(752,OS_INTC_EIC216) allow to be unreferenced */
  extern uint16 OS_INTC_EIC217; /*lint -esym(752,OS_INTC_EIC217) allow to be unreferenced */
  extern uint16 OS_INTC_EIC218; /*lint -esym(752,OS_INTC_EIC218) allow to be unreferenced */
  extern uint16 OS_INTC_EIC219; /*lint -esym(752,OS_INTC_EIC219) allow to be unreferenced */
  extern uint16 OS_INTC_EIC220; /*lint -esym(752,OS_INTC_EIC220) allow to be unreferenced */
  extern uint16 OS_INTC_EIC221; /*lint -esym(752,OS_INTC_EIC221) allow to be unreferenced */
  extern uint16 OS_INTC_EIC222; /*lint -esym(752,OS_INTC_EIC222) allow to be unreferenced */
  extern uint16 OS_INTC_EIC223; /*lint -esym(752,OS_INTC_EIC223) allow to be unreferenced */
  extern uint16 OS_INTC_EIC224; /*lint -esym(752,OS_INTC_EIC224) allow to be unreferenced */
  extern uint16 OS_INTC_EIC225; /*lint -esym(752,OS_INTC_EIC225) allow to be unreferenced */
  extern uint16 OS_INTC_EIC226; /*lint -esym(752,OS_INTC_EIC226) allow to be unreferenced */
  extern uint16 OS_INTC_EIC227; /*lint -esym(752,OS_INTC_EIC227) allow to be unreferenced */
  extern uint16 OS_INTC_EIC228; /*lint -esym(752,OS_INTC_EIC228) allow to be unreferenced */
  extern uint16 OS_INTC_EIC229; /*lint -esym(752,OS_INTC_EIC229) allow to be unreferenced */
  extern uint16 OS_INTC_EIC230; /*lint -esym(752,OS_INTC_EIC230) allow to be unreferenced */
  extern uint16 OS_INTC_EIC231; /*lint -esym(752,OS_INTC_EIC231) allow to be unreferenced */
  extern uint16 OS_INTC_EIC232; /*lint -esym(752,OS_INTC_EIC232) allow to be unreferenced */
  extern uint16 OS_INTC_EIC233; /*lint -esym(752,OS_INTC_EIC233) allow to be unreferenced */
  extern uint16 OS_INTC_EIC234; /*lint -esym(752,OS_INTC_EIC234) allow to be unreferenced */
  extern uint16 OS_INTC_EIC235; /*lint -esym(752,OS_INTC_EIC235) allow to be unreferenced */
  extern uint16 OS_INTC_EIC236; /*lint -esym(752,OS_INTC_EIC236) allow to be unreferenced */
  extern uint16 OS_INTC_EIC237; /*lint -esym(752,OS_INTC_EIC237) allow to be unreferenced */
  extern uint16 OS_INTC_EIC238; /*lint -esym(752,OS_INTC_EIC238) allow to be unreferenced */
  extern uint16 OS_INTC_EIC239; /*lint -esym(752,OS_INTC_EIC239) allow to be unreferenced */
  extern uint16 OS_INTC_EIC240; /*lint -esym(752,OS_INTC_EIC240) allow to be unreferenced */
  extern uint16 OS_INTC_EIC241; /*lint -esym(752,OS_INTC_EIC241) allow to be unreferenced */
  extern uint16 OS_INTC_EIC242; /*lint -esym(752,OS_INTC_EIC242) allow to be unreferenced */
  extern uint16 OS_INTC_EIC243; /*lint -esym(752,OS_INTC_EIC243) allow to be unreferenced */
  extern uint16 OS_INTC_EIC244; /*lint -esym(752,OS_INTC_EIC244) allow to be unreferenced */
  extern uint16 OS_INTC_EIC245; /*lint -esym(752,OS_INTC_EIC245) allow to be unreferenced */
  extern uint16 OS_INTC_EIC246; /*lint -esym(752,OS_INTC_EIC246) allow to be unreferenced */
  extern uint16 OS_INTC_EIC247; /*lint -esym(752,OS_INTC_EIC247) allow to be unreferenced */
  extern uint16 OS_INTC_EIC248; /*lint -esym(752,OS_INTC_EIC248) allow to be unreferenced */
  extern uint16 OS_INTC_EIC249; /*lint -esym(752,OS_INTC_EIC249) allow to be unreferenced */
  extern uint16 OS_INTC_EIC250; /*lint -esym(752,OS_INTC_EIC250) allow to be unreferenced */
  extern uint16 OS_INTC_EIC251; /*lint -esym(752,OS_INTC_EIC251) allow to be unreferenced */
  extern uint16 OS_INTC_EIC252; /*lint -esym(752,OS_INTC_EIC252) allow to be unreferenced */
  extern uint16 OS_INTC_EIC253; /*lint -esym(752,OS_INTC_EIC253) allow to be unreferenced */
  extern uint16 OS_INTC_EIC254; /*lint -esym(752,OS_INTC_EIC254) allow to be unreferenced */
  extern uint16 OS_INTC_EIC255; /*lint -esym(752,OS_INTC_EIC255) allow to be unreferenced */
  extern uint16 OS_INTC_EIC256; /*lint -esym(752,OS_INTC_EIC256) allow to be unreferenced */
  extern uint16 OS_INTC_EIC257; /*lint -esym(752,OS_INTC_EIC257) allow to be unreferenced */
  extern uint16 OS_INTC_EIC258; /*lint -esym(752,OS_INTC_EIC258) allow to be unreferenced */
  extern uint16 OS_INTC_EIC259; /*lint -esym(752,OS_INTC_EIC259) allow to be unreferenced */
  extern uint16 OS_INTC_EIC260; /*lint -esym(752,OS_INTC_EIC260) allow to be unreferenced */
  extern uint16 OS_INTC_EIC261; /*lint -esym(752,OS_INTC_EIC261) allow to be unreferenced */
  extern uint16 OS_INTC_EIC262; /*lint -esym(752,OS_INTC_EIC262) allow to be unreferenced */
  extern uint16 OS_INTC_EIC263; /*lint -esym(752,OS_INTC_EIC263) allow to be unreferenced */
  extern uint16 OS_INTC_EIC264; /*lint -esym(752,OS_INTC_EIC264) allow to be unreferenced */
  extern uint16 OS_INTC_EIC265; /*lint -esym(752,OS_INTC_EIC265) allow to be unreferenced */
  extern uint16 OS_INTC_EIC266; /*lint -esym(752,OS_INTC_EIC266) allow to be unreferenced */
  extern uint16 OS_INTC_EIC267; /*lint -esym(752,OS_INTC_EIC267) allow to be unreferenced */
  extern uint16 OS_INTC_EIC268; /*lint -esym(752,OS_INTC_EIC268) allow to be unreferenced */
  extern uint16 OS_INTC_EIC269; /*lint -esym(752,OS_INTC_EIC269) allow to be unreferenced */
  extern uint16 OS_INTC_EIC270; /*lint -esym(752,OS_INTC_EIC270) allow to be unreferenced */
  extern uint16 OS_INTC_EIC271; /*lint -esym(752,OS_INTC_EIC271) allow to be unreferenced */
  extern uint16 OS_INTC_EIC272; /*lint -esym(752,OS_INTC_EIC272) allow to be unreferenced */
  extern uint16 OS_INTC_EIC273; /*lint -esym(752,OS_INTC_EIC273) allow to be unreferenced */
  extern uint16 OS_INTC_EIC274; /*lint -esym(752,OS_INTC_EIC274) allow to be unreferenced */
  extern uint16 OS_INTC_EIC275; /*lint -esym(752,OS_INTC_EIC275) allow to be unreferenced */
  extern uint16 OS_INTC_EIC276; /*lint -esym(752,OS_INTC_EIC276) allow to be unreferenced */
  extern uint16 OS_INTC_EIC277; /*lint -esym(752,OS_INTC_EIC277) allow to be unreferenced */
  extern uint16 OS_INTC_EIC278; /*lint -esym(752,OS_INTC_EIC278) allow to be unreferenced */
  extern uint16 OS_INTC_EIC279; /*lint -esym(752,OS_INTC_EIC279) allow to be unreferenced */
  extern uint16 OS_INTC_EIC280; /*lint -esym(752,OS_INTC_EIC280) allow to be unreferenced */
  extern uint16 OS_INTC_EIC281; /*lint -esym(752,OS_INTC_EIC281) allow to be unreferenced */
  extern uint16 OS_INTC_EIC282; /*lint -esym(752,OS_INTC_EIC282) allow to be unreferenced */
  extern uint16 OS_INTC_EIC283; /*lint -esym(752,OS_INTC_EIC283) allow to be unreferenced */
  extern uint16 OS_INTC_EIC284; /*lint -esym(752,OS_INTC_EIC284) allow to be unreferenced */
  extern uint16 OS_INTC_EIC285; /*lint -esym(752,OS_INTC_EIC285) allow to be unreferenced */
  extern uint16 OS_INTC_EIC286; /*lint -esym(752,OS_INTC_EIC286) allow to be unreferenced */
  extern uint16 OS_INTC_EIC287; /*lint -esym(752,OS_INTC_EIC287) allow to be unreferenced */
  extern uint16 OS_INTC_EIC288; /*lint -esym(752,OS_INTC_EIC288) allow to be unreferenced */
  extern uint16 OS_INTC_EIC289; /*lint -esym(752,OS_INTC_EIC289) allow to be unreferenced */
  extern uint16 OS_INTC_EIC290; /*lint -esym(752,OS_INTC_EIC290) allow to be unreferenced */
  extern uint16 OS_INTC_EIC291; /*lint -esym(752,OS_INTC_EIC291) allow to be unreferenced */
  extern uint16 OS_INTC_EIC292; /*lint -esym(752,OS_INTC_EIC292) allow to be unreferenced */
  extern uint16 OS_INTC_EIC293; /*lint -esym(752,OS_INTC_EIC293) allow to be unreferenced */
  extern uint16 OS_INTC_EIC294; /*lint -esym(752,OS_INTC_EIC294) allow to be unreferenced */
  extern uint16 OS_INTC_EIC295; /*lint -esym(752,OS_INTC_EIC295) allow to be unreferenced */
  extern uint16 OS_INTC_EIC296; /*lint -esym(752,OS_INTC_EIC296) allow to be unreferenced */
  extern uint16 OS_INTC_EIC297; /*lint -esym(752,OS_INTC_EIC297) allow to be unreferenced */
  extern uint16 OS_INTC_EIC298; /*lint -esym(752,OS_INTC_EIC298) allow to be unreferenced */
  extern uint16 OS_INTC_EIC299; /*lint -esym(752,OS_INTC_EIC299) allow to be unreferenced */
  extern uint16 OS_INTC_EIC300; /*lint -esym(752,OS_INTC_EIC300) allow to be unreferenced */
  extern uint16 OS_INTC_EIC301; /*lint -esym(752,OS_INTC_EIC301) allow to be unreferenced */
  extern uint16 OS_INTC_EIC302; /*lint -esym(752,OS_INTC_EIC302) allow to be unreferenced */
  extern uint16 OS_INTC_EIC303; /*lint -esym(752,OS_INTC_EIC303) allow to be unreferenced */
  extern uint16 OS_INTC_EIC304; /*lint -esym(752,OS_INTC_EIC304) allow to be unreferenced */
  extern uint16 OS_INTC_EIC305; /*lint -esym(752,OS_INTC_EIC305) allow to be unreferenced */
  extern uint16 OS_INTC_EIC306; /*lint -esym(752,OS_INTC_EIC306) allow to be unreferenced */
  extern uint16 OS_INTC_EIC307; /*lint -esym(752,OS_INTC_EIC307) allow to be unreferenced */
  extern uint16 OS_INTC_EIC308; /*lint -esym(752,OS_INTC_EIC308) allow to be unreferenced */
  extern uint16 OS_INTC_EIC309; /*lint -esym(752,OS_INTC_EIC309) allow to be unreferenced */
  extern uint16 OS_INTC_EIC310; /*lint -esym(752,OS_INTC_EIC310) allow to be unreferenced */
  extern uint16 OS_INTC_EIC311; /*lint -esym(752,OS_INTC_EIC311) allow to be unreferenced */
  extern uint16 OS_INTC_EIC312; /*lint -esym(752,OS_INTC_EIC312) allow to be unreferenced */
  extern uint16 OS_INTC_EIC313; /*lint -esym(752,OS_INTC_EIC313) allow to be unreferenced */
  extern uint16 OS_INTC_EIC314; /*lint -esym(752,OS_INTC_EIC314) allow to be unreferenced */
  extern uint16 OS_INTC_EIC315; /*lint -esym(752,OS_INTC_EIC315) allow to be unreferenced */
  extern uint16 OS_INTC_EIC316; /*lint -esym(752,OS_INTC_EIC316) allow to be unreferenced */
  extern uint16 OS_INTC_EIC317; /*lint -esym(752,OS_INTC_EIC317) allow to be unreferenced */
  extern uint16 OS_INTC_EIC318; /*lint -esym(752,OS_INTC_EIC318) allow to be unreferenced */
  extern uint16 OS_INTC_EIC319; /*lint -esym(752,OS_INTC_EIC319) allow to be unreferenced */
  extern uint16 OS_INTC_EIC320; /*lint -esym(752,OS_INTC_EIC320) allow to be unreferenced */
  extern uint16 OS_INTC_EIC321; /*lint -esym(752,OS_INTC_EIC321) allow to be unreferenced */
  extern uint16 OS_INTC_EIC322; /*lint -esym(752,OS_INTC_EIC322) allow to be unreferenced */
  extern uint16 OS_INTC_EIC323; /*lint -esym(752,OS_INTC_EIC323) allow to be unreferenced */
  extern uint16 OS_INTC_EIC324; /*lint -esym(752,OS_INTC_EIC324) allow to be unreferenced */
  extern uint16 OS_INTC_EIC325; /*lint -esym(752,OS_INTC_EIC325) allow to be unreferenced */
  extern uint16 OS_INTC_EIC326; /*lint -esym(752,OS_INTC_EIC326) allow to be unreferenced */
  extern uint16 OS_INTC_EIC327; /*lint -esym(752,OS_INTC_EIC327) allow to be unreferenced */
  extern uint16 OS_INTC_EIC328; /*lint -esym(752,OS_INTC_EIC328) allow to be unreferenced */
  extern uint16 OS_INTC_EIC329; /*lint -esym(752,OS_INTC_EIC329) allow to be unreferenced */
  extern uint16 OS_INTC_EIC330; /*lint -esym(752,OS_INTC_EIC330) allow to be unreferenced */
  extern uint16 OS_INTC_EIC331; /*lint -esym(752,OS_INTC_EIC331) allow to be unreferenced */
  extern uint16 OS_INTC_EIC332; /*lint -esym(752,OS_INTC_EIC332) allow to be unreferenced */
  extern uint16 OS_INTC_EIC333; /*lint -esym(752,OS_INTC_EIC333) allow to be unreferenced */
  extern uint16 OS_INTC_EIC334; /*lint -esym(752,OS_INTC_EIC334) allow to be unreferenced */
  extern uint16 OS_INTC_EIC335; /*lint -esym(752,OS_INTC_EIC335) allow to be unreferenced */
  extern uint16 OS_INTC_EIC336; /*lint -esym(752,OS_INTC_EIC336) allow to be unreferenced */
  extern uint16 OS_INTC_EIC337; /*lint -esym(752,OS_INTC_EIC337) allow to be unreferenced */
  extern uint16 OS_INTC_EIC338; /*lint -esym(752,OS_INTC_EIC338) allow to be unreferenced */
  extern uint16 OS_INTC_EIC339; /*lint -esym(752,OS_INTC_EIC339) allow to be unreferenced */
  extern uint16 OS_INTC_EIC340; /*lint -esym(752,OS_INTC_EIC340) allow to be unreferenced */
  extern uint16 OS_INTC_EIC341; /*lint -esym(752,OS_INTC_EIC341) allow to be unreferenced */
  extern uint16 OS_INTC_EIC342; /*lint -esym(752,OS_INTC_EIC342) allow to be unreferenced */
  extern uint16 OS_INTC_EIC343; /*lint -esym(752,OS_INTC_EIC343) allow to be unreferenced */
  extern uint16 OS_INTC_EIC344; /*lint -esym(752,OS_INTC_EIC344) allow to be unreferenced */
  extern uint16 OS_INTC_EIC345; /*lint -esym(752,OS_INTC_EIC345) allow to be unreferenced */
  extern uint16 OS_INTC_EIC346; /*lint -esym(752,OS_INTC_EIC346) allow to be unreferenced */
  extern uint16 OS_INTC_EIC347; /*lint -esym(752,OS_INTC_EIC347) allow to be unreferenced */
  extern uint16 OS_INTC_EIC348; /*lint -esym(752,OS_INTC_EIC348) allow to be unreferenced */
  extern uint16 OS_INTC_EIC349; /*lint -esym(752,OS_INTC_EIC349) allow to be unreferenced */
  extern uint16 OS_INTC_EIC350; /*lint -esym(752,OS_INTC_EIC350) allow to be unreferenced */
  extern uint16 OS_INTC_EIC351; /*lint -esym(752,OS_INTC_EIC351) allow to be unreferenced */
  extern uint16 OS_INTC_EIC352; /*lint -esym(752,OS_INTC_EIC352) allow to be unreferenced */
  extern uint16 OS_INTC_EIC353; /*lint -esym(752,OS_INTC_EIC353) allow to be unreferenced */
  extern uint16 OS_INTC_EIC354; /*lint -esym(752,OS_INTC_EIC354) allow to be unreferenced */
  extern uint16 OS_INTC_EIC355; /*lint -esym(752,OS_INTC_EIC355) allow to be unreferenced */
  extern uint16 OS_INTC_EIC356; /*lint -esym(752,OS_INTC_EIC356) allow to be unreferenced */
  extern uint16 OS_INTC_EIC357; /*lint -esym(752,OS_INTC_EIC357) allow to be unreferenced */
  extern uint16 OS_INTC_EIC358; /*lint -esym(752,OS_INTC_EIC358) allow to be unreferenced */
  extern uint16 OS_INTC_EIC359; /*lint -esym(752,OS_INTC_EIC359) allow to be unreferenced */
  extern uint16 OS_INTC_EIC360; /*lint -esym(752,OS_INTC_EIC360) allow to be unreferenced */
  extern uint16 OS_INTC_EIC361; /*lint -esym(752,OS_INTC_EIC361) allow to be unreferenced */
  extern uint16 OS_INTC_EIC362; /*lint -esym(752,OS_INTC_EIC362) allow to be unreferenced */
  extern uint16 OS_INTC_EIC363; /*lint -esym(752,OS_INTC_EIC363) allow to be unreferenced */
  extern uint16 OS_INTC_EIC364; /*lint -esym(752,OS_INTC_EIC364) allow to be unreferenced */
  extern uint16 OS_INTC_EIC365; /*lint -esym(752,OS_INTC_EIC365) allow to be unreferenced */
  extern uint16 OS_INTC_EIC366; /*lint -esym(752,OS_INTC_EIC366) allow to be unreferenced */
  extern uint16 OS_INTC_EIC367; /*lint -esym(752,OS_INTC_EIC367) allow to be unreferenced */
  extern uint16 OS_INTC_EIC368; /*lint -esym(752,OS_INTC_EIC368) allow to be unreferenced */
  extern uint16 OS_INTC_EIC369; /*lint -esym(752,OS_INTC_EIC369) allow to be unreferenced */
  extern uint16 OS_INTC_EIC370; /*lint -esym(752,OS_INTC_EIC370) allow to be unreferenced */
  extern uint16 OS_INTC_EIC371; /*lint -esym(752,OS_INTC_EIC371) allow to be unreferenced */
  extern uint16 OS_INTC_EIC372; /*lint -esym(752,OS_INTC_EIC372) allow to be unreferenced */
  extern uint16 OS_INTC_EIC373; /*lint -esym(752,OS_INTC_EIC373) allow to be unreferenced */
  extern uint16 OS_INTC_EIC374; /*lint -esym(752,OS_INTC_EIC374) allow to be unreferenced */
  extern uint16 OS_INTC_EIC375; /*lint -esym(752,OS_INTC_EIC375) allow to be unreferenced */
  extern uint16 OS_INTC_EIC376; /*lint -esym(752,OS_INTC_EIC376) allow to be unreferenced */
  extern uint16 OS_INTC_EIC377; /*lint -esym(752,OS_INTC_EIC377) allow to be unreferenced */
  extern uint16 OS_INTC_EIC378; /*lint -esym(752,OS_INTC_EIC378) allow to be unreferenced */
  extern uint16 OS_INTC_EIC379; /*lint -esym(752,OS_INTC_EIC379) allow to be unreferenced */
  extern uint16 OS_INTC_EIC380; /*lint -esym(752,OS_INTC_EIC380) allow to be unreferenced */
  extern uint16 OS_INTC_EIC381; /*lint -esym(752,OS_INTC_EIC381) allow to be unreferenced */
  extern uint16 OS_INTC_EIC382; /*lint -esym(752,OS_INTC_EIC382) allow to be unreferenced */
  extern uint16 OS_INTC_EIC383; /*lint -esym(752,OS_INTC_EIC383) allow to be unreferenced */
  extern uint16 OS_INTC_EIC384; /*lint -esym(752,OS_INTC_EIC384) allow to be unreferenced */
  extern uint16 OS_INTC_EIC385; /*lint -esym(752,OS_INTC_EIC385) allow to be unreferenced */
  extern uint16 OS_INTC_EIC386; /*lint -esym(752,OS_INTC_EIC386) allow to be unreferenced */
  extern uint16 OS_INTC_EIC387; /*lint -esym(752,OS_INTC_EIC387) allow to be unreferenced */
  extern uint16 OS_INTC_EIC388; /*lint -esym(752,OS_INTC_EIC388) allow to be unreferenced */
  extern uint16 OS_INTC_EIC389; /*lint -esym(752,OS_INTC_EIC389) allow to be unreferenced */
  extern uint16 OS_INTC_EIC390; /*lint -esym(752,OS_INTC_EIC390) allow to be unreferenced */
  extern uint16 OS_INTC_EIC391; /*lint -esym(752,OS_INTC_EIC391) allow to be unreferenced */
  extern uint16 OS_INTC_EIC392; /*lint -esym(752,OS_INTC_EIC392) allow to be unreferenced */
  extern uint16 OS_INTC_EIC393; /*lint -esym(752,OS_INTC_EIC393) allow to be unreferenced */
  extern uint16 OS_INTC_EIC394; /*lint -esym(752,OS_INTC_EIC394) allow to be unreferenced */
  extern uint16 OS_INTC_EIC395; /*lint -esym(752,OS_INTC_EIC395) allow to be unreferenced */
  extern uint16 OS_INTC_EIC396; /*lint -esym(752,OS_INTC_EIC396) allow to be unreferenced */
  extern uint16 OS_INTC_EIC397; /*lint -esym(752,OS_INTC_EIC397) allow to be unreferenced */
  extern uint16 OS_INTC_EIC398; /*lint -esym(752,OS_INTC_EIC398) allow to be unreferenced */
  extern uint16 OS_INTC_EIC399; /*lint -esym(752,OS_INTC_EIC399) allow to be unreferenced */
  extern uint16 OS_INTC_EIC400; /*lint -esym(752,OS_INTC_EIC400) allow to be unreferenced */
  extern uint16 OS_INTC_EIC401; /*lint -esym(752,OS_INTC_EIC401) allow to be unreferenced */
  extern uint16 OS_INTC_EIC402; /*lint -esym(752,OS_INTC_EIC402) allow to be unreferenced */
  extern uint16 OS_INTC_EIC403; /*lint -esym(752,OS_INTC_EIC403) allow to be unreferenced */
  extern uint16 OS_INTC_EIC404; /*lint -esym(752,OS_INTC_EIC404) allow to be unreferenced */
  extern uint16 OS_INTC_EIC405; /*lint -esym(752,OS_INTC_EIC405) allow to be unreferenced */
  extern uint16 OS_INTC_EIC406; /*lint -esym(752,OS_INTC_EIC406) allow to be unreferenced */
  extern uint16 OS_INTC_EIC407; /*lint -esym(752,OS_INTC_EIC407) allow to be unreferenced */
  extern uint16 OS_INTC_EIC408; /*lint -esym(752,OS_INTC_EIC408) allow to be unreferenced */
  extern uint16 OS_INTC_EIC409; /*lint -esym(752,OS_INTC_EIC409) allow to be unreferenced */
  extern uint16 OS_INTC_EIC410; /*lint -esym(752,OS_INTC_EIC410) allow to be unreferenced */
  extern uint16 OS_INTC_EIC411; /*lint -esym(752,OS_INTC_EIC411) allow to be unreferenced */
  extern uint16 OS_INTC_EIC412; /*lint -esym(752,OS_INTC_EIC412) allow to be unreferenced */
  extern uint16 OS_INTC_EIC413; /*lint -esym(752,OS_INTC_EIC413) allow to be unreferenced */
  extern uint16 OS_INTC_EIC414; /*lint -esym(752,OS_INTC_EIC414) allow to be unreferenced */
  extern uint16 OS_INTC_EIC415; /*lint -esym(752,OS_INTC_EIC415) allow to be unreferenced */
  extern uint16 OS_INTC_EIC416; /*lint -esym(752,OS_INTC_EIC416) allow to be unreferenced */
  extern uint16 OS_INTC_EIC417; /*lint -esym(752,OS_INTC_EIC417) allow to be unreferenced */
  extern uint16 OS_INTC_EIC418; /*lint -esym(752,OS_INTC_EIC418) allow to be unreferenced */
  extern uint16 OS_INTC_EIC419; /*lint -esym(752,OS_INTC_EIC419) allow to be unreferenced */
  extern uint16 OS_INTC_EIC420; /*lint -esym(752,OS_INTC_EIC420) allow to be unreferenced */
  extern uint16 OS_INTC_EIC421; /*lint -esym(752,OS_INTC_EIC421) allow to be unreferenced */
  extern uint16 OS_INTC_EIC422; /*lint -esym(752,OS_INTC_EIC422) allow to be unreferenced */
  extern uint16 OS_INTC_EIC423; /*lint -esym(752,OS_INTC_EIC423) allow to be unreferenced */
  extern uint16 OS_INTC_EIC424; /*lint -esym(752,OS_INTC_EIC424) allow to be unreferenced */
  extern uint16 OS_INTC_EIC425; /*lint -esym(752,OS_INTC_EIC425) allow to be unreferenced */
  extern uint16 OS_INTC_EIC426; /*lint -esym(752,OS_INTC_EIC426) allow to be unreferenced */
  extern uint16 OS_INTC_EIC427; /*lint -esym(752,OS_INTC_EIC427) allow to be unreferenced */
  extern uint16 OS_INTC_EIC428; /*lint -esym(752,OS_INTC_EIC428) allow to be unreferenced */
  extern uint16 OS_INTC_EIC429; /*lint -esym(752,OS_INTC_EIC429) allow to be unreferenced */
  extern uint16 OS_INTC_EIC430; /*lint -esym(752,OS_INTC_EIC430) allow to be unreferenced */
  extern uint16 OS_INTC_EIC431; /*lint -esym(752,OS_INTC_EIC431) allow to be unreferenced */
  extern uint16 OS_INTC_EIC432; /*lint -esym(752,OS_INTC_EIC432) allow to be unreferenced */
  extern uint16 OS_INTC_EIC433; /*lint -esym(752,OS_INTC_EIC433) allow to be unreferenced */
  extern uint16 OS_INTC_EIC434; /*lint -esym(752,OS_INTC_EIC434) allow to be unreferenced */
  extern uint16 OS_INTC_EIC435; /*lint -esym(752,OS_INTC_EIC435) allow to be unreferenced */
  extern uint16 OS_INTC_EIC436; /*lint -esym(752,OS_INTC_EIC436) allow to be unreferenced */
  extern uint16 OS_INTC_EIC437; /*lint -esym(752,OS_INTC_EIC437) allow to be unreferenced */
  extern uint16 OS_INTC_EIC438; /*lint -esym(752,OS_INTC_EIC438) allow to be unreferenced */
  extern uint16 OS_INTC_EIC439; /*lint -esym(752,OS_INTC_EIC439) allow to be unreferenced */
  extern uint16 OS_INTC_EIC440; /*lint -esym(752,OS_INTC_EIC440) allow to be unreferenced */
  extern uint16 OS_INTC_EIC441; /*lint -esym(752,OS_INTC_EIC441) allow to be unreferenced */
  extern uint16 OS_INTC_EIC442; /*lint -esym(752,OS_INTC_EIC442) allow to be unreferenced */
  extern uint16 OS_INTC_EIC443; /*lint -esym(752,OS_INTC_EIC443) allow to be unreferenced */
  extern uint16 OS_INTC_EIC444; /*lint -esym(752,OS_INTC_EIC444) allow to be unreferenced */
  extern uint16 OS_INTC_EIC445; /*lint -esym(752,OS_INTC_EIC445) allow to be unreferenced */
  extern uint16 OS_INTC_EIC446; /*lint -esym(752,OS_INTC_EIC446) allow to be unreferenced */
  extern uint16 OS_INTC_EIC447; /*lint -esym(752,OS_INTC_EIC447) allow to be unreferenced */
  extern uint16 OS_INTC_EIC448; /*lint -esym(752,OS_INTC_EIC448) allow to be unreferenced */
  extern uint16 OS_INTC_EIC449; /*lint -esym(752,OS_INTC_EIC449) allow to be unreferenced */
  extern uint16 OS_INTC_EIC450; /*lint -esym(752,OS_INTC_EIC450) allow to be unreferenced */
  extern uint16 OS_INTC_EIC451; /*lint -esym(752,OS_INTC_EIC451) allow to be unreferenced */
  extern uint16 OS_INTC_EIC452; /*lint -esym(752,OS_INTC_EIC452) allow to be unreferenced */
  extern uint16 OS_INTC_EIC453; /*lint -esym(752,OS_INTC_EIC453) allow to be unreferenced */
  extern uint16 OS_INTC_EIC454; /*lint -esym(752,OS_INTC_EIC454) allow to be unreferenced */
  extern uint16 OS_INTC_EIC455; /*lint -esym(752,OS_INTC_EIC455) allow to be unreferenced */
  extern uint16 OS_INTC_EIC456; /*lint -esym(752,OS_INTC_EIC456) allow to be unreferenced */
  extern uint16 OS_INTC_EIC457; /*lint -esym(752,OS_INTC_EIC457) allow to be unreferenced */
  extern uint16 OS_INTC_EIC458; /*lint -esym(752,OS_INTC_EIC458) allow to be unreferenced */
  extern uint16 OS_INTC_EIC459; /*lint -esym(752,OS_INTC_EIC459) allow to be unreferenced */
  extern uint16 OS_INTC_EIC460; /*lint -esym(752,OS_INTC_EIC460) allow to be unreferenced */
  extern uint16 OS_INTC_EIC461; /*lint -esym(752,OS_INTC_EIC461) allow to be unreferenced */
  extern uint16 OS_INTC_EIC462; /*lint -esym(752,OS_INTC_EIC462) allow to be unreferenced */
  extern uint16 OS_INTC_EIC463; /*lint -esym(752,OS_INTC_EIC463) allow to be unreferenced */
  extern uint16 OS_INTC_EIC464; /*lint -esym(752,OS_INTC_EIC464) allow to be unreferenced */
  extern uint16 OS_INTC_EIC465; /*lint -esym(752,OS_INTC_EIC465) allow to be unreferenced */
  extern uint16 OS_INTC_EIC466; /*lint -esym(752,OS_INTC_EIC466) allow to be unreferenced */
  extern uint16 OS_INTC_EIC467; /*lint -esym(752,OS_INTC_EIC467) allow to be unreferenced */
  extern uint16 OS_INTC_EIC468; /*lint -esym(752,OS_INTC_EIC468) allow to be unreferenced */
  extern uint16 OS_INTC_EIC469; /*lint -esym(752,OS_INTC_EIC469) allow to be unreferenced */
  extern uint16 OS_INTC_EIC470; /*lint -esym(752,OS_INTC_EIC470) allow to be unreferenced */
  extern uint16 OS_INTC_EIC471; /*lint -esym(752,OS_INTC_EIC471) allow to be unreferenced */
  extern uint16 OS_INTC_EIC472; /*lint -esym(752,OS_INTC_EIC472) allow to be unreferenced */
  extern uint16 OS_INTC_EIC473; /*lint -esym(752,OS_INTC_EIC473) allow to be unreferenced */
  extern uint16 OS_INTC_EIC474; /*lint -esym(752,OS_INTC_EIC474) allow to be unreferenced */
  extern uint16 OS_INTC_EIC475; /*lint -esym(752,OS_INTC_EIC475) allow to be unreferenced */
  extern uint16 OS_INTC_EIC476; /*lint -esym(752,OS_INTC_EIC476) allow to be unreferenced */
  extern uint16 OS_INTC_EIC477; /*lint -esym(752,OS_INTC_EIC477) allow to be unreferenced */
  extern uint16 OS_INTC_EIC478; /*lint -esym(752,OS_INTC_EIC478) allow to be unreferenced */
  extern uint16 OS_INTC_EIC479; /*lint -esym(752,OS_INTC_EIC479) allow to be unreferenced */
  extern uint16 OS_INTC_EIC480; /*lint -esym(752,OS_INTC_EIC480) allow to be unreferenced */
  extern uint16 OS_INTC_EIC481; /*lint -esym(752,OS_INTC_EIC481) allow to be unreferenced */
  extern uint16 OS_INTC_EIC482; /*lint -esym(752,OS_INTC_EIC482) allow to be unreferenced */
  extern uint16 OS_INTC_EIC483; /*lint -esym(752,OS_INTC_EIC483) allow to be unreferenced */
  extern uint16 OS_INTC_EIC484; /*lint -esym(752,OS_INTC_EIC484) allow to be unreferenced */
  extern uint16 OS_INTC_EIC485; /*lint -esym(752,OS_INTC_EIC485) allow to be unreferenced */
  extern uint16 OS_INTC_EIC486; /*lint -esym(752,OS_INTC_EIC486) allow to be unreferenced */
  extern uint16 OS_INTC_EIC487; /*lint -esym(752,OS_INTC_EIC487) allow to be unreferenced */
  extern uint16 OS_INTC_EIC488; /*lint -esym(752,OS_INTC_EIC488) allow to be unreferenced */
  extern uint16 OS_INTC_EIC489; /*lint -esym(752,OS_INTC_EIC489) allow to be unreferenced */
  extern uint16 OS_INTC_EIC490; /*lint -esym(752,OS_INTC_EIC490) allow to be unreferenced */
  extern uint16 OS_INTC_EIC491; /*lint -esym(752,OS_INTC_EIC491) allow to be unreferenced */
  extern uint16 OS_INTC_EIC492; /*lint -esym(752,OS_INTC_EIC492) allow to be unreferenced */
  extern uint16 OS_INTC_EIC493; /*lint -esym(752,OS_INTC_EIC493) allow to be unreferenced */
  extern uint16 OS_INTC_EIC494; /*lint -esym(752,OS_INTC_EIC494) allow to be unreferenced */
  extern uint16 OS_INTC_EIC495; /*lint -esym(752,OS_INTC_EIC495) allow to be unreferenced */
  extern uint16 OS_INTC_EIC496; /*lint -esym(752,OS_INTC_EIC496) allow to be unreferenced */
  extern uint16 OS_INTC_EIC497; /*lint -esym(752,OS_INTC_EIC497) allow to be unreferenced */
  extern uint16 OS_INTC_EIC498; /*lint -esym(752,OS_INTC_EIC498) allow to be unreferenced */
  extern uint16 OS_INTC_EIC499; /*lint -esym(752,OS_INTC_EIC499) allow to be unreferenced */
  extern uint16 OS_INTC_EIC500; /*lint -esym(752,OS_INTC_EIC500) allow to be unreferenced */
  extern uint16 OS_INTC_EIC501; /*lint -esym(752,OS_INTC_EIC501) allow to be unreferenced */
  extern uint16 OS_INTC_EIC502; /*lint -esym(752,OS_INTC_EIC502) allow to be unreferenced */
  extern uint16 OS_INTC_EIC503; /*lint -esym(752,OS_INTC_EIC503) allow to be unreferenced */
  extern uint16 OS_INTC_EIC504; /*lint -esym(752,OS_INTC_EIC504) allow to be unreferenced */
  extern uint16 OS_INTC_EIC505; /*lint -esym(752,OS_INTC_EIC505) allow to be unreferenced */
  extern uint16 OS_INTC_EIC506; /*lint -esym(752,OS_INTC_EIC506) allow to be unreferenced */
  extern uint16 OS_INTC_EIC507; /*lint -esym(752,OS_INTC_EIC507) allow to be unreferenced */
  extern uint16 OS_INTC_EIC508; /*lint -esym(752,OS_INTC_EIC508) allow to be unreferenced */
  extern uint16 OS_INTC_EIC509; /*lint -esym(752,OS_INTC_EIC509) allow to be unreferenced */
  extern uint16 OS_INTC_EIC510; /*lint -esym(752,OS_INTC_EIC510) allow to be unreferenced */
  extern uint16 OS_INTC_EIC511; /*lint -esym(752,OS_INTC_EIC511) allow to be unreferenced */
  extern uint16 OS_INTC_EIC512; /*lint -esym(752,OS_INTC_EIC512) allow to be unreferenced */
  extern uint16 OS_INTC_EIC513; /*lint -esym(752,OS_INTC_EIC513) allow to be unreferenced */
  extern uint16 OS_INTC_EIC514; /*lint -esym(752,OS_INTC_EIC514) allow to be unreferenced */
  extern uint16 OS_INTC_EIC515; /*lint -esym(752,OS_INTC_EIC515) allow to be unreferenced */
  extern uint16 OS_INTC_EIC516; /*lint -esym(752,OS_INTC_EIC516) allow to be unreferenced */
  extern uint16 OS_INTC_EIC517; /*lint -esym(752,OS_INTC_EIC517) allow to be unreferenced */
  extern uint16 OS_INTC_EIC518; /*lint -esym(752,OS_INTC_EIC518) allow to be unreferenced */
  extern uint16 OS_INTC_EIC519; /*lint -esym(752,OS_INTC_EIC519) allow to be unreferenced */
  extern uint16 OS_INTC_EIC520; /*lint -esym(752,OS_INTC_EIC520) allow to be unreferenced */
  extern uint16 OS_INTC_EIC521; /*lint -esym(752,OS_INTC_EIC521) allow to be unreferenced */
  extern uint16 OS_INTC_EIC522; /*lint -esym(752,OS_INTC_EIC522) allow to be unreferenced */
  extern uint16 OS_INTC_EIC523; /*lint -esym(752,OS_INTC_EIC523) allow to be unreferenced */
  extern uint16 OS_INTC_EIC524; /*lint -esym(752,OS_INTC_EIC524) allow to be unreferenced */
  extern uint16 OS_INTC_EIC525; /*lint -esym(752,OS_INTC_EIC525) allow to be unreferenced */
  extern uint16 OS_INTC_EIC526; /*lint -esym(752,OS_INTC_EIC526) allow to be unreferenced */
  extern uint16 OS_INTC_EIC527; /*lint -esym(752,OS_INTC_EIC527) allow to be unreferenced */
  extern uint16 OS_INTC_EIC528; /*lint -esym(752,OS_INTC_EIC528) allow to be unreferenced */
  extern uint16 OS_INTC_EIC529; /*lint -esym(752,OS_INTC_EIC529) allow to be unreferenced */
  extern uint16 OS_INTC_EIC530; /*lint -esym(752,OS_INTC_EIC530) allow to be unreferenced */
  extern uint16 OS_INTC_EIC531; /*lint -esym(752,OS_INTC_EIC531) allow to be unreferenced */
  extern uint16 OS_INTC_EIC532; /*lint -esym(752,OS_INTC_EIC532) allow to be unreferenced */
  extern uint16 OS_INTC_EIC533; /*lint -esym(752,OS_INTC_EIC533) allow to be unreferenced */
  extern uint16 OS_INTC_EIC534; /*lint -esym(752,OS_INTC_EIC534) allow to be unreferenced */
  extern uint16 OS_INTC_EIC535; /*lint -esym(752,OS_INTC_EIC535) allow to be unreferenced */
  extern uint16 OS_INTC_EIC536; /*lint -esym(752,OS_INTC_EIC536) allow to be unreferenced */
  extern uint16 OS_INTC_EIC537; /*lint -esym(752,OS_INTC_EIC537) allow to be unreferenced */
  extern uint16 OS_INTC_EIC538; /*lint -esym(752,OS_INTC_EIC538) allow to be unreferenced */
  extern uint16 OS_INTC_EIC539; /*lint -esym(752,OS_INTC_EIC539) allow to be unreferenced */
  extern uint16 OS_INTC_EIC540; /*lint -esym(752,OS_INTC_EIC540) allow to be unreferenced */
  extern uint16 OS_INTC_EIC541; /*lint -esym(752,OS_INTC_EIC541) allow to be unreferenced */
  extern uint16 OS_INTC_EIC542; /*lint -esym(752,OS_INTC_EIC542) allow to be unreferenced */
  extern uint16 OS_INTC_EIC543; /*lint -esym(752,OS_INTC_EIC543) allow to be unreferenced */
  extern uint16 OS_INTC_EIC544; /*lint -esym(752,OS_INTC_EIC544) allow to be unreferenced */
  extern uint16 OS_INTC_EIC545; /*lint -esym(752,OS_INTC_EIC545) allow to be unreferenced */
  extern uint16 OS_INTC_EIC546; /*lint -esym(752,OS_INTC_EIC546) allow to be unreferenced */
  extern uint16 OS_INTC_EIC547; /*lint -esym(752,OS_INTC_EIC547) allow to be unreferenced */
  extern uint16 OS_INTC_EIC548; /*lint -esym(752,OS_INTC_EIC548) allow to be unreferenced */
  extern uint16 OS_INTC_EIC549; /*lint -esym(752,OS_INTC_EIC549) allow to be unreferenced */
  extern uint16 OS_INTC_EIC550; /*lint -esym(752,OS_INTC_EIC550) allow to be unreferenced */
  extern uint16 OS_INTC_EIC551; /*lint -esym(752,OS_INTC_EIC551) allow to be unreferenced */
  extern uint16 OS_INTC_EIC552; /*lint -esym(752,OS_INTC_EIC552) allow to be unreferenced */
  extern uint16 OS_INTC_EIC553; /*lint -esym(752,OS_INTC_EIC553) allow to be unreferenced */
  extern uint16 OS_INTC_EIC554; /*lint -esym(752,OS_INTC_EIC554) allow to be unreferenced */
  extern uint16 OS_INTC_EIC555; /*lint -esym(752,OS_INTC_EIC555) allow to be unreferenced */
  extern uint16 OS_INTC_EIC556; /*lint -esym(752,OS_INTC_EIC556) allow to be unreferenced */
  extern uint16 OS_INTC_EIC557; /*lint -esym(752,OS_INTC_EIC557) allow to be unreferenced */
  extern uint16 OS_INTC_EIC558; /*lint -esym(752,OS_INTC_EIC558) allow to be unreferenced */
  extern uint16 OS_INTC_EIC559; /*lint -esym(752,OS_INTC_EIC559) allow to be unreferenced */
  extern uint16 OS_INTC_EIC560; /*lint -esym(752,OS_INTC_EIC560) allow to be unreferenced */
  extern uint16 OS_INTC_EIC561; /*lint -esym(752,OS_INTC_EIC561) allow to be unreferenced */
  extern uint16 OS_INTC_EIC562; /*lint -esym(752,OS_INTC_EIC562) allow to be unreferenced */
  extern uint16 OS_INTC_EIC563; /*lint -esym(752,OS_INTC_EIC563) allow to be unreferenced */
  extern uint16 OS_INTC_EIC564; /*lint -esym(752,OS_INTC_EIC564) allow to be unreferenced */
  extern uint16 OS_INTC_EIC565; /*lint -esym(752,OS_INTC_EIC565) allow to be unreferenced */
  extern uint16 OS_INTC_EIC566; /*lint -esym(752,OS_INTC_EIC566) allow to be unreferenced */
  extern uint16 OS_INTC_EIC567; /*lint -esym(752,OS_INTC_EIC567) allow to be unreferenced */
  extern uint16 OS_INTC_EIC568; /*lint -esym(752,OS_INTC_EIC568) allow to be unreferenced */
  extern uint16 OS_INTC_EIC569; /*lint -esym(752,OS_INTC_EIC569) allow to be unreferenced */
  extern uint16 OS_INTC_EIC570; /*lint -esym(752,OS_INTC_EIC570) allow to be unreferenced */
  extern uint16 OS_INTC_EIC571; /*lint -esym(752,OS_INTC_EIC571) allow to be unreferenced */
  extern uint16 OS_INTC_EIC572; /*lint -esym(752,OS_INTC_EIC572) allow to be unreferenced */
  extern uint16 OS_INTC_EIC573; /*lint -esym(752,OS_INTC_EIC573) allow to be unreferenced */
  extern uint16 OS_INTC_EIC574; /*lint -esym(752,OS_INTC_EIC574) allow to be unreferenced */
  extern uint16 OS_INTC_EIC575; /*lint -esym(752,OS_INTC_EIC575) allow to be unreferenced */
  extern uint16 OS_INTC_EIC576; /*lint -esym(752,OS_INTC_EIC576) allow to be unreferenced */
  extern uint16 OS_INTC_EIC577; /*lint -esym(752,OS_INTC_EIC577) allow to be unreferenced */
  extern uint16 OS_INTC_EIC578; /*lint -esym(752,OS_INTC_EIC578) allow to be unreferenced */
  extern uint16 OS_INTC_EIC579; /*lint -esym(752,OS_INTC_EIC579) allow to be unreferenced */
  extern uint16 OS_INTC_EIC580; /*lint -esym(752,OS_INTC_EIC580) allow to be unreferenced */
  extern uint16 OS_INTC_EIC581; /*lint -esym(752,OS_INTC_EIC581) allow to be unreferenced */
  extern uint16 OS_INTC_EIC582; /*lint -esym(752,OS_INTC_EIC582) allow to be unreferenced */
  extern uint16 OS_INTC_EIC583; /*lint -esym(752,OS_INTC_EIC583) allow to be unreferenced */
  extern uint16 OS_INTC_EIC584; /*lint -esym(752,OS_INTC_EIC584) allow to be unreferenced */
  extern uint16 OS_INTC_EIC585; /*lint -esym(752,OS_INTC_EIC585) allow to be unreferenced */
  extern uint16 OS_INTC_EIC586; /*lint -esym(752,OS_INTC_EIC586) allow to be unreferenced */
  extern uint16 OS_INTC_EIC587; /*lint -esym(752,OS_INTC_EIC587) allow to be unreferenced */
  extern uint16 OS_INTC_EIC588; /*lint -esym(752,OS_INTC_EIC588) allow to be unreferenced */
  extern uint16 OS_INTC_EIC589; /*lint -esym(752,OS_INTC_EIC589) allow to be unreferenced */
  extern uint16 OS_INTC_EIC590; /*lint -esym(752,OS_INTC_EIC590) allow to be unreferenced */
  extern uint16 OS_INTC_EIC591; /*lint -esym(752,OS_INTC_EIC591) allow to be unreferenced */
  extern uint16 OS_INTC_EIC592; /*lint -esym(752,OS_INTC_EIC592) allow to be unreferenced */
  extern uint16 OS_INTC_EIC593; /*lint -esym(752,OS_INTC_EIC593) allow to be unreferenced */
  extern uint16 OS_INTC_EIC594; /*lint -esym(752,OS_INTC_EIC594) allow to be unreferenced */
  extern uint16 OS_INTC_EIC595; /*lint -esym(752,OS_INTC_EIC595) allow to be unreferenced */
  extern uint16 OS_INTC_EIC596; /*lint -esym(752,OS_INTC_EIC596) allow to be unreferenced */
  extern uint16 OS_INTC_EIC597; /*lint -esym(752,OS_INTC_EIC597) allow to be unreferenced */
  extern uint16 OS_INTC_EIC598; /*lint -esym(752,OS_INTC_EIC598) allow to be unreferenced */
  extern uint16 OS_INTC_EIC599; /*lint -esym(752,OS_INTC_EIC599) allow to be unreferenced */
  extern uint16 OS_INTC_EIC600; /*lint -esym(752,OS_INTC_EIC600) allow to be unreferenced */
  extern uint16 OS_INTC_EIC601; /*lint -esym(752,OS_INTC_EIC601) allow to be unreferenced */
  extern uint16 OS_INTC_EIC602; /*lint -esym(752,OS_INTC_EIC602) allow to be unreferenced */
  extern uint16 OS_INTC_EIC603; /*lint -esym(752,OS_INTC_EIC603) allow to be unreferenced */
  extern uint16 OS_INTC_EIC604; /*lint -esym(752,OS_INTC_EIC604) allow to be unreferenced */
  extern uint16 OS_INTC_EIC605; /*lint -esym(752,OS_INTC_EIC605) allow to be unreferenced */
  extern uint16 OS_INTC_EIC606; /*lint -esym(752,OS_INTC_EIC606) allow to be unreferenced */
  extern uint16 OS_INTC_EIC607; /*lint -esym(752,OS_INTC_EIC607) allow to be unreferenced */
  extern uint16 OS_INTC_EIC608; /*lint -esym(752,OS_INTC_EIC608) allow to be unreferenced */
  extern uint16 OS_INTC_EIC609; /*lint -esym(752,OS_INTC_EIC609) allow to be unreferenced */
  extern uint16 OS_INTC_EIC610; /*lint -esym(752,OS_INTC_EIC610) allow to be unreferenced */
  extern uint16 OS_INTC_EIC611; /*lint -esym(752,OS_INTC_EIC611) allow to be unreferenced */
  extern uint16 OS_INTC_EIC612; /*lint -esym(752,OS_INTC_EIC612) allow to be unreferenced */
  extern uint16 OS_INTC_EIC613; /*lint -esym(752,OS_INTC_EIC613) allow to be unreferenced */
  extern uint16 OS_INTC_EIC614; /*lint -esym(752,OS_INTC_EIC614) allow to be unreferenced */
  extern uint16 OS_INTC_EIC615; /*lint -esym(752,OS_INTC_EIC615) allow to be unreferenced */
  extern uint16 OS_INTC_EIC616; /*lint -esym(752,OS_INTC_EIC616) allow to be unreferenced */
  extern uint16 OS_INTC_EIC617; /*lint -esym(752,OS_INTC_EIC617) allow to be unreferenced */
  extern uint16 OS_INTC_EIC618; /*lint -esym(752,OS_INTC_EIC618) allow to be unreferenced */
  extern uint16 OS_INTC_EIC619; /*lint -esym(752,OS_INTC_EIC619) allow to be unreferenced */
  extern uint16 OS_INTC_EIC620; /*lint -esym(752,OS_INTC_EIC620) allow to be unreferenced */
  extern uint16 OS_INTC_EIC621; /*lint -esym(752,OS_INTC_EIC621) allow to be unreferenced */
  extern uint16 OS_INTC_EIC622; /*lint -esym(752,OS_INTC_EIC622) allow to be unreferenced */
  extern uint16 OS_INTC_EIC623; /*lint -esym(752,OS_INTC_EIC623) allow to be unreferenced */
  extern uint16 OS_INTC_EIC624; /*lint -esym(752,OS_INTC_EIC624) allow to be unreferenced */
  extern uint16 OS_INTC_EIC625; /*lint -esym(752,OS_INTC_EIC625) allow to be unreferenced */
  extern uint16 OS_INTC_EIC626; /*lint -esym(752,OS_INTC_EIC626) allow to be unreferenced */
  extern uint16 OS_INTC_EIC627; /*lint -esym(752,OS_INTC_EIC627) allow to be unreferenced */
  extern uint16 OS_INTC_EIC628; /*lint -esym(752,OS_INTC_EIC628) allow to be unreferenced */
  extern uint16 OS_INTC_EIC629; /*lint -esym(752,OS_INTC_EIC629) allow to be unreferenced */
  extern uint16 OS_INTC_EIC630; /*lint -esym(752,OS_INTC_EIC630) allow to be unreferenced */
  extern uint16 OS_INTC_EIC631; /*lint -esym(752,OS_INTC_EIC631) allow to be unreferenced */
  extern uint16 OS_INTC_EIC632; /*lint -esym(752,OS_INTC_EIC632) allow to be unreferenced */
  extern uint16 OS_INTC_EIC633; /*lint -esym(752,OS_INTC_EIC633) allow to be unreferenced */
  extern uint16 OS_INTC_EIC634; /*lint -esym(752,OS_INTC_EIC634) allow to be unreferenced */
  extern uint16 OS_INTC_EIC635; /*lint -esym(752,OS_INTC_EIC635) allow to be unreferenced */
  extern uint16 OS_INTC_EIC636; /*lint -esym(752,OS_INTC_EIC636) allow to be unreferenced */
  extern uint16 OS_INTC_EIC637; /*lint -esym(752,OS_INTC_EIC637) allow to be unreferenced */
  extern uint16 OS_INTC_EIC638; /*lint -esym(752,OS_INTC_EIC638) allow to be unreferenced */
  extern uint16 OS_INTC_EIC639; /*lint -esym(752,OS_INTC_EIC639) allow to be unreferenced */
  extern uint16 OS_INTC_EIC640; /*lint -esym(752,OS_INTC_EIC640) allow to be unreferenced */
  extern uint16 OS_INTC_EIC641; /*lint -esym(752,OS_INTC_EIC641) allow to be unreferenced */
  extern uint16 OS_INTC_EIC642; /*lint -esym(752,OS_INTC_EIC642) allow to be unreferenced */
  extern uint16 OS_INTC_EIC643; /*lint -esym(752,OS_INTC_EIC643) allow to be unreferenced */
  extern uint16 OS_INTC_EIC644; /*lint -esym(752,OS_INTC_EIC644) allow to be unreferenced */
  extern uint16 OS_INTC_EIC645; /*lint -esym(752,OS_INTC_EIC645) allow to be unreferenced */
  extern uint16 OS_INTC_EIC646; /*lint -esym(752,OS_INTC_EIC646) allow to be unreferenced */
  extern uint16 OS_INTC_EIC647; /*lint -esym(752,OS_INTC_EIC647) allow to be unreferenced */
  extern uint16 OS_INTC_EIC648; /*lint -esym(752,OS_INTC_EIC648) allow to be unreferenced */
  extern uint16 OS_INTC_EIC649; /*lint -esym(752,OS_INTC_EIC649) allow to be unreferenced */
  extern uint16 OS_INTC_EIC650; /*lint -esym(752,OS_INTC_EIC650) allow to be unreferenced */
  extern uint16 OS_INTC_EIC651; /*lint -esym(752,OS_INTC_EIC651) allow to be unreferenced */
  extern uint16 OS_INTC_EIC652; /*lint -esym(752,OS_INTC_EIC652) allow to be unreferenced */
  extern uint16 OS_INTC_EIC653; /*lint -esym(752,OS_INTC_EIC653) allow to be unreferenced */
  extern uint16 OS_INTC_EIC654; /*lint -esym(752,OS_INTC_EIC654) allow to be unreferenced */
  extern uint16 OS_INTC_EIC655; /*lint -esym(752,OS_INTC_EIC655) allow to be unreferenced */
  extern uint16 OS_INTC_EIC656; /*lint -esym(752,OS_INTC_EIC656) allow to be unreferenced */
  extern uint16 OS_INTC_EIC657; /*lint -esym(752,OS_INTC_EIC657) allow to be unreferenced */
  extern uint16 OS_INTC_EIC658; /*lint -esym(752,OS_INTC_EIC658) allow to be unreferenced */
  extern uint16 OS_INTC_EIC659; /*lint -esym(752,OS_INTC_EIC659) allow to be unreferenced */
  extern uint16 OS_INTC_EIC660; /*lint -esym(752,OS_INTC_EIC660) allow to be unreferenced */
  extern uint16 OS_INTC_EIC661; /*lint -esym(752,OS_INTC_EIC661) allow to be unreferenced */
  extern uint16 OS_INTC_EIC662; /*lint -esym(752,OS_INTC_EIC662) allow to be unreferenced */
  extern uint16 OS_INTC_EIC663; /*lint -esym(752,OS_INTC_EIC663) allow to be unreferenced */
  extern uint16 OS_INTC_EIC664; /*lint -esym(752,OS_INTC_EIC664) allow to be unreferenced */
  extern uint16 OS_INTC_EIC665; /*lint -esym(752,OS_INTC_EIC665) allow to be unreferenced */
  extern uint16 OS_INTC_EIC666; /*lint -esym(752,OS_INTC_EIC666) allow to be unreferenced */
  extern uint16 OS_INTC_EIC667; /*lint -esym(752,OS_INTC_EIC667) allow to be unreferenced */
  extern uint16 OS_INTC_EIC668; /*lint -esym(752,OS_INTC_EIC668) allow to be unreferenced */
  extern uint16 OS_INTC_EIC669; /*lint -esym(752,OS_INTC_EIC669) allow to be unreferenced */
  extern uint16 OS_INTC_EIC670; /*lint -esym(752,OS_INTC_EIC670) allow to be unreferenced */
  extern uint16 OS_INTC_EIC671; /*lint -esym(752,OS_INTC_EIC671) allow to be unreferenced */
  extern uint16 OS_INTC_EIC672; /*lint -esym(752,OS_INTC_EIC672) allow to be unreferenced */
  extern uint16 OS_INTC_EIC673; /*lint -esym(752,OS_INTC_EIC673) allow to be unreferenced */
  extern uint16 OS_INTC_EIC674; /*lint -esym(752,OS_INTC_EIC674) allow to be unreferenced */
  extern uint16 OS_INTC_EIC675; /*lint -esym(752,OS_INTC_EIC675) allow to be unreferenced */
  extern uint16 OS_INTC_EIC676; /*lint -esym(752,OS_INTC_EIC676) allow to be unreferenced */
  extern uint16 OS_INTC_EIC677; /*lint -esym(752,OS_INTC_EIC677) allow to be unreferenced */
  extern uint16 OS_INTC_EIC678; /*lint -esym(752,OS_INTC_EIC678) allow to be unreferenced */
  extern uint16 OS_INTC_EIC679; /*lint -esym(752,OS_INTC_EIC679) allow to be unreferenced */
  extern uint16 OS_INTC_EIC680; /*lint -esym(752,OS_INTC_EIC680) allow to be unreferenced */
  extern uint16 OS_INTC_EIC681; /*lint -esym(752,OS_INTC_EIC681) allow to be unreferenced */
  extern uint16 OS_INTC_EIC682; /*lint -esym(752,OS_INTC_EIC682) allow to be unreferenced */
  extern uint16 OS_INTC_EIC683; /*lint -esym(752,OS_INTC_EIC683) allow to be unreferenced */
  extern uint16 OS_INTC_EIC684; /*lint -esym(752,OS_INTC_EIC684) allow to be unreferenced */
  extern uint16 OS_INTC_EIC685; /*lint -esym(752,OS_INTC_EIC685) allow to be unreferenced */
  extern uint16 OS_INTC_EIC686; /*lint -esym(752,OS_INTC_EIC686) allow to be unreferenced */
  extern uint16 OS_INTC_EIC687; /*lint -esym(752,OS_INTC_EIC687) allow to be unreferenced */
  extern uint16 OS_INTC_EIC688; /*lint -esym(752,OS_INTC_EIC688) allow to be unreferenced */
  extern uint16 OS_INTC_EIC689; /*lint -esym(752,OS_INTC_EIC689) allow to be unreferenced */
  extern uint16 OS_INTC_EIC690; /*lint -esym(752,OS_INTC_EIC690) allow to be unreferenced */
  extern uint16 OS_INTC_EIC691; /*lint -esym(752,OS_INTC_EIC691) allow to be unreferenced */
  extern uint16 OS_INTC_EIC692; /*lint -esym(752,OS_INTC_EIC692) allow to be unreferenced */
  extern uint16 OS_INTC_EIC693; /*lint -esym(752,OS_INTC_EIC693) allow to be unreferenced */
  extern uint16 OS_INTC_EIC694; /*lint -esym(752,OS_INTC_EIC694) allow to be unreferenced */
  extern uint16 OS_INTC_EIC695; /*lint -esym(752,OS_INTC_EIC695) allow to be unreferenced */
  extern uint16 OS_INTC_EIC696; /*lint -esym(752,OS_INTC_EIC696) allow to be unreferenced */
  extern uint16 OS_INTC_EIC697; /*lint -esym(752,OS_INTC_EIC697) allow to be unreferenced */
  extern uint16 OS_INTC_EIC698; /*lint -esym(752,OS_INTC_EIC698) allow to be unreferenced */
  extern uint16 OS_INTC_EIC699; /*lint -esym(752,OS_INTC_EIC699) allow to be unreferenced */
  extern uint16 OS_INTC_EIC700; /*lint -esym(752,OS_INTC_EIC700) allow to be unreferenced */
  extern uint16 OS_INTC_EIC701; /*lint -esym(752,OS_INTC_EIC701) allow to be unreferenced */
  extern uint16 OS_INTC_EIC702; /*lint -esym(752,OS_INTC_EIC702) allow to be unreferenced */
  extern uint16 OS_INTC_EIC703; /*lint -esym(752,OS_INTC_EIC703) allow to be unreferenced */
  extern uint16 OS_INTC_EIC704; /*lint -esym(752,OS_INTC_EIC704) allow to be unreferenced */
  extern uint16 OS_INTC_EIC705; /*lint -esym(752,OS_INTC_EIC705) allow to be unreferenced */
  extern uint16 OS_INTC_EIC706; /*lint -esym(752,OS_INTC_EIC706) allow to be unreferenced */
  extern uint16 OS_INTC_EIC707; /*lint -esym(752,OS_INTC_EIC707) allow to be unreferenced */
  extern uint16 OS_INTC_EIC708; /*lint -esym(752,OS_INTC_EIC708) allow to be unreferenced */
  extern uint16 OS_INTC_EIC709; /*lint -esym(752,OS_INTC_EIC709) allow to be unreferenced */
  extern uint16 OS_INTC_EIC710; /*lint -esym(752,OS_INTC_EIC710) allow to be unreferenced */
  extern uint16 OS_INTC_EIC711; /*lint -esym(752,OS_INTC_EIC711) allow to be unreferenced */
  extern uint16 OS_INTC_EIC712; /*lint -esym(752,OS_INTC_EIC712) allow to be unreferenced */
  extern uint16 OS_INTC_EIC713; /*lint -esym(752,OS_INTC_EIC713) allow to be unreferenced */
  extern uint16 OS_INTC_EIC714; /*lint -esym(752,OS_INTC_EIC714) allow to be unreferenced */
  extern uint16 OS_INTC_EIC715; /*lint -esym(752,OS_INTC_EIC715) allow to be unreferenced */
  extern uint16 OS_INTC_EIC716; /*lint -esym(752,OS_INTC_EIC716) allow to be unreferenced */
  extern uint16 OS_INTC_EIC717; /*lint -esym(752,OS_INTC_EIC717) allow to be unreferenced */
  extern uint16 OS_INTC_EIC718; /*lint -esym(752,OS_INTC_EIC718) allow to be unreferenced */
  extern uint16 OS_INTC_EIC719; /*lint -esym(752,OS_INTC_EIC719) allow to be unreferenced */
  extern uint16 OS_INTC_EIC720; /*lint -esym(752,OS_INTC_EIC720) allow to be unreferenced */
  extern uint16 OS_INTC_EIC721; /*lint -esym(752,OS_INTC_EIC721) allow to be unreferenced */
  extern uint16 OS_INTC_EIC722; /*lint -esym(752,OS_INTC_EIC722) allow to be unreferenced */
  extern uint16 OS_INTC_EIC723; /*lint -esym(752,OS_INTC_EIC723) allow to be unreferenced */
  extern uint16 OS_INTC_EIC724; /*lint -esym(752,OS_INTC_EIC724) allow to be unreferenced */
  extern uint16 OS_INTC_EIC725; /*lint -esym(752,OS_INTC_EIC725) allow to be unreferenced */
  extern uint16 OS_INTC_EIC726; /*lint -esym(752,OS_INTC_EIC726) allow to be unreferenced */
  extern uint16 OS_INTC_EIC727; /*lint -esym(752,OS_INTC_EIC727) allow to be unreferenced */
  extern uint16 OS_INTC_EIC728; /*lint -esym(752,OS_INTC_EIC728) allow to be unreferenced */
  extern uint16 OS_INTC_EIC729; /*lint -esym(752,OS_INTC_EIC729) allow to be unreferenced */
  extern uint16 OS_INTC_EIC730; /*lint -esym(752,OS_INTC_EIC730) allow to be unreferenced */
  extern uint16 OS_INTC_EIC731; /*lint -esym(752,OS_INTC_EIC731) allow to be unreferenced */
  extern uint16 OS_INTC_EIC732; /*lint -esym(752,OS_INTC_EIC732) allow to be unreferenced */
  extern uint16 OS_INTC_EIC733; /*lint -esym(752,OS_INTC_EIC733) allow to be unreferenced */
  extern uint16 OS_INTC_EIC734; /*lint -esym(752,OS_INTC_EIC734) allow to be unreferenced */
  extern uint16 OS_INTC_EIC735; /*lint -esym(752,OS_INTC_EIC735) allow to be unreferenced */
  extern uint16 OS_INTC_EIC736; /*lint -esym(752,OS_INTC_EIC736) allow to be unreferenced */
  extern uint16 OS_INTC_EIC737; /*lint -esym(752,OS_INTC_EIC737) allow to be unreferenced */
  extern uint16 OS_INTC_EIC738; /*lint -esym(752,OS_INTC_EIC738) allow to be unreferenced */
  extern uint16 OS_INTC_EIC739; /*lint -esym(752,OS_INTC_EIC739) allow to be unreferenced */
  extern uint16 OS_INTC_EIC740; /*lint -esym(752,OS_INTC_EIC740) allow to be unreferenced */
  extern uint16 OS_INTC_EIC741; /*lint -esym(752,OS_INTC_EIC741) allow to be unreferenced */
  extern uint16 OS_INTC_EIC742; /*lint -esym(752,OS_INTC_EIC742) allow to be unreferenced */
  extern uint16 OS_INTC_EIC743; /*lint -esym(752,OS_INTC_EIC743) allow to be unreferenced */
  extern uint16 OS_INTC_EIC744; /*lint -esym(752,OS_INTC_EIC744) allow to be unreferenced */
  extern uint16 OS_INTC_EIC745; /*lint -esym(752,OS_INTC_EIC745) allow to be unreferenced */
  extern uint16 OS_INTC_EIC746; /*lint -esym(752,OS_INTC_EIC746) allow to be unreferenced */
  extern uint16 OS_INTC_EIC747; /*lint -esym(752,OS_INTC_EIC747) allow to be unreferenced */
  extern uint16 OS_INTC_EIC748; /*lint -esym(752,OS_INTC_EIC748) allow to be unreferenced */
  extern uint16 OS_INTC_EIC749; /*lint -esym(752,OS_INTC_EIC749) allow to be unreferenced */
  extern uint16 OS_INTC_EIC750; /*lint -esym(752,OS_INTC_EIC750) allow to be unreferenced */
  extern uint16 OS_INTC_EIC751; /*lint -esym(752,OS_INTC_EIC751) allow to be unreferenced */
  extern uint16 OS_INTC_EIC752; /*lint -esym(752,OS_INTC_EIC752) allow to be unreferenced */
  extern uint16 OS_INTC_EIC753; /*lint -esym(752,OS_INTC_EIC753) allow to be unreferenced */
  extern uint16 OS_INTC_EIC754; /*lint -esym(752,OS_INTC_EIC754) allow to be unreferenced */
  extern uint16 OS_INTC_EIC755; /*lint -esym(752,OS_INTC_EIC755) allow to be unreferenced */
  extern uint16 OS_INTC_EIC756; /*lint -esym(752,OS_INTC_EIC756) allow to be unreferenced */
  extern uint16 OS_INTC_EIC757; /*lint -esym(752,OS_INTC_EIC757) allow to be unreferenced */
  extern uint16 OS_INTC_EIC758; /*lint -esym(752,OS_INTC_EIC758) allow to be unreferenced */
  extern uint16 OS_INTC_EIC759; /*lint -esym(752,OS_INTC_EIC759) allow to be unreferenced */
  extern uint16 OS_INTC_EIC760; /*lint -esym(752,OS_INTC_EIC760) allow to be unreferenced */
  extern uint16 OS_INTC_EIC761; /*lint -esym(752,OS_INTC_EIC761) allow to be unreferenced */
  extern uint16 OS_INTC_EIC762; /*lint -esym(752,OS_INTC_EIC762) allow to be unreferenced */
  extern uint16 OS_INTC_EIC763; /*lint -esym(752,OS_INTC_EIC763) allow to be unreferenced */
  extern uint16 OS_INTC_EIC764; /*lint -esym(752,OS_INTC_EIC764) allow to be unreferenced */
  extern uint16 OS_INTC_EIC765; /*lint -esym(752,OS_INTC_EIC765) allow to be unreferenced */
  extern uint16 OS_INTC_EIC766; /*lint -esym(752,OS_INTC_EIC766) allow to be unreferenced */
  extern uint16 OS_INTC_EIC767; /*lint -esym(752,OS_INTC_EIC767) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD0; /*lint -esym(752,OS_INTC_EIBD0) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD1; /*lint -esym(752,OS_INTC_EIBD1) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD2; /*lint -esym(752,OS_INTC_EIBD2) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD3; /*lint -esym(752,OS_INTC_EIBD3) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD4; /*lint -esym(752,OS_INTC_EIBD4) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD5; /*lint -esym(752,OS_INTC_EIBD5) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD6; /*lint -esym(752,OS_INTC_EIBD6) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD7; /*lint -esym(752,OS_INTC_EIBD7) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD8; /*lint -esym(752,OS_INTC_EIBD8) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD9; /*lint -esym(752,OS_INTC_EIBD9) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD10; /*lint -esym(752,OS_INTC_EIBD10) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD11; /*lint -esym(752,OS_INTC_EIBD11) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD12; /*lint -esym(752,OS_INTC_EIBD12) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD13; /*lint -esym(752,OS_INTC_EIBD13) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD14; /*lint -esym(752,OS_INTC_EIBD14) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD15; /*lint -esym(752,OS_INTC_EIBD15) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD16; /*lint -esym(752,OS_INTC_EIBD16) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD17; /*lint -esym(752,OS_INTC_EIBD17) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD18; /*lint -esym(752,OS_INTC_EIBD18) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD19; /*lint -esym(752,OS_INTC_EIBD19) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD20; /*lint -esym(752,OS_INTC_EIBD20) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD21; /*lint -esym(752,OS_INTC_EIBD21) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD22; /*lint -esym(752,OS_INTC_EIBD22) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD23; /*lint -esym(752,OS_INTC_EIBD23) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD24; /*lint -esym(752,OS_INTC_EIBD24) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD25; /*lint -esym(752,OS_INTC_EIBD25) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD26; /*lint -esym(752,OS_INTC_EIBD26) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD27; /*lint -esym(752,OS_INTC_EIBD27) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD28; /*lint -esym(752,OS_INTC_EIBD28) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD29; /*lint -esym(752,OS_INTC_EIBD29) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD30; /*lint -esym(752,OS_INTC_EIBD30) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD31; /*lint -esym(752,OS_INTC_EIBD31) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD32; /*lint -esym(752,OS_INTC_EIBD32) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD33; /*lint -esym(752,OS_INTC_EIBD33) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD34; /*lint -esym(752,OS_INTC_EIBD34) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD35; /*lint -esym(752,OS_INTC_EIBD35) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD36; /*lint -esym(752,OS_INTC_EIBD36) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD37; /*lint -esym(752,OS_INTC_EIBD37) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD38; /*lint -esym(752,OS_INTC_EIBD38) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD39; /*lint -esym(752,OS_INTC_EIBD39) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD40; /*lint -esym(752,OS_INTC_EIBD40) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD41; /*lint -esym(752,OS_INTC_EIBD41) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD42; /*lint -esym(752,OS_INTC_EIBD42) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD43; /*lint -esym(752,OS_INTC_EIBD43) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD44; /*lint -esym(752,OS_INTC_EIBD44) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD45; /*lint -esym(752,OS_INTC_EIBD45) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD46; /*lint -esym(752,OS_INTC_EIBD46) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD47; /*lint -esym(752,OS_INTC_EIBD47) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD48; /*lint -esym(752,OS_INTC_EIBD48) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD49; /*lint -esym(752,OS_INTC_EIBD49) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD50; /*lint -esym(752,OS_INTC_EIBD50) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD51; /*lint -esym(752,OS_INTC_EIBD51) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD52; /*lint -esym(752,OS_INTC_EIBD52) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD53; /*lint -esym(752,OS_INTC_EIBD53) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD54; /*lint -esym(752,OS_INTC_EIBD54) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD55; /*lint -esym(752,OS_INTC_EIBD55) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD56; /*lint -esym(752,OS_INTC_EIBD56) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD57; /*lint -esym(752,OS_INTC_EIBD57) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD58; /*lint -esym(752,OS_INTC_EIBD58) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD59; /*lint -esym(752,OS_INTC_EIBD59) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD60; /*lint -esym(752,OS_INTC_EIBD60) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD61; /*lint -esym(752,OS_INTC_EIBD61) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD62; /*lint -esym(752,OS_INTC_EIBD62) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD63; /*lint -esym(752,OS_INTC_EIBD63) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD64; /*lint -esym(752,OS_INTC_EIBD64) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD65; /*lint -esym(752,OS_INTC_EIBD65) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD66; /*lint -esym(752,OS_INTC_EIBD66) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD67; /*lint -esym(752,OS_INTC_EIBD67) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD68; /*lint -esym(752,OS_INTC_EIBD68) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD69; /*lint -esym(752,OS_INTC_EIBD69) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD70; /*lint -esym(752,OS_INTC_EIBD70) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD71; /*lint -esym(752,OS_INTC_EIBD71) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD72; /*lint -esym(752,OS_INTC_EIBD72) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD73; /*lint -esym(752,OS_INTC_EIBD73) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD74; /*lint -esym(752,OS_INTC_EIBD74) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD75; /*lint -esym(752,OS_INTC_EIBD75) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD76; /*lint -esym(752,OS_INTC_EIBD76) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD77; /*lint -esym(752,OS_INTC_EIBD77) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD78; /*lint -esym(752,OS_INTC_EIBD78) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD79; /*lint -esym(752,OS_INTC_EIBD79) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD80; /*lint -esym(752,OS_INTC_EIBD80) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD81; /*lint -esym(752,OS_INTC_EIBD81) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD82; /*lint -esym(752,OS_INTC_EIBD82) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD83; /*lint -esym(752,OS_INTC_EIBD83) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD84; /*lint -esym(752,OS_INTC_EIBD84) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD85; /*lint -esym(752,OS_INTC_EIBD85) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD86; /*lint -esym(752,OS_INTC_EIBD86) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD87; /*lint -esym(752,OS_INTC_EIBD87) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD88; /*lint -esym(752,OS_INTC_EIBD88) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD89; /*lint -esym(752,OS_INTC_EIBD89) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD90; /*lint -esym(752,OS_INTC_EIBD90) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD91; /*lint -esym(752,OS_INTC_EIBD91) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD92; /*lint -esym(752,OS_INTC_EIBD92) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD93; /*lint -esym(752,OS_INTC_EIBD93) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD94; /*lint -esym(752,OS_INTC_EIBD94) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD95; /*lint -esym(752,OS_INTC_EIBD95) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD96; /*lint -esym(752,OS_INTC_EIBD96) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD97; /*lint -esym(752,OS_INTC_EIBD97) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD98; /*lint -esym(752,OS_INTC_EIBD98) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD99; /*lint -esym(752,OS_INTC_EIBD99) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD100; /*lint -esym(752,OS_INTC_EIBD100) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD101; /*lint -esym(752,OS_INTC_EIBD101) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD102; /*lint -esym(752,OS_INTC_EIBD102) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD103; /*lint -esym(752,OS_INTC_EIBD103) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD104; /*lint -esym(752,OS_INTC_EIBD104) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD105; /*lint -esym(752,OS_INTC_EIBD105) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD106; /*lint -esym(752,OS_INTC_EIBD106) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD107; /*lint -esym(752,OS_INTC_EIBD107) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD108; /*lint -esym(752,OS_INTC_EIBD108) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD109; /*lint -esym(752,OS_INTC_EIBD109) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD110; /*lint -esym(752,OS_INTC_EIBD110) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD111; /*lint -esym(752,OS_INTC_EIBD111) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD112; /*lint -esym(752,OS_INTC_EIBD112) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD113; /*lint -esym(752,OS_INTC_EIBD113) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD114; /*lint -esym(752,OS_INTC_EIBD114) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD115; /*lint -esym(752,OS_INTC_EIBD115) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD116; /*lint -esym(752,OS_INTC_EIBD116) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD117; /*lint -esym(752,OS_INTC_EIBD117) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD118; /*lint -esym(752,OS_INTC_EIBD118) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD119; /*lint -esym(752,OS_INTC_EIBD119) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD120; /*lint -esym(752,OS_INTC_EIBD120) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD121; /*lint -esym(752,OS_INTC_EIBD121) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD122; /*lint -esym(752,OS_INTC_EIBD122) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD123; /*lint -esym(752,OS_INTC_EIBD123) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD124; /*lint -esym(752,OS_INTC_EIBD124) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD125; /*lint -esym(752,OS_INTC_EIBD125) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD126; /*lint -esym(752,OS_INTC_EIBD126) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD127; /*lint -esym(752,OS_INTC_EIBD127) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD128; /*lint -esym(752,OS_INTC_EIBD128) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD129; /*lint -esym(752,OS_INTC_EIBD129) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD130; /*lint -esym(752,OS_INTC_EIBD130) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD131; /*lint -esym(752,OS_INTC_EIBD131) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD132; /*lint -esym(752,OS_INTC_EIBD132) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD133; /*lint -esym(752,OS_INTC_EIBD133) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD134; /*lint -esym(752,OS_INTC_EIBD134) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD135; /*lint -esym(752,OS_INTC_EIBD135) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD136; /*lint -esym(752,OS_INTC_EIBD136) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD137; /*lint -esym(752,OS_INTC_EIBD137) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD138; /*lint -esym(752,OS_INTC_EIBD138) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD139; /*lint -esym(752,OS_INTC_EIBD139) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD140; /*lint -esym(752,OS_INTC_EIBD140) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD141; /*lint -esym(752,OS_INTC_EIBD141) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD142; /*lint -esym(752,OS_INTC_EIBD142) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD143; /*lint -esym(752,OS_INTC_EIBD143) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD144; /*lint -esym(752,OS_INTC_EIBD144) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD145; /*lint -esym(752,OS_INTC_EIBD145) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD146; /*lint -esym(752,OS_INTC_EIBD146) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD147; /*lint -esym(752,OS_INTC_EIBD147) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD148; /*lint -esym(752,OS_INTC_EIBD148) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD149; /*lint -esym(752,OS_INTC_EIBD149) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD150; /*lint -esym(752,OS_INTC_EIBD150) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD151; /*lint -esym(752,OS_INTC_EIBD151) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD152; /*lint -esym(752,OS_INTC_EIBD152) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD153; /*lint -esym(752,OS_INTC_EIBD153) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD154; /*lint -esym(752,OS_INTC_EIBD154) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD155; /*lint -esym(752,OS_INTC_EIBD155) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD156; /*lint -esym(752,OS_INTC_EIBD156) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD157; /*lint -esym(752,OS_INTC_EIBD157) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD158; /*lint -esym(752,OS_INTC_EIBD158) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD159; /*lint -esym(752,OS_INTC_EIBD159) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD160; /*lint -esym(752,OS_INTC_EIBD160) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD161; /*lint -esym(752,OS_INTC_EIBD161) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD162; /*lint -esym(752,OS_INTC_EIBD162) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD163; /*lint -esym(752,OS_INTC_EIBD163) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD164; /*lint -esym(752,OS_INTC_EIBD164) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD165; /*lint -esym(752,OS_INTC_EIBD165) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD166; /*lint -esym(752,OS_INTC_EIBD166) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD167; /*lint -esym(752,OS_INTC_EIBD167) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD168; /*lint -esym(752,OS_INTC_EIBD168) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD169; /*lint -esym(752,OS_INTC_EIBD169) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD170; /*lint -esym(752,OS_INTC_EIBD170) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD171; /*lint -esym(752,OS_INTC_EIBD171) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD172; /*lint -esym(752,OS_INTC_EIBD172) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD173; /*lint -esym(752,OS_INTC_EIBD173) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD174; /*lint -esym(752,OS_INTC_EIBD174) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD175; /*lint -esym(752,OS_INTC_EIBD175) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD176; /*lint -esym(752,OS_INTC_EIBD176) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD177; /*lint -esym(752,OS_INTC_EIBD177) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD178; /*lint -esym(752,OS_INTC_EIBD178) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD179; /*lint -esym(752,OS_INTC_EIBD179) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD180; /*lint -esym(752,OS_INTC_EIBD180) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD181; /*lint -esym(752,OS_INTC_EIBD181) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD182; /*lint -esym(752,OS_INTC_EIBD182) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD183; /*lint -esym(752,OS_INTC_EIBD183) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD184; /*lint -esym(752,OS_INTC_EIBD184) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD185; /*lint -esym(752,OS_INTC_EIBD185) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD186; /*lint -esym(752,OS_INTC_EIBD186) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD187; /*lint -esym(752,OS_INTC_EIBD187) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD188; /*lint -esym(752,OS_INTC_EIBD188) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD189; /*lint -esym(752,OS_INTC_EIBD189) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD190; /*lint -esym(752,OS_INTC_EIBD190) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD191; /*lint -esym(752,OS_INTC_EIBD191) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD192; /*lint -esym(752,OS_INTC_EIBD192) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD193; /*lint -esym(752,OS_INTC_EIBD193) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD194; /*lint -esym(752,OS_INTC_EIBD194) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD195; /*lint -esym(752,OS_INTC_EIBD195) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD196; /*lint -esym(752,OS_INTC_EIBD196) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD197; /*lint -esym(752,OS_INTC_EIBD197) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD198; /*lint -esym(752,OS_INTC_EIBD198) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD199; /*lint -esym(752,OS_INTC_EIBD199) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD200; /*lint -esym(752,OS_INTC_EIBD200) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD201; /*lint -esym(752,OS_INTC_EIBD201) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD202; /*lint -esym(752,OS_INTC_EIBD202) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD203; /*lint -esym(752,OS_INTC_EIBD203) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD204; /*lint -esym(752,OS_INTC_EIBD204) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD205; /*lint -esym(752,OS_INTC_EIBD205) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD206; /*lint -esym(752,OS_INTC_EIBD206) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD207; /*lint -esym(752,OS_INTC_EIBD207) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD208; /*lint -esym(752,OS_INTC_EIBD208) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD209; /*lint -esym(752,OS_INTC_EIBD209) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD210; /*lint -esym(752,OS_INTC_EIBD210) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD211; /*lint -esym(752,OS_INTC_EIBD211) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD212; /*lint -esym(752,OS_INTC_EIBD212) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD213; /*lint -esym(752,OS_INTC_EIBD213) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD214; /*lint -esym(752,OS_INTC_EIBD214) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD215; /*lint -esym(752,OS_INTC_EIBD215) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD216; /*lint -esym(752,OS_INTC_EIBD216) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD217; /*lint -esym(752,OS_INTC_EIBD217) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD218; /*lint -esym(752,OS_INTC_EIBD218) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD219; /*lint -esym(752,OS_INTC_EIBD219) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD220; /*lint -esym(752,OS_INTC_EIBD220) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD221; /*lint -esym(752,OS_INTC_EIBD221) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD222; /*lint -esym(752,OS_INTC_EIBD222) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD223; /*lint -esym(752,OS_INTC_EIBD223) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD224; /*lint -esym(752,OS_INTC_EIBD224) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD225; /*lint -esym(752,OS_INTC_EIBD225) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD226; /*lint -esym(752,OS_INTC_EIBD226) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD227; /*lint -esym(752,OS_INTC_EIBD227) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD228; /*lint -esym(752,OS_INTC_EIBD228) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD229; /*lint -esym(752,OS_INTC_EIBD229) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD230; /*lint -esym(752,OS_INTC_EIBD230) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD231; /*lint -esym(752,OS_INTC_EIBD231) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD232; /*lint -esym(752,OS_INTC_EIBD232) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD233; /*lint -esym(752,OS_INTC_EIBD233) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD234; /*lint -esym(752,OS_INTC_EIBD234) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD235; /*lint -esym(752,OS_INTC_EIBD235) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD236; /*lint -esym(752,OS_INTC_EIBD236) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD237; /*lint -esym(752,OS_INTC_EIBD237) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD238; /*lint -esym(752,OS_INTC_EIBD238) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD239; /*lint -esym(752,OS_INTC_EIBD239) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD240; /*lint -esym(752,OS_INTC_EIBD240) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD241; /*lint -esym(752,OS_INTC_EIBD241) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD242; /*lint -esym(752,OS_INTC_EIBD242) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD243; /*lint -esym(752,OS_INTC_EIBD243) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD244; /*lint -esym(752,OS_INTC_EIBD244) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD245; /*lint -esym(752,OS_INTC_EIBD245) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD246; /*lint -esym(752,OS_INTC_EIBD246) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD247; /*lint -esym(752,OS_INTC_EIBD247) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD248; /*lint -esym(752,OS_INTC_EIBD248) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD249; /*lint -esym(752,OS_INTC_EIBD249) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD250; /*lint -esym(752,OS_INTC_EIBD250) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD251; /*lint -esym(752,OS_INTC_EIBD251) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD252; /*lint -esym(752,OS_INTC_EIBD252) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD253; /*lint -esym(752,OS_INTC_EIBD253) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD254; /*lint -esym(752,OS_INTC_EIBD254) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD255; /*lint -esym(752,OS_INTC_EIBD255) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD256; /*lint -esym(752,OS_INTC_EIBD256) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD257; /*lint -esym(752,OS_INTC_EIBD257) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD258; /*lint -esym(752,OS_INTC_EIBD258) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD259; /*lint -esym(752,OS_INTC_EIBD259) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD260; /*lint -esym(752,OS_INTC_EIBD260) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD261; /*lint -esym(752,OS_INTC_EIBD261) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD262; /*lint -esym(752,OS_INTC_EIBD262) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD263; /*lint -esym(752,OS_INTC_EIBD263) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD264; /*lint -esym(752,OS_INTC_EIBD264) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD265; /*lint -esym(752,OS_INTC_EIBD265) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD266; /*lint -esym(752,OS_INTC_EIBD266) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD267; /*lint -esym(752,OS_INTC_EIBD267) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD268; /*lint -esym(752,OS_INTC_EIBD268) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD269; /*lint -esym(752,OS_INTC_EIBD269) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD270; /*lint -esym(752,OS_INTC_EIBD270) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD271; /*lint -esym(752,OS_INTC_EIBD271) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD272; /*lint -esym(752,OS_INTC_EIBD272) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD273; /*lint -esym(752,OS_INTC_EIBD273) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD274; /*lint -esym(752,OS_INTC_EIBD274) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD275; /*lint -esym(752,OS_INTC_EIBD275) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD276; /*lint -esym(752,OS_INTC_EIBD276) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD277; /*lint -esym(752,OS_INTC_EIBD277) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD278; /*lint -esym(752,OS_INTC_EIBD278) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD279; /*lint -esym(752,OS_INTC_EIBD279) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD280; /*lint -esym(752,OS_INTC_EIBD280) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD281; /*lint -esym(752,OS_INTC_EIBD281) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD282; /*lint -esym(752,OS_INTC_EIBD282) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD283; /*lint -esym(752,OS_INTC_EIBD283) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD284; /*lint -esym(752,OS_INTC_EIBD284) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD285; /*lint -esym(752,OS_INTC_EIBD285) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD286; /*lint -esym(752,OS_INTC_EIBD286) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD287; /*lint -esym(752,OS_INTC_EIBD287) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD288; /*lint -esym(752,OS_INTC_EIBD288) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD289; /*lint -esym(752,OS_INTC_EIBD289) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD290; /*lint -esym(752,OS_INTC_EIBD290) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD291; /*lint -esym(752,OS_INTC_EIBD291) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD292; /*lint -esym(752,OS_INTC_EIBD292) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD293; /*lint -esym(752,OS_INTC_EIBD293) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD294; /*lint -esym(752,OS_INTC_EIBD294) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD295; /*lint -esym(752,OS_INTC_EIBD295) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD296; /*lint -esym(752,OS_INTC_EIBD296) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD297; /*lint -esym(752,OS_INTC_EIBD297) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD298; /*lint -esym(752,OS_INTC_EIBD298) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD299; /*lint -esym(752,OS_INTC_EIBD299) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD300; /*lint -esym(752,OS_INTC_EIBD300) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD301; /*lint -esym(752,OS_INTC_EIBD301) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD302; /*lint -esym(752,OS_INTC_EIBD302) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD303; /*lint -esym(752,OS_INTC_EIBD303) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD304; /*lint -esym(752,OS_INTC_EIBD304) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD305; /*lint -esym(752,OS_INTC_EIBD305) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD306; /*lint -esym(752,OS_INTC_EIBD306) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD307; /*lint -esym(752,OS_INTC_EIBD307) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD308; /*lint -esym(752,OS_INTC_EIBD308) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD309; /*lint -esym(752,OS_INTC_EIBD309) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD310; /*lint -esym(752,OS_INTC_EIBD310) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD311; /*lint -esym(752,OS_INTC_EIBD311) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD312; /*lint -esym(752,OS_INTC_EIBD312) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD313; /*lint -esym(752,OS_INTC_EIBD313) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD314; /*lint -esym(752,OS_INTC_EIBD314) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD315; /*lint -esym(752,OS_INTC_EIBD315) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD316; /*lint -esym(752,OS_INTC_EIBD316) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD317; /*lint -esym(752,OS_INTC_EIBD317) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD318; /*lint -esym(752,OS_INTC_EIBD318) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD319; /*lint -esym(752,OS_INTC_EIBD319) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD320; /*lint -esym(752,OS_INTC_EIBD320) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD321; /*lint -esym(752,OS_INTC_EIBD321) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD322; /*lint -esym(752,OS_INTC_EIBD322) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD323; /*lint -esym(752,OS_INTC_EIBD323) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD324; /*lint -esym(752,OS_INTC_EIBD324) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD325; /*lint -esym(752,OS_INTC_EIBD325) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD326; /*lint -esym(752,OS_INTC_EIBD326) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD327; /*lint -esym(752,OS_INTC_EIBD327) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD328; /*lint -esym(752,OS_INTC_EIBD328) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD329; /*lint -esym(752,OS_INTC_EIBD329) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD330; /*lint -esym(752,OS_INTC_EIBD330) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD331; /*lint -esym(752,OS_INTC_EIBD331) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD332; /*lint -esym(752,OS_INTC_EIBD332) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD333; /*lint -esym(752,OS_INTC_EIBD333) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD334; /*lint -esym(752,OS_INTC_EIBD334) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD335; /*lint -esym(752,OS_INTC_EIBD335) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD336; /*lint -esym(752,OS_INTC_EIBD336) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD337; /*lint -esym(752,OS_INTC_EIBD337) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD338; /*lint -esym(752,OS_INTC_EIBD338) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD339; /*lint -esym(752,OS_INTC_EIBD339) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD340; /*lint -esym(752,OS_INTC_EIBD340) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD341; /*lint -esym(752,OS_INTC_EIBD341) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD342; /*lint -esym(752,OS_INTC_EIBD342) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD343; /*lint -esym(752,OS_INTC_EIBD343) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD344; /*lint -esym(752,OS_INTC_EIBD344) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD345; /*lint -esym(752,OS_INTC_EIBD345) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD346; /*lint -esym(752,OS_INTC_EIBD346) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD347; /*lint -esym(752,OS_INTC_EIBD347) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD348; /*lint -esym(752,OS_INTC_EIBD348) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD349; /*lint -esym(752,OS_INTC_EIBD349) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD350; /*lint -esym(752,OS_INTC_EIBD350) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD351; /*lint -esym(752,OS_INTC_EIBD351) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD352; /*lint -esym(752,OS_INTC_EIBD352) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD353; /*lint -esym(752,OS_INTC_EIBD353) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD354; /*lint -esym(752,OS_INTC_EIBD354) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD355; /*lint -esym(752,OS_INTC_EIBD355) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD356; /*lint -esym(752,OS_INTC_EIBD356) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD357; /*lint -esym(752,OS_INTC_EIBD357) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD358; /*lint -esym(752,OS_INTC_EIBD358) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD359; /*lint -esym(752,OS_INTC_EIBD359) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD360; /*lint -esym(752,OS_INTC_EIBD360) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD361; /*lint -esym(752,OS_INTC_EIBD361) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD362; /*lint -esym(752,OS_INTC_EIBD362) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD363; /*lint -esym(752,OS_INTC_EIBD363) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD364; /*lint -esym(752,OS_INTC_EIBD364) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD365; /*lint -esym(752,OS_INTC_EIBD365) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD366; /*lint -esym(752,OS_INTC_EIBD366) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD367; /*lint -esym(752,OS_INTC_EIBD367) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD368; /*lint -esym(752,OS_INTC_EIBD368) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD369; /*lint -esym(752,OS_INTC_EIBD369) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD370; /*lint -esym(752,OS_INTC_EIBD370) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD371; /*lint -esym(752,OS_INTC_EIBD371) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD372; /*lint -esym(752,OS_INTC_EIBD372) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD373; /*lint -esym(752,OS_INTC_EIBD373) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD374; /*lint -esym(752,OS_INTC_EIBD374) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD375; /*lint -esym(752,OS_INTC_EIBD375) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD376; /*lint -esym(752,OS_INTC_EIBD376) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD377; /*lint -esym(752,OS_INTC_EIBD377) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD378; /*lint -esym(752,OS_INTC_EIBD378) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD379; /*lint -esym(752,OS_INTC_EIBD379) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD380; /*lint -esym(752,OS_INTC_EIBD380) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD381; /*lint -esym(752,OS_INTC_EIBD381) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD382; /*lint -esym(752,OS_INTC_EIBD382) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD383; /*lint -esym(752,OS_INTC_EIBD383) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD384; /*lint -esym(752,OS_INTC_EIBD384) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD385; /*lint -esym(752,OS_INTC_EIBD385) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD386; /*lint -esym(752,OS_INTC_EIBD386) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD387; /*lint -esym(752,OS_INTC_EIBD387) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD388; /*lint -esym(752,OS_INTC_EIBD388) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD389; /*lint -esym(752,OS_INTC_EIBD389) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD390; /*lint -esym(752,OS_INTC_EIBD390) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD391; /*lint -esym(752,OS_INTC_EIBD391) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD392; /*lint -esym(752,OS_INTC_EIBD392) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD393; /*lint -esym(752,OS_INTC_EIBD393) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD394; /*lint -esym(752,OS_INTC_EIBD394) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD395; /*lint -esym(752,OS_INTC_EIBD395) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD396; /*lint -esym(752,OS_INTC_EIBD396) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD397; /*lint -esym(752,OS_INTC_EIBD397) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD398; /*lint -esym(752,OS_INTC_EIBD398) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD399; /*lint -esym(752,OS_INTC_EIBD399) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD400; /*lint -esym(752,OS_INTC_EIBD400) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD401; /*lint -esym(752,OS_INTC_EIBD401) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD402; /*lint -esym(752,OS_INTC_EIBD402) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD403; /*lint -esym(752,OS_INTC_EIBD403) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD404; /*lint -esym(752,OS_INTC_EIBD404) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD405; /*lint -esym(752,OS_INTC_EIBD405) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD406; /*lint -esym(752,OS_INTC_EIBD406) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD407; /*lint -esym(752,OS_INTC_EIBD407) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD408; /*lint -esym(752,OS_INTC_EIBD408) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD409; /*lint -esym(752,OS_INTC_EIBD409) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD410; /*lint -esym(752,OS_INTC_EIBD410) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD411; /*lint -esym(752,OS_INTC_EIBD411) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD412; /*lint -esym(752,OS_INTC_EIBD412) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD413; /*lint -esym(752,OS_INTC_EIBD413) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD414; /*lint -esym(752,OS_INTC_EIBD414) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD415; /*lint -esym(752,OS_INTC_EIBD415) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD416; /*lint -esym(752,OS_INTC_EIBD416) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD417; /*lint -esym(752,OS_INTC_EIBD417) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD418; /*lint -esym(752,OS_INTC_EIBD418) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD419; /*lint -esym(752,OS_INTC_EIBD419) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD420; /*lint -esym(752,OS_INTC_EIBD420) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD421; /*lint -esym(752,OS_INTC_EIBD421) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD422; /*lint -esym(752,OS_INTC_EIBD422) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD423; /*lint -esym(752,OS_INTC_EIBD423) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD424; /*lint -esym(752,OS_INTC_EIBD424) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD425; /*lint -esym(752,OS_INTC_EIBD425) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD426; /*lint -esym(752,OS_INTC_EIBD426) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD427; /*lint -esym(752,OS_INTC_EIBD427) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD428; /*lint -esym(752,OS_INTC_EIBD428) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD429; /*lint -esym(752,OS_INTC_EIBD429) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD430; /*lint -esym(752,OS_INTC_EIBD430) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD431; /*lint -esym(752,OS_INTC_EIBD431) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD432; /*lint -esym(752,OS_INTC_EIBD432) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD433; /*lint -esym(752,OS_INTC_EIBD433) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD434; /*lint -esym(752,OS_INTC_EIBD434) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD435; /*lint -esym(752,OS_INTC_EIBD435) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD436; /*lint -esym(752,OS_INTC_EIBD436) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD437; /*lint -esym(752,OS_INTC_EIBD437) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD438; /*lint -esym(752,OS_INTC_EIBD438) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD439; /*lint -esym(752,OS_INTC_EIBD439) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD440; /*lint -esym(752,OS_INTC_EIBD440) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD441; /*lint -esym(752,OS_INTC_EIBD441) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD442; /*lint -esym(752,OS_INTC_EIBD442) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD443; /*lint -esym(752,OS_INTC_EIBD443) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD444; /*lint -esym(752,OS_INTC_EIBD444) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD445; /*lint -esym(752,OS_INTC_EIBD445) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD446; /*lint -esym(752,OS_INTC_EIBD446) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD447; /*lint -esym(752,OS_INTC_EIBD447) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD448; /*lint -esym(752,OS_INTC_EIBD448) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD449; /*lint -esym(752,OS_INTC_EIBD449) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD450; /*lint -esym(752,OS_INTC_EIBD450) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD451; /*lint -esym(752,OS_INTC_EIBD451) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD452; /*lint -esym(752,OS_INTC_EIBD452) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD453; /*lint -esym(752,OS_INTC_EIBD453) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD454; /*lint -esym(752,OS_INTC_EIBD454) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD455; /*lint -esym(752,OS_INTC_EIBD455) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD456; /*lint -esym(752,OS_INTC_EIBD456) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD457; /*lint -esym(752,OS_INTC_EIBD457) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD458; /*lint -esym(752,OS_INTC_EIBD458) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD459; /*lint -esym(752,OS_INTC_EIBD459) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD460; /*lint -esym(752,OS_INTC_EIBD460) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD461; /*lint -esym(752,OS_INTC_EIBD461) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD462; /*lint -esym(752,OS_INTC_EIBD462) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD463; /*lint -esym(752,OS_INTC_EIBD463) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD464; /*lint -esym(752,OS_INTC_EIBD464) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD465; /*lint -esym(752,OS_INTC_EIBD465) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD466; /*lint -esym(752,OS_INTC_EIBD466) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD467; /*lint -esym(752,OS_INTC_EIBD467) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD468; /*lint -esym(752,OS_INTC_EIBD468) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD469; /*lint -esym(752,OS_INTC_EIBD469) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD470; /*lint -esym(752,OS_INTC_EIBD470) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD471; /*lint -esym(752,OS_INTC_EIBD471) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD472; /*lint -esym(752,OS_INTC_EIBD472) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD473; /*lint -esym(752,OS_INTC_EIBD473) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD474; /*lint -esym(752,OS_INTC_EIBD474) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD475; /*lint -esym(752,OS_INTC_EIBD475) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD476; /*lint -esym(752,OS_INTC_EIBD476) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD477; /*lint -esym(752,OS_INTC_EIBD477) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD478; /*lint -esym(752,OS_INTC_EIBD478) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD479; /*lint -esym(752,OS_INTC_EIBD479) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD480; /*lint -esym(752,OS_INTC_EIBD480) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD481; /*lint -esym(752,OS_INTC_EIBD481) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD482; /*lint -esym(752,OS_INTC_EIBD482) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD483; /*lint -esym(752,OS_INTC_EIBD483) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD484; /*lint -esym(752,OS_INTC_EIBD484) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD485; /*lint -esym(752,OS_INTC_EIBD485) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD486; /*lint -esym(752,OS_INTC_EIBD486) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD487; /*lint -esym(752,OS_INTC_EIBD487) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD488; /*lint -esym(752,OS_INTC_EIBD488) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD489; /*lint -esym(752,OS_INTC_EIBD489) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD490; /*lint -esym(752,OS_INTC_EIBD490) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD491; /*lint -esym(752,OS_INTC_EIBD491) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD492; /*lint -esym(752,OS_INTC_EIBD492) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD493; /*lint -esym(752,OS_INTC_EIBD493) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD494; /*lint -esym(752,OS_INTC_EIBD494) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD495; /*lint -esym(752,OS_INTC_EIBD495) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD496; /*lint -esym(752,OS_INTC_EIBD496) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD497; /*lint -esym(752,OS_INTC_EIBD497) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD498; /*lint -esym(752,OS_INTC_EIBD498) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD499; /*lint -esym(752,OS_INTC_EIBD499) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD500; /*lint -esym(752,OS_INTC_EIBD500) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD501; /*lint -esym(752,OS_INTC_EIBD501) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD502; /*lint -esym(752,OS_INTC_EIBD502) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD503; /*lint -esym(752,OS_INTC_EIBD503) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD504; /*lint -esym(752,OS_INTC_EIBD504) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD505; /*lint -esym(752,OS_INTC_EIBD505) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD506; /*lint -esym(752,OS_INTC_EIBD506) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD507; /*lint -esym(752,OS_INTC_EIBD507) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD508; /*lint -esym(752,OS_INTC_EIBD508) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD509; /*lint -esym(752,OS_INTC_EIBD509) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD510; /*lint -esym(752,OS_INTC_EIBD510) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD511; /*lint -esym(752,OS_INTC_EIBD511) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD512; /*lint -esym(752,OS_INTC_EIBD512) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD513; /*lint -esym(752,OS_INTC_EIBD513) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD514; /*lint -esym(752,OS_INTC_EIBD514) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD515; /*lint -esym(752,OS_INTC_EIBD515) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD516; /*lint -esym(752,OS_INTC_EIBD516) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD517; /*lint -esym(752,OS_INTC_EIBD517) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD518; /*lint -esym(752,OS_INTC_EIBD518) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD519; /*lint -esym(752,OS_INTC_EIBD519) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD520; /*lint -esym(752,OS_INTC_EIBD520) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD521; /*lint -esym(752,OS_INTC_EIBD521) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD522; /*lint -esym(752,OS_INTC_EIBD522) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD523; /*lint -esym(752,OS_INTC_EIBD523) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD524; /*lint -esym(752,OS_INTC_EIBD524) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD525; /*lint -esym(752,OS_INTC_EIBD525) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD526; /*lint -esym(752,OS_INTC_EIBD526) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD527; /*lint -esym(752,OS_INTC_EIBD527) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD528; /*lint -esym(752,OS_INTC_EIBD528) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD529; /*lint -esym(752,OS_INTC_EIBD529) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD530; /*lint -esym(752,OS_INTC_EIBD530) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD531; /*lint -esym(752,OS_INTC_EIBD531) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD532; /*lint -esym(752,OS_INTC_EIBD532) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD533; /*lint -esym(752,OS_INTC_EIBD533) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD534; /*lint -esym(752,OS_INTC_EIBD534) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD535; /*lint -esym(752,OS_INTC_EIBD535) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD536; /*lint -esym(752,OS_INTC_EIBD536) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD537; /*lint -esym(752,OS_INTC_EIBD537) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD538; /*lint -esym(752,OS_INTC_EIBD538) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD539; /*lint -esym(752,OS_INTC_EIBD539) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD540; /*lint -esym(752,OS_INTC_EIBD540) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD541; /*lint -esym(752,OS_INTC_EIBD541) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD542; /*lint -esym(752,OS_INTC_EIBD542) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD543; /*lint -esym(752,OS_INTC_EIBD543) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD544; /*lint -esym(752,OS_INTC_EIBD544) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD545; /*lint -esym(752,OS_INTC_EIBD545) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD546; /*lint -esym(752,OS_INTC_EIBD546) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD547; /*lint -esym(752,OS_INTC_EIBD547) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD548; /*lint -esym(752,OS_INTC_EIBD548) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD549; /*lint -esym(752,OS_INTC_EIBD549) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD550; /*lint -esym(752,OS_INTC_EIBD550) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD551; /*lint -esym(752,OS_INTC_EIBD551) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD552; /*lint -esym(752,OS_INTC_EIBD552) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD553; /*lint -esym(752,OS_INTC_EIBD553) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD554; /*lint -esym(752,OS_INTC_EIBD554) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD555; /*lint -esym(752,OS_INTC_EIBD555) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD556; /*lint -esym(752,OS_INTC_EIBD556) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD557; /*lint -esym(752,OS_INTC_EIBD557) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD558; /*lint -esym(752,OS_INTC_EIBD558) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD559; /*lint -esym(752,OS_INTC_EIBD559) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD560; /*lint -esym(752,OS_INTC_EIBD560) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD561; /*lint -esym(752,OS_INTC_EIBD561) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD562; /*lint -esym(752,OS_INTC_EIBD562) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD563; /*lint -esym(752,OS_INTC_EIBD563) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD564; /*lint -esym(752,OS_INTC_EIBD564) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD565; /*lint -esym(752,OS_INTC_EIBD565) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD566; /*lint -esym(752,OS_INTC_EIBD566) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD567; /*lint -esym(752,OS_INTC_EIBD567) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD568; /*lint -esym(752,OS_INTC_EIBD568) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD569; /*lint -esym(752,OS_INTC_EIBD569) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD570; /*lint -esym(752,OS_INTC_EIBD570) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD571; /*lint -esym(752,OS_INTC_EIBD571) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD572; /*lint -esym(752,OS_INTC_EIBD572) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD573; /*lint -esym(752,OS_INTC_EIBD573) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD574; /*lint -esym(752,OS_INTC_EIBD574) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD575; /*lint -esym(752,OS_INTC_EIBD575) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD576; /*lint -esym(752,OS_INTC_EIBD576) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD577; /*lint -esym(752,OS_INTC_EIBD577) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD578; /*lint -esym(752,OS_INTC_EIBD578) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD579; /*lint -esym(752,OS_INTC_EIBD579) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD580; /*lint -esym(752,OS_INTC_EIBD580) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD581; /*lint -esym(752,OS_INTC_EIBD581) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD582; /*lint -esym(752,OS_INTC_EIBD582) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD583; /*lint -esym(752,OS_INTC_EIBD583) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD584; /*lint -esym(752,OS_INTC_EIBD584) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD585; /*lint -esym(752,OS_INTC_EIBD585) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD586; /*lint -esym(752,OS_INTC_EIBD586) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD587; /*lint -esym(752,OS_INTC_EIBD587) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD588; /*lint -esym(752,OS_INTC_EIBD588) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD589; /*lint -esym(752,OS_INTC_EIBD589) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD590; /*lint -esym(752,OS_INTC_EIBD590) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD591; /*lint -esym(752,OS_INTC_EIBD591) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD592; /*lint -esym(752,OS_INTC_EIBD592) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD593; /*lint -esym(752,OS_INTC_EIBD593) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD594; /*lint -esym(752,OS_INTC_EIBD594) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD595; /*lint -esym(752,OS_INTC_EIBD595) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD596; /*lint -esym(752,OS_INTC_EIBD596) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD597; /*lint -esym(752,OS_INTC_EIBD597) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD598; /*lint -esym(752,OS_INTC_EIBD598) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD599; /*lint -esym(752,OS_INTC_EIBD599) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD600; /*lint -esym(752,OS_INTC_EIBD600) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD601; /*lint -esym(752,OS_INTC_EIBD601) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD602; /*lint -esym(752,OS_INTC_EIBD602) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD603; /*lint -esym(752,OS_INTC_EIBD603) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD604; /*lint -esym(752,OS_INTC_EIBD604) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD605; /*lint -esym(752,OS_INTC_EIBD605) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD606; /*lint -esym(752,OS_INTC_EIBD606) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD607; /*lint -esym(752,OS_INTC_EIBD607) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD608; /*lint -esym(752,OS_INTC_EIBD608) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD609; /*lint -esym(752,OS_INTC_EIBD609) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD610; /*lint -esym(752,OS_INTC_EIBD610) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD611; /*lint -esym(752,OS_INTC_EIBD611) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD612; /*lint -esym(752,OS_INTC_EIBD612) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD613; /*lint -esym(752,OS_INTC_EIBD613) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD614; /*lint -esym(752,OS_INTC_EIBD614) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD615; /*lint -esym(752,OS_INTC_EIBD615) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD616; /*lint -esym(752,OS_INTC_EIBD616) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD617; /*lint -esym(752,OS_INTC_EIBD617) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD618; /*lint -esym(752,OS_INTC_EIBD618) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD619; /*lint -esym(752,OS_INTC_EIBD619) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD620; /*lint -esym(752,OS_INTC_EIBD620) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD621; /*lint -esym(752,OS_INTC_EIBD621) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD622; /*lint -esym(752,OS_INTC_EIBD622) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD623; /*lint -esym(752,OS_INTC_EIBD623) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD624; /*lint -esym(752,OS_INTC_EIBD624) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD625; /*lint -esym(752,OS_INTC_EIBD625) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD626; /*lint -esym(752,OS_INTC_EIBD626) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD627; /*lint -esym(752,OS_INTC_EIBD627) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD628; /*lint -esym(752,OS_INTC_EIBD628) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD629; /*lint -esym(752,OS_INTC_EIBD629) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD630; /*lint -esym(752,OS_INTC_EIBD630) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD631; /*lint -esym(752,OS_INTC_EIBD631) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD632; /*lint -esym(752,OS_INTC_EIBD632) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD633; /*lint -esym(752,OS_INTC_EIBD633) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD634; /*lint -esym(752,OS_INTC_EIBD634) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD635; /*lint -esym(752,OS_INTC_EIBD635) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD636; /*lint -esym(752,OS_INTC_EIBD636) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD637; /*lint -esym(752,OS_INTC_EIBD637) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD638; /*lint -esym(752,OS_INTC_EIBD638) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD639; /*lint -esym(752,OS_INTC_EIBD639) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD640; /*lint -esym(752,OS_INTC_EIBD640) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD641; /*lint -esym(752,OS_INTC_EIBD641) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD642; /*lint -esym(752,OS_INTC_EIBD642) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD643; /*lint -esym(752,OS_INTC_EIBD643) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD644; /*lint -esym(752,OS_INTC_EIBD644) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD645; /*lint -esym(752,OS_INTC_EIBD645) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD646; /*lint -esym(752,OS_INTC_EIBD646) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD647; /*lint -esym(752,OS_INTC_EIBD647) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD648; /*lint -esym(752,OS_INTC_EIBD648) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD649; /*lint -esym(752,OS_INTC_EIBD649) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD650; /*lint -esym(752,OS_INTC_EIBD650) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD651; /*lint -esym(752,OS_INTC_EIBD651) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD652; /*lint -esym(752,OS_INTC_EIBD652) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD653; /*lint -esym(752,OS_INTC_EIBD653) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD654; /*lint -esym(752,OS_INTC_EIBD654) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD655; /*lint -esym(752,OS_INTC_EIBD655) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD656; /*lint -esym(752,OS_INTC_EIBD656) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD657; /*lint -esym(752,OS_INTC_EIBD657) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD658; /*lint -esym(752,OS_INTC_EIBD658) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD659; /*lint -esym(752,OS_INTC_EIBD659) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD660; /*lint -esym(752,OS_INTC_EIBD660) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD661; /*lint -esym(752,OS_INTC_EIBD661) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD662; /*lint -esym(752,OS_INTC_EIBD662) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD663; /*lint -esym(752,OS_INTC_EIBD663) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD664; /*lint -esym(752,OS_INTC_EIBD664) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD665; /*lint -esym(752,OS_INTC_EIBD665) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD666; /*lint -esym(752,OS_INTC_EIBD666) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD667; /*lint -esym(752,OS_INTC_EIBD667) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD668; /*lint -esym(752,OS_INTC_EIBD668) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD669; /*lint -esym(752,OS_INTC_EIBD669) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD670; /*lint -esym(752,OS_INTC_EIBD670) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD671; /*lint -esym(752,OS_INTC_EIBD671) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD672; /*lint -esym(752,OS_INTC_EIBD672) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD673; /*lint -esym(752,OS_INTC_EIBD673) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD674; /*lint -esym(752,OS_INTC_EIBD674) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD675; /*lint -esym(752,OS_INTC_EIBD675) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD676; /*lint -esym(752,OS_INTC_EIBD676) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD677; /*lint -esym(752,OS_INTC_EIBD677) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD678; /*lint -esym(752,OS_INTC_EIBD678) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD679; /*lint -esym(752,OS_INTC_EIBD679) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD680; /*lint -esym(752,OS_INTC_EIBD680) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD681; /*lint -esym(752,OS_INTC_EIBD681) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD682; /*lint -esym(752,OS_INTC_EIBD682) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD683; /*lint -esym(752,OS_INTC_EIBD683) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD684; /*lint -esym(752,OS_INTC_EIBD684) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD685; /*lint -esym(752,OS_INTC_EIBD685) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD686; /*lint -esym(752,OS_INTC_EIBD686) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD687; /*lint -esym(752,OS_INTC_EIBD687) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD688; /*lint -esym(752,OS_INTC_EIBD688) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD689; /*lint -esym(752,OS_INTC_EIBD689) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD690; /*lint -esym(752,OS_INTC_EIBD690) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD691; /*lint -esym(752,OS_INTC_EIBD691) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD692; /*lint -esym(752,OS_INTC_EIBD692) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD693; /*lint -esym(752,OS_INTC_EIBD693) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD694; /*lint -esym(752,OS_INTC_EIBD694) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD695; /*lint -esym(752,OS_INTC_EIBD695) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD696; /*lint -esym(752,OS_INTC_EIBD696) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD697; /*lint -esym(752,OS_INTC_EIBD697) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD698; /*lint -esym(752,OS_INTC_EIBD698) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD699; /*lint -esym(752,OS_INTC_EIBD699) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD700; /*lint -esym(752,OS_INTC_EIBD700) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD701; /*lint -esym(752,OS_INTC_EIBD701) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD702; /*lint -esym(752,OS_INTC_EIBD702) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD703; /*lint -esym(752,OS_INTC_EIBD703) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD704; /*lint -esym(752,OS_INTC_EIBD704) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD705; /*lint -esym(752,OS_INTC_EIBD705) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD706; /*lint -esym(752,OS_INTC_EIBD706) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD707; /*lint -esym(752,OS_INTC_EIBD707) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD708; /*lint -esym(752,OS_INTC_EIBD708) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD709; /*lint -esym(752,OS_INTC_EIBD709) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD710; /*lint -esym(752,OS_INTC_EIBD710) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD711; /*lint -esym(752,OS_INTC_EIBD711) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD712; /*lint -esym(752,OS_INTC_EIBD712) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD713; /*lint -esym(752,OS_INTC_EIBD713) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD714; /*lint -esym(752,OS_INTC_EIBD714) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD715; /*lint -esym(752,OS_INTC_EIBD715) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD716; /*lint -esym(752,OS_INTC_EIBD716) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD717; /*lint -esym(752,OS_INTC_EIBD717) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD718; /*lint -esym(752,OS_INTC_EIBD718) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD719; /*lint -esym(752,OS_INTC_EIBD719) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD720; /*lint -esym(752,OS_INTC_EIBD720) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD721; /*lint -esym(752,OS_INTC_EIBD721) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD722; /*lint -esym(752,OS_INTC_EIBD722) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD723; /*lint -esym(752,OS_INTC_EIBD723) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD724; /*lint -esym(752,OS_INTC_EIBD724) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD725; /*lint -esym(752,OS_INTC_EIBD725) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD726; /*lint -esym(752,OS_INTC_EIBD726) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD727; /*lint -esym(752,OS_INTC_EIBD727) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD728; /*lint -esym(752,OS_INTC_EIBD728) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD729; /*lint -esym(752,OS_INTC_EIBD729) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD730; /*lint -esym(752,OS_INTC_EIBD730) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD731; /*lint -esym(752,OS_INTC_EIBD731) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD732; /*lint -esym(752,OS_INTC_EIBD732) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD733; /*lint -esym(752,OS_INTC_EIBD733) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD734; /*lint -esym(752,OS_INTC_EIBD734) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD735; /*lint -esym(752,OS_INTC_EIBD735) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD736; /*lint -esym(752,OS_INTC_EIBD736) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD737; /*lint -esym(752,OS_INTC_EIBD737) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD738; /*lint -esym(752,OS_INTC_EIBD738) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD739; /*lint -esym(752,OS_INTC_EIBD739) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD740; /*lint -esym(752,OS_INTC_EIBD740) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD741; /*lint -esym(752,OS_INTC_EIBD741) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD742; /*lint -esym(752,OS_INTC_EIBD742) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD743; /*lint -esym(752,OS_INTC_EIBD743) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD744; /*lint -esym(752,OS_INTC_EIBD744) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD745; /*lint -esym(752,OS_INTC_EIBD745) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD746; /*lint -esym(752,OS_INTC_EIBD746) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD747; /*lint -esym(752,OS_INTC_EIBD747) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD748; /*lint -esym(752,OS_INTC_EIBD748) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD749; /*lint -esym(752,OS_INTC_EIBD749) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD750; /*lint -esym(752,OS_INTC_EIBD750) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD751; /*lint -esym(752,OS_INTC_EIBD751) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD752; /*lint -esym(752,OS_INTC_EIBD752) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD753; /*lint -esym(752,OS_INTC_EIBD753) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD754; /*lint -esym(752,OS_INTC_EIBD754) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD755; /*lint -esym(752,OS_INTC_EIBD755) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD756; /*lint -esym(752,OS_INTC_EIBD756) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD757; /*lint -esym(752,OS_INTC_EIBD757) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD758; /*lint -esym(752,OS_INTC_EIBD758) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD759; /*lint -esym(752,OS_INTC_EIBD759) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD760; /*lint -esym(752,OS_INTC_EIBD760) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD761; /*lint -esym(752,OS_INTC_EIBD761) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD762; /*lint -esym(752,OS_INTC_EIBD762) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD763; /*lint -esym(752,OS_INTC_EIBD763) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD764; /*lint -esym(752,OS_INTC_EIBD764) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD765; /*lint -esym(752,OS_INTC_EIBD765) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD766; /*lint -esym(752,OS_INTC_EIBD766) allow to be unreferenced */
  extern uint32 OS_INTC_EIBD767; /*lint -esym(752,OS_INTC_EIBD767) allow to be unreferenced */
#else
  #define OS_INTC_EIC0 (*(OS_VOLATILE uint16 *)(0xFFFC0000U))
  #define OS_INTC_EIC1 (*(OS_VOLATILE uint16 *)(0xFFFC0002U))
  #define OS_INTC_EIC2 (*(OS_VOLATILE uint16 *)(0xFFFC0004U))
  #define OS_INTC_EIC3 (*(OS_VOLATILE uint16 *)(0xFFFC0006U))
  #define OS_INTC_EIC4 (*(OS_VOLATILE uint16 *)(0xFFFC0008U))
  #define OS_INTC_EIC5 (*(OS_VOLATILE uint16 *)(0xFFFC000AU))
  #define OS_INTC_EIC6 (*(OS_VOLATILE uint16 *)(0xFFFC000CU))
  #define OS_INTC_EIC7 (*(OS_VOLATILE uint16 *)(0xFFFC000EU))
  #define OS_INTC_EIC8 (*(OS_VOLATILE uint16 *)(0xFFFC0010U))
  #define OS_INTC_EIC9 (*(OS_VOLATILE uint16 *)(0xFFFC0012U))
  #define OS_INTC_EIC10 (*(OS_VOLATILE uint16 *)(0xFFFC0014U))
  #define OS_INTC_EIC11 (*(OS_VOLATILE uint16 *)(0xFFFC0016U))
  #define OS_INTC_EIC12 (*(OS_VOLATILE uint16 *)(0xFFFC0018U))
  #define OS_INTC_EIC13 (*(OS_VOLATILE uint16 *)(0xFFFC001AU))
  #define OS_INTC_EIC14 (*(OS_VOLATILE uint16 *)(0xFFFC001CU))
  #define OS_INTC_EIC15 (*(OS_VOLATILE uint16 *)(0xFFFC001EU))
  #define OS_INTC_EIC16 (*(OS_VOLATILE uint16 *)(0xFFFC0020U))
  #define OS_INTC_EIC17 (*(OS_VOLATILE uint16 *)(0xFFFC0022U))
  #define OS_INTC_EIC18 (*(OS_VOLATILE uint16 *)(0xFFFC0024U))
  #define OS_INTC_EIC19 (*(OS_VOLATILE uint16 *)(0xFFFC0026U))
  #define OS_INTC_EIC20 (*(OS_VOLATILE uint16 *)(0xFFFC0028U))
  #define OS_INTC_EIC21 (*(OS_VOLATILE uint16 *)(0xFFFC002AU))
  #define OS_INTC_EIC22 (*(OS_VOLATILE uint16 *)(0xFFFC002CU))
  #define OS_INTC_EIC23 (*(OS_VOLATILE uint16 *)(0xFFFC002EU))
  #define OS_INTC_EIC24 (*(OS_VOLATILE uint16 *)(0xFFFC0030U))
  #define OS_INTC_EIC25 (*(OS_VOLATILE uint16 *)(0xFFFC0032U))
  #define OS_INTC_EIC26 (*(OS_VOLATILE uint16 *)(0xFFFC0034U))
  #define OS_INTC_EIC27 (*(OS_VOLATILE uint16 *)(0xFFFC0036U))
  #define OS_INTC_EIC28 (*(OS_VOLATILE uint16 *)(0xFFFC0038U))
  #define OS_INTC_EIC29 (*(OS_VOLATILE uint16 *)(0xFFFC003AU))
  #define OS_INTC_EIC30 (*(OS_VOLATILE uint16 *)(0xFFFC003CU))
  #define OS_INTC_EIC31 (*(OS_VOLATILE uint16 *)(0xFFFC003EU))
  #define OS_INTC_EIC32 (*(OS_VOLATILE uint16 *)(0xFFF80040U))
  #define OS_INTC_EIC33 (*(OS_VOLATILE uint16 *)(0xFFF80042U))
  #define OS_INTC_EIC34 (*(OS_VOLATILE uint16 *)(0xFFF80044U))
  #define OS_INTC_EIC35 (*(OS_VOLATILE uint16 *)(0xFFF80046U))
  #define OS_INTC_EIC36 (*(OS_VOLATILE uint16 *)(0xFFF80048U))
  #define OS_INTC_EIC37 (*(OS_VOLATILE uint16 *)(0xFFF8004AU))
  #define OS_INTC_EIC38 (*(OS_VOLATILE uint16 *)(0xFFF8004CU))
  #define OS_INTC_EIC39 (*(OS_VOLATILE uint16 *)(0xFFF8004EU))
  #define OS_INTC_EIC40 (*(OS_VOLATILE uint16 *)(0xFFF80050U))
  #define OS_INTC_EIC41 (*(OS_VOLATILE uint16 *)(0xFFF80052U))
  #define OS_INTC_EIC42 (*(OS_VOLATILE uint16 *)(0xFFF80054U))
  #define OS_INTC_EIC43 (*(OS_VOLATILE uint16 *)(0xFFF80056U))
  #define OS_INTC_EIC44 (*(OS_VOLATILE uint16 *)(0xFFF80058U))
  #define OS_INTC_EIC45 (*(OS_VOLATILE uint16 *)(0xFFF8005AU))
  #define OS_INTC_EIC46 (*(OS_VOLATILE uint16 *)(0xFFF8005CU))
  #define OS_INTC_EIC47 (*(OS_VOLATILE uint16 *)(0xFFF8005EU))
  #define OS_INTC_EIC48 (*(OS_VOLATILE uint16 *)(0xFFF80060U))
  #define OS_INTC_EIC49 (*(OS_VOLATILE uint16 *)(0xFFF80062U))
  #define OS_INTC_EIC50 (*(OS_VOLATILE uint16 *)(0xFFF80064U))
  #define OS_INTC_EIC51 (*(OS_VOLATILE uint16 *)(0xFFF80066U))
  #define OS_INTC_EIC52 (*(OS_VOLATILE uint16 *)(0xFFF80068U))
  #define OS_INTC_EIC53 (*(OS_VOLATILE uint16 *)(0xFFF8006AU))
  #define OS_INTC_EIC54 (*(OS_VOLATILE uint16 *)(0xFFF8006CU))
  #define OS_INTC_EIC55 (*(OS_VOLATILE uint16 *)(0xFFF8006EU))
  #define OS_INTC_EIC56 (*(OS_VOLATILE uint16 *)(0xFFF80070U))
  #define OS_INTC_EIC57 (*(OS_VOLATILE uint16 *)(0xFFF80072U))
  #define OS_INTC_EIC58 (*(OS_VOLATILE uint16 *)(0xFFF80074U))
  #define OS_INTC_EIC59 (*(OS_VOLATILE uint16 *)(0xFFF80076U))
  #define OS_INTC_EIC60 (*(OS_VOLATILE uint16 *)(0xFFF80078U))
  #define OS_INTC_EIC61 (*(OS_VOLATILE uint16 *)(0xFFF8007AU))
  #define OS_INTC_EIC62 (*(OS_VOLATILE uint16 *)(0xFFF8007CU))
  #define OS_INTC_EIC63 (*(OS_VOLATILE uint16 *)(0xFFF8007EU))
  #define OS_INTC_EIC64 (*(OS_VOLATILE uint16 *)(0xFFF80080U))
  #define OS_INTC_EIC65 (*(OS_VOLATILE uint16 *)(0xFFF80082U))
  #define OS_INTC_EIC66 (*(OS_VOLATILE uint16 *)(0xFFF80084U))
  #define OS_INTC_EIC67 (*(OS_VOLATILE uint16 *)(0xFFF80086U))
  #define OS_INTC_EIC68 (*(OS_VOLATILE uint16 *)(0xFFF80088U))
  #define OS_INTC_EIC69 (*(OS_VOLATILE uint16 *)(0xFFF8008AU))
  #define OS_INTC_EIC70 (*(OS_VOLATILE uint16 *)(0xFFF8008CU))
  #define OS_INTC_EIC71 (*(OS_VOLATILE uint16 *)(0xFFF8008EU))
  #define OS_INTC_EIC72 (*(OS_VOLATILE uint16 *)(0xFFF80090U))
  #define OS_INTC_EIC73 (*(OS_VOLATILE uint16 *)(0xFFF80092U))
  #define OS_INTC_EIC74 (*(OS_VOLATILE uint16 *)(0xFFF80094U))
  #define OS_INTC_EIC75 (*(OS_VOLATILE uint16 *)(0xFFF80096U))
  #define OS_INTC_EIC76 (*(OS_VOLATILE uint16 *)(0xFFF80098U))
  #define OS_INTC_EIC77 (*(OS_VOLATILE uint16 *)(0xFFF8009AU))
  #define OS_INTC_EIC78 (*(OS_VOLATILE uint16 *)(0xFFF8009CU))
  #define OS_INTC_EIC79 (*(OS_VOLATILE uint16 *)(0xFFF8009EU))
  #define OS_INTC_EIC80 (*(OS_VOLATILE uint16 *)(0xFFF800A0U))
  #define OS_INTC_EIC81 (*(OS_VOLATILE uint16 *)(0xFFF800A2U))
  #define OS_INTC_EIC82 (*(OS_VOLATILE uint16 *)(0xFFF800A4U))
  #define OS_INTC_EIC83 (*(OS_VOLATILE uint16 *)(0xFFF800A6U))
  #define OS_INTC_EIC84 (*(OS_VOLATILE uint16 *)(0xFFF800A8U))
  #define OS_INTC_EIC85 (*(OS_VOLATILE uint16 *)(0xFFF800AAU))
  #define OS_INTC_EIC86 (*(OS_VOLATILE uint16 *)(0xFFF800ACU))
  #define OS_INTC_EIC87 (*(OS_VOLATILE uint16 *)(0xFFF800AEU))
  #define OS_INTC_EIC88 (*(OS_VOLATILE uint16 *)(0xFFF800B0U))
  #define OS_INTC_EIC89 (*(OS_VOLATILE uint16 *)(0xFFF800B2U))
  #define OS_INTC_EIC90 (*(OS_VOLATILE uint16 *)(0xFFF800B4U))
  #define OS_INTC_EIC91 (*(OS_VOLATILE uint16 *)(0xFFF800B6U))
  #define OS_INTC_EIC92 (*(OS_VOLATILE uint16 *)(0xFFF800B8U))
  #define OS_INTC_EIC93 (*(OS_VOLATILE uint16 *)(0xFFF800BAU))
  #define OS_INTC_EIC94 (*(OS_VOLATILE uint16 *)(0xFFF800BCU))
  #define OS_INTC_EIC95 (*(OS_VOLATILE uint16 *)(0xFFF800BEU))
  #define OS_INTC_EIC96 (*(OS_VOLATILE uint16 *)(0xFFF800C0U))
  #define OS_INTC_EIC97 (*(OS_VOLATILE uint16 *)(0xFFF800C2U))
  #define OS_INTC_EIC98 (*(OS_VOLATILE uint16 *)(0xFFF800C4U))
  #define OS_INTC_EIC99 (*(OS_VOLATILE uint16 *)(0xFFF800C6U))
  #define OS_INTC_EIC100 (*(OS_VOLATILE uint16 *)(0xFFF800C8U))
  #define OS_INTC_EIC101 (*(OS_VOLATILE uint16 *)(0xFFF800CAU))
  #define OS_INTC_EIC102 (*(OS_VOLATILE uint16 *)(0xFFF800CCU))
  #define OS_INTC_EIC103 (*(OS_VOLATILE uint16 *)(0xFFF800CEU))
  #define OS_INTC_EIC104 (*(OS_VOLATILE uint16 *)(0xFFF800D0U))
  #define OS_INTC_EIC105 (*(OS_VOLATILE uint16 *)(0xFFF800D2U))
  #define OS_INTC_EIC106 (*(OS_VOLATILE uint16 *)(0xFFF800D4U))
  #define OS_INTC_EIC107 (*(OS_VOLATILE uint16 *)(0xFFF800D6U))
  #define OS_INTC_EIC108 (*(OS_VOLATILE uint16 *)(0xFFF800D8U))
  #define OS_INTC_EIC109 (*(OS_VOLATILE uint16 *)(0xFFF800DAU))
  #define OS_INTC_EIC110 (*(OS_VOLATILE uint16 *)(0xFFF800DCU))
  #define OS_INTC_EIC111 (*(OS_VOLATILE uint16 *)(0xFFF800DEU))
  #define OS_INTC_EIC112 (*(OS_VOLATILE uint16 *)(0xFFF800E0U))
  #define OS_INTC_EIC113 (*(OS_VOLATILE uint16 *)(0xFFF800E2U))
  #define OS_INTC_EIC114 (*(OS_VOLATILE uint16 *)(0xFFF800E4U))
  #define OS_INTC_EIC115 (*(OS_VOLATILE uint16 *)(0xFFF800E6U))
  #define OS_INTC_EIC116 (*(OS_VOLATILE uint16 *)(0xFFF800E8U))
  #define OS_INTC_EIC117 (*(OS_VOLATILE uint16 *)(0xFFF800EAU))
  #define OS_INTC_EIC118 (*(OS_VOLATILE uint16 *)(0xFFF800ECU))
  #define OS_INTC_EIC119 (*(OS_VOLATILE uint16 *)(0xFFF800EEU))
  #define OS_INTC_EIC120 (*(OS_VOLATILE uint16 *)(0xFFF800F0U))
  #define OS_INTC_EIC121 (*(OS_VOLATILE uint16 *)(0xFFF800F2U))
  #define OS_INTC_EIC122 (*(OS_VOLATILE uint16 *)(0xFFF800F4U))
  #define OS_INTC_EIC123 (*(OS_VOLATILE uint16 *)(0xFFF800F6U))
  #define OS_INTC_EIC124 (*(OS_VOLATILE uint16 *)(0xFFF800F8U))
  #define OS_INTC_EIC125 (*(OS_VOLATILE uint16 *)(0xFFF800FAU))
  #define OS_INTC_EIC126 (*(OS_VOLATILE uint16 *)(0xFFF800FCU))
  #define OS_INTC_EIC127 (*(OS_VOLATILE uint16 *)(0xFFF800FEU))
  #define OS_INTC_EIC128 (*(OS_VOLATILE uint16 *)(0xFFF80100U))
  #define OS_INTC_EIC129 (*(OS_VOLATILE uint16 *)(0xFFF80102U))
  #define OS_INTC_EIC130 (*(OS_VOLATILE uint16 *)(0xFFF80104U))
  #define OS_INTC_EIC131 (*(OS_VOLATILE uint16 *)(0xFFF80106U))
  #define OS_INTC_EIC132 (*(OS_VOLATILE uint16 *)(0xFFF80108U))
  #define OS_INTC_EIC133 (*(OS_VOLATILE uint16 *)(0xFFF8010AU))
  #define OS_INTC_EIC134 (*(OS_VOLATILE uint16 *)(0xFFF8010CU))
  #define OS_INTC_EIC135 (*(OS_VOLATILE uint16 *)(0xFFF8010EU))
  #define OS_INTC_EIC136 (*(OS_VOLATILE uint16 *)(0xFFF80110U))
  #define OS_INTC_EIC137 (*(OS_VOLATILE uint16 *)(0xFFF80112U))
  #define OS_INTC_EIC138 (*(OS_VOLATILE uint16 *)(0xFFF80114U))
  #define OS_INTC_EIC139 (*(OS_VOLATILE uint16 *)(0xFFF80116U))
  #define OS_INTC_EIC140 (*(OS_VOLATILE uint16 *)(0xFFF80118U))
  #define OS_INTC_EIC141 (*(OS_VOLATILE uint16 *)(0xFFF8011AU))
  #define OS_INTC_EIC142 (*(OS_VOLATILE uint16 *)(0xFFF8011CU))
  #define OS_INTC_EIC143 (*(OS_VOLATILE uint16 *)(0xFFF8011EU))
  #define OS_INTC_EIC144 (*(OS_VOLATILE uint16 *)(0xFFF80120U))
  #define OS_INTC_EIC145 (*(OS_VOLATILE uint16 *)(0xFFF80122U))
  #define OS_INTC_EIC146 (*(OS_VOLATILE uint16 *)(0xFFF80124U))
  #define OS_INTC_EIC147 (*(OS_VOLATILE uint16 *)(0xFFF80126U))
  #define OS_INTC_EIC148 (*(OS_VOLATILE uint16 *)(0xFFF80128U))
  #define OS_INTC_EIC149 (*(OS_VOLATILE uint16 *)(0xFFF8012AU))
  #define OS_INTC_EIC150 (*(OS_VOLATILE uint16 *)(0xFFF8012CU))
  #define OS_INTC_EIC151 (*(OS_VOLATILE uint16 *)(0xFFF8012EU))
  #define OS_INTC_EIC152 (*(OS_VOLATILE uint16 *)(0xFFF80130U))
  #define OS_INTC_EIC153 (*(OS_VOLATILE uint16 *)(0xFFF80132U))
  #define OS_INTC_EIC154 (*(OS_VOLATILE uint16 *)(0xFFF80134U))
  #define OS_INTC_EIC155 (*(OS_VOLATILE uint16 *)(0xFFF80136U))
  #define OS_INTC_EIC156 (*(OS_VOLATILE uint16 *)(0xFFF80138U))
  #define OS_INTC_EIC157 (*(OS_VOLATILE uint16 *)(0xFFF8013AU))
  #define OS_INTC_EIC158 (*(OS_VOLATILE uint16 *)(0xFFF8013CU))
  #define OS_INTC_EIC159 (*(OS_VOLATILE uint16 *)(0xFFF8013EU))
  #define OS_INTC_EIC160 (*(OS_VOLATILE uint16 *)(0xFFF80140U))
  #define OS_INTC_EIC161 (*(OS_VOLATILE uint16 *)(0xFFF80142U))
  #define OS_INTC_EIC162 (*(OS_VOLATILE uint16 *)(0xFFF80144U))
  #define OS_INTC_EIC163 (*(OS_VOLATILE uint16 *)(0xFFF80146U))
  #define OS_INTC_EIC164 (*(OS_VOLATILE uint16 *)(0xFFF80148U))
  #define OS_INTC_EIC165 (*(OS_VOLATILE uint16 *)(0xFFF8014AU))
  #define OS_INTC_EIC166 (*(OS_VOLATILE uint16 *)(0xFFF8014CU))
  #define OS_INTC_EIC167 (*(OS_VOLATILE uint16 *)(0xFFF8014EU))
  #define OS_INTC_EIC168 (*(OS_VOLATILE uint16 *)(0xFFF80150U))
  #define OS_INTC_EIC169 (*(OS_VOLATILE uint16 *)(0xFFF80152U))
  #define OS_INTC_EIC170 (*(OS_VOLATILE uint16 *)(0xFFF80154U))
  #define OS_INTC_EIC171 (*(OS_VOLATILE uint16 *)(0xFFF80156U))
  #define OS_INTC_EIC172 (*(OS_VOLATILE uint16 *)(0xFFF80158U))
  #define OS_INTC_EIC173 (*(OS_VOLATILE uint16 *)(0xFFF8015AU))
  #define OS_INTC_EIC174 (*(OS_VOLATILE uint16 *)(0xFFF8015CU))
  #define OS_INTC_EIC175 (*(OS_VOLATILE uint16 *)(0xFFF8015EU))
  #define OS_INTC_EIC176 (*(OS_VOLATILE uint16 *)(0xFFF80160U))
  #define OS_INTC_EIC177 (*(OS_VOLATILE uint16 *)(0xFFF80162U))
  #define OS_INTC_EIC178 (*(OS_VOLATILE uint16 *)(0xFFF80164U))
  #define OS_INTC_EIC179 (*(OS_VOLATILE uint16 *)(0xFFF80166U))
  #define OS_INTC_EIC180 (*(OS_VOLATILE uint16 *)(0xFFF80168U))
  #define OS_INTC_EIC181 (*(OS_VOLATILE uint16 *)(0xFFF8016AU))
  #define OS_INTC_EIC182 (*(OS_VOLATILE uint16 *)(0xFFF8016CU))
  #define OS_INTC_EIC183 (*(OS_VOLATILE uint16 *)(0xFFF8016EU))
  #define OS_INTC_EIC184 (*(OS_VOLATILE uint16 *)(0xFFF80170U))
  #define OS_INTC_EIC185 (*(OS_VOLATILE uint16 *)(0xFFF80172U))
  #define OS_INTC_EIC186 (*(OS_VOLATILE uint16 *)(0xFFF80174U))
  #define OS_INTC_EIC187 (*(OS_VOLATILE uint16 *)(0xFFF80176U))
  #define OS_INTC_EIC188 (*(OS_VOLATILE uint16 *)(0xFFF80178U))
  #define OS_INTC_EIC189 (*(OS_VOLATILE uint16 *)(0xFFF8017AU))
  #define OS_INTC_EIC190 (*(OS_VOLATILE uint16 *)(0xFFF8017CU))
  #define OS_INTC_EIC191 (*(OS_VOLATILE uint16 *)(0xFFF8017EU))
  #define OS_INTC_EIC192 (*(OS_VOLATILE uint16 *)(0xFFF80180U))
  #define OS_INTC_EIC193 (*(OS_VOLATILE uint16 *)(0xFFF80182U))
  #define OS_INTC_EIC194 (*(OS_VOLATILE uint16 *)(0xFFF80184U))
  #define OS_INTC_EIC195 (*(OS_VOLATILE uint16 *)(0xFFF80186U))
  #define OS_INTC_EIC196 (*(OS_VOLATILE uint16 *)(0xFFF80188U))
  #define OS_INTC_EIC197 (*(OS_VOLATILE uint16 *)(0xFFF8018AU))
  #define OS_INTC_EIC198 (*(OS_VOLATILE uint16 *)(0xFFF8018CU))
  #define OS_INTC_EIC199 (*(OS_VOLATILE uint16 *)(0xFFF8018EU))
  #define OS_INTC_EIC200 (*(OS_VOLATILE uint16 *)(0xFFF80190U))
  #define OS_INTC_EIC201 (*(OS_VOLATILE uint16 *)(0xFFF80192U))
  #define OS_INTC_EIC202 (*(OS_VOLATILE uint16 *)(0xFFF80194U))
  #define OS_INTC_EIC203 (*(OS_VOLATILE uint16 *)(0xFFF80196U))
  #define OS_INTC_EIC204 (*(OS_VOLATILE uint16 *)(0xFFF80198U))
  #define OS_INTC_EIC205 (*(OS_VOLATILE uint16 *)(0xFFF8019AU))
  #define OS_INTC_EIC206 (*(OS_VOLATILE uint16 *)(0xFFF8019CU))
  #define OS_INTC_EIC207 (*(OS_VOLATILE uint16 *)(0xFFF8019EU))
  #define OS_INTC_EIC208 (*(OS_VOLATILE uint16 *)(0xFFF801A0U))
  #define OS_INTC_EIC209 (*(OS_VOLATILE uint16 *)(0xFFF801A2U))
  #define OS_INTC_EIC210 (*(OS_VOLATILE uint16 *)(0xFFF801A4U))
  #define OS_INTC_EIC211 (*(OS_VOLATILE uint16 *)(0xFFF801A6U))
  #define OS_INTC_EIC212 (*(OS_VOLATILE uint16 *)(0xFFF801A8U))
  #define OS_INTC_EIC213 (*(OS_VOLATILE uint16 *)(0xFFF801AAU))
  #define OS_INTC_EIC214 (*(OS_VOLATILE uint16 *)(0xFFF801ACU))
  #define OS_INTC_EIC215 (*(OS_VOLATILE uint16 *)(0xFFF801AEU))
  #define OS_INTC_EIC216 (*(OS_VOLATILE uint16 *)(0xFFF801B0U))
  #define OS_INTC_EIC217 (*(OS_VOLATILE uint16 *)(0xFFF801B2U))
  #define OS_INTC_EIC218 (*(OS_VOLATILE uint16 *)(0xFFF801B4U))
  #define OS_INTC_EIC219 (*(OS_VOLATILE uint16 *)(0xFFF801B6U))
  #define OS_INTC_EIC220 (*(OS_VOLATILE uint16 *)(0xFFF801B8U))
  #define OS_INTC_EIC221 (*(OS_VOLATILE uint16 *)(0xFFF801BAU))
  #define OS_INTC_EIC222 (*(OS_VOLATILE uint16 *)(0xFFF801BCU))
  #define OS_INTC_EIC223 (*(OS_VOLATILE uint16 *)(0xFFF801BEU))
  #define OS_INTC_EIC224 (*(OS_VOLATILE uint16 *)(0xFFF801C0U))
  #define OS_INTC_EIC225 (*(OS_VOLATILE uint16 *)(0xFFF801C2U))
  #define OS_INTC_EIC226 (*(OS_VOLATILE uint16 *)(0xFFF801C4U))
  #define OS_INTC_EIC227 (*(OS_VOLATILE uint16 *)(0xFFF801C6U))
  #define OS_INTC_EIC228 (*(OS_VOLATILE uint16 *)(0xFFF801C8U))
  #define OS_INTC_EIC229 (*(OS_VOLATILE uint16 *)(0xFFF801CAU))
  #define OS_INTC_EIC230 (*(OS_VOLATILE uint16 *)(0xFFF801CCU))
  #define OS_INTC_EIC231 (*(OS_VOLATILE uint16 *)(0xFFF801CEU))
  #define OS_INTC_EIC232 (*(OS_VOLATILE uint16 *)(0xFFF801D0U))
  #define OS_INTC_EIC233 (*(OS_VOLATILE uint16 *)(0xFFF801D2U))
  #define OS_INTC_EIC234 (*(OS_VOLATILE uint16 *)(0xFFF801D4U))
  #define OS_INTC_EIC235 (*(OS_VOLATILE uint16 *)(0xFFF801D6U))
  #define OS_INTC_EIC236 (*(OS_VOLATILE uint16 *)(0xFFF801D8U))
  #define OS_INTC_EIC237 (*(OS_VOLATILE uint16 *)(0xFFF801DAU))
  #define OS_INTC_EIC238 (*(OS_VOLATILE uint16 *)(0xFFF801DCU))
  #define OS_INTC_EIC239 (*(OS_VOLATILE uint16 *)(0xFFF801DEU))
  #define OS_INTC_EIC240 (*(OS_VOLATILE uint16 *)(0xFFF801E0U))
  #define OS_INTC_EIC241 (*(OS_VOLATILE uint16 *)(0xFFF801E2U))
  #define OS_INTC_EIC242 (*(OS_VOLATILE uint16 *)(0xFFF801E4U))
  #define OS_INTC_EIC243 (*(OS_VOLATILE uint16 *)(0xFFF801E6U))
  #define OS_INTC_EIC244 (*(OS_VOLATILE uint16 *)(0xFFF801E8U))
  #define OS_INTC_EIC245 (*(OS_VOLATILE uint16 *)(0xFFF801EAU))
  #define OS_INTC_EIC246 (*(OS_VOLATILE uint16 *)(0xFFF801ECU))
  #define OS_INTC_EIC247 (*(OS_VOLATILE uint16 *)(0xFFF801EEU))
  #define OS_INTC_EIC248 (*(OS_VOLATILE uint16 *)(0xFFF801F0U))
  #define OS_INTC_EIC249 (*(OS_VOLATILE uint16 *)(0xFFF801F2U))
  #define OS_INTC_EIC250 (*(OS_VOLATILE uint16 *)(0xFFF801F4U))
  #define OS_INTC_EIC251 (*(OS_VOLATILE uint16 *)(0xFFF801F6U))
  #define OS_INTC_EIC252 (*(OS_VOLATILE uint16 *)(0xFFF801F8U))
  #define OS_INTC_EIC253 (*(OS_VOLATILE uint16 *)(0xFFF801FAU))
  #define OS_INTC_EIC254 (*(OS_VOLATILE uint16 *)(0xFFF801FCU))
  #define OS_INTC_EIC255 (*(OS_VOLATILE uint16 *)(0xFFF801FEU))
  #define OS_INTC_EIC256 (*(OS_VOLATILE uint16 *)(0xFFF80200U))
  #define OS_INTC_EIC257 (*(OS_VOLATILE uint16 *)(0xFFF80202U))
  #define OS_INTC_EIC258 (*(OS_VOLATILE uint16 *)(0xFFF80204U))
  #define OS_INTC_EIC259 (*(OS_VOLATILE uint16 *)(0xFFF80206U))
  #define OS_INTC_EIC260 (*(OS_VOLATILE uint16 *)(0xFFF80208U))
  #define OS_INTC_EIC261 (*(OS_VOLATILE uint16 *)(0xFFF8020AU))
  #define OS_INTC_EIC262 (*(OS_VOLATILE uint16 *)(0xFFF8020CU))
  #define OS_INTC_EIC263 (*(OS_VOLATILE uint16 *)(0xFFF8020EU))
  #define OS_INTC_EIC264 (*(OS_VOLATILE uint16 *)(0xFFF80210U))
  #define OS_INTC_EIC265 (*(OS_VOLATILE uint16 *)(0xFFF80212U))
  #define OS_INTC_EIC266 (*(OS_VOLATILE uint16 *)(0xFFF80214U))
  #define OS_INTC_EIC267 (*(OS_VOLATILE uint16 *)(0xFFF80216U))
  #define OS_INTC_EIC268 (*(OS_VOLATILE uint16 *)(0xFFF80218U))
  #define OS_INTC_EIC269 (*(OS_VOLATILE uint16 *)(0xFFF8021AU))
  #define OS_INTC_EIC270 (*(OS_VOLATILE uint16 *)(0xFFF8021CU))
  #define OS_INTC_EIC271 (*(OS_VOLATILE uint16 *)(0xFFF8021EU))
  #define OS_INTC_EIC272 (*(OS_VOLATILE uint16 *)(0xFFF80220U))
  #define OS_INTC_EIC273 (*(OS_VOLATILE uint16 *)(0xFFF80222U))
  #define OS_INTC_EIC274 (*(OS_VOLATILE uint16 *)(0xFFF80224U))
  #define OS_INTC_EIC275 (*(OS_VOLATILE uint16 *)(0xFFF80226U))
  #define OS_INTC_EIC276 (*(OS_VOLATILE uint16 *)(0xFFF80228U))
  #define OS_INTC_EIC277 (*(OS_VOLATILE uint16 *)(0xFFF8022AU))
  #define OS_INTC_EIC278 (*(OS_VOLATILE uint16 *)(0xFFF8022CU))
  #define OS_INTC_EIC279 (*(OS_VOLATILE uint16 *)(0xFFF8022EU))
  #define OS_INTC_EIC280 (*(OS_VOLATILE uint16 *)(0xFFF80230U))
  #define OS_INTC_EIC281 (*(OS_VOLATILE uint16 *)(0xFFF80232U))
  #define OS_INTC_EIC282 (*(OS_VOLATILE uint16 *)(0xFFF80234U))
  #define OS_INTC_EIC283 (*(OS_VOLATILE uint16 *)(0xFFF80236U))
  #define OS_INTC_EIC284 (*(OS_VOLATILE uint16 *)(0xFFF80238U))
  #define OS_INTC_EIC285 (*(OS_VOLATILE uint16 *)(0xFFF8023AU))
  #define OS_INTC_EIC286 (*(OS_VOLATILE uint16 *)(0xFFF8023CU))
  #define OS_INTC_EIC287 (*(OS_VOLATILE uint16 *)(0xFFF8023EU))
  #define OS_INTC_EIC288 (*(OS_VOLATILE uint16 *)(0xFFF80240U))
  #define OS_INTC_EIC289 (*(OS_VOLATILE uint16 *)(0xFFF80242U))
  #define OS_INTC_EIC290 (*(OS_VOLATILE uint16 *)(0xFFF80244U))
  #define OS_INTC_EIC291 (*(OS_VOLATILE uint16 *)(0xFFF80246U))
  #define OS_INTC_EIC292 (*(OS_VOLATILE uint16 *)(0xFFF80248U))
  #define OS_INTC_EIC293 (*(OS_VOLATILE uint16 *)(0xFFF8024AU))
  #define OS_INTC_EIC294 (*(OS_VOLATILE uint16 *)(0xFFF8024CU))
  #define OS_INTC_EIC295 (*(OS_VOLATILE uint16 *)(0xFFF8024EU))
  #define OS_INTC_EIC296 (*(OS_VOLATILE uint16 *)(0xFFF80250U))
  #define OS_INTC_EIC297 (*(OS_VOLATILE uint16 *)(0xFFF80252U))
  #define OS_INTC_EIC298 (*(OS_VOLATILE uint16 *)(0xFFF80254U))
  #define OS_INTC_EIC299 (*(OS_VOLATILE uint16 *)(0xFFF80256U))
  #define OS_INTC_EIC300 (*(OS_VOLATILE uint16 *)(0xFFF80258U))
  #define OS_INTC_EIC301 (*(OS_VOLATILE uint16 *)(0xFFF8025AU))
  #define OS_INTC_EIC302 (*(OS_VOLATILE uint16 *)(0xFFF8025CU))
  #define OS_INTC_EIC303 (*(OS_VOLATILE uint16 *)(0xFFF8025EU))
  #define OS_INTC_EIC304 (*(OS_VOLATILE uint16 *)(0xFFF80260U))
  #define OS_INTC_EIC305 (*(OS_VOLATILE uint16 *)(0xFFF80262U))
  #define OS_INTC_EIC306 (*(OS_VOLATILE uint16 *)(0xFFF80264U))
  #define OS_INTC_EIC307 (*(OS_VOLATILE uint16 *)(0xFFF80266U))
  #define OS_INTC_EIC308 (*(OS_VOLATILE uint16 *)(0xFFF80268U))
  #define OS_INTC_EIC309 (*(OS_VOLATILE uint16 *)(0xFFF8026AU))
  #define OS_INTC_EIC310 (*(OS_VOLATILE uint16 *)(0xFFF8026CU))
  #define OS_INTC_EIC311 (*(OS_VOLATILE uint16 *)(0xFFF8026EU))
  #define OS_INTC_EIC312 (*(OS_VOLATILE uint16 *)(0xFFF80270U))
  #define OS_INTC_EIC313 (*(OS_VOLATILE uint16 *)(0xFFF80272U))
  #define OS_INTC_EIC314 (*(OS_VOLATILE uint16 *)(0xFFF80274U))
  #define OS_INTC_EIC315 (*(OS_VOLATILE uint16 *)(0xFFF80276U))
  #define OS_INTC_EIC316 (*(OS_VOLATILE uint16 *)(0xFFF80278U))
  #define OS_INTC_EIC317 (*(OS_VOLATILE uint16 *)(0xFFF8027AU))
  #define OS_INTC_EIC318 (*(OS_VOLATILE uint16 *)(0xFFF8027CU))
  #define OS_INTC_EIC319 (*(OS_VOLATILE uint16 *)(0xFFF8027EU))
  #define OS_INTC_EIC320 (*(OS_VOLATILE uint16 *)(0xFFF80280U))
  #define OS_INTC_EIC321 (*(OS_VOLATILE uint16 *)(0xFFF80282U))
  #define OS_INTC_EIC322 (*(OS_VOLATILE uint16 *)(0xFFF80284U))
  #define OS_INTC_EIC323 (*(OS_VOLATILE uint16 *)(0xFFF80286U))
  #define OS_INTC_EIC324 (*(OS_VOLATILE uint16 *)(0xFFF80288U))
  #define OS_INTC_EIC325 (*(OS_VOLATILE uint16 *)(0xFFF8028AU))
  #define OS_INTC_EIC326 (*(OS_VOLATILE uint16 *)(0xFFF8028CU))
  #define OS_INTC_EIC327 (*(OS_VOLATILE uint16 *)(0xFFF8028EU))
  #define OS_INTC_EIC328 (*(OS_VOLATILE uint16 *)(0xFFF80290U))
  #define OS_INTC_EIC329 (*(OS_VOLATILE uint16 *)(0xFFF80292U))
  #define OS_INTC_EIC330 (*(OS_VOLATILE uint16 *)(0xFFF80294U))
  #define OS_INTC_EIC331 (*(OS_VOLATILE uint16 *)(0xFFF80296U))
  #define OS_INTC_EIC332 (*(OS_VOLATILE uint16 *)(0xFFF80298U))
  #define OS_INTC_EIC333 (*(OS_VOLATILE uint16 *)(0xFFF8029AU))
  #define OS_INTC_EIC334 (*(OS_VOLATILE uint16 *)(0xFFF8029CU))
  #define OS_INTC_EIC335 (*(OS_VOLATILE uint16 *)(0xFFF8029EU))
  #define OS_INTC_EIC336 (*(OS_VOLATILE uint16 *)(0xFFF802A0U))
  #define OS_INTC_EIC337 (*(OS_VOLATILE uint16 *)(0xFFF802A2U))
  #define OS_INTC_EIC338 (*(OS_VOLATILE uint16 *)(0xFFF802A4U))
  #define OS_INTC_EIC339 (*(OS_VOLATILE uint16 *)(0xFFF802A6U))
  #define OS_INTC_EIC340 (*(OS_VOLATILE uint16 *)(0xFFF802A8U))
  #define OS_INTC_EIC341 (*(OS_VOLATILE uint16 *)(0xFFF802AAU))
  #define OS_INTC_EIC342 (*(OS_VOLATILE uint16 *)(0xFFF802ACU))
  #define OS_INTC_EIC343 (*(OS_VOLATILE uint16 *)(0xFFF802AEU))
  #define OS_INTC_EIC344 (*(OS_VOLATILE uint16 *)(0xFFF802B0U))
  #define OS_INTC_EIC345 (*(OS_VOLATILE uint16 *)(0xFFF802B2U))
  #define OS_INTC_EIC346 (*(OS_VOLATILE uint16 *)(0xFFF802B4U))
  #define OS_INTC_EIC347 (*(OS_VOLATILE uint16 *)(0xFFF802B6U))
  #define OS_INTC_EIC348 (*(OS_VOLATILE uint16 *)(0xFFF802B8U))
  #define OS_INTC_EIC349 (*(OS_VOLATILE uint16 *)(0xFFF802BAU))
  #define OS_INTC_EIC350 (*(OS_VOLATILE uint16 *)(0xFFF802BCU))
  #define OS_INTC_EIC351 (*(OS_VOLATILE uint16 *)(0xFFF802BEU))
  #define OS_INTC_EIC352 (*(OS_VOLATILE uint16 *)(0xFFF802C0U))
  #define OS_INTC_EIC353 (*(OS_VOLATILE uint16 *)(0xFFF802C2U))
  #define OS_INTC_EIC354 (*(OS_VOLATILE uint16 *)(0xFFF802C4U))
  #define OS_INTC_EIC355 (*(OS_VOLATILE uint16 *)(0xFFF802C6U))
  #define OS_INTC_EIC356 (*(OS_VOLATILE uint16 *)(0xFFF802C8U))
  #define OS_INTC_EIC357 (*(OS_VOLATILE uint16 *)(0xFFF802CAU))
  #define OS_INTC_EIC358 (*(OS_VOLATILE uint16 *)(0xFFF802CCU))
  #define OS_INTC_EIC359 (*(OS_VOLATILE uint16 *)(0xFFF802CEU))
  #define OS_INTC_EIC360 (*(OS_VOLATILE uint16 *)(0xFFF802D0U))
  #define OS_INTC_EIC361 (*(OS_VOLATILE uint16 *)(0xFFF802D2U))
  #define OS_INTC_EIC362 (*(OS_VOLATILE uint16 *)(0xFFF802D4U))
  #define OS_INTC_EIC363 (*(OS_VOLATILE uint16 *)(0xFFF802D6U))
  #define OS_INTC_EIC364 (*(OS_VOLATILE uint16 *)(0xFFF802D8U))
  #define OS_INTC_EIC365 (*(OS_VOLATILE uint16 *)(0xFFF802DAU))
  #define OS_INTC_EIC366 (*(OS_VOLATILE uint16 *)(0xFFF802DCU))
  #define OS_INTC_EIC367 (*(OS_VOLATILE uint16 *)(0xFFF802DEU))
  #define OS_INTC_EIC368 (*(OS_VOLATILE uint16 *)(0xFFF802E0U))
  #define OS_INTC_EIC369 (*(OS_VOLATILE uint16 *)(0xFFF802E2U))
  #define OS_INTC_EIC370 (*(OS_VOLATILE uint16 *)(0xFFF802E4U))
  #define OS_INTC_EIC371 (*(OS_VOLATILE uint16 *)(0xFFF802E6U))
  #define OS_INTC_EIC372 (*(OS_VOLATILE uint16 *)(0xFFF802E8U))
  #define OS_INTC_EIC373 (*(OS_VOLATILE uint16 *)(0xFFF802EAU))
  #define OS_INTC_EIC374 (*(OS_VOLATILE uint16 *)(0xFFF802ECU))
  #define OS_INTC_EIC375 (*(OS_VOLATILE uint16 *)(0xFFF802EEU))
  #define OS_INTC_EIC376 (*(OS_VOLATILE uint16 *)(0xFFF802F0U))
  #define OS_INTC_EIC377 (*(OS_VOLATILE uint16 *)(0xFFF802F2U))
  #define OS_INTC_EIC378 (*(OS_VOLATILE uint16 *)(0xFFF802F4U))
  #define OS_INTC_EIC379 (*(OS_VOLATILE uint16 *)(0xFFF802F6U))
  #define OS_INTC_EIC380 (*(OS_VOLATILE uint16 *)(0xFFF802F8U))
  #define OS_INTC_EIC381 (*(OS_VOLATILE uint16 *)(0xFFF802FAU))
  #define OS_INTC_EIC382 (*(OS_VOLATILE uint16 *)(0xFFF802FCU))
  #define OS_INTC_EIC383 (*(OS_VOLATILE uint16 *)(0xFFF802FEU))
  #define OS_INTC_EIC384 (*(OS_VOLATILE uint16 *)(0xFFF80300U))
  #define OS_INTC_EIC385 (*(OS_VOLATILE uint16 *)(0xFFF80302U))
  #define OS_INTC_EIC386 (*(OS_VOLATILE uint16 *)(0xFFF80304U))
  #define OS_INTC_EIC387 (*(OS_VOLATILE uint16 *)(0xFFF80306U))
  #define OS_INTC_EIC388 (*(OS_VOLATILE uint16 *)(0xFFF80308U))
  #define OS_INTC_EIC389 (*(OS_VOLATILE uint16 *)(0xFFF8030AU))
  #define OS_INTC_EIC390 (*(OS_VOLATILE uint16 *)(0xFFF8030CU))
  #define OS_INTC_EIC391 (*(OS_VOLATILE uint16 *)(0xFFF8030EU))
  #define OS_INTC_EIC392 (*(OS_VOLATILE uint16 *)(0xFFF80310U))
  #define OS_INTC_EIC393 (*(OS_VOLATILE uint16 *)(0xFFF80312U))
  #define OS_INTC_EIC394 (*(OS_VOLATILE uint16 *)(0xFFF80314U))
  #define OS_INTC_EIC395 (*(OS_VOLATILE uint16 *)(0xFFF80316U))
  #define OS_INTC_EIC396 (*(OS_VOLATILE uint16 *)(0xFFF80318U))
  #define OS_INTC_EIC397 (*(OS_VOLATILE uint16 *)(0xFFF8031AU))
  #define OS_INTC_EIC398 (*(OS_VOLATILE uint16 *)(0xFFF8031CU))
  #define OS_INTC_EIC399 (*(OS_VOLATILE uint16 *)(0xFFF8031EU))
  #define OS_INTC_EIC400 (*(OS_VOLATILE uint16 *)(0xFFF80320U))
  #define OS_INTC_EIC401 (*(OS_VOLATILE uint16 *)(0xFFF80322U))
  #define OS_INTC_EIC402 (*(OS_VOLATILE uint16 *)(0xFFF80324U))
  #define OS_INTC_EIC403 (*(OS_VOLATILE uint16 *)(0xFFF80326U))
  #define OS_INTC_EIC404 (*(OS_VOLATILE uint16 *)(0xFFF80328U))
  #define OS_INTC_EIC405 (*(OS_VOLATILE uint16 *)(0xFFF8032AU))
  #define OS_INTC_EIC406 (*(OS_VOLATILE uint16 *)(0xFFF8032CU))
  #define OS_INTC_EIC407 (*(OS_VOLATILE uint16 *)(0xFFF8032EU))
  #define OS_INTC_EIC408 (*(OS_VOLATILE uint16 *)(0xFFF80330U))
  #define OS_INTC_EIC409 (*(OS_VOLATILE uint16 *)(0xFFF80332U))
  #define OS_INTC_EIC410 (*(OS_VOLATILE uint16 *)(0xFFF80334U))
  #define OS_INTC_EIC411 (*(OS_VOLATILE uint16 *)(0xFFF80336U))
  #define OS_INTC_EIC412 (*(OS_VOLATILE uint16 *)(0xFFF80338U))
  #define OS_INTC_EIC413 (*(OS_VOLATILE uint16 *)(0xFFF8033AU))
  #define OS_INTC_EIC414 (*(OS_VOLATILE uint16 *)(0xFFF8033CU))
  #define OS_INTC_EIC415 (*(OS_VOLATILE uint16 *)(0xFFF8033EU))
  #define OS_INTC_EIC416 (*(OS_VOLATILE uint16 *)(0xFFF80340U))
  #define OS_INTC_EIC417 (*(OS_VOLATILE uint16 *)(0xFFF80342U))
  #define OS_INTC_EIC418 (*(OS_VOLATILE uint16 *)(0xFFF80344U))
  #define OS_INTC_EIC419 (*(OS_VOLATILE uint16 *)(0xFFF80346U))
  #define OS_INTC_EIC420 (*(OS_VOLATILE uint16 *)(0xFFF80348U))
  #define OS_INTC_EIC421 (*(OS_VOLATILE uint16 *)(0xFFF8034AU))
  #define OS_INTC_EIC422 (*(OS_VOLATILE uint16 *)(0xFFF8034CU))
  #define OS_INTC_EIC423 (*(OS_VOLATILE uint16 *)(0xFFF8034EU))
  #define OS_INTC_EIC424 (*(OS_VOLATILE uint16 *)(0xFFF80350U))
  #define OS_INTC_EIC425 (*(OS_VOLATILE uint16 *)(0xFFF80352U))
  #define OS_INTC_EIC426 (*(OS_VOLATILE uint16 *)(0xFFF80354U))
  #define OS_INTC_EIC427 (*(OS_VOLATILE uint16 *)(0xFFF80356U))
  #define OS_INTC_EIC428 (*(OS_VOLATILE uint16 *)(0xFFF80358U))
  #define OS_INTC_EIC429 (*(OS_VOLATILE uint16 *)(0xFFF8035AU))
  #define OS_INTC_EIC430 (*(OS_VOLATILE uint16 *)(0xFFF8035CU))
  #define OS_INTC_EIC431 (*(OS_VOLATILE uint16 *)(0xFFF8035EU))
  #define OS_INTC_EIC432 (*(OS_VOLATILE uint16 *)(0xFFF80360U))
  #define OS_INTC_EIC433 (*(OS_VOLATILE uint16 *)(0xFFF80362U))
  #define OS_INTC_EIC434 (*(OS_VOLATILE uint16 *)(0xFFF80364U))
  #define OS_INTC_EIC435 (*(OS_VOLATILE uint16 *)(0xFFF80366U))
  #define OS_INTC_EIC436 (*(OS_VOLATILE uint16 *)(0xFFF80368U))
  #define OS_INTC_EIC437 (*(OS_VOLATILE uint16 *)(0xFFF8036AU))
  #define OS_INTC_EIC438 (*(OS_VOLATILE uint16 *)(0xFFF8036CU))
  #define OS_INTC_EIC439 (*(OS_VOLATILE uint16 *)(0xFFF8036EU))
  #define OS_INTC_EIC440 (*(OS_VOLATILE uint16 *)(0xFFF80370U))
  #define OS_INTC_EIC441 (*(OS_VOLATILE uint16 *)(0xFFF80372U))
  #define OS_INTC_EIC442 (*(OS_VOLATILE uint16 *)(0xFFF80374U))
  #define OS_INTC_EIC443 (*(OS_VOLATILE uint16 *)(0xFFF80376U))
  #define OS_INTC_EIC444 (*(OS_VOLATILE uint16 *)(0xFFF80378U))
  #define OS_INTC_EIC445 (*(OS_VOLATILE uint16 *)(0xFFF8037AU))
  #define OS_INTC_EIC446 (*(OS_VOLATILE uint16 *)(0xFFF8037CU))
  #define OS_INTC_EIC447 (*(OS_VOLATILE uint16 *)(0xFFF8037EU))
  #define OS_INTC_EIC448 (*(OS_VOLATILE uint16 *)(0xFFF80380U))
  #define OS_INTC_EIC449 (*(OS_VOLATILE uint16 *)(0xFFF80382U))
  #define OS_INTC_EIC450 (*(OS_VOLATILE uint16 *)(0xFFF80384U))
  #define OS_INTC_EIC451 (*(OS_VOLATILE uint16 *)(0xFFF80386U))
  #define OS_INTC_EIC452 (*(OS_VOLATILE uint16 *)(0xFFF80388U))
  #define OS_INTC_EIC453 (*(OS_VOLATILE uint16 *)(0xFFF8038AU))
  #define OS_INTC_EIC454 (*(OS_VOLATILE uint16 *)(0xFFF8038CU))
  #define OS_INTC_EIC455 (*(OS_VOLATILE uint16 *)(0xFFF8038EU))
  #define OS_INTC_EIC456 (*(OS_VOLATILE uint16 *)(0xFFF80390U))
  #define OS_INTC_EIC457 (*(OS_VOLATILE uint16 *)(0xFFF80392U))
  #define OS_INTC_EIC458 (*(OS_VOLATILE uint16 *)(0xFFF80394U))
  #define OS_INTC_EIC459 (*(OS_VOLATILE uint16 *)(0xFFF80396U))
  #define OS_INTC_EIC460 (*(OS_VOLATILE uint16 *)(0xFFF80398U))
  #define OS_INTC_EIC461 (*(OS_VOLATILE uint16 *)(0xFFF8039AU))
  #define OS_INTC_EIC462 (*(OS_VOLATILE uint16 *)(0xFFF8039CU))
  #define OS_INTC_EIC463 (*(OS_VOLATILE uint16 *)(0xFFF8039EU))
  #define OS_INTC_EIC464 (*(OS_VOLATILE uint16 *)(0xFFF803A0U))
  #define OS_INTC_EIC465 (*(OS_VOLATILE uint16 *)(0xFFF803A2U))
  #define OS_INTC_EIC466 (*(OS_VOLATILE uint16 *)(0xFFF803A4U))
  #define OS_INTC_EIC467 (*(OS_VOLATILE uint16 *)(0xFFF803A6U))
  #define OS_INTC_EIC468 (*(OS_VOLATILE uint16 *)(0xFFF803A8U))
  #define OS_INTC_EIC469 (*(OS_VOLATILE uint16 *)(0xFFF803AAU))
  #define OS_INTC_EIC470 (*(OS_VOLATILE uint16 *)(0xFFF803ACU))
  #define OS_INTC_EIC471 (*(OS_VOLATILE uint16 *)(0xFFF803AEU))
  #define OS_INTC_EIC472 (*(OS_VOLATILE uint16 *)(0xFFF803B0U))
  #define OS_INTC_EIC473 (*(OS_VOLATILE uint16 *)(0xFFF803B2U))
  #define OS_INTC_EIC474 (*(OS_VOLATILE uint16 *)(0xFFF803B4U))
  #define OS_INTC_EIC475 (*(OS_VOLATILE uint16 *)(0xFFF803B6U))
  #define OS_INTC_EIC476 (*(OS_VOLATILE uint16 *)(0xFFF803B8U))
  #define OS_INTC_EIC477 (*(OS_VOLATILE uint16 *)(0xFFF803BAU))
  #define OS_INTC_EIC478 (*(OS_VOLATILE uint16 *)(0xFFF803BCU))
  #define OS_INTC_EIC479 (*(OS_VOLATILE uint16 *)(0xFFF803BEU))
  #define OS_INTC_EIC480 (*(OS_VOLATILE uint16 *)(0xFFF803C0U))
  #define OS_INTC_EIC481 (*(OS_VOLATILE uint16 *)(0xFFF803C2U))
  #define OS_INTC_EIC482 (*(OS_VOLATILE uint16 *)(0xFFF803C4U))
  #define OS_INTC_EIC483 (*(OS_VOLATILE uint16 *)(0xFFF803C6U))
  #define OS_INTC_EIC484 (*(OS_VOLATILE uint16 *)(0xFFF803C8U))
  #define OS_INTC_EIC485 (*(OS_VOLATILE uint16 *)(0xFFF803CAU))
  #define OS_INTC_EIC486 (*(OS_VOLATILE uint16 *)(0xFFF803CCU))
  #define OS_INTC_EIC487 (*(OS_VOLATILE uint16 *)(0xFFF803CEU))
  #define OS_INTC_EIC488 (*(OS_VOLATILE uint16 *)(0xFFF803D0U))
  #define OS_INTC_EIC489 (*(OS_VOLATILE uint16 *)(0xFFF803D2U))
  #define OS_INTC_EIC490 (*(OS_VOLATILE uint16 *)(0xFFF803D4U))
  #define OS_INTC_EIC491 (*(OS_VOLATILE uint16 *)(0xFFF803D6U))
  #define OS_INTC_EIC492 (*(OS_VOLATILE uint16 *)(0xFFF803D8U))
  #define OS_INTC_EIC493 (*(OS_VOLATILE uint16 *)(0xFFF803DAU))
  #define OS_INTC_EIC494 (*(OS_VOLATILE uint16 *)(0xFFF803DCU))
  #define OS_INTC_EIC495 (*(OS_VOLATILE uint16 *)(0xFFF803DEU))
  #define OS_INTC_EIC496 (*(OS_VOLATILE uint16 *)(0xFFF803E0U))
  #define OS_INTC_EIC497 (*(OS_VOLATILE uint16 *)(0xFFF803E2U))
  #define OS_INTC_EIC498 (*(OS_VOLATILE uint16 *)(0xFFF803E4U))
  #define OS_INTC_EIC499 (*(OS_VOLATILE uint16 *)(0xFFF803E6U))
  #define OS_INTC_EIC500 (*(OS_VOLATILE uint16 *)(0xFFF803E8U))
  #define OS_INTC_EIC501 (*(OS_VOLATILE uint16 *)(0xFFF803EAU))
  #define OS_INTC_EIC502 (*(OS_VOLATILE uint16 *)(0xFFF803ECU))
  #define OS_INTC_EIC503 (*(OS_VOLATILE uint16 *)(0xFFF803EEU))
  #define OS_INTC_EIC504 (*(OS_VOLATILE uint16 *)(0xFFF803F0U))
  #define OS_INTC_EIC505 (*(OS_VOLATILE uint16 *)(0xFFF803F2U))
  #define OS_INTC_EIC506 (*(OS_VOLATILE uint16 *)(0xFFF803F4U))
  #define OS_INTC_EIC507 (*(OS_VOLATILE uint16 *)(0xFFF803F6U))
  #define OS_INTC_EIC508 (*(OS_VOLATILE uint16 *)(0xFFF803F8U))
  #define OS_INTC_EIC509 (*(OS_VOLATILE uint16 *)(0xFFF803FAU))
  #define OS_INTC_EIC510 (*(OS_VOLATILE uint16 *)(0xFFF803FCU))
  #define OS_INTC_EIC511 (*(OS_VOLATILE uint16 *)(0xFFF803FEU))
  #define OS_INTC_EIC512 (*(OS_VOLATILE uint16 *)(0xFFF80400U))
  #define OS_INTC_EIC513 (*(OS_VOLATILE uint16 *)(0xFFF80402U))
  #define OS_INTC_EIC514 (*(OS_VOLATILE uint16 *)(0xFFF80404U))
  #define OS_INTC_EIC515 (*(OS_VOLATILE uint16 *)(0xFFF80406U))
  #define OS_INTC_EIC516 (*(OS_VOLATILE uint16 *)(0xFFF80408U))
  #define OS_INTC_EIC517 (*(OS_VOLATILE uint16 *)(0xFFF8040AU))
  #define OS_INTC_EIC518 (*(OS_VOLATILE uint16 *)(0xFFF8040CU))
  #define OS_INTC_EIC519 (*(OS_VOLATILE uint16 *)(0xFFF8040EU))
  #define OS_INTC_EIC520 (*(OS_VOLATILE uint16 *)(0xFFF80410U))
  #define OS_INTC_EIC521 (*(OS_VOLATILE uint16 *)(0xFFF80412U))
  #define OS_INTC_EIC522 (*(OS_VOLATILE uint16 *)(0xFFF80414U))
  #define OS_INTC_EIC523 (*(OS_VOLATILE uint16 *)(0xFFF80416U))
  #define OS_INTC_EIC524 (*(OS_VOLATILE uint16 *)(0xFFF80418U))
  #define OS_INTC_EIC525 (*(OS_VOLATILE uint16 *)(0xFFF8041AU))
  #define OS_INTC_EIC526 (*(OS_VOLATILE uint16 *)(0xFFF8041CU))
  #define OS_INTC_EIC527 (*(OS_VOLATILE uint16 *)(0xFFF8041EU))
  #define OS_INTC_EIC528 (*(OS_VOLATILE uint16 *)(0xFFF80420U))
  #define OS_INTC_EIC529 (*(OS_VOLATILE uint16 *)(0xFFF80422U))
  #define OS_INTC_EIC530 (*(OS_VOLATILE uint16 *)(0xFFF80424U))
  #define OS_INTC_EIC531 (*(OS_VOLATILE uint16 *)(0xFFF80426U))
  #define OS_INTC_EIC532 (*(OS_VOLATILE uint16 *)(0xFFF80428U))
  #define OS_INTC_EIC533 (*(OS_VOLATILE uint16 *)(0xFFF8042AU))
  #define OS_INTC_EIC534 (*(OS_VOLATILE uint16 *)(0xFFF8042CU))
  #define OS_INTC_EIC535 (*(OS_VOLATILE uint16 *)(0xFFF8042EU))
  #define OS_INTC_EIC536 (*(OS_VOLATILE uint16 *)(0xFFF80430U))
  #define OS_INTC_EIC537 (*(OS_VOLATILE uint16 *)(0xFFF80432U))
  #define OS_INTC_EIC538 (*(OS_VOLATILE uint16 *)(0xFFF80434U))
  #define OS_INTC_EIC539 (*(OS_VOLATILE uint16 *)(0xFFF80436U))
  #define OS_INTC_EIC540 (*(OS_VOLATILE uint16 *)(0xFFF80438U))
  #define OS_INTC_EIC541 (*(OS_VOLATILE uint16 *)(0xFFF8043AU))
  #define OS_INTC_EIC542 (*(OS_VOLATILE uint16 *)(0xFFF8043CU))
  #define OS_INTC_EIC543 (*(OS_VOLATILE uint16 *)(0xFFF8043EU))
  #define OS_INTC_EIC544 (*(OS_VOLATILE uint16 *)(0xFFF80440U))
  #define OS_INTC_EIC545 (*(OS_VOLATILE uint16 *)(0xFFF80442U))
  #define OS_INTC_EIC546 (*(OS_VOLATILE uint16 *)(0xFFF80444U))
  #define OS_INTC_EIC547 (*(OS_VOLATILE uint16 *)(0xFFF80446U))
  #define OS_INTC_EIC548 (*(OS_VOLATILE uint16 *)(0xFFF80448U))
  #define OS_INTC_EIC549 (*(OS_VOLATILE uint16 *)(0xFFF8044AU))
  #define OS_INTC_EIC550 (*(OS_VOLATILE uint16 *)(0xFFF8044CU))
  #define OS_INTC_EIC551 (*(OS_VOLATILE uint16 *)(0xFFF8044EU))
  #define OS_INTC_EIC552 (*(OS_VOLATILE uint16 *)(0xFFF80450U))
  #define OS_INTC_EIC553 (*(OS_VOLATILE uint16 *)(0xFFF80452U))
  #define OS_INTC_EIC554 (*(OS_VOLATILE uint16 *)(0xFFF80454U))
  #define OS_INTC_EIC555 (*(OS_VOLATILE uint16 *)(0xFFF80456U))
  #define OS_INTC_EIC556 (*(OS_VOLATILE uint16 *)(0xFFF80458U))
  #define OS_INTC_EIC557 (*(OS_VOLATILE uint16 *)(0xFFF8045AU))
  #define OS_INTC_EIC558 (*(OS_VOLATILE uint16 *)(0xFFF8045CU))
  #define OS_INTC_EIC559 (*(OS_VOLATILE uint16 *)(0xFFF8045EU))
  #define OS_INTC_EIC560 (*(OS_VOLATILE uint16 *)(0xFFF80460U))
  #define OS_INTC_EIC561 (*(OS_VOLATILE uint16 *)(0xFFF80462U))
  #define OS_INTC_EIC562 (*(OS_VOLATILE uint16 *)(0xFFF80464U))
  #define OS_INTC_EIC563 (*(OS_VOLATILE uint16 *)(0xFFF80466U))
  #define OS_INTC_EIC564 (*(OS_VOLATILE uint16 *)(0xFFF80468U))
  #define OS_INTC_EIC565 (*(OS_VOLATILE uint16 *)(0xFFF8046AU))
  #define OS_INTC_EIC566 (*(OS_VOLATILE uint16 *)(0xFFF8046CU))
  #define OS_INTC_EIC567 (*(OS_VOLATILE uint16 *)(0xFFF8046EU))
  #define OS_INTC_EIC568 (*(OS_VOLATILE uint16 *)(0xFFF80470U))
  #define OS_INTC_EIC569 (*(OS_VOLATILE uint16 *)(0xFFF80472U))
  #define OS_INTC_EIC570 (*(OS_VOLATILE uint16 *)(0xFFF80474U))
  #define OS_INTC_EIC571 (*(OS_VOLATILE uint16 *)(0xFFF80476U))
  #define OS_INTC_EIC572 (*(OS_VOLATILE uint16 *)(0xFFF80478U))
  #define OS_INTC_EIC573 (*(OS_VOLATILE uint16 *)(0xFFF8047AU))
  #define OS_INTC_EIC574 (*(OS_VOLATILE uint16 *)(0xFFF8047CU))
  #define OS_INTC_EIC575 (*(OS_VOLATILE uint16 *)(0xFFF8047EU))
  #define OS_INTC_EIC576 (*(OS_VOLATILE uint16 *)(0xFFF80480U))
  #define OS_INTC_EIC577 (*(OS_VOLATILE uint16 *)(0xFFF80482U))
  #define OS_INTC_EIC578 (*(OS_VOLATILE uint16 *)(0xFFF80484U))
  #define OS_INTC_EIC579 (*(OS_VOLATILE uint16 *)(0xFFF80486U))
  #define OS_INTC_EIC580 (*(OS_VOLATILE uint16 *)(0xFFF80488U))
  #define OS_INTC_EIC581 (*(OS_VOLATILE uint16 *)(0xFFF8048AU))
  #define OS_INTC_EIC582 (*(OS_VOLATILE uint16 *)(0xFFF8048CU))
  #define OS_INTC_EIC583 (*(OS_VOLATILE uint16 *)(0xFFF8048EU))
  #define OS_INTC_EIC584 (*(OS_VOLATILE uint16 *)(0xFFF80490U))
  #define OS_INTC_EIC585 (*(OS_VOLATILE uint16 *)(0xFFF80492U))
  #define OS_INTC_EIC586 (*(OS_VOLATILE uint16 *)(0xFFF80494U))
  #define OS_INTC_EIC587 (*(OS_VOLATILE uint16 *)(0xFFF80496U))
  #define OS_INTC_EIC588 (*(OS_VOLATILE uint16 *)(0xFFF80498U))
  #define OS_INTC_EIC589 (*(OS_VOLATILE uint16 *)(0xFFF8049AU))
  #define OS_INTC_EIC590 (*(OS_VOLATILE uint16 *)(0xFFF8049CU))
  #define OS_INTC_EIC591 (*(OS_VOLATILE uint16 *)(0xFFF8049EU))
  #define OS_INTC_EIC592 (*(OS_VOLATILE uint16 *)(0xFFF804A0U))
  #define OS_INTC_EIC593 (*(OS_VOLATILE uint16 *)(0xFFF804A2U))
  #define OS_INTC_EIC594 (*(OS_VOLATILE uint16 *)(0xFFF804A4U))
  #define OS_INTC_EIC595 (*(OS_VOLATILE uint16 *)(0xFFF804A6U))
  #define OS_INTC_EIC596 (*(OS_VOLATILE uint16 *)(0xFFF804A8U))
  #define OS_INTC_EIC597 (*(OS_VOLATILE uint16 *)(0xFFF804AAU))
  #define OS_INTC_EIC598 (*(OS_VOLATILE uint16 *)(0xFFF804ACU))
  #define OS_INTC_EIC599 (*(OS_VOLATILE uint16 *)(0xFFF804AEU))
  #define OS_INTC_EIC600 (*(OS_VOLATILE uint16 *)(0xFFF804B0U))
  #define OS_INTC_EIC601 (*(OS_VOLATILE uint16 *)(0xFFF804B2U))
  #define OS_INTC_EIC602 (*(OS_VOLATILE uint16 *)(0xFFF804B4U))
  #define OS_INTC_EIC603 (*(OS_VOLATILE uint16 *)(0xFFF804B6U))
  #define OS_INTC_EIC604 (*(OS_VOLATILE uint16 *)(0xFFF804B8U))
  #define OS_INTC_EIC605 (*(OS_VOLATILE uint16 *)(0xFFF804BAU))
  #define OS_INTC_EIC606 (*(OS_VOLATILE uint16 *)(0xFFF804BCU))
  #define OS_INTC_EIC607 (*(OS_VOLATILE uint16 *)(0xFFF804BEU))
  #define OS_INTC_EIC608 (*(OS_VOLATILE uint16 *)(0xFFF804C0U))
  #define OS_INTC_EIC609 (*(OS_VOLATILE uint16 *)(0xFFF804C2U))
  #define OS_INTC_EIC610 (*(OS_VOLATILE uint16 *)(0xFFF804C4U))
  #define OS_INTC_EIC611 (*(OS_VOLATILE uint16 *)(0xFFF804C6U))
  #define OS_INTC_EIC612 (*(OS_VOLATILE uint16 *)(0xFFF804C8U))
  #define OS_INTC_EIC613 (*(OS_VOLATILE uint16 *)(0xFFF804CAU))
  #define OS_INTC_EIC614 (*(OS_VOLATILE uint16 *)(0xFFF804CCU))
  #define OS_INTC_EIC615 (*(OS_VOLATILE uint16 *)(0xFFF804CEU))
  #define OS_INTC_EIC616 (*(OS_VOLATILE uint16 *)(0xFFF804D0U))
  #define OS_INTC_EIC617 (*(OS_VOLATILE uint16 *)(0xFFF804D2U))
  #define OS_INTC_EIC618 (*(OS_VOLATILE uint16 *)(0xFFF804D4U))
  #define OS_INTC_EIC619 (*(OS_VOLATILE uint16 *)(0xFFF804D6U))
  #define OS_INTC_EIC620 (*(OS_VOLATILE uint16 *)(0xFFF804D8U))
  #define OS_INTC_EIC621 (*(OS_VOLATILE uint16 *)(0xFFF804DAU))
  #define OS_INTC_EIC622 (*(OS_VOLATILE uint16 *)(0xFFF804DCU))
  #define OS_INTC_EIC623 (*(OS_VOLATILE uint16 *)(0xFFF804DEU))
  #define OS_INTC_EIC624 (*(OS_VOLATILE uint16 *)(0xFFF804E0U))
  #define OS_INTC_EIC625 (*(OS_VOLATILE uint16 *)(0xFFF804E2U))
  #define OS_INTC_EIC626 (*(OS_VOLATILE uint16 *)(0xFFF804E4U))
  #define OS_INTC_EIC627 (*(OS_VOLATILE uint16 *)(0xFFF804E6U))
  #define OS_INTC_EIC628 (*(OS_VOLATILE uint16 *)(0xFFF804E8U))
  #define OS_INTC_EIC629 (*(OS_VOLATILE uint16 *)(0xFFF804EAU))
  #define OS_INTC_EIC630 (*(OS_VOLATILE uint16 *)(0xFFF804ECU))
  #define OS_INTC_EIC631 (*(OS_VOLATILE uint16 *)(0xFFF804EEU))
  #define OS_INTC_EIC632 (*(OS_VOLATILE uint16 *)(0xFFF804F0U))
  #define OS_INTC_EIC633 (*(OS_VOLATILE uint16 *)(0xFFF804F2U))
  #define OS_INTC_EIC634 (*(OS_VOLATILE uint16 *)(0xFFF804F4U))
  #define OS_INTC_EIC635 (*(OS_VOLATILE uint16 *)(0xFFF804F6U))
  #define OS_INTC_EIC636 (*(OS_VOLATILE uint16 *)(0xFFF804F8U))
  #define OS_INTC_EIC637 (*(OS_VOLATILE uint16 *)(0xFFF804FAU))
  #define OS_INTC_EIC638 (*(OS_VOLATILE uint16 *)(0xFFF804FCU))
  #define OS_INTC_EIC639 (*(OS_VOLATILE uint16 *)(0xFFF804FEU))
  #define OS_INTC_EIC640 (*(OS_VOLATILE uint16 *)(0xFFF80500U))
  #define OS_INTC_EIC641 (*(OS_VOLATILE uint16 *)(0xFFF80502U))
  #define OS_INTC_EIC642 (*(OS_VOLATILE uint16 *)(0xFFF80504U))
  #define OS_INTC_EIC643 (*(OS_VOLATILE uint16 *)(0xFFF80506U))
  #define OS_INTC_EIC644 (*(OS_VOLATILE uint16 *)(0xFFF80508U))
  #define OS_INTC_EIC645 (*(OS_VOLATILE uint16 *)(0xFFF8050AU))
  #define OS_INTC_EIC646 (*(OS_VOLATILE uint16 *)(0xFFF8050CU))
  #define OS_INTC_EIC647 (*(OS_VOLATILE uint16 *)(0xFFF8050EU))
  #define OS_INTC_EIC648 (*(OS_VOLATILE uint16 *)(0xFFF80510U))
  #define OS_INTC_EIC649 (*(OS_VOLATILE uint16 *)(0xFFF80512U))
  #define OS_INTC_EIC650 (*(OS_VOLATILE uint16 *)(0xFFF80514U))
  #define OS_INTC_EIC651 (*(OS_VOLATILE uint16 *)(0xFFF80516U))
  #define OS_INTC_EIC652 (*(OS_VOLATILE uint16 *)(0xFFF80518U))
  #define OS_INTC_EIC653 (*(OS_VOLATILE uint16 *)(0xFFF8051AU))
  #define OS_INTC_EIC654 (*(OS_VOLATILE uint16 *)(0xFFF8051CU))
  #define OS_INTC_EIC655 (*(OS_VOLATILE uint16 *)(0xFFF8051EU))
  #define OS_INTC_EIC656 (*(OS_VOLATILE uint16 *)(0xFFF80520U))
  #define OS_INTC_EIC657 (*(OS_VOLATILE uint16 *)(0xFFF80522U))
  #define OS_INTC_EIC658 (*(OS_VOLATILE uint16 *)(0xFFF80524U))
  #define OS_INTC_EIC659 (*(OS_VOLATILE uint16 *)(0xFFF80526U))
  #define OS_INTC_EIC660 (*(OS_VOLATILE uint16 *)(0xFFF80528U))
  #define OS_INTC_EIC661 (*(OS_VOLATILE uint16 *)(0xFFF8052AU))
  #define OS_INTC_EIC662 (*(OS_VOLATILE uint16 *)(0xFFF8052CU))
  #define OS_INTC_EIC663 (*(OS_VOLATILE uint16 *)(0xFFF8052EU))
  #define OS_INTC_EIC664 (*(OS_VOLATILE uint16 *)(0xFFF80530U))
  #define OS_INTC_EIC665 (*(OS_VOLATILE uint16 *)(0xFFF80532U))
  #define OS_INTC_EIC666 (*(OS_VOLATILE uint16 *)(0xFFF80534U))
  #define OS_INTC_EIC667 (*(OS_VOLATILE uint16 *)(0xFFF80536U))
  #define OS_INTC_EIC668 (*(OS_VOLATILE uint16 *)(0xFFF80538U))
  #define OS_INTC_EIC669 (*(OS_VOLATILE uint16 *)(0xFFF8053AU))
  #define OS_INTC_EIC670 (*(OS_VOLATILE uint16 *)(0xFFF8053CU))
  #define OS_INTC_EIC671 (*(OS_VOLATILE uint16 *)(0xFFF8053EU))
  #define OS_INTC_EIC672 (*(OS_VOLATILE uint16 *)(0xFFF80540U))
  #define OS_INTC_EIC673 (*(OS_VOLATILE uint16 *)(0xFFF80542U))
  #define OS_INTC_EIC674 (*(OS_VOLATILE uint16 *)(0xFFF80544U))
  #define OS_INTC_EIC675 (*(OS_VOLATILE uint16 *)(0xFFF80546U))
  #define OS_INTC_EIC676 (*(OS_VOLATILE uint16 *)(0xFFF80548U))
  #define OS_INTC_EIC677 (*(OS_VOLATILE uint16 *)(0xFFF8054AU))
  #define OS_INTC_EIC678 (*(OS_VOLATILE uint16 *)(0xFFF8054CU))
  #define OS_INTC_EIC679 (*(OS_VOLATILE uint16 *)(0xFFF8054EU))
  #define OS_INTC_EIC680 (*(OS_VOLATILE uint16 *)(0xFFF80550U))
  #define OS_INTC_EIC681 (*(OS_VOLATILE uint16 *)(0xFFF80552U))
  #define OS_INTC_EIC682 (*(OS_VOLATILE uint16 *)(0xFFF80554U))
  #define OS_INTC_EIC683 (*(OS_VOLATILE uint16 *)(0xFFF80556U))
  #define OS_INTC_EIC684 (*(OS_VOLATILE uint16 *)(0xFFF80558U))
  #define OS_INTC_EIC685 (*(OS_VOLATILE uint16 *)(0xFFF8055AU))
  #define OS_INTC_EIC686 (*(OS_VOLATILE uint16 *)(0xFFF8055CU))
  #define OS_INTC_EIC687 (*(OS_VOLATILE uint16 *)(0xFFF8055EU))
  #define OS_INTC_EIC688 (*(OS_VOLATILE uint16 *)(0xFFF80560U))
  #define OS_INTC_EIC689 (*(OS_VOLATILE uint16 *)(0xFFF80562U))
  #define OS_INTC_EIC690 (*(OS_VOLATILE uint16 *)(0xFFF80564U))
  #define OS_INTC_EIC691 (*(OS_VOLATILE uint16 *)(0xFFF80566U))
  #define OS_INTC_EIC692 (*(OS_VOLATILE uint16 *)(0xFFF80568U))
  #define OS_INTC_EIC693 (*(OS_VOLATILE uint16 *)(0xFFF8056AU))
  #define OS_INTC_EIC694 (*(OS_VOLATILE uint16 *)(0xFFF8056CU))
  #define OS_INTC_EIC695 (*(OS_VOLATILE uint16 *)(0xFFF8056EU))
  #define OS_INTC_EIC696 (*(OS_VOLATILE uint16 *)(0xFFF80570U))
  #define OS_INTC_EIC697 (*(OS_VOLATILE uint16 *)(0xFFF80572U))
  #define OS_INTC_EIC698 (*(OS_VOLATILE uint16 *)(0xFFF80574U))
  #define OS_INTC_EIC699 (*(OS_VOLATILE uint16 *)(0xFFF80576U))
  #define OS_INTC_EIC700 (*(OS_VOLATILE uint16 *)(0xFFF80578U))
  #define OS_INTC_EIC701 (*(OS_VOLATILE uint16 *)(0xFFF8057AU))
  #define OS_INTC_EIC702 (*(OS_VOLATILE uint16 *)(0xFFF8057CU))
  #define OS_INTC_EIC703 (*(OS_VOLATILE uint16 *)(0xFFF8057EU))
  #define OS_INTC_EIC704 (*(OS_VOLATILE uint16 *)(0xFFF80580U))
  #define OS_INTC_EIC705 (*(OS_VOLATILE uint16 *)(0xFFF80582U))
  #define OS_INTC_EIC706 (*(OS_VOLATILE uint16 *)(0xFFF80584U))
  #define OS_INTC_EIC707 (*(OS_VOLATILE uint16 *)(0xFFF80586U))
  #define OS_INTC_EIC708 (*(OS_VOLATILE uint16 *)(0xFFF80588U))
  #define OS_INTC_EIC709 (*(OS_VOLATILE uint16 *)(0xFFF8058AU))
  #define OS_INTC_EIC710 (*(OS_VOLATILE uint16 *)(0xFFF8058CU))
  #define OS_INTC_EIC711 (*(OS_VOLATILE uint16 *)(0xFFF8058EU))
  #define OS_INTC_EIC712 (*(OS_VOLATILE uint16 *)(0xFFF80590U))
  #define OS_INTC_EIC713 (*(OS_VOLATILE uint16 *)(0xFFF80592U))
  #define OS_INTC_EIC714 (*(OS_VOLATILE uint16 *)(0xFFF80594U))
  #define OS_INTC_EIC715 (*(OS_VOLATILE uint16 *)(0xFFF80596U))
  #define OS_INTC_EIC716 (*(OS_VOLATILE uint16 *)(0xFFF80598U))
  #define OS_INTC_EIC717 (*(OS_VOLATILE uint16 *)(0xFFF8059AU))
  #define OS_INTC_EIC718 (*(OS_VOLATILE uint16 *)(0xFFF8059CU))
  #define OS_INTC_EIC719 (*(OS_VOLATILE uint16 *)(0xFFF8059EU))
  #define OS_INTC_EIC720 (*(OS_VOLATILE uint16 *)(0xFFF805A0U))
  #define OS_INTC_EIC721 (*(OS_VOLATILE uint16 *)(0xFFF805A2U))
  #define OS_INTC_EIC722 (*(OS_VOLATILE uint16 *)(0xFFF805A4U))
  #define OS_INTC_EIC723 (*(OS_VOLATILE uint16 *)(0xFFF805A6U))
  #define OS_INTC_EIC724 (*(OS_VOLATILE uint16 *)(0xFFF805A8U))
  #define OS_INTC_EIC725 (*(OS_VOLATILE uint16 *)(0xFFF805AAU))
  #define OS_INTC_EIC726 (*(OS_VOLATILE uint16 *)(0xFFF805ACU))
  #define OS_INTC_EIC727 (*(OS_VOLATILE uint16 *)(0xFFF805AEU))
  #define OS_INTC_EIC728 (*(OS_VOLATILE uint16 *)(0xFFF805B0U))
  #define OS_INTC_EIC729 (*(OS_VOLATILE uint16 *)(0xFFF805B2U))
  #define OS_INTC_EIC730 (*(OS_VOLATILE uint16 *)(0xFFF805B4U))
  #define OS_INTC_EIC731 (*(OS_VOLATILE uint16 *)(0xFFF805B6U))
  #define OS_INTC_EIC732 (*(OS_VOLATILE uint16 *)(0xFFF805B8U))
  #define OS_INTC_EIC733 (*(OS_VOLATILE uint16 *)(0xFFF805BAU))
  #define OS_INTC_EIC734 (*(OS_VOLATILE uint16 *)(0xFFF805BCU))
  #define OS_INTC_EIC735 (*(OS_VOLATILE uint16 *)(0xFFF805BEU))
  #define OS_INTC_EIC736 (*(OS_VOLATILE uint16 *)(0xFFF805C0U))
  #define OS_INTC_EIC737 (*(OS_VOLATILE uint16 *)(0xFFF805C2U))
  #define OS_INTC_EIC738 (*(OS_VOLATILE uint16 *)(0xFFF805C4U))
  #define OS_INTC_EIC739 (*(OS_VOLATILE uint16 *)(0xFFF805C6U))
  #define OS_INTC_EIC740 (*(OS_VOLATILE uint16 *)(0xFFF805C8U))
  #define OS_INTC_EIC741 (*(OS_VOLATILE uint16 *)(0xFFF805CAU))
  #define OS_INTC_EIC742 (*(OS_VOLATILE uint16 *)(0xFFF805CCU))
  #define OS_INTC_EIC743 (*(OS_VOLATILE uint16 *)(0xFFF805CEU))
  #define OS_INTC_EIC744 (*(OS_VOLATILE uint16 *)(0xFFF805D0U))
  #define OS_INTC_EIC745 (*(OS_VOLATILE uint16 *)(0xFFF805D2U))
  #define OS_INTC_EIC746 (*(OS_VOLATILE uint16 *)(0xFFF805D4U))
  #define OS_INTC_EIC747 (*(OS_VOLATILE uint16 *)(0xFFF805D6U))
  #define OS_INTC_EIC748 (*(OS_VOLATILE uint16 *)(0xFFF805D8U))
  #define OS_INTC_EIC749 (*(OS_VOLATILE uint16 *)(0xFFF805DAU))
  #define OS_INTC_EIC750 (*(OS_VOLATILE uint16 *)(0xFFF805DCU))
  #define OS_INTC_EIC751 (*(OS_VOLATILE uint16 *)(0xFFF805DEU))
  #define OS_INTC_EIC752 (*(OS_VOLATILE uint16 *)(0xFFF805E0U))
  #define OS_INTC_EIC753 (*(OS_VOLATILE uint16 *)(0xFFF805E2U))
  #define OS_INTC_EIC754 (*(OS_VOLATILE uint16 *)(0xFFF805E4U))
  #define OS_INTC_EIC755 (*(OS_VOLATILE uint16 *)(0xFFF805E6U))
  #define OS_INTC_EIC756 (*(OS_VOLATILE uint16 *)(0xFFF805E8U))
  #define OS_INTC_EIC757 (*(OS_VOLATILE uint16 *)(0xFFF805EAU))
  #define OS_INTC_EIC758 (*(OS_VOLATILE uint16 *)(0xFFF805ECU))
  #define OS_INTC_EIC759 (*(OS_VOLATILE uint16 *)(0xFFF805EEU))
  #define OS_INTC_EIC760 (*(OS_VOLATILE uint16 *)(0xFFF805F0U))
  #define OS_INTC_EIC761 (*(OS_VOLATILE uint16 *)(0xFFF805F2U))
  #define OS_INTC_EIC762 (*(OS_VOLATILE uint16 *)(0xFFF805F4U))
  #define OS_INTC_EIC763 (*(OS_VOLATILE uint16 *)(0xFFF805F6U))
  #define OS_INTC_EIC764 (*(OS_VOLATILE uint16 *)(0xFFF805F8U))
  #define OS_INTC_EIC765 (*(OS_VOLATILE uint16 *)(0xFFF805FAU))
  #define OS_INTC_EIC766 (*(OS_VOLATILE uint16 *)(0xFFF805FCU))
  #define OS_INTC_EIC767 (*(OS_VOLATILE uint16 *)(0xFFF805FEU))
  #define OS_INTC_EIBD0 (*(OS_VOLATILE uint32 *)(0xFFFC0100U))
  #define OS_INTC_EIBD1 (*(OS_VOLATILE uint32 *)(0xFFFC0104U))
  #define OS_INTC_EIBD2 (*(OS_VOLATILE uint32 *)(0xFFFC0108U))
  #define OS_INTC_EIBD3 (*(OS_VOLATILE uint32 *)(0xFFFC010CU))
  #define OS_INTC_EIBD4 (*(OS_VOLATILE uint32 *)(0xFFFC0110U))
  #define OS_INTC_EIBD5 (*(OS_VOLATILE uint32 *)(0xFFFC0114U))
  #define OS_INTC_EIBD6 (*(OS_VOLATILE uint32 *)(0xFFFC0118U))
  #define OS_INTC_EIBD7 (*(OS_VOLATILE uint32 *)(0xFFFC011CU))
  #define OS_INTC_EIBD8 (*(OS_VOLATILE uint32 *)(0xFFFC0120U))
  #define OS_INTC_EIBD9 (*(OS_VOLATILE uint32 *)(0xFFFC0124U))
  #define OS_INTC_EIBD10 (*(OS_VOLATILE uint32 *)(0xFFFC0128U))
  #define OS_INTC_EIBD11 (*(OS_VOLATILE uint32 *)(0xFFFC012CU))
  #define OS_INTC_EIBD12 (*(OS_VOLATILE uint32 *)(0xFFFC0130U))
  #define OS_INTC_EIBD13 (*(OS_VOLATILE uint32 *)(0xFFFC0134U))
  #define OS_INTC_EIBD14 (*(OS_VOLATILE uint32 *)(0xFFFC0138U))
  #define OS_INTC_EIBD15 (*(OS_VOLATILE uint32 *)(0xFFFC013CU))
  #define OS_INTC_EIBD16 (*(OS_VOLATILE uint32 *)(0xFFFC0140U))
  #define OS_INTC_EIBD17 (*(OS_VOLATILE uint32 *)(0xFFFC0144U))
  #define OS_INTC_EIBD18 (*(OS_VOLATILE uint32 *)(0xFFFC0148U))
  #define OS_INTC_EIBD19 (*(OS_VOLATILE uint32 *)(0xFFFC014CU))
  #define OS_INTC_EIBD20 (*(OS_VOLATILE uint32 *)(0xFFFC0150U))
  #define OS_INTC_EIBD21 (*(OS_VOLATILE uint32 *)(0xFFFC0154U))
  #define OS_INTC_EIBD22 (*(OS_VOLATILE uint32 *)(0xFFFC0158U))
  #define OS_INTC_EIBD23 (*(OS_VOLATILE uint32 *)(0xFFFC015CU))
  #define OS_INTC_EIBD24 (*(OS_VOLATILE uint32 *)(0xFFFC0160U))
  #define OS_INTC_EIBD25 (*(OS_VOLATILE uint32 *)(0xFFFC0164U))
  #define OS_INTC_EIBD26 (*(OS_VOLATILE uint32 *)(0xFFFC0168U))
  #define OS_INTC_EIBD27 (*(OS_VOLATILE uint32 *)(0xFFFC016CU))
  #define OS_INTC_EIBD28 (*(OS_VOLATILE uint32 *)(0xFFFC0170U))
  #define OS_INTC_EIBD29 (*(OS_VOLATILE uint32 *)(0xFFFC0174U))
  #define OS_INTC_EIBD30 (*(OS_VOLATILE uint32 *)(0xFFFC0178U))
  #define OS_INTC_EIBD31 (*(OS_VOLATILE uint32 *)(0xFFFC017CU))
  #define OS_INTC_EIBD32 (*(OS_VOLATILE uint32 *)(0xFFF82080U))
  #define OS_INTC_EIBD33 (*(OS_VOLATILE uint32 *)(0xFFF82084U))
  #define OS_INTC_EIBD34 (*(OS_VOLATILE uint32 *)(0xFFF82088U))
  #define OS_INTC_EIBD35 (*(OS_VOLATILE uint32 *)(0xFFF8208CU))
  #define OS_INTC_EIBD36 (*(OS_VOLATILE uint32 *)(0xFFF82090U))
  #define OS_INTC_EIBD37 (*(OS_VOLATILE uint32 *)(0xFFF82094U))
  #define OS_INTC_EIBD38 (*(OS_VOLATILE uint32 *)(0xFFF82098U))
  #define OS_INTC_EIBD39 (*(OS_VOLATILE uint32 *)(0xFFF8209CU))
  #define OS_INTC_EIBD40 (*(OS_VOLATILE uint32 *)(0xFFF820A0U))
  #define OS_INTC_EIBD41 (*(OS_VOLATILE uint32 *)(0xFFF820A4U))
  #define OS_INTC_EIBD42 (*(OS_VOLATILE uint32 *)(0xFFF820A8U))
  #define OS_INTC_EIBD43 (*(OS_VOLATILE uint32 *)(0xFFF820ACU))
  #define OS_INTC_EIBD44 (*(OS_VOLATILE uint32 *)(0xFFF820B0U))
  #define OS_INTC_EIBD45 (*(OS_VOLATILE uint32 *)(0xFFF820B4U))
  #define OS_INTC_EIBD46 (*(OS_VOLATILE uint32 *)(0xFFF820B8U))
  #define OS_INTC_EIBD47 (*(OS_VOLATILE uint32 *)(0xFFF820BCU))
  #define OS_INTC_EIBD48 (*(OS_VOLATILE uint32 *)(0xFFF820C0U))
  #define OS_INTC_EIBD49 (*(OS_VOLATILE uint32 *)(0xFFF820C4U))
  #define OS_INTC_EIBD50 (*(OS_VOLATILE uint32 *)(0xFFF820C8U))
  #define OS_INTC_EIBD51 (*(OS_VOLATILE uint32 *)(0xFFF820CCU))
  #define OS_INTC_EIBD52 (*(OS_VOLATILE uint32 *)(0xFFF820D0U))
  #define OS_INTC_EIBD53 (*(OS_VOLATILE uint32 *)(0xFFF820D4U))
  #define OS_INTC_EIBD54 (*(OS_VOLATILE uint32 *)(0xFFF820D8U))
  #define OS_INTC_EIBD55 (*(OS_VOLATILE uint32 *)(0xFFF820DCU))
  #define OS_INTC_EIBD56 (*(OS_VOLATILE uint32 *)(0xFFF820E0U))
  #define OS_INTC_EIBD57 (*(OS_VOLATILE uint32 *)(0xFFF820E4U))
  #define OS_INTC_EIBD58 (*(OS_VOLATILE uint32 *)(0xFFF820E8U))
  #define OS_INTC_EIBD59 (*(OS_VOLATILE uint32 *)(0xFFF820ECU))
  #define OS_INTC_EIBD60 (*(OS_VOLATILE uint32 *)(0xFFF820F0U))
  #define OS_INTC_EIBD61 (*(OS_VOLATILE uint32 *)(0xFFF820F4U))
  #define OS_INTC_EIBD62 (*(OS_VOLATILE uint32 *)(0xFFF820F8U))
  #define OS_INTC_EIBD63 (*(OS_VOLATILE uint32 *)(0xFFF820FCU))
  #define OS_INTC_EIBD64 (*(OS_VOLATILE uint32 *)(0xFFF82100U))
  #define OS_INTC_EIBD65 (*(OS_VOLATILE uint32 *)(0xFFF82104U))
  #define OS_INTC_EIBD66 (*(OS_VOLATILE uint32 *)(0xFFF82108U))
  #define OS_INTC_EIBD67 (*(OS_VOLATILE uint32 *)(0xFFF8210CU))
  #define OS_INTC_EIBD68 (*(OS_VOLATILE uint32 *)(0xFFF82110U))
  #define OS_INTC_EIBD69 (*(OS_VOLATILE uint32 *)(0xFFF82114U))
  #define OS_INTC_EIBD70 (*(OS_VOLATILE uint32 *)(0xFFF82118U))
  #define OS_INTC_EIBD71 (*(OS_VOLATILE uint32 *)(0xFFF8211CU))
  #define OS_INTC_EIBD72 (*(OS_VOLATILE uint32 *)(0xFFF82120U))
  #define OS_INTC_EIBD73 (*(OS_VOLATILE uint32 *)(0xFFF82124U))
  #define OS_INTC_EIBD74 (*(OS_VOLATILE uint32 *)(0xFFF82128U))
  #define OS_INTC_EIBD75 (*(OS_VOLATILE uint32 *)(0xFFF8212CU))
  #define OS_INTC_EIBD76 (*(OS_VOLATILE uint32 *)(0xFFF82130U))
  #define OS_INTC_EIBD77 (*(OS_VOLATILE uint32 *)(0xFFF82134U))
  #define OS_INTC_EIBD78 (*(OS_VOLATILE uint32 *)(0xFFF82138U))
  #define OS_INTC_EIBD79 (*(OS_VOLATILE uint32 *)(0xFFF8213CU))
  #define OS_INTC_EIBD80 (*(OS_VOLATILE uint32 *)(0xFFF82140U))
  #define OS_INTC_EIBD81 (*(OS_VOLATILE uint32 *)(0xFFF82144U))
  #define OS_INTC_EIBD82 (*(OS_VOLATILE uint32 *)(0xFFF82148U))
  #define OS_INTC_EIBD83 (*(OS_VOLATILE uint32 *)(0xFFF8214CU))
  #define OS_INTC_EIBD84 (*(OS_VOLATILE uint32 *)(0xFFF82150U))
  #define OS_INTC_EIBD85 (*(OS_VOLATILE uint32 *)(0xFFF82154U))
  #define OS_INTC_EIBD86 (*(OS_VOLATILE uint32 *)(0xFFF82158U))
  #define OS_INTC_EIBD87 (*(OS_VOLATILE uint32 *)(0xFFF8215CU))
  #define OS_INTC_EIBD88 (*(OS_VOLATILE uint32 *)(0xFFF82160U))
  #define OS_INTC_EIBD89 (*(OS_VOLATILE uint32 *)(0xFFF82164U))
  #define OS_INTC_EIBD90 (*(OS_VOLATILE uint32 *)(0xFFF82168U))
  #define OS_INTC_EIBD91 (*(OS_VOLATILE uint32 *)(0xFFF8216CU))
  #define OS_INTC_EIBD92 (*(OS_VOLATILE uint32 *)(0xFFF82170U))
  #define OS_INTC_EIBD93 (*(OS_VOLATILE uint32 *)(0xFFF82174U))
  #define OS_INTC_EIBD94 (*(OS_VOLATILE uint32 *)(0xFFF82178U))
  #define OS_INTC_EIBD95 (*(OS_VOLATILE uint32 *)(0xFFF8217CU))
  #define OS_INTC_EIBD96 (*(OS_VOLATILE uint32 *)(0xFFF82180U))
  #define OS_INTC_EIBD97 (*(OS_VOLATILE uint32 *)(0xFFF82184U))
  #define OS_INTC_EIBD98 (*(OS_VOLATILE uint32 *)(0xFFF82188U))
  #define OS_INTC_EIBD99 (*(OS_VOLATILE uint32 *)(0xFFF8218CU))
  #define OS_INTC_EIBD100 (*(OS_VOLATILE uint32 *)(0xFFF82190U))
  #define OS_INTC_EIBD101 (*(OS_VOLATILE uint32 *)(0xFFF82194U))
  #define OS_INTC_EIBD102 (*(OS_VOLATILE uint32 *)(0xFFF82198U))
  #define OS_INTC_EIBD103 (*(OS_VOLATILE uint32 *)(0xFFF8219CU))
  #define OS_INTC_EIBD104 (*(OS_VOLATILE uint32 *)(0xFFF821A0U))
  #define OS_INTC_EIBD105 (*(OS_VOLATILE uint32 *)(0xFFF821A4U))
  #define OS_INTC_EIBD106 (*(OS_VOLATILE uint32 *)(0xFFF821A8U))
  #define OS_INTC_EIBD107 (*(OS_VOLATILE uint32 *)(0xFFF821ACU))
  #define OS_INTC_EIBD108 (*(OS_VOLATILE uint32 *)(0xFFF821B0U))
  #define OS_INTC_EIBD109 (*(OS_VOLATILE uint32 *)(0xFFF821B4U))
  #define OS_INTC_EIBD110 (*(OS_VOLATILE uint32 *)(0xFFF821B8U))
  #define OS_INTC_EIBD111 (*(OS_VOLATILE uint32 *)(0xFFF821BCU))
  #define OS_INTC_EIBD112 (*(OS_VOLATILE uint32 *)(0xFFF821C0U))
  #define OS_INTC_EIBD113 (*(OS_VOLATILE uint32 *)(0xFFF821C4U))
  #define OS_INTC_EIBD114 (*(OS_VOLATILE uint32 *)(0xFFF821C8U))
  #define OS_INTC_EIBD115 (*(OS_VOLATILE uint32 *)(0xFFF821CCU))
  #define OS_INTC_EIBD116 (*(OS_VOLATILE uint32 *)(0xFFF821D0U))
  #define OS_INTC_EIBD117 (*(OS_VOLATILE uint32 *)(0xFFF821D4U))
  #define OS_INTC_EIBD118 (*(OS_VOLATILE uint32 *)(0xFFF821D8U))
  #define OS_INTC_EIBD119 (*(OS_VOLATILE uint32 *)(0xFFF821DCU))
  #define OS_INTC_EIBD120 (*(OS_VOLATILE uint32 *)(0xFFF821E0U))
  #define OS_INTC_EIBD121 (*(OS_VOLATILE uint32 *)(0xFFF821E4U))
  #define OS_INTC_EIBD122 (*(OS_VOLATILE uint32 *)(0xFFF821E8U))
  #define OS_INTC_EIBD123 (*(OS_VOLATILE uint32 *)(0xFFF821ECU))
  #define OS_INTC_EIBD124 (*(OS_VOLATILE uint32 *)(0xFFF821F0U))
  #define OS_INTC_EIBD125 (*(OS_VOLATILE uint32 *)(0xFFF821F4U))
  #define OS_INTC_EIBD126 (*(OS_VOLATILE uint32 *)(0xFFF821F8U))
  #define OS_INTC_EIBD127 (*(OS_VOLATILE uint32 *)(0xFFF821FCU))
  #define OS_INTC_EIBD128 (*(OS_VOLATILE uint32 *)(0xFFF82200U))
  #define OS_INTC_EIBD129 (*(OS_VOLATILE uint32 *)(0xFFF82204U))
  #define OS_INTC_EIBD130 (*(OS_VOLATILE uint32 *)(0xFFF82208U))
  #define OS_INTC_EIBD131 (*(OS_VOLATILE uint32 *)(0xFFF8220CU))
  #define OS_INTC_EIBD132 (*(OS_VOLATILE uint32 *)(0xFFF82210U))
  #define OS_INTC_EIBD133 (*(OS_VOLATILE uint32 *)(0xFFF82214U))
  #define OS_INTC_EIBD134 (*(OS_VOLATILE uint32 *)(0xFFF82218U))
  #define OS_INTC_EIBD135 (*(OS_VOLATILE uint32 *)(0xFFF8221CU))
  #define OS_INTC_EIBD136 (*(OS_VOLATILE uint32 *)(0xFFF82220U))
  #define OS_INTC_EIBD137 (*(OS_VOLATILE uint32 *)(0xFFF82224U))
  #define OS_INTC_EIBD138 (*(OS_VOLATILE uint32 *)(0xFFF82228U))
  #define OS_INTC_EIBD139 (*(OS_VOLATILE uint32 *)(0xFFF8222CU))
  #define OS_INTC_EIBD140 (*(OS_VOLATILE uint32 *)(0xFFF82230U))
  #define OS_INTC_EIBD141 (*(OS_VOLATILE uint32 *)(0xFFF82234U))
  #define OS_INTC_EIBD142 (*(OS_VOLATILE uint32 *)(0xFFF82238U))
  #define OS_INTC_EIBD143 (*(OS_VOLATILE uint32 *)(0xFFF8223CU))
  #define OS_INTC_EIBD144 (*(OS_VOLATILE uint32 *)(0xFFF82240U))
  #define OS_INTC_EIBD145 (*(OS_VOLATILE uint32 *)(0xFFF82244U))
  #define OS_INTC_EIBD146 (*(OS_VOLATILE uint32 *)(0xFFF82248U))
  #define OS_INTC_EIBD147 (*(OS_VOLATILE uint32 *)(0xFFF8224CU))
  #define OS_INTC_EIBD148 (*(OS_VOLATILE uint32 *)(0xFFF82250U))
  #define OS_INTC_EIBD149 (*(OS_VOLATILE uint32 *)(0xFFF82254U))
  #define OS_INTC_EIBD150 (*(OS_VOLATILE uint32 *)(0xFFF82258U))
  #define OS_INTC_EIBD151 (*(OS_VOLATILE uint32 *)(0xFFF8225CU))
  #define OS_INTC_EIBD152 (*(OS_VOLATILE uint32 *)(0xFFF82260U))
  #define OS_INTC_EIBD153 (*(OS_VOLATILE uint32 *)(0xFFF82264U))
  #define OS_INTC_EIBD154 (*(OS_VOLATILE uint32 *)(0xFFF82268U))
  #define OS_INTC_EIBD155 (*(OS_VOLATILE uint32 *)(0xFFF8226CU))
  #define OS_INTC_EIBD156 (*(OS_VOLATILE uint32 *)(0xFFF82270U))
  #define OS_INTC_EIBD157 (*(OS_VOLATILE uint32 *)(0xFFF82274U))
  #define OS_INTC_EIBD158 (*(OS_VOLATILE uint32 *)(0xFFF82278U))
  #define OS_INTC_EIBD159 (*(OS_VOLATILE uint32 *)(0xFFF8227CU))
  #define OS_INTC_EIBD160 (*(OS_VOLATILE uint32 *)(0xFFF82280U))
  #define OS_INTC_EIBD161 (*(OS_VOLATILE uint32 *)(0xFFF82284U))
  #define OS_INTC_EIBD162 (*(OS_VOLATILE uint32 *)(0xFFF82288U))
  #define OS_INTC_EIBD163 (*(OS_VOLATILE uint32 *)(0xFFF8228CU))
  #define OS_INTC_EIBD164 (*(OS_VOLATILE uint32 *)(0xFFF82290U))
  #define OS_INTC_EIBD165 (*(OS_VOLATILE uint32 *)(0xFFF82294U))
  #define OS_INTC_EIBD166 (*(OS_VOLATILE uint32 *)(0xFFF82298U))
  #define OS_INTC_EIBD167 (*(OS_VOLATILE uint32 *)(0xFFF8229CU))
  #define OS_INTC_EIBD168 (*(OS_VOLATILE uint32 *)(0xFFF822A0U))
  #define OS_INTC_EIBD169 (*(OS_VOLATILE uint32 *)(0xFFF822A4U))
  #define OS_INTC_EIBD170 (*(OS_VOLATILE uint32 *)(0xFFF822A8U))
  #define OS_INTC_EIBD171 (*(OS_VOLATILE uint32 *)(0xFFF822ACU))
  #define OS_INTC_EIBD172 (*(OS_VOLATILE uint32 *)(0xFFF822B0U))
  #define OS_INTC_EIBD173 (*(OS_VOLATILE uint32 *)(0xFFF822B4U))
  #define OS_INTC_EIBD174 (*(OS_VOLATILE uint32 *)(0xFFF822B8U))
  #define OS_INTC_EIBD175 (*(OS_VOLATILE uint32 *)(0xFFF822BCU))
  #define OS_INTC_EIBD176 (*(OS_VOLATILE uint32 *)(0xFFF822C0U))
  #define OS_INTC_EIBD177 (*(OS_VOLATILE uint32 *)(0xFFF822C4U))
  #define OS_INTC_EIBD178 (*(OS_VOLATILE uint32 *)(0xFFF822C8U))
  #define OS_INTC_EIBD179 (*(OS_VOLATILE uint32 *)(0xFFF822CCU))
  #define OS_INTC_EIBD180 (*(OS_VOLATILE uint32 *)(0xFFF822D0U))
  #define OS_INTC_EIBD181 (*(OS_VOLATILE uint32 *)(0xFFF822D4U))
  #define OS_INTC_EIBD182 (*(OS_VOLATILE uint32 *)(0xFFF822D8U))
  #define OS_INTC_EIBD183 (*(OS_VOLATILE uint32 *)(0xFFF822DCU))
  #define OS_INTC_EIBD184 (*(OS_VOLATILE uint32 *)(0xFFF822E0U))
  #define OS_INTC_EIBD185 (*(OS_VOLATILE uint32 *)(0xFFF822E4U))
  #define OS_INTC_EIBD186 (*(OS_VOLATILE uint32 *)(0xFFF822E8U))
  #define OS_INTC_EIBD187 (*(OS_VOLATILE uint32 *)(0xFFF822ECU))
  #define OS_INTC_EIBD188 (*(OS_VOLATILE uint32 *)(0xFFF822F0U))
  #define OS_INTC_EIBD189 (*(OS_VOLATILE uint32 *)(0xFFF822F4U))
  #define OS_INTC_EIBD190 (*(OS_VOLATILE uint32 *)(0xFFF822F8U))
  #define OS_INTC_EIBD191 (*(OS_VOLATILE uint32 *)(0xFFF822FCU))
  #define OS_INTC_EIBD192 (*(OS_VOLATILE uint32 *)(0xFFF82300U))
  #define OS_INTC_EIBD193 (*(OS_VOLATILE uint32 *)(0xFFF82304U))
  #define OS_INTC_EIBD194 (*(OS_VOLATILE uint32 *)(0xFFF82308U))
  #define OS_INTC_EIBD195 (*(OS_VOLATILE uint32 *)(0xFFF8230CU))
  #define OS_INTC_EIBD196 (*(OS_VOLATILE uint32 *)(0xFFF82310U))
  #define OS_INTC_EIBD197 (*(OS_VOLATILE uint32 *)(0xFFF82314U))
  #define OS_INTC_EIBD198 (*(OS_VOLATILE uint32 *)(0xFFF82318U))
  #define OS_INTC_EIBD199 (*(OS_VOLATILE uint32 *)(0xFFF8231CU))
  #define OS_INTC_EIBD200 (*(OS_VOLATILE uint32 *)(0xFFF82320U))
  #define OS_INTC_EIBD201 (*(OS_VOLATILE uint32 *)(0xFFF82324U))
  #define OS_INTC_EIBD202 (*(OS_VOLATILE uint32 *)(0xFFF82328U))
  #define OS_INTC_EIBD203 (*(OS_VOLATILE uint32 *)(0xFFF8232CU))
  #define OS_INTC_EIBD204 (*(OS_VOLATILE uint32 *)(0xFFF82330U))
  #define OS_INTC_EIBD205 (*(OS_VOLATILE uint32 *)(0xFFF82334U))
  #define OS_INTC_EIBD206 (*(OS_VOLATILE uint32 *)(0xFFF82338U))
  #define OS_INTC_EIBD207 (*(OS_VOLATILE uint32 *)(0xFFF8233CU))
  #define OS_INTC_EIBD208 (*(OS_VOLATILE uint32 *)(0xFFF82340U))
  #define OS_INTC_EIBD209 (*(OS_VOLATILE uint32 *)(0xFFF82344U))
  #define OS_INTC_EIBD210 (*(OS_VOLATILE uint32 *)(0xFFF82348U))
  #define OS_INTC_EIBD211 (*(OS_VOLATILE uint32 *)(0xFFF8234CU))
  #define OS_INTC_EIBD212 (*(OS_VOLATILE uint32 *)(0xFFF82350U))
  #define OS_INTC_EIBD213 (*(OS_VOLATILE uint32 *)(0xFFF82354U))
  #define OS_INTC_EIBD214 (*(OS_VOLATILE uint32 *)(0xFFF82358U))
  #define OS_INTC_EIBD215 (*(OS_VOLATILE uint32 *)(0xFFF8235CU))
  #define OS_INTC_EIBD216 (*(OS_VOLATILE uint32 *)(0xFFF82360U))
  #define OS_INTC_EIBD217 (*(OS_VOLATILE uint32 *)(0xFFF82364U))
  #define OS_INTC_EIBD218 (*(OS_VOLATILE uint32 *)(0xFFF82368U))
  #define OS_INTC_EIBD219 (*(OS_VOLATILE uint32 *)(0xFFF8236CU))
  #define OS_INTC_EIBD220 (*(OS_VOLATILE uint32 *)(0xFFF82370U))
  #define OS_INTC_EIBD221 (*(OS_VOLATILE uint32 *)(0xFFF82374U))
  #define OS_INTC_EIBD222 (*(OS_VOLATILE uint32 *)(0xFFF82378U))
  #define OS_INTC_EIBD223 (*(OS_VOLATILE uint32 *)(0xFFF8237CU))
  #define OS_INTC_EIBD224 (*(OS_VOLATILE uint32 *)(0xFFF82380U))
  #define OS_INTC_EIBD225 (*(OS_VOLATILE uint32 *)(0xFFF82384U))
  #define OS_INTC_EIBD226 (*(OS_VOLATILE uint32 *)(0xFFF82388U))
  #define OS_INTC_EIBD227 (*(OS_VOLATILE uint32 *)(0xFFF8238CU))
  #define OS_INTC_EIBD228 (*(OS_VOLATILE uint32 *)(0xFFF82390U))
  #define OS_INTC_EIBD229 (*(OS_VOLATILE uint32 *)(0xFFF82394U))
  #define OS_INTC_EIBD230 (*(OS_VOLATILE uint32 *)(0xFFF82398U))
  #define OS_INTC_EIBD231 (*(OS_VOLATILE uint32 *)(0xFFF8239CU))
  #define OS_INTC_EIBD232 (*(OS_VOLATILE uint32 *)(0xFFF823A0U))
  #define OS_INTC_EIBD233 (*(OS_VOLATILE uint32 *)(0xFFF823A4U))
  #define OS_INTC_EIBD234 (*(OS_VOLATILE uint32 *)(0xFFF823A8U))
  #define OS_INTC_EIBD235 (*(OS_VOLATILE uint32 *)(0xFFF823ACU))
  #define OS_INTC_EIBD236 (*(OS_VOLATILE uint32 *)(0xFFF823B0U))
  #define OS_INTC_EIBD237 (*(OS_VOLATILE uint32 *)(0xFFF823B4U))
  #define OS_INTC_EIBD238 (*(OS_VOLATILE uint32 *)(0xFFF823B8U))
  #define OS_INTC_EIBD239 (*(OS_VOLATILE uint32 *)(0xFFF823BCU))
  #define OS_INTC_EIBD240 (*(OS_VOLATILE uint32 *)(0xFFF823C0U))
  #define OS_INTC_EIBD241 (*(OS_VOLATILE uint32 *)(0xFFF823C4U))
  #define OS_INTC_EIBD242 (*(OS_VOLATILE uint32 *)(0xFFF823C8U))
  #define OS_INTC_EIBD243 (*(OS_VOLATILE uint32 *)(0xFFF823CCU))
  #define OS_INTC_EIBD244 (*(OS_VOLATILE uint32 *)(0xFFF823D0U))
  #define OS_INTC_EIBD245 (*(OS_VOLATILE uint32 *)(0xFFF823D4U))
  #define OS_INTC_EIBD246 (*(OS_VOLATILE uint32 *)(0xFFF823D8U))
  #define OS_INTC_EIBD247 (*(OS_VOLATILE uint32 *)(0xFFF823DCU))
  #define OS_INTC_EIBD248 (*(OS_VOLATILE uint32 *)(0xFFF823E0U))
  #define OS_INTC_EIBD249 (*(OS_VOLATILE uint32 *)(0xFFF823E4U))
  #define OS_INTC_EIBD250 (*(OS_VOLATILE uint32 *)(0xFFF823E8U))
  #define OS_INTC_EIBD251 (*(OS_VOLATILE uint32 *)(0xFFF823ECU))
  #define OS_INTC_EIBD252 (*(OS_VOLATILE uint32 *)(0xFFF823F0U))
  #define OS_INTC_EIBD253 (*(OS_VOLATILE uint32 *)(0xFFF823F4U))
  #define OS_INTC_EIBD254 (*(OS_VOLATILE uint32 *)(0xFFF823F8U))
  #define OS_INTC_EIBD255 (*(OS_VOLATILE uint32 *)(0xFFF823FCU))
  #define OS_INTC_EIBD256 (*(OS_VOLATILE uint32 *)(0xFFF82400U))
  #define OS_INTC_EIBD257 (*(OS_VOLATILE uint32 *)(0xFFF82404U))
  #define OS_INTC_EIBD258 (*(OS_VOLATILE uint32 *)(0xFFF82408U))
  #define OS_INTC_EIBD259 (*(OS_VOLATILE uint32 *)(0xFFF8240CU))
  #define OS_INTC_EIBD260 (*(OS_VOLATILE uint32 *)(0xFFF82410U))
  #define OS_INTC_EIBD261 (*(OS_VOLATILE uint32 *)(0xFFF82414U))
  #define OS_INTC_EIBD262 (*(OS_VOLATILE uint32 *)(0xFFF82418U))
  #define OS_INTC_EIBD263 (*(OS_VOLATILE uint32 *)(0xFFF8241CU))
  #define OS_INTC_EIBD264 (*(OS_VOLATILE uint32 *)(0xFFF82420U))
  #define OS_INTC_EIBD265 (*(OS_VOLATILE uint32 *)(0xFFF82424U))
  #define OS_INTC_EIBD266 (*(OS_VOLATILE uint32 *)(0xFFF82428U))
  #define OS_INTC_EIBD267 (*(OS_VOLATILE uint32 *)(0xFFF8242CU))
  #define OS_INTC_EIBD268 (*(OS_VOLATILE uint32 *)(0xFFF82430U))
  #define OS_INTC_EIBD269 (*(OS_VOLATILE uint32 *)(0xFFF82434U))
  #define OS_INTC_EIBD270 (*(OS_VOLATILE uint32 *)(0xFFF82438U))
  #define OS_INTC_EIBD271 (*(OS_VOLATILE uint32 *)(0xFFF8243CU))
  #define OS_INTC_EIBD272 (*(OS_VOLATILE uint32 *)(0xFFF82440U))
  #define OS_INTC_EIBD273 (*(OS_VOLATILE uint32 *)(0xFFF82444U))
  #define OS_INTC_EIBD274 (*(OS_VOLATILE uint32 *)(0xFFF82448U))
  #define OS_INTC_EIBD275 (*(OS_VOLATILE uint32 *)(0xFFF8244CU))
  #define OS_INTC_EIBD276 (*(OS_VOLATILE uint32 *)(0xFFF82450U))
  #define OS_INTC_EIBD277 (*(OS_VOLATILE uint32 *)(0xFFF82454U))
  #define OS_INTC_EIBD278 (*(OS_VOLATILE uint32 *)(0xFFF82458U))
  #define OS_INTC_EIBD279 (*(OS_VOLATILE uint32 *)(0xFFF8245CU))
  #define OS_INTC_EIBD280 (*(OS_VOLATILE uint32 *)(0xFFF82460U))
  #define OS_INTC_EIBD281 (*(OS_VOLATILE uint32 *)(0xFFF82464U))
  #define OS_INTC_EIBD282 (*(OS_VOLATILE uint32 *)(0xFFF82468U))
  #define OS_INTC_EIBD283 (*(OS_VOLATILE uint32 *)(0xFFF8246CU))
  #define OS_INTC_EIBD284 (*(OS_VOLATILE uint32 *)(0xFFF82470U))
  #define OS_INTC_EIBD285 (*(OS_VOLATILE uint32 *)(0xFFF82474U))
  #define OS_INTC_EIBD286 (*(OS_VOLATILE uint32 *)(0xFFF82478U))
  #define OS_INTC_EIBD287 (*(OS_VOLATILE uint32 *)(0xFFF8247CU))
  #define OS_INTC_EIBD288 (*(OS_VOLATILE uint32 *)(0xFFF82480U))
  #define OS_INTC_EIBD289 (*(OS_VOLATILE uint32 *)(0xFFF82484U))
  #define OS_INTC_EIBD290 (*(OS_VOLATILE uint32 *)(0xFFF82488U))
  #define OS_INTC_EIBD291 (*(OS_VOLATILE uint32 *)(0xFFF8248CU))
  #define OS_INTC_EIBD292 (*(OS_VOLATILE uint32 *)(0xFFF82490U))
  #define OS_INTC_EIBD293 (*(OS_VOLATILE uint32 *)(0xFFF82494U))
  #define OS_INTC_EIBD294 (*(OS_VOLATILE uint32 *)(0xFFF82498U))
  #define OS_INTC_EIBD295 (*(OS_VOLATILE uint32 *)(0xFFF8249CU))
  #define OS_INTC_EIBD296 (*(OS_VOLATILE uint32 *)(0xFFF824A0U))
  #define OS_INTC_EIBD297 (*(OS_VOLATILE uint32 *)(0xFFF824A4U))
  #define OS_INTC_EIBD298 (*(OS_VOLATILE uint32 *)(0xFFF824A8U))
  #define OS_INTC_EIBD299 (*(OS_VOLATILE uint32 *)(0xFFF824ACU))
  #define OS_INTC_EIBD300 (*(OS_VOLATILE uint32 *)(0xFFF824B0U))
  #define OS_INTC_EIBD301 (*(OS_VOLATILE uint32 *)(0xFFF824B4U))
  #define OS_INTC_EIBD302 (*(OS_VOLATILE uint32 *)(0xFFF824B8U))
  #define OS_INTC_EIBD303 (*(OS_VOLATILE uint32 *)(0xFFF824BCU))
  #define OS_INTC_EIBD304 (*(OS_VOLATILE uint32 *)(0xFFF824C0U))
  #define OS_INTC_EIBD305 (*(OS_VOLATILE uint32 *)(0xFFF824C4U))
  #define OS_INTC_EIBD306 (*(OS_VOLATILE uint32 *)(0xFFF824C8U))
  #define OS_INTC_EIBD307 (*(OS_VOLATILE uint32 *)(0xFFF824CCU))
  #define OS_INTC_EIBD308 (*(OS_VOLATILE uint32 *)(0xFFF824D0U))
  #define OS_INTC_EIBD309 (*(OS_VOLATILE uint32 *)(0xFFF824D4U))
  #define OS_INTC_EIBD310 (*(OS_VOLATILE uint32 *)(0xFFF824D8U))
  #define OS_INTC_EIBD311 (*(OS_VOLATILE uint32 *)(0xFFF824DCU))
  #define OS_INTC_EIBD312 (*(OS_VOLATILE uint32 *)(0xFFF824E0U))
  #define OS_INTC_EIBD313 (*(OS_VOLATILE uint32 *)(0xFFF824E4U))
  #define OS_INTC_EIBD314 (*(OS_VOLATILE uint32 *)(0xFFF824E8U))
  #define OS_INTC_EIBD315 (*(OS_VOLATILE uint32 *)(0xFFF824ECU))
  #define OS_INTC_EIBD316 (*(OS_VOLATILE uint32 *)(0xFFF824F0U))
  #define OS_INTC_EIBD317 (*(OS_VOLATILE uint32 *)(0xFFF824F4U))
  #define OS_INTC_EIBD318 (*(OS_VOLATILE uint32 *)(0xFFF824F8U))
  #define OS_INTC_EIBD319 (*(OS_VOLATILE uint32 *)(0xFFF824FCU))
  #define OS_INTC_EIBD320 (*(OS_VOLATILE uint32 *)(0xFFF82500U))
  #define OS_INTC_EIBD321 (*(OS_VOLATILE uint32 *)(0xFFF82504U))
  #define OS_INTC_EIBD322 (*(OS_VOLATILE uint32 *)(0xFFF82508U))
  #define OS_INTC_EIBD323 (*(OS_VOLATILE uint32 *)(0xFFF8250CU))
  #define OS_INTC_EIBD324 (*(OS_VOLATILE uint32 *)(0xFFF82510U))
  #define OS_INTC_EIBD325 (*(OS_VOLATILE uint32 *)(0xFFF82514U))
  #define OS_INTC_EIBD326 (*(OS_VOLATILE uint32 *)(0xFFF82518U))
  #define OS_INTC_EIBD327 (*(OS_VOLATILE uint32 *)(0xFFF8251CU))
  #define OS_INTC_EIBD328 (*(OS_VOLATILE uint32 *)(0xFFF82520U))
  #define OS_INTC_EIBD329 (*(OS_VOLATILE uint32 *)(0xFFF82524U))
  #define OS_INTC_EIBD330 (*(OS_VOLATILE uint32 *)(0xFFF82528U))
  #define OS_INTC_EIBD331 (*(OS_VOLATILE uint32 *)(0xFFF8252CU))
  #define OS_INTC_EIBD332 (*(OS_VOLATILE uint32 *)(0xFFF82530U))
  #define OS_INTC_EIBD333 (*(OS_VOLATILE uint32 *)(0xFFF82534U))
  #define OS_INTC_EIBD334 (*(OS_VOLATILE uint32 *)(0xFFF82538U))
  #define OS_INTC_EIBD335 (*(OS_VOLATILE uint32 *)(0xFFF8253CU))
  #define OS_INTC_EIBD336 (*(OS_VOLATILE uint32 *)(0xFFF82540U))
  #define OS_INTC_EIBD337 (*(OS_VOLATILE uint32 *)(0xFFF82544U))
  #define OS_INTC_EIBD338 (*(OS_VOLATILE uint32 *)(0xFFF82548U))
  #define OS_INTC_EIBD339 (*(OS_VOLATILE uint32 *)(0xFFF8254CU))
  #define OS_INTC_EIBD340 (*(OS_VOLATILE uint32 *)(0xFFF82550U))
  #define OS_INTC_EIBD341 (*(OS_VOLATILE uint32 *)(0xFFF82554U))
  #define OS_INTC_EIBD342 (*(OS_VOLATILE uint32 *)(0xFFF82558U))
  #define OS_INTC_EIBD343 (*(OS_VOLATILE uint32 *)(0xFFF8255CU))
  #define OS_INTC_EIBD344 (*(OS_VOLATILE uint32 *)(0xFFF82560U))
  #define OS_INTC_EIBD345 (*(OS_VOLATILE uint32 *)(0xFFF82564U))
  #define OS_INTC_EIBD346 (*(OS_VOLATILE uint32 *)(0xFFF82568U))
  #define OS_INTC_EIBD347 (*(OS_VOLATILE uint32 *)(0xFFF8256CU))
  #define OS_INTC_EIBD348 (*(OS_VOLATILE uint32 *)(0xFFF82570U))
  #define OS_INTC_EIBD349 (*(OS_VOLATILE uint32 *)(0xFFF82574U))
  #define OS_INTC_EIBD350 (*(OS_VOLATILE uint32 *)(0xFFF82578U))
  #define OS_INTC_EIBD351 (*(OS_VOLATILE uint32 *)(0xFFF8257CU))
  #define OS_INTC_EIBD352 (*(OS_VOLATILE uint32 *)(0xFFF82580U))
  #define OS_INTC_EIBD353 (*(OS_VOLATILE uint32 *)(0xFFF82584U))
  #define OS_INTC_EIBD354 (*(OS_VOLATILE uint32 *)(0xFFF82588U))
  #define OS_INTC_EIBD355 (*(OS_VOLATILE uint32 *)(0xFFF8258CU))
  #define OS_INTC_EIBD356 (*(OS_VOLATILE uint32 *)(0xFFF82590U))
  #define OS_INTC_EIBD357 (*(OS_VOLATILE uint32 *)(0xFFF82594U))
  #define OS_INTC_EIBD358 (*(OS_VOLATILE uint32 *)(0xFFF82598U))
  #define OS_INTC_EIBD359 (*(OS_VOLATILE uint32 *)(0xFFF8259CU))
  #define OS_INTC_EIBD360 (*(OS_VOLATILE uint32 *)(0xFFF825A0U))
  #define OS_INTC_EIBD361 (*(OS_VOLATILE uint32 *)(0xFFF825A4U))
  #define OS_INTC_EIBD362 (*(OS_VOLATILE uint32 *)(0xFFF825A8U))
  #define OS_INTC_EIBD363 (*(OS_VOLATILE uint32 *)(0xFFF825ACU))
  #define OS_INTC_EIBD364 (*(OS_VOLATILE uint32 *)(0xFFF825B0U))
  #define OS_INTC_EIBD365 (*(OS_VOLATILE uint32 *)(0xFFF825B4U))
  #define OS_INTC_EIBD366 (*(OS_VOLATILE uint32 *)(0xFFF825B8U))
  #define OS_INTC_EIBD367 (*(OS_VOLATILE uint32 *)(0xFFF825BCU))
  #define OS_INTC_EIBD368 (*(OS_VOLATILE uint32 *)(0xFFF825C0U))
  #define OS_INTC_EIBD369 (*(OS_VOLATILE uint32 *)(0xFFF825C4U))
  #define OS_INTC_EIBD370 (*(OS_VOLATILE uint32 *)(0xFFF825C8U))
  #define OS_INTC_EIBD371 (*(OS_VOLATILE uint32 *)(0xFFF825CCU))
  #define OS_INTC_EIBD372 (*(OS_VOLATILE uint32 *)(0xFFF825D0U))
  #define OS_INTC_EIBD373 (*(OS_VOLATILE uint32 *)(0xFFF825D4U))
  #define OS_INTC_EIBD374 (*(OS_VOLATILE uint32 *)(0xFFF825D8U))
  #define OS_INTC_EIBD375 (*(OS_VOLATILE uint32 *)(0xFFF825DCU))
  #define OS_INTC_EIBD376 (*(OS_VOLATILE uint32 *)(0xFFF825E0U))
  #define OS_INTC_EIBD377 (*(OS_VOLATILE uint32 *)(0xFFF825E4U))
  #define OS_INTC_EIBD378 (*(OS_VOLATILE uint32 *)(0xFFF825E8U))
  #define OS_INTC_EIBD379 (*(OS_VOLATILE uint32 *)(0xFFF825ECU))
  #define OS_INTC_EIBD380 (*(OS_VOLATILE uint32 *)(0xFFF825F0U))
  #define OS_INTC_EIBD381 (*(OS_VOLATILE uint32 *)(0xFFF825F4U))
  #define OS_INTC_EIBD382 (*(OS_VOLATILE uint32 *)(0xFFF825F8U))
  #define OS_INTC_EIBD383 (*(OS_VOLATILE uint32 *)(0xFFF825FCU))
  #define OS_INTC_EIBD384 (*(OS_VOLATILE uint32 *)(0xFFF82600U))
  #define OS_INTC_EIBD385 (*(OS_VOLATILE uint32 *)(0xFFF82604U))
  #define OS_INTC_EIBD386 (*(OS_VOLATILE uint32 *)(0xFFF82608U))
  #define OS_INTC_EIBD387 (*(OS_VOLATILE uint32 *)(0xFFF8260CU))
  #define OS_INTC_EIBD388 (*(OS_VOLATILE uint32 *)(0xFFF82610U))
  #define OS_INTC_EIBD389 (*(OS_VOLATILE uint32 *)(0xFFF82614U))
  #define OS_INTC_EIBD390 (*(OS_VOLATILE uint32 *)(0xFFF82618U))
  #define OS_INTC_EIBD391 (*(OS_VOLATILE uint32 *)(0xFFF8261CU))
  #define OS_INTC_EIBD392 (*(OS_VOLATILE uint32 *)(0xFFF82620U))
  #define OS_INTC_EIBD393 (*(OS_VOLATILE uint32 *)(0xFFF82624U))
  #define OS_INTC_EIBD394 (*(OS_VOLATILE uint32 *)(0xFFF82628U))
  #define OS_INTC_EIBD395 (*(OS_VOLATILE uint32 *)(0xFFF8262CU))
  #define OS_INTC_EIBD396 (*(OS_VOLATILE uint32 *)(0xFFF82630U))
  #define OS_INTC_EIBD397 (*(OS_VOLATILE uint32 *)(0xFFF82634U))
  #define OS_INTC_EIBD398 (*(OS_VOLATILE uint32 *)(0xFFF82638U))
  #define OS_INTC_EIBD399 (*(OS_VOLATILE uint32 *)(0xFFF8263CU))
  #define OS_INTC_EIBD400 (*(OS_VOLATILE uint32 *)(0xFFF82640U))
  #define OS_INTC_EIBD401 (*(OS_VOLATILE uint32 *)(0xFFF82644U))
  #define OS_INTC_EIBD402 (*(OS_VOLATILE uint32 *)(0xFFF82648U))
  #define OS_INTC_EIBD403 (*(OS_VOLATILE uint32 *)(0xFFF8264CU))
  #define OS_INTC_EIBD404 (*(OS_VOLATILE uint32 *)(0xFFF82650U))
  #define OS_INTC_EIBD405 (*(OS_VOLATILE uint32 *)(0xFFF82654U))
  #define OS_INTC_EIBD406 (*(OS_VOLATILE uint32 *)(0xFFF82658U))
  #define OS_INTC_EIBD407 (*(OS_VOLATILE uint32 *)(0xFFF8265CU))
  #define OS_INTC_EIBD408 (*(OS_VOLATILE uint32 *)(0xFFF82660U))
  #define OS_INTC_EIBD409 (*(OS_VOLATILE uint32 *)(0xFFF82664U))
  #define OS_INTC_EIBD410 (*(OS_VOLATILE uint32 *)(0xFFF82668U))
  #define OS_INTC_EIBD411 (*(OS_VOLATILE uint32 *)(0xFFF8266CU))
  #define OS_INTC_EIBD412 (*(OS_VOLATILE uint32 *)(0xFFF82670U))
  #define OS_INTC_EIBD413 (*(OS_VOLATILE uint32 *)(0xFFF82674U))
  #define OS_INTC_EIBD414 (*(OS_VOLATILE uint32 *)(0xFFF82678U))
  #define OS_INTC_EIBD415 (*(OS_VOLATILE uint32 *)(0xFFF8267CU))
  #define OS_INTC_EIBD416 (*(OS_VOLATILE uint32 *)(0xFFF82680U))
  #define OS_INTC_EIBD417 (*(OS_VOLATILE uint32 *)(0xFFF82684U))
  #define OS_INTC_EIBD418 (*(OS_VOLATILE uint32 *)(0xFFF82688U))
  #define OS_INTC_EIBD419 (*(OS_VOLATILE uint32 *)(0xFFF8268CU))
  #define OS_INTC_EIBD420 (*(OS_VOLATILE uint32 *)(0xFFF82690U))
  #define OS_INTC_EIBD421 (*(OS_VOLATILE uint32 *)(0xFFF82694U))
  #define OS_INTC_EIBD422 (*(OS_VOLATILE uint32 *)(0xFFF82698U))
  #define OS_INTC_EIBD423 (*(OS_VOLATILE uint32 *)(0xFFF8269CU))
  #define OS_INTC_EIBD424 (*(OS_VOLATILE uint32 *)(0xFFF826A0U))
  #define OS_INTC_EIBD425 (*(OS_VOLATILE uint32 *)(0xFFF826A4U))
  #define OS_INTC_EIBD426 (*(OS_VOLATILE uint32 *)(0xFFF826A8U))
  #define OS_INTC_EIBD427 (*(OS_VOLATILE uint32 *)(0xFFF826ACU))
  #define OS_INTC_EIBD428 (*(OS_VOLATILE uint32 *)(0xFFF826B0U))
  #define OS_INTC_EIBD429 (*(OS_VOLATILE uint32 *)(0xFFF826B4U))
  #define OS_INTC_EIBD430 (*(OS_VOLATILE uint32 *)(0xFFF826B8U))
  #define OS_INTC_EIBD431 (*(OS_VOLATILE uint32 *)(0xFFF826BCU))
  #define OS_INTC_EIBD432 (*(OS_VOLATILE uint32 *)(0xFFF826C0U))
  #define OS_INTC_EIBD433 (*(OS_VOLATILE uint32 *)(0xFFF826C4U))
  #define OS_INTC_EIBD434 (*(OS_VOLATILE uint32 *)(0xFFF826C8U))
  #define OS_INTC_EIBD435 (*(OS_VOLATILE uint32 *)(0xFFF826CCU))
  #define OS_INTC_EIBD436 (*(OS_VOLATILE uint32 *)(0xFFF826D0U))
  #define OS_INTC_EIBD437 (*(OS_VOLATILE uint32 *)(0xFFF826D4U))
  #define OS_INTC_EIBD438 (*(OS_VOLATILE uint32 *)(0xFFF826D8U))
  #define OS_INTC_EIBD439 (*(OS_VOLATILE uint32 *)(0xFFF826DCU))
  #define OS_INTC_EIBD440 (*(OS_VOLATILE uint32 *)(0xFFF826E0U))
  #define OS_INTC_EIBD441 (*(OS_VOLATILE uint32 *)(0xFFF826E4U))
  #define OS_INTC_EIBD442 (*(OS_VOLATILE uint32 *)(0xFFF826E8U))
  #define OS_INTC_EIBD443 (*(OS_VOLATILE uint32 *)(0xFFF826ECU))
  #define OS_INTC_EIBD444 (*(OS_VOLATILE uint32 *)(0xFFF826F0U))
  #define OS_INTC_EIBD445 (*(OS_VOLATILE uint32 *)(0xFFF826F4U))
  #define OS_INTC_EIBD446 (*(OS_VOLATILE uint32 *)(0xFFF826F8U))
  #define OS_INTC_EIBD447 (*(OS_VOLATILE uint32 *)(0xFFF826FCU))
  #define OS_INTC_EIBD448 (*(OS_VOLATILE uint32 *)(0xFFF82700U))
  #define OS_INTC_EIBD449 (*(OS_VOLATILE uint32 *)(0xFFF82704U))
  #define OS_INTC_EIBD450 (*(OS_VOLATILE uint32 *)(0xFFF82708U))
  #define OS_INTC_EIBD451 (*(OS_VOLATILE uint32 *)(0xFFF8270CU))
  #define OS_INTC_EIBD452 (*(OS_VOLATILE uint32 *)(0xFFF82710U))
  #define OS_INTC_EIBD453 (*(OS_VOLATILE uint32 *)(0xFFF82714U))
  #define OS_INTC_EIBD454 (*(OS_VOLATILE uint32 *)(0xFFF82718U))
  #define OS_INTC_EIBD455 (*(OS_VOLATILE uint32 *)(0xFFF8271CU))
  #define OS_INTC_EIBD456 (*(OS_VOLATILE uint32 *)(0xFFF82720U))
  #define OS_INTC_EIBD457 (*(OS_VOLATILE uint32 *)(0xFFF82724U))
  #define OS_INTC_EIBD458 (*(OS_VOLATILE uint32 *)(0xFFF82728U))
  #define OS_INTC_EIBD459 (*(OS_VOLATILE uint32 *)(0xFFF8272CU))
  #define OS_INTC_EIBD460 (*(OS_VOLATILE uint32 *)(0xFFF82730U))
  #define OS_INTC_EIBD461 (*(OS_VOLATILE uint32 *)(0xFFF82734U))
  #define OS_INTC_EIBD462 (*(OS_VOLATILE uint32 *)(0xFFF82738U))
  #define OS_INTC_EIBD463 (*(OS_VOLATILE uint32 *)(0xFFF8273CU))
  #define OS_INTC_EIBD464 (*(OS_VOLATILE uint32 *)(0xFFF82740U))
  #define OS_INTC_EIBD465 (*(OS_VOLATILE uint32 *)(0xFFF82744U))
  #define OS_INTC_EIBD466 (*(OS_VOLATILE uint32 *)(0xFFF82748U))
  #define OS_INTC_EIBD467 (*(OS_VOLATILE uint32 *)(0xFFF8274CU))
  #define OS_INTC_EIBD468 (*(OS_VOLATILE uint32 *)(0xFFF82750U))
  #define OS_INTC_EIBD469 (*(OS_VOLATILE uint32 *)(0xFFF82754U))
  #define OS_INTC_EIBD470 (*(OS_VOLATILE uint32 *)(0xFFF82758U))
  #define OS_INTC_EIBD471 (*(OS_VOLATILE uint32 *)(0xFFF8275CU))
  #define OS_INTC_EIBD472 (*(OS_VOLATILE uint32 *)(0xFFF82760U))
  #define OS_INTC_EIBD473 (*(OS_VOLATILE uint32 *)(0xFFF82764U))
  #define OS_INTC_EIBD474 (*(OS_VOLATILE uint32 *)(0xFFF82768U))
  #define OS_INTC_EIBD475 (*(OS_VOLATILE uint32 *)(0xFFF8276CU))
  #define OS_INTC_EIBD476 (*(OS_VOLATILE uint32 *)(0xFFF82770U))
  #define OS_INTC_EIBD477 (*(OS_VOLATILE uint32 *)(0xFFF82774U))
  #define OS_INTC_EIBD478 (*(OS_VOLATILE uint32 *)(0xFFF82778U))
  #define OS_INTC_EIBD479 (*(OS_VOLATILE uint32 *)(0xFFF8277CU))
  #define OS_INTC_EIBD480 (*(OS_VOLATILE uint32 *)(0xFFF82780U))
  #define OS_INTC_EIBD481 (*(OS_VOLATILE uint32 *)(0xFFF82784U))
  #define OS_INTC_EIBD482 (*(OS_VOLATILE uint32 *)(0xFFF82788U))
  #define OS_INTC_EIBD483 (*(OS_VOLATILE uint32 *)(0xFFF8278CU))
  #define OS_INTC_EIBD484 (*(OS_VOLATILE uint32 *)(0xFFF82790U))
  #define OS_INTC_EIBD485 (*(OS_VOLATILE uint32 *)(0xFFF82794U))
  #define OS_INTC_EIBD486 (*(OS_VOLATILE uint32 *)(0xFFF82798U))
  #define OS_INTC_EIBD487 (*(OS_VOLATILE uint32 *)(0xFFF8279CU))
  #define OS_INTC_EIBD488 (*(OS_VOLATILE uint32 *)(0xFFF827A0U))
  #define OS_INTC_EIBD489 (*(OS_VOLATILE uint32 *)(0xFFF827A4U))
  #define OS_INTC_EIBD490 (*(OS_VOLATILE uint32 *)(0xFFF827A8U))
  #define OS_INTC_EIBD491 (*(OS_VOLATILE uint32 *)(0xFFF827ACU))
  #define OS_INTC_EIBD492 (*(OS_VOLATILE uint32 *)(0xFFF827B0U))
  #define OS_INTC_EIBD493 (*(OS_VOLATILE uint32 *)(0xFFF827B4U))
  #define OS_INTC_EIBD494 (*(OS_VOLATILE uint32 *)(0xFFF827B8U))
  #define OS_INTC_EIBD495 (*(OS_VOLATILE uint32 *)(0xFFF827BCU))
  #define OS_INTC_EIBD496 (*(OS_VOLATILE uint32 *)(0xFFF827C0U))
  #define OS_INTC_EIBD497 (*(OS_VOLATILE uint32 *)(0xFFF827C4U))
  #define OS_INTC_EIBD498 (*(OS_VOLATILE uint32 *)(0xFFF827C8U))
  #define OS_INTC_EIBD499 (*(OS_VOLATILE uint32 *)(0xFFF827CCU))
  #define OS_INTC_EIBD500 (*(OS_VOLATILE uint32 *)(0xFFF827D0U))
  #define OS_INTC_EIBD501 (*(OS_VOLATILE uint32 *)(0xFFF827D4U))
  #define OS_INTC_EIBD502 (*(OS_VOLATILE uint32 *)(0xFFF827D8U))
  #define OS_INTC_EIBD503 (*(OS_VOLATILE uint32 *)(0xFFF827DCU))
  #define OS_INTC_EIBD504 (*(OS_VOLATILE uint32 *)(0xFFF827E0U))
  #define OS_INTC_EIBD505 (*(OS_VOLATILE uint32 *)(0xFFF827E4U))
  #define OS_INTC_EIBD506 (*(OS_VOLATILE uint32 *)(0xFFF827E8U))
  #define OS_INTC_EIBD507 (*(OS_VOLATILE uint32 *)(0xFFF827ECU))
  #define OS_INTC_EIBD508 (*(OS_VOLATILE uint32 *)(0xFFF827F0U))
  #define OS_INTC_EIBD509 (*(OS_VOLATILE uint32 *)(0xFFF827F4U))
  #define OS_INTC_EIBD510 (*(OS_VOLATILE uint32 *)(0xFFF827F8U))
  #define OS_INTC_EIBD511 (*(OS_VOLATILE uint32 *)(0xFFF827FCU))
  #define OS_INTC_EIBD512 (*(OS_VOLATILE uint32 *)(0xFFF82800U))
  #define OS_INTC_EIBD513 (*(OS_VOLATILE uint32 *)(0xFFF82804U))
  #define OS_INTC_EIBD514 (*(OS_VOLATILE uint32 *)(0xFFF82808U))
  #define OS_INTC_EIBD515 (*(OS_VOLATILE uint32 *)(0xFFF8280CU))
  #define OS_INTC_EIBD516 (*(OS_VOLATILE uint32 *)(0xFFF82810U))
  #define OS_INTC_EIBD517 (*(OS_VOLATILE uint32 *)(0xFFF82814U))
  #define OS_INTC_EIBD518 (*(OS_VOLATILE uint32 *)(0xFFF82818U))
  #define OS_INTC_EIBD519 (*(OS_VOLATILE uint32 *)(0xFFF8281CU))
  #define OS_INTC_EIBD520 (*(OS_VOLATILE uint32 *)(0xFFF82820U))
  #define OS_INTC_EIBD521 (*(OS_VOLATILE uint32 *)(0xFFF82824U))
  #define OS_INTC_EIBD522 (*(OS_VOLATILE uint32 *)(0xFFF82828U))
  #define OS_INTC_EIBD523 (*(OS_VOLATILE uint32 *)(0xFFF8282CU))
  #define OS_INTC_EIBD524 (*(OS_VOLATILE uint32 *)(0xFFF82830U))
  #define OS_INTC_EIBD525 (*(OS_VOLATILE uint32 *)(0xFFF82834U))
  #define OS_INTC_EIBD526 (*(OS_VOLATILE uint32 *)(0xFFF82838U))
  #define OS_INTC_EIBD527 (*(OS_VOLATILE uint32 *)(0xFFF8283CU))
  #define OS_INTC_EIBD528 (*(OS_VOLATILE uint32 *)(0xFFF82840U))
  #define OS_INTC_EIBD529 (*(OS_VOLATILE uint32 *)(0xFFF82844U))
  #define OS_INTC_EIBD530 (*(OS_VOLATILE uint32 *)(0xFFF82848U))
  #define OS_INTC_EIBD531 (*(OS_VOLATILE uint32 *)(0xFFF8284CU))
  #define OS_INTC_EIBD532 (*(OS_VOLATILE uint32 *)(0xFFF82850U))
  #define OS_INTC_EIBD533 (*(OS_VOLATILE uint32 *)(0xFFF82854U))
  #define OS_INTC_EIBD534 (*(OS_VOLATILE uint32 *)(0xFFF82858U))
  #define OS_INTC_EIBD535 (*(OS_VOLATILE uint32 *)(0xFFF8285CU))
  #define OS_INTC_EIBD536 (*(OS_VOLATILE uint32 *)(0xFFF82860U))
  #define OS_INTC_EIBD537 (*(OS_VOLATILE uint32 *)(0xFFF82864U))
  #define OS_INTC_EIBD538 (*(OS_VOLATILE uint32 *)(0xFFF82868U))
  #define OS_INTC_EIBD539 (*(OS_VOLATILE uint32 *)(0xFFF8286CU))
  #define OS_INTC_EIBD540 (*(OS_VOLATILE uint32 *)(0xFFF82870U))
  #define OS_INTC_EIBD541 (*(OS_VOLATILE uint32 *)(0xFFF82874U))
  #define OS_INTC_EIBD542 (*(OS_VOLATILE uint32 *)(0xFFF82878U))
  #define OS_INTC_EIBD543 (*(OS_VOLATILE uint32 *)(0xFFF8287CU))
  #define OS_INTC_EIBD544 (*(OS_VOLATILE uint32 *)(0xFFF82880U))
  #define OS_INTC_EIBD545 (*(OS_VOLATILE uint32 *)(0xFFF82884U))
  #define OS_INTC_EIBD546 (*(OS_VOLATILE uint32 *)(0xFFF82888U))
  #define OS_INTC_EIBD547 (*(OS_VOLATILE uint32 *)(0xFFF8288CU))
  #define OS_INTC_EIBD548 (*(OS_VOLATILE uint32 *)(0xFFF82890U))
  #define OS_INTC_EIBD549 (*(OS_VOLATILE uint32 *)(0xFFF82894U))
  #define OS_INTC_EIBD550 (*(OS_VOLATILE uint32 *)(0xFFF82898U))
  #define OS_INTC_EIBD551 (*(OS_VOLATILE uint32 *)(0xFFF8289CU))
  #define OS_INTC_EIBD552 (*(OS_VOLATILE uint32 *)(0xFFF828A0U))
  #define OS_INTC_EIBD553 (*(OS_VOLATILE uint32 *)(0xFFF828A4U))
  #define OS_INTC_EIBD554 (*(OS_VOLATILE uint32 *)(0xFFF828A8U))
  #define OS_INTC_EIBD555 (*(OS_VOLATILE uint32 *)(0xFFF828ACU))
  #define OS_INTC_EIBD556 (*(OS_VOLATILE uint32 *)(0xFFF828B0U))
  #define OS_INTC_EIBD557 (*(OS_VOLATILE uint32 *)(0xFFF828B4U))
  #define OS_INTC_EIBD558 (*(OS_VOLATILE uint32 *)(0xFFF828B8U))
  #define OS_INTC_EIBD559 (*(OS_VOLATILE uint32 *)(0xFFF828BCU))
  #define OS_INTC_EIBD560 (*(OS_VOLATILE uint32 *)(0xFFF828C0U))
  #define OS_INTC_EIBD561 (*(OS_VOLATILE uint32 *)(0xFFF828C4U))
  #define OS_INTC_EIBD562 (*(OS_VOLATILE uint32 *)(0xFFF828C8U))
  #define OS_INTC_EIBD563 (*(OS_VOLATILE uint32 *)(0xFFF828CCU))
  #define OS_INTC_EIBD564 (*(OS_VOLATILE uint32 *)(0xFFF828D0U))
  #define OS_INTC_EIBD565 (*(OS_VOLATILE uint32 *)(0xFFF828D4U))
  #define OS_INTC_EIBD566 (*(OS_VOLATILE uint32 *)(0xFFF828D8U))
  #define OS_INTC_EIBD567 (*(OS_VOLATILE uint32 *)(0xFFF828DCU))
  #define OS_INTC_EIBD568 (*(OS_VOLATILE uint32 *)(0xFFF828E0U))
  #define OS_INTC_EIBD569 (*(OS_VOLATILE uint32 *)(0xFFF828E4U))
  #define OS_INTC_EIBD570 (*(OS_VOLATILE uint32 *)(0xFFF828E8U))
  #define OS_INTC_EIBD571 (*(OS_VOLATILE uint32 *)(0xFFF828ECU))
  #define OS_INTC_EIBD572 (*(OS_VOLATILE uint32 *)(0xFFF828F0U))
  #define OS_INTC_EIBD573 (*(OS_VOLATILE uint32 *)(0xFFF828F4U))
  #define OS_INTC_EIBD574 (*(OS_VOLATILE uint32 *)(0xFFF828F8U))
  #define OS_INTC_EIBD575 (*(OS_VOLATILE uint32 *)(0xFFF828FCU))
  #define OS_INTC_EIBD576 (*(OS_VOLATILE uint32 *)(0xFFF82900U))
  #define OS_INTC_EIBD577 (*(OS_VOLATILE uint32 *)(0xFFF82904U))
  #define OS_INTC_EIBD578 (*(OS_VOLATILE uint32 *)(0xFFF82908U))
  #define OS_INTC_EIBD579 (*(OS_VOLATILE uint32 *)(0xFFF8290CU))
  #define OS_INTC_EIBD580 (*(OS_VOLATILE uint32 *)(0xFFF82910U))
  #define OS_INTC_EIBD581 (*(OS_VOLATILE uint32 *)(0xFFF82914U))
  #define OS_INTC_EIBD582 (*(OS_VOLATILE uint32 *)(0xFFF82918U))
  #define OS_INTC_EIBD583 (*(OS_VOLATILE uint32 *)(0xFFF8291CU))
  #define OS_INTC_EIBD584 (*(OS_VOLATILE uint32 *)(0xFFF82920U))
  #define OS_INTC_EIBD585 (*(OS_VOLATILE uint32 *)(0xFFF82924U))
  #define OS_INTC_EIBD586 (*(OS_VOLATILE uint32 *)(0xFFF82928U))
  #define OS_INTC_EIBD587 (*(OS_VOLATILE uint32 *)(0xFFF8292CU))
  #define OS_INTC_EIBD588 (*(OS_VOLATILE uint32 *)(0xFFF82930U))
  #define OS_INTC_EIBD589 (*(OS_VOLATILE uint32 *)(0xFFF82934U))
  #define OS_INTC_EIBD590 (*(OS_VOLATILE uint32 *)(0xFFF82938U))
  #define OS_INTC_EIBD591 (*(OS_VOLATILE uint32 *)(0xFFF8293CU))
  #define OS_INTC_EIBD592 (*(OS_VOLATILE uint32 *)(0xFFF82940U))
  #define OS_INTC_EIBD593 (*(OS_VOLATILE uint32 *)(0xFFF82944U))
  #define OS_INTC_EIBD594 (*(OS_VOLATILE uint32 *)(0xFFF82948U))
  #define OS_INTC_EIBD595 (*(OS_VOLATILE uint32 *)(0xFFF8294CU))
  #define OS_INTC_EIBD596 (*(OS_VOLATILE uint32 *)(0xFFF82950U))
  #define OS_INTC_EIBD597 (*(OS_VOLATILE uint32 *)(0xFFF82954U))
  #define OS_INTC_EIBD598 (*(OS_VOLATILE uint32 *)(0xFFF82958U))
  #define OS_INTC_EIBD599 (*(OS_VOLATILE uint32 *)(0xFFF8295CU))
  #define OS_INTC_EIBD600 (*(OS_VOLATILE uint32 *)(0xFFF82960U))
  #define OS_INTC_EIBD601 (*(OS_VOLATILE uint32 *)(0xFFF82964U))
  #define OS_INTC_EIBD602 (*(OS_VOLATILE uint32 *)(0xFFF82968U))
  #define OS_INTC_EIBD603 (*(OS_VOLATILE uint32 *)(0xFFF8296CU))
  #define OS_INTC_EIBD604 (*(OS_VOLATILE uint32 *)(0xFFF82970U))
  #define OS_INTC_EIBD605 (*(OS_VOLATILE uint32 *)(0xFFF82974U))
  #define OS_INTC_EIBD606 (*(OS_VOLATILE uint32 *)(0xFFF82978U))
  #define OS_INTC_EIBD607 (*(OS_VOLATILE uint32 *)(0xFFF8297CU))
  #define OS_INTC_EIBD608 (*(OS_VOLATILE uint32 *)(0xFFF82980U))
  #define OS_INTC_EIBD609 (*(OS_VOLATILE uint32 *)(0xFFF82984U))
  #define OS_INTC_EIBD610 (*(OS_VOLATILE uint32 *)(0xFFF82988U))
  #define OS_INTC_EIBD611 (*(OS_VOLATILE uint32 *)(0xFFF8298CU))
  #define OS_INTC_EIBD612 (*(OS_VOLATILE uint32 *)(0xFFF82990U))
  #define OS_INTC_EIBD613 (*(OS_VOLATILE uint32 *)(0xFFF82994U))
  #define OS_INTC_EIBD614 (*(OS_VOLATILE uint32 *)(0xFFF82998U))
  #define OS_INTC_EIBD615 (*(OS_VOLATILE uint32 *)(0xFFF8299CU))
  #define OS_INTC_EIBD616 (*(OS_VOLATILE uint32 *)(0xFFF829A0U))
  #define OS_INTC_EIBD617 (*(OS_VOLATILE uint32 *)(0xFFF829A4U))
  #define OS_INTC_EIBD618 (*(OS_VOLATILE uint32 *)(0xFFF829A8U))
  #define OS_INTC_EIBD619 (*(OS_VOLATILE uint32 *)(0xFFF829ACU))
  #define OS_INTC_EIBD620 (*(OS_VOLATILE uint32 *)(0xFFF829B0U))
  #define OS_INTC_EIBD621 (*(OS_VOLATILE uint32 *)(0xFFF829B4U))
  #define OS_INTC_EIBD622 (*(OS_VOLATILE uint32 *)(0xFFF829B8U))
  #define OS_INTC_EIBD623 (*(OS_VOLATILE uint32 *)(0xFFF829BCU))
  #define OS_INTC_EIBD624 (*(OS_VOLATILE uint32 *)(0xFFF829C0U))
  #define OS_INTC_EIBD625 (*(OS_VOLATILE uint32 *)(0xFFF829C4U))
  #define OS_INTC_EIBD626 (*(OS_VOLATILE uint32 *)(0xFFF829C8U))
  #define OS_INTC_EIBD627 (*(OS_VOLATILE uint32 *)(0xFFF829CCU))
  #define OS_INTC_EIBD628 (*(OS_VOLATILE uint32 *)(0xFFF829D0U))
  #define OS_INTC_EIBD629 (*(OS_VOLATILE uint32 *)(0xFFF829D4U))
  #define OS_INTC_EIBD630 (*(OS_VOLATILE uint32 *)(0xFFF829D8U))
  #define OS_INTC_EIBD631 (*(OS_VOLATILE uint32 *)(0xFFF829DCU))
  #define OS_INTC_EIBD632 (*(OS_VOLATILE uint32 *)(0xFFF829E0U))
  #define OS_INTC_EIBD633 (*(OS_VOLATILE uint32 *)(0xFFF829E4U))
  #define OS_INTC_EIBD634 (*(OS_VOLATILE uint32 *)(0xFFF829E8U))
  #define OS_INTC_EIBD635 (*(OS_VOLATILE uint32 *)(0xFFF829ECU))
  #define OS_INTC_EIBD636 (*(OS_VOLATILE uint32 *)(0xFFF829F0U))
  #define OS_INTC_EIBD637 (*(OS_VOLATILE uint32 *)(0xFFF829F4U))
  #define OS_INTC_EIBD638 (*(OS_VOLATILE uint32 *)(0xFFF829F8U))
  #define OS_INTC_EIBD639 (*(OS_VOLATILE uint32 *)(0xFFF829FCU))
  #define OS_INTC_EIBD640 (*(OS_VOLATILE uint32 *)(0xFFF82A00U))
  #define OS_INTC_EIBD641 (*(OS_VOLATILE uint32 *)(0xFFF82A04U))
  #define OS_INTC_EIBD642 (*(OS_VOLATILE uint32 *)(0xFFF82A08U))
  #define OS_INTC_EIBD643 (*(OS_VOLATILE uint32 *)(0xFFF82A0CU))
  #define OS_INTC_EIBD644 (*(OS_VOLATILE uint32 *)(0xFFF82A10U))
  #define OS_INTC_EIBD645 (*(OS_VOLATILE uint32 *)(0xFFF82A14U))
  #define OS_INTC_EIBD646 (*(OS_VOLATILE uint32 *)(0xFFF82A18U))
  #define OS_INTC_EIBD647 (*(OS_VOLATILE uint32 *)(0xFFF82A1CU))
  #define OS_INTC_EIBD648 (*(OS_VOLATILE uint32 *)(0xFFF82A20U))
  #define OS_INTC_EIBD649 (*(OS_VOLATILE uint32 *)(0xFFF82A24U))
  #define OS_INTC_EIBD650 (*(OS_VOLATILE uint32 *)(0xFFF82A28U))
  #define OS_INTC_EIBD651 (*(OS_VOLATILE uint32 *)(0xFFF82A2CU))
  #define OS_INTC_EIBD652 (*(OS_VOLATILE uint32 *)(0xFFF82A30U))
  #define OS_INTC_EIBD653 (*(OS_VOLATILE uint32 *)(0xFFF82A34U))
  #define OS_INTC_EIBD654 (*(OS_VOLATILE uint32 *)(0xFFF82A38U))
  #define OS_INTC_EIBD655 (*(OS_VOLATILE uint32 *)(0xFFF82A3CU))
  #define OS_INTC_EIBD656 (*(OS_VOLATILE uint32 *)(0xFFF82A40U))
  #define OS_INTC_EIBD657 (*(OS_VOLATILE uint32 *)(0xFFF82A44U))
  #define OS_INTC_EIBD658 (*(OS_VOLATILE uint32 *)(0xFFF82A48U))
  #define OS_INTC_EIBD659 (*(OS_VOLATILE uint32 *)(0xFFF82A4CU))
  #define OS_INTC_EIBD660 (*(OS_VOLATILE uint32 *)(0xFFF82A50U))
  #define OS_INTC_EIBD661 (*(OS_VOLATILE uint32 *)(0xFFF82A54U))
  #define OS_INTC_EIBD662 (*(OS_VOLATILE uint32 *)(0xFFF82A58U))
  #define OS_INTC_EIBD663 (*(OS_VOLATILE uint32 *)(0xFFF82A5CU))
  #define OS_INTC_EIBD664 (*(OS_VOLATILE uint32 *)(0xFFF82A60U))
  #define OS_INTC_EIBD665 (*(OS_VOLATILE uint32 *)(0xFFF82A64U))
  #define OS_INTC_EIBD666 (*(OS_VOLATILE uint32 *)(0xFFF82A68U))
  #define OS_INTC_EIBD667 (*(OS_VOLATILE uint32 *)(0xFFF82A6CU))
  #define OS_INTC_EIBD668 (*(OS_VOLATILE uint32 *)(0xFFF82A70U))
  #define OS_INTC_EIBD669 (*(OS_VOLATILE uint32 *)(0xFFF82A74U))
  #define OS_INTC_EIBD670 (*(OS_VOLATILE uint32 *)(0xFFF82A78U))
  #define OS_INTC_EIBD671 (*(OS_VOLATILE uint32 *)(0xFFF82A7CU))
  #define OS_INTC_EIBD672 (*(OS_VOLATILE uint32 *)(0xFFF82A80U))
  #define OS_INTC_EIBD673 (*(OS_VOLATILE uint32 *)(0xFFF82A84U))
  #define OS_INTC_EIBD674 (*(OS_VOLATILE uint32 *)(0xFFF82A88U))
  #define OS_INTC_EIBD675 (*(OS_VOLATILE uint32 *)(0xFFF82A8CU))
  #define OS_INTC_EIBD676 (*(OS_VOLATILE uint32 *)(0xFFF82A90U))
  #define OS_INTC_EIBD677 (*(OS_VOLATILE uint32 *)(0xFFF82A94U))
  #define OS_INTC_EIBD678 (*(OS_VOLATILE uint32 *)(0xFFF82A98U))
  #define OS_INTC_EIBD679 (*(OS_VOLATILE uint32 *)(0xFFF82A9CU))
  #define OS_INTC_EIBD680 (*(OS_VOLATILE uint32 *)(0xFFF82AA0U))
  #define OS_INTC_EIBD681 (*(OS_VOLATILE uint32 *)(0xFFF82AA4U))
  #define OS_INTC_EIBD682 (*(OS_VOLATILE uint32 *)(0xFFF82AA8U))
  #define OS_INTC_EIBD683 (*(OS_VOLATILE uint32 *)(0xFFF82AACU))
  #define OS_INTC_EIBD684 (*(OS_VOLATILE uint32 *)(0xFFF82AB0U))
  #define OS_INTC_EIBD685 (*(OS_VOLATILE uint32 *)(0xFFF82AB4U))
  #define OS_INTC_EIBD686 (*(OS_VOLATILE uint32 *)(0xFFF82AB8U))
  #define OS_INTC_EIBD687 (*(OS_VOLATILE uint32 *)(0xFFF82ABCU))
  #define OS_INTC_EIBD688 (*(OS_VOLATILE uint32 *)(0xFFF82AC0U))
  #define OS_INTC_EIBD689 (*(OS_VOLATILE uint32 *)(0xFFF82AC4U))
  #define OS_INTC_EIBD690 (*(OS_VOLATILE uint32 *)(0xFFF82AC8U))
  #define OS_INTC_EIBD691 (*(OS_VOLATILE uint32 *)(0xFFF82ACCU))
  #define OS_INTC_EIBD692 (*(OS_VOLATILE uint32 *)(0xFFF82AD0U))
  #define OS_INTC_EIBD693 (*(OS_VOLATILE uint32 *)(0xFFF82AD4U))
  #define OS_INTC_EIBD694 (*(OS_VOLATILE uint32 *)(0xFFF82AD8U))
  #define OS_INTC_EIBD695 (*(OS_VOLATILE uint32 *)(0xFFF82ADCU))
  #define OS_INTC_EIBD696 (*(OS_VOLATILE uint32 *)(0xFFF82AE0U))
  #define OS_INTC_EIBD697 (*(OS_VOLATILE uint32 *)(0xFFF82AE4U))
  #define OS_INTC_EIBD698 (*(OS_VOLATILE uint32 *)(0xFFF82AE8U))
  #define OS_INTC_EIBD699 (*(OS_VOLATILE uint32 *)(0xFFF82AECU))
  #define OS_INTC_EIBD700 (*(OS_VOLATILE uint32 *)(0xFFF82AF0U))
  #define OS_INTC_EIBD701 (*(OS_VOLATILE uint32 *)(0xFFF82AF4U))
  #define OS_INTC_EIBD702 (*(OS_VOLATILE uint32 *)(0xFFF82AF8U))
  #define OS_INTC_EIBD703 (*(OS_VOLATILE uint32 *)(0xFFF82AFCU))
  #define OS_INTC_EIBD704 (*(OS_VOLATILE uint32 *)(0xFFF82B00U))
  #define OS_INTC_EIBD705 (*(OS_VOLATILE uint32 *)(0xFFF82B04U))
  #define OS_INTC_EIBD706 (*(OS_VOLATILE uint32 *)(0xFFF82B08U))
  #define OS_INTC_EIBD707 (*(OS_VOLATILE uint32 *)(0xFFF82B0CU))
  #define OS_INTC_EIBD708 (*(OS_VOLATILE uint32 *)(0xFFF82B10U))
  #define OS_INTC_EIBD709 (*(OS_VOLATILE uint32 *)(0xFFF82B14U))
  #define OS_INTC_EIBD710 (*(OS_VOLATILE uint32 *)(0xFFF82B18U))
  #define OS_INTC_EIBD711 (*(OS_VOLATILE uint32 *)(0xFFF82B1CU))
  #define OS_INTC_EIBD712 (*(OS_VOLATILE uint32 *)(0xFFF82B20U))
  #define OS_INTC_EIBD713 (*(OS_VOLATILE uint32 *)(0xFFF82B24U))
  #define OS_INTC_EIBD714 (*(OS_VOLATILE uint32 *)(0xFFF82B28U))
  #define OS_INTC_EIBD715 (*(OS_VOLATILE uint32 *)(0xFFF82B2CU))
  #define OS_INTC_EIBD716 (*(OS_VOLATILE uint32 *)(0xFFF82B30U))
  #define OS_INTC_EIBD717 (*(OS_VOLATILE uint32 *)(0xFFF82B34U))
  #define OS_INTC_EIBD718 (*(OS_VOLATILE uint32 *)(0xFFF82B38U))
  #define OS_INTC_EIBD719 (*(OS_VOLATILE uint32 *)(0xFFF82B3CU))
  #define OS_INTC_EIBD720 (*(OS_VOLATILE uint32 *)(0xFFF82B40U))
  #define OS_INTC_EIBD721 (*(OS_VOLATILE uint32 *)(0xFFF82B44U))
  #define OS_INTC_EIBD722 (*(OS_VOLATILE uint32 *)(0xFFF82B48U))
  #define OS_INTC_EIBD723 (*(OS_VOLATILE uint32 *)(0xFFF82B4CU))
  #define OS_INTC_EIBD724 (*(OS_VOLATILE uint32 *)(0xFFF82B50U))
  #define OS_INTC_EIBD725 (*(OS_VOLATILE uint32 *)(0xFFF82B54U))
  #define OS_INTC_EIBD726 (*(OS_VOLATILE uint32 *)(0xFFF82B58U))
  #define OS_INTC_EIBD727 (*(OS_VOLATILE uint32 *)(0xFFF82B5CU))
  #define OS_INTC_EIBD728 (*(OS_VOLATILE uint32 *)(0xFFF82B60U))
  #define OS_INTC_EIBD729 (*(OS_VOLATILE uint32 *)(0xFFF82B64U))
  #define OS_INTC_EIBD730 (*(OS_VOLATILE uint32 *)(0xFFF82B68U))
  #define OS_INTC_EIBD731 (*(OS_VOLATILE uint32 *)(0xFFF82B6CU))
  #define OS_INTC_EIBD732 (*(OS_VOLATILE uint32 *)(0xFFF82B70U))
  #define OS_INTC_EIBD733 (*(OS_VOLATILE uint32 *)(0xFFF82B74U))
  #define OS_INTC_EIBD734 (*(OS_VOLATILE uint32 *)(0xFFF82B78U))
  #define OS_INTC_EIBD735 (*(OS_VOLATILE uint32 *)(0xFFF82B7CU))
  #define OS_INTC_EIBD736 (*(OS_VOLATILE uint32 *)(0xFFF82B80U))
  #define OS_INTC_EIBD737 (*(OS_VOLATILE uint32 *)(0xFFF82B84U))
  #define OS_INTC_EIBD738 (*(OS_VOLATILE uint32 *)(0xFFF82B88U))
  #define OS_INTC_EIBD739 (*(OS_VOLATILE uint32 *)(0xFFF82B8CU))
  #define OS_INTC_EIBD740 (*(OS_VOLATILE uint32 *)(0xFFF82B90U))
  #define OS_INTC_EIBD741 (*(OS_VOLATILE uint32 *)(0xFFF82B94U))
  #define OS_INTC_EIBD742 (*(OS_VOLATILE uint32 *)(0xFFF82B98U))
  #define OS_INTC_EIBD743 (*(OS_VOLATILE uint32 *)(0xFFF82B9CU))
  #define OS_INTC_EIBD744 (*(OS_VOLATILE uint32 *)(0xFFF82BA0U))
  #define OS_INTC_EIBD745 (*(OS_VOLATILE uint32 *)(0xFFF82BA4U))
  #define OS_INTC_EIBD746 (*(OS_VOLATILE uint32 *)(0xFFF82BA8U))
  #define OS_INTC_EIBD747 (*(OS_VOLATILE uint32 *)(0xFFF82BACU))
  #define OS_INTC_EIBD748 (*(OS_VOLATILE uint32 *)(0xFFF82BB0U))
  #define OS_INTC_EIBD749 (*(OS_VOLATILE uint32 *)(0xFFF82BB4U))
  #define OS_INTC_EIBD750 (*(OS_VOLATILE uint32 *)(0xFFF82BB8U))
  #define OS_INTC_EIBD751 (*(OS_VOLATILE uint32 *)(0xFFF82BBCU))
  #define OS_INTC_EIBD752 (*(OS_VOLATILE uint32 *)(0xFFF82BC0U))
  #define OS_INTC_EIBD753 (*(OS_VOLATILE uint32 *)(0xFFF82BC4U))
  #define OS_INTC_EIBD754 (*(OS_VOLATILE uint32 *)(0xFFF82BC8U))
  #define OS_INTC_EIBD755 (*(OS_VOLATILE uint32 *)(0xFFF82BCCU))
  #define OS_INTC_EIBD756 (*(OS_VOLATILE uint32 *)(0xFFF82BD0U))
  #define OS_INTC_EIBD757 (*(OS_VOLATILE uint32 *)(0xFFF82BD4U))
  #define OS_INTC_EIBD758 (*(OS_VOLATILE uint32 *)(0xFFF82BD8U))
  #define OS_INTC_EIBD759 (*(OS_VOLATILE uint32 *)(0xFFF82BDCU))
  #define OS_INTC_EIBD760 (*(OS_VOLATILE uint32 *)(0xFFF82BE0U))
  #define OS_INTC_EIBD761 (*(OS_VOLATILE uint32 *)(0xFFF82BE4U))
  #define OS_INTC_EIBD762 (*(OS_VOLATILE uint32 *)(0xFFF82BE8U))
  #define OS_INTC_EIBD763 (*(OS_VOLATILE uint32 *)(0xFFF82BECU))
  #define OS_INTC_EIBD764 (*(OS_VOLATILE uint32 *)(0xFFF82BF0U))
  #define OS_INTC_EIBD765 (*(OS_VOLATILE uint32 *)(0xFFF82BF4U))
  #define OS_INTC_EIBD766 (*(OS_VOLATILE uint32 *)(0xFFF82BF8U))
  #define OS_INTC_EIBD767 (*(OS_VOLATILE uint32 *)(0xFFF82BFCU))
#endif /* _lint */

#define OS_ICR_EIMK 7 /* The bit position of the MXxx bit, intrinsic __SET1/__CLR1 expects a signed int */
#define OS_EIC_EIMK (0x0080U)
#define OS_EIC_EITB (0x0040U)
#define OS_EIC_EIRF (0x1000U)
#define OS_ICR_EIRF_MASK (0xEFFFU)

/* [MISRA 2012 Rule 1.1] */ /*lint -estring(9023, CAT1_ISR) */
/* CAT1_ISR */
/* [MISRA 2012 Rule 21.7] */ /*lint -estring(9024, CAT1_ISR) */
/* CAT1_ISR */
#define CAT1_ISR(x)\
__inline static void Os_inline_##x(void);\
void x(void) {\
  OS_VOLATILE uint32 prev_isr = OS_CAT1_TRACKER_##x;\
  OS_CAT1_TRACKER_##x = OS_CAT1_ID_##x;\
  Os_inline_##x();\
  OS_CAT1_TRACKER_##x = prev_isr;\
}\
__inline static void Os_inline_##x(void)
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(StatusType, OS_CALLOUT_CODE) Os_Cbk_StartCore(uint16 CoreID);
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
extern FUNC(void, OS_CODE) Os_AwaitStartup(void);
extern FUNC(void, OS_CODE) Os_CacheCoreID(void);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern OS_VOLATILE VAR(uint32, OS_VAR_NO_INIT) Os_RunningCat1ISR0;
extern OS_VOLATILE VAR(uint32, OS_VAR_NO_INIT) Os_RunningCat1ISR1;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif
typedef sint32 Os_jmp_buf[14];
extern sint32 Os_setjmp(Os_jmp_buf env);
extern __attribute__((noinline,noreturn)) void Os_longjmp(Os_jmp_buf env);


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
/* Lint/MISRA checking has a problem with the compiler intrinsic functions so
 * obscure this when lint checking */
#if defined(_lint) || defined(__cplusplus)
extern Os_StackValueType Os_GetSP(void);
extern void Os_MoveSP(Os_StackValueType value);
#else
Os_StackValueType Os_GetSP(void);
__asm Os_StackValueType Os_GetSP(void)
{
%reg
  mov r3, r10
%con
  mov  r3, r10
%mem
  mov  r3, r10
}
void Os_MoveSP(Os_StackValueType value);
__asm void Os_MoveSP(Os_StackValueType value)
{
%reg value
  add value, r3
%con value
  add value, r3
}
#endif /* _lint, __cplusplus */

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
#define OS_PSW_REGID (5)
#define OS_PSW_SELID (0)
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
typedef unsigned int TickType; /* [$UKS 276] */
typedef signed int SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType; /* [$UKS 277] */
typedef uint32 PhysicalTimeType; /* [$UKS  842] */
typedef unsigned int Os_StopwatchTickType; /* [$UKS 535] */
typedef P2VAR(Os_StopwatchTickType, TYPEDEF, OS_VAR) Os_StopwatchTickRefType;
typedef signed int Os_TimeLimitType;

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
#define OS_PLMR_REGID (14)
#define OS_PLMR_SELID (2)
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
#define StartOS(x) {if (Os_StartOS(x)) {while(Os_Cbk_Idle()) {} /* [$UKS 161] */; for(;;) {} /* [$UKS 16] */}}
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
#define GetCoreID() ((CoreIdType)/*lint --e(9034) [MISRA 2012 Dir 10.3] Depends on CoreIdType size */OS_STSR(OS_PEID_REGID, OS_PEID_SELID))  /* [$UKS 1619] [$UKS 1620] [$UKS 1621] */
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
#define Os_ErrorInformation (Os_const_coreconfiguration[OS_STSR(OS_PEID_REGID, OS_PEID_SELID)].controlled->ErrorInformation)
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
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskStart(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_TaskEnd(TaskType task);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISRStart(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_CrosscoreISREnd(CoreIdType core_id);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISRStart(ISRType isr);
extern FUNC(void, OS_CALLOUT_CODE) Os_Cbk_ISREnd(ISRType isr);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
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
