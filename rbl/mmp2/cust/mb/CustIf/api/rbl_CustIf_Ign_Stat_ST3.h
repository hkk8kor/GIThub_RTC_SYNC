/// @file rbl_CustIf_Ign_Stat_ST3.h
/// @brief This header provides definitions for ESP_HAD_BACKUP_GW_Container2_ST3_Ign_Stat_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_IGN_STAT_ST3_H_
#define RBL_CUSTIF_IGN_STAT_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// Ignition lock
#define   I_C03_ISW_STAT_IGN_LOCK    0
/// Ignition off
#define   I_C03_ISW_STAT_IGN_OFF     1
/// Ignition accessory
#define   I_C03_ISW_STAT_IGN_ACC     2
/// Ignition on
#define   I_C03_ISW_STAT_IGN_ON      4
/// Ignition start
#define   I_C03_ISW_STAT_IGN_START   5
/// SNA Value from data type
#define   I_C03_ISW_STAT_SNA         7


/* Structure definitions */

/// structure type for Ign_Stat_ST3 pdu group signals
typedef struct
{
 uint16 CRC_Ign_Stat_Pr5_ST3;                      ///< CRC-checksum of signal group according to AUTOSAR Profile 5
 uint8 SQC_Ign_Stat_Pr5_ST3;                       ///< Sequence counter
 uint8 ISw_Stat_ST3;                               ///< Ignition switch state
 uint8  Veh_Op_Mode_ST3;                           ///< Operating Mode Vehicle
 boolean KG_StartSw_Psd_ST3;                       ///< Keyless Go start switch pressed
} rbl_CustIf_Ign_Stat_ST3_t;

///  RBMESG for Ign_Stat_ST3 (ignition state) pdu relared Group signals for reception
RBMESG_DefineMESGType_ST(Ign_Stat_ST3, rbl_CustIf_Ign_Stat_ST3_t);
RBMESG_DeclareMESG(Ign_Stat_ST3);


///  RBMESG for Ign_Stat_ST3 (ignition state) pdu relared Group signals for transmission
RBMESG_DefineMESGType_ST(rbl_CustIf_Ign_Stat_ST3, rbl_CustIf_Ign_Stat_ST3_t);
RBMESG_DeclareMESG(rbl_CustIf_Ign_Stat_ST3);

/* ***** END_SECTION Definitions ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_Ign_Stat_ST3.c
/// @brief This API will be called if time out occurs
/// Application can perform the condition checks and required actions if any.
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_Ign_Stat_ST3(void);


/// @c_file  rbl_CustIf_Ign_Stat_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include Ign_Stat_ST3.puml
/// @enduml
/// If Ign_Stat_ST3 pdu reception is not successfull i.e., time-out happened for Ign_Stat_ST3 pdu
/// then signal updated with @ref I_C03_ISW_STAT_SNA.\n
/// Otherwise function receives the Ign_Stat_ST3 group signal from ComScl via @ref RBMESG_Ign_Stat_ST3 variable,
/// after the reception check if the data received for the structure member "ISw_Stat_ST3" is valid.\n
/// If yes, then there is no error reported to @ref Dem_ReportErrorStatus, and the received signal will be transmitted
/// over @ref RBMESG_rbl_CustIf_Ign_Stat_ST3.\n
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_Ign_Stat_ST3 error to Dem via @ref Dem_ReportErrorStatus
/// and ISw_Stat_ST3 signal is updated with @ref I_C03_ISW_STAT_SNA value and it will be transmitted via
/// @ref RBMESG_rbl_CustIf_Ign_Stat_ST3 .\n
/// Below are the valid values for ISw_Stat_ST3 signal
/// * @ref I_C03_ISW_STAT_IGN_LOCK
/// * @ref I_C03_ISW_STAT_IGN_OFF
/// * @ref I_C03_ISW_STAT_IGN_ACC
/// * @ref I_C03_ISW_STAT_IGN_ON
/// * @ref I_C03_ISW_STAT_IGN_START
///
/// @note invalid value includes @ref I_C03_ISW_STAT_SNA and any other value other than valid values
/// If thrid party software is RBFS_ThirdPartySoftware_ON the recived ISw_Stat_ST3 signal sent to RTE using
/// "Rte_Write_P_Ign_Stat_Pr5_ST3_Ign_Stat_Pr5_ST3" function
void rbl_CustIf_Ign_Stat_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */


#endif /* RBL_CUSTIF_IGN_STAT_ST3_H_ */
