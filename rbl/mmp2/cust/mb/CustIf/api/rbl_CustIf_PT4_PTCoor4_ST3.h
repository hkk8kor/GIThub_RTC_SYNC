/// @file rbl_CustIf_PT4_PTCoor4_ST3.h
/// @brief This header provides definitions for PT4_PTCoor4_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_PT4_PTCOOR4_ST3_H_
#define RBL_CUSTIF_PT4_PTCOOR4_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// No combustion start required
#define   I_C03_ENGSTARTPN14_STAT_NO_COMBUSTIONSTART_RQ    0
/// Customer start required
#define   I_C03_ENGSTARTPN14_STAT_CUSTOMER_START_RQ        1
 /// Automatic start without powernet support required
#define   I_C03_ENGSTARTPN14_STAT_AUTO_START_NO_PN_SUP_RQ  2
/// Automatic start with powernet support required
#define   I_C03_ENGSTARTPN14_STAT_AUTO_START_PN_SUP_RQ     3
/// SNA value from data type
#define   I_C03_ENGSTARTPN14_STAT_SNA                      7


/* Structure definitions */

/// structure type for PT4_PTCoor4_ST3 pdu group signals
typedef struct
{
    uint8 PT4_PTCoor_PT_Rdy_ST3;                             ///< CRC-checksum of signal group according to AUTOSAR Profile 5
    uint8 SQC_PT4_PTCoor4_Pr5_ST3;                           ///< Sequence counter
    uint16 CRC_PT4_PTCoor4_Pr5_ST3;                          ///< Powertrain ready
    uint8 PT4_PTCoor_SSA_EngSp_ST3;                          ///< Stop/start automatic has engine stopped
    uint8 PT4_PTCoor_EngStartPN14_Stat_ST3;                  ///< PT4 Engine Start PN14 State
    uint8 Rsrv1_PT4_PTCoor_PT_Rdy_Pr5_ST3;                   ///< Reserved for future use
}rbl_CustIf_PT4_PTCoor4_ST3_t;

/// RBMESG for PT4_PTCoor4_ST3 related group signals for reception
RBMESG_DefineMESGType_ST(PT4_PTCoor4_ST3, rbl_CustIf_PT4_PTCoor4_ST3_t);
RBMESG_DeclareMESG(PT4_PTCoor4_ST3);

/// RBMESG for PT4_PTCoor4_ST3 related group signals for tranmission
RBMESG_DefineMESGType_ST(rbl_CustIf_PT4_PTCoor4_ST3, rbl_CustIf_PT4_PTCoor4_ST3_t);
RBMESG_DeclareMESG(rbl_CustIf_PT4_PTCoor4_ST3);

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_PT4_PTCoor4_ST3.c
/// @brief This API will be called if time out occurs
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_PT4_PTCoor4_ST3(void);


/// @c_file  rbl_CustIf_PT4_PTCoor4_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include PT4_PTCoor4_ST3.puml
/// @enduml
/// If PT4_PTCoor4_ST3 pdu reception is not successfull i.e., time-out happened then PT4_PTCoor_EngStartPN14_Stat_ST3
/// signal updated with I_C03_ENGSTARTPN14_STAT_NO_COMBUSTIONSTART_RQ
/// Otherwise function receives the PT4_PTCoor4_ST3 group signal from ComScl via @ref RBMESG_PT4_PTCoor4_ST3 variable,
/// after the reception check if the data received for the structure member "PT4_PTCoor_EngStartPN14_Stat_ST3" is valid,
/// If yes, then there is no error reported @ref Dem_ReportErrorStatus
/// and the received data will be transmitted via @ref RBMESG_rbl_CustIf_PT4_PTCoor4_ST3.\n
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_PT4_PTCoor4_ST3 error to Dem via @ref Dem_ReportErrorStatus,
/// PT4_PTCoor_EngStartPN14_Stat_ST3 signal value is updated to @ref I_C03_ENGSTARTPN14_STAT_SNA value and transmitted
/// over @ref RBMESG_rbl_CustIf_PT4_PTCoor4_ST3.\n
/// Below are the valid values for signal RBMESG_PT4_PTCoor4_ST3  \n
/// * @ref I_C03_ENGSTARTPN14_STAT_NO_COMBUSTIONSTART_RQ    \n
/// * @ref I_C03_ENGSTARTPN14_STAT_CUSTOMER_START_RQ        \n
/// * @ref I_C03_ENGSTARTPN14_STAT_AUTO_START_NO_PN_SUP_RQ  \n
/// * @ref I_C03_ENGSTARTPN14_STAT_AUTO_START_PN_SUP_RQ     \n
/// @note invalid value includes @ref I_C03_ENGSTARTPN14_STAT_SNA and any other value other than valid values
void rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */
#endif /* RBL_MMP2_CUST_MB_RBL_CUSTIF_API_RBL_CUSTIF_PT4_PTCOOR4_ST3_H_ */
