/// @file rbl_CustIf_VSS_TP_RealTmOffset_ST3.h
/// @brief This header provides definitions for VSS_TP_RealTmOffset_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express RealTmOffsetorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef  RBL_CUSTIF_VSS_TP_REALTMOFFSET_ST3_H_
#define  RBL_CUSTIF_VSS_TP_REALTMOFFSET_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_ImuStdTypes.h"
#include "Com.h"
#include "RBMESG_Explicit.h"
/* ***** END_SECTION Includes ***** */

/// Structure type for VSS_TP_RealTmOffset_ST3 pdu group signals
typedef struct
{
    uint8 VSS_TP_RealTmOffset_0_ST3;   ///< Real Time Offset 0
    uint8 VSS_TP_RealTmOffset_1_ST3;   ///< Real Time Offset 1
    uint8 VSS_TP_RealTmOffset_2_ST3;   ///< Real Time Offset 2
    uint8 VSS_TP_RealTmOffset_3_ST3;   ///< Real Time Offset 3
    uint8 VSS_TP_RealTmOffset_4_ST3;   ///< Real Time Offset 4
    uint8 VSS_TP_RealTmOffset_5_ST3;   ///< Real Time Offset 5
    uint8 VSS_TP_RealTmOffset_6_ST3;   ///< Real Time Offset 6
    uint8 VSS_TP_RealTmOffset_7_ST3;   ///< Real Time Offset 7
}rbl_CustIf_VSS_TP_RealTmOffset_ST3_t;

///  RBMESG Define for reception of group signals of Real Time Offset PDU, VSS_TP_RealTmOffset_ST3
RBMESG_DefineMESGType_ST(VSS_TP_RealTmOffset_ST3, rbl_CustIf_VSS_TP_RealTmOffset_ST3_t);
RBMESG_DeclareMESG(VSS_TP_RealTmOffset_ST3);

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file  rbl_CustIf_VSS_TP_RealTmOffset_ST3.c
/// @pre Spontaneous called whenever the signal group of VSS_TP_RealTmOffset_ST3 pdu is received
/// @param[in]  id : Type of Pdu Id
/// @param[in]  ptr : the pointer reference to basic information (SDU (payload), Meta Data of the PDU, corresponding length of the SDU in bytes) about VSS_TP_RealTmOffset_ST3 pdu
/// @return none
/// @details Write the received data to RTE port via @ref Rte_Write_P_VSS_TP_RealTmOffset_ST3_VSS_TP_RealTmOffset_ST3 function.

extern void rbl_CustIf_SgnGrp_Cbk_VSS_TP_RealTmOffset_ST3(PduIdType id, const PduInfoType *ptr);
/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */
#endif /*  rbl_CustIf_VSS_TP_RealTmOffset_ST3_H_ */
