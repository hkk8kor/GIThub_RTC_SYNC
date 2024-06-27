/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_RoutineControl.c
 *    Author: VQQ1KOR
 *    Generated on: 04-Nov-2022 16:05:16
 *    Generated from: dcom_MB_RoutineControl.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_RoutineControl.h"
#include "dcom_Lib.h"
#include "RBMESG_Explicit.h"
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */
#define DCOM_REPROG_SPEEDLIMIT 0x10

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_dcom_MB_RoutineControl_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_dcom_MB_RoutineControl_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
boolean dcom_isSpeedLimitExceeded(uint16 l_Value);

/* Global data */
volatile RBMESG_Type_Platform_Stat_Star3 RBMESG_Platform_Stat_Star3;
boolean dcom_CheckReprogPreConditionFullfilled;

/* Expected variables for global data */
RBMESG_Type_Platform_Stat_Star3 expected_RBMESG_Platform_Stat_Star3;
boolean expected_dcom_CheckReprogPreConditionFullfilled;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(RBMESG_Platform_Stat_Star3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(RBMESG_Platform_Stat_Star3, expected_RBMESG_Platform_Stat_Star3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_CHAR(RBMESG_Platform_Stat_Star3, expected_RBMESG_Platform_Stat_Star3);
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_CheckReprogrammingPreconditions_0203_Start(int);

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
    OPEN_LOG("ut_dcom_MB_RoutineControl.ctr", false, 100);
    START_SCRIPT("dcom_MB_RoutineControl", true);

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

	ut_dcom_CheckReprogrammingPreconditions_0203_Start(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_RoutineControl.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_dcom_CheckReprogrammingPreconditions_0203_Start(int doIt)
{
	if (doIt) {
	    START_TEST("47793: dcom_CheckReprogrammingPreconditions_0203_Start",
	                   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47793");
		   /* Test case data declarations */
		Dcm_OpStatusType OpStatus = 0x01;
		uint8  buffer_dataOut1[2]={0x00,0x01};
		uint8  buffer_dataOut2[3]={0x00,0x01,0x02};
		uint8 * dataOut1 = &buffer_dataOut1;
		uint8 * dataOut2 = &buffer_dataOut2;
		uint16 buf_CurrentDataLength = 0x10;
		uint16 expected_buf_CurrentDataLength;
		uint16 * CurrentDataLength = &buf_CurrentDataLength ;
		Dcm_NegativeResponseCodeType buffer_ErrorCode = 0x01 ;
		Dcm_NegativeResponseCodeType * ErrorCode = &buffer_ErrorCode;
		Std_ReturnType returnValue = E_NOT_OK,ExpectedReturnValue = E_OK;
		uint8 expected_numberOfPreconditions_u8;
		/* Test steps */
	    START_STEP("1_NTS", true);
		/* Set global data */
		initialise_global_data();
		/* Set expected values for global data checks */
		initialise_expected_global_data();
	   #if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
		   expected_buf_CurrentDataLength = 3;
		   expected_numberOfPreconditions_u8 = 2;
		   RBMESG_Platform_Stat_Star3 = 5;
		   expected_RBMESG_Platform_Stat_Star3 = 5;
		   dcom_CheckReprogPreConditionFullfilled = false;
		   expected_dcom_CheckReprogPreConditionFullfilled = false;
		  /* Expected Call Sequence  */
		   EXPECTED_CALLS(
				   "dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitNotExceeded;"
				   );
	   #else
		   expected_buf_CurrentDataLength = 3;
		   expected_numberOfPreconditions_u8 = 0;
		   EXPECTED_CALLS("");
	   #endif

	  /* Call SUT */
	   returnValue = dcom_CheckReprogrammingPreconditions_0203_Start(OpStatus, dataOut1, dataOut2, CurrentDataLength, ErrorCode);
	  /* Test case checks */
	   CHECK_U_CHAR(returnValue, ExpectedReturnValue);
	   CHECK_U_CHAR( dataOut2[0],expected_numberOfPreconditions_u8);
	   CHECK_U_CHAR( dataOut1[0], DCOM_ROUTINE_SUCCESSFULLY_COMPLETED );
	   CHECK_U_CHAR( * ErrorCode, DCOM_NO_ERROR );
	   CHECK_U_CHAR( * CurrentDataLength, expected_buf_CurrentDataLength);
	   CHECK_U_CHAR( OpStatus, 0x01);

	   #if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
		   CHECK_U_CHAR( dataOut2[1],DCOM_VEHICLE_SPEED_HIGH);
		   CHECK_U_CHAR( dataOut2[2],DCOM_FBL_CFG_STAR3);
	   #endif
			/* Checks on global data */
			check_global_data();
	   END_CALLS();
	   END_STEP();
	   START_STEP("2_NTS", true);
	   		/* Set global data */
	   				initialise_global_data();
	   				/* Set expected values for global data checks */
	   				initialise_expected_global_data();
	   		#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
	   		   expected_buf_CurrentDataLength = 2;
	   		   expected_numberOfPreconditions_u8 = 1;
	   		RBMESG_Platform_Stat_Star3 = 4;
	   		expected_RBMESG_Platform_Stat_Star3 = 4;
	   		dcom_CheckReprogPreConditionFullfilled = false;
	   		expected_dcom_CheckReprogPreConditionFullfilled = false;
	   		EXPECTED_CALLS("dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitNotExceeded"
	   				);
	   		#else
	   		   expected_buf_CurrentDataLength = 3;
	   		   expected_numberOfPreconditions_u8 = 0;
	   		   EXPECTED_CALLS("");
	   		#endif
	   		/* Call SUT */
	   		returnValue = dcom_CheckReprogrammingPreconditions_0203_Start(OpStatus, dataOut1, dataOut2, CurrentDataLength, ErrorCode);

	   		/* Test case checks */
	   		CHECK_U_CHAR(returnValue, ExpectedReturnValue);
	   		CHECK_U_CHAR( dataOut2[0],expected_numberOfPreconditions_u8);
	   		CHECK_U_CHAR( dataOut1[0], DCOM_ROUTINE_SUCCESSFULLY_COMPLETED );
	   		CHECK_U_CHAR( * ErrorCode, DCOM_NO_ERROR );
	   		CHECK_U_CHAR( * CurrentDataLength, expected_buf_CurrentDataLength);
	   		CHECK_U_CHAR( OpStatus, 0x01);
	   		#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
	   		   CHECK_U_CHAR( dataOut2[1],DCOM_VEHICLE_SPEED_HIGH);
	   	   #endif
	   			/* Checks on global data */
	   			check_global_data();
	   		END_CALLS();
	   		END_STEP();
	   		/* Test steps */
			START_STEP("3_NTS", true);
			initialise_global_data();
			/* Set expected values for global data checks */
			initialise_expected_global_data();
			#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
			expected_buf_CurrentDataLength = 2;
			   expected_numberOfPreconditions_u8 = 1;
			   RBMESG_Platform_Stat_Star3 = 8;
			   expected_RBMESG_Platform_Stat_Star3 = 8;
			   dcom_CheckReprogPreConditionFullfilled = false;
			   expected_dcom_CheckReprogPreConditionFullfilled = false;
			/* Expected Call Sequence  */
			EXPECTED_CALLS("dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitExceeded;"
					"dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitExceeded"
			);
			#else
			expected_buf_CurrentDataLength = 3;
			expected_numberOfPreconditions_u8 = 0;
			EXPECTED_CALLS("");
			#endif
			/* Call SUT */
			returnValue = dcom_CheckReprogrammingPreconditions_0203_Start(OpStatus, dataOut1, dataOut2, CurrentDataLength, ErrorCode);

			/* Test case checks */
			CHECK_U_CHAR(returnValue, ExpectedReturnValue);
			CHECK_U_CHAR( dataOut2[0],expected_numberOfPreconditions_u8);
			CHECK_U_CHAR( dataOut1[0], DCOM_ROUTINE_SUCCESSFULLY_COMPLETED );
			CHECK_U_CHAR( * ErrorCode, DCOM_NO_ERROR );
			CHECK_U_CHAR( * CurrentDataLength, expected_buf_CurrentDataLength);
			CHECK_U_CHAR( OpStatus, 0x01);
			#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
			CHECK_U_CHAR( dataOut2[1],DCOM_FBL_CFG_STAR3);
			#endif
			   /* Checks on global data */
			   check_global_data();
			END_CALLS();
			END_STEP();
			START_STEP("4_NTS", true);
			/* Set global data */
			initialise_global_data();
			/* Set expected values for global data checks */
			initialise_expected_global_data();

			#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
			expected_buf_CurrentDataLength = 1;
			expected_numberOfPreconditions_u8 = 0;
			RBMESG_Platform_Stat_Star3 = 4;
			   expected_RBMESG_Platform_Stat_Star3 = 4;
			   dcom_CheckReprogPreConditionFullfilled = true;
			   expected_dcom_CheckReprogPreConditionFullfilled = true;
			/* Expected Call Sequence  */
			EXPECTED_CALLS("dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitExceeded;"
					);
			#else
			expected_buf_CurrentDataLength = 3;
			expected_numberOfPreconditions_u8 = 0;
			EXPECTED_CALLS("");
			#endif
			/* Call SUT */
			returnValue = dcom_CheckReprogrammingPreconditions_0203_Start(OpStatus, dataOut1, dataOut2, CurrentDataLength, ErrorCode);

			/* Test case checks */
			CHECK_U_CHAR(returnValue, ExpectedReturnValue);
			CHECK_U_CHAR( dataOut2[0],expected_numberOfPreconditions_u8);
			CHECK_U_CHAR( dataOut1[0], DCOM_ROUTINE_SUCCESSFULLY_COMPLETED );
			CHECK_U_CHAR( * ErrorCode, DCOM_NO_ERROR );
			CHECK_U_CHAR( * CurrentDataLength, expected_buf_CurrentDataLength);
			CHECK_U_CHAR( OpStatus, 0x01);
			/* Checks on global data */
			check_global_data();
			END_CALLS();
			END_STEP();
			START_STEP("5_NTS", true);
			/* Set global data */
			initialise_global_data();
			/* Set expected values for global data checks */
			initialise_expected_global_data();

			#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
			expected_buf_CurrentDataLength = 1;
				   expected_numberOfPreconditions_u8 = 0;
				   RBMESG_Platform_Stat_Star3 = 8;
				   expected_RBMESG_Platform_Stat_Star3 = 8;
				   dcom_CheckReprogPreConditionFullfilled = true;
				   expected_dcom_CheckReprogPreConditionFullfilled = true;
			/* Expected Call Sequence  */
			EXPECTED_CALLS("dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitExceeded;"
					"dcom_isSpeedLimitExceeded#stub_dcom_isSpeedLimitNotExceeded"
					);
			#else
			expected_buf_CurrentDataLength = 3;
			expected_numberOfPreconditions_u8 = 0;
			EXPECTED_CALLS("");
			#endif
			/* Call SUT */
			returnValue = dcom_CheckReprogrammingPreconditions_0203_Start(OpStatus, dataOut1, dataOut2, CurrentDataLength, ErrorCode);

			/* Test case checks */
			CHECK_U_CHAR(returnValue, ExpectedReturnValue);
			CHECK_U_CHAR( dataOut2[0],expected_numberOfPreconditions_u8);
			CHECK_U_CHAR( dataOut1[0], DCOM_ROUTINE_SUCCESSFULLY_COMPLETED );
			CHECK_U_CHAR( * ErrorCode, DCOM_NO_ERROR );
			CHECK_U_CHAR( * CurrentDataLength, expected_buf_CurrentDataLength);
			CHECK_U_CHAR( OpStatus, 0x01);
			/* Checks on global data */
			check_global_data();
			END_CALLS();
			END_STEP();
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

/* Stub for function dcom_isSpeedLimitExceeded */
boolean dcom_isSpeedLimitExceeded(uint16 l_Value){
	REGISTER_CALL("dcom_isSpeedLimitExceeded");
	    boolean returnValue;
	    IF_INSTANCE("stub_dcom_isSpeedLimitNotExceeded") {
	    	CHECK_U_CHAR(l_Value,DCOM_REPROG_SPEEDLIMIT);
	    	returnValue = TRUE;
	        return returnValue;
	    }
	    IF_INSTANCE("stub_dcom_isSpeedLimitExceeded") {
	    	 CHECK_U_CHAR(l_Value,DCOM_REPROG_SPEEDLIMIT);
	         returnValue = FALSE;
	         return returnValue;
	     }
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
