/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmSecaValidKey.c
 *    Author: VQQ1KOR
 *    Generated on: 05-Nov-2022 17:40:21
 *    Generated from: DcmAppl_DcmSecaValidKey.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from Call SUT */
#include "Nvm.h"
#include "Dcm.h"
#include "Dem.h"

#include "DcmDspUds_Seca_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */


extern Std_ReturnType DcmAppl_DcmSecaValidKey(VAR(uint8,AUTOMATIC) SecTabIdx);
/* Global data */


/* Expected variables for global data */


/* Prototypes for test functions */
void run_tests();
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
void ut_DcmAppl_DcmSecaValidKey(int);
#endif


/*****************************************************************************/
/* Coverage Analysis                                                         */
/*****************************************************************************/
/* Coverage Rule Set: Report all Metrics */
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
    OPEN_LOG("ut_DcmAppl_DcmSecaValidKey.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmSecaValidKey", true);

    // Write Test Suite information into the log and the report
    WRITE_LOG("*----------TEST SUITE OF PROGRAM : DcmAppl_DcmSecaValidKey---------*", cppth_ll_minimal,true);
    WRITE_LOG("*-----------------PROJECT: MMP2 ------ SOFTWARE: ASW------------------*", cppth_ll_minimal,true);
    WRITE_LOG("*----TEST CAMPAGN RUN NUMBER 2.0 -- LAST SCRIPT UPDATE: 10/06/2020----*", cppth_ll_minimal,true);
    WRITE_LOG("*---SCRIPT IMPLEMENTED BY: cah6abt -- TEST RUN PERFORMED BY cah6abt---*", cppth_ll_minimal,true);
    WRITE_LOG("*------SCRIPT REWORKED BY : cah6abt ------ TEST RUN PERFORMED BY: cah6abt---*",cppth_ll_minimal,true);
    WRITE_LOG("*-------------------------TEST SUITE ID: 948 --------------------------*", cppth_ll_minimal,true);


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
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
    ut_DcmAppl_DcmSecaValidKey(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmSecaValidKey.cov", cppca_export_replace);
#endif
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )
void ut_DcmAppl_DcmSecaValidKey(int doIt)
{
	if (doIt)
	{
		START_TEST("48810: [MMP2.1x] UTC_Dcom_DcmAppl_DcmSecaValidKey",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48810");

		START_STEP("NTS_1",TRUE);
		{
			// INITIAL CONDITIONS
			 Std_ReturnType returnValue;

			// EXPECTED CALLS
			EXPECTED_CALLS("");

			// CALL SUT
			returnValue = DcmAppl_DcmSecaValidKey(0);

			END_CALLS();

			// EXPECTED RESULTS
			CHECK_U_CHAR(returnValue, E_OK);
		}
		END_STEP();
		END_TEST();
	}
}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
