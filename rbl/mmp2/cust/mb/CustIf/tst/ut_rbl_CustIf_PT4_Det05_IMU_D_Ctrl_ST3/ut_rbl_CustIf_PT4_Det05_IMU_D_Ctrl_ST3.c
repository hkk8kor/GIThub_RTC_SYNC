/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 14-Apr-2024 15:29:53
 *    Generated from: rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.h"
#include "rbl_CustIf_TiSync.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern boolean ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn);
extern uint8 ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_IMU_D_PrepareStatus(uint8 Status);
extern void ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_RBSYS_ExitCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signal_Status(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet, const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(uint32 MMPtimeStamp);
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
uint16 rbl_CustIf_Calc_Convert(float32 value, float32 formula, const CompuMethod * parameter);
Std_ReturnType rbl_TiSync_convertSystemTickstoGTS_AMG(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st);

/* Global data */
volatile RBMESG_Type_SigChain_FinalRaw RBMESG_SigChain_FinalRaw;
extern volatile RBMESG_Type_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3 RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3;
typedef struct rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct { rbl_CustIf_IMU_D_Det05_ST3_PT4_st * ref_rbl_CustIf_ImuDrivingSigData; const CompuMethod(* ref_rbl_CustIf_Driving_compu_param)[3]; } rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct;
extern rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct av_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3;

/* initilasation of input variables */
rbl_ImuStdTypes_ImuSignalSet_t imu_FilData;
rbl_ImuStdTypes_ImuSignalSet_t imu_derivedData;
rbl_ImuStdTypes_ImuSignalSet_t imu_RawData;

/* Expected variables for global data */
RBMESG_Type_SigChain_FinalRaw expected_RBMESG_SigChain_FinalRaw;
RBMESG_Type_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3 expected_RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3;
typedef struct expected_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct { rbl_CustIf_IMU_D_Det05_ST3_PT4_st ref_rbl_CustIf_ImuDrivingSigData; CompuMethod ref_rbl_CustIf_Driving_compu_param[3]; } expected_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct;
expected_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_av_struct expected_av_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData));
    /* No initialisation for const data: rbl_CustIf_Driving_compu_param */
    INITIALISE(RBMESG_SigChain_FinalRaw);
    INITIALISE(RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData));
    COPY_TO_EXPECTED(RBMESG_SigChain_FinalRaw, expected_RBMESG_SigChain_FinalRaw);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3, expected_RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData)", &ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData)));
    CHECK_MEMORY("RBMESG_SigChain_FinalRaw", &RBMESG_SigChain_FinalRaw, &expected_RBMESG_SigChain_FinalRaw, sizeof(expected_RBMESG_SigChain_FinalRaw));
    CHECK_MEMORY("RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3", &RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3, &expected_RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3, sizeof(expected_RBMESG_rbl_CustIf_IMU_D_Det05_CtrlMsg_ST3));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_IMU_D_PrepareStatus(int );
void ut_rbl_CustIf_Prepare_IMU_D_Signal_Status(int );
void ut_rbl_CustIf_Prepare_IMU_D_Signals(int );
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
void ut_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(int );
#endif
void ut_rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(int );
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
    OPEN_LOG("ut_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3", true);

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
	ut_rbl_CustIf_IMU_D_PrepareStatus(1);
	ut_rbl_CustIf_Prepare_IMU_D_Signal_Status(1);
	ut_rbl_CustIf_Prepare_IMU_D_Signals(1);
#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
    ut_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(1);
