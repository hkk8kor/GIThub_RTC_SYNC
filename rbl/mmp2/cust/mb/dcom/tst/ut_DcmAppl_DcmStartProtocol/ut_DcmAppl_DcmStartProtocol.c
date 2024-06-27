/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmStartProtocol.c
 *    Author: VQQ1KOR
 *    Generated on: 05-Nov-2022 17:54:04
 *    Generated from: DcmAppl_DcmStartProtocol.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern Std_ReturnType DcmAppl_DcmStartProtocol(Dcm_ProtocolType ProtocolID);

/* Prototypes for test functions */
void run_tests();
void ut_DcmAppl_DcmStartProtocol(int);
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) rba_DiagAdapt_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID);
#endif
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
    OPEN_LOG("ut_DcmAppl_DcmStartProtocol.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmStartProtocol", true);

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
    ut_DcmAppl_DcmStartProtocol(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmStartProtocol.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_DcmAppl_DcmStartProtocol(int doIt){
if (doIt) {

    Std_ReturnType returnValue;

    START_TEST("48813: [MMP2.1x] UTC_dcom_DcmAppl_DcmStartProtocol",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48813");
    /* Expected Call Sequence  */
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    	EXPECTED_CALLS("rba_DiagAdapt_StartProtocol#001");
#else

        EXPECTED_CALLS("");
#endif

            /* Call SUT */
            returnValue = DcmAppl_DcmStartProtocol(0);

            /* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);

        END_CALLS();
    END_TEST();
}}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
/* Stub for function rba_DiagAdapt_StartProtocol */
FUNC(void,DCM_CODE) rba_DiagAdapt_StartProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID){
	REGISTER_CALL("rba_DiagAdapt_StartProtocol");


	IF_INSTANCE("001") {
		CHECK_U_CHAR(ProtocolID, 0);
		return;
	}

	LOG_SCRIPT_ERROR("Call instance not defined.");
	return;
}
#endif
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
