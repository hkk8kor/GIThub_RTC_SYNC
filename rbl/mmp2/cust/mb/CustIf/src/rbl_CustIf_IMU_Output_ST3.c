/// @file rbl_CustIf_IMU_Output_ST3.c
/// @brief This header provides definitions for Communication control service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "cc_int_parts.h"

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
    #include "rbl_CustIf_TiSync.h"
#endif
/* Include other headers here */

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */
/* Variables */

/// RBMESG varible for IMU signal data
RBMESG_DefineMESG(rbl_CustIf_IMU_OutPutMsg_ST3);

/// RBMESG variable IMU signal data
static rbl_CustIf_OutputMsg_ST3_st rbl_CustIf_ImuSigData;

static const CompuMethod rbl_CustIf_compu_param[4] =
{
    /* {Scale, Offset, LowerLimit, UpperLimit}*/
    {Acc_X_Y_Z_SCALE, Acc_X_Y_Z_OFFSET, Acc_X_Y_Z_PHY_LOWER_LIMIT, Acc_X_Y_Z_PHY_UPPER_LIMIT}  // acc is param[0]
    ,{Rate_X_Y_Z_SCALE,  Rate_X_Y_Z_OFFSET,  Rate_X_Y_Z_PHY_LOWER_LIMIT,  Rate_X_Y_Z_PHY_UPPER_LIMIT} // rate is param[1]
    ,{AngAcc_X_Y_Z_SCALE,  AngAcc_X_Y_Z_OFFSET,  AngAcc_X_Y_Z_PHY_LOWER_LIMIT,  AngAcc_X_Y_Z_PHY_UPPER_LIMIT} // angacc is param[2]
    ,{RBL_rbl_CustIf_MB_Temp_SCALE, RBL_rbl_CustIf_MB_Temp_OFFSET, RBL_rbl_CustIf_MB_Temp_LOWER_LIMIT, RBL_rbl_CustIf_MB_Temp_UPPER_LIMIT} // temp is param[3]
};

/* ***** Local Function decleration ***** */

static void rbl_CustIf_IMU_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);

static void rbl_CustIf_Prepare_AngAcc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);

static void rbl_CustIf_Prepare_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);

static void rbl_CustIf_Prepare_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);

static uint8 rbl_CustIf_Prepare_IMU_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);

static uint8 rbl_CustIf_Prepare_IMU_Signal_Status_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);

static uint8 rbl_CustIf_Prepare_IMU_Signal_Status_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);

static uint8 rbl_CustIf_PrepareStatus(uint8 StatusX,uint8 StatusY,uint8 StatusZ);

static uint8 rbl_CustIf_checkBits(uint8 Status);

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
static void rbl_CustIf_Prepare_timeStamp(uint32 MMPtimeStamp);
#endif
/* ***** END_SECTION Local Definitions ***** */


/* *********************************************************************************************************************
 ***** Local function: rbl_CustIf_checkBits **** */
static uint8  rbl_CustIf_checkBits(uint8 Status)
{
    uint8 Interanl_SigStatus ;

    /* Function check the internal status of indivitual signals  */
    /* calculated based on priority and priority order of status is
     * INTERNAL INIT >INTERNAL ERROR_PERMENENT >INTERNAL ERROR_TEMPERATURE >INTERNAL ERROR_OVERLOAD >INTERNAL ERROR_TEMPERORY >VALID */

    if(FALSE != (cc_is_bit_set_u8(Status,RBL_CUSTIF_INIT_STATUS_BIT_POS)))
       {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;
       }
      else if(FALSE != (cc_is_bit_set_u8(Status,RBL_CUSTIF_PERM_STATUS_BIT_POS)))
      {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;
      }
      else if(FALSE != (cc_is_bit_set_u8(Status,RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS)))
      {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;
      }
      else if(FALSE != (cc_is_bit_set_u8(Status,RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS)))
      {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;
      }
      else if(FALSE != (cc_is_bit_set_u8(Status,RBL_CUSTIF_TEMP_STATUS_BIT_POS)))
      {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;
      }
      else
      {
          Interanl_SigStatus = RBL_CUSTIF_INTERNAL_SIGSTATUS_VALID;
      }

      return Interanl_SigStatus;

}

/* ***** END_API rbl_CustIf_checkBits ***** */

/* *********************************************************************************************************************/
 /* ***** Local function: rbl_CustIf_PrepareStatus ***** */

