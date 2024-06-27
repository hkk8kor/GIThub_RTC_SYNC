/// @file rbl_dcom_MB_Pub.h
/// @brief This header provides definitions for the Macros and Structure definition api,
/// functions may be used by other components
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_PUB_H
#define RBL_DCOM_MB_PUB_H

 /**
**********************************************************************************************************************
*  Includes
**********************************************************************************************************************
*/
#include "rbl_dcom_Common.h"
/**
**********************************************************************************************************************
*  Constants and Macro definitions
**********************************************************************************************************************
*/
#define DCOM_FIRST_TESTER                                   0xEF8U
#define DCOM_SECOND_TESTER                                  0xF0DU
#define DCOM_AUTOSAR_CLASSIC                                 0x00

#if (RBFS_OEMBootloader != RBFS_OEMBootloader_No)
#define DCOM_BOOTLOADER_ADDRESS                   			0x0000A01CU
#define DCOM_APPLICATION_STARTADDRESS             			0x00040000U
#define DCOM_APPLICATION_ENDADDRESS               			0x001B7FFFU
#endif

/*Active supplier Specific Message mode Range*/
# define RBL_DCOM_INVALID_SPLR_MSGS_U8      (2U)

/* Length of F103 Vedoc Relevant Information*/
#define DID_F103_DATA_LENGTH 32U
#define SupplierInfo_EndIndex 15U
//Macros for ReadDataByIdentifier

/*Default Values DDS Package Release  */
#define DCOM_DDSPCKG_YEAR                         			0x14U //Year in Decimal
#define DCOM_DDSPCKG_MONTH                        			0x01U //Month in Decimal

/* Active Diagnostic Information */
#define DCOM_ACTIVE_DIAG_STATUS_APPL                        0x00U //Active Diagnostic Status Application in Decimal

#define DCOM_INACTIVATE_SPLR_MSGS_U8               			0U  //Inactive Message
#define DCOM_INVALID_SPLR_MSGS_MODE_U8             			2U  //Invalid Message

/* Below ECU Extract version values shall be in BCD range 0x00 - 0x99 */
#define DCOM_ECU_EXTRACT_MAJOR_VERSION                      0x24U  //ECU Extract Major Version
#define DCOM_ECU_EXTRACT_MINOR_VERSION                      0x05U  //ECU Extract Minor Version
#define DCOM_ECU_EXTRACT_PATCH_VERSION                      0x00U  //ECU Extract Patch Version
#define DCOM_ECU_EXTRACT_INFO_ID_TYPE                       0x00U  //ECU Extract Information Identification type

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXTRACT_INFO_XDIS_VERSION                  (uint8)'2',(uint8)'3',(uint8)'.',(uint8)'4',\
        (uint8)'.',(uint8)'4',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ' //ASCII 23.3.1

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXTRACT_INFO_EXPORT_DATE                   (uint8)'2',(uint8)'0',(uint8)'2',(uint8)'4',\
        (uint8)'-',(uint8)'0',(uint8)'2',(uint8)'-',(uint8)'0',(uint8)'2' // ASCII 2024-02-02

#if (RBFS_MMP2 == RBFS_MMP2_IMUA)

#define DCOM_ACTIVE_DIAG_VARIANT                            0x0AU //Active Diagnostic Variant in Decimal
#define DCOM_ACTIVE_DIAG_VERSION                            0x07U //Active Diagnostic Version in Decimal

