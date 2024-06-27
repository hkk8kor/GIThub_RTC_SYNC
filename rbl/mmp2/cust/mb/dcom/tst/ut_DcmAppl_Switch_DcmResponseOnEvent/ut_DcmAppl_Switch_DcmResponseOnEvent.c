/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_Switch_DcmResponseOnEvent.c
 *    Author: VQQ1KOR
 *    Generated on: 06-Nov-2022 12:34:28
 *    Generated from: DcmAppl_Switch_DcmResponseOnEvent.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "DcmDspUds_Roe_Inf.h"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))
extern void DcmAppl_Switch_DcmResponseOnEvent(uint8 RoeEventId_u8, Dcm_DspRoeEventState_ten RoeEventStatus_en);
#endif

/* Prototypes for test functions */
void run_tests();
#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))
void ut_DcmAppl_Switch_DcmResponseOnEvent(int);
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
    OPEN_LOG("ut_DcmAppl_Switch_DcmResponseOnEvent.ctr", false, 100);
    START_SCRIPT("DcmAppl_Switch_DcmResponseOnEvent", true);

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
#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

	ut_DcmAppl_Switch_DcmResponseOnEvent(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_Switch_DcmResponseOnEvent.cov", cppca_export_replace);
#endif
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

void ut_DcmAppl_Switch_DcmResponseOnEvent(int doIt){
if (doIt) {

    /* Test case data declarations */
    Dcm_DspRoeEventState_ten RoeEventStatus_en = 0;

    START_TEST("48832: [MMP2.1x] UTC_dcom_cubas_DcmAppl_Switch_DcmResponseOnEvent",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48832");

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            DcmAppl_Switch_DcmResponseOnEvent(0, RoeEventStatus_en);

        END_CALLS();
    END_TEST();
}}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
