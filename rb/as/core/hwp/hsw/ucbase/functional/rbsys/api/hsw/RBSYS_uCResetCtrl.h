#ifndef RBSYS_UCRESETCTRL_H__
#define RBSYS_UCRESETCTRL_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file  RBSYS_uCResetCtrl.h
 * @brief Triggering of an immediate uC SW Reset
 *
 * This interface handles only an immediate low level uC reset, which is allowed to be called only in case
 * of serious "not recoverable" system faults or within very special circumstances (BaseOS).
 *
 * Official interface RB_SWReset.h must be used for default SW reset use cases, which handles the ASIC safety logic
 * before triggering an uC reset!
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_uCResetInfo.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockSupport,
                          RBFS_SysBootblockSupport_OFF,
                          RBFS_SysBootblockSupport_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FOTA,
                          RBFS_FOTA_OFF,
                          RBFS_FOTA_BASE,
                          RBFS_FOTA_BASEPLUS,
                          RBFS_FOTA_ENHANCED,
                          RBFS_FOTA_PREMIUM);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HswRecoveryReset,
                          RBFS_HswRecoveryReset_Enabled,
                          RBFS_HswRecoveryReset_Disabled);

/*
  =========================================================================
  Attention
  -------------------------------------------------------------------------
  Current SW reset concept triggers an Application Reset 1 without re-
  triggering BIST and therefore without HW based zeroing of Backup-RAM.
  If BIST must be executed after a SW triggered reset (e.g. long runners),
  it's necessary to handle this via the ASIC (SPI_res_HW) and not via the
  uC internal System Reset 2. This limitation of the System Reset 2 with
  BIST is documented within the CVM chapter of the user manual.
  This implies of course that the Backup-RAM content will be destroyed!
  =========================================================================
*/

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  /**
    * @brief Clear ECM reset flags of the uC
    *
    * Following flags of the RESF (Reset Factor) register belonging to "ECM" reset are cleared:
    *        ECM Application Reset Flag
    *        ECM System Reset Flag
    *
    * Hint: ECM reset flags will currently only be used in bootblock and have to be cleared at the controlled ending of the bootblock
    *       before going to FSW (so Control Mode in FSW will never see them)
    *
    */
  static inline void RBSYS_clearECMResetFlags(void)
  {
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      RBSYS_RESFC = (RBSYS_RESET_FLAG_ECM_APPLICATION | RBSYS_RESET_FLAG_ECM_SYSTEM);
    #else
      RBSYS_RESFC = (RBSYS_RESET_FLAG_ECM_SYSTEM);
    #endif
  }
