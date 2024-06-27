/// @file rbl_SigChain_Init.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#include "rbl_SigChain_OsPub.h"
#include "rbl_SigChain_priv.h"
#include "rbl_SigChain_SigFil.h"
#include "Dem.h"
#include "rbl_ImuCdd_Interfaces.h"

static boolean rbl_SigChain_NVMcontentValid(uint32* activeModules);
static boolean rbl_SigChainActive_Init(uint32* activeModules);


uint32 rbl_SignalChainActive;            /* all active components of signal chain */

/*----------SigChain_stValid ---------*/
RBMESG_DefineMESG(SigChain_stValid);

/*[[MEASUREMENT*/
/*NAME=RBMESG_SigChain_stValid */
/*COMMENT= active signals for signal chain */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/* ****************************************************************************/
void rbl_SigChainInit(void)
{
    RBMESG_DefineMESGDef(SigChain_stValid);
    uint32 activeModules = 0;   /* which parts of signal chain shall be called */
    l_SigChain_stValid = FALSE; /* is the status valid, or is there some reason to set signals invalid */

    /*rbl_SigChain_InitFilter updates with selected Filter values when RBFS_NvmBasedFilter_ON in Nvm file */
    /*rbl_SigChain_InitFilter is set to NULL to avoid overwriting of the rbl_SigChain_FilVal and rbl_SigChain_SigFilFlush when RBFS_NvmBasedFilter_OFF  */

    rbl_SigChain_InitFilter(NULL, 0,0.0f);
#if (RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
    rbl_SigChain_InitFilter2(NULL, 0,0.0f);
#endif

    /* check which units are marked as active */
    if(FALSE != rbl_SigChainActive_Init(&activeModules))
    {
        /* check if NVM configuration of active units is valid */
        l_SigChain_stValid = rbl_SigChain_NVMcontentValid(&activeModules);
    }

    rbl_SignalChainActive = activeModules;
    RBMESG_SendMESGDef(SigChain_stValid);

    return;
}

static boolean rbl_SigChainActive_Init(uint32* activeModules)
{
    /* todo: change intermediate implementation if compiler switches are complete */
    *activeModules =  RBL_SIGCHAIN_ALL;
    return TRUE;

}

/* check which modules are active */
static boolean rbl_SigChain_NVMcontentValid(uint32* activeModules)
{
    uint32 nvm = 0;   /* contains bitmask of broken units */
    uint32 modules = *activeModules;
    boolean retVal = TRUE;  /* init with no faults found */

    /* if the stored configuration can't be read in NVM, then the unit won't be called in the signal chain */
    /* the bit of the unit with the broken configuration is visible in the DEM failure */
    /*___________________ Channel Mapper ___________________________ */
    /*___________________ TCOS ___________________________ */
    if (0u != (modules & RBL_IMU_TCOS))
    {
        if (FALSE == rbl_SigChain_TCOSAllNvmItemsValid() )
        {
            nvm |= RBL_IMU_TCOS;
        }
    }

    /*___________________ Alignement ___________________________ */
    if (0u != (modules & RBL_IMU_ALGN))
    {
        if (
                (FALSE == rbl_SigChain_AlgnAccSnvtyNvmVld )
                ||(FALSE == rbl_SigChain_Algn_RateSnvtyNvmVld ))
        {
            nvm |= RBL_IMU_ALGN;
        }
    }
#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
    /*___________________ Signal Filter ___________________________ */
    if (0u != (modules & RBL_IMU_SIGFIL))
    {
        if (FALSE == rbl_SigChain_SigFilNvmVld )
        {
            nvm |= RBL_IMU_SIGFIL;
        }
    }
#endif

    /*____________________ condensed results __________________________________*/
    if ( 0 != nvm)
    {
        retVal = FALSE;
        /* mark signals as invalid */
        *activeModules = (modules & ~nvm);
        /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
        (void)Dem_SetEventStatusWithMonitorData(DemConf_DemEventParameter_RBL_Nvm_SigChain_Content, DEM_EVENT_STATUS_FAILED, nvm, 0);
    }
    else
    {
        /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
        (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_Nvm_SigChain_Content, DEM_EVENT_STATUS_PASSED);
    }

    return retVal;
}

