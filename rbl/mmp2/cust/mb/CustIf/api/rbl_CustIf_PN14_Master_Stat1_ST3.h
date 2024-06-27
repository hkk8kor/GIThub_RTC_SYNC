/// @file rbl_CustIf_PN14_Master_Stat1_ST3.h
/// @brief This header provides definitions for PN14_Master_Stat1_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_PN14_MASTER_STAT1_ST3_H_
#define RBL_CUSTIF_PN14_MASTER_STAT1_ST3_H_

/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */
/* Constants and Macro definitions */

/* This values are directly taken from arxml files because of that its not following "rbl_" prefix */

/// Transport mode permanantly off
#define  I_C02_TRANSMD_STAT_OFF       0
/// Transport mode temporarily off
#define  I_C02_TRANSMD_STAT_TEMP_OFF  1
/// Transport mode active
#define  I_C02_TRANSMD_STAT_ACTV       2
/// SNA value from data type
#define  I_C02_TRANSMD_STAT_SNA        3


/// Production mode off
#define  I_C03_PN14_PRODMD_STAT_ST3_OFF           0
/// Production mode active
#define  I_C03_PN14_PRODMD_STAT_ST3_ON            1
/// Production mode special function 1
#define  I_C03_PN14_PRODMD_STAT_ST3_SF01          2
/// Production mode special function 2
#define  I_C03_PN14_PRODMD_STAT_ST3_SF02          3
/// Production mode special function 3
#define  I_C03_PN14_PRODMD_STAT_ST3_SF03          4
/// SNA value from data type
#define  I_C03_PN14_PRODMD_STAT_ST3_SNA           7


/// TDP switch closed
#define  I_C03_PN14_TDP_SW_STAT_CLS             0
/// Pre reset warning
#define  I_C03_PN14_TDP_SW_STAT_PRE_RESET       1
/// Reset active
#define  I_C03_PN14_TDP_SW_STAT_RESET           2
/// Pre open warning
#define  I_C03_PN14_TDP_SW_STAT_PRE_OPN         3
/// TDP switch open
#define  I_C03_PN14_TDP_SW_STAT_OPN             4
/// SNA value from data type
#define  I_C03_PN14_TDP_SW_STAT_SNA             7

/// SNA value from data type for PN14_SupBat_Volt_ST3
#define I_C10_V_0_25K55_0K025_SNA  1023

/// RBMESG created for signals related to PN14_Master_Stat1_ST3 pdu

/// RBMESG for Powernet transport mode status for reception
RBMESG_DefineMESGType_u8(PN14_TransMd_Stat_ST3);
RBMESG_DeclareMESG(PN14_TransMd_Stat_ST3);

/// RBMESG for Powernet transport mode status for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_TransMd_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_TransMd_Stat_ST3);

///RBMESG for Deep discharge protection switch state for reception
RBMESG_DefineMESGType_u8(PN14_DDP_Sw_Stat_ST3);
RBMESG_DeclareMESG(PN14_DDP_Sw_Stat_ST3);

///RBMESG for Deep discharge protection switch state for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_DDP_Sw_Stat_ST3);


/// RBMESG for Powernet production mode state for reception
RBMESG_DefineMESGType_u8(PN14_ProdMd_Stat_ST3);
RBMESG_DeclareMESG(PN14_ProdMd_Stat_ST3);

/// RBMESG for Powernet production mode state for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_ProdMd_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_ProdMd_Stat_ST3);

///RBMESG for Actual 12V battery state during production mode for reception
RBMESG_DefineMESGType_u8(PN14_ProdMd_BatStat_ST3);
RBMESG_DeclareMESG(PN14_ProdMd_BatStat_ST3);

///RBMESG for Actual 12V battery state during production mode for tranmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_ProdMd_BatStat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_ProdMd_BatStat_ST3);

///RBMESG for Supply battery state for reception
RBMESG_DefineMESGType_u8(PN14_SupBat_Stat_ST3);
RBMESG_DeclareMESG(PN14_SupBat_Stat_ST3);

///RBMESG for Supply battery state for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_SupBat_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_SupBat_Stat_ST3);

///RBMESG for Supply battery voltage for reception
RBMESG_DefineMESGType_u16(PN14_SupBat_Volt_ST3);
RBMESG_DeclareMESG(PN14_SupBat_Volt_ST3);

