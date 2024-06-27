/// @file rbl_SigChain_Measure_Nvm.h
/// @brief measurement comments
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_SIGCHAIN_MEASURE_NVM_H__
#define RBL_SIGCHAIN_MEASURE_NVM_H__

#include "CM_Basetypes_COMMON.h"
#include "rbl_ImuStdTypes.h"

/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_AlgnAccSnvtyNvmVld*/
/*COMMENT= flag indicates if Nvm values are valid */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/


/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_Algn_RateSnvtyNvmVld*/
/*COMMENT= flag indicates if Nvm values are valid */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_SigFilNvmVld*/
/*COMMENT= flag indicates if Nvm values are valid */
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
#endif

#endif
