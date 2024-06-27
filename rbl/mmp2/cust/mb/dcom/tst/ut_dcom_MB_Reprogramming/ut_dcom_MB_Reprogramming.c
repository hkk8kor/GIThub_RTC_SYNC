/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_Reprogramming.c
 *    Author: GDEV1KOR
 *    Generated on: 11-Oct-2023 14:15:41
 *    Generated from: dcom_MB_Reprogramming.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "Dcm_Prv.h"
#include "dcom_MB_Pub.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/dcom_MB_Reprogramming.h"
#include "RBLCF_MemoryRemap.h"
#include "RB_SWReset.h"
#include "rba_DcmPma.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
void RB_performSWResetWithBootBlock4OEM();

/* Global data */
uint16 dcom_Requested_Tester;
boolean rba_DcmPma_PlantModeStatus_b;
const Dcm_Dsp_Session_t Dcm_Dsp_Session[3U];
uint8 Dcm_ctDiaSess_u8;
typedef struct dcom_MB_Reprogramming_av_struct { volatile dcom_BackUp_RAM_tst * ref_DcmAppl_BackUp_RAM; } dcom_MB_Reprogramming_av_struct;
extern dcom_MB_Reprogramming_av_struct av_dcom_MB_Reprogramming;

/* Expected variables for global data */
uint16 expected_dcom_Requested_Tester;
boolean expected_rba_DcmPma_PlantModeStatus_b;
uint8 expected_Dcm_ctDiaSess_u8;
typedef struct expected_dcom_MB_Reprogramming_av_struct { dcom_BackUp_RAM_tst ref_DcmAppl_BackUp_RAM; } expected_dcom_MB_Reprogramming_av_struct;
expected_dcom_MB_Reprogramming_av_struct expected_av_dcom_MB_Reprogramming;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM));
    INITIALISE(dcom_Requested_Tester);
    INITIALISE(rba_DcmPma_PlantModeStatus_b);
    /* No initialisation for const data: Dcm_Dsp_Session */
    INITIALISE(Dcm_ctDiaSess_u8);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM), ACCESS_EXPECTED_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM));
    COPY_TO_EXPECTED(dcom_Requested_Tester, expected_dcom_Requested_Tester);
    COPY_TO_EXPECTED(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
    COPY_TO_EXPECTED(Dcm_ctDiaSess_u8, expected_Dcm_ctDiaSess_u8);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM)", &ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM), &ACCESS_EXPECTED_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM), sizeof(ACCESS_EXPECTED_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM)));
    CHECK_U_INT(dcom_Requested_Tester, expected_dcom_Requested_Tester);
    CHECK_BOOLEAN(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
    CHECK_U_CHAR(Dcm_ctDiaSess_u8, expected_Dcm_ctDiaSess_u8);
}

/* Prototypes for test functions */
#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)
void ut_dcom_SetProgConditions(int);

#else

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
void ut_Dcm_GetProgConditions(int);
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_Switch_DcmExecuteDscReset(int);
void ut_DcmAppl_DcmGetStoreType(int);
void ut_Dcm_SetProgConditions(int);
#endif
#endif

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
    OPEN_LOG("ut_dcom_MB_Reprogramming.ctr", false, 100);
    START_SCRIPT("rrdcom_MB_Reprogramming", true);

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
#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)
	ut_dcom_SetProgConditions(1);
#else

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
	ut_DcmAppl_Switch_DcmExecuteDscReset(1);
	ut_DcmAppl_DcmGetStoreType(1);
	ut_Dcm_SetProgConditions(1);
#endif
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
	ut_Dcm_GetProgConditions(1);
#endif

