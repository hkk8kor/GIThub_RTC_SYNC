/// @file rbl_CustIf_ECU_Stat_IMU_X_ST3.c
/// @brief This file provides definitions ECU_Stat_IMU_A_ST3 and ECU_Stat_IMU_B_ST3 pdu related services
/// related to PDU ECU_Stat_IMU_A_ST3
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_ECU_Stat_IMU_X_ST3.h"
#include "rbl_dcom_MB_Pub.h"
#include "rbl_net_AwakeNWStart.h"


/* ***** END_SECTION Includes ***** */
/* ***** SECTION Local Definitions ***** */
/* ***** Local Function decleration ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update *****/

void rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update (void )
{
    rbl_CustIf_ECU_Stat_IMU_X_ST3_t ECU_Stat_IMU_X_Msg;

    /* Update the defalut NW ID */
    ECU_Stat_IMU_X_Msg.NwId_Rsrv_ST3 = RBL_CUSTIF_IMU_NW_ID;

    /* Update the MB ECU ID of IMU */
    ECU_Stat_IMU_X_Msg.ECU_Id_IMU_X_ST3 = RBL_CUSTIF_IMU_ECU_ID;

    /* Update the Wakeup network name */
    ECU_Stat_IMU_X_Msg.WakeupRsn_IMU_X_ST3 = RBL_CUSTIF_WAKEUPRSN_ST3_EXTCAN_NW;

    /* Update if awake reason is Active Diagnostics */
    ECU_Stat_IMU_X_Msg.Awake_Diag_Actv_IMU_X_ST3 = rbl_dcomActiveDiagSession;

    /* Update if awake reason is Network */
    ECU_Stat_IMU_X_Msg.Awake_NwStart_IMU_X_ST3 = rbl_net_GetAwakeNwStartStatus();

    /* for IMU A related signlas */
 #if (RBFS_MMP2 == RBFS_MMP2_IMUA)

    /*   write signal values for COMSCL processing   */
    /*   cast return value to void in order to explicitly ignor it. Return can be of values: E_OK/COM_SERVICE_NOT_AVAILABLE/COM_BUSY */
    /*   ECU identifier signal                       */
    (void) Com_SendSignal(ComConf_ComSignal_S_ECU_Id_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&ECU_Stat_IMU_X_Msg.ECU_Id_IMU_X_ST3);

    /* Signal to close the gap in ECU-Stat-PDUs for ECUs w/o NW-ID */
    (void) Com_SendSignal(ComConf_ComSignal_S_NwId_Rsrv_ST3_HAD_BACKUP_CAN_Tx,&ECU_Stat_IMU_X_Msg.NwId_Rsrv_ST3);

    /*  Wakeup reason signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_WakeupRsn_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&ECU_Stat_IMU_X_Msg.WakeupRsn_IMU_X_ST3);

    /* Stay awake for diagnostics active signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_Awake_Diag_Actv_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_Diag_Actv_IMU_X_ST3);

    /* Stay awake for network startup signal */
    (void) Com_SendSignal(ComConf_ComSignal_S_Awake_NwStart_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_NwStart_IMU_X_ST3);

    /* for IMU B related signals */
 #elif (RBFS_MMP2 == RBFS_MMP2_IMUB)

        /*   write signal values for COMSCL processing   */
        /*   cast return value to void in order to explicitly ignor it. Return can be of values: E_OK/COM_SERVICE_NOT_AVAILABLE/COM_BUSY */
        /*   ECU identifier signal                       */
        (void) Com_SendSignal(ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_HAD_IMU_CAN_Tx,&ECU_Stat_IMU_X_Msg.ECU_Id_IMU_X_ST3);

        /* Signal to close the gap in ECU-Stat-PDUs for ECUs w/o NW-ID */
        (void) Com_SendSignal(ComConf_ComSignal_S_NwId_HAD_IMU_ST3_CAN_Tx,&ECU_Stat_IMU_X_Msg.NwId_Rsrv_ST3);

        /*  Wakeup reason signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_HAD_IMU_CAN_Tx,&ECU_Stat_IMU_X_Msg.WakeupRsn_IMU_X_ST3);

        /* Stay awake for diagnostics active signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_HAD_IMU_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_Diag_Actv_IMU_X_ST3);

        /* Stay awake for network startup signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_HAD_IMU_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_NwStart_IMU_X_ST3);


        /* Update the defalut NW ID for Internal CAN */
        ECU_Stat_IMU_X_Msg.NwId_Rsrv_ST3 = 0;

        /* signals for IMU B internal trasmission */

        (void) Com_SendSignal(ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&ECU_Stat_IMU_X_Msg.ECU_Id_IMU_X_ST3);

        /* Signal to close the gap in ECU-Stat-PDUs for ECUs w/o NW-ID */
        (void) Com_SendSignal(ComConf_ComSignal_S_NwId_Rsrv_ST3_IMU_INTERNAL_CAN_Tx,&ECU_Stat_IMU_X_Msg.NwId_Rsrv_ST3);

        /*  Wakeup reason signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&ECU_Stat_IMU_X_Msg.WakeupRsn_IMU_X_ST3);

        /* Stay awake for diagnostics active signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_Diag_Actv_IMU_X_ST3);

        /* Stay awake for network startup signal */
        (void) Com_SendSignal(ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&ECU_Stat_IMU_X_Msg.Awake_NwStart_IMU_X_ST3);
#endif
}

/* ***** END_API rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update ***** */

/* ***** END_SECTION API functions ***** */
