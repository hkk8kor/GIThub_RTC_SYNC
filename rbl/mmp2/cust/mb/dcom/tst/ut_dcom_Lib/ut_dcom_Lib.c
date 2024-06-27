/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_Lib.c
 *    Author: GDEV1KOR
 *    Generated on: 27-Mar-2024 16:01:26
 *    Generated from: dcom_Lib.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_dcom_Lib_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_dcom_Lib_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType * RequestResultPtr);
Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, NvM_Rb_VoidPtr NvM_DstPtr);
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId, NvM_Rb_ConstVoidPtr NvM_SrcPtr);

/* Global data */
volatile RBMESG_Type_VehSpd_Disp_ST3 RBMESG_VehSpd_Disp_ST3;
typedef struct dcom_Lib_av_struct { dcom_NvMReadWriteType_tst * ref_dcom_EepromReadByPdmState; dcom_NvMReadWriteType_tst * ref_dcom_EepromWriteByPdmState; } dcom_Lib_av_struct;
extern dcom_Lib_av_struct av_dcom_Lib;

/* Expected variables for global data */
RBMESG_Type_VehSpd_Disp_ST3 expected_RBMESG_VehSpd_Disp_ST3;
typedef struct expected_dcom_Lib_av_struct { dcom_NvMReadWriteType_tst ref_dcom_EepromReadByPdmState; dcom_NvMReadWriteType_tst ref_dcom_EepromWriteByPdmState; } expected_dcom_Lib_av_struct;
expected_dcom_Lib_av_struct expected_av_dcom_Lib;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState));
    INITIALISE(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState));
    INITIALISE(RBMESG_VehSpd_Disp_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), ACCESS_EXPECTED_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), ACCESS_EXPECTED_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState));
    COPY_TO_EXPECTED(RBMESG_VehSpd_Disp_ST3, expected_RBMESG_VehSpd_Disp_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), ACCESS_EXPECTED_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState));
    CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), ACCESS_EXPECTED_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState));
    CHECK_U_INT(RBMESG_VehSpd_Disp_ST3, expected_RBMESG_VehSpd_Disp_ST3);
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_Lib_ReadNvMData(int);
void ut_dcom_Lib_WriteNvMData(int);
void ut_dcom_isSpeedLimitExceeded(int);
void ut_dcom_Lib_HexNibble2ASCII(int);
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
    OPEN_LOG("ut_dcom_Lib.ctr", false, 100);
    START_SCRIPT("dcom_Lib", true);

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
	ut_dcom_Lib_ReadNvMData(1);
	ut_dcom_Lib_WriteNvMData(1);
    ut_dcom_isSpeedLimitExceeded(1);
    ut_dcom_Lib_HexNibble2ASCII(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_Lib.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_Lib_ReadNvMData(int doIt){
if (doIt) {

		//Test case data declarations
        Std_ReturnType retVal;

        START_TEST("46386: [MMP2.11]UTC_dcom_Lib_ReadNvMData",
                   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46386");
        //Initial declarations
		NvM_BlockIdType Block_Id;
		uint8 Data[3];
		uint8 NvM_Length;
		uint8 Fill_NvM;

		START_STEP("1_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;"
						"NvM_ReadBlock#OK");

            /* Call SUT */
             retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_AfterReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("2_NTS", TRUE);

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;"
						"NvM_ReadBlock#NOK;"
						"NvM_GetErrorStatus#OK;"
						"NvM_ReadBlock#NOK;"
						"NvM_GetErrorStatus#OK;"
						"NvM_ReadBlock#NOK;");

            /* Call SUT */
            for(int i= 0; i < 3; i++)
			{
				ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
				retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);
			}

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_Error_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("3_NTS", TRUE);


        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;");

            /* Call SUT */
            for(int i= 0; i < 5; i++)
			{
				ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
				retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);
			}

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_Error_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("4_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_Done_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("5_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#PENDING;");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_AfterReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("6_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

		Fill_NvM = 0x5F;
		NvM_Length = 3;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#INTEGRITY_FAILED;");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, E_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);
			for(uint8 l_LoopIndex_u8 = (uint8)0; l_LoopIndex_u8 < NvM_Length; l_LoopIndex_u8++)
            {
                CHECK_U_INT(Data[l_LoopIndex_u8], Fill_NvM);
			}

        END_CALLS();

		END_STEP();

		START_STEP("7_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

		Fill_NvM = 0x5F;
		NvM_Length = 3;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#NV_INVALIDATED;");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, E_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);
			for(uint8 l_LoopIndex_u8 = (uint8)0; l_LoopIndex_u8 < NvM_Length; l_LoopIndex_u8++)
            {
                CHECK_U_INT(Data[l_LoopIndex_u8], Fill_NvM);
			}

        END_CALLS();

		END_STEP();

		START_STEP("8_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#other;");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_Error_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("9_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_Done_ReadOrWriteNVMBlock;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, E_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("10_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = dcom_Error_ReadOrWriteNVMBlock;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, E_NOT_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("11_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState) = 0xFF;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_ReadNvMData(Block_Id, Data, NvM_Length, Fill_NvM);

			CHECK_U_INT(retVal, E_NOT_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromReadByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();
    END_TEST();
}}

void ut_dcom_Lib_WriteNvMData(int doIt){
if (doIt) {

		//Test case data declarations
        Std_ReturnType retVal;
        int i;

        START_TEST("46387: [MMP2.11]UTC_dcom_Lib_WriteNvMData",
             "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46387");

	    //Initial declarations
  		Dcm_NegativeResponseCodeType ErrorCode;
		NvM_BlockIdType Block_Id;
		uint8 Data[3];

       START_STEP("1_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;"
						"NvM_WriteBlock#OK");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_AfterReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("2_NTS", TRUE);

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;"
						"NvM_WriteBlock#NOK;"
						"NvM_GetErrorStatus#OK;"
						"NvM_WriteBlock#NOK;"
						"NvM_GetErrorStatus#OK;"
						"NvM_WriteBlock#NOK;");

            /* Call SUT */
            for(i= 0; i < 3; i++)
			{
				ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
				retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);
			}

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_Error_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("3_NTS", TRUE);


        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;"
						"NvM_GetErrorStatus#PENDING;");

            /* Call SUT */
            for(i= 0; i < 5; i++)
			{
				ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest;
				retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);
			}

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_Error_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("4_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#OK;");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_Done_ReadOrWriteNVMBlock);

        END_CALLS();

		END_STEP();

		START_STEP("5_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#PENDING;");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, DCM_E_PENDING);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_AfterReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("6_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_NvMGetErrorStatus_AfterReadOrWriteRequest;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("NvM_GetErrorStatus#other");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, E_NOT_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("7_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_Done_ReadOrWriteNVMBlock;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, E_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("8_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = dcom_Error_ReadOrWriteNVMBlock;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, E_NOT_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();

		START_STEP("9_NTS", TRUE);

		ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState) = 0xFF;

        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = dcom_Lib_WriteNvMData(Block_Id, Data, &ErrorCode);

			CHECK_U_INT(retVal, E_NOT_OK);
			CHECK_U_INT(ACCESS_VARIABLE(dcom_Lib, dcom_EepromWriteByPdmState), dcom_NvMGetErrorStatus_BeforeReadOrWriteRequest);

        END_CALLS();

		END_STEP();
    END_TEST();
}}

