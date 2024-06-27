/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RAM Backup Service
 *
 * This service will provide a possibility to store data over a reset into Backup RAM.
 * Please keep in mind that RBSYS provides only the infrastructure for saving data to Backup RAM.
 * So each client must be registered in RBSYS, but the client itself must take care by it's own
 * when the data must be saved and when the data must be restored!
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_PlantStartupCtrl.h"
#include "RBLCF_MemoryRemap.h"
#include "RBLCF_MemoryMap.h"
#include "RBSYS_Intrinsics.h"
#include <string.h>
#include "RB_MemoryBarrier.h"


/* realized interfaces */
#include "RBSYS_RAMBackupService.h"
#include "RBSYS_RAMBackupServiceIntern.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_OFF,
                          RBFS_HSWSimulation_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_ON,
                          RBFS_TPSWTestsuite_OFF);


/* --------------------------------------------------------------------- */
/* Attention:                                                            */
/* Current SW reset concept triggers an Application Reset 1 without      */
/* re-triggering BIST and therefore without HW based zeroing of Backup-  */
/* RAM. But if the concept will be changed that BIST is re-triggered     */
/* after a SW reset, Backup-RAM content will be destroyed!               */
/* --------------------------------------------------------------------- */



/* --------------------------------------------------------------------- */
/* -------------------- FSW Backup RAM handling ------------------------ */
/* --------------------------------------------------------------------- */

typedef struct {
  volatile uint8* PartitionContent;
  const uint32 PartitionSize;
} RBSYS_BackupRAMPartitionInfo_t;

#if( RBFS_HSWSimulation == RBFS_HSWSimulation_OFF )

  /* Memory in Backup RAM. But please keep in mind that this memory will only
  * be used for saving and recovering data. Original location must be normal RAM */
  RBSECTION_START_BURAM_FSW_BSS_NOCLEAR
    static volatile RBSYS_BURAM_t RBSYS_BURAM;
  RBSECTION_END_BURAM_FSW_BSS_NOCLEAR


  /* Backup RAM clients for saving and restoring data */
  static const RBSYS_BackupRAMPartitionInfo_t rbsys_BackupRAMPartitions[RBSYS_BackupRAMUser_NumOfUsers] = {
    { &RBSYS_BURAM.RBSYS_BackupRAMFSW_RBSYS[0],         RBSYS_BURAM_PARTITION_SIZE_RBSYS },
    { &RBSYS_BURAM.RBSYS_BackupRAMFSW_RBECM[0],         RBSYS_BURAM_PARTITION_SIZE_RBECM },
    #if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
      { &RBSYS_BURAM.RBSYS_BackupRAMFSW_RBTPSWTEST[0],  RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST },
    #endif
    { &RBSYS_BURAM.RBSYS_BackupRAMFSW_RBSUPPLYBASE[0],  RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE },
    { &RBSYS_BURAM.RBSYS_BackupRAMFSW_RBHSWESR[0],      RBSYS_BURAM_PARTITION_SIZE_RBHSWESR }
  };
#else
  #include "HwModels/Memory/Hwm_RAMBackupService.h"

  static const RBSYS_BackupRAMPartitionInfo_t rbsys_BackupRAMPartitions[RBSYS_BackupRAMUser_NumOfUsers] = {
    { (uint8*)&Hwm_BackupRAM[0],                                                                                                             RBSYS_BURAM_PARTITION_SIZE_RBSYS },
    { (uint8*)&Hwm_BackupRAM[ RBSYS_BURAM_PARTITION_SIZE_RBSYS ],                                                                            RBSYS_BURAM_PARTITION_SIZE_RBECM },
    #if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
      { (uint8*)&Hwm_BackupRAM[ RBSYS_BURAM_PARTITION_SIZE_RBSYS + RBSYS_BURAM_PARTITION_SIZE_RBECM  ],                                      RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST },
    #endif
    { (uint8*)&Hwm_BackupRAM[ RBSYS_BURAM_PARTITION_SIZE_RBSYS + RBSYS_BURAM_PARTITION_SIZE_RBECM + RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST ], RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE },
    { (uint8*)&Hwm_BackupRAM[ RBSYS_BURAM_PARTITION_SIZE_RBSYS + RBSYS_BURAM_PARTITION_SIZE_RBECM + RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST + RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE ], RBSYS_BURAM_PARTITION_SIZE_RBHSWESR }
  };

  static_assert( Hwm_BackupRAM_Size_byte > ( RBSYS_BURAM_PARTITION_SIZE_RBSYS
                                           + RBSYS_BURAM_PARTITION_SIZE_RBECM
                                           #if( RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON )
                                             + RBSYS_BURAM_PARTITION_SIZE_RBTPSWTEST
                                           #endif
                                           + RBSYS_BURAM_PARTITION_SIZE_RBSUPPLYBASE
                                           + RBSYS_BURAM_PARTITION_SIZE_RBHSWESR), "Hwm-BackupRAM too small");
