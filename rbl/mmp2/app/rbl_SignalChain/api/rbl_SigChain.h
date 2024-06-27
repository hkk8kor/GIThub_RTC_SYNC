
/// @file rbl_SigChain.h
/// @brief public defines and functions for signal chain
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_H
#define RBL_SIGCHAIN_H


/* Include direct headers here */
#include "rbl_ImuStdTypes.h"  /* includes std types and prj_global settings */
#include "rbl_SigChain_ConfigSettings.h"
#include "CM_Basetypes_COMMON.h"
#include "RBMESG_Explicit.h"  // for RBMESG check with diag to change their header include

/* ***** END_SECTION Includes ***** */


/* define functions mapping */

#define RBL_IMU_CHMAP		RBL_IMU_BIT2
#define RBL_IMU_TCOS		RBL_IMU_BIT3

#define RBL_IMU_ALGN		RBL_IMU_BIT5


#define RBL_IMU_SIGFIL      RBL_IMU_BIT9



/* condensed defines for possible coding of signal chain */
#define RBL_SIGCHAIN_OPTIONAL (RBL_IMU_TCOS|RBL_IMU_ALGN|RBL_IMU_SIGFIL)
#define RBL_SIGCHAIN_MANDATORY (RBL_IMU_CHMAP)
#define RBL_SIGCHAIN_ALL (RBL_SIGCHAIN_MANDATORY|RBL_SIGCHAIN_OPTIONAL)

/// number of points for offset interpolation
#define RBL_SIGCHAIN_TCOPNTS 32

/// conversion factor for temperature offset
#define RBL_SIGCHAIN_FACOFFSET 0.015f

/// size of struct for offset interpolation
#define RBL_SIGCHAIN_SIZEOFTCOPNTS (RBL_SIGCHAIN_TCOPNTS*sizeof(sint16))

/// number of points for sensitivity interpolation
#define RBL_SIGCHAIN_TCSPNTS   16

/// conversion factor for sensitivity
#define RBL_SIGCHAIN_FACSVNTY   (3.05e-6f) //0.00000305f

/// size of struct for sensitivity interpolation
#define RBL_SIGCHAIN_SIZEOFTCSPNTS (RBL_SIGCHAIN_TCSPNTS*sizeof(sint16))

#define RBL_SIGCHAIN_ALGN_PNTS 3
#define RBL_SIGCHAIN_MTRX  ((float32)(3.05e-6))


/* Structure definitions */

typedef struct
{
   sint16 AlgnOrthMtrx[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
} rbl_SigChain_AlgnMtrx_t;





typedef struct
{
   uint16    dAbs;
   uint16    dRel;
   uint16    dDriftAbs;
} rbl_SigChain_PairLimit_t;


/* Stores the different limits for the correlation validity for Acc and Rate */
typedef struct
{
    rbl_SigChain_PairLimit_t    acc;
    rbl_SigChain_PairLimit_t    rate;
} rbl_SigChain_CorrMonLimit_t;

typedef struct /*TOOL_SCAN*/
{
    float32 facA[2];
    float32 facB[3];
} rbl_SigChain_Filter_t;

#endif
