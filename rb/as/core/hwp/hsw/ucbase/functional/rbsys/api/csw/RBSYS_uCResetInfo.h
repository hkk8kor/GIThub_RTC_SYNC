#ifndef RBSYS_UCRESETINFO_H__
#define RBSYS_UCRESETINFO_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_uCResetInfo.h
 * @brief APIs to get Reset Flags and Reset Sources
 *
 * These APIs can be used to detect Resets and identify Reset Sources.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

#include "RBSYS_uCRegisters.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


/* uC reset flags */
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_RESET_FLAG_POWERON                  ((uint32)1 << 0)
  #define RBSYS_RESET_FLAG_TERMINAL                 ((uint32)1 << 1)
  #define RBSYS_RESET_FLAG_CVM                      ((uint32)1 << 2)
  #define RBSYS_RESET_FLAG_SW_SYSTEM_0              ((uint32)1 << 3)
  #define RBSYS_RESET_FLAG_ECM_SYSTEM               ((uint32)1 << 5)
  #define RBSYS_RESET_FLAG_SW_APPLICATION_0         ((uint32)1 << 7)
  #define RBSYS_RESET_FLAG_ECM_APPLICATION          ((uint32)1 << 9)
  #define RBSYS_RESET_FLAG_HW_BIST                  ((uint32)1 << 10)
#elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
  #define RBSYS_RESET_FLAG_POWERON                  ((uint32)1 << 0)
  #define RBSYS_RESET_FLAG_TERMINAL                 ((uint32)1 << 2)
  #define RBSYS_RESET_FLAG_VMON                     ((uint32)1 << 3)
  #define RBSYS_RESET_FLAG_SW_SYSTEM_0              ((uint32)1 << 4)
  #define RBSYS_RESET_FLAG_ECM_SYSTEM               ((uint32)1 << 6)
  #define RBSYS_RESET_FLAG_WDTBA                    ((uint32)1 << 7)
  #define RBSYS_RESET_FLAG_SW_APPLICATION_0         ((uint32)1 << 8)
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #define RBSYS_RESET_FLAG_ECM_APPLICATION          ((uint32)1 << 10)
  #endif
  #define RBSYS_RESET_FLAG_HW_BIST_F0               ((uint32)1 << 12)
  #define RBSYS_RESET_FLAG_HW_BIST_F1               ((uint32)1 << 13)
  #define RBSYS_RESET_FLAG_HW_BIST_F2               ((uint32)1 << 14)
  #define RBSYS_RESET_FLAG_DeepSTOP                 ((uint32)1 << 15)
  #define RBSYS_RESET_FLAG_ICUM_SW_SYSTEM           ((uint32)1 << 16)
  #define RBSYS_RESET_FLAG_ICUM_SW_APPLICATION      ((uint32)1 << 17)
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  /* destructive resets */
  #define RBSYS_RESET_DEST_FLAG_ICUM_VMON                ((uint32)1 << 29)
  #define RBSYS_RESET_DEST_FLAG_DOMAIN2_VMON             ((uint32)1 << 27)
  #define RBSYS_RESET_DEST_FLAG_DOMAIN1_VMON             ((uint32)1 << 26)
  #define RBSYS_RESET_DEST_FLAG_DOMAIN0_VMON             ((uint32)1 << 25)
  #define RBSYS_RESET_DEST_FLAG_DOMAINPER_VMON           ((uint32)1 << 24)
  #define RBSYS_RESET_DEST_FLAG_ICUM                     ((uint32)1 << 15)
  // #define RBSYS_RESET_DEST_FLAG_SSCM                     ((uint32)1 << 14)
  #define RBSYS_RESET_DEST_FLAG_JTAG                     ((uint32)1 << 10)
  #define RBSYS_RESET_DEST_FLAG_HW_BIST_HARDFAULT        ((uint32)1 << 5)
  #define RBSYS_RESET_DEST_FLAG_SW_RESET                 ((uint32)1 << 3)
  #define RBSYS_RESET_DEST_FLAG_RESETPIN_B               ((uint32)1 << 2)
  #define RBSYS_RESET_DEST_FLAG_RESETPIN_A               ((uint32)1 << 1)
  #define RBSYS_RESET_DEST_FLAG_POWERON                  ((uint32)1 << 0)
  /* functional resets */
  #define RBSYS_RESET_FUNC_FLAG_FCCU_SAFE                ((uint32)1 << 7)
  #define RBSYS_RESET_FUNC_FLAG_SW_RESET                 ((uint32)1 << 3)
  #define RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE         ((uint32)1 << 2)
  #define RBSYS_RESET_FUNC_FLAG_RESETPIN_B               ((uint32)1 << 0)
