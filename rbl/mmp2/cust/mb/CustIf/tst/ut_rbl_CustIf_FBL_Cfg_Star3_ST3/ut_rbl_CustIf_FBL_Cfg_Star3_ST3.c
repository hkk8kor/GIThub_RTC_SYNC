/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_FBL_Cfg_Star3_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 08-Oct-2023 19:16:52
 *    Generated from: rbl_CustIf_FBL_Cfg_Star3_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_rbl_CustIf_FBL_Cfg_Star3_ST3_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_FBL_Cfg_Star3_ST3_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);

/* Global data */
extern volatile RBMESG_Type_Platform_Stat_Star3 RBMESG_Platform_Stat_Star3;
extern volatile RBMESG_Type_rbl_CustIf_Platform_Stat_Star3 RBMESG_rbl_CustIf_Platform_Stat_Star3;

/* Expected variables for global data */
RBMESG_Type_Platform_Stat_Star3 expected_RBMESG_Platform_Stat_Star3;
RBMESG_Type_rbl_CustIf_Platform_Stat_Star3 expected_RBMESG_rbl_CustIf_Platform_Stat_Star3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(RBMESG_Platform_Stat_Star3);
    INITIALISE(RBMESG_rbl_CustIf_Platform_Stat_Star3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(RBMESG_Platform_Stat_Star3, expected_RBMESG_Platform_Stat_Star3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_Platform_Stat_Star3, expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_CHAR(RBMESG_Platform_Stat_Star3, expected_RBMESG_Platform_Stat_Star3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_Platform_Stat_Star3, expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive(int);
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
    OPEN_LOG("ut_rbl_CustIf_FBL_Cfg_Star3_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_FBL_Cfg_Star3_ST3", true);

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
	ut_rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_FBL_Cfg_Star3_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive(int doIt)
{
	if (doIt)
	{
		START_TEST("47817: [MMP2.11]UTC_rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47817");
		/*Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_IDLE;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_IDLE;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_IDLE;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR1;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR1;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR1;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("3_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR2;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR2;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR2;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("4_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR3;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR3;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_STAR3;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("5_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES8;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES8;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES8;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("6_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES16;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES16;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES16;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("7_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES32;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES32;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES32;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("8_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES64;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES64;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES64;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("9_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES128;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES128;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_RES128;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_2");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("10_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_SNA;
			expected_RBMESG_Platform_Stat_Star3=I_C08_PLATFORM_STAT_SNA;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_SNA;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 200;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_1");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

		/*Test steps*/
		START_STEP("11_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test step data */
			RBMESG_Platform_Stat_Star3=129;
			expected_RBMESG_Platform_Stat_Star3=129;
			expected_RBMESG_rbl_CustIf_Platform_Stat_Star3=I_C08_PLATFORM_STAT_SNA;
			RBMESG_rbl_CustIf_Platform_Stat_Star3= 129;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Stub_1");

			/* Call SUT */
			rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();

			/* Test step checks */
			CHECK_U_INT(RBMESG_rbl_CustIf_Platform_Stat_Star3,expected_RBMESG_rbl_CustIf_Platform_Stat_Star3);

			END_CALLS();
			END_STEP();
		}

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

/* Stub for function Dem_SetEventStatus */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                                  Dem_EventStatusType EventStatus){
    REGISTER_CALL("Dem_SetEventStatus");

    IF_INSTANCE("Stub_1") {
   		CHECK_U_CHAR(EventId, DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3);
   		CHECK_U_CHAR(EventStatus, DEM_EVENT_STATUS_PREFAILED);
   		return DEM_EVENT_STATUS_PREFAILED;
    }

    IF_INSTANCE("Stub_2") {
   		CHECK_U_CHAR(EventId, DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_FBL_Cfg_Star3_ST3);
   		CHECK_U_CHAR(EventStatus, DEM_EVENT_STATUS_PREPASSED);
   		return DEM_EVENT_STATUS_PREPASSED;
    }

    IF_INSTANCE("Dem_SetEventStatus_3") {
   		CHECK_U_CHAR(EventId, DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_DIAG_Stat_ST3);
   		CHECK_U_CHAR(EventStatus, CANTATA_DEFAULT_VALUE);
   		return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
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

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
