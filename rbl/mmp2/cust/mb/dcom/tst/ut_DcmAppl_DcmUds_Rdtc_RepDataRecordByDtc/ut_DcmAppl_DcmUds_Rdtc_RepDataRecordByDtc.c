/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc.c
 *    Author: VQQ1KOR
 *    Generated on: 05-Nov-2022 18:37:09
 *    Generated from: DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/app/dcom/src/cubas/DcmAppl.h"
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
/* None */

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
    OPEN_LOG("ut_DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc", true);

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

#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))

	ut_DcmAppl_DcmUds_Rdtc_RepDataRecordByDTC(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc.cov", cppca_export_replace);

#endif
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if((DCM_CFG_DSP_RDTCSUBFUNC_0x06_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_RDTCSUBFUNC_0x10_ENABLED != DCM_CFG_OFF) ||(DCM_CFG_DSP_RDTCSUBFUNC_0x19_ENABLED != DCM_CFG_OFF))
void ut_DcmAppl_DcmUds_Rdtc_RepDataRecordByDTC(int doIt){
if (doIt) {


    START_TEST("48818: [MMP2.1x] UTC_dcom_cubas_DcmAppl_DcmUds_Rdtc_RepDataRecordByDtc",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48818");

    VAR(uint8, DCM_VAR) s_dataRDTCSubFunc_u8 = 0xFF;
    VAR(uint32, DCM_VAR) RdtcDTC_u32 = 0xFFFFFFFF;
    VAR(uint8, DCM_VAR) DspRDTCRecordNum_u8	= 0xFF;

    uint16 Var_DspMaxResDataLen_u16 = 0xFFFF;
	uint16 *DspMaxResDataLen_u16 = &Var_DspMaxResDataLen_u16;

	VAR(uint32, DCM_VAR) dataFillRespLen_u32 = 0xFFFFFFFF;
	Dcm_MsgContextType Var_pMsgContext;

	Dcm_MsgContextType *pMsgContext = &Var_pMsgContext;

	Dcm_NegativeResponseCodeType Var_dataNegRespCode_u8 = 0x55;
	Dcm_NegativeResponseCodeType  *dataNegRespCode_u8 = &Var_dataNegRespCode_u8;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
        DcmAppl_DcmUds_Rdtc_RepDataRecordByDTC(s_dataRDTCSubFunc_u8, RdtcDTC_u32, DspRDTCRecordNum_u8, DspMaxResDataLen_u16, dataFillRespLen_u32, pMsgContext, dataNegRespCode_u8);

        CHECK_U_CHAR(*dataNegRespCode_u8, 0x55);
        END_CALLS();
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
