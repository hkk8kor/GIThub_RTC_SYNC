/// @file rbl_CustIf_FBL_Cfg_Star3_ST3.h
/// @brief This header provides definitions for FBL_Cfg_Star3_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_FBL_CFG_STAR3_ST3_H_
#define RBL_CUSTIF_FBL_CFG_STAR3_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// Not defined state
#define I_C08_PLATFORM_STAT_IDLE     0
/// platform star 1
#define I_C08_PLATFORM_STAT_STAR1    1
/// platform star 2
#define I_C08_PLATFORM_STAT_STAR2    2
/// platform star 3
#define I_C08_PLATFORM_STAT_STAR3    4
/// reserved
#define I_C08_PLATFORM_STAT_RES8     8
/// reserved
#define I_C08_PLATFORM_STAT_RES16    16
/// reserved
#define I_C08_PLATFORM_STAT_RES32    32
/// reserved
#define I_C08_PLATFORM_STAT_RES64    64
/// reserved
#define I_C08_PLATFORM_STAT_RES128   128
///SNA value from data type
#define  I_C08_PLATFORM_STAT_SNA     255

/// RBMSEG for Platform State signal for reception
RBMESG_DefineMESGType_u8(Platform_Stat_Star3);
RBMESG_DeclareMESG(Platform_Stat_Star3);

/// RBMSEG for Platform State signal for transmission
RBMESG_DefineMESGType_u8( rbl_CustIf_Platform_Stat_Star3);
RBMESG_DeclareMESG(rbl_CustIf_Platform_Stat_Star3);

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_FBL_Cfg_Star3_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include FBL_Cfg_Star3_ST3.puml
/// @enduml
/// Function receives the Platform_Stat_Star3 signal from ComScl via @ref RBMESG_Platform_Stat_Star3 variable,
/// after the reception checks if the data is valid. If yes, then there is no error reported @ref Dem_ReportErrorStatus
/// and the same received signal data will be transmitted via @ref RBMESG_rbl_CustIf_Platform_Stat_Star3.
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3 error to Dem via @ref Dem_ReportErrorStatus
/// and @ref I_C08_PLATFORM_STAT_SNA value is transmitted via @ref RBMESG_rbl_CustIf_Platform_Stat_Star3. \n
/// below are the valid values for Platform_Stat_Star3 signal \n
/// * @ref I_C08_PLATFORM_STAT_IDLE
/// * @ref I_C08_PLATFORM_STAT_STAR1
/// * @ref I_C08_PLATFORM_STAT_STAR2
/// * @ref I_C08_PLATFORM_STAT_STAR3
/// * @ref I_C08_PLATFORM_STAT_RES8
/// * @ref I_C08_PLATFORM_STAT_RES16
/// * @ref I_C08_PLATFORM_STAT_RES32
/// * @ref I_C08_PLATFORM_STAT_RES64
/// * @ref I_C08_PLATFORM_STAT_RES128
///
/// @note invalid value includes @ref I_C08_PLATFORM_STAT_SNA and any other value other than valid values

void rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */


#endif /* RBL_CUSTIF_FBL_CFG_STAR3_ST3_H_ */
