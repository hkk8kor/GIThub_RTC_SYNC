/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Nvm.h"
#include "rbl_SigChain_Nvm.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"
#include "rba_BswSrv.h"
#include "RB_Contract.h"
#include "RBPDM.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rba_BswSrv_MemCopy8(uint8 * xDest_pu8, const uint8 * xSrc_pcu8, uint32 numBytes_u32);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCOAccRedXReadCb(const void * NvMBuffer, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCOAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCORateRedXReadCb(const void * NvMBuffer, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCORateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCSAccRedXReadCb(const void * NvMBuffer, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCSAccRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCSRateRedXReadCb(const void * NvMBuffer, uint8 x);
extern Std_ReturnType ACCESS_FUNCTION_rbl_SigChain_NvmTCOS_rbl_SigChain_TCSRateRedXResultCb(uint8 ServiceId, NvM_RequestResultType JobResult, uint8 x);
void RBSYS_EnterCommonLock_intern();
void RBSYS_ExitCommonLock_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
boolean rbl_SigChain_NvmValidCheck(uint8 ServiceId, NvM_RequestResultType JobResult);

/* Global data */
sint16 rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
sint16 rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];
sint16 rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
sint16 rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

typedef struct rbl_SigChain_NvmTCOS_av_struct
{ boolean(* ref_rbl_SigChain_TCOAccVld)[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
boolean(* ref_rbl_SigChain_TCORateVld)[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
boolean(* ref_rbl_SigChain_TCSAccVld)[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
boolean(* ref_rbl_SigChain_TCSRateVld)[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
} rbl_SigChain_NvmTCOS_av_struct;
extern rbl_SigChain_NvmTCOS_av_struct av_rbl_SigChain_NvmTCOS;

/* Expected variables for global data */
sint16 expected_rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
sint16 expected_rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];
sint16 expected_rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
sint16 expected_rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

typedef struct expected_rbl_SigChain_NvmTCOS_av_struct
{ boolean ref_rbl_SigChain_TCOAccVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
boolean ref_rbl_SigChain_TCORateVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
boolean ref_rbl_SigChain_TCSAccVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
boolean ref_rbl_SigChain_TCSRateVld[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
} expected_rbl_SigChain_NvmTCOS_av_struct;

expected_rbl_SigChain_NvmTCOS_av_struct expected_av_rbl_SigChain_NvmTCOS;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_SigChain_TCOAcc);
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld));
    INITIALISE(rbl_SigChain_TCORate);
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld));
    INITIALISE(rbl_SigChain_TCSAcc);
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld));
    INITIALISE(rbl_SigChain_TCSRate);
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_SigChain_TCOAcc, expected_rbl_SigChain_TCOAcc);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld));
    COPY_TO_EXPECTED(rbl_SigChain_TCORate, expected_rbl_SigChain_TCORate);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld));
    COPY_TO_EXPECTED(rbl_SigChain_TCSAcc, expected_rbl_SigChain_TCSAcc);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld));
    COPY_TO_EXPECTED(rbl_SigChain_TCSRate, expected_rbl_SigChain_TCSRate);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("rbl_SigChain_TCOAcc", rbl_SigChain_TCOAcc, expected_rbl_SigChain_TCOAcc, sizeof(expected_rbl_SigChain_TCOAcc));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)", ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)));
    CHECK_MEMORY("rbl_SigChain_TCORate", rbl_SigChain_TCORate, expected_rbl_SigChain_TCORate, sizeof(expected_rbl_SigChain_TCORate));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)", ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)));
    CHECK_MEMORY("rbl_SigChain_TCSAcc", rbl_SigChain_TCSAcc, expected_rbl_SigChain_TCSAcc, sizeof(expected_rbl_SigChain_TCSAcc));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)", ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)));
    CHECK_MEMORY("rbl_SigChain_TCSRate", rbl_SigChain_TCSRate, expected_rbl_SigChain_TCSRate, sizeof(expected_rbl_SigChain_TCSRate));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)", ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChain_TCOAccRedXReadCb(int);
