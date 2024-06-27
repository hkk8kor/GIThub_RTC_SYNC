
/// @file rbl_SigChain_Nvm.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#include "Nvm.h"
#include "rbl_SigChain_Nvm.h"
#include "rbl_SigChain_priv.h"
#include "rbl_SigChain_SigFil.h"
#include "rbl_ImuCdd_Interfaces.h"
#include "rba_BswSrv.h"

#include "RB_Contract.h"  // for RB_CHECK_COMPATIBLE_FUNCTYPE()
#include "RBPDM.h"        // for RBPDM_NvMReadCallback_t/RBPDM_NvMWriteCallback_t


/* --------------------- nvm valid marker ---------------------------------*/

boolean rbl_SigChain_AlgnAccSnvtyNvmVld;
boolean rbl_SigChain_Algn_RateSnvtyNvmVld;

#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
boolean rbl_SigChain_SigFilNvmVld;
uint8 rbl_SigChain_PickFilValue[2];
#endif

boolean rbl_SigChain_NvmValidCheck(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    boolean valid = FALSE;
    if (ServiceId == NVM_SERVICE_ID_READ_ALL)
    {
        /*Startup*/
        if(JobResult == NVM_REQ_OK)
        {
            valid = TRUE;
        }
    }
    return valid;
}

Std_ReturnType rbl_SigChain_GenericWriteCb(void* NvMBuffer)
{
    // write is only allowed by plant with eeprom container. therefore this function is returning E_NOT_OK
    return E_NOT_OK;
}

/* ----------------------------- Alignment -------------------------------------------------*/

Std_ReturnType rbl_SigChain_AlgnAccSnvtyReadCb(const void* NvMBuffer)
{
    uint32 red;
    uint32 row;
    uint32 colum;
    uint32 i;
    sint16 matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
    rba_BswSrv_MemCopy8((uint8 *) matrix, (const uint8 *) NvMBuffer, sizeof(matrix));
    for (red=0; red< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC;red++)
    {
        for (row=0; row< RBL_IMUSTDTYPES_AXIS_NO;row++)
        {
            for (colum=0; colum< RBL_IMUSTDTYPES_AXIS_NO;colum++)
            {
                for (i=0; i< RBL_SIGCHAIN_ALGN_PNTS;i++)
                {
                    rbl_SigChain_AlgnAccOrthMtrx[red].AlgnOrthMtrx[row][colum][i] = matrix[red][row][colum][i];
                }
            }
        }
    }




    return E_OK;
}

Std_ReturnType rbl_SigChain_AlgnAccSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{

    rbl_SigChain_AlgnAccSnvtyNvmVld = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
    return E_OK;
}
Std_ReturnType rbl_SigChain_AlgnRateSnvtyReadCb(const void* NvMBuffer)
{
    uint32 red;
    // AlgnOrthMtrx[Row][Column][RBL_SIGCHAIN_ALGN_PNTS]
                                 uint32 row;
    uint32 colum;
    uint32 i;
    sint16 matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
    rba_BswSrv_MemCopy8((uint8 *) matrix, (const uint8 *) NvMBuffer, sizeof(matrix));
    for (red=0; red< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT;red++)
    {
        for (row=0; row< RBL_IMUSTDTYPES_AXIS_NO;row++)
        {
            for (colum=0; colum< RBL_IMUSTDTYPES_AXIS_NO;colum++)
            {
                for (i=0; i< RBL_SIGCHAIN_ALGN_PNTS;i++)
                {
                    rbl_SigChain_AlgnRateOrthMtrx[red].AlgnOrthMtrx[row][colum][i] = matrix[red][row][colum][i];
                }
            }
        }
    }
    return E_OK;
}

Std_ReturnType rbl_SigChain_AlgnRateSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{

    rbl_SigChain_Algn_RateSnvtyNvmVld = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);
    return E_OK;
}

#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
Std_ReturnType rbl_SigChain_PickFilResultCb(uint8 ServiceId, NvM_RequestResultType JobResult)
{
    boolean cfgVld = FALSE;

    if (ServiceId == NVM_SERVICE_ID_READ_ALL)
    {
        /*Startup*/
        if(JobResult == NVM_REQ_OK)
        {
            /* nvm read success, check filter content */
            cfgVld = TRUE;

            /* nvm read success, check filter content */
            switch(rbl_SigChain_PickFilValue[0])
            {
            /*rbl_SigChain_FilVal and rbl_SigChain_SigFilFlush updated with the selected filter  when RBFS_NvmBasedFilter_ON */
            case RBL_SIGCHAIN_NOFILTER:
                rbl_SigChain_InitFilter(&rbl_SigChain_FilValNoFilter, RBL_SIGCHAIN_SIGFILNONEFLUSH,0.0f);
                break;
            case RBL_SIGCHAIN_20HZFILTER:
                rbl_SigChain_InitFilter(&rbl_SigChain_FilVal20Hz, RBL_SIGCHAIN_SIGFIL20HZFLUSH, RBL_SIGCHAIN_TIMESTAMPDELAYMS20HZ);
            	break;
            case RBL_SIGCHAIN_45HZFILTER:
                rbl_SigChain_InitFilter(&rbl_SigChain_FilVal45Hz, RBL_SIGCHAIN_SIGFIL45HZFLUSH, RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ);
                break;
            default:
                rbl_SigChain_InitFilter(&rbl_SigChain_FilValNoFilter, RBL_SIGCHAIN_SIGFILNONEFLUSH,0.0f);
                break;
            }

        }
    }
    rbl_SigChain_SigFilNvmVld = cfgVld;
    return E_OK;
}
#endif //#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
