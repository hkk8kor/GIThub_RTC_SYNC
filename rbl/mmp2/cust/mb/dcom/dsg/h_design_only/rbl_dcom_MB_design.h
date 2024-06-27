/// @file rbl_dcom_MB_design.h
/// @brief The file consists of the API's design for Read Data by Identifier DID's
/// and Write Data by Identifier DID's identified for Customer Diagnostics for MB.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_DESIGN.H
#define RBL_DCOM_MB_DESIGN.H


/***Extern declarations for XXX_ReadData of type USE_DATA_SYNCH_FNC ***/


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the VIN value of the server.
/// @pre \p Data of VINDataIdentifier should be written to the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Vehicle Identification Number of ECU shall be stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_VINDataIdentifier_F190_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Active Diagnostic Status Application, Active Diagnostic Variant,
/// Active Diagnostic Version and Active Session from ECU
/// @pre \p Data on Active Diagnostic Status Application, Active Diagnostic Variant, Active Diagnostic Version
/// macros must be defined and \p Data on Active session must be known.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding active diagnostic session is stored
/// @return Std_ReturnType  The status of read operation is returned and the data is filled in Data buffer.
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
extern Std_ReturnType dcom_ActiveDiagnosticSession_F100_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used for reading the DDS package from the ECU
/// @pre \p Data of DDS package release year and month for application and boot software must be defined.
/// The check for RBFS_OEMBootloader is enabled and data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding boot DDS package release information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_DDS_Package_Release_F10D_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_DDS_Package_Release_F10D_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used for reading the Diagnostic TraceMemory data from NvM
/// @pre \p Data of Diagnostic Trace Memory should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Diagnostic TraceMemory information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_Diagnostic_Trace_Memory_102_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Major version, Minor version,Patch Level, Identification Type,
/// XDIS Version, Export Date, Ecu Name, Check Sum of ECU extract version
/// @pre \p Data of Major version, Minor version,Patch Level, Identification Type,
/// XDIS Version, Export Date, Ecu Name, Check Sum of ECU extract version macros must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding ECU extract version is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_Ecu_Extract_Version_EF00_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_Ecu_Extract_Version_EF00_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read out the serial number of ECU which is unique for each ECU
/// @pre \p Data of ECU Serial Number should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding ECU serial number is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_ECUSerialNumber_F18C_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Hardware Supplier Identification of an ECU which
/// determines the manufacturer of an ECU's hardware
/// @pre \p Data of Hardware Supplier Identification must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding hardware Supplier information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
extern Std_ReturnType dcom_HardwareSupplier_F154_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Hardware Version Information of an ECU
/// (when the hardware was designed)
/// @pre \p Data of Hardware Version data should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding hardware version information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_HardwareVersion_F150_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Hardware Part Number of an ECU
/// @pre \p Data of Mercedes Car Group Hardware Part Number.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding hardware part number information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_MercedesCarGroupHardware_F111_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the software integrity, compatibility, logical block erase status and
/// reprogramming status. The DID uniquely identifies the last user and External Diagnostic Test Tool which
/// reprogrammed the ECU.
/// @pre \p Data of Read Software Fingerprint(s) should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Software fingerprint(s) information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the information regarding number of reprogramming attempts made by tester
/// and Maximum number of reprogramming attempts
/// @pre \p Data of Reprogramming Attempt Counter should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding number of reprogramming attempts is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_ReprogrammingAttemptCounter_0100_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Software Supplier Identification of a reprogrammable ECU for Bootloader Logical Block.
/// @pre \p Data of Bootloader Software Supplier Identification must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding software supplier information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer is filled with Bootloader Software Supplier Identification if OEM Bootldaer is avialble or fill with Default values.
extern Std_ReturnType dcom_SoftwareSupplier_Bootloader_F155_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Software Supplier Identification of a reprogrammable ECU for Application Logical Block.
/// @pre \p Data of Application Software Supplier Identification must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding software supplier information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer is filled with Application Software Supplier Identification.
extern Std_ReturnType dcom_SoftwareSupplier_Application_F155_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Major version, Minor version,Patch Level, Candela Version,
/// DDM Version, Exported Diagnostic Variant of Diagnostic extract version
/// @pre \p Data of Major version, Minor version,Patch Level, Identification Type, Candela Version,
/// DDM Version, Exported Diagnostic Variant of Diagnostic extract version macros must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Diagnostic extract version is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_Diagnostic_Extract_Version_EF01_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_Diagnostic_Extract_Version_EF01_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the ECU Name
/// @pre \p Data of ECU Name macros must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding ECU Name is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_ECU_Name_F104_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_ECU_Name_F104_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the software Part Numbers from the ECU for the Bootloader Data and Application Data.
/// @pre \p Data of Software Part Number macros must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding software part number is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details The first 10 bytes of data updated would be Bootloader data and next 10 Bytes of data updated would be Application Data.
extern Std_ReturnType dcom_MercedesCarGroupSoftware_F121_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Minimum Software Version Information for reprogrammable ECU for Bootloader Logical block
/// @pre \p Data of Bootloader Minimum Software Version of Year, Week and Patch level must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Minimum Software Version is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData function is filled with Block_Id,Data,NVM Length and Default Values to fill NVM.
extern Std_ReturnType dcom_Minimum_Software_Version_Bootloader_EF05_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Minimum Software Version Information for reprogrammable ECU for Application Logical block
/// @pre \p Data of Application Minimum Software Version of Year, Week and Patch level must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Minimum Software Version is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData function is filled with Block_Id,Data,NVM Length and Default Values to fill NVM.
extern Std_ReturnType dcom_Minimum_Software_Version_Application_EF05_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Bootloader Software Version Information for reprogrammable ECU,
/// also contains information about when the software was designed
/// @pre \p Data of Bootloader Software Version of Year, Week and Patch level must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Software version information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer fill with Bootloader Software Version of Year, Week and Patch level.
extern Std_ReturnType dcom_BootLoaderSoftwareVersion_F151_F153_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Application Software Version Information for reprogrammable ECU,
/// also contains information about when the software was designed
/// @pre \p Data of Application Software Version of Year, Week and Patch level must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Software version information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer fill with Application Software Version of Year, Week and Patch level.
extern Std_ReturnType dcom_SoftwareVersion_Application_F151_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief This function is used to read SW Version of SW Package. It includes the Major Version, Minor Version,
/// Build Version and Patch Level Version information.
/// @pre \p Data of Standard Application Software Package Version must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Software version of Standard application is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer fill with SW Release version and Sprint version
extern Std_ReturnType dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief This function is used to read MicroController Identification of SW Package
/// @pre \p Data of Standard Application Software Package XC Identification Version must be defined.
/// The check for data buffer not equal to null pointer and
/// l_dcom_HexBlock.HexInfoRef is equal to RBLCF_HEXINFOTYPE_FSW or
/// RBLCF_HEXINFOTYPE_COMPLETE should be performed.
/// @param[in,out] Data: buffer where data regarding MicroController Identification  is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief  This function is used to read Supplier Identification of SW Package
/// @pre \p Data of Standard Application Software Package Supplier Identification Version must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Supplier Identification is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer fill with Supplier Identification.
extern Std_ReturnType dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief  This function is used to read AUTOSAR platform name used in IMU.
/// @pre The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding AUTOSAR platform name will stored/
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Data pointer fill with AUTOSAR platform name.
extern Std_ReturnType dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to read the Supported Configuration Mechanisms of an ECU
/// @pre \p Data of Supported Configuration Mechanisms must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Supported Configuration Mechanisms is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
extern Std_ReturnType dcom_Supported_Configuration_Mechanisms_F131_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Vedoc Relevant Information of Hardware Part Number of the ECU.
/// @pre \p Data of Vedoc Relavant Hardware Part Number should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data of Vedoc Relevant Information of Hardware Part Number is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_VedocRelavantHardwarePartNumber_F103_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Vedoc Relevant Information of Hardware Supplier Identification of the ECU.
/// @pre \p Data of Vedoc Relavant Hardware Supplier Identification must be defined.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data of Vedoc Relevant Information of Hardware Supplier Identification is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Vedoc Relevant Information of ECU serial Number of the ECU.
/// @pre \p Data Vedoc Relavant of ECU Serial Number should be defined in the NvM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Vedoc Relevant Information on ECU serial number is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_VedocRelavantECUSerialNumber_F103_ReadData (uint8 * Data);