void ut_rbl_SigChain_TCOAccRedXResultCb(int);
void ut_rbl_SigChain_TCOAccRed0ReadCb(int);
void ut_rbl_SigChain_TCOAccRed0ResultCb(int);
void ut_rbl_SigChain_TCOAccRed1ReadCb(int);
void ut_rbl_SigChain_TCOAccRed1ResultCb(int);
void ut_rbl_SigChain_TCOAccRed2ReadCb(int);
void ut_rbl_SigChain_TCOAccRed2ResultCb(int);
void ut_rbl_SigChain_TCORateRedXReadCb(int);
void ut_rbl_SigChain_TCORateRedXResultCb(int);
void ut_rbl_SigChain_TCORateRed0ReadCb(int);
void ut_rbl_SigChain_TCORateRed0ResultCb(int);
//void ut_rbl_SigChain_TCORateRed1ReadCb(int);
//void ut_rbl_SigChain_TCORateRed1ResultCb(int);
void ut_rbl_SigChain_TCSAccRedXReadCb(int);
void ut_rbl_SigChain_TCSAccRedXResultCb(int);
void ut_rbl_SigChain_TCSAccRed0ReadCb(int);
void ut_rbl_SigChain_TCSAccRed0ResultCb(int);
void ut_rbl_SigChain_TCSAccRed1ReadCb(int);
void ut_rbl_SigChain_TCSAccRed1ResultCb(int);
void ut_rbl_SigChain_TCSAccRed2ReadCb(int);
void ut_rbl_SigChain_TCSAccRed2ResultCb(int);
void ut_rbl_SigChain_TCSRateRedXReadCb(int);
void ut_rbl_SigChain_TCSRateRedXResultCb(int);
void ut_rbl_SigChain_TCSRateRed0ReadCb(int);
void ut_rbl_SigChain_TCSRateRed0ResultCb(int);
//void ut_rbl_SigChain_TCSRateRed1ReadCb(int);
//void ut_rbl_SigChain_TCSRateRed1ResultCb(int);
void ut_rbl_SigChain_TCOSAllNvmItemsValid(int);

Std_ReturnType global_returnValue;
Std_ReturnType expected_global_returnValue;
uint8 global_ServiceId;
uint8 expected_global_ServiceId;
NvM_RequestResultType global_JobResult;
NvM_RequestResultType expected_global_JobResult;
uint8 global_x;
uint8 expected_global_x;
uint8 global_NvMBuffer;
uint8 expected_global_NvMBuffer;
int i;
uint8 global_values_address1;
uint8 global_values_address2;
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
    OPEN_LOG("ut_rbl_SigChain_NvmTCOS.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_NvmTCOS", true);

    WRITE_LOG(" * ------------------ TEST SUITE OF rbl_SigChain_NvmTCOS -----------------*", cppth_ll_minimal,true);
	WRITE_LOG(" * -----------------PROJECT: MMP2 ------ SOFTWARE: ASW------------------ * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ------------------ LAST SCRIPT UPDATE: 12/12/2023 ------------------- * ", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT IMPLEMENTED BY:MAJ3BRG --- TEST RUN PERFORMED BY MAJ3BRG --- *", cppth_ll_minimal,true);
	WRITE_LOG(" * ---SCRIPT REWORKED BY: MAJ3BRG ----- TEST RUN PERFORMED BY: MAJ3BRG --- *",cppth_ll_minimal,true);
	WRITE_LOG(" * -------------------------TEST SUITE ID: 1443 ------------------------- *", cppth_ll_minimal,true);


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
    ut_rbl_SigChain_TCOAccRedXReadCb(1);
    ut_rbl_SigChain_TCOAccRedXResultCb(1);
    ut_rbl_SigChain_TCOAccRed0ReadCb(1);
    ut_rbl_SigChain_TCOAccRed0ResultCb(1);
    ut_rbl_SigChain_TCOAccRed1ReadCb(1);
    ut_rbl_SigChain_TCOAccRed1ResultCb(1);
    ut_rbl_SigChain_TCOAccRed2ReadCb(1);
    ut_rbl_SigChain_TCOAccRed2ResultCb(1);
	#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
    ut_rbl_SigChain_TCOAccRed3ReadCb(1);
    ut_rbl_SigChain_TCOAccRed3ResultCb(1);
	#endif
    ut_rbl_SigChain_TCORateRedXReadCb(1);
    ut_rbl_SigChain_TCORateRedXResultCb(1);
    ut_rbl_SigChain_TCORateRed0ReadCb(1);
    ut_rbl_SigChain_TCORateRed0ResultCb(1);
//    ut_rbl_SigChain_TCORateRed1ReadCb(1);
//    ut_rbl_SigChain_TCORateRed1ResultCb(1);
    ut_rbl_SigChain_TCSAccRedXReadCb(1);
    ut_rbl_SigChain_TCSAccRedXResultCb(1);
    ut_rbl_SigChain_TCSAccRed0ReadCb(1);
    ut_rbl_SigChain_TCSAccRed0ResultCb(1);
    ut_rbl_SigChain_TCSAccRed1ReadCb(1);
    ut_rbl_SigChain_TCSAccRed1ResultCb(1);
    ut_rbl_SigChain_TCSAccRed2ReadCb(1);
    ut_rbl_SigChain_TCSAccRed2ResultCb(1);
	#if(RBFS_SigChainChMap == RBFS_SigChainChMap_4SMU)
    ut_rbl_SigChain_TCSAccRed3ReadCb(1);
    ut_rbl_SigChain_TCSAccRed3ResultCb(1);
	#endif
    ut_rbl_SigChain_TCSRateRedXReadCb(1);
    ut_rbl_SigChain_TCSRateRedXResultCb(1);
    ut_rbl_SigChain_TCSRateRed0ReadCb(1);
    ut_rbl_SigChain_TCSRateRed0ResultCb(1);
//    ut_rbl_SigChain_TCSRateRed1ReadCb(1);
//    ut_rbl_SigChain_TCSRateRed1ResultCb(1);
    ut_rbl_SigChain_TCOSAllNvmItemsValid(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_NvmTCOS.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChain_TCOAccRedXReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47530: [MMP2.11]UTC_rbl_SigChain_TCOAccRedXReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47530");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			// EXPECTED CALLS
			EXPECTED_CALLS("rba_BswSrv_MemCopy8#rbl_SigChain_TCOAccRedXReadCb_step1_call1\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCOAccRedXReadCb_step1_call2\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCOAccRedXReadCb_step1_call3\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCOAccRedXReadCb_step1_call4");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC + 1;
			expected_global_x = global_x;

			global_returnValue = 0;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);


			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRedXResultCb(int doIt)
{
	if (doIt)
	{
		START_TEST("47531: [MMP2.11]UTC_rbl_SigChain_TCOAccRedXResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47531");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			ACCESS_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld )[global_x] = FALSE;
			ACCESS_EXPECTED_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld )[global_x] = TRUE;

			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_NvmValidCheck", "1", "rbl_SigChain_TCOAccRedXResultCb_step1_call1");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}


		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("", "", "");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}


		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed0ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47532: [MMP2.11]UTC_rbl_SigChain_TCOAccRed0ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47532");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXReadCb","1","rbl_SigChain_TCOAccRed0ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed0ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed0ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47533: [MMP2.11]UTC_rbl_SigChain_TCOAccRed0ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47533");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXResultCb","1","rbl_SigChain_TCOAccRed0ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed0ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed1ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47534: [MMP2.11]UTC_rbl_SigChain_TCOAccRed1ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47534");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXReadCb","1","rbl_SigChain_TCOAccRed1ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed1ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed1ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47535: [MMP2.11]UTC_rbl_SigChain_TCOAccRed1ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47535");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXResultCb","1","rbl_SigChain_TCOAccRed1ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed1ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed2ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47536: [MMP2.11]UTC_rbl_SigChain_TCOAccRed2ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47536");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXReadCb","1","rbl_SigChain_TCOAccRed2ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed2ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCOAccRed2ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47537: [MMP2.11]UTC_rbl_SigChain_TCOAccRed2ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47537");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCOAccRedXResultCb","1","rbl_SigChain_TCOAccRed2ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCOAccRed2ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCORateRedXReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47538: [MMP2.11]UTC_rbl_SigChain_TCORateRedXReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47538");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			// EXPECTED CALLS
			EXPECTED_CALLS("rba_BswSrv_MemCopy8#rbl_SigChain_TCORateRedXReadCb_step1_call1\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCORateRedXReadCb_step1_call2\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCORateRedXReadCb_step1_call3\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCORateRedXReadCb_step1_call4");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);


			check_global_data();

			END_CALLS();
			END_STEP();
		}


		END_TEST();
	}
}

