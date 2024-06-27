/// @file rbl_CustIf_PT4_PTCoor4_ST3.c
/// @brief This file provides definitions PT4_PTCoor4_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_PT4_PTCoor4_ST3.h"
/* ***** END_SECTION Includes ***** */

static boolean rbl_CustIf_PT4_PTCoor4_ST3_Timeout = FALSE;

/* ***** SECTION Definitions ***** */

/// RBMESG definition for group signals related to PT4_PTCoor4_ST3 for reception
RBMESG_DefineMESG(PT4_PTCoor4_ST3);

/// RBMESG definition for group signals related to PT4_PTCoor4_ST3 for reception
RBMESG_DefineMESG(rbl_CustIf_PT4_PTCoor4_ST3);

/* ***** END_SECTION Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_PT4_PTCoor4_ST3(void)
{
    rbl_CustIf_PT4_PTCoor4_ST3_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive *****/
void rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive (void)
{

    Dem_EventStatusType EventStatus;

    /* local varible created for RBMESG variables */
    RBMESG_DefineMESGDef(PT4_PTCoor4_ST3);

    /********************  Reception  of group signals from com scl through RBMESG variables ***********************/

    /* reception of PT4_PTCoor4_ST3 pdu related group signals */
    RBMESG_RcvMESG (l_PT4_PTCoor4_ST3, PT4_PTCoor4_ST3);

    if(rbl_CustIf_PT4_PTCoor4_ST3_Timeout == FALSE)
    {
        /* Check if the received signal PT4_PTCoor_EngStartPN14_Stat_ST3 is valid */
        switch(l_PT4_PTCoor4_ST3.PT4_PTCoor_EngStartPN14_Stat_ST3)
        {
            case I_C03_ENGSTARTPN14_STAT_NO_COMBUSTIONSTART_RQ:
            case I_C03_ENGSTARTPN14_STAT_CUSTOMER_START_RQ:
            case I_C03_ENGSTARTPN14_STAT_AUTO_START_NO_PN_SUP_RQ:
            case I_C03_ENGSTARTPN14_STAT_AUTO_START_PN_SUP_RQ:
                  EventStatus = DEM_EVENT_STATUS_PREPASSED;                                      /*signal valid */
                  break;
            case I_C03_ENGSTARTPN14_STAT_SNA:
            default:
                  EventStatus = DEM_EVENT_STATUS_PREFAILED;                                        /*signal invalid */
                  l_PT4_PTCoor4_ST3.PT4_PTCoor_EngStartPN14_Stat_ST3 = I_C03_ENGSTARTPN14_STAT_SNA;
                  break;
        }
    }
    else
    {
        l_PT4_PTCoor4_ST3.PT4_PTCoor_EngStartPN14_Stat_ST3 = I_C03_ENGSTARTPN14_STAT_NO_COMBUSTIONSTART_RQ;
        /* Reset flag */
        rbl_CustIf_PT4_PTCoor4_ST3_Timeout = FALSE;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PT4_PTCoor4_ST3, EventStatus);

    /******************** send the recieved group signals through RBMESG variables ***********************/

    /* sending PT4_PTCoor4_ST3 pdu related group signals through RBMESG varible */
    RBMESG_GROUP_LOCK
    RBMESG_SendMESG_GROUP(rbl_CustIf_PT4_PTCoor4_ST3,l_PT4_PTCoor4_ST3);
    RBMESG_GROUP_UNLOCK

}
/* ***** END_API rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive ***** */
/* ***** END_SECTION API functions ***** */