#endif

/******************************************************************/
/* Backup RAM structure for client RBSYS                          */
/******************************************************************/
typedef struct
{
  uint32 BaseOSRequestbySW;
  uint32 SkipBootblockRequester;
  uint32 ResetFlagsForRBECM;      //< Initialized by RBSYS, Provided to RBECM via API (can also be modified by RBECM)
} RBSYS_BURAM_SYS_t;

static RBSYS_BURAM_SYS_t RBSYS_BackupRAM_SYS_Current;

/* Todo: When reading / writing BackupRam Data, BURAM Raw Data is copied to the current working set.
 *       Idea: BURAM Raw Data could be copied once during startup and could be written back before SW Reset.
 *             -> potential change: BURAM is not updated at Power Loss / HW Reset. */

/**
 * @brief RBSYS_saveBaseOSRequestToBackupRAM
 *
 * Save message \#RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32 to Backup RAM area.
 * Hint: This function should be called before triggering SW reset.
 *
 * @return void
 */
void RBSYS_saveBaseOSRequestToBackupRAM(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

  RBSYS_BackupRAM_SYS_Current.BaseOSRequestbySW = l_RBMESG_RBSYSBaseOSRequestbySW_u32;

  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS,
                                offsetof(RBSYS_BURAM_SYS_t, BaseOSRequestbySW),
                                (void*)&RBSYS_BackupRAM_SYS_Current.BaseOSRequestbySW,
                                4 );
}


/**
 * @brief RBSYS_restoreBaseOSRequestFromBackupRAM
 *
 * Restore message \#RBMESG_RBMESG_RBSYSBaseOSRequestbySW_u32 from Backup RAM area.
 * Hint: This function should be called during startup only in case of SW reset.
 *
 * @return void
 */
void RBSYS_restoreBaseOSRequestFromBackupRAM(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

  RBSYS_BackupRAMFSW_ReadData(  RBSYS_BackupRAMUser_RBSYS,
                                offsetof(RBSYS_BURAM_SYS_t, BaseOSRequestbySW),
                                (void*)&RBSYS_BackupRAM_SYS_Current.BaseOSRequestbySW,
                                4 );

  l_RBMESG_RBSYSBaseOSRequestbySW_u32 = RBSYS_BackupRAM_SYS_Current.BaseOSRequestbySW;

  RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
}


/**
 * @brief RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM
 *
 * Send message \#RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 and store the same to Backup RAM area
 * Hint: This function should be called before triggering SW reset (to read the Requester during next startup).
 *
 * @return void
 */
void RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(uint32 request)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32) = request;
  RBMESG_SendMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

  RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester = request;

  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS,
                                offsetof(RBSYS_BURAM_SYS_t, SkipBootblockRequester),
                                (void*)&RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester,
                                4 );
}


/**
 * @brief RBSYS_restoreSkipBootblockRequesterFromBackupRAM
 *
 * Restore message \#RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 from Backup RAM area.
 * Hint: This function shall be called during startup only once in case of SW reset.
 *
 * @return void
 */
