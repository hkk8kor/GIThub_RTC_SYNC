/// @file rbl_CustIf_ECU_Stat_IMU_X_ST3.h
/// @brief This header provides definitions for ECU_Stat_IMU_A_ST3 and ECU_Stat_IMU_B_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_ECU_STAT_IMU_X_ST3_H_
#define RBL_CUSTIF_ECU_STAT_IMU_X_ST3_H_
/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */


/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

///  Wake up by network
#define RBL_CUSTIF_D_WAKEUPRSN_ST3_NETWORK          (0U)

/// Wake up reason, ECU ID and network ID for IMU A and IMU B
#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
    #define RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW      (34U)
    #define RBL_CUSTIF_IMU_ECU_ID                   (0x16A)
    #define RBL_CUSTIF_IMU_NW_ID                    (0U)
#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
    #define RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW      (53U)
    #define RBL_CUSTIF_IMU_ECU_ID                   (0x16B)
    #define RBL_CUSTIF_IMU_NW_ID                    (46U)
#endif

/// Structure type for ECU_Stat_IMU_X_ST3 pdu group signals
typedef struct
{
 uint16  ECU_Id_IMU_X_ST3;               ///< ECU identifier
 uint8   NwId_Rsrv_ST3;                  ///< Network identifier
 uint16  WakeupRsn_IMU_X_ST3;            ///< Wakeup reason
 boolean Awake_Diag_Actv_IMU_X_ST3;       ///< Stay awake for diagnostics active
 boolean Awake_NwStart_IMU_X_ST3;         ///< Stay awake for network startup
} rbl_CustIf_ECU_Stat_IMU_X_ST3_t;

/// @c_file  rbl_CustIf_ECU_Stat_IMU_X_ST3.c
/// @brief   The Function transmits ECU_Stat_IMU_X_ST3 PDU related signals[X indicated A or B ].
/// @pre     periodically called from rbl_CustIf_20ms_Proc in every 20 ms
/// @param[in] : void
/// @return    : nones
/// @details
/// ECU_Id_IMU_X_ST3 contains ECU identifier @ref RBL_CUSTIF_IMU_ECU_ID ,0x16A for IMU A and 0x16B for IMU B \n
/// WakeupRsn_IMU_X_ST3 is updated with @ref  RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW value.\n
/// NwId_Rsrv_ST3 is set to @ref RBL_CUSTIF_IMU_NW_ID .\n
/// Awake_Diag_Actv_IMU_X_ST3 is set to @ref rbl_dcomActiveDiagSession which holds the active session information. \n
/// and Awake_NwStart_IMU_X_ST3 is set to @ref rbl_net_GetAwakeNwStartStatus() function which has the Awake NM Start status.\n
/// For IMU B internal transmission NwId_Rsrv_ST3 set to zero. \n
/// Function transmits the signal via @ref Com_SendSignal service.\n
/// if IMU A (RBFS_MMP2_IMUA ) variant is activated then Com Signal Id Type for each signal is given below \n
///
/// * @ref ComConf_ComSignal_S_ECU_Id_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ECU_Id_IMU_X_ST3 \n
/// * @ref ComConf_ComSignal_S_NwId_Rsrv_ST3_HAD_BACKUP_CAN_Tx for transmitting NwId_Rsrv_ST3 \n
/// * @ref ComConf_ComSignal_S_WakeupRsn_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting WakeupRsn_IMU_X_ST3  \n
/// * @ref ComConf_ComSignal_S_Awake_Diag_Actv_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting Awake_Diag_Actv_IMU_X_ST3   \n
/// * @ref ComConf_ComSignal_S_Awake_NwStart_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting Awake_NwStart_IMU_X_ST3   \n
/// if IMU B (RBFS_MMP2_IMUB) variant is activated then Com Signal Id Type for each signal is given below \n
///
/// * @ref ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_HAD_IMU_CAN_Tx for transmitting ECU_Id_IMU_X_ST3 \n
/// * @ref ComConf_ComSignal_S_NwId_HAD_IMU_ST3_CAN_Tx for transmitting NwId_Rsrv_ST3 \n
/// * @ref ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_HAD_IMU_CAN_Tx for transmitting WakeupRsn_IMU_X_ST3  \n
/// * @ref ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_HAD_IMU_CAN_Tx for transmitting Awake_Diag_Actv_IMU_X_ST3   \n
/// * @ref ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_HAD_IMU_CAN_Tx for transmitting Awake_NwStart_IMU_X_ST3   \n

/// if IMU B (RBFS_MMP2_IMUB) variant is activated then Com Signal Id Type for Internal transmission signal is given below \n
/// * @ref ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ECU_Id_IMU_X_ST3 \n
/// * @ref ComConf_ComSignal_S_NwId_Rsrv_ST3_IMU_INTERNAL_CAN_Tx for transmitting NwId_Rsrv_ST3 \n
/// * @ref ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting WakeupRsn_IMU_X_ST3  \n
/// * @ref ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting Awake_Diag_Actv_IMU_X_ST3   \n
/// * @ref ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting Awake_NwStart_IMU_X_ST3   \n

void rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update (void );

#endif /* RBL_CUSTIF_ECU_STAT_IMU_X_ST3_H_ */
