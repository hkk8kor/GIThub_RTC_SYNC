/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_ReadDataByIdentifier.c
 *    Author: GDEV1KOR
 *    Generated on: 11-Apr-2024 12:44:22
 *    Generated from: dcom_MB_ReadDataByIdentifier.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"
#include "dcom_MB_Pub.h"
#include "dcom_SWVersion.h"
#include "RBLCF_Hexblocks_Iterator.h"
#include "RBCM_CSWPrSettings_MMP2.h"
#include "Rte_rbl_SwcDiagAdapter_Srv.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType * SesCtrlType);
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id, uint8 * Data, uint8 NvM_Length, uint8 Fill_NvM);
void RBLCF_GetFirstHexBlock(RBLCF_HexBlockLayout_t * nHexBlock);
void RBLCF_GetNextHexBlock(RBLCF_HexBlockLayout_t * nHexBlock);
uint8 dcom_Lib_HexNibble2ASCII(uint8 t_Nibble_UB);
Std_ReturnType rbl_SwcDiagAdapter_ReadOdometerData(uint8 * Data);
Std_ReturnType rbl_SwcDiagAdapter_ReadOperatingTimeData(uint8 * Data);

/* Global data */
extern uint8 DCOM_SupplierPubKey_Sig_RAM_Mirror[258];
typedef struct dcom_MB_ReadDataByIdentifier_av_struct { uint16 * ref_DID0x01A2_DataLength; const volatile dcom_ApplHeader_tst * ref_dcom_ApplHeader_st; } dcom_MB_ReadDataByIdentifier_av_struct;
extern dcom_MB_ReadDataByIdentifier_av_struct av_dcom_MB_ReadDataByIdentifier;
RBLCF_StdHexInfoStruct_t buffer_HexInfoRef;
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
#define BOOTSOFTWAREVERDDSPCKG_YEAR    (0x01)
#define BOOTSOFTWAREVERDDSPCKG_MONTH   (0x01)
#define BOOTSOFTWAREVERSION_YEAR 0x01
#define BOOTSOFTWAREVERSION_WEEK 0x01
#define BOOTSOFTWAREVERSION_LEVEL 0x01
dcom_BootHeader_tst TestVar = {BOOTSOFTWAREVERDDSPCKG_YEAR,BOOTSOFTWAREVERDDSPCKG_MONTH,BOOTSOFTWAREVERSION_YEAR,BOOTSOFTWAREVERSION_WEEK,BOOTSOFTWAREVERSION_LEVEL};
dcom_BootHeader_tst *DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
dcom_BootHeader_tst *DCOM_APPLICATION_ENDADDRESS_STUBBED = &TestVar;