///RBMESG for Supply battery voltage for transmission
RBMESG_DefineMESGType_u16(rbl_CustIf_PN14_SupBat_Volt_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_SupBat_Volt_ST3);

///RBMESG for Supply battery current for reception
RBMESG_DefineMESGType_u16(PN14_SupBat_Curr_ST3);
RBMESG_DeclareMESG(PN14_SupBat_Curr_ST3);

///RBMESG for Supply battery current for transmission
RBMESG_DefineMESGType_u16(rbl_CustIf_PN14_SupBat_Curr_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_SupBat_Curr_ST3);

///RBMESG for Supply battery temperature for reception
RBMESG_DefineMESGType_u8(PN14_SupBat_Temp_ST3);
RBMESG_DeclareMESG(PN14_SupBat_Temp_ST3);

///RBMESG for Supply battery temperature for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_SupBat_Temp_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_SupBat_Temp_ST3);

///RBMESG for Enable for Recharge Secondary-Batterie for reception
RBMESG_DefineMESGType_u8(PN14_PNSec_RechargeEnable_ST3);
RBMESG_DeclareMESG(PN14_PNSec_RechargeEnable_ST3);

///RBMESG for Enable for Recharge Secondary-Batterie for tranmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);


///RBMESG for external barttery charging detected for reception
RBMESG_DefineMESGType_u8(PN14_ExtBat_Charge_Actv_ST3);
RBMESG_DeclareMESG(PN14_ExtBat_Charge_Actv_ST3);

///RBMESG for external barttery charging detected for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);

/// RBMESG for State of DDP Switch2 (Always On Switch) state for reception
RBMESG_DefineMESGType_u8(PN14_DDP_Sw2_Stat_ST3);
RBMESG_DeclareMESG(PN14_DDP_Sw2_Stat_ST3);

/// RBMESG for State of DDP Switch2 (Always On Switch) state for transmission
RBMESG_DefineMESGType_u8(rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);
RBMESG_DeclareMESG(rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);

/// signal validity Position bit for TransMd_Stat_ST3
#define RBL_CUSTIF_TRANSMD_STAT_ST3_POS  1U

/// signal validity Position bit for ProdMd_Stat_ST3
#define RBL_CUSTIF_PRODMD_STAT_ST3_POS  2U

/// signal validity Position bit  for DDP_Sw_Stat_ST3
#define RBL_CUSTIF_DDPSW_STAT_ST3_POS   4U

/// signal validityPosition bit  for SupBat_Volt_ST3
#define RBL_CUSTIF_SUPBAT_VOLT_ST3_POS   8U

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_PN14_Master_Stat1_ST3.c
/// @brief This API will be called if time out occurs
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3(void);


