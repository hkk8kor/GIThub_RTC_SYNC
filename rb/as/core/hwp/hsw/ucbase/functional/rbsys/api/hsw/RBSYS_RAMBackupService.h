#ifndef RBSYS_RAMBACKUPSERVICE_H__
#define RBSYS_RAMBACKUPSERVICE_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief RAM backup service
 *
 * This service will provide a possibility to store data over a reset.
 * Please keep in mind that RBSYS provides only the infrastructure for saving data to Backup RAM.
 * So each client must be registered in RBSYS, but the client itself must take care by it's own
 * when the data must be saved and when the data must be restored!
 *
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_ON,
                          RBFS_TPSWTestsuite_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);



/******************************************************************/
/* overall structure which contain all Backup RAM clients for FSW */
/******************************************************************/

#define RBSYS_BURAM_PARTITION_SIZE_RBSYS           (7*4)  /* 28 Bytes required today */
#define RBSYS_BURAM_PARTITION_SIZE_RBECM           (100)  /* max. 92 Bytes required today */
#if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
  #define RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST    (2*4) /* = 8 Bytes required today */
#else
  #define RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST    (0)
#endif
#define RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE    (4)    /* 4 Bytes required today */
#define RBSYS_BURAM_PARTITION_SIZE_RBHSWESR        (4*4)  /* 12 Bytes required today */

typedef struct
{
  uint8 RBSYS_BackupRAMFSW_RBSYS        [RBSYS_BURAM_PARTITION_SIZE_RBSYS];
  uint8 RBSYS_BackupRAMFSW_RBECM        [RBSYS_BURAM_PARTITION_SIZE_RBECM];
  #if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
    uint8 RBSYS_BackupRAMFSW_RBTPSWTEST   [RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST];
  #endif
  uint8 RBSYS_BackupRAMFSW_RBSUPPLYBASE [RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE];
  uint8 RBSYS_BackupRAMFSW_RBHSWESR     [RBSYS_BURAM_PARTITION_SIZE_RBHSWESR];
} RBSYS_BURAM_t;


/* New Approach: Keep User Data private - RBSYS administers Backup RAM Parititions */

typedef enum {
  RBSYS_BackupRAMUser_RBSYS = 0,
  RBSYS_BackupRAMUser_RBECM,
  #if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
    RBSYS_BackupRAMUser_RBTPSWTEST,
  #endif
  RBSYS_BackupRAMUser_RBSUPPLYBASE,
  RBSYS_BackupRAMUser_RBHSWESR,
  RBSYS_BackupRAMUser_NumOfUsers
}RBSYS_BackupRAMUser_n;


/**
  * @brief Copies BackupRAM Data from the User's [UserId] partition to the target Buffer [tgtPtr].
  *
  * @param UserId       User-Identifier which matches an existing BackupRAM partition
  * @param OffsetBytes  Offset inside the respective partition [in Bytes]
  * @param TargetPtr    Pointer to the Target Buffer / Object / Memory Location to copy the data to
  * @param NumBytes     Number of Bytes to copy [in Bytes]
  *
  * Example "partial read":
  *    RBSYS_BackupRAMFSW_ReadData(
  *         RBSYS_BackupRAMUser_RBECM,                          <- User Identifier
  *         offsetof(RBSYS_BURAM_ECM_t, ECM0StatusRegBackup),   <- offsetof gives the Offset of a member in a struct
  *         &RBSYS_BURAM_ECM.ECM0StatusRegBackup,               <- target object inside "normal" (not Backup!) RAM
  *         sizeof(RBECM_ECM0StatusRegBackup_t));               <- size to copy
  *
  * Example "complete read":
  *    RBSYS_BackupRAMFSW_ReadData(
  *         RBSYS_BackupRAMUser_RBECM,                          <- User Identifier
  *         0,                                                  <- offsetof gives the Offset of a member in a struct
  *         &RBSYS_BURAM_ECM,                                   <- target object inside "normal" (not Backup!) RAM
  *         sizeof(RBSYS_BURAM_ECM_t));                         <- size to copy
  */
extern void RBSYS_BackupRAMFSW_ReadData(RBSYS_BackupRAMUser_n UserId, uint32 OffsetBytes, void* TargetPtr, uint32 NumBytes);

/**
  * @brief Copies BackupRAM Data for the User's [UserId] RAM Buffer [SourcePtr] to the target partition.
  *
  * @param UserId       User-Identifier which matches an existing BackupRAM partition
  * @param OffsetBytes  Offset inside the respective partition [in Bytes]
  * @param SourcePtr    Pointer to the Source Buffer / Object / Memory Location to copy the data from
  * @param NumBytes     Number of Bytes to copy [in Bytes]
  *
  * Example "partial write":
  *    RBSYS_BackupRAMFSW_WriteData(
  *         RBSYS_BackupRAMUser_RBECM,                          <- User Identifier
  *         offsetof(RBSYS_BURAM_ECM_t, ECM0StatusRegBackup),   <- offsetof gives the Offset of a member in a struct
  *         &RBSYS_BURAM_ECM.ECM0StatusRegBackup,               <- source object inside "normal" (not Backup!) RAM
  *         sizeof(RBECM_ECM0StatusRegBackup_t));               <- size to copy
  *
  * Example "complete write":
  *    RBSYS_BackupRAMFSW_WriteData(
  *         RBSYS_BackupRAMUser_RBECM,                          <- User Identifier
  *         0,                                                  <- offsetof gives the Offset of a member in a struct
  *         &RBSYS_BURAM_ECM,                                   <- source object inside "normal" (not Backup!) RAM
  *         sizeof(RBSYS_BURAM_ECM_t));                         <- size to copy
  */
extern void RBSYS_BackupRAMFSW_WriteData(RBSYS_BackupRAMUser_n UserId, uint32 OffsetBytes, const void* SourcePtr, uint32 NumBytes);


#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
  /**
   * @brief Get the stored Reset Flags from FSW BackupRAM
   *
   * Attention: Shall only be used by RBECM!
   *
   * @return stored value
   */
  extern uint32 RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(void);

  /**
   * @brief Set the stored Reset Flags inside FSW BackupRAM
   *
   * Attention: Shall only be used by RBECM!
   *
   * @param value to be stored
   */
  extern void   RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM(uint32 flags);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
