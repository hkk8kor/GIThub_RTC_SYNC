/// @file rbl_SigChain_Main.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#include "rbl_SigChain_OsPub.h"
#include "rbl_SigChain_priv.h"
#include "rbl_SigChain_SigFil.h"
#include "rbl_SigChain_ChMap.h"
#include "RB_Prj_GlobalSettings.h"
#include "rbl_ImuCdd_RbMesg.h"

#if (RBFS_ConfigurationType== RBFS_ConfigurationType_DEVELOP)
/* Variables for testing interface*/
__attribute__((used))
static uint32 rbl_SigChain_SwtTestMod;
/*[[MEASUREMENT*/
/*NAME=rbl_SigChain_SwtTestMod*/
/*COMMENT=for testing of signal chain*/
/*FORMULA=NF_IDENTITY*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/

/* channel set */
static rbl_ImuStdTypes_SmxChannelSet_t rbl_SigChain_TestInjChannelSet;
/* signal set */
static rbl_ImuStdTypes_ImuSignalSet_t  rbl_SigChain_TestInjSigSet;   /* signal set, calculated within signal chain */

#endif

static const rbl_ImuStdTypes_ImuSignalSet_t rbl_SigChain_emptySigset; /* ram init with 0 */

/* ****************************************************************************
 * ***** API public: rbl_SigChain_Proc *****
 * Description:
 *    Cyclic process of component rbl_SigChain
 *
 * Arguments:
 *    void
 *
 * Return:
 *    void
 *
 * Scheduling :
 *    This API is called during OS cyclic tasks
 *
 * Remarks:
 * ****************************************************************************/