/// @c_file  rbl_CustIf_PN14_Master_Stat1_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @details
/// @startuml
/// !include PN14_Master_Stat1_ST3.puml
/// @enduml
/// If PN14_Master_Stat1_ST3 pdu reception is not successfull i.e., time-out happened for PN14_Master_Stat1_ST3 pdu
/// then signal updated as below
/// SNA value of PN14_TransMd_Stat_ST3 signal is @ref I_C02_TRANSMD_STAT_SNA \n
/// SNA value of PN14_ProdMd_Stat_ST3 signal is @ref I_C02_TRANSMD_STAT_SNA  \n
/// SNA value of PN14_SupBat_Volt_ST3 signal is @ref I_C10_V_0_25K55_0K025_SNA  \n
/// Otherwise function receives below mentioned PN14_Master_Stat1 pdu related signal from ComScl through RBMESG variables.\n
/// PN14_TransMd_Stat_ST3 received via @ref RBMESG_PN14_TransMd_Stat_ST3 \n
/// PN14_DDP_Sw_Stat_ST3 received via  @ref RBMESG_PN14_DDP_Sw_Stat_ST3 \n
/// PN14_ProdMd_Stat_ST3 received via  @ref RBMESG_PN14_ProdMd_Stat_ST3 \n
/// PN14_ProdMd_BatStat_ST3 received via @ref RBMESG_PN14_ProdMd_BatStat_ST3 \n
/// PN14_SupBat_Stat_ST3 received via @ref RBMESG_PN14_SupBat_Stat_ST3 \n
/// PN14_SupBat_Volt_ST3 received via @ref RBMESG_PN14_SupBat_Volt_ST3 \n
/// PN14_SupBat_Curr_ST3 received via @ref RBMESG_PN14_SupBat_Curr_ST3 \n
/// PN14_SupBat_Temp_ST3 received via @ref RBMESG_PN14_SupBat_Temp_ST3  \n
/// PN14_PNSec_RechargeEnable_ST3 received via @ref RBMESG_PN14_PNSec_RechargeEnable_ST3  \n
/// PN14_ExtBat_Charge_Actv_ST3 received via @ref RBMESG_PN14_ExtBat_Charge_Actv_ST3   \n
/// PN14_DDP_Sw2_Stat_ST3 received via @ref RBMESG_PN14_DDP_Sw2_Stat_ST3 \n
/// After the reception check if the received PN14_DDP_Sw_Stat_ST3, PN14_ProdMd_Stat_ST3, PN14_TransMd_Stat_ST3 and
/// PN14_SupBat_Volt_ST3 signals are valid,
/// if any one of the signal are not valid then report @ref RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3 error to
/// Dem via @ref Dem_ReportErrorStatus. And update the received signals with corresponding SNA values and transmitted
/// via corresponding RBMESG varibles.\n
/// If the received signals are valid then report no error to dem @ref Dem_ReportErrorStatus and transmit the received
/// signals over respective RBMESG variables.
///
/// Below are the valid value for  PN14_TransMd_Stat_ST3 \n
/// * @ref I_C02_TRANSMD_STAT_OFF
/// * @ref I_C02_TRANSMD_STAT_TEMP_OFF
/// * @ref I_C02_TRANSMD_STAT_ACTV \n
/// Below are the valid value for  PN14_ProdMd_Stat_ST3 \n
/// * @ref I_C03_PN14_PRODMD_STAT_ST3_OFF
/// * @ref I_C03_PN14_PRODMD_STAT_ST3_ON
/// * @ref I_C03_PN14_PRODMD_STAT_ST3_SF01
/// * @ref I_C03_PN14_PRODMD_STAT_ST3_SF02
/// * @ref I_C03_PN14_PRODMD_STAT_ST3_SF03 \n
/// Below are the valid values for PN14_DDP_Sw_Stat_ST3 \n
/// * @ref I_C03_PN14_TDP_SW_STAT_CLS
/// * @ref I_C03_PN14_TDP_SW_STAT_PRE_RESET
/// * @ref I_C03_PN14_TDP_SW_STAT_RESET
/// * @ref I_C03_PN14_TDP_SW_STAT_PRE_OPN
/// * @ref I_C03_PN14_TDP_SW_STAT_OPN \n
/// valid values for PN14_SupBat_Volt_ST3 is from 0 to 1022  \n
///
/// Below are the names of RBMESG varible used for transmission \n
/// PN14_TransMd_Stat_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 \n
/// PN14_DDP_Sw_Stat_ST3 transmitted via  @ref RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 \n
/// PN14_ProdMd_Stat_ST3 transmitted via  @ref RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 \n
/// PN14_ProdMd_BatStat_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 \n
/// PN14_SupBat_Stat_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 \n
/// PN14_SupBat_Volt_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 \n
/// PN14_SupBat_Curr_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 \n
/// PN14_SupBat_Temp_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3  \n
/// PN14_PNSec_RechargeEnable_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3  \n
/// PN14_ExtBat_Charge_Actv_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3   \n
/// PN14_DDP_Sw2_Stat_ST3 transmitted via @ref RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 \n
///
/// @note SNA value for the signals are mentioned below \n
/// SNA value of PN14_TransMd_Stat_ST3 signal is @ref I_C02_TRANSMD_STAT_SNA \n
/// SNA value of PN14_ProdMd_Stat_ST3 signal is @ref I_C02_TRANSMD_STAT_SNA  \n
/// SNA value of PN14_DDP_Sw_Stat_ST3 signal is @ref I_C03_PN14_TDP_SW_STAT_SNA  \n
/// SNA value of PN14_SupBat_Volt_ST3 signal is @ref I_C10_V_0_25K55_0K025_SNA  \n
void rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */

#endif /* RBL_CUSTIF_FBL_CFG_STAR3_ST3_H_ */
