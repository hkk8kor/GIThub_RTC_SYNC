#ifndef RBEMM_PROJECT_H__
#define RBEMM_PROJECT_H__

/**********************************************************************************/
/* [COPYRIGHT]                                                                    */
/* Robert Bosch GmbH reserves all rights even in the event of industrial          */
/* property rights. We reserve all rights of disposal such as copying and         */
/* passing on to third parties.                                                   */
/* [COPYRIGHT_END]                                                                */
/**********************************************************************************/

#include "RB_Config.h"
#include "RBEMM_Types.h"

/******************************************************************************/
/*** Start / Start / Start / Start / Start / Start / Start / Start / Start / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/

/**********************************************************************************/
// 1. EMM-SchM-Protection
#if (RBFS_EMMSupportPreEmptiveTaskOrMultiCore == RBFS_EMMSupportPreEmptiveTaskOrMultiCore_On)

#define RBEMM_SchM_AtomicEnter_Project()         AddValidEnterProtection_Or_Define_Empty
#define RBEMM_SchM_AtomicExit_Project()          AddValidExitProtection_Or_Define_Empty

#define RBEMM_SchM_ComplexExterProject()         AddValidEnterProtection_ItIsNotAllowedToSetThisDefine_Empty
#define RBEMM_SchM_ComplexExit_Project()         AddValidExitProtection_ItIsNotAllowedToSetThisDefine_Empty

#endif

/******************************************************************************/
/*** End / End / End / End / End / End / End / End / End / End / End / End / **/
/*** Customer Part /  Customer Part /  Customer Part /  Customer Part /  ******/
/******************************************************************************/
#if (RBFS_EMM == RBFS_EMM_Basic)

extern const RBEMM_PrjNetwork_ParamType g_RBEMM_Prj_NetworkChnlPara_ast[RBEMM_PROJECT_NETWORK_MAXCHANNELS];

#elif (RBFS_EMM == RBFS_EMM_Extended)

extern const RBEMM_ExtPrjNetwork_ParamType g_RBEMM_Prj_NetworkChnlPara_ast[RBEMM_PROJECT_NETWORK_MAXCHANNELS];
extern const RBEMM_ExtPrjBaseOSParamType   g_RBEMM_Extended_PrjTableBaseOS_ast[RBEMM_Project_ExtendedBaseOSMaxChannels];

#endif // (RBFS_EMM == RBFS_EMM_Basic) or (RBFS_EMM == RBFS_EMM_Extended)
#endif /* INCLUDE PROTECTION: RBEMM_PROJECT_H__ */
