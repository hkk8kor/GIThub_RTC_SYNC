/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_AdjustISOParam_WRDBI.c
 *    Author: GDEV1KOR
 *    Generated on: 27-Mar-2024 16:44:38
 *    Generated from: dcom_MB_AdjustISOParam_WRDBI.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"
#include "dcom_MB_Pub.h"
#include "CanTp.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType CanTp_ReadParameter(PduIdType id, TPParameterType parameter, uint16 * value);
Std_ReturnType CanTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);


/* Global data */
uint16 dcom_Requested_Tester;

/* Expected variables for global data */
uint16 expected_dcom_Requested_Tester;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(dcom_Requested_Tester);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(dcom_Requested_Tester, expected_dcom_Requested_Tester);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_INT(dcom_Requested_Tester, expected_dcom_Requested_Tester);
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_CanTp_ReadParameter_010B_ReadData(int);
void ut_dcom_CanTp_ChangeParameter_010B_WriteData(int);
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
    OPEN_LOG("ut_dcom_MB_AdjustISOParam_WRDBI.ctr", false, 100);
    START_SCRIPT("dcom_MB_AdjustISOParam_WRDBI", true);

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
	ut_dcom_CanTp_ReadParameter_010B_ReadData(1);
	ut_dcom_CanTp_ChangeParameter_010B_WriteData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_AdjustISOParam_WRDBI.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_CanTp_ReadParameter_010B_ReadData(int doIt){
if (doIt) {

			START_TEST("48201: [MMP2.11]UTC_dcom_CanTp_ReadParameter_010B_ReadData",
			           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48201");

			uint8 Data_buffer[10]={0x01};
			uint8 * Data = Data_buffer;
			Std_ReturnType retVal;

			START_STEP("1_NTS", true);
			{
			//Initial declarations
			dcom_Requested_Tester = DCOM_FIRST_TESTER;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("CanTp_ReadParameter#CanTp_ReadParameter_BS;"
			               "CanTp_ReadParameter#CanTp_ReadParameter_STmin");

			/* Call SUT */
			retVal = dcom_CanTp_ReadParameter_010B_ReadData(Data);

			/* Test case checks */
			CHECK_U_CHAR(retVal,E_OK);
			CHECK_U_CHAR(Data,0x4A);

			END_CALLS();
			}
			END_STEP();

			START_STEP("2_NTS", true);
			{
			//Initial declarations
			dcom_Requested_Tester = DCOM_SECOND_TESTER;
			#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
			/* Expected Call Sequence  */
		    EXPECTED_CALLS("CanTp_ReadParameter#CanTp_ReadParameter_BS;"
			               "CanTp_ReadParameter#CanTp_ReadParameter_STmin");

			#endif
			/* Call SUT */
			retVal = dcom_CanTp_ReadParameter_010B_ReadData(Data);

			/* Test case checks */
			CHECK_U_CHAR(retVal,E_OK);
			CHECK_U_CHAR(Data,0x4A);

			END_CALLS();
			}
			END_STEP();

		    START_STEP("3_NTS", true);
		    {
		    //Initial declarations
			dcom_Requested_Tester = DCOM_SECOND_TESTER;
			#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
			/* Expected Call Sequence  */
		    EXPECTED_CALLS("CanTp_ReadParameter#CanTp_ReadParameter_BS;"
			               "CanTp_ReadParameter#CanTp_ReadParameter_STmin_False");

			#endif
			/* Call SUT */
		    retVal = dcom_CanTp_ReadParameter_010B_ReadData(Data);

		    /* Test case checks */
	        CHECK_U_CHAR(retVal,E_OK);
	        CHECK_U_CHAR(Data,0x4A);

			END_CALLS();
		    }
			END_STEP();

	        START_STEP("4_NTS", true);
	        {
	        //Initial declarations
			dcom_Requested_Tester = 0;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retVal = dcom_CanTp_ReadParameter_010B_ReadData(Data);

			/* Test case checks */
			CHECK_U_CHAR(retVal,E_NOT_OK);
			CHECK_U_CHAR(Data,0x4A);

			END_CALLS();
		    }
			END_STEP();

		    START_STEP("5_NTS", true);
		    {
		    //Initial declarations
			uint8 *Data = NULL_PTR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retVal = dcom_CanTp_ReadParameter_010B_ReadData(Data);

			/* Test case checks */
			CHECK_U_CHAR(retVal,E_OK);
			CHECK_U_CHAR(Data,0x00);

			END_CALLS();
		    }
			END_STEP();
	        END_TEST();
		}
}

void ut_dcom_CanTp_ChangeParameter_010B_WriteData(int doIt){
if (doIt) {

           START_TEST("48209: [MMP2.11]UTC_dcom_CanTp_ChangeParameter_010B_WriteData",
                      "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48209");

           uint8 Data_buffer[10]={0x01};
           uint8 * Data = Data_buffer;
           uint8 ErrorCode = 0x00;
           Std_ReturnType   retVal = E_NOT_OK;

           START_STEP("1_NTS", true);
           {
           //Initial declarations
		   dcom_Requested_Tester = DCOM_FIRST_TESTER;

           /* Expected Call Sequence  */
           EXPECTED_CALLS("CanTp_ChangeParameter#CanTp_ChangeParameter_BS;"
        		          "CanTp_ChangeParameter#CanTp_ChangeParameter_STmin");

            /* Call SUT */
            retVal = dcom_CanTp_ChangeParameter_010B_WriteData(Data,&ErrorCode);

            /* Test case checks */
            CHECK_U_CHAR(retVal,E_OK);
            CHECK_U_CHAR(Data,0x4A);
            CHECK_U_CHAR(ErrorCode,0x00);

            END_CALLS();
           }
		END_STEP();

		    START_STEP("2_NTS", true);
		    {
		    //Initial declarations
		    dcom_Requested_Tester = DCOM_SECOND_TESTER;
#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
            /* Expected Call Sequence  */
            EXPECTED_CALLS("CanTp_ChangeParameter#CanTp_ChangeParameter_BS;"
        		           "CanTp_ChangeParameter#CanTp_ChangeParameter_STmin");
#endif
            /* Call SUT */
            retVal = dcom_CanTp_ChangeParameter_010B_WriteData(Data,&ErrorCode);

             /* Test case checks */
             CHECK_U_CHAR(retVal,E_OK);
             CHECK_U_CHAR(Data,0x4A);
             CHECK_U_CHAR(ErrorCode,0x00);

             END_CALLS();
		    }
		END_STEP();

		    START_STEP("3_NTS", true);
		    {
		    //Initial declarations
		    dcom_Requested_Tester = DCOM_SECOND_TESTER;
#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
            /* Expected Call Sequence  */
            EXPECTED_CALLS("CanTp_ChangeParameter#CanTp_ChangeParameter_BS;"
        		           "CanTp_ChangeParameter#CanTp_ChangeParameter_STmin_False");
#endif
            /* Call SUT */
            retVal = dcom_CanTp_ChangeParameter_010B_WriteData(Data,&ErrorCode);

            /* Test case checks */
            CHECK_U_CHAR(retVal,E_OK);
            CHECK_U_CHAR(Data,0x4A);
            CHECK_U_CHAR(ErrorCode,0x00);

            END_CALLS();
		    }
		    END_STEP();

		START_STEP("4_NTS", true);
		{
		//Initial declarations
		dcom_Requested_Tester = 0;

		/* Expected Call Sequence  */
		EXPECTED_CALLS("");

		/* Call SUT */
        retVal = dcom_CanTp_ChangeParameter_010B_WriteData(Data,&ErrorCode);

        /* Test case checks */
		CHECK_U_CHAR(retVal,E_NOT_OK);
        CHECK_U_CHAR(Data,0x4A);
        CHECK_U_CHAR(ErrorCode,0x00);

        END_CALLS();
	    }
		END_STEP();


		START_STEP("5_NTS", true);
		{
		//Initial declarations
		uint8 *Data = NULL_PTR;

		/* Expected Call Sequence  */
		EXPECTED_CALLS("");

		/* Call SUT */
		retVal = dcom_CanTp_ChangeParameter_010B_WriteData(Data,&ErrorCode);

		/* Test case checks */
		CHECK_U_CHAR(retVal,E_OK);
        CHECK_U_CHAR(Data,0x00);
        CHECK_U_CHAR(ErrorCode,0x00);

        END_CALLS();
		}
		END_STEP();
		END_TEST();
		}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function CanTp_ReadParameter */
Std_ReturnType CanTp_ReadParameter(PduIdType id,
                                   TPParameterType parameter,
                                   uint16 * value){
    REGISTER_CALL("CanTp_ReadParameter");
    IF_INSTANCE("CanTp_ReadParameter_BS") {
               return E_OK;
           }
       IF_INSTANCE("CanTp_ReadParameter_STmin") {
               return E_OK;
           }
       IF_INSTANCE("CanTp_ReadParameter_STmin_False") {
               return E_NOT_OK;
           }

       IF_INSTANCE("default") {
           return CANTATA_DEFAULT_VALUE;
       }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}
/* Stub for function CanTp_ChangeParameter */
Std_ReturnType CanTp_ChangeParameter(PduIdType id,
                                     TPParameterType parameter,
                                     uint16 value){
    REGISTER_CALL("CanTp_ChangeParameter");
    IF_INSTANCE("CanTp_ChangeParameter_BS") {
               return E_OK;
           }
       IF_INSTANCE("CanTp_ChangeParameter_STmin") {
               return E_OK;
           }
       IF_INSTANCE("CanTp_ChangeParameter_STmin_False") {
       	return E_NOT_OK;
       }

       IF_INSTANCE("default") {
           return CANTATA_DEFAULT_VALUE;
       }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