#endif
/* Expected variables for global data */
uint8 expected_DCOM_SupplierPubKey_Sig_RAM_Mirror[258];
typedef struct expected_dcom_MB_ReadDataByIdentifier_av_struct { uint16 ref_DID0x01A2_DataLength; dcom_ApplHeader_tst ref_dcom_ApplHeader_st; } expected_dcom_MB_ReadDataByIdentifier_av_struct;
expected_dcom_MB_ReadDataByIdentifier_av_struct expected_av_dcom_MB_ReadDataByIdentifier;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No initialisation for const data: dcom_ApplHeader_st */
    INITIALISE(DCOM_SupplierPubKey_Sig_RAM_Mirror);
    INITIALISE(ACCESS_VARIABLE(dcom_MB_ReadDataByIdentifier, DID0x01A2_DataLength));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(DCOM_SupplierPubKey_Sig_RAM_Mirror, expected_DCOM_SupplierPubKey_Sig_RAM_Mirror);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_ReadDataByIdentifier, DID0x01A2_DataLength), ACCESS_EXPECTED_VARIABLE(dcom_MB_ReadDataByIdentifier, DID0x01A2_DataLength));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("DCOM_SupplierPubKey_Sig_RAM_Mirror", DCOM_SupplierPubKey_Sig_RAM_Mirror, expected_DCOM_SupplierPubKey_Sig_RAM_Mirror, sizeof(expected_DCOM_SupplierPubKey_Sig_RAM_Mirror));
    CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_ReadDataByIdentifier, DID0x01A2_DataLength), ACCESS_EXPECTED_VARIABLE(dcom_MB_ReadDataByIdentifier, DID0x01A2_DataLength));
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_ActiveDiagnosticSession_F100_ReadData(int doIt);
void ut_dcom_DDS_Package_Release_F10D_ReadData(int doIt);
void ut_dcom_Diagnostic_Trace_Memory_102_ReadData(int doIt);
void ut_dcom_Ecu_Extract_Version_EF00_ReadData(int doIt);
void ut_dcom_ECUSerialNumber_F18C_ReadData(int doIt);
void ut_dcom_HardwareSupplier_F154_ReadData(int doIt);
void ut_dcom_HardwareVersion_F150_ReadData(int doIt);
void ut_dcom_MercedesCarGroupHardware_F111_ReadData(int doIt);
void ut_dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(int doIt);
void ut_dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(int doIt);
void ut_dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(int doIt);
void ut_dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(int doIt);
void ut_dcom_SoftwareSupplier_Bootloader_F155_ReadData(int doIt);
void ut_dcom_SoftwareSupplier_Application_F155_ReadData(int doIt);
void ut_dcom_Diagnostic_Extract_Version_EF01_ReadData(int doIt);
void ut_dcom_ECU_Name_F104_ReadData(int doIt);
void ut_dcom_MercedesCarGroupSoftware_F121_ReadData(int doIt);
void ut_dcom_Minimum_Software_Version_Bootloader_EF05_ReadData(int doIt);
void ut_dcom_Minimum_Software_Version_Application_EF05_ReadData(int doIt);
void ut_dcom_BootSoftwareVersion_F151_F153_ReadData(int doIt);
void ut_dcom_SoftwareVersion_Application_F151_ReadData(int doIt);
void ut_dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData(int doIt);
void ut_dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(int doIt);
void ut_dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData(int doIt);
void ut_dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData(int doIt);
void ut_dcom_Supported_Configuration_Mechanisms_F131_ReadData(int doIt);
void ut_dcom_VedocRelavantHardwarePartNumber_F103_ReadData(int doIt);
void ut_dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData(int doIt);
void ut_dcom_VedocRelavantECUSerialNumber_F103_ReadData(int doIt);
void ut_dcom_VehicleOdometerLowResolution_10A_ReadData(int doIt);
void ut_dcom_CurrentOperatingTime_133_ReadData(int doIt);
void ut_dcom_ActivateSupplierSpecificMessages_012A_ReadData(int doIt);
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
    OPEN_LOG("ut_dcom_MB_ReadDataByIdentifier.ctr", false, 100);
    START_SCRIPT("dcom_MB_ReadDataByIdentifier", true);

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
	ut_dcom_ActiveDiagnosticSession_F100_ReadData(1);
	ut_dcom_DDS_Package_Release_F10D_ReadData(1);
	ut_dcom_Diagnostic_Trace_Memory_102_ReadData(1);
	ut_dcom_Ecu_Extract_Version_EF00_ReadData(1);
	ut_dcom_ECUSerialNumber_F18C_ReadData(1);
	ut_dcom_HardwareSupplier_F154_ReadData(1);
	ut_dcom_HardwareVersion_F150_ReadData(1);
	ut_dcom_MercedesCarGroupHardware_F111_ReadData(1);
	ut_dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(1);
	ut_dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(1);
	ut_dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(1);
	ut_dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(1);
	ut_dcom_SoftwareSupplier_Bootloader_F155_ReadData(1);
	ut_dcom_SoftwareSupplier_Application_F155_ReadData(1);
	ut_dcom_Diagnostic_Extract_Version_EF01_ReadData(1);
	ut_dcom_ECU_Name_F104_ReadData(1);
	ut_dcom_MercedesCarGroupSoftware_F121_ReadData(1);
	ut_dcom_Minimum_Software_Version_Bootloader_EF05_ReadData(1);
	ut_dcom_Minimum_Software_Version_Application_EF05_ReadData(1);
	ut_dcom_BootSoftwareVersion_F151_F153_ReadData(1);
	ut_dcom_SoftwareVersion_Application_F151_ReadData(1);
	ut_dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData(1);
	ut_dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(1);
	ut_dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData(1);
	ut_dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData(1);
	ut_dcom_Supported_Configuration_Mechanisms_F131_ReadData(1);
	ut_dcom_VedocRelavantHardwarePartNumber_F103_ReadData(1);
	ut_dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData(1);
	ut_dcom_VedocRelavantECUSerialNumber_F103_ReadData(1);
	ut_dcom_VehicleOdometerLowResolution_10A_ReadData(1);
	ut_dcom_CurrentOperatingTime_133_ReadData(1);
	ut_dcom_ActivateSupplierSpecificMessages_012A_ReadData(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_ReadDataByIdentifier.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_ActiveDiagnosticSession_F100_ReadData(int doIt){
if (doIt) {

    START_TEST("46147: [MMP2.11]UTC_dcom_CustDiag_ActiveDiagSession_F100_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46147");

					/*TEST STEPS*/
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 data_buffer[4]= {0X00,0X00,0X00,0X00};
					uint8 * Data = data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("Dcm_GetSesCtrlType#stub_Dcm_GetSesCtrlType");

					/* Call SUT */
					returnValue = dcom_ActiveDiagnosticSession_F100_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], DCOM_ACTIVE_DIAG_STATUS_APPL);
					CHECK_U_CHAR(Data[1], DCOM_ACTIVE_DIAG_VARIANT);
					CHECK_U_CHAR(Data[2], DCOM_ACTIVE_DIAG_VERSION);
					CHECK_U_CHAR(Data[3], 0x01);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_ActiveDiagnosticSession_F100_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_DDS_Package_Release_F10D_ReadData(int doIt){
if (doIt) {
    START_TEST("46255: [MMP2.11]UTC_dcom_DDS_Package_Release_F10D_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46255");

					#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 dataBuffer[4] = {0x00};
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[4] = {DCOM_DDSPCKG_YEAR,DCOM_DDSPCKG_MONTH,DCOM_DDSPCKG_MONTH,DCOM_DDSPCKG_MONTH};
					Std_ReturnType returnValue = E_NOT_OK;

					DCOM_APPLICATION_ENDADDRESS_STUBBED = &TestVar;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_DDS_Package_Release_F10D_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 dataBuffer[4] = {0x00};
					memset(dataBuffer,0x00,sizeof(dataBuffer));
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[4] = {DCOM_DDSPCKG_YEAR,DCOM_DDSPCKG_MONTH,DCOM_SUPPLIERID_HIGHBYTE,DCOM_SUPPLIERID_HIGHBYTE};
					Std_ReturnType returnValue = E_NOT_OK;

					DCOM_BOOTLOADER_ADDRESS_STUBBED = NULL_PTR;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_DDS_Package_Release_F10D_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
					END_STEP();

					START_STEP("3_NTS", true);
					/* Test step data */
					uint8 dataBuffer[4] = {0x00};
					memset(dataBuffer,0x55,sizeof(dataBuffer));
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[4] = {DCOM_DDSPCKG_YEAR,DCOM_DDSPCKG_MONTH,0x55,0x55};
					Std_ReturnType returnValue = E_NOT_OK;

					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
					DCOM_APPLICATION_ENDADDRESS_STUBBED = 0;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_DDS_Package_Release_F10D_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
					#endif

					START_STEP("4_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_DDS_Package_Release_F10D_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
       END_TEST();
}}

void ut_dcom_Diagnostic_Trace_Memory_102_ReadData(int doIt){
if (doIt) {

   START_TEST("46148: [MMP2.11]UTC_dcom_Diagnostic_Trace_Memory_102_ReadData",
              "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46148 ");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_102");

					/* Call SUT */
					returnValue = dcom_Diagnostic_Trace_Memory_102_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],0x01);
					CHECK_U_CHAR(Data[1],0x02);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Diagnostic_Trace_Memory_102_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_Ecu_Extract_Version_EF00_ReadData(int doIt){
if (doIt) {

    START_TEST("46168: [MMP2.11]UTC_dcom_Ecu_Extract_Version_EF00_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46168");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 data_buffer[100]= {0x00};
					uint8 * Data = data_buffer;
					uint8 Expected_DiagnosticExtractInformationXDISversion[10] = {DCOM_ECU_EXTRACT_INFO_XDIS_VERSION};
					uint8 Expected_DiagnosticExtractInformationexportdate[10] = {DCOM_ECU_EXTRACT_INFO_EXPORT_DATE};
					uint8 Expected_DiagnosticExtractInformationEcuname[30] = {DCOM_ECU_EXT_INFO_ECU_NAME};
					uint8 Expected_DiagnosticExtractInformationChecksum[40]={DCOM_ECU_EXTRACT_INFO_CHECKSUM};
					Std_ReturnType returnValue = E_NOT_OK;
					uint8 i;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Ecu_Extract_Version_EF00_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], DCOM_ECU_EXTRACT_MAJOR_VERSION);
					CHECK_U_CHAR(Data[1], DCOM_ECU_EXTRACT_MINOR_VERSION);
					CHECK_U_CHAR(Data[2], DCOM_ECU_EXTRACT_PATCH_VERSION);
					CHECK_U_CHAR(Data[3], DCOM_ECU_EXTRACT_INFO_ID_TYPE);

					for (i=0;i<10;i++)
					{
					CHECK_U_CHAR(Data[4+i], Expected_DiagnosticExtractInformationXDISversion[i]);
					}
					for (i=0;i<10;i++)
					{
					CHECK_U_CHAR(Data[14+i], Expected_DiagnosticExtractInformationexportdate[i]);
					}
					for (i=0;i<30;i++)
					{
					CHECK_U_CHAR(Data[24+i], Expected_DiagnosticExtractInformationEcuname[i]);
					}
					for (i=0;i<40;i++)
					{
					CHECK_U_CHAR(Data[54+i], Expected_DiagnosticExtractInformationChecksum[i]);
					}

					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Ecu_Extract_Version_EF00_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_ECUSerialNumber_F18C_ReadData(int doIt){
if (doIt) {

   START_TEST("46149: [MMP2.11]UTC_dcom_ECUSerialNumber_F18C_ReadData",
              "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46149");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_data[2]={0X00,0X00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("{dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F18C}");

					/* Call SUT */
					returnValue =  dcom_ECUSerialNumber_F18C_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x0f);
					CHECK_U_CHAR(Data[1], 0xff);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_ECUSerialNumber_F18C_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
   END_TEST();
}}

void ut_dcom_HardwareSupplier_F154_ReadData(int doIt){
if (doIt) {

    START_TEST("46150: [MMP2.11]UTC_dcom_HardwareSupplier_F154_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46150");

				START_STEP("1_NTS", true);
				/* Test step data */
				uint8 Data_buffer[2]={0x00,0x01};
				uint8 *Data  = Data_buffer;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_HardwareSupplier_F154_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(Data[0],DCOM_SUPPLIERID_HIGHBYTE);
				CHECK_U_CHAR(Data[1],DCOM_SUPPLIERID_LOWBYTE);
				CHECK_U_CHAR(returnValue, E_OK);

				END_CALLS();
				END_STEP();

				START_STEP("2_NTS", true);
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_HardwareSupplier_F154_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);

				END_CALLS();
				END_STEP();
    END_TEST();
}}

void ut_dcom_HardwareVersion_F150_ReadData(int doIt){
if (doIt) {

    START_TEST("46151: [MMP2.11]UTC_dcom_HardwareVersion_F150_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46151");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_Data[4]={0X00,0X00,0X00,0X00} ;
					uint8 * Data = buffer_Data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F150");

					/* Call SUT */
					returnValue = dcom_HardwareVersion_F150_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(Data[2], 0x03);
					CHECK_U_CHAR(Data[3], 0x04);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_HardwareVersion_F150_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_MercedesCarGroupHardware_F111_ReadData(int doIt){
if (doIt) {

   START_TEST("46152: [MMP2.11]UTC_dcom_MercedesCarGroupHardware_F111_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46152");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Buffer_data[4]={0x00,0x00,0x00,0x00};
					uint8 * Data = Buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F111");

					/* Call SUT */
					returnValue = dcom_MercedesCarGroupHardware_F111_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(Data[2], 0x03);
					CHECK_U_CHAR(Data[3], 0x04);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_MercedesCarGroupHardware_F111_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(int doIt)
{
	 if (doIt) {

	     START_TEST("48963: [MMP2.11]UTC_dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData",
	                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48963");

						START_STEP("1_NTS", true);
						/* Test step data */
						uint8 buffer_Data[2] = {0x00,0x00};
						uint8 * Data = buffer_Data;
						Std_ReturnType returnValue = E_NOT_OK;

						/* Expected Call Sequence  */
						EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub2_dcom_Lib_ReadNvMData_F15B");

						/* Call SUT */
						returnValue = dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(Data);

						/* Test case checks */
						CHECK_U_CHAR(Data[0], 0x01);
						CHECK_U_CHAR(Data[1], 0x02);
						CHECK_U_CHAR(returnValue, E_OK);

						/* Checks on global data */
						check_global_data();
						END_CALLS();
						END_STEP();

						START_STEP("2_NTS", true);
						/* Test step data */
						uint8 * Data = NULL_PTR;
						Std_ReturnType returnValue = E_OK;

						/* Expected Call Sequence  */
						EXPECTED_CALLS("");

						/* Call SUT */
						returnValue = dcom_Read_Software_Fingerprint_s_Bootloader_Data_F15B_ReadData(Data);

						/* Test case checks */
						CHECK_U_CHAR(returnValue, E_NOT_OK);

						/* Checks on global data */
						check_global_data();
						END_CALLS();
						END_STEP();
	     END_TEST();
}}
void ut_dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(int doIt){
if (doIt) {

    START_TEST("46153: [MMP2.11]UTC_dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46153");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_Data[2] = {0x00,0x00};
					uint8 * Data = buffer_Data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F15B");

					/* Call SUT */
					returnValue = dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Read_Software_Fingerprint_s_Application_Data_F15B_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(int doIt)
{
	 if (doIt) {

	     START_TEST("48962: [MMP2.11]UTC_dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData",
	                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48962");

						START_STEP("1_NTS", true);
						/* Test step data */
						uint8 Data_buffer[4] ={0x00,0x00,0x00,0x00,0x00};
						uint8 * Data = Data_buffer;
						Std_ReturnType returnValue = E_NOT_OK;

						/* Expected Call Sequence  */
						EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub2_dcom_Lib_ReadNvMData_0100_005");

						/* Call SUT */
						returnValue = dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(Data);

						/* Test case checks */
						CHECK_U_CHAR(Data[0], 0x01);
						CHECK_U_CHAR(Data[1], 0x02);
						CHECK_U_CHAR(Data[2], DCOM_MAX_REPROG_ATT_MSB);
						CHECK_U_CHAR(Data[3], DCOM_MAX_REPROG_ATT_LSB);
						CHECK_U_CHAR(returnValue, E_OK);

						END_CALLS();
						END_STEP();

						START_STEP("2_NTS", true);
						/* Test step data */
						uint8 Data_buffer[4] ={0x00,0x00,0x00,0x00};
						uint8 * Data = Data_buffer;
						Std_ReturnType returnValue = E_NOT_OK;

						/* Expected Call Sequence  */
						EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub2_dcom_Lib_ReadNvMData_0100_06");

						/* Call SUT */
						returnValue = dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(Data);

						/* Test case checks */
						CHECK_U_CHAR(Data[0], 0x01);
						CHECK_U_CHAR(Data[1], 0x02);
						CHECK_U_CHAR(Data[2], 0x03);
						CHECK_U_CHAR(Data[3], 0x04);
						CHECK_U_CHAR(returnValue, E_NOT_OK);

						END_CALLS();
						END_STEP();

						START_STEP("3_NTS", true);
						/* Test step data */
						uint8 * Data = NULL_PTR;
						Std_ReturnType returnValue = E_OK;
						/* Expected Call Sequence  */
						EXPECTED_CALLS("");

						/* Call SUT */
						returnValue = dcom_ReprogrammingAttemptCounter_Bootloader_Data_0100_ReadData(Data);

						/* Test case checks */
						CHECK_U_CHAR(returnValue, E_NOT_OK);

						END_CALLS();
						END_STEP();
	     END_TEST();
}}

void ut_dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(int doIt){
if (doIt) {

    START_TEST("46155: [MMP2.11]UTC_dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46155");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Data_buffer[4] ={0x00,0x00,0x00,0x00,0x00};
					uint8 * Data = Data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_0100_005");

					/* Call SUT */
					returnValue = dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(Data[2], DCOM_MAX_REPROG_ATT_MSB);
					CHECK_U_CHAR(Data[3], DCOM_MAX_REPROG_ATT_LSB);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 Data_buffer[4] ={0x00,0x00,0x00,0x00};
					uint8 * Data = Data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_0100_06");

					/* Call SUT */
					returnValue = dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(Data[2], 0x03);
					CHECK_U_CHAR(Data[3], 0x04);
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();

					START_STEP("3_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;
					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_ReprogrammingAttemptCounter_Application_Data_0100_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_SoftwareSupplier_Bootloader_F155_ReadData(int doIt){
if (doIt) {

             START_TEST("49019: [MMP2.11]UTC_dcom_SoftwareSupplier_Bootloader_F155_ReadData",
                        "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49019");

					START_STEP("1_NTS", TRUE);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x01};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_SoftwareSupplier_Bootloader_F155_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],DCOM_SUPPLIERID_HIGHBYTE);
					CHECK_U_CHAR(Data[1],DCOM_SUPPLIERID_LOWBYTE);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", TRUE);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_SoftwareSupplier_Bootloader_F155_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();

    END_TEST();

}}

void ut_dcom_SoftwareSupplier_Application_F155_ReadData(int doIt){
if (doIt) {

             START_TEST("46156: [MMP2.11]UTC_dcom_SoftwareSupplier_Application_F155_ReadData",
                        "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46156");

					START_STEP("1_NTS", TRUE);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_SoftwareSupplier_Application_F155_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],DCOM_SUPPLIERID_HIGHBYTE);
					CHECK_U_CHAR(Data[1],DCOM_SUPPLIERID_LOWBYTE);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", TRUE);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_SoftwareSupplier_Application_F155_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();

}}

void ut_dcom_Diagnostic_Extract_Version_EF01_ReadData(int doIt){
if (doIt) {


    START_TEST("46187: [MMP2.11]UTC_dcom_Diagnostic_Extract_Version_EF01_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46187");

					/* Test steps */
					START_STEP("1_NTS", true);

					/* Test step data */
					uint8 Data_buffer[60]={0x00};
					uint8 *Data = Data_buffer;

					uint8 Expected_DiagnosticExtractCandelaVersion[10] = {DCOM_DIAGNOSTIC_EXTRACT_CANDELA_VERSION};
					uint8 Expected_DiagnosticExtractDDMVersion[10] = {DCOM_DIAGNOSTIC_EXTRACT_DDM_VERSION};
					uint8 Expected_DiagnosticExtractExportedDiagnosticVariant[30] = {DCOM_DIAGNOSTIC_EXTRACT_EXPORTED_DIAGNOSTIC_VARIANT};
					Std_ReturnType returnValue = E_NOT_OK;
					uint8 i;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Diagnostic_Extract_Version_EF01_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(Data[0], DCOM_DIAGNOSTIC_EXTRACT_MAJOR_VERSION);
					CHECK_U_CHAR(Data[1], DCOM_DIAGNOSTIC_EXTRACT_MINOR_VERSION);
					CHECK_U_CHAR(Data[2], DCOM_DIAGNOSTIC_EXTRACT_PATCH_VERSION);

					for (i=0;i<10;i++)
					{
					CHECK_U_CHAR(Data[3+i], Expected_DiagnosticExtractCandelaVersion[i]);
					}
					for (i=0;i<10;i++)
					{
					CHECK_U_CHAR(Data[13+i], Expected_DiagnosticExtractDDMVersion[i]);
					}
					for (i=0;i<30;i++)
					{
					CHECK_U_CHAR(Data[23+i], Expected_DiagnosticExtractExportedDiagnosticVariant[i]);
					}
					CHECK_U_CHAR(returnValue,E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);

					/* Test step data */
					uint8 *Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Diagnostic_Extract_Version_EF01_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
					END_STEP();

    END_TEST();
}}

void ut_dcom_ECU_Name_F104_ReadData(int doIt){
if (doIt) {

    START_TEST("46175: [MMP2.11]UTC_dcom_ECU_Name_F104_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46175");

				/* Test steps */
				START_STEP("1_NTS", true);
				/* Test step data */
				uint8 Data_buffer[10]={0x00};
				uint8 expected_ECUname[10]={DCOM_IMU_ECU_NAME};
				uint8 * Data = Data_buffer;
				Std_ReturnType returnValue = E_NOT_OK;
				uint8 i;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_ECU_Name_F104_ReadData(Data);

				/* Test step checks */
				for(i=0;i<10;i++)
				{
				CHECK_U_CHAR(Data[i],expected_ECUname[i]);
				}

				CHECK_U_CHAR(returnValue,E_OK);
				END_CALLS();
				END_STEP();

				START_STEP("2_NTS", true);

				/* Test step data */
				uint8 * Data = NULL_PTR;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_ECU_Name_F104_ReadData(Data);

				/* Test step checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);
				END_CALLS();
			END_STEP();

    END_TEST();
}}

void ut_dcom_MercedesCarGroupSoftware_F121_ReadData(int doIt){
if (doIt) {

    START_TEST("46157: [MMP2.11]UTC_dcom_MercedesCarGroupSoftware_F121_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46157");
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Buffer_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 Expected_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 i;
					uint8 *Data = Buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
					DCOM_APPLICATION_ENDADDRESS_STUBBED = &TestVar;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_MercedesCarGroupSoftware_F121_ReadData(Data);

					/* Test case checks */
					CHECK_MEMORY("Data",Data,Expected_data,sizeof(Expected_data));
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();
					START_STEP("2_NTS", true);

					/* Test step data */
					uint8 Buffer_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 Expected_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 i;
					uint8 *Data = Buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = NULL_PTR;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_MercedesCarGroupSoftware_F121_ReadData(Data);

					/* Test case checks */
					CHECK_MEMORY("Data",Data,Expected_data,sizeof(Expected_data));
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
					START_STEP("3_NTS", true);

					/* Test step data */
					uint8 Buffer_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 Expected_data[10] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
					uint8 i;
					uint8 *Data = Buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
					DCOM_APPLICATION_ENDADDRESS_STUBBED = 0;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_MercedesCarGroupSoftware_F121_ReadData(Data);

					/* Test case checks */
					CHECK_MEMORY("Data",Data,Expected_data,sizeof(Expected_data));
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
#endif

					START_STEP("4_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;
					/* Expected Call Sequence  */
					EXPECTED_CALLS("");
					/* Call SUT */
					returnValue = dcom_MercedesCarGroupSoftware_F121_ReadData(Data);
					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();
}}

void ut_dcom_Minimum_Software_Version_Bootloader_EF05_ReadData(int doIt){
if (doIt) {

    START_TEST("49070: [MMP2.11]UTC_dcom_Minimum_Software_Version_Bootloader_EF05_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49070");

					/* Test steps */
					START_STEP("1_NTS", true);
					/* Test step data */
					Std_ReturnType returnValue = E_NOT_OK;
					uint8 buffer_data[2]={0X00,0X00};
					uint8 * Data = buffer_data;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_EF05");

					/* Call SUT */
					returnValue = dcom_Minimum_Software_Version_Bootloader_EF05_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(returnValue,E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Minimum_Software_Version_Bootloader_EF05_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
					END_STEP();

    END_TEST();
}}

void ut_dcom_Minimum_Software_Version_Application_EF05_ReadData(int doIt){
if (doIt) {

    START_TEST("46186: [MMP2.11]UTC_dcom_Minimum_Software_Version_Application_EF05_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46186");

					/* Test steps */
					START_STEP("1_NTS", true);
					/* Test step data */
					Std_ReturnType returnValue = E_NOT_OK;
					uint8 buffer_data[2]={0X00,0X00};
					uint8 * Data = buffer_data;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_EF05_01");

					/* Call SUT */
					returnValue = dcom_Minimum_Software_Version_Application_EF05_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(Data[0], 0x01);
					CHECK_U_CHAR(Data[1], 0x02);
					CHECK_U_CHAR(returnValue,E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Minimum_Software_Version_Application_EF05_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
					END_STEP();

    END_TEST();
}}

void ut_dcom_BootSoftwareVersion_F151_F153_ReadData(int doIt){
if (doIt) {

    START_TEST("49018: [MMP2.11]UTC_dcom_BootSoftwareVersion_F151_F153_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49018");

					#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 dataBuffer[3]={0x00};
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[3]= {BOOTSOFTWAREVERSION_YEAR,BOOTSOFTWAREVERSION_WEEK,BOOTSOFTWAREVERSION_LEVEL};
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
					DCOM_APPLICATION_ENDADDRESS_STUBBED = &TestVar;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_BootSoftwareVersion_F151_F153_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 dataBuffer[3] = {0x00};
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[3]= {0x00,0x00,0x00};
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = NULL_PTR;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_BootSoftwareVersion_F151_F153_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();

					START_STEP("3_NTS", true);
					/* Test step data */
					uint8 dataBuffer[3] = {0x00};
					uint8 *Data = dataBuffer;
					uint8 expected_dataBuffer[3]= {0x00,0x00,0x00};
					Std_ReturnType returnValue = E_NOT_OK;
					DCOM_BOOTLOADER_ADDRESS_STUBBED = &TestVar;
					DCOM_APPLICATION_ENDADDRESS_STUBBED = 0;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_BootSoftwareVersion_F151_F153_ReadData(Data);

					/* Test step checks */
					CHECK_MEMORY("Data",Data,expected_dataBuffer,sizeof(expected_dataBuffer));
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
#endif

					START_STEP("4_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");
					/* Call SUT */
					returnValue = dcom_BootSoftwareVersion_F151_F153_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();

       END_TEST();

}}

void ut_dcom_SoftwareVersion_Application_F151_ReadData(int doIt){
 if (doIt) {

     START_TEST("46158: [MMP2.11]UTC_dcom_SoftwareVersion_Application_F151_ReadData",
                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46158");

				START_STEP("1_NTS", TRUE);
				/* Test step data */
				uint8 Buffer_data[3]={0x00,0x01,0x02};
				uint8 * Data = Buffer_data;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_SoftwareVersion_Application_F151_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(Data[0], DCOM_SOFTWARE_VERSION_YEAR);
				CHECK_U_CHAR(Data[1], DCOM_SOFTWARE_VERSION_WEEK);
				CHECK_U_CHAR(Data[2], DCOM_SOFTWARE_VERSION_PATCH_LEVEL);
				CHECK_U_CHAR(returnValue, E_OK);

				END_CALLS();
				END_STEP();

				START_STEP("2_NTS", TRUE);
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_SoftwareVersion_Application_F151_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);

				END_CALLS();
				END_STEP();
     END_TEST();
 }}

void ut_dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData(int doIt){
if (doIt) {

	START_TEST("46159: [MMP2.11]UTC_dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData",
		       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46159");

				START_STEP("1_NTS", true);
				uint8 buffer_Data[5] ={0x01,0x02,0x03,0x04,0x05};
				uint8 * Data = buffer_Data;
				Std_ReturnType returnValue = E_NOT_OK;

				/* Expected Call Sequence */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(Data[0],DCOM_SWRELEASE_MAJORVERSION);
				CHECK_U_CHAR(Data[1],DCOM_SWRELEASE_MINORVERSION);
				CHECK_U_CHAR(Data[2],DCOM_SWSPRINT_MAJORVERSION);
				CHECK_U_CHAR(Data[3],DCOM_SWSPRINT_MINORVERSION);
				CHECK_U_CHAR(returnValue, E_OK);
				END_CALLS();
				END_STEP();

				START_STEP("2_NTS", true);
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_StandardApplicationSWPackageSWVersion_EF03_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);

				END_CALLS();
				END_STEP();
END_TEST();
}}

void ut_dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(int doIt){
 if (doIt) {

     START_TEST("46160: [MMP2.11]UTC_dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData",
                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46160");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_Data[20] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
					uint8 * Data = buffer_Data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("RBLCF_GetFirstHexBlock#stub_RBLCF_GetFirstHexBlock_;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[1],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[2],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[3],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[4],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[5],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[6],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[7],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[8],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[9],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 buffer_Data[20] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
					uint8 * Data = buffer_Data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("RBLCF_GetFirstHexBlock#stub_RBLCF_GetFirstHexBlock_001;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[1],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[2],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[3],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[4],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[5],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[6],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[7],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[8],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[9],DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("3_NTS", true);
					/* Test step data */
					uint8 buffer_Data[20] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
					uint8 * Data = buffer_Data;
					uint8 i;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("RBLCF_GetFirstHexBlock#stub_RBLCF_GetFirstHexBlock_002;"
					               "RBLCF_GetNextHexBlock#stub_RBLCF_GetNextHexBlock;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_2;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_3;"
					               "dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_1");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(Data);

					/* Test case checks */
			        for(i=0;i<12;i++)
			        {
			        	CHECK_U_CHAR(Data[i], DCOM_READ_PDMEMPTY_ASCII_NULL);
			        }
						  CHECK_U_CHAR(returnValue, E_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

					START_STEP("4_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageXCIdentification_EF03_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
         END_TEST();
}}

void ut_dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData(int doIt){
 if (doIt) {

     START_TEST("46161: [MMP2.11]UTC_dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData",
                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46161");

					/* Test steps */
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_Data[2]= {0x00,0x00};
					uint8 * Data = buffer_Data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData(Data);

					/* Test case checks */
					CHECK_CHAR(Data[0],DCOM_SUPPLIERID_HIGHBYTE);
					CHECK_CHAR(Data[1],DCOM_SUPPLIERID_LOWBYTE);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackageSupplierIdentification_EF03_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
     END_TEST();
 }}

void ut_dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData(int doIt){
if (doIt) {

    START_TEST("49069: [MMP2.11]UTC_dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49069");

					/* Test steps */
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Data_buffer[1]={0x01};
					uint8 * Data = Data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(Data[0], DCOM_AUTOSAR_CLASSIC);
					CHECK_U_CHAR(returnValue,E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_StandardApplicationSWPackage_AUTOSAR_Platform_EF03_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
            END_STEP();

    END_TEST();
}}

void ut_dcom_Supported_Configuration_Mechanisms_F131_ReadData(int doIt){
if (doIt) {

    START_TEST("46174: [MMP2.11]UTC_dcom_Supported_Configuration_Mechanisms_F131_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46174");

					/* Test steps */
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Data_buffer[1]={0x01};
					uint8 * Data = Data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Supported_Configuration_Mechanisms_F131_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(Data[0], 0x00);
					CHECK_U_CHAR(returnValue,E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_Supported_Configuration_Mechanisms_F131_ReadData(Data);

					/* Test step checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);
					END_CALLS();
            END_STEP();

    END_TEST();
}}

void ut_dcom_VedocRelavantHardwarePartNumber_F103_ReadData(int doIt){
 if (doIt) {

     START_TEST("46162: [MMP2.11]UTC_dcom_VedocRelavantHardwarePartNumber_F103_ReadData",
                "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46162");

				START_STEP("1_NTS", true);
				/* Test step data */
				Std_ReturnType returnValue = E_NOT_OK;
				uint8 buffer_data[2]={0X00,0X00};
				uint8 * Data = buffer_data;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("{dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F103}");

				/* Call SUT */
				returnValue = dcom_VedocRelavantHardwarePartNumber_F103_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(Data[0], 0x00);
				CHECK_U_CHAR(Data[1], 0x01);
				CHECK_U_CHAR(returnValue, E_OK);

				END_CALLS();
				END_STEP();

				START_STEP("2_NTS", true);
				/* Test step data */
				uint8 * Data = NULL_PTR;
				Std_ReturnType returnValue = E_OK;

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = dcom_VedocRelavantHardwarePartNumber_F103_ReadData(Data);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_NOT_OK);

				END_CALLS();
				END_STEP();
     END_TEST();
 }}

void ut_dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData(int doIt){
if (doIt) {

    START_TEST("46163: [MMP2.11]UTC_dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46163");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 Data_buffer[5]={0x00,0x01,0x02,0x3,0x04};
					uint8 * Data = Data_buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII;"
					"dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_001;"
					"dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_002;"
					"dcom_Lib_HexNibble2ASCII#stub_dcom_Lib_HexNibble2ASCII_003");

					/* Call SUT */
					returnValue = dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(Data[0], DCOM_READ_PDMEMPTY_ASCII_NULL);
					CHECK_U_CHAR(Data[1], 0x00);
					CHECK_U_CHAR(Data[2], 0x01);
					CHECK_U_CHAR(Data[3], 0x02);
					CHECK_U_CHAR(Data[4], 0x03);
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_VedocRelavantHardwareSupplierIdentification_F103_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
				END_STEP();
    END_TEST();
}}

void ut_dcom_VedocRelavantECUSerialNumber_F103_ReadData(int doIt){
if (doIt) {

    START_TEST("46164: [MMP2.11]UTC_dcom_VedocRelavantECUSerialNumber_F103_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46164");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer[16] = {0X00};
					uint8 * Data = buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_F103_01");

					/* Call SUT */
					returnValue = dcom_VedocRelavantECUSerialNumber_F103_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_VedocRelavantECUSerialNumber_F103_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

         END_TEST();
}}

void ut_dcom_VehicleOdometerLowResolution_10A_ReadData(int doIt){
if (doIt) {

             START_TEST("48413: [MMP2.11]UTC_dcom_VehicleOdometerLowResolution_10A_ReadData",
                        "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48413");

#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
					START_STEP("1_NTS", true);

					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("rbl_SwcDiagAdapter_ReadOdometerData#rbl_SwcDiagAdapter_ReadOdometerData_1");

					/* Call SUT */
					returnValue = dcom_VehicleOdometerLowResolution_10A_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();
#endif

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_VehicleOdometerLowResolution_10A_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
    END_TEST();

}}

void ut_dcom_CurrentOperatingTime_133_ReadData(int doIt){
  if (doIt) {

   START_TEST("48416: [MMP2.11]UTC_dcom_CurrentOperatingTime_133_ReadData",
              "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48416");
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer_data[2]={0x00,0x00};
					uint8 * Data = buffer_data;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("rbl_SwcDiagAdapter_ReadOperatingTimeData#rbl_SwcDiagAdapter_ReadOperatingTimeData_1");

					/* Call SUT */
					returnValue = dcom_CurrentOperatingTime_133_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();
#endif
					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_CurrentOperatingTime_133_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					END_CALLS();
					END_STEP();
      END_TEST();

  }}

void ut_dcom_ActivateSupplierSpecificMessages_012A_ReadData(int doIt){
  if (doIt) {

                START_TEST("48945: [MMP2.11]UTC_dcom_ActivateSupplierSpecificMessages_012A_ReadData",
                           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48945");

					START_STEP("1_NTS", true);
					/* Test step data */
					uint8 buffer[16] = {0X00};
					uint8 * Data = buffer;
					Std_ReturnType returnValue = E_NOT_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("dcom_Lib_ReadNvMData#stub_dcom_Lib_ReadNvMData_012A");

					/* Call SUT */
					returnValue = dcom_ActivateSupplierSpecificMessages_012A_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_OK);

					END_CALLS();
					END_STEP();

					START_STEP("2_NTS", true);
					/* Test step data */
					uint8 * Data = NULL_PTR;
					Std_ReturnType returnValue = E_OK;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					returnValue = dcom_ActivateSupplierSpecificMessages_012A_ReadData(Data);

					/* Test case checks */
					CHECK_U_CHAR(returnValue, E_NOT_OK);

					/* Checks on global data */
					check_global_data();
					END_CALLS();
					END_STEP();

      END_TEST();
}}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function Dcm_GetSesCtrlType */
Std_ReturnType Dcm_GetSesCtrlType(Dcm_SesCtrlType * SesCtrlType){
    REGISTER_CALL("Dcm_GetSesCtrlType");

    IF_INSTANCE("stub_Dcm_GetSesCtrlType") {
                    *SesCtrlType = 0x01;
                    return 0;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function dcom_Lib_ReadNvMData */
Std_ReturnType dcom_Lib_ReadNvMData(NvM_BlockIdType Block_Id,
                                    uint8 * Data,
                                    uint8 NvM_Length,
                                    uint8 Fill_NvM){
    REGISTER_CALL("dcom_Lib_ReadNvMData");

    IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F190") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_VIN);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_VIN);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY_ASCII_NULL);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0xFF;
				Data[1] = 0xFF;
				return E_OK;
    }

    IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F103") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_HW_PartNumber);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY_ASCII_NULL);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x00;
				Data[1] = 0x01;
				return E_OK;
    }

    IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F103_01") {
				int i;
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_ECU_SerialNr);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY_ASCII_NULL);
				for(i=0;i<16;i++)
				{
				CHECK_U_CHAR(Data[i],0);
				}
				for(i=0;i<16;i++)
				{
				Data[i] = 1;
				}

				return E_OK;
    }

     IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F18C") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_ECU_SerialNr);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ECU_SerialNr);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY_ASCII_NULL);
				CHECK_U_CHAR(Data[0], 0);
				CHECK_U_CHAR(Data[1], 0);
				Data[0] = 0x0F;
				Data[1] = 0xFF;
				return E_OK;
    }

    IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F150") {
				CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_rbl_HwVers);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_rbl_HwVers);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0], 0);
				CHECK_U_CHAR(Data[1], 0);
				CHECK_U_CHAR(Data[2], 0);
				CHECK_U_CHAR(Data[3], 0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
    }

    IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F111") {
				CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_DCOM_MB_HW_PartNumber);
				CHECK_U_CHAR(NvM_Length,NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_HW_PartNumber);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY_ASCII_NULL);
				CHECK_U_CHAR(Data[0], 0);
				CHECK_U_CHAR(Data[1], 0);
				CHECK_U_CHAR(Data[2], 0);
				CHECK_U_CHAR(Data[3], 0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
     }

     IF_INSTANCE("stub_dcom_Lib_ReadNvMData_F15B") {
				CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_FLASH_MB_SWFingerprint_LB1);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_FLASH_MB_SWFingerprint_LB1);
				CHECK_U_CHAR(Fill_NvM,DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				return E_OK;
     }

     IF_INSTANCE("stub2_dcom_Lib_ReadNvMData_F15B") {
				CHECK_U_CHAR(Block_Id, NvMConf_NvMBlockDescriptor_FLASH_MB_SWFingerprint_LB0);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_FLASH_MB_SWFingerprint_LB0);
				CHECK_U_CHAR(Fill_NvM,DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				return E_OK;
     }

     IF_INSTANCE("stub_dcom_Lib_ReadNvMData_102") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_DiagTraceMem);
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_DiagTraceMem);
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				return E_OK;
     }

     IF_INSTANCE("stub_dcom_Lib_ReadNvMData_0100_005") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB1 );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB1 );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0);
				CHECK_U_CHAR(Data[3],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
     }

     IF_INSTANCE("stub_dcom_Lib_ReadNvMData_0100_06") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB1 );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB1 );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0);
				CHECK_U_CHAR(Data[3],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_NOT_OK;
      }

      IF_INSTANCE("stub2_dcom_Lib_ReadNvMData_0100_005") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB0 );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB0 );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0);
				CHECK_U_CHAR(Data[3],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
      }

      IF_INSTANCE("stub2_dcom_Lib_ReadNvMData_0100_06") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_ReprogAttCounter_LB0 );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_ReprogAttCounter_LB0 );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0);
				CHECK_U_CHAR(Data[3],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_NOT_OK;
      }

      IF_INSTANCE("stub_dcom_Lib_ReadNvMData_EF05") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion_LB0 );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion_LB0 );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0x01);
				CHECK_U_CHAR(Data[3],0x25);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
      }

      IF_INSTANCE("stub_dcom_Lib_ReadNvMData_EF05_01") {
				CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_MinimumSWVersion );
				CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_MinimumSWVersion );
				CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
				CHECK_U_CHAR(Data[0],0);
				CHECK_U_CHAR(Data[1],0);
				CHECK_U_CHAR(Data[2],0x01);
				CHECK_U_CHAR(Data[3],0);
				Data[0] = 0x01;
				Data[1] = 0x02;
				Data[2] = 0x03;
				Data[3] = 0x04;
				return E_OK;
      }

      IF_INSTANCE("stub_dcom_Lib_ReadNvMData_012A") {
    		    int i;
    		    CHECK_U_CHAR(Block_Id,NvMConf_NvMBlockDescriptor_DCOM_MB_ActivateSupplierMsgs);
    		    CHECK_U_CHAR(NvM_Length, NVM_CFG_NV_BLOCK_LENGTH_DCOM_MB_ActivateSupplierMsgs);
    		    CHECK_U_CHAR(Fill_NvM, DCOM_READ_PDMEMPTY);
    			for(i=0;i<16;i++)
    			{
    			CHECK_U_CHAR(Data[i],0);
    			}
    			for(i=0;i<16;i++)
    			{
    			Data[i] = 1;
    			}
    			return E_OK;
      }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function RBLCF_GetFirstHexBlock */