void ut_dcom_isSpeedLimitExceeded(int doIt){
	if (doIt) {

	START_TEST("46389: [MMP2.11]UTC_dcom_isSpeedLimitExceeded",
			    "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46389");

					/* Test steps */
			START_STEP("1_NTS", TRUE);

			initialise_global_data();

				/* Set expected values for global data checks */
			   initialise_expected_global_data();
				boolean returnValue = FALSE ;
				boolean Expected_returnValue = FALSE;
				uint16 l_Value  = 1;

			/*Test step data */
			RBMESG_VehSpd_Disp_ST3 =255;
			expected_RBMESG_VehSpd_Disp_ST3 =255;

				/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			returnValue = dcom_isSpeedLimitExceeded(l_Value);

			/* Test case checks */
			CHECK_BOOLEAN(returnValue, Expected_returnValue);
			CHECK_U_CHAR(l_Value, 1);

	        END_CALLS();
	        END_STEP();

				START_STEP("2_NTS", TRUE);

				/*Test step data */

				initialise_global_data();

				/* Set expected values for global data checks */
				initialise_expected_global_data();
				boolean returnValue = FALSE ;
				boolean Expected_returnValue = TRUE;
				uint16 l_Value  = 10;

				/*Test step data */
				RBMESG_VehSpd_Disp_ST3 =100;
				expected_RBMESG_VehSpd_Disp_ST3 =100;

	        /* Expected Call Sequence  */
	        EXPECTED_CALLS("");
	            /* Call SUT */
	            returnValue = dcom_isSpeedLimitExceeded(l_Value);

	            /* Test case checks */
	            CHECK_BOOLEAN(returnValue, Expected_returnValue);/*Work around for current implementation*/
	            CHECK_U_CHAR(l_Value, 10);

	            END_CALLS();
	            END_STEP();

				START_STEP("3_NTS", TRUE);

				/*Test step data */
				initialise_global_data();

			    /* Set expected values for global data checks */
				initialise_expected_global_data();
				boolean returnValue = FALSE ;
				boolean Expected_returnValue = TRUE;
				uint16 l_Value  = 10;

				/*Test step data */
				RBMESG_VehSpd_Disp_ST3 = 10;
				expected_RBMESG_VehSpd_Disp_ST3 =10;

				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_isSpeedLimitExceeded(l_Value);

				/* Test case checks */
				CHECK_BOOLEAN(returnValue, Expected_returnValue);
				CHECK_U_CHAR(l_Value,10);

				/* Checks on global data */
				check_global_data();
	        END_CALLS();

	 END_STEP();
 END_TEST();

}}

