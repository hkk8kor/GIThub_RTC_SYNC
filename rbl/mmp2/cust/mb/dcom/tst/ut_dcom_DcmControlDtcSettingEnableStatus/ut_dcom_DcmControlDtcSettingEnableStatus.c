/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_DcmControlDtcSettingEnableStatus.c
 *    Author: GDEV1KOR
 *    Generated on: 11-Oct-2023 09:36:23
 *    Generated from: dcom_DcmControlDtcSettingEnableStatus.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"
#define DCM_START_SEC_CODE 
#include "Dcm_Cfg_MemMap.h"
#include "rbl_SwcDiagAdapter_Srv.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
void rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus(const boolean ControlDtcSettingEnableStatus);

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
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
void ut_DcmAppl_DcmControlDtcSettingEnableStatus(int);
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
    OPEN_LOG("ut_dcom_DcmControlDtcSettingEnableStatus.ctr", false, 100);
    START_SCRIPT("dcom_DcmControlDtcSettingEnableStatus", true);

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
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
    ut_DcmAppl_DcmControlDtcSettingEnableStatus(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_DcmControlDtcSettingEnableStatus.cov", cppca_export_replace);
#endif
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
void ut_DcmAppl_DcmControlDtcSettingEnableStatus(int doIt){
if (doIt) {

    START_TEST("48789: [MMP2.11]UTC_DcmAppl_DcmControlDtcSettingEnableStatus",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48789");
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
        /* Expected Call Sequence  */
        EXPECTED_CALLS("rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus#default");
#endif
            VAR(boolean,AUTOMATIC) ControlDtcSettingEnableStatus = 0;

            /* Call SUT */
            DcmAppl_DcmControlDtcSettingEnableStatus(ControlDtcSettingEnableStatus);

        END_CALLS();
    END_TEST();
}}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
/* Stub for function rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus */
void rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus(const boolean ControlDtcSettingEnableStatus){
    REGISTER_CALL("rbl_SwcDiagAdapter_DcmControlDtcSettingEnableStatus");

    IF_INSTANCE("default") {
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
