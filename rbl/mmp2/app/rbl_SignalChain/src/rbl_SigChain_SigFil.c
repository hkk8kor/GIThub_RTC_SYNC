/// @file rbl_SigChain_SigFil.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.



/* ***** SECTION Includes ***** */
#include "rbl_ImuGenFunc_ErrCntrPub.h"
#include "rbl_SigChain_SigFil.h"
#include "rbl_SigChain_Measure_SigFil.h"
#include "rbl_ImuCdd_Interfaces.h"
#include <math.h>

static const rbl_ImuStdTypes_ImuSignalSet_t rbl_SigChain_FilSigSetEmpty;

static rbl_SigChain_FilterArray_t rbl_SigChain_FilVal;
static uint16 rbl_SigChain_SigFilFlush;
static uint32 rbl_SigChain_TimeStampDelayTick;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_FilterArray_t rbl_SigChain_FilVal2;
static uint16 rbl_SigChain_SigFilFlush2;
static uint32 rbl_SigChain_TimeStampDelayTick2;
#endif


/* Error counter values */
static rbl_SigChain_AccFilCnt_t rbl_SigChain_AccFlushCnt;
static rbl_SigChain_RateFilCnt_t rbl_SigChain_RateFlushCnt;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_AccFilCnt_t rbl_SigChain_AccFlushCnt2;
static rbl_SigChain_RateFilCnt_t rbl_SigChain_RateFlushCnt2;
#endif

static rbl_SigChain_AccFilCnt_t rbl_SigChain_AccInitFlushCnt;
static rbl_SigChain_RateFilCnt_t rbl_SigChain_RateInitFlushCnt;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_AccFilCnt_t rbl_SigChain_AccInitFlushCnt2;
static rbl_SigChain_RateFilCnt_t rbl_SigChain_RateInitFlushCnt2;
#endif

/* storage for filter tabs */
static rbl_SigChain_RateFilTabsSteps_t rbl_SigChain_RateFilTabs;
static rbl_SigChain_AccFilTabsSteps_t rbl_SigChain_AccFilTabs;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_RateFilTabsSteps_t rbl_SigChain_RateFilTabs2;
static rbl_SigChain_AccFilTabsSteps_t rbl_SigChain_AccFilTabs2;
#endif


static rbl_SigChain_RateFilTabs_t rbl_SigChain_RateDerFilTabs;
static rbl_SigChain_AccFilTabs_t rbl_SigChain_AccDerFilTabs;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_RateFilTabs_t rbl_SigChain_RateDerFilTabs2;
static rbl_SigChain_AccFilTabs_t rbl_SigChain_AccDerFilTabs2;
#endif

static rbl_SigChain_RateFilTabs_t rbl_SigChain_RatePhaCorrnTabs;
static rbl_SigChain_AccFilTabs_t rbl_SigChain_AccPhaCorrnTabs;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_RateFilTabs_t rbl_SigChain_RatePhaCorrnTabs2;
static rbl_SigChain_AccFilTabs_t rbl_SigChain_AccPhaCorrnTabs2;
#endif

static rbl_SigChain_FilData_t usedData = { {(&rbl_SigChain_AccInitFlushCnt),(&rbl_SigChain_AccFlushCnt),(&rbl_SigChain_AccFilTabs),(&rbl_SigChain_AccDerFilTabs),(&rbl_SigChain_AccPhaCorrnTabs)},
        {(&rbl_SigChain_RateInitFlushCnt),(&rbl_SigChain_RateFlushCnt),(&rbl_SigChain_RateFilTabs),(&rbl_SigChain_RateDerFilTabs),(&rbl_SigChain_RatePhaCorrnTabs)},
        (&rbl_SigChain_FilVal),(&rbl_SigChain_SigFilFlush),(&rbl_SigChain_TimeStampDelayTick)};
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
static rbl_SigChain_FilData_t usedData2 = { {(&rbl_SigChain_AccInitFlushCnt2),(&rbl_SigChain_AccFlushCnt2),(&rbl_SigChain_AccFilTabs2),(&rbl_SigChain_AccDerFilTabs2),(&rbl_SigChain_AccPhaCorrnTabs2)},
        {(&rbl_SigChain_RateInitFlushCnt2),(&rbl_SigChain_RateFlushCnt2),(&rbl_SigChain_RateFilTabs2),(&rbl_SigChain_RateDerFilTabs2),(&rbl_SigChain_RatePhaCorrnTabs2)},
        (&rbl_SigChain_FilVal2),(&rbl_SigChain_SigFilFlush2),(&rbl_SigChain_TimeStampDelayTick2)};
