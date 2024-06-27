/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_PlantModeActivation.c
 *    Author: GDEV1KOR
 *    Generated on: 27-Mar-2024 16:21:43
 *    Generated from: dcom_PlantModeActivation.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rba_DcmPma.h"
#include "RBTSI_RbDiagInit.h"
#include "RBSYS_PlantStartupCtrl.h"
#define DCM_START_SEC_CODE 
#include "Dcm_Cfg_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_dcom_PlantModeActivation_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_dcom_PlantModeActivation_RBSYS_ExitCommonLockSysfast();
extern boolean ACCESS_FUNCTION_dcom_PlantModeActivation_RBSYS_isBaseOSActive();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void FUN_InitializeTSI_V();
void FUN_DiagExitInit_V();

/* Global data */
volatile BOOL RBMESG_RBMESG_RBSYSBaseOSActive;

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
void ut_rba_DcmPmaAppl_PlantModeActivation(int);
void ut_rba_DcmPmaAppl_FillPlantModeResponse(int);
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
    OPEN_LOG("ut_dcom_PlantModeActivation.ctr", false, 100);
    START_SCRIPT("dcom_PlantModeActivation", true);

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
	ut_rba_DcmPmaAppl_PlantModeActivation(1);
    ut_rba_DcmPmaAppl_FillPlantModeResponse(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_PlantModeActivation.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rba_DcmPmaAppl_PlantModeActivation(int doIt)
{
	if (doIt)
	{
		initialise_global_data();
		initialise_expected_global_data();

		 START_TEST("46397: [MMP2.11]UTC_rba_DcmPmaAppl_PlantModeActivation",
		               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46397");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			bool stActive_b = 1;
			bool expected_stActive_b = stActive_b;

			// EXPECTED CALLS
			EXPECTED_CALLS("FUN_InitializeTSI_V#default");

			// SUT
			rba_DcmPmaAppl_PlantModeActivation(stActive_b);

			// EXPECTED RESULTS
			check_global_data();
			CHECK_U_INT(stActive_b , expected_stActive_b);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			bool stActive_b = 0;
			bool expected_stActive_b = stActive_b;

			// EXPECTED CALLS
			EXPECTED_CALLS("FUN_DiagExitInit_V#default");

			// SUT
			rba_DcmPmaAppl_PlantModeActivation(stActive_b);

			// EXPECTED RESULTS
			check_global_data();
			CHECK_U_INT(stActive_b , expected_stActive_b);

			END_CALLS();
			END_STEP();
		}

		END_TEST();
	}
}

void ut_rba_DcmPmaAppl_FillPlantModeResponse(int doIt)
{
	if (doIt)
	{

		START_TEST("46398: [MMP2.11]UTC_rba_DcmPmaAppl_FillPlantModeResponse",
		               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46398");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			ACCESS_FUNCTION(dcom_PlantModeActivation, RBSYS_isBaseOSActive)(1);

		    uint8 returnValue = 0x01;
			uint8 expected_returnValue =  returnValue;

			// EXPECTED CALLS
			EXPECTED_CALLS("RBSYS_isBaseOSActive#RBSYS_isBaseOSActive_1");

			// SUT
			returnValue = rba_DcmPmaAppl_FillPlantModeResponse();

			// EXPECTED RESULTS
			CHECK_U_INT(returnValue , expected_returnValue);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			ACCESS_FUNCTION(dcom_PlantModeActivation, RBSYS_isBaseOSActive)(0);

			uint8 returnValue = 0x00;
			uint8 expected_returnValue =  returnValue;

			// EXPECTED CALLS
			EXPECTED_CALLS("RBSYS_isBaseOSActive#RBSYS_isBaseOSActive_2");

			// SUT
			returnValue = rba_DcmPmaAppl_FillPlantModeResponse();

			// EXPECTED RESULTS
			CHECK_U_INT(returnValue , expected_returnValue);

			END_CALLS();
			END_STEP();

		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSYS_EnterCommonLockSysfast_intern */
void RBSYS_EnterCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLockSysfast_intern */
void RBSYS_ExitCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function FUN_InitializeTSI_V */
void FUN_InitializeTSI_V(){
    REGISTER_CALL("FUN_InitializeTSI_V");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function FUN_DiagExitInit_V */
void FUN_DiagExitInit_V(){
    REGISTER_CALL("FUN_DiagExitInit_V");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RBSYS_EnterCommonLockSysfast */
int BEFORE_RBSYS_EnterCommonLockSysfast(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_EnterCommonLockSysfast */
void AFTER_RBSYS_EnterCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_EnterCommonLockSysfast */
void REPLACE_RBSYS_EnterCommonLockSysfast(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCommonLockSysfast */
int BEFORE_RBSYS_ExitCommonLockSysfast(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_ExitCommonLockSysfast */
void AFTER_RBSYS_ExitCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_ExitCommonLockSysfast */
void REPLACE_RBSYS_ExitCommonLockSysfast(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_isBaseOSActive */
int BEFORE_RBSYS_isBaseOSActive(){
    REGISTER_CALL("RBSYS_isBaseOSActive");

    IF_INSTANCE("RBSYS_isBaseOSActive_1") {
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("RBSYS_isBaseOSActive_2") {
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_isBaseOSActive */
boolean AFTER_RBSYS_isBaseOSActive(boolean cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function RBSYS_isBaseOSActive */
boolean REPLACE_RBSYS_isBaseOSActive(){
    IF_INSTANCE("RBSYS_isBaseOSActive_1") {
        return TRUE;
    }
    IF_INSTANCE("RBSYS_isBaseOSActive_2") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
