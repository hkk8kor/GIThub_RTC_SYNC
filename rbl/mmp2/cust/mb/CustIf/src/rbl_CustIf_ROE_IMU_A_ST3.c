/// @file rbl_CustIf_ROE_IMU_A_ST3.c
/// @brief This source file provides definitions for ROE_IMU_A_ST3 pdu related service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** SECTION Includes ***** */
#include "rbl_CustIf_ROE_IMU_A_ST3.h"


/* Include other headers here */

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local function Definitions ***** */

/* ***** END_SECTION Local function Definitions ***** */


/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_ROE_IMU_A_ST3_PDU_Update *****/
void rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(SwcDiag_RoERecordType RoERecord_ST3)
{

    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
        /*Updating signal values for Com*/
        /*Response on Event signals*/
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_0_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_0);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_1_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_1);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_2_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_2);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_3_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_3);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_4_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_4);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_5_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_5);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_6_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_6);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_7_IMU_A_ST3_HAD_BACKUP_CAN_Tx,&RoERecord_ST3.ROE_7);

        (void) Com_SendSignalGroup(ComConf_ComSignalGroup_SG_ROE_IMU_A_ST3_edm6y60q0qq6e5iaka50e3c31_HAD_BACKUP_CAN_Tx);

    #elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        /*Updating signal values for Com*/
        /*Response on Event signals*/
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_0_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_0);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_1_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_1);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_2_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_2);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_3_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_3);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_4_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_4);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_5_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_5);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_6_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_6);
        (void) Com_SendSignal(ComConf_ComGroupSignal_GS_ROE_7_IMU_B_ST3_IMU_INTERNAL_CAN_Tx,&RoERecord_ST3.ROE_7);

        (void) Com_SendSignalGroup(ComConf_ComSignalGroup_SG_ROE_IMU_B_ST3_7zavpp3siu6s2eitdaqxg7lwg_IMU_INTERNAL_CAN_Tx);

    #endif
}
/* ***** END_API rbl_CustIf_ROE_IMU_A_ST3_PDU_Update ***** */

/* ***** END_SECTION API functions ***** */