#endif
/* Constant tables */
static const rbl_SigChain_Filter_t rbl_SigChain_DerFilCfg = {{0.0F, 0.0F},{0.5F, 0.0F, -0.5F}};
static const rbl_SigChain_Filter_t rbl_SigChain_PhaseCorrnCfg = {{0.0F, 0.0F},{0.0F, 1.0F, 0.0F}};
/* ***** SECTION Local function prototypes ***** */
/* Local function prototypes here... remember to add the static keyword */
static uint8 rbl_SigChain_debounce(uint8 mask, uint8 status, uint16 debounceSteps, uint16 *counter);
static void rbl_SigChain_UpdateFilter(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, const rbl_SigChain_FilData_t * data, rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
static void rbl_SigChain_UpdateDerivation(rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
static void rbl_SigChain_PhaseCorrection(rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
static void rbl_ImuSigFil_UpdateStatus(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, const rbl_SigChain_FilData_t * data);
static float rbl_SigChain_CalcSecOrdSctn(const rbl_SigChain_Filter_t *FilCoeff, rbl_SigChain_FilTabs_t *filTabsArray, float32 x);
static void rbl_SigChain_runFilterSteps(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, const rbl_SigChain_FilData_t * data);
static void rbl_SigChain_UpdateFilTab (rbl_SigChain_FilTabs_t * tabs, float32 filVal);

void rbl_SigChain_InitFilter(const rbl_SigChain_FilterArray_t* filter, uint16  flush, float timestampdelay )
{

#if (RBFS_SigChainFilter == RBFS_SigChainFilter_20Hz)
    rbl_SigChain_FilVal = rbl_SigChain_FilVal20Hz;
    rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL20HZFLUSH;
    rbl_SigChain_TimeStampDelayTick = (uint32)rbl_ImuCdd_Float2ticks(1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS20HZ); // Timestamp delay of 13.83 ms for 20Hz Filter
#elif(RBFS_SigChainFilter==RBFS_SigChainFilter_45Hz)
    rbl_SigChain_FilVal = rbl_SigChain_FilVal45Hz;
    rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
    rbl_SigChain_TimeStampDelayTick = (uint32)rbl_ImuCdd_Float2ticks(1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ); // Timestamp delay of 5.56 ms for 45Hz Filter
#elif(RBFS_SigChainFilter==RBFS_SigChainFilter_NoFilter)
    rbl_SigChain_FilVal = rbl_SigChain_FilValNoFilter;
    rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFILNONEFLUSH;
    rbl_SigChain_TimeStampDelayTick = 0; // No Time delay for No filter
#elif(RBFS_SigChainFilter == RBFS_SigChainFilter_Nvm)
    if (NULL != filter)
    {
        rbl_SigChain_FilVal = *filter;
        rbl_SigChain_SigFilFlush = flush;
        rbl_SigChain_TimeStampDelayTick = (uint32)rbl_ImuCdd_Float2ticks(1000.0f*timestampdelay);
    }
#else
#error ("Invalid Switch setting!")
#endif
}

#if (RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
void rbl_SigChain_InitFilter2(const rbl_SigChain_FilterArray_t* filter, uint16 flush, float timestampdelay )
{

#if(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_45Hz)
    rbl_SigChain_FilVal2 = rbl_SigChain_FilVal45Hz;
    rbl_SigChain_SigFilFlush2 = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
    rbl_SigChain_TimeStampDelayTick2 = (uint32)rbl_ImuCdd_Float2ticks(1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ); // Timestamp delay of 5.56 ms for 45Hz Filter
#elif(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_Nvm)
    if (NULL != filter)
    {
        rbl_SigChain_FilVal2 = *filter;
        rbl_SigChain_SigFilFlush2 = flush;
        rbl_SigChain_TimeStampDelayTick2 = (uint32)rbl_ImuCdd_Float2ticks(1000.0f*timestampdelay);
    }
#else
#error ("Invalid Switch setting!")
#endif
}
#endif


void rbl_SigChainSigFil(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, uint32 filterNumber)
{
    /*-----------------------------------------------------------------------*/
    /* prefill output buffers with copies of input buffer */

    *signalSetFil = *signalSetRaw;
    *signalSetDer = *signalSetRaw;

    switch(filterNumber)
    {
        // first filter
        case RBL_SIGCHAIN_FIRSTFILTER:
            rbl_SigChain_runFilterSteps(signalSetRaw, signalSetFil, signalSetDer, &usedData);
            break;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
            // Second filter
        case RBL_SIGCHAIN_SECONDFILTER:
            rbl_SigChain_runFilterSteps(signalSetRaw, signalSetFil, signalSetDer, &usedData2);
            break;
#endif
        default:
            // invalid call, do nothing
            break;
    }

    return;
}

static void rbl_SigChain_runFilterSteps(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw,
        rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil,
        rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer,
        const rbl_SigChain_FilData_t * data)
{

    uint8 axis, red, SosNo;
    float32 filVal;
    rbl_ImuStdTypes_ImuSignalSet_t tempSigSet;  // temporary used during several steps of calculation
    rbl_ImuCdd_State_t stateCDD;

    tempSigSet = rbl_SigChain_FilSigSetEmpty;

    stateCDD = rbl_ImuCdd_GetCDDState();
    // only in normal or error the cdd is getting the raw data from SMU
    if ((rbl_ImuCdd_Normal_e != stateCDD)
            &&(rbl_ImuCdd_Error_e != stateCDD)) ///< normal operation
    {

        for(axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
        {
            for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; red++)
            {

                filVal = signalSetRaw->acc[axis][red].value;

                /*Filtered output signalSetFil is already prefilled with the Raw values*/

                /*Update the Derived output with 0 during the Initialisation phase */
                signalSetDer->acc[axis][red].value = 0.0f;

                for(SosNo = 0; SosNo < RBL_SIGCHN_FIL; SosNo++)
                {
                    /*Update the Filter Tab values with Raw value during the Initialisation phase to overcome the transient oscillation at the startup  */
                    rbl_SigChain_UpdateFilTab ( &data->acc.steps->tabs[axis][red][SosNo], filVal);
                }

                /*Update the Phasecorrection Tab values with Raw value during the Initialisation phase to overcome the transient oscillation at the startup  */
                rbl_SigChain_UpdateFilTab ( &data->acc.phaCorrn->tabs[axis][red], filVal);

                /*Update the Derived Tab values with Raw value during the Initialisation phase to overcome the transient oscillation at the startup  */
                rbl_SigChain_UpdateFilTab ( &data->acc.derived->tabs[axis][red], filVal);
            }

            for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
            {
                filVal = signalSetRaw->rate[axis][red].value;

                /*Filtered output signalSetFil is already prefilled with the Raw values*/

                /*Update the Derived output with 0 during the Initialisation phase */
                signalSetDer->rate[axis][red].value = 0.0f;

                for(SosNo = 0; SosNo < RBL_SIGCHN_FIL; SosNo++)
                {
                    /*Update the Filter Tab values with Raw value during the Initialisation phase to overcome the transient oscillation at the startup  */
                    rbl_SigChain_UpdateFilTab ( &data->rate.steps->tabs[axis][red][SosNo], filVal);
                }

                rbl_SigChain_UpdateFilTab ( &data->rate.phaCorrn->tabs[axis][red], filVal);

                /*Update the Derived Tab values with Raw value during the Initialisation phase to overcome the transient oscillation at the startup  */
                rbl_SigChain_UpdateFilTab ( &data->rate.derived->tabs[axis][red], filVal);

            }
        }

        rbl_ImuSigFil_UpdateStatus(signalSetRaw, signalSetFil, signalSetDer, data);
    }
    else
    {
        /* perform filtering and derivation computation after the initialisation is complete */
        rbl_SigChain_UpdateFilter(signalSetRaw, data, &tempSigSet);
        rbl_SigChain_PhaseCorrection(signalSetFil, data, &tempSigSet);
        rbl_SigChain_UpdateDerivation(signalSetDer, data, &tempSigSet);
        rbl_ImuSigFil_UpdateStatus(signalSetRaw, signalSetFil, signalSetDer, data);
    }
}

/* ****************************************************************************
 * ***** API private: UpdateFilTab *****
 * Description:
 *    Update the filter tab with the Filval values
 *
 * Arguments:
 *    tabs, filval
 *
 *
 * Return:
 *    void
 *
 *
 * Remarks:
 *   Function to update the tab value with the raw values during Initialisation
 * ****************************************************************************/

static void rbl_SigChain_UpdateFilTab (rbl_SigChain_FilTabs_t * tabs, float32 filVal)
{
    tabs->filTabs[0][0] = filVal;
    tabs->filTabs[0][1] = filVal;
    tabs->filTabs[1][0] = filVal;
    tabs->filTabs[1][1] = filVal;
}


/* ****************************************************************************
 * ***** API private: UpdateFilter *****
 * Description:
 *    Calculation of the low pass filter
 *
 * Arguments:
 *    signalSetRaw
 *
 *
 * Return:
 *    void
 *
 *
 * Remarks:
 *    -
 * ****************************************************************************/
static void rbl_SigChain_UpdateFilter(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, const rbl_SigChain_FilData_t * data, rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    uint8 axis, red, SosNo;
    float32 filVal;

    for(axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; red++)
        {
            filVal = signalSetRaw->acc[axis][red].value;
            for(SosNo = 0; SosNo < RBL_SIGCHN_FIL; SosNo++)
            {
                filVal = rbl_SigChain_CalcSecOrdSctn(&data->filter->filVal[SosNo], &data->acc.steps->tabs[axis][red][SosNo], filVal);

            }
            tempSigSet->acc[axis][red].value = filVal;
        }

        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            filVal = signalSetRaw->rate[axis][red].value;
            for(SosNo = 0; SosNo < RBL_SIGCHN_FIL; SosNo++)
            {
                filVal = rbl_SigChain_CalcSecOrdSctn(&data->filter->filVal[SosNo], &data->rate.steps->tabs[axis][red][SosNo], filVal);
            }
            tempSigSet->rate[axis][red].value = filVal;
        }
    }
    // timestamp delay
    tempSigSet->timeStamp = signalSetRaw->timeStamp - *(data->timestampdelaytick);
    return;
}

/* ****************************************************************************
 * ***** API private: UpdateDerivation *****
 * Description:
 *    Calculation of the derivation
 *
 * Arguments:
 *    signalSetDer
 *
 *
 * Return:
 *    void
 *
 *
 * Remarks:
 *    This process assumes that function UpdateFilter is called directly before UpdateDerivation.
 * ****************************************************************************/
static void rbl_SigChain_UpdateDerivation(rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    uint8 axis, red;
    float32 filVal;

    for(axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; red++)
        {
            filVal = tempSigSet->acc[axis][red].value;
            filVal = rbl_SigChain_CalcSecOrdSctn(&rbl_SigChain_DerFilCfg, &data->acc.derived->tabs[axis][red], filVal);
            signalSetDer->acc[axis][red].value = filVal;
        }

        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            filVal = tempSigSet->rate[axis][red].value;
            filVal = rbl_SigChain_CalcSecOrdSctn(&rbl_SigChain_DerFilCfg, &data->rate.derived->tabs[axis][red], filVal);
            signalSetDer->rate[axis][red].value = filVal;
        }
    }
    // timestamp delay
    signalSetDer->timeStamp = tempSigSet->timeStamp;
    return;
}

