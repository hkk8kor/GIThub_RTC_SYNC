/// @file rbl_CustIf_ImuOutPutStdTypes.h
/// @brief This header provides definitions for Communication control service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_IMUOUTPUTSTDTYPES_H__
#define RBL_CUSTIF_IMUOUTPUTSTDTYPES_H__

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/// scale, offset, upper and lower limit values for tempertaure

/// scale for tempertaure
#define RBL_rbl_CustIf_MB_Temp_SCALE             ((float32)1.00f)
/// offset for tempertaure
#define RBL_rbl_CustIf_MB_Temp_OFFSET            ((float32)-50.0f)
/// lower limit for tempertaure
#define RBL_rbl_CustIf_MB_Temp_LOWER_LIMIT       ((float32)0.00f)
/// upper limit for tempertaure
#define RBL_rbl_CustIf_MB_Temp_UPPER_LIMIT       ((float32)210.00f)

/// defines for Phy2Int_Acc_x_y_Z

/// scale for acceleration
#define Acc_X_Y_Z_SCALE                          ((float32)0.002f)
/// offset for acceleration
#define Acc_X_Y_Z_OFFSET                         ((float32)-50.00f)
/// lower limit for acceleration
#define Acc_X_Y_Z_PHY_LOWER_LIMIT                ((float32)0.00f)
/// upper limit for acceleration
#define Acc_X_Y_Z_PHY_UPPER_LIMIT                ((float32)50000.00f)

/// defines for Phy2Int_rate_x_y

/// scale for rate
#define Rate_X_Y_Z_SCALE                          ((float32)0.01f)
/// offset for rate
#define Rate_X_Y_Z_OFFSET                         ((float32)-300.00f)
/// lower limit for rate
#define Rate_X_Y_Z_PHY_LOWER_LIMIT                ((float32)0.00f)
/// upper limit for rate
#define Rate_X_Y_Z_PHY_UPPER_LIMIT                ((float32)60000.00f)

/// defines for Phy2Int_angular_acc
/// scale for angular acceleration
#define AngAcc_X_Y_Z_SCALE                        ((float32)0.04f)
/// offset for acceleration
#define AngAcc_X_Y_Z_OFFSET                       ((float32)-1200.00f)
/// lower limit for acceleration
#define AngAcc_X_Y_Z_PHY_LOWER_LIMIT              ((float32)0.00f)
/// upper limit for acceleration
#define AngAcc_X_Y_Z_PHY_UPPER_LIMIT              ((float32)60000.00f)

/**************************************************************************************/
/*Status value for MB signals :output signal on CAN BUS*/
/// Init Status
#define RBL_CUSTIF_SIGSTATUS_INIT                   (1U)
/// Valid Status
#define RBL_CUSTIF_SIGSTATUS_VALID                  (2U)
/// Sporadic Error Status
#define RBL_CUSTIF_SIGSTATUS_SPORADIC_ERROR         (3U)
/// Permanent Error Status
#define RBL_CUSTIF_SIGSTATUS_PERMANENT_ERROR        (4U)
/// overload error
#define RBL_CUSTIF_SIGSTATUS_OVERLOAD_ERROR         (5U)
/// temperature error
#define RBL_CUSTIF_SIGSTATUS_TEMP_ERROR             (6U)

/* internal signals status will not be available on CAN BUS and will be used for interanl status calculation */
/// internal Valid Status
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_VALID         (1U)
/// internal overload error
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR (2U)
/// internal temperature out of spec error
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR     (3U)
/// internal Sporadic Error Status
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR (4U)
/// internal Permanent Error Status
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR (5U)
/// internal Init Status
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT           (6U)
/// internal not defined status
#define RBL_CUSTIF_INTERNAL_SIGSTATUS_UNDEFINED      (7U)


///  imu status values
/// init status
#define RBL_CUSTIF_IMU_STATUS_INIT                  1U
/// operational
#define RBL_CUSTIF_IMU_STATUS_OPERATIONAL           2U

/// permanent
#define RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT       4U

/// default values for varaible

