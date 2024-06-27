/// @file rbl_CustIf_DIAG_Stat_ST3.c
/// @brief This file provides definitions DIAG_Stat_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_DIAG_Stat_ST3.h"
/* ***** END_SECTION Includes ***** */

//void rbl_CustIf_TimeOut_Cbk_DIAG_Stat_ST3(void);

static boolean rbl_CustIf_DIAG_Stat_ST3_Timeout = FALSE;

/* ***** SECTION Definitions ***** */

/// RBMESG defintion for  Actv_Line_Stat_ST3 for reception
RBMESG_DefineMESG(Actv_Line_Stat_ST3);

/// RBMESG defintion for  Actv_Line_Stat_ST3 for transmission
RBMESG_DefineMESG(rbl_CustIf_Actv_Line_Stat_ST3);

/// RBMESG defintion for DidA_ExtTest_Pres_ST3 for reception
RBMESG_DefineMESG(DidA_ExtTest_Pres_ST3);


/// RBMESG defintion for DidA_ExtTest_Pres_ST3 for transmission
RBMESG_DefineMESG(rbl_CustIf_DidA_ExtTest_Pres_ST3);

/* ***** END_SECTION Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_DIAG_Stat_ST3(void)
{
    rbl_CustIf_DIAG_Stat_ST3_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_DIAG_Stat_ST3_PDU_Receive *****/

void rbl_CustIf_DIAG_Stat_ST3_PDU_Receive (void)
{
    Dem_EventStatusType EventStatus;

    /* local varaibles creation for RBMESG varibles */
    RBMESG_DefineMESGDef(Actv_Line_Stat_ST3);
    RBMESG_DefineMESGDef(DidA_ExtTest_Pres_ST3);

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /* Activation Line state              */
    RBMESG_RcvMESG (l_Actv_Line_Stat_ST3, Actv_Line_Stat_ST3);

    /* DidA external tester present        */
    RBMESG_RcvMESG (l_DidA_ExtTest_Pres_ST3,DidA_ExtTest_Pres_ST3);

    if(rbl_CustIf_DIAG_Stat_ST3_Timeout == FALSE)
    {
        /* Check if recieved signal value is valid for DidA_ExtTest_Pres_ST3  */
        switch(l_DidA_ExtTest_Pres_ST3)
        {
           case I_C02_NDEF_FALSE_TRUE_ST3_FALSE:
           case I_C02_NDEF_FALSE_TRUE_ST3_TRUE:
               EventStatus = DEM_EVENT_STATUS_PREPASSED;         /*signal valid */
               break;
           case I_C02_NDEF_FALSE_TRUE_ST3_SNA:
           default:
               EventStatus = DEM_EVENT_STATUS_PREFAILED;         /*signal invalid */
               l_DidA_ExtTest_Pres_ST3 = I_C02_NDEF_FALSE_TRUE_ST3_SNA;
               break;
        }
    }
    else
    {
        l_DidA_ExtTest_Pres_ST3 = I_C02_NDEF_FALSE_TRUE_ST3_SNA;
        /* Reset flag */
        rbl_CustIf_DIAG_Stat_ST3_Timeout = FALSE;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3, EventStatus);
    /******************** send the recieved signals through RBMESG variables ***********************/

    RBMESG_SendMESG(rbl_CustIf_DidA_ExtTest_Pres_ST3,l_DidA_ExtTest_Pres_ST3);

    /* currently below mentioned signal not used by any application components */
    RBMESG_SendMESG(rbl_CustIf_Actv_Line_Stat_ST3,l_Actv_Line_Stat_ST3);
}

/* ***** END_API rbl_CustIf_DIAG_Stat_ST3_PDU_Receive ***** */

/* ***** END_SECTION API functions ***** */
