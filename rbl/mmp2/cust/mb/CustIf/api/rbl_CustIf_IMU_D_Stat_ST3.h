/// @file rbl_CustIf_IMU_D_Stat_ST3.h
/// @brief This header provides definitions for IMU_B driving Can related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_IMU_D_STAT_ST3_H_
#define RBL_CUSTIF_IMU_D_STAT_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/// SNA value for Inertial Sensors #3 identification
#define RBL_CUSTIF_IMU_D_4294967294_1_SNA   4294967295U

/// SNA value for Temperature of vehicle yaw rate sensor element
#define RBL_CUSTIF_IMU_D_DEGC_M70_184_1_SNA  0xFF

typedef struct{
uint32  IMU_D_Id_ST3;                       ///< Inertial Sensors #3 identification
uint8   IMU_D_VehYawRateSens_Temp_ST3;      ///<Tempareture of vehical yaw rate sensor element
}rbl_CustIf_IMU_D_Stat_Pr5_ST3_st;

/// scale for tempertaure
#define RBL_rbl_CustIf_MB_CAN3_Temp_SCALE             ((float32)1.00f)
/// offset for tempertaure
#define RBL_rbl_CustIf_MB_CAN3_Temp_OFFSET            ((float32)-70.0f)
/// lower limit for tempertaure
#define RBL_rbl_CustIf_MB_CAN3_Temp_LOWER_LIMIT       ((float32)0.00f)
/// upper limit for tempertaure
#define RBL_rbl_CustIf_MB_Temp_CAN3_UPPER_LIMIT       ((float32)254.00f)

RBMESG_DefineMESGType_ST(rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_st);
RBMESG_DeclareMESG(rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3);

/// @c_file rbl_CustIf_IMU_D_Stat_ST3.c
/// @brief  The Function receives the signals from signal chain and its transmits the updated signals to comscl via @ref RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3.\n
///  This function Transmits IMU_D_Driving_Container1_ST3_IMU_D_Stat_ST3 pdu related information.
/// @pre periodically called in every 5ms
/// @param[in] void
/// @return none
/// @details
/// IMU_D_Stat_Star3 pdu contains two signals \n
/// 1. IMU_D_Id_ST3 updated with the @ref RBL_CUSTIF_IMU_D_4294967294_1_SNA value
/// 2. IMU_D_VehYawRateSens_Temp_ST3 calculated from filtered signal via  @ref rbl_CustIf_IMU_Prepare_Temp   \n
/// @note below is the diagram  for IMU_D_VehYawRateSens_Temp_ST3 signal preparation \n
/// diagram : VehYawRateSens_Temp_preparation
/// @startuml
/// !include VehYawRateSens_Temp_preparation.puml
/// @enduml


void rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 (const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData);
#endif /* RBL_CUSTIF_IMU_D_STAT_ST3_H_ */