#else
  #error ("Reset Flag definition is missing for this uCFamily")
#endif


static inline uint32 RBSYS_GetCurrentResetFlagsForMM6(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return RBSYS_RESF;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return MC_RGM_PER.FES; //< todo: maybe report DES or mix of both?
  #endif
}

/**
  * @brief Software reset flag of the uC
  *
  * Following flags of the Reset Factor register are evaluated to detect if a "Software" reset has occurred:
  *        Renesas P1x: RESF.SRESF2  => Software System Reset
  *                     RESF.ARESF0  => Software Application Reset
  *
  *        Renesas U2A: RESF.SRES2F0 => Software System Reset
  *                     RESF.ARESF0  => Software Application Reset
  *
  *        STM Stellar: RGM_PER.DES.SOFT_DEST => Software System Reset (Phase 0 Destructive Reset)
  *                     RGM_PER.FES.SOFT_FUNC => Software Application Reset (Phase 1 Functional Reset)
  *
  * Hint1: Software reset flags will normally not be cleared by software, so if the system has once seen
  *        a software reset in this power cycle, the return is always TRUE. The only exception is a Terminal reset,
  *        which means in case of a Terminal reset (e.g. undervoltage detected by ASIC) the software reset flags are cleared once
  *        to ensure the same start-up sequence as in case of a real Power-On reset (see Defect 181338)!
  *
  * Hint2: Take care that bootblock in Gen9.3 must be left always via software reset to application software! This is
  *        ensured within RBSYS_Bootblock_Startup.c: Only in case of an SW reset the jump to the application is possible!
  *
  * Hint3: IsSystemReset-Flag will be cleared during startup.
  *
  * Hint4: These functions must be always inlined because they are used during RBSYS_StartupPreOSPhase0 when the stack is not yet
  *        initialized!
  *
  * @returns TRUE if the system comes out of the specific reset, otherwise FALSE.
  */
__attribute__((always_inline)) static inline boolean RBSYS_isSWSystemReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return ( (RBSYS_RESF & RBSYS_RESET_FLAG_SW_SYSTEM_0) != 0u);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return ( (MC_RGM_PER.DES & RBSYS_RESET_DEST_FLAG_SW_RESET) != 0u);
  #endif
}

__attribute__((always_inline)) static inline boolean RBSYS_isSWApplicationReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return ( (RBSYS_RESF & RBSYS_RESET_FLAG_SW_APPLICATION_0) != 0u);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return ( (MC_RGM_PER.FES & RBSYS_RESET_FUNC_FLAG_SW_RESET) != 0u);
  #endif
}


/**
  * @brief BIST reset flag of the uC
  *
  * Following flags of the RESF (Reset Factor) register are evaluated to detect if a "BIST" reset has occurred:
  *        BIST reset flag
  *
  * Hint: BIST reset flag will be cleared in Control Mode only (not BaseOS) after HW BIST evaluation.
  *       So this flag will be used after any kind of reset to verify if HW BIST evaluation during start-up is required.
  *
  * @returns TRUE if the system comes out of BIST reset, otherwise FALSE.
  */
static inline boolean RBSYS_isBISTReset(void)
{
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_HW_BIST) != 0u);
  #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    // Ignore other HW_BIST flags: DeepStop-HWBist Flags shall not have any influence on isBistReset() because we cannot face a DeepStop reset
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_HW_BIST_F0) != 0u);
  #else
    return ((MC_RGM_PER.FES & RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE) != 0u);
  #endif
}

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  /**
    * @brief ECM reset flags of the uC
    *
    * Following flags of the RESF (Reset Factor) register are evaluated to detect if an "ECM" reset has occurred:
    *        ECM Application Reset Flag
    *        ECM System Reset Flag
    *
    * Hint: ECM reset flags will currently only be used in bootblock and have to be cleared at the controlled ending of the bootblock
    *       before going to FSW (so Control Mode in FSW will never see them)
    *
    * @returns TRUE if the system comes out of an ECM reset, otherwise FALSE.
    */
  static inline boolean RBSYS_isECMReset(void)
  {
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      return ((RBSYS_RESF & (RBSYS_RESET_FLAG_ECM_APPLICATION | RBSYS_RESET_FLAG_ECM_SYSTEM)) != 0u);
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      return ((RBSYS_RESF & RBSYS_RESET_FLAG_ECM_SYSTEM) != 0u);
    #endif
  }
#endif

