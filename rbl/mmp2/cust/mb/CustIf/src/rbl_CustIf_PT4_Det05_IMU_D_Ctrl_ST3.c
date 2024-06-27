/// @file rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.c
/// @brief This c files provides definitions for IMU driving can related signal trasmissions
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h"

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
    #include "rbl_CustIf_TiSync.h"
#endif
/* ***** END_SECTION Includes ***** */

/* ***** SECTION  Definitions ***** */


/// RBMESG varible for IMU signal data
RBMESG_DefineMESG(rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3);

/// Static variable IMU Driving Can signal data
static rbl_CustIf_IMU_D_Det05_ST3_PT4_st rbl_CustIf_ImuDrivingSigData;

static const CompuMethod rbl_CustIf_Driving_compu_param[3] =
{
/* {Scale, Offset, LowerLimit, UpperLimit}*/
{RBL_CUSTIF_DRIVING_Acc_X_Y_Z_SCALE, RBL_CUSTIF_DRIVING_Acc_X_Y_Z_OFFSET, RBL_CUSTIF_DRIVING_Acc_X_Y_Z_PHY_LOWER_LIMIT, RBL_CUSTIF_DRIVING_Acc_X_Y_Z_PHY_UPPER_LIMIT}  // acc is param[0]
,{RBL_CUSTIF_DRIVING_Rate_X_Y_Z_SCALE,  RBL_CUSTIF_DRIVING_Rate_X_Y_Z_OFFSET,  RBL_CUSTIF_DRIVING_Rate_X_Y_Z_PHY_LOWER_LIMIT,  RBL_CUSTIF_DRIVING_Rate_X_Y_Z_PHY_UPPER_LIMIT} // rate is param[1]
,{RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_SCALE,  RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_OFFSET,  RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_PHY_LOWER_LIMIT,  RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_PHY_UPPER_LIMIT} // angacc is param[2]
};

static void rbl_CustIf_Prepare_IMU_D_Signal_Status(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                    const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet);

static void rbl_CustIf_Prepare_IMU_D_Signals(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
        const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);

static uint8 rbl_CustIf_IMU_D_PrepareStatus(uint8 Status);

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
static void rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(uint32 MMPtimeStamp);
#endif