#endif


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

  #if( (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    /**
      * @brief Trigger an immediate uC SW Reset (System Reset) with uC BIST and Bootblock execution
      *
      * This function executes an immediate SW reset with execution of bootblock after reset.
      * This low level API may only be called in Application and only in case of reset after programming SW for FOTA
      * Premium. This System Reset will also activate the selected Flash Configuration Area setting.
      *
      * This function must only be called by RBFSL, which does additionally handle ASIC safety logic before reset.
      *
      * Hint: Any RAM will be zeroed by this reset (uC dependent via SW or HW).
      *
      * @return void
      */
    extern void RBSYS_uCReset_SystemReset(void);
  #endif



  /**
  * @brief Trigger an immediate uC SW Reset (Application Reset 1) without bootblock
  *
  * This function executes an immediate SW reset without executing bootblock after reset.
  * This low level API may only be called in case of serious "not recoverable" system faults or
  * very special circumstances (BaseOS). Any other SW part must use the higher level API
  * #RB_performSWResetSkipBootBlock(), which does some additional ASIC safety logic handling.
  *
  * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
  *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
  *       - Application Reset 1 will not trigger Logic and Memory BIST
  * Additional hint for Renesas P1x family only:
  *       - all RAMs (excluding Backup-RAM) will be cleared by HW
  *
  * @return void
  */
  extern void RBSYS_uCReset_ApplResetSkipBootBlock(void);


  #if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
    /**
    * @brief Trigger an immediate uC SW Reset (Application Reset 1) without bootblock
    *
    * This function executes an immediate SW reset without executing bootblock after reset.
    * This low level API may only be called in case of very special circumstances (e.g. reprog request).
    * Any other SW part must use the higher level API #RB_performSWResetSkipBootBlock(),
    * which does some additional ASIC safety logic handling.
    *
    * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
    *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
    *       - Application Reset 1 will not trigger Logic and Memory BIST
    * Additional hint for Renesas P1x family only:
    *       - LRAM will be cleared by HW
    *       - GRAM and Backup-RAM will NOT be cleared
    *
    * @ToDo: Function must be removed once Reprog Driver is not being used anymore (replaced by RB Bootloader) -> see 1745590: [Reprog] Prohibit using ReprogDriver by default when using HSM
    *
    * @return void
    */
    extern void RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing(void);
  #endif

  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
    )
    /**
    * @brief Trigger an immediate uC SW Reset (Application Reset 1) without bootblock
    *
    * This function executes an immediate SW reset without executing bootblock after reset.
    * This low level API may only be called in case of very special circumstances (e.g. reprog request).
    * Any other SW part must use the higher level API #RB_performSWResetSkipBootBlock(),
    * which does some additional ASIC safety logic handling.
    *
    * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
    *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
    *       - Application Reset 1 will not trigger Logic and Memory BIST
    * Additional hint for Renesas P1x family only:
    *       - LRAM and Backup-RAM will NOT be cleared
    *
    * @ToDo: Function must be removed once Reprog Driver is not being used anymore (replaced by RB Bootloader) -> see 1745590: [Reprog] Prohibit using ReprogDriver by default when using HSM
    *
    * @return void
    */
    extern void RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing(void);
  #endif

  #if (RBFS_SysBootblockSupport == RBFS_SysBootblockSupport_ON)
    /**
    * @brief Trigger an immediate uC SW Reset (Application Reset 1) with bootblock to enter OEM-Reprog
    *
    * This function executes an immediate SW reset with executing OEM bootloader after reset.
    * This low level API may only be called in case of serious "not recoverable" system faults or
    * very special circumstances (BaseOS). Any other SW part must use the higher level API
    * #RB_performSWResetWithBootBlock4OEM(), which does some additional ASIC safety logic handling.
    *
    * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
    *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
    *       - Application Reset 1 will not trigger Logic and Memory BIST
    * Additional hint for Renesas P1x family only:
    *       - all RAMs (excluding Backup-RAM) will be cleared by HW
    *
    * @return void
    */
    extern void RBSYS_uCReset_ApplResetWithBootBlock4OEM(void);


    /**
    * @brief Trigger an immediate uC SW Reset (Application Reset 1) with bootblock to enter RB-Reprog
    *
    * This function executes an immediate SW reset with executing RB bootloader after reset.
    * This low level API may only be called in case of serious "not recoverable" system faults or
    * very special circumstances (BaseOS). Any other SW part must use the higher level API
    * #RB_performSWResetWithBootBlock4RB(), which does some additional ASIC safety logic handling.
    *
    * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
    *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
    *       - Application Reset 1 will not trigger Logic and Memory BIST
    * Additional hint for Renesas P1x family only:
    *       - all RAMs (excluding Backup-RAM) will be cleared by HW
    *
    * @return void
    */
    extern void RBSYS_uCReset_ApplResetWithBootBlock4RB(void);


    // deprecated but required for backwards compatibility
    extern void RBSYS_uCReset_ApplResetWithBootBlock(void);

  #endif
  
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
    )
    /**
     * @brief Clear Flags indicating uC Reset due to uC Voltage Monitoring (VMON / CVM)
     *
     * @return void
     */
    extern void RBSYS_uCReset_ClearuCVoltageMonResetFlags(void);
  #endif

  /** @brief Clear Reset Factors after Safety Tests (or if Safety-Tests should not be executed in the next reset cycle, e.g. because System is already degraded)
    * HWBIST: HWBist Reset Flags have to be reset to not evaluate old HWBIST results again
    * ECM:    Safety Tests shall be executed once per power cycle -> indicated by PowerOn Reset Flag
    * 
    * Hint: This API shall only be used by RBSYS and RBHSWESR!!
    */
  extern void RBSYS_ClearResetFactorsAfterSafetyTests(void);

#endif



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
