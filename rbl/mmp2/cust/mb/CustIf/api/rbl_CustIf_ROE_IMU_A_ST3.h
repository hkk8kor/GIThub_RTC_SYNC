/// @file rbl_CustIf_ROE_IMU_A_ST3.h
/// @brief This header provides definitions for ROE_IMU_A_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_CUSTIF_ROE_IMU_A_ST3_H__
#define RBL_CUSTIF_ROE_IMU_A_ST3_H__

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
#include "rbl/mmp2/cust/mb/3rdPartySwInt/rbl_SwcDiagAdapter/api/rbl_SwcDiagAdapter_Appl.h"

/* ***** END_SECTION Includes ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file  rbl_CustIf_ROE_IMU_A_ST3.c
/// @brief   The Function transmits Received ROE_IMU_A_ST3 PDU related group signals.
/// @pre     called from rbl_SwcDiagAdapter_Appl when RBFS_ThirdPartySoftware_ON.
/// @param[in] RoERecord_ST3: Its structure pointer represent RoE Record data[RoE_0 - RoE_7]
/// @return    : none
/// @details  Function receives RoERecord_ST3  data from swcDiag,
/// After reception transmits the received signal via @ref Com_SendSignal service.\n
/// if IMU A (RBFS_MMP2_IMUA ) variant is activated then Com SignalId Type for each signal is given below \n
///
/// * @ref ComConf_ComGroupSignal_GS_ROE_0_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_0 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_1_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_1 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_2_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_2  \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_3_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_3   \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_4_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_4   \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_5_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_5   \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_6_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_6  \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_7_IMU_A_ST3_HAD_BACKUP_CAN_Tx for transmitting ROE_7  \n
/// if IMU B (RBFS_MMP2_IMUB) variant is activated then Com Signal Id Type for each signal is given below \n
///
/// * @ref ComConf_ComGroupSignal_GS_ROE_0_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_0 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_1_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_1  \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_2_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_2 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_3_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_3 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_4_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_4 \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_5_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_5  \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_6_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_6  \n
/// * @ref ComConf_ComGroupSignal_GS_ROE_6_IMU_B_ST3_IMU_INTERNAL_CAN_Tx for transmitting ROE_7  \n

/// After individual signal transmission signal group also transmitted via @ref Com_SendSignalGroup .\n
/// For IMU A signal group id is @ref ComConf_ComSignalGroup_SG_ROE_IMU_A_ST3_edm6y60q0qq6e5iaka50e3c31_HAD_BACKUP_CAN_Tx .\n
/// For IMU B signal group id is @ref ComConf_ComSignalGroup_SG_ROE_IMU_B_ST3_7zavpp3siu6s2eitdaqxg7lwg_IMU_INTERNAL_CAN_Tx


void rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(SwcDiag_RoERecordType RoERecord_ST3);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */

#endif /* RBL_CUSTIF_ROE_IMU_A_ST3_H__ */
