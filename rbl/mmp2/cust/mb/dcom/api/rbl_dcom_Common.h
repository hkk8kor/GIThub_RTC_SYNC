/// @file rbl_dcom_Common.h
/// @brief This header provides common macros and variables
/// @copyright (C) 2018 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_COMMON_H
#define RBL_DCOM_COMMON_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "Platform_Types.h"
#include "Dcm.h"
#include "DcmAppl.h"
#include "rbl/mmp2/ms/cswpr/cfg/RB_Prj_ConfigSettings.h"
/*
**********************************************************************************************************************
*  Constants and Macro definitions
**********************************************************************************************************************
*/
//MACRO to initialize Errorcodes before service request processing
#define DCOM_NO_ERROR                             0x00U

/* Diag Session Control Service */
#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
#define DCM_SUPPLIER_SESSION                      0x70U
#endif

/* ECU Reset Service */
#define DCOM_HARD_RESET                           0x01U
#define DCOM_SOFT_RESET                           0x03U

/* Routine Control Service */
#define DCOM_ROUTINE_SUCCESSFULLY_COMPLETED       0x00U

/* Read Data Service */

/* Value to be read when NvM is empty */
#define DCOM_READ_PDMEMPTY                        0x00U
#define DCOM_READ_PDMEMPTY_ASCII_NULL             0x30U

#define DCOM_SUPPLIERID_HIGHBYTE                  0x00U
#define DCOM_SUPPLIERID_LOWBYTE                   0x03U

#define DCOM_LOGICAL_BLOCK_NUMBER_ASW             0x00U

#define DCOM_MAX_REPROG_ATT_MSB                   0x03U
#define DCOM_MAX_REPROG_ATT_LSB                   0xE8U

/*
**********************************************************************************************************************
*  Variables
**********************************************************************************************************************
*/
#if (RBFS_CheckProgPreCondition != RBFS_CheckProgPreCondition_OFF)
extern boolean dcom_CheckReprogPreConditionFullfilled;
#endif

#endif /* RBL_DCOM_COMMON_H */
