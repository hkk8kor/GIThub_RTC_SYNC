/// @file rbl_CustIf_VSS_TP_SharedSecret_ST3.h
/// @brief This header provides definitions for VSS_TP_SharedSecret_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef  RBL_CUSTIF_VSS_TP_SHAREDSECRET_ST3_H_
#define  RBL_CUSTIF_VSS_TP_SHAREDSECRET_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_ImuStdTypes.h"
#include "Com.h"
#include "RBMESG_Explicit.h"
/* ***** END_SECTION Includes ***** */

/// Structure type for VSS_TP_SharedSecret_ST3 pdu group signals
typedef struct
{
    uint8 VSS_TP_SharedSecret_0_ST3;    ///< Shared Secret signal 0
    uint8 VSS_TP_SharedSecret_1_ST3;    ///< Shared Secret signal 1
    uint8 VSS_TP_SharedSecret_2_ST3;    ///< Shared Secret signal 2
    uint8 VSS_TP_SharedSecret_3_ST3;    ///< Shared Secret signal 3
    uint8 VSS_TP_SharedSecret_4_ST3;    ///< Shared Secret signal 4
    uint8 VSS_TP_SharedSecret_5_ST3;    ///< Shared Secret signal 5
    uint8 VSS_TP_SharedSecret_6_ST3;    ///< Shared Secret signal 6
    uint8 VSS_TP_SharedSecret_7_ST3;    ///< Shared Secret signal 7
}rbl_CustIf_VSS_TP_SharedSecret_t;

///  RBMESG Define for reception of group signals of Shared Secret PDU, VSS_TP_SharedSecret_ST3
RBMESG_DefineMESGType_ST(VSS_TP_SharedSecret_ST3, rbl_CustIf_VSS_TP_SharedSecret_t);
RBMESG_DeclareMESG(VSS_TP_SharedSecret_ST3);

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file  rbl_CustIf_VSS_TP_SharedSecret_ST3.c
/// @pre Spontaneous called whenever the signal group of VSS_TP_SharedSecret_ST3 pdu is received
/// @param[in]  id : Type of Pdu Id
/// @param[in]  ptr : the pointer reference to basic information (SDU (payload), Meta Data of the PDU, corresponding length of the SDU in bytes) about VSS_TP_SharedSecret_ST3 pdu
/// @return none
/// @details Write the received data to RTE port via @ref Rte_Write_P_VSS_TP_SharedSecret_ST3_VSS_TP_SharedSecret_ST3 function.

extern void rbl_CustIf_SgnGrp_Cbk_VSS_TP_SharedSecret_ST3(PduIdType id, const PduInfoType *ptr);
/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */
#endif /*  RBL_CUSTIF_VSS_TP_SHAREDSECRET_ST3_H_ */
