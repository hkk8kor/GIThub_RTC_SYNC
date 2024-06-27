/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
*    Filename: ut_rbl_SigChain_Invalidate.c
*    Author: MAJ3BRG
*    Generated on: 30-Jun-2020 12:35:06
*    Generated from: rbl_SigChain_Invalidate.c
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
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rbl_SigChain_addStatusSmx(rbl_ImuStdTypes_SmxChannelSet_t * ImuData, uint8 status, uint8 smx);
extern void rbl_SigChain_addStatusSignalSet(rbl_ImuStdTypes_ImuSignalSet_t * signalSet, uint8 status);
extern void rbl_SigChain_setSignalSetZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
extern void rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
extern void rbl_SigChain_invalidate(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);


/* Global data */
rbl_ImuStdTypes_ImuSignalSet_t global_signalSet;

/* Expected variables for global data */
rbl_ImuStdTypes_ImuSignalSet_t global_expected_signalSet;


/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChain_addStatusSmx(int);
void ut_rbl_SigChain_addStatusSignalSet(int);
void ut_rbl_SigChain_setSignalSetZero(int);
void ut_rbl_SigChain_setAxesZero(int);
//void ut_rbl_SigChain_invalidate(int);

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
    OPEN_LOG("ut_rbl_SigChain_Invalidate.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_Invalidate", true);

    WRITE_LOG(" * ----------------------TEST SUITE OF rbl_SigChain_Invalidate----------------------*", cppth_ll_minimal,true);
	WRITE_LOG(" * -----------------PROJECT: MMP2------ SOFTWARE: ASW------------------ * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ----TEST CAMPAGN RUN NUMBER 2.0-- LAST SCRIPT UPDATE: 27/07/2022 ---- * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT IMPLEMENTED BY:MAJ3BRG -- TEST RUN PERFORMED BY MAJ3BRG --- *", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT REWORKED BY: MAJ3BRG ----- TEST RUN PERFORMED BY: MAJ3BRG --- *",cppth_ll_minimal,true);
	WRITE_LOG(" * -------------------------TEST SUITE ID: 1381 ------------------------- *", cppth_ll_minimal,true);

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
    ut_rbl_SigChain_addStatusSmx(1);
    ut_rbl_SigChain_addStatusSignalSet(1);
    ut_rbl_SigChain_setSignalSetZero(1);
    ut_rbl_SigChain_setAxesZero(1);
//    ut_rbl_SigChain_invalidate(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_Invalidate.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/


void ut_rbl_SigChain_addStatusSmx(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_SmxChannelSet_t ImuData;
		rbl_ImuStdTypes_SmxChannelSet_t expected_ImuData;
		uint8 status = 0;
		int i, smx = 0;

		START_TEST("47483: [MMP2.11]UTC_rbl_SigChain_addStatusSmx",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47483");

		START_STEP("1_NTS", TRUE);
		{
			//Iterate for all possible values of variable "smx"
			for(smx = 0; smx < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; smx++)
			{
				//Initial conditions/ Expected results
				status = 3;	//Random value

				ImuData.temp[smx].status = 4;
				expected_ImuData.temp[smx].status = ImuData.temp[smx].status | status;

				for(i = 0; i < RBL_IMUSTDTYPES_NO_OF_ACC_PER_SMX; i++)
				{
					ImuData.acc[smx][i].status = 5;
					expected_ImuData.acc[smx][i].status = ImuData.acc[smx][i].status | status;
				}

				for(i = 0; i < RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX; i++)
				{
					ImuData.rate[smx][i].status = 6;
					expected_ImuData.rate[smx][i].status = ImuData.rate[smx][i].status | status;
				}

				// Expected Call Sequence
				EXPECT_CALL("", "", "");

				// Call SUT
				rbl_SigChain_addStatusSmx(&ImuData, status, smx);

				// Test case checks
				for(i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_SMX; i++)
				{
					CHECK_U_INT(ImuData.temp[smx].status, expected_ImuData.temp[smx].status);
				}

				for(i = 0; i < RBL_IMUSTDTYPES_NO_OF_ACC_PER_SMX; i++)
				{
					CHECK_U_INT(ImuData.acc[smx][i].status, expected_ImuData.acc[smx][i].status);
				}

				for(i = 0; i < RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX; i++)
				{
					CHECK_U_INT(ImuData.rate[smx][i].status, expected_ImuData.rate[smx][i].status);
				}

				END_CALLS();
			}
		}
		END_STEP();

		END_TEST();
	}
}

void ut_rbl_SigChain_addStatusSignalSet(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t signalSet;
		rbl_ImuStdTypes_ImuSignalSet_t expected_signalSet;
		uint8 status = 0;
		int i, j = 0;

		START_TEST("47484: [MMP2.11]UTC_rbl_SigChain_addStatusSignalSet",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47484");

		START_STEP("1_NTS", TRUE);
		{
			//Initial conditions/ Expected results
			status = 8;	//Random value

			for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					signalSet.acc[i][j].status = 3;
					expected_signalSet.acc[i][j].status = signalSet.acc[i][j].status | status;
				}
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					signalSet.rate[i][j].status = 4;
					expected_signalSet.rate[i][j].status = signalSet.rate[i][j].status |  status;
				}
			}

			// Expected Call Sequence
			EXPECT_CALL("", "", "");

			// Call SUT
			rbl_SigChain_addStatusSignalSet(&signalSet, status);

			// Test case checks
			for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					CHECK_U_INT(signalSet.acc[i][j].status, expected_signalSet.acc[i][j].status);
				}
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					CHECK_U_INT(signalSet.rate[i][j].status , expected_signalSet.rate[i][j].status );
				}
			}

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

