/// @file rbl_SigChain_NvmTCOS.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "Nvm.h"
#include "rbl_SigChain_Nvm.h"
#include "rbl_SigChain_priv.h"
#include "rba_BswSrv.h"

#include "RBPDM.h"        // for RBPDM_NvMReadCallback_t/RBPDM_NvMWriteCallback_t

static boolean rbl_SigChain_TCOAccVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
static boolean rbl_SigChain_TCORateVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
static boolean rbl_SigChain_TCSAccVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
static boolean rbl_SigChain_TCSRateVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];

/* wrapper functions, as each redundancy has its own pdm item but writes in a common struct */
static Std_ReturnType rbl_SigChain_TCOAccRedXReadCb(const void* NvMBuffer, uint8 x);
static Std_ReturnType rbl_SigChain_TCOAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
static Std_ReturnType rbl_SigChain_TCORateRedXReadCb(const void* NvMBuffer, uint8 x);
static Std_ReturnType rbl_SigChain_TCORateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
static Std_ReturnType rbl_SigChain_TCSAccRedXReadCb(const void* NvMBuffer, uint8 x);
static Std_ReturnType rbl_SigChain_TCSAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
static Std_ReturnType rbl_SigChain_TCSRateRedXReadCb(const void* NvMBuffer, uint8 x);
static Std_ReturnType rbl_SigChain_TCSRateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);

/****                                ACC Offset                                                              ***/
static Std_ReturnType rbl_SigChain_TCOAccRedXReadCb(const void* NvMBuffer, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC >= x)
    {

        /* temporary array for Nvm values to avoid pointer arithmetic on NvmBuffer pointer */
        uint8 values[3*RBL_SIGCHAIN_SIZEOFTCOPNTS] = {0};
        /* cast from void pointer to uint8 for copy */
        rba_BswSrv_MemCopy8(values, (const uint8 *) NvMBuffer, 3*RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_X][x][0]), values, RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_Y][x][0]), &values[RBL_SIGCHAIN_SIZEOFTCOPNTS], RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_Z][x][0]), &values[2*RBL_SIGCHAIN_SIZEOFTCOPNTS], RBL_SIGCHAIN_SIZEOFTCOPNTS);

        retVal = E_OK;
    }
    return retVal;
}

static Std_ReturnType rbl_SigChain_TCOAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC >= x)
    {
        rbl_SigChain_TCOAccVld[x] = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
        retVal = E_OK;
    }
    return retVal;
}

/**** ______________________________ TCOAccRed0 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCOAccRed0ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCOAccRedXReadCb(NvMBuffer, 0u);
}

Std_ReturnType rbl_SigChain_TCOAccRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCOAccRedXResultCb(ServiceId,JobResult,0u);
}

/**** ______________________________ TCOAccRed1 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCOAccRed1ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCOAccRedXReadCb(NvMBuffer, 1u);
}

Std_ReturnType rbl_SigChain_TCOAccRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCOAccRedXResultCb(ServiceId,JobResult,1u);
}
/**** ______________________________ TCOAccRed2 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCOAccRed2ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCOAccRedXReadCb(NvMBuffer, 2u);
}


Std_ReturnType rbl_SigChain_TCOAccRed2ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCOAccRedXResultCb(ServiceId,JobResult,2u);
}
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/**** ______________________________ TCOAccRed3 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCOAccRed3ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCOAccRedXReadCb(NvMBuffer, 3u);
}


Std_ReturnType rbl_SigChain_TCOAccRed3ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCOAccRedXResultCb(ServiceId,JobResult,3u);
}
#endif

static Std_ReturnType rbl_SigChain_TCORateRedXReadCb(const void* NvMBuffer, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT >= x)
    {
        /* temporary array for Nvm values to avoid pointer arithmetic on NvmBuffer pointer */
        uint8 values[3*RBL_SIGCHAIN_SIZEOFTCOPNTS] = {0};
        /* cast from void pointer to uint8 for copy */
        rba_BswSrv_MemCopy8(values, (const uint8 *) NvMBuffer, 3*RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_X][x][0]), values, RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_Y][x][0]), &values[RBL_SIGCHAIN_SIZEOFTCOPNTS], RBL_SIGCHAIN_SIZEOFTCOPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_Z][x][0]), &values[2*RBL_SIGCHAIN_SIZEOFTCOPNTS], RBL_SIGCHAIN_SIZEOFTCOPNTS);
        retVal = E_OK;
    }
    return retVal;
}


static Std_ReturnType rbl_SigChain_TCORateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT >= x)
    {
        rbl_SigChain_TCORateVld[x] = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
        retVal = E_OK;
    }
    return retVal;
}


