/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_Hndl_Utils.c
 *    Author: GDEV1KOR
 *    Generated on: 13-Apr-2024 18:06:01
 *    Generated from: rbl_CustIf_Hndl_Utils.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include <math.h>

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern uint32 ACCESS_FUNCTION_rbl_CustIf_Hndl_Utils_RB_FloatToIntLimiter_f32_u32_Impl(float32 var_f32, float32 minLimit_f32, float32 maxLimit_f32);
extern float32 rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters, float32 phy_value);
extern uint16 ACCESS_FUNCTION_rbl_CustIf_Hndl_Utils_RB_FloatToInt_f32_u16(float32 var_f32);
void RB_AssertHandleWithCond(_Bool isFailed, const char * expr, const char * file, const char * func, int line);
float32 Mfl_Round_f32(float32 ValValue);

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
void ut_rbl_CustIf_Calc_Convert(int );
void ut_rbl_CustIf_Calc_CompuMethod_Phy2Int(int );
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
    OPEN_LOG("ut_rbl_CustIf_Hndl_Utils.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_Hndl_Utils", true);

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
	ut_rbl_CustIf_Calc_Convert(1);
	ut_rbl_CustIf_Calc_CompuMethod_Phy2Int(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_Hndl_Utils.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_Calc_Convert(int doIt)
{
	if (doIt)
	{
		START_TEST("49011: [MMP2.11]UTC_rbl_CustIf_Calc_Convert",
					"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49011");
		float32 value;
		float32 formula;
		CompuMethod const parameter;

		START_STEP("1_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
		    uint16 Phys_Value;
		    float32 Converted_Value;
		    float32 rawASWValue = 0.00f;

			// EXPECTED CALLS
			 EXPECTED_CALLS("rbl_CustIf_Calc_CompuMethod_Phy2Int#rbl_CustIf_Calc_CompuMethod_Phy2Int_1;\
					         RB_FloatToInt_f32_u16#RB_FloatToInt_f32_u16_1");

			// CALL SUT
			 Phys_Value = rbl_CustIf_Calc_Convert(value, formula,&parameter);

			// EXPECTED RESULTS
			 CHECK_U_INT(Phys_Value, 0x00);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_Calc_CompuMethod_Phy2Int(int doIt)
{
	if (doIt)
	{
		START_TEST("46573: [MMP2.11]UTC_rbl_CustIf_Calc_CompuMethod_Phy2Int",
					"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46573");
		float32 ReturnValue;

		START_STEP("1_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
			CompuMethod parameters;
			float32 phy_value;

			parameters.UpperLimit = 65.536;
			parameters.LowerLimit = -65.536;
			parameters.Offset = 0.0;
			parameters.Scale = 0.002;
			phy_value = -66;

			float32 lower_limit = (parameters.LowerLimit);

			// EXPECTED CALLS
			EXPECTED_CALLS("");

			// CALL SUT
			 ReturnValue = rbl_CustIf_Calc_CompuMethod_Phy2Int(parameters, phy_value);

			// EXPECTED RESULTS
			 CHECK_DOUBLE(ReturnValue, lower_limit);

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
			CompuMethod parameters;
			float32 phy_value;

			parameters.UpperLimit = 65.536;
			parameters.LowerLimit = -65.536;
			parameters.Offset = 0.0;
			parameters.Scale = 0.002;
			phy_value = 66;
			float32 upper_limit = (parameters.UpperLimit);


			// EXPECTED CALLS
			EXPECTED_CALLS("");

			// CALL SUT
			 ReturnValue = rbl_CustIf_Calc_CompuMethod_Phy2Int(parameters,phy_value);

			// EXPECTED RESULTS
			 CHECK_DOUBLE(ReturnValue, upper_limit);

			END_CALLS();
			END_STEP();
		}

		START_STEP("3_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
			CompuMethod parameters;
			float32 phy_value;

			parameters.UpperLimit = 65.536;
			parameters.LowerLimit = -65.536;
			parameters.Offset = 0.0;
			parameters.Scale = 0.002;
			phy_value = 0.1;
			float32 phys_value = (phy_value - parameters.Offset) / parameters.Scale;

			// EXPECTED CALLS
			EXPECTED_CALLS("Mfl_Round_f32#Stub_Mfl_Round_f32");


			// CALL SUT
			 ReturnValue = rbl_CustIf_Calc_CompuMethod_Phy2Int(parameters,phy_value);

			// EXPECTED RESULTS
			 CHECK_DOUBLE(ReturnValue,50.00);

			END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
			CompuMethod parameters;
			float32 phy_value;

			parameters.UpperLimit = 65.536;
			parameters.LowerLimit = -65.536;
			parameters.Offset = 0.00;
			parameters.Scale = 0.002;
			phy_value = 3.50282e+038;

			// EXPECTED CALLS
			EXPECTED_CALLS("");

			// CALL SUT
			 ReturnValue = rbl_CustIf_Calc_CompuMethod_Phy2Int(parameters,phy_value);

			// EXPECTED RESULTS
			CHECK_DOUBLE(ReturnValue, 0);

			END_CALLS();
			END_STEP();
		}

		START_STEP("5_NTS" , TRUE);
		{
			// INITIAL CONDITIONS
			CompuMethod parameters;
			float32 phy_value;

			parameters.UpperLimit = 65.536;
			parameters.LowerLimit = -65.536;
			parameters.Offset = 0.00;
			parameters.Scale = 0.002;
			phy_value = NAN;


			// EXPECTED CALLS
			EXPECTED_CALLS("");

			// CALL SUT
			 ReturnValue = rbl_CustIf_Calc_CompuMethod_Phy2Int(parameters,phy_value);

			// EXPECTED RESULTS
			CHECK_DOUBLE(ReturnValue, 0);

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

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

/* Stub for function Mfl_Round_f32 */
float32 Mfl_Round_f32(float32 ValValue){
    REGISTER_CALL("Mfl_Round_f32");

    IF_INSTANCE("Stub_Mfl_Round_f32")
    {
        return 50.00;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RB_FloatToIntLimiter_f32_u32_Impl */
int BEFORE_RB_FloatToIntLimiter_f32_u32_Impl(float32 var_f32,
                                             float32 minLimit_f32,
                                             float32 maxLimit_f32){
    REGISTER_CALL("RB_FloatToIntLimiter_f32_u32_Impl");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RB_FloatToIntLimiter_f32_u32_Impl */
uint32 AFTER_RB_FloatToIntLimiter_f32_u32_Impl(uint32 cppsm_return_value,
                                               float32 var_f32,
                                               float32 minLimit_f32,
                                               float32 maxLimit_f32){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function RB_FloatToIntLimiter_f32_u32_Impl */
uint32 REPLACE_RB_FloatToIntLimiter_f32_u32_Impl(float32 var_f32,
                                                 float32 minLimit_f32,
                                                 float32 maxLimit_f32){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_Calc_CompuMethod_Phy2Int */
int BEFORE_rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters,
                                               float32 phy_value){
    REGISTER_CALL("rbl_CustIf_Calc_CompuMethod_Phy2Int");

    IF_INSTANCE("rbl_CustIf_Calc_CompuMethod_Phy2Int_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return REPLACE_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_Calc_CompuMethod_Phy2Int */
float32 AFTER_rbl_CustIf_Calc_CompuMethod_Phy2Int(float32 cppsm_return_value,
                                                  CompuMethod parameters,
                                                  float32 phy_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_Calc_CompuMethod_Phy2Int */
float32 REPLACE_rbl_CustIf_Calc_CompuMethod_Phy2Int(CompuMethod parameters,
                                                    float32 phy_value){
    IF_INSTANCE("rbl_CustIf_Calc_CompuMethod_Phy2Int_1") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function RB_FloatToInt_f32_u16 */
int BEFORE_RB_FloatToInt_f32_u16(float32 var_f32){
    REGISTER_CALL("RB_FloatToInt_f32_u16");

    IF_INSTANCE("RB_FloatToInt_f32_u16_1") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return REPLACE_WRAPPER;
}

/* After-Wrapper for function RB_FloatToInt_f32_u16 */
uint16 AFTER_RB_FloatToInt_f32_u16(uint16 cppsm_return_value,
                                   float32 var_f32){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function RB_FloatToInt_f32_u16 */
uint16 REPLACE_RB_FloatToInt_f32_u16(float32 var_f32){
    IF_INSTANCE("RB_FloatToInt_f32_u16_1") {
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}
#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
