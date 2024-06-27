/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_EcuReset.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 15:22:31
 *    Generated from: dcom_EcuReset.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
#include "dcom_Common.h"
#include "rba_DcmPma.h"
#include "RB_SWReset.h"
#include "RBEMM_DCOM.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern Std_ReturnType ACCESS_FUNCTION_dcom_EcuReset_dcom_SoftResetRdy_check();
void RB_performSWResetSkipBootBlock();
boolean RBEMM_DCOM_SpecialServiceNvMWriteAll_Start();
boolean RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished();

/* Global data */
boolean rba_DcmPma_PlantModeStatus_b;
typedef struct dcom_EcuReset_av_struct { Std_ReturnType * ref_dcom_SoftResetstatus; } dcom_EcuReset_av_struct;
extern dcom_EcuReset_av_struct av_dcom_EcuReset;

/* Expected variables for global data */
boolean expected_rba_DcmPma_PlantModeStatus_b;
typedef struct expected_dcom_EcuReset_av_struct { Std_ReturnType ref_dcom_SoftResetstatus; } expected_dcom_EcuReset_av_struct;
expected_dcom_EcuReset_av_struct expected_av_dcom_EcuReset;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rba_DcmPma_PlantModeStatus_b);
    INITIALISE(ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus), ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_BOOLEAN(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
    CHECK_U_CHAR(ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus), ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus));
}

