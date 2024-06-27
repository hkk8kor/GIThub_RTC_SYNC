/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/

/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Nvm.h"
#include "rbl_SigChain_Nvm.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_SigFil.h"
#include "rba_BswSrv.h"
#include "RB_Contract.h"
#include "RBPDM.h"

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/


/* Global Functions */
extern boolean rbl_SigChain_NvmValidCheck(uint8 ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType rbl_SigChain_GenericWriteCb(void * NvMBuffer);
extern Std_ReturnType rbl_SigChain_AlgnAccSnvtyReadCb(void * NvMBuffer);
extern Std_ReturnType rbl_SigChain_AlgnAccSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);
extern Std_ReturnType rbl_SigChain_AlgnRateSnvtyReadCb(void * NvMBuffer);
extern Std_ReturnType rbl_SigChain_AlgnRateSnvtyResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);
//extern Std_ReturnType rbl_SigChain_PickFilResultCb(uint8 ServiceId, NvM_RequestResultType JobResult);

// Aux functions
static void init_filters_random();

/* Global data */
rbl_SigChain_AlgnMtrx_t rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
extern boolean rbl_SigChain_AlgnAccSnvtyNvmVld;
rbl_SigChain_AlgnMtrx_t rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
extern boolean rbl_SigChain_Algn_RateSnvtyNvmVld;
//extern uint8 rbl_SigChain_PickFilValue[2];
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal;
rbl_SigChain_FilterArray_t rbl_SigChain_FilValNoFilter;
uint16 rbl_SigChain_SigFilFlush;
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal20Hz;
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal45Hz;
//extern boolean rbl_SigChain_SigFilNvmVld;

sint16 globalAcc_matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
sint16 expected_globalAcc_matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];

sint16 globalRate_matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];
sint16 expected_globalRate_matrix[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_AXIS_NO][RBL_SIGCHAIN_ALGN_PNTS];