/// @c_file rbl_dcom_MB_AdjustISOParam_WRDBI.c
/// @brief The Function is used to read dynamically changed ISO 15765-2 transport protocol parameters BlockSize (BS)
///   and SeparationTime minimum (STmin) which are transmitted within the FlowControl message.
/// @pre \p The data of BS and STmin is updated from CanTp_ReadParameter.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding BlockSize and SeparationTime mimimum is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_AdjustISO_dcom_CanTp_ReadParameter_010B_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_CanTp_ReadParameter_010B_ReadData (uint8 * Data);

/// @c_file  rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to read the Supplier Specific Messages Mode are Active or Inactive.
/// @pre \p Supplier Specific Message should be Defined in NVM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Supplier Specific Messages Mode will transfer from NVM.
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Read Supplier Specific Messages Mode from DCOM_MB_ActivateSupplierMsgs NVM block using dcom_Lib_ReadNvMData function.
extern Std_ReturnType dcom_ActivateSupplierSpecificMessages_012A_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the software integrity, compatibility, logical block erase status and
/// reprogramming status of the bootloader data.
/// @pre \p Data of Read Software Fingerprint(s) should be defined in the NvM for Bootloader data.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Software fingerprint(s) information is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_ReadNvMData is filled with Block_Id,Data,NVM Length and Fill_NVM
extern Std_ReturnType dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the information regarding number of reprogramming attempts made by tester
/// and Maximum number of reprogramming attempts of Bootloader Data
/// @pre \p Data of Reprogramming Attempt Counter should be defined in the NvM for Bootloader data.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding number of reprogramming attempts is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ReadDataByIdentifier_dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Vehicle Odometer in Low Resolution 16km/bit.
/// @pre The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data from Vehicle Odometer in Low Resolution  is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details using function rbl_SwcDiagAdapter_ReadOdometerData read Vehicle Odometer in Low Resolution value and pass it to Data pointer.
extern Std_ReturnType dcom_VehicleOdometerLowResolution_10A_ReadData (uint8 * Data);

