/// @file rbl_CustIf_Meas_IMU_X_ST3.h
/// @brief This header provides definitions for Meas_IMU_X_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_MEAS_IMU_X_ST3_H_
#define RBL_CUSTIF_MEAS_IMU_X_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
#include "StbM.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */


/* Shift Definitions */
#define RBL_CUSTIF_ONE_BYTE_SHIFT                                           8U
#define RBL_CUSTIF_TWO_BYTES_SHIFT                                          16U
#define RBL_CUSTIF_THREE_BYTES_SHIFT                                        24U


/// @c_file  rbl_CustIf_Meas_IMU_X_ST3.c
/// @brief   The Function transmits Measurement IMUA (Meas_IMU_A_ST3)and IMUB (Meas_IMU_B_ST3) PDU related signals.
/// @pre     periodically called from rbl_CustIf_20ms_Proc for every 20 ms
/// @param[in,out] syncRecordTableBlock :Provides the structure of Record table Block Data related to global time Synchronization.
/// @return    : none
/// @details
/// Function receives GTS related data from dcom an transmit the data to com by using @ref rbl_CustIf_Meas_IMU_X_ST3_Msg
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[x] ([x indicating 00 t0 22])filled with respective data from syncRecordTableBlock in big endian format. \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[0-3] filled with GlbSeconds data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[4-7] filled with GlbNanoSeconds data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[8]   filled with TimeBaseStatus data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[9-12]  filled with VirtualLocalTimeLow data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[13-14] filled with RateDeviation data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[15-18] filled with LocSeconds data \n
///  rbl_CustIf_Meas_IMU_X_ST3_Msg[19-22] filled with LocNanoSeconds data \n
/// if IMU A (RBFS_MMP2_IMUA ) variant is activated then Com Signal Id Type for signal is given below \n
/// * @ref ComConf_ComGroupSignal_GS_Meas_IMU_A_XX_ST3_HAD_BACKUP_CAN_Tx [XX indicating 01 t0 23]
/// if IMU A (RBFS_MMP2_IMUB ) variant is activated then Com Signal Id Type for signal is given below \n
/// * @ref ComConf_ComGroupSignal_GS_Meas_IMU_B_XX_ST3_IMU_INTERNAL_CAN_Tx [XX indicating 01 t0 23]
/// After individual signal transmission signal group also transmitted via @ref Com_SendSignalGroup .\n
/// For IMU A signal group id is @ref ComConf_ComSignalGroup_SG_Meas_IMU_A_ST3_3n5lsz3gjs8xv6brvjbxgbhhx_HAD_BACKUP_CAN_Tx .\n
/// For IMU B signal group id is @ref ComConf_ComSignalGroup_SG_Meas_IMU_B_ST3_9b4k5uqw790qkzbaaznvwy423_IMU_INTERNAL_CAN_Tx

void rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(const StbM_SyncRecordTableBlockType *syncRecordTableBlock);

#endif /* RBL_CUSTIF_MEAS_IMU_X_ST3_H_ */
