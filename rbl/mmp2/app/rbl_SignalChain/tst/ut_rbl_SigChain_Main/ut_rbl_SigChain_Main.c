/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_SigChain_Main.c
 *    Author: MAJ3BRG
 *    Generated on: 28-Jul-2020 09:17:38
 *    Generated from: rbl_SigChain_Main.c
 *    Project: MMP2
 *    Software: ASW
 *    Tester: MAJ3BRG
 *    Version: 2.0
 *    Last update: 27/07/2022
 *
*/
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_SigChain_OsPub.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_SigFil.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_ChMap.h"
#include "RB_Prj_GlobalSettings.h"
#include "rbl_ImuCdd_RbMesg.h"

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rbl_SigChain_Proc();
void RBSYS_EnterCommonLock_intern();
void RBSYS_ExitCommonLock_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
void rbl_SigChain_addStatusSmx(rbl_ImuStdTypes_SmxChannelSet_t * ImuData, uint8 status, uint8 smx);
void rbl_SigChainChMap(const rbl_ImuStdTypes_SmxChannelSet_t * smxSet, rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
void rbl_SigChain_TCOS(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
void rbl_SigChainAlgn(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
void rbl_SigChainSigFil(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, uint32 filterNumber);
void rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
void rbl_SigChain_addStatusSignalSet(rbl_ImuStdTypes_ImuSignalSet_t * signalSet, uint8 status);
void initialise_aux_structures();
void initialise_source_structures();
void check_global_data();

/* Global data */
volatile RBMESG_Type_SigChain_stValid RBMESG_SigChain_stValid;
volatile RBMESG_Type_SigChain_SigSetSigFil RBMESG_SigChain_SigSetSigFil;
volatile RBMESG_Type_rbl_ImuCdd_SmxChannelSet RBMESG_rbl_ImuCdd_SmxChannelSet;
uint32 rbl_SignalChainActive;
volatile RBMESG_Type_SigChain_SmxChannels RBMESG_SigChain_SmxChannels;
volatile RBMESG_Type_SigChain_FinalDer RBMESG_SigChain_FinalDer;
volatile RBMESG_Type_SigChain_FinalFil RBMESG_SigChain_FinalFil;
volatile RBMESG_Type_SigChain_FinalDer2 RBMESG_SigChain_FinalDer2;
volatile RBMESG_Type_SigChain_FinalFil2 RBMESG_SigChain_FinalFil2;
volatile RBMESG_Type_SigChain_FinalRaw RBMESG_SigChain_FinalRaw;
volatile RBMESG_Type_SigChain_SigSetChMap RBMESG_SigChain_SigSetChMap;
volatile RBMESG_Type_SigChain_SigSetTCOS RBMESG_SigChain_SigSetTCOS;
volatile RBMESG_Type_SigChain_SigSetAlgn RBMESG_SigChain_SigSetAlgn;
volatile RBMESG_Type_SigChain_SigSetSigDer RBMESG_SigChain_SigSetSigDer;
typedef struct rbl_SigChain_Main_av_struct
{
	uint32 * ref_rbl_SigChain_SwtTestMod;
	rbl_ImuStdTypes_SmxChannelSet_t * ref_rbl_SigChain_TestInjChannelSet;
	rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_SigChain_TestInjSigSet;
	const rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_SigChain_emptySigset;
} rbl_SigChain_Main_av_struct;
extern rbl_SigChain_Main_av_struct av_rbl_SigChain_Main;


/* Expected variables for global data */
RBMESG_Type_SigChain_stValid expected_RBMESG_SigChain_stValid;
RBMESG_Type_SigChain_SigSetSigFil expected_RBMESG_SigChain_SigSetSigFil;
RBMESG_Type_rbl_ImuCdd_SmxChannelSet expected_RBMESG_rbl_ImuCdd_SmxChannelSet;
uint32 expected_rbl_SignalChainActive;
RBMESG_Type_SigChain_SmxChannels expected_RBMESG_SigChain_SmxChannels;
RBMESG_Type_SigChain_FinalDer expected_RBMESG_SigChain_FinalDer;
RBMESG_Type_SigChain_FinalFil expected_RBMESG_SigChain_FinalFil;
RBMESG_Type_SigChain_FinalDer2 expected_RBMESG_SigChain_FinalDer2;
RBMESG_Type_SigChain_FinalFil2 expected_RBMESG_SigChain_FinalFil2;
RBMESG_Type_SigChain_FinalRaw expected_RBMESG_SigChain_FinalRaw;
RBMESG_Type_SigChain_SigSetChMap expected_RBMESG_SigChain_SigSetChMap;
RBMESG_Type_SigChain_SigSetTCOS expected_RBMESG_SigChain_SigSetTCOS;
RBMESG_Type_SigChain_SigSetAlgn expected_RBMESG_SigChain_SigSetAlgn;
RBMESG_Type_SigChain_SigSetSigDer expected_RBMESG_SigChain_SigSetSigDer;
typedef struct expected_rbl_SigChain_Main_av_struct
{
	uint32 ref_rbl_SigChain_SwtTestMod;
	rbl_ImuStdTypes_SmxChannelSet_t ref_rbl_SigChain_TestInjChannelSet;
	rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_SigChain_TestInjSigSet;
	rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_SigChain_emptySigset;
} expected_rbl_SigChain_Main_av_struct;
expected_rbl_SigChain_Main_av_struct expected_av_rbl_SigChain_Main;

rbl_ImuStdTypes_ImuSignalSet_t Aux_ImuSignalSet;

void initialise_aux_structures()
{
	int i = 0, j = 0;
	// NULL/Filled Signal Set
	for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
	{
		// --- ACC ---
		for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
		{
			Aux_ImuSignalSet.acc[i][j].value = 1;
			Aux_ImuSignalSet.acc[i][j].status = 2;
			Aux_ImuSignalSet.acc[i][j].smx = 3;
		}

		// --- RATE ---
		for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
		{
			Aux_ImuSignalSet.rate[i][j].value = 4;
			Aux_ImuSignalSet.rate[i][j].status = 5;
			Aux_ImuSignalSet.rate[i][j].smx = 6;
		}
	}

	// --- TEMP ---
	for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
	{
		Aux_ImuSignalSet.temp[i].value = 7;
		Aux_ImuSignalSet.temp[i].status = 8;
		Aux_ImuSignalSet.temp[i].smx = 9;
	}

	Aux_ImuSignalSet.timeStamp = 10;
}

void initialise_source_structures()
{
	int i = 0, j = 0;

	for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
	{
		// --- ACC ---
		for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
		{
			// --- TestInjChannelSet ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).acc[i][j].value = i + j;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).acc[i][j].status = i + j + 1;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).acc[i][j].smx = i + j + 2;

			// --- TestInjSigSet ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j].value = i + j + 3;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j].status = i + j + 4;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j].smx = i + j + 5;

			// --- SigFil ---
			RBMESG_SigChain_SigSetSigFil.acc[i][j].value = i + j + 6;
			RBMESG_SigChain_SigSetSigFil.acc[i][j].status = i + j + 7;
			RBMESG_SigChain_SigSetSigFil.acc[i][j].smx = i + j + 8;

			// --- SigDer ---
			RBMESG_SigChain_SigSetSigDer.acc[i][j].value = i + j + 9;
			RBMESG_SigChain_SigSetSigDer.acc[i][j].status = i + j + 10;
			RBMESG_SigChain_SigSetSigDer.acc[i][j].smx = i + j + 11;

			// --- SetChMap ---
			RBMESG_SigChain_SigSetChMap.acc[i][j].value = i + j + 12;
			RBMESG_SigChain_SigSetChMap.acc[i][j].status = i + j + 13;
			RBMESG_SigChain_SigSetChMap.acc[i][j].smx = i + j + 14;

			// --- TCOS ---
			RBMESG_SigChain_SigSetTCOS.acc[i][j].value = i + j + 15;
			RBMESG_SigChain_SigSetTCOS.acc[i][j].status = i + j + 16;
			RBMESG_SigChain_SigSetTCOS.acc[i][j].smx = i + j + 17;

			// --- Algn ---
			RBMESG_SigChain_SigSetAlgn.acc[i][j].value = i + j + 18;
			RBMESG_SigChain_SigSetAlgn.acc[i][j].status = i + j + 19;
			RBMESG_SigChain_SigSetAlgn.acc[i][j].smx = i + j + 20;

			// --- SmxChannels ---
			RBMESG_SigChain_SmxChannels.acc[i][j].value = i + j + 21;
			RBMESG_SigChain_SmxChannels.acc[i][j].status = i + j + 22;
			RBMESG_SigChain_SmxChannels.acc[i][j].smx = i + j + 23;

			// --- FinalDer ---
			RBMESG_SigChain_FinalDer.acc[i][j].value = i + j + 24;
			RBMESG_SigChain_FinalDer.acc[i][j].status = i + j + 25;
			RBMESG_SigChain_FinalDer.acc[i][j].smx = i + j + 26;

			// --- FinalFil ---
			RBMESG_SigChain_FinalFil.acc[i][j].value = i + j + 27;
			RBMESG_SigChain_FinalFil.acc[i][j].status = i + j + 28;
			RBMESG_SigChain_FinalFil.acc[i][j].smx = i + j + 29;

			// --- FinalRaw ---
			RBMESG_SigChain_FinalRaw.acc[i][j].value = i + j + 30;
			RBMESG_SigChain_FinalRaw.acc[i][j].status = i + j + 31;
			RBMESG_SigChain_FinalRaw.acc[i][j].smx = i + j + 32;
		}

		// --- RATE ---
		for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
		{
			// --- TestInjChannelSet ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).rate[i][j].value = i + j;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).rate[i][j].status = i + j + 1;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).rate[i][j].smx = i + j + 2;

			// --- TestInjSigSet ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j].value = i + j + 3;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j].status = i + j + 4;
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j].smx = i + j + 5;

			// --- SigFil ---
			RBMESG_SigChain_SigSetSigFil.rate[i][j].value = i + j + 6;
			RBMESG_SigChain_SigSetSigFil.rate[i][j].status = i + j + 7;
			RBMESG_SigChain_SigSetSigFil.rate[i][j].smx = i + j + 8;

			// --- SigDer ---
			RBMESG_SigChain_SigSetSigDer.rate[i][j].value = i + j + 9;
			RBMESG_SigChain_SigSetSigDer.rate[i][j].status = i + j + 10;
			RBMESG_SigChain_SigSetSigDer.rate[i][j].smx = i + j + 11;

			// --- SetChMap ---
			RBMESG_SigChain_SigSetChMap.rate[i][j].value = i + j + 12;
			RBMESG_SigChain_SigSetChMap.rate[i][j].status = i + j + 13;
			RBMESG_SigChain_SigSetChMap.rate[i][j].smx = i + j + 14;

			// --- TCOS ---
			RBMESG_SigChain_SigSetTCOS.rate[i][j].value = i + j + 15;
			RBMESG_SigChain_SigSetTCOS.rate[i][j].status = i + j + 16;
			RBMESG_SigChain_SigSetTCOS.rate[i][j].smx = i + j + 17;

			// --- Algn ---
			RBMESG_SigChain_SigSetAlgn.rate[i][j].value = i + j + 18;
			RBMESG_SigChain_SigSetAlgn.rate[i][j].status = i + j + 19;
			RBMESG_SigChain_SigSetAlgn.rate[i][j].smx = i + j + 20;

			// --- SmxChannels ---
			RBMESG_SigChain_SmxChannels.rate[i][j].value = i + j + 21;
			RBMESG_SigChain_SmxChannels.rate[i][j].status = i + j + 22;
			RBMESG_SigChain_SmxChannels.rate[i][j].smx = i + j + 23;

			// --- FinalDer ---
			RBMESG_SigChain_FinalDer.rate[i][j].value = i + j + 24;
			RBMESG_SigChain_FinalDer.rate[i][j].status = i + j + 25;
			RBMESG_SigChain_FinalDer.rate[i][j].smx = i + j + 26;

			// --- FinalFil ---
			RBMESG_SigChain_FinalFil.rate[i][j].value = i + j + 27;
			RBMESG_SigChain_FinalFil.rate[i][j].status = i + j + 28;
			RBMESG_SigChain_FinalFil.rate[i][j].smx = i + j + 29;

			// --- FinalRaw ---
			RBMESG_SigChain_FinalRaw.rate[i][j].value = i + j + 30;
			RBMESG_SigChain_FinalRaw.rate[i][j].status = i + j + 31;
			RBMESG_SigChain_FinalRaw.rate[i][j].smx = i + j + 32;
		}
	}

	// --- TEMP ---
	for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
	{
		// --- TestInjChannelSet ---
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).temp[i].value = i;
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).temp[i].status = i + 1;
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).temp[i].smx = i + 2;

		// --- TestInjSigSet ---
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i].value = i + 3;
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i].status = i + 4;
		ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i].smx = i + 5;

		// --- SigFil ---
		RBMESG_SigChain_SigSetSigFil.temp[i].value = i + 6;
		RBMESG_SigChain_SigSetSigFil.temp[i].status = i + 7;
		RBMESG_SigChain_SigSetSigFil.temp[i].smx = i + 8;

		// --- SigDer ---
		RBMESG_SigChain_SigSetSigDer.temp[i].value = i + 9;
		RBMESG_SigChain_SigSetSigDer.temp[i].status = i + 10;
		RBMESG_SigChain_SigSetSigDer.temp[i].smx = i + 11;

		// --- SetChMap ---
		RBMESG_SigChain_SigSetChMap.temp[i].value = i + 12;
		RBMESG_SigChain_SigSetChMap.temp[i].status = i + 13;
		RBMESG_SigChain_SigSetChMap.temp[i].smx = i + 14;

		// --- TCOS ---
		RBMESG_SigChain_SigSetTCOS.temp[i].value = i + 15;
		RBMESG_SigChain_SigSetTCOS.temp[i].status = i + 16;
		RBMESG_SigChain_SigSetTCOS.temp[i].smx = i + 17;

		// --- Algn ---
		RBMESG_SigChain_SigSetAlgn.temp[i].value = i + 18;
		RBMESG_SigChain_SigSetAlgn.temp[i].status = i + 19;
		RBMESG_SigChain_SigSetAlgn.temp[i].smx = i + 20;

		// --- SmxChannels ---
		RBMESG_SigChain_SmxChannels.temp[i].value = i + 21;
		RBMESG_SigChain_SmxChannels.temp[i].status = i + 22;
		RBMESG_SigChain_SmxChannels.temp[i].smx = i + 23;

		// --- FinalDer ---
		RBMESG_SigChain_FinalDer.temp[i].value = i + 24;
		RBMESG_SigChain_FinalDer.temp[i].status = i + 25;
		RBMESG_SigChain_FinalDer.temp[i].smx = i + 26;

		// --- FinalFil ---
		RBMESG_SigChain_FinalFil.temp[i].value = i + 27;
		RBMESG_SigChain_FinalFil.temp[i].status = i + 28;
		RBMESG_SigChain_FinalFil.temp[i].smx = i + 29;

		// --- FinalRaw ---
		RBMESG_SigChain_FinalRaw.temp[i].value = i + 30;
		RBMESG_SigChain_FinalRaw.temp[i].status = i + 31;
		RBMESG_SigChain_FinalRaw.temp[i].smx = i + 32;
	}

	// --- Cdd Channel Set ---
	for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_SMX; i++)
	{
		// --- ACC ---
		for (j=0; j< RBL_IMUSTDTYPES_NO_OF_ACC_PER_SMX; j++)
		{
			RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j].value = i + j;
			RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j].status = i + j + 1;
			RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j].smx = i + j + 2;
		}

		// --- RATE ---
		for (j=0; j< RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX; j++)
		{
			RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j].value = i + j + 3;
			RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j].status = i + j + 4;
			RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j].smx = i + j + 5;
		}

		// --- TEMP ---
		RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i].value = i + 6;
		RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i].status = i + 7;
		RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i].smx = i + 8;
	}

	// --- TIMESTAMP ---
		// --- TestInjChannelSet ---
	ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).timeStamp = 0;

		// --- TestInjSigSet ---
	ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp = 1;

		// --- SigFil ---
	RBMESG_SigChain_SigSetSigFil.timeStamp = 2;

		// --- SigDer ---
	RBMESG_SigChain_SigSetSigDer.timeStamp = 3;

		// --- SetChMap ---
	RBMESG_SigChain_SigSetChMap.timeStamp = 4;

		// --- TCOS ---
	RBMESG_SigChain_SigSetTCOS.timeStamp = 5;

		// --- Algn ---
	RBMESG_SigChain_SigSetAlgn.timeStamp = 6;

		// --- SmxChannels ---
	RBMESG_SigChain_SmxChannels.timeStamp = 7;

		// --- FinalDer ---
	RBMESG_SigChain_FinalDer.timeStamp = 8;

		// --- FinalFil ---
	RBMESG_SigChain_FinalFil.timeStamp = 9;

		// --- FinalRaw ---
	RBMESG_SigChain_FinalRaw.timeStamp = 10;

		// --- Cdd Channel Set ---
	RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = 11;


	// --- EXPECTED VALUES ---
	ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet) = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet);
	ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet) = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet);
	expected_RBMESG_SigChain_SigSetSigFil = RBMESG_SigChain_SigSetSigFil;
	expected_RBMESG_SigChain_SigSetSigDer = RBMESG_SigChain_SigSetSigDer;
	expected_RBMESG_SigChain_SigSetChMap = RBMESG_SigChain_SigSetChMap;
	expected_RBMESG_SigChain_SigSetTCOS = RBMESG_SigChain_SigSetTCOS;
	expected_RBMESG_SigChain_SigSetAlgn = RBMESG_SigChain_SigSetAlgn;
	expected_RBMESG_SigChain_SmxChannels = RBMESG_SigChain_SmxChannels;
	expected_RBMESG_rbl_ImuCdd_SmxChannelSet = RBMESG_rbl_ImuCdd_SmxChannelSet;
}