/// @c_file rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to Read the Current Operting time from Syncronize time base manager.
/// @pre The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data from Vehicle Odometer in Low Resolution  is stored
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details using function rbl_SwcDiagAdapter_ReadOperatingTimeData read Current Operting Time and pass it to Data pointer.
extern Std_ReturnType dcom_CurrentOperatingTime_133_ReadData (uint8 * Data);

/// @c_file  rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to read the Supplier Public Key and Supplier Signature.
/// @pre \p Supplier Specific Public Key and Supplier Signature should be Defined in NVM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Supplier Specific Messages Mode will transfer from NVM.
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @details Read Supplier Public Key and Supplier Signature from DCOM_MB_SupplierPublicKey_Signature NVM block using memmap function.
extern Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadData (uint8 * Data);

/// @c_file  rbl_dcom_MB_ReadDataByIdentifier.c
/// @brief The function is used to read the Supplier Public Key and Supplier Signature length.
/// @pre \p Supplier Specific Public Key and Supplier Signature should be Defined in NVM.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Supplier Specific Messages Mode will transfer from NVM.
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Read Supplier Public Key and Supplier Signature length from DCOM_SupplierPubKey_Sig_RAM_Mirror RAM mirror array variable.
extern Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_ReadDataLength (uint16 * DidLength);

/// @c_file  rbl_dcom_MB_RDBI_VariantCoding.c
/// @brief The function is used to read the Varinat coding data of MB AMG Switch varinat configuration.
/// @pre The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding MB AMG Switch varinat configuration will transfer from NVM.
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Read MB AMG Switch varinat configuration from DCOM_AMG_SWITCH NVM block using dcom_Lib_ReadNvMData function.
extern Std_ReturnType dcom_AMG_SWITCH_0400_ReadData (uint8 * Data);

/// @c_file  rbl_dcom_MB_RDBI_VariantCoding.c
/// @brief The function is used to read the Calibration Identification.
/// @pre The check for data buffer not equal to null pointer should be performed.
/// @param[in,out] Data: buffer where data regarding Calibration Identification will transfer from NVM.
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details Read Calibration Identification from DCOM_MB_CALID NVM block using dcom_Lib_ReadNvMData function.
extern Std_ReturnType dcom_Calibration_Identifications_E104_ReadData (uint8 * Data);

/***Extern declarations for XXX_WriteData of type USE_DATA_SYNCH_FNC ***/


/// @c_file rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The function is used for writing the VIN number into Nvm
/// @pre \p Area where the data to be written to be identified.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: Buffer that stores the VIN data to be written as per request
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of write operation is returned.
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_WriteNvMData is filled with Block_Id,Data and ErrorCode
extern Std_ReturnType dcom_VINDataIdentifier_F190_WriteData(const uint8* Data,Dcm_NegativeResponseCodeType*ErrorCode);


/// @c_file rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The function is used for writing the Diagnostic Trace Memory data to Nvm
/// @pre \p Area where the data to be written to be identified.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: buffer used to store information regarding the Diagnostic TraceMemory
/// @param[in,out] ErrorCode: parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of write operation is returned.
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @details dcom_Lib_WriteNvMData is filled with Block_Id,Data and ErrorCode
extern Std_ReturnType dcom_DiagnosticTraceMemory_102_WriteData(const uint8*Data,Dcm_NegativeResponseCodeType*ErrorCode);


