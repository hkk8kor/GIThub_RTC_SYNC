/// @file rbl_CustIf_Hndl_Utils.h
/// @brief This header provides definitions for Communication control service
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_CUSTIF_HNDL_UTILS_H__
#define RBL_CUSTIF_HNDL_UTILS_H__

/* ***** SECTION Includes ***** */

#include "rbl_CustIf_Main.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "RB_FloatConversion.h"

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Definitions ***** */

/* Constants and Macro definitions */
/// Macros used to validate Signal Chain error status bit

/// bit for Permeant status
#define RBL_CUSTIF_PERM_STATUS_BIT_POS              0U

/// bit for temporary status
#define RBL_CUSTIF_TEMP_STATUS_BIT_POS              1U

/// bit for correlation status
#define RBL_CUSTIF_CORRL_STATUS_BIT_POS             2U

/// bit for initialization status
#define RBL_CUSTIF_INIT_STATUS_BIT_POS              4U

/// bit for overload status
#define RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS          6U

/// bit for temparature status
#define RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS       7U


/// Sensitivity of SMU (also used to define the unit for the internal rot signals in float) is 100LSB/degree/s
/// That means, that an rotation of 1degree/s is represented by a value of 100 in the rotation IMU signals
/// #define RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG      (100)
/// derived acc signals are calculated as delta over 1ms
/// That means, that an angular acceleration of 1degree/s^2 is represented by a value of 100.000 in the derived rotation IMU signals
/// #define RBL_IMUSTDTYPES_SENSITIVITY_DELTA_ROT_LSB_PER_DEG_PER_S2    (RBL_IMUSTDTYPES_SENSITIVITY_ROT_LSB_PER_DEG / 1000)
#define RBL_CUSTIF_SENSITIVITY_DELTA_ROT_LSB_PER_DEG_PER_S2                         (0.1f)


/// Value used for conversion between g and m/s2
/// cast required to insure the constant size
#define RBL_CUSTIF_G_TO_MS2                      ((float32)9.80665F)


/// structure for computation
typedef struct {
    float32 Scale;          ///< scale
    float32 Offset;         ///< offset
    float32 LowerLimit;     ///< lower limit
    float32 UpperLimit;     ///< upper limit
} CompuMethod;

/* ***** END_SECTION Local Definitions ***** */


/* ***** END_SECTION Definitions ***** */

/* ***** External Function Declaration ***** */

// Function used to round the the Imu values before transmission
extern float32 Mfl_Round_f32(float32 ValValue);

// Function used to convert a float32 to sint16 variable
extern sint16 Mfl_Cvrt_f32_s16(float32 ValFloat, sint16 ValFixedExponent);

/* ***** END External Function Declaration ***** */

/* ***** PUBLIC/PROTECTED API function prototypes ***** */

/// @c_file rbl_CustIf_Hndl_Utils.c
/// @brief This Function used for converting the physical values to integer values
/// @pre None
/// @param[in] value: Its the physical  value received from signal chain
/// @param[in] formula : Its sensitivity factor for each signal
/// @param[out] parameter : Its represent scale, offset ,upper and lower limit values
/// @return uint16 :Its uint16 value calculated after the physical to integer conversion
/// @retval  The Function returns the converted values.
/// @details
/// The Function divides the received signal chain value by corresponding sensitivity factor and \n
/// convert the physical value to int with the help of @ref rbl_CustIf_Calc_Convert service.

uint16 rbl_CustIf_Calc_Convert(float32 value, float32 formula, CompuMethod const *parameter);

/// @c_file rbl_CustIf_Hndl_Utils.c
/// @brief This Function responsible to convert the physical values to integer values
/// @pre None
/// @param[in] parameters: Its structure represent scale, offset ,upper and lower limit values
/// @param[in] phy_value : Its the physical  value received from signal chain
/// @return float32 :Its float value calculated after the physical to integer conversion
/// @retval  The Function returns the converted values.
/// @details
/// @startuml
/// !include CompuMethod_PhyInt.puml
/// @enduml
/// Function checks the physical value received is NaN via @ref isnan function and
/// also it checks the physical value received is infinity number or not via @ref isInf , if any
/// of the checks are true then function returns zero as converted value.
/// other wise it calculates the integer value by an expression given below \n
/// "phy_value - parameters.Offset) / parameters.Scale".\n

float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters, float32 phy_value);

/* ******************************************************************************************************************** */
/* ***** END_SECTION API functions ***** */

#endif /* RBL_CUSTIF_HNDL_UTILS_H__ */
