/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmClearRoeEventInformation.c
 *    Author: GDEV1KOR
 *    Generated on: 26-May-2023 15:09:16
 *    Generated from: DcmAppl_DcmClearRoeEventInformation.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "DcmDspUds_Roe_Inf.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl.h"
#if( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
     (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
     (DCM_ROE_ENABLED != DCM_CFG_OFF))
#endif

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern FUNC (void, DCM_APPL_CODE) DcmAppl_DcmClearRoeEventInformation (void);

/* Global data */
/* None */

/* Expected variables for global data */
/* None */

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No global data */
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    /* No global data */
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    /* No global data */
}

/* Prototypes for test functions */
void run_tests();
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
     (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
     (DCM_ROE_ENABLED != DCM_CFG_OFF))
void ut_DcmAppl_DcmClearRoeEventInformation(int);
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
    OPEN_LOG("ut_DcmAppl_DcmClearRoeEventInformation.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmClearRoeEventInformation", true);

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
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
    (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
    (DCM_ROE_ENABLED != DCM_CFG_OFF))
   ut_DcmAppl_DcmClearRoeEventInformation(1);
#endif
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmClearRoeEventInformation.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
     (DCM_CFG_DSP_CLEARDIAGNOSTICINFORMATION_ENABLED != DCM_CFG_OFF) && \
     (DCM_ROE_ENABLED != DCM_CFG_OFF))
void ut_DcmAppl_DcmClearRoeEventInformation(int doIt){
if (doIt) {

    START_TEST("48785: [MMP2.1x] UTC_dcom_cubas_DcmAppl_DcmClearRoeEventInformation",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48785");
        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            DcmAppl_DcmClearRoeEventInformation();

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