static uint8 rbl_CustIf_PrepareStatus(uint8 StatusX,uint8 StatusY,uint8 StatusZ)
{

    uint8 ret_SigStaus ;
    uint8 InternalStatX;
    uint8 InternalStatY;
    uint8 InternalStatZ;
    Dem_MonitorStatusType MonitorStatus = 0;

    /*Read ambient temperature data */
    (void) Dem_GetMonitorStatus(DemConf_DemEventParameter_RBL_AmbientTemperatureFault, &MonitorStatus);

    /* Imux (x indicates A or B ) signal acc status and rate status is calculated from this service
     * status is calculated from X,Y,Z axis data which combined together and returned as corresponding signal status
     * calculated based on priority and priority order of status is INIT >ERROR_PERMENENT >ERROR_SPRODIAC >ERROR_TEMPERATURE > ERROR_OVERLOAD > >VALID
     */

    /*Reading indivitual signal status and calculate internal signal status */
    InternalStatX = rbl_CustIf_checkBits(StatusX);
    InternalStatY = rbl_CustIf_checkBits(StatusY);
    InternalStatZ = rbl_CustIf_checkBits(StatusZ);

   if((RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT == InternalStatX) ||
      (RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT == InternalStatY)  ||
      (RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT == InternalStatZ))
   {
       ret_SigStaus = RBL_CUSTIF_SIGSTATUS_INIT;
   }
   else if((RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR == InternalStatX)   ||
           (RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR == InternalStatY)   ||
           (RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR == InternalStatZ))
   {
       ret_SigStaus = RBL_CUSTIF_SIGSTATUS_PERMANENT_ERROR;
   }
   else if((RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR == InternalStatX) ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR == InternalStatY)  ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR == InternalStatZ))
    {
        ret_SigStaus = RBL_CUSTIF_SIGSTATUS_SPORADIC_ERROR;
    }
  else if((RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR == InternalStatX)       ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR == InternalStatY)       ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR == InternalStatZ)       ||
          ((MonitorStatus & DEM_MONITOR_STATUS_TF) == DEM_MONITOR_STATUS_TF))
   {
        ret_SigStaus = RBL_CUSTIF_SIGSTATUS_TEMP_ERROR;
   }
  else if((RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR == InternalStatX)   ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR == InternalStatY)   ||
          (RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR == InternalStatZ))
   {
       ret_SigStaus = RBL_CUSTIF_SIGSTATUS_OVERLOAD_ERROR;
   }
  else
   {
       ret_SigStaus = RBL_CUSTIF_SIGSTATUS_VALID;
   }

   return ret_SigStaus;
}

/* ***** END_API rbl_CustIf_PrepareStatus ***** */

/* *********************************************************************************************************************/
 /* ***** Local function: rbl_CustIf_Prepare_IMU_Stat_ST3 ***** */
static uint8 rbl_CustIf_Prepare_IMU_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet)
{
    uint8 ret_ImuStatus ;
    boolean componentFailed_uCPeriphery = FALSE;
    boolean componentFailed_SysAsic1 = FALSE;
    boolean componentFailed_uCMemoryGuard = FALSE;
    boolean componentFailed_MMP_SyncError = FALSE;
    boolean componentFailed_MMP_Nvm_SigChnMonContents = FALSE;
    boolean componentFailed_MMP_SignalChain = FALSE;
    boolean componentFailed_MMP_ReInitError = FALSE;
    uint8  Custif_SigStatus_Acc = 0x00;
    uint8  Custif_SigStatus_Rate = 0x00;

     /*  overall imu status is calculated from this service ,there are 3 smu's avaialble (i=0,1,2)
     *   all the three smu data is combined together.status is calculated based on priority
     *   priority order of status is INIT >ERROR_PERMENENT > OPERATIONAL
     */

    (void) Dem_GetComponentFailed(DemConf_DemComponent_uCPeriphery,&componentFailed_uCPeriphery);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_SysAsic1,&componentFailed_SysAsic1);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_uCMemoryGuard,&componentFailed_uCMemoryGuard);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_MMP_SyncError,&componentFailed_MMP_SyncError);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_MMP_Nvm_SigChnMonContents,&componentFailed_MMP_Nvm_SigChnMonContents);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_MMP_SignalChain,&componentFailed_MMP_SignalChain);
    (void) Dem_GetComponentFailed(DemConf_DemComponent_MMP_ReInitError,&componentFailed_MMP_ReInitError);
    Custif_SigStatus_Acc = rbl_CustIf_Prepare_IMU_Signal_Status_Acc(SignalSet);
    Custif_SigStatus_Rate = rbl_CustIf_Prepare_IMU_Signal_Status_Rate(SignalSet);
    /*  Check the rate status or acceleration status is init ie, inertial signals status is in init  */
    if((RBL_CUSTIF_SIGSTATUS_INIT == Custif_SigStatus_Acc)||(RBL_CUSTIF_SIGSTATUS_INIT == Custif_SigStatus_Rate))
    {
        /* INIT can be calculated based on the ACC and rate of the signals */
        ret_ImuStatus = RBL_CUSTIF_IMU_STATUS_INIT;
    }
    else if((componentFailed_uCPeriphery == TRUE) || (componentFailed_SysAsic1 == TRUE)|| (componentFailed_uCMemoryGuard == TRUE) ||
            (componentFailed_MMP_SyncError == TRUE) || (componentFailed_MMP_Nvm_SigChnMonContents == TRUE) ||
            (componentFailed_MMP_SignalChain == TRUE) || (componentFailed_MMP_ReInitError == TRUE))
    {
        /* Based on the DEM Node active for ECU,ucMemoryGuard,SyncError,NvM_FreqContent,SignalChain Permanent error calculated */
        ret_ImuStatus = RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT ;
    }
    else
    {
        ret_ImuStatus = RBL_CUSTIF_IMU_STATUS_OPERATIONAL;
    }
    return ret_ImuStatus;
}

