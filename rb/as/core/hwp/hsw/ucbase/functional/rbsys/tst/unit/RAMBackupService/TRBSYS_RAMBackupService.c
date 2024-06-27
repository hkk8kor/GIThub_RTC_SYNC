#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_TPSWSVPRestrictions, RBFS_TPSWTestsuite

#include "RBSYS_RAMBackupService.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_PlantStartupCtrl.h"
#include <string.h>
#include "TRBLCF_MemoryMap.h"

#include "TRBSYS_RAMBackupService_Adaptor.h"




#define DUMMY_REQUEST_1 0xAAAA5555
#define DUMMY_REQUEST_2 0x5555AAAA


/**
 * \Reference
 * RBSYS_saveBaseOSRequestToBackupRAM, RBSYS_restoreBaseOSRequestFromBackupRAM, Gen_SWCS_HSW_uC_Base_SYS-223
 *
 * \Purpose
 * Verify the function which stores the BaseOS request to Backup-RAM
 *
 * \Sequence
 * Set BaseOS request
 * Call function RBSYS_saveBaseOSRequestToBackupRAM
 * manipulate BaseOS request
 * Call function RBSYS_restoreBaseOSRequestFromBackupRAM
 * Check: Manipulated value has been overwritten with restored value from BURAM
 *
 * \ExpectedResult
 * see \Sequence
 */
SWTEST void TRBSYS_saveBaseOSRequestToBackupRAM(void)
{
  // 1st teststep
  TRBSYS_setRBSYSBaseOSRequestbySW_u32(DUMMY_REQUEST_1);

  RBSYS_saveBaseOSRequestToBackupRAM();
  TRBSYS_setRBSYSBaseOSRequestbySW_u32(DUMMY_REQUEST_2);
  RBSYS_restoreBaseOSRequestFromBackupRAM();

  SWT_EvalEqX(TRBSYS_getRBSYSBaseOSRequestbySW_u32(), DUMMY_REQUEST_1);
}



/**
 * \Reference
 * RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM, RBSYS_restoreSkipBootblockRequesterFromBackupRAM, Gen_SWCS_HSW_uC_Base_SYS-277
 *
 * \Purpose
 * Verify the function which stores the SkipBootblockRequester info to Backup-RAM
 *
 * \Sequence
 * Call function RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM with Requester
 * Call function RBSYS_restoreSkipBootblockRequesterFromBackupRAM to restore value from BURAM
 *
 * \ExpectedResult
 * Backup-RAM content must contain the corresponding SkipBootblockRequester info
 * public Message must contain the restored BURAM value
 */
SWTEST void TRBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(void)
{
  // Store BootblockRequester = DUMMY_1
  RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(DUMMY_REQUEST_1);

  // Overwrite BootblockRequester in normal RAM
  RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = DUMMY_REQUEST_2;

  // Restore Value from BURAM
  RBSYS_restoreSkipBootblockRequesterFromBackupRAM();
  // Eval: Requester == DUMMY_1
  SWT_EvalEqX(RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, DUMMY_REQUEST_1);

  // For next Reset, Request shall be initialized to Default
  RBSYS_restoreSkipBootblockRequesterFromBackupRAM();
  SWT_EvalEqX(RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_SKIP_BOOTBLOCKTrigResetValue);
}



#if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
  /**
    * \Reference
    * RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM,
    * RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM,
    * RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM
    *
    * \Purpose
    * Verify Get/Set API for ResetFlags
    *
    * \Sequence
    * Call Update with value A
    * Eval: Getter shall return value A
    * Call Setter with value X
    * Eval: Getter shall return value X
    *
    * \ExpectedResult
    * see \Sequence
    */
  SWTEST void TRBSYS_ResetFlagInterfacesForRBECM(void)
  {
    // Set value from RBSYS
    RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM(0x13371337);
    SWT_EvalEq(RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(), 0x13371337);
    RBSYS_BackupRAM_FSW_UpdateResetFlagsForRBECM(0x73317331);
    SWT_EvalEq(RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(), 0x13371337 | 0x73317331);

    // test with value 0xA5A5A5A5u
    RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM(0xA5A5A5A5u);
    SWT_EvalEq(RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(), 0xA5A5A5A5u);

    // test with value 0x5A5A5A5Au
    RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM(0x5A5A5A5Au);
    SWT_EvalEq(RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(), 0x5A5A5A5Au);
  }
#endif


/**
 * \Reference All Get and Set Interfaces
 *
 * \Purpose
 * Check if any interface is writing to different RAM locations than expected
 *
 * \Sequence
 * Call all Set Functions with unique values
 * Call all Get Functions -> shall read the same values as written
 *
 * \ExpectedResult
 * see \Sequence
 */
