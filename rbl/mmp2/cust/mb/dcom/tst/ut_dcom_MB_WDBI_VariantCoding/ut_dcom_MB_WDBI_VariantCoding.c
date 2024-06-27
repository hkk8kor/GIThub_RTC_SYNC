/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_WDBI_VariantCoding.c
 *    Author: GDEV1KOR
 *    Generated on: 19-Dec-2023 14:08:55
 *    Generated from: dcom_MB_WDBI_VariantCoding.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"
#include "dcom_MB_Pub.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_RWDBI_VariantCoding.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
/* None */

/* Global data */
extern uint8 rbl_dcom_MirrorAMGVarSwitch_u8[1];
extern uint8 rbl_Mirrordcom_CalId_u8[16];

/* Expected variables for global data */
uint8 expected_rbl_dcom_MirrorAMGVarSwitch_u8[1];
uint8 expected_rbl_Mirrordcom_CalId_u8[16];

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_dcom_MirrorAMGVarSwitch_u8);
    INITIALISE(rbl_Mirrordcom_CalId_u8);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_dcom_MirrorAMGVarSwitch_u8, expected_rbl_dcom_MirrorAMGVarSwitch_u8);
    COPY_TO_EXPECTED(rbl_Mirrordcom_CalId_u8, expected_rbl_Mirrordcom_CalId_u8);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("rbl_dcom_MirrorAMGVarSwitch_u8", rbl_dcom_MirrorAMGVarSwitch_u8, expected_rbl_dcom_MirrorAMGVarSwitch_u8, sizeof(expected_rbl_dcom_MirrorAMGVarSwitch_u8));
    CHECK_MEMORY("rbl_Mirrordcom_CalId_u8", rbl_Mirrordcom_CalId_u8, expected_rbl_Mirrordcom_CalId_u8, sizeof(expected_rbl_Mirrordcom_CalId_u8));
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_AMG_SWITCH_0400_WriteData(int);
void ut_dcom_Calibration_Identifications_F804_WriteData(int);
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
    OPEN_LOG("ut_dcom_MB_WDBI_VariantCoding.ctr", false, 100);
    START_SCRIPT("dcom_MB_WDBI_VariantCoding", true);

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
	ut_dcom_AMG_SWITCH_0400_WriteData(1);
	ut_dcom_Calibration_Identifications_F804_WriteData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_WDBI_VariantCoding.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_AMG_SWITCH_0400_WriteData(int doIt){
if (doIt) {

    START_TEST("49607: [MMP2.11]UTC_dcom_AMG_SWITCH_0400_WriteData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49607");

				START_STEP("1_NTS", true);
				{
				/* Test step data */
				uint8 Data_buffer[2]={0x00,0x01};
				uint8 *Data  = Data_buffer;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_AMG_SWITCH_0400_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_OK);
				CHECK_U_CHAR(ErrorCode, 0x00);
				CHECK_U_CHAR(rbl_dcom_MirrorAMGVarSwitch_u8[0], Data[0]);

				END_CALLS();
				END_STEP();
				}

				START_STEP("2_NTS", true);
				{
				/* Test step data */
				uint8 Data_buffer[2]={0x03,0x04};
				uint8 *Data  = Data_buffer;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_AMG_SWITCH_0400_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);
				CHECK_U_CHAR(ErrorCode, DCM_E_REQUESTOUTOFRANGE);

				END_CALLS();
				END_STEP();
				}

				START_STEP("3_NTS", true);
				{
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_AMG_SWITCH_0400_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);
				CHECK_U_CHAR(ErrorCode, DCM_E_CONDITIONSNOTCORRECT);

				END_CALLS();
				END_STEP();
				}
    END_TEST();
}}

void ut_dcom_Calibration_Identifications_F804_WriteData(int doIt){
if (doIt) {

    START_TEST("49608: [MMP2.11]UTC_dcom_Calibration_Identifications_F804_WriteData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49608");

				START_STEP("1_NTS", true);
				{
				/* Test step data */
				uint8 Data_buffer[2]={0x01,0x01};
				uint8 *Data  = Data_buffer;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_NOT_OK;
				uint8 rbl_dcom_CalIdCnt_u8 = 0 ;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_Calibration_Identifications_F804_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_OK);
				CHECK_U_CHAR(ErrorCode, 0x00);
                for(rbl_dcom_CalIdCnt_u8 = 0; rbl_dcom_CalIdCnt_u8 < 16; rbl_dcom_CalIdCnt_u8++)
                {
                	CHECK_U_CHAR(rbl_Mirrordcom_CalId_u8[rbl_dcom_CalIdCnt_u8], Data[rbl_dcom_CalIdCnt_u8 + 1]);
                }

				END_CALLS();
				END_STEP();
				}

				START_STEP("2_NTS", true);
				{
				/* Test step data */
				uint8 Data_buffer[2]={0x03,0x04};
				uint8 *Data  = Data_buffer;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_Calibration_Identifications_F804_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);
				CHECK_U_CHAR(ErrorCode, DCM_E_REQUESTOUTOFRANGE);

				END_CALLS();
				END_STEP();
				}

				START_STEP("3_NTS", true);
				{
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Dcm_NegativeResponseCodeType ErrorCode = 0x00;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_Calibration_Identifications_F804_WriteData(Data,&ErrorCode);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);
				CHECK_U_CHAR(ErrorCode, DCM_E_CONDITIONSNOTCORRECT);

				END_CALLS();
				END_STEP();
				}
    END_TEST();
}}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