void check_global_data()
{
	CHECK_MEMORY("RBMESG_rbl_ImuCdd_SmxChannelSet", (const void *)&RBMESG_rbl_ImuCdd_SmxChannelSet, &expected_RBMESG_rbl_ImuCdd_SmxChannelSet, sizeof(RBMESG_rbl_ImuCdd_SmxChannelSet));
	CHECK_MEMORY("RBMESG_SigChain_SigSetSigFil", (const void *)&RBMESG_SigChain_SigSetSigFil, &expected_RBMESG_SigChain_SigSetSigFil, sizeof(RBMESG_SigChain_SigSetSigFil));
	CHECK_MEMORY("RBMESG_SigChain_SigSetSigDer", (const void *)&RBMESG_SigChain_SigSetSigDer, &expected_RBMESG_SigChain_SigSetSigDer, sizeof(RBMESG_SigChain_SigSetSigDer));
	CHECK_MEMORY("RBMESG_SigChain_SmxChannels", (const void *)&RBMESG_SigChain_SmxChannels, &expected_RBMESG_SigChain_SmxChannels, sizeof(RBMESG_SigChain_SmxChannels));
	CHECK_MEMORY("RBMESG_SigChain_SigSetChMap", (const void *)&RBMESG_SigChain_SigSetChMap, &expected_RBMESG_SigChain_SigSetChMap, sizeof(RBMESG_SigChain_SigSetChMap));
	CHECK_MEMORY("RBMESG_SigChain_SigSetTCOS", (const void *)&RBMESG_SigChain_SigSetTCOS, &expected_RBMESG_SigChain_SigSetTCOS, sizeof(RBMESG_SigChain_SigSetTCOS));
	CHECK_MEMORY("RBMESG_SigChain_SigSetAlgn", (const void *)&RBMESG_SigChain_SigSetAlgn, &expected_RBMESG_SigChain_SigSetAlgn, sizeof(RBMESG_SigChain_SigSetAlgn));
	CHECK_MEMORY("TestInjChannelSet", (const void *)&ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet), &ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet), sizeof(ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet)));
	CHECK_MEMORY("TestInjSigSet", (const void *)&ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), &ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), sizeof(ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet)));

	CHECK_U_INT(RBMESG_SigChain_stValid, expected_RBMESG_SigChain_stValid);
	CHECK_U_INT(rbl_SignalChainActive, expected_rbl_SignalChainActive);
	CHECK_U_INT(ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChain_Proc(int);

/*****************************************************************************/
/* Coverage Analysis                                                         */
/*****************************************************************************/
/* Coverage Rule Set: ISO26262-6 2011 ASIL D unit level (HR) */
static void rule_set(char* cppca_sut,
                     char* cppca_context)
{
    START_TEST("COVERAGE RULE SET",
               "ISO26262-6 2011 ASIL D unit level (HR)");
#ifdef CANTPP_SUBSET_DEFERRED_ANALYSIS
    TEST_SCRIPT_WARNING("Coverage Rule Set ignored in deferred analysis mode\n");
#elif CANTPP_COVERAGE_INSTRUMENTATION_DISABLED
    TEST_SCRIPT_WARNING("Coverage Instrumentation has been disabled\n");
#elif CANTPP_INSTRUMENTATION_DISABLED
    TEST_SCRIPT_WARNING("Instrumentation has been disabled\n");
#else
    ANALYSIS_CHECK("100% Entry Point Coverage",
                   cppca_entrypoint_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Statement Coverage",
                   cppca_statement_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Decision Coverage",
                   cppca_decision_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Boolean Operand Effectiveness Coverage",
                   cppca_booleff_cov,
                   100.0);
    
    REPORT_COVERAGE(cppca_entrypoint_cov|
                    cppca_statement_cov|
                    cppca_decision_cov|
                    cppca_booleff_cov,
                    cppca_sut,
                    cppca_all_details|cppca_include_catch,
                    cppca_context);
#endif
    END_TEST();
}

/*****************************************************************************/
/* Program Entry Point                                                       */
/*****************************************************************************/
int main()
{
    CONFIGURE_COVERAGE("cov:boolcomb:yes");
    OPEN_LOG("ut_rbl_SigChain_Main.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_Main", true);

    WRITE_LOG(" * ------------------- TEST SUITE OF rbl_SigChain_Main -------------------*", cppth_ll_minimal,true);
	WRITE_LOG(" * -----------------PROJECT: MMP2 ------ SOFTWARE: ASW------------------ * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ------------------ LAST SCRIPT UPDATE: 12/12/2023 ------------------- * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT IMPLEMENTED BY:MAJ3BRG --- TEST RUN PERFORMED BY MAJ3BRG --- *", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT REWORKED BY: MAJ3BRG ----- TEST RUN PERFORMED BY: MAJ3BRG --- *",cppth_ll_minimal,true);
	WRITE_LOG(" * -------------------------TEST SUITE ID: 1443 ------------------------- *", cppth_ll_minimal,true);

    run_tests();

    return !END_SCRIPT(true);
}

/*****************************************************************************/
/* Test Control                                                              */
/*****************************************************************************/
/* run_tests() contains calls to the individual test cases, you can turn test*/
/* cases off by adding comments*/
void run_tests()
{
    ut_rbl_SigChain_Proc(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_Main.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChain_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("47488: [MMP2.11]UTC_rbl_SigChain_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47488");

		int i = 0, j = 0;

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS | EXPECTED RESULTS
			initialise_aux_structures();
			initialise_source_structures();

			// --- SigChain Active ---
			rbl_SignalChainActive = RBL_IMU_CHMAP | RBL_IMU_TCOS |  RBL_IMU_ALGN |  RBL_IMU_SIGFIL;
			expected_rbl_SignalChainActive = rbl_SignalChainActive;

			// --- SwTestMod ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = rbl_SignalChainActive;
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod);

			// --- Signal valid? ---
			RBMESG_SigChain_stValid = FALSE;
			expected_RBMESG_SigChain_stValid = RBMESG_SigChain_stValid;

			// --- SIGNALS ---
			for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				// --- Acc ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SmxChannels.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).acc[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetChMap.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
				}

				// --- Rate ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SmxChannels.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).rate[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetChMap.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
				}
			}

			// --- Temp ---
			for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
			{
				// --- SigFil ---
				RBMESG_SigChain_SigSetSigFil.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigFil.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- SigDer ---
				RBMESG_SigChain_SigSetSigDer.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigDer.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- ImuCDD_SmxChannelSet ---
				RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i];
				// --- SmxChannels ---
				RBMESG_SigChain_SmxChannels.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SmxChannels.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).temp[i];
				// --- SigSetChMap ---
				RBMESG_SigChain_SigSetChMap.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetChMap.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- TCOS ---
				RBMESG_SigChain_SigSetTCOS.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetTCOS.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- Algn ---
				RBMESG_SigChain_SigSetAlgn.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetAlgn.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
			}

			// --- Timestamp ---
				// --- SigFil ---
			RBMESG_SigChain_SigSetSigFil.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigFil.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- SigDer ---
			RBMESG_SigChain_SigSetSigDer.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigDer.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- ImuCDD_SmxChannelSet ---
			RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp;
				// --- SmxChannels ---
			RBMESG_SigChain_SmxChannels.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SmxChannels.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).timeStamp;
				// --- SigSetChMap ---
			RBMESG_SigChain_SigSetChMap.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetChMap.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- TCOS ---
			RBMESG_SigChain_SigSetTCOS.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetTCOS.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- Algn ---
			RBMESG_SigChain_SigSetAlgn.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetAlgn.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;


