
/// @file rbl_SigChain_Nvm.h
/// @brief Interface to the mem stack - api, functions may be used by other components
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_SIGCHAIN_NVM_H__
#define RBL_SIGCHAIN_NVM_H__
#include "rbl_ImuStdTypes.h"  /* includes std types and prj_global settings */
#include "rbl_SigChain_ConfigSettings.h" // for compiler switches
/// @c_file rbl_SigChain_Nvm.c 
/// @pre not to be called
/// @param[in,out] NvMBuffer 
/// @return always E_NOT_OK
/// @details stub needed for generation of pdm function. Items are only written in plant by adress, never by pdm id
Std_ReturnType rbl_SigChain_GenericWriteCb(void* NvMBuffer);


// TCO
/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoAccOffsVal_Red0 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8 \n
/// * part one in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_X][0]
/// * part two in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][0]
/// * part three in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][0]
///
Std_ReturnType rbl_SigChain_TCOAccRed0ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCOAccVld[0]
///
Std_ReturnType rbl_SigChain_TCOAccRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoAccOffsVal_Red1 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8 \n
/// * part one in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_X][1]
/// * part two in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][1]
/// * part three in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][1]

Std_ReturnType rbl_SigChain_TCOAccRed1ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCOAccVld[1]
///
Std_ReturnType rbl_SigChain_TCOAccRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoAccOffsVal_Red2 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8 \n
/// * part one in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_X][2]
/// * part two in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][2]
/// * part three in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][2]
///

Std_ReturnType rbl_SigChain_TCOAccRed2ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCOAccVld[2]
///
Std_ReturnType rbl_SigChain_TCOAccRed2ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoAccOffsVal_Red3 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8 \n
/// * part one in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_X][3]
/// * part two in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][3]
/// * part three in @ref rbl_SigChain_TCOAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][3]
///
Std_ReturnType rbl_SigChain_TCOAccRed3ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCOAccVld[3]
///
Std_ReturnType rbl_SigChain_TCOAccRed3ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);


/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoRateOffsVal_Red0 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_X][0]
/// * part two in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_Y][0]
/// * part three in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_Z][0] 
///
Std_ReturnType rbl_SigChain_TCORateRed0ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCORateVld[0]
///
Std_ReturnType rbl_SigChain_TCORateRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcoRateOffsVal_Red1 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_X][1]
/// * part two in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_Y][1]
/// * part three in @ref rbl_SigChain_TCORate[@ref RBL_IMUSTDTYPES_AXIS_Z][1]
///
Std_ReturnType rbl_SigChain_TCORateRed1ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCORateVld[1]
///
Std_ReturnType rbl_SigChain_TCORateRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);
#endif

// TCS

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsAccSnvtyVal_Red0 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_X][0]
/// * part two in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][0]
/// * part three in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][0]
///

Std_ReturnType rbl_SigChain_TCSAccRed0ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSAccVld[0]
///
Std_ReturnType rbl_SigChain_TCSAccRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsAccSnvtyVal_Red1 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_X][1]
/// * part two in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][1]
/// * part three in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][1]
///

Std_ReturnType rbl_SigChain_TCSAccRed1ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSAccVld[1]
///
Std_ReturnType rbl_SigChain_TCSAccRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsAccSnvtyVal_Red2 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_X][2]
/// * part two in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][2]
/// * part three in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][2]
///

Std_ReturnType rbl_SigChain_TCSAccRed2ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSAccVld[2]
///
Std_ReturnType rbl_SigChain_TCSAccRed2ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsAccSnvtyVal_Red3 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_X][3]
/// * part two in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Y][3]
/// * part three in @ref rbl_SigChain_TCSAcc[@ref RBL_IMUSTDTYPES_AXIS_Z][3]
///

Std_ReturnType rbl_SigChain_TCSAccRed3ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSAccVld[3]
///
Std_ReturnType rbl_SigChain_TCSAccRed3ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsRateSnvtyVal_Red0 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_X][0]
/// * part two in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_Y][0]
/// * part three in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_Z][0]
///

Std_ReturnType rbl_SigChain_TCSRateRed0ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] ResultType JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSRateVld[0]
///
Std_ReturnType rbl_SigChain_TCSRateRed0ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] NvMBuffer size as provided by the pdm configuration 
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_TcsRateSnvtyVal_Red1 is split into 3 parts and written via @ref rba_BswSrv_MemCopy8\n
/// * part one in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_X][1]
/// * part two in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_Y][1]
/// * part three in @ref rbl_SigChain_TCSRate[@ref RBL_IMUSTDTYPES_AXIS_Z][1]
///

Std_ReturnType rbl_SigChain_TCSRateRed1ReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_NvmTCOS.c
/// @pre called only by generated Nvm 
/// @param[in] ServiceId
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_TCSRateVld[1]
///
Std_ReturnType rbl_SigChain_TCSRateRed1ResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);
#endif
// alignment
/// @c_file rbl_SigChain_Nvm.c 
/// @pre called only by generated Nvm
/// @param[in,out] NvMBuffer size as provided by the pdm configuration  
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_AlgnmntAccVal is written via @ref rbl_SigChain_AlgnAccOrthMtrx
Std_ReturnType rbl_SigChain_AlgnAccSnvtyReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_Nvm.c
/// @pre called only by generated Nvm
/// @param[in] ServiceId
///
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.
/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_AlgnAccSnvtyNvmVld
Std_ReturnType rbl_SigChain_AlgnAccSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

/// @c_file rbl_SigChain_Nvm.c 
/// @pre called only by generated Nvm
/// @param[in,out] NvMBuffer size as provided by the pdm configuration  
///
/// @return Std_ReturnType always E_OK
/// @details content of dataitem rbl_SigChain_AlgnmntRateVal is written via @ref rbl_SigChain_AlgnRateOrthMtrx
Std_ReturnType rbl_SigChain_AlgnRateSnvtyReadCb(const void* NvMBuffer);

/// @c_file rbl_SigChain_Nvm.c 
/// @pre called only by generated Nvm
/// @param[in] ServiceId
///
/// @param[in] JobResult
///
/// @return Std_ReturnType E_OK means that reading of NVM configuration data was successful.

/// @details writes result of @ref rbl_SigChain_NvmValidCheck into @ref rbl_SigChain_Algn_RateSnvtyNvmVld
Std_ReturnType rbl_SigChain_AlgnRateSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);


// Signal Filter

/// @c_file rbl_SigChain_Nvm.c
/// @pre called only by generated Nvm
/// @param[in] ServiceId
///
/// @param[in] JobResult
///
/// @return Std_ReturnType always E_OK. Means reading of NVM configuration data was successful
/// @details Content of the data item rbl_SigChain_PickFilValue is read and the corresponding filter value (@ref rbl_SigChain_FilVal) and flush time (@ref rbl_SigChain_SigFilFlush) is selected
#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)
Std_ReturnType rbl_SigChain_PickFilResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);
#endif
/* ***** END_SECTION API functions ***** */

#endif
