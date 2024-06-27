/// @file rbl_CustIf_VehSpd_Disp_ST3.h
/// @brief This header provides definitions for VehSpd_Disp_ST3 signal related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_VEHSPD_DISP_ST3_H_
#define RBL_CUSTIF_VEHSPD_DISP_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */

/* Constants and Macro definitions */

/// maximum vehicle speed
#define RBL_CUSTIF_MAX_VEHSPD  255

/// minimum vehicle speed
#define RBL_CUSTIF_MIN_VEHSPD  0

/* This value is directly taken from arxml files because of that its not following "rbl_" prefix */
/// vehicle speed invalid
#define I_C12_KM_P_H_0_409K4_0K1_SNA  4095

///   RBMSG for VehSpd_Disp_ST3 (Displayed vehicle speed (without attenuation)) signal reception
RBMESG_DefineMESGType_u16(VehSpd_Disp_ST3);
RBMESG_DeclareMESG(VehSpd_Disp_ST3);

///   RBMSG for VehSpd_Disp_ST3 (Displayed vehicle speed (without attenuation)) signal tranmission
RBMESG_DefineMESGType_u16(rbl_CustIf_VehSpd_Disp_ST3);
RBMESG_DeclareMESG(rbl_CustIf_VehSpd_Disp_ST3);

extern uint16 rbl_dcom_VehSpd_Disp_ST3;
/* ***** END_SECTION Definitions ***** */

/// @c_file  rbl_CustIf_VehSpd_Disp_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include VehSpd_Disp_ST3.puml
/// @enduml
/// Function receives the VehSpd_Disp_ST3 signal from ComScl via @ref RBMESG_VehSpd_Disp_ST3 variable,
/// after the reception checks if the data received is valid, If yes, then there is no error reported @ref Dem_ReportErrorStatus.\n
/// otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_VEHSPD_DISP_ST3 error to Dem via @ref Dem_ReportErrorStatus.\n
/// and the signal value is updated to @ref I_C12_KM_P_H_0_409K4_0K1_SNA value and transmitted over @ref RBMESG_rbl_CustIf_VehSpd_Disp_ST3 \n
/// if the data is valid then the received value is scaled down by scaling factor 10 , if the scaled down value is exceeds the
/// @ref RBL_CUSTIF_MAX_VEHSPD (maximum value) then it will be limited to @ref RBL_CUSTIF_MAX_VEHSPD (maximum value)and
/// transmitted over @ref RBMESG_rbl_CustIf_VehSpd_Disp_ST3 .\n
/// valid values for VehSpd_Disp_ST3 is from 0 to 4094 \n
/// @note invalid value includes @ref I_C12_KM_P_H_0_409K4_0K1_SNA and any other value other than valid values

void rbl_CustIf_VehSpd_Disp_ST3_Receive (void);

#endif /* RBL_CUSTIF_VEHSPD_DISP_ST3_H_ */
