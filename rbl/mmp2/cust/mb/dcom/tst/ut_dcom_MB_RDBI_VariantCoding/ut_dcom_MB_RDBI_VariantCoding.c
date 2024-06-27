/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_RDBI_VariantCoding.c
 *    Author: GDEV1KOR
 *    Generated on: 22-Dec-2023 09:10:28
 *    Generated from: dcom_MB_RDBI_VariantCoding.c
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
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id, uint8 * Data, uint8 NvM_Length, uint8 Fill_NvM);

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
void ut_dcom_AMG_SWITCH_0400_ReadData(int);
void ut_dcom_Calibration_Identifications_E104_ReadData(int);
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
    OPEN_LOG("ut_dcom_MB_RDBI_VariantCoding.ctr", false, 100);
    START_SCRIPT("dcom_MB_RDBI_VariantCoding", true);

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
	ut_dcom_AMG_SWITCH_0400_ReadData(1);
	ut_dcom_Calibration_Identifications_E104_ReadData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_RDBI_VariantCoding.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_AMG_SWITCH_0400_ReadData(int doIt){
if (doIt) {

   START_TEST("49609: [MMP2.11]UTC_dcom_AMG_SWITCH_0400_ReadData",
              "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49609 ");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

					/* Call SUT */
					returnValue = dcom_AMG_SWITCH_0400_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],0x01);
					CHECK_U_CHAR(Data[1],0x02);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_AMG_SWITCH_0400_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_Calibration_Identifications_E104_ReadData(int doIt){
if (doIt) {

   START_TEST("49610: [MMP2.11]UTC_dcom_Calibration_Identifications_E104_ReadData",
              "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49610 ");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_2");

					/* Call SUT */
					returnValue = dcom_Calibration_Identifications_E104_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],0x01);
					CHECK_U_CHAR(Data[1],0x02);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Calibration_Identifications_E104_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function dcom_Lib_ReadNvMData */
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id,
                                    uint8 * Data,
                                    uint8 NvM_Length,
                                    uint8 Fill_NvM){
    REGISTER_CALL("dcom_Lib_ReadNvMData");

    IF_INSTANCE("dcom_Lib_ReadNvMData_1") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_AMG_SWITCH);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				return E_OK;
    }

    IF_INSTANCE("dcom_Lib_ReadNvMData_2") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_CALID);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_CALID);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				return E_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
