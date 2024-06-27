/// @file rbl_SigChainRBMESG.h
/// @brief  message declarations
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAINRBMESG_H__
#define RBL_SIGCHAINRBMESG_H__

#include "RBMESG_Explicit.h"
#include "rbl_SigChain.h"

/* final output of signal chain */
RBMESG_DefineMESGType_ST(SigChain_FinalDer, rbl_ImuStdTypes_ImuSignalSet_t); /// signal chain output derived signals
RBMESG_DeclareMESG(SigChain_FinalDer);
RBMESG_DefineMESGType_ST(SigChain_FinalFil, rbl_ImuStdTypes_ImuSignalSet_t); /// signal chain output filtered signals
RBMESG_DeclareMESG(SigChain_FinalFil);

/* final output of signal chain for second filter */
RBMESG_DefineMESGType_ST(SigChain_FinalDer2, rbl_ImuStdTypes_ImuSignalSet_t); /// signal chain output derived signals for second filter
RBMESG_DeclareMESG(SigChain_FinalDer2);
RBMESG_DefineMESGType_ST(SigChain_FinalFil2, rbl_ImuStdTypes_ImuSignalSet_t); /// signal chain output filtered signals for second filter
RBMESG_DeclareMESG(SigChain_FinalFil2);

RBMESG_DefineMESGType_ST(SigChain_FinalRaw, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_FinalRaw);
/* channel sets */
RBMESG_DefineMESGType_ST(SigChain_SmxChannels, rbl_ImuStdTypes_SmxChannelSet_t);
RBMESG_DeclareMESG(SigChain_SmxChannels);

/* signal sets */

RBMESG_DefineMESGType_ST(SigChain_SigSetChMap, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_SigSetChMap);

RBMESG_DefineMESGType_ST(SigChain_SigSetTCOS, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_SigSetTCOS);

RBMESG_DefineMESGType_ST(SigChain_SigSetAlgn, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_SigSetAlgn);

RBMESG_DefineMESGType_ST(SigChain_SigSetSigFil, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_SigSetSigFil);

RBMESG_DefineMESGType_ST(SigChain_SigSetSigDer, rbl_ImuStdTypes_ImuSignalSet_t);
RBMESG_DeclareMESG(SigChain_SigSetSigDer);

/* shall signal be valid or not (e.g because nvm has failure) */
RBMESG_DefineMESGType_B(SigChain_stValid);
RBMESG_DeclareMESG(SigChain_stValid);

#endif /* RBL_SIGCHAINRBMESG_H_ */
