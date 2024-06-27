/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/

/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/


#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_SigChain_OsPub.h"
#include "../src/rbl_SigChain_priv.h"
#include "../src/rbl_SigChain_SigFil.h"
#include "Dem.h"
#include "rbl_ImuCdd_Interfaces.h"

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rbl_SigChainInit();
extern boolean ACCESS_FUNCTION_rbl_SigChain_Init_rbl_SigChainActive_Init(uint32 * activeModules);
extern boolean ACCESS_FUNCTION_rbl_SigChain_Init_rbl_SigChain_NVMcontentValid(uint32 * activeModules);
void RBSYS_EnterCommonLock_intern();
void RBSYS_ExitCommonLock_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus);
Std_ReturnType rbl_ImuCddIf_GetAvlSmi(uint8 * AvlSmi_au8);
boolean rbl_SigChain_MntgOffsInit(boolean active);
void rbl_SigChain_MntgOrntInit(boolean active);
void Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
boolean rbl_SigChain_TCOSAllNvmItemsValid();
boolean rbl_SigChain_TCSAllNvmItemsValid();
boolean rbl_SigChain_AngOffsInit(boolean active);
void rbl_SigChain_InitFilter(const rbl_SigChain_FilterArray_t * filter, uint16 flush, float timestampdelay);
void rbl_SigChain_InitFilter2(const rbl_SigChain_FilterArray_t* filter, uint16 flush, float timestampdelay);
Std_ReturnType Dem_SetEventStatusWithMonitorData(Dem_EventIdType EventId, Dem_EventStatusType EventStatus, Dem_MonitorDataType monitorData0, Dem_MonitorDataType monitorData1);
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);


/* Global data */
extern uint32 rbl_SignalChainActive;
extern volatile RBMESG_Type_SigChain_stValid RBMESG_SigChain_stValid;
boolean rbl_SigChain_AlgnAccSnvtyNvmVld;
boolean rbl_SigChain_Algn_RateSnvtyNvmVld;
boolean rbl_SigChain_SigFilNvmVld;

extern rbl_SigChain_FilterArray_t rbl_SigChain_FilVal;
extern uint16 rbl_SigChain_SigFilFlush;


