/// @file ComScl_Appl_AliveCounterLib.h
/// @brief This header provides definitions for dig com SW version
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_SWVERSION_H_
#define RBL_DCOM_SWVERSION_H_

#if (RBFS_MMP2 == RBFS_MMP2_IMUA)

/***********************************************/
/* Software Version Info                       */
/* Values shall be in Decimal                  */
/***********************************************/
#define DCOM_SOFTWARE_VERSION_YEAR                   24U //Year in Decimal
#define DCOM_SOFTWARE_VERSION_WEEK                   16U //Week in Decimal
#define DCOM_SOFTWARE_VERSION_PATCH_LEVEL            00U //Patch Level in Decimal

/***********************************************/
/*Software Part Number                         */
/* Values shall be in ASCII                    */
/***********************************************/

/* RB-MacroDefParentheses VIOLATION: This MACRO is used with parenthesis in code,not impacting functionality */
 #define RBL_IMUPLADATASWNR          (uint8)'2',(uint8)'2',(uint8)'3',(uint8)'9',(uint8)'0',(uint8)'2',(uint8)'4',(uint8)'8',(uint8)'2',(uint8)'3'

/***********************************************/
/* Standard Application SW Package Information */
/* Values shall be in BCD range 0x00 - 0x99    */
/***********************************************/
/* Example of Software Release SW 0.11 */
#define DCOM_SWRELEASE_MAJORVERSION                  0x1U  //Software Release Major Version
#define DCOM_SWRELEASE_MINORVERSION                  0x8U //Software Release Minor Version
/* Example of Software Sprint 2022.10 */
#define DCOM_SWSPRINT_MAJORVERSION                   0x24U //Software Sprint Major Version
#define DCOM_SWSPRINT_MINORVERSION                   0x05U //Software Sprint Minor Version

#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)


/***********************************************/
/* Software Version Info                       */
/* Values shall be in Decimal                  */
/***********************************************/
#define DCOM_SOFTWARE_VERSION_YEAR                   24U //Year in Decimal
#define DCOM_SOFTWARE_VERSION_WEEK                   16U //Week in Decimal
#define DCOM_SOFTWARE_VERSION_PATCH_LEVEL            00U //Patch Level in Decimal

/***********************************************/
/*Software Part Number                         */
/* Values shall be in ASCII                    */
/***********************************************/
 #define RBL_IMUPLADATASWNR          (uint8)'2',(uint8)'2',(uint8)'3',(uint8)'9',(uint8)'0',(uint8)'2',(uint8)'2',(uint8)'2',(uint8)'2',(uint8)'4'

/***********************************************/
/* Standard Application SW Package Information */
/* Values shall be in BCD range 0x00 - 0x99    */
/***********************************************/
/* Example of Software Release SW 0.11 */
#define DCOM_SWRELEASE_MAJORVERSION                  0x1U  //Software Release Major Version
#define DCOM_SWRELEASE_MINORVERSION                  0x8U //Software Release Minor Version
/* Example of Software Sprint 2022.10 */
#define DCOM_SWSPRINT_MAJORVERSION                   0x24U //Software Sprint Major Version
#define DCOM_SWSPRINT_MINORVERSION                   0x05U //Software Sprint Minor Version

#else
      #error (" ECU name is missing missing!")
#endif

/***********************************************/
/* Downgrade Protection Version Info           */
/* Values shall be in Decimal                  */
/***********************************************/
#define DCOM_DPV_SOFTWARE_VERSION_YEAR                   24U //Year in Decimal
#define DCOM_DPV_SOFTWARE_VERSION_WEEK                    5U //Week in Decimal
#define DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL            00U //Patch Level in Decimal


#endif /* RBL_DCOM_SWVERSION_H_ */