/* ***** END_SECTION  Definitions ***** */
/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_Prepare_IMU_D_Signal_Status *****/
static uint8 rbl_CustIf_IMU_D_PrepareStatus(uint8 Status)
{
    uint8 ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_INIT;
    /*     IMU Driving can sensor signals staus calculated based on priority order
           status is calculated from the bit position and X,Y,Z axis status received from signal chain
          priority order of status is INIT >PRMNT_FAIL >TMP_FAIL > STAT_OK
    */
    if(TRUE == Bfx_GetBit_u8u8_u8(Status,RBL_CUSTIF_INIT_STATUS_BIT_POS))
    {
        ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_INIT;
    }
    else if(TRUE == Bfx_GetBit_u8u8_u8(Status,RBL_CUSTIF_PERM_STATUS_BIT_POS))
    {
        ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_PRMNT_FAIL;
    }
    else if(TRUE == Bfx_GetBit_u8u8_u8(Status,RBL_CUSTIF_TEMP_STATUS_BIT_POS))
    {
        ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_TMP_FAIL;
    }
    else
    {
        ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
    }

    return ret_SigStaus;
}
/* ***** END_API rbl_CustIf_Prepare_IMU_D_Signal_Status ***** */

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_Prepare_IMU_D_Signal_Status *****/
static void rbl_CustIf_Prepare_IMU_D_Signal_Status(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet)
{
    /* function calculates the IMU Driving can signal status from signal chain */
    /* 1. VehAccel_X_Stat_ST3 , IMU_D_VehAccel_Y_Stat_ST3 and IMU_D_VehAccel_Z _Stat_ST3 calculated from LinAccX,LinAccY,LinAccZ status respectively
     * ie, from signal chain filtered signal acceleration status
     * 2.IMU_D_VehRollRate_Stat_ST3 calculated from  AngRateX status ie, from signal chain filtered signal rate X status
     * 3.IMU_D_VehPitchRate_Stat_ST3 status calculated from AngRateY status ie, from signal chain filtered signal rate Y status
     * 4.IMU_D_VehYawRate_Stat_ST3 status calculated from AngRateZ status ie, from signal chain filtered signal rate Z status
     * 5.IMU_D_VehRollAccel_Stat_ST3 Status calculated from AngAccX status ie,from signal chain derived signal rate X status
     * 6.IMU_D_VehPitchAccel_Stat_ST3 Status calculated from AngAccY status ie,from signal chain derived signal rate Y status
     * 7.IMU_D_VehYawAccel_Stat_ST3 Status calculated from AngAccZ status ie,from signal chain derived signal rate Z status
     */

    /****************        Status for IMU_D_VehAccel_X_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_X_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].status);

    /****************      Status for  IMU_D_VehRollRate_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollRate_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status);

    /****************    Status for  IMU_D_VehRollAccel_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollAccel_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status);

    /****************    Status for  IMU_D_VehAccel_Y_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Y_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].status);

    /****************    Status for  IMU_D_VehYawRate_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawRate_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status);

    /****************    Status for  IMU_D_VehYawAccel_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawAccel_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status);

    /****************    Status for  IMU_D_VehAccel_Z_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Z_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].status);

    /****************    Status for  IMU_D_VehPitchRate_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitchRate_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status);

    /****************    Status for  IMU_D_VehPitchAccel_Stat_ST3  *************/
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitchAccel_Stat_ST3 = rbl_CustIf_IMU_D_PrepareStatus (Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status);

}
/* ***** END_API rbl_CustIf_Prepare_IMU_D_Signal_Status ***** */

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_Prepare_IMU_D_Signals *****/
static void rbl_CustIf_Prepare_IMU_D_Signals(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
        const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet)
{

float32 formulaAcc,formulaRate,formulaAngAcc;
uint8 RawSignalSetx,RawSignalSety,RawSignalSetz;

    /* function calculates the IMU Driving can signals from signal chain */
    /* 1. IMU_D_VehAccel_X_ST3 , IMU_D_VehAccel_Y_ST3 and IMU_D_VehAccel_Z_ST3 calculated from LinAccX,LinAccY,LinAccZ status respectively
     * ie, from signal chain filtered signal acceleration
     * 2.IMU_D_VehRollRate_ST3 calculated from  AngRateX status ie, from signal chain filtered signal rate X value
     * 3.IMU_D_VehPitchRate_ST3 status calculated from AngRateY status ie, from signal chain filtered signal rate Y value
     * 4.IMU_D_VehYawRate_ST3 status calculated from AngRateZ status ie, from signal chain filtered signal rate Z value
     * 5.IMU_D_VehRollAccel_ST3 Status calculated from AngAccX status ie,from signal chain derived signal rate X value
     * 6.IMU_D_VehPitch_Accel_ST3 Status calculated from AngAccY status ie,from signal chain derived signal rate Y value
     * 7.IMU_D_VehYawAccel_ST3 Status calculated from AngAccZ status ie,from signal chain derived signal rate Z value
     */
 /******************************************Sensitivity of SMU ********************************************************************/
    /* For each Linear Axis exists an array with four values, to provide redundancy
     * For Axis X we agree to use the first value of the redundancy array
     * sensitivity of SMU (also used to define the unit for the internal acc signals in float) is 5000LSB/g
     * That means, that an acceleration of 1g is represented by a value of 5000 in the acceleration IMU signals
     * The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
     * The MMP2 has a resolution of 1/5000 = 0.0002g. For Z axis calculation without g value is considerd
       */
    /* for rate sensitivity of SMU (also used to define the unit for the internal rot signals in float) is 100LSB/degree/sec
    * That means, that an rotation of 1degree/sec is represented by a value of 100 in the rotation IMU signals
    * The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
    * The MMP2 has a resolution of 1/100 = 0.01 degree/sec.
    * */
    /* for derived rate signals sensitivity of SMU (also used to define the unit for the internal rot signals in float) is 100LSB/degree/sec
     * derived acc signals are calculated as delta over 1ms
     * That means, that an angular acceleration of 1degree/s^2 is represented by a value of 100.000 in the derived rotation IMU signals
     * The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
     * */
 /**********************************************************************************************************************************/


    CompuMethod const *paramAcc = &rbl_CustIf_Driving_compu_param[0];
    CompuMethod const *paramRate = &rbl_CustIf_Driving_compu_param[1];
    CompuMethod const *paramAngAcc = &rbl_CustIf_Driving_compu_param[2];

    /* In future for z axis acceleration calculation -1g needs to be considerd  */
    formulaAcc = (float32)RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_PER_G / RBL_CUSTIF_G_TO_MS2;
    formulaRate =  (float32) RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG;
    formulaAngAcc = (float32) RBL_CUSTIF_SENSITIVITY_DELTA_ROT_LSB_PER_DEG_PER_S2;

    /* raw signals values  */
    RawSignalSetx = RawSignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].status;
    RawSignalSety = RawSignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].status;
    RawSignalSetz = RawSignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].status;

    /* acceleration signals */
    if ((RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSetx)) ||
        (RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSety)) ||
        (RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSetz)))
    {
        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_X_ST3 = 0;
        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Y_ST3 = 0;
        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Z_ST3 = 0;
    }
    else
    {

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_X_ST3 = rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].value, formulaAcc,paramAcc);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Y_ST3  = rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].value, formulaAcc,paramAcc);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehAccel_Z_ST3 =   rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].value, formulaAcc,paramAcc);
    }

    RawSignalSetx = RawSignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status;
    RawSignalSety = RawSignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status;
    RawSignalSetz = RawSignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status;

    /* rate signal */
    if ((RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSetx)) ||
       (RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSety)) ||
       (RBL_CUSTIF_IMU_D_SENS_STAT_INIT == rbl_CustIf_IMU_D_PrepareStatus(RawSignalSetz)))
    {
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollRate_ST3 = 0;
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollAccel_ST3 = 0;
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawRate_ST3 = 0;
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawAccel_ST3 = 0;
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitchRate_ST3 = 0;
         rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitch_Accel_ST3 = 0;
     }
    else
    {

       rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollRate_ST3 = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].value,formulaRate,paramRate);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehRollAccel_ST3 = rbl_CustIf_Calc_Convert(Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].value, formulaAngAcc,paramAngAcc);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawRate_ST3 = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].value,formulaRate,paramRate);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehYawAccel_ST3 =  rbl_CustIf_Calc_Convert(Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].value, formulaAngAcc,paramAngAcc);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitchRate_ST3 = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].value ,formulaRate,paramRate);

        rbl_CustIf_ImuDrivingSigData.IMU_D_VehPitch_Accel_ST3 = rbl_CustIf_Calc_Convert(Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].value, formulaAngAcc,paramAngAcc);
    }

}
/* ***** END_API rbl_CustIf_Prepare_IMU_D_Signals ***** */

