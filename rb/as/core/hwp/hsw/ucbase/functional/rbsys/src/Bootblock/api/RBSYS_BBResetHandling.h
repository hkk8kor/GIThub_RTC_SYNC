#ifndef RBSYS_BBRESETHANDLING_H__
#define RBSYS_BBRESETHANDLING_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief SW reset handling for bootblock
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CpuInfo.h" //< required for backwards compatibility, used implicitely by BLDR



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);


/* --------------------------------------------------------------------- */
/* Attention:                                                            */
/* Current SW reset concept triggers an Application Reset 1 without      */
/* re-triggering BIST and therefore without HW based zeroing of Backup-  */
/* RAM. But if the concept will be changed that BIST is re-triggered     */
/* after a SW reset, Backup-RAM content will be destroyed!               */
/* --------------------------------------------------------------------- */


// all functions may only be called by bootblock
#if (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)

  /**
   * @brief Trigger a SW Reset (Application Reset 1) without bootblock
   *
   * This function may only be called by the bootblock.
   * It executes a SW reset without executing bootblock after reset.
   *
   * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
   *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
   *       - Application Reset 1 will not trigger Logic and Memory BIST
   *       - all RAMs (excluding Backup-RAM) will be cleared by HW
   *
   * @return void
   */
  extern void RBSYS_BBSWResetSkipBB(void);


  /**
   * @brief Trigger a SW Reset (Application Reset 1) with bootblock
   *
   * This function may only be called by the bootblock.
   * It executes a SW reset with executing bootblock after reset.

   * Hint: - ErrorPin state will not influenced by this Application Reset 1. But please keep in mind
   *         that all higher prio resets (e.g. PORST, Terminal or System Reset) will set ErrorPin to low after reset release.
   *       - Application Reset 1 will not trigger Logic and Memory BIST
   *       - all RAMs (excluding Backup-RAM) will be cleared by HW
   *
   * @return void
   */
  extern void RBSYS_BBSWResetWithBB(void);


  /**
   * @brief Checks if reset was initiated by bootblock
   *
   * This function may only be called by the bootblock.
   * It indicates whether the bootblock was entered from bootblock context (via RBSYS_BBSWResetWithBB).
   *
   * @return TRUE if reset was initiated by bootblock, otherwise FALSE
   */
  extern boolean RBSYS_BBisSWResetByBB(void);


  /**
   * @brief Checks if reset was initiated by FSW
   *
   * This function may only be called by the bootblock.
   * It indicates whether the bootblock was entered for OEM-Reprog from FSW context (via RBSYS_uCReset_ApplResetWithBootBlock/RBSYS_uCReset_ApplResetWithBootBlock4OEM).
   *
   * @return TRUE if reset was initiated for OEM-Reprog by FSW, otherwise FALSE
   */
  extern boolean RBSYS_BBisSWResetByFSW2OEMBoot(void);


  /**
   * @brief Checks if reset was initiated by FSW
   *
   * This function may only be called by the bootblock.
   * It indicates whether the bootblock was entered for RB-Reprog from FSW context (via RBSYS_uCReset_ApplResetWithBootBlock4RB).
   *
   * @return TRUE if reset was initiated for RB-Reprog by FSW, otherwise FALSE
   */
  extern boolean RBSYS_BBisSWResetByFSW2RBBoot(void);


  // deprecated but required for backwards compatibility
  static inline boolean RBSYS_BBisSWResetByFSW(void)
  {
    return RBSYS_BBisSWResetByFSW2OEMBoot();
  }


  /**
   * @brief Trigger an immediate uC SW Reset (System Reset 2)
   *
   * This function may only be called by the bootblock.
   * This function executes an immediate SW reset. May only be used by bootblock after reprogramming Option Bytes.
   *
   * @return void
   */
  extern void RBSYS_BBSystemReset(void);

#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
