/// @file rbl_dcom_Lib.h
/// @brief This header provides definitions for Dcom Library Files api, functions may be used by other components
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_LIB_H__
#define RBL_DCOM_LIB_H__

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

#include "rbl_dcom_Common.h"
#include "NvM.h"
#include "rbl_CustIf_VehSpd_Disp_ST3.h"

/*
**********************************************************************************************************************
* Enumeration definitions
**********************************************************************************************************************
*/
extern uint8 DCOM_SupplierPubKey_Sig_RAM_Mirror[258];// RAM mirror for SupplierPublicKey and Signature
extern uint8 rbl_dcom_DCOM_MB_HW_PartNumber[10]; //RAM mirror Sensor serial number
extern uint8 rbl_SnsrSerlNr_RAM_Mirror[16]; //RAM mirror HW part number
extern uint8 rbl_ECU_SerialNr_RAM_Mirror[17];// RAM mirror ECU serial number

///Defination for Dcom Library files

typedef enum
{
    dcom_NvMGetErrorStatus_AfterReadOrWriteRequest, ///<To Read or Write Request after NVM gets Error Status
    dcom_Done_ReadOrWriteNVMBlock, ///<To Read or Write Request from NVM block is done
    dcom_Error_ReadOrWriteNVMBlock, ///<To Read or Write Request from NVM block got Error
    dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest ///<To Read or Write Request Before NVM gets Error Status
}dcom_NvMReadWriteType_tst;

/*
**********************************************************************************************************************
* Function Protoypes
**********************************************************************************************************************
*/

/// @c_file dcom_Lib.c
/// @brief The function is used to copy the data from EEPROM into the specfied RAM Buffer
/// @pre Appropriate data should be filled in all NvM blocks before read operation
/// @param[in] Block_Id The NvM Block Id from where the data has to be read from
/// @param[in,out] Data The RAM Buffer to which the data is copied to
/// @param[in] NvM_Length The length of the NvM block would be accessed
/// @param[in] Fill_NvM The default values to be filled into RAM buffer if specified NvM Block is empty
/// @return Std_ReturnType The status of the read of NvM block
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @retval DCM_E_PENDING if Operation Pending
/// @details NvM_GetErrorStatus data is filled with BlockId and RequestResultPtr
/// @startuml
/// !include dcom_Lib_dcom_Lib_ReadNvMData.puml
/// @enduml
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id, uint8* Data, uint8 NvM_Length,uint8 Fill_NvM);


/// @c_file dcom_Lib.c
/// @brief The function is used to copy the data from EEPROM into the specfied RAM Buffer ,
/// Copy data from input Data buffer into specific NvM block
/// @pre Writing of appropriate data corresponding NvM block should be ensured
/// @param[in] Dcm_NegativeResponseCodeType   Negative Response code would be passed in for failing conditions
/// @param[in] Block_Id The NvM Block Id to which the data has to be written to
/// @param[in] Data The RAM Buffer from which the data is copied
/// @param[in] ErrorCode  Pointer to the Negative Response Code (NRC)
/// @return Data, The RAM Buffer from which the data is copied
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @retval DCM_E_PENDING if Operation Pending
/// @details NvM_GetErrorStatus data is filled with BlockId and RequestResultPtr
/// @note Complete Design for Function dcom_Lib_WriteNvMData is divide into four diffrent state machine as below
/// @note Below is the design for first state dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest
/// @startuml
/// !include dcom_Lib_dcom_Lib_WriteNvMData_State_dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest.puml
/// @enduml
/// @note Below is the design for Second state dcom_NvMGetErrorStatus_AfterReadOrWriteRequest
/// @startuml
/// !include dcom_Lib_dcom_Lib_WriteNvMData_State_dcom_NvMGetErrorStatus_AfterReadOrWriteRequest.puml
/// @enduml
/// @note Below is the design for Third state dcom_Error_ReadOrWriteNVMBlock
/// @startuml
/// !include dcom_Lib_dcom_Lib_WriteNvMData_state_dcom_Error_ReadOrWriteNVMBlock.puml
/// @enduml
/// @note Below is the design for Fourth state dcom_Done_ReadOrWriteNVMBlock
/// @startuml
/// !include dcom_Lib_dcom_Lib_WriteNvMData_state_dcom_Done_ReadOrWriteNVMBlock.puml
/// @enduml
Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id, const uint8* Data,
        Dcm_NegativeResponseCodeType * ErrorCode);



/// @c_file dcom_Lib.c
/// @brief The function provides the information whether the speed limit is exceeding
/// @pre Vehicle speed signal has to be read and received
/// @param[in] l_Value Speed limit for the use case
/// @return boolean expression whether it is True/False
/// @retval TRUE  = vehicle speed is >= given threshold
/// @retval FALSE = vehicle speed is < give threshold or no valid vehilce speed available
/// @startuml
/// !include dcom_Lib_dcom_isSpeedLimitExceeded.puml
/// @enduml
boolean dcom_isSpeedLimitExceeded (uint16 l_Value);


/// @c_file dcom_Lib.c
/// @brief The function basically provides the ASCII value of the Nibble passed
/// @pre Function to be called with nibble data
/// @param[in] t_Nibble_UB  Data that needs to be passed as an ASCII
/// @return uint8 ASCII value of the respective data sent
/// @startuml
/// !include dcom_Lib_dcom_Lib_HexNibble2ASCII.puml
/// @enduml
uint8 dcom_Lib_HexNibble2ASCII (uint8 t_Nibble_UB);


#endif /* RBL_DCOM_LIB_H__ */



