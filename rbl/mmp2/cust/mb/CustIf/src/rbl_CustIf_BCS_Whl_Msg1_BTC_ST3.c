/// @file rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.c
/// @brief This file provides definitions BCS_Whl_Msg1_BTC_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h"

static uint8 rbl_CustIf_TimedOut_Counter_u8 = 0;
static boolean rbl_CustIf_TimedOut_flag_b = FALSE;

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */

/// RBMESG definition for group signals related to BCS_Whl_Msg1_BTC_Pr5_ST3 pdu
RBMESG_DefineMESG(BCS_Whl_Msg1_BTC_Pr5_ST3);

/// RBMESG varible for GTS_ESP_Clk_Stat_Bckp_ST3 transmission
RBMESG_DefineMESG(rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
/* ***** END_SECTION Definitions ***** */

void rbl_CustIf_TimeOut_Cbk_BCS_Whl_Msg1_BTC_ST3(void)
{
    rbl_CustIf_TimedOut_flag_b = TRUE;
}

/* ***** Local Function Definition ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive *****/

void rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive (void)
{

    Dem_EventStatusType EventStatus;

    /* local varaibles creation for RBMESG varibles */
    RBMESG_DefineMESGDef(rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);

    /********************  Reception  of signals from com scl through RBMESG variables ***********************/

    /*  reception of rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 signals   */
    RBMESG_RcvMESG_StMemberu8(l_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, BCS_Whl_Msg1_BTC_Pr5_ST3.GTS_ESP_Clk_Stat_Bckp_ST3);

    if (rbl_CustIf_TimedOut_flag_b == FALSE)
    {
        rbl_CustIf_TimedOut_Counter_u8 = 0u;                           /* Reset counter */
        /* Check if recieved signal rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 valid  */
         switch(l_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3)
         {
            case I_C02_GTS_ESP_CLK_STAT_ST3_INIT:
            case I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK:
            case I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_NOK:
                EventStatus = DEM_EVENT_STATUS_PREPASSED;         /*signal valid */
                break;
            default:
                l_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INIT;
                EventStatus = DEM_EVENT_STATUS_PREFAILED;         /*signal invalid */
                break;
         }
    }
    else
    {
        /* Increment the counter */
        rbl_CustIf_TimedOut_Counter_u8++;
        if(rbl_CustIf_TimedOut_Counter_u8 >= 10u)
        {
            l_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_NOK;
        }
        else
        {
            /* Do nothing */
        }
        /* Reset flag */
        rbl_CustIf_TimedOut_flag_b = FALSE;
    }

    /* report the error to dem */
    /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_BCS_Whl_Msg1_BTC_ST3, EventStatus);

    /******************** send the recieved group signals through RBMESG variables ***********************/
    RBMESG_SendMESG(rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3,l_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
}

/* ***** END_API rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive ***** */

/* ***** END_SECTION API functions ***** */
