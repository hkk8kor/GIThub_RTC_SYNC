/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_Main.c
 *    Author: GDEV1KOR
 *    Generated on: 14-Apr-2024 13:49:04
 *    Generated from: rbl_CustIf_Main.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_CustIf_Pub.h"
#include "rbl_CustIf_OsPub.h"
#include "rbl_CustIf_Main.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "rbl_CustIf_FBL_Cfg_Star3_ST3.h"
#include "rbl_CustIf_DIAG_Stat_ST3.h"
#include "rbl_CustIf_Ign_Stat_ST3.h"
#include "rbl_CustIf_DI_OdoSpeedometer_ST3.h"
#include "rbl_CustIf_VehSpd_Disp_ST3.h"
#include "rbl_CustIf_ECU_Stat_IMU_X_ST3.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Measurement.h"
#include "rbl_CustIf_PT4_PTCoor4_ST3.h"
#include "rbl_CustIf_PN14_Master_Stat1_ST3.h"
#include "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3.h"
#include "rbl_CustIf_Meas_IMU_X_ST3.h"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "rbl_CustIf_VSS_TP_Auth_ST3.h"
#include "rbl_CustIf_VSS_TP_RealTmOffset_ST3.h"
#include "rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.h"
#include "rbl_CustIf_VSS_TP_SharedSecret_ST3.h"
#include "rbl_CustIf_VSS_TP_VIN_ST3.h"
#endif
#if(RBFS_MMP2 == RBFS_MMP2_IMUA)
#include "rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3.h"
#endif
#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
#include "rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3.h"
#endif
#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
#include "rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h"
#include "rbl_CustIf_IMU_D_Stat_ST3.h"
#include "rbl_CustIf_ECU_Stat_IMU_D_ST3.h"
#endif
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
#include "rbl_CustIf_GTS_Monitoring.h"
#include "rbl_CustIf_TiSync.h"
#endif

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_rbl_CustIf_Main_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_Main_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
void rbl_CustIf_IMU_Output_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData, const rbl_ImuStdTypes_ImuSignalSet_t * imu_derivedData);
void rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData, const rbl_ImuStdTypes_ImuSignalSet_t * imu_derivedData);
void rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData);
void rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive();
void rbl_CustIf_DIAG_Stat_ST3_PDU_Receive();
void rbl_CustIf_Ign_Stat_ST3_PDU_Receive();
void rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive();
void rbl_CustIf_VehSpd_Disp_ST3_Receive();
void rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive();
void rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();
void rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive();
void rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update();
void rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive();
void rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update();
void rbl_CustIf_GTS_Monitoring();
void rbl_CustIf_GTS_LocalFallBackCheck();

/* Global data */
volatile RBMESG_Type_SigChain_FinalDer RBMESG_SigChain_FinalDer;
volatile RBMESG_Type_SigChain_FinalFil RBMESG_SigChain_FinalFil;
volatile RBMESG_Type_SigChain_FinalDer2 RBMESG_SigChain_FinalDer2;
volatile RBMESG_Type_SigChain_FinalFil2 RBMESG_SigChain_FinalFil2;
typedef struct rbl_CustIf_Main_av_struct { uint8 * ref_rbl_CustIf_SysSt; uint32 * ref_rbl_CustIf_SwtTestModEna; rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_CustIf_filtered_ImuSignalSet_st_test; rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_CustIf_Derived_ImuSignalSet_st_test; } rbl_CustIf_Main_av_struct;
extern rbl_CustIf_Main_av_struct av_rbl_CustIf_Main;

/* Expected variables for global data */
RBMESG_Type_SigChain_FinalDer expected_RBMESG_SigChain_FinalDer;
RBMESG_Type_SigChain_FinalFil expected_RBMESG_SigChain_FinalFil;
RBMESG_Type_SigChain_FinalDer2 expected_RBMESG_SigChain_FinalDer2;
RBMESG_Type_SigChain_FinalFil2 expected_RBMESG_SigChain_FinalFil2;
typedef struct expected_rbl_CustIf_Main_av_struct { uint8 ref_rbl_CustIf_SysSt; uint32 ref_rbl_CustIf_SwtTestModEna; rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_CustIf_filtered_ImuSignalSet_st_test; rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_CustIf_Derived_ImuSignalSet_st_test; } expected_rbl_CustIf_Main_av_struct;
expected_rbl_CustIf_Main_av_struct expected_av_rbl_CustIf_Main;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(RBMESG_SigChain_FinalDer);
    INITIALISE(RBMESG_SigChain_FinalFil);
    INITIALISE(RBMESG_SigChain_FinalDer2);
    INITIALISE(RBMESG_SigChain_FinalFil2);
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna));
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test));
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test));
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SysSt));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalDer, expected_RBMESG_SigChain_FinalDer);
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalFil, expected_RBMESG_SigChain_FinalFil);
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalDer2, expected_RBMESG_SigChain_FinalDer2);
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalFil2, expected_RBMESG_SigChain_FinalFil2);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SysSt), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SysSt));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("RBMESG_SigChain_FinalDer", &RBMESG_SigChain_FinalDer, &expected_RBMESG_SigChain_FinalDer, sizeof(expected_RBMESG_SigChain_FinalDer));
    CHECK_MEMORY("RBMESG_SigChain_FinalFil", &RBMESG_SigChain_FinalFil, &expected_RBMESG_SigChain_FinalFil, sizeof(expected_RBMESG_SigChain_FinalFil));
    CHECK_MEMORY("RBMESG_SigChain_FinalDer2", &RBMESG_SigChain_FinalDer2, &expected_RBMESG_SigChain_FinalDer2, sizeof(expected_RBMESG_SigChain_FinalDer2));
    CHECK_MEMORY("RBMESG_SigChain_FinalFil2", &RBMESG_SigChain_FinalFil2, &expected_RBMESG_SigChain_FinalFil2, sizeof(expected_RBMESG_SigChain_FinalFil2));
    CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)));
    CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SysSt), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SysSt));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_10ms_Proc(int);
void ut_rbl_CustIf_5ms_Proc(int);
void ut_rbl_CustIf_GetSystemState(int);
void ut_rbl_CustIf_20ms_Proc(int);
void ut_rbl_CustIf_Monitoring_20ms_Proc(int);
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
    OPEN_LOG("ut_rbl_CustIf_Main.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_Main", true);

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
    ut_rbl_CustIf_10ms_Proc(1);
	ut_rbl_CustIf_5ms_Proc(1);
	ut_rbl_CustIf_GetSystemState(1);
	ut_rbl_CustIf_20ms_Proc(1);
	ut_rbl_CustIf_Monitoring_20ms_Proc(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_Main.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_10ms_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("46998: [MMP2.11]UTC_rbl_CustIf_10ms_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46998");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			//Expected Call Sequence
			EXPECTED_CALLS("");

			//Call SUT
			rbl_CustIf_10ms_Proc();

			//Test case checks
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_5ms_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("46999: [MMP2.11]UTC_rbl_CustIf_5ms_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46999");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

#if (RBFS_ConfigurationType == RBFS_ConfigurationType_DEVELOP)
		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna) = RBL_IMUSTDTYPES_TEST_MOD_ENAD;

			// Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
					       "RBSYS_ExitCommonLockSysfast_intern#default;"
					       "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
					       "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
						   "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
						   "rbl_CustIf_IMU_Output_ST3_PDU_Update#rbl_CustIf_IMU_Output_ST3_PDU_Update_1");

			// Call SUT
			rbl_CustIf_5ms_Proc();

			// Test case checksF
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna), RBL_IMUSTDTYPES_TEST_MOD_ENAD);

			END_CALLS();
			END_STEP();

		}
	#endif

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
			ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna) = 0x00;

			// Expected Call Sequence
			EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
					       "RBSYS_ExitCommonLockSysfast_intern#default;"
					       "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
					       "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
						   "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default;"
						   "rbl_CustIf_IMU_Output_ST3_PDU_Update#rbl_CustIf_IMU_Output_ST3_PDU_Update_1;"
#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
						   "rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update#rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update_1;"
						   "rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3#default");
#endif

			// Call SUT
			rbl_CustIf_5ms_Proc();

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_SwtTestModEna), 0x00);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_GetSystemState(int doIt)
{
	if (doIt)
	{
		START_TEST("47077: [MMP2.11]UTC_rbl_CustIf_GetSystemState",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47077");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			// Expected Call Sequence
			EXPECTED_CALLS("");

			// Call SUT
			rbl_CustIf_GetSystemState();

			// Test case checks
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_20ms_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("47822: [MMP2.11]UTC_rbl_CustIf_20ms_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47822");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

		   //Expected Call Sequence
		   EXPECTED_CALLS("rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive#default;"
						   "rbl_CustIf_DIAG_Stat_ST3_PDU_Receive#default;"
						   "rbl_CustIf_Ign_Stat_ST3_PDU_Receive#default;"
						   "rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive#default;"
						   "rbl_CustIf_VehSpd_Disp_ST3_Receive#default;"
						   "rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive#default;"
						   "rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive#default;"
						   "rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive#default;"
						   "rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update#default;"
#if(RBFS_MMP2 == RBFS_MMP2_IMUA)
				           "rbl_CustIf_ADAS_HAD_Stat_IDC_S_FSI_Bckp_ST3_PDU_Receive#default;"
#endif
#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
				           "rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive#default;"
#endif
#if(RBFS_DrivingCANSignals == RBFS_DrivingCANSignals_ON)
					       "rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update#default");

#endif

			// Call SUT
			rbl_CustIf_20ms_Proc();

			// Test case checks
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
		}
}

void ut_rbl_CustIf_Monitoring_20ms_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("48760: [MMP2.11]UTC_rbl_CustIf_Monitoring_20ms_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48760");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			//Expected Call Sequence
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
			EXPECTED_CALLS("rbl_CustIf_GTS_Monitoring#default;"
					       "rbl_CustIf_GTS_LocalFallBackCheck#default");
#endif
			// Call SUT
			rbl_CustIf_Monitoring_20ms_Proc();

			// Test case checks
			check_global_data();

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

/* Stub for function rbl_CustIf_IMU_Output_ST3_PDU_Update */
void rbl_CustIf_IMU_Output_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData,
                                          const rbl_ImuStdTypes_ImuSignalSet_t * imu_derivedData){
    REGISTER_CALL("rbl_CustIf_IMU_Output_ST3_PDU_Update");

    IF_INSTANCE("rbl_CustIf_IMU_Output_ST3_PDU_Update_1") {
        CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)));
        CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)));
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update */
void rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData,
                                                                            const rbl_ImuStdTypes_ImuSignalSet_t * imu_derivedData){
    REGISTER_CALL("rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update");

    IF_INSTANCE("rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update_1") {
        CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)));
        CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_Derived_ImuSignalSet_st_test)));
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3 */
void rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * imu_FilData){
    REGISTER_CALL("rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3");

    IF_INSTANCE("default") {
        CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)", &ACCESS_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Main, rbl_CustIf_filtered_ImuSignalSet_st_test)));
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive */
void rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_FBL_Cfg_Star3_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_DIAG_Stat_ST3_PDU_Receive */
void rbl_CustIf_DIAG_Stat_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_DIAG_Stat_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_Ign_Stat_ST3_PDU_Receive */
void rbl_CustIf_Ign_Stat_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_Ign_Stat_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive */
void rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_DI_OdoSpeedometer_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_VehSpd_Disp_ST3_Receive */
void rbl_CustIf_VehSpd_Disp_ST3_Receive(){
    REGISTER_CALL("rbl_CustIf_VehSpd_Disp_ST3_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive */
void rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_PT4_PTCoor4_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive */
void rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive */
void rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive(){
    REGISTER_CALL("rbl_CustIf_BCS_Whl_Msg1_BTC_ST3_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update */
void rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update(){
    REGISTER_CALL("rbl_CustIf_ECU_Stat_IMU_X_ST3_PDU_Update");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive */
void rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive(){
    REGISTER_CALL("rbl_CustIf_ADAS_HAD_Stat_IDC_M_FSI_ST3_PDU_Receive");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update */
void rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update(){
    REGISTER_CALL("rbl_CustIf_ECU_Stat_IMU_D_ST3_PDU_Update");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_GTS_Monitoring */
void rbl_CustIf_GTS_Monitoring(){
    REGISTER_CALL("rbl_CustIf_GTS_Monitoring");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_CustIf_GTS_LocalFallBackCheck */
void rbl_CustIf_GTS_LocalFallBackCheck(){
    REGISTER_CALL("rbl_CustIf_GTS_LocalFallBackCheck");

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

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
