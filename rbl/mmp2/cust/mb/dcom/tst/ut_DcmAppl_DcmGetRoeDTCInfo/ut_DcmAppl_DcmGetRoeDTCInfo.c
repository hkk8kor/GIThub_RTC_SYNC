/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmGetRoeDTCInfo.c
 *    Author: VQQ1KOR
 *    Generated on: 12-Nov-2022 12:41:20
 *    Generated from: DcmAppl_DcmGetRoeDTCInfo.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "DcmDspUds_Roe_Inf.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
extern FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRoeDTCInfo(VAR(uint8,AUTOMATIC)  RoeeventID,
                                                P2VAR(Dcm_DspRoeEventState_ten,AUTOMATIC,DCM_INTERN_DATA) RoeEventStatus,
                                                P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) RoeEventWindowTime_u8,
                                                P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA)  SourceAddress,
                                                P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) StatusMask,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeCtrlStorageState_b,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeSetUpStorageState_b,
                                                P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) dspRoeSession_b);
#endif
#endif


/* Prototypes for test functions */
void run_tests();
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_DcmGetRoeDTCInfo(int);
#endif
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
    OPEN_LOG("ut_DcmAppl_DcmGetRoeDTCInfo.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmGetRoeDTCInfo", true);

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
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
    ut_DcmAppl_DcmGetRoeDTCInfo(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmGetRoeDTCInfo.cov", cppca_export_replace);
#endif
#endif
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_DcmGetRoeDTCInfo(int doIt){
if (doIt) {

    START_TEST("48795:[MMP2.1x] UTC_dcom_cubas_DcmAppl_DcmGetRoeDTCInfo",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48795");

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

			VAR(uint8,AUTOMATIC)  RoeeventID = 0;
            P2VAR(Dcm_DspRoeEventState_ten,AUTOMATIC,DCM_INTERN_DATA) RoeEventStatus = 0;
            P2VAR(uint8, AUTOMATIC,DCM_INTERN_DATA) RoeEventWindowTime_u8 = 0;
            P2VAR(uint16,AUTOMATIC,DCM_INTERN_DATA)  SourceAddress = 0;
            P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) StatusMask = 0;
            P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeCtrlStorageState_b = 0;
            P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA)  dspRoeSetUpStorageState_b = 0;
            P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) dspRoeSession_b = 0;

            /* Call SUT */
            Std_ReturnType retVal = DcmAppl_DcmGetRoeDTCInfo(RoeeventID, RoeEventStatus, RoeEventWindowTime_u8, SourceAddress, StatusMask, dspRoeCtrlStorageState_b, dspRoeSetUpStorageState_b, dspRoeSession_b);

			CHECK_U_INT(retVal, E_OK);

        END_CALLS();
    END_TEST();
}}
#endif
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
