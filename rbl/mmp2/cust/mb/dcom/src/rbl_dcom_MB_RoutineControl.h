/// @file rbl_dcom_MB_RoutineControl.h
/// @brief  This header provides protoTypes for API's for RIDs
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_ROUTINECONTROL_H
#define RBL_DCOM_MB_ROUTINECONTROL_H
/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

#include "rbl_dcom_Common.h"

/*
**********************************************************************************************************************
* Macros and Constant Definitions
**********************************************************************************************************************
*/
#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
#define DCOM_REPROG_SPEEDLIMIT          0x10U
#define DCOM_FBL_STAR3                  0x04U
#define DCOM_VEHICLE_SPEED_HIGH         0x05U  //Not fulfilled Precondition for Vehicle Speed
#define DCOM_FBL_CFG_STAR3              0xC0U  //not fulfilled preconditions for Platform_Stat_Star3
#endif

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/


#endif /* RBL_DCOM_MB_ROUTINECONTROL_H */