/* ****************************************************************************
 * ***** API private: rbl_SigChain_PhaseCorrection *****
 * Description:
 *    apply a phase correction to have matching phase between lowpass filtered signal and aditional derived data.
 *
 * Arguments:
 *    signalSetFil
 *
 *
 * Return:
 *    void
 *
 *
 *
 * Remarks:
 *    This process assumes that function UpdateFilter is called directly before rbl_SigChain_PhaseCorrection.
 * ****************************************************************************/
static void rbl_SigChain_PhaseCorrection(rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    uint8 axis, red;
    float32 filVal;

    for(axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; red++)
        {
            filVal = tempSigSet->acc[axis][red].value;
            filVal = rbl_SigChain_CalcSecOrdSctn(&rbl_SigChain_PhaseCorrnCfg, &data->acc.phaCorrn->tabs[axis][red], filVal);
            signalSetFil->acc[axis][red].value = filVal;
        }

        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            filVal = tempSigSet->rate[axis][red].value;
            filVal = rbl_SigChain_CalcSecOrdSctn(&rbl_SigChain_PhaseCorrnCfg, &data->rate.phaCorrn->tabs[axis][red], filVal);
            signalSetFil->rate[axis][red].value = filVal;
        }
    }
    // timestamp delay
    signalSetFil->timeStamp = tempSigSet->timeStamp;
    return;
}

