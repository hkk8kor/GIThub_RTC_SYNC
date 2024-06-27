/// @file rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h
/// @brief This header provides definitions for IMU_B driving Can related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_PT4_DET05_IMU_D_CTRL_ST3_H_
#define RBL_CUSTIF_PT4_DET05_IMU_D_CTRL_ST3_H_


/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/*defines for IMU_D_VehAccel_X_ST3,IMU_D_VehAccel_Z_ST3and IMU_D_VehAccel_Y_ST3 */

/// scale for vehicle acceleration , scale calculated by formula ((float64)(NUM1/DEN0)) for vehicle acceleration NUM1 is 40959 , DEN0 is 32767000 as per arxml
/// so the scale is equal to 0.00125
#define RBL_CUSTIF_DRIVING_Acc_X_Y_Z_SCALE                          ((float32)0.00125f)
/// offset for vehicle acceleration ,offset calculated by formula ((float64)(NUM0/DEN0)) for vehicle acceleration NUM0 is -1342136320, DEN0 is 32767000 as per arxml
/// so the offset is equal to -40.96
#define RBL_CUSTIF_DRIVING_Acc_X_Y_Z_OFFSET                         ((float32)-40.96f)
/// lower limit for vehicle acceleration
#define RBL_CUSTIF_DRIVING_Acc_X_Y_Z_PHY_LOWER_LIMIT                ((float32)0.00f)
/// upper limit for vehicle acceleration
#define RBL_CUSTIF_DRIVING_Acc_X_Y_Z_PHY_UPPER_LIMIT                ((float32)65534.00f)

/*defines for IMU_D_VehPitchRate_ST3 ,IMU_D_VehYawRate_ST3 and IMU_D_VehRollRate_ST3 */

/// scale for vehicle rate ,scale calculated by formula ((float64)(NUM1/DEN0)) for vehicle rate NUM1 is  0.01 , DEN0 is 1 as per arxml
/// so the scale is equal to 0.01
#define RBL_CUSTIF_DRIVING_Rate_X_Y_Z_SCALE                          ((float32)0.01f)
/// offset for vehicle rate , offset calculated by formula ((float64)(NUM0/DEN0)) for vehicle rate NUM0 is -327.68 , DEN0 is 1 as per arxml
/// so the offset is equal to -327.68
#define RBL_CUSTIF_DRIVING_Rate_X_Y_Z_OFFSET                         ((float32)-327.68f)
/// lower limit for vehicle rate
#define RBL_CUSTIF_DRIVING_Rate_X_Y_Z_PHY_LOWER_LIMIT                ((float32)0.00f)
/// upper limit for vehicle rate
#define RBL_CUSTIF_DRIVING_Rate_X_Y_Z_PHY_UPPER_LIMIT                ((float32)65534.00f)

/* defines for IMU_D_VehYawAccel_ST3 ,IMU_D_VehPitch_Accel_ST3 and IMU_D_VehRollAccel_ST3 */

/// scale for IMU_D_VehYawAccel_ST3 ,IMU_D_VehPitch_Accel_ST3 and IMU_D_VehRollAccel_ST3
/// scale calculated by formula ((float64)(NUM1/DEN0)) for vehicle angular rate NUM1 is  0.125 , DEN0 is 1 as per arxml
/// so the scale is equal to 0.125
#define RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_SCALE                        ((float32)0.125f)

/// offset for IMU_D_VehYawAccel_ST3 ,IMU_D_VehPitch_Accel_ST3 and IMU_D_VehRollAccel_ST3
/// offset calculated by formula ((float64)(NUM0/DEN0)) for vehicle rate NUM0 is  -4096 , DEN0 is 1 as per arxml
/// so the offset is equal to -4096
#define RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_OFFSET                       ((float32)-4096.00f)

/// lower limit for IMU_D_VehYawAccel_ST3 ,IMU_D_VehPitch_Accel_ST3 and IMU_D_VehRollAccel_ST3
#define RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_PHY_LOWER_LIMIT              ((float32)0.00f)

/// upper limit for IMU_D_VehYawAccel_ST3 ,IMU_D_VehPitch_Accel_ST3 and IMU_D_VehRollAccel_ST3
#define RBL_CUSTIF_DRIVING_AngAcc_X_Y_Z_PHY_UPPER_LIMIT              ((float32)65534.00f)

