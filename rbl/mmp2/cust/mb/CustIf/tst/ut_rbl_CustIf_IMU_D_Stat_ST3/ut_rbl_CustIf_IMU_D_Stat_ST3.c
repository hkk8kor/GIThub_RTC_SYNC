/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_IMU_D_Stat_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 13-Apr-2024 18:26:15
 *    Generated from: rbl_CustIf_IMU_D_Stat_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_IMU_D_Stat_ST3.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern uint8 ACCESS_FUNCTION_rbl_CustIf_IMU_D_Stat_ST3_RB_FloatToInt_f32_u8(float32 var_f32);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_D_Stat_ST3_rbl_CustIf_IMU_D_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet);
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_D_Stat_ST3_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_IMU_D_Stat_ST3_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters, float32 phy_value);

/* Global data */
extern volatile RBMESG_Type_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3 RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3;
typedef struct rbl_CustIf_IMU_D_Stat_ST3_av_struct { rbl_CustIf_IMU_D_Stat_Pr5_ST3_st * ref_rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData; const CompuMethod(* ref_rbl_CustIf_CAN3_compu_param)[1]; } rbl_CustIf_IMU_D_Stat_ST3_av_struct;
extern rbl_CustIf_IMU_D_Stat_ST3_av_struct av_rbl_CustIf_IMU_D_Stat_ST3;

/* Expected variables for global data */
RBMESG_Type_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3 expected_RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3;
typedef struct expected_rbl_CustIf_IMU_D_Stat_ST3_av_struct { rbl_CustIf_IMU_D_Stat_Pr5_ST3_st ref_rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData; CompuMethod ref_rbl_CustIf_CAN3_compu_param[1]; } expected_rbl_CustIf_IMU_D_Stat_ST3_av_struct;
expected_rbl_CustIf_IMU_D_Stat_ST3_av_struct expected_av_rbl_CustIf_IMU_D_Stat_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No initialisation for const data: rbl_CustIf_CAN3_compu_param */
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData));
    INITIALISE(RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData));
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3, expected_RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData)", &ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData)));
    CHECK_MEMORY("RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3", &RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3, &expected_RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3, sizeof(expected_RBMESG_rbl_CustIf_IMU_D_Stat_Pr5Msg_ST3));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_IMU_D_Prepare_Temp(int);
void ut_rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(int);
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
    OPEN_LOG("ut_rbl_CustIf_IMU_D_Stat_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_IMU_D_Stat_ST3", true);

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
	ut_rbl_CustIf_IMU_D_Prepare_Temp(1);
	ut_rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_IMU_D_Stat_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_IMU_D_Prepare_Temp(int doIt)
{
	if (doIt)
	{
		START_TEST("49912: [MMP2.11]UTC_rbl_CustIf_IMU_D_Prepare_Temp",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49912");

		/*initialise_globals*/

		/* Test case data declarations */
		rbl_ImuStdTypes_ImuSignalSet_t SignalSet;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData).IMU_D_VehYawRateSens_Temp_ST3 = 0;

			// Expected Call Sequence
			EXPECTED_CALLS("rbl_CustIf_Calc_CompuMethod_Phy2Int#default;"
					       "RB_FloatToInt_f32_u8#default");

			// Call SUT
			ACCESS_FUNCTION_rbl_CustIf_IMU_D_Stat_ST3_rbl_CustIf_IMU_D_Prepare_Temp(&SignalSet);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData).IMU_D_VehYawRateSens_Temp_ST3, 0);

			END_CALLS();
			END_STEP();
		}
	}
	END_TEST();
}

void ut_rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(int doIt)
{
	if (doIt)
	{
		START_TEST("48732: [MMP2.11]UTC_rbl_CustIf_IMU_D_Stat_ST3_rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48732");

		/*initialise_globals*/

		/* Test case data declarations */
		rbl_ImuStdTypes_ImuSignalSet_t imu_FilData;

		/*Test steps*/
		START_STEP("1_NTS", true);
		{
			/* Test case data Initializations */
			ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData).IMU_D_Id_ST3 = RBL_CUSTIF_IMU_D_4294967294_1_SNA;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rbl_CustIf_IMU_D_Prepare_Temp#default;"
					       "RBSYS_EnterCommonLockSysfast#default;"
						   "RBSYS_EnterCommonLockSysfast_intern#default;"
						   "RBSYS_ExitCommonLockSysfast#default;"
						   "RBSYS_ExitCommonLockSysfast_intern#default");

			/* Call SUT */
			rbl_CustIf_IMU_D_Driving_IMU_D_Stat_ST3(&imu_FilData);

			/* Test step checks */
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_IMU_D_Stat_ST3, rbl_CustIf_IMU_D_Stat_Pr5_ST3_SigData).IMU_D_Id_ST3,RBL_CUSTIF_IMU_D_4294967294_1_SNA);

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

/* Stub for function rbl_CustIf_Calc_CompuMethod_Phy2Int */
float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters,
                                            float32 phy_value){
    REGISTER_CALL("rbl_CustIf_Calc_CompuMethod_Phy2Int");

    IF_INSTANCE("default") {
    	CHECK_DOUBLE(parameters.LowerLimit,0.0f);
    	CHECK_DOUBLE(parameters.Offset,-70);
    	CHECK_DOUBLE(parameters.Scale,1);
    	CHECK_DOUBLE(parameters.UpperLimit,254);
    	CHECK_U_INT(phy_value, 50);
        return 0.00;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RB_FloatToInt_f32_u8 */
int BEFORE_RB_FloatToInt_f32_u8(float32 var_f32){
    REGISTER_CALL("RB_FloatToInt_f32_u8");

    IF_INSTANCE("default") {
    	CHECK_DOUBLE(var_f32,0.0f);
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

    IF_INSTANCE("default") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_IMU_D_Prepare_Temp */
int BEFORE_rbl_CustIf_IMU_D_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    REGISTER_CALL("rbl_CustIf_IMU_D_Prepare_Temp");

    IF_INSTANCE("default") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_IMU_D_Prepare_Temp */
void AFTER_rbl_CustIf_IMU_D_Prepare_Temp(struct cppsm_void_return cppsm_dummy,
                                         const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_CustIf_IMU_D_Prepare_Temp */
void REPLACE_rbl_CustIf_IMU_D_Prepare_Temp(const rbl_ImuStdTypes_ImuSignalSet_t * SignalSet){

    IF_INSTANCE("default") {
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
