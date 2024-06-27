/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_SigChain_TCOS.c
 *    Author: FDI2BRG
 *    Generated on: 18-May-2022 08:57:06
 *    Generated from: rbl_SigChain_TCOS.c
 *    Project: MMP2
 *    Software: ASW
 *    Tester: FDI2BRG
 *    Version: 2.0
 *    Last update: 25/07/2022
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/


#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_priv.h"

#include <cantpp.h>  /* Cantata Directives */

/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void rbl_SigChain_TCOS(rbl_ImuStdTypes_ImuSignalSet_t * signalSet);
extern void ACCESS_FUNCTION_rbl_SigChain_TCOS_rbl_SigChain_addSnvty(float32 * value, sint16 temp, const sint16 * valArray);
extern void ACCESS_FUNCTION_rbl_SigChain_TCOS_rbl_SigChain_addOffset(float32 * value, sint16 temp, const sint16 * valArray);
void RBSYS_EnterCommonLock_intern();
void RBSYS_ExitCommonLock_intern();
void RBSYS_EnterCorelocalIntlock_intern();
void RBSYS_ExitCorelocalIntlock_intern();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
void RBSYS_EnterCorelocalIntlockSysfast_intern();
void RBSYS_ExitCorelocalIntlockSysfast_intern();
sint16 Ifx_IntIpoCur_s16_s16(sint16 Xin, sint16 N, const sint16 * X_array, const sint16 * Val_array);

/* Global data */
extern sint16 rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
extern sint16 rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
extern sint16 rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];
extern sint16 rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

float32  global_value;
sint16  global_valArray;
sint16 global_temp;
float32 offset;
float32 Snvty;
float32  expected_global_value;
sint16  expected_global_valArray;
sint16 expected_global_temp;
rbl_ImuStdTypes_ImuSignalSet_t  global_signalSet;
rbl_ImuStdTypes_ImuSignalSet_t  expected_global_signalSet;

int axis = 0;
int red = 0;

static const sint16 rbl_SigChain_TCO[RBL_SIGCHAIN_TCOPNTS] = {-20000,-18000,-17000,-16000,-15000,-14000,-13000,-12000,-11000,-10000,-9000,-8000,-7000,-6000,-5000,-4000,-3000,-2000,-1000,0,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,11000,15000};
static const sint16 rbl_SigChain_TCS[RBL_SIGCHAIN_TCSPNTS] = {-20000,-18000,-15800,-13600,-11400,-9200,-7000,-4800,-2600,-400,1800,4000,6200,8400,10600,15000};

typedef struct rbl_SigChain_TCOS_av_struct
{
	const sint16(* ref_rbl_SigChain_TCO)[32];
	const sint16(* ref_rbl_SigChain_TCS)[16];
} rbl_SigChain_TCOS_av_struct;
extern rbl_SigChain_TCOS_av_struct av_rbl_SigChain_TCOS;

/* Expected variables for global data */
sint16 expected_rbl_SigChain_TCOAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCOPNTS];
sint16 expected_rbl_SigChain_TCSAcc[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHAIN_TCSPNTS];
sint16 expected_rbl_SigChain_TCORate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCOPNTS];
sint16 expected_rbl_SigChain_TCSRate[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHAIN_TCSPNTS];

