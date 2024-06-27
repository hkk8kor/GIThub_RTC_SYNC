/// @file rbl_CustIf_ECU_Stat_IMU_D_ST3.h
/// @brief This header provides definitions for Ecu status for driving can related signals
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_ECU_STAT_IMU_D_ST3_H_
#define RBL_CUSTIF_ECU_STAT_IMU_D_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
#include "rbl_CustIf_ECU_Stat_IMU_X_ST3.h"
/* ***** END_SECTION Includes ***** */


/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/// @c_file  rbl_CustIf_ECU_Stat_IMU_D_ST3.c
/// @brief   The Function transmits ECU_Stat_IMU_B_DRIVING_ST3 PDU related signals
/// @pre     periodically called from rbl_CustIf_20ms_Proc in every 20 ms
/// @param[in] : void
/// @return    : none
/// @details
/// ECU_Id_IMU_X_ST3 contains ECU identifier @ref RBL_CUSTIF_IMU_ECU_ID . \n
/// WakeupRsn_IMU_X_ST3 is updated with @ref RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW value. \n
/// NwId_Rsrv_ST3 is set to 0. \n
/// Awake_Diag_Actv_IMU_X_ST3 is set to @ref rbl_dcomActiveDiagSession which holds the active session information .\n
/// Awake_NwStart_IMU_X_ST3 are set to @ref rbl_net_GetAwakeNwStartStatus() function which has the Awake NM Start status.\n
///
/// Function transmits the signal via @ref Com_SendSignal service.\n
/// if IMU B- AMG varient  (RBFS_MMP2_IMUB) variant is activated then Com Signal Id Type for each signal is given below \n
///
/// * @ref ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_DRIVING_CAN_Tx for transmitting ECU_Id_IMU_X_ST3 \n
/// * @ref ComConf_ComSignal_S_NwId_Rsrv_ST3_DRIVING_CAN_Tx for transmitting NwId_Rsrv_ST3 \n
/// * @ref ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_DRIVING_CAN_Tx for transmitting WakeupRsn_IMU_X_ST3  \n
/// * @ref ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_DRIVING_CAN_Tx for transmitting Awake_Diag_Actv_IMU_X_ST3   \n
/// * @ref ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_DRIVING_CAN_Tx for transmitting Awake_NwStart_IMU_X_ST3   \n
void rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update(void );

#endif /* RBL_CUSTIF_ECU_STAT_IMU_D_ST3_H_ */
