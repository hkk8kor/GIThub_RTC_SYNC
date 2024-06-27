/// @file rbl_dcom_PlantModeActivation.c
/// @brief This file is used to  fill in the Plant mode activation type
/// @copyright (C) 2012 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

#include "rba_DcmPma.h"
#include "RBTSI_RbDiagInit.h"
#include "RBSYS_PlantStartupCtrl.h"

/**
 * @ingroup RBA_DCMPMA_TPL
 */

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/

#include "Dcm_Cfg_MemMap.h"

/* ****************************************************************************
 * ***** API public: rba_DcmPmaAppl_PlantModeActivation  ***** */
void rba_DcmPmaAppl_PlantModeActivation(boolean stActive_b)
{
    if (stActive_b)
    {
        FUN_InitializeTSI_V();
    }
    else
    {
        FUN_DiagExitInit_V();
    }
}
/* ***** END_API rba_DcmPmaAppl_PlantModeActivation   ***** */


/* ****************************************************************************
 * ***** API public: rba_DcmPmaAppl_FillPlantModeResponse  ***** */
uint8 rba_DcmPmaAppl_FillPlantModeResponse(void)
{
    uint8 retVal = 0x00;

    BOOL BaseOsStatus = RBSYS_isBaseOSActive();

    if (BaseOsStatus == TRUE)
    {
        retVal = 0x01;
    }

    return retVal;
    /*Returns one byte positive response for service 0x80*/
}
/* ***** END_API rba_DcmPmaAppl_FillPlantModeResponse  ***** */
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
