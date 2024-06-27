/// @file rbl_CustIf_PN14_Master_Stat1_ST3.c
/// @brief This file provides definitions PN14_Master_Stat1_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_PN14_Master_Stat1_ST3.h"

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "Rte_rbl_CustIf.h"
#endif
/* ***** END_SECTION Includes ***** */

static boolean rbl_CustIf_Pn14_Signal_Timeout = FALSE;

/* ***** SECTION Definitions ***** */

/// RBMESG definition for signals related to PN14_Master_Stat1_ST3 pdu for reception
RBMESG_DefineMESG (PN14_TransMd_Stat_ST3);
RBMESG_DefineMESG (PN14_DDP_Sw_Stat_ST3);
RBMESG_DefineMESG (PN14_ProdMd_Stat_ST3);
RBMESG_DefineMESG (PN14_ProdMd_BatStat_ST3);
RBMESG_DefineMESG (PN14_SupBat_Stat_ST3);
RBMESG_DefineMESG (PN14_SupBat_Volt_ST3 );
RBMESG_DefineMESG (PN14_SupBat_Curr_ST3);
RBMESG_DefineMESG (PN14_SupBat_Temp_ST3);
RBMESG_DefineMESG (PN14_PNSec_RechargeEnable_ST3);
RBMESG_DefineMESG (PN14_ExtBat_Charge_Actv_ST3);
RBMESG_DefineMESG (PN14_DDP_Sw2_Stat_ST3);