/* Prototypes for test functions */
void run_tests();
void ut_DcmAppl_Switch_DcmExecuteEcuReset(int);
void ut_dcom_SoftResetRdy_check(int);
void ut_DcmAppl_DcmEcuResetPreparation(int);

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
    OPEN_LOG("ut_dcom_EcuReset.ctr", false, 100);
    START_SCRIPT("dcom_EcuReset", true);

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
	 ut_DcmAppl_Switch_DcmExecuteEcuReset(1);
	 ut_dcom_SoftResetRdy_check(1);
	 ut_DcmAppl_DcmEcuResetPreparation(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_EcuReset.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_DcmAppl_Switch_DcmExecuteEcuReset(int doIt){
if (doIt) {

    START_TEST("46401: [MMP2.11]UTC_DcmAppl_Switch_DcmExecuteEcuReset",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46401");

            /* Test steps */
    		START_STEP("1_NTS", true);
    		{
    		uint8 ResetType_u8=DCOM_HARD_RESET;
    		rba_DcmPma_PlantModeStatus_b=FALSE;

            /* Expected Call Sequence  */
            EXPECTED_CALLS("RB_performSWResetSkipBootBlock#stub_RB_performSWResetSkipBootBlock");

            /* Call SUT */
            DcmAppl_Switch_DcmExecuteEcuReset(ResetType_u8);

        	/* Test case checks */
            CHECK_U_INT(ResetType_u8,DCOM_HARD_RESET);

            END_CALLS();
            END_STEP();
    		}
               START_STEP("2_NTS", true);
               {
               uint8 ResetType_u8=DCOM_SOFT_RESET;
       		   rba_DcmPma_PlantModeStatus_b=FALSE;

               /* Expected Call Sequence  */
               EXPECTED_CALLS("RB_performSWResetSkipBootBlock#stub_RB_performSWResetSkipBootBlock");

               /* Call SUT */
               DcmAppl_Switch_DcmExecuteEcuReset(ResetType_u8);

           	/* Test case checks */
               CHECK_U_INT(ResetType_u8,DCOM_SOFT_RESET);

           END_CALLS();
           END_STEP();
               }

              START_STEP("3_NTS", true);
              {
               uint8 ResetType_u8=DCOM_SOFT_RESET;
               rba_DcmPma_PlantModeStatus_b=TRUE;

              /* Expected Call Sequence  */
              EXPECTED_CALLS("RB_performSWResetSkipBootBlock#stub_RB_performSWResetSkipBootBlock");

              /* Call SUT */
              DcmAppl_Switch_DcmExecuteEcuReset(ResetType_u8);

              /* Test case checks */
              CHECK_U_INT(ResetType_u8,DCOM_SOFT_RESET);

              END_CALLS();
              END_STEP();
              }

         START_STEP("4_NTS", true);
         {
          uint8 ResetType_u8 = DCOM_HARD_RESET;
          rba_DcmPma_PlantModeStatus_b = TRUE;

          /* Expected Call Sequence  */
          EXPECTED_CALLS("");

          /* Call SUT */
          DcmAppl_Switch_DcmExecuteEcuReset(ResetType_u8);

          /* Test case checks */
          CHECK_U_INT(ResetType_u8,DCOM_HARD_RESET);

          END_CALLS();
          END_STEP();
          }

          START_STEP("5_NTS", true);
          {
           uint8 ResetType_u8 = 0;
           rba_DcmPma_PlantModeStatus_b = FALSE;

           /* Expected Call Sequence  */
           EXPECTED_CALLS("");

           /* Call SUT */
           DcmAppl_Switch_DcmExecuteEcuReset(ResetType_u8);

           END_CALLS();
           END_STEP();
           }
     END_TEST();
  }}

void ut_dcom_SoftResetRdy_check(int doIt){
if (doIt) {
START_TEST("46391: [MMP2.11]UTC_dcom_SoftResetRdy_check",
           "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46391");

				/* Test steps */
			START_STEP("1_NTS", true);
			{
			/*Test step data */
			Std_ReturnType returnValue;

            /* Set global data */
            initialise_global_data();
            ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus)= E_OK;

            /* Set expected values for global data checks */
            initialise_expected_global_data();

    	    ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus) = DCM_E_PENDING;

		   /* Expected Call Sequence  */
           EXPECTED_CALLS("RBEMM_DCOM_SpecialServiceNvMWriteAll_Start#stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_Start");

            /* Call SUT */
           returnValue = ACCESS_FUNCTION(dcom_EcuReset, dcom_SoftResetRdy_check)();
            /* Test case checks */
            CHECK_U_CHAR(returnValue, DCM_E_PENDING);

            /* Checks on global data */
            check_global_data();
        END_CALLS();
    END_STEP();
			}

			    START_STEP("2_NTS", true);
			    {
			   /*Test step data */
			   Std_ReturnType returnValue;

			   /* Set global data */
               initialise_global_data();
               ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus)= E_OK;

               /* Set expected values for global data checks */
               initialise_expected_global_data();

    	       ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus) = E_NOT_OK;
		      /* Expected Call Sequence  */
              EXPECTED_CALLS("RBEMM_DCOM_SpecialServiceNvMWriteAll_Start#stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_Start_01");

            /* Call SUT */
            returnValue =  ACCESS_FUNCTION(dcom_EcuReset, dcom_SoftResetRdy_check)();

            /* Test case checks */
           CHECK_U_CHAR(returnValue, E_NOT_OK);

            /* Checks on global data */
            check_global_data();
        END_CALLS();
    END_STEP();
			    }

	        START_STEP("3_NTS", true);
	        {
            /*Test step data */
			Std_ReturnType returnValue;

			/* Set global data */
            initialise_global_data();
            ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus)= DCM_E_PENDING;

           /* Set expected values for global data checks */
           initialise_expected_global_data();

    	   ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus) = E_OK;
		   /* Expected Call Sequence  */
           EXPECTED_CALLS("RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished#stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished");

            /* Call SUT */
            returnValue =  ACCESS_FUNCTION(dcom_EcuReset, dcom_SoftResetRdy_check)();

            /* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);

            /* Checks on global data */
            check_global_data();
        END_CALLS();
    END_STEP();
	        }

		    START_STEP("4_NTS", true);
		    {
            /*Test step data */
			Std_ReturnType returnValue;

			    /* Set global data */
            initialise_global_data();
            ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus)= DCM_E_PENDING;

            /* Set expected values for global data checks */
            initialise_expected_global_data();

    	    ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus) = DCM_E_PENDING;

		        /* Expected Call Sequence  */
            EXPECTED_CALLS("RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished#stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished_01");


            /* Call SUT */
           returnValue = ACCESS_FUNCTION(dcom_EcuReset, dcom_SoftResetRdy_check)();

           /* Test case checks */
            CHECK_U_CHAR(returnValue, DCM_E_PENDING);

            /* Checks on global data */
            check_global_data();
        END_CALLS();
    END_STEP();
		    }

	       START_STEP("5_NTS", true);
	       {
            /*Test step data */
			Std_ReturnType returnValue;

			/* Set global data */
            initialise_global_data();
            ACCESS_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus)= E_NOT_OK;

            /* Set expected values for global data checks */
            initialise_expected_global_data();

    	    ACCESS_EXPECTED_VARIABLE(dcom_EcuReset, dcom_SoftResetstatus) = E_NOT_OK;

		    /* Expected Call Sequence  */
           EXPECTED_CALLS("");

            /* Call SUT */
           returnValue =  ACCESS_FUNCTION(dcom_EcuReset, dcom_SoftResetRdy_check)();

            /* Test case checks */
            CHECK_U_CHAR(returnValue, E_NOT_OK);

            /* Checks on global data */
            check_global_data();
        END_CALLS();
    END_STEP();
	       }
 END_TEST();
}}

   void ut_DcmAppl_DcmEcuResetPreparation(int doIt){
   if (doIt) {
            START_TEST("46390: [MMP2.11]UTC_DcmAppl_DcmEcuResetPreparation_02",
       		            "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46390");
   				/* Test steps */
   			START_STEP("1_NTS", true);
   			{
   			/*Test step data */
   			Dcm_NegativeResponseCodeType buffer_code = 0x01;
   	        Dcm_NegativeResponseCodeType * ErrorCode = &buffer_code;
   	        uint8 ResetType = DCOM_SOFT_RESET ;
   	        Std_ReturnType returnValue = E_NOT_OK, Expected_returnValue = E_OK;

   	        /* Set global data */
            initialise_global_data();

            /* Set expected values for global data checks */
            initialise_expected_global_data();

   		     /* Expected Call Sequence  */
             EXPECTED_CALLS("dcom_SoftResetRdy_check#WRAPPER_dcom_SoftResetRdy_check_01");

             /* Call SUT */
             returnValue = DcmAppl_DcmEcuResetPreparation(ResetType, ErrorCode);

               /* Test case checks */
               CHECK_U_CHAR(returnValue, E_NOT_OK);
               CHECK_U_CHAR(* ErrorCode, DCOM_NO_ERROR);
               CHECK_U_CHAR(ResetType,DCOM_SOFT_RESET);
               /* Checks on global data */
               check_global_data();
           END_CALLS();
       END_STEP();
   			}

   		START_STEP("2_NTS", true);
   		{
   			/*Test step data */
   			Dcm_NegativeResponseCodeType buffer_code = 0x01;
   	        Dcm_NegativeResponseCodeType * ErrorCode = &buffer_code;
   	        uint8 ResetType = DCOM_HARD_RESET;
   	        Std_ReturnType returnValue = E_OK, Expected_returnValue = E_NOT_OK;

   	       /* Set global data */
           initialise_global_data();

           /* Set expected values for global data checks */
           initialise_expected_global_data();

   	       /* Expected Call Sequence  */
           EXPECTED_CALLS(" ");

           /* Call SUT */
           returnValue = DcmAppl_DcmEcuResetPreparation(ResetType, ErrorCode);

           /* Test case checks */
           CHECK_U_CHAR(returnValue, E_OK);
           CHECK_U_CHAR(* ErrorCode, DCOM_NO_ERROR);

          /* Checks on global data */
          check_global_data();
           END_CALLS();
       END_STEP();
   		}
   END_TEST();
   }}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RB_performSWResetSkipBootBlock */