/* IMU D sensor status value */
/// Signal initializing
#define  RBL_CUSTIF_IMU_D_SENS_STAT_INIT              0U
/// signal in specification
#define  RBL_CUSTIF_IMU_D_SENS_STAT_OK                2U
///signal temperory failure
#define  RBL_CUSTIF_IMU_D_SENS_STAT_TMP_FAIL          3U
///signal permanant failure
#define  RBL_CUSTIF_IMU_D_SENS_STAT_PRMNT_FAIL        4U


/// SNA value for Tymsync status
#define RBL_CUSTIF_IMU_D_TMSYNC_STAT_SNA    3U

/// Init value for Vehicle dynamics data time stamp
#define RBL_CUSTIF_IMU_D_VehDynData_TmStmp_Sec_SNA    0
#define RBL_CUSTIF_IMU_D_VehDynData_TmStmp_NanoSec_SNA    0

typedef struct{
uint8   Rsrv02_PT4_Det05_IMU_D_Ctrl_Pr5_ST3;        ///<reserved for future use
uint16  CRC_PT4_Det05_IMU_D_Ctrl_Pr5_ST3;           ///<CRC-checksum of signal group according to autosar profile 5
uint16  IMU_D_VehAccel_X_ST3;                       ///< total of gravitations and vehical longitudinal acceleration
uint16  IMU_D_VehRollRate_ST3;                      ///<vehical roll rate
uint16  IMU_D_VehRollAccel_ST3;                     ///<vehical roll accelaration
uint16  IMU_D_VehAccel_Y_ST3;                       ///total of gravitations and vehical lateral acceleration
uint16  IMU_D_VehYawRate_ST3;                       ///<vehical yaw rate
uint16  IMU_D_VehYawAccel_ST3;                      ///<vehical yaw accelaration
uint16  IMU_D_VehAccel_Z_ST3;                       ///<total of gravitations and vehical vertical acceleration
uint16  IMU_D_VehPitchRate_ST3;                     ///<vehical pitch rate
uint16  IMU_D_VehPitch_Accel_ST3;                   ///< vehical pitch accelaration
uint8   SQC_PT4_Det05_IMU_D_Ctrl_Pr5_ST3;           ///< Sequence counter
uint8   IMU_D_VehAccel_X_Stat_ST3;                  ///<vehical longitudinal accelaration state
uint8   IMU_D_VehRollRate_Stat_ST3;                 ///< Vehical roll rate state
uint8   IMU_D_VehRollAccel_Stat_ST3;                ///< Vehical roll accelaration state
uint8   IMU_D_VehAccel_Y_Stat_ST3;                  ///<vehical lateral accelaration state
uint8   IMU_D_VehYawRate_Stat_ST3;                  ///<vehical yaw rate state
uint8   IMU_D_VehYawAccel_Stat_ST3;                 ///<vehical yaw rate state
uint8   IMU_D_VehAccel_Z_Stat_ST3;                  ///<vehical vertical accelaration state
uint8   IMU_D_VehPitchRate_Stat_ST3;                ///< vehical pitch rate state
uint8   IMU_D_VehPitchAccel_Stat_ST3;               ///<vehical pitch accelaration state
uint8   IMU_D_VehDynData_TmSyncStat_ST3;            ///<global timestamp synchronisation status of component IMU-D
uint8   Rsrv01_PT4_Det05_IMU_D_Ctrl_Pr5_ST3;        ///< reserved for future use
uint32  IMU_D_VehDynData_TmStmp_Sec_ST3;            ///< IMU timestamp, whole seconds part
uint32  IMU_D_VehDynData_TmStmp_NanoSec_ST3;        ///< IMU timestamp, fractional digits part in nanoseconds fast
}rbl_CustIf_IMU_D_Det05_ST3_PT4_st;


/// RBMSEG for IMU_D_DRIVING_Container_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3 pdu signals (powertrain deterministic concept -IMUD control)
RBMESG_DefineMESGType_ST(rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3, rbl_CustIf_IMU_D_Det05_ST3_PT4_st);
RBMESG_DeclareMESG(rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3);