typedef struct expected_rbl_SigChain_TCOS_av_struct
{
	sint16 ref_rbl_SigChain_TCO[32];
	sint16 ref_rbl_SigChain_TCS[16];
} expected_rbl_SigChain_TCOS_av_struct;
expected_rbl_SigChain_TCOS_av_struct expected_av_rbl_SigChain_TCOS;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data()
{
    INITIALISE(rbl_SigChain_TCOAcc);
    INITIALISE(rbl_SigChain_TCSAcc);
    INITIALISE(rbl_SigChain_TCORate);
    INITIALISE(rbl_SigChain_TCSRate);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data()
{
    COPY_TO_EXPECTED(rbl_SigChain_TCOAcc, expected_rbl_SigChain_TCOAcc);
    COPY_TO_EXPECTED(rbl_SigChain_TCSAcc, expected_rbl_SigChain_TCSAcc);
    COPY_TO_EXPECTED(rbl_SigChain_TCORate, expected_rbl_SigChain_TCORate);
    COPY_TO_EXPECTED(rbl_SigChain_TCSRate, expected_rbl_SigChain_TCSRate);
}

/* This function checks global data against the expected values. */
static void check_global_data()
{
    CHECK_MEMORY("rbl_SigChain_TCOAcc", rbl_SigChain_TCOAcc, expected_rbl_SigChain_TCOAcc, sizeof(expected_rbl_SigChain_TCOAcc));
    CHECK_MEMORY("rbl_SigChain_TCSAcc", rbl_SigChain_TCSAcc, expected_rbl_SigChain_TCSAcc, sizeof(expected_rbl_SigChain_TCSAcc));
    CHECK_MEMORY("rbl_SigChain_TCORate", rbl_SigChain_TCORate, expected_rbl_SigChain_TCORate, sizeof(expected_rbl_SigChain_TCORate));
    CHECK_MEMORY("rbl_SigChain_TCSRate", rbl_SigChain_TCSRate, expected_rbl_SigChain_TCSRate, sizeof(expected_rbl_SigChain_TCSRate));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_SigChain_TCOS(int);
void ut_rbl_SigChain_addSnvty(int);
void ut_rbl_SigChain_addOffset(int);

/*****************************************************************************/
/* Coverage Analysis                                                         */
/*****************************************************************************/
/* Coverage Rule Set: ISO26262-6 2011 ASIL D unit level (HR) */
static void rule_set(char* cppca_sut, char* cppca_context)
{
    START_TEST("COVERAGE RULE SET",
               "ISO26262-6 2011 ASIL D unit level (HR)");
#ifdef CANTPP_SUBSET_DEFERRED_ANALYSIS
    ut_SCRIPT_WARNING("Coverage Rule Set ignored in deferred analysis mode\n");
#elif CANTPP_COVERAGE_INSTRUMENTATION_DISABLED
    ut_SCRIPT_WARNING("Coverage Instrumentation has been disabled\n");
#elif CANTPP_INSTRUMENTATION_DISABLED
    ut_SCRIPT_WARNING("Instrumentation has been disabled\n");
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
    OPEN_LOG("ut_rbl_SigChain_TCOS.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_TCOS", true);

    WRITE_LOG(" * ------------------- TEST SUITE OF rbl_SigChain_TCOS -------------------*", cppth_ll_minimal,true);
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
    ut_rbl_SigChain_TCOS(1);
    ut_rbl_SigChain_addSnvty(1);
    ut_rbl_SigChain_addOffset(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_TCOS.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/


void ut_rbl_SigChain_TCOS(int doIt)
{
	if (doIt)
	{
		initialise_global_data();
		initialise_expected_global_data();


		START_TEST("47507: [MMP2.11]UTC_rbl_SigChain_TCOS",
				"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47507");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			for(axis= 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					global_signalSet.acc[axis][red].smx = 0;
					expected_global_signalSet.acc[axis][red].smx = global_signalSet.acc[axis][red].smx;

					global_signalSet.temp[global_signalSet.acc[axis][red].smx].status = 1;
					expected_global_signalSet.temp[global_signalSet.acc[axis][red].smx].status = global_signalSet.temp[global_signalSet.acc[axis][red].smx].status;

					global_signalSet.acc[axis][red].status = 1;
					expected_global_signalSet.acc[axis][red].status = global_signalSet.acc[axis][red].status | global_signalSet.temp[global_signalSet.acc[axis][red].smx].status;
				}

				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					global_signalSet.rate[axis][red].smx = 0;
					expected_global_signalSet.rate[axis][red].smx = global_signalSet.rate[axis][red].smx;

					global_signalSet.temp[global_signalSet.rate[axis][red].smx].status = 1;
					expected_global_signalSet.temp[global_signalSet.rate[axis][red].smx].status = global_signalSet.temp[global_signalSet.rate[axis][red].smx].status;

					global_signalSet.rate[axis][red].status = 1;
					expected_global_signalSet.rate[axis][red].status = global_signalSet.rate[axis][red].status | global_signalSet.temp[global_signalSet.rate[axis][red].smx].status;
				}
			}


			// EXPECTED CALLS
			EXPECTED_CALLS("\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_1\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_1\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_2\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_2\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_3\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_3\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_4\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_4\
					\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_5\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_5\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_6\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_6\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_7\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_7\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_8\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_8\
					\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_9\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_9\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_10\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_10\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_11\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_11\
					rbl_SigChain_addOffset#TCOS_addOffset_TS1_12\
					rbl_SigChain_addSnvty#TCOS_addSnvty_TS1_12\
					");

			// SUT
			rbl_SigChain_TCOS(&global_signalSet);

			// EXPECTED CALLS
			check_global_data();

			for(axis= 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					CHECK_U_INT(global_signalSet.acc[axis][red].smx , expected_global_signalSet.acc[axis][red].smx);
					CHECK_U_INT(global_signalSet.temp[global_signalSet.acc[axis][red].smx].status , expected_global_signalSet.temp[global_signalSet.acc[axis][red].smx].status);
					CHECK_U_INT(global_signalSet.acc[axis][red].status , expected_global_signalSet.acc[axis][red].status);
				}

				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					CHECK_U_INT(global_signalSet.rate[axis][red].smx , expected_global_signalSet.rate[axis][red].smx);
					CHECK_U_INT(global_signalSet.temp[global_signalSet.rate[axis][red].smx].status , expected_global_signalSet.temp[global_signalSet.rate[axis][red].smx].status);
					CHECK_U_INT(global_signalSet.rate[axis][red].status , expected_global_signalSet.rate[axis][red].status);
				}
			}

			END_CALLS();
			END_STEP();

		}


		START_STEP("2_NTS", true);
		{
			// INITIAL CONDITIONS
			for(axis= 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					global_signalSet.acc[axis][red].smx = 7;
					expected_global_signalSet.acc[axis][red].smx = global_signalSet.acc[axis][red].smx;
				}

				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					global_signalSet.rate[axis][red].smx = 7;
					expected_global_signalSet.rate[axis][red].smx = global_signalSet.rate[axis][red].smx;
				}
			}

			// EXPECTED CALLS
			EXPECT_CALL("","","");

			// SUT
			rbl_SigChain_TCOS(&global_signalSet);

			// EXPECTED RESULTS
			check_global_data();

			for(axis= 0; axis < RBL_IMUSTDTYPES_AXIS_NO; axis++)
			{
				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; red++)
				{
					CHECK_U_INT(global_signalSet.acc[axis][red].smx , expected_global_signalSet.acc[axis][red].smx);
				}

				for(red = 0; red < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; red++)
				{
					CHECK_U_INT(global_signalSet.rate[axis][red].smx , expected_global_signalSet.rate[axis][red].smx);
				}
			}

			END_CALLS();
			END_STEP();

		}

		END_TEST();
	}
}