void RB_performSWResetSkipBootBlock(){
    REGISTER_CALL("RB_performSWResetSkipBootBlock");

    IF_INSTANCE("stub_RB_performSWResetSkipBootBlock") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBEMM_DCOM_SpecialServiceNvMWriteAll_Start */
boolean RBEMM_DCOM_SpecialServiceNvMWriteAll_Start(){
    REGISTER_CALL("RBEMM_DCOM_SpecialServiceNvMWriteAll_Start");

    IF_INSTANCE("stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_Start") {
                  return 1;
              }
      IF_INSTANCE("stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_Start_01") {
                      return 0;
                  }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished */
boolean RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished(){
    REGISTER_CALL("RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished");

    IF_INSTANCE("stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished") {
                  return 1;
              }
      IF_INSTANCE("stub_RBEMM_DCOM_SpecialServiceNvMWriteAll_CheckIsFinished_01") {
                     return 0;
                 }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function dcom_SoftResetRdy_check */
int BEFORE_dcom_SoftResetRdy_check(){
    REGISTER_CALL("dcom_SoftResetRdy_check");

    IF_INSTANCE("WRAPPER_dcom_SoftResetRdy_check") {

               return REPLACE_WRAPPER;
           }
       IF_INSTANCE("WRAPPER_dcom_SoftResetRdy_check_01") {

                   return REPLACE_WRAPPER;
            }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function dcom_SoftResetRdy_check */
Std_ReturnType AFTER_dcom_SoftResetRdy_check(Std_ReturnType cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function dcom_SoftResetRdy_check */
Std_ReturnType REPLACE_dcom_SoftResetRdy_check(){

	IF_INSTANCE("WRAPPER_dcom_SoftResetRdy_check") {
   		        return E_OK;
   		    }
   	IF_INSTANCE("WRAPPER_dcom_SoftResetRdy_check_01") {
   		 	     return E_NOT_OK;
   		 	    }


	LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
