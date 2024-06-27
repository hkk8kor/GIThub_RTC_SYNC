/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief TPSW RAM Backup Service
 *
 * This service provides a possibility to store and restore TPSW data over a reset.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_RAMBackupService.h"
#include <stddef.h>   // for offsetof

/* realized interfaces */
#include "RBTPSW_MyTPSW_RAMBackupService.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_ON,
                          RBFS_TPSWTestsuite_OFF);


#if RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON

  void RBTPSW_setTPSWtestPersistentDataToBackupRAM(const RBTPSW_BURAM_tests_t* pTPSWpersistData)
  {
    RBSYS_BackupRAMFSW_WriteData(
      RBSYS_BackupRAMUser_RBTPSWTEST,
      0,
      pTPSWpersistData,
      sizeof(*pTPSWpersistData));
  }

  void RBTPSW_getTPSWtestPersistentDataFromBackupRAM(RBTPSW_BURAM_tests_t* pTPSWpersistData)
  {
    RBSYS_BackupRAMFSW_ReadData(
      RBSYS_BackupRAMUser_RBTPSWTEST,
      0,
      pTPSWpersistData,
      sizeof(*pTPSWpersistData));
  }

#endif



/** @} */
/* End ingroup RBTPSW */
