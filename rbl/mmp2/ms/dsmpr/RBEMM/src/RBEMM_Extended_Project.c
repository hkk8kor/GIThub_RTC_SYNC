/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, Robert Bosch GmbH, 2023. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/


/**********************************************************************************/
/* MANDATORY_INTERFACES:               */
#include "Std_Types.h"
#include "RBEMM_Config.h"
#include "CanTrcv_Cfg.h"
#include "RBEMM_Types.h"
/* MANDATORY_INTERFACES_END:           */
/**********************************************************************************/
/* USED_INTERFACES:                    */
#include "RBEMM_Project.h"
/* USED_INTERFACES_END:                */
/**********************************************************************************/

#if (RBFS_EMM == RBFS_EMM_Extended)

/**********************************************************************************/
// CAN Project w/ Wake-up is configured
/**********************************************************************************/
/* EMM Extended: Definition of main configuration structure */
const RBEMM_ExtPrjNetwork_ParamType g_RBEMM_Prj_NetworkChnlPara_ast[RBEMM_PROJECT_NETWORK_MAXCHANNELS] = {
    {C_RBEMM_BUSTYPE_CAN_01_N,
#if(RBFS_MMP2 == RBFS_MMP2_IMUD)
     RBWAU_Client_Can2Trcv,
     {C_RBEMM_TrcvTypeExtCAN_TJA1043_N, CANTRCV_CanTrcvChannel_0},
     {TRUE, NmConf_NmChannelConfig_NmChannelConfig_Can},
     SMM_Requester_IDEMM_NM_AMGCAN
#else
     EMM_RBWAU_No_CLIENT,
     {C_RBEMM_TrcvTypeExtCAN_TJA104x_EE_N, EMM_Trcv_DummyClientTJA104x_ElcEbd},
     {TRUE, NmConf_NmChannelConfig_NmChannelConfig_Can},
     SMM_Requester_IDEMM_NM_MBIntCAN
#endif
    }

#if(RBFS_DualCanSupport == RBFS_DualCanSupport_Yes)
,
    {C_RBEMM_BUSTYPE_CAN_02_N,
        RBWAU_Client_Can2Trcv,
        #if((RBFS_MMP2 == RBFS_MMP2_IMUB) && ((RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xTargetBoard) || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xDevBoard)) )
            {C_RBEMM_TrcvTypeExtCAN_TJA1043_N, CANTRCV_CanTrcvChannel_0},
        #else
            {C_RBEMM_TrcvTypeExtCAN_TJA1145_ATA6572_N, CANTRCV_CanTrcvChannel_0},
        #endif
        {TRUE, NmConf_NmChannelConfig_NmChannelConfig_Can1},
        SMM_Requester_IDEMM_NM_MBExtCAN
    }
#endif

#if (RBFS_ThirdCanSupport == RBFS_ThirdCanSupport_Yes)
,
    {C_RBEMM_BUSTYPE_CAN_03_N,
         RBWAU_Client_Can3Trcv,
        {C_RBEMM_TrcvTypeExtCAN_TJA1043_N, CANTRCV_CanTrcvChannel_1},
        {TRUE, NmConf_NmChannelConfig_NmChannelConfig_Can2},
        SMM_Requester_IDEMM_NM_AMGCAN
    }
#endif

};

/* EMM Extended: Definition of BaseOs related configuration structure */
const RBEMM_ExtPrjBaseOSParamType g_RBEMM_Extended_PrjTableBaseOS_ast[RBEMM_Project_ExtendedBaseOSMaxChannels] =
{
   {
#if (RBFS_MMP2 == RBFS_MMP2_IMUD)
     ComMConf_ComMChannel_ComMChannel_Can,
     ComMConf_ComMUser_ComMUser_Can
#else
     ComMConf_ComMChannel_ComMChannel_Can1,
     ComMConf_ComMUser_ComMUser_Can1
#endif
   }
};

/***********************************************************************************************************************
End Of Parameters
***********************************************************************************************************************/
 // (RBFS_BUILDCONFIG Checks)
#endif // (RBFS_EMM == RBFS_EMM_Extended)

/**********************************************************************************/
// latest line: EOF