/* Expected variables for global data */
uint32 expected_rbl_SignalChainActive;
RBMESG_Type_SigChain_stValid expected_RBMESG_SigChain_stValid;
boolean expected_rbl_SigChain_AlgnAccSnvtyNvmVld;
boolean expected_rbl_SigChain_Algn_RateSnvtyNvmVld;
boolean expected_rbl_SigChain_SigFilNvmVld;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal;
uint16 expected_rbl_SigChain_SigFilFlush;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data()
{
    INITIALISE(rbl_SignalChainActive);
    INITIALISE(RBMESG_SigChain_stValid);
    INITIALISE(rbl_SigChain_AlgnAccSnvtyNvmVld);
    INITIALISE(rbl_SigChain_Algn_RateSnvtyNvmVld);
    INITIALISE(rbl_SigChain_SigFilNvmVld);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data()
{
    COPY_TO_EXPECTED(rbl_SignalChainActive, expected_rbl_SignalChainActive);
    COPY_TO_EXPECTED(RBMESG_SigChain_stValid, expected_RBMESG_SigChain_stValid);
    COPY_TO_EXPECTED(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
    COPY_TO_EXPECTED(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);
    COPY_TO_EXPECTED(rbl_SigChain_SigFilNvmVld, expected_rbl_SigChain_SigFilNvmVld);
}

/* This function checks global data against the expected values. */
static void check_global_data()
{
    CHECK_U_INT(rbl_SignalChainActive, expected_rbl_SignalChainActive);
    CHECK_BOOLEAN(RBMESG_SigChain_stValid, expected_RBMESG_SigChain_stValid);
    CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
    CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);
    CHECK_BOOLEAN(rbl_SigChain_SigFilNvmVld, expected_rbl_SigChain_SigFilNvmVld);
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChainInit(int);
void ut_rbl_SigChainActive_Init(int);
void ut_rbl_SigChain_NVMcontentValid(int);

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
    OPEN_LOG("ut_rbl_SigChain_Init.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_Init", true);

    WRITE_LOG("\n * ---------------------- TEST SUITE UTS_rbl_SigChain ----------------------*\n", cppth_ll_minimal,true);
    WRITE_LOG(" * -----------------PROJECT: MMP2------ SOFTWARE: ASW------------------ *\n", cppth_ll_minimal,true);
    WRITE_LOG(" * ----TEST CAMPAIGN RUN NUMBER 1.6-- LAST SCRIPT UPDATE: 16/10/2023 ---- *\n", cppth_ll_minimal,true);
    WRITE_LOG(" * ---SCRIPT IMPLEMENTED BY:MAJ3BRG -- TEST RUN PERFORMED BY MAJ3BRG --- *\n", cppth_ll_minimal,true);
    WRITE_LOG(" * ---SCRIPT REWORKED BY: MAJ3BRG ----- TEST RUN PERFORMED BY: MAJ3BRG --- *\n",cppth_ll_minimal,true);
    WRITE_LOG(" * -------------------------TEST SUITE ID: 1443 ------------------------- *\n\n", cppth_ll_minimal,true);

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
    ut_rbl_SigChainInit(1);
    ut_rbl_SigChainActive_Init(1);
    ut_rbl_SigChain_NVMcontentValid(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_Init.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChainInit(int doIt)
{
	if (doIt)
	{

		START_TEST("47478: [MMP2.11]UTC_rbl_SigChain_Init",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47478");

		START_STEP("1_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Active components of Signal Chain
		    rbl_SignalChainActive = RBL_SIGCHAIN_ALL;
		    expected_rbl_SignalChainActive = 0;

		    	// Are signals valid
		    RBMESG_SigChain_stValid = FALSE;
			expected_RBMESG_SigChain_stValid = TRUE;


			// EXPECTED CALLS
#if (RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)

			EXPECTED_CALLS("rbl_SigChain_InitFilter#SigChainInit_InitFilter;\
							rbl_SigChain_InitFilter2#SigChainInit_InitFilter2;\
							rbl_SigChainActive_Init#SigChainInit_ActiveInit_S1;\
							rbl_SigChain_NVMcontentValid#SigChainInit_NVMcontent;");
#else

			EXPECTED_CALLS("rbl_SigChain_InitFilter#SigChainInit_InitFilter;\
							rbl_SigChainActive_Init#SigChainInit_ActiveInit_S1;\
							rbl_SigChain_NVMcontentValid#SigChainInit_NVMcontent;");
#endif

			// CALL SUT
			rbl_SigChainInit();


			// EXPECTED RESULTS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		START_STEP("2_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS

				// Active components of Signal Chain
			rbl_SignalChainActive = RBL_SIGCHAIN_ALL;
			expected_rbl_SignalChainActive = 0;

				// Are signals valid
			RBMESG_SigChain_stValid = TRUE;
			expected_RBMESG_SigChain_stValid = FALSE;


			// EXPECTED CALLS
#if (RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)

			EXPECTED_CALLS("rbl_SigChain_InitFilter#SigChainInit_InitFilter;\
							rbl_SigChain_InitFilter2#SigChainInit_InitFilter2;\
							rbl_SigChainActive_Init#SigChainInit_ActiveInit_S2;");
#else

			EXPECTED_CALLS("rbl_SigChain_InitFilter#SigChainInit_InitFilter;\
							rbl_SigChainActive_Init#SigChainInit_ActiveInit_S2;");
#endif


			// CALL SUT
			rbl_SigChainInit();


			// EXPECTED RESULTS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChainActive_Init(int doIt)
{
	if (doIt)
	{
		boolean returnValue = 0, expected_returnValue = 0;
		uint32 activeModules = 0,expected_activeModules = 0;

		START_TEST("47479: [MMP2.11]UTC_rbl_SigChainActive_Init",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47479");


		START_STEP("1_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS

				// SigChain active components
			activeModules = 0;
			expected_activeModules = RBL_SIGCHAIN_ALL;

				// Return value
			returnValue = FALSE;
			expected_returnValue = TRUE;


			// EXPECTED CALLS
			EXPECTED_CALLS("");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChainActive_Init)(&activeModules);


			// EXPECTED RESULTS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_NVMcontentValid(int doIt)
{
	if (doIt)
	{
		boolean returnValue = FALSE;
		uint32 activeModules = FALSE;

		boolean expected_returnValue = returnValue;
		uint32 expected_activeModules = activeModules;

		START_TEST("47480: [MMP2.11]UTC_rbl_SigChain_NVMcontentValid",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47480");

		START_STEP("1_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS

				// Return value
			returnValue = FALSE;
			expected_returnValue = TRUE;

				// Active modules
			activeModules = FALSE;
			expected_activeModules = activeModules;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatus#rbl_SigChain_SetEventStatus");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);

			END_CALLS();
		}
		END_STEP();


		START_STEP("2_NTS" , TRUE); // ------- TCO cond1 T  -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = TRUE;
			expected_returnValue = FALSE;

				// Active modules
			activeModules = RBL_IMU_TCOS;
			expected_activeModules = 0;


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_SigChain_TCOSAllNvmItemsValid#Return_False;\
							Dem_SetEventStatusWithMonitorData#NVMcontentValid_SetEventStatusWithMonitorData_TS2;");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);

			END_CALLS();
		}
		END_STEP();


		START_STEP("3_NTS" , TRUE); // ------- TCO cond1 F  -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = FALSE;
			expected_returnValue = TRUE;

				// Active modules
			activeModules = RBL_IMU_TCOS;
			expected_activeModules = activeModules;


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_SigChain_TCOSAllNvmItemsValid#Return_True;\
							Dem_SetEventStatus#rbl_SigChain_SetEventStatus");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);

			END_CALLS();
		}
		END_STEP();


		START_STEP("4_NTS" , TRUE); // ------- Alignement cond1 F  cond 2  T  cond 3 F -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = TRUE;
			expected_returnValue = FALSE;

				// Active modules
			activeModules = RBL_IMU_ALGN;
			expected_activeModules = 0;

				//  Acc Nvm valid marker
			rbl_SigChain_AlgnAccSnvtyNvmVld = FALSE;
			expected_rbl_SigChain_AlgnAccSnvtyNvmVld = rbl_SigChain_AlgnAccSnvtyNvmVld;

				//  Rate Nvm valid marker
			rbl_SigChain_Algn_RateSnvtyNvmVld = TRUE;
			expected_rbl_SigChain_Algn_RateSnvtyNvmVld = rbl_SigChain_Algn_RateSnvtyNvmVld;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatusWithMonitorData#NVMcontentValid_SetEventStatusWithMonitorData_TS4");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);
			CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
			CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);

			END_CALLS();
		}
		END_STEP();


		START_STEP("5_NTS" , TRUE); // ------- Alignement cond1 F  cond 2  F  cond 3 T -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = TRUE;
			expected_returnValue = FALSE;

				// Active modules
			activeModules = RBL_IMU_ALGN;
			expected_activeModules = 0;

				//  Acc Nvm valid marker
			rbl_SigChain_AlgnAccSnvtyNvmVld = TRUE;
			expected_rbl_SigChain_AlgnAccSnvtyNvmVld = rbl_SigChain_AlgnAccSnvtyNvmVld;

				//  Rate Nvm valid marker
			rbl_SigChain_Algn_RateSnvtyNvmVld = FALSE;
			expected_rbl_SigChain_Algn_RateSnvtyNvmVld = rbl_SigChain_Algn_RateSnvtyNvmVld;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatusWithMonitorData#NVMcontentValid_SetEventStatusWithMonitorData_TS5");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);
			CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
			CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);

			END_CALLS();
		}
		END_STEP();


		START_STEP("6_NTS" , TRUE); // ------- Alignement cond1 F  cond 2  F  cond 3 F -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = FALSE;
			expected_returnValue = TRUE;

				// Active modules
			activeModules = RBL_IMU_ALGN;
			expected_activeModules = activeModules;

				//  Acc Nvm valid marker
			rbl_SigChain_AlgnAccSnvtyNvmVld = TRUE;
			expected_rbl_SigChain_AlgnAccSnvtyNvmVld = rbl_SigChain_AlgnAccSnvtyNvmVld;

				//  Rate Nvm valid marker
			rbl_SigChain_Algn_RateSnvtyNvmVld = TRUE;
			expected_rbl_SigChain_Algn_RateSnvtyNvmVld = rbl_SigChain_Algn_RateSnvtyNvmVld;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatus#rbl_SigChain_SetEventStatus");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);
			CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
			CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);

			END_CALLS();
		}
		END_STEP();


#if (RBFS_NvmBasedFilter == RBFS_NvmBasedFilter_ON)

		START_STEP("7_NTS" , TRUE); // ------- Signal Filter cond1 T  cond 2 T -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = FALSE;
			expected_returnValue = TRUE;

				// Active modules
			activeModules = RBL_IMU_SIGFIL;
			expected_activeModules = activeModules;

				//  SigFil valid marker
			rbl_SigChain_SigFilNvmVld = TRUE;
			expected_rbl_SigChain_SigFilNvmVld = rbl_SigChain_SigFilNvmVld;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatus#rbl_SigChain_SetEventStatus");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);
			CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
			CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);

			END_CALLS();
		}
		END_STEP();

		START_STEP("8_NTS" , TRUE); // ------- Signal Filter cond1 T  cond 2 T -------
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED_RESULTS
				// Return value
			returnValue = TRUE;
			expected_returnValue = FALSE;

				// Active modules
			activeModules = RBL_IMU_SIGFIL;
			expected_activeModules = activeModules & ~RBL_IMU_SIGFIL;

				//  SigFil valid marker
			rbl_SigChain_SigFilNvmVld = FALSE;
			expected_rbl_SigChain_SigFilNvmVld = rbl_SigChain_SigFilNvmVld;


			// EXPECTED CALLS
			EXPECTED_CALLS("Dem_SetEventStatusWithMonitorData#NVMcontentValid_SetEventStatusWithMonitorData_TS8");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_Init, rbl_SigChain_NVMcontentValid)(&activeModules);


			// SUT CHECKS
			check_global_data();
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			CHECK_U_INT(activeModules, expected_activeModules);
			CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
			CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);

			END_CALLS();
		}
		END_STEP();

