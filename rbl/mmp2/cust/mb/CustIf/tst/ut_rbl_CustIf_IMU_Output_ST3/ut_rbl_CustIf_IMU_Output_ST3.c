/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_IMU_Output_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 10-Apr-2024 12:11:25
 *    Generated from: rbl_CustIf_IMU_Output_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_ImuOutPutStdTypes.h"
#include "cc_int_parts.h"
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
#include "rbl_CustIf_TiSync.h"
#endif

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern _Bool ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_cc_is_bit_set_u8(uint8_t value, unsigned int bit_position);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(uint8 Status);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(uint8 StatusX, uint8 StatusY, uint8 StatusZ);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_RB_FloatToInt_f32_u8(float32 var_f32);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_RBSYS_ExitCommonLockSysfast();
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_IMU_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_AngAcc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_timeStamp(uint32 MMPtimeStamp);
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
Std_ReturnType Dem_GetMonitorStatus(Dem_EventIdType EventID, Dem_MonitorStatusType * MonitorStatus);
Std_ReturnType Dem_GetComponentFailed(Dem_ComponentIdType ComponentId, boolean * ComponentFailed);
float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters, float32 phy_value);
uint16 rbl_CustIf_Calc_Convert(float32 value, float32 formula, const CompuMethod * parameter);
Std_ReturnType rbl_CustIf_TiSync_MMP2GtsTime(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st);

/* Global data */
volatile RBMESG_Type_SigChain_FinalRaw RBMESG_SigChain_FinalRaw;
extern volatile RBMESG_Type_rbl_CustIf_IMU_OutPutMsg_ST3 RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3;
typedef struct rbl_CustIf_IMU_Output_ST3_av_struct { rbl_CustIf_OutputMsg_ST3_st * ref_rbl_CustIf_ImuSigData; const CompuMethod(* ref_rbl_CustIf_compu_param)[4]; } rbl_CustIf_IMU_Output_ST3_av_struct;
extern rbl_CustIf_IMU_Output_ST3_av_struct av_rbl_CustIf_IMU_Output_ST3;

/*input variable initialization */
rbl_ImuStdTypes_ImuSignalSet_t imu_FilData;
rbl_ImuStdTypes_ImuSignalSet_t imu_derivedData;

