/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "CM_Basetypes_COMMON.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"
#include <math.h>

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/
rbl_ImuStdTypes_ImuSignalSet_t global_ImuSignalSet;
rbl_ImuStdTypes_ImuSignalSet_t global_expected_ImuSignalSet;
sint16 global_TPnts[RBL_IMUSTDTYPES_MAX_NO_OF_SMX][RBL_SIGCHAIN_ALGN_PNTS];
sint16 global_expected_TPnts[RBL_IMUSTDTYPES_MAX_NO_OF_SMX][RBL_SIGCHAIN_ALGN_PNTS];
sint16 global_OrthMtrxPnts[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
sint16 global_expected_OrthMtrxPnts[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];

/* Global Functions */
extern void rbl_SigChainAlgn(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
extern void ACCESS_FUNCTION_rbl_SigChain_Algn_rbl_SigChain_GetTempInterpOrthMtrx(float32(* orthMatrix)[3U], const rbl_ImuStdTypes_ImuSignalSet_t * ImuSignalSet, const sint16 * TPnts, const rbl_SigChain_AlgnMtrx_t * OrthMtrxSource, uint8 red, boolean isAcc);

sint16 Ifx_IntIpoCur_s16_s16(sint16 Xin, sint16 N, const sint16 * X_array, const sint16 * Val_array);

/* Global data */
extern rbl_SigChain_AlgnMtrx_t rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
extern rbl_SigChain_AlgnMtrx_t rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
typedef struct rbl_SigChain_Algn_av_struct { const sint16(* ref_rbl_SigChain_AlgnT)[3]; } rbl_SigChain_Algn_av_struct;
extern rbl_SigChain_Algn_av_struct av_rbl_SigChain_Algn;

/* Expected variables for global data */
rbl_SigChain_AlgnMtrx_t expected_rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
rbl_SigChain_AlgnMtrx_t expected_rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
typedef struct expected_rbl_SigChain_Algn_av_struct { sint16 ref_rbl_SigChain_AlgnT[3]; } expected_rbl_SigChain_Algn_av_struct;
expected_rbl_SigChain_Algn_av_struct expected_av_rbl_SigChain_Algn;

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChainAlgn(int);
void ut_rbl_SigChain_GetTempInterpOrthMtrx(int);

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
    OPEN_LOG("ut_rbl_SigChain_Algn.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_Algn", true);

    WRITE_LOG(" * -------------------- TEST SUITE OF rbl_SigChain_Algn ------------------*", cppth_ll_minimal,true);
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
    ut_rbl_SigChainAlgn(1);
    ut_rbl_SigChain_GetTempInterpOrthMtrx(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_Algn.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChainAlgn(int doIt)
{
	if (doIt)
	{
		/* Test case data declarations */
		int row, column, red = 0;

		START_TEST("47472: UTC_rbl_SigChainAlgn",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47472");

		START_STEP("1_NTS", true);
		{
			for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					global_ImuSignalSet.acc[column][red].value = 7;
					global_ImuSignalSet.acc[column][red].status = 8;

					global_expected_ImuSignalSet.acc[column][red].value = 4 * global_ImuSignalSet.acc[column][red].value;	//Must remain unchanged
					global_expected_ImuSignalSet.acc[column][red].status = 8;	//Must remain unchanged
				}
			}


			for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					global_ImuSignalSet.rate[column][red].value = 9;
					global_ImuSignalSet.rate[column][red].status = 10;

					global_expected_ImuSignalSet.rate[column][red].value = 4 * global_ImuSignalSet.rate[column][red].value;	//Must remain unchanged
					global_expected_ImuSignalSet.rate[column][red].status = 10;	//Must remain unchanged
				}
			}

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS1_1;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS1;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS1_2;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS1;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS1_3;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS1;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS1_5;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS1;");

			// Call SUT
			rbl_SigChainAlgn(&global_ImuSignalSet);

			// Test case checks
			for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					CHECK_DOUBLE(global_ImuSignalSet.acc[column][red].value, global_expected_ImuSignalSet.acc[column][red].value);
					CHECK_U_INT(global_ImuSignalSet.acc[column][red].status, global_expected_ImuSignalSet.acc[column][red].status);
				}
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					CHECK_DOUBLE(global_ImuSignalSet.rate[column][red].value, global_expected_ImuSignalSet.rate[column][red].value);
					CHECK_U_INT(global_ImuSignalSet.rate[column][red].status, global_expected_ImuSignalSet.rate[column][red].status);
				}
			}

			END_CALLS();
		}
		END_STEP();


		START_STEP("2_NTS", true);
		{
			for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
			{
				for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
				{
					global_ImuSignalSet.acc[column][red].value = 13;
					global_ImuSignalSet.acc[column][red].status = 0;

					global_expected_ImuSignalSet.acc[column][red].value = global_ImuSignalSet.acc[column][red].value;	//Must remain unchanged because multiplier is 0
					global_expected_ImuSignalSet.acc[column][red].status = global_ImuSignalSet.acc[column][red].status;
				}
			}

			for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
			{
				for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
				{
					global_ImuSignalSet.acc[column][red].value = 10;
					global_ImuSignalSet.acc[column][red].status = 0;

					global_expected_ImuSignalSet.acc[column][red].value = global_ImuSignalSet.acc[column][red].value;	//Must remain unchanged because multiplier is 0
					global_expected_ImuSignalSet.acc[column][red].status = global_ImuSignalSet.acc[column][red].status;
				}
			}

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS2_1;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS2;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS2_2;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS2;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS2_3;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS2;\
							rbl_SigChain_GetTempInterpOrthMtrx#rbl_SigChain_GetTempInterpOrthMtrx_TS2_5;\
							9*__fpclassifyf#SigChainAlgn_fpclassify_TS2;");


			// Call SUT
			rbl_SigChainAlgn(&global_ImuSignalSet);

			// Test case checks
			for(column = 0; column < RBL_IMUSTDTYPES_AXIS_NO; column++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					CHECK_DOUBLE(global_ImuSignalSet.acc[column][red].value, global_expected_ImuSignalSet.acc[column][red].value);
					CHECK_U_INT(global_ImuSignalSet.acc[column][red].status, global_expected_ImuSignalSet.acc[column][red].status);
				}
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					CHECK_DOUBLE(global_ImuSignalSet.rate[column][red].value, global_expected_ImuSignalSet.rate[column][red].value);
					CHECK_U_INT(global_ImuSignalSet.rate[column][red].status, global_expected_ImuSignalSet.rate[column][red].status);
				}
			}


			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

