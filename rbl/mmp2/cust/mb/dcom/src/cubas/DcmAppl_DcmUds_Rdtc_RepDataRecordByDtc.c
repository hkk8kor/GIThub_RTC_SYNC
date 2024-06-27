/**********************************************************************************************************************
*
* COPYRIGHT RESERVED, 2022 Robert Bosch GmbH. All rights reserved.
* The reproduction, distribution and utilization of this document as well as the communication of its contents to
* others without explicit authorization is prohibited. Offenders will be held liable for the payment of damages.
* All rights reserved in the event of the grant of a patent, utility model or design.
*
**********************************************************************************************************************/

#include "Dcm.h"

/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmUds_Rdtc_RepDataRecordByDTC :-\n     (This call can be used only by CEVT and MRA2 projects)
 * This callback function helps in modify response.
 *
 * @param[in]    s_dataRDTCSubFunc_u8        : DID for which readdata has returned E_NOT_OKFor subfunction of RDTC.
 * @param[in]    Dsp_RdtcDTC_u32             : DTC value.
 * @param[in]    Dcm_DspRDTCRecordNum_u8     : Number of DTC
 * @param[out]   Dcm_DspMaxResDataLen_u16    : Maximum response length this variable need to be 0 in application implimentation.
 * @param[out]   dataFillRespLen_u32         : response length
 * @param[out]   pMsgContext                 : Pointer to message structure
 * @param[out]   Dcm_DspNegResCode_u8        : NRC update
 *
 *
 */
void DcmAppl_DcmUds_Rdtc_RepDataRecordByDTC(uint8 s_dataRDTCSubFunc_u8,uint32 Dsp_RdtcDTC_u32,uint8 Dcm_DspRDTCRecordNum_u8,uint16 * Dcm_DspMaxResDataLen_u16,uint32 dataFillRespLen_u32,Dcm_MsgContextType * pMsgContext,Dcm_NegativeResponseCodeType * Dcm_DspNegResCode_u8)
{

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