void RBSYS_restoreSkipBootblockRequesterFromBackupRAM(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

  RBSYS_BackupRAMFSW_ReadData(  RBSYS_BackupRAMUser_RBSYS,
                                offsetof(RBSYS_BURAM_SYS_t, SkipBootblockRequester),
                                (void*)&RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester,
                                4 );

  l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester;

  RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester = RBSYS_SKIP_BOOTBLOCKTrigResetValue;

  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS,
                                offsetof(RBSYS_BURAM_SYS_t, SkipBootblockRequester),
                                (void*)&RBSYS_BackupRAM_SYS_Current.SkipBootblockRequester,
                                4 );

  RBMESG_SendMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
}


#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
  /* Attention: This interface is called before CInit. Dont use initialized entities. */
  uint32 RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(void)
  {
    RBSYS_BackupRAMFSW_ReadData(  RBSYS_BackupRAMUser_RBSYS,
                                  offsetof(RBSYS_BURAM_SYS_t, ResetFlagsForRBECM),
                                  (void*)&RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM,
                                  4 );

    return RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM;
  }

  /* Attention: This interface is called before CInit. Dont use initialized entities. */
  void RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM(uint32 flags)
  {
    RBSYS_BackupRAMFSW_ReadData(  RBSYS_BackupRAMUser_RBSYS,
                                  offsetof(RBSYS_BURAM_SYS_t, ResetFlagsForRBECM),
                                  (void*)&RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM,
                                  4 );

    RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM |= flags;

    RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS,
                                  offsetof(RBSYS_BURAM_SYS_t, ResetFlagsForRBECM),
                                  (void*)&RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM,
                                  4 );
  }

  /* Attention: This interface is called before CInit. Dont use initialized entities. */
  void RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM(uint32 flags)
  {
    RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM = flags;

    RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS,
                                  offsetof(RBSYS_BURAM_SYS_t, ResetFlagsForRBECM),
                                  (void*)&RBSYS_BackupRAM_SYS_Current.ResetFlagsForRBECM,
                                  4 );
  }
#endif


void RBSYS_ClearFSWBackupRAM(void)
{
  uint32 addressStart = RBLCF_getStartAddress_BURAM_FSW();
  uint32 size = RBLCF_getLength_BURAM_FSW();

  memset((void*)addressStart, 0, size);
}

/* New Approach: Keep User Data private - RBSYS administers Backup RAM Partitions */

static void rbsys_BackupRAMFSW_CopyData(volatile void* dest, volatile const void* src, uint32 size)
{
  /* Volatile is used here to enforce read and write accesses. The underlying HW RAM does not have any side-effects but
   * might already be initilized before the SW takes control (initialized from last reset cycle). */
  uint32 i;
  for( i = 0; i < size; i++ )
  {
    ((volatile uint8*)dest)[i] = ((volatile const uint8*)src)[i];
  }
}


void RBSYS_BackupRAMFSW_WriteData(RBSYS_BackupRAMUser_n UserId, uint32 OffsetBytes, const void* SourcePtr, uint32 NumBytes)
{
  if( (UserId < RBSYS_BackupRAMUser_NumOfUsers) && ((OffsetBytes + NumBytes) <= rbsys_BackupRAMPartitions[UserId].PartitionSize) )
  {
    rbsys_BackupRAMFSW_CopyData( &rbsys_BackupRAMPartitions[UserId].PartitionContent[OffsetBytes], SourcePtr, NumBytes);
    RB_FullHardwareMemoryBarrier();
  }
}

void RBSYS_BackupRAMFSW_ReadData(RBSYS_BackupRAMUser_n UserId, uint32 OffsetBytes, void* TargetPtr, uint32 NumBytes)
{
  if( (UserId < RBSYS_BackupRAMUser_NumOfUsers) && ((OffsetBytes + NumBytes) <= rbsys_BackupRAMPartitions[UserId].PartitionSize) )
  {
    rbsys_BackupRAMFSW_CopyData( TargetPtr, &rbsys_BackupRAMPartitions[UserId].PartitionContent[OffsetBytes], NumBytes );
  }
}





/** @} */
/* End ingroup RBSYS */
