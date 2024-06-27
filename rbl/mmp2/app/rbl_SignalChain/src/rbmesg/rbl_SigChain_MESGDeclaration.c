/// @file rbl_SigChain_MESGDeclaration.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#include "../rbl_SigChain_priv.h"

#include "rbl_SigChain_smxChannels.h"

#include "rbl_SigChain_SigSetChMap.h"
#include "rbl_SigChain_SigSetTCOS.h"
#include "rbl_SigChain_SigSetAlgn.h"

#include "rbl_SigChain_SigSetSigFil.h"
#include "rbl_SigChain_SigSetSigDer.h"

#include "rbl_SigChain_FinalDerived.h"
#include "rbl_SigChain_FinalFiltered.h"
#include "rbl_SigChain_FinalDerived2.h"
#include "rbl_SigChain_FinalFiltered2.h"
#include "rbl_SigChain_FinalRaw.h"

RBMESG_DefineMESG(SigChain_FinalDer);
RBMESG_DefineMESG(SigChain_FinalFil);
RBMESG_DefineMESG(SigChain_FinalDer2);
RBMESG_DefineMESG(SigChain_FinalFil2);
RBMESG_DefineMESG(SigChain_FinalRaw);

RBMESG_DefineMESG(SigChain_SmxChannels);

RBMESG_DefineMESG(SigChain_SigSetChMap);
RBMESG_DefineMESG(SigChain_SigSetTCOS);
RBMESG_DefineMESG(SigChain_SigSetAlgn);

RBMESG_DefineMESG(SigChain_SigSetSigFil);
RBMESG_DefineMESG(SigChain_SigSetSigDer);