/**** ______________________________ TCORateRed0 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCORateRed0ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCORateRedXReadCb(NvMBuffer, 0u);
}

Std_ReturnType rbl_SigChain_TCORateRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCORateRedXResultCb(ServiceId,JobResult,0u);
}

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/**** ______________________________ TCORateRed1 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCORateRed1ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCORateRedXReadCb(NvMBuffer, 1u);
}

Std_ReturnType rbl_SigChain_TCORateRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCORateRedXResultCb(ServiceId,JobResult,1u);
}
#endif

/****                                ACC Sensitivity                                                              ***/
static Std_ReturnType rbl_SigChain_TCSAccRedXReadCb(const void* NvMBuffer, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC >= x)
    {
        /* temporary array for Nvm values to avoid pointer arithmetic on NvmBuffer pointer */
        uint8 values[3*RBL_SIGCHAIN_SIZEOFTCSPNTS] = {0};
        /* cast from void pointer to uint8 for copy */
        rba_BswSrv_MemCopy8(values, (const uint8 *) NvMBuffer, 3*RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_X][x][0]), values, RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_Y][x][0]), &values[RBL_SIGCHAIN_SIZEOFTCSPNTS], RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_Z][x][0]), &values[2*RBL_SIGCHAIN_SIZEOFTCSPNTS], RBL_SIGCHAIN_SIZEOFTCSPNTS);

        retVal = E_OK;
    }
    return retVal;
}

static Std_ReturnType rbl_SigChain_TCSAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC >= x)
    {
        rbl_SigChain_TCSAccVld[x] = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
        retVal = E_OK;
    }
    return retVal;
}
/**** ______________________________ TCSAccRed0 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSAccRed0ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSAccRedXReadCb(NvMBuffer, 0u);
}


Std_ReturnType rbl_SigChain_TCSAccRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSAccRedXResultCb(ServiceId,JobResult,0u);
}

/**** ______________________________ TCSAccRed1 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSAccRed1ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSAccRedXReadCb(NvMBuffer, 1u);
}

Std_ReturnType rbl_SigChain_TCSAccRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSAccRedXResultCb(ServiceId,JobResult,1u);
}
/**** ______________________________ TCSAccRed2 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSAccRed2ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSAccRedXReadCb(NvMBuffer, 2u);
}


Std_ReturnType rbl_SigChain_TCSAccRed2ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSAccRedXResultCb(ServiceId,JobResult,2u);
}

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/**** ______________________________ TCSAccRed3 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSAccRed3ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSAccRedXReadCb(NvMBuffer, 3u);
}


Std_ReturnType rbl_SigChain_TCSAccRed3ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSAccRedXResultCb(ServiceId,JobResult,3u);
}
#endif

static Std_ReturnType rbl_SigChain_TCSRateRedXReadCb(const void* NvMBuffer, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT >= x)
    {

        /* temporary array for Nvm values to avoid pointer arithmetic on NvmBuffer pointer */
        uint8 values[3*RBL_SIGCHAIN_SIZEOFTCSPNTS] = {0};
        /* cast from void pointer to uint8 for copy */
        rba_BswSrv_MemCopy8(values, (const uint8 *) NvMBuffer, 3*RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_X][x][0]), values , RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_Y][x][0]), &values[RBL_SIGCHAIN_SIZEOFTCSPNTS], RBL_SIGCHAIN_SIZEOFTCSPNTS);
        /* cast to uint8 * for memcopy */
        rba_BswSrv_MemCopy8((uint8 *) &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_Z][x][0]), &values[2*RBL_SIGCHAIN_SIZEOFTCSPNTS], RBL_SIGCHAIN_SIZEOFTCSPNTS);
        retVal = E_OK;
    }
    return retVal;
}

static Std_ReturnType rbl_SigChain_TCSRateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x)
{
    Std_ReturnType retVal = E_NOT_OK;
    if (RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT >= x)
    {
        rbl_SigChain_TCSRateVld[x] = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
        retVal = E_OK;
    }
    return retVal;
}


/**** ______________________________ TCSRateRed0 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSRateRed0ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSRateRedXReadCb(NvMBuffer, 0u);
}


Std_ReturnType rbl_SigChain_TCSRateRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSRateRedXResultCb(ServiceId,JobResult,0u);
}

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/**** ______________________________ TCSRateRed1 ______________________________________________________  ***/
Std_ReturnType rbl_SigChain_TCSRateRed1ReadCb(const void* NvMBuffer)
{
    return rbl_SigChain_TCSRateRedXReadCb(NvMBuffer, 1u);
}


Std_ReturnType rbl_SigChain_TCSRateRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    return rbl_SigChain_TCSRateRedXResultCb(ServiceId,JobResult,1u);
}
#endif

boolean rbl_SigChain_TCOSAllNvmItemsValid(void)
{
    uint8 i;
    boolean status = TRUE;

    for(i=0;i<RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC;i++)
    {
        status = status && rbl_SigChain_TCSAccVld[i];
        status = status && rbl_SigChain_TCOAccVld[i];
    }
    for(i=0;i<RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT;i++)
    {
        status = status && rbl_SigChain_TCSRateVld[i];
        status = status && rbl_SigChain_TCORateVld[i];
    }
    return status;

}


