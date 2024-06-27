/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_TiSync_AMG.c
 *    Author: GDEV1KOR
 *    Generated on: 08-Apr-2024 12:53:14
 *    Generated from: rbl_CustIf_TiSync_AMG.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/TimeSync/rbl_CustIf_TiSync.h"
#include "Bfx.h"
#include "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/TimeSync/rbl_CustIf_GTS_Monitoring.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern uint32 ACCESS_FUNCTION_rbl_CustIf_TiSync_AMG_RBSYS_getRealtimeTickCtr();
extern boolean ACCESS_FUNCTION_rbl_CustIf_TiSync_AMG_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn);
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_AMG_RBSYS_EnterCorelocalIntlock();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_AMG_RBSYS_ExitCorelocalIntlock();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_AMG_rbl_TiSync_StbMAddNanoSeconds_AMG(StbM_TimeStampType * timeGTS_st, uint32 nanoseconds);
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
Std_ReturnType StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeStampType * timeStamp, StbM_UserDataType * userData);

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
void ut_rbl_TiSync_convertSystemTickstoGTS_AMG(int);
void ut_rbl_TiSync_StbMAddNanoSeconds_AMG(int);
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
    OPEN_LOG("ut_rbl_CustIf_TiSync_AMG.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_TiSync_AMG", true);

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
	ut_rbl_TiSync_convertSystemTickstoGTS_AMG(1);
	ut_rbl_TiSync_StbMAddNanoSeconds_AMG(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_TiSync_AMG.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_TiSync_convertSystemTickstoGTS_AMG(int doIt)
{
	if (doIt)
	{
		START_TEST("49906: [MMP2.11]UTC_rbl_TiSync_convertSystemTickstoGTS_AMG",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49906");

		/* Test case data declarations */
		uint32 timeMMP_u32;
		StbM_TimeStampType timeGTS_st;
		Std_ReturnType retVal = E_OK;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			//Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_1;"
					       "RBSYS_getRealtimeTickCtr#default;"
					       "RBSYS_ExitCorelocalIntlock#default;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_1;"
					       "rbl_TiSync_StbMAddNanoSeconds_AMG#rbl_TiSync_StbMAddNanoSeconds_AMG_1");

			// Call SUT
			retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_NO_INITIAL_SYNC);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			//Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_1;"
					       "RBSYS_getRealtimeTickCtr#default;"
					       "RBSYS_ExitCorelocalIntlock#default;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_3;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_4;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_5;"
					       "rbl_TiSync_StbMAddNanoSeconds_AMG#rbl_TiSync_StbMAddNanoSeconds_AMG_2");

			// Call SUT
			retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_SYNC_OK);

			END_CALLS();
			END_STEP();
		}

		START_STEP("3_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = RBL_CUSTIF_TISYNC_MAXSYSTICKS+1;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			//Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_1;"
					       "RBSYS_getRealtimeTickCtr#default;"
					       "RBSYS_ExitCorelocalIntlock#default;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_3;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_4;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_6");

			// Call SUT
			retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeMMP_u32, RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_SYNC_LOST);

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = (-RBL_CUSTIF_TISYNC_MAXSYSTICKS) - 1;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			//Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_1;"
					       "RBSYS_getRealtimeTickCtr#default;"
					       "RBSYS_ExitCorelocalIntlock#default;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_3;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_7");

			// Call SUT
			retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_SYNC_LOST);

			END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			//Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_2;"
					       "RBSYS_getRealtimeTickCtr#default;"
					       "RBSYS_ExitCorelocalIntlock#default;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_8");

			// Call SUT
			retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_SYNC_LOST);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_TiSync_StbMAddNanoSeconds_AMG(int doIt)
{
	if (doIt)
	{
		START_TEST("49905: [MMP2.11]UTC_rbl_TiSync_StbMAddNanoSeconds_AMG",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49905");

		/* Test case data declarations */
		StbM_TimeStampType timeGTS_st;
		uint32 nanoseconds;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0;
			timeGTS_st.nanoseconds=0;
			timeGTS_st.secondsHi=0;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG,rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();

		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = RBL_CUSTIF_TISYNC_MAXSYSTICKS+1;
			timeGTS_st.seconds=0;
			timeGTS_st.nanoseconds=0;
			timeGTS_st.secondsHi=0;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG,rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds,RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);
			CHECK_U_INT(timeGTS_st.seconds,0);
			CHECK_U_INT(timeGTS_st.secondsHi,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus,0);
			CHECK_U_INT(nanoseconds,RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);

			END_CALLS();
			END_STEP();

		}

		START_STEP("3_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = -RBL_CUSTIF_TISYNC_MAXSYSTICKS-1;
			timeGTS_st.seconds=0;
			timeGTS_st.nanoseconds=0;
			timeGTS_st.secondsHi=0;

			// Expected Call Sequence
			EXPECTED_CALLS("");
			// Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,RBL_CUSTIF_TISYNC_S2NS - RBL_CUSTIF_TISYNC_MAXSYSTICKS - 1);
			CHECK_U_INT(timeGTS_st.seconds ,0xFFFFFFFFu);
			CHECK_U_INT(timeGTS_st.secondsHi ,0xFFFF);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0xFD9DA5FF);

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0x01;
			timeGTS_st.nanoseconds=0;
			timeGTS_st.secondsHi=0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");
			// Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,1);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0x01;
			timeGTS_st.nanoseconds=RBL_CUSTIF_TISYNC_S2NS+1;
			timeGTS_st.secondsHi=0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");
			// Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,1);
			CHECK_U_INT(timeGTS_st.seconds ,2);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();
		}

		START_STEP("6_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0xFFFFFFFF;
			timeGTS_st.nanoseconds=RBL_CUSTIF_TISYNC_S2NS+1;
			timeGTS_st.secondsHi=0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,1);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,2);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();

		}

		START_STEP("7_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0x01;
			timeGTS_st.nanoseconds=-RBL_CUSTIF_TISYNC_S2NS;
			timeGTS_st.secondsHi=0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();

		}

		START_STEP("8_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds=0xFFFFFFFF+0x1;
			timeGTS_st.nanoseconds=-RBL_CUSTIF_TISYNC_S2NS;
			timeGTS_st.secondsHi=0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION(rbl_CustIf_TiSync_AMG, rbl_TiSync_StbMAddNanoSeconds_AMG)(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0xFFFFFFFF);
			CHECK_U_INT(timeGTS_st.secondsHi ,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSYS_EnterCorelocalIntlockSysfast_intern */
void RBSYS_EnterCorelocalIntlockSysfast_intern(){
    REGISTER_CALL("RBSYS_EnterCorelocalIntlockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlockSysfast_intern */
void RBSYS_ExitCorelocalIntlockSysfast_intern(){
    REGISTER_CALL("RBSYS_ExitCorelocalIntlockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCorelocalIntlock_intern */
void RBSYS_EnterCorelocalIntlock_intern(){
    REGISTER_CALL("RBSYS_EnterCorelocalIntlock_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlock_intern */
void RBSYS_ExitCorelocalIntlock_intern(){
    REGISTER_CALL("RBSYS_ExitCorelocalIntlock_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function StbM_GetCurrentTime */
Std_ReturnType StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId,
                                   StbM_TimeStampType * timeStamp,
                                   StbM_UserDataType * userData){
    REGISTER_CALL("StbM_GetCurrentTime");

    IF_INSTANCE("StbM_GetCurrentTime_1") {
    CHECK_U_INT(timeBaseId,2);
    CHECK_U_INT(timeStamp->nanoseconds,0);
    CHECK_U_INT(timeStamp->seconds,0);
    CHECK_U_INT(timeStamp->secondsHi,0);
    CHECK_U_INT(timeStamp->timeBaseStatus,0);
   	CHECK_U_INT(userData->userDataLength,0);
   	CHECK_U_INT(userData->userByte0,0);
   	CHECK_U_INT(userData->userByte1,0);
   	CHECK_U_INT(userData->userByte2,0);
   	return E_OK;
       }

   	IF_INSTANCE("StbM_GetCurrentTime_2") {
   	CHECK_U_INT(timeBaseId,2);
   	CHECK_U_INT(timeStamp->nanoseconds,0);
   	CHECK_U_INT(timeStamp->seconds,0);
   	CHECK_U_INT(timeStamp->secondsHi,0);
   	CHECK_U_INT(timeStamp->timeBaseStatus,0);
   	CHECK_U_INT(userData->userDataLength,0);
   	CHECK_U_INT(userData->userByte0,0);
   	CHECK_U_INT(userData->userByte1,0);
   	CHECK_U_INT(userData->userByte2,0);
   	return E_NOT_OK;
       }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RBSYS_getRealtimeTickCtr */
int BEFORE_RBSYS_getRealtimeTickCtr(){
    REGISTER_CALL("RBSYS_getRealtimeTickCtr");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_getRealtimeTickCtr */
uint32 AFTER_RBSYS_getRealtimeTickCtr(uint32 cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function RBSYS_getRealtimeTickCtr */
uint32 REPLACE_RBSYS_getRealtimeTickCtr(){
    IF_INSTANCE("default") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
int BEFORE_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data,
                                      uint8 BitPn){
    REGISTER_CALL("Bfx_Prv_GetBit_u8u8_u8_Inl");

    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_1") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMEOUT_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_4") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_PAST_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_5") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_6") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_7") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_PAST_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMEOUT_BflPn);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
boolean AFTER_Bfx_Prv_GetBit_u8u8_u8_Inl(boolean cppsm_return_value,
                                         uint8 Data,
                                         uint8 BitPn){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
boolean REPLACE_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data,
                                           uint8 BitPn){
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_1") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_4") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_5") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_6") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_7") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
        return TRUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function RBSYS_EnterCorelocalIntlock */
int BEFORE_RBSYS_EnterCorelocalIntlock(){
    REGISTER_CALL("RBSYS_EnterCorelocalIntlock");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_EnterCorelocalIntlock */
void AFTER_RBSYS_EnterCorelocalIntlock(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_EnterCorelocalIntlock */
void REPLACE_RBSYS_EnterCorelocalIntlock(){
    IF_INSTANCE("default") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCorelocalIntlock */
int BEFORE_RBSYS_ExitCorelocalIntlock(){
    REGISTER_CALL("RBSYS_ExitCorelocalIntlock");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_ExitCorelocalIntlock */
void AFTER_RBSYS_ExitCorelocalIntlock(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_ExitCorelocalIntlock */
void REPLACE_RBSYS_ExitCorelocalIntlock(){
    IF_INSTANCE("default") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_TiSync_StbMAddNanoSeconds_AMG */
int BEFORE_rbl_TiSync_StbMAddNanoSeconds_AMG(StbM_TimeStampType * timeGTS_st,
                                             uint32 nanoseconds){
    REGISTER_CALL("rbl_TiSync_StbMAddNanoSeconds_AMG");

    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_1") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, RBL_CUSTIF_NO_INITIAL_SYNC);
    	CHECK_U_INT(nanoseconds, 0);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_2") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, RBL_CUSTIF_SYNC_OK);
    	CHECK_U_INT(nanoseconds, 0);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_3") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, RBL_CUSTIF_SYNC_LOST);
    	CHECK_U_INT(nanoseconds, 0);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_TiSync_StbMAddNanoSeconds_AMG */
void AFTER_rbl_TiSync_StbMAddNanoSeconds_AMG(struct cppsm_void_return cppsm_dummy,
                                             StbM_TimeStampType * timeGTS_st,
                                             uint32 nanoseconds){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_TiSync_StbMAddNanoSeconds_AMG */
void REPLACE_rbl_TiSync_StbMAddNanoSeconds_AMG(StbM_TimeStampType * timeGTS_st,
                                               uint32 nanoseconds){
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_1") {
        return;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_2") {
        return;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_AMG_3") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
