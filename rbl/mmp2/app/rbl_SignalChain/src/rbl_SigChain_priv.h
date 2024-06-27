/// @file rbl_SigChain_priv.h
/// @brief private definitions and functions used within the signal chain
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_PRIV_H
#define RBL_SIGCHAIN_PRIV_H

#include "rbl_SigChain.h"   // for data types
#include "rbl_SigChainRBMESG.h"
#include "rbl_ImuGenFunc_Types.h"
#include "rbl_SigChain_Nvm_priv.h"

/* measurements */
#include "CM_Basetypes_COMMON.h"
#include "rbl_SigChain_Measure_Flush.h"
#include "rbl_SigChain_Measure_Nvm.h"
#include "rbl_SigChain_Measure_TestInjChannelSet.h"
#include "rbl_SigChain_Measure_TestInjSigSet.h"


typedef struct
{
	float64  valuesSum;
	float64  squaresSum;
} rbl_SigChain_Sample_t;

typedef struct
{
	rbl_SigChain_Sample_t acc[RBL_IMUSTDTYPES_AXIS_NO];
	rbl_SigChain_Sample_t rate[RBL_IMUSTDTYPES_AXIS_NO];
}rbl_SigChain_SampleSet_t;

#define RBL_SIGCHN_SQUARE(x) ((x)*(x))

extern uint32 rbl_SignalChainActive;
/*[[MEASUREMENT*/
/*NAME=rbl_SignalChainActive*/
/*COMMENT=Activation */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/* matrix points for calculations interpolation  */
/// interpolation array TCO for accelerations
extern sint16 rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
/// interpolation array TCO for rates
extern sint16 rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];

/// interpolation array TCS for accelerations
extern sint16 rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
/// interpolation array TCS for rates
extern sint16 rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

/// matrix for ACC Alignement
extern rbl_SigChain_AlgnMtrx_t  rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
/// matrix for Rate Alignement
extern rbl_SigChain_AlgnMtrx_t  rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];


/* -----------------Signal Chain Init functions ---------------------------*/


/* -----------------Signal Chain cyclic functions ---------------------------*/
/// @c_file rbl_SigChain_TCOS.c
/// @brief temperature dependend offset and sensitivity correction
///
/// @pre part of signal chain
/// @param[in,out] *signalSet all signals in MMP2 orientation
///
/// @return void 
///
/// @details
/// @startuml
/// !include tcos.puml
/// @enduml

/// The correction is done for all relevant acceleration and rate signals.
/// the correction value is calculated with the help of the interpolation function @ref Ifx_IntIpoCur_s16_s16 \n
///	the inputs for the interpolation function are: \n
/// * signal value (acc and rate)
/// * temperature part of @ref signalSet
/// * specific interpolation array \n
///  * @ref rbl_SigChain_TCOAcc
///  * @ref rbl_SigChain_TCORate
///  * @ref rbl_SigChain_TCSAcc
///  * @ref rbl_SigChain_TCSRate

void rbl_SigChain_TCOS(rbl_ImuStdTypes_ImuSignalSet_t *signalSet);
/// @c_file rbl_SigChain_Algn.c
/// @pre called by signal chain
/// @param[in,out] *signalSet   signals in IMU coordinate system
///
/// @return void 
///
/// @details calls @ref Ifx_IntIpoCur_s16_s16 with the temperature to get the correction rates for accelaration and rates
///
void rbl_SigChainAlgn(rbl_ImuStdTypes_ImuSignalSet_t *signalSet);




/* -----------------Signal Chain Helper functions ---------------------------*/

/// @c_file rbl_SigChain_Invalidate.c 
/// @pre valid parameter must me checked by calling function 
/// @param[in,out] *ImuData  signals in smx coordinate system 
/// @param[in] status to be added to former status
/// @param[in] smx affected smx
/// @return void 
/// @details add all stati which belong to a smx with the requested value
void rbl_SigChain_addStatusSmx(rbl_ImuStdTypes_SmxChannelSet_t *ImuData, uint8 status, uint8 smx);

/// @c_file rbl_SigChain_Invalidate.c
/// @pre valid parameter must me checked by calling function 
/// @param[in,out] *signalSet  
/// @param[in] status 
/// @return void 
/// @details add stati of a signal set with the requested value
///
void rbl_SigChain_addStatusSignalSet(rbl_ImuStdTypes_ImuSignalSet_t *signalSet, uint8 status);

/// @c_file rbl_SigChain_Invalidate.c
/// @pre valid parameter must me checked by calling function
/// @param[in,out] *signalSet signals IMU coordinate systems
///
/// @return void 
///
/// @details set all values to 0, no change of other data like smx, status..., calls @ref rbl_SigChain_setAxesZero
///
void rbl_SigChain_setSignalSetZero(rbl_ImuStdTypes_ImuSignalSet_t *signalSet);

/// @c_file rbl_SigChain_Invalidate.c 
/// @pre valid parameter must me checked by calling function 
/// @param[in,out] *signalSet signals IMU coordinate systems
///
/// @return void 
///
/// @details set all axes related values to 0
///
void rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t *signalSet);


/// @brief Interpolation of an sint16 curve with a sint16 distribution at a given position.
/// Please check Autosar for more details
/// Document ID 396: AUTOSAR_SWS_IFXLibrary SWS_Ifx_00035
/// header from CUBAS code has not the official Autosar interface but a wrapper that only calls the official interface
///, so the official is also in this header 
sint16 Ifx_IntIpoCur_s16_s16(sint16 Xin, sint16 N, const sint16* X_array, const sint16* Val_array);

#endif /* End of multiple include protection */
