/// @file rbl_CustIf_VehSpd_Disp_ST3.c
/// @brief This file provides definitions VehSpd_Disp_ST3 signal related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_VehSpd_Disp_ST3.h"

/* ***** END_SECTION Includes ***** */

//Dcom VehSpd_Disp_ST3 global variable
uint16 rbl_dcom_VehSpd_Disp_ST3 =0x00;
/// VehSpd_Disp_ST3 reception signal
RBMESG_DefineMESG(VehSpd_Disp_ST3);

/// VehSpd_Disp_ST3 transmission signal
RBMESG_DefineMESG(rbl_CustIf_VehSpd_Disp_ST3);

/* ***** SECTION Local Definitions ***** */
/* ***** Local Function decleration ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_VehSpd_Disp_ST3_Receive *****/
void rbl_CustIf_VehSpd_Disp_ST3_Receive (void)
{
    uint16 l_VehSpd_Disp;
    Dem_EventStatusType EventStatus;

    /* local varaibles creation for RBMESG varibles */
    RBMESG_DefineMESGDef(VehSpd_Disp_ST3);

    RBMESG_DefineMESGDef(rbl_CustIf_VehSpd_Disp_ST3);

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /*  reception of  Displayed vehicle speed (without attenuation)   */
    RBMESG_RcvMESG (l_VehSpd_Disp_ST3, VehSpd_Disp_ST3);

    RBMESG_RcvMESG (rbl_dcom_VehSpd_Disp_ST3, VehSpd_Disp_ST3);

    /* Check if the received signal is valid */
    if (l_VehSpd_Disp_ST3 <= 4094)
    {
        EventStatus = DEM_EVENT_STATUS_PREPASSED;

        //store the reception signal in to another local varaible
        l_VehSpd_Disp = l_VehSpd_Disp_ST3;


         /* scale down received value by scaling factor 10 and stored in to transmission local variable*/
        l_rbl_CustIf_VehSpd_Disp_ST3= l_VehSpd_Disp / 10  ;

         /*  checking if the vehicle speed exceeded the upper limit  */
         if(l_rbl_CustIf_VehSpd_Disp_ST3 > RBL_CUSTIF_MAX_VEHSPD)
         {
             l_rbl_CustIf_VehSpd_Disp_ST3 = 255U;
         }
    }
    else
    {
       /* signal is invalid */
        EventStatus = DEM_EVENT_STATUS_PREFAILED;
        l_rbl_CustIf_VehSpd_Disp_ST3 = I_C12_KM_P_H_0_409K4_0K1_SNA;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_VEHSPD_DISP_ST3, EventStatus);

     /******************** send the vehicle updated vehicle speed through RBMESG variables ***********************/
    RBMESG_SendMESG(rbl_CustIf_VehSpd_Disp_ST3,l_rbl_CustIf_VehSpd_Disp_ST3);
}
/* ***** END_API rbl_CustIf_VehSpd_Disp_ST3_Receive ***** */
/* ***** END_SECTION API functions ***** */
