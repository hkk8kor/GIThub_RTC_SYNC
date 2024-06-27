
/*
**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2020 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************
*/

/**********************************************************************************/
/* MANDATORY_INTERFACES:               */
#include "Std_Types.h"
#include "RBEMM_Config.h"
#include "RBEMM_Types.h"
#include "RBEMM_Extended_Callouts.h"
/* MANDATORY_INTERFACES_END:           */
#include "RBEMM_Project.h"

/**********************************************************************************/


#if (RBFS_EMM == RBFS_EMM_Extended)

#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    #include "CanNm.h"
#endif

/**********************************************************************************/
// CAN Project w/ Wake-up is configured
/**********************************************************************************/
void RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout(void)
{
    uint8 l_cnt;

	for(l_cnt=0;l_cnt<RBEMM_PROJECT_NETWORK_MAXCHANNELS;l_cnt++)
	{
		/* Set the SMM requesters to Net ON*/
		if(EMM_CFG_NO_REQUESTER != g_RBEMM_Prj_NetworkChnlPara_ast[l_cnt].SMM_NM_Requester_en)
		{
			RBSMM_RequestMode(&(RBAllSMM_Requester_st[g_RBEMM_Prj_NetworkChnlPara_ast[l_cnt].SMM_NM_Requester_en]), C_SMM_NET_ON_N);
#if(RBFS_MMP2 != RBFS_MMP2_IMUA)
			(void)CanNm_ConfirmPnAvailability(l_cnt);
#endif
		}
	}

}


void NM_RxIndication( const NetworkHandleType NetworkHandle)
{
    SystemMode_N l_CurrentSystemMode_N;

    l_CurrentSystemMode_N = RBSMM_CurrentSystemMode();

    if (NetworkHandle == NmConf_NmChannelConfig_NmChannelConfig_Can)
    {
        if(l_CurrentSystemMode_N >= C_SMM_NET_ON_N)
        {
        #if(RBFS_MMP2 != RBFS_MMP2_IMUD)          
            RBSMM_RequestMode(RBSMM_Requester_EMM_NM_MBIntCAN, C_SMM_NET_ON_N);
        #endif
        }
    }
}
/***********************************************************************************************************************
End Of Functions
***********************************************************************************************************************/
#endif // (RBFS_EMM == RBFS_EMM_Extended)

