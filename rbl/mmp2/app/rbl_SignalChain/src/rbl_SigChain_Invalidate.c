/// @file rbl_SigChain_Invalidate.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
#include "rbl_SigChain_priv.h"


/*****************************************************************************/
void rbl_SigChain_addStatusSmx(rbl_ImuStdTypes_SmxChannelSet_t *ImuData, uint8 status, uint8 smx)
{
    uint8 ch; /* channel */
    ImuData->temp[smx].status |= status;

    for(ch = 0; ch < RBL_IMUSTDTYPES_NO_OF_ACC_PER_SMX; ch++)
    {
        /* iterate over all acceleration signals of the output structure */
        ImuData->acc[smx][ch].status |= status;
    }
    for(ch = 0; ch < RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX; ch++)
    {
        /* iterate over all rotation signals of the output structure */
        ImuData->rate[smx][ch].status |= status;
    }
}


/* ****************************************************************************
 * ***** API: rbl_SigChain_addStatusSignalSet*****
 * Description:
 *    helper function for signal chain
 *    add stati of a signal set with the requested value
 *
 * Arguments:
 *    signalSet
 *    status - status to be added
 *
 * Return:
 *    void

 *
 * Remarks:
 *
 * ****************************************************************************/
void rbl_SigChain_addStatusSignalSet(rbl_ImuStdTypes_ImuSignalSet_t *signalSet, uint8 status)
{
    uint8 axis;
    uint8 red;

    // currently no temperature status set

    /*set Status of all Acceleration and Rotation Values to Calibration in Prozess behaviour. (each Calibration in Process cycle)*/
    for (axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
        {
            signalSet->acc[axis][red].status |= status;
        }
        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            signalSet->rate[axis][red].status |= status;
        }
    }
}

/*****************************************************************************/
void rbl_SigChain_setSignalSetZero(rbl_ImuStdTypes_ImuSignalSet_t *signalSet)
{
    uint8 red;
    for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; red++)
    {
        signalSet->temp[red].value = 0;
    }
    /*set all Acceleration and Rotation Values */
    rbl_SigChain_setAxesZero(signalSet);
}

/* ****************************************************************************
 * ***** API: rbl_SigChain_setAxesZero*****
 * Description:
 *    helper function for signal chain
 *    set all axes related values to 0
 *    no change of other data like smx, status...
 *
 * Arguments:
 *    signalSet
 *
 * Return:
 *    void

 *
 * Remarks:
 *
 * ****************************************************************************/
void rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t *signalSet)
{
    uint8 axis;
    uint8 red;

    for (axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
        {
            signalSet->acc[axis][red].value = 0.0f;
        }
        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            signalSet->rate[axis][red].value = 0.0f;
        }
    }
}


