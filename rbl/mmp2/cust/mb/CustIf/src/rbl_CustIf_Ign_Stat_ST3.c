/// @file rbl_CustIf_Ign_Stat_ST3.c
/// @brief This contains implementation details for service related to PDU
/// ESP_HAD_BACKUP_GW_Container2_ST3_Ign_Stat_ST3
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Ign_Stat_ST3.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
    #include "Rte_rbl_CustIf.h"
    #include "Rte_Type.h"
#endif

/* ***** END_SECTION Includes ***** */

static boolean rbl_CustIf_Ign_Stat_ST3_Timeout = FALSE;

/* ***** SECTION  Definitions ***** */

/// RBMESG definition for group signals related to Ign_Stat_ST3 reception
RBMESG_DefineMESG(Ign_Stat_ST3);

/// RBMESG definition for group signals related to Ign_Stat_ST3 for transmission
RBMESG_DefineMESG(rbl_CustIf_Ign_Stat_ST3);


/* ***** END_SECTION  Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_Ign_Stat_ST3(void)
{
    rbl_CustIf_Ign_Stat_ST3_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_Ign_Stat_ST3_PDU_Receive *****/

void rbl_CustIf_Ign_Stat_ST3_PDU_Receive (void)
{
    #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        Ssa_IgnitionStatusType Ssa_IgnitionStatus_Msg;
    #endif

    Dem_EventStatusType EventStatus;

    /*local varaible created for RBMESG variables */
    RBMESG_DefineMESGDef(Ign_Stat_ST3);

    /********************  Reception  of group signals from com scl through RBMESG variables ***********************/

    /* reception of Ign_Stat_ST3 pdu related group signals */
    RBMESG_RcvMESG (l_Ign_Stat_ST3, Ign_Stat_ST3);

    #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        Ssa_IgnitionStatus_Msg.ISw_Stat_ST3 = 0;
    #endif

    if(rbl_CustIf_Ign_Stat_ST3_Timeout == FALSE)
    {
        /* check if the received  ISw_Stat_ST3 is valid */
        switch(l_Ign_Stat_ST3.ISw_Stat_ST3)
        {
           case I_C03_ISW_STAT_IGN_LOCK:
           case I_C03_ISW_STAT_IGN_OFF:
           case I_C03_ISW_STAT_IGN_ACC:
           case I_C03_ISW_STAT_IGN_ON:
           case I_C03_ISW_STAT_IGN_START:
               EventStatus = DEM_EVENT_STATUS_PREPASSED;                /*signal valid */
               break;
           case I_C03_ISW_STAT_SNA:
           default:
               EventStatus = DEM_EVENT_STATUS_PREFAILED;                /*signal invalid */
               l_Ign_Stat_ST3.ISw_Stat_ST3 = I_C03_ISW_STAT_SNA;
               break;
        }
    }
    else
    {
        l_Ign_Stat_ST3.ISw_Stat_ST3 = I_C03_ISW_STAT_SNA;
        /* Reset flag */
        rbl_CustIf_Ign_Stat_ST3_Timeout = FALSE;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_Ign_Stat_ST3, EventStatus);
    /******************** send the recieved group signals through RBMESG variables ***********************/

    /* sending Ign_Stat_ST3 pdu related group signals through RBMESG varible */
    RBMESG_GROUP_LOCK
    RBMESG_SendMESG_GROUP(rbl_CustIf_Ign_Stat_ST3,l_Ign_Stat_ST3);
    RBMESG_GROUP_UNLOCK

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)

    Ssa_IgnitionStatus_Msg.ISw_Stat_ST3 = l_Ign_Stat_ST3.ISw_Stat_ST3;
    (void)Rte_Write_P_Ign_Stat_Pr5_ST3_Ign_Stat_Pr5_ST3(&Ssa_IgnitionStatus_Msg);
#endif

}

/* ***** END_API rbl_CustIf_Ign_Stat_ST3_PDU_Receive ***** */

/* ***** END_SECTION API functions ***** */
