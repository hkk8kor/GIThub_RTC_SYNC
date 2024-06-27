/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_SSA_Functions.c
 *    Author: GDEV1KOR
 *    Generated on: 21-Feb-2024 12:38:06
 *    Generated from: dcom_MB_SSA_Functions.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Rte_rbl_CustIf.h"
#include "dcom_MB_Pub.h"
#include "RBSEC_Prj_Wrapper.h"
#include "dcom_Lib.h"
#define DID_F103_DATA_LENGTH 32U
#include "rbl_CustIf_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType RBSEC_SSA_KeyPairGenerate(uint32 PrivatekeyId, uint32 PublickeyId);
uint8 dcom_Lib_HexNibble2ASCII(uint8 t_Nibble_UB);

/* Global data */
uint8 rbl_dcom_DCOM_MB_HW_PartNumber[10];
uint8 rbl_ECU_SerialNr_RAM_Mirror[17];

/* Expected variables for global data */
uint8 expected_rbl_dcom_DCOM_MB_HW_PartNumber[10];
uint8 expected_rbl_ECU_SerialNr_RAM_Mirror[17];

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_dcom_DCOM_MB_HW_PartNumber);
    INITIALISE(rbl_ECU_SerialNr_RAM_Mirror);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_dcom_DCOM_MB_HW_PartNumber, expected_rbl_dcom_DCOM_MB_HW_PartNumber);
    COPY_TO_EXPECTED(rbl_ECU_SerialNr_RAM_Mirror, expected_rbl_ECU_SerialNr_RAM_Mirror);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("rbl_dcom_DCOM_MB_HW_PartNumber", rbl_dcom_DCOM_MB_HW_PartNumber, expected_rbl_dcom_DCOM_MB_HW_PartNumber, sizeof(expected_rbl_dcom_DCOM_MB_HW_PartNumber));
    CHECK_MEMORY("rbl_ECU_SerialNr_RAM_Mirror", rbl_ECU_SerialNr_RAM_Mirror, expected_rbl_ECU_SerialNr_RAM_Mirror, sizeof(expected_rbl_ECU_SerialNr_RAM_Mirror));
}

/* Prototypes for test functions */
void run_tests();
void ut_GenerateKeyPair(int);
void ut_dcom_MB_GetDiagnosticData(int);
void ut_dcom_MB_GetSupplierData(int);
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
    OPEN_LOG("ut_dcom_MB_SSA_Functions.ctr", false, 100);
    START_SCRIPT("dcom_MB_SSA_Functions", true);

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
	ut_GenerateKeyPair(1);
	ut_dcom_MB_GetDiagnosticData(1);
	ut_dcom_MB_GetSupplierData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_SSA_Functions.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_GenerateKeyPair(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = E_NOT_OK;
		START_TEST("49397: [MMP2.11]UTC_GenerateKeyPair",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49397");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			uint32 privateKeyId;
			uint32 publicKeyId;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSEC_SSA_KeyPairGenerate#RBSEC_SSA_KeyPairGenerate_1");

			/* Call SUT */
			retValue = GenerateKeyPair(&privateKeyId,&publicKeyId);

			/* Test step checks */
			CHECK_U_CHAR(retValue, E_NOT_OK);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_dcom_MB_GetDiagnosticData(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = E_NOT_OK;
		uint8 diagVersion;
		uint8 diagVariant;
		START_TEST("49821: [MMP2.11]UTC_dcom_MB_GetDiagnosticData",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49821");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			diagVersion = 0x01;
			diagVariant = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = dcom_MB_GetDiagnosticData(&diagVersion,&diagVariant);

			/* Test step checks */
			CHECK_U_CHAR(retValue, E_OK);
			CHECK_U_CHAR(diagVersion, DCOM_ACTIVE_DIAG_VERSION);
			CHECK_U_CHAR(diagVariant, DCOM_ACTIVE_DIAG_VARIANT);

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals*/
			diagVersion = NULL_PTR;
			diagVariant = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = dcom_MB_GetDiagnosticData(diagVersion,&diagVariant);

			/* Test step checks */
			CHECK_U_CHAR(retValue, E_NOT_OK);

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("3_NTS", true);
		{
			/*initialise_globals*/
			diagVersion = 0x01;
			diagVariant = NULL_PTR;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = dcom_MB_GetDiagnosticData(&diagVersion,diagVariant);

			/* Test step checks */
			CHECK_U_CHAR(retValue, E_NOT_OK);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_dcom_MB_GetSupplierData(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = E_NOT_OK;
		uint8 data[30] = {0x01};
		uint16 dataLength;
	    uint8 byte_01;
	    uint8 byte_02;
	    uint8 index_1,index_2 = 0;

		START_TEST("49822: [MMP2.11]UTC_dcom_MB_GetSupplierData",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49822");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			dataLength = 0x01;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("dcom_Lib_HexNibble2ASCII#dcom_Lib_HexNibble2ASCII_1;"
					       "dcom_Lib_HexNibble2ASCII#dcom_Lib_HexNibble2ASCII_2;"
					       "dcom_Lib_HexNibble2ASCII#dcom_Lib_HexNibble2ASCII_3;"
					       "dcom_Lib_HexNibble2ASCII#dcom_Lib_HexNibble2ASCII_4");

			/* Call SUT */
			retValue = dcom_MB_GetSupplierData(&data,&dataLength);

			/* Test step checks */
		    for(index_1=0;index_1<NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber;index_1++)
		    {
		    	CHECK_U_CHAR(data[index_1], rbl_dcom_DCOM_MB_HW_PartNumber[index_1]);
		    }

		    for(index_1=15;index_1<(15+NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr);index_1++)
		    {
		    	CHECK_U_CHAR(data[index_1], rbl_ECU_SerialNr_RAM_Mirror[index_2]);
		    }
			CHECK_U_CHAR(retValue, E_OK);
			CHECK_U_CHAR(dataLength, DID_F103_DATA_LENGTH);
			CHECK_U_CHAR(byte_01, DCOM_SUPPLIERID_HIGHBYTE);
			CHECK_U_CHAR(byte_02, DCOM_SUPPLIERID_HIGHBYTE);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSEC_SSA_KeyPairGenerate */
Std_ReturnType RBSEC_SSA_KeyPairGenerate(uint32 PrivatekeyId,
                                        uint32 PublickeyId){
    REGISTER_CALL("RBSEC_SSA_KeyPairGenerate");

    IF_INSTANCE("RBSEC_SSA_KeyPairGenerate_1") {
        return E_NOT_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function dcom_Lib_HexNibble2ASCII */
uint8 dcom_Lib_HexNibble2ASCII(uint8 t_Nibble_UB){
    REGISTER_CALL("dcom_Lib_HexNibble2ASCII");

    IF_INSTANCE("dcom_Lib_HexNibble2ASCII_1") {
    	CHECK_U_CHAR(t_Nibble_UB, DCOM_SUPPLIERID_HIGHBYTE);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("dcom_Lib_HexNibble2ASCII_2") {
    	CHECK_U_CHAR(t_Nibble_UB, DCOM_SUPPLIERID_HIGHBYTE);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("dcom_Lib_HexNibble2ASCII_3") {
    	CHECK_U_CHAR(t_Nibble_UB, DCOM_SUPPLIERID_HIGHBYTE);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("dcom_Lib_HexNibble2ASCII_4") {
    	CHECK_U_CHAR(t_Nibble_UB, DCOM_SUPPLIERID_LOWBYTE);
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
