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
#include "Rte_Dcm.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 *  @ingroup DCM_TPL
 *  DcmAppl_Switch_DcmExecuteReset :-\n
 *  This API is invoked to notify the application that Dcm shall trigger Ecu Reset soon after this API is called.The application may
 *  do the necessary actions required before reset in this function.The API is called only if RTE is disabled.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        None
 *
 */
void DcmAppl_Switch_DcmExecuteReset(void)
{
    /* add your implementation here*/
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"


