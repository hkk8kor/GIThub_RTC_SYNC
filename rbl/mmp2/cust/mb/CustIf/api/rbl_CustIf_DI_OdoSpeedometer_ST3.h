/// @file rbl_CustIf_DI_OdoSpeedometer_ST3.h
/// @brief This header provides definitions for DI_OdoSpeedometer_ST3 pdu related services
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#ifndef RBL_CUSTIF_DI_ODOSPEEDOMETER_ST3_H_
#define RBL_CUSTIF_DI_ODOSPEEDOMETER_ST3_H_


/* ***** SECTION Includes ***** */
#include "rbl_CustIf_Main.h"
/* ***** END_SECTION Includes ***** */


/* ***** SECTION Definitions ***** */

/* Constants and Macro definitions */

/// SNA value for Odo_ST3 signal
#define  rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA_SNA  16777215
#define rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA_INVLD 16777214

/* Structure definitions */

/// stucture type for DI_OdoSpeedometer_ST3 group signals
typedef struct
{
 uint16  CRC_DI_Odo_Pr5_ST3;           ///< CRC-checksum of signal group according to AUTOSAR Profile 5
 uint8   SQC_DI_Odo_Pr5_ST3;           ///< Sequence counter
 uint32  Odo_ST3;                      ///< Odometer (for everyone)
} rbl_CustIf_DI_OdoSpeedometer_ST3_t;

///  RBMESG for DI_OdoSpeedometer_ST3 (Driver information odometer and speedometer)  pdu relared signals (group signals) for reception
RBMESG_DefineMESGType_ST(DI_OdoSpeedometer_ST3, rbl_CustIf_DI_OdoSpeedometer_ST3_t);
RBMESG_DeclareMESG(DI_OdoSpeedometer_ST3);

///  RBMESG for DI_OdoSpeedometer_ST3 (Driver information odometer and speedometer)  pdu relared signals (group signals) for transmission
RBMESG_DefineMESGType_ST(rbl_CustIf_OdoSpeedometer_ST3, rbl_CustIf_DI_OdoSpeedometer_ST3_t);
RBMESG_DeclareMESG(rbl_CustIf_OdoSpeedometer_ST3);

/* ***** END_SECTION Definitions ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_DI_OdoSpeedometer_ST3.c
/// @brief This API will be called if time out occurs
/// @pre The callout function shall be invoked if timeout occurs
/// @param[in] void
/// @return void
void rbl_CustIf_TimeOut_Cbk_DI_OdoSpeedometer_ST3(void);


/// @c_file  rbl_CustIf_DI_OdoSpeedometer_ST3.c
/// @pre periodically called from rbl_CustIf_20ms_Proc in every 20ms
/// @param[in] void
/// @return none
/// @startuml
/// !include DI_OdoSpeedometer_ST3.puml
/// @enduml
/// @details
/// If DI_OdoSpeedometer_ST3 pdu reception is not successfull i.e., time-out happened for DI_OdoSpeedometer_ST3 pdu
/// then signal updated with @ref rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA.\n
/// Otherwise function receives the DI_OdoSpeedometer_ST3 group signal from ComScl via @ref RBMESG_DI_OdoSpeedometer_ST3
/// variable, after the reception check if the data received for the structure member "Odo_ST3" is valid,
/// if yes, then there is no error reported @ref Dem_ReportErrorStatus, and the same received data will be transmitted
/// via @ref RBMESG_rbl_CustIf_OdoSpeedometer_ST3.\n
/// Otherwise report @ref RBL_CUSTIF_SIGNAL_INVALID_DI_OdoSpeedometer_ST3 error to Dem via @ref Dem_ReportErrorStatus
/// and Odo_ST3 signal value is updated to @ref rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA value and transmitted over
/// @ref RBMESG_rbl_CustIf_OdoSpeedometer_ST3.
///
/// @note valid values for signal Odo_ST3 is the range from 0 to 9999999 \n
/// invalid value includes @ref rbl_CustIf_c24_km_0_999999k9_0k1_Invld_SNA and any other value other than valid values
void rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive (void);

/* ***** END_PUBLIC/PROTECTED API function prototypes ***** */

#endif /* RBL_CUSTIF_DI_ODOSPEEDOMETER_ST3_H_ */