void ut_rbl_SigChain_TCORateRedXResultCb(int doIt)
{
	if (doIt)
	{
		START_TEST("47539: [MMP2.11]UTC_rbl_SigChain_TCORateRedXResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47539");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			ACCESS_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld )[global_x] = FALSE;
			ACCESS_EXPECTED_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld )[global_x] = TRUE;

			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_NvmValidCheck", "1", "rbl_SigChain_TCORateRedXResultCb_step1_call1");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}


		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("", "", "");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCORateRed0ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47540: [MMP2.11]UTC_rbl_SigChain_TCORateRed0ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47540");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCORateRedXReadCb","1","rbl_SigChain_TCORateRed0ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCORateRed0ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCORateRed0ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47541: [MMP2.11]UTC_rbl_SigChain_TCORateRed0ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47541");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCORateRedXResultCb","1","rbl_SigChain_TCORateRed0ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCORateRed0ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

//void ut_rbl_SigChain_TCORateRed1ReadCb(int doIt)
//{
//	if (doIt)
//	{
//
//		START_TEST("47542: [MMP2.11]UTC_rbl_SigChain_TCORateRed1ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47542");
//
//		START_STEP("1_NTS", true);
//		{
//			// INITIAL CONDITIONS
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			global_returnValue = FALSE;
//			expected_global_returnValue = TRUE;
//
//
//			// EXPECTED CALLS
//			EXPECT_CALL("rbl_SigChain_TCORateRedXReadCb","1","rbl_SigChain_TCORateRed1ReadCb_step1_call1");
//
//
//			// CALL SUT
//			global_returnValue = rbl_SigChain_TCORateRed1ReadCb(&global_NvMBuffer);
//
//			// EXPECTED RESULTS
//			CHECK_U_INT(global_returnValue, expected_global_returnValue);
//
//			check_global_data();
//
//			END_CALLS();
//			END_STEP();
//		}
//		END_TEST();
//	}
//}

