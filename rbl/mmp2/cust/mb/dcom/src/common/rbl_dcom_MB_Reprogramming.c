/// @file rbl_dcom_MB_Reprogramming.c
/// @brief This module provides API for jumping to BootLoader
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


/*
**********************************************************************************************************************
*  Includes
**********************************************************************************************************************
*/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "Dcm_Prv.h"

#include "rbl_dcom_MB_Pub.h"
#include "rbl_dcom_MB_Reprogramming.h"
#include "RBLCF_MemoryRemap.h"
#include "RB_SWReset.h"
#include "rba_DcmPma.h"

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
RBSECTION_START_REMAP_BSS(.buram_bb_noclear)
/** volatile is used for memory-mapped register so optimization shall not happen */
static volatile dcom_BackUp_RAM_tst DcmAppl_BackUp_RAM;
RBSECTION_END_REMAP_BSS
#endif


#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)

/** ****************************************************************************
* ***** API public: dcom_SetProgConditions ***** */

void dcom_SetProgConditions(void)
{

#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)

       /* Indicate that the bootloader is to be started */
     DcmAppl_BackUp_RAM.Bldr_Start_Request_Inverted = DCOM_REQPROGREQUESTINVERTED;

     /* Indicate that programming session is to be started */
    #if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
     /* Check for tester and enable FBL to init on same tester */
        if (DCOM_SECOND_TESTER == dcom_Requested_Tester)
        {
            DcmAppl_BackUp_RAM.Bldr_Reset_Reason = DCOM_PROGRAMMINGSESSION_2NDTESTER;
        }
     else
    #endif
        {
            DcmAppl_BackUp_RAM.Bldr_Reset_Reason = DCOM_PROGRAMMINGSESSION;
        }

     /* disable watchdog and reset, startup in Bootloader */
     RB_performSWResetWithBootBlock4OEM();

#endif
}

/****** END_API dcom_SetProgConditions ***** */

#else

#if (DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

/** ****************************************************************************
* ***** API public: dcom_SetProgConditions ***** */

Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType * ProgConditions)
{
    Std_ReturnType retVal = E_OK;
    /* To avoid Warnings */
    (void)OpStatus;

    #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)


       /* Indicate that the bootloader is to be started */
        DcmAppl_BackUp_RAM.Bldr_Start_Request_Inverted = DCOM_REQPROGREQUESTINVERTED;

         /* Indicate that programming session is to be started */
    #if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)

         /* Check for tester and enable FBL to init on same tester */
        if (DCOM_SECOND_TESTER == dcom_Requested_Tester)
        {
            DcmAppl_BackUp_RAM.Bldr_Reset_Reason = DCOM_PROGRAMMINGSESSION_2NDTESTER;
        }
        else
    #endif
        {
            DcmAppl_BackUp_RAM.Bldr_Reset_Reason = DCOM_PROGRAMMINGSESSION;
        }
    #endif

    return retVal;
}

/****** END_API dcom_SetProgConditions ***** */


/** ****************************************************************************
* ***** API public: DcmAppl_DcmGetStoreType ***** */
uint8 DcmAppl_DcmGetStoreType(uint8 dataBootType_u8, uint8 SID)
{
    uint8 retVal = DCM_NOTVALID_TYPE;
    /* To avoid Warnings */
    (void)dataBootType_u8;
    (void)SID;

    #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
        retVal = DCM_WARMRESPONSE_TYPE;
    #endif

    return retVal;
}

/****** END_API DcmAppl_DcmGetStoreType ***** */


/** ****************************************************************************
* ***** API public: DcmAppl_DcmGetStoreType ***** */
void DcmAppl_Switch_DcmExecuteDscReset(uint8 SessionLevel_u8)
{
   (void)SessionLevel_u8;

   #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
   if(rba_DcmPma_PlantModeStatus_b != TRUE)
   {
       RB_performSWResetWithBootBlock4OEM();
   }
   #endif

}
/****** END_API DcmAppl_Switch_DcmExecuteDscReset ***** */

#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

/** ****************************************************************************
* ***** API public: Dcm_GetProgConditions ***** */

Dcm_EcuStartModeType Dcm_GetProgConditions (Dcm_ProgConditionsType * ProgConditions)
{
    Dcm_EcuStartModeType retVal = DCM_COLD_START;

	#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
      uint16 dataTimingValue = 0;
      uint32 bldr_reset_reason = DcmAppl_BackUp_RAM.Bldr_Reset_Reason;


           /***Tester address allocated based on the reset reason flag***/
        if((bldr_reset_reason == DCOM_DEFAULTSESSION )||(bldr_reset_reason == DCOM_HARDRESET))
		{
			/***Response should be send on external tester***/
            ProgConditions->ProtocolId       = DCM_SUPPLIER_1;
            ProgConditions->TesterSourceAddr = 0xEF8;
        }

	#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
        else if((bldr_reset_reason == DCOM_DEFAULTSESSION_2NDTESTER)||(bldr_reset_reason == DCOM_HARDRESET_2NDTESTER))
        {
			/***Response should be send on internal tester***/
			ProgConditions->ProtocolId       = DCM_SUPPLIER_2;
			ProgConditions->TesterSourceAddr = 0xF0D;
        }
	#endif
        else
		{
            /*do nothing*/
        }


		switch(bldr_reset_reason)
		{

		case DCOM_DEFAULTSESSION:
	#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		case DCOM_DEFAULTSESSION_2NDTESTER:
	#endif
	        /** Origin was default session request, send positive response 0x50  */
		    ProgConditions->SessionLevel     = 0x01;
		    ProgConditions->Sid              = 0x50;
		    ProgConditions->SubFncId         = 0x01;
			ProgConditions->ReqResLen        = 0x2;
			ProgConditions->StoreType        = DCM_WARMRESPONSE_TYPE;
			ProgConditions->ApplUpdated      = TRUE;
			ProgConditions->ResponseRequired = TRUE;
			/** Fill P2 Max Time */
			dataTimingValue = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000);
			ProgConditions->ReqResBuf[0] = (uint8)(dataTimingValue >> 8);
			ProgConditions->ReqResBuf[1] = (uint8)(dataTimingValue & 0x00FFu);
			/** Fill P2 Star Max Time */
			dataTimingValue = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000);
			ProgConditions->ReqResBuf[2] = (uint8)(dataTimingValue >> 8);
			ProgConditions->ReqResBuf[3] = (uint8)(dataTimingValue & 0x00FFu);
			ProgConditions->ReqResLen += 0x4;

            retVal = DCM_WARM_START;
        break;


		case DCOM_HARDRESET:
	#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		case DCOM_HARDRESET_2NDTESTER:
	#endif

            /** Origin was ECU reset request, send positive response 0x51  */
            ProgConditions->SessionLevel     = 0x01;
            ProgConditions->Sid              = 0x51;
            ProgConditions->SubFncId         = 0x01;
            ProgConditions->ReqResLen        = 0x2;
            ProgConditions->StoreType        = DCM_WARMRESPONSE_TYPE;
            ProgConditions->ApplUpdated      = TRUE;
            ProgConditions->ResponseRequired = TRUE;

            retVal = DCM_WARM_START;
        break;


        default:

            retVal = DCM_COLD_START;

        break;

        }



     #endif

    return retVal;
}

/****** END_API Dcm_GetProgConditions ***** */
#endif

#endif
