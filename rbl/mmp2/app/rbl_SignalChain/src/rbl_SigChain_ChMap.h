/// @file
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_CHMAP_H_
#define RBL_SIGCHAIN_CHMAP_H_

/// channel mapping configuration one channel
typedef struct
{
    uint8 smx; ///< smx to be used for this signal
    uint8 ch;  ///< channel to be used
    uint8 invert; ///< signal invertion
} rbl_SigChain_ChMapSig_t;

/// channel mapping all channels
typedef struct
{
    rbl_SigChain_ChMapSig_t acc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC]; ///< mapping for acc channels
    rbl_SigChain_ChMapSig_t rate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];///< mapping for rate channels
}rbl_SigChain_ChMap_t;

/// @c_file rbl_SigChain_ChMap.c
/// @brief maps signals from SMX coordinate system to IMU coordinate systems.
///
/// @pre called by Signal Chain
/// @param[in] *smxSet signals in smx coordinate system
/// @param[out] *signalSet signals IMU coordinate systems
///
/// @return void
///
/// @details signals are copied as defined in @ref rbl_SigChain_ChMapSigSet
///
void rbl_SigChainChMap(const rbl_ImuStdTypes_SmxChannelSet_t *smxSet,rbl_ImuStdTypes_ImuSignalSet_t *signalSet);

#define RBL_SIGCHAIN_MAP_ACC1 0  ///< map target ACC1
#define RBL_SIGCHAIN_MAP_ACC2 1  ///< map target ACC2
#define RBL_SIGCHAIN_MAP_ACC3 2  ///< map target ACC3

#define RBL_SIGCHAIN_MAP_RATE1 0  ///< map target RATE1 (sometimes known as YRS1)


#endif