#endif
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_Reprogramming.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)
void ut_dcom_SetProgConditions(int doIt){
if (doIt) {

    /* Test case data declarations */

    START_TEST("46404: [MMP2.11]UTC_dcom_SetProgConditions",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46404");

            /* Test steps */
        START_STEP("1_NTS", true);
        {
           /* Test step data */
           uint16 dcom_Requested_Tester;

       	   #if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
           	   	  dcom_Requested_Tester = DCOM_SECOND_TESTER;
       	   #endif
       	   #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
           	   	  ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted = 0xFF;
           	   	  ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = 0xFF;
       	   #endif

            /* Expected Call Sequence  */
       	   #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
           	   	  EXPECTED_CALLS("RB_performSWResetWithBootBlock4OEM#SWReset");
       	   #else
           	   	  EXPECTED_CALLS("");
       	   #endif

                /* Call SUT */
                dcom_SetProgConditions();

                /* Test step checks */
           #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
                   CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted, DCOM_REQPROGREQUESTINVERTED);
           #if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
                   CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION_2NDTESTER);
           #else
                   CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
           #endif
           #endif

            END_CALLS();
            END_STEP();
        }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
            /* Test step data */
            uint16 dcom_Requested_Tester;
            dcom_Requested_Tester = DCOM_FIRST_TESTER;
            #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
                    ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = 0xFF;
            #endif
                        /* Expected Call Sequence  */
            #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
                    EXPECTED_CALLS("RB_performSWResetWithBootBlock4OEM#SWReset");
            #else
                    EXPECTED_CALLS("");
            #endif
                            /* Call SUT */
                            dcom_SetProgConditions();

                            /* Test step checks */
            #if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
                            CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted, DCOM_REQPROGREQUESTINVERTED);
            #if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
                            CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
            #else
                            CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
            #endif
            #endif
                            END_CALLS();
                        END_STEP();
            }
    END_TEST();
}}

#else

#if (DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_DcmGetStoreType(int doIt){
if (doIt) {

    START_TEST("47778: [MMP2.11]UTC_rrdcom_MB_Reprogramming_DcmAppl_DcmGetStoreType",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47778");

		START_STEP("1_NTS", true);
		{
			uint8 dataBootType_u8 = 0x00;
			uint8 SID = 0x00;
			uint8 retVal = DCM_NOTVALID_TYPE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retVal = DcmAppl_DcmGetStoreType(dataBootType_u8,  SID);

		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
			CHECK_U_INT(retVal, DCM_WARMRESPONSE_TYPE);
		#else
			CHECK_U_INT(retVal, DCM_NOTVALID_TYPE);
		#endif
			END_CALLS();
		END_STEP();
		}
    END_TEST();
}}

void ut_DcmAppl_Switch_DcmExecuteDscReset(int doIt){
if (doIt) {

    START_TEST("47779: [MMP2.11]UTC_DcmAppl_Switch_DcmExecuteDscReset",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47779");

		START_STEP("1_NTS", true);
		{
		uint8 SessionLevel_u8 = 0x00;
		rba_DcmPma_PlantModeStatus_b = FALSE;

        /* Expected Call Sequence  */
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
        EXPECTED_CALLS("RB_performSWResetWithBootBlock4OEM#SWReset");
		#else
        EXPECTED_CALLS("");
		#endif

            /* Call SUT */
        DcmAppl_Switch_DcmExecuteDscReset(SessionLevel_u8);

        END_CALLS();
		END_STEP();
		}

		START_STEP("2_NTS", true);
		{
		uint8 SessionLevel_u8 = 0x00;
		rba_DcmPma_PlantModeStatus_b = TRUE;

		        /* Expected Call Sequence  */
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
		EXPECTED_CALLS("");
        #else
        EXPECTED_CALLS("");
		#endif

		            /* Call SUT */
		DcmAppl_Switch_DcmExecuteDscReset(SessionLevel_u8);

		END_CALLS();
	END_STEP();
		}
	END_TEST();
}}

void ut_Dcm_SetProgConditions(int doIt){
if (doIt) {

    START_TEST("47782: [MMP2.11]UTC_Dcm_SetProgConditions",
               " https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47782");

       Dcm_OpStatusType OpStatus = 0x00;
       Dcm_ProgConditionsType *ProgConditions = 0x00;
       Std_ReturnType retVal = E_NOT_OK;

    START_STEP("1_NTS", true);
    {
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
		ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted = 0x55;
		ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = 0x55;
#endif

#if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
		dcom_Requested_Tester = DCOM_SECOND_TESTER;
#endif
        /* Expected Call Sequence  */
        EXPECTED_CALLS("");

            /* Call SUT */
            retVal = Dcm_SetProgConditions(OpStatus, ProgConditions);

            /* Test case checks */
        CHECK_U_INT(retVal, E_OK);
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted, DCOM_REQPROGREQUESTINVERTED);
#if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION_2NDTESTER);
#elif
        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
#endif
#endif
        END_CALLS();
		END_STEP();
    }

		START_STEP("2_NTS", true);
		{
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
				ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted = 0x55;
				ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = 0x55;
		#endif

		#if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
				dcom_Requested_Tester = DCOM_FIRST_TESTER;
		#endif

		        /* Expected Call Sequence  */
		        EXPECTED_CALLS("");

		            /* Call SUT */
		            retVal = Dcm_SetProgConditions(OpStatus, ProgConditions);

		            /* Test case checks */
		        CHECK_U_INT(retVal, E_OK);
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
		        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Start_Request_Inverted, DCOM_REQPROGREQUESTINVERTED);
		#if (RBFS_DcomSecondTesterSupport == RBFS_DcomSecondTesterSupport_ON)
		        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
		#elif
		        CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason, DCOM_PROGRAMMINGSESSION);
		#endif
		#endif
		        END_CALLS();
				END_STEP();
		}
	END_TEST();
}}
#endif