/* Expected variables for global data */
RBMESG_Type_SigChain_FinalRaw expected_RBMESG_SigChain_FinalRaw;
RBMESG_Type_rbl_CustIf_IMU_OutPutMsg_ST3 expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3;
typedef struct expected_rbl_CustIf_IMU_Output_ST3_av_struct { rbl_CustIf_OutputMsg_ST3_st ref_rbl_CustIf_ImuSigData; CompuMethod ref_rbl_CustIf_compu_param[4]; } expected_rbl_CustIf_IMU_Output_ST3_av_struct;
expected_rbl_CustIf_IMU_Output_ST3_av_struct expected_av_rbl_CustIf_IMU_Output_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No initialisation for const data: rbl_CustIf_compu_param */
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData));
    INITIALISE(RBMESG_SigChain_FinalRaw);
    INITIALISE(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData));
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalRaw, expected_RBMESG_SigChain_FinalRaw);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData)", &ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData)));
    CHECK_MEMORY("RBMESG_SigChain_FinalRaw", &RBMESG_SigChain_FinalRaw, &expected_RBMESG_SigChain_FinalRaw, sizeof(expected_RBMESG_SigChain_FinalRaw));
    CHECK_MEMORY("RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3", &RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3, &expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3, sizeof(expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_checkBits(int);
void ut_rbl_CustIf_PrepareStatus(int);
void ut_rbl_CustIf_Prepare_IMU_Stat_ST3(int );
void ut_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(int );
void ut_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(int );
void ut_rbl_CustIf_Prepare_Temp(int );
void ut_rbl_CustIf_Prepare_AngAcc(int );
void ut_rbl_CustIf_Prepare_Rate(int );
void ut_rbl_CustIf_Prepare_Acc(int );
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
void ut_rbl_CustIf_Prepare_timeStamp(int );
#endif
void ut_rbl_CustIf_IMU_Output_ST3_PDU_Update (int );
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
    OPEN_LOG("ut_rbl_CustIf_IMU_Output_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_IMU_Output_ST3", true);

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
	ut_rbl_CustIf_checkBits(1);
	ut_rbl_CustIf_PrepareStatus(1);
	ut_rbl_CustIf_Prepare_IMU_Stat_ST3(1);
	ut_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(1);
	ut_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(1);
	ut_rbl_CustIf_Prepare_Temp(1);
	ut_rbl_CustIf_Prepare_AngAcc(1);
	ut_rbl_CustIf_Prepare_Rate(1);
	ut_rbl_CustIf_Prepare_Acc(1);
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
	ut_rbl_CustIf_Prepare_timeStamp(1);
#endif
	ut_rbl_CustIf_IMU_Output_ST3_PDU_Update(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_IMU_Output_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_checkBits(int doIt)
{
	if (doIt)
	{
		/*initialise_globals*/
		uint8 Status;
		uint8 Interanl_SigStatus;
		initialise_global_data();
		initialise_expected_global_data();

		START_TEST("49387: [MMP2.11]UTC_rbl_CustIf_checkBits",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49387");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_INIT_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_1");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_INIT_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_PERM_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_2;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_3");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_PERM_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("3_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_4;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_5;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_6");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("4_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_7;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_8;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_9;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_10");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("5_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_TEMP_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_11;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_12;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_13;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_14;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_15");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_TEMP_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("6_NTS", true);
		{
			/*initialise_globals */
			Status = RBL_CUSTIF_TEMP_STATUS_BIT_POS;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("cc_is_bit_set_u8#cc_is_bit_set_u8_11;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_12;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_13;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_14;"
					       "cc_is_bit_set_u8#cc_is_bit_set_u8_16");

			/* Call SUT */
			Interanl_SigStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_checkBits(Status);

			/* Test step checks */
			CHECK_U_CHAR(Status, RBL_CUSTIF_TEMP_STATUS_BIT_POS);
			CHECK_U_CHAR(Interanl_SigStatus, RBL_CUSTIF_INTERNAL_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_PrepareStatus(int doIt)
{
	if (doIt)
	{
		/*initialise_globals*/
		uint8 ret_SigStaus;
		uint8 StatusX;
		uint8 StatusY;
		uint8 StatusZ;
		Dem_MonitorStatusType MonitorStatus = 0;
		initialise_global_data();
		initialise_expected_global_data();

		START_TEST("49388: [MMP2.11]UTC_rbl_CustIf_PrepareStatus",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49388");

		/* Test steps*/
		START_STEP("1_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_2");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_INIT);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_2");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_INIT);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("3_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_2");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_INIT);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("4_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("5_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_3");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_PERMANENT_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("6_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_3");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_PERMANENT_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("7_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_3");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_PERMANENT_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("8_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("9_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_4");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_SPORADIC_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("10_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_4");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_SPORADIC_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("11_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_4");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_SPORADIC_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("12_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("13_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_5");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_TEMP_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("14_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_5");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_TEMP_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("15_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_5");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_TEMP_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("16_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_2;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_TEMP_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("17_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_3;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("18_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_6");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_OVERLOAD_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("19_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "rbl_CustIf_checkBits#rbl_CustIf_checkBits_1;"
					       "2*rbl_CustIf_checkBits#rbl_CustIf_checkBits_6");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_OVERLOAD_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("20_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;
			StatusY = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;
			StatusZ = RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_6");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_OVERLOAD_ERROR);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("21_NTS", TRUE);
		{
			/*initialise_globals*/
			StatusX = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusY = RBL_CUSTIF_SIGSTATUS_INIT;
			StatusZ = RBL_CUSTIF_SIGSTATUS_INIT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_GetMonitorStatus#Dem_GetMonitorStatus_1;"
					       "3*rbl_CustIf_checkBits#rbl_CustIf_checkBits_1");

			/* Call SUT */
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_PrepareStatus(StatusX,StatusY,StatusZ);

			/* Test step checks */
			CHECK_U_CHAR(StatusX,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusY,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_CHAR(StatusZ,RBL_CUSTIF_SIGSTATUS_INIT);
			CHECK_U_INT(ret_SigStaus, RBL_CUSTIF_SIGSTATUS_VALID);
			check_global_data();

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_IMU_Stat_ST3(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t SignalSet;
		uint8 ret_ImuStatus;

		START_TEST("46994: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_Stat_ST3",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46994");

		START_STEP("1_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_1;"
					       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_INIT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
				           "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
		                   "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_INIT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("3_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_OPERATIONAL);

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Ecu;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#uCMemoryGuard;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("6_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#MMP_SyncError;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("7_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#MMP_NvM_FreqContent;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("8_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#MMP_SignalChain;"
					       "Dem_GetComponentFailed#Component_failed;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}

		START_STEP("9_NTS", TRUE);
		{
			//INITIAL CONDITIONS.

			//Expected Call Sequence
			EXPECTED_CALLS("Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#Component_failed;"
					       "Dem_GetComponentFailed#ChargePump;"
			               "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
	                       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2");

			// Call SUT
			ret_ImuStatus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Stat_ST3(&SignalSet);

			// Test case checks
			CHECK_U_INT(ret_ImuStatus,RBL_CUSTIF_IMU_STATUS_ERROR_PERMENENT);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;
		uint8 ret_SigStaus;

		START_TEST("46993: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_Signal_Status_Acc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46993");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_PrepareStatus#rbl_CustIf_PrepareStatus_1");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(&l_SignalSet);

			// Test case checks
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_SIGSTATUS_INIT);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;
		uint8 ret_SigStaus;

		START_TEST("46992: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_Signal_Status_Acc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46992");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_PrepareStatus#rbl_CustIf_PrepareStatus_2");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(&l_SignalSet);

			// Test case checks
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_SIGSTATUS_INIT);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_Temp(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;

		START_TEST("46990: [MMP2.11]UTC_rbl_CustIf_Prepare_Temp",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46990");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			l_SignalSet.temp[0].value =0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue = 0.1f;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue = 0.00f;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Calc_CompuMethod_Phy2Int#Stub_Prepare_Temp;"
					       "RB_FloatToInt_f32_u8#RB_FloatToInt_f32_u8_1");
			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_IMU_Prepare_Temp(&l_SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_AngAcc(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;
		rbl_ImuStdTypes_ImuSignalSet_t Raw_SignalSet;

		START_TEST("46989: [MMP2.11]UTC_rbl_CustIf_Prepare_AngAcc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46989");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_X][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Y][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Z][0].value = 60000.00;

			/*initialize raw signal */
			memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = 60000;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = 60000;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = 60000;

			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = RBL_CUSTIF_IMU_ACC_RATE_INIT;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = RBL_CUSTIF_IMU_ACC_RATE_INIT;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_AngAcc(&l_SignalSet,&Raw_SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ);

			END_CALLS();
			END_STEP();
		}
		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_X][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Y][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Z][0].value = 60000.00;

			/*initialize raw signal */
			memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = 0;

			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = 60000;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = 60000;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = 60000;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2\
					        3*rbl_CustIf_Calc_Convert#rbl_CustIf_Calc_Convert_1");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_AngAcc(&l_SignalSet,&Raw_SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_Rate(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;
		rbl_ImuStdTypes_ImuSignalSet_t Raw_SignalSet;

		START_TEST("46988: [MMP2.11]UTC_rbl_CustIf_Prepare_Rate",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46988");

		START_STEP("1_NTS", TRUE);
		{
					// INITIAL CONDITIONS
					l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_X][0].value = 60000.00;
					l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Y][0].value = 60000.00;
					l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Z][0].value = 60000.00;

					/*initialize raw signal */
					memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX =60000;
					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = 60000;
					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ =60000;

					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX =RBL_CUSTIF_IMU_ACC_RATE_INIT;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ =RBL_CUSTIF_IMU_ACC_RATE_INIT;

					// Expected Call Sequence
					EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1");

					// Call SUT
		            ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Rate(&l_SignalSet,&Raw_SignalSet);

					// Test case checks
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ);

					END_CALLS();
					END_STEP();
       }

		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_X][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Y][0].value = 60000.00;
			l_SignalSet.rate[RBL_IMUSTDTYPES_AXIS_Z][0].value = 60000.00;

			/*initialize raw signal */
			memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX =0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ =0;

			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX = 60000;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = 60000;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ =60000;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2;"
					       "3*rbl_CustIf_Calc_Convert#rbl_CustIf_Calc_Convert_1");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Rate(&l_SignalSet,&Raw_SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_Acc(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		rbl_ImuStdTypes_ImuSignalSet_t l_SignalSet;
		rbl_ImuStdTypes_ImuSignalSet_t Raw_SignalSet;

		START_TEST("46984: [MMP2.11]UTC_rbl_CustIf_Prepare_Acc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46984");

		START_STEP("1_NTS", TRUE);
				{
					// INITIAL CONDITIONS
					l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_X][0].value = 50000.00;
					l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_Y][0].value = 50000.00;
					l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_Z][0].value = 50000.00;

					/*initialize raw signal */
					memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = 0;
					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY =0;
					ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = 0;

					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = RBL_CUSTIF_IMU_ACC_RATE_INIT;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY = RBL_CUSTIF_IMU_ACC_RATE_INIT;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = RBL_CUSTIF_IMU_ACC_RATE_INIT;

					// Expected Call Sequence
					EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_1");

					// Call SUT
					ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Acc(&l_SignalSet,&Raw_SignalSet);

					// Test case checks
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ);

					END_CALLS();
					END_STEP();
				}
		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_X][0].value = 50000.00;
			l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_Y][0].value = 50000.00;
			l_SignalSet.acc[RBL_IMUSTDTYPES_AXIS_Z][0].value = 50000.00;

			/*initialize raw signal */
			memset((void*)&Raw_SignalSet, 0x00, sizeof(Raw_SignalSet));

			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY =0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = 0;

			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = 25509;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY = 25509;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = 25509;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2;"
					       "3*rbl_CustIf_Calc_Convert#rbl_CustIf_Calc_Convert_2");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_Acc(&l_SignalSet,&Raw_SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
void ut_rbl_CustIf_Prepare_timeStamp(int doIt)
{
	if (doIt)
	{
		//Test case data declarations
		uint32 MMPtimeStamp = 0;

		START_TEST("47565: [MMP2.11]UTC_rbl_CustIf_IMU_Output_ST3_Prepare_timeStamp",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47565");

		START_STEP("1_NTS", TRUE);
	    {
			// INITIAL CONDITIONS
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 0;

			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0xC;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 100;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 200;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_TiSync_MMP2GtsTime#Stub_rbl_CustIf_TiSync_MMP2GtsTime_001;");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_timeStamp(MMPtimeStamp);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec);

			END_CALLS();
			END_STEP();
	   }

	  START_STEP("2_NTS", TRUE);
		{
		    // INITIAL CONDITIONS
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 0;
			ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 0;
;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 0 ;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_TiSync_MMP2GtsTime#Stub_rbl_CustIf_TiSync_MMP2GtsTime_002;");

			// Call SUT
		    ACCESS_FUNCTION_rbl_CustIf_IMU_Output_ST3_rbl_CustIf_Prepare_timeStamp(MMPtimeStamp);

		    // Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec);

		  END_CALLS();
		  END_STEP();
		}
	END_TEST();
	}
}
#endif

void ut_rbl_CustIf_IMU_Output_ST3_PDU_Update(int doIt)
{
	if (doIt)
		{
		START_TEST("47007: [MMP2.11]UTC_rbl_CustIf_IMU_Output_ST3_PDU_Update",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47007");

	START_STEP("1_NTS", TRUE);
	{
		memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
		memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

		/* raw signal value */
		memset((void*)&RBMESG_SigChain_FinalRaw, 0x01, sizeof(RBMESG_SigChain_FinalRaw));

		/* expected value for raw signals */
		memcpy((void*)&expected_RBMESG_SigChain_FinalRaw, (void*)&RBMESG_SigChain_FinalRaw, (size_t)sizeof(RBMESG_SigChain_FinalRaw));

		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc = 65535;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc = 254;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).ImuStat = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngAccStat = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateStat = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccStat = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_1 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_2 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_3 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_4 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_5 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_6 = 0x00;
		ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_7 = 0x00;

		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc = ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc = ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).ImuStat = RBL_CUSTIF_IMU_STATUS_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngAccStat = RBL_CUSTIF_IMU_STATUS_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateStat = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccStat = RBL_CUSTIF_IMU_STATUS_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec = 0x00;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_1 = RBL_CUSTIF_IMU_RESERVED1_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_2 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_3 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_4 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_5 = RBL_CUSTIF_IMU_RESERVED2TO5_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_6 = RBL_CUSTIF_IMU_RESERVED6_INIT;
		ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_7 = RBL_CUSTIF_IMU_RESERVED7_INIT;

		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Crc = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Sqc = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.ImuStat = RBL_CUSTIF_SIGSTATUS_INIT;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngAccStat = RBL_CUSTIF_SIGSTATUS_INIT;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateStat = RBL_CUSTIF_SIGSTATUS_INIT;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccStat = RBL_CUSTIF_SIGSTATUS_INIT;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Tempvalue = RBL_CUSTIF_IMU_TEMP_INIT;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TymsyncStat = RBL_CUSTIF_IMU_GTSSTATUS_NOTAVAILABLE;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccX = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccY = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccZ = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateX = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateY = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateZ = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccX = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccY = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccZ = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampnanosec = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampsec = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_1 = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_2 = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_3= 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_4 = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_5 = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_6 = 0;
		RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7 = 0;

		// expected RBMSG varible are initialized
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Crc = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Sqc = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.ImuStat = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).ImuStat;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngAccStat = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngAccStat;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateStat = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateStat;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccStat = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccStat;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Tempvalue = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TymsyncStat = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccX = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccY = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccZ = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateX = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateY = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateZ = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccX = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccY = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccZ = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampnanosec = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampsec = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_1 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_1;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_2 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_2;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_3= ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_3;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_4 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_4;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_5 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_5;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_6 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_6;
		expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7 = ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_7;

		// Expected Call Sequence
		EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#default;"
					   "RBSYS_EnterCommonLockSysfast_intern#default;"
				       "RBSYS_ExitCommonLockSysfast#default;"
					   "RBSYS_ExitCommonLockSysfast_intern#default;"
				       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1;"
				       "rbl_CustIf_Prepare_IMU_Signal_Status_Rate#rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2;"
				       "rbl_CustIf_Prepare_IMU_Signal_Status_Acc#rbl_CustIf_Prepare_IMU_Signal_Status_Acc_1;"
				       "rbl_CustIf_Prepare_IMU_Stat_ST3#rbl_CustIf_Prepare_IMU_Stat_ST3_1;"
				       "rbl_CustIf_IMU_Prepare_Temp#rbl_CustIf_IMU_Prepare_Temp_1;"
				       "rbl_CustIf_Prepare_AngAcc#rbl_CustIf_Prepare_AngAcc_1;"
				       "rbl_CustIf_Prepare_Rate#rbl_CustIf_Prepare_Rate_1;"
				       "rbl_CustIf_Prepare_Acc#rbl_CustIf_Prepare_Acc_1;"
                       "rbl_CustIf_Prepare_timeStamp#rbl_CustIf_Prepare_timeStamp_1;"
				       "RBSYS_EnterCommonLockSysfast#default;"
					   "RBSYS_EnterCommonLockSysfast_intern#default;"
				       "RBSYS_ExitCommonLockSysfast#default;"
				       "RBSYS_ExitCommonLockSysfast_intern#default");


		// Call SUT
		rbl_CustIf_IMU_Output_ST3_PDU_Update(&imu_FilData,&imu_derivedData);

		// Test case checks
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Crc);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Sqc);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).ImuStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).ImuStat);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngAccStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngAccStat);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateStat);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccStat);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Tempvalue);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TymsyncStat);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccX);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccY);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AngaccZ);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateX);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateY);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).RateZ);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccX);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccY);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).AccZ);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampnanosec);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec, ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).TempStampsec);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_1, RBL_CUSTIF_IMU_RESERVED1_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_2, RBL_CUSTIF_IMU_RESERVED2TO5_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_3, RBL_CUSTIF_IMU_RESERVED2TO5_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_4, RBL_CUSTIF_IMU_RESERVED2TO5_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_5, RBL_CUSTIF_IMU_RESERVED2TO5_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_6, RBL_CUSTIF_IMU_RESERVED6_INIT);
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_Output_ST3, rbl_CustIf_ImuSigData).Reserved_7, RBL_CUSTIF_IMU_RESERVED7_INIT);

		// checking the  RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3 varaible updated with global values
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Crc , expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Crc);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Sqc , expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Sqc);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.ImuStat,expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.ImuStat);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngAccStat ,expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngAccStat);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateStat, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateStat);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccStat, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccStat);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Tempvalue, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Tempvalue);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TymsyncStat, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TymsyncStat);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccX, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccX);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccY, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccY);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccZ, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AngaccZ);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateX, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateX);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateY, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateY);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateZ, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.RateZ);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccX, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccX);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccY, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccY);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccZ, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.AccZ);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampnanosec, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampnanosec);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampsec, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.TempStampsec);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_1, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_1);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_2, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_2);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_3, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_3);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_4, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_4);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_5, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_5);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_6, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_6);
		CHECK_U_INT(RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7, expected_RBMESG_rbl_CustIf_IMU_OutPutMsg_ST3.Reserved_7);

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

