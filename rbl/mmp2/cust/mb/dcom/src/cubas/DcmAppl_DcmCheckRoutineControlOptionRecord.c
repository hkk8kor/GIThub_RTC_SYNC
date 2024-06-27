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
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"
 /**
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmCheckRoutineControlOptionRecord:-\n
 *  This API is called by Dcm_Prv_DspRoutineControl(service handler for RC service) incase a received request contains a control option record. \n
 *  The application shall check the validity of the control option record in this function and it shall return E_OK if the record is valid.\n
 *  For an invalid record application shall return E_NOT_OK.
 *
 * @param[in]     nrRID_u16 : This is the routine identifier.
 * @param[in]     dataSubFunc_u8 :This parameter gives the requested subfunction value.(start/stop/RequestResults)
 * @param[in]     adrRoutineCtrlOptRec_pcst : This is a poniter to the control option record received.
 * @param[in]     dataRoutineCtrlOptRecSize_u16 : This parameter gives the length of the control option record.
 * @param[out]    None
 *
 * @retval        E_OK      : Indicates that the request can be accepted and processed\n
 * @retval        E_NOT_OK  : Indicates that the request shall be rejected with NRC 0x31\n
 *
 */
Std_ReturnType DcmAppl_DcmCheckRoutineControlOptionRecord(uint16 nrRID_u16,
                                           uint8 dataSubFunc_u8,const uint8 * adrRoutineCtrlOptRec_pcst,uint16 dataRoutineCtrlOptRecSize_u16)
{
    /* add your implementation here*/
    return E_OK;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_MemMap.h"

#endif