#endif

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

/* Stub for function Dem_SetEventAvailable */
Std_ReturnType Dem_SetEventAvailable(Dem_EventIdType EventId, boolean AvailableStatus)
{
    REGISTER_CALL("Dem_SetEventAvailable");

    IF_INSTANCE("default")
    {
        return 0;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_ImuCddIf_GetAvlSmi */
Std_ReturnType rbl_ImuCddIf_GetAvlSmi(uint8 * AvlSmi_au8)
{
    REGISTER_CALL("rbl_ImuCddIf_GetAvlSmi");

    IF_INSTANCE("rbl_SigChainInit_Return_E_OK")
    {
    	//CHECK_U_INT(AvlSmi_au8 , rbl_SigChain_AvlSmi);
        return E_OK;
    }

    IF_INSTANCE("rbl_SigChainInit_Return_E_NOT_OK")
    {
    	//CHECK_U_INT(AvlSmi_au8 , rbl_SigChain_AvlSmi);
        return E_NOT_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_SigChain_MntgOffsInit */
boolean rbl_SigChain_MntgOffsInit(boolean active)
{
    REGISTER_CALL("rbl_SigChain_MntgOffsInit");

    IF_INSTANCE("rbl_SigChainInit_Return_false")
    {
    	CHECK_U_INT(active , FALSE);
        return 0;
    }

    IF_INSTANCE("rbl_SigChainInit_Return_true")
    {
    	CHECK_U_INT(active , FALSE);
        return 1;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_SigChain_MntgOrntInit */
void rbl_SigChain_MntgOrntInit(boolean active)
{
    REGISTER_CALL("rbl_SigChain_MntgOrntInit");

    IF_INSTANCE("rbl_SigChainInit_Return")
    {
    	CHECK_U_INT(active , FALSE);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function Dem_ReportErrorStatus */
void Dem_ReportErrorStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
    REGISTER_CALL("Dem_ReportErrorStatus");


    IF_INSTANCE("rbl_SigChainActive_Init_Return_Passed")
    {
    	CHECK_U_INT( EventId , 104u);
    	CHECK_U_INT( EventStatus , DEM_EVENT_STATUS_PASSED);
        return;
    }

    IF_INSTANCE("rbl_SigChain_NVMcontentValid_Return_Passed")
    {
    	CHECK_U_INT( EventId , DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
    	CHECK_U_INT( EventStatus , DEM_EVENT_STATUS_PASSED);
        return;
    }


    IF_INSTANCE("Return")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChain_TCOSAllNvmItemsValid */
boolean rbl_SigChain_TCOSAllNvmItemsValid()
{
    REGISTER_CALL("rbl_SigChain_TCOSAllNvmItemsValid");

    IF_INSTANCE("Return_True")
    {
        return TRUE;
    }

    IF_INSTANCE("Return_False")
    {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_SigChain_TCSAllNvmItemsValid */
boolean rbl_SigChain_TCSAllNvmItemsValid()
{
    REGISTER_CALL("rbl_SigChain_TCSAllNvmItemsValid");

    IF_INSTANCE("Return_True")
    {
        return TRUE;
    }

    IF_INSTANCE("Return_False")
    {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_SigChain_AngOffsInit */
boolean rbl_SigChain_AngOffsInit(boolean active)
{
    REGISTER_CALL("rbl_SigChain_AngOffsInit");

    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_ANGOFFS_RBL_IMU_MNTGOFFS_return_0")
    {
    	CHECK_U_INT(active, FALSE);
        return 0;
    }

    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_ANGOFFS_RBL_IMU_MNTGOFFS_return_1")
    {
    	CHECK_U_INT(active, FALSE);
        return 1;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_SigChain_InitFilter */
void rbl_SigChain_InitFilter(const rbl_SigChain_FilterArray_t * filter,
                             uint16 flush,
                             float timestampdelay)
{
    REGISTER_CALL("rbl_SigChain_InitFilter");

    IF_INSTANCE("default")
    {
        return;
    }

    IF_INSTANCE("SigChainInit_InitFilter")
    {
    	CHECK_U_INT((unsigned int) filter, NULL);
    	CHECK_U_INT(flush, 0);
    	CHECK_DOUBLE(timestampdelay, 0.0);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_SigChain_InitFilter2 */
void rbl_SigChain_InitFilter2(const rbl_SigChain_FilterArray_t * filter,
                             uint16 flush,
                             float timestampdelay)
{
    REGISTER_CALL("rbl_SigChain_InitFilter2");

    IF_INSTANCE("default")
    {
        return;
    }

    IF_INSTANCE("SigChainInit_InitFilter2")
    {
    	CHECK_U_INT((unsigned int) filter, NULL);
    	CHECK_U_INT(flush, 0);
    	CHECK_DOUBLE(timestampdelay, 0.0);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function Dem_SetEventStatusWithMonitorData */
Std_ReturnType Dem_SetEventStatusWithMonitorData(Dem_EventIdType EventId,
                                                 Dem_EventStatusType EventStatus,
                                                 Dem_MonitorDataType monitorData0,
                                                 Dem_MonitorDataType monitorData1){
    REGISTER_CALL("Dem_SetEventStatusWithMonitorData");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("NVMcontentValid_SetEventStatusWithMonitorData_TS2")
    {
    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
		CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
		CHECK_U_INT(monitorData0, RBL_IMU_TCOS);
		CHECK_U_INT(monitorData1, 0);
        return 0;
    }

    IF_INSTANCE("NVMcontentValid_SetEventStatusWithMonitorData_TS4")
    {
    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
		CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
		CHECK_U_INT(monitorData0, RBL_IMU_ALGN);
		CHECK_U_INT(monitorData1, 0);
        return 0;
    }

    IF_INSTANCE("NVMcontentValid_SetEventStatusWithMonitorData_TS5")
    {
    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
		CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
		CHECK_U_INT(monitorData0, RBL_IMU_ALGN);
		CHECK_U_INT(monitorData1, 0);
        return 0;
    }

    IF_INSTANCE("NVMcontentValid_SetEventStatusWithMonitorData_TS8")
    {
    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
		CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
		CHECK_U_INT(monitorData0, RBL_IMU_SIGFIL);
		CHECK_U_INT(monitorData1, 0);
        return 0;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function Dem_SetEventStatus */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                                  Dem_EventStatusType EventStatus)
{
    REGISTER_CALL("Dem_SetEventStatus");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("rbl_SigChain_SetEventStatus")
    {
    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_PASSED);
        return 0;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

///* Stub for function Dem_ReportErrorStatusWithEnvData */
//void Dem_ReportErrorStatusWithEnvData(Dem_EventIdType EventId, Dem_EventStatusType EventStatus, Dem_DebugDataType debug0, Dem_DebugDataType debug1)
//{
//    REGISTER_CALL("Dem_ReportErrorStatusWithEnvData");
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_CHMAP")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	CHECK_U_INT(debug0, RBL_IMU_CHMAP);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_TCO")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	CHECK_U_INT(debug0, RBL_IMU_TCOS);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_TCO")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	CHECK_U_INT(debug0, RBL_IMU_TCOS);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_ALGN")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	CHECK_U_INT(debug0, RBL_IMU_ALGN);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_FINEOFF")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	//CHECK_U_INT(debug0, RBL_IMU_FINEOFF);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_SIGSEL")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	//CHECK_U_INT(debug0, RBL_IMU_SIGSEL);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_CORRMONHF_27")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	// CHECK_U_INT(debug0, RBL_IMU_CORRMONHF & (RBL_IMU_CORRMONHF));
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_CORRMONHF_28")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	// CHECK_U_INT(debug0, RBL_IMU_CORRMONHF & (RBL_IMU_CORRMONHF));
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_CORRMONHF")
//     {
//     	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//     	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//     	// CHECK_U_INT(debug0, RBL_IMU_CORRMONHF);
//     	CHECK_U_INT(debug1, FALSE);
//
//         return;
//     }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_SIGFIL")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	CHECK_U_INT(debug0, RBL_IMU_SIGFIL);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_ORIENTATION")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	// CHECK_U_INT(debug0, RBL_IMU_ORIENTATION);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    IF_INSTANCE("rbl_SigChain_NVMcontentValid_RBL_IMU_ANGOFFS_RBL_IMU_MNTGOFFS")
//    {
//    	CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_Nvm_SigChain_Content);
//    	CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
//    	//CHECK_U_INT(debug0, RBL_IMU_ANGOFFS);
//    	CHECK_U_INT(debug1, FALSE);
//
//        return;
//    }
//
//    LOG_SCRIPT_ERROR("Call instance not defined.");
//    return;
//}
#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChainActive_Init */
int BEFORE_rbl_SigChainActive_Init(uint32 * x)
{
    REGISTER_CALL("rbl_SigChainActive_Init");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("SigChainInit_ActiveInit_S1")
    {
    	CHECK_U_INT(*x, 0);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("SigChainInit_ActiveInit_S2")
    {
    	CHECK_U_INT(*x, 0);
        return REPLACE_WRAPPER;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChainActive_Init */
boolean AFTER_rbl_SigChainActive_Init(boolean cppsm_return_value, uint32 * x)
{
    IF_INSTANCE("Return")
    {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChainActive_Init */
boolean REPLACE_rbl_SigChainActive_Init(uint32 * x)
{

    IF_INSTANCE("default")
    {
        return FALSE;
    }

    IF_INSTANCE("SigChainInit_ActiveInit_S1")
    {
        return TRUE;
    }

    IF_INSTANCE("SigChainInit_ActiveInit_S2")
    {
        return FALSE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Before-Wrapper for function rbl_SigChain_NVMcontentValid */
int BEFORE_rbl_SigChain_NVMcontentValid(uint32 * x)
{
    REGISTER_CALL("rbl_SigChain_NVMcontentValid");

    IF_INSTANCE("SigChainInit_NVMcontent")
    {
    	CHECK_U_INT(*x, FALSE);

        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_NVMcontentValid */
boolean AFTER_rbl_SigChain_NVMcontentValid(boolean cppsm_return_value, uint32 * x)
{
    IF_INSTANCE("Return")
    {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_NVMcontentValid */
boolean REPLACE_rbl_SigChain_NVMcontentValid(uint32 * x)
{

    IF_INSTANCE("SigChainInit_NVMcontent")
    {
        return TRUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
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