void RBLCF_GetFirstHexBlock(RBLCF_HexBlockLayout_t * nHexBlock){
    REGISTER_CALL("RBLCF_GetFirstHexBlock");

    IF_INSTANCE("stub_RBLCF_GetFirstHexBlock_"){
				nHexBlock->hasNext = 1;
				buffer_HexInfoRef.BlockStructureID = RBLCF_HEXINFOTYPE_COMPLETE;
				RBLCF_HexBlockStruct_t buffer;
				buffer.DeviceID = 10;
				nHexBlock->HexInfoRef = &buffer_HexInfoRef;
				nHexBlock->HexBlockRef = &buffer;
				return;
       }

        IF_INSTANCE("stub_RBLCF_GetFirstHexBlock_001") {
				nHexBlock->hasNext = 1;
				buffer_HexInfoRef.BlockStructureID = RBLCF_HEXINFOTYPE_FSW;
				RBLCF_HexBlockStruct_t buffer;
				buffer.DeviceID = 10;
				nHexBlock->HexInfoRef = &buffer_HexInfoRef;
				nHexBlock->HexBlockRef = &buffer;
				return;
       }

        IF_INSTANCE("stub_RBLCF_GetFirstHexBlock_002") {
				nHexBlock->hasNext = 1;
				buffer_HexInfoRef.BlockStructureID = 0x00;
				RBLCF_HexBlockStruct_t buffer;
				buffer.DeviceID = 10;
				nHexBlock->HexInfoRef = &buffer_HexInfoRef;
				nHexBlock->HexBlockRef = &buffer;
				return;
       }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBLCF_GetNextHexBlock */
void RBLCF_GetNextHexBlock(RBLCF_HexBlockLayout_t * nHexBlock){
    REGISTER_CALL("RBLCF_GetNextHexBlock");

    IF_INSTANCE("stub_RBLCF_GetNextHexBlock") {
                nHexBlock->hasNext = 0;
                return;
            }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function dcom_Lib_HexNibble2ASCII */
uint8 dcom_Lib_HexNibble2ASCII(uint8 t_Nibble_UB){
    REGISTER_CALL("dcom_Lib_HexNibble2ASCII");

    uint8 return_value;
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII") {
                CHECK_CHAR(t_Nibble_UB ,DCOM_SUPPLIERID_HIGHBYTE >> 4);
                return_value = 0;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_001") {
                CHECK_CHAR(t_Nibble_UB ,DCOM_SUPPLIERID_HIGHBYTE & 0x0Fu);
                return_value = 0x01;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_002") {
                CHECK_CHAR(t_Nibble_UB ,DCOM_SUPPLIERID_LOWBYTE >> 4);
                return_value = 0x02;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_003") {
                CHECK_CHAR(t_Nibble_UB ,DCOM_SUPPLIERID_LOWBYTE & 0x0Fu);
                return_value = 0x03;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_") {
                return_value = 0;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_1") {
                return_value = 0x01;
                return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_2") {
                 return_value = 0x02;
                 return return_value;
    }
    IF_INSTANCE("stub_dcom_Lib_HexNibble2ASCII_3") {
                  return_value = 0x03;
                  return return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_SwcDiagAdapter_ReadOdometerData */
Std_ReturnType rbl_SwcDiagAdapter_ReadOdometerData(uint8 * Data){
    REGISTER_CALL("rbl_SwcDiagAdapter_ReadOdometerData");

    IF_INSTANCE("rbl_SwcDiagAdapter_ReadOdometerData_1") {
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_SwcDiagAdapter_ReadOperatingTimeData */
Std_ReturnType rbl_SwcDiagAdapter_ReadOperatingTimeData(uint8 * Data){
    REGISTER_CALL("rbl_SwcDiagAdapter_ReadOperatingTimeData");

    IF_INSTANCE("rbl_SwcDiagAdapter_ReadOperatingTimeData_1") {
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
