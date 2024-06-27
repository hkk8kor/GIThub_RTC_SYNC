/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rba_DcmPmaAppl_PlantModeActivation.c
 *    Author: BEE5LR
 *    Generated on: 09-Apr-2020 11:48:38
 *    Generated from: rba_DcmPmaAppl_PlantModeActivation.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rba_DcmPma.h"
#include "RBTSI_RbDiagInit.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rba_DcmPmaAppl_PlantModeActivation(boolean);


/* Prototypes for test functions */
void run_tests();
void ut_rba_DcmPmaAppl_PlantModeActivation(int);

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
    OPEN_LOG("ut_rba_DcmPmaAppl_PlantModeActivation.ctr", false, 100);
    START_SCRIPT("rba_DcmPmaAppl_PlantModeActivation", true);

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
    ut_rba_DcmPmaAppl_PlantModeActivation(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rba_DcmPmaAppl_PlantModeActivation.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rba_DcmPmaAppl_PlantModeActivation(int doIt){
if (doIt) {

    START_TEST("36334: UTC_dcom_common_rba_DcmPmaAppl_PlantModeActivation",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=36334");

		boolean stActive_b;

		START_STEP("1_NTS", true);

			/* Expected Call Sequence  */
			EXPECTED_CALLS("FUN_InitializeTSI_V#001");

			stActive_b = true;

            /* Call SUT */
            rba_DcmPmaAppl_PlantModeActivation(stActive_b);

			END_CALLS();
		END_STEP();
		START_STEP("2_NTS", true);

			/* Expected Call Sequence  */
			EXPECTED_CALLS("FUN_DiagExitInit_V#001");

			stActive_b = false;

            /* Call SUT */
            rba_DcmPmaAppl_PlantModeActivation(stActive_b);

			END_CALLS();
		END_STEP();
    END_TEST();
}}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function FUN_DiagExitInit_V */
void FUN_DiagExitInit_V(void){
    REGISTER_CALL("FUN_DiagExitInit_V");

    IF_INSTANCE("001") {
		return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function FUN_InitializeTSI_V */
void FUN_InitializeTSI_V(void){
    REGISTER_CALL("FUN_InitializeTSI_V");

    IF_INSTANCE("001") {
		return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
