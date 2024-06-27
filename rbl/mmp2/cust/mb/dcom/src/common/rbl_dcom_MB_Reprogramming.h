/// @file rbl_dcom_MB_Reprogramming.h
/// @brief This header provides definitions for the Macros and Structure definition api,
/// functions may be used by other components
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_REPROGRAMMING_H
#define RBL_DCOM_MB_REPROGRAMMING_H

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
///Inverted pattern for reprogramming request which indicates Bootloader start request
#define DCOM_REQPROGREQUESTINVERTED                         0x5AA5E11EU


///MB External Tester Reset reason pattern which indicates to start programming session in FBL
#define DCOM_PROGRAMMINGSESSION                             0x88BB1007U



//#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
///MB Internal Tester Reset reason pattern which indicates to start programming session in FBL
#define DCOM_PROGRAMMINGSESSION_2NDTESTER               0x44BB1002U

//#endif

#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Cold)
///MB External Tester Reset reason pattern which indicates to send positive response for $10 01 in Application
#define DCOM_DEFAULTSESSION                                 0x88991006U

///MB External Tester Reset reason pattern which indicates to send positive response for $11 01 in Application
#define DCOM_HARDRESET                                      0x88AA1106U

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)

///MB Internal Tester Reset reason pattern which indicates to send positive response for $10 01 in Application
    #define DCOM_DEFAULTSESSION_2NDTESTER                   0x66991001U

///MB Internal Tester Reset reason pattern which indicates to send positive response for $11 01 in Application
    #define DCOM_HARDRESET_2NDTESTER                        0x55AA1101U

#endif

#endif

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/


/**
**********************************************************************************************************************
* Structure definitions
**********************************************************************************************************************
*/
///BackUp RAM flags defined for transition between Application and OEM Bootloader.
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
typedef struct
{
    uint32 Bldr_Start_Request_Inverted; ///< Reprog Request inverted to OEM Bootloader
    uint32 Bldr_Reset_Reason;           ///< Reset reason flag
    uint32 Reserved[2];                 ///< Reserved flag
}dcom_BackUp_RAM_tst;
#endif


#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)

/// @c_file rbl_dcom_MB_Reprogramming.c
/// @brief This API should set botloader start request for the Application to Bootloader jump.
/// @pre Function is only active if RBFS_DcomReprogResponseType is configured to RBFS_DcomReprogResponseType_Cold
/// @param[in]   : none
/// @param[out]  : none
/// @return      : none
/// @startuml
/// !include rbl_dcom_Reprog_dcom_set_prog.puml
///@enduml
/// @details API shall set the following informations:
///     Reprogramming request inverted(at address 0xFEBF_FC04) to @ref DCOM_REQPROGREQUESTINVERTED.
///     If the requested tester is external tester ,Reset reason (at address 0xFEBF_FC08) to @ref DCOM_PROGRAMMINGSESSION.
///     If the requested tester is internal tester ,Reset reason (at address 0xFEBF_FC08) to @ref DCOM_PROGRAMMINGSESSION_2NDTESTER
///     Application reset has to be performed through @ref RB_performSWResetWithBootBlock4OEM

void dcom_SetProgConditions(void);
#endif


#endif /** RBL_DCOM_MB_REPROGRAMMING_H **/
