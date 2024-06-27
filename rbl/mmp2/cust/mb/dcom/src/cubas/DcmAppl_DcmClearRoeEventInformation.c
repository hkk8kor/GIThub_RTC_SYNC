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
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"

#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
     (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
     (DCM_ROE_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmClearRoeEventInformation:-\n
 * This API is used to reset the ROE scheduler,then clear the ROE transmission queue.
 * @param[in]   None
 * @param[out]  None
 * @retval None
 */
void DcmAppl_DcmClearRoeEventInformation (void)
{
    /* add your implementation here*/

    /*example code*/
    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    /* If reset the ROE scheduler is not required then user has to comment the below code */
    /* CLear the ROE transmission queue */
    //Dcm_DslDsd_ResetROEScheduler();
    #endif
    /*end example code*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF)
         && (DCM_ROE_ENABLED != DCM_CFG_OFF)*/
