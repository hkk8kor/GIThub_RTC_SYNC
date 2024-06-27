/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

/**********************************************************************************/
/* MANDATORY_INTERFACES:               */
#include "Std_Types.h"
#include "RBEMM_Config.h"
#include "RBEMM_Types.h"
/* MANDATORY_INTERFACES_END:           */

/**********************************************************************************/
/* USED_INTERFACES:                    */
#include "RBEMM_Project.h"
#include "RBPduHandler_Callouts.h"
#include "rbl/mmp2/ms/cswpr/cfg/RB_Prj_GlobalSettings.h"

#if(RBFS_NetworkManagement == RBFS_NetworkManagement_On)
#include "Nm.h"
#endif
/* USED_INTERFACES_END:                */
/**********************************************************************************/

/**********************************************************************************/
/* REALIZED_INTERFACES:                */
/* REALIZED_INTERFACES_END:            */
/**********************************************************************************/

/**********************************************************************************/
/* USED_SWITCHES:                     */
/* USED_SWITCHES_END:                 */
/**********************************************************************************/

/**********************************************************************************/
/* SUPPORTED_SWITCH_SETTINGS:          */
/* SUPPORTED_SWITCH_SETTINGS_END:      */
/**********************************************************************************/

/**********************************************************************************/
/* LOCAL_DEFINE_EXPRESSIONS:           */
/* LOCAL_DEFINE_EXPRESSIONS_END:       */
/**********************************************************************************/

/**********************************************************************************/
/* LOCAL_TYPE_DEFINITIONS:             */
/* LOCAL_TYPE_DEFINITIONS_END:         */
/**********************************************************************************/

/**********************************************************************************/
/* DATA_OBJECT_DEFINITIONS:            */
/* DATA_OBJECT_DEFINITIONS_END:        */
/**********************************************************************************/

/**********************************************************************************/
/* LOCAL_FUNCTION_PROTOTYPES:          */
/* LOCAL_FUNCTION_PROTOTYPES_END:      */
/**********************************************************************************/

/**********************************************************************************/
/* FUNCTION_DEFINITIONS:               */
/* FUNCTION_DEFINITIONS_END:           */
/**********************************************************************************/

/**********************************************************************************/
/* PROCESS_DEFINITIONS:                */
/* PROCESS_DEFINITIONS_END:            */
/**********************************************************************************/

/**********************************************************************************/
/* FUNCTION_IMPLEMENTATION:                                                       */
/**********************************************************************************/
/* Projects are responsible for starting and stopping the Ipdugroups pertaining to
 * a particular network channel. Lin network still needs special handling. Since LIN
 * sleep is not implemented, LIN channel will be always in FULLCOMM . Lin schedule
 * is enabled based on any other network. CUrrently LIN schedule table is
 * requested/released in sync with other channels state (say "CAN"). Therefore
 * Use any of the Prj_EnableApplPdusForThisChannel function to enable Lin schedule within the
 * project specific part.
 */

/******************************************************************************/
/*** Start / Start / Start / Start / Start / Start / Start / Start / Start / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/

/**********************************************************************************/
// 1. Function Switches:
// => please refer to RBEMM_ConfigSettings.h

/**********************************************************************************/
// 2. Application callbacks
// => please refer to RBPduHandler_Callouts.h

/**********************************************************************************/
// 3. RBEMM Network-Channel Parameters

#if ((RBFS_EMM == RBFS_EMM_Basic)  || \
     (RBFS_EMM == RBFS_EMM_Extended))
/*******************************************************************************/
// BUILDCONFIG for ProjectBuildGroup HWRef

/*******************************************************************************/
// BUILDCONFIG for ISW DEV mainstream build options !!!
//#if (RBFS_HWREFEMMCLUSTER == RBFS_HWREFEMMCLUSTER_CANAsicInt)
/**********************************************************************************/
// EMM configuration table
const RBEMM_PrjNetwork_ParamType g_RBEMM_Prj_NetworkChnlPara_ast[RBEMM_PROJECT_NETWORK_MAXCHANNELS] =
    {
        /* !!! Start !!! */
        {C_RBEMM_BUSTYPE_CAN_01_N,
        {C_RBEMM_NoWakeupByBus_N, EMM_RBWAU_No_CLIENT},                         /* identifier to configure wake-up support and RBWau client (refer to schematic) */
    #if (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP2xDevBoard)
    	{C_RBEMM_TrcvTypeCANASICInternal_N, CANTRCV_CANTRCVCHANNEL_0},        /* refer to CanTrcv_Cfg.h */
    #elif ((RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB0xDevBoard) \
        || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB0xTargetBoard ) \
        || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xDevBoard) \
        || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xTargetBoard) \
        || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xDevBoard ) \
        || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xTargetBoard ) )
		//double check//?
        #if (RBFS_ComBase == RBFS_ComBase_COMxRBxPlantxV3)
            {C_RBEMM_TrcvTypeExtCAN_TJA1043_N, CANTRCV_CANTRCVCHANNEL_0},        /* refer to CanTrcv_Cfg.h */
        #else
            {C_RBEMM_TrcvTypeExtCAN_TJA104x_EE_N, EMM_Trcv_DummyClientTJA104x_ElcEbd},        /* refer to CanTrcv_Cfg.h */
        #endif
    #else
        #error ("Can transceiver configuration missing for EMM!")
    #endif
        {ComMConf_ComMChannel_ComMChannel_Can, ComMConf_ComMUser_ComMUser_Can}, /* refer to ComM_Cfg.h */
        {FALSE, EMM_CFG_NO_NM},                                                 /* no NM */
         EMM_CFG_NO_REQUESTER,                                                   /* NM needs SMM Requester, refer to RBSMM_Requester_Cfg.h */
    #if (RBFS_EMM == RBFS_EMM_Basic)
        & Prj_EnableApplPDUsNetworkChannel_1,
        &Prj_DisableApplPDUsNetworkChannel_1
    #endif

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
        },
        /* !!! Start !!! */
        {C_RBEMM_BUSTYPE_CAN_02_N,
        /* Wake up handling is done in RB_Prj_GlobalSettings.h for MMP2 variants */
    #if(RBFS_NwManagement == RBFS_NwManagement_Can)
        {C_RBEMM_WakeupByBus_N, RBWAU_Client_Can2Trcv},                         /* identifier to configure wake-up support and RBWau client (refer to schematic) */
    #else
        {C_RBEMM_NoWakeupByBus_N, EMM_RBWAU_No_CLIENT},                         /* identifier to configure wake-up support and RBWau client (refer to schematic) */
    #endif
        {C_RBEMM_TrcvTypeExtCAN_TJA1145_ATA6572_N, CANTRCV_CANTRCVCHANNEL_0},        /* refer to CanTrcv_Cfg.h */
        {ComMConf_ComMChannel_ComMChannel_Can1, ComMConf_ComMUser_ComMUser_Can1}, /* refer to ComM_Cfg.h */
        {FALSE, EMM_CFG_NO_NM},                                                 /* no NM */
        EMM_CFG_NO_REQUESTER,                                                   /* NM needs SMM Requester, refer to RBSMM_Requester_Cfg.h */
    #if (RBFS_EMM == RBFS_EMM_Basic)
        &Prj_EnableApplPDUsNetworkChannel_2,
        &Prj_DisableApplPDUsNetworkChannel_2
    #endif
#endif

#if (RBFS_ThirdCanSupport == RBFS_ThirdCanSupport_Yes)
        },
        /* !!! Start !!! */
        {C_RBEMM_BUSTYPE_CAN_03_N,
        /* Wake up handling is done in RB_Prj_GlobalSettings.h for MMP2 variants */
    #if(RBFS_NwManagement == RBFS_NwManagement_Can)
        {C_RBEMM_WakeupByBus_N, RBWAU_Client_Can3Trcv},                         /* identifier to configure wake-up support and RBWau client (refer to schematic) */
    #else
        {C_RBEMM_NoWakeupByBus_N, EMM_RBWAU_No_CLIENT},                         /* identifier to configure wake-up support and RBWau client (refer to schematic) */
    #endif
        {C_RBEMM_TrcvTypeExtCAN_TJA1043_N, CANTRCV_CANTRCVCHANNEL_1},        /* refer to CanTrcv_Cfg.h */
        {ComMConf_ComMChannel_ComMChannel_Can2, ComMConf_ComMUser_ComMUser_Can2}, /* refer to ComM_Cfg.h */
        {FALSE, EMM_CFG_NO_NM},                                                 /* no NM */
        EMM_CFG_NO_REQUESTER,                                                   /* NM needs SMM Requester, refer to RBSMM_Requester_Cfg.h */
    #if (RBFS_EMM == RBFS_EMM_Basic)
        &Prj_EnableApplPDUsNetworkChannel_3,
        &Prj_DisableApplPDUsNetworkChannel_3
    #endif
#endif
        }
            /* !!! End !!! */
    };

#endif // #if ((RBFS_EMM == RBFS_EMM_Basic)  || (RBFS_EMM == RBFS_EMM_Extended))

/******************************************************************************/
/*** End / End / End / End / End / End / End / End / End / End / End / End / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/

/**********************************************************************************/
// latest line: EOF