/// RBMESG definition for signals related to PN14_Master_Stat1_ST3 pdu for tranmission
RBMESG_DefineMESG (rbl_CustIf_PN14_TransMd_Stat_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_ProdMd_Stat_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_ProdMd_BatStat_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_SupBat_Stat_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_SupBat_Volt_ST3 );
RBMESG_DefineMESG (rbl_CustIf_PN14_SupBat_Curr_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_SupBat_Temp_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
RBMESG_DefineMESG (rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);

/* ***** END_SECTION Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3(void)
{
    rbl_CustIf_Pn14_Signal_Timeout = TRUE;
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive *****/
void rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive (void)
{

    static uint8 StatusFlag = 0x00;
    Dem_EventStatusType EventStatus;

    #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        VAR(Std_ReturnType, AUTOMATIC) l_ret_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3;
    #endif

    /* local varaibles creation for RBMESG varibles */
    RBMESG_DefineMESGDef (PN14_TransMd_Stat_ST3);
    RBMESG_DefineMESGDef (PN14_DDP_Sw_Stat_ST3);
    RBMESG_DefineMESGDef (PN14_ProdMd_Stat_ST3);
    RBMESG_DefineMESGDef (PN14_ProdMd_BatStat_ST3);
    RBMESG_DefineMESGDef (PN14_SupBat_Stat_ST3);
    RBMESG_DefineMESGDef (PN14_SupBat_Volt_ST3 );
    RBMESG_DefineMESGDef (PN14_SupBat_Curr_ST3);
    RBMESG_DefineMESGDef (PN14_SupBat_Temp_ST3);
    RBMESG_DefineMESGDef (PN14_PNSec_RechargeEnable_ST3);
    RBMESG_DefineMESGDef (PN14_ExtBat_Charge_Actv_ST3);
    RBMESG_DefineMESGDef (PN14_DDP_Sw2_Stat_ST3);


    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /*  Powernet transport mode status           */
    RBMESG_RcvMESG (l_PN14_TransMd_Stat_ST3,PN14_TransMd_Stat_ST3);

    /* Deep discharge protection switch state   */
    RBMESG_RcvMESG (l_PN14_DDP_Sw_Stat_ST3,PN14_DDP_Sw_Stat_ST3);

    /* Powernet production mode state           */
    RBMESG_RcvMESG (l_PN14_ProdMd_Stat_ST3,PN14_ProdMd_Stat_ST3);

    /*  Actual 12V battery state during production mode   */
    RBMESG_RcvMESG  (l_PN14_ProdMd_BatStat_ST3,PN14_ProdMd_BatStat_ST3);

    /*             Supply battery state                     */
    RBMESG_RcvMESG (l_PN14_SupBat_Stat_ST3,PN14_SupBat_Stat_ST3);

    /*  Supply battery voltage                                */
    RBMESG_RcvMESG (l_PN14_SupBat_Volt_ST3,PN14_SupBat_Volt_ST3 );

    /*  Supply battery current                                */
    RBMESG_RcvMESG (l_PN14_SupBat_Curr_ST3,PN14_SupBat_Curr_ST3);

    /*   Supply battery temperature                         */
    RBMESG_RcvMESG (l_PN14_SupBat_Temp_ST3,PN14_SupBat_Temp_ST3);

    /*  Enable for Recharge Secondary-Batterie                */
    RBMESG_RcvMESG (l_PN14_PNSec_RechargeEnable_ST3,PN14_PNSec_RechargeEnable_ST3);

    /* external barttery charging detected               */
    RBMESG_RcvMESG (l_PN14_ExtBat_Charge_Actv_ST3,PN14_ExtBat_Charge_Actv_ST3);

    /*  State of DDP Switch2 (Always On Switch)           */
    RBMESG_RcvMESG (l_PN14_DDP_Sw2_Stat_ST3,PN14_DDP_Sw2_Stat_ST3);

    /* *************** check the recieved signals are valid *****************   */

    if(rbl_CustIf_Pn14_Signal_Timeout == FALSE)
    {
        /* Check if recieved signal TransMd_Stat_ST3 valid  */
        if((l_PN14_TransMd_Stat_ST3 != I_C02_TRANSMD_STAT_OFF  ) && (l_PN14_TransMd_Stat_ST3 != I_C02_TRANSMD_STAT_TEMP_OFF  )
                && (l_PN14_TransMd_Stat_ST3 != I_C02_TRANSMD_STAT_ACTV ))
        {
            StatusFlag |= RBL_CUSTIF_TRANSMD_STAT_ST3_POS;     /* signal invalid */
            l_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_SNA;

        }
        /* Check if recieved signal PN14_ProdMd_Stat_ST3 valid  */
        if((l_PN14_ProdMd_Stat_ST3 != I_C03_PN14_PRODMD_STAT_ST3_OFF ) && (l_PN14_ProdMd_Stat_ST3 != I_C03_PN14_PRODMD_STAT_ST3_ON )&&
                (l_PN14_ProdMd_Stat_ST3 != I_C03_PN14_PRODMD_STAT_ST3_SF01 ) &&  (l_PN14_ProdMd_Stat_ST3 != I_C03_PN14_PRODMD_STAT_ST3_SF02 )&&
                (l_PN14_ProdMd_Stat_ST3 != I_C03_PN14_PRODMD_STAT_ST3_SF03 ))
        {
            StatusFlag |= RBL_CUSTIF_PRODMD_STAT_ST3_POS ;             /* signal invalid */
            l_PN14_ProdMd_Stat_ST3  = I_C03_PN14_PRODMD_STAT_ST3_SNA;
        }

        /* check if received signal PN14_DDP_Sw_Stat_ST3 is valid */
        if ((l_PN14_DDP_Sw_Stat_ST3 != I_C03_PN14_TDP_SW_STAT_CLS) &&   ( l_PN14_DDP_Sw_Stat_ST3 != I_C03_PN14_TDP_SW_STAT_PRE_RESET) &&
                (l_PN14_DDP_Sw_Stat_ST3 != I_C03_PN14_TDP_SW_STAT_RESET) && ( l_PN14_DDP_Sw_Stat_ST3 != I_C03_PN14_TDP_SW_STAT_PRE_OPN) &&
                (l_PN14_DDP_Sw_Stat_ST3 != I_C03_PN14_TDP_SW_STAT_OPN))
        {
            StatusFlag |=  RBL_CUSTIF_DDPSW_STAT_ST3_POS;        /* signal invalid */
            l_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_SNA;
        }
        /* check if received signal SupBat_Volt_ST3 is valid */
        if (l_PN14_SupBat_Volt_ST3 > 1022)
        {
            StatusFlag |= RBL_CUSTIF_SUPBAT_VOLT_ST3_POS;        /* signal invalid */
            l_PN14_SupBat_Volt_ST3 = I_C10_V_0_25K55_0K025_SNA;
        }

        /* if signals are not valid then report to dem prefailed */
        if (StatusFlag == 0x00)
        {
            EventStatus = DEM_EVENT_STATUS_PREPASSED;
        }
        else
        {
            EventStatus = DEM_EVENT_STATUS_PREFAILED;
            /* resetting status flag */
            StatusFlag = 0x00;
        }
    }
    else
    {
        l_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_SNA;
        l_PN14_ProdMd_Stat_ST3  = I_C03_PN14_PRODMD_STAT_ST3_SNA;
        l_PN14_SupBat_Volt_ST3  = I_C10_V_0_25K55_0K025_SNA;
        /* Reset flag */
        rbl_CustIf_Pn14_Signal_Timeout     = FALSE;
    }
    /*Report error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3, EventStatus);

    #if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        l_ret_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3 = Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3(l_PN14_DDP_Sw_Stat_ST3);
    #endif

    /******************** send the recieved signals through RBMESG variables ***********************/

    /* Used only for the SWC Diag */

    RBMESG_SendMESG(rbl_CustIf_PN14_TransMd_Stat_ST3,l_PN14_TransMd_Stat_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_ProdMd_Stat_ST3,l_PN14_ProdMd_Stat_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_SupBat_Volt_ST3,l_PN14_SupBat_Volt_ST3);

    /* note : currently below mentioned signal are not used by any application components */
    RBMESG_SendMESG(rbl_CustIf_PN14_DDP_Sw_Stat_ST3,l_PN14_DDP_Sw_Stat_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_ProdMd_BatStat_ST3,l_PN14_ProdMd_BatStat_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_SupBat_Stat_ST3,l_PN14_SupBat_Stat_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_SupBat_Curr_ST3,l_PN14_SupBat_Curr_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_SupBat_Temp_ST3,l_PN14_SupBat_Temp_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,l_PN14_PNSec_RechargeEnable_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,l_PN14_ExtBat_Charge_Actv_ST3);
    RBMESG_SendMESG(rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,l_PN14_DDP_Sw2_Stat_ST3);
}
/* ***** END_API rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive ***** */
/* ***** END_SECTION API functions ***** */
