/// @file rbl_CustIf_OsPub.h
/// @brief This header provides definitions for Customer interface service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_OSPUB_H__
#define RBL_CUSTIF_OSPUB_H__

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* Enumerations */

/* Structure definitions */

/* Variables definitions */

/* ***** END_SECTION Definitions ***** */


/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_Main.c
/// @brief
/// @pre
/// @param[in] void
/// @return none
///@note function will be removed in future

void rbl_CustIf_10ms_Proc(void);

/// @c_file rbl_CustIf_Main.c
/// @brief The function receives the signal chain data, filtered signals and derived signals
/// which will be used for further process.\n
/// @pre Called every 5ms from proc services
/// @param[in] void
/// @return void
/// @details
/// Receives the filtered data from signal chain via @ref RBMESG_SigChain_FinalFil and derived signals via @ref RBMESG_SigChain_FinalDer for .\n
/// Receives the filtered data from signal chain via @ref RBMESG_SigChain_FinalFil2 and derived signals via @ref RBMESG_SigChain_FinalDer2 for Driving Can signal.\n
/// Received signal are passed to below mentioned services
/// 1. @ref rbl_CustIf_IMU_Output_ST3_PDU_Update services for calculating the IMU_X_Output_ST3 (X for A or B) pdu data required for com.\n
/// 2. @ref rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update for updating driving can signals required for com trasmission,its called only if driving Can signals are On. \n
/// 3. if driving Can signals are On , Function also calls @ref rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 and it recieves @ref RBMESG_SigChain_FinalFil2 signal from signal chain. \n
/// 4. Also this service periodically calling @ref rbl_CustIf_GTS_Monitoring services for global time synchrostaion .\n
/// 5 .if  RBFS_ConfigurationType_DEVELOP switch is on and @ref rbl_CustIf_SwtTestModEna is active (@ref RBL_IMUSTDTYPES_TEST_MOD_ENAD) then,
/// then instead of signal chain data test mode variables @ref rbl_CustIf_filtered_ImuSignalSet_st_test and @ref rbl_CustIf_Derived_ImuSignalSet_st_test  passed to @ref rbl_CustIf_IMU_Output_ST3_PDU_Update .
void rbl_CustIf_5ms_Proc(void);

/// @c_file rbl_CustIf_Main.c
/// @brief The Function calls reception and transmission services
/// @pre called every 20ms from proc service
/// @param[in] void
/// @return void
/// @details
/// The subunits of the rbl_CustIf_20ms_Proc are called in this order (reception services) \n
/// * @ref rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive \n
/// * @ref rbl_CustIf_DIAG_Stat_ST3_PDU_Receive    \n
/// * @ref rbl_CustIf_Ign_Stat_ST3_PDU_Receive    \n
/// * @ref rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive   \n
/// * @ref rbl_CustIf_VehSpd_Disp_ST3_Receive           \n
/// * @ref rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive         \n
/// * @ref rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive    \n
/// * @ref rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive        \n
/// If IMU A (RBFS_MMP2_IMUA) variant is activated then the receive function for ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3 is called as below: \n
/// * @ref rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_PDU_Receive        \n
/// If IMU B (RBFS_MMP2_IMUB) variant is activated then the receive function for ADAS_HAD_Stat_IDC_M_FSI_ST3 is called as below: \n
/// * @ref rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive        \n
///
/// The subunits of the rbl_CustIf_20ms_Proc are called in this order (trasmission services) \n
/// * @ref rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update     \n
/// * @ref rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update is only called if driving can signals are activated \n
/// The following are invoked if RBFS_ThirdPartySoftware is set to RBFS_ThirdPartySoftware_ON
/// * @ref rbl_CustIf_VSS_TP_Auth_ST3_PDU_Receive        \n
/// * @ref rbl_CustIf_VSS_TP_RealTmOffset_ST3_PDU_Receive        \n
/// * @ref rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3_PDU_Receive        \n
/// * @ref rbl_CustIf_VSS_TP_SharedSecret_ST3_PDU_Receive        \n
/// * @ref rbl_CustIf_VSS_TP_VIN_ST3_PDU_Receive        \n
void rbl_CustIf_20ms_Proc(void);

/// @c_file rbl_CustIf_Main.c
/// @brief The Function calls GTS Monitoring service
/// @pre called every 20ms from proc service
/// @param[in] void
/// @return void

void rbl_CustIf_Monitoring_20ms_Proc(void);

/* ***** END_SECTION API functions ***** */

#endif /* RBL_CUSTIF_OSPUB_H__ */
