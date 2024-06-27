/// @file rbl_CustIf_ECU_Stat_IMU_D_ST3.c
/// @brief This file provides definitions ECU_Stat_IMU_B_DRIVING_ST3 pdu related services
/// related to PDU ECU_Stat_IMU_A_ST3
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_ECU_Stat_IMU_D_ST3.h"
#include "rbl_dcom_MB_Pub.h"
#include "rbl_net_AwakeNWStart.h"

/* ***** Local Function decleration ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update *****/

void rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update (void )
{
    rbl_CustIf_ECU_Stat_IMU_X_ST3_t ECU_Stat_IMU_D_Msg;

	/* Update the defalut NW ID */
    ECU_Stat_IMU_D_Msg.NwId_Rsrv_ST3 =0;

    /* Update the MB ECU ID of IMU */
	ECU_Stat_IMU_D_Msg.ECU_Id_IMU_X_ST3= RBL_CUSTIF_IMU_ECU_ID;

	/* Update the Wakeup network name */
    ECU_Stat_IMU_D_Msg.WakeupRsn_IMU_X_ST3 = RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW;

    /* Update if awake reason is Active Diagnostics */
    ECU_Stat_IMU_D_Msg.Awake_Diag_Actv_IMU_X_ST3 = rbl_dcomActiveDiagSession;

    /* Update if awake reason is Network */
    ECU_Stat_IMU_D_Msg.Awake_NwStart_IMU_X_ST3 = rbl_net_GetAwakeNwStartStatus();

    (void) Com_SendSignal(ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_DRIVING_CAN_Tx,&ECU_Stat_IMU_D_Msg.ECU_Id_IMU_X_ST3);

    /* Signal to close the gap in ECU-Stat-PDUs for ECUs w/o NW-ID */
    (void) Com_SendSignal(ComConf_ComSignal_S_NwId_Rsrv_ST3_DRIVING_CAN_Tx,&ECU_Stat_IMU_D_Msg.NwId_Rsrv_ST3);

    /*  Wakeup reason signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_DRIVING_CAN_Tx,&ECU_Stat_IMU_D_Msg.WakeupRsn_IMU_X_ST3);

    /* Stay awake for diagnostics active signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_DRIVING_CAN_Tx,&ECU_Stat_IMU_D_Msg.Awake_Diag_Actv_IMU_X_ST3);

    /* Stay awake for network startup signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_DRIVING_CAN_Tx,&ECU_Stat_IMU_D_Msg.Awake_NwStart_IMU_X_ST3);
}

/* ***** END_API rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update ***** */

/* ***** END_SECTION API functions ***** */
