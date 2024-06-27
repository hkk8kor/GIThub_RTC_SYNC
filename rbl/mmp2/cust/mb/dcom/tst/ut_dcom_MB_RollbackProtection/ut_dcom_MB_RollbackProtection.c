/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_RollbackProtection.c
 *    Author: GDEV1KOR
 *    Generated on: 27-Mar-2024 18:13:11
 *    Generated from: dcom_MB_RollbackProtection.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_RollbackProtection.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id, uint8 * Data, uint8 NvM_Length, uint8 Fill_NvM);
Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id, const uint8 * Data, Dcm_NegativeResponseCodeType * ErrorCode);

/* Global data */
typedef struct dcom_MB_RollbackProtection_av_struct { uint8(* ref_rbl_dcom_MinSwVer)[3]; rbl_dcom_DPVcheck_state * ref_dcom_MinSwVer_State; } dcom_MB_RollbackProtection_av_struct;
extern dcom_MB_RollbackProtection_av_struct av_dcom_MB_RollbackProtection;

/* Expected variables for global data */
typedef struct expected_dcom_MB_RollbackProtection_av_struct { uint8 ref_rbl_dcom_MinSwVer[3]; rbl_dcom_DPVcheck_state ref_dcom_MinSwVer_State; } expected_dcom_MB_RollbackProtection_av_struct;
expected_dcom_MB_RollbackProtection_av_struct expected_av_dcom_MB_RollbackProtection;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State));
    INITIALISE(ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State), ACCESS_EXPECTED_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer), ACCESS_EXPECTED_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State), ACCESS_EXPECTED_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State));
    CHECK_MEMORY("ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)", ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer), ACCESS_EXPECTED_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer), sizeof(ACCESS_EXPECTED_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_dcom_DowngradeProtection_Check(int);
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
    OPEN_LOG("ut_dcom_MB_RollbackProtection.ctr", false, 100);
    START_SCRIPT("dcom_MB_RollbackProtection", true);

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
	ut_rbl_dcom_DowngradeProtection_Check(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_RollbackProtection.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_dcom_DowngradeProtection_Check(int doIt)
{
	if (doIt)
	{
		//Initial conditions
		static uint8 rbl_dcom_MinSwVer[3];
		rbl_dcom_DPVcheck_state dcom_MinSwVer_State;
	    Std_ReturnType  statusNvm;

		START_TEST("48961: [MMP2.11]UTC_rbl_dcom_DowngradeProtection_Check",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48961");

		START_STEP("1_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL + 1;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

		   END_CALLS();
		}
		END_STEP();
		START_STEP("2_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL ;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();


		START_STEP("3_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL + 1;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();

		START_STEP("4_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();


		START_STEP("5_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL + 1;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);


			END_CALLS();
		}
		END_STEP();


		START_STEP("6_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK + 1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();


		START_STEP("7_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL;

 		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();


		START_STEP("8_NTS", TRUE);
		{
		   statusNvm = E_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_1");

		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR +1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK+1;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, rbl_dcom_MinSwVer)[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL+1;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
		END_STEP();

		START_STEP("9_NTS", TRUE);
		{
		   statusNvm = E_NOT_OK;
		   ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = READ_STATE;

		   //Expected Call Sequence
		   EXPECTED_CALLS("dcom_Lib_ReadNvMData#dcom_Lib_ReadNvMData_2");

		   rbl_dcom_MinSwVer[0] = DCOM_DPV_SOFTWARE_VERSION_YEAR;
		   rbl_dcom_MinSwVer[1] = DCOM_DPV_SOFTWARE_VERSION_WEEK;
		   rbl_dcom_MinSwVer[2] = DCOM_DPV_SOFTWARE_VERSION_PATCH_LEVEL;

		   //Call FUT
		   rbl_dcom_DowngradeProtection_Check();

		   CHECK_U_INT(statusNvm, E_NOT_OK);

			END_CALLS();
		}
		END_STEP();

		START_STEP("10_NTS", TRUE);
		{
			//Test case data declarations
			statusNvm = E_OK;
			ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = WRITE_STATE;


			//Expected Call Sequence
			EXPECTED_CALLS("dcom_Lib_WriteNvMData#dcom_Lib_WriteNvMData_1");

			//Call SUT
			rbl_dcom_DowngradeProtection_Check();

			CHECK_U_INT(statusNvm, E_OK);

			END_CALLS();
		}
        END_STEP();

		START_STEP("11_NTS", TRUE);
		{
			//Test case data declarations
			statusNvm = E_NOT_OK;
			ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = WRITE_STATE;


			//Expected Call Sequence
			EXPECTED_CALLS("dcom_Lib_WriteNvMData#dcom_Lib_WriteNvMData_2");

			//Call FUT
			rbl_dcom_DowngradeProtection_Check();

			CHECK_U_INT(statusNvm, E_NOT_OK);

			END_CALLS();
		}
        END_STEP();

		START_STEP("12_NTS", TRUE);
		{
			//Test case data declarations
			statusNvm = E_NOT_OK;
			ACCESS_VARIABLE(dcom_MB_RollbackProtection, dcom_MinSwVer_State) = 0;


			//Expected Call Sequence
			EXPECTED_CALLS("");

			//Call FUT
			rbl_dcom_DowngradeProtection_Check();

			CHECK_U_INT(statusNvm, E_NOT_OK);

			END_CALLS();
		}
        END_STEP();


		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function dcom_Lib_ReadNvMData */
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id,
                                    uint8 * Data,
                                    uint8 NvM_Length,
                                    uint8 Fill_NvM){
    REGISTER_CALL("dcom_Lib_ReadNvMData");

    IF_INSTANCE("dcom_Lib_ReadNvMData_1")
    {
		CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion);
		CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion );
		CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
        return E_OK;
    }

    IF_INSTANCE("dcom_Lib_ReadNvMData_2")
      {
  		CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion);
  		CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion );
  		CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
        return E_NOT_OK;
      }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function dcom_Lib_WriteNvMData */
Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id,
                                     const uint8 * Data,
                                     Dcm_NegativeResponseCodeType * ErrorCode){
    REGISTER_CALL("dcom_Lib_WriteNvMData");

    IF_INSTANCE("dcom_Lib_WriteNvMData_1")
    {
    	CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion);
    	* ErrorCode = 0;
        return E_OK;
    }

    IF_INSTANCE("dcom_Lib_WriteNvMData_2")
    {
      	CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion);
      	* ErrorCode = 0;
      	return E_NOT_OK;
     }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