void ut_rbl_SigChain_addSnvty(int doIt)
{
	if (doIt)
	{
		initialise_global_data();
		initialise_expected_global_data();

		START_TEST("47508: [MMP2.11]UTC_rbl_SigChain_addSnvty",
				"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47508");

		START_STEP("1_NTS", true);
		{
			// INITIAL CONDITIONS
			global_value = 0;
			expected_global_value = global_value * ((Snvty * RBL_SIGCHAIN_FACSVNTY) + 1.0f);

			global_temp = 0;
			expected_global_temp = global_temp;

			global_valArray = 0;
			expected_global_valArray = global_valArray;

			// EXPECTED CALLS
			EXPECT_CALL("Ifx_IntIpoCur_s16_s16", "1", "ut_rbl_SigChain_addSnvty_step1_call1");

			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_TCOS, rbl_SigChain_addSnvty)( &global_value, global_temp, global_valArray);

			// EXPECTED RESULTS
			check_global_data();
			CHECK_DOUBLE(global_value, expected_global_value );
			CHECK_DOUBLE(global_temp, expected_global_temp );
			CHECK_DOUBLE(global_valArray, expected_global_valArray );

			END_CALLS();
			END_STEP();

		}

		END_TEST();
	}
}

void ut_rbl_SigChain_addOffset(int doIt)
{
	if (doIt)
	{

		initialise_global_data();
		initialise_expected_global_data();

		START_TEST("47509: [MMP2.11]UTC_rbl_SigChain_addOffset",
				"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47509");

		START_STEP("1_NTS", true);
		{

			// INITIAL CONDITIONS
			global_value = 0;
			expected_global_value = global_value - (1 * RBL_SIGCHAIN_FACOFFSET);

			global_temp = 0;
			expected_global_temp = global_temp;

			global_valArray = 0;
			expected_global_valArray = global_valArray - (offset * RBL_SIGCHAIN_FACOFFSET);

			// EXPECTED CALLS
			EXPECT_CALL("Ifx_IntIpoCur_s16_s16", "1", "ut_rbl_SigChain_addOffset_step1_call1");

			// SUT
			ACCESS_FUNCTION(rbl_SigChain_TCOS, rbl_SigChain_addOffset)( &global_value, global_temp, global_valArray);

			// EXPECTED RESULTS
			CHECK_DOUBLE(global_value, expected_global_value );
			CHECK_DOUBLE(global_temp, expected_global_temp );
			CHECK_DOUBLE(global_valArray, expected_global_valArray );

			check_global_data();

			END_CALLS();
			END_STEP();
		}

		END_TEST();
	}
}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSYS_EnterCommonLock_intern */
void RBSYS_EnterCommonLock_intern()
{
    REGISTER_CALL("RBSYS_EnterCommonLock_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLock_intern */
void RBSYS_ExitCommonLock_intern()
{
    REGISTER_CALL("RBSYS_ExitCommonLock_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCorelocalIntlock_intern */
void RBSYS_EnterCorelocalIntlock_intern()
{
    REGISTER_CALL("RBSYS_EnterCorelocalIntlock_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlock_intern */
void RBSYS_ExitCorelocalIntlock_intern()
{
    REGISTER_CALL("RBSYS_ExitCorelocalIntlock_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCommonLockSysfast_intern */
void RBSYS_EnterCommonLockSysfast_intern()
{
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLockSysfast_intern */
void RBSYS_ExitCommonLockSysfast_intern()
{
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_EnterCorelocalIntlockSysfast_intern */
void RBSYS_EnterCorelocalIntlockSysfast_intern()
{
    REGISTER_CALL("RBSYS_EnterCorelocalIntlockSysfast_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCorelocalIntlockSysfast_intern */
void RBSYS_ExitCorelocalIntlockSysfast_intern()
{
    REGISTER_CALL("RBSYS_ExitCorelocalIntlockSysfast_intern");

    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function Ifx_IntIpoCur_s16_s16 */
sint16 Ifx_IntIpoCur_s16_s16(sint16 Xin,
                             sint16 N,
                             const sint16 * X_array,
                             const sint16 * Val_array)
{
    REGISTER_CALL("Ifx_IntIpoCur_s16_s16");

    IF_INSTANCE("ut_rbl_SigChain_addSnvty_step1_call1")
    {
    	CHECK_S_INT(Xin , global_temp);
    	CHECK_S_INT(N , RBL_SIGCHAIN_TCSPNTS);

    	for(int i=0; i<RBL_SIGCHAIN_TCSPNTS; i++ )
    	{ CHECK_S_INT(X_array[i] , rbl_SigChain_TCS[i]);}

    	CHECK_S_INT(Val_array , global_valArray);

    	Snvty = 1;

        return Snvty;
    }

    IF_INSTANCE("ut_rbl_SigChain_addOffset_step1_call1")
    {
    	CHECK_S_INT(Xin , global_temp);
    	CHECK_S_INT(N , RBL_SIGCHAIN_TCOPNTS);

    	for(int i=0; i<RBL_SIGCHAIN_TCOPNTS; i++ )
    	{ CHECK_S_INT(X_array[i] , rbl_SigChain_TCO[i]);}

    	CHECK_S_INT(Val_array , global_valArray);

    	offset = 1;

        return offset;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChain_addOffset */
int BEFORE_rbl_SigChain_addOffset(float32 * value,
                                  sint16 temp,
                                  const sint16 * valArray)
{
    REGISTER_CALL("rbl_SigChain_addOffset");

    IF_INSTANCE("TCOS_addOffset_TS1_1")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[0][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][0].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[0][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_2")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[0][1].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][1].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[0][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_3")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[0][2].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][2].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[0][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_4")
    {
    	CHECK_U_INT(value, &(global_signalSet.rate[0][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[0][0].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCORate[0][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_5")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[1][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][0].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[1][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_6")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[1][1].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][1].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[1][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_7")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[1][2].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][2].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[1][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_8")
    {
    	CHECK_U_INT(value, &(global_signalSet.rate[1][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[1][0].smx].value));
    	CHECK_U_INT(valArray , &rbl_SigChain_TCORate[1][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_9")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[2][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][0].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[2][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_10")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[2][1].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][1].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[2][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_11")
    {
    	CHECK_U_INT(value, &(global_signalSet.acc[2][2].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][2].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCOAcc[2][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_12")
    {
    	CHECK_U_INT(value, &(global_signalSet.rate[2][0].value));
    	CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[2][0].smx].value));
    	CHECK_U_INT(valArray, &rbl_SigChain_TCORate[2][0][0]);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_addOffset */
void AFTER_rbl_SigChain_addOffset(struct cppsm_void_return cppsm_dummy,
                                  float32 * value,
                                  sint16 temp,
                                  const sint16 * valArray)
{
    IF_INSTANCE("default")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_addOffset */
void REPLACE_rbl_SigChain_addOffset(float32 * value,
                                    sint16 temp,
                                    const sint16 * valArray)
{

	IF_INSTANCE("default")
	{
        return;
	}


    IF_INSTANCE("TCOS_addOffset_TS1_1")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_2")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_3")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_4")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_5")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_6")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_7")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_8")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_9")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_10")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_11")
    {
        return;
    }

    IF_INSTANCE("TCOS_addOffset_TS1_12")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_addSnvty */
int BEFORE_rbl_SigChain_addSnvty(float32 * value,
                                 sint16 temp,
                                 const sint16 * valArray)
{
    REGISTER_CALL("rbl_SigChain_addSnvty");

    IF_INSTANCE("default")
    {

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_1")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[0][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[0][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_2")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[0][1].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][1].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[0][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_3")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[0][2].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[0][2].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[0][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_4")
    {
		CHECK_U_INT(value, &(global_signalSet.rate[0][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[0][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSRate[0][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_5")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[1][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[1][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_6")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[1][1].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][1].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[1][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_7")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[1][2].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[1][2].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[1][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_8")
    {
		CHECK_U_INT(value, &(global_signalSet.rate[1][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[1][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSRate[1][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_9")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[2][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[2][0][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_10")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[2][1].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][1].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[2][1][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_11")
    {
		CHECK_U_INT(value, &(global_signalSet.acc[2][2].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.acc[2][2].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSAcc[2][2][0]);
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_12")
    {
		CHECK_U_INT(value, &(global_signalSet.rate[2][0].value));
		CHECK_S_INT(temp, (global_signalSet.temp[global_signalSet.rate[2][0].smx].value));
		CHECK_U_INT(valArray, &rbl_SigChain_TCSRate[2][0][0]);
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_addSnvty */
void AFTER_rbl_SigChain_addSnvty(struct cppsm_void_return cppsm_dummy,
                                 float32 * value,
                                 sint16 temp,
                                 const sint16 * valArray)
{
    IF_INSTANCE("default")
    {
        return;
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_addSnvty */
void REPLACE_rbl_SigChain_addSnvty(float32 * value,
                                   sint16 temp,
                                   const sint16 * valArray)
{

	IF_INSTANCE("default")
	{
		return ;
	}


    IF_INSTANCE("TCOS_addSnvty_TS1_1")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_2")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_3")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_4")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_5")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_6")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_7")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_8")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_9")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_10")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_11")
    {
        return ;
    }

    IF_INSTANCE("TCOS_addSnvty_TS1_12")
    {
        return ;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