/* Stub for function Dem_GetMonitorStatus */
Std_ReturnType Dem_GetMonitorStatus(Dem_EventIdType EventID,
                                    Dem_MonitorStatusType * MonitorStatus){
    REGISTER_CALL("Dem_GetMonitorStatus");

    IF_INSTANCE("Dem_GetMonitorStatus_1") {
    	CHECK_U_CHAR(EventID,DemConf_DemEventParameter_RBL_AmbientTemperatureFault);
    	CHECK_U_CHAR(*MonitorStatus, 0);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("Dem_GetMonitorStatus_2") {
    	CHECK_U_CHAR(EventID,DemConf_DemEventParameter_RBL_AmbientTemperatureFault);
    	*MonitorStatus = DEM_MONITOR_STATUS_TF;
    	CHECK_U_CHAR(*MonitorStatus, DEM_MONITOR_STATUS_TF);
        return MonitorStatus;
    }

    IF_INSTANCE("Dem_GetMonitorStatus_3") {
    	CHECK_U_CHAR(EventID,DemConf_DemEventParameter_RBL_AmbientTemperatureFault);
    	*MonitorStatus = CANTATA_DEFAULT_VALUE;
    	CHECK_U_CHAR(*MonitorStatus, 0);
        return MonitorStatus;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Dem_GetComponentFailed */
Std_ReturnType Dem_GetComponentFailed(Dem_ComponentIdType ComponentId,
                                      boolean * ComponentFailed){
    REGISTER_CALL("Dem_GetComponentFailed");

    IF_INSTANCE("Component_failed")
    {
    	*ComponentFailed = FALSE;
    	CHECK_U_INT(*ComponentFailed,FALSE);
    	return ComponentFailed;
    }

    IF_INSTANCE("Ecu") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_Ecu);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }
    IF_INSTANCE("uCMemoryGuard") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_uCMemoryGuard);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }
    IF_INSTANCE("MMP_SyncError") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_MMP_SyncError);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }
    IF_INSTANCE("MMP_NvM_FreqContent") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_MMP_Nvm_SigChnMonContents);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }
    IF_INSTANCE("MMP_SignalChain") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_MMP_SignalChain);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }
    IF_INSTANCE("ChargePump") {
    	*ComponentFailed = TRUE;
    	CHECK_U_INT(ComponentId,DemConf_DemComponent_MMP_ReInitError);
    	CHECK_U_INT(*ComponentFailed,TRUE);
        return ComponentFailed;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_Calc_CompuMethod_Phy2Int */
float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters,
                                            float32 phy_value){
    REGISTER_CALL("rbl_CustIf_Calc_CompuMethod_Phy2Int");

    IF_INSTANCE("Stub_Prepare_Temp") {
        return 0.00f;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_Calc_Convert */
uint16 rbl_CustIf_Calc_Convert(float32 value,
                               float32 formula,
                               const CompuMethod * parameter){
    REGISTER_CALL("rbl_CustIf_Calc_Convert");

    IF_INSTANCE("rbl_CustIf_Calc_Convert_1") {
        return 60000;
    }
    IF_INSTANCE("rbl_CustIf_Calc_Convert_2") {
        return 25509;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_TiSync_MMP2GtsTime */
Std_ReturnType rbl_CustIf_TiSync_MMP2GtsTime(uint32 timeMMP_u32,
                                             StbM_TimeStampType * timeGTS_st){
    REGISTER_CALL("rbl_CustIf_TiSync_MMP2GtsTime");

    IF_INSTANCE("Stub_rbl_CustIf_TiSync_MMP2GtsTime_001") {
         	timeGTS_st->nanoseconds =100;
         	timeGTS_st->seconds =200;
         	timeGTS_st->timeBaseStatus=0xC;
         	return E_OK;
         }

         IF_INSTANCE("Stub_rbl_CustIf_TiSync_MMP2GtsTime_002") {
         	timeGTS_st->nanoseconds =0;
         	timeGTS_st->seconds =0;
         	timeGTS_st->timeBaseStatus=0x0;
             	return E_NOT_OK;
         }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function cc_is_bit_set_u8 */
int BEFORE_cc_is_bit_set_u8(uint8_t value,
                            unsigned int bit_position){
    REGISTER_CALL("cc_is_bit_set_u8");

    IF_INSTANCE("cc_is_bit_set_u8_1") {
    	CHECK_U_CHAR(value,0x04);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_2") {
    	CHECK_U_CHAR(value,0x00);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_3") {
    	CHECK_U_CHAR(value,0x00);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_4") {
    	CHECK_U_CHAR(value,0x07);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_5") {
    	CHECK_U_CHAR(value,0x07);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_6") {
    	CHECK_U_CHAR(value,0x07);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_7") {
    	CHECK_U_CHAR(value,0x06);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_8") {
    	CHECK_U_CHAR(value,0x06);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_9") {
    	CHECK_U_CHAR(value,0x06);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_10") {
    	CHECK_U_CHAR(value,0x06);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_11") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_12") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_13") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_TEMPERATURE_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_14") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_OVERLOAD_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_15") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_TEMP_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("cc_is_bit_set_u8_16") {
    	CHECK_U_CHAR(value,0x01);
    	CHECK_U_INT(bit_position,RBL_CUSTIF_TEMP_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function cc_is_bit_set_u8 */
_Bool AFTER_cc_is_bit_set_u8(_Bool cppsm_return_value,
                             uint8_t value,
                             unsigned int bit_position){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function cc_is_bit_set_u8 */
_Bool REPLACE_cc_is_bit_set_u8(uint8_t value,
                               unsigned int bit_position){

    IF_INSTANCE("cc_is_bit_set_u8_1") {
        return TRUE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_2") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_3") {
        return TRUE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_4") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_5") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_6") {
        return TRUE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_7") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_8") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_9") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_10") {
        return TRUE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_11") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_12") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_13") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_14") {
        return FALSE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_15") {
        return TRUE;
    }
    IF_INSTANCE("cc_is_bit_set_u8_16") {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_checkBits */
int BEFORE_rbl_CustIf_checkBits(uint8 Status){
    REGISTER_CALL("rbl_CustIf_checkBits");

    IF_INSTANCE("rbl_CustIf_checkBits_1") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_SIGSTATUS_INIT);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_2") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_3") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_4") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_5") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_6") {
    	CHECK_U_CHAR(Status,RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_checkBits */
uint8 AFTER_rbl_CustIf_checkBits(uint8 cppsm_return_value,
                                 uint8 Status){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_checkBits */
uint8 REPLACE_rbl_CustIf_checkBits(uint8 Status){

    IF_INSTANCE("rbl_CustIf_checkBits_1") {
        return RBL_CUSTIF_SIGSTATUS_INIT;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_2") {
        return RBL_CUSTIF_INTERNAL_SIGSTATUS_INIT;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_3") {
        return RBL_CUSTIF_INTERNAL_SIGSTATUS_PERMANENT_ERROR;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_4") {
        return RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMPERORY_ERROR;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_5") {
        return RBL_CUSTIF_INTERNAL_SIGSTATUS_TEMP_ERROR;
    }
    IF_INSTANCE("rbl_CustIf_checkBits_6") {
        return RBL_CUSTIF_INTERNAL_SIGSTATUS_OVERLOAD_ERROR;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Acc */
int BEFORE_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_Signal_Status_Acc");

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Acc_1") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Acc */
uint8 AFTER_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(uint8 cppsm_return_value,
                                                     const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Acc */
uint8 REPLACE_rbl_CustIf_Prepare_IMU_Signal_Status_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Acc_1") {

        return RBL_CUSTIF_SIGSTATUS_INIT;
    }

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Acc_2") {

        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Rate */
int BEFORE_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_Signal_Status_Rate");

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Rate */
uint8 AFTER_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(uint8 cppsm_return_value,
                                                      const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_Signal_Status_Rate */
uint8 REPLACE_rbl_CustIf_Prepare_IMU_Signal_Status_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Rate_1") {
        return RBL_CUSTIF_SIGSTATUS_INIT;
    }

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Signal_Status_Rate_2") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_PrepareStatus */
int BEFORE_rbl_CustIf_PrepareStatus(uint8 StatusX,
                                    uint8 StatusY,
                                    uint8 StatusZ){
    REGISTER_CALL("rbl_CustIf_PrepareStatus");

    IF_INSTANCE("rbl_CustIf_PrepareStatus_1") {
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("rbl_CustIf_PrepareStatus_2") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_PrepareStatus */
uint8 AFTER_rbl_CustIf_PrepareStatus(uint8 cppsm_return_value,
                                     uint8 StatusX,
                                     uint8 StatusY,
                                     uint8 StatusZ){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_PrepareStatus */
uint8 REPLACE_rbl_CustIf_PrepareStatus(uint8 StatusX,
                                       uint8 StatusY,
                                       uint8 StatusZ){

    IF_INSTANCE("rbl_CustIf_PrepareStatus_1") {
        return RBL_CUSTIF_SIGSTATUS_INIT;
    }
    IF_INSTANCE("rbl_CustIf_PrepareStatus_2") {
        return RBL_CUSTIF_SIGSTATUS_INIT;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function RB_FloatToInt_f32_u8 */
int BEFORE_RB_FloatToInt_f32_u8(float32 var_f32){
    REGISTER_CALL("RB_FloatToInt_f32_u8");

    IF_INSTANCE("RB_FloatToInt_f32_u8_1") {
    	CHECK_DOUBLE(var_f32,0.00);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RB_FloatToInt_f32_u8 */
uint8 AFTER_RB_FloatToInt_f32_u8(uint8 cppsm_return_value,
                                 float32 var_f32){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function RB_FloatToInt_f32_u8 */
uint8 REPLACE_RB_FloatToInt_f32_u8(float32 var_f32){

    IF_INSTANCE("RB_FloatToInt_f32_u8_1") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
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

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_Stat_ST3 */
int BEFORE_rbl_CustIf_Prepare_IMU_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_Stat_ST3");

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Stat_ST3_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_Stat_ST3 */
uint8 AFTER_rbl_CustIf_Prepare_IMU_Stat_ST3(uint8 cppsm_return_value,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_Stat_ST3 */
uint8 REPLACE_rbl_CustIf_Prepare_IMU_Stat_ST3(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_Stat_ST3_1") {
        return RBL_CUSTIF_SIGSTATUS_INIT;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_IMU_Prepare_Temp */
int BEFORE_rbl_CustIf_IMU_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    REGISTER_CALL("rbl_CustIf_IMU_Prepare_Temp");

    IF_INSTANCE("rbl_CustIf_IMU_Prepare_Temp_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_IMU_Prepare_Temp */
void AFTER_rbl_CustIf_IMU_Prepare_Temp(struct cppsm_void_return cppsm_dummy,
                                       const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_IMU_Prepare_Temp */
void REPLACE_rbl_CustIf_IMU_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){

    IF_INSTANCE("rbl_CustIf_IMU_Prepare_Temp_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_AngAcc */
int BEFORE_rbl_CustIf_Prepare_AngAcc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                     const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_AngAcc");

    IF_INSTANCE("rbl_CustIf_Prepare_AngAcc_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_AngAcc */
void AFTER_rbl_CustIf_Prepare_AngAcc(struct cppsm_void_return cppsm_dummy,
                                     const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                     const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_AngAcc */
void REPLACE_rbl_CustIf_Prepare_AngAcc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                       const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_AngAcc_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_Rate */
int BEFORE_rbl_CustIf_Prepare_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                   const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_Rate");

    IF_INSTANCE("rbl_CustIf_Prepare_Rate_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_Rate */
void AFTER_rbl_CustIf_Prepare_Rate(struct cppsm_void_return cppsm_dummy,
                                   const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                   const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_Rate */
void REPLACE_rbl_CustIf_Prepare_Rate(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                     const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_Rate_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_Acc */
int BEFORE_rbl_CustIf_Prepare_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                  const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_Acc");

    IF_INSTANCE("rbl_CustIf_Prepare_Acc_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_Acc */
void AFTER_rbl_CustIf_Prepare_Acc(struct cppsm_void_return cppsm_dummy,
                                  const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                  const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_Acc */
void REPLACE_rbl_CustIf_Prepare_Acc(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                    const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_Acc_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_timeStamp */
int BEFORE_rbl_CustIf_Prepare_timeStamp(uint32 MMPtimeStamp){
    REGISTER_CALL("rbl_CustIf_Prepare_timeStamp");

    IF_INSTANCE("rbl_CustIf_Prepare_timeStamp_1") {
    	CHECK_U_INT(MMPtimeStamp,0x55555555);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_timeStamp */
void AFTER_rbl_CustIf_Prepare_timeStamp(struct cppsm_void_return cppsm_dummy,
                                        uint32 MMPtimeStamp){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_timeStamp */
void REPLACE_rbl_CustIf_Prepare_timeStamp(uint32 MMPtimeStamp){

    IF_INSTANCE("rbl_CustIf_Prepare_timeStamp_1") {
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
