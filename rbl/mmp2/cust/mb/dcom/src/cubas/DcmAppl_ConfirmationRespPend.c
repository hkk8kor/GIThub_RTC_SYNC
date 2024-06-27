/**********************************************************************************************************************
 *
 * COPYRIGHT RESERVED, 2010 Robert Bosch GmbH. All rights reserved.
 * The reproduction, distribution and utilization of this document as well as the communication of its contents to
 * others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
 * All rights reserved in the event of the grant of a patent, utility model or design.
 *
 **********************************************************************************************************************/
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"

#include "Rte_Dcm.h"
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "rba_DiagAdapt.h"
#endif


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_ConfirmationRespPend :-\n
 *  This API confirms the successful transmission of waitpend response.
 *
 *  @param[in]       status :  A Status indication about confirmation\n
 *  @param[out]      None
 *  @retval          None
 *
 */
void DcmAppl_ConfirmationRespPend(Dcm_ConfirmationStatusType status)
{
    /* add your implementation here*/

    /* example code: call DiagAdapt, if this component is used*/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_ConfirmationRespPend(status);
#endif
    /* end example code*/
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