void ut_rbl_SigChain_setSignalSetZero(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		int i = 0;

		START_TEST("47485: [MMP2.11]UTC_rbl_SigChain_setSignalSetZero",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47485");

		START_STEP("1_NTS", TRUE);
		{
			//Initial conditions/ Expected results
			for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
			{
				global_signalSet.temp[i].value = 3;	//Random value, must be different from zero
				global_expected_signalSet.temp[i].value = 0;	//Must be zero at the end
			}

			// Expected Call Sequence
			EXPECT_CALL("rbl_SigChain_setAxesZero", "1", "setSignalSetZero_setAxesZero");

			// Call SUT
			rbl_SigChain_setSignalSetZero(&global_signalSet);

			// Test case checks
			for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
			{
				CHECK_U_INT(global_signalSet.temp[i].value, global_expected_signalSet.temp[i].value);
			}

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

void ut_rbl_SigChain_setAxesZero(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t signalSet;
		rbl_ImuStdTypes_ImuSignalSet_t expected_signalSet;
		int i, j = 0;

		START_TEST("47486: [MMP2.11]UTC_rbl_SigChain_setAxesZero",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47486");

		START_STEP("1_NTS", TRUE);
		{
			//Initial conditions/ Expected results
		    for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
		    {
		        for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
		        {
		            signalSet.acc[i][j].value = 5.7;	//Random value, must be different from zero
		            expected_signalSet.acc[i][j].value = 0.0;
		        }
		        for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
		        {
		            signalSet.rate[i][j].value = 3.4;	//Random value, must be different from zero
		            expected_signalSet.rate[i][j].value = 0.0;
		        }
		    }

			// Expected Call Sequence
			EXPECT_CALL("", "", "");

			// Call SUT
			rbl_SigChain_setAxesZero(&signalSet);

			// Test case checks
			for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
				{
					CHECK_DOUBLE(signalSet.acc[i][j].value, expected_signalSet.acc[i][j].value);
				}
				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
				{
					CHECK_DOUBLE(signalSet.rate[i][j].value, expected_signalSet.rate[i][j].value);
				}
			}

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

//void ut_rbl_SigChain_invalidate(int doIt)
//{
//	if (doIt)
//	{
//		// Test case data declarations
//		rbl_ImuStdTypes_ImuSignalSet_t signalSet;
//		rbl_ImuStdTypes_ImuSignalSet_t expected_signalSet;
//		int i, j = 0;
//
//		START_TEST("47487: [MMP2.11]UTC_rbl_SigChain_invalidate",
//				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47487");
//
//		START_STEP("1_NTS", TRUE);
//		{
//			for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
//			{
//
//				signalSet.temp[i].status = RBL_IMUSTDTYPES_PRMNT_INVALID + 1;	//Must be different from RBL_IMUSTDTYPES_PRMNT_INVALID
//				signalSet.temp[i].smx = 5;	//Random value, must be different from zero
//
//				expected_signalSet.temp[i].status = RBL_IMUSTDTYPES_PRMNT_INVALID|RBL_IMUSTDTYPES_NOT_AVL;
//				expected_signalSet.temp[i].smx = RBL_IMUSTDTYPES_SMX_MISCONFIG;
//			}
//
//			for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
//			{
//				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
//				{
//					signalSet.acc[i][j].status = RBL_IMUSTDTYPES_PRMNT_INVALID + 1;	//Must be different from RBL_IMUSTDTYPES_PRMNT_INVALID
//					signalSet.acc[i][j].smx = 2.7;	//Random value, must be different from zero
//
//					expected_signalSet.acc[i][j].status = RBL_IMUSTDTYPES_PRMNT_INVALID|RBL_IMUSTDTYPES_NOT_AVL;
//					expected_signalSet.acc[i][j].smx = RBL_IMUSTDTYPES_SMX_MISCONFIG;
//				}
//				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
//				{
//					signalSet.rate[i][j].status = RBL_IMUSTDTYPES_PRMNT_INVALID + 1;	//Must be different from RBL_IMUSTDTYPES_PRMNT_INVALID
//					signalSet.rate[i][j].smx = 10.3;	//Random value, must be different from zero
//
//					expected_signalSet.rate[i][j].status = RBL_IMUSTDTYPES_PRMNT_INVALID|RBL_IMUSTDTYPES_NOT_AVL;
//					expected_signalSet.rate[i][j].smx = RBL_IMUSTDTYPES_SMX_MISCONFIG;
//				}
//			}
//
//			// Expected Call Sequence
//			EXPECT_CALL("", "", "");
//
//			// Call SUT
//			rbl_SigChain_invalidate(&signalSet);
//
//			// Test case checks
//			for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; i++)
//			{
//				CHECK_U_INT(signalSet.temp[i].status, expected_signalSet.temp[i].status);
//				CHECK_U_INT(signalSet.temp[i].smx, expected_signalSet.temp[i].smx);
//			}
//
//			for (i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
//			{
//				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; j++)
//				{
//					CHECK_U_INT(signalSet.acc[i][j].status, expected_signalSet.acc[i][j].status);
//					CHECK_DOUBLE(signalSet.acc[i][j].smx, expected_signalSet.acc[i][j].smx);
//				}
//				for (j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; j++)
//				{
//					CHECK_U_INT(signalSet.rate[i][j].status, expected_signalSet.acc[i][j].status);
//					CHECK_DOUBLE(signalSet.rate[i][j].smx, expected_signalSet.acc[i][j].smx);
//				}
//			}
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		END_TEST();
//	}
//}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/


#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChain_setAxesZero */
int BEFORE_rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet)
{
    REGISTER_CALL("rbl_SigChain_setAxesZero");

    IF_INSTANCE("default")
    {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("setSignalSetZero_setAxesZero")
	{
    	CHECK_U_INT((int) signalSet, (int) &global_signalSet);
		return REPLACE_WRAPPER;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_setAxesZero */
void AFTER_rbl_SigChain_setAxesZero(struct cppsm_void_return cppsm_dummy, rbl_ImuStdTypes_ImuSignalSet_t * signalSet)
{
    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_setAxesZero */
void REPLACE_rbl_SigChain_setAxesZero(rbl_ImuStdTypes_ImuSignalSet_t * signalSet)
{
    IF_INSTANCE("setSignalSetZero_setAxesZero")
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
