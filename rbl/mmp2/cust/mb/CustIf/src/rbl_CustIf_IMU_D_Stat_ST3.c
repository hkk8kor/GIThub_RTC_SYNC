/// @file rbl_CustIf_IMU_D_Stat_ST3.c
/// @brief This c files provides definitions for IMU driving can related signal trasmissions
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_IMU_D_Stat_ST3.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION  Definitions ***** */

/// RBMESG varible for IMU signal data
RBMESG_DefineMESG(rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3);

static void rbl_CustIf_IMU_D_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);

static rbl_CustIf_IMU_D_Stat_Pr5_ST3_st rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData;

static const CompuMethod rbl_CustIf_CAN3_compu_param[1] =
{
    /* {Scale, Offset, LowerLimit, UpperLimit}*/
  {RBL_rbl_CustIf_MB_CAN3_Temp_SCALE, RBL_rbl_CustIf_MB_CAN3_Temp_OFFSET, RBL_rbl_CustIf_MB_CAN3_Temp_LOWER_LIMIT, RBL_rbl_CustIf_MB_Temp_CAN3_UPPER_LIMIT} // temp
};

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 *****/
static void rbl_CustIf_IMU_D_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet)
{
    // Process data structure to keep float precision when retrieving data
    float32 l_TempSmu = 0.0f;
    float32 Converted_Value;
    // Calculate the temperature value and converted in to float
    l_TempSmu =  (((float32)SignalSet->temp[0].value + RBL_CUSTIF_OFFSET_TEMP_AT_0LSB_PER_C)/ RBL_CUSTIF_SENSITIVITY_TEMP_LSB_PER_K );

    // Calculate the temperature value converted from physical value to int
    Converted_Value = rbl_CustIf_Calc_CompuMethod_Phy2Int(rbl_CustIf_CAN3_compu_param[0],l_TempSmu);

    /* float to unisgned integer converion */
    rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData.IMU_D_VehYawRateSens_Temp_ST3 = RB_FloatToInt_f32_u8(Converted_Value);
}

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 *****/

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 *****/

void rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 (const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData)
{

    /* all the signals of IMU_D_Driving_Container1_ST3_IMU_D_Stat_ST3 pdu updated with corresponding invalid values
     * mentioned in arxml file
     */
    rbl_CustIf_IMU_D_Prepare_Temp(imu_FilData);
    rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData.IMU_D_Id_ST3 = RBL_CUSTIF_IMU_D_4294967294_1_SNA;

    /* write signal values for COMSCL processing */
    RBMESG_GROUP_LOCK
    RBMESG_SendMESG_GROUP(rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData);
    RBMESG_GROUP_UNLOCK


}

/* ***** END_API rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 ***** */