/*ECU Name Info*/
/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_IMU_ECU_NAME                                   (uint8)'I',(uint8)'M',(uint8)'U',(uint8)'_',\
        (uint8)'A',(uint8)'_',(uint8)'G',(uint8)'E',(uint8)'N',(uint8)'6'   //ASCII IMU_A_GEN6

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXT_INFO_ECU_NAME                          (uint8)'I',(uint8)'M',(uint8)'U',(uint8)'_',\
        (uint8)'A',(uint8)'_',(uint8)'S',(uint8)'T',(uint8)'A',(uint8)'R',(uint8)'_',(uint8)'3',\
        (uint8)'_',(uint8)'2',(uint8)'0',(uint8)'2',(uint8)'4',(uint8)'_',(uint8)'0',(uint8)'5',\
        (uint8)'a',(uint8)'0',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',\
        (uint8)' ',(uint8)' '   // IMU_A_STAR_3_2024_05a0

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_DIAGNOSTIC_EXTRACT_EXPORTED_DIAGNOSTIC_VARIANT (uint8)'A',(uint8)'p',(uint8)'p',(uint8)'l',\
    (uint8)'_',(uint8)'0',(uint8)'x',(uint8)'0',(uint8)'0',(uint8)'0',(uint8)'A',(uint8)'0',(uint8)'7', \
    (uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ', \
    (uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' '  //ASCII Appl_0x000A07

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXTRACT_INFO_CHECKSUM                          (uint8)'9', (uint8)'A', (uint8)'B', (uint8)'4',\
    (uint8)'6', (uint8)'F', (uint8)'0', (uint8)'A', (uint8)'B', (uint8)'3', (uint8)'C', (uint8)'3', (uint8)'7',\
    (uint8)'3', (uint8)'1', (uint8)'2', (uint8)'9', (uint8)'2', (uint8)'8', (uint8)'1', (uint8)'D', (uint8)'C',\
    (uint8)'4', (uint8)'5', (uint8)'7', (uint8)'F', (uint8)'6', (uint8)'2', (uint8)'1', (uint8)'5', (uint8)'4',\
    (uint8)'E', (uint8)'4', (uint8)'B', (uint8)'D', (uint8)'9', (uint8)'C', (uint8)'F', (uint8)'C', (uint8)'9'
       // 9AB46F0AB3C373129281DC457F62154E4BD9CFC9

#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)

#define DCOM_ACTIVE_DIAG_VARIANT                            0x0BU //Active Diagnostic Variant in Decimal
#define DCOM_ACTIVE_DIAG_VERSION                            0x07U //Active Diagnostic Version in Decimal

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_IMU_ECU_NAME                                   (uint8)'I',(uint8)'M',(uint8)'U',(uint8)'_',\
        (uint8)'B',(uint8)'_',(uint8)'G',(uint8)'E',(uint8)'N',(uint8)'6'   //ASCII IMU_B_GEN6

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXT_INFO_ECU_NAME                          (uint8)'I',(uint8)'M',(uint8)'U',(uint8)'_',\
        (uint8)'B',(uint8)'_',(uint8)'S',(uint8)'T',(uint8)'A',(uint8)'R',(uint8)'_',(uint8)'3',\
        (uint8)'_',(uint8)'2',(uint8)'0',(uint8)'2',(uint8)'4',(uint8)'_',(uint8)'0',(uint8)'5',\
        (uint8)'a',(uint8)'0',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',\
        (uint8)' ',(uint8)' '   // IMU_B_STAR_3_2024_05a0

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_DIAGNOSTIC_EXTRACT_EXPORTED_DIAGNOSTIC_VARIANT (uint8)'A',(uint8)'p',(uint8)'p',(uint8)'l',\
    (uint8)'_',(uint8)'0',(uint8)'x',(uint8)'0',(uint8)'0',(uint8)'0',(uint8)'B',(uint8)'0',(uint8)'7', \
    (uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ', \
    (uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' ',(uint8)' '  //ASCII Appl_0x000B07

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_ECU_EXTRACT_INFO_CHECKSUM                          (uint8)'0', (uint8)'7', (uint8)'2', (uint8)'C',\
    (uint8)'F', (uint8)'E', (uint8)'8', (uint8)'A', (uint8)'9', (uint8)'E', (uint8)'4', (uint8)'F', (uint8)'9',\
    (uint8)'3', (uint8)'5', (uint8)'9', (uint8)'E', (uint8)'3', (uint8)'4', (uint8)'D', (uint8)'2', (uint8)'E',\
    (uint8)'E', (uint8)'5', (uint8)'6', (uint8)'C', (uint8)'F', (uint8)'C', (uint8)'C', (uint8)'C', (uint8)'3',\
    (uint8)'C', (uint8)'F', (uint8)'C', (uint8)'C', (uint8)'9', (uint8)'E', (uint8)'B', (uint8)'F', (uint8)'6'
        //072CFE8A9E4F9359E34D2EE56CFCCC3CFCC9EBF6

#else
      #error (" ECU name is missing missing!")
#endif

#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
/*Diagnostic Extract Version Info*/
#define DCOM_DIAGNOSTIC_EXTRACT_MAJOR_VERSION               0x01U //Diagnostic Extract Major Version
#define DCOM_DIAGNOSTIC_EXTRACT_MINOR_VERSION               0x04U //Diagnostic Extract Minor Version
#define DCOM_DIAGNOSTIC_EXTRACT_PATCH_VERSION               0x01U //Diagnostic Extract Patch Version
#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
/*Diagnostic Extract Version Info*/
#define DCOM_DIAGNOSTIC_EXTRACT_MAJOR_VERSION               0x01U //Diagnostic Extract Major Version
#define DCOM_DIAGNOSTIC_EXTRACT_MINOR_VERSION               0x04U //Diagnostic Extract Minor Version
#define DCOM_DIAGNOSTIC_EXTRACT_PATCH_VERSION               0x00U //Diagnostic Extract Patch Version
#endif

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_DIAGNOSTIC_EXTRACT_CANDELA_VERSION             (uint8)'1',(uint8)'6',(uint8)'.',(uint8)'0',\
	(uint8)'.',(uint8)'1',(uint8)'0',(uint8)'0',(uint8)' ',(uint8)' '	//ASCII 16.0.100

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
#define DCOM_DIAGNOSTIC_EXTRACT_DDM_VERSION                 (uint8)'V',(uint8)'2',(uint8)'0',(uint8)'.',\
	(uint8)'2',(uint8)'.',(uint8)'0',(uint8)' ',(uint8)' ',(uint8)' '  //ASCII V20.2.0

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
/** Active diagnostics status */
extern boolean rbl_dcomActiveDiagSession;

/*Active Supplier specific Mesage Mode Ram Block*/
extern uint8 rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1];

/** Start with assumption that the tester is EF8 */
extern  uint16 dcom_Requested_Tester;

/**
**********************************************************************************************************************
* Structure definitions
**********************************************************************************************************************
*/
///Defination for Structures Members
typedef struct
{
    uint8 EcuMajorVersion; ///<ECU Major Version
    uint8 EcuMinorVersion; ///<ECU Minor Version
    uint8 EcuPatchLevel; ///<ECU Patch Level
    uint8 EcuIdentificationType; ///<ECU Identification Type
    uint8 EcuXDISVersion[10]; ///<ECU XDIS Version
    uint8 EcuExportDate[10]; ///<ECU Export Data
    uint8 EcuName[30]; ///<ECU Name
    uint8 EcuCheckSum[40]; ///<ECU Check Sum
}dcom_EcuExtractVersion_tst;

///Defination for Structures Members
typedef struct
{
    uint8 DiagnosticExtractMajorVersion; ///<Diagnostic Extract Major Version
    uint8 DiagnosticExtractMinorVersion; ///<Diagnostic Extract Minor Version
    uint8 DiagnosticExtractPatchVersion; ///<Diagnostic Extract Patch Version
    uint8 DiagnosticExtractCandelaVersion[10]; ///<Diagnostic Extract Candela Version
    uint8 DiagnosticExtractDDMVersion[10]; ///<Diagnostic Extract DDM Version
    uint8 DiagnosticExtractExportedDiagnosticVariant[30]; ///<Diagnostic Extract Exported Diagnostic Varaint
}dcom_DiagnosticExtractVersion_tst;

///Defination for Structures Members
typedef struct
{
    uint8 ImuEcuName[10];///<IMU Ecu name
}dcom_EcuName_tst;

///Defination for Structures Members
typedef struct
{
    uint8 BootDdsPackageReleaseInfo[2]; ///<Boot Package Release information in Decimal
    uint8 BootSwVersion[3]; ///<Boot Software Version in Decimal
    uint8 BootSwPartNumber[10]; ///<Boot Software Part Number in decimal
}dcom_BootHeader_tst;

///Defination for Structures Members
typedef struct
{
    uint8 ApplSwVersion[3]; ///<Application Software Version in decimal
    uint8 ApplSwPartNumber[10]; ///<Application Software Part Number in decimal
    uint8 ApplSwSupplierInformation[2]; ///<Application Software Supplier Information in decimal
    uint8 ApplDdsPackageReleaseOfApplication[2]; ///<Application Package Release of Information in decimal
    uint8 ApplHwSupplierInformation[2]; ///<Application Hardware Supplier Information in decimal
}dcom_ApplHeader_tst;

/*
**********************************************************************************************************************
* Extern declarations
**********************************************************************************************************************
*/

#endif /** RBL_DCOM_MB_PUB_H **/