/* Expected variables for global data */
rbl_SigChain_AlgnMtrx_t expected_rbl_SigChain_AlgnAccOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
boolean expected_rbl_SigChain_AlgnAccSnvtyNvmVld;
rbl_SigChain_AlgnMtrx_t expected_rbl_SigChain_AlgnRateOrthMtrx[RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
boolean expected_rbl_SigChain_Algn_RateSnvtyNvmVld;
//uint8 expected_rbl_SigChain_PickFilValue[2];
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilValNoFilter;
uint16 expected_rbl_SigChain_SigFilFlush;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal20Hz;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal45Hz;
//boolean expected_rbl_SigChain_SigFilNvmVld;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data()
{
    INITIALISE(rbl_SigChain_AlgnAccOrthMtrx);
    INITIALISE(rbl_SigChain_AlgnAccSnvtyNvmVld);
    INITIALISE(rbl_SigChain_AlgnRateOrthMtrx);
    INITIALISE(rbl_SigChain_Algn_RateSnvtyNvmVld);
//    INITIALISE(rbl_SigChain_PickFilValue);
    INITIALISE(rbl_SigChain_FilVal);
    INITIALISE(rbl_SigChain_FilValNoFilter);
    INITIALISE(rbl_SigChain_SigFilFlush);
    INITIALISE(rbl_SigChain_FilVal20Hz);
    INITIALISE(rbl_SigChain_FilVal45Hz);
//    INITIALISE(rbl_SigChain_SigFilNvmVld);
    init_filters_random();
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data()
{
    COPY_TO_EXPECTED(rbl_SigChain_AlgnAccOrthMtrx, expected_rbl_SigChain_AlgnAccOrthMtrx);
    COPY_TO_EXPECTED(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
    COPY_TO_EXPECTED(rbl_SigChain_AlgnRateOrthMtrx, expected_rbl_SigChain_AlgnRateOrthMtrx);
    COPY_TO_EXPECTED(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);
//    COPY_TO_EXPECTED(rbl_SigChain_PickFilValue, expected_rbl_SigChain_PickFilValue);
    COPY_TO_EXPECTED(rbl_SigChain_FilVal, expected_rbl_SigChain_FilVal);
    COPY_TO_EXPECTED(rbl_SigChain_FilValNoFilter, expected_rbl_SigChain_FilValNoFilter);
    COPY_TO_EXPECTED(rbl_SigChain_SigFilFlush, expected_rbl_SigChain_SigFilFlush);
    COPY_TO_EXPECTED(rbl_SigChain_FilVal20Hz, expected_rbl_SigChain_FilVal20Hz);
    COPY_TO_EXPECTED(rbl_SigChain_FilVal45Hz, expected_rbl_SigChain_FilVal45Hz);
//    COPY_TO_EXPECTED(rbl_SigChain_SigFilNvmVld, expected_rbl_SigChain_SigFilNvmVld);
}

/* This function checks global data against the expected values. */
static void check_global_data()
{
    CHECK_MEMORY("rbl_SigChain_AlgnAccOrthMtrx", rbl_SigChain_AlgnAccOrthMtrx, expected_rbl_SigChain_AlgnAccOrthMtrx, sizeof(expected_rbl_SigChain_AlgnAccOrthMtrx));
    CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
    CHECK_MEMORY("rbl_SigChain_AlgnRateOrthMtrx", rbl_SigChain_AlgnRateOrthMtrx, expected_rbl_SigChain_AlgnRateOrthMtrx, sizeof(expected_rbl_SigChain_AlgnRateOrthMtrx));
    CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);
//    CHECK_U_INT(rbl_SigChain_PickFilValue[0], expected_rbl_SigChain_PickFilValue[0]);
//    CHECK_U_INT(rbl_SigChain_PickFilValue[1], expected_rbl_SigChain_PickFilValue[1]);
    CHECK_MEMORY("rbl_SigChain_FilVal", &rbl_SigChain_FilVal, &expected_rbl_SigChain_FilVal, sizeof(expected_rbl_SigChain_FilVal));
    CHECK_MEMORY("rbl_SigChain_FilValNoFilter", &rbl_SigChain_FilValNoFilter, &expected_rbl_SigChain_FilValNoFilter, sizeof(expected_rbl_SigChain_FilValNoFilter));
    CHECK_U_INT(rbl_SigChain_SigFilFlush, expected_rbl_SigChain_SigFilFlush);
    CHECK_MEMORY("rbl_SigChain_FilVal20Hz", &rbl_SigChain_FilVal20Hz, &expected_rbl_SigChain_FilVal20Hz, sizeof(expected_rbl_SigChain_FilVal20Hz));
    CHECK_MEMORY("rbl_SigChain_FilVal45Hz", &rbl_SigChain_FilVal45Hz, &expected_rbl_SigChain_FilVal45Hz, sizeof(expected_rbl_SigChain_FilVal45Hz));
//    CHECK_BOOLEAN(rbl_SigChain_SigFilNvmVld, expected_rbl_SigChain_SigFilNvmVld);

    CHECK_MEMORY("globalAcc_matrix", &globalAcc_matrix, &expected_globalAcc_matrix, sizeof(globalAcc_matrix));
}

static void init_filters_random()
{
	int i = 0, j = 0, k = 0;

	for (i = 0; i < RBL_SIGCHN_FIL; i++)
	{
		for (j = 0; j < 2; j++)
		{
			rbl_SigChain_FilVal.filVal[i].facA[j] = i + j + 1;
			rbl_SigChain_FilValNoFilter.filVal[i].facA[j] = 3 * (i + j + 2);
			rbl_SigChain_FilVal20Hz.filVal[i].facA[j] = -4 * (i + j + 3);
			rbl_SigChain_FilVal45Hz.filVal[i].facA[j] = 50 * (i + j + 4);
		}

		for (k = 0; k < 3; k++)
		{
			rbl_SigChain_FilVal.filVal[i].facB[k] = i + k + 1;
			rbl_SigChain_FilValNoFilter.filVal[i].facB[k]= -7 * (i + k + 2);
			rbl_SigChain_FilVal20Hz.filVal[i].facB[k]= 11 * (i + k + 3);
			rbl_SigChain_FilVal45Hz.filVal[i].facB[k]= - 23 * (i + k + 4);
		}
	}

}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChain_NvmValidCheck(int);
void ut_rbl_SigChain_GenericWriteCb(int);
void ut_rbl_SigChain_AlgnAccSnvtyReadCb(int);
void ut_rbl_SigChain_AlgnAccSnvtyResultCb(int);
void ut_rbl_SigChain_AlgnRateSnvtyReadCb(int);
void ut_rbl_SigChain_AlgnRateSnvtyResultCb(int);
//void ut_rbl_SigChain_PickFilResultCb(int);

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
    OPEN_LOG("ut_rbl_SigChain_Nvm.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_Nvm", true);

    WRITE_LOG(" * -------------------- TEST SUITE OF UTS_rbl_SigChain -------------------*", cppth_ll_minimal,true);
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
    ut_rbl_SigChain_NvmValidCheck(1);
    ut_rbl_SigChain_GenericWriteCb(1);
    ut_rbl_SigChain_AlgnAccSnvtyReadCb(1);
    ut_rbl_SigChain_AlgnAccSnvtyResultCb(1);
    ut_rbl_SigChain_AlgnRateSnvtyReadCb(1);
    ut_rbl_SigChain_AlgnRateSnvtyResultCb(1);
//    ut_rbl_SigChain_PickFilResultCb(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_Nvm.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChain_NvmValidCheck(int doIt)
{
	if (doIt)
	{
		uint8 ServiceId = 0;
		NvM_RequestResultType JobResult = 0;
		boolean returnValue = 0, expected_returnValue = 0;

		START_TEST("47518: [MMP2.11]UTC_rbl_SigChain_NvmValidCheck",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47518");

		START_STEP("1_NTS", TRUE)
		{
			initialise_global_data();
			initialise_expected_global_data();


			// Initial conditions/ expected results
			ServiceId = NVM_SERVICE_ID_READ_ALL + 1;	// Must be different from NVM_SERVICE_ID_READ_ALL
			JobResult = 0;								// Value does not matter

			returnValue = TRUE;
			expected_returnValue = FALSE;


			// Expected Call Sequence
			EXPECTED_CALLS("");


			// Call SUT
			returnValue = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);


			// Test case checks
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			check_global_data();

			END_CALLS();
		}
		END_STEP();

		START_STEP("2_NTS", TRUE)
		{
			initialise_global_data();
			initialise_expected_global_data();


			// Initial conditions/ expected results
			ServiceId = NVM_SERVICE_ID_READ_ALL;
			JobResult = NVM_REQ_OK + 1;				// Must be different from NVM_REQ_OK

			returnValue = TRUE;
			expected_returnValue = FALSE;


			// Expected Call Sequence
			EXPECTED_CALLS("");


			// Call SUT
			returnValue = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);


			// Test case checks
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			check_global_data();

			END_CALLS();
		}
		END_STEP();

		START_STEP("3_NTS", TRUE)
		{
			initialise_global_data();
			initialise_expected_global_data();


			// Initial conditions/ expected results
			ServiceId = NVM_SERVICE_ID_READ_ALL;
			JobResult = NVM_REQ_OK;

			returnValue = FALSE;
			expected_returnValue = TRUE;


			// Expected Call Sequence
			EXPECTED_CALLS("");


			// Call SUT
			returnValue = rbl_SigChain_NvmValidCheck(ServiceId, JobResult);


			// Test case checks
			CHECK_BOOLEAN(returnValue, expected_returnValue);
			check_global_data();

			END_CALLS();
		}
		END_STEP();

		END_TEST();
	}
}

void ut_rbl_SigChain_GenericWriteCb(int doIt)
{
	if (doIt)
	{
		boolean returnValue = 0, expected_returnValue = 0;
		void * NvMBuffer;

		START_TEST("47519: [MMP2.11]UTC_rbl_SigChain_GenericWriteCb",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47519");

			initialise_global_data();
			initialise_expected_global_data();

			// Initial conditions/ Expected results
			returnValue = E_OK;
			expected_returnValue = E_NOT_OK;


			// Expected Call Sequence
			EXPECTED_CALLS("");


			// Call SUT
			returnValue = rbl_SigChain_GenericWriteCb(NvMBuffer);


			// Test case checks
			CHECK_U_CHAR(returnValue, expected_returnValue);
			check_global_data();

			END_CALLS();

		END_TEST();
	}
}

void ut_rbl_SigChain_AlgnAccSnvtyReadCb(int doIt)
{
	if (doIt)
	{
		Std_ReturnType returnValue = 0, expected_returnValue = 0;
		int i = 0, j = 0, k = 0, l = 0;

		START_TEST("47522: [MMP2.11]UTC_rbl_SigChain_AlgnAccSnvtyReadCb",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47522");

			initialise_global_data();
			initialise_expected_global_data();

			// Initial conditions/ Expected results
			returnValue = E_NOT_OK;
			expected_returnValue = E_OK;

			for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; i++)
			{
				for (j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
				{
					for (k = 0; k < RBL_IMUSTDTYPES_AXIS_NO; k++)
					{
						for (l = 0; l < RBL_SIGCHAIN_ALGN_PNTS; l++)
						{
							globalAcc_matrix[i][j][k][l] = i + j + k + l + 1;		// I + J + K + L + one || "Random" value
							expected_globalAcc_matrix[i][j][k][l] = globalAcc_matrix[i][j][k][l];

							rbl_SigChain_AlgnAccOrthMtrx[i].AlgnOrthMtrx[j][k][l] = 0;
							expected_rbl_SigChain_AlgnAccOrthMtrx[i].AlgnOrthMtrx[j][k][l] = globalAcc_matrix[i][j][k][l];
						}
					}
				}
			}


			// Expected Call Sequence
			EXPECTED_CALLS("rba_BswSrv_MemCopy8#AlgnAccSnvtyReadCb");


			// Call SUT
			returnValue = rbl_SigChain_AlgnAccSnvtyReadCb(globalAcc_matrix);


			// Test case checks
			CHECK_U_CHAR(returnValue, expected_returnValue);
			check_global_data();

			END_CALLS();

		END_TEST();
	}
}

void ut_rbl_SigChain_AlgnAccSnvtyResultCb(int doIt)
{
	if (doIt)
	{
		START_TEST("47523: [MMP2.11]UTC_rbl_SigChain_AlgnAccSnvtyResultCb",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47523");

		initialise_global_data();
		initialise_expected_global_data();

		uint8 ServiceId = 0;
		NvM_RequestResultType JobResult = 0;
		Std_ReturnType returnValue = 0, expected_returnValue = 0;

		// Initial conditions/ Expected results

		ServiceId = 7;			//Random value
		JobResult = 1;			//Random value

		rbl_SigChain_AlgnAccSnvtyNvmVld = FALSE;
		expected_rbl_SigChain_AlgnAccSnvtyNvmVld = TRUE;

		returnValue = E_NOT_OK;
		expected_returnValue = E_OK;


		// Expected Call Sequence
		EXPECTED_CALLS("rbl_SigChain_NvmValidCheck#AlgnAccSnvtyResultCb");


		// Call SUT
		returnValue = rbl_SigChain_AlgnAccSnvtyResultCb(ServiceId, JobResult);


		// Test case checks
		CHECK_U_CHAR(returnValue, expected_returnValue);
		CHECK_BOOLEAN(rbl_SigChain_AlgnAccSnvtyNvmVld, expected_rbl_SigChain_AlgnAccSnvtyNvmVld);
		check_global_data();

		END_CALLS();

		END_TEST();
	}
}

void ut_rbl_SigChain_AlgnRateSnvtyReadCb(int doIt)
{
	if (doIt)
	{
		Std_ReturnType returnValue = 0, expected_returnValue = 0;
		int i = 0, j = 0, k = 0, l = 0;

		START_TEST("47524: [MMP2.11]UTC_rbl_SigChain_AlgnRateSnvtyReadCb",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47524");

		// Initial conditions/ Expected results

		initialise_global_data();
		initialise_expected_global_data();

		returnValue = E_NOT_OK;
		expected_returnValue = E_OK;

	    for (i = 0; i < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; i++)
	    {
	        for (j = 0; j < RBL_IMUSTDTYPES_AXIS_NO; j++)
	        {
	            for (k = 0; k < RBL_IMUSTDTYPES_AXIS_NO; k++)
	            {
	                for (l = 0; l < RBL_SIGCHAIN_ALGN_PNTS; l++)
	                {
	                	globalRate_matrix[i][j][k][l] = i + j + k + l + 2;		// I + J + K + L + two || "Random" value
						expected_globalRate_matrix[i][j][k][l] = globalRate_matrix[i][j][k][l];

	                    rbl_SigChain_AlgnRateOrthMtrx[i].AlgnOrthMtrx[j][k][l] = 0;
	                    expected_rbl_SigChain_AlgnRateOrthMtrx[i].AlgnOrthMtrx[j][k][l] = globalRate_matrix[i][j][k][l];
	                }
	            }
	        }
	    }


		// Expected Call Sequence
		EXPECTED_CALLS("rba_BswSrv_MemCopy8#AlgnRateSnvtyReadCb");


		// Call SUT
		returnValue = rbl_SigChain_AlgnRateSnvtyReadCb(globalRate_matrix);

		// Test case checks
		CHECK_U_CHAR(returnValue, expected_returnValue);
		check_global_data();

		END_CALLS();

		END_TEST();
	}
}

void ut_rbl_SigChain_AlgnRateSnvtyResultCb(int doIt)
{
	if (doIt)
	{
		uint8 ServiceId = 0;
		NvM_RequestResultType JobResult = 0;
		Std_ReturnType returnValue = 0, expected_returnValue = 0;

		START_TEST("47525: [MMP2.11]UTC_rbl_SigChain_AlgnRateSnvtyResultCb",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47525");

		initialise_global_data();
		initialise_expected_global_data();

		// Initial conditions/ Expected results
		ServiceId = 7;		//Random value
		JobResult = 5;		//Random value

		rbl_SigChain_Algn_RateSnvtyNvmVld = FALSE;
		expected_rbl_SigChain_Algn_RateSnvtyNvmVld = TRUE;

		returnValue = E_NOT_OK;
		expected_returnValue = E_OK;


		// Expected Call Sequence
		EXPECTED_CALLS("rbl_SigChain_NvmValidCheck#AlgnRateSnvtyResultCb");


		// Call SUT
		returnValue = rbl_SigChain_AlgnRateSnvtyResultCb(ServiceId, JobResult);


		// Test case checks
		CHECK_U_CHAR(returnValue, expected_returnValue);
		CHECK_BOOLEAN(rbl_SigChain_Algn_RateSnvtyNvmVld, expected_rbl_SigChain_Algn_RateSnvtyNvmVld);
		check_global_data();

		END_CALLS();

		END_TEST();
	}
}

//void ut_rbl_SigChain_PickFilResultCb(int doIt)
//{
//	if (doIt)
//	{
//		uint8 ServiceId = 0;
//		NvM_RequestResultType JobResult = 0;
//		Std_ReturnType returnValue = 0, expected_returnValue = 0;
//
//		START_TEST("49149: [MMP2.1x] UTC_rbl_SigChain_Nvm_rbl_SigChain_PickFilResultCb",
//				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49149");
//
//		START_STEP("1_NTS", TRUE);	// Invalid service ID
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = !NVM_SERVICE_ID_READ_ALL;
//			JobResult = 0;		//Unused in this scenario
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = TRUE;
//			expected_rbl_SigChain_SigFilNvmVld = FALSE;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		START_STEP("2_NTS", TRUE);	// Invalid job result
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = NVM_SERVICE_ID_READ_ALL;
//			JobResult = !NVM_REQ_OK;
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = TRUE;
//			expected_rbl_SigChain_SigFilNvmVld = FALSE;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		START_STEP("3_NTS", TRUE);	// No filter is selected, by default
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = NVM_SERVICE_ID_READ_ALL;
//			JobResult = NVM_REQ_OK;
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = FALSE;
//			expected_rbl_SigChain_SigFilNvmVld = TRUE;
//
//				// Filter value selection
//			rbl_SigChain_PickFilValue[0] = 0xFF;		// Invalid option, won't select a filter by default
//			rbl_SigChain_PickFilValue[1] = 0xFF;		// Invalid option, won't select a filter by default
//		    COPY_TO_EXPECTED(rbl_SigChain_PickFilValue, expected_rbl_SigChain_PickFilValue);
//
//				// Filter value
//			rbl_SigChain_FilVal = rbl_SigChain_FilVal20Hz;
//			expected_rbl_SigChain_FilVal = rbl_SigChain_FilValNoFilter;
//
//				// Filter flush time
//			rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
//			expected_rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFILNONEFLUSH;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		START_STEP("4_NTS", TRUE);	// No filter selected, on purpose
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = NVM_SERVICE_ID_READ_ALL;
//			JobResult = NVM_REQ_OK;
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = FALSE;
//			expected_rbl_SigChain_SigFilNvmVld = TRUE;
//
//				// Filter value selection
//			rbl_SigChain_PickFilValue[0] = RBL_SIGCHAIN_NOFILTER;	// Select no filter
//		    COPY_TO_EXPECTED(rbl_SigChain_PickFilValue, expected_rbl_SigChain_PickFilValue);
//
//				// Filter value
//			rbl_SigChain_FilVal = rbl_SigChain_FilVal20Hz;
//			expected_rbl_SigChain_FilVal = rbl_SigChain_FilValNoFilter;
//
//				// Filter flush time
//			rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL20HZFLUSH;
//			expected_rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFILNONEFLUSH;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		START_STEP("5_NTS", TRUE);	// Select 20Hz filter
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = NVM_SERVICE_ID_READ_ALL;
//			JobResult = NVM_REQ_OK;
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = FALSE;
//			expected_rbl_SigChain_SigFilNvmVld = TRUE;
//
//				// Filter value selection
//			rbl_SigChain_PickFilValue[0] = RBL_SIGCHAIN_20HZFILTER;	// Select 20Hz filter
//		    COPY_TO_EXPECTED(rbl_SigChain_PickFilValue, expected_rbl_SigChain_PickFilValue);
//
//				// Filter value
//			rbl_SigChain_FilVal = rbl_SigChain_FilValNoFilter;
//			expected_rbl_SigChain_FilVal = rbl_SigChain_FilVal20Hz;
//
//				// Filter flush time
//			rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFILNONEFLUSH;
//			expected_rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL20HZFLUSH;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		START_STEP("6_NTS", TRUE);	// Select 45Hz filter
//		{
//			initialise_global_data();
//			initialise_expected_global_data();
//
//			// Initial conditions/ Expected results
//
//				// SUT parameters
//			ServiceId = NVM_SERVICE_ID_READ_ALL;
//			JobResult = NVM_REQ_OK;
//
//				// Return value
//			returnValue = E_NOT_OK;
//			expected_returnValue = E_OK;
//
//				// Nvm read valid
//			rbl_SigChain_SigFilNvmVld = FALSE;
//			expected_rbl_SigChain_SigFilNvmVld = TRUE;
//
//				// Filter value selection
//			rbl_SigChain_PickFilValue[0] = RBL_SIGCHAIN_45HZFILTER;	// Select 20Hz filter
//		    COPY_TO_EXPECTED(rbl_SigChain_PickFilValue, expected_rbl_SigChain_PickFilValue);
//
//				// Filter value
//			rbl_SigChain_FilVal = rbl_SigChain_FilValNoFilter;
//			expected_rbl_SigChain_FilVal = rbl_SigChain_FilVal45Hz;
//
//				// Filter flush time
//			rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFILNONEFLUSH;
//			expected_rbl_SigChain_SigFilFlush = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
//
//
//			// EXPECTED CALLS
//			EXPECTED_CALLS("");
//
//
//			// CALL SUT
//			returnValue = rbl_SigChain_PickFilResultCb(ServiceId, JobResult);
//
//
//			// SUT CHECKS
//			CHECK_U_CHAR(returnValue, expected_returnValue);
//			check_global_data();
//
//			END_CALLS();
//		}
//		END_STEP();
//
//		END_TEST();
//	}
//}

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

/* Stub for function rba_BswSrv_MemCopy8 */
void rba_BswSrv_MemCopy8(uint8 * xDest_pu8,
                         const uint8 * xSrc_pcu8,
                         uint32 numBytes_u32)
{
    REGISTER_CALL("rba_BswSrv_MemCopy8");

    IF_INSTANCE("default")
    {
        return;
    }

    IF_INSTANCE("AlgnAccSnvtyReadCb")
	{
		// xDest_pu8 is a local variable's address, cannot be checked
		CHECK_U_INT((uint8) xSrc_pcu8, (uint8) &globalAcc_matrix);
		CHECK_U_INT(numBytes_u32, sizeof(globalAcc_matrix));

	    int i = 0;

	    for(i = 0; i < numBytes_u32; i++)
	    {
	        *xDest_pu8 = *xSrc_pcu8;
	        xDest_pu8++;
	        xSrc_pcu8++;
	    }

		return;
	}

    IF_INSTANCE("AlgnRateSnvtyReadCb")
	{
		// xDest_pu8 is a local variable's address, cannot be checked
		CHECK_U_INT((uint8) xSrc_pcu8, (uint8) &globalRate_matrix);
		CHECK_U_INT(numBytes_u32, sizeof(globalRate_matrix));

	    int i = 0;

	    for(i = 0; i < numBytes_u32; i++)
	    {
	        *xDest_pu8 = *xSrc_pcu8;
	        xDest_pu8++;
	        xSrc_pcu8++;
	    }

		return;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChain_NvmValidCheck */
int BEFORE_rbl_SigChain_NvmValidCheck(uint8 ServiceId,
                                      NvM_RequestResultType JobResult)
{
    REGISTER_CALL("rbl_SigChain_NvmValidCheck");

    IF_INSTANCE("default")
    {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("AlgnAccSnvtyResultCb")
	{
    	CHECK_U_INT(ServiceId, 7);
    	CHECK_U_INT(JobResult, 1);
		return REPLACE_WRAPPER;
	}

    IF_INSTANCE("AlgnRateSnvtyResultCb")
	{
    	CHECK_U_INT(ServiceId, 7);
    	CHECK_U_INT(JobResult, 5);
		return REPLACE_WRAPPER;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return REPLACE_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_NvmValidCheck */
boolean AFTER_rbl_SigChain_NvmValidCheck(boolean cppsm_return_value,
                                         uint8 ServiceId,
                                         NvM_RequestResultType JobResult)
{
    IF_INSTANCE("default")
    {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_NvmValidCheck */
boolean REPLACE_rbl_SigChain_NvmValidCheck(uint8 ServiceId,
                                           NvM_RequestResultType JobResult)
{
	IF_INSTANCE("default")
	{
		return FALSE;
	}

	IF_INSTANCE("AlgnAccSnvtyResultCb")
	{
		return TRUE;
	}

	IF_INSTANCE("AlgnRateSnvtyResultCb")
	{
		return TRUE;
	}

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