/* ****************************************************************************
 * ***** API private: rbl_ImuSigFil_UpdateStatus *****
 * Description:
 *    Update the status bits of the interntial data, therefore filterflush time is taken into account
 *
 * Arguments:
 *    signalSetRaw
 *    signalSetFil
 *    signalSetDer
 * Return:
 *    void
 *
 *
 * Remarks:
 *    -
 * ****************************************************************************/
static void rbl_ImuSigFil_UpdateStatus(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, const rbl_SigChain_FilData_t * data)
{
    uint8 axis;
    uint8 red;
    uint8 newStatus;
    uint8 status;
    uint8 mask;
    uint16 debounceSteps;

    debounceSteps = *(data->flush);
    /*-----------------------------------------------------------------------*/
    /* call filter flushing error counter update functions */
    /* during the flush time, the old status will be kept */

    for (axis = 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
        {
            newStatus = 0;
            status = signalSetRaw->acc[axis][red].status;
            /* flush acc status */
            mask = RBL_IMUSTDTYPES_STATUS_TMP_MASK;
            newStatus |= rbl_SigChain_debounce(mask, status, debounceSteps, &data->acc.Cnt->counter[axis][red]);

            /* flush acc init status */
            mask = RBL_IMUSTDTYPES_STATUS_INIT_MASK;
            newStatus |= rbl_SigChain_debounce(mask, status, debounceSteps, &data->acc.initCnt->counter[axis][red]);

            /* update status */
            signalSetFil->acc[axis][red].status |= newStatus;
            signalSetDer->acc[axis][red].status = signalSetFil->acc[axis][red].status;
        }

        for (red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            newStatus = 0;
            status = signalSetRaw->rate[axis][red].status;
            /* flush rate status */
            mask = RBL_IMUSTDTYPES_STATUS_TMP_MASK;
            newStatus |= rbl_SigChain_debounce(mask, status, debounceSteps, &data->rate.Cnt->counter[axis][red]);

            /* flush rate init status */
            mask = RBL_IMUSTDTYPES_STATUS_INIT_MASK;
            newStatus |= rbl_SigChain_debounce(mask, status, debounceSteps, &data->rate.initCnt->counter[axis][red]);

            signalSetFil->rate[axis][red].status |= newStatus;
            /* copy rate signal status to derived rate signal status */
            signalSetDer->rate[axis][red].status = signalSetFil->rate[axis][red].status;
        }
    }
    return;
}