void ut_rbl_SigChain_GetTempInterpOrthMtrx(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		int i, j, k, column, row = 0;

		boolean isAcc = FALSE;
		int red = 0;
		float32 orthMatrix[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO];

		float32 expected_orthMatrix[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO];

		START_TEST("47473: UTC_rbl_SigChain_GetTempInterpOrthMtrx",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47473");

		// Acc
		START_STEP("1_NTS", TRUE);
		{
			//Initial conditions / Expected results
			boolean isAcc = TRUE;
			red = 0;

			for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				global_ImuSignalSet.temp[i].value = i;

				for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
				{
					global_ImuSignalSet.acc[i][j].smx = RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1;
					orthMatrix[j][i] = 0;

					expected_orthMatrix[j][i] = 5 * RBL_SIGCHAIN_MTRX; //5 is the value the stub returns

					for(int k = 0; k < RBL_SIGCHAIN_ALGN_PNTS; k++)
					{
						global_OrthMtrxPnts[i][j][k] = 3;

						global_expected_OrthMtrxPnts[i][j][k] = global_OrthMtrxPnts[i][j][k];	// Must remain unchanged
					}
				}
			}

			global_expected_ImuSignalSet = global_ImuSignalSet;	//Must remain unchanged

			for(column = 0; column < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; column++)
			{
				for(row = 0; row < RBL_SIGCHAIN_ALGN_PNTS; row++)
				{
					global_TPnts[column][row] = 2;

					global_expected_TPnts[column][row] = global_TPnts[column][row];		// Must remain unchanged
				}
			}


			// Expected Call Sequence
			EXPECTED_CALLS("Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_1;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_2;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_3;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_4;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_5;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_6;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_7;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_8;\
							Ifx_IntIpoCur_s16_s16#GetTempInterpOrthMtrx_IntIpoCur_TS1_9;");


			// Call SUT
			ACCESS_FUNCTION(rbl_SigChain_Algn, rbl_SigChain_GetTempInterpOrthMtrx)(orthMatrix, &global_ImuSignalSet, global_TPnts, global_OrthMtrxPnts, red, isAcc);


			// Test case checks
			CHECK_MEMORY("Checking ImuSignalSet", &global_ImuSignalSet, &global_expected_ImuSignalSet, sizeof(global_ImuSignalSet));
			CHECK_MEMORY("Checking TPnts", global_TPnts, global_expected_TPnts, sizeof(global_TPnts));
			CHECK_MEMORY("Checking OrthMtrxPnts", global_OrthMtrxPnts, global_expected_OrthMtrxPnts, sizeof(global_OrthMtrxPnts));
			CHECK_MEMORY("Checking orthMatrix", orthMatrix, expected_orthMatrix, sizeof(orthMatrix));

			END_CALLS();
		}
		END_STEP();

		// Rate
		START_STEP("2_NTS", TRUE);
		{
			//Initial conditions / Expected results
			boolean isAcc = FALSE;
			red = 0;

			for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
				{
					global_ImuSignalSet.rate[i][j].smx = RBL_IMUSTDTYPES_MAX_NO_OF_SMX + 1;
					orthMatrix[j][i] = 1;

					expected_orthMatrix[j][i] = 0;
				}
			}

			global_expected_ImuSignalSet = global_ImuSignalSet;	//Must remain unchanged


			// Expected Call Sequence
			EXPECTED_CALLS("");


			// Call SUT
			ACCESS_FUNCTION(rbl_SigChain_Algn, rbl_SigChain_GetTempInterpOrthMtrx)(orthMatrix, &global_ImuSignalSet, global_TPnts, global_OrthMtrxPnts, red, isAcc);



			// Test case checks
			CHECK_MEMORY("Checking ImuSignalSet", &global_ImuSignalSet, &global_expected_ImuSignalSet, sizeof(global_ImuSignalSet));
			CHECK_MEMORY("Checking TPnts", global_TPnts, global_expected_TPnts, sizeof(global_TPnts));
			CHECK_MEMORY("Checking OrthMtrxPnts", global_OrthMtrxPnts, global_expected_OrthMtrxPnts, sizeof(global_OrthMtrxPnts));
			CHECK_MEMORY("Checking orthMatrix", orthMatrix, expected_orthMatrix, sizeof(orthMatrix));

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/


/* Stub for function Ifx_IntIpoCur_s16_s16 */
sint16 Ifx_IntIpoCur_s16_s16(sint16 Xin,
                             sint16 N,
                             const sint16 * X_array,
                             const sint16 * Val_array)
{
    REGISTER_CALL("Ifx_IntIpoCur_s16_s16");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("default")
	{
		return 0;
	}

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_1")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[0][0][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_2")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[1][0][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_3")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[2][0][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_4")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[0][1][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_5")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[1][1][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_6")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[2][1][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_7")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[0][2][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_8")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[1][2][0] );
        return 5;
    }

    IF_INSTANCE("GetTempInterpOrthMtrx_IntIpoCur_TS1_9")
    {
    	CHECK_S_INT(Xin, global_ImuSignalSet.temp[RBL_IMUSTDTYPES_MAX_NO_OF_SMX - 1].value);
    	CHECK_S_INT(N, RBL_SIGCHAIN_ALGN_PNTS);
    	CHECK_MEMORY("Checking TPnts", (int) X_array, global_TPnts, sizeof(global_TPnts));
    	CHECK_U_INT((int) Val_array, (int) &global_OrthMtrxPnts[2][2][0] );
        return 5;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function __fpclassify */
__cdecl int __fpclassify(double param_1)
{
    REGISTER_CALL("__fpclassify");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("SigChainAlgn_fpclassify_TS1")
    {
    	// Variable param_1 cannot be checked as it is a local variable
        return 0;
    }

    IF_INSTANCE("SigChainAlgn_fpclassify_TS2")
    {
    	// Variable param_1 cannot be checked as it is a local variable
        return 0;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function __fpclassifyf */
__cdecl int __fpclassifyf(float param_1){
    REGISTER_CALL("__fpclassifyf");

    IF_INSTANCE("default") {
        return 0;
    }

    IF_INSTANCE("SigChainAlgn_fpclassify_TS1")
    {
    	// Variable param_1 cannot be checked as it is a local variable
        return !FP_ZERO;
    }

    IF_INSTANCE("SigChainAlgn_fpclassify_TS2")
    {
    	// Variable param_1 cannot be checked as it is a local variable
        return FP_ZERO;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function __fpclassifyl */
__cdecl int __fpclassifyl(long double param_1){
    REGISTER_CALL("__fpclassifyl");

    IF_INSTANCE("default") {
        return 0;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChain_GetTempInterpOrthMtrx */
int BEFORE_rbl_SigChain_GetTempInterpOrthMtrx(float32(* orthMatrix)[3U],
                                              rbl_ImuStdTypes_ImuSignalSet_t * ImuSignalSet,
                                              sint16(* TPnts)[3],
                                              sint16(* OrthMtrx)[3U][3],
                                              uint8 red,
                                              boolean isAcc)
{
    REGISTER_CALL("rbl_SigChain_GetTempInterpOrthMtrx");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_1")
	{
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 0);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_2")
	{
    	//Parameter check
    	//Variable "orthMatrix" cannot be checked because it is local
    	//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 1);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_3")
	{
    	//Parameter check
    	//Variable "orthMatrix" cannot be checked because it is local
    	//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 2);
		CHECK_BOOLEAN(isAcc, TRUE);


		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_4")
	{
    	//Parameter check
    	//Variable "orthMatrix" cannot be checked because it is local
    	//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 3);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_5")
	{
    	//Parameter check
    	//Variable "orthMatrix" cannot be checked because it is local
    	//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 0);
		CHECK_BOOLEAN(isAcc, FALSE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_6")
	{
    	//Parameter check
    	//Variable "orthMatrix" cannot be checked because it is local
    	//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 1);
		CHECK_BOOLEAN(isAcc, FALSE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_1")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 0);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_2")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 1);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_3")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 2);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_4")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 3);
		CHECK_BOOLEAN(isAcc, TRUE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_5")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 0);
		CHECK_BOOLEAN(isAcc, FALSE);

		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_6")
	{
    	//Parameter check
		//Variable "orthMatrix" cannot be checked because it is local
		//Variable "ImuSignalSet" cannot be checked because it is local
    	CHECK_MEMORY("Checking TPnts", TPnts, ACCESS_VARIABLE(rbl_SigChain_Algn , rbl_SigChain_AlgnT), sizeof(TPnts));
    	CHECK_MEMORY("Checking TPnts", OrthMtrx, rbl_SigChain_AlgnAccOrthMtrx, sizeof(OrthMtrx));
		CHECK_U_INT(red, 1);
		CHECK_BOOLEAN(isAcc, FALSE);

		return REPLACE_WRAPPER;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_GetTempInterpOrthMtrx */
void AFTER_rbl_SigChain_GetTempInterpOrthMtrx(struct cppsm_void_return cppsm_dummy,
                                              float32(* orthMatrix)[3U],
                                              rbl_ImuStdTypes_ImuSignalSet_t * ImuSignalSet,
                                              sint16(* TPnts)[3],
                                              sint16(* OrthMtrx)[3U][3],
                                              uint8 red,
                                              boolean isAcc){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_GetTempInterpOrthMtrx */
void REPLACE_rbl_SigChain_GetTempInterpOrthMtrx(float32(* orthMatrix)[3U],
                                                rbl_ImuStdTypes_ImuSignalSet_t * ImuSignalSet,
                                                sint16(* TPnts)[3],
                                                sint16(* OrthMtrx)[3U][3],
                                                uint8 red,
                                                boolean isAcc)
{
    IF_INSTANCE("default")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_1")
	{
    	int i, j = 0;

		//Variable manipulation
    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_2")
	{
    	int i, j, k, l = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_3")
	{
    	int i, j = 0;

    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_4")
	{
    	int i, j = 0;

    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_5")
	{
    	int i, j = 0;

    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

    IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS1_6")
	{
    	int i, j = 0;

    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 1;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_1")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_2")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_3")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_4")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_5")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

		return;
	}

	IF_INSTANCE("rbl_SigChain_GetTempInterpOrthMtrx_TS2_6")
	{
    	int i, j = 0;


    	for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				orthMatrix[i][j] = 0;
			}
		}

    	for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
		{
			for(j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
			{
				ImuSignalSet->acc[j][i].value = 2;
				ImuSignalSet->acc[j][i].status = 4;
			}
		}

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