#endif
	ut_rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_IMU_D_PrepareStatus(int doIt)
{
	if (doIt)
	{
		START_TEST("48741: [MMP2.11]UTC_rbl_CustIf_IMU_D_PrepareStatus",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48741");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */
		uint8 ret_SigStaus = RBL_CUSTIF_IMU_D_SENS_STAT_INIT;
		uint8 Status;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
		    Status = 0x10; /*Init Bit position */

			// Expected Call Sequence
			EXPECTED_CALLS("Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_1");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_IMU_D_PrepareStatus(Status);

			// Test case checks
			CHECK_U_CHAR(Status,0x10);
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_IMU_D_SENS_STAT_INIT);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */
			Status  = 0x01;/*Permanent bit position */

			// Expected Call Sequence
			EXPECTED_CALLS("Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_3");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_IMU_D_PrepareStatus(Status);

			// Test case checks
			CHECK_U_CHAR(Status,0x01);
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_IMU_D_SENS_STAT_PRMNT_FAIL);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("3_NTS", TRUE);
		{
			/* Test case data Initializations */
			Status  = 0x02; /*temperory bit position */

			// Expected Call Sequence
			EXPECTED_CALLS("Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_4;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_5;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_6");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_IMU_D_PrepareStatus(Status);

			// Test case checks
			CHECK_U_CHAR(Status,0x02);
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_IMU_D_SENS_STAT_TMP_FAIL);
			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", TRUE);
		{
			/* Test case data Initializations */
			Status  = 0x00;

			// Expected Call Sequence
			EXPECTED_CALLS("Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_7;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_8;"
					       "Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_9");

			// Call SUT
			ret_SigStaus = ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_IMU_D_PrepareStatus(Status);

			// Test case checks
			CHECK_U_CHAR(Status,0x00);
			CHECK_U_INT(ret_SigStaus,RBL_CUSTIF_IMU_D_SENS_STAT_OK);
			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Prepare_IMU_D_Signal_Status(int doIt)
{
	if (doIt)
	{
		START_TEST("48739: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_D_Signal_Status",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48739");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			/*set all input values to zero including status ----> opertional */
			memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));

			memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

			/*initialize global variable */
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_Stat_ST3 = 0x00;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchAccel_Stat_ST3 = 0x00;

			/*Expected output global variable */
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchAccel_Stat_ST3 = RBL_CUSTIF_IMU_D_SENS_STAT_OK;

			// Expected Call Sequence
			EXPECTED_CALLS("9*rbl_CustIf_IMU_D_PrepareStatus#default");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signal_Status(&imu_FilData,&imu_derivedData);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_Stat_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_Stat_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_Stat_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchAccel_Stat_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchAccel_Stat_ST3);

			END_CALLS();
			END_STEP();
		}
	}
}

void ut_rbl_CustIf_Prepare_IMU_D_Signals(int doIt)
{
	if (doIt)
	{
		// Test case data declarations

		START_TEST("48738: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_D_Signals",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48738");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			/*initialize  all input values */
			memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
			memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

			/* raw signal value */
			memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

			/*initialize global variable */
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

			/* Expected output global variable */
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

			// Expected Call Sequence
			EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
			                1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
				{
					// INITIAL CONDITIONS
					/*initialize  all input values */
					memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
					memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

					/* raw signal value */
					memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

					/*initialize global variable */
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

					/* Expected output global variable */
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

					// Expected Call Sequence
					EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

					// Call SUT
					ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

					// Test case checks

					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

					END_CALLS();
					END_STEP();
				}

		START_STEP("3_NTS", TRUE);
				{
					// INITIAL CONDITIONS
					/*initialize  all input values */
					memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
					memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

					/* raw signal value */
					memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

					/*initialize global variable */
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

					/* Expected output global variable */
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

					// Expected Call Sequence
					EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

					// Call SUT
					ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

					// Test case checks
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

					END_CALLS();
					END_STEP();
}

				           START_STEP("4_NTS", TRUE);
						   {
							// INITIAL CONDITIONS
							/*initialize  all input values */
							memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
							memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

							/* raw signal value */
							memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

							/*initialize global variable */
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
							ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

							/* Expected output global variable */
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
							ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

							// Expected Call Sequence
							EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
									        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
									        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
									        3*rbl_CustIf_Calc_Convert#default\
									        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

							// Call SUT
							ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

							// Test case checks
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
							CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

							END_CALLS();
							END_STEP();
}

                   START_STEP("5_NTS", TRUE);
				   {
					// INITIAL CONDITIONS
					/*initialize  all input values */
					memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
					memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

					/* raw signal value */
					memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

					/*initialize global variable */
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
					ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

					/* Expected output global variable */
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
					ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

					// Expected Call Sequence
					EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        3*rbl_CustIf_Calc_Convert#default\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
							        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

					// Call SUT
					ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

					// Test case checks
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
					CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

				    END_CALLS();
					END_STEP();
}

            START_STEP("6_NTS", TRUE);
		    {
			// INITIAL CONDITIONS
			/*initialize  all input values */
			memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
			memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

			/* raw signal value */
			memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

			/*initialize global variable */
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

			/* Expected output global variable */
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

			// Expected Call Sequence
			EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        3*rbl_CustIf_Calc_Convert#default\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_Init");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

			// Test case checks

			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

			END_CALLS();
			END_STEP();
}

           START_STEP("7_NTS", TRUE);
		   {
			// INITIAL CONDITIONS
			/*initialize  all input values */
			memset((void*)&imu_FilData, 0x55, sizeof(imu_FilData));
			memset((void*)&imu_derivedData, 0x55, sizeof(imu_derivedData));

			/* raw signal value */
			memset((void*)&imu_RawData, 0x55, sizeof(imu_RawData));

			/*initialize global variable */
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x55;
			ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x55;

			/* Expected output global variable */
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3 = 0x00;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3 = 0x00;

			// Expected Call Sequence
			EXPECTED_CALLS("1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        3*rbl_CustIf_Calc_Convert#default\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        1*rbl_CustIf_IMU_D_PrepareStatus#rawAccStatuS_NotInit\
					        6*rbl_CustIf_Calc_Convert#default");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signals(&imu_FilData,&imu_derivedData,&imu_RawData);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3 ,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_ST3);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3,ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitch_Accel_ST3);

			END_CALLS();
			END_STEP();
		}
	}
}