/**
  * @brief Get Current Power-On reset flag of the uC
  *
  *  Following flags of the Reset Factor register are evaluated to detect if a "Power-On" reset has occurred:
  *        Renesas P1x / U2A: RESF.PRESF
  *        STM Stellar: RGM_PER.DES.F_POR
  *
  * Hint: Power-On reset flag will be cleared in Control Mode only (not BaseOS) after executing uC Safety tests.
  *       So this flag will be used after any kind of reset (e.g. SW reset from BaseOS to Control Mode) to evaluate
  *       if uC Safety tests have to be executed. Cleared means that uC safety tests are still executed once within this power cycle!
  *
  * ATTENTION: To detect a Power On Reset during Init-Task / Cyclic-Tasks, use RBSYS_HasPowerOnResetOccurred!
  *
  * @returns TRUE if the system comes out of Power-On reset, otherwise FALSE.
  */
static inline boolean RBSYS_isPowerOnReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_POWERON) != 0u);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return ((MC_RGM_PER.DES & RBSYS_RESET_DEST_FLAG_POWERON) != 0u);
  #endif
}

/**
  * @brief API to get if a Power Cycle has occurred
  *
  * Attention: This will return TRUE if the last Reset has been a PowerOn Reset.
  *            Once any other kind of reset occurs, it will return FALSE again.
  *
  * This interface can be used at ANY time after Init-Task has been started.
  *
  * @returns TRUE if the system comes out of PowerOn Reset, otherwise FALSE.
  */
extern boolean RBSYS_HasPowerOnResetOccurred(void);


/**
  * @brief Terminal reset flag of the uC
  *
  * Following flags of the RESF (Reset Factor) register are evaluated to detect if a "Terminal" reset has occurred:
  *        Terminal reset flag
  *
  * Attention: Shall only be used by RBSYS due to zeroing of the flag during startup!!
  *            -> see defect 2023282
  *
  * Hint: Terminal reset flag will be cleared within the bootblock start-up code. This must be done to ensure
  *       the same start-up sequence in case of a Terminal reset (e.g. undervoltage detected by ASIC)
  *       as in case of a real Power-On reset (see Defect 181338)!
  *
  * @returns TRUE if the system comes out of Terminal reset, otherwise FALSE.
  */
__attribute__((always_inline)) static inline boolean RBSYS_isTerminalReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_TERMINAL) != 0u);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    return ((MC_RGM_PER.DES & RBSYS_RESET_DEST_FLAG_RESETPIN_A) != 0);
  #endif
}



/** @returns TRUE if the a Reset occured recently (System or Application)
    @brief Not used RBSYS-internally anymore! */
__attribute__((always_inline)) static inline boolean RBSYS_isSWReset(void)
{
  return (RBSYS_isSWApplicationReset() || RBSYS_isSWSystemReset());
}

/** @returns TRUE if the last Reset was an Application Reset (not a System Reset) */
__attribute__((always_inline)) static inline boolean RBSYS_isSWResetByApplicationReset(void)
{
  // no need to check for Software System Reset flag as it will always be cleared before an Application Reset is triggered
  // attention: Terminal Reset can occur at any point in time and is cleared before an Application Reset is triggered
  // attention: System Reset has to be considered because ReprogDriver is always resetting with SW System Reset
  return (RBSYS_isSWApplicationReset() && !RBSYS_isSWSystemReset());
}


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /**
    * @brief CVM (Core Voltage Monitor) reset flag of the uC
    *
    * Following flags of the RESF (Reset Factor) register are evaluated to detect if a "CVM" reset has occurred:
    *        CVM reset flag
    *
    * Hint: CVM reset flag will not be cleared by software, so if the system has once seen
    *       a CVM reset in this power cycle, the return is always TRUE.
    *
    * @returns TRUE if the system comes out of CVM reset, otherwise FALSE.
    */
  static inline boolean RBSYS_isCVMReset(void)
  {
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_CVM) != 0u);
  }
#elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  /**
    * @brief VMON (Voltage Monitor) reset flag of the uC
    *
    * Following flags of the RESF (Reset Factor) register are evaluated to detect if a "VMON" reset has occurred:
    *        VMON reset flag
    *
    * Hint: VMON reset flag will not be cleared by software, so if the system has once seen
    *       a VMON reset in this power cycle, the return is always TRUE.
    *
    * @returns TRUE if the system comes out of VMON reset, otherwise FALSE.
    */
  static inline boolean RBSYS_isVMONReset(void)
  {
    return ((RBSYS_RESF & RBSYS_RESET_FLAG_VMON) != 0u);
  }
#endif


/** @} */
/* End ingroup RBSYS */

#endif

