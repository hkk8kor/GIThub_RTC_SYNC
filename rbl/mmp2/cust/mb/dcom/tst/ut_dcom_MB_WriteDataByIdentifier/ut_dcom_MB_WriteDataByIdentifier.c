/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_WriteDataByIdentifier.c
 *    Author: GDEV1KOR
 *    Generated on: 11-Apr-2024 11:55:12
 *    Generated from: dcom_MB_WriteDataByIdentifier.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"
#include "dcom_MB_Pub.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id, const uint8 * Data, Dcm_NegativeResponseCodeType * ErrorCode);

/* Global data */
extern uint8 rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1];
uint8 DCOM_SupplierPubKey_Sig_RAM_Mirror[258];
uint8 Data_NvM[20];

/* Expected variables for global data */
uint8 expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1];
uint8 expected_DCOM_SupplierPubKey_Sig_RAM_Mirror[258];

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_dcom_MirrorActvtDbgFrmsAppl_u8);
    INITIALISE(DCOM_SupplierPubKey_Sig_RAM_Mirror);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_dcom_MirrorActvtDbgFrmsAppl_u8, expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8);
    COPY_TO_EXPECTED(DCOM_SupplierPubKey_Sig_RAM_Mirror, expected_DCOM_SupplierPubKey_Sig_RAM_Mirror);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("rbl_dcom_MirrorActvtDbgFrmsAppl_u8", rbl_dcom_MirrorActvtDbgFrmsAppl_u8, expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8, sizeof(expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8));
    CHECK_MEMORY("DCOM_SupplierPubKey_Sig_RAM_Mirror", DCOM_SupplierPubKey_Sig_RAM_Mirror, expected_DCOM_SupplierPubKey_Sig_RAM_Mirror, sizeof(expected_DCOM_SupplierPubKey_Sig_RAM_Mirror));
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_DiagnosticTraceMemory_102_WriteData(int);
void ut_dcom_ActivateSupplierSpecificMessages_012A_WriteData(int);
void ut_dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(int);
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
    OPEN_LOG("ut_dcom_MB_WriteDataByIdentifier.ctr", false, 100);
    START_SCRIPT("dcom_MB_WriteDataByIdentifier", true);

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
    ut_dcom_DiagnosticTraceMemory_102_WriteData(1);
    ut_dcom_ActivateSupplierSpecificMessages_012A_WriteData(1);
    ut_dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_WriteDataByIdentifier.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_DiagnosticTraceMemory_102_WriteData(int doIt){
if (doIt) {

    START_TEST("46140: [MMP2.11]UTC_dcom_DiagnosticTraceMemory_102_WriteData",
	           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46140");

               /* Test steps */
			START_STEP("1_NTS", true);

			   /*Test step data */

			   uint8 ErrorCode = 0x00;
			   Std_ReturnType returnValue = E_NOT_OK;

               /* Expected Call Sequence  */
               EXPECTED_CALLS("dcom_Lib_WriteNvMData#dcom_Lib_WriteNvMData_0102");

               /* Call SUT */
               returnValue = dcom_DiagnosticTraceMemory_102_WriteData(Data_NvM,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_OK);
               CHECK_U_CHAR(ErrorCode, 0x00);
               CHECK_U_CHAR(Data_NvM, 0xA0);

			   END_CALLS();

               END_STEP();

            START_STEP("2_NTS", true);
			   /* Test step data */
			   uint8 * Data = NULL_PTR;
			   uint8 ErrorCode = 0x00;
			   Std_ReturnType returnValue = E_OK;

               /* Expected Call Sequence  */
			   EXPECTED_CALLS("");

               /* Call SUT */
               returnValue = dcom_DiagnosticTraceMemory_102_WriteData(Data,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_NOT_OK);
               CHECK_U_CHAR(ErrorCode, 0x00);
               CHECK_U_CHAR(Data, NULL_PTR);

			   END_CALLS();
           END_STEP();

   END_TEST();

}}
void ut_dcom_ActivateSupplierSpecificMessages_012A_WriteData(int doIt){
if (doIt) {

    START_TEST("48954: [MMP2.11]UTC_dcom_ActivateSupplierSpecificMessages_012A_WriteData",
	           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48954");

               /* Test steps */
			START_STEP("1_NTS", true);

			   /*Test step data */
			   uint8 * Data = 0x01;
			   Data_NvM[0]= 0x01;
               rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] = 0x01;
			   uint8 ErrorCode = 0x00;
			   Std_ReturnType returnValue = E_NOT_OK;
               expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] = 0x01;

               /* Expected Call Sequence  */
               EXPECTED_CALLS("dcom_Lib_WriteNvMData#dcom_Lib_WriteNvMData_012A");

               /* Call SUT */
               returnValue = dcom_ActivateSupplierSpecificMessages_012A_WriteData(Data_NvM,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_OK);
               CHECK_U_CHAR(ErrorCode, 0x00);
               CHECK_U_CHAR(Data_NvM, 0xA0);
               CHECK_U_CHAR(rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0], expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0]);
			   END_CALLS();

               END_STEP();

               /* Test steps */
			START_STEP("2_NTS", true);

			   /*Test step data */
			   uint8 * Data = 0x01;
			   Data_NvM[0] = 0x10;
			   uint8 ErrorCode = DCM_E_REQUESTOUTOFRANGE;
			   Std_ReturnType returnValue = E_NOT_OK;

               /* Expected Call Sequence  */
               EXPECTED_CALLS("");

               /* Call SUT */
               returnValue = dcom_ActivateSupplierSpecificMessages_012A_WriteData(Data_NvM,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_NOT_OK);
               CHECK_U_CHAR(ErrorCode, DCM_E_REQUESTOUTOFRANGE);
               CHECK_U_CHAR(Data_NvM, 0xA0);

			   END_CALLS();

               END_STEP();

            START_STEP("3_NTS", true);
			   /* Test step data */
			   uint8 * Data = NULL_PTR;
			   uint8 ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
			   Std_ReturnType returnValue = E_OK;

               /* Expected Call Sequence  */
			   EXPECTED_CALLS("");

               /* Call SUT */
               returnValue = dcom_ActivateSupplierSpecificMessages_012A_WriteData(Data,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_NOT_OK);
               CHECK_U_CHAR(ErrorCode, DCM_E_CONDITIONSNOTCORRECT);
               CHECK_U_CHAR(Data, NULL_PTR);
			   END_CALLS();
           END_STEP();

   END_TEST();

}}

