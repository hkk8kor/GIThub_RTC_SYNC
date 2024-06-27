/// @file rbl_dcom_MB_Main.c
/// @brief The file consists of the proc functions for Dcom module
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/* ***** Includes ***** */
#include "Dem.h"
#include "rbl_dcom_MB_OsPub.h"
#include "rbl_dcom_MB_RollbackProtection.h"
#include "rbl_dcom_Lib.h"
#include "rbl_dcom_MB_RWDBI_VariantCoding.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */
/* Constants and Macro definitions */

/* Variables */

uint8 rbl_SnsrSerlNr_RAM_Mirror[16]= {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}; // RAM mirror Sensor serial number
uint8 rbl_dcom_DCOM_MB_HW_PartNumber[10] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}; //RAM mirror HW part number
uint8 rbl_ECU_SerialNr_RAM_Mirror[17]= {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30}; // RAM mirror ECU serial number

/* Structure definitions */

/* ***** PUBLIC/PROTECTED API functions ***** */
/* *********************************************************************************************************************
 * ***** API public: rbl_dcom_MB_Init_Proc *****/
void rbl_dcom_MB_Init_Proc(void)
{
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)

    NvM_RequestResultType l_NvM_Result = NVM_REQ_NOT_OK;

    /*Check if NVM iteam is not empty*/
    (void)NvM_GetErrorStatus(NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH,&l_NvM_Result);
    /*varinat monitoring for Valid Varinat is coded or not i.e. MB/AMG */
    if ((NVM_REQ_OK == l_NvM_Result) && \
        ((rbl_dcom_MirrorAMGVarSwitch_u8[0]== RBL_MB_VARIANT) || (rbl_dcom_MirrorAMGVarSwitch_u8[0]== RBL_AMG_VARIANT)))
    {
        /*Passed the DTC for valid Varinats */
        (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_NVM_Variant_handler, DEM_EVENT_STATUS_PASSED);
    }
    else
    {
        /*Failed the DTC for invalid Varinats */
        (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_NVM_Variant_handler, DEM_EVENT_STATUS_FAILED);
    }

#endif
}
/* ***** END_API rbl_dcom_MB_Init_Proc ***** */

/* *********************************************************************************************************************
 * ***** API public: dcom_MB_20ms_Proc *****/

void rbl_dcom_MB_20ms_Proc(void)
{
    rbl_dcom_DowngradeProtection_Check();
}
/* ***** END_API dcom_MB_20ms_Proc ***** */

/* ***** END_SECTION API functions ***** */