/* *********************************************************************************************************************/

/* ***** Local function: rbl_CustIf_Prepare_timeStamp *****/
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
static void rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(uint32 MMPtimeStamp)
{

    Std_ReturnType retVal = E_NOT_OK;
    static StbM_TimeStampType MMPtimeStampGTS_st = {0};

    rbl_CustIf_TiSync_MMP2GtsTime_AMG(MMPtimeStamp, &MMPtimeStampGTS_st);


    rbl_CustIf_ImuDrivingSigData.IMU_D_VehDynData_TmStmp_Sec_ST3 = MMPtimeStampGTS_st.seconds;
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehDynData_TmStmp_NanoSec_ST3 = MMPtimeStampGTS_st.nanoseconds;
    rbl_CustIf_ImuDrivingSigData.IMU_D_VehDynData_TmSyncStat_ST3 = MMPtimeStampGTS_st.timeBaseStatus;

}
#endif

/* ***** Local function: rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update *****/
void rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData,
                                          const rbl_ImuStdTypes_ImuSignalSet_t *imu_derivedData)
{

		RBMESG_DefineMESGDef(SigChain_FinalRaw);

        /* read raw signal values */
        RBMESG_RcvMESGDef(SigChain_FinalRaw);
        /* prepare imu driving Can signals */

        /* prepare imu driving can signal status */
        rbl_CustIf_Prepare_IMU_D_Signal_Status (imu_FilData,imu_derivedData);

        /* prepare imu driving can signal status */
        rbl_CustIf_Prepare_IMU_D_Signals(imu_FilData,imu_derivedData,&l_SigChain_FinalRaw);

        rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(imu_FilData->timeStamp);

        /* below mentioned signal contains same values (SNA or 0) in init state and periodic state */
        rbl_CustIf_ImuDrivingSigData.Rsrv01_PT4_Det05_IMU_D_Ctrl_Pr5_ST3 = 0;
        rbl_CustIf_ImuDrivingSigData.Rsrv02_PT4_Det05_IMU_D_Ctrl_Pr5_ST3 = 0;


   /* write signal values for COMSCL processing */
   RBMESG_GROUP_LOCK
   RBMESG_SendMESG_GROUP(rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3, rbl_CustIf_ImuDrivingSigData);
   RBMESG_GROUP_UNLOCK
}
/* ***** END_API rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update ***** */

