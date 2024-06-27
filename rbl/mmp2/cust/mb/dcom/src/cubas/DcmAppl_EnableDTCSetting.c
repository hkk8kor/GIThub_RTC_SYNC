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
#include "DcmDspUds_Cdtcs_Inf.h"
#include "Rte_Dcm.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_EnableDTCSetting :-\n
 * This api will be invoked after calling "Dem_EnableDTCSetting".The return value from "Dem_EnableDTCSetting"
 * is passed to  DcmAppl_EnableDTCSetting as DtcEnableStatus.Based on the status ,Customer specific operations
 * can be performed.
 * @param[in]     DtcEnableStatus: Value to indicate whether DTC enabling is successful or not.
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_EnableDTCSetting( Std_ReturnType DtcEnableStatus )
{
    /* add your implementation here*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */

