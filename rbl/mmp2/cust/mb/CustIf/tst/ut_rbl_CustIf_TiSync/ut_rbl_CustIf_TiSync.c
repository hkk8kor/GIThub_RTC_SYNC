/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_TiSync.c
 *    Author: GDEV1KOR
 *    Generated on: 12-Apr-2024 13:45:50
 *    Generated from: rbl_CustIf_TiSync.c
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
extern uint32 ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_getRealtimeTickCtr();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_EnterCommonLock();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_ExitCommonLock();
extern Std_ReturnType ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st);
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_EnterCorelocalIntlock();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_ExitCorelocalIntlock();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(StbM_TimeStampType * timeGTS_st, uint32 nanoseconds);
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_Bfx_Prv_SetBit_u8u8_Inl(uint8 * Data, uint8 BitPn);
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_TiSync_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLock_intern();
void RBSYS_ExitCommonLock_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
Std_ReturnType StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeBaseStatusType * syncTimeBaseStatus, StbM_TimeBaseStatusType * offsetTimeBaseStatus);
void rbl_CustIf_StbM_Monitor_Time_Rate_Copy(Dem_EventStatusType EventStatusTimeCopy, Dem_EventStatusType EventStatusRateCopy);
Std_ReturnType StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeStampType * timeStamp, StbM_UserDataType * userData);
Std_ReturnType StbM_GetRateDeviation(StbM_SynchronizedTimeBaseType timeBaseId, StbM_RateDeviationType * rateDeviation);
Std_ReturnType StbM_SetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId, const StbM_TimeStampType * timeStamp, const StbM_UserDataType * userData);
Std_ReturnType StbM_SetRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId, StbM_RateDeviationType rateDeviation);
boolean rbl_CustIf_StbM_Check_Init_Sync();
boolean rbl_CustIf_StbM_Check_Lost_Sync();
boolean rbl_CustIf_StbM_Check_TimeLeap();

/* Global data */
volatile RBMESG_Type_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3;
typedef struct rbl_CustIf_TiSync_av_struct { RBL_CUSTIF_GTS_LOCALFALLBACK_STATE * ref_rbl_Custif_GtslocalfallbackStatus; boolean * ref_rbl_Custif_Gtslocalfallback; Dem_EventStatusType * ref_eventStatusTimeCopy; Dem_EventStatusType * ref_eventStatusRateCopy; } rbl_CustIf_TiSync_av_struct;
extern rbl_CustIf_TiSync_av_struct av_rbl_CustIf_TiSync;
extern uint16 (* cppth_alv_rbl_CustIf_TiSync_rbl_CustIf_GTS_LocalFallBackCheck_cnt);

/* Expected variables for global data */
RBMESG_Type_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 expected_RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3;
typedef struct expected_rbl_CustIf_TiSync_av_struct { RBL_CUSTIF_GTS_LOCALFALLBACK_STATE ref_rbl_Custif_GtslocalfallbackStatus; boolean ref_rbl_Custif_Gtslocalfallback; Dem_EventStatusType ref_eventStatusTimeCopy; Dem_EventStatusType ref_eventStatusRateCopy; } expected_rbl_CustIf_TiSync_av_struct;
expected_rbl_CustIf_TiSync_av_struct expected_av_rbl_CustIf_TiSync;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusTimeCopy));
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusRateCopy));
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback));
    INITIALISE(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusTimeCopy), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, eventStatusTimeCopy));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusRateCopy), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, eventStatusRateCopy));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback));
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, expected_RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusTimeCopy), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, eventStatusTimeCopy));
    CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, eventStatusRateCopy), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, eventStatusRateCopy));
    CHECK_BOOLEAN(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback));
    CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, expected_RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3);
    CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_TiSync_MMP2GtsTime(int);
void ut_rbl_TiSync_convertSystemTickstoGTS(int);
void ut_rbl_TiSync_cloneToPureLocalTime(int);
void ut_rbl_TiSync_StbMAddNanoSeconds(int);
void ut_rbl_CustIf_GTS_LocalFallBackCheck(int);
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
    OPEN_LOG("ut_rbl_CustIf_TiSync.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_TiSync", true);

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
	ut_rbl_CustIf_TiSync_MMP2GtsTime(1);
	ut_rbl_TiSync_convertSystemTickstoGTS(1);
	ut_rbl_TiSync_cloneToPureLocalTime(1);
	ut_rbl_TiSync_StbMAddNanoSeconds(1);
	ut_rbl_CustIf_GTS_LocalFallBackCheck(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_TiSync.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_TiSync_MMP2GtsTime(int doIt)
{
	if (doIt)
	{
		START_TEST("47563: [MMP2.11]UTC_rbl_CustIf_TiSync_MMP2GtsTime",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47563");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */
		uint32 timeMMP_u32;
		StbM_TimeStampType timeGTS_st;
		Std_ReturnType retVal = E_OK;
	    StbM_SynchronizedTimeBaseType TimeBaseId = 0;
	    StbM_TimeBaseStatusType syncTimeBaseStatus = 0;
	    StbM_TimeBaseStatusType offsetTimeBaseStatus = 0;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			timeMMP_u32 = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.secondsHi = 0;
			timeGTS_st.timeBaseStatus = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_TiSync_convertSystemTickstoGTS#rbl_TiSync_convertSystemTickstoGTS_1;"
						   "StbM_GetTimeBaseStatus#StbM_GetTimeBaseStatus_1;"
						   "rbl_CustIf_StbM_Monitor_Time_Rate_Copy#rbl_CustIf_StbM_Monitor_Time_Rate_Copy_1");

			  // Call SUT
			retVal=rbl_CustIf_TiSync_MMP2GtsTime(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

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

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_TiSync_convertSystemTickstoGTS#rbl_TiSync_convertSystemTickstoGTS_2;"
						   "rbl_CustIf_StbM_Monitor_Time_Rate_Copy#rbl_CustIf_StbM_Monitor_Time_Rate_Copy_1");

			  // Call SUT
			retVal=rbl_CustIf_TiSync_MMP2GtsTime(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

			END_CALLS();
			END_STEP();

		}
		END_TEST();
	}
}

void ut_rbl_TiSync_convertSystemTickstoGTS(int doIt)
{
	if (doIt)
	{
		START_TEST("49911: [MMP2.11]UTC_rbl_TiSync_convertSystemTickstoGTS",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49911");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

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
					       "rbl_TiSync_StbMAddNanoSeconds#rbl_TiSync_StbMAddNanoSeconds_1");

			// Call SUT
			retVal = ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

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
					       "rbl_TiSync_StbMAddNanoSeconds#rbl_TiSync_StbMAddNanoSeconds_2");

			// Call SUT
			retVal = ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, RBL_CUSTIF_SYNC_OK);
			check_global_data();

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
					       "RBSYS_ExitCorelocalIntlock#default");

			// Call SUT
			retVal = ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeMMP_u32, RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

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
					       "RBSYS_ExitCorelocalIntlock#default");

			// Call SUT
			retVal = ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

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
					       "RBSYS_ExitCorelocalIntlock#default");

			// Call SUT
			retVal = ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_convertSystemTickstoGTS(timeMMP_u32,&timeGTS_st);

			// Test case checks
			CHECK_U_INT(retVal,E_NOT_OK);
			CHECK_U_INT(timeMMP_u32, 0);
			CHECK_U_INT(timeGTS_st.nanoseconds, 0);
			CHECK_U_INT(timeGTS_st.seconds, 0);
			CHECK_U_INT(timeGTS_st.secondsHi, 0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus, 0);
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_TiSync_cloneToPureLocalTime(int doIt)
{
	if (doIt)
	{
		START_TEST("49921: [MMP2.11]UTC_rbl_TiSync_cloneToPureLocalTime",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49921");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */
	    Std_ReturnType retVal = E_NOT_OK;
	    StbM_TimeStampType timestampGTS_st = {0};
	    StbM_TimeBaseStatusType TimeBaseIdPureLocal = 32;
	    StbM_SynchronizedTimeBaseType TimeBaseId = 0;
	    StbM_UserDataType UserData_st = {0};
	    StbM_RateDeviationType rateDeviation = 0;
	    StbM_TimeBaseStatusType TimeStampStatus;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback) = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_3;"
					       "StbM_GetRateDeviation#StbM_GetRateDeviation_1;"
					       "rbl_TiSync_StbMAddNanoSeconds#rbl_TiSync_StbMAddNanoSeconds_3;"
			               "StbM_SetGlobalTime#StbM_SetGlobalTime_1;"
					       "StbM_SetRateCorrection#StbM_SetRateCorrection_1;"
			               "RBSYS_ExitCorelocalIntlock#default");

			/* Call SUT */
			rbl_TiSync_cloneToPureLocalTime();

			/* Test case checks */
			CHECK_U_CHAR(retVal, E_NOT_OK);
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback), FALSE);

		    END_CALLS();
			END_STEP();

		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback) = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSYS_EnterCorelocalIntlock#default;"
					       "StbM_GetCurrentTime#StbM_GetCurrentTime_3;"
					       "StbM_GetRateDeviation#StbM_GetRateDeviation_2;"
					       "Bfx_Prv_SetBit_u8u8_Inl#Bfx_Prv_SetBit_u8u8_Inl_1;"
			               "RBSYS_ExitCorelocalIntlock#default");

			/* Call SUT */
			rbl_TiSync_cloneToPureLocalTime();

			/* Test case checks */
			CHECK_U_CHAR(retVal, E_NOT_OK);
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_Gtslocalfallback), TRUE);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_TiSync_StbMAddNanoSeconds(int doIt)
{
	if (doIt)
	{
		START_TEST("49370: [MMP2.11]UTC_rbl_TiSync_StbMAddNanoSeconds",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49370");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */
		StbM_TimeStampType timeGTS_st;
		uint32 nanoseconds;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.secondsHi = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();

		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = RBL_CUSTIF_TISYNC_MAXSYSTICKS+1;
			timeGTS_st.seconds = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.secondsHi = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds,RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);
			CHECK_U_INT(timeGTS_st.seconds,0);
			CHECK_U_INT(timeGTS_st.secondsHi,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus,0);
			CHECK_U_INT(nanoseconds,RBL_CUSTIF_TISYNC_MAXSYSTICKS+1);
			check_global_data();

			END_CALLS();
			END_STEP();

		}

		START_STEP("3_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = -RBL_CUSTIF_TISYNC_MAXSYSTICKS-1;
			timeGTS_st.seconds = 0;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.secondsHi = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,RBL_CUSTIF_TISYNC_S2NS - RBL_CUSTIF_TISYNC_MAXSYSTICKS - 1);
			CHECK_U_INT(timeGTS_st.seconds ,0xFFFFFFFFu);
			CHECK_U_INT(timeGTS_st.secondsHi ,0xFFFF);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0xFD9DA5FF);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 1;
			timeGTS_st.nanoseconds = 0;
			timeGTS_st.secondsHi = 1;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,1);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 0x01;
			timeGTS_st.nanoseconds = RBL_CUSTIF_TISYNC_S2NS+1;
			timeGTS_st.secondsHi = 0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,1);
			CHECK_U_INT(timeGTS_st.seconds ,2);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("6_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 0xFFFFFFFF;
			timeGTS_st.nanoseconds = RBL_CUSTIF_TISYNC_S2NS+1;
			timeGTS_st.secondsHi = 1;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,1);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,2);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();

		}

		START_STEP("7_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 1;
			timeGTS_st.nanoseconds = -RBL_CUSTIF_TISYNC_S2NS;
			timeGTS_st.secondsHi = 1;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0);
			CHECK_U_INT(timeGTS_st.secondsHi ,1);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();

		}

		START_STEP("8_NTS", TRUE);
		{
			/* Test case data Initializations */
			nanoseconds = 0;
			timeGTS_st.seconds = 0xFFFFFFFF+0x1;
			timeGTS_st.nanoseconds = -RBL_CUSTIF_TISYNC_S2NS;
			timeGTS_st.secondsHi = 0x01;

			// Expected Call Sequence
			EXPECTED_CALLS("");

			  // Call SUT
			ACCESS_FUNCTION_rbl_CustIf_TiSync_rbl_TiSync_StbMAddNanoSeconds(&timeGTS_st, nanoseconds);

			// Test case checks
			CHECK_U_INT(timeGTS_st.nanoseconds ,0);
			CHECK_U_INT(timeGTS_st.seconds ,0xFFFFFFFF);
			CHECK_U_INT(timeGTS_st.secondsHi ,0);
			CHECK_U_INT(timeGTS_st.timeBaseStatus ,0);
			CHECK_U_INT(nanoseconds ,0);
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_GTS_LocalFallBackCheck(int doIt)
{
	if (doIt)
	{
		START_TEST("49371: [MMP2.11]UTC_rbl_CustIf_GTS_LocalFallBackCheck",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49371");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_IDLE;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_CHECK);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x01);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_IDLE;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_2");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */\
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_IDLE);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x01);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("3_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_IDLE;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x00;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_IDLE);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x00);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_CHECK;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x00;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x00);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_CHECK;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x01);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("6_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_CHECK;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x01);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("7_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_CHECK;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_2");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_CHECK);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x01);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("8_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK;
	        ACCESS_LOCAL_VARIABLE(rbl_CustIf_TiSync, rbl_CustIf_GTS_LocalFallBackCheck, cnt) = RBL_CUSTIF_PLOCWAITTIME;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_2");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_CHECK);
			CHECK_U_CHAR(ACCESS_LOCAL_VARIABLE(rbl_CustIf_TiSync, rbl_CustIf_GTS_LocalFallBackCheck, cnt), 0x01);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("9_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK;
	        ACCESS_LOCAL_VARIABLE(rbl_CustIf_TiSync, rbl_CustIf_GTS_LocalFallBackCheck, cnt) = 0x00;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_2");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(ACCESS_LOCAL_VARIABLE(rbl_CustIf_TiSync, rbl_CustIf_GTS_LocalFallBackCheck, cnt), 0x01);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("10_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_2;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("11_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_2;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("12_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, I_C02_GTS_ESP_CLK_STAT_ST3_INTERNAL_ESP_CLOCK_OK);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("13_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT;
	        RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3 = 0x00;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);
			CHECK_U_CHAR(RBMESG_rbl_CustIf_GTS_ESP_Clk_Stat_Bckp_ST3, 0x00);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("14_NTS", TRUE);
		{
			/* Test case data Initializations */
	        ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus) = GTS_LOCALFALLBACK_WAIT + 1;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#rbl_CustIf_StbM_Check_Init_Sync_1;"
					       "rbl_CustIf_StbM_Check_Lost_Sync#rbl_CustIf_StbM_Check_Lost_Sync_1;"
					       "rbl_CustIf_StbM_Check_TimeLeap#rbl_CustIf_StbM_Check_TimeLeap_1");

			/* Call SUT */
			rbl_CustIf_GTS_LocalFallBackCheck();

			/* Test case checks */
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_TiSync, rbl_Custif_GtslocalfallbackStatus), GTS_LOCALFALLBACK_WAIT);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSYS_EnterCommonLock_intern */
void RBSYS_EnterCommonLock_intern(){
    REGISTER_CALL("RBSYS_EnterCommonLock_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLock_intern */
void RBSYS_ExitCommonLock_intern(){
    REGISTER_CALL("RBSYS_ExitCommonLock_intern");

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

/* Stub for function RB_AssertHandleWithCond */
void RB_AssertHandleWithCond(_Bool isFailed,
                             const char * expr,
                             const char * file,
                             const char * func,
                             int line){
    REGISTER_CALL("RB_AssertHandleWithCond");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function StbM_GetTimeBaseStatus */
Std_ReturnType StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId,
                                      StbM_TimeBaseStatusType * syncTimeBaseStatus,
                                      StbM_TimeBaseStatusType * offsetTimeBaseStatus){
    REGISTER_CALL("StbM_GetTimeBaseStatus");

    IF_INSTANCE("StbM_GetTimeBaseStatus_1") {
        CHECK_U_CHAR(timeBaseId,0);
        CHECK_U_CHAR(* syncTimeBaseStatus,0);
        CHECK_U_CHAR(* offsetTimeBaseStatus,0);
        return E_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_StbM_Monitor_Time_Rate_Copy */
void rbl_CustIf_StbM_Monitor_Time_Rate_Copy(Dem_EventStatusType EventStatusTimeCopy,
                                            Dem_EventStatusType EventStatusRateCopy){
    REGISTER_CALL("rbl_CustIf_StbM_Monitor_Time_Rate_Copy");

    IF_INSTANCE("rbl_CustIf_StbM_Monitor_Time_Rate_Copy_1") {
        CHECK_U_CHAR(EventStatusTimeCopy,0x55);
        CHECK_U_CHAR(EventStatusRateCopy,0x55);
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
    CHECK_U_INT(timeBaseId,0x20);
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
   	CHECK_U_INT(timeBaseId,0x20);
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
    IF_INSTANCE("StbM_GetCurrentTime_3") {
    CHECK_U_INT(timeBaseId,0);
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
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function StbM_GetRateDeviation */
Std_ReturnType StbM_GetRateDeviation(StbM_SynchronizedTimeBaseType timeBaseId,
                                     StbM_RateDeviationType * rateDeviation){
    REGISTER_CALL("StbM_GetRateDeviation");

    IF_INSTANCE("StbM_GetRateDeviation_1") {
        return E_NOT_OK;
    }
    IF_INSTANCE("StbM_GetRateDeviation_2") {
        return E_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function StbM_SetGlobalTime */
Std_ReturnType StbM_SetGlobalTime(StbM_SynchronizedTimeBaseType timeBaseId,
                                  const StbM_TimeStampType * timeStamp,
                                  const StbM_UserDataType * userData){
    REGISTER_CALL("StbM_SetGlobalTime");

    IF_INSTANCE("StbM_SetGlobalTime_1") {
	CHECK_U_INT(timeBaseId,0x20);
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
    IF_INSTANCE("StbM_SetGlobalTime_2") {
    CHECK_U_INT(timeBaseId,0);
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

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function StbM_SetRateCorrection */
Std_ReturnType StbM_SetRateCorrection(StbM_SynchronizedTimeBaseType timeBaseId,
                                      StbM_RateDeviationType rateDeviation){
    REGISTER_CALL("StbM_SetRateCorrection");

    IF_INSTANCE("StbM_SetRateCorrection_1") {
        CHECK_U_INT(timeBaseId,0x20);
        CHECK_U_INT(rateDeviation,0);
        return E_NOT_OK;
    }
    IF_INSTANCE("StbM_SetRateCorrection_2") {
        CHECK_U_INT(timeBaseId,0);
        CHECK_U_INT(rateDeviation,0);
        return E_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_StbM_Check_Init_Sync */
boolean rbl_CustIf_StbM_Check_Init_Sync(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_Init_Sync");

    IF_INSTANCE("rbl_CustIf_StbM_Check_Init_Sync_1") {
        return TRUE;
    }
    IF_INSTANCE("rbl_CustIf_StbM_Check_Init_Sync_2") {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_StbM_Check_Lost_Sync */
boolean rbl_CustIf_StbM_Check_Lost_Sync(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_Lost_Sync");

    IF_INSTANCE("rbl_CustIf_StbM_Check_Lost_Sync_1") {
        return TRUE;
    }
    IF_INSTANCE("rbl_CustIf_StbM_Check_Lost_Sync_2") {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_StbM_Check_TimeLeap */
boolean rbl_CustIf_StbM_Check_TimeLeap(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_TimeLeap");

    IF_INSTANCE("rbl_CustIf_StbM_Check_TimeLeap_1") {
        return TRUE;
    }
    IF_INSTANCE("rbl_CustIf_StbM_Check_TimeLeap_2") {
        return FALSE;
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

/* Before-Wrapper for function RBSYS_EnterCommonLock */
int BEFORE_RBSYS_EnterCommonLock(){
    REGISTER_CALL("RBSYS_EnterCommonLock");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_EnterCommonLock */
void AFTER_RBSYS_EnterCommonLock(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_EnterCommonLock */
void REPLACE_RBSYS_EnterCommonLock(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCommonLock */
int BEFORE_RBSYS_ExitCommonLock(){
    REGISTER_CALL("RBSYS_ExitCommonLock");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_ExitCommonLock */
void AFTER_RBSYS_ExitCommonLock(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_ExitCommonLock */
void REPLACE_RBSYS_ExitCommonLock(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_TiSync_convertSystemTickstoGTS */
int BEFORE_rbl_TiSync_convertSystemTickstoGTS(uint32 timeMMP_u32,
                                              StbM_TimeStampType * timeGTS_st){
    REGISTER_CALL("rbl_TiSync_convertSystemTickstoGTS");

    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_1") {
		CHECK_U_INT(timeMMP_u32, 0);
		CHECK_U_INT(timeGTS_st->nanoseconds, 0);
		CHECK_U_INT(timeGTS_st->seconds, 0);
		CHECK_U_INT(timeGTS_st->secondsHi, 0);
		CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_2") {
		CHECK_U_INT(timeMMP_u32, 0);
		CHECK_U_INT(timeGTS_st->nanoseconds, 0);
		CHECK_U_INT(timeGTS_st->seconds, 0);
		CHECK_U_INT(timeGTS_st->secondsHi, 0);
		CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_TiSync_convertSystemTickstoGTS */
Std_ReturnType AFTER_rbl_TiSync_convertSystemTickstoGTS(Std_ReturnType cppsm_return_value,
                                                        uint32 timeMMP_u32,
                                                        StbM_TimeStampType * timeGTS_st){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_TiSync_convertSystemTickstoGTS */
Std_ReturnType REPLACE_rbl_TiSync_convertSystemTickstoGTS(uint32 timeMMP_u32,
                                                          StbM_TimeStampType * timeGTS_st){
    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_1") {
        return E_OK;
    }
    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_2") {
        return E_NOT_OK;
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

/* Before-Wrapper for function rbl_TiSync_StbMAddNanoSeconds */
int BEFORE_rbl_TiSync_StbMAddNanoSeconds(StbM_TimeStampType * timeGTS_st,
                                         uint32 nanoseconds){
    REGISTER_CALL("rbl_TiSync_StbMAddNanoSeconds");

    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_1") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
    	CHECK_U_INT(nanoseconds, 0);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_2") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
    	CHECK_U_INT(nanoseconds, 0);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_3") {
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
    	CHECK_U_INT(nanoseconds, RBL_CUSTIF_CLONING_DELAY_NS);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_TiSync_StbMAddNanoSeconds */
void AFTER_rbl_TiSync_StbMAddNanoSeconds(struct cppsm_void_return cppsm_dummy,
                                         StbM_TimeStampType * timeGTS_st,
                                         uint32 nanoseconds){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_TiSync_StbMAddNanoSeconds */
void REPLACE_rbl_TiSync_StbMAddNanoSeconds(StbM_TimeStampType * timeGTS_st,
                                           uint32 nanoseconds){

    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_1") {
        return;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_2") {
        return;
    }
    IF_INSTANCE("rbl_TiSync_StbMAddNanoSeconds_3") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function Bfx_Prv_SetBit_u8u8_Inl */
int BEFORE_Bfx_Prv_SetBit_u8u8_Inl(uint8 * Data,
                                   uint8 BitPn){
    REGISTER_CALL("Bfx_Prv_SetBit_u8u8_Inl");

    IF_INSTANCE("Bfx_Prv_SetBit_u8u8_Inl_1") {
    	CHECK_U_CHAR(*Data,0x00);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_SYNC2PURELOCAL_TIMEBASE_BflPn);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function Bfx_Prv_SetBit_u8u8_Inl */
void AFTER_Bfx_Prv_SetBit_u8u8_Inl(struct cppsm_void_return cppsm_dummy,
                                   uint8 * Data,
                                   uint8 BitPn){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function Bfx_Prv_SetBit_u8u8_Inl */
void REPLACE_Bfx_Prv_SetBit_u8u8_Inl(uint8 * Data,
                                     uint8 BitPn){

    IF_INSTANCE("Bfx_Prv_SetBit_u8u8_Inl_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

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
