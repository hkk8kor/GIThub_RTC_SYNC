/// @file rbl_SigChain_TCOS.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.



/* ***** SECTION Includes ***** */
#include "rbl_SigChain_priv.h"

/* input data */

/// fixed temperature points for TCO
static const sint16 rbl_SigChain_TCO[RBL_SIGCHAIN_TCOPNTS] = {-20000,-18000,-17000,-16000,-15000,-14000,-13000,-12000,-11000,-10000,-9000,-8000,-7000,-6000,-5000,-4000,-3000,-2000,-1000,0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,15000};
sint16 rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
sint16 rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];

/// fixed temperature points for TCS
static const sint16 rbl_SigChain_TCS[RBL_SIGCHAIN_TCSPNTS] = {-20000,-18000,-15800,-13600,-11400,-9200,-7000,-4800,-2600,-400,1800,4000,6200,8400,10600,15000};
sint16 rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
sint16 rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

/// @details offset calculation extracted in static function
static void rbl_SigChain_addOffset(float32* value, sint16 temp, const sint16* valArray);

/// @details sensitivity calculation extracted in static function
static void rbl_SigChain_addSnvty(float32* value, sint16 temp, const sint16* valArray);

/* ****************************************************************************
 * ***** API public: rbl_SigChainTCS *****
 * Description:
 *    Unit of signal chain
 *
 * Arguments:
 *    signalSet signals in IMU coordinate system
 *
 *
 * Return:
 *   void

 * Remarks:

 * ****************************************************************************/
void rbl_SigChain_TCOS(rbl_ImuStdTypes_ImuSignalSet_t *signalSet)
{
	/* Local variables */
	uint8 axis, red;
	uint8 smx;

	float32* value;
	sint16 temperature;

	for(axis= 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
	{
		for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
		{
			/* get source for current inertial signal */
			smx = signalSet->acc[axis][red].smx;
			/* check if smx is mounted */
			if (smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX)
			{
				value = &(signalSet->acc[axis][red].value);
				temperature = signalSet->temp[smx].value;
				rbl_SigChain_addOffset(value,temperature,&(rbl_SigChain_TCOAcc[axis][red][0]));
				rbl_SigChain_addSnvty(value,temperature,&(rbl_SigChain_TCSAcc[axis][red][0]));
				signalSet->acc[axis][red].status |= signalSet->temp[smx].status;
			}
		}
		for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
		{
			/* get source for current inertial signal */
			smx = signalSet->rate[axis][red].smx;
			/* check if smx is mounted */
			if (smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX)
			{
				value = &(signalSet->rate[axis][red].value);
				temperature = signalSet->temp[smx].value;
				rbl_SigChain_addOffset(value,temperature,&(rbl_SigChain_TCORate[axis][red][0]));
				rbl_SigChain_addSnvty(value,temperature,&(rbl_SigChain_TCSRate[axis][red][0]));
				signalSet->rate[axis][red].status |= signalSet->temp[smx].status;
			}
		}
	}
	return;
}

static void rbl_SigChain_addSnvty(float32* value, sint16 temp, const sint16* valArray)
{
	sint16 interpSnvty;
	float32 Snvty;
	/* search for index in temperature points */
	/* get offset incl. interpolation */
	interpSnvty = Ifx_IntIpoCur_s16_s16(temp,RBL_SIGCHAIN_TCSPNTS,rbl_SigChain_TCS,valArray);

	Snvty = (float32)interpSnvty;
	Snvty = Snvty * RBL_SIGCHAIN_FACSVNTY;
	/* apply offset to measured value corrected = input * sensitivity + input = input * (1 + sensitivity) */
    /* only the deviation from 1 is stored in NvM, to get highest precition possible, the one is added by adding the base/input value  */
	*value = *value * (Snvty + 1.0f);
}

static void rbl_SigChain_addOffset(float32* value, sint16 temp, const sint16* valArray)
{
	sint16 interpOffs;
	float32 offset;
	/* search for index in temperature points */
	/* get offset incl. interpolation */
	interpOffs = Ifx_IntIpoCur_s16_s16(temp,RBL_SIGCHAIN_TCOPNTS,rbl_SigChain_TCO,valArray);

	offset = (float32)interpOffs;
	offset = offset * RBL_SIGCHAIN_FACOFFSET;

	/* apply offset to measured value */
	*value = *value - offset;
}
