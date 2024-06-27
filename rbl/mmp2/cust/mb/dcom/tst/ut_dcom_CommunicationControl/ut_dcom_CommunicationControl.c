/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_CommunicationControl.c
 *    Author: QRH1KOR
 *    Generated on: 14-Jun-2023 15:38:27
 *    Generated from: dcom_CommunicationControl.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/dcom_CommunicationControl.h"
#include "RbPduHandler.h"

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
void ut_DcmAppl_DcmCommControlConditionCheck(int);
void ut_DcmAppl_DcmSwitchCommunicationControl(int);
#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
void ut_DcmAppl_DcmIsComModeDefault(int);
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
    OPEN_LOG("ut_dcom_CommunicationControl.ctr", false, 100);
    START_SCRIPT("dcom_CommunicationControl", true);

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
	ut_DcmAppl_DcmCommControlConditionCheck(1);
	ut_DcmAppl_DcmSwitchCommunicationControl(1);
#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
    ut_DcmAppl_DcmIsComModeDefault(1);
#endif
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_CommunicationControl.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_DcmAppl_DcmCommControlConditionCheck(int doIt){

if (doIt) {
    /* Test case data declarations */


    START_TEST("46394: ut_DcmAppl_DcmCommControlConditionCheck",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46394");


   START_STEP("1_NTS", true);
    /*Test step data declarations*/
     Dcm_NegativeResponseCodeType dataNegRespCode_u8 = 0x00;
     uint8 DataCommType_u8=0x01;
     uint8 RequestData=0x00;
     uint16 RequestLength=0x00;
     Std_ReturnType returnValue = E_NOT_OK;
	 uint8 ControlType_u8 = 0x00;

     /*Expected Call Sequence*/
     EXPECTED_CALLS(" ");

     /*Call SUT*/
     returnValue = DcmAppl_DcmCommControlConditionCheck(ControlType_u8, DataCommType_u8, RequestData, RequestLength, &dataNegRespCode_u8);

	  /*Test case checks*/
	 CHECK_U_CHAR(DataCommType_u8,DCOM_COMMUNICATION_MESSAGES_NORMAL);
	 CHECK_U_CHAR(returnValue, E_OK);

     END_CALLS();

  END_STEP();


    START_STEP("2_NTS", true);

     /*Test step data declarations*/
     Dcm_NegativeResponseCodeType dataNegRespCode_u8 = 0x00;
     uint8 DataCommType_u8=0x00;
     uint8 RequestData=0x00;
     uint16 RequestLength=0x00;
     Std_ReturnType returnValue = E_NOT_OK;
	 uint8 ControlType_u8 = 0x00;

     /*Expected Call Sequence*/
     EXPECTED_CALLS(" ");

     /*Call SUT*/
     returnValue = DcmAppl_DcmCommControlConditionCheck(ControlType_u8, DataCommType_u8, RequestData, RequestLength, &dataNegRespCode_u8);

     /*Test case checks*/
     CHECK_U_CHAR(returnValue, E_NOT_OK);
     CHECK_U_CHAR(DataCommType_u8,DCOM_COMMUNICATION_MESSAGES_ENABLE);
     CHECK_U_INT(dataNegRespCode_u8,DCM_E_REQUESTOUTOFRANGE);

        END_CALLS();
    END_STEP();


    END_TEST();
}}


void ut_DcmAppl_DcmSwitchCommunicationControl(int doIt){
if (doIt) {

    /* Test case data declarations */
	Dcm_CommunicationModeType RequestedMode;
	uint8 NetworkID = 0x00;

    START_TEST("46395: ut_DcmAppl_DcmSwitchCommunicationControl",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46395");

		START_STEP("1_NTS", true);

			/* Expected Call Sequence  */
			EXPECTED_CALLS(" ");

			/* Call SUT */
			DcmAppl_DcmSwitchCommunicationControl(NetworkID, RequestedMode);

			END_CALLS();
		END_STEP();

    END_TEST();
}}

#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
void ut_DcmAppl_DcmIsComModeDefault(int doIt){
if (doIt) {

    START_TEST("46396: ut_DcmAppl_DcmIsComModeDefault",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46396");

    	uint8 NetworkID = 0;
    	boolean retVal = FALSE;

    	START_STEP("1_NTS", true);

    		EXPECTED_CALLS(" ");

    		/* Call SUT */
    		boolean retVal = DcmAppl_DcmIsComModeDefault(NetworkID);

    		CHECK_BOOLEAN(retVal, TRUE);

    		END_CALLS();

    	END_STEP();

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