#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
void ut_Dcm_GetProgConditions(int doIt){
if (doIt) {

    START_TEST("47781: [MMP2.11]UTC_rrdcom_MB_Reprogramming_Dcm_GetProgConditions",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47781");

			Dcm_ProgConditionsType ProgConditions1 = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0,0,0,0x55,0x55,0x55,0x55,0x55,0x55};
		    Dcm_ProgConditionsType *ProgConditions = &ProgConditions1;
			Dcm_ProgConditionsType expected_ProgConditions = {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55,0,0,0,0x55,0x55,0x55,0x55,0x55,0x55};

           START_STEP("1_NTS", true);
           {
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
			ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = 0;
#endif
			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			Dcm_EcuStartModeType retVal = Dcm_GetProgConditions(ProgConditions);

			CHECK_U_INT(retVal, DCM_COLD_START);
			CHECK_MEMORY("Conditions", ProgConditions,&expected_ProgConditions,sizeof(expected_ProgConditions));

			END_CALLS();
		END_STEP();
           }

		START_STEP("2_NTS", true);
		{
			ProgConditions->ReqResLen = 0x00;
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
			ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = DCOM_DEFAULTSESSION;
#endif
			expected_ProgConditions.ProtocolId       = DCM_SUPPLIER_1;
			expected_ProgConditions.TesterSourceAddr  = 0xEF8;
			expected_ProgConditions.SessionLevel     = 0x01;
			expected_ProgConditions.Sid              = 0x50;
			expected_ProgConditions.SubFncId         = 0x01;
			expected_ProgConditions.StoreType        = DCM_WARMRESPONSE_TYPE;
			expected_ProgConditions.ApplUpdated      = TRUE;
			expected_ProgConditions.ResponseRequired = TRUE;
			uint16 dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000);
			expected_ProgConditions.ReqResBuf[0] = (uint8)(dataTimingValue_u16 >> 8);
			expected_ProgConditions.ReqResBuf[1] = (uint8)(dataTimingValue_u16 & 0x00ff);

			dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000);
			expected_ProgConditions.ReqResBuf[2] = (uint8)(dataTimingValue_u16 >> 8);
			expected_ProgConditions.ReqResBuf[3] = (uint8)(dataTimingValue_u16 & 0x00ff);
			expected_ProgConditions.ReqResLen = 0x6;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

				/* Call SUT */
				Dcm_EcuStartModeType retVal = Dcm_GetProgConditions(ProgConditions);

				/* Test Step Checks */
			CHECK_U_INT(retVal, DCM_WARM_START);
			CHECK_MEMORY("Conditions", ProgConditions,&expected_ProgConditions,sizeof(expected_ProgConditions));

			END_CALLS();
		END_STEP();
		}

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		START_STEP("3_NTS", true);
		{
					ProgConditions->ReqResLen = 0x00;
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
					ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = DCOM_DEFAULTSESSION_2NDTESTER;
		#endif

					expected_ProgConditions.ProtocolId       = DCM_SUPPLIER_2;
					expected_ProgConditions.TesterSourceAddr  = 0xF0D;
					expected_ProgConditions.SessionLevel     = 0x01;
					expected_ProgConditions.Sid              = 0x50;
					expected_ProgConditions.SubFncId         = 0x01;
					expected_ProgConditions.StoreType        = DCM_WARMRESPONSE_TYPE;
					expected_ProgConditions.ApplUpdated      = TRUE;
					expected_ProgConditions.ResponseRequired = TRUE;
					uint16 dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000);
					expected_ProgConditions.ReqResBuf[0] = (uint8)(dataTimingValue_u16 >> 8);
					expected_ProgConditions.ReqResBuf[1] = (uint8)(dataTimingValue_u16 & 0x00ff);

					dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000);
					expected_ProgConditions.ReqResBuf[2] = (uint8)(dataTimingValue_u16 >> 8);
					expected_ProgConditions.ReqResBuf[3] = (uint8)(dataTimingValue_u16 & 0x00ff);
					expected_ProgConditions.ReqResLen = 0x6;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

						/* Call SUT */
						Dcm_EcuStartModeType retVal = Dcm_GetProgConditions(ProgConditions);

						/* Test Step Checks */
					CHECK_U_INT(retVal, DCM_WARM_START);
					CHECK_MEMORY("Conditions", ProgConditions,&expected_ProgConditions,sizeof(expected_ProgConditions));

					END_CALLS();
				END_STEP();
		}
