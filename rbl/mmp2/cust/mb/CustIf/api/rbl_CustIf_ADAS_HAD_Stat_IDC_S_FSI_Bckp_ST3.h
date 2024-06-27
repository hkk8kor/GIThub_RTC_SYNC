/// @file rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.h
/// @brief This header provides definitions for ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_ADAS_HAD_STAT_IDC_S_FSI_BCKP_ST3_H_
#define RBL_CUSTIF_ADAS_HAD_STAT_IDC_S_FSI_BCKP_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// HAD_OFF
#define  I_C3_HAD_EXT_STAT_ST3_HAD_OFF               0
/// HAD_IN_PREPARATION
#define  I_C3_HAD_EXT_STAT_ST3_HAD_IN_PREPARATION    1
/// HAD FADE IN
#define  I_C3_HAD_EXT_STAT_ST3_HAD_FADE_IN           2
/// HAD ON
#define  I_C3_HAD_EXT_STAT_ST3_HAD_ON                3
/// HAD FADE OUT
#define  I_C3_HAD_EXT_STAT_ST3_HAD_FADE_OUT          4
/// SNA Value from data type
#define  I_C3_HAD_EXT_STAT_ST3_SNA                   7

/* Structure definitions */

/// structure type for ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 pdu group signals
typedef struct
{
 uint16 CRC_ADAS_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3;                      ///< CRC-checksum of signal group according to AUTOSAR Profile 5
 uint8 SQC_ADAS_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3;                       ///< Sequence counter
 uint8 ADAS_HAD_Ext_Stat_S_FSI_Bckp_ST3;                               ///< Drive Assistance Package Highly Automated Driving State Satelite
 uint8  Rsrv1_ADAS_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3;                    ///< Reserved for future purpose
 uint32 Rsrv2_ADAS_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3;                    ///< Reserved for future purpose
} rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_t;

///  RBMESG for ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 pdu relared Group signals for reception
RBMESG_DefineMESGType_ST(ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3, rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_t);
RBMESG_DeclareMESG(ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3);

/* ***** END_SECTION Definitions ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.c
/// @brief This API will be called if time out occurs
/// Application can perform the condition checks and required actions if any.
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3(void);


/// @c_file  rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.puml
/// @enduml
/// If ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 pdu reception is not successfull i.e., time-out happened for ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 pdu
/// then signal updated with @ref I_C3_HAD_EXT_STAT_ST3_SNA.\n
/// Otherwise function receives the ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 group signal from ComScl via @ref RBMESG_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 variable,
/// after the reception check if the data received for the structure member "ADAS_HAD_Ext_Stat_S_FSI_Bckp_ST3" is valid.\n
/// If yes, then there is no error reported to @ref Dem_ReportErrorStatus, and the received signal will be transmitted
/// over @ref RBMESG_rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.\n
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_S_FSI_Bckp_Pr5_ST3 error to Dem via @ref Dem_ReportErrorStatus.\n
/// Below are the valid values for ADAS_HAD_Ext_Stat_S_FSI_Bckp_ST3 signal
/// * @ref I_C3_HAD_EXT_STAT_ST3_HAD_OFF
/// * @ref I_C3_HAD_EXT_STAT_ST3_HAD_IN_PREPARATION
/// * @ref I_C3_HAD_EXT_STAT_ST3_HAD_FADE_IN
/// * @ref I_C3_HAD_EXT_STAT_ST3_HAD_ON
/// * @ref I_C3_HAD_EXT_STAT_ST3_HAD_FADE_OUT
///
/// @note invalid value includes @ref I_C3_HAD_EXT_STAT_ST3_SNA and any other value other than valid values

void rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */


#endif /* RBL_CUSTIF_ADAS_HAD_STAT_IDC_S_FSI_BCKP_ST3_H_ */