/// @c_file rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.c
/// @brief   The Function prepare IMU_D_DRIVING_Container_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3 PDU data from signal chain input and transmits the updated signals to comscl via @ref RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3.
/// @pre     periodically called from rbl_CustIf_5ms_Proc in every 5ms
/// @param[in]  imu_FilData :filtered signal data received from signal chain
/// @param[in]  imu_derivedData : derived signal data received from signal chain
/// @return      none
/// @details
/// Function receives the raw signal from ComScl via @ref RBMESG_SigChain_FinalRaw variable and it is used for calculating
/// init value of Acc, rate and angular rate signals.\n
/// @note The Diagram for IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update
/// @startuml
/// !include Det05_IMU_D_Ctrl_ST3.puml
/// @enduml
///
/// Function prepare the IMU Driving can signal status from signal chain via @ref rbl_CustIf_Prepare_IMU_D_Signal_Status.\n
/// * 1. IMU_D_VehAccel_X_Stat_ST3 calculated from signal chain filtered signal acc X status \n
/// * 2. IMU_D_VehAccel_Y_Stat_ST3 calculated from signal chain filtered signal acc Y status  \n
/// * 3. IMU_D_VehAccel_Z _Stat_ST3 calculated from signal chain filtered signal acc Z status \n
/// * 4.IMU_D_VehRollRate_Stat_ST3 calculated from signal chain filtered signal rate X status \n
/// * 5.IMU_D_VehPitchRate_Stat_ST3 status calculated from signal chain filtered signal rate Y status \n
/// * 6.IMU_D_VehYawRate_Stat_ST3 status calculated from signal chain filtered signal rate Z status \n
/// * 7.IMU_D_VehRollAccel_Stat_ST3 Status calculated from signal chain derived signal rate X status \n
/// * 8.IMU_D_VehPitchAccel_Stat_ST3 Status calculated from signal chain derived signal rate Y status \n
/// * 9.IMU_D_VehYawAccel_Stat_ST3 Status calculated from signal chain derived signal rate Z status \n
/// @note The Diagram is for signals stutus calculation \n
/// Diagram : IMU_D_PrepareStatus
/// @startuml
/// !include IMU_D_PrepareStatus.puml
/// @enduml
/// Driving CAN Signals prepared from signal chain signal values via @ref  rbl_CustIf_Prepare_IMU_D_Signals. \n
/// 1. IMU_D_VehAccel_X_ST3 calculated from signal chain filtered signal acceleration X value \n
/// 2. IMU_D_VehAccel_Y_ST3 calculated from signal chain filtered signal acceleration Y value \n
/// 3. IMU_D_VehAccel_Z_ST3 calculated from signal chain filtered signal acceleration Z value \n
/// 4. IMU_D_VehRollRate_ST3 calculated from signal chain filtered signal rate X value \n
/// 5. IMU_D_VehPitchRate_ST3  calculated from signal chain filtered signal rate Y value \n
/// 6. IMU_D_VehYawRate_ST3  calculated from signal chain filtered signal rate Z value \n
/// 7. IMU_D_VehRollAccel_ST3  calculated from signal chain derived signal rate X value \n
/// 8. IMU_D_VehPitch_Accel_ST3  calculated from signal chain derived signal rate Y value  \n
/// 9. IMU_D_VehYawAccel_ST3 calculated from signal chain derived signal rate Z value  \n
/// @note The Diagram for signal preparation \n
/// Diagram : Prepare_IMU_D_Signals
/// @startuml
/// !include Prepare_IMU_D_Signals.puml
/// @enduml
/// Other signals related to this pdu have below mentined values. \n
/// IMU_D_VehDynData_TmStmp_Sec_ST3 is updated with @ref  RBL_CUSTIF_IMU_D_VehDynData_TmStmp_Sec_SNA,\n
/// IMU_D_VehDynData_TmStmp_NanoSec_ST3 is updated with @ref  RBL_CUSTIF_IMU_D_VehDynData_TmStmp_NanoSec_SNA,\n
/// IMU_D_VehDynData_TmSyncStat_ST3 is updated with the @ref RBL_CUSTIF_IMU_D_TMSYNC_STAT_SNA \n
/// Other members Rsrv01_PT4_Det05_IMU_D_Ctrl_Pr5_ST3,Rsrv02_PT4_Det05_IMU_D_Ctrl_Pr5_ST3 are set to Zero \n



void rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t *imu_FilData,
                                          const rbl_ImuStdTypes_ImuSignalSet_t *imu_derivedData);



#endif /* RBL_CUSTIF_PT4_DET05_IMU_D_CTRL_ST3_H_ */