/* ***** END_API rbl_CustIf_Prepare_IMU_Stat_ST3 ***** */

/* *********************************************************************************************************************
 ***** Local function: rbl_CustIf_Prepare_IMU_Signal_Status_Acc **** */

static uint8 rbl_CustIf_Prepare_IMU_Signal_Status_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet)
{

    uint8 AccStatusx,AccStatusy,AccStatusz;

    uint8 ret_AccSigStaus;

    /* calculation of acceleration status which is combined staus of X,Y,Z axis values of signal chain acceleration status */

    AccStatusx = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].status;
    AccStatusy = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].status;
    AccStatusz = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].status;

    /* calculate the combined status */
    ret_AccSigStaus = rbl_CustIf_PrepareStatus(AccStatusx,AccStatusy,AccStatusz);

    return ret_AccSigStaus;
}


/* ***** END_API rbl_CustIf_Prepare_IMU_Signal_Status_Acc ***** */


/* *********************************************************************************************************************
 ***** Local function: rbl_CustIf_Prepare_IMU_Signal_Status_Rate **** */

static uint8 rbl_CustIf_Prepare_IMU_Signal_Status_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet)
{

    uint8 ret_RateSigStaus;
    uint8 RateStatusx,RateStatusy,RateStatusz;

    /* Imu rate/angular signal status calculated from this serviceie, status is calculated from
     X,Y,Z axis data which combined together */

    RateStatusx = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status;
    RateStatusy = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status;
    RateStatusz = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status;

    /* calculate the combined status */
    ret_RateSigStaus =  rbl_CustIf_PrepareStatus(RateStatusx,RateStatusy,RateStatusz);

    return ret_RateSigStaus;

}

/* ***** END_API rbl_CustIf_Prepare_IMU_Signal_Status_Rate ***** */

/* *********************************************************************************************************************
 * ***** API public: rbl_CustIf_IMU_Prepare_Temp *****/

static void rbl_CustIf_IMU_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet)
{
    // Process data structure to keep float precision when retrieving data
    float32 l_TempSmu = 0.0f;
    float32 Converted_Value;
    // Calculate the temperature value and converted in to float
    l_TempSmu =  (((float32)SignalSet->temp[0].value + RBL_CUSTIF_OFFSET_TEMP_AT_0LSB_PER_C)/ RBL_CUSTIF_SENSITIVITY_TEMP_LSB_PER_K );

    // Calculate the temperature value converted from physical value to int
    Converted_Value = rbl_CustIf_Calc_CompuMethod_Phy2Int(rbl_CustIf_compu_param[3],l_TempSmu);

    /* float to unisgned integer converion */
    rbl_CustIf_ImuSigData.Tempvalue = RB_FloatToInt_f32_u8(Converted_Value);
}

/* ***** END_API rbl_CustIf_IMU_Prepare_Temp ***** */

/* *********************************************************************************************************************
 * ***** Local function: rbl_ImuCustOut_Prepare_AngAcc*****/

