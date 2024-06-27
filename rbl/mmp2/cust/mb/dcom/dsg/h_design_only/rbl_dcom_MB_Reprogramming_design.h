/// @file rbl_dcom_MB_Reprogramming_design.h
/// @brief This header provides definitions for Reprogramming module.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef DCOM_MB_REPROGRAMMING_DESIGN_H
#define DCOM_MB_REPROGRAMMING_DESIGN_H



/// @c_file rbl_dcom_MB_Reprogramming.c
/// @brief This API should  set the Programming conditions based on the bootloader reset reason stored in Non volatile memory
///  (0xFEBF_FC08) during Jump To Application.
/// @pre Function is only active if RBFS_DcomReprogResponseType is configured to RBFS_DcomReprogResponseType_Warm and
///      DCM_CFG_RESTORING_ENABLED is configured to DCM_CFG_ON
/// @param[in] ProgConditions : Pointer to the location where the programming conditions are stored
/// @return Dcm_EcuStartModeType : This will specify the Ecu Start mode
/// @retVal DCM_WARM_START   The ECU starts from a bootloader jump\n
///         DCM_COLD_START   Start ECU Normally
/// @startuml
/// !include rbl_dcom_Reprog_dcm_get_prog.puml
/// @enduml
/// @details In this API user has to restore the protocol information required to start Dcm.\n
///  Below are the reset reason values to be checked :\n
///  1) @ref DCOM_DEFAULTSESSION - Shall fill the response with positive response to $10 01 on EXT Tester\n
///  2) @ref DCOM_HARDRESET - Shall fill the response with positive response to $11 01 on EXT Tester\n
///  3) @ref DCOM_DEFAULTSESSION_2NDTESTER - Shall fill the response with positive response to $10 01 on EXT Tester\n
///  4) @ref DCOM_HARDRESET_2NDTESTER - Shall fill the response with positive response to $11 01 on EXT Tester\n
///  The following information needs to be filled by the user in ProgConditions\n
///  1. ProtocolID - protocol which needs to be started as default (DCM_SUPPLIER_1/DCM_SUPPLIER_2).\n
///  2. Tester Source address - Connection will be derived from this input(0xEF8/0xF0D).\n
///  3. SID - service identifier (In case of Warm request/Warm response)\n
///  4. SubFncId - Subfunction ID\n
///  5. StoreType - Storage Type used for restoring, Warm Request/Warm Response/Warm Init\n
///  6. SessionLevel - Session level which needs to be started\n
///  7. ReqResLen - Total request/response length including SID and Subfunc\n
///  8. Request/Response bytes which follows the SID and Subfunc\n
///  9. ReprogramingRequest - Reprograming of ecu requested or not\n
///  10. ApplUpdated - Application has to be updated or not



Dcm_EcuStartModeType Dcm_GetProgConditions (Dcm_ProgConditionsType * ProgConditions);


/// @c_file rbl_dcom_MB_Reprogramming.c
/// @brief This API is used to retrieve the Type of Storage required by User.
/// @pre Function is only active if RBFS_DcomReprogResponseType is configured to RBFS_DcomReprogResponseType_Warm and
///      DCM_CFG_STORING_ENABLED is configured to DCM_CFG_ON
/// @param[in] dataBootType_u8 : boot type used for jump
/// @param[in] SID :Service identifier
/// @return uint8 : Storage Type required by the user for Jump to Boot
/// @retVal DCM_WARMRESPONSE_TYPE :  Warm Response Type\n
/// @details Parameters passed to function are not used and are typecasted to void.

uint8 DcmAppl_DcmGetStoreType(uint8 dataBootType_u8, uint8 SID);


/// @c_file rbl_dcom_MB_Reprogramming.c
/// @brief This API is invoked to inform the application to execute reset where the reset is triggered due to DSC service
///        when used for jump to boot
/// @pre Function is only active if RBFS_DcomReprogResponseType is configured to RBFS_DcomReprogResponseType_Warm and
///      DCM_CFG_STORING_ENABLED is configured to DCM_CFG_ON
/// @param[in] SessionLevel_u8 : Session level used for jump
/// @return void
/// @details Reset is invoked through function call @ref RB_performSWResetWithBootBlock4OEM\n
///          Parameters passed to function are not used and are typecasted to void.

void DcmAppl_Switch_DcmExecuteDscReset(uint8 SessionLevel_u8);


/// @c_file rbl_dcom_MB_Reprogramming.c
/// @brief This API should set botloader start request for the Application to Bootloader jump.
/// @pre Function is only active if RBFS_DcomReprogResponseType is configured to RBFS_DcomReprogResponseType_Warm and
///      DCM_CFG_STORING_ENABLED is configured to DCM_CFG_ON
/// @param[in]    OpStatus  :  operation status
/// @param[in]    ProgConditions :  Pointer to the location where the programming conditions are stored
/// @return Std_ReturnType :status of storing the programming conditions\n
/// @retVal E_OK :Storing is sucessful
/// @startuml
/// !include rbl_dcom_Reprog_dcm_set_prog.puml
/// @enduml
/// @details API shall set the following informations:
///     Reprogramming request inverted(at address 0xFEBF_FC04) to @ref DCOM_REQPROGREQUESTINVERTED\n
///     If the requested tester is external tester ,Reset reason (at address 0xFEBF_FC08) to  @ref DCOM_PROGRAMMINGSESSION.\n
///     If the requested tester is internal tester ,Reset reason (at address 0xFEBF_FC08) to  @ref DCOM_PROGRAMMINGSESSION_2NDTESTER.

Std_ReturnType Dcm_SetProgConditions(Dcm_OpStatusType OpStatus, const Dcm_ProgConditionsType * ProgConditions);