void ut_dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(int doIt){
if (doIt) {

    START_TEST("49868: [MMP2.11]UTC_dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData",
	           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49868");

               /* Test steps */
			START_STEP("1_NTS", true);

			   /*Test step data */
			   uint8 ErrorCode = 0x00;
			   Std_ReturnType returnValue = E_NOT_OK;
			   uint16 DataLength = 0x00;

               /* Expected Call Sequence  */
               EXPECTED_CALLS("memcpy#default;"
            		          "dcom_Lib_WriteNvMData#dcom_Lib_WriteNvMData_01A2");

               /* Call SUT */
               returnValue = dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(Data_NvM,DataLength,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_OK);
               CHECK_U_CHAR(Data_NvM, 0xA0);
               CHECK_U_CHAR(DataLength, 0x00);
               CHECK_U_CHAR(ErrorCode, 0x00);
			   END_CALLS();

               END_STEP();

            START_STEP("2_NTS", true);
			   /* Test step data */
			   uint8 * Data = NULL_PTR;
			   uint8 ErrorCode = 0x00;
			   uint16 DataLength;
			   Std_ReturnType returnValue = E_OK;

               /* Expected Call Sequence  */
			   EXPECTED_CALLS("");

               /* Call SUT */
               returnValue = dcom_Trust_Model_CSR_Supplier_Signature_01A2_WriteData(Data,&DataLength,&ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_NOT_OK);
               CHECK_U_CHAR(Data, NULL_PTR);
               CHECK_U_CHAR(DataLength, 0x00);
               CHECK_U_CHAR(ErrorCode, 0x00);
			   END_CALLS();
           END_STEP();

   END_TEST();

}}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function dcom_Lib_WriteNvMData */
Std_ReturnType dcom_Lib_WriteNvMData(NvM_BlockIdType Block_Id,
                                     const uint8 * Data,
                                     Dcm_NegativeResponseCodeType * ErrorCode){
    REGISTER_CALL("dcom_Lib_WriteNvMData");

        IF_INSTANCE("dcom_Lib_WriteNvMData_0102") {
        		CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_DiagTraceMem);
        		CHECK_U_CHAR(* ErrorCode , 0x00);
        		CHECK_ADDRESS(Data,&Data_NvM);
                return E_OK;
            }
        IF_INSTANCE("dcom_Lib_WriteNvMData_012A") {
        		CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_ActivateSupplierMsgs);
        		CHECK_U_CHAR(* ErrorCode , 0x00);
        		CHECK_ADDRESS(Data,&Data_NvM);
                return E_OK;
            }
        IF_INSTANCE("dcom_Lib_WriteNvMData_01A2") {
        		CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_SupplierPublicKey_Signature);
        		CHECK_U_CHAR(* ErrorCode , 0x00);
        		CHECK_ADDRESS(Data,&Data_NvM);
                return E_OK;
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
        return REPLACE_WRAPPER;
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
    IF_INSTANCE("default") {
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