#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_1;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_2;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_3;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChainChMap#Proc_ChMap_TS1;\
							rbl_SigChain_TCOS#Proc_TCOS_TS1;\
							rbl_SigChainAlgn#Proc_Algn_TS1;\
							rbl_SigChainSigFil#Proc_SigFil_TS1_1;\
							rbl_SigChainSigFil#Proc_SigFil_TS1_2;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_1;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_2;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_3;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;");

#else
			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_1;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_2;\
							rbl_SigChain_addStatusSmx#Proc_addStatusSmx_TS1_3;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChainChMap#Proc_ChMap_TS1;\
							rbl_SigChain_TCOS#Proc_TCOS_TS1;\
							rbl_SigChainAlgn#Proc_Algn_TS1;\
							rbl_SigChainSigFil#Proc_SigFil_TS1_1;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_1;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_2;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS1_3;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;");
#endif

			// CALL SUT
			rbl_SigChain_Proc();

			// EXPECTED RESULTS
			check_global_data();

			END_CALLS();
		}
		END_STEP();

		START_STEP("2_NTS", TRUE);
		{
			int i = 0, j = 0;

			// INITIAL CONDITIONS | EXPECTED RESULTS
			initialise_aux_structures();
			initialise_source_structures();

			// --- SigChain Active ---
			rbl_SignalChainActive = 0;
			expected_rbl_SignalChainActive = rbl_SignalChainActive;

			// --- SwTestMod ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = rbl_SignalChainActive;
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod);

			// --- Signal valid? ---
			RBMESG_SigChain_stValid = TRUE;
			expected_RBMESG_SigChain_stValid = RBMESG_SigChain_stValid;

			// --- SIGNALS ---
			for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				// --- Acc ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SmxChannels.acc[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetChMap.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
				}

				// --- Rate ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SmxChannels.rate[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetChMap.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
				}
			}

			// --- Temp ---
			for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
			{
				// --- SigFil ---
				RBMESG_SigChain_SigSetSigFil.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigFil.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- SigDer ---
				RBMESG_SigChain_SigSetSigDer.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigDer.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- ImuCDD_SmxChannelSet ---
				RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i];
				// --- SmxChannels ---
				RBMESG_SigChain_SmxChannels.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SmxChannels.temp[i] = RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i];
				// --- SigSetChMap ---
				RBMESG_SigChain_SigSetChMap.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetChMap.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- TCOS ---
				RBMESG_SigChain_SigSetTCOS.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetTCOS.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- Algn ---
				RBMESG_SigChain_SigSetAlgn.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetAlgn.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
			}

			// --- Timestamp ---
				// --- SigFil ---
			RBMESG_SigChain_SigSetSigFil.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigFil.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- SigDer ---
			RBMESG_SigChain_SigSetSigDer.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigDer.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- ImuCDD_SmxChannelSet ---
			RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp;
				// --- SmxChannels ---
			RBMESG_SigChain_SmxChannels.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SmxChannels.timeStamp = RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp;
				// --- SigSetChMap ---
			RBMESG_SigChain_SigSetChMap.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetChMap.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- TCOS ---
			RBMESG_SigChain_SigSetTCOS.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetTCOS.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- Algn ---
			RBMESG_SigChain_SigSetAlgn.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetAlgn.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;


			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChain_setAxesZero#Proc_setAxesZero_TS2;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS2;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;");

			// CALL SUT
			rbl_SigChain_Proc();


			// EXPECTED RESULTS
			check_global_data();


			END_CALLS();
		}
		END_STEP();

		START_STEP("3_NTS", TRUE);
		{
			int i = 0, j = 0;

			// INITIAL CONDITIONS | EXPECTED RESULTS
			initialise_aux_structures();
			initialise_source_structures();

			// --- SigChain Active ---
			rbl_SignalChainActive = RBL_IMU_TCOS |  RBL_IMU_ALGN;
			expected_rbl_SignalChainActive = rbl_SignalChainActive;

			// --- SwTestMod ---
			ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = rbl_SignalChainActive;
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod) = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_SwtTestMod);

			// --- Signal valid? ---
			RBMESG_SigChain_stValid = TRUE;
			expected_RBMESG_SigChain_stValid = RBMESG_SigChain_stValid;

			// --- SIGNALS ---
			for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				// --- Acc ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).acc[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.acc[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SmxChannels.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).acc[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetChMap.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.acc[i][j] = Aux_ImuSignalSet.acc[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.acc[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).acc[i][j];
				}

				// --- Rate ---
				for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					// --- SigFil ---
					RBMESG_SigChain_SigSetSigFil.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigFil.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- SigDer ---
					RBMESG_SigChain_SigSetSigDer.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetSigDer.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).rate[i][j];
					// --- ImuCDD_SmxChannelSet ---
					RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j] = RBMESG_rbl_ImuCdd_SmxChannelSet.rate[i][j];
					// --- SmxChannels ---
					RBMESG_SigChain_SmxChannels.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SmxChannels.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).rate[i][j];
					// --- SigSetChMap ---
					RBMESG_SigChain_SigSetChMap.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetChMap.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- TCOS ---
					RBMESG_SigChain_SigSetTCOS.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetTCOS.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
					// --- Algn ---
					RBMESG_SigChain_SigSetAlgn.rate[i][j] = Aux_ImuSignalSet.rate[i][j];
					expected_RBMESG_SigChain_SigSetAlgn.rate[i][j] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).rate[i][j];
				}
			}

			// --- Temp ---
			for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
			{
				// --- SigFil ---
				RBMESG_SigChain_SigSetSigFil.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigFil.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- SigDer ---
				RBMESG_SigChain_SigSetSigDer.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetSigDer.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).temp[i];
				// --- ImuCDD_SmxChannelSet ---
				RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i] = RBMESG_rbl_ImuCdd_SmxChannelSet.temp[i];
				// --- SmxChannels ---
				RBMESG_SigChain_SmxChannels.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SmxChannels.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).temp[i];
				// --- SigSetChMap ---
				RBMESG_SigChain_SigSetChMap.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetChMap.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- TCOS ---
				RBMESG_SigChain_SigSetTCOS.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetTCOS.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
				// --- Algn ---
				RBMESG_SigChain_SigSetAlgn.temp[i] = Aux_ImuSignalSet.temp[i];
				expected_RBMESG_SigChain_SigSetAlgn.temp[i] = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).temp[i];
			}

			// --- Timestamp ---
				// --- SigFil ---
			RBMESG_SigChain_SigSetSigFil.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigFil.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- SigDer ---
			RBMESG_SigChain_SigSetSigDer.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetSigDer.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset).timeStamp;
				// --- ImuCDD_SmxChannelSet ---
			RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp = RBMESG_rbl_ImuCdd_SmxChannelSet.timeStamp;
				// --- SmxChannels ---
			RBMESG_SigChain_SmxChannels.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SmxChannels.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjChannelSet).timeStamp;
				// --- SigSetChMap ---
			RBMESG_SigChain_SigSetChMap.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetChMap.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- TCOS ---
			RBMESG_SigChain_SigSetTCOS.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetTCOS.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;
				// --- Algn ---
			RBMESG_SigChain_SigSetAlgn.timeStamp = Aux_ImuSignalSet.timeStamp;
			expected_RBMESG_SigChain_SigSetAlgn.timeStamp = ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet).timeStamp;


			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;\
							rbl_SigChain_TCOS#Proc_TCOS_TS3;\
							rbl_SigChainAlgn#Proc_Algn_TS3;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS3_1;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS3_2;\
							rbl_SigChain_addStatusSignalSet#Proc_addStatusSignalSet_TS3_3;\
							RBSYS_EnterCommonLockSysfast#return;\
							RBSYS_ExitCommonLockSysfast#return;");


			// CALL SUT
			rbl_SigChain_Proc();


			// EXPECTED RESULTS
			check_global_data();


			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