void ut_dcom_Lib_HexNibble2ASCII(int doIt){
if (doIt) {

	START_TEST("46388: [MMP2.11]UTC_dcom_Lib_HexNibble2ASCII",
			    "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46388");

			/* Test steps */
			START_STEP("1_NTS", TRUE);

			/*Test step data */
			uint8 t_Nibble_UB = 0x7F;
            uint8 returnValue =0x00 ,Expected_ReturnValue =0x46;

            /* Set global data */
            initialise_global_data();

           /* Set expected values for global data checks */
           initialise_expected_global_data();

		  /* Expected Call Sequence  */
          EXPECTED_CALLS("");

          /* Call SUT */
          returnValue = dcom_Lib_HexNibble2ASCII(t_Nibble_UB);

          /* Test case checks */
          CHECK_U_CHAR(returnValue, Expected_ReturnValue);
          CHECK_U_CHAR(t_Nibble_UB ,0x7F);

          /* Checks on global data */
          check_global_data();

        END_CALLS();
    END_STEP();

	     	START_STEP("2_NTS", TRUE);

		    /*Test step data */
		 	uint8 t_Nibble_UB = 0x00;
            uint8 returnValue =0x00 ,Expected_ReturnValue =0x30;

            /* Set global data */
            initialise_global_data();

            /* Set expected values for global data checks */
            initialise_expected_global_data();

	        /* Expected Call Sequence  */
            EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = dcom_Lib_HexNibble2ASCII(t_Nibble_UB);

            /* Test case checks */
            CHECK_U_CHAR(returnValue, Expected_ReturnValue);
            CHECK_U_CHAR(t_Nibble_UB , 0x00);

            /* Checks on global data */
            check_global_data();\

        END_CALLS();
    END_STEP();

			START_STEP("3_NTS", TRUE);

            /*Test step data */

			uint8 t_Nibble_UB = 0xFF;
            uint8 returnValue =0x00 ,Expected_ReturnValue =0x46;

            /* Set global data */
            initialise_global_data();

            /* Set expected values for global data checks */
            initialise_expected_global_data();

	        /* Expected Call Sequence  */
            EXPECTED_CALLS("");

           /* Call SUT */
           returnValue = dcom_Lib_HexNibble2ASCII(t_Nibble_UB);

           /* Test case checks */
           CHECK_U_CHAR(returnValue, Expected_ReturnValue);
           CHECK_U_CHAR(t_Nibble_UB , 0xff);

            /* Checks on global data */
            check_global_data();

        END_CALLS();
       END_STEP();
    END_TEST();
}}
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

/* Stub for function NvM_GetErrorStatus */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId,
                                  NvM_RequestResultType * RequestResultPtr){
    REGISTER_CALL("NvM_GetErrorStatus");

    IF_INSTANCE("OK"){
    	*RequestResultPtr = NVM_REQ_OK;
        return E_OK;
    }
    IF_INSTANCE("PENDING"){
    	*RequestResultPtr = NVM_REQ_PENDING;
        return E_OK;
    }
    IF_INSTANCE("INTEGRITY_FAILED"){
    	*RequestResultPtr = NVM_REQ_INTEGRITY_FAILED;
        return E_OK;
    }
    IF_INSTANCE("NV_INVALIDATED"){
    	*RequestResultPtr = NVM_REQ_NV_INVALIDATED;
        return E_OK;
    }
    IF_INSTANCE("other"){
    	*RequestResultPtr = 0xFF;
        return E_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function NvM_ReadBlock */
Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId,
                             NvM_Rb_VoidPtr NvM_DstPtr){
    REGISTER_CALL("NvM_ReadBlock");

    IF_INSTANCE("OK"){
        return E_OK;
    }
    IF_INSTANCE("NOK"){
        return E_NOT_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function NvM_WriteBlock */
Std_ReturnType NvM_WriteBlock(NvM_BlockIdType BlockId,
                              NvM_Rb_ConstVoidPtr NvM_SrcPtr){
    REGISTER_CALL("NvM_WriteBlock");

    IF_INSTANCE("OK"){
        return E_OK;
    }
    IF_INSTANCE("NOK"){
        return E_NOT_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
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