static void rbl_CustIf_Prepare_AngAcc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet)
{


       float32 formula;
       CompuMethod const *param = &rbl_CustIf_compu_param[2];
       formula = (float32) RBL_CUSTIF_SENSITIVITY_DELTA_ROT_LSB_PER_DEG_PER_S2;

   /* For each Linear Axis exists an array with four values, to provide redundancy.
    * For the data primary angular acceleration we agree to use the first value of the redundancy array in Axis X
    * from derived data.
    * sensitivity of SMU (also used to define the unit for the internal rot signals in float) is 100LSB/degree/sec
    * derived acc signals are calculated as delta over 1ms
    * That means, that an angular acceleration of 1degree/s^2 is represented by a value of 100.000 in the derived rotation IMU signals
    * The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
    */

       /* check if the raw signal status is init  */
    if(RBL_CUSTIF_SIGSTATUS_INIT == rbl_CustIf_Prepare_IMU_Signal_Status_Rate(RawSignalSet))
    {
        /* send init values */
        rbl_CustIf_ImuSigData.AngaccX = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.AngaccY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.AngaccZ = RBL_CUSTIF_IMU_ACC_RATE_INIT;
    }
    else
    {
        /* update the global variable X,Y,Z with converted values */
        rbl_CustIf_ImuSigData.AngaccX = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].value,formula,param);
        rbl_CustIf_ImuSigData.AngaccY = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].value,formula,param);
        rbl_CustIf_ImuSigData.AngaccZ = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].value,formula,param);

    }
}

/* ***** END_API rbl_ImuCustOut_Prepare_AngAcc ***** */

/* *********************************************************************************************************************
 * ***** Local function: rbl_ImuCustOut_Prepare_Rate *****/

static void rbl_CustIf_Prepare_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet)
{

    float32 formula;
     CompuMethod const *param = &rbl_CustIf_compu_param[1];
     formula = (float32)RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG;

    /* Read the axis inversion satus before conversion
    *  For each Axis exists an array with two values, to provide redundancy
    *  For Rotational Axis X we agree to use the first value of the redundancy array
    *  sensitivity of SMU (also used to define the unit for the internal rot signals in float) is 100LSB/degree/sec
    *  That means, that an rotation of 1degree/sec is represented by a value of 100 in the rotation IMU signals
    *  The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
    *  The MMP2 has a resolution of 1/100 = 0.01 degree/sec.
    */

         /* check if the raw signal status is init  */
    if(RBL_CUSTIF_SIGSTATUS_INIT == rbl_CustIf_Prepare_IMU_Signal_Status_Rate(RawSignalSet))
    {
         /* send init values */
        rbl_CustIf_ImuSigData.RateX = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.RateY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.RateZ = RBL_CUSTIF_IMU_ACC_RATE_INIT;
    }
    else
    {
        /* update the global variable X,Y,Z with converted values */
        rbl_CustIf_ImuSigData.RateX = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].value,formula,param);
        rbl_CustIf_ImuSigData.RateY = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].value,formula,param);
        rbl_CustIf_ImuSigData.RateZ = rbl_CustIf_Calc_Convert(SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].value,formula,param);
    }

}
/* ***** END_API rbl_ImuCustOut_Prepare_Rate ***** */

/**********************************************************************************************************************
 * ***** Local function: rbl_CustIf_Prepare_Acc *****/

static void rbl_CustIf_Prepare_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet)
{
    float32 formula;
    CompuMethod const *param = &rbl_CustIf_compu_param[0];
    formula = (float32) RBL_IMUSTDTYPES_SENSITIVITY_ACC_LSB_PER_G / RBL_CUSTIF_G_TO_MS2;


    /* Read the axis inversion satus before conversion
    * For each Linear Axis exists an array with four values, to provide redundancy
    * For Axis X we agree to use the first value of the redundancy array
    * sensitivity of SMU (also used to define the unit for the internal acc signals in float) is 5000LSB/g
    * That means, that an acceleration of 1g is represented by a value of 5000 in the acceleration IMU signals
    * The signal is represented in 32 bits (float). 32 bits equals to 2,147,483,647 different readings
    * The MMP2 has a resolution of 1/5000 = 0.0002g. At rest, we should have a reading of 5000 in the Z axis, which means 1G.
    */

        /* check if the raw signal status is init */
    if(RBL_CUSTIF_SIGSTATUS_INIT == rbl_CustIf_Prepare_IMU_Signal_Status_Acc(RawSignalSet))
    {
        /* send init values    */
        rbl_CustIf_ImuSigData.AccX = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.AccY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
        rbl_CustIf_ImuSigData.AccZ  = RBL_CUSTIF_IMU_ACC_RATE_INIT;
    }
    else
    {
        /*  Update Acc data for transmission , update the global variable X,Y,Z with converted integer values values */
        rbl_CustIf_ImuSigData.AccX = rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].value,formula,param);
        rbl_CustIf_ImuSigData.AccY = rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].value,formula,param);
        rbl_CustIf_ImuSigData.AccZ = rbl_CustIf_Calc_Convert(SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].value,formula,param);

    }
}

