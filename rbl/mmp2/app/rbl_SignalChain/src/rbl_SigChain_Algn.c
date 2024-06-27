/// @file rbl_SigChain_Algn.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#include "CM_Basetypes_COMMON.h"
#include "rbl_SigChain_priv.h"
#include <math.h>  /* fpclassify, FP_ZERO */

/* Variables */
/// temperature points
static const sint16 rbl_SigChain_AlgnT[RBL_SIGCHAIN_ALGN_PNTS] = {-20000,-5000,15000};
/// matrix used for Acc interpolation
rbl_SigChain_AlgnMtrx_t  rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
/// matrix used for rate interpolation
rbl_SigChain_AlgnMtrx_t  rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];


/* rbl_SigChain_AlgnMtrx_t[redundancy] with member
 * AlgnOrthMtrx[Row][Column][RBL_SIGCHAIN_ALGN_PNTS]
 *
 *       | Column0 | Column1 | Column2
 * ------|---------|---------|---------
 *  Row0 |   Mxx   |   Mxy   |   Mxz
 * ------|---------|---------|---------
 *  Row1 |   Myx   |   Myy   |   Myz
 * ------|---------|---------|---------
 *  Row2 |   Mzx   |   Mzy   |   Mzz    */

static void rbl_SigChain_GetTempInterpOrthMtrx(float32 orthMatrix[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO],
        const rbl_ImuStdTypes_ImuSignalSet_t *ImuSignalSet,
        const sint16 TPnts[RBL_SIGCHAIN_ALGN_PNTS],
        const rbl_SigChain_AlgnMtrx_t* OrthMtrxSource,
        uint8 red, boolean isAcc);

/* ****************************************************************************/
void rbl_SigChainAlgn(rbl_ImuStdTypes_ImuSignalSet_t *signalSet)
{
    uint8 red;
    float32 orthMatrix[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO];
    float32 element;
    uint8 row, column;

    rbl_ImuStdTypes_ImuSignalSet_t InputSignalSet;

    InputSignalSet = *signalSet;

    /* go through each redundancy of ACC signals */
    for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
    {
        /* prepare orthogonality matrix */
        rbl_SigChain_GetTempInterpOrthMtrx(orthMatrix,
                &InputSignalSet,
                rbl_SigChain_AlgnT,
                &rbl_SigChain_AlgnAccOrthMtrx[red],
                red,TRUE);

        /* for each element in the orthogonality matrix */
        for(row = 0; row < RBL_IMUSTDTYPES_AXIS_NO; row++)
        {
            for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
            {
                element = orthMatrix[row][column];
                /* If the processed element in the orthogonality matrix is 0 then nothing it to be done */
                if (FP_ZERO != fpclassify(element))
                {
                    /* the value was initialized with the input value, this represents the identity matrix */
                    /* the orthogonalityMatrix * input value */
                    signalSet->acc[row][red].value += InputSignalSet.acc[column][red].value *element;

                    /* after mixing two signals, we always get the "worst" of both */
                    signalSet->acc[row][red].status |= InputSignalSet.acc[column][red].status;
                }
            }
        }
    }

    /* go through each redundancy of rate signals */
    for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
    {
        /* prepare orthogonality matrix */
        rbl_SigChain_GetTempInterpOrthMtrx(orthMatrix,
                &InputSignalSet,
                rbl_SigChain_AlgnT,
                &rbl_SigChain_AlgnRateOrthMtrx[red],
                red,FALSE);

        /* for each element in the orthogonality matrix */
        for(row = 0; row < RBL_IMUSTDTYPES_AXIS_NO; row++)
        {
            for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
            {
                element = orthMatrix[row][column];
                /* If the processed element in the orthogonality matrix is 0 then nothing it to be done */
                if (FP_ZERO != fpclassify(element))
                {
                    /* the value was initialized with the input value, this represents the identity matrix */
                    /* the orthogonalityMatrix * input value is added here */
                    signalSet->rate[row][red].value += InputSignalSet.rate[column][red].value * element;

                    /* after mixing two signals, we always get the "worst" of both */
                    signalSet->rate[row][red].status |= InputSignalSet.rate[column][red].status;
                }
            }
        }
    }
    return;
}

/* ****************************************************************************
 * ***** Local function: GetTempInterpOrthMtrx *****
 * Description:
 *    Help function to calculate the temperature dependent interpolated Orthogonality Matrix
 *
 * Arguments:
 *    orthMatrix: resulting matrix with interpolated values
 *    ImuSignalSet: input of temperature and source of the channels
 *    TPnts: array of temperature reference points
 *    OrthMtrx: array of missalignment matrix for corresponding to the temperature references
 *    red: defines for wich of the redundances the matrix shall be created
 *    isAcc: TRUE for ACC, FALSE for rate
 *
 * Return:
 *    void
 * ****************************************************************************/

static void rbl_SigChain_GetTempInterpOrthMtrx(float32 orthMatrix[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO],
        const rbl_ImuStdTypes_ImuSignalSet_t *ImuSignalSet,
        const sint16 TPnts[RBL_SIGCHAIN_ALGN_PNTS],
        const rbl_SigChain_AlgnMtrx_t* OrthMtrxSource,
        uint8 red, boolean isAcc)
{
    uint8 row, column;
    uint8 smx;
    sint16 temp; /* temperature */
    float32 var; /* interpolation result */

    /* iterate over the columns of the matrix */
    for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
    {
        /* get the smx for this redundancy */
        if(FALSE != isAcc)
        {
            smx = ImuSignalSet->acc[column][red].smx;
        }
        else
        {
            smx = ImuSignalSet->rate[column][red].smx;
        }

        /* check if smx is mounted */
        if (smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX)
        {
            /* use for the whole Row the same the temperature */
            temp = ImuSignalSet->temp[smx].value;

            /* iterate over the rows of the matrix */
            for(row = 0; row < RBL_IMUSTDTYPES_AXIS_NO; row++)
            {
                /* interpolate between stored temperatures */
                var = (float32)Ifx_IntIpoCur_s16_s16(temp, RBL_SIGCHAIN_ALGN_PNTS, TPnts, &(OrthMtrxSource->AlgnOrthMtrx[row][column][0]));
                orthMatrix[row][column] = var * RBL_SIGCHAIN_MTRX;
            }
        }
        else /* if smx for this redundancy is not mounted, the matrix is 0 */
        {
            for(row = 0; row < RBL_IMUSTDTYPES_AXIS_NO; row++)
            {
                orthMatrix[row][column] = 0.0f;
            }
        }
    }
}