#if(RBFS_TimeSync == RBFS_TimeSync_TSCan)
void ut_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(int doIt)
{
	if (doIt)
	{
		START_TEST("49913: [MMP2.11]UTC_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49913");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */
		uint32 MMPtimeStamp = 0;
		Std_ReturnType retVal = E_NOT_OK;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			//Expected Call Sequence
			EXPECTED_CALLS("rbl_TiSync_convertSystemTickstoGTS_AMG#rbl_TiSync_convertSystemTickstoGTS_AMG_1");

			//Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(MMPtimeStamp);

			//Test case checks
			CHECK_U_INT(MMPtimeStamp,0);
			CHECK_U_INT(retVal,E_NOT_OK);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			/* Test case data Initializations */

			//Expected Call Sequence
			EXPECTED_CALLS("rbl_TiSync_convertSystemTickstoGTS_AMG#rbl_TiSync_convertSystemTickstoGTS_AMG_2");

			//Call SUT
			ACCESS_FUNCTION_rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(MMPtimeStamp);

			//Test case checks
			CHECK_U_INT(MMPtimeStamp,0);
			CHECK_U_INT(retVal,E_NOT_OK);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
#endif

void ut_rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(int doIt)
{
	if (doIt)
	{
		START_TEST("48740: [MMP2.11]UTC_rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48740");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			// Expected Call Sequence
				EXPECTED_CALLS("RBSYS_EnterCommonLockSysfast#default;"
						       "RBSYS_ExitCommonLockSysfast#default;"
			                   "rbl_CustIf_Prepare_IMU_D_Signal_Status#rbl_CustIf_Prepare_IMU_D_Signal_Status_1;"
					           "rbl_CustIf_Prepare_IMU_D_Signals#rbl_CustIf_Prepare_IMU_D_Signals_1;"
						       "rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp#rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp_1;"
						       "RBSYS_EnterCommonLockSysfast#default;"
						       "RBSYS_ExitCommonLockSysfast#default");

			// Call SUT
			rbl_CustIf_IMU_D_DRIVING_Det05_ST3_PT4_Det05_IMU_D_Ctrl_ST3_PDU_Update(&imu_FilData,&imu_derivedData);

			// Test case checks
			CHECK_U_CHAR(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).Rsrv01_PT4_Det05_IMU_D_Ctrl_Pr5_ST3, 0);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).Rsrv02_PT4_Det05_IMU_D_Ctrl_Pr5_ST3, 0);

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

/* Stub for function rbl_CustIf_Calc_Convert */
uint16 rbl_CustIf_Calc_Convert(float32 value,
                               float32 formula,
                               const CompuMethod * parameter){
    REGISTER_CALL("rbl_CustIf_Calc_Convert");

    IF_INSTANCE("default") {
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_TiSync_convertSystemTickstoGTS_AMG */
Std_ReturnType rbl_TiSync_convertSystemTickstoGTS_AMG(uint32 timeMMP_u32,
                                                      StbM_TimeStampType * timeGTS_st){
    REGISTER_CALL("rbl_TiSync_convertSystemTickstoGTS_AMG");

    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_AMG_1") {
    	CHECK_U_INT(timeMMP_u32,0);
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
        return E_OK;
    }
    IF_INSTANCE("rbl_TiSync_convertSystemTickstoGTS_AMG_2") {
    	CHECK_U_INT(timeMMP_u32,0);
    	CHECK_U_INT(timeGTS_st->nanoseconds, 0);
    	CHECK_U_INT(timeGTS_st->seconds, 0);
    	CHECK_U_INT(timeGTS_st->secondsHi, 0);
    	CHECK_U_INT(timeGTS_st->timeBaseStatus, 0);
        return E_NOT_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
int BEFORE_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data,
                                      uint8 BitPn){
    REGISTER_CALL("Bfx_Prv_GetBit_u8u8_u8_Inl");

    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_1") {
    	CHECK_U_CHAR(Data,0x10);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
    	CHECK_U_CHAR(Data,0x01);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
    	CHECK_U_CHAR(Data,0x01);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_4") {
    	CHECK_U_CHAR(Data,0x02);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_5") {
    	CHECK_U_CHAR(Data,0x02);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_6") {
    	CHECK_U_CHAR(Data,0x02);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TEMP_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_7") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_INIT_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_PERM_STATUS_BIT_POS);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_9") {
    	CHECK_U_CHAR(Data,0);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TEMP_STATUS_BIT_POS);
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
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
        return TRUE;
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
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_9") {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_IMU_D_PrepareStatus */
int BEFORE_rbl_CustIf_IMU_D_PrepareStatus(uint8 Status){
    REGISTER_CALL("rbl_CustIf_IMU_D_PrepareStatus");

    IF_INSTANCE("rawAccStatuS_Init") {
    	 CHECK_U_INT(Status,0x55);
    return REPLACE_WRAPPER;
      }
    IF_INSTANCE("rawAccStatuS_NotInit") {
    	 CHECK_U_INT(Status,0x55);
    return REPLACE_WRAPPER;
      }
    IF_INSTANCE("default") {
    	CHECK_U_INT(Status,0x55);
    return REPLACE_WRAPPER;
     }

    IF_INSTANCE("rbl_CustIf_IMU_D_PrepareStatus_1") {
    	CHECK_U_INT(Status,0x55);
    return REPLACE_WRAPPER;
     }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_IMU_D_PrepareStatus */
uint8 AFTER_rbl_CustIf_IMU_D_PrepareStatus(uint8 cppsm_return_value,
                                           uint8 Status){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_IMU_D_PrepareStatus */
uint8 REPLACE_rbl_CustIf_IMU_D_PrepareStatus(uint8 Status){

	IF_INSTANCE("rawAccStatuS_Init") {

		 return RBL_CUSTIF_IMU_D_SENS_STAT_INIT;
		      }
	IF_INSTANCE("rawAccStatuS_NotInit") {

	     return RBL_CUSTIF_IMU_D_SENS_STAT_OK;
	          }
	IF_INSTANCE("default") {

	     return RBL_CUSTIF_IMU_D_SENS_STAT_OK;
	    }
	IF_INSTANCE("rbl_CustIf_IMU_D_PrepareStatus_1") {

	     return CANTATA_DEFAULT_VALUE;
	    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function RBSYS_EnterCommonLockSysfast */
int BEFORE_RBSYS_EnterCommonLockSysfast(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
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

    IF_INSTANCE("default") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCommonLockSysfast */
int BEFORE_RBSYS_ExitCommonLockSysfast(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
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

    IF_INSTANCE("default") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_Status */
int BEFORE_rbl_CustIf_Prepare_IMU_D_Signal_Status(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                                  const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_D_Signal_Status");

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signal_Status_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_Status */
void AFTER_rbl_CustIf_Prepare_IMU_D_Signal_Status(struct cppsm_void_return cppsm_dummy,
                                                  const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                                  const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_Status */
void REPLACE_rbl_CustIf_Prepare_IMU_D_Signal_Status(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                                    const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet){

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signal_Status_1") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signals */
int BEFORE_rbl_CustIf_Prepare_IMU_D_Signals(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_D_Signals");

	  IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signals_1") {
		  CHECK_MEMORY("Checking SignalSet", SignalSet, &imu_FilData, sizeof(imu_FilData));
		  CHECK_MEMORY("Checking Derived_SignalSet", Derived_SignalSet, &imu_derivedData, sizeof(imu_derivedData));
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_X_Stat_ST3 = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_X][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollRate_Stat_ST3 = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehRollAccel_Stat_ST3 = Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_X][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Y_Stat_ST3 = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Y][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawRate_Stat_ST3 = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehYawAccel_Stat_ST3 = Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Z][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehAccel_Z_Stat_ST3 = SignalSet->acc[RBL_IMUSTDTYPES_AXIS_Z][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchRate_Stat_ST3 = SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status;
		  ACCESS_VARIABLE(rbl_CustIf_PT4_Det05_IMU_D_Ctrl_ST3, rbl_CustIf_ImuDrivingSigData).IMU_D_VehPitchAccel_Stat_ST3 = Derived_SignalSet->rate[RBL_IMUSTDTYPES_AXIS_Y][0].status;
		  return REPLACE_WRAPPER;
	    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signals */
void AFTER_rbl_CustIf_Prepare_IMU_D_Signals(struct cppsm_void_return cppsm_dummy,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet,
                                            const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signals */
void REPLACE_rbl_CustIf_Prepare_IMU_D_Signals(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet,
                                              const rbl_ImuStdTypes_ImuSignalSet_t * Derived_SignalSet,
                                              const rbl_ImuStdTypes_ImuSignalSet_t * RawSignalSet){

	IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signals_1") {
        return;
	}
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp */
int BEFORE_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(uint32 MMPtimeStamp){
    REGISTER_CALL("rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp");

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp_1") {
    	MMPtimeStamp = 0;
    	CHECK_U_INT(MMPtimeStamp,0);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp */
void AFTER_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(struct cppsm_void_return cppsm_dummy,
                                                     uint32 MMPtimeStamp){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp */
void REPLACE_rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp(uint32 MMPtimeStamp){

    IF_INSTANCE("rbl_CustIf_Prepare_IMU_D_Signal_TimeStamp_1") {
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