/* ****************************************************************************
 * ***** API private: rbl_SigChain_CalcSecOrdSctn *****
 * Description:
 *    calculation function for a second order section of a filter.
 *
 * Arguments:
 *    FilCoeff
 *    filTabs
 *    x
 *
 * Return:
 *    void
 *
 *
 *
 * Remarks:
 *    -
 * ****************************************************************************/
static float rbl_SigChain_CalcSecOrdSctn(const rbl_SigChain_Filter_t *FilCoeff, rbl_SigChain_FilTabs_t *filTabsArray, float32 x)
{
    float32 y;

    /* calculate new filter output */
    y = x * FilCoeff->facB[0];
    y += filTabsArray->filTabs[0][0] * FilCoeff->facB[1];
    y += filTabsArray->filTabs[0][1] * FilCoeff->facB[2];

    y -= filTabsArray->filTabs[1][0] * FilCoeff->facA[0];
    y -= filTabsArray->filTabs[1][1] * FilCoeff->facA[1];

    /* update filter tabs */
    filTabsArray->filTabs[0][1] = filTabsArray->filTabs[0][0];
    filTabsArray->filTabs[0][0] = x;

    filTabsArray->filTabs[1][1] = filTabsArray->filTabs[1][0];
    filTabsArray->filTabs[1][0] = y;

    return y;
}

static uint8 rbl_SigChain_debounce(uint8 mask, uint8 status, uint16 debounceSteps, uint16 *counter)
{
    uint8 retStatus=status;
    /* status set, set amount of debouncing steps */
    if (0u != (mask & status))
    {
        *counter = debounceSteps;
    }
    /* status not set, rbl_SigChain_debounce */
    else
    {
        if (*counter > 0)
        {
            *counter -= 1;
        }
        /* give old status until debouncing is over */
        if (*counter > 0)
        {
            retStatus |= mask;
        }
    }
    return retStatus;
}


/* ***** END_SECTION local functions ***** */
