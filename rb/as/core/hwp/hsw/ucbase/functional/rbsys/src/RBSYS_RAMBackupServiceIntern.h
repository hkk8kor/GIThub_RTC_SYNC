#ifndef RBSYS_RAMBACKUPSERVICEINTERN_H__
#define RBSYS_RAMBACKUPSERVICEINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RAM backup service
 *
 * This service will provide a possibility to store data over a reset.
 * Please keep in mind that RBSYS provides only the infrastructure for saving data to Backup RAM.
 * So each client must be registered in RBSYS, but the client itself must take care by it's own
 * when the data must be saved and when the data must be restored!
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"
#include "RBSYS_RAMBackupService.h"
#include "RBSYS_BBFSW_StartupServices.h"

/* used interfaces */

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )


  extern void RBSYS_saveBaseOSRequestToBackupRAM(void);
  extern void RBSYS_restoreBaseOSRequestFromBackupRAM(void);

  extern void RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(uint32 request);
  extern void RBSYS_restoreSkipBootblockRequesterFromBackupRAM(void);

  /**
    * @brief Update the stored Reset Flags for RBECM with current Reset Flags (OR logic)
    *
    * Attention: Shall only be used by RBSYS!
    *
    * @return void
    */
  extern void RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM(uint32 flags);

  /**
    * @brief RBSYS_ClearFSWBackupRAM
    *
    * Clear complete BURAM_FSW (Backup RAM for FSW -> FSW communication)
    * Hint: This API may only be used for special usecases (e.g. invalidating BackupRAM before flashing new software via
    *       Bootloader. New Application software could misinterpret the possibly changed BackupRAM structure.)
    *
    * @return void
    */
  extern void RBSYS_ClearFSWBackupRAM(void);

#endif



#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )

  /**
    * @brief Update the stored central ResetFlags inside BBFSW BackupRAM
    *
    * Attention: Shall only be used by RBSYS!
    *
    * @return Reset Flags
    */
  static inline void RBSYS_BackupRAM_BBFSW_UpdateResetFlags(uint32 flags)
  {
    RBSYS_BURAM_BB_FSW_INTERFACE.ResetFlags |= flags;
  }

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    /**
      * @brief Get the stored central ResetFlags from BBFSW BackupRAM
      *
      * Attention: Shall only be used by RBSYS!
      *
      * @return Reset Flags
      */
    static inline uint32 RBSYS_BackupRAM_BBFSW_GetResetFlags(void)
    {
      return RBSYS_BURAM_BB_FSW_INTERFACE.ResetFlags;
    }

    /**
      * @brief Clear the stored central ResetFlags inside BBFSW BackupRAM
      *
      * Attention: Shall only be used by RBSYS!
      *
      * @return Reset Flags
      */
    static inline void RBSYS_BackupRAM_BBFSW_ClearResetFlags(void)
    {
      RBSYS_BURAM_BB_FSW_INTERFACE.ResetFlags = 0;
    }

    /**
      * @brief Copy ResetFlags from BBFSW-BURAM to FSW-BURAM for RBECM
      *
      * @return void
      */
    static inline void RBSYS_BackupRAM_FSW_ResetFlagHandlingForRBECM(void)
    {
      /* Current Reset flags are added to already set Reset Flags from Bootblock -> Bitwise OR */
      #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
        RBSYS_BackupRAM_BBFSW_UpdateResetFlags( RBSYS_RESF ); //< todo: Stellar support
      #endif

      /* Copy central Reset Flags to User Reset Flags */
      RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM( RBSYS_BackupRAM_BBFSW_GetResetFlags() );
      /* Clear central Reset Flags */
      RBSYS_BackupRAM_BBFSW_ClearResetFlags();
    }

  #else // Bootmanager, Bootloader, RBBootloader

    /**
      * @brief Store current Reset Flags into BackupRAM to recover those during startup of FSW
      * @return void
      */
    static inline void RBSYS_BackupRAM_BB_ResetFlagHandlingForRBECM(void)
    {
      /* Current Reset flags are stored into BackupRAM */
      #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
        RBSYS_BackupRAM_BBFSW_UpdateResetFlags( RBSYS_RESF ); //< todo: Stellar support
      #endif
    }

  #endif
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