void rbl_SigChain_Proc(void)
{
    /* channel set, from cddif */
    rbl_ImuStdTypes_SmxChannelSet_t channelSet;
    /* signal set, after channel mapping */
    rbl_ImuStdTypes_ImuSignalSet_t  sigSet;   /* signal set, calculated within signal chain */
    /* signal set after filter */
    rbl_ImuStdTypes_ImuSignalSet_t  filteredSigSet; /* filtered signal set */
    rbl_ImuStdTypes_ImuSignalSet_t  derivedSigSet;  /* derived signal set */

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
    // Filtered and Derived Signal set for second filter
    rbl_ImuStdTypes_ImuSignalSet_t  filteredSigSet2; /* filtered signal set */
    rbl_ImuStdTypes_ImuSignalSet_t  derivedSigSet2;  /* derived signal set */
#endif
    uint8 smx = 0;
    uint32 chainLinks;


    RBMESG_DefineMESGDef(SigChain_SmxChannels);
    RBMESG_DefineMESGDef(rbl_ImuCdd_SmxChannelSet);
    RBMESG_DefineMESGDef(SigChain_SigSetChMap);
    RBMESG_DefineMESGDef(SigChain_SigSetTCOS);
    RBMESG_DefineMESGDef(SigChain_SigSetAlgn);
    RBMESG_DefineMESGDef(SigChain_SigSetSigFil);
    RBMESG_DefineMESGDef(SigChain_SigSetSigDer);
    RBMESG_DefineMESGDef(SigChain_stValid);

#if (RBFS_ConfigurationType== RBFS_ConfigurationType_DEVELOP)
    uint32 activeTest = 0;
#endif

    RBMESG_GROUP_LOCK
    RBMESG_RcvMESG_GROUP(l_SigChain_stValid, SigChain_stValid);
    /* for functions, which need the value from last call get the old values */

    RBMESG_RcvMESG_GROUP(l_SigChain_SigSetSigFil, SigChain_SigSetSigFil);

    RBMESG_RcvMESG_GROUP(l_rbl_ImuCdd_SmxChannelSet,rbl_ImuCdd_SmxChannelSet);
    RBMESG_GROUP_UNLOCK

    chainLinks = rbl_SignalChainActive;
    sigSet = rbl_SigChain_emptySigset;
    filteredSigSet = rbl_SigChain_emptySigset;
    derivedSigSet = rbl_SigChain_emptySigset;

#if (RBFS_ConfigurationType== RBFS_ConfigurationType_DEVELOP)
    /* is requested test active? */
    /* if you configure more than one module for test, keep in mind that the first influence the input signal of the next modules */
    activeTest = rbl_SigChain_SwtTestMod & chainLinks;

    /* if testing is active */
    if(0u != activeTest)
    {
        chainLinks = activeTest;

        /* for testing not the values for CDD are taken, depending on the unit to test, the messages can be manipulated with xcp */
        channelSet = rbl_SigChain_TestInjChannelSet;
        sigSet = rbl_SigChain_TestInjSigSet;
        filteredSigSet = rbl_SigChain_TestInjSigSet;
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
        filteredSigSet2 = rbl_SigChain_TestInjSigSet;
#endif
    }
    else
#endif
    {
        /* get data from CddIf */
        channelSet = l_rbl_ImuCdd_SmxChannelSet;
    }

    /* provide status after signal chain step for testing and diagnosis purpose */
    l_SigChain_SmxChannels = channelSet;
    /* mark signals invalid if there are invalid NVM signals*/

    for(smx = 0; smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; smx++ )
    {
        if (FALSE == l_SigChain_stValid)
        {
            rbl_SigChain_addStatusSmx(&channelSet, RBL_IMUSTDTYPES_PRMNT_INVALID, smx);
        }
    }

    RBMESG_SendMESGDef(SigChain_SmxChannels);

    /*___________________ Channel Mapper ___________________________ */
    if (0u != (chainLinks & RBL_IMU_CHMAP))
    {
        /* channelSet is input, sigSet is output */
        rbl_SigChainChMap(&channelSet,&sigSet);
    }
    /* provide status after signal chain step for testing and diagnosis purpose */
    l_SigChain_SigSetChMap = sigSet;

    /*___________________ TCOS ___________________________ */
    if (0u != (chainLinks & RBL_IMU_TCOS))
    {
        rbl_SigChain_TCOS(&sigSet);
    }
    /* provide status after signal chain step for testing and diagnosis purpose */
    l_SigChain_SigSetTCOS = sigSet;

    /*___________________ Alignment ___________________________ */
    if (0u != (chainLinks & RBL_IMU_ALGN))
    {
        rbl_SigChainAlgn(&sigSet);
    }
    /* provide status after signal chain step for testing and diagnosis purpose */
    l_SigChain_SigSetAlgn = sigSet;

#if	(RBFS_SigChainMounting != RBFS_SigChainMounting_OFF)
#error in case mounting is needed, check component baseline 1130 or older
#endif
    /*___________________ Signal Filter ___________________________ */
    // signal filter     + derived signals
    if (0u != (chainLinks & RBL_IMU_SIGFIL))
    {
        /* call it */
        rbl_SigChainSigFil(&sigSet, &filteredSigSet, &derivedSigSet, RBL_SIGCHAIN_FIRSTFILTER);
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
        rbl_SigChainSigFil(&sigSet, &filteredSigSet2, &derivedSigSet2, RBL_SIGCHAIN_SECONDFILTER);
#endif
    }
    else
    {
#if (RBFS_ConfigurationType== RBFS_ConfigurationType_DEVELOP)
        /* don't manipulate values, if they are needed for test */
        if(0u == activeTest)
#endif
        {
            /* if the signal filter is not active, the sig set and the filtered sig set are identical */
            filteredSigSet = sigSet;
            derivedSigSet = sigSet;

            /* derived signal can't be calculated, so derived signals are 0 and permanently invalid */
            rbl_SigChain_setAxesZero(&derivedSigSet);
            rbl_SigChain_addStatusSignalSet(&derivedSigSet, RBL_IMUSTDTYPES_PRMNT_INVALID);

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
            filteredSigSet2 = filteredSigSet;
            derivedSigSet2 = derivedSigSet;
#endif
        }
    }
    /* provide status after signal chain step for testing and diagnosis purpose */
    l_SigChain_SigSetSigFil = filteredSigSet;
    l_SigChain_SigSetSigDer = derivedSigSet;

#if (RBFS_ConfigurationType== RBFS_ConfigurationType_DEVELOP)
    /* mark signal sets as invalid, if the they were manipulated by test */
    if(0u != activeTest)
    {
        rbl_SigChain_addStatusSignalSet(&sigSet,RBL_IMUSTDTYPES_PRMNT_INVALID);
        rbl_SigChain_addStatusSignalSet(&filteredSigSet,RBL_IMUSTDTYPES_PRMNT_INVALID);
        rbl_SigChain_addStatusSignalSet(&derivedSigSet,RBL_IMUSTDTYPES_PRMNT_INVALID);
    }
#endif
    RBMESG_GROUP_LOCK
    /* end of signal chain */
    /* final signals for CustIF */
    RBMESG_SendMESG_GROUP(SigChain_FinalDer, derivedSigSet);
    RBMESG_SendMESG_GROUP(SigChain_FinalFil, filteredSigSet);
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
    /*Final signals for Second Filter */
    RBMESG_SendMESG_GROUP(SigChain_FinalDer2, derivedSigSet2);
    RBMESG_SendMESG_GROUP(SigChain_FinalFil2, filteredSigSet2);
#endif
    RBMESG_SendMESG_GROUP(SigChain_FinalRaw, sigSet);
    /* intermediate signals of signal chain */
    RBMESG_SendMESG_GROUP(SigChain_SmxChannels,l_SigChain_SmxChannels);
    RBMESG_SendMESG_GROUP(SigChain_SigSetChMap, l_SigChain_SigSetChMap);
    RBMESG_SendMESG_GROUP(SigChain_SigSetTCOS, l_SigChain_SigSetTCOS);
    RBMESG_SendMESG_GROUP(SigChain_SigSetAlgn, l_SigChain_SigSetAlgn);
    RBMESG_SendMESG_GROUP(SigChain_SigSetSigFil, l_SigChain_SigSetSigFil);
    RBMESG_SendMESG_GROUP(SigChain_SigSetSigDer, l_SigChain_SigSetSigDer);

    RBMESG_GROUP_UNLOCK
    return;
}
/* ***** END_API rbl_SigChain ***** */