/// @c_file rbl_dcom_MB_AdjustISOParam_WRDBI.c
/// @brief The Function is used to write dynamically changed ISO 15765-2 transport protocol parameters BlockSize (BS)
///   and SeparationTime minimum (STmin) which are transmitted within the FlowControl message.
/// @pre \p The data of BS and STmin is written from CanTp_ChangeParameter.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: Buffer that stores data regarding BlockSize and SeparationTime mimimum to be written
///  as per request
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of write operation is returned.
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_AdjustISO_dcom_CanTp_ChangeParameter_010B_WriteData.puml
/// @enduml
extern Std_ReturnType dcom_CanTp_ChangeParameter_010B_WriteData (uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode);

/// @c_file  rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The function is used to Write the Supplier Specific Messages Mode i.e. Active or Inactive in NVM.
/// @pre \p DCOM_MB_ActivateSupplierMsgs NVM block should be present.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: buffer where data regarding Supplier Specific Messages Mode will transferd to NVM.
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_ActivateSupplierSpecificMessages_012A_WriteData.puml
/// @enduml
extern Std_ReturnType dcom_ActivateSupplierSpecificMessages_012A_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode);

/// @c_file  rbl_dcom_MB_WDBI_VariantCoding.c
/// @brief The function is used to Write Varinat coding data for MB AMG SWITCH Configuration.
/// @pre \p rbl_dcom_MirrorAMGVarSwitch_u8 RAM mirror block should be present.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: buffer where data regarding MB AMG SWITCH Configuration transferd to RAM mirror.
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_AMG_SWITCH_0400_WriteData.puml
/// @enduml
extern Std_ReturnType dcom_AMG_SWITCH_0400_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode);

/// @c_file  rbl_dcom_MB_WDBI_VariantCoding.c
/// @brief The function is used to Write Calibration Identificaion and its number data items.
/// @pre \p rbl_Mirrordcom_CalId_u8 RAM mirror block should be present and number data items is equal to 1.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: buffer where data regarding Calibration Identificaion transferd to RAM mirror.
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_Calibration_Identifications_F804_WriteData.puml
/// @enduml
extern Std_ReturnType dcom_Calibration_Identifications_F804_WriteData(const uint8 * Data,Dcm_NegativeResponseCodeType * ErrorCode);

/***Routine control Appl functions***/
/*** Extern declaration for dcom_CheckReprogrammingPreconditions_0203_Start ***/

/// @c_file rbl_dcom_MB_RoutineControl.c
/// @brief The function is used to check programming preconditions
/// @pre This function is available when the Bootloader functionality is enabled for variant.
/// When the function switch RBFS_CheckProgPreCondition is ON then check
/// is Speed Limit Exceeded
/// is Status signal received
/// @param[in] OpStatus - This parameter is currently unused
/// @param[in,out] dataOut1 : Status of routine completion
/// @param[in,out] dataOut2 : Number of Unfulfilled Preconditions
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @param[in,out] CurrentDataLength : Length of the Response based on Number of Preconditions
/// @return Std_ReturnType It checks the conditions and fill the conditions as per the requirement
/// and sends the reprogramming is done
/// @retval E_OK
/// @startuml
/// !include rbl_dcom_RoutineControl_dcom_CheckReprogrammingPreconditions_0203_Start.puml
/// @enduml
extern Std_ReturnType dcom_CheckReprogrammingPreconditions_0203_Start(Dcm_OpStatusType OpStatus, uint8 * dataOut1,
uint8 * dataOut2, uint16 * CurrentDataLength,Dcm_NegativeResponseCodeType * ErrorCode);

/// @c_file  rbl_dcom_MB_WriteDataByIdentifier.c
/// @brief The function is used to Write the Supplier Public Key and Supplier Signature in NVM.
/// @pre \p DCOM_MB_SupplierPublicKey_Signature NVM block should be present.
/// The check for data buffer not equal to null pointer should be performed.
/// @param[in] Data: buffer where data regarding Supplier Specific Public Key and Signature will transferd to NVM.
/// @param[in] DataLength: length of buffer where data regarding Supplier Specific Public Key and Signature will transferd to NVM.
/// @param[in,out] ErrorCode : Parameter which is used to update negative response code in case of errors
/// @return Std_ReturnType The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Operation sucessful
/// @retval E_NOT_OK if Operation unsucessful
/// @startuml
/// !include rbl_dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData.puml
/// @enduml
extern Std_ReturnType dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(const uint8 * Data,uint16 DataLength, Dcm_NegativeResponseCodeType * ErrorCode);


/***Routine control Appl functions for Range Routine***/

#endif /* RBL_DCOM_MB_DESIGN.H */
