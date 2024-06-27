#ifndef RBEMM_CONFIGSETTINGS_H__
#define RBEMM_CONFIGSETTINGS_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "rb/as/core/app/dsm/api/RBDSM_ConfigElements.h"
#include "rb/as/core/app/dsm/rbemm/RBEMM/api/RBEMM_ConfigElements.h"
#include "rbl/mmp2/ms/cswpr/cfg/RB_Prj_GlobalSettings.h"
/******************************************************************************/
/*** Start / Start / Start / Start / Start / Start / Start / Start / Start / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/

/**********************************************************************************/

/**********************************************************************************/
// 1. Function-Switch Settings
/*******************************************************************************/

/*******************************************************************************/
// BUILDCONFIG for ProjectBuildGroup HWRef
/**********************************************************************************/

/*******************************************************************************/
// BUILDCONFIG for ProjectBuildGroup HWRef

/*******************************************************************************/


/**********************************************************************************/

#if ((RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xDevBoard) \
  || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xTargetBoard ) \
  || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xDevBoard ) \
  || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xTargetBoard ))

    #if ((RBFS_MMP2 == RBFS_MMP2_IMUB))
        #define RBFS_EMMConfiguredNetworkChannels             RBFS_EMMConfiguredNetworkChannels_3
    #elif ((RBFS_MMP2 == RBFS_MMP2_IMUD))
	    #define RBFS_EMMConfiguredNetworkChannels             RBFS_EMMConfiguredNetworkChannels_1
    #else
       #define RBFS_EMMConfiguredNetworkChannels                 RBFS_EMMConfiguredNetworkChannels_2
    #endif




    #if((RBFS_NwManagement == RBFS_NwManagement_Can) && (RBFS_BuildConfigType == RBFS_BuildConfigType_APPLICATION))
        #define RBFS_EMM                                          RBFS_EMM_Extended
	    #define RBFS_EMMSupportNetworkMgmtMain                    RBFS_EMMSupportNetworkMgmtMain_SingleNM
        #define RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF     RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF_On
	    #define RBFS_EMMExtendedOnlineGenerationForBswMEcuM       RBFS_EMMExtendedOnlineGenerationForBswMEcuM_On
    #else
        #define RBFS_EMM                                          RBFS_EMM_Basic
        #define RBFS_EMMSupportNetworkMgmtMain                    RBFS_EMMSupportNetworkMgmtMain_Disabled
        #define RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF     RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF_Off
        #define RBFS_EMMExtendedOnlineGenerationForBswMEcuM       RBFS_EMMExtendedOnlineGenerationForBswMEcuM_Off
    #endif

#else

	#if (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP2xDevBoard)
		#define RBFS_EMMConfiguredNetworkChannels             RBFS_EMMConfiguredNetworkChannels_1
	#elif ((RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB0xDevBoard) || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB0xTargetBoard ))
		#define RBFS_EMMConfiguredNetworkChannels             RBFS_EMMConfiguredNetworkChannels_2
	#endif

	#define RBFS_EMM                                          RBFS_EMM_Basic
	#if(RBFS_NwManagement == RBFS_NwManagement_Can)
		#define RBFS_EMMSupportNetworkMgmtMain                RBFS_EMMSupportNetworkMgmtMain_SingleNM
	#else
		#define RBFS_EMMSupportNetworkMgmtMain                RBFS_EMMSupportNetworkMgmtMain_Disabled
	#endif

    #define RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF     RBFS_EMMSupportNetworkMgmtCANPpeBusSlp2NETOFF_On
    #define RBFS_EMMExtendedOnlineGenerationForBswMEcuM       RBFS_EMMExtendedOnlineGenerationForBswMEcuM_Off

#endif

// RBEMM Features
#define RBFS_EMMSupportEcuPostRunAbortWithNetOff      RBFS_EMMSupportEcuPostRunAbortWithNetOff_Off
#define RBFS_EMMSupportWakeupViaLIN                   RBFS_EMMSupportWakeupViaLIN_Off
#define RBFS_EMMExTrcvSleepAdditionalRetries          RBFS_EMMExTrcvSleepAdditionalRetries_Off
#define RBFS_EMMExTrcvSleepLogging                    RBFS_EMMExTrcvSleepLogging_Off
#define RBFS_EMMExTrcvGetWakeUpReason                 RBFS_EMMExTrcvGetWakeUpReason_Off
#define RBFS_EMMGetStateOfRBWauClients                RBFS_EMMGetStateOfRBWauClients_Off

#if (RBFS_EMM == RBFS_EMM_Extended)
	// new define, needed only for EMM Extended
	#define RBEMM_Project_ExtendedBaseOSMaxChannels       1u
#endif

#ifndef RBFS_EMMSimulation
    #define RBFS_EMMSimulation  RBFS_EMMSimulation_Off
#endif

// dependently from Software Architecture!
// One for all HWRef RBFS_BUILDCONFIGs, but can be separated too
#define RBFS_EMMSupportPreEmptiveTaskOrMultiCore      RBFS_EMMSupportPreEmptiveTaskOrMultiCore_Off

// RBEMM Debugging
// One for all HWRef RBFS_BUILDCONFIGs, but can be separated too
#if (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
#define RBFS_EMMSupportDET                            RBFS_EMMSupportDET_Off
#define RBFS_EMMSupportDebugging                      RBFS_EMMSupportDebugging_Off
#else
#define RBFS_EMMSupportDET                            RBFS_EMMSupportDET_On
#define RBFS_EMMSupportDebugging                      RBFS_EMMSupportDebugging_On
#endif

/**********************************************************************************/
// 2. Customer specific define

// DET RBEMM Configuration
// One for all RBFS_BUILDCONFIGs, but can be separated too
#define RBA_DET_RBEMM_MODULE_ID                       ((uint16)300) // compare with AUTOSAR_TR_BSWModuleList.pdf, use an unspecified ID!

/******************************************************************************/
/*** End / End / End / End / End / End / End / End / End / End / End / End / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/

/**********************************************************************************/
/* Default setting for RBFS_EcuM and RBFS_BswM is OFF. This can however be overrided using
 * project specific settings for the switches RBFS_EcuM and RBFS_BswM.
 */
#if (RBFS_EMM == RBFS_EMM_Extended)
    #ifndef RBFS_EcuM
        #define RBFS_EcuM RBFS_EcuM_On
    #endif
    #ifndef RBFS_BswM
        #define RBFS_BswM RBFS_BswM_On
    #endif
#else
    #ifndef RBFS_EcuM
        #define RBFS_EcuM RBFS_EcuM_Off
    #endif
    #ifndef RBFS_BswM
        #define RBFS_BswM RBFS_BswM_Off
    #endif
#endif
/**********************************************************************************/

#endif /* INCLUDE PROTECTION: RBEMM_CONFIGSETTINGS_H__ */
