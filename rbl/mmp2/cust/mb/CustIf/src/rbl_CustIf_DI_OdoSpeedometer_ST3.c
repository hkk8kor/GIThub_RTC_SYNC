/// @file rbl_CustIf_DI_OdoSpeedometer_ST3.c
/// @brief This file provides definitions DI_OdoSpeedometer_ST3 pdu related services
/// related to PDU DI_OdoSpeedometer_ST3
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_DI_OdoSpeedometer_ST3.h"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "Rte_rbl_CustIf.h"
#endif
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */

/// RBMESG defintion for  DI_OdoSpeedometer_ST3 signal for reception
RBMESG_DefineMESG(DI_OdoSpeedometer_ST3);
/// RBMESG defintion for  DI_OdoSpeedometer_ST3 signal for transmission
RBMESG_DefineMESG(rbl_CustIf_OdoSpeedometer_ST3);

static boolean rbl_CustIf_DI_OdoSpeedometer_ST3_Timeout = FALSE;

/* ***** END_SECTION Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_DI_OdoSpeedometer_ST3(void)
{
    rbl_CustIf_DI_OdoSpeedometer_ST3_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive *****/

void rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive (void)
{
    Dem_EventStatusType EventStatus;

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
    Ssa_OdometerRecordType rbl_CustIf_DI_OdoSpeedometer_ST3;
#endif

    /* local varaibles creation for RBMESG varibles */
    RBMESG_DefineMESGDef(DI_OdoSpeedometer_ST3);

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    if (rbl_CustIf_DI_OdoSpeedometer_ST3_Timeout == FALSE)
    {
        /* Reception of odometer group signal  */
        RBMESG_RcvMESG (l_DI_OdoSpeedometer_ST3, DI_OdoSpeedometer_ST3);

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        if(l_DI_OdoSpeedometer_ST3.Odo_ST3 >= rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA_INVLD)
        {
            rbl_CustIf_DI_OdoSpeedometer_ST3.Odo_ST3 = rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA_SNA;
        }

        Rte_Write_P_Odo_Pr5_ST3_DI_Odo_Pr5_ST3(&rbl_CustIf_DI_OdoSpeedometer_ST3);
#endif
        /* Chcek if recieved Odo_ST3 signal value is valid  */
        if (l_DI_OdoSpeedometer_ST3.Odo_ST3 <= 9999999 )
        {
            EventStatus = DEM_EVENT_STATUS_PREPASSED;
        }
        else
        {
            EventStatus = DEM_EVENT_STATUS_PREFAILED;
        }
    }
    else
    {
        l_DI_OdoSpeedometer_ST3.Odo_ST3 = rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA_SNA;
        /* Reset flag */
        rbl_CustIf_DI_OdoSpeedometer_ST3_Timeout = FALSE;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_DI_OdoSpeedometer_ST3, EventStatus);

    /******************** send the recieved group signals through RBMESG variables ***********************/

    RBMESG_SendMESG(rbl_CustIf_OdoSpeedometer_ST3,l_DI_OdoSpeedometer_ST3);

}

/* ***** END_API rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive ***** */

/* ***** END_SECTION API functions ***** */
