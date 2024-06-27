/// @file rbl_CustIf_FBL_Cfg_Star3_ST3.c
/// @brief This file provides definitions FBL_Cfg_Star3_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION  Definitions ***** */

/// RBMESG definition for Platform state signal for reception
RBMESG_DefineMESG(Platform_Stat_Star3);

/// RBMESG definition for Platform state signal for transmission
RBMESG_DefineMESG(rbl_CustIf_Platform_Stat_Star3);

/* ***** END_SECTION  Definitions ***** */

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive *****/
void rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive (void)
{
    Dem_EventStatusType EventStatus;

    /*local varaible created for RBMESG variables */
    RBMESG_DefineMESGDef(Platform_Stat_Star3);

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /*  Platform state reception          */
    RBMESG_RcvMESG (l_Platform_Stat_Star3, Platform_Stat_Star3);

    /* Check if recieved signal value is valid  */
    switch(l_Platform_Stat_Star3)
    {
       case I_C08_PLATFORM_STAT_IDLE:
       case I_C08_PLATFORM_STAT_STAR1:
       case I_C08_PLATFORM_STAT_STAR2:
       case I_C08_PLATFORM_STAT_STAR3:
       case I_C08_PLATFORM_STAT_RES8:
       case I_C08_PLATFORM_STAT_RES16:
       case I_C08_PLATFORM_STAT_RES32:
       case I_C08_PLATFORM_STAT_RES64:
       case I_C08_PLATFORM_STAT_RES128:
           EventStatus = DEM_EVENT_STATUS_PREPASSED;         /*signal valid */
           break;
       case I_C08_PLATFORM_STAT_SNA:
       default:
           EventStatus = DEM_EVENT_STATUS_PREFAILED;         /*signal invalid */
           l_Platform_Stat_Star3 = I_C08_PLATFORM_STAT_SNA;
           break;
    }

     /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3, EventStatus);

    /******************** send the recieved signal through RBMESG variables ***********************/

    /* sending Ign_Stat_ST3 pdu related group signals through RBMESG varible */
    RBMESG_SendMESG(rbl_CustIf_Platform_Stat_Star3,l_Platform_Stat_Star3);

}
/* ***** END_API rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive ***** */

/* ***** END_SECTION API functions ***** */
