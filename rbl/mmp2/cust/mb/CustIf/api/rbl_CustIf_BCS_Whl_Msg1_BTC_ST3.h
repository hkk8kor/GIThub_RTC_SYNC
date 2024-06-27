/// @file rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h
/// @brief This header provides definitions for BCS_Whl_Msg1_BTC_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_BCS_WHL_MSG1_BTC_ST3_H_
#define RBL_CUSTIF_BCS_WHL_MSG1_BTC_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* constants and macro definitions  */

// This values are directly taken from arxml files because of that its not following "rbl_" prefix

/// init
#define   I_C02_GTS_ESP_CLK_STAT_ST3_INIT  0
/// internal ESP Clock ok
#define   I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK   1
///internal ESP Clock not ok
#define   I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_NOK 2

/* structure definitions */

/// structure for BCS_Whl_Msg1_BTC_Pr5_ST3 pdu related group signals
typedef struct {
uint16 CRC_BCS_Whl_Msg1_BTC_Pr5_ST3;        ///< CRC-checksum of signal group according to AUTOSAR Profile 5
uint16  WhlPlsCnt_RL_BTC_ST3;               ///< Wheel pulse counter rear left (160 per rotation)
uint16  WhlRPM_FL_BTC_ST3;                  ///< Wheel rpm front left
uint16  WhlRPM_FR_BTC_ST3;                  ///< Wheel rpm front right
uint16  WhlRPM_RL_BTC_ST3;                  ///< Wheel rpm rear left
uint16  WhlRPM_RR_BTC_ST3;                  ///< Wheel rpm rear right
uint16  WhlPlsCnt_FL_BTC_ST3;               ///< Wheel pulse counter front left (160 per rotation)
uint16  WhlPlsCnt_FR_BTC_ST3;               ///< Wheel pulse counter front right (160 per rotation)
uint16 WhlPlsCnt_RR_BTC_ST3;                ///< Wheel pulse counter rear right (160 per rotation)
uint16  BCS_Whl_Msg1_TmStmp_BTC_ST3;        ///< Wheel message #1 time stamp
uint8 SQC_BCS_Whl_Msg1_BTC_Pr5_ST3;         ///< Sequence counter
uint8 WhlDir_FL_Stat_BTC_ST3;               ///< Direction of rotation of front left wheel
uint8 WhlDir_FR_Stat_BTC_ST3;               ///< Direction of rotation of front right wheel
uint8 WhlDir_RL_Stat_BTC_ST3;               ///< Direction of rotation of rear left wheel
uint8 WhlRPM_FL_Qual_BTC_ST3;               ///< Quality of wheel rpm front left
uint8 WhlRPM_FR_Qual_BTC_ST3;               ///< Quality of wheel rpm front right
uint8 WhlRPM_RL_Qual_BTC_ST3;               ///< Quality of wheel rpm rear left
uint8 WhlRPM_RR_Qual_BTC_ST3;               ///< Quality of wheel rpm rear right
uint8 WhlDir_RR_Stat_BTC_ST3;               ///< Direction of rotation of rear right wheel
uint8 BCS_Whl_Msg1_TmSyncStat_BTC_ST3;      ///< Global Timestamp synchronisation status of component ESP
uint8 GTS_ESP_Clk_Stat_Bckp_ST3;            ///< Internal ESP GTS Clock Stat
uint8 Rsrv1_BCS_Whl_Msg1_BTC_Pr5_ST3;       ///< Reserved for future use
}rbl_CustIf_BCS_Whl_Msg1_BTC_Pr5_ST3_st;

///  RBMESG for wheel message BCS_Whl_Msg1_BTC_ST3 pdu relared signals for reception
RBMESG_DefineMESGType_ST(BCS_Whl_Msg1_BTC_Pr5_ST3, rbl_CustIf_BCS_Whl_Msg1_BTC_Pr5_ST3_st);
RBMESG_DeclareMESG(BCS_Whl_Msg1_BTC_Pr5_ST3);

/// RBMESG for Internal ESP GTS Clock Stat signal For transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
RBMESG_DeclareMESG(rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);


/* ***** END_SECTION Definitions ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.c
/// @brief This API will be called if time out occurs
/// Application can perform the condition checks and required actions if any.
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_BCS_Whl_Msg1_BTC_ST3(void);


/// @c_file  rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @startuml
/// !include BCS_Whl_Msg1_BTC_ST3.puml
/// @enduml
/// @details
/// If BCS_Whl_Msg1_BTC_ST3 pdu reception is not successfull i.e., time-out happened for 200ms then
/// signal rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 updated with @ref I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_NOK.\n
/// If consecutive time-out failure is not happened for 200 ms then last received value will be send.\n
/// If BCS_Whl_Msg1_BTC_ST3 pdu received without timeout, then the GTS_ESP_Clk_Stat_Bckp_ST3 signal receives data from
/// ComScl via @ref RBMESG_BCS_Whl_Msg1_BTC_Pr5_ST3 variable, after the reception checks if the data received is valid
/// if yes, then there is no error reported @ref Dem_ReportErrorStatus.\n
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_BCS_Whl_Msg1_BTC_ST3 error to Dem via @ref Dem_ReportErrorStatus,
/// then transmit received signal over @ref RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 variable.\n
/// Below are the valid values for GTS_ESP_Clk_Stat_Bckp_ST3  \n
/// * @ref I_C02_GTS_ESP_CLK_STAT_ST3_INIT
/// * @ref I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK
/// * @ref I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_NOK
void rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive(void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */

#endif /* RBL_CUSTIF_BCS_WHL_MSG1_BTC_ST3_H_ */