/// init value for signal status
#define RBL_CUSTIF_STATUS_INIT                      1U
/// init value for acceleration,rate and angular acceleration
#define RBL_CUSTIF_IMU_ACC_RATE_INIT                0xFFFF
/// temperature init value
#define RBL_CUSTIF_IMU_TEMP_INIT           	        0xFF
/// timesync status  available
#define RBL_CUSTIF_IMU_GTSSTATUS_AVAILABLE          0x00
/// timesync status not  available
#define RBL_CUSTIF_IMU_GTSSTATUS_NOTAVAILABLE       0x80
/// init value for reserved 1 signal
#define RBL_CUSTIF_IMU_RESERVED1_INIT               0x1FF
/// init value for reserved signal 2 to 5
#define RBL_CUSTIF_IMU_RESERVED2TO5_INIT            0xFF
/// init value for reserved 6 signal
#define RBL_CUSTIF_IMU_RESERVED6_INIT               0xFFFF
/// init value for reserved 7 signal
#define RBL_CUSTIF_IMU_RESERVED7_INIT               0x7

/**************************************************************************************/
/* Constants and Macro definitions */


/// Temperature offset at 0 LSB in SMU (used to define the initial point for temp signals in sint) is 50 degree celsius
/// Sensitivity of SMU (also used to define the unit for the internal temp signals in sint) is 200LSB/K
/// That means, that an temperature of 0 degree celsius is represent by a value of 10000 LSB in the temperature IMU signals
// cast required to insure the constant size
#define RBL_CUSTIF_OFFSET_TEMP_AT_0LSB_PER_C    ((float32)10000u)

/// Sensitivity of SMU (also used to define the unit for the internal temp signals in sint) is 200LSB/K
/// That means, that an temperatura of 1K is represented by a value of 200 in the temperature IMU signals
/// cast required to insure the constant size
#define RBL_CUSTIF_SENSITIVITY_TEMP_LSB_PER_K   ((float32)200u)

/* ***** END_SECTION Definitions ***** */

/* Structure definitions */

/// Variables used for sending IMU data to COMSCL
typedef struct{
    uint16 Crc;                    ///< check sum
    uint8 Sqc;                     ///< sequence counter
    uint8 ImuStat;                 ///< Imu status
    uint8 AngAccStat;              ///< Angular acceleration status
    uint8 RateStat;                ///< angular rate status
    uint8 Reserved_7;              ///< reserved 7
    uint8 AccStat;                 ///< acceleration status
    uint8 Tempvalue;               ///< tempearture value
    uint8 TymsyncStat;             ///< time sync status
    uint16 AngaccX;                ///< Angular acceleration X axis
    uint16 AngaccY;                ///< Angular acceleration Y axis
    uint16 AngaccZ;                ///< Angular acceleration Z axis
    uint16 RateX;                  ///< rate X axis
    uint16 RateY;                  ///< rate Y axis
    uint16 RateZ;                  ///< rate Z axis
    uint16 AccX;                   ///< Acceleration X axis
    uint16 AccY;                   ///< Acceleration Y axis
    uint16 AccZ;                   ///< Acceleration Z axis
    uint32 TempStampnanosec;       ///< Time stamp in nano sec
    uint32 TempStampsec;           ///< Time stamp in sec
    uint16 Reserved_1;             ///< reserved 1
    uint8 Reserved_2;              ///< reserved 2
    uint8 Reserved_3;              ///< reserved 3
    uint8 Reserved_4;              ///< reserved 4
    uint8 Reserved_5;              ///< reserved 5
    uint16 Reserved_6;             ///< reserved 6
}rbl_CustIf_OutputMsg_ST3_st;


/// RBMSEG for sending IMU_A_Output_ST3 pdu group signals
RBMESG_DefineMESGType_ST(rbl_CustIf_IMU_OutPutMsg_ST3, rbl_CustIf_OutputMsg_ST3_st);
RBMESG_DeclareMESG(rbl_CustIf_IMU_OutPutMsg_ST3);

/* ***** END_SECTION Definitions ***** */


