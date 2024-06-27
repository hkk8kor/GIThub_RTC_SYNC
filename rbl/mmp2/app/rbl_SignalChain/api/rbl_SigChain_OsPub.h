/// @file rbl_SigChain_OsPub.h
/// @brief interface to OS for init and normal operation
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#ifndef RBL_SIGCHAIN_OSPUB_H__
#define RBL_SIGCHAIN_OSPUB_H__


/// @c_file rbl_SigChain_Init.c
/// @brief Initialization process of signal chain
/// @pre  called during OS initialization tasks
/// @return void 
/// @details
/// @startuml
/// !include sigchain_init.puml
/// @enduml
/// checks if the nvm data is valid. If yes, there is no error reported @ref Dem_ReportErrorStatus,
/// otherwise there is in the debug data, what nvm items were invalid via @ref Dem_ReportErrorStatusWithEnvData
void rbl_SigChainInit(void);

/// @c_file rbl_SigChain_Main.c
/// @brief Cyclic process of component rbl_SigChain 
/// @pre called during OS cyclic tasks
/// @return void 
///
/// @details 
/// @startuml
/// !include sigchain_proc.puml
/// @enduml
/// The subunits of the signal chain are called in this order
/// * @ref rbl_ImuCdd_GetImuData
/// * @ref rbl_SigChain_addStatusSmx
/// * @ref rbl_SigChainChMap
/// * @ref rbl_SigChain_TCOS
/// * @ref rbl_SigChainAlgn
/// * @ref rbl_SigChainSigFil

/// @note correlation monitor and mounting functions are switched off, they have to be adapted for MMP2 Premium
void rbl_SigChain_Proc(void);

#endif /* RBL_SIGCHAIN_OSPUB_H__ */
