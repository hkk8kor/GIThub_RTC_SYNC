/// @file rbl_SigChain_ChMap.c
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.


#include "rbl_SigChain_priv.h"
#include "rbl_SigChain_ChMap.h"

/// mapping of channels
static const rbl_SigChain_ChMap_t rbl_SigChain_ChMapSigSet =
#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
{
        {
                {{3,RBL_SIGCHAIN_MAP_ACC1,1},{0,RBL_SIGCHAIN_MAP_ACC2,1},{1,RBL_SIGCHAIN_MAP_ACC1,1},{2,RBL_SIGCHAIN_MAP_ACC2,1}}, //x
                {{3,RBL_SIGCHAIN_MAP_ACC2,1},{0,RBL_SIGCHAIN_MAP_ACC1,0},{1,RBL_SIGCHAIN_MAP_ACC2,1},{2,RBL_SIGCHAIN_MAP_ACC1,0}}, //y
                {{3,RBL_SIGCHAIN_MAP_ACC3,1},{0,RBL_SIGCHAIN_MAP_ACC3,1},{1,RBL_SIGCHAIN_MAP_ACC3,1},{2,RBL_SIGCHAIN_MAP_ACC3,1}}  //z
        },
        {
                {{0,RBL_SIGCHAIN_MAP_RATE1,1},{0,RBL_SIGCHAIN_MAP_RATE1,1}}, //x
                {{3,RBL_SIGCHAIN_MAP_RATE1,1},{3,RBL_SIGCHAIN_MAP_RATE1,1}}, //y
                {{1,RBL_SIGCHAIN_MAP_RATE1,1},{2,RBL_SIGCHAIN_MAP_RATE1,1}}  //z
        }
};
#elif (RBFS_SigChainChMap == RBFS_SigChainChMap_3SMU)
#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
{
    #if ((RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xDevBoard) \
      || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xB1xTargetBoard) \
      || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xDevBoard) \
      || (RBFS_HSWProjectVariant == RBFS_HSWProjectVariant_MMP211xC0xTargetBoard))
    {
        //  acc
        //smu / channel / inversion
        {{0,RBL_SIGCHAIN_MAP_ACC2,1},{2,RBL_SIGCHAIN_MAP_ACC1,1},{1,RBL_SIGCHAIN_MAP_ACC2,1}},  //x
        {{0,RBL_SIGCHAIN_MAP_ACC1,0},{2,RBL_SIGCHAIN_MAP_ACC2,1},{1,RBL_SIGCHAIN_MAP_ACC1,0}},  //y
        {{0,RBL_SIGCHAIN_MAP_ACC3,1},{2,RBL_SIGCHAIN_MAP_ACC3,1},{1,RBL_SIGCHAIN_MAP_ACC3,1}}   //z
    },
    {
            // rate
            {{1,RBL_SIGCHAIN_MAP_RATE1,1}}, //x
            {{2,RBL_SIGCHAIN_MAP_RATE1,1}}, //y
            {{0,RBL_SIGCHAIN_MAP_RATE1,1}}  //z
    }
    #else
    {
        //  acc
        //smu / channel / inversion
        {{2,RBL_SIGCHAIN_MAP_ACC2,1},{1,RBL_SIGCHAIN_MAP_ACC1,0},{0,RBL_SIGCHAIN_MAP_ACC1,0}},  //x
        {{2,RBL_SIGCHAIN_MAP_ACC1,0},{1,RBL_SIGCHAIN_MAP_ACC2,0},{0,RBL_SIGCHAIN_MAP_ACC2,0}},  //y
        {{2,RBL_SIGCHAIN_MAP_ACC3,1},{1,RBL_SIGCHAIN_MAP_ACC3,1},{0,RBL_SIGCHAIN_MAP_ACC3,1}}   //z
    },
    {
            // rate
            {{2,RBL_SIGCHAIN_MAP_RATE1,1}}, //x
            {{1,RBL_SIGCHAIN_MAP_RATE1,0}}, //y
            {{0,RBL_SIGCHAIN_MAP_RATE1,1}}  //z
    }
    #endif
};
#elif  ((RBFS_MMP2 == RBFS_MMP2_IMUB) || (RBFS_MMP2 == RBFS_MMP2_IMUD))
{
    {
        //  acc
        //smu / channel / inversion
        {{2,RBL_SIGCHAIN_MAP_ACC2,0},{1,RBL_SIGCHAIN_MAP_ACC1,0},{0,RBL_SIGCHAIN_MAP_ACC1,0}},  //x
        {{2,RBL_SIGCHAIN_MAP_ACC1,1},{1,RBL_SIGCHAIN_MAP_ACC2,0},{0,RBL_SIGCHAIN_MAP_ACC2,0}},  //y
        {{2,RBL_SIGCHAIN_MAP_ACC3,1},{1,RBL_SIGCHAIN_MAP_ACC3,1},{0,RBL_SIGCHAIN_MAP_ACC3,1}}   //z
    },
    {
            // rate
            {{2,RBL_SIGCHAIN_MAP_RATE1,0}}, //x
            {{1,RBL_SIGCHAIN_MAP_RATE1,0}}, //y
            {{0,RBL_SIGCHAIN_MAP_RATE1,1}}  //z
    }
};
#endif
#else
#error
#endif


void rbl_SigChainChMap(const rbl_ImuStdTypes_SmxChannelSet_t *smxSet,rbl_ImuStdTypes_ImuSignalSet_t *signalSet)
{
    uint8 smx;
    uint8 axis;
    uint8 red; /* redundant */
    uint8 ch;  /* channel */
    /* iterate over the output temperature channels */
    for(smx = 0; smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; smx++)
    {
        /* copy temperature from input (SmxChannelSet) to output (ImuSignalSet) buffer */
        signalSet->temp[smx] = smxSet->temp[smx];
    }

    /* take over time stamp from (SmxChannelSet) to output (ImuSignalSet) buffer */
    signalSet->timeStamp = smxSet->timeStamp;

    /* iterate over the output structure axis */
    for(axis=0; axis<RBL_IMUSTDTYPES_AXIS_NO; axis++)
    {
        /* iterate over the output structure acc redundancies */
        for(red=0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
        {
            /* iterate over all acceleration signals */
            /* get SMx ID and Channel number of the source from Nvm Structure */
            smx = rbl_SigChain_ChMapSigSet.acc[axis][red].smx;
            ch = rbl_SigChain_ChMapSigSet.acc[axis][red].ch;

            /* copy data from input (SmxChannelSet) to output (ImuSignalSet) buffer */
            signalSet->acc[axis][red] = smxSet->acc[smx][ch];

            /* invert value if needed */
            if(rbl_SigChain_ChMapSigSet.acc[axis][red].invert != 0)
            {
                /* apply signal inversion */
                signalSet->acc[axis][red].value *= -1.0f;
            }

        }

        /* iterate over the output structure rate redundancies */
        for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
        {
            /* iterate over all rotational / rate signals */
            /* get SMx ID and Channel number of the source from Nvm Structure */
            smx = rbl_SigChain_ChMapSigSet.rate[axis][red].smx;
            ch = rbl_SigChain_ChMapSigSet.rate[axis][red].ch;

            /* copy data from input (SmxChannelSet) to output (ImuSignalSet) buffer */
            signalSet->rate[axis][red] = smxSet->rate[smx][ch];

            /* invert value if needed */
            if(rbl_SigChain_ChMapSigSet.rate[axis][red].invert != 0)
            {
                /* apply signal inversion */
                signalSet->rate[axis][red].value *= -1.0f;
            }

        }
    }

    return;
}