//void ut_rbl_SigChain_TCORateRed1ResultCb(int doIt)
//{
//	if (doIt)
//	{
//
//		START_TEST("47543: [MMP2.11]UTC_rbl_SigChain_TCORateRed1ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47543");
//
//		START_STEP("1_NTS", true);
//		{
//			// INITIAL CONDITIONS
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			global_returnValue = FALSE;
//			expected_global_returnValue = TRUE;
//
//
//			// EXPECTED CALLS
//			EXPECT_CALL("rbl_SigChain_TCORateRedXResultCb","1","rbl_SigChain_TCORateRed1ResultCb_step1_call1");
//
//
//			// CALL SUT
//			global_returnValue = rbl_SigChain_TCORateRed1ResultCb(global_ServiceId, global_JobResult);
//
//			// EXPECTED RESULTS
//			CHECK_U_INT(global_returnValue, expected_global_returnValue);
//
//			check_global_data();
//
//			END_CALLS();
//			END_STEP();
//		}
//		END_TEST();
//	}
//}

void ut_rbl_SigChain_TCSAccRedXReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47544: [MMP2.11]UTC_rbl_SigChain_TCSAccRedXReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47544");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = 1;
			expected_global_x = 1;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			// EXPECTED CALLS
			EXPECTED_CALLS("rba_BswSrv_MemCopy8#rbl_SigChain_TCSAccRedXReadCb_step1_call1\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSAccRedXReadCb_step1_call2\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSAccRedXReadCb_step1_call3\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSAccRedXReadCb_step1_call4");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);


			check_global_data();

			END_CALLS();
			END_STEP();
		}


		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRedXResultCb(int doIt)
{
	if (doIt)
	{
		START_TEST("47545: [MMP2.11]UTC_rbl_SigChain_TCSAccRedXResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47545");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			ACCESS_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld )[global_x] = FALSE;
			ACCESS_EXPECTED_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld )[global_x] = TRUE;

			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_NvmValidCheck", "1", "rbl_SigChain_TCSAccRedXResultCb_step1_call1");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = 1;

			global_JobResult = 2;
			expected_global_JobResult = 2;

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC + 1;
			expected_global_x =global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed0ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47546: [MMP2.11]UTC_rbl_SigChain_TCSAccRed0ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47546");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXReadCb","1","rbl_SigChain_TCSAccRed0ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed0ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed0ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47547: [MMP2.11]UTC_rbl_SigChain_TCSAccRed0ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47547");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXResultCb","1","rbl_SigChain_TCSAccRed0ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed0ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed1ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47548: [MMP2.11]UTC_rbl_SigChain_TCSAccRed1ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47548");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXReadCb","1","rbl_SigChain_TCSAccRed1ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed1ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed1ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47549: [MMP2.11]UTC_rbl_SigChain_TCSAccRed1ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47549");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXResultCb","1","rbl_SigChain_TCSAccRed1ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed1ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed2ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47550: [MMP2.11]UTC_rbl_SigChain_TCSAccRed2ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47550");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXReadCb","1","rbl_SigChain_TCSAccRed2ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed2ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSAccRed2ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47551: [MMP2.11]UTC_rbl_SigChain_TCSAccRed2ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47551");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSAccRedXResultCb","1","rbl_SigChain_TCSAccRed2ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSAccRed2ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSRateRedXReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47552: [MMP2.11]UTC_rbl_SigChain_TCSRateRedXReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47552");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = 1;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			// EXPECTED CALLS
			EXPECTED_CALLS("rba_BswSrv_MemCopy8#rbl_SigChain_TCSRateRedXReadCb_step1_call1\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSRateRedXReadCb_step1_call2\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSRateRedXReadCb_step1_call3\
							rba_BswSrv_MemCopy8#rbl_SigChain_TCSRateRedXReadCb_step1_call4");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateRedXReadCb)(&global_NvMBuffer, global_x);


			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);


			check_global_data();

			END_CALLS();
			END_STEP();
		}


		END_TEST();
	}
}

void ut_rbl_SigChain_TCSRateRedXResultCb(int doIt)
{
	if (doIt)
	{
		START_TEST("47553: [MMP2.11]UTC_rbl_SigChain_TCSRateRedXResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47553");

		START_STEP("1_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = 0;
			expected_global_x = global_x;

			global_returnValue = E_NOT_OK;
			expected_global_returnValue = E_OK;

			ACCESS_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld )[global_x] = FALSE;
			ACCESS_EXPECTED_VARIABLE( rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld )[global_x] = TRUE;

			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_NvmValidCheck", "1", "rbl_SigChain_TCSRateRedXResultCb_step1_call1");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("2_NTS", TRUE);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_ServiceId = 1;
			expected_global_ServiceId = global_ServiceId;

			global_JobResult = 2;
			expected_global_JobResult = global_JobResult;

			global_x = RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT + 1;
			expected_global_x = global_x;

			global_returnValue = E_OK;
			expected_global_returnValue = E_NOT_OK;

			// EXPECTED CALLS
			EXPECT_CALL("", "", "");

			// CALL SUT
			global_returnValue = ACCESS_FUNCTION(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateRedXResultCb)(global_ServiceId, global_JobResult, global_x);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);
			CHECK_U_INT(global_ServiceId, expected_global_ServiceId);
			CHECK_U_INT(global_JobResult, expected_global_JobResult);
			CHECK_U_INT(global_x, expected_global_x);

			check_global_data();

			END_CALLS();
			END_STEP();
		}



		END_TEST();
	}
}

