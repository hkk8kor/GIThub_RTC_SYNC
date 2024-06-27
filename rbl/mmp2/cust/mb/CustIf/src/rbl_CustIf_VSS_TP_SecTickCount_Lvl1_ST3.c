/// @file rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.c
/// @brief This file provides definitions VSS_TP_SecTickCount_Lvl1_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.h"
#include "Rte_rbl_CustIf.h"

/* ***** END_SECTION Includes ***** */

///  RBMESG Define for reception of group signals of VIN PDU
RBMESG_DefineMESG (VSS_TP_SecTickCount_Lvl1_ST3);

/* ***** SECTION Local Definitions ***** */

/* *********************************************************************************************************************/

void rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(void)
{
    Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3 = 0x01U;
}

/* *********************************************************************************************************************/
void rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(PduIdType id, const PduInfoType *ptr)
{
    // Write date in to RTE port
    (void)Rte_Write_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3(ptr->SduDataPtr);
}

/* ***** END_API rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3_PDU_Receive ***** */
/* ***** END_SECTION API functions ***** */
