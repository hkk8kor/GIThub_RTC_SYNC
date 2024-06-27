#ifndef RBSYS_FPU_H__
#define RBSYS_FPU_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Floating Point Unit
 *
 * All CC CUBE devices are equipped with a HW Floating Point Unit (FPU).
 * Therefore this module is responsible for whole FPU configuration!
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);



#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  #define   RBSYS_FPSR_FN          ((uint32) 1 << 23)   // flush to nearest mode
  #define   RBSYS_FPSR_IF          ((uint32) 1 << 22)   // input operand was flushed status
  #define   RBSYS_FPSR_PEM         ((uint32) 1 << 21)   // precise exception
  #define   RBSYS_FPSR_RM          ((uint32) 1 << 18)   // rounding mode
  #define   RBSYS_FPSR_FS          ((uint32) 1 << 17)   // flushing abnormal numbers


  /* Meaning of exception bits:
   * E bit = 1: software emulation required
   * V bit = 1: invalid operation
   * Z bit = 1: division by zero
   * O bit = 1: overflow
   * U bit = 1: underflow
   * I bit = 1: inexact operation
   */
  #define   RBSYS_FPSR_XC               (10)   // cause exception bits          (E, V, Z, O, U, I)
  #define   RBSYS_FPSR_XE                (5)   // enable exception bits            (V, Z, O, U, I)
  #define   RBSYS_FPSR_XP                (0)   // preservation exception bits      (V, Z, O, U, I)

#elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

  #define RBSYS_FPSCR   0x1u
  #define RBSYS_FPEXC   0x8u

  #define RBSYS_FPSCR_AHP     ((uint32) 1 << 26)  // Alternative Half-Precision control bit
  #define RBSYS_FPSCR_DN      ((uint32) 1 << 25)  // Default NaN mode control bit
  #define RBSYS_FPSCR_FZ      ((uint32) 1 << 24)  // Flush-to-zero mode control bit
  #define RBSYS_FPSCR_RMode   ((uint32) 3 << 22)  // Rounding Mode control field

#endif

/**
 * @brief Initialization and activation of Hardware Floating Point Unit
 *
 * Renesas P1x-C and U2A supports single-precision (32-bit) and double-precision (64-bit) FPU.
 * Both controller families have implemented the IEEE754-2008 Standard.
 *
 * ST Stellar support single-precision (32-bit) and double-precision (64-bit) FPU.
 * TODO: which precision is supported on P2/P3? How are the FPU and NEON/SIMD separated?
 * The controller family has implemented the IEEE754-2008 Standard.
 *
 * CC-AS preferred setting:
 *
 * Renesas RH850:
 *    FN  = 0 (disable flush-to-nearest mode for subnormal numbers in rounding mode RN, neccessary as this does not work correctly, see Renesas HW Erratum RB128)
 *    IF  = 0 (status bit cleared)
 *    PEM = 1 (handle exceptions as precise => tests show no improvement when using imprecise exceptions)
 *            Third party SW can also use float, therefore it's important to handle the FPU exceptions always precise
 *    RM  = 0 (RN => round nearest)
 *    FS  = 1 (enable subnormal numbers => exception ignored)
 *    XC  = 0 (status bits cleared)
 *    XE  = V, Z  ==> I set to 0 due to flushing subnormal numbers, precision of rounded results (increment by 0.13 within a loop)
 *    XP  = 0 (status bits cleared)
 * STM Stellar:
 *    AHP   = 0 (IEEE half-precision format selected)(same half precision format as RH850 (non configurable))
 *    DN    = 1 (Any operation involving one or more NaNs returns the Default NaN.)
 *              (TODO: TBC: Same behavior as RH850, but different NaNs (non configurable))
 *    FZ    = 0 (Flush-to-zero mode disabled to be IEEE754 compliant)(TODO: TBC: behavior is different from RH850 setting, see FS bit)
 *    RMode = 0 (Round to Nearest (RN) mode)(same behavior as RH850 setting, see RM bits)
 *  TODO: TBC all Stellar settings (Task 2296075)
 *  TODO: RBSYS_FPSR_PEM does not exist in U2A? But must be set to 1 anyway?
 *
 *
 * FPU compiler option:
 *
 * MTC >= 10.0.4.0 uses "-fsingle", which means HW FPU for single-precision but SW lib for double-precision
 *                 ("-fhard" option removed from latest GHS compiler manual (2013.5.5))
 * MTC >= 10.0.7.0 uses "-fhard" instead of "-fsingle" which means HW support for single- and double-precision
 *                 ("-fhard" option was wrongly removed from GHS manual; option still available and preferred option from GHS for CC-CUBE)
 *                  => see architecture protocol referred in ALM task 1535
 *
 * In general not allowed FPU compiler setting for CC-AS will be "-floatsingle"
 *                    -> implicit conversion to single-precision deviates from c-standard
 *                    -> CC-AS code does not require double-precision, but maybe third party software
 *
 * @return void
 */
static inline void RBSYS_InitFPU(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    unsigned int psw,fpsr;

    // initialize FPU co-processor
    psw = RBSYS_STSR(5,0);
    psw |= 0x00010000u;                   // set PSW.CU0 (bit16) to 1
    RBSYS_LDSR(5,0,psw);

    // set CC-AS specific FPU settings
    fpsr = ((0x18u << RBSYS_FPSR_XE) | RBSYS_FPSR_FS | RBSYS_FPSR_PEM);
    RBSYS_LDSR(6,0,fpsr);

    // introduce sync instruction after updating FPU related registers as requested within the UM (see chapter "System Register Hazards")
    RBSYS_SYNCP();
  #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

    unsigned int fpscr, fpexc, value;

    /* Must be called by every core */
    // allow FPU access for EL0 and EL1 via system register CPACR
    value = RBSYS_MRC(15, 0, 1, 0, 2);
    value |= (0xFu << 20u);   // set 11b to cp10 and cp11
    RBSYS_MCR(15, 0, value, 1, 0, 2);

    /** TODO:
     * See ARMv8 Archtiecture RM F6.1.126 VMSR:
     * Must fpexc be written in user mode?
     */

    /* Init described in ARM Cortex R52 RM 6.1.2 Floating-point Unit. */

    /** TODO: why is it enabled on reset in the sim?
     * according to 15.5 Register summary in R52 RM it should be disabled */
    /* enable FPU: set enable bit (VECITR is RES1) */
    fpexc = (0x1u << 30) | (0x7u << 8);
    RBSYS_VMSR(RBSYS_FPEXC, fpexc);


    // set CC-AS specific FPU settings
    // Hint: FPEXC.EN must be set to 1 to access this register, see
    // ARMv8 Archtiecture G1.19.2 Enabling Advanced SIMD and floating-point support
    // AHP = 0, DN = 1, FZ = 0, RMODE = 0
    fpscr = (RBSYS_FPSCR_DN);
    RBSYS_VMSR(RBSYS_FPSCR, fpscr);



    // TODO, see Task 2296075
    #warning "FPU parameters for ST not finalized"

  #endif
}



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
