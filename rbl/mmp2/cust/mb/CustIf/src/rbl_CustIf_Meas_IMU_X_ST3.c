/// @file rbl_CustIf_Meas_IMU_X_ST3.c
/// @brief This source file provides definitions for Meas_IMU_X_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Meas_IMU_X_ST3.h"
/* ***** END_SECTION Includes ***** */

/// array for measurement pdu
static uint8 rbl_CustIf_Meas_IMU_X_ST3_Msg[64];
/* ***** SECTION  Definitions ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf__Meas_IMU_X_ST3_PDU_Update *****/

void rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(const StbM_SyncRecordTableBlockType *syncRecordTableBlock)
{

        /* Convert 1 measurement to fit Data array*/
    rbl_CustIf_Meas_IMU_X_ST3_Msg[0]  = (uint8)(syncRecordTableBlock->GlbSeconds >> RBL_CUSTIF_THREE_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[1] =  (uint8)(syncRecordTableBlock->GlbSeconds >> RBL_CUSTIF_TWO_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[2]  = (uint8)(syncRecordTableBlock->GlbSeconds >> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[3] =  (uint8)(syncRecordTableBlock->GlbSeconds);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[4]  = (uint8)(syncRecordTableBlock->GlbNanoSeconds >>RBL_CUSTIF_THREE_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[5] =  (uint8)(syncRecordTableBlock->GlbNanoSeconds >> RBL_CUSTIF_TWO_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[6]  = (uint8)(syncRecordTableBlock->GlbNanoSeconds >> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[7]  = (uint8)(syncRecordTableBlock->GlbNanoSeconds);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[8]  = syncRecordTableBlock->TimeBaseStatus;
    rbl_CustIf_Meas_IMU_X_ST3_Msg[9]  = (uint8)(syncRecordTableBlock->VirtualLocalTimeLow >> RBL_CUSTIF_THREE_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[10] = (uint8)(syncRecordTableBlock->VirtualLocalTimeLow >> RBL_CUSTIF_TWO_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[11] = (uint8)(syncRecordTableBlock->VirtualLocalTimeLow >> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[12] = (uint8)(syncRecordTableBlock->VirtualLocalTimeLow);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[13] = (uint8)((uint16)(syncRecordTableBlock->RateDeviation )>> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[14] = (uint8)(syncRecordTableBlock->RateDeviation);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[15] = (uint8)(syncRecordTableBlock->LocSeconds >> RBL_CUSTIF_THREE_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[16] = (uint8)(syncRecordTableBlock->LocSeconds >> RBL_CUSTIF_TWO_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[17] = (uint8)(syncRecordTableBlock->LocSeconds >> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[18] = (uint8)(syncRecordTableBlock->LocSeconds);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[19] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> RBL_CUSTIF_THREE_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[20] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> RBL_CUSTIF_TWO_BYTES_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[21] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> RBL_CUSTIF_ONE_BYTE_SHIFT);
    rbl_CustIf_Meas_IMU_X_ST3_Msg[22] = (uint8)(syncRecordTableBlock->LocNanoSeconds);

    /******************************send data to com ***********************************************************/
#if (RBFS_MMP2 == RBFS_MMP2_IMUA)

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_A_01_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[0]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_02_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[1]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_A_03_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[2]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_04_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[3]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_05_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[4]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_06_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[5]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_07_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[6]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_08_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[7]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_09_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[8]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_10_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[9]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_11_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[10]);

    (void)  Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_A_12_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[11]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_13_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[12]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_14_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[13]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_15_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[14]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_A_16_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[15]);

    (void) Com_SendSignal(ComConf_ComGroupSignal_GS_Meas_IMU_A_17_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[16]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_A_18_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[17]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_A_19_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[18]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_A_20_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[19]);

    (void) Com_SendSignal(ComConf_ComGroupSignal_GS_Meas_IMU_A_21_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[20]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_A_22_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[21]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_A_23_ST3_HAD_BACKUP_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[22]);

    (void) Com_SendSignalGroup (ComConf_ComSignalGroup_SG_Meas_IMU_A_ST3_3n5lsz3gjs8xv6brvjbxgbhhx_HAD_BACKUP_CAN_Tx);

    /* for IMU B related signals */
 #elif (RBFS_MMP2 == RBFS_MMP2_IMUB)

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_01_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[0]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_02_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[1]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_03_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[2]);

    (void) Com_SendSignal ( ComConf_ComGroupSignal_GS_Meas_IMU_B_04_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[3]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_05_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[4]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_06_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[5]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_07_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[6]);

    (void) Com_SendSignal  (ComConf_ComGroupSignal_GS_Meas_IMU_B_08_ST3_IMU_INTERNAL_CAN_Tx,&rbl_CustIf_Meas_IMU_X_ST3_Msg[7]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_09_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[8]);

    (void) Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_B_10_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[9]);

    (void)  Com_SendSignal( ComConf_ComGroupSignal_GS_Meas_IMU_B_11_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[10]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_12_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[11]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_13_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[12]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_14_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[13]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_15_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[14]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_16_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[15]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_17_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[16]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_18_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[17]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_19_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[18]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_20_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[19]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_21_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[20]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_22_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[21]);

    (void) Com_SendSignal (ComConf_ComGroupSignal_GS_Meas_IMU_B_23_ST3_IMU_INTERNAL_CAN_Tx ,&rbl_CustIf_Meas_IMU_X_ST3_Msg[22]);

    (void) Com_SendSignalGroup (ComConf_ComSignalGroup_SG_Meas_IMU_B_ST3_9b4k5uqw790qkzbaaznvwy423_IMU_INTERNAL_CAN_Tx);

#endif
}

/* ***** END_API rbl_CustIf__Meas_IMU_X_ST3_PDU_Update ***** */