SWTEST void TRBSYS_CheckCrossEffectsOfInterfaces(void)
{
  // Call all write interfaces with unique values
  #if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
    RBSYS_BackupRAM_FSW_SetResetFlagsForRBECM(0x11111111u);
  #endif
  RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(0x44444444u);
  TRBSYS_setRBSYSBaseOSRequestbySW_u32(0x55555555u);
  RBSYS_saveBaseOSRequestToBackupRAM();

  // Call all read interfaces and check if read value matches expected
  #if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
    SWT_EvalEq(RBSYS_BackupRAM_FSW_GetResetFlagsForRBECM(), 0x11111111u);
  #endif
  RBSYS_restoreSkipBootblockRequesterFromBackupRAM();
  SWT_EvalEqX(RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, 0x44444444u);
  RBSYS_restoreBaseOSRequestFromBackupRAM();
  SWT_EvalEqX(TRBSYS_getRBSYSBaseOSRequestbySW_u32(), 0x55555555u);
}


/**
 * \Reference RBSYS_BackupRAMFSW_WriteData, RBSYS_BackupRAMFSW_ReadData
 *
 * \Purpose
 * Check if sanity check for valid Memory range works
 *
 * \Sequence
 * Call interfaces with request for memory range outside of the partition
 *
 * \ExpectedResult
 * no modification of BackupRAM if sanity check fails
 */
SWTEST void TRBSYS_InterfaceSanityChecks(void)
{
  uint8 dummy_write_buffer[100];
  uint8 dummy_read_buffer[100];
  uint8 dummy_write_buffer_reset[100] = {0};

  uint32 i;
  for(i=0; i<RBSYS_BURAM_PARTITION_SIZE_RBSYS; i++)
  {
    dummy_write_buffer[i] = i+1; //< fill with numbers 1..RBSYS_BURAM_PARTITION_SIZE_RBSYS
  }

  /******************************* Sanity Check shall Pass **********************************/

  /* Attempting copy from Index "LastIndex" with Size = 1 */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, RBSYS_BURAM_PARTITION_SIZE_RBSYS-1, dummy_write_buffer, 1);
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, RBSYS_BURAM_PARTITION_SIZE_RBSYS-1, dummy_read_buffer, 1);
  SWT_EvalEq(dummy_read_buffer[0], 1);

  dummy_read_buffer[0] = 0; //< reset for next test

  /* Attempting copy from Index 0 with Size = AllowedSize */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS);
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS);
  for(i=0; i<RBSYS_BURAM_PARTITION_SIZE_RBSYS; i++)
  {
    SWT_EvalEq(dummy_read_buffer[i], i+1);
    dummy_read_buffer[i] = 0; //< reset for next test
  }

  /* Reset Backup RAM */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer_reset, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // valid write to all 0


  /******************************* Sanity Check shall Fail **********************************/

  /* Attempting Write from Index 0 with Size = AllowedSize + 1 */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS+1); // invalid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS);     // valid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);

  /* Attempting Write from Index "LastIndex" with Size = 2 */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, RBSYS_BURAM_PARTITION_SIZE_RBSYS-1, dummy_write_buffer, 2); // invalid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS);     // valid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);

  /* Attempting Write with invalid User ID */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_NumOfUsers, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // invalid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // valid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);

  /* Attempting Read from Index 0 with Size = AllowedSize + 1 */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // valid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS+1); // invalid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);

  /* Attempting Read from Index "LastIndex" with Size = 2 */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // valid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_RBSYS, RBSYS_BURAM_PARTITION_SIZE_RBSYS-1, dummy_read_buffer, 2); // invalid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);

  /* Attempting Read with invalid User ID */
  RBSYS_BackupRAMFSW_WriteData( RBSYS_BackupRAMUser_RBSYS, 0, dummy_write_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // valid
  RBSYS_BackupRAMFSW_ReadData( RBSYS_BackupRAMUser_NumOfUsers, 0, dummy_read_buffer, RBSYS_BURAM_PARTITION_SIZE_RBSYS); // invalid
  SWT_EvalEq(dummy_read_buffer[0], 0);
  SWT_EvalEq(dummy_read_buffer[RBSYS_BURAM_PARTITION_SIZE_RBSYS-1], 0);
}

/**
 * \Reference
 * RBSYS_ClearFSWBackupRAM
 *
 * \Purpose
 * Verify if RBSYS_ClearFSWBackupRAM clears complete BURAM_FSW
 *
 * \Sequence
 * Set Backup-RAM content to 0xFF
 * Call function RBSYS_ClearFSWBackupRAM
 *
 * \ExpectedResult
 * Backup-RAM content shall be 0x00
 */
SWTEST void TRBSYS_ClearFSWBackupRAM(void)
{
  uint32 i;
  memset(&TRBSYS_BURAM_FSW[0], 0xFFFFFFFF, sizeof(TRBSYS_BURAM_FSW));
  RBSYS_ClearFSWBackupRAM();

  for(i = 0; i < TRBSYS_BURAM_FSW_Length; i++)
  {
    SWT_EvalEq(TRBSYS_BURAM_FSW[i], 0x00000000u);
  }
}