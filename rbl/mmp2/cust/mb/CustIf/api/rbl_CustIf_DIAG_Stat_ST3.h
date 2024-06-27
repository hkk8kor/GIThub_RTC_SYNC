/// @file rbl_CustIf_DIAG_Stat_ST3.h
/// @brief This header provides definitions for DIAG_Stat_ST3_t pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_DIAG_STAT_ST3_H_
#define RBL_CUSTIF_DIAG_STAT_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */

/* Constants and Macro definitions */


/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// Values applicable for DidA external tester present (DidA_ExtTest_Pres_ST3)

/// False
#define  I_C02_NDEF_FALSE_TRUE_ST3_FALSE    1
/// True
#define   I_C02_NDEF_FALSE_TRUE_ST3_TRUE    2
/// SNA value from data type
#define   I_C02_NDEF_FALSE_TRUE_ST3_SNA     3

/// RBMESG for Activation Line state for reception
RBMESG_DefineMESGType_u8(Actv_Line_Stat_ST3);
RBMESG_DeclareMESG(Actv_Line_Stat_ST3);

/// RBMESG for Activation Line state for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_Actv_Line_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_Actv_Line_Stat_ST3);

/// RBMESG for DidA external tester present for reception
RBMESG_DefineMESGType_u8(DidA_ExtTest_Pres_ST3);
RBMESG_DeclareMESG(DidA_ExtTest_Pres_ST3);

/// RBMESG for DidA external tester present for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_DidA_ExtTest_Pres_ST3);
RBMESG_DeclareMESG(rbl_CustIf_DidA_ExtTest_Pres_ST3);

/* ***** END_SECTION Definitions ***** */

/// @c_file rbl_CustIf_DIAG_Stat_ST3.c
/// @brief This API will be called if time out occurs
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_DIAG_Stat_ST3(void);


/// @c_file  rbl_CustIf_DIAG_Stat_ST3.c
/// @param[in] void
/// @return none
/// @startuml
/// !include DIAG_Stat_ST3.puml
/// @enduml
/// @details
/// If DIAG_Stat_ST3 pdu reception is not successfull i.e., time-out happened for DIAG_Stat_ST3 pdu
/// then signal updated with @ref I_C02_NDEF_FALSE_TRUE_ST3_SNA.\n
/// Otherwise function receives the DIAG_Stat_ST3 pdu related signals @ref Actv_Line_Stat_ST3 and
/// @ref DidA_ExtTest_Pres_ST3 signal from ComScl via @ref RBMESG_Actv_Line_Stat_ST3 and
/// @ref RBMESG_DidA_ExtTest_Pres_ST3 varibles respectively. After the reception checks if the data received for the
/// signal "DidA_ExtTest_Pres_ST3" is valid,
/// If yes, then there is no error reported @ref Dem_ReportErrorStatus and the received signals will be transmitted over
/// corresponding RBMESG variables. Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3 error to Dem
/// via @ref Dem_ReportErrorStatus and DidA_ExtTest_Pres_ST3 signal is updated with @ref I_C02_NDEF_FALSE_TRUE_ST3_SNA
/// and same will be transmitted via @ref RBMESG_rbl_CustIf_DidA_ExtTest_Pres_ST3.\n
/// Below are the valid values for DidA_ExtTest_Pres_ST3 signal
/// * @ref I_C02_NDEF_FALSE_TRUE_ST3_FALSE
/// * @ref I_C02_NDEF_FALSE_TRUE_ST3_TRUE
///
/// @note invalid value includes @ref I_C02_NDEF_FALSE_TRUE_ST3_SNA and any other value other than valid values. \n
/// Actv_Line_Stat_ST3 transmitted via @ref RBMESG_rbl_CustIf_Actv_Line_Stat_ST3 And DidA_ExtTest_Pres_ST3 transmitted
/// via @ref RBMESG_rbl_CustIf_DidA_ExtTest_Pres_ST3
void rbl_CustIf_DIAG_Stat_ST3_PDU_Receive(void);

#endif /* RBL_CUSTIF_DIAG_STAT_ST3_H_ */