/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file  rbl_CustIf_IMU_Output_ST3.c
/// @brief   The Function receives the signals from signal chain and its transmits the updated signals to comscl via @ref RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.
/// @pre     periodically called from rbl_CustIf_5ms_Proc in every 5ms
/// @param[in]  imu_FilData :filtered signal data received from signal chain
/// @param[in]  imu_derivedData : derived signal data received from signal chain
/// @return      none
/// @note below is the diagram  for input - output signals relations
/// @startuml
/// !include Input_Output.puml
/// @enduml
/// @note below is the diagram  for rbl_CustIf_IMU_Output_ST3_PDU_Update function
/// @startuml
/// !include IMU_Output_ST3.puml
/// @enduml
/// @details
/// Function receives the raw signal from ComScl via @ref RBMESG_SigChain_FinalRaw variable and it is used for calculating
/// init value of Acc, rate and angular rate signals.\n
///
/// 1. AngAccStat is calculated from derived signal via @ref rbl_CustIf_Prepare_IMU_Signal_Status_Rate  \n
/// 2. RateStat is calculated from filtered signal via  @ref rbl_CustIf_Prepare_IMU_Signal_Status_Rate  \n
/// 3. AccStat is calculated from filtered signal via   @ref rbl_CustIf_Prepare_IMU_Signal_Status_Acc   \n
/// @note below is the diagram  for acceleartion, rate and angular acceleration signal status preparation \n
/// Signal stautus calculated by checking the indivitual axis internal signals status firstly and later all the three \n
/// axis (X,Y,Z) status information grouped together and sent as single status on IMU output .\n
/// diagram : IMU_X_Prepare_Signal_Status
/// @startuml
/// !include IMU_X_Prepare_Signal_Status.puml
/// @enduml
/// 4. ImuStat is calculated from filtered signal via   @ref rbl_CustIf_Prepare_IMU_Stat_ST3 \n
/// @note below is the diagram  for IMU overall status preparation \n
/// diagram : ImuStatus_preparation
/// @startuml
/// !include ImuStatus_preparation.puml
/// @enduml
/// 5. Tempvalue is calculated from filtered signal via  @ref rbl_CustIf_IMU_Prepare_Temp   \n
/// @note below is the diagram  for temperature signal preparation \n
/// diagram : Temp_preparation
/// @startuml
/// !include Temp_preparation.puml
/// @enduml
/// 6. AngaccX , AngaccY, AngaccZ are calculated from derived signals via @ref rbl_CustIf_Prepare_AngAcc  \n
/// 7. RateX , RateY, RateZ calculated from filtered signal via @ref rbl_CustIf_Prepare_Rate  \n
/// 8. AccX , AccY, AccZ Calculated from filtered signal via @ref rbl_CustIf_Prepare_Acc    \n
/// @note below is the diagram  for acceleartion, rate and angular acceleration signal preparation
///  diagram : IMU_X_Signal_preparation
/// @startuml
/// !include IMU_X_Signal_preparation.puml
/// @enduml
/// 9. TymsyncStat,TempStampnanosec and TempStampsec calculated from filtered signal  via @ref rbl_CustIf_Prepare_timeStamp \n
/// with the help of  @ref rbl_CustIf_TiSync_MMP2GtsTime .\n
/// @ref rbl_CustIf_Prepare_timeStamp is called only if @ref RBFS_TimeSync switch is set to @ref RBFS_TimeSync_TSCan.\n
/// If the return values of @ref rbl_CustIf_TiSync_MMP2GtsTime is OK then TymsyncStat,TempStampnanosec and TempStampsec updated with
/// output values from  @ref rbl_CustIf_TiSync_MMP2GtsTime function. \n
/// @note  @ref RBMESG_rbl_CustIf_ImuSigData value is transmitted via @ref RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3. \n
/// @ref Dem_GetComponentFailed function from dem used for checking dem node failure inorder to calculated imu status. \n
/// All Reserverd signal contains init values.

void rbl_CustIf_IMU_Output_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData,
                                          const rbl_ImuStdTypes_ImuSignalSet_t *imu_derivedData);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */

#endif /* RBL_CUSTIF_IMUOUTPUTSTDTYPES_H__ */
