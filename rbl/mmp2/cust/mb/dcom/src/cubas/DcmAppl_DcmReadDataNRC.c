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


#if ( (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmReadDataNRC :-\n
 * If ReadData function has returned E_NOT_OK, Invoke the DcmAppl_DcmReadDataNRC to obtain the NRC from the application.
 *
 * @param[in]     Did : DID for which readdata has returned E_NOT_OK
 * @param[in]     DidSignalPosn : Signalposition within the DID whose readdata function has returned E_NOT_OK
 * @param[out]    ErrorCode     : NRC to be set by the application
 * @retval        E_OK      : The application has set the NRC successfully\n
 * @retval        E_NOT_OK  : The application has not set the NRC successfully\n
 *
 *
 */
Std_ReturnType DcmAppl_DcmReadDataNRC(uint16 Did, uint32 DidSignalPosn, Dcm_NegativeResponseCodeType * ErrorCode)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
#endif