void ut_rbl_SigChain_TCSRateRed0ReadCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47554: [MMP2.11]UTC_rbl_SigChain_TCSRateRed0ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47554");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSRateRedXReadCb","1","rbl_SigChain_TCSRateRed0ReadCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSRateRed0ReadCb(&global_NvMBuffer);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_SigChain_TCSRateRed0ResultCb(int doIt)
{
	if (doIt)
	{

		START_TEST("47555: [MMP2.11]UTC_rbl_SigChain_TCSRateRed0ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47555");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = FALSE;
			expected_global_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECT_CALL("rbl_SigChain_TCSRateRedXResultCb","1","rbl_SigChain_TCSRateRed0ResultCb_step1_call1");


			// CALL SUT
			global_returnValue = rbl_SigChain_TCSRateRed0ResultCb(global_ServiceId, global_JobResult);

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

//void ut_rbl_SigChain_TCSRateRed1ReadCb(int doIt)
//{
//	if (doIt)
//	{
//
//		START_TEST("47556: [MMP2.11]UTC_rbl_SigChain_TCSRateRed1ReadCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47556");
//
//		START_STEP("1_NTS", true);
//		{
//			// INITIAL CONDITIONS
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			global_returnValue = FALSE;
//			expected_global_returnValue = TRUE;
//
//
//			// EXPECTED CALLS
//			EXPECT_CALL("rbl_SigChain_TCSRateRedXReadCb","1","rbl_SigChain_TCSRateRed1ReadCb_step1_call1");
//
//
//			// CALL SUT
//			global_returnValue = rbl_SigChain_TCSRateRed1ReadCb(&global_NvMBuffer);
//
//			// EXPECTED RESULTS
//			CHECK_U_INT(global_returnValue, expected_global_returnValue);
//
//			check_global_data();
//
//			END_CALLS();
//			END_STEP();
//		}
//		END_TEST();
//	}
//}
//
//void ut_rbl_SigChain_TCSRateRed1ResultCb(int doIt)
//{
//	if (doIt)
//	{
//
//		START_TEST("47557: [MMP2.11]UTC_rbl_SigChain_TCSRateRed1ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47557");
//
//		START_STEP("1_NTS", true);
//		{
//			// INITIAL CONDITIONS
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			global_returnValue = FALSE;
//			expected_global_returnValue = TRUE;
//
//
//			// EXPECTED CALLS
//			EXPECT_CALL("rbl_SigChain_TCSRateRedXResultCb","1","rbl_SigChain_TCSRateRed1ResultCb_step1_call1");
//
//
//			// CALL SUT
//			global_returnValue = rbl_SigChain_TCSRateRed1ResultCb(global_ServiceId, global_JobResult);
//
//			// EXPECTED RESULTS
//			CHECK_U_INT(global_returnValue, expected_global_returnValue);
//
//			check_global_data();
//
//			END_CALLS();
//			END_STEP();
//		}
//		END_TEST();
//	}
//}

void ut_rbl_SigChain_TCOSAllNvmItemsValid(int doIt)
{
	if (doIt)
	{

		START_TEST("47558: [MMP2.11]UTC_rbl_SigChain_TCSRateRed1ResultCb", "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47558");

		// TT, TF and FT for rbl_SigChain_TCSAccVld
		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = FALSE;

			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = TRUE;

			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		// // TT, TF and FT for rbl_SigChain_TCOAccVld
		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = FALSE;

			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = TRUE;


			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		// F F condition
		START_STEP("3_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = FALSE;

			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = FALSE;

			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}



		START_STEP("4_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = TRUE;

			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = TRUE;


			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];



			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = TRUE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = FALSE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = TRUE;

			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}


		START_STEP("5_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = FALSE;

			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = TRUE;


			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];



			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = FALSE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = TRUE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = TRUE;

			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		START_STEP("6_NTS", true);
		{
			// INITIAL CONDITIONS
			initialise_global_data();
			initialise_expected_global_data();

			global_returnValue = TRUE;
			expected_global_returnValue = FALSE;


			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = TRUE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = TRUE;


			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSAccVld)[2];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCOAccVld)[2];


			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = FALSE;
			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = FALSE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = FALSE;
//			ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = FALSE;

			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[0];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCSRateVld)[1];
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1] = ACCESS_VARIABLE(rbl_SigChain_NvmTCOS, rbl_SigChain_TCORateVld)[1];

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// CALL SUT
			global_returnValue = rbl_SigChain_TCOSAllNvmItemsValid();

			// EXPECTED RESULTS
			CHECK_U_INT(global_returnValue, expected_global_returnValue);

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

/* Stub for function rbl_SigChain_NvmValidCheck */
boolean rbl_SigChain_NvmValidCheck(uint8 ServiceId,  NvM_RequestResultType JobResult)

{
    REGISTER_CALL("rbl_SigChain_NvmValidCheck");

    IF_INSTANCE("rbl_SigChain_TCOAccRedXResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRedXResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRedXResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	return TRUE;
    }



    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function memcpy */
int BEFORE_memcpy(void * __restrict__ _Dst,
                  const void * __restrict__ _Src,
                  size_t _Size){
    REGISTER_CALL("memcpy");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function memcpy */
void * AFTER_memcpy(void * cppsm_return_value,
                    void * __restrict__ _Dst,
                    const void * __restrict__ _Src,
                    size_t _Size){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function memcpy */
void * REPLACE_memcpy(void * __restrict__ _Dst,
                      const void * __restrict__ _Src,
                      size_t _Size){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Before-Wrapper for function memset */
int BEFORE_memset(void * _Dst,
                  int _Val,
                  size_t _Size){
    REGISTER_CALL("memset");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function memset */
void * AFTER_memset(void * cppsm_return_value,
                    void * _Dst,
                    int _Val,
                    size_t _Size){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function memset */
void * REPLACE_memset(void * _Dst,
                      int _Val,
                      size_t _Size){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Before-Wrapper for function rba_BswSrv_MemCopy8 */
int BEFORE_rba_BswSrv_MemCopy8(uint8 * xDest_pu8,  const uint8 * xSrc_pcu8, uint32 numBytes_u32)
{
    REGISTER_CALL("rba_BswSrv_MemCopy8");

    IF_INSTANCE("default")
	{
    	return REPLACE_WRAPPER;
	}

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call1")
    {
    	for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCOPNTS ;i++)
    	{
    		CHECK_U_INT(xDest_pu8[i], 0);
    	}

    	CHECK_U_INT(xSrc_pcu8, &global_NvMBuffer);
    	CHECK_U_INT(numBytes_u32, 3*RBL_SIGCHAIN_SIZEOFTCOPNTS);

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call2")
    {
    	CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_X][global_x][0]));
    	for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCOPNTS ;i++)
		{
    		CHECK_U_INT(xSrc_pcu8[i], 0);
		}
    	CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call3")
    {
    	CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_Y][global_x][0]));
    	// xSrc_pcu8 address not possible to reach
    	CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call4")
    {
    	CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_Z][global_x][0]));
    	// xSrc_pcu8 address not possible to reach
    	CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call1")
	{
		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCOPNTS ;i++)
		{
			CHECK_U_INT(xDest_pu8[i], 0);
		}
		CHECK_U_INT(xSrc_pcu8, &global_NvMBuffer);
		CHECK_U_INT(numBytes_u32, 3*RBL_SIGCHAIN_SIZEOFTCOPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call2")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_X][global_x][0]));
		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCOPNTS ;i++)
		{
			CHECK_U_INT(xSrc_pcu8[i], 0);
		}
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call3")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_Y][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call4")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_Z][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCOPNTS);

		return REPLACE_WRAPPER;
	}


	IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call1")
	{
		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCSPNTS ;i++)
		{
			CHECK_U_INT(xDest_pu8[i], 0);
		}
		CHECK_U_INT(xSrc_pcu8, &global_NvMBuffer);
		CHECK_U_INT(numBytes_u32, 3*RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call2")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_X][global_x][0]));

		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCSPNTS ;i++)
		{
			CHECK_U_INT(xSrc_pcu8[i], 0);
		}

		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call3")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_Y][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call4")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_Z][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call1")
	{
		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCSPNTS ;i++)
		{
			CHECK_U_INT(xDest_pu8[i], 0);
		}
		CHECK_U_INT(xSrc_pcu8, &global_NvMBuffer);
		CHECK_U_INT(numBytes_u32, 3*RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call2")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_X][global_x][0]));
		for(i=0; i<3*RBL_SIGCHAIN_SIZEOFTCSPNTS ;i++)
		{
			CHECK_U_INT(xSrc_pcu8[i], 0);
		}
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call3")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_Y][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}

	IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call4")
	{
		CHECK_U_INT(xDest_pu8, &(rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_Z][global_x][0]));
		// xSrc_pcu8 address not possible to reach
		CHECK_U_INT(numBytes_u32, RBL_SIGCHAIN_SIZEOFTCSPNTS);

		return REPLACE_WRAPPER;
	}



    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rba_BswSrv_MemCopy8 */
void AFTER_rba_BswSrv_MemCopy8(struct cppsm_void_return cppsm_dummy,
                               uint8 * xDest_pu8,
                               const uint8 * xSrc_pcu8,
                               uint32 numBytes_u32)
{
    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rba_BswSrv_MemCopy8 */
void REPLACE_rba_BswSrv_MemCopy8(uint8 * xDest_pu8, const uint8 * xSrc_pcu8,   uint32 numBytes_u32)
{
    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call1")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call2")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call3")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRedXReadCb_step1_call4")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call1")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call2")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call3")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRedXReadCb_step1_call4")
    {
        return;
    }


    IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call1")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call2")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call3")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRedXReadCb_step1_call4")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call1")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call2")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call3")
    {
        return;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRedXReadCb_step1_call4")
    {
        return;
    }


    IF_INSTANCE("default")
	{
    	return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_TCOAccRedXReadCb */
int BEFORE_rbl_SigChain_TCOAccRedXReadCb(const void * NvMBuffer,
                                         uint8 x){
    REGISTER_CALL("rbl_SigChain_TCOAccRedXReadCb");

    IF_INSTANCE("rbl_SigChain_TCOAccRed0ReadCb_step1_call1")
    {
    	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
    	CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed1ReadCb_step1_call1")
    {
    	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
    	CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed2ReadCb_step1_call1")
    {
    	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
    	CHECK_U_INT(x, 2);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed3ReadCb_step1_call1")
    {
    	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
    	CHECK_U_INT(x, 3);
        return REPLACE_WRAPPER;
    }




    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCOAccRedXReadCb */
Std_ReturnType AFTER_rbl_SigChain_TCOAccRedXReadCb(Std_ReturnType cppsm_return_value,
                                                   const void * NvMBuffer,
                                                   uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCOAccRedXReadCb */
Std_ReturnType REPLACE_rbl_SigChain_TCOAccRedXReadCb(const void * NvMBuffer, uint8 x)
{

    IF_INSTANCE("rbl_SigChain_TCOAccRed0ReadCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed1ReadCb_step1_call1")
    {
    	 return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed2ReadCb_step1_call1")
    {
    	return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed3ReadCb_step1_call1")
    {
    	return TRUE;
    }




    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCOAccRedXResultCb */
int BEFORE_rbl_SigChain_TCOAccRedXResultCb(uint8 ServiceId,
                                           NvM_RequestResultType JobResult,
                                           uint8 x){
    REGISTER_CALL("rbl_SigChain_TCOAccRedXResultCb");



    IF_INSTANCE("rbl_SigChain_TCOAccRed0ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed1ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed2ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 2);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed3ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 3);
        return REPLACE_WRAPPER;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCOAccRedXResultCb */
Std_ReturnType AFTER_rbl_SigChain_TCOAccRedXResultCb(Std_ReturnType cppsm_return_value,
                                                     uint8 ServiceId,
                                                     NvM_RequestResultType JobResult,
                                                     uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCOAccRedXResultCb */
Std_ReturnType REPLACE_rbl_SigChain_TCOAccRedXResultCb(uint8 ServiceId,
                                                       NvM_RequestResultType JobResult,
                                                       uint8 x){


    IF_INSTANCE("rbl_SigChain_TCOAccRed0ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed1ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed2ResultCb_step1_call1")
    {
    	return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCOAccRed3ResultCb_step1_call1")
    {
    	return TRUE;
    }





    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCORateRedXReadCb */
int BEFORE_rbl_SigChain_TCORateRedXReadCb(const void * NvMBuffer,
                                          uint8 x){
    REGISTER_CALL("rbl_SigChain_TCORateRedXReadCb");

    IF_INSTANCE("rbl_SigChain_TCORateRed0ReadCb_step1_call1")
    {
		CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
		CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRed1ReadCb_step1_call1")
    {
		CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
		CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCORateRedXReadCb */
Std_ReturnType AFTER_rbl_SigChain_TCORateRedXReadCb(Std_ReturnType cppsm_return_value,
                                                    const void * NvMBuffer,
                                                    uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCORateRedXReadCb */
Std_ReturnType REPLACE_rbl_SigChain_TCORateRedXReadCb(const void * NvMBuffer,
                                                      uint8 x){

    IF_INSTANCE("rbl_SigChain_TCORateRed0ReadCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRed1ReadCb_step1_call1")
    {
        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCORateRedXResultCb */
int BEFORE_rbl_SigChain_TCORateRedXResultCb(uint8 ServiceId,
                                            NvM_RequestResultType JobResult,
                                            uint8 x){
    REGISTER_CALL("rbl_SigChain_TCORateRedXResultCb");

    IF_INSTANCE("rbl_SigChain_TCORateRed0ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRed1ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCORateRedXResultCb */
Std_ReturnType AFTER_rbl_SigChain_TCORateRedXResultCb(Std_ReturnType cppsm_return_value,
                                                      uint8 ServiceId,
                                                      NvM_RequestResultType JobResult,
                                                      uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCORateRedXResultCb */
Std_ReturnType REPLACE_rbl_SigChain_TCORateRedXResultCb(uint8 ServiceId,
                                                        NvM_RequestResultType JobResult,
                                                        uint8 x){

    IF_INSTANCE("rbl_SigChain_TCORateRed0ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCORateRed1ResultCb_step1_call1")
    {
        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCSAccRedXReadCb */
int BEFORE_rbl_SigChain_TCSAccRedXReadCb(const void * NvMBuffer,
                                         uint8 x){
    REGISTER_CALL("rbl_SigChain_TCSAccRedXReadCb");

    IF_INSTANCE("rbl_SigChain_TCSAccRed0ReadCb_step1_call1")
      {
      	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
      	CHECK_U_INT(x, 0);
          return REPLACE_WRAPPER;
      }

      IF_INSTANCE("rbl_SigChain_TCSAccRed1ReadCb_step1_call1")
      {
      	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
      	CHECK_U_INT(x, 1);
          return REPLACE_WRAPPER;
      }

      IF_INSTANCE("rbl_SigChain_TCSAccRed2ReadCb_step1_call1")
      {
      	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
      	CHECK_U_INT(x, 2);
          return REPLACE_WRAPPER;
      }

      IF_INSTANCE("rbl_SigChain_TCSAccRed3ReadCb_step1_call1")
      {
      	CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
      	CHECK_U_INT(x, 3);
          return REPLACE_WRAPPER;
      }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCSAccRedXReadCb */
Std_ReturnType AFTER_rbl_SigChain_TCSAccRedXReadCb(Std_ReturnType cppsm_return_value,
                                                   const void * NvMBuffer,
                                                   uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCSAccRedXReadCb */
Std_ReturnType REPLACE_rbl_SigChain_TCSAccRedXReadCb(const void * NvMBuffer,
                                                     uint8 x){

    IF_INSTANCE("rbl_SigChain_TCSAccRed0ReadCb_step1_call1")
	{
	  return TRUE;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRed1ReadCb_step1_call1")
	{
	  return TRUE;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRed2ReadCb_step1_call1")
	{
	  return TRUE;
	}

	IF_INSTANCE("rbl_SigChain_TCSAccRed3ReadCb_step1_call1")
	{
	  return TRUE;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCSAccRedXResultCb */
int BEFORE_rbl_SigChain_TCSAccRedXResultCb(uint8 ServiceId,
                                           NvM_RequestResultType JobResult,
                                           uint8 x){
    REGISTER_CALL("rbl_SigChain_TCSAccRedXResultCb");


    IF_INSTANCE("rbl_SigChain_TCSAccRed0ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed1ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed2ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 2);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed3ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 3);
        return REPLACE_WRAPPER;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCSAccRedXResultCb */
Std_ReturnType AFTER_rbl_SigChain_TCSAccRedXResultCb(Std_ReturnType cppsm_return_value,
                                                     uint8 ServiceId,
                                                     NvM_RequestResultType JobResult,
                                                     uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCSAccRedXResultCb */
Std_ReturnType REPLACE_rbl_SigChain_TCSAccRedXResultCb(uint8 ServiceId,
                                                       NvM_RequestResultType JobResult,
                                                       uint8 x){

    IF_INSTANCE("rbl_SigChain_TCSAccRed0ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed1ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed2ResultCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSAccRed3ResultCb_step1_call1")
    {
        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCSRateRedXReadCb */
int BEFORE_rbl_SigChain_TCSRateRedXReadCb(const void * NvMBuffer,
                                          uint8 x){
    REGISTER_CALL("rbl_SigChain_TCSRateRedXReadCb");

    IF_INSTANCE("rbl_SigChain_TCSRateRed0ReadCb_step1_call1")
    {
		CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
		CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRed1ReadCb_step1_call1")
    {
		CHECK_U_INT(NvMBuffer, &global_NvMBuffer);
		CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCSRateRedXReadCb */
Std_ReturnType AFTER_rbl_SigChain_TCSRateRedXReadCb(Std_ReturnType cppsm_return_value,
                                                    const void * NvMBuffer,
                                                    uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCSRateRedXReadCb */
Std_ReturnType REPLACE_rbl_SigChain_TCSRateRedXReadCb(const void * NvMBuffer,
                                                      uint8 x){

    IF_INSTANCE("rbl_SigChain_TCSRateRed0ReadCb_step1_call1")
    {
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRed1ReadCb_step1_call1")
    {

        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_SigChain_TCSRateRedXResultCb */
int BEFORE_rbl_SigChain_TCSRateRedXResultCb(uint8 ServiceId,
                                            NvM_RequestResultType JobResult,
                                            uint8 x){
    REGISTER_CALL("rbl_SigChain_TCSRateRedXResultCb");

    IF_INSTANCE("rbl_SigChain_TCSRateRed0ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRed1ResultCb_step1_call1")
    {
    	CHECK_U_INT(ServiceId, global_ServiceId);
    	CHECK_U_INT(JobResult, global_JobResult);
    	CHECK_U_INT(x, 1);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_TCSRateRedXResultCb */
Std_ReturnType AFTER_rbl_SigChain_TCSRateRedXResultCb(Std_ReturnType cppsm_return_value,
                                                      uint8 ServiceId,
                                                      NvM_RequestResultType JobResult,
                                                      uint8 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_TCSRateRedXResultCb */
Std_ReturnType REPLACE_rbl_SigChain_TCSRateRedXResultCb(uint8 ServiceId,
                                                        NvM_RequestResultType JobResult,
                                                        uint8 x){

    IF_INSTANCE("rbl_SigChain_TCSRateRed0ResultCb_step1_call1")
	{
        return TRUE;
    }

    IF_INSTANCE("rbl_SigChain_TCSRateRed1ResultCb_step1_call1")
    {
        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
