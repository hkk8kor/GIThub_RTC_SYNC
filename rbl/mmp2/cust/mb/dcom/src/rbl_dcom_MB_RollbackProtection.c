/// @file rbl_dcom_MB_RollbackProtection.c
/// @brief This file provides Rollback Protection Feature related services
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */
#include "rbl_dcom_MB_RollbackProtection.h"
/* ***** END_SECTION Includes ***** */

/* ***** SECTION  Definitions ***** */

static uint8 rbl_dcom_MinSwVer[3];
static rbl_dcom_DPVcheck_state dcom_MinSwVer_State = READ_STATE;


 /* ****************************************************************************
  * ***** API public: rbl_dcom_DowngradeProtection_Check ***** */
void rbl_dcom_DowngradeProtection_Check(void)
{

    Std_ReturnType  statusNvm = E_NOT_OK;
    Dcm_NegativeResponseCodeType  ErrorCode = 0;

    switch (dcom_MinSwVer_State)
    {

    /*Initiates MSV NVM Read operation */
    case READ_STATE:

        /*Call to NvM read Generic api for reading the Minimum software version number  */
        statusNvm = dcom_Lib_ReadNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion,
                rbl_dcom_MinSwVer, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion, DCOM_READ_PDMEMPTY);

        if(E_OK == statusNvm)
        {
            /*Check if Minimum Software version is equal to Downgrade Protection version*/
            if((rbl_dcom_MinSwVer[0] != DCOM_DPV_SOFTWARE_VERSION_YEAR)||(rbl_dcom_MinSwVer[1] != DCOM_DPV_SOFTWARE_VERSION_WEEK)||(rbl_dcom_MinSwVer[2] != DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL))
            {
                /*Updates Minimum Software version with Downgrade Protection version*/
                rbl_dcom_MinSwVer[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
                rbl_dcom_MinSwVer[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
                rbl_dcom_MinSwVer[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL;
                dcom_MinSwVer_State = WRITE_STATE;
            }
            else
            {
                dcom_MinSwVer_State = IDLE_STATE;
            }
        }
        break;

    /*Initiates MSV NVM Write operation */
    case WRITE_STATE:

        /*Call to NvM write Generic api for writing the Minimum software version number  */
        statusNvm = dcom_Lib_WriteNvMData(NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion, rbl_dcom_MinSwVer,&ErrorCode);

        if (E_OK == statusNvm)
        {
            dcom_MinSwVer_State = IDLE_STATE;
        }

        break;

    default:

         // nothing to do in idle state, or if read / write was finished
        break;
    }

}
/* ***** END_API rbl_dcom_DowngradeProtection_Check ***** */




/* ***** END_SECTION API functions ***** */