void rbl_SigChain_TCOS(rbl_ImuStdTypes_ImuSignalSet_t * signalSet)
{
    REGISTER_CALL("rbl_SigChain_TCOS");

    IF_INSTANCE("Proc_TCOS_TS1")
    {
        return;
    }

    IF_INSTANCE("Proc_TCOS_TS3")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCommonLock_intern */
void RBSYS_EnterCommonLock_intern(){
    REGISTER_CALL("RBSYS_EnterCommonLock_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLock_intern */
void RBSYS_ExitCommonLock_intern(){
    REGISTER_CALL("RBSYS_ExitCommonLock_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCorelocalIntlock_intern */
void RBSYS_EnterCorelocalIntlock_intern(){
    REGISTER_CALL("RBSYS_EnterCorelocalIntlock_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlock_intern */
void RBSYS_ExitCorelocalIntlock_intern(){
    REGISTER_CALL("RBSYS_ExitCorelocalIntlock_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCommonLockSysfast_intern */
void RBSYS_EnterCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLockSysfast_intern */
void RBSYS_ExitCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCorelocalIntlockSysfast_intern */
void RBSYS_EnterCorelocalIntlockSysfast_intern(){
    REGISTER_CALL("RBSYS_EnterCorelocalIntlockSysfast_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlockSysfast_intern */
void RBSYS_ExitCorelocalIntlockSysfast_intern(){
    REGISTER_CALL("RBSYS_ExitCorelocalIntlockSysfast_intern");

    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_ImuCddIf_GetImuData */
void rbl_ImuCddIf_GetImuData(rbl_ImuStdTypes_SmxChannelSet_t * ImuData_ps){
    REGISTER_CALL("rbl_ImuCddIf_GetImuData");

    IF_INSTANCE("return")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChain_addStatusSmx */
void rbl_SigChain_addStatusSmx(rbl_ImuStdTypes_SmxChannelSet_t * ImuData,
                               uint8 status,
                               uint8 smx){
    REGISTER_CALL("rbl_SigChain_addStatusSmx");

    IF_INSTANCE("return")
    {
        return;
    }

    IF_INSTANCE("Proc_addStatusSmx_TS1_1")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
    	CHECK_U_INT(smx, 0);
        return;
    }

    IF_INSTANCE("Proc_addStatusSmx_TS1_2")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
    	CHECK_U_INT(smx, 1);
        return;
    }

    IF_INSTANCE("Proc_addStatusSmx_TS1_3")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
    	CHECK_U_INT(smx, 2);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChainTempMon */
void rbl_SigChainTempMon(rbl_ImuStdTypes_SmxChannelSet_t * ImuData)

		{
    REGISTER_CALL("rbl_SigChainTempMon");

    IF_INSTANCE("return")
    {
        return;
    }

    IF_INSTANCE("Proc_TempMon_TS1")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address

        return;
    }

    IF_INSTANCE("Proc_TempMon_TS3")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address

        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChainChMap */
void rbl_SigChainChMap(const rbl_ImuStdTypes_SmxChannelSet_t * smxSet,
                       rbl_ImuStdTypes_ImuSignalSet_t * signalSet){
    REGISTER_CALL("rbl_SigChainChMap");

    IF_INSTANCE("return")
    {
        return;
    }

    IF_INSTANCE("Proc_ChMap_TS1")
    {
    	// ImuData cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	// signalSet cannot be checked as sigSet is a local variable and it is impossible to obtain its address

        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChain_addStatusSignalSet */
void rbl_SigChain_addStatusSignalSet(rbl_ImuStdTypes_ImuSignalSet_t * signalSet,
                                     uint8 status){
    REGISTER_CALL("rbl_SigChain_addStatusSignalSet");

    IF_INSTANCE("return")
    {
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS1_1")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS1_2")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS1_3")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS2")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS3_1")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS3_2")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    IF_INSTANCE("Proc_addStatusSignalSet_TS3_3")
    {
    	// signalSet cannot be checked as channelSet is a local variable and it is impossible to obtain its address
    	CHECK_U_INT(status, RBL_IMUSTDTYPES_PRMNT_INVALID);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChainAlgn */
void rbl_SigChainAlgn(rbl_ImuStdTypes_ImuSignalSet_t * signalSet){
    REGISTER_CALL("rbl_SigChainAlgn");

    IF_INSTANCE("return")
    {
        return;
    }

	IF_INSTANCE("Proc_Algn_TS1")
	{
		// signalSet cannot be checked as sigSet is a local variable and it is impossible to obtain its address

		return;
	}

	IF_INSTANCE("Proc_Algn_TS3")
	{
		// signalSet cannot be checked as sigSet is a local variable and it is impossible to obtain its address

		return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChainSigFil */
void rbl_SigChainSigFil(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                        rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                        rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
						uint32 filterNumber)
{
    REGISTER_CALL("rbl_SigChainSigFil");

    IF_INSTANCE("return")
    {
        return;
    }

	IF_INSTANCE("Proc_SigFil_TS1_1")
	{
		CHECK_MEMORY("Checking variable signalSetRaw",signalSetRaw, &ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), sizeof(rbl_ImuStdTypes_ImuSignalSet_t));
		CHECK_MEMORY("Checking variable signalSetFil",signalSetFil, &ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), sizeof(rbl_ImuStdTypes_ImuSignalSet_t));
		CHECK_MEMORY("Checking variable signalSetDer",signalSetDer, &ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_emptySigset), sizeof(rbl_ImuStdTypes_ImuSignalSet_t));
		CHECK_U_INT(filterNumber, RBL_SIGCHAIN_FIRSTFILTER);

		return;
	}

	IF_INSTANCE("Proc_SigFil_TS1_2")
	{
		CHECK_MEMORY("Checking variable signalSetRaw",signalSetRaw, &ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), sizeof(rbl_ImuStdTypes_ImuSignalSet_t));
		CHECK_MEMORY("Checking variable signalSetFil",signalSetFil, &ACCESS_VARIABLE(rbl_SigChain_Main, rbl_SigChain_TestInjSigSet), sizeof(rbl_ImuStdTypes_ImuSignalSet_t));
		// Variable signalSetDer cannot be checked as it is a local variable that does not have an assigned value by the time the function is called
		CHECK_U_INT(filterNumber, RBL_SIGCHAIN_SECONDFILTER);

		return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChain_setAxesZero */
void rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet)
{
    REGISTER_CALL("rbl_SigChain_setAxesZero");

    IF_INSTANCE("default")
    {
        return;
    }

    IF_INSTANCE("Proc_setAxesZero_TS2")
    {
		// signalSet cannot be checked as sigSet is a local variable and it is impossible to obtain its address
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RBSYS_EnterCommonLockSysfast */
int BEFORE_RBSYS_EnterCommonLockSysfast(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast");

    IF_INSTANCE("return") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return REPLACE_WRAPPER;
}

/* After-Wrapper for function RBSYS_EnterCommonLockSysfast */
void AFTER_RBSYS_EnterCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_EnterCommonLockSysfast */
void REPLACE_RBSYS_EnterCommonLockSysfast()
{
	IF_INSTANCE("return")
	{
		return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCommonLockSysfast */
int BEFORE_RBSYS_ExitCommonLockSysfast(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast");

    IF_INSTANCE("return")
    {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return REPLACE_WRAPPER;
}

/* After-Wrapper for function RBSYS_ExitCommonLockSysfast */
void AFTER_RBSYS_ExitCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("return") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_ExitCommonLockSysfast */
void REPLACE_RBSYS_ExitCommonLockSysfast()
{
	IF_INSTANCE("return")
	{
		return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
