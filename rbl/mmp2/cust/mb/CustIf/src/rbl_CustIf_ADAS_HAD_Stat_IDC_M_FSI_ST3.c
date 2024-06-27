/// @file rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3.c
/// @brief This contains implementation details for service related to PDU
/// ADAS_HAD_Stat_IDC_M_FSI_ST3
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
    #include "Rte_rbl_CustIf.h"
    #include "Rte_Type.h"
#endif

/* ***** END_SECTION Includes ***** */


/* ***** SECTION  Definitions ***** */

/// RBMESG definition for group signals related to ADAS_HAD_Stat_IDC_M_FSI_ST3 reception
RBMESG_DefineMESG(ADAS_HAD_Stat_IDC_M_FSI_ST3);

static boolean rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_Timeout = FALSE;

/* ***** END_SECTION  Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_ADAS_HAD_Stat_IDC_M_FSI_ST3(void)
{
    rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive *****/

void rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive (void)
{
    Dem_EventStatusType EventStatus;

    /*local varaible created for RBMESG variables */
    RBMESG_DefineMESGDef(ADAS_HAD_Stat_IDC_M_FSI_ST3);

    /********************  Reception  of group signals from com scl through RBMESG variables ***********************/

    /* reception of ADAS_HAD_Stat_IDC_M_FSI_ST3 pdu related group signals */

    RBMESG_RcvMESG (l_ADAS_HAD_Stat_IDC_M_FSI_ST3, ADAS_HAD_Stat_IDC_M_FSI_ST3);

    if(rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_Timeout == FALSE)
     {
         /* Check if recieved signal value is valid for ADAS_HAD_Ext_Stat_M_FSI_ST3  */
         switch(l_ADAS_HAD_Stat_IDC_M_FSI_ST3.ADAS_HAD_Ext_Stat_M_FSI_ST3)
         {
             case I_C3_HAD_EXT_STAT_ST3_HAD_OFF:
             case I_C3_HAD_EXT_STAT_ST3_HAD_IN_PREPARATION:
             case I_C3_HAD_EXT_STAT_ST3_HAD_FADE_IN:
             case I_C3_HAD_EXT_STAT_ST3_HAD_ON:
             case I_C3_HAD_EXT_STAT_ST3_HAD_FADE_OUT:
                 EventStatus = DEM_EVENT_STATUS_PREPASSED;         /*signal valid */
                 break;
             case I_C3_HAD_EXT_STAT_ST3_SNA:
             default:
                EventStatus = DEM_EVENT_STATUS_PREFAILED;         /*signal invalid */
                l_ADAS_HAD_Stat_IDC_M_FSI_ST3.ADAS_HAD_Ext_Stat_M_FSI_ST3 = I_C3_HAD_EXT_STAT_ST3_SNA;
                break;
         }
     }
     else
     {
         l_ADAS_HAD_Stat_IDC_M_FSI_ST3.ADAS_HAD_Ext_Stat_M_FSI_ST3 = I_C3_HAD_EXT_STAT_ST3_SNA;
         /* Reset flag */
         rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_Timeout = FALSE;
     }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
     (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_HAD_Stat_IDC_M_FSI_Pr5_ST3, EventStatus);

}

/* ***** END_API rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_Bckp_ST3_PDU_Receive ***** */

/* ***** END_SECTION API functions ***** */
