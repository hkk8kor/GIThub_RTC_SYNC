/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmAppl.h"

#if((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserRIDModeRuleService :-\n
 * Function to do specific checks on the RID in  the routine control requests before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]     rid_u16 : RID under processing
 * @param[in]     Subfunc_u8 : Subfunction of the service under process
 * @param[out]    Nrc_u8 : NRC to be set by the application
 * @retval               E_OK   : RID specific checks passed successfully \n
 * @retval               E_NOT_OK  : RID specific checks failed\n
 *
 */
Std_ReturnType DcmAppl_UserRIDModeRuleService(Dcm_NegativeResponseCodeType * Nrc_u8, uint16 rid_u16, uint8 subfunction_u8)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif

