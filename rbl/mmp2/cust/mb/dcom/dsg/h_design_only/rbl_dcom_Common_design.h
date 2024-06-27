/// @file rbl_dcom_Common_design.h
/// @brief The file consists of the API's design for Communication Control, Dcm Notif, Diagnostic Session Control
/// Ecu Reset and Plant Mode Activation files.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef DCOM_COMMON_DESIGN_H
#define DCOM_COMMON_DESIGN_H



/// @c_file rbl_dcom_CommunicationControl.c
/// @brief This API will be called after the request length check for the UDS service Communication
/// control(0x28)request. Dcm will pass the information from the request to this API.
/// Application can perform the condition checks and required actions if any.
/// @pre When communication is requested to be enabled during system degraded,
/// the function will return NRC 0x22 to indicate Conditions Not Correct.
/// The check if System state is not equal to normal and Commnication type is enabled should be checked
/// along with whether the valid communication type is requested needs to be checked.
/// @param[in] ControlType_u8
/// @param[in] DataCommType_u8
/// @param[in] RequestData
/// @param[in] RequestLength
/// @param[in,out] Dcm_NegativeResponseCodeType*dataNegRespCode_u8
/// @return Std_ReturnType Length of the request message sent
/// @retval E_OK : DataCommType_u8 is supported
/// @retval E_NOT_OK : DataCommType_u8 is not supported.
/// @startuml
/// !include rbl_dcom_CommunicationControl_DcmAppl_DcmCommControlConditionCheck.puml
/// @enduml
extern Std_ReturnType DcmAppl_DcmCommControlConditionCheck(uint8 ControlType_u8, uint8 DataCommType_u8,
const uint8* RequestData, uint16 RequestLength, Dcm_NegativeResponseCodeType*dataNegRespCode_u8);



/// @c_file rbl_dcom_CommunicationControl.c
/// @brief This API will be called after sending the confirmation for the UDS service Communication control(0x28)
/// Dcm will pass the network ID of the channel and the new requested Communication mode to this API.
/// Application can perform required actions if any.
/// @pre The check for Requested Mode of DCM whether it enables or disables RX TX shall be checked in different modes.
/// @param[in] NetworkID
/// @param[in] RequestedMode
/// @return void
/// @details
/// Function act as a call back service, NetworkID and RequestedMode passed to this API
extern void DcmAppl_DcmSwitchCommunicationControl(uint8 NetworkID,Dcm_CommunicationModeType RequestedMode);



/// @c_file rbl_dcom_CommunicationControl.c
/// @brief This api is called to check whether the ComM channel identified by the passed Network ID
/// is in default ComMode.
/// @pre The check if RBFS_EcuNodeDegradationType is in Stop Transmission State along with if
/// rbl custif system state normal is not equal to rbl ImuCustIf Get System State should be verified.
/// @param[in] NetworkID
/// @return boolean
/// @retval TRUE : ComMode is default
/// @retval FALSE : ComMode is not default
/// @details Update return value to TRUE and call NetworkID argument.
extern boolean DcmAppl_DcmIsComModeDefault(uint8 NetworkID);



/// @c_file rbl_dcom_DcmNotif.c
/// @brief This API indicates the successful reception of a new request to application and it is called
/// right before processing the diagnostic service XXX_Dcm<DiagnosticService>.
/// Within this function application can examine the permission of the diagnostic service
/// environment (e.g. ECU state after run).
/// Return of application will lead to an acceptance of diagnostic request,reject of diagnostic request
/// (-> no response will be send) or to an NRC 0x22 (ConditionsNotCorrect).
/// @pre This functionality is available only when Supplier Notification feature is enabled.
/// @param[in] SID : Value of service identifier
/// @param[in] RequestData : Pointer to the request data buffer
/// @param[in] RequestLength : Request data length
/// @param[in] RequestType : It says whether the request is FUNCTIONAL/PHYSICAL
/// @param[in] DcmRxPduId :  RxPduId on which the request is received
/// @param[in] SourceAddress : This variable gives the Tester source address
/// @param[in,out] Dcm_NegativeResponseCodeType*ErrorCode : Pointer to the variable to update the error code
/// @return Std_ReturnType Reception of the new message request
/// @retval E_OK : Operation sucessful
/// @retval E_NOT_OK : Operation unsucessful
/// @details ErrorCode is set to DCOM_NO_ERROR
extern Std_ReturnType DcmAppl_DcmNotification(uint8 SID, const uint8* const RequestData, PduLengthType RequestLength,
uint8 RequestType, PduIdType DcmRxPduId, uint16 SourceAddress, Dcm_NegativeResponseCodeType*ErrorCode);



/// @c_file rbl_dcom_DcmNotif.c
/// @brief This function indicates that successful reception of a new request to manufacturer application
/// and it is called right before before the DSD verification (SID, security access,diagnostic session).
/// Within this function application can examine the permission of the diagnostic service /
/// environment (e.g. ECU state afterrun).
/// @pre This functionality is available only when Manufacturer Notification feature is enabled and allocates
/// the tester relavant source address (first or second tester address) based on whether second tester is supported.
/// The check if RBFS Dcom Second Tester Support is not OFF should be performed and if
/// dcom first tester is equal SourceAddress then the requested tester would be DCOM_FIRST_TESTER else
/// it would be DCOM_SECOND_TESTER.
/// @param[in] SID : Value of service identifier
/// @param[in] RequestData : Pointer to the request data buffer
/// @param[in] RequestLength : Request data length
/// @param[in] RequestType : It says whether the request is FUNCTIONAL/PHYSICAL
/// @param[in] DcmRxPduId : RxPduId on which the request is received
/// @param[in] SourceAddress : This variable gives the source address
/// @param[in,out] Dcm_MsgContextType*adrMsgContext_pcst : Pointer to variable to update the Address message context
/// @param[in,out] Dcm_NegativeResponseCodeType*ErrorCode : Pointer to variable to update the error code
/// @return Std_ReturnType Reception of the new message request to manufacturer application
/// @retval E_OK : Operation sucessful
/// @retval E_NOT_OK : Operation unsucessful
/// @startuml
/// !include rbl_dcom_DcmNotif_DcmAppl_ManufacturerNotification.puml
/// @enduml
extern Std_ReturnType DcmAppl_ManufacturerNotification(uint8 SID, const uint8* const RequestData, PduLengthType RequestLength,
uint8 RequestType, PduIdType DcmRxPduId, uint16 SourceAddress, Dcm_MsgContextType*adrMsgContext_pcst,
Dcm_NegativeResponseCodeType*ErrorCode);



/// @c_file rbl_dcom_DiagnosticSessionControl.c
/// @brief Indication to application, that the active session is changed (but keep
/// in mind that a change into the same session as active before is also
/// possible !)
/// This change was either initiated by DiagnosticSessionControl command
/// S3Server timeout or exceeding of the speed limit.
/// The diagnostic application needs to provide this function as a callback
/// function to Dcm.
/// @pre The generic sessions supported across all variants is default, programming and extended.
/// In addition, customer specific sessions may be supported if required.
/// The check if RBFS_DcomReprogResponseType is not equal to warm along with if RBFS_DcomSupplierSession
/// is not disabled should be verified.
/// @param[in] SesCtrlTypeOld : Former active session control type value
/// @param[in] SesCtrlTypeNew : Newly set session control type value
/// @return void
/// @startuml
/// !include rbl_dcom_DiagnosticSessionControl_DcmAppl_DcmSesCtrlChangeIndication.puml
/// @enduml
extern void DcmAppl_DcmSesCtrlChangeIndication (Dcm_SesCtrlType SesCtrlTypeOld, Dcm_SesCtrlType SesCtrlTypeNew);




/// @c_file rbl_dcom_DiagnosticSessionControl.c
/// @brief Request from Dcm to diagnostic application, to check if the conditions
/// allow to start requested session control.
/// This function is only required if the Dcm implementation of the
/// DiagnosticSessionControl service is used.
/// @pre   The generic sessions supported across all variants is default, programming and extended.
/// In addition, customer specific sessions may be supported if required.
/// When bootloader is enabled, permission to transition to Boot is permitted after certain checks.
/// The check if RBFS_CheckProgPreConditio is ON along with if RBFS_DcomSupplierSession
/// is not disabled should be verified.
/// @param[in] SesCtrlTypeActive : Former active session control type value
/// @param[in] SesCtrlTypeNew : Newly set session control type value
/// @param[in,out] Dcm_NegativeResponseCodeType*ErrorCode : Pointer to the variable to update the error code
/// @return Std_ReturnType E_OK or E_NOT_OK
/// @retval E_OK : session can be started
/// @retval E_NOT_OK : Session cannot be started
/// @retval	DCM_E_SESSION_NOT_ALLOWED : session is not allowed to start
/// @retval	DCM_E_PENDING : Some more time required to change the requested session
/// @startuml
/// !include rbl_dcom_DiagnosticSessionControl_DcmAppl_DcmGetSesChgPermission.puml
/// @enduml
extern Std_ReturnType DcmAppl_DcmGetSesChgPermission (Dcm_SesCtrlType SesCtrlTypeActive, Dcm_SesCtrlType SesCtrlTypeNew,
Dcm_NegativeResponseCodeType*ErrorCode);



/// @c_file rbl_dcom_EcuReset.c
/// @brief This api is called after Dcm gets the Tx Confirmation of the response sent to trigger the Ecu Reset.
/// Application should take further actions to trigger reset.
/// @pre The check if rba_DcmPma_PlantModeStatus_b is not true and ResetType_u8 is equal to DCOM_HARD_RESET
/// or DCOM_SOFT_RESET shall be verified.
/// @param[in] ResetType : information about the requested reset type
/// @return void
/// @startuml
/// !include rbl_dcom_EcuReset_DcmAppl_Switch_DcmExecuteEcuReset.puml
/// @enduml
extern void DcmAppl_Switch_DcmExecuteEcuReset(uint8 ResetType_u8);



/// @c_file rbl_dcom_EcuReset.c
/// @brief This function prepares for reset.Integrator should add the code for the actions to be
/// performed before Ecu Reset.
/// @pre The check ResetType is equal DCOM_SOFT_RESET should be verified.
/// @param[in] ResetType : information about the requested reset type
/// @param[in,out] Dcm_NegativeResponseCodeType*ErrorCode : information about the error caused
/// @return Std_ReturnType ECU Reset successful
/// @retval E_OK : Reset Preparation Condition OK.
/// @retval E_NOT_OK : Reset Preparation Condition NOT OK.
/// @startuml
/// !include rbl_dcom_EcuReset_DcmAppl_DcmEcuResetPreparation.puml
/// @enduml
extern Std_ReturnType DcmAppl_DcmEcuResetPreparation(uint8 ResetType, Dcm_NegativeResponseCodeType*ErrorCode);


/// @c_file rbl_dcom_EcuReset.c
/// @brief This API is to check for soft reset readiness and perform soft reset
/// @pre The check for dcom_SoftResetstatus is equal to E_OK else if DCM_E_PENDING should be checked.
/// @return Std_ReturnType Check for Soft Reset
/// @retval E_OK : Operation succesful
/// @retval E_NOT_OK : Operation unsuccesful
/// @retval DCM_E_PENDING : Operation pending
extern static Std_ReturnType dcom_SoftResetRdy_check(void);



/// @c_file rbl_dcom_PlantModeActivation.c
/// @brief  After the successful plant mode activation, application can send a positive response value for the
/// second request.This one byte response value should be returned from this API.
/// @pre Entry to plant mode is supported only when ECU is not already in Plant.
/// NRC 11 is expected if Plant Mode Activation service is requested while in Plant mode.
/// The check if BaseOs Active should be verfied.
/// @return uint8,DCM_APPL_CODE
/// @retval Returns one byte positive response for the service 0x80
extern uint8 rba_DcmPmaAppl_FillPlantModeResponse(void);



/// @c_file rbl_dcom_PlantModeActivation.c
/// @brief This API used to inform other SW components that DCM is in plant mode or exited plant mode
/// @pre Entry to plant mode is supported only when ECU is not already in Plant.
/// NRC 11 is expected if Plant Mode Activation service is requested while in Plant mode.
/// The check if Plant mode active should be verfied.
/// @param[in] boolean
/// @param[in] stActive_b indicated if PlantModeActivation is active/not active
/// @return VAR
/// @retval void
extern void rba_DcmPmaAppl_PlantModeActivation (boolean stActive_b);


/// @c_file rbl_dcom_DcmControlDtcSettingEnableStatus.c
/// @brief This API is called when the control dtc setting status is changed.
/// @pre None
/// @param[in]  ControlDtcSettingEnableStatus: Value to indicate whether DTC is enabled or not\n
/// @param[out] None
/// @retval None
/// @details rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus method needs to called when RBFS_ThirdPartySoftware is turned ON
extern void DcmAppl_DcmControlDtcSettingEnableStatus (boolean ControlDtcSettingEnableStatus);

#endif /*DCOM_COMMON_DESIGN_H */