#endif

		START_STEP("4_NTS", true);
		{
			ProgConditions->ReqResLen = 0x00;
#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
			ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = DCOM_HARDRESET;
#endif
			expected_ProgConditions.ProtocolId       = DCM_SUPPLIER_1;
			expected_ProgConditions.TesterSourceAddr = 0xEF8;
			expected_ProgConditions.SessionLevel     = 0x01;
			expected_ProgConditions.Sid              = 0x51;
			expected_ProgConditions.SubFncId         = 0x01;
			expected_ProgConditions.ReqResLen        = 0x2;
			expected_ProgConditions.StoreType        = DCM_WARMRESPONSE_TYPE;
			expected_ProgConditions.ApplUpdated      = TRUE;
			expected_ProgConditions.ResponseRequired = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			Dcm_EcuStartModeType retVal = Dcm_GetProgConditions(ProgConditions);

			/* Test Step Checks */
			CHECK_U_INT(retVal, DCM_WARM_START);
			CHECK_MEMORY("Conditions", ProgConditions,&expected_ProgConditions,sizeof(expected_ProgConditions));

			END_CALLS();
		END_STEP();
		}

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		START_STEP("5_NTS", true);
		{
					ProgConditions->ReqResLen = 0x00;
		#if (RBFS_OEMBootloader == RBFS_OEMBootloader_Yes)
					ACCESS_VARIABLE(dcom_MB_Reprogramming, DcmAppl_BackUp_RAM).Bldr_Reset_Reason = DCOM_HARDRESET_2NDTESTER;
		#endif
					expected_ProgConditions.ProtocolId       = DCM_SUPPLIER_2;
					expected_ProgConditions.TesterSourceAddr = 0xF0D;
					expected_ProgConditions.SessionLevel     = 0x01;
					expected_ProgConditions.Sid              = 0x51;
					expected_ProgConditions.SubFncId         = 0x01;
					expected_ProgConditions.ReqResLen        = 0x2;
					expected_ProgConditions.StoreType        = DCM_WARMRESPONSE_TYPE;
					expected_ProgConditions.ApplUpdated      = TRUE;
					expected_ProgConditions.ResponseRequired = TRUE;

					/* Expected Call Sequence  */
					EXPECTED_CALLS("");

					/* Call SUT */
					Dcm_EcuStartModeType retVal = Dcm_GetProgConditions(ProgConditions);

					/* Test Step Checks */
					CHECK_U_INT(retVal, DCM_WARM_START);
					CHECK_MEMORY("Conditions", ProgConditions,&expected_ProgConditions,sizeof(expected_ProgConditions));

					END_CALLS();
				END_STEP();
		}
#endif
	END_TEST();
}}
#endif
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RB_performSWResetWithBootBlock4OEM */
void RB_performSWResetWithBootBlock4OEM(){
    REGISTER_CALL("RB_performSWResetWithBootBlock4OEM");

    IF_INSTANCE("SWReset") {
            return;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
