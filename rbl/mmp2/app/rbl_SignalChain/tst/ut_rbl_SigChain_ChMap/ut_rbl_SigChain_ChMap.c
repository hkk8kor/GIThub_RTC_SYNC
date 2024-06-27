/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: Ut_rbl_SigChain_ChMap.c
 *    Author: maj3brg
 *    Generated on: 08-Feb-2023 16:42:30
 *    Generated from: rbl_SigChain_ChMap.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_ChMap.h"

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rbl_SigChainChMap(const rbl_ImuStdTypes_SmxChannelSet_t * smxSet, rbl_ImuStdTypes_ImuSignalSet_t * signalSet);

/* Global data */
typedef struct rbl_SigChain_ChMap_av_struct
{
	const rbl_SigChain_ChMap_t * ref_rbl_SigChain_ChMapSigSet;
} rbl_SigChain_ChMap_av_struct;
extern rbl_SigChain_ChMap_av_struct av_rbl_SigChain_ChMap;

/* Expected variables for global data */
typedef struct expected_rbl_SigChain_ChMap_av_struct
{
	rbl_SigChain_ChMap_t ref_rbl_SigChain_ChMapSigSet;
} expected_rbl_SigChain_ChMap_av_struct;
expected_rbl_SigChain_ChMap_av_struct expected_av_rbl_SigChain_ChMap;

/* Prototypes for test functions */
void run_tests();
void test_rbl_SigChainChMap(int);

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
    OPEN_LOG("Ut_rbl_SigChain_ChMap.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_ChMap", true);

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
    test_rbl_SigChainChMap(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("Ut_rbl_SigChain_ChMap.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void test_rbl_SigChainChMap(int doIt)
{
	if (doIt)
	{
		int i = 0, j = 0;
		rbl_ImuStdTypes_SmxChannelSet_t smxSet;
		rbl_ImuStdTypes_ImuSignalSet_t signalSet;
		rbl_ImuStdTypes_SmxChannelSet_t expected_smxSet;
		rbl_ImuStdTypes_ImuSignalSet_t expected_signalSet;

		START_TEST( "47475: UTC_rbl_SigChainChMap",
					"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47475");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS

			// --- smxSet ---
				for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_SMX; i++)
				{
					// --- ACC ---
					for (j=0; j< RBL_IMUSTDTYPES_NO_OF_ACC_PER_SMX; j++)
					{
						smxSet.acc[i][j].smx = 1;
						smxSet.acc[i][j].status = 2;
						smxSet.acc[i][j].value = 3;
					}
					// --- RATE ---
					for (j=0; j< RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX; j++)
					{
						smxSet.rate[i][j].smx = 4;
						smxSet.rate[i][j].status = 5;
						smxSet.rate[i][j].value = 6;
					}

					// --- TEMP ---
					smxSet.temp[i].smx = 7;
					smxSet.temp[i].status = 8;
					smxSet.temp[i].value = 9;
				}

				// --- TIMESTAMP ---
				smxSet.timeStamp = 10;

			// --- signalSet ---
				for (i=0; i< RBL_IMUSTDTYPES_AXIS_NO; i++)
				{
					// --- ACC ---
					for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
					{
						signalSet.acc[i][j].smx = 11;
						signalSet.acc[i][j].status = 12;
						signalSet.acc[i][j].value = 13;
					}
					// --- RATE ---
					for (j=0; j< RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
					{
						signalSet.rate[i][j].smx = 14;
						signalSet.rate[i][j].status = 15;
						signalSet.rate[i][j].value = 16;
					}
				}
				// --- TEMP ---
				for (i=0; i< RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
				{
					signalSet.temp[i].smx = 17;
					signalSet.temp[i].status = 18;
					signalSet.temp[i].value = 19;
				}

				// --- TIMESTAMP ---
				signalSet.timeStamp = 20;


			// EXPECTED RESULTS

			// --- smxSet ---
				expected_smxSet = smxSet;

			// --- signalSet ---
				expected_signalSet = signalSet;

				for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
				{
					// -- ACC --
					for(j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
					{
						expected_signalSet.acc[i][j] = smxSet.acc[ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).acc[i][j].smx][ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).acc[i][j].ch];

						// If there is value inversion for this signal
						if(ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).acc[i][j].invert != 0)
						{
							expected_signalSet.acc[i][j].value *= -1;
						}
					}

					// -- RATE --
					for(j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
					{
						expected_signalSet.rate[i][j] = smxSet.rate[ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).rate[i][j].smx][ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).rate[i][j].ch];

						// If there is value inversion for this signal
						if(ACCESS_VARIABLE(rbl_SigChain_ChMap, rbl_SigChain_ChMapSigSet).rate[i][j].invert != 0)
						{
							expected_signalSet.rate[i][j].value *= -1;
						}
					}
				}

				// --- TEMP ---
				for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; i++)
				{
					expected_signalSet.temp[i] = smxSet.temp[i];
				}
				// --- TIMESTAMP ---
				expected_signalSet.timeStamp = smxSet.timeStamp;


			// EXPECTED CALLS
			EXPECTED_CALLS("");


			// CALL SUT
			rbl_SigChainChMap(&smxSet, &signalSet);


			// EXPECTED RESULTS
			CHECK_MEMORY("Checking variable smxSet", &smxSet, &expected_smxSet, sizeof(smxSet));
			CHECK_MEMORY("Checking variable signalSet", &signalSet, &expected_signalSet, sizeof(signalSet));

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
