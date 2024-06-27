#ifndef RBTPSW_MYTPSW_RAMBACKUPSERVICE_H__
#define RBTPSW_MYTPSW_RAMBACKUPSERVICE_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief TPSW RAM backup service
 *
 * This service provides a possibility to store and restore TPSW data over a reset.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_ON,
                          RBFS_TPSWTestsuite_OFF);

/******************************************************************/
/* Backup RAM structure for client RBTPSW tests                   */
/******************************************************************/
#define RBSYS_TPSWPERSIST_NUMBER_TESTMASKS 8

typedef struct {
  uint32 flags;
  uint32 current_test_id;
} RBTPSW_BURAM_tests_t;

#if RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON
  /**
   * @brief Store testsuite info to Backup RAM
   *
   * This function stores testsuite info to Backup RAM area in case an exception occured due to additional supervisor restrictions.
   * Hint: This function should be called before potentially triggering such an exception.
   *
   * @param pTPSWpersistData [in] pointer to the data structure to be stored in Backup RAM
   */
  extern void RBTPSW_setTPSWtestPersistentDataToBackupRAM(const RBTPSW_BURAM_tests_t* pTPSWpersistData);

  /**
   * @brief Restore testsuite info from Backup RAM
   *
   * Hint: This function shall be called during startup in case of SW reset
   *
   * @param pTPSWpersistData [out] pointer to the data structure where to restore the Backup RAM data
   */
  extern void RBTPSW_getTPSWtestPersistentDataFromBackupRAM(RBTPSW_BURAM_tests_t* pTPSWpersistData);
#endif



/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
