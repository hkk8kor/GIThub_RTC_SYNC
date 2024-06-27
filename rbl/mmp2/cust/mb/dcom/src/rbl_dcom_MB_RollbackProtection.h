/// @file rbl_dcom_MB_RollbackProtection.h
/// @brief This header provides protoTypes for Rollback Protection Feature related services
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_DCOM_MB_ROLLBACKPROTECTION_H_
#define RBL_DCOM_MB_ROLLBACKPROTECTION_H_

/* ***** SECTION Includes ***** */
#include "rbl_dcom_Lib.h"
#include "rbl_dcom_SWVersion.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

///Definition for Minimum Software Version NVM State Machine
typedef enum
{
  IDLE_STATE,  ///< NVM operation idle state
  READ_STATE,  ///< state for initiating Minimum Software Version Read operation
  WRITE_STATE ///< state for initiating Minimum Software Version Write operation
}rbl_dcom_DPVcheck_state;

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_dcom_MB_RollbackProtection.c
/// @brief The function checks the Minimum Software Version against Downgrade Protection version and
///        updates Minimum Software Version with Downgrade Protection version if they are not equal.
/// @pre periodically called from dcom_MB_20ms_Proc in every 20ms
/// @param[in] void
/// @return void
/// @startuml
/// !include rbl_dcom_MB_RollbackProtection.puml
/// @enduml
/// @details Function initialises NVM state to READ_STATE and calls the function @dcom_Lib_ReadNvMData to read Minimum Software Version.
/// If Minimum Software Version is not equal to Downgrade Protection version,NVM state is changed to WRITE_STATE and Downgrade Protection version value
/// is written to Minimum Software Version NVM block using function @dcom_Lib_WriteNvMData.
///  Once read/write is done NVM state is moved to IDLE_STATE where no operation is performed.

void rbl_dcom_DowngradeProtection_Check (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */


#endif /* RBL_DCOM_MB_ROLLBACKPROTECTION_H_ */
