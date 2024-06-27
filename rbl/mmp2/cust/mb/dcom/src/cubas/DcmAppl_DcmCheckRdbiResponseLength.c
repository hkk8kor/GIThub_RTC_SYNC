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
#include "DcmDspUds_Rdbi_Inf.h"
#include "Rte_Dcm.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmCheckRdbiResponseLength :-\n
 *  This application function shall be called if there is at-least one valid DID in the multi DID RDBI request to validate the total response length.\n
 *  This function shall be called before reading the Data for the requested DIDs.\n
 *  If the *ErrorCode is updated to be a non zero value, then the same shall be sent from Dcm as the response irrespective of the return value.\n
 *  In case the project does not want to do the length validation, then E_OK should be returned.
 *
 *  @param[in]       dataTotalRespLength_u32  : The total response length in bytes of all DIDs to be read in the current request\n
 *  @param[in]       dataNumOfDids_u16        : The number of valid DIDs in the multi DID request
 *  @param[out]      ErrorCode                : The negative response code to be updated by the application after validating dataTotalRespLength_u32\n
 *
 *  @retval          E_OK - If the project has validated the length successfully\n
 *  @retval          E_NOT_OK - If the length validation is not successful.\n
 *                  (In this case, Dcm shall send NRC0x22 (Conditions Not Correct) if *ErrorCode is not updated)\n
 *
 */
Std_ReturnType DcmAppl_DcmCheckRdbiResponseLength(
                                                    uint32 dataTotalRespLength_u32,
                                                    uint16 dataNumOfDids_u16,
                                                    Dcm_NegativeResponseCodeType * ErrorCode
                                                )
{
    /* add your implementation here*/
    return E_OK;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif /* (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) */