/* ***** END_API rbl_CustIf_Prepare_Acc ***** */

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_Prepare_timeStamp *****/
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
static void rbl_CustIf_Prepare_timeStamp(uint32 MMPtimeStamp)
{

    Std_ReturnType retVal = E_NOT_OK;
    static StbM_TimeStampType MMPtimeStampGTS_st = {0};

    (void)rbl_CustIf_TiSync_MMP2GtsTime(MMPtimeStamp, &MMPtimeStampGTS_st);

    rbl_CustIf_ImuSigData.TymsyncStat = MMPtimeStampGTS_st.timeBaseStatus;
    rbl_CustIf_ImuSigData.TempStampnanosec = MMPtimeStampGTS_st.nanoseconds;
    rbl_CustIf_ImuSigData.TempStampsec = MMPtimeStampGTS_st.seconds;

}
#endif
/* ***** END_API rbl_CustIf_Prepare_timeStamp ***** */

/* *********************************************************************************************************************/
/* ***** Local function: rbl_CustIf_IMU_Output_ST3_PDU_Update *****/
void rbl_CustIf_IMU_Output_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData,
                                          const rbl_ImuStdTypes_ImuSignalSet_t *imu_derivedData)
{

    RBMESG_DefineMESGDef(SigChain_FinalRaw);

    /* read raw signal values */
    RBMESG_RcvMESGDef(SigChain_FinalRaw);

    /* prepare angular acceleration status */
    rbl_CustIf_ImuSigData.AngAccStat = rbl_CustIf_Prepare_IMU_Signal_Status_Rate(imu_derivedData);

    /* prepare angular rate status */
    rbl_CustIf_ImuSigData.RateStat = rbl_CustIf_Prepare_IMU_Signal_Status_Rate(imu_FilData);

    /* prepare spec force status */
    rbl_CustIf_ImuSigData.AccStat = rbl_CustIf_Prepare_IMU_Signal_Status_Acc(imu_FilData);

    /*  prepare imu status  */
    /*  Imu stat is only called after RateStat and AccStat calculation because
     * intertial signal status is used for imu status calculation  */

    rbl_CustIf_ImuSigData.ImuStat = rbl_CustIf_Prepare_IMU_Stat_ST3(imu_FilData);

    /* prepare temperature */
    rbl_CustIf_IMU_Prepare_Temp(imu_FilData);

    /* prepare angular acceleration */
    rbl_CustIf_Prepare_AngAcc(imu_derivedData,&l_SigChain_FinalRaw);

    /* prepare rate */
    rbl_CustIf_Prepare_Rate(imu_FilData,&l_SigChain_FinalRaw);

    /* prepare acc */
    rbl_CustIf_Prepare_Acc(imu_FilData,&l_SigChain_FinalRaw);

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
    /* prepare timeStamp */
    rbl_CustIf_Prepare_timeStamp(imu_FilData->timeStamp);
#endif


    /* Reserved bits initilaized to Init values */
    rbl_CustIf_ImuSigData.Reserved_1 = RBL_CUSTIF_IMU_RESERVED1_INIT;
    rbl_CustIf_ImuSigData.Reserved_2 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
    rbl_CustIf_ImuSigData.Reserved_3 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
    rbl_CustIf_ImuSigData.Reserved_4 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
    rbl_CustIf_ImuSigData.Reserved_5 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
    rbl_CustIf_ImuSigData.Reserved_6 = RBL_CUSTIF_IMU_RESERVED6_INIT;
    rbl_CustIf_ImuSigData.Reserved_7 = RBL_CUSTIF_IMU_RESERVED7_INIT;

    /* write signal values for COMSCL processing */
    RBMESG_GROUP_LOCK
    RBMESG_SendMESG_GROUP(rbl_CustIf_IMU_OutPutMsg_ST3, rbl_CustIf_ImuSigData);
    RBMESG_GROUP_UNLOCK

}
/* ***** END_API rbl_CustIf_IMU_Output_ST3_PDU_Update ***** */

/* ***** END_SECTION API functions ***** */
