/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/

/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_ImuGenFunc_ErrCntrPub.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_SigFil.h"
#include "../../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Measure_SigFil.h"
#include "rbl_ImuCdd_Interfaces.h"
#include <math.h>

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
extern void rbl_SigChain_InitFilter2(const rbl_SigChain_FilterArray_t * filter, uint16 flush, float timestampdelay);
#endif
extern void rbl_SigChain_InitFilter(const rbl_SigChain_FilterArray_t * filter, uint16 flush, float timestampdelay);
extern void rbl_SigChainSigFil(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer, uint32 filterNumber);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_runFilterSteps(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer, const rbl_SigChain_FilData_t * data);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_UpdateFilTab(rbl_SigChain_FilTabs_t * tabs, float32 filVal);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_UpdateFilter(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw, const rbl_SigChain_FilData_t * data, rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_UpdateDerivation(rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_PhaseCorrection(rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil, const rbl_SigChain_FilData_t * data, const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet);
extern void ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_ImuSigFil_UpdateStatus(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer, const rbl_SigChain_FilData_t * data);
extern float ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_CalcSecOrdSctn(const rbl_SigChain_Filter_t * FilCoeff, rbl_SigChain_FilTabs_t * filTabsArray, float32 x);
extern uint8 ACCESS_FUNCTION_rbl_SigChain_SigFil_rbl_SigChain_debounce(uint8 mask, uint8 status, uint16 debounceSteps, uint16 * counter);
sint32 rbl_ImuCdd_Float2ticks(float32 timeInMicroseconds);
rbl_ImuCdd_State_t rbl_ImuCdd_GetCDDState();

/* Global data */
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal20Hz;
rbl_SigChain_FilterArray_t rbl_SigChain_FilVal45Hz;
rbl_SigChain_FilterArray_t rbl_SigChain_FilValNoFilter;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal20Hz;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal45Hz;
rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilValNoFilter;

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)

	/* Global data */
	typedef struct rbl_SigChain_SigFil_av_struct
	{
		const rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_SigChain_FilSigSetEmpty;
		rbl_SigChain_FilterArray_t * ref_rbl_SigChain_FilVal;
		uint16 * ref_rbl_SigChain_SigFilFlush;
		uint32 * ref_rbl_SigChain_TimeStampDelayTick;
		rbl_SigChain_FilterArray_t * ref_rbl_SigChain_FilVal2;
		uint16 * ref_rbl_SigChain_SigFilFlush2;
		uint32 * ref_rbl_SigChain_TimeStampDelayTick2;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccFlushCnt;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateFlushCnt;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccFlushCnt2;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateFlushCnt2;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccInitFlushCnt;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateInitFlushCnt;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccInitFlushCnt2;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateInitFlushCnt2;
		rbl_SigChain_RateFilTabsSteps_t * ref_rbl_SigChain_RateFilTabs;
		rbl_SigChain_AccFilTabsSteps_t * ref_rbl_SigChain_AccFilTabs;
		rbl_SigChain_RateFilTabsSteps_t * ref_rbl_SigChain_RateFilTabs2;
		rbl_SigChain_AccFilTabsSteps_t * ref_rbl_SigChain_AccFilTabs2;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RateDerFilTabs;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccDerFilTabs;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RateDerFilTabs2;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccDerFilTabs2;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RatePhaCorrnTabs;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccPhaCorrnTabs;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RatePhaCorrnTabs2;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccPhaCorrnTabs2;
		rbl_SigChain_FilData_t * ref_usedData;
		rbl_SigChain_FilData_t * ref_usedData2;
		const rbl_SigChain_Filter_t * ref_rbl_SigChain_DerFilCfg;
		const rbl_SigChain_Filter_t * ref_rbl_SigChain_PhaseCorrnCfg;
	} rbl_SigChain_SigFil_av_struct;
	extern rbl_SigChain_SigFil_av_struct av_rbl_SigChain_SigFil;

	/* Expected variables for global data */
	rbl_SigChain_FilterArray_t expected_rbl_SigChain_FilVal20Hz;
	typedef struct expected_rbl_SigChain_SigFil_av_struct
	{
		rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_SigChain_FilSigSetEmpty;
		rbl_SigChain_FilterArray_t ref_rbl_SigChain_FilVal;
		uint16 ref_rbl_SigChain_SigFilFlush;
		uint32 ref_rbl_SigChain_TimeStampDelayTick;
		rbl_SigChain_FilterArray_t ref_rbl_SigChain_FilVal2;
		uint16 ref_rbl_SigChain_SigFilFlush2;
		uint32 ref_rbl_SigChain_TimeStampDelayTick2;
		rbl_SigChain_AccFilCnt_t ref_rbl_SigChain_AccFlushCnt;
		rbl_SigChain_RateFilCnt_t ref_rbl_SigChain_RateFlushCnt;
		rbl_SigChain_AccFilCnt_t ref_rbl_SigChain_AccFlushCnt2;
		rbl_SigChain_RateFilCnt_t ref_rbl_SigChain_RateFlushCnt2;
		rbl_SigChain_AccFilCnt_t ref_rbl_SigChain_AccInitFlushCnt;
		rbl_SigChain_RateFilCnt_t ref_rbl_SigChain_RateInitFlushCnt;
		rbl_SigChain_AccFilCnt_t ref_rbl_SigChain_AccInitFlushCnt2;
		rbl_SigChain_RateFilCnt_t ref_rbl_SigChain_RateInitFlushCnt2;
		rbl_SigChain_RateFilTabsSteps_t ref_rbl_SigChain_RateFilTabs;
		rbl_SigChain_AccFilTabsSteps_t ref_rbl_SigChain_AccFilTabs;
		rbl_SigChain_RateFilTabsSteps_t ref_rbl_SigChain_RateFilTabs2;
		rbl_SigChain_AccFilTabsSteps_t ref_rbl_SigChain_AccFilTabs2;
		rbl_SigChain_RateFilTabs_t ref_rbl_SigChain_RateDerFilTabs;
		rbl_SigChain_AccFilTabs_t ref_rbl_SigChain_AccDerFilTabs;
		rbl_SigChain_RateFilTabs_t ref_rbl_SigChain_RateDerFilTabs2;
		rbl_SigChain_AccFilTabs_t ref_rbl_SigChain_AccDerFilTabs2;
		rbl_SigChain_RateFilTabs_t ref_rbl_SigChain_RatePhaCorrnTabs;
		rbl_SigChain_AccFilTabs_t ref_rbl_SigChain_AccPhaCorrnTabs;
		rbl_SigChain_RateFilTabs_t ref_rbl_SigChain_RatePhaCorrnTabs2;
		rbl_SigChain_AccFilTabs_t ref_rbl_SigChain_AccPhaCorrnTabs2;
		rbl_SigChain_FilData_t ref_usedData;
		rbl_SigChain_FilData_t ref_usedData2;
		rbl_SigChain_Filter_t ref_rbl_SigChain_DerFilCfg;
		rbl_SigChain_Filter_t ref_rbl_SigChain_PhaseCorrnCfg;
	} expected_rbl_SigChain_SigFil_av_struct;
	expected_rbl_SigChain_SigFil_av_struct expected_av_rbl_SigChain_SigFil;

#else

	/* Global data */
	typedef struct rbl_SigChain_SigFil_av_struct
	{
		const rbl_ImuStdTypes_ImuSignalSet_t * ref_rbl_SigChain_FilSigSetEmpty;
		rbl_SigChain_FilterArray_t * ref_rbl_SigChain_FilVal;
		uint16 * ref_rbl_SigChain_SigFilFlush;
		uint32 * ref_rbl_SigChain_TimeStampDelayTick;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccFlushCnt;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateFlushCnt;
		rbl_SigChain_AccFilCnt_t * ref_rbl_SigChain_AccInitFlushCnt;
		rbl_SigChain_RateFilCnt_t * ref_rbl_SigChain_RateInitFlushCnt;
		rbl_SigChain_RateFilTabsSteps_t * ref_rbl_SigChain_RateFilTabs;
		rbl_SigChain_AccFilTabsSteps_t * ref_rbl_SigChain_AccFilTabs;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RateDerFilTabs;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccDerFilTabs;
		rbl_SigChain_RateFilTabs_t * ref_rbl_SigChain_RatePhaCorrnTabs;
		rbl_SigChain_AccFilTabs_t * ref_rbl_SigChain_AccPhaCorrnTabs;
		rbl_SigChain_FilData_t * ref_usedData;
		const rbl_SigChain_Filter_t * ref_rbl_SigChain_DerFilCfg;
		const rbl_SigChain_Filter_t * ref_rbl_SigChain_PhaseCorrnCfg;
	} rbl_SigChain_SigFil_av_struct;
	extern rbl_SigChain_SigFil_av_struct av_rbl_SigChain_SigFil;

	/* Expected variables for global data */
	typedef struct expected_rbl_SigChain_SigFil_av_struct
	{
		rbl_ImuStdTypes_ImuSignalSet_t ref_rbl_SigChain_FilSigSetEmpty;
		rbl_SigChain_FilterArray_t ref_rbl_SigChain_FilVal;
		uint16 ref_rbl_SigChain_SigFilFlush;
		uint32 ref_rbl_SigChain_TimeStampDelayTick;
		rbl_SigChain_FilData_t ref_usedData;
		rbl_SigChain_Filter_t ref_rbl_SigChain_DerFilCfg;
		rbl_SigChain_Filter_t ref_rbl_SigChain_PhaseCorrnCfg;
	} expected_rbl_SigChain_SigFil_av_struct;
	expected_rbl_SigChain_SigFil_av_struct expected_av_rbl_SigChain_SigFil;

#endif

/* User variables */
rbl_ImuStdTypes_ImuSignalSet_t global_signalSetRaw, global_expected_signalSetRaw;
rbl_ImuStdTypes_ImuSignalSet_t global_signalSetFil, global_expected_signalSetFil;
rbl_ImuStdTypes_ImuSignalSet_t global_signalSetDer, global_expected_signalSetDer;
rbl_SigChain_FilData_t global_data, global_expected_data;
rbl_ImuStdTypes_ImuSignalSet_t global_tempSigSet, global_expected_tempSigSet;
uint8_t global_AccCounter = 1;
uint8_t global_RateCounter = 1;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal));
    INITIALISE(rbl_SigChain_FilVal20Hz);
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush));
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick));
    INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData));

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
	INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData2));
#endif

    INITIALISE(global_signalSetRaw);
    INITIALISE(global_signalSetFil);
    INITIALISE(global_signalSetDer);
    INITIALISE(global_data);
    INITIALISE(global_tempSigSet);
    global_AccCounter = 1;
    global_RateCounter = 1;
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal));
    COPY_TO_EXPECTED(rbl_SigChain_FilVal20Hz, expected_rbl_SigChain_FilVal20Hz);
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData));

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
	COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData2), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData2));
#endif

    COPY_TO_EXPECTED(global_signalSetRaw, global_expected_signalSetRaw);
    COPY_TO_EXPECTED(global_signalSetFil, global_expected_signalSetFil);
    COPY_TO_EXPECTED(global_signalSetDer, global_expected_signalSetDer);
    COPY_TO_EXPECTED(global_data, global_expected_data);
    COPY_TO_EXPECTED(global_tempSigSet, global_expected_tempSigSet);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal)", &ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal), &ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal)));
    CHECK_MEMORY("rbl_SigChain_FilVal20Hz", &rbl_SigChain_FilVal20Hz, &expected_rbl_SigChain_FilVal20Hz, sizeof(expected_rbl_SigChain_FilVal20Hz));
    CHECK_U_INT(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush));
    CHECK_U_INT(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick), ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick));
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData)", &ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData), &ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData)));

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
	CHECK_MEMORY("Checking variable usedData2", &ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData2), &ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData2), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, usedData2)));
#endif

	CHECK_MEMORY("Checking variable global_signalSetRaw", &global_signalSetRaw, &global_expected_signalSetRaw, sizeof(global_signalSetRaw));
	CHECK_MEMORY("Checking variable global_signalSetFil", &global_signalSetFil, &global_expected_signalSetFil, sizeof(global_signalSetFil));
	CHECK_MEMORY("Checking variable global_signalSetDer", &global_signalSetDer, &global_expected_signalSetDer, sizeof(global_signalSetDer));
    CHECK_MEMORY("Checking variable global_data", &global_data, &global_expected_data, sizeof(global_data));
    CHECK_MEMORY("Checking variable global_tempSigSet", &global_tempSigSet, &global_expected_tempSigSet, sizeof(global_tempSigSet));
}

/* Prototypes for test functions */
void run_tests();
#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
	void ut_rbl_SigChain_InitFilter2(int);
#endif
void ut_rbl_SigChain_InitFilter(int);
void ut_rbl_SigChainSigFil(int);
void ut_rbl_SigChain_runFilterSteps(int);
void ut_rbl_SigChain_UpdateFilTab(int);
void ut_rbl_SigChain_UpdateFilter(int);
void ut_rbl_SigChain_UpdateDerivation(int);
void ut_rbl_SigChain_PhaseCorrection(int);
void ut_rbl_ImuSigFil_UpdateStatus(int);
void ut_rbl_SigChain_CalcSecOrdSctn(int);
void ut_rbl_SigChain_debounce(int);

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
    OPEN_LOG("ut_rbl_SigChain_SigFil.ctr", false, 100);
    START_SCRIPT("rbl_SigChain_SigFil", true);

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
    ut_rbl_SigChain_InitFilter(1);

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
	ut_rbl_SigChain_InitFilter2(1);
#endif

    ut_rbl_SigChainSigFil(1);
    ut_rbl_SigChain_runFilterSteps(1);
    ut_rbl_SigChain_UpdateFilTab(1);
    ut_rbl_SigChain_UpdateFilter(1);
    ut_rbl_SigChain_UpdateDerivation(1);
    ut_rbl_SigChain_PhaseCorrection(1);
    ut_rbl_ImuSigFil_UpdateStatus(1);
    ut_rbl_SigChain_CalcSecOrdSctn(1);
    ut_rbl_SigChain_debounce(1);

    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_SigChain_SigFil.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_SigChain_InitFilter(int doIt)
{
	if (doIt)
	{
		rbl_SigChain_FilterArray_t filter, expected_filter;
		uint16 flush = 0;
		float timestampdelay = 0.0;


		START_TEST("49452: UTC_rbl_SigChain_InitFilter",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49452");


		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS

				// Filter coefficient
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal));
				// Filter flush time
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush));
				// Time stamp delay
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick));

				// Flush time
			flush = 13;					// "Random" value

				// Time stamp delay
			timestampdelay = 2.5;		// "Random" value

				// Filter coefficient - input
			INITIALISE(filter);
			expected_filter = filter;


			// EXPECTED RESULTS

			#if (RBFS_SigChainFilter == RBFS_SigChainFilter_20Hz)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal) = rbl_SigChain_FilVal20Hz;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush) = RBL_SIGCHAIN_SIGFIL20HZFLUSH;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) + 1;	 // Value returned by the stub

			#elif(RBFS_SigChainFilter==RBFS_SigChainFilter_45Hz)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal) = rbl_SigChain_FilVal45Hz;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush) = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) + 1;	 // Value returned by the stub

			#elif(RBFS_SigChainFilter==RBFS_SigChainFilter_NoFilter)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal) = rbl_SigChain_FilValNoFilter;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush) = RBL_SIGCHAIN_SIGFILNONEFLUSH;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) = 0;

			#elif(RBFS_SigChainFilter == RBFS_SigChainFilter_Nvm)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal) = *filter;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush) = flush;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) + 1;	 // Value returned by the stub

			#endif


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_ImuCdd_Float2ticks#InitFilter_Float2ticks;");


			// CALL SUT
			rbl_SigChain_InitFilter(&filter, flush, timestampdelay);


			// SUT CHECKS
			CHECK_MEMORY("Checking variable filter", &filter, &expected_filter, sizeof(filter));
			check_global_data();


			END_CALLS();
		END_STEP();
		}

#if(RBFS_SigChainFilter == RBFS_SigChainFilter_Nvm)

		// Scenario where the filter is supposed to be fetched from nvm but is actually NULL
		START_STEP("2_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Filter coefficient
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal);

				// Filter flush time
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush);

				// Time stamp delay
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick);


			// EXPECTED CALLS
			EXPECTED_CALLS("");


			// CALL SUT
			rbl_SigChain_InitFilter(NULL, flush, timestampdelay);


			// SUT CHECKS
			CHECK_MEMORY("Checking variable filter", &filter, &expected_filter, sizeof(filter));
			check_global_data();


			END_CALLS();
		END_STEP();
		}
#endif

		END_TEST();
	}
}

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
void ut_rbl_SigChain_InitFilter2(int doIt)
{
	if (doIt)
	{
		rbl_SigChain_FilterArray_t filter, expected_filter;
		uint16 flush = 0;
		float timestampdelay = 0.0;


		START_TEST("49453: UTC_rbl_SigChain_InitFilter2",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49453");


		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS

				// Filter coefficient
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2));
				// Filter flush time
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2));
				// Time stamp delay
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2));

				// Flush time
			flush = 13;					// "Random" value

				// Time stamp delay
			timestampdelay = 4.1;		// "Random" value

				// Filter coefficient - input
			INITIALISE(filter);
			expected_filter = filter;

			#if(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_45Hz)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2) = rbl_SigChain_FilVal45Hz;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2) = RBL_SIGCHAIN_SIGFIL45HZFLUSH;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) + 1;	 // Value returned by the stub

			#elif(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_Nvm)

					// Filter coefficient
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2) = *filter;
					// Filter flush time
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2) = flush;
					// Time stamp delay
				ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) + 1;	 // Value returned by the stub

			#endif


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_ImuCdd_Float2ticks#InitFilter2_Float2ticks;");


			// CALL SUT
			rbl_SigChain_InitFilter2(&filter, flush, timestampdelay);


			// SUT CHECKS
			CHECK_MEMORY("Checking variable filter", &filter, &expected_filter, sizeof(filter));
			check_global_data();


			END_CALLS();
		END_STEP();
		}

#if(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_Nvm)

		// Scenario where the filter is supposed to be fetched from nvm but is actually NULL
		START_STEP("2_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Filter coefficient
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilVal2);

				// Filter flush time
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_SigFilFlush2);

				// Time stamp delay
			INITIALISE(ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2));
			ACCESS_EXPECTED_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) = ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2);


			// EXPECTED CALLS
			EXPECTED_CALLS("");


			// CALL SUT
			rbl_SigChain_InitFilter2(NULL, flush, timestampdelay);


			// SUT CHECKS
			CHECK_MEMORY("Checking variable filter", &filter, &expected_filter, sizeof(filter));
			check_global_data();


			END_CALLS();
		END_STEP();
		}
#endif

		END_TEST();
	}
}
#endif

void ut_rbl_SigChainSigFil(int doIt)
{
	if (doIt)
	{
		int iterator_1 = 0, iterator_2 = 0;
		uint32 filterNumber = 0;

		START_TEST("47510: UTC_rbl_SigChainSigFil",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47510");

		// Fitler number = First filter
		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Filter number
			filterNumber = RBL_SIGCHAIN_FIRSTFILTER;	// First filter

				// Original signal set, filtered signal set, derived signal set
			for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
			{
				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; iterator_2++)
				{
					global_signalSetRaw.acc[iterator_1][iterator_2].value = -700;
					global_signalSetRaw.acc[iterator_1][iterator_2].status = 1;
					global_signalSetRaw.acc[iterator_1][iterator_2].smx = 1;

					global_signalSetFil.acc[iterator_1][iterator_2].value = 0;
					global_signalSetFil.acc[iterator_1][iterator_2].status = 1;
					global_signalSetFil.acc[iterator_1][iterator_2].smx = 1;

					global_signalSetDer.acc[iterator_1][iterator_2].value = 700;
					global_signalSetDer.acc[iterator_1][iterator_2].status = 1;
					global_signalSetDer.acc[iterator_1][iterator_2].smx = 1;

				}

				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; iterator_2++)
				{
					global_signalSetRaw.rate[iterator_1][iterator_2].value = 498;
					global_signalSetRaw.rate[iterator_1][iterator_2].status = 2;
					global_signalSetRaw.rate[iterator_1][iterator_2].smx = 2;

					global_signalSetFil.rate[iterator_1][iterator_2].value = -498;
					global_signalSetFil.rate[iterator_1][iterator_2].status = 2;
					global_signalSetFil.rate[iterator_1][iterator_2].smx = 2;

					global_signalSetDer.rate[iterator_1][iterator_2].value = 0;
					global_signalSetDer.rate[iterator_1][iterator_2].status = 2;
					global_signalSetDer.rate[iterator_1][iterator_2].smx = 2;
				}
			}

			for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; iterator_1++)
			{
				global_signalSetRaw.temp[iterator_1].value= 0;
				global_signalSetRaw.temp[iterator_1].status= 3;
				global_signalSetRaw.temp[iterator_1].smx= 3;

				global_signalSetFil.temp[iterator_1].value = -900;
				global_signalSetFil.temp[iterator_1].status = 3;
				global_signalSetFil.temp[iterator_1].smx = 3;

				global_signalSetDer.temp[iterator_1].value= 900;
				global_signalSetDer.temp[iterator_1].status= 3;
				global_signalSetDer.temp[iterator_1].smx= 3;
			}

			global_signalSetRaw.timeStamp = 7;
			global_signalSetFil.timeStamp = 8;
			global_signalSetDer.timeStamp = 9;

			global_expected_signalSetRaw = global_signalSetRaw;
			global_expected_signalSetFil = global_signalSetRaw;
			global_expected_signalSetDer = global_signalSetRaw;


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_SigChain_runFilterSteps#SigChainSigFil_runFilterSteps_TS1;");


			// CALL SUT
			rbl_SigChainSigFil(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, filterNumber);


			// SUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
		// Filter number = Second filter
		START_STEP("2_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Filter number
			filterNumber = RBL_SIGCHAIN_SECONDFILTER;	// Second filter

				// Original signal set, filtered signal set, derived signal set
			for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
			{
				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; iterator_2++)
				{
					global_signalSetRaw.acc[iterator_1][iterator_2].value = -700;
					global_signalSetRaw.acc[iterator_1][iterator_2].status = 1;
					global_signalSetRaw.acc[iterator_1][iterator_2].smx = 1;

					global_signalSetFil.acc[iterator_1][iterator_2].value = 0;
					global_signalSetFil.acc[iterator_1][iterator_2].status = 1;
					global_signalSetFil.acc[iterator_1][iterator_2].smx = 1;

					global_signalSetDer.acc[iterator_1][iterator_2].value = 700;
					global_signalSetDer.acc[iterator_1][iterator_2].status = 1;
					global_signalSetDer.acc[iterator_1][iterator_2].smx = 1;

				}

				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; iterator_2++)
				{
					global_signalSetRaw.rate[iterator_1][iterator_2].value = 498;
					global_signalSetRaw.rate[iterator_1][iterator_2].status = 2;
					global_signalSetRaw.rate[iterator_1][iterator_2].smx = 2;

					global_signalSetFil.rate[iterator_1][iterator_2].value = -498;
					global_signalSetFil.rate[iterator_1][iterator_2].status = 2;
					global_signalSetFil.rate[iterator_1][iterator_2].smx = 2;

					global_signalSetDer.rate[iterator_1][iterator_2].value = 0;
					global_signalSetDer.rate[iterator_1][iterator_2].status = 2;
					global_signalSetDer.rate[iterator_1][iterator_2].smx = 2;
				}
			}

			for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; iterator_1++)
			{
				global_signalSetRaw.temp[iterator_1].value= 0;
				global_signalSetRaw.temp[iterator_1].status= 3;
				global_signalSetRaw.temp[iterator_1].smx= 3;

				global_signalSetFil.temp[iterator_1].value = -900;
				global_signalSetFil.temp[iterator_1].status = 3;
				global_signalSetFil.temp[iterator_1].smx = 3;

				global_signalSetDer.temp[iterator_1].value= 900;
				global_signalSetDer.temp[iterator_1].status= 3;
				global_signalSetDer.temp[iterator_1].smx= 3;
			}

			global_signalSetRaw.timeStamp = 7;
			global_signalSetFil.timeStamp = 8;
			global_signalSetDer.timeStamp = 9;

			global_expected_signalSetRaw = global_signalSetRaw;
			global_expected_signalSetFil = global_signalSetRaw;
			global_expected_signalSetDer = global_signalSetRaw;


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_SigChain_runFilterSteps#SigChainSigFil_runFilterSteps_TS2;");


			// CALL SUT
			rbl_SigChainSigFil(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, filterNumber);


			// SUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}
#endif


	// Filter number = Invalid filter
	START_STEP("3_NTS", TRUE);
	{
		initialise_global_data();
		initialise_expected_global_data();

		// INITIAL CONDITIONS || EXPECTED RESULTS

			// Filter number
		filterNumber = 3;	// Invalid filter

			// Original signal set, filtered signal set, derived signal set
		for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
		{
			for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; iterator_2++)
			{
				global_signalSetRaw.acc[iterator_1][iterator_2].value = -700;
				global_signalSetRaw.acc[iterator_1][iterator_2].status = 1;
				global_signalSetRaw.acc[iterator_1][iterator_2].smx = 1;

				global_signalSetFil.acc[iterator_1][iterator_2].value = 0;
				global_signalSetFil.acc[iterator_1][iterator_2].status = 1;
				global_signalSetFil.acc[iterator_1][iterator_2].smx = 1;

				global_signalSetDer.acc[iterator_1][iterator_2].value = 700;
				global_signalSetDer.acc[iterator_1][iterator_2].status = 1;
				global_signalSetDer.acc[iterator_1][iterator_2].smx = 1;

			}

			for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; iterator_2++)
			{
				global_signalSetRaw.rate[iterator_1][iterator_2].value = 498;
				global_signalSetRaw.rate[iterator_1][iterator_2].status = 2;
				global_signalSetRaw.rate[iterator_1][iterator_2].smx = 2;

				global_signalSetFil.rate[iterator_1][iterator_2].value = -498;
				global_signalSetFil.rate[iterator_1][iterator_2].status = 2;
				global_signalSetFil.rate[iterator_1][iterator_2].smx = 2;

				global_signalSetDer.rate[iterator_1][iterator_2].value = 0;
				global_signalSetDer.rate[iterator_1][iterator_2].status = 2;
				global_signalSetDer.rate[iterator_1][iterator_2].smx = 2;
			}
		}

		for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_MAX_NO_OF_TEMP; iterator_1++)
		{
			global_signalSetRaw.temp[iterator_1].value= 0;
			global_signalSetRaw.temp[iterator_1].status= 3;
			global_signalSetRaw.temp[iterator_1].smx= 3;

			global_signalSetFil.temp[iterator_1].value = -900;
			global_signalSetFil.temp[iterator_1].status = 3;
			global_signalSetFil.temp[iterator_1].smx = 3;

			global_signalSetDer.temp[iterator_1].value= 900;
			global_signalSetDer.temp[iterator_1].status= 3;
			global_signalSetDer.temp[iterator_1].smx= 3;
		}

		global_signalSetRaw.timeStamp = 7;
		global_signalSetFil.timeStamp = 8;
		global_signalSetDer.timeStamp = 9;

		global_expected_signalSetRaw = global_signalSetRaw;
		global_expected_signalSetFil = global_signalSetRaw;
		global_expected_signalSetDer = global_signalSetRaw;


		// EXPECTED CALLS
		EXPECTED_CALLS("");


		// CALL SUT
		rbl_SigChainSigFil(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, filterNumber);


		// SUT CHECKS
		check_global_data();


		END_CALLS();
	END_STEP();
	}

	END_TEST();
	}
}

void ut_rbl_SigChain_runFilterSteps(int doIt)
{
	if (doIt)
	{
		int i = 0, j = 0, k = 0;

		START_TEST("49451: UTC_rbl_SigChain_runFilterSteps",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49451");


		// Cdd is in normal operation
		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_ImuCdd_GetCDDState#runFilterSteps_GetCDDState_TS1;\
							rbl_SigChain_UpdateFilter#runFilterSteps_UpdateFilter;\
							rbl_SigChain_PhaseCorrection#runFilterSteps_PhaseCorrection;\
							rbl_SigChain_UpdateDerivation#runFilterSteps_UpdateDerivation;\
							rbl_ImuSigFil_UpdateStatus#runFilterSteps_UpdateStatus;");

			// CALL FUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_runFilterSteps)(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, &global_data);


			// FUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}


		// Cdd is in error state
		START_STEP("2_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();


			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_ImuCdd_GetCDDState#runFilterSteps_GetCDDState_TS2;\
							rbl_SigChain_UpdateFilter#runFilterSteps_UpdateFilter;\
							rbl_SigChain_PhaseCorrection#runFilterSteps_PhaseCorrection;\
							rbl_SigChain_UpdateDerivation#runFilterSteps_UpdateDerivation;\
							rbl_ImuSigFil_UpdateStatus#runFilterSteps_UpdateStatus;");


			// CALL FUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_runFilterSteps)(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, &global_data);


			// FUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		// Cdd is neither in normal or error state
		START_STEP("3_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITONS || EXPECTED RESULTS

			for(i = 0; i < RBL_IMUSTDTYPES_AXIS_NO; i++)
			{
				for(j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; j++)
				{
					global_signalSetDer.acc[i][j].value = 1;
					global_expected_signalSetDer.acc[i][j].value = 0;
				}

				for(j = 0; j < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT ; j++)
				{
					global_signalSetDer.rate[i][j].value = 1;
					global_expected_signalSetDer.rate[i][j].value = 0;
				}
			}

			// EXPECTED CALLS
			EXPECTED_CALLS("rbl_ImuCdd_GetCDDState#runFilterSteps_GetCDDState_TS3;\
							12*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Acc;\
							4*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Rate;\
							12*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Acc;\
							4*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Rate;\
							12*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Acc;\
							4*rbl_SigChain_UpdateFilTab#runFilterSteps_UpdateFilTab_Rate;\
							rbl_ImuSigFil_UpdateStatus#runFilterSteps_UpdateStatus;");


			// CALL FUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_runFilterSteps)(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, &global_data);


			// FUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_UpdateFilTab(int doIt)
{
	if (doIt)
	{
		rbl_SigChain_FilTabs_t tabs, expected_tabs;
		float32 filVal = 0;

		initialise_global_data();
		initialise_expected_global_data();


		START_TEST("49690: UTC_rbl_SigChain_UpdateFilTab",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49690");

		// INITIAL CONDITIONS || EXPECTED RESULTS

				// Filter value
			filVal = 2;

				// Filter tab
			INITIALISE(tabs);
			INITIALISE(expected_tabs);

			tabs.filTabs[0][0] = !filVal;
			tabs.filTabs[0][1] = !filVal;
			tabs.filTabs[1][0] = !filVal;
			tabs.filTabs[1][1] = !filVal;

			expected_tabs.filTabs[0][0] = filVal;
			expected_tabs.filTabs[0][1] = filVal;
			expected_tabs.filTabs[1][0] = filVal;
			expected_tabs.filTabs[1][1] = filVal;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_UpdateFilTab)(&tabs, filVal);


			// SUT CHECKS
			CHECK_MEMORY("Checking variable tabs", &tabs, &expected_tabs, sizeof(tabs));
			check_global_data();

			END_CALLS();
		END_TEST();
		}
}

void ut_rbl_SigChain_UpdateFilter(int doIt)
{
	if (doIt)
	{
		float32 i = 1, j = 1;
		int iterator_1 = 0, iterator_2 = 0;

		START_TEST("47511: UTC_rbl_SigChain_UpdateFilter",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47511");

		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// New filter values
		    for(iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
		    {
		        for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; iterator_2++)
		        {
		            global_expected_tempSigSet.acc[iterator_1][iterator_2].value = (float32)(i + 2);
		            i+=2;
		        }

		        for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT ; iterator_2++)
		        {
		        	global_expected_tempSigSet.rate[iterator_1][iterator_2].value = (float32)(j + 2);
		            j+=2;
		        }
		    }

		    	// Time stamp delay tick
		    (global_data.timestampdelaytick) = malloc(sizeof(uint32));
		    *(global_data.timestampdelaytick) = 40;	// random value

		    global_expected_data = global_data;

		    	// TimeStamps
		    global_signalSetRaw.timeStamp = 73;
		    global_expected_signalSetRaw.timeStamp =  global_signalSetRaw.timeStamp;

		    global_tempSigSet.timeStamp = 0;
		    global_expected_tempSigSet.timeStamp = global_signalSetRaw.timeStamp - (*global_data.timestampdelaytick);


			// EXPECTED CALLS

			// The call sequence repeats this 3 times:
			// First for Acc   -> 3 * 2
			// Second for Rate -> 2 * 2
			EXPECTED_CALLS("6*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Acc;\
							2*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Rate;\
							6*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Acc;\
							2*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Rate;\
							6*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Acc;\
							2*rbl_SigChain_CalcSecOrdSctn#UpdateFilter_CalcSecOrdSctn_Rate;");


			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_UpdateFilter)(&global_signalSetRaw, &global_data, &global_tempSigSet);


			// SUT CHECKS
			check_global_data();

			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_UpdateDerivation(int doIt)
{
	if (doIt)
	{
		float32 i = 1, j = 1;
		int iterator_1 = 0, iterator_2 = 0;


		START_TEST("47512: UTC_rbl_SigChain_UpdateDerivation",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47512");

		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Derived signal
			for(iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
			{
				for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; iterator_2++)
				{
					global_expected_signalSetDer.acc[iterator_1][iterator_2].value = (float32)(i + 1);
					i+=1;
				}

				for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT ; iterator_2++)
				{
					global_expected_signalSetDer.rate[iterator_1][iterator_2].value = (float32)(j + 1);
		            j+=1;
				}
			}
		    global_signalSetDer.timeStamp = !global_tempSigSet.timeStamp;
		    global_expected_signalSetDer.timeStamp = global_tempSigSet.timeStamp;


			// EXPECTED CALLS

			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 3x
			// Second for Rate -> 1x
			EXPECTED_CALLS("3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;\
						  3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;\
						  3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;");

			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 3x
			// Second for Rate -> 2x
			EXPECTED_CALLS("3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  2*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;\
						  3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  2*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;\
						  3*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Acc;\
						  2*rbl_SigChain_CalcSecOrdSctn#UpdateDerivation_CalcSecOrdSctn_Rate;");
			#endif

			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_UpdateDerivation)(&global_signalSetDer, &global_data, &global_tempSigSet);


			// SUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_PhaseCorrection(int doIt)
{
	if (doIt)
	{
		float32 i = 1, j = 1;
		int iterator_1 = 0, iterator_2 = 0;

		START_TEST("47513: UTC_rbl_SigChain_PhaseCorrection",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47513");


		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

			for(iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
			{
				for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC ; iterator_2++)
				{
					global_expected_signalSetFil.acc[iterator_1][iterator_2].value = (float32)(i + 1);
					i+=1;
				}

				for(iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT ; iterator_2++)
				{
					global_expected_signalSetFil.rate[iterator_1][iterator_2].value = (float32)(j + 1);
		            j+=1;
				}
			}
		    global_signalSetFil.timeStamp = !global_tempSigSet.timeStamp;
		    global_expected_signalSetFil.timeStamp = global_tempSigSet.timeStamp;


			// EXPECTED CALLS

			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 3x
			// Second for Rate -> 1x
			  EXPECTED_CALLS("3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;\
							  3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;\
							  3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;");

			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 3x
			// Second for Rate -> 2x
			  EXPECTED_CALLS("3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  2*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;\
							  3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  2*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;\
							  3*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Acc;\
							  2*rbl_SigChain_CalcSecOrdSctn#PhaseCorrection_CalcSecOrdSctn_Rate;");
			#endif

			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_PhaseCorrection)(&global_signalSetFil, &global_data, &global_tempSigSet);


			// SUT CHECKS
			check_global_data();


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_ImuSigFil_UpdateStatus(int doIt)
{
	if (doIt)
	{
		int iterator_1 = 0, iterator_2 = 0;

		START_TEST("47514: UTC_rbl_ImuSigFil_UpdateStatus",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47514");

		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS

				// Raw, derived and filtered signals
			for (iterator_1 = 0; iterator_1 < RBL_IMUSTDTYPES_AXIS_NO; iterator_1++)
			{
				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC; iterator_2++)
				{
					global_expected_signalSetFil.acc[iterator_1][iterator_2].status |= ( 0 | 0xE5 | 0x2C );	// Values returned by stubs
					global_expected_signalSetDer.acc[iterator_1][iterator_2].status =  global_expected_signalSetFil.acc[iterator_1][iterator_2].status;
				}

				for (iterator_2 = 0; iterator_2 < RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT; iterator_2++)
				{
					global_expected_signalSetFil.rate[iterator_1][iterator_2].status |= ( 0 | 0xD7 | 0x9B );	// Values returned by stubs
					global_expected_signalSetDer.rate[iterator_1][iterator_2].status =  global_expected_signalSetFil.rate[iterator_1][iterator_2].status;
				}
			}
			global_expected_signalSetRaw = global_signalSetRaw;

				// Filter flush
			(global_data.flush) = malloc(sizeof(uint16));
			*(global_data.flush) = 9;	// random value

			global_expected_data = global_data;


			// EXPECTED CALLS

			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 6x
			// Second for Rate -> 2x
			EXPECTED_CALLS("rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;");

			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
			// The call sequence repeats this 3 times:
			// First for Acc   -> 6x
			// Second for Rate -> 4x
			EXPECTED_CALLS("rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Acc_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_FirstCall;\
						  rbl_SigChain_debounce#UpdateStatus_debounce_Rate_SecondCall;");

			#endif

			// CALL SUT
			ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_ImuSigFil_UpdateStatus)(&global_signalSetRaw, &global_signalSetFil, &global_signalSetDer, &global_data);


			// SUT CHECKS
			check_global_data();

			END_CALLS();

		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_CalcSecOrdSctn(int doIt)
{
	if (doIt)
	{
		float returnValue = 0, expected_returnValue = 0;
		float32 x = 0;
		rbl_SigChain_Filter_t FilCoeff, expected_FilCoeff;
		rbl_SigChain_FilTabs_t filTabsArray, expected_filTabsArray;

		START_TEST("47515: UTC_rbl_SigChain_CalcSecOrdSctn",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47515");

		START_STEP("1_NTS", TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS
				// x
			x = 0x1234ABCD; // Random value

				// Filter coefficient
			FilCoeff.facA[0] = 0x00000000;	// Random value
			FilCoeff.facA[1] = 0xFFFFFFFF;	// Random value
			FilCoeff.facB[0] = 0x55555555;	// Random value
			FilCoeff.facB[1] = 0xCCCCCCCC;	// Random value
			FilCoeff.facB[2] = 0x1234ABCD;	// Random value

				// Filter tabs
			filTabsArray.filTabs[0][0] = 0x00000000;	// Random value
			filTabsArray.filTabs[0][1] = 0xFFFFFFFF;	// Random value
			filTabsArray.filTabs[1][0] = 0x1234ACBD;	// Random value
			filTabsArray.filTabs[1][1] = 0xCCCCCCCC;	// Random value

				// Return value
			returnValue = 0;


			// EXPECTED RESULTS
				// Filter coefficient
			expected_FilCoeff = FilCoeff;

				// Return value
			expected_returnValue =	(x * FilCoeff.facB[0]) +
									(filTabsArray.filTabs[0][0] * FilCoeff.facB[1]) +
									(filTabsArray.filTabs[0][1] * FilCoeff.facB[2]) -
									(filTabsArray.filTabs[1][0] * FilCoeff.facA[0]) -
									(filTabsArray.filTabs[1][1] * FilCoeff.facA[1]);

				// Filter tabs
			expected_filTabsArray.filTabs[0][0] = x;
			expected_filTabsArray.filTabs[0][1] = filTabsArray.filTabs[0][0];
			expected_filTabsArray.filTabs[1][0] = expected_returnValue;
			expected_filTabsArray.filTabs[1][1] = filTabsArray.filTabs[1][0];


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_CalcSecOrdSctn)(&FilCoeff, &filTabsArray, x);


			// SUT CHECKS
			check_global_data();
			CHECK_DOUBLE(returnValue, expected_returnValue);
			CHECK_MEMORY("Checking variable FilCoeff", &FilCoeff, &expected_FilCoeff, sizeof(FilCoeff));
			CHECK_MEMORY("Checking variable filTabs", &filTabsArray, &expected_filTabsArray, sizeof(filTabsArray));


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

void ut_rbl_SigChain_debounce(int doIt)
{
	if (doIt)
	{
		uint16 counter = 0, expected_counter = 0, debounceSteps = 0;
		uint8 returnValue = 0, expected_returnValue = 0, mask = 1, status = 1;

		START_TEST("47517: UTC_rbl_SigChain_debounce",
		"https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47517");


		START_STEP("1_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS
				// Mask, status, debounce steps and counter
			mask = 0xEE;
			status = 0xEE;
			debounceSteps = 0;
			counter = 11;	// Random value
			expected_counter = debounceSteps;

				// returned value
			returnValue = 33; // Random value
			expected_returnValue = status;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_debounce)(mask, status, debounceSteps, &counter);


			// SUT CHECKS
			check_global_data();
			CHECK_U_CHAR(returnValue, expected_returnValue);
			CHECK_U_CHAR(counter, expected_counter);


			END_CALLS();
		END_STEP();
		}

		START_STEP("2_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS
				// Mask, status, debounce steps and counter
			mask = 0xFF;
			status = 0;
			debounceSteps = 0;
			counter = 54;	// Random greater than 1 value
			expected_counter = counter - 1;

				// returned value
			returnValue = 33; // Random value
			expected_returnValue = status | mask;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_debounce)(mask, status, debounceSteps, &counter);


			// SUT CHECKS
			check_global_data();
			CHECK_U_CHAR(returnValue, expected_returnValue);
			CHECK_U_CHAR(counter, expected_counter);


			END_CALLS();
		END_STEP();
		}

		START_STEP("3_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS
				// Mask, status, debounce steps and counter
			mask = 0;
			status = 0xFF;
			debounceSteps = 0;
			counter = 0;
			expected_counter = counter;

				// returned value
			returnValue = 33; // Random value
			expected_returnValue = status;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_debounce)(mask, status, debounceSteps, &counter);


			// SUT CHECKS
			check_global_data();
			CHECK_U_CHAR(returnValue, expected_returnValue);
			CHECK_U_CHAR(counter, expected_counter);


			END_CALLS();
		END_STEP();
		}

		START_STEP("4_NTS" , TRUE);
		{
			initialise_global_data();
			initialise_expected_global_data();

			// INITIAL CONDITIONS || EXPECTED RESULTS
				// Mask, status, debounce steps and counter
			mask = 0;
			status = 0;
			debounceSteps =0;
			counter = 4;
			expected_counter = counter - 1;

				// returned value
			returnValue = 33; // Random value
			expected_returnValue = status | mask;


			// EXPECTED CALLS
			EXPECT_CALL("", "", "");


			// CALL SUT
			returnValue = ACCESS_FUNCTION(rbl_SigChain_SigFil, rbl_SigChain_debounce)(mask, status, debounceSteps, &counter);


			// SUT CHECKS
			check_global_data();
			CHECK_U_CHAR(returnValue, expected_returnValue);
			CHECK_U_CHAR(counter, expected_counter);


			END_CALLS();
		END_STEP();
		}

		END_TEST();
	}
}

/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function rbl_ImuCdd_Float2ticks */
sint32 rbl_ImuCdd_Float2ticks(float32 timeInMicroseconds)
{
    REGISTER_CALL("rbl_ImuCdd_Float2ticks");

    IF_INSTANCE("default")
    {
        return 0;
    }

    IF_INSTANCE("InitFilter_Float2ticks")
    {

		#if	(RBFS_SigChainFilter == RBFS_SigChainFilter_20Hz)
    		float32 expectedValue = (1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS20HZ);

    	#elif(RBFS_SigChainFilter==RBFS_SigChainFilter_45Hz)
	    	float32 expectedValue = (1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ);

		#elif(RBFS_SigChainFilter == RBFS_SigChainFilter_Nvm)
	    	float32 expectedValue = (1000.0f*2.5);	// 0 is the timestampdelay value passed as the calling function parameter

		#else
	    	float32 expectedValue = 0;	// Default case, so the script does not crash

		#endif

        CHECK_DOUBLE_RANGE(timeInMicroseconds, expectedValue - 0.001 * expectedValue, expectedValue + 0.001 * expectedValue);

        return (ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick) + 1);
    }

    IF_INSTANCE("InitFilter2_Float2ticks")
    {

		#if	(RBFS_SigChainFilter2 == RBFS_SigChainFilter2_45Hz)
    		float32 expectedValue = (1000.0f*RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ);

		#elif (RBFS_SigChainFilter2 == RBFS_SigChainFilter2_Nvm)
    		float32 expectedValue = (1000.0f*4.1);	// 0 is the timestampdelay value passed as the calling function parameter

		#else
			float32 expectedValue = 0;	// Default case, so the script does not crash

		#endif


        CHECK_DOUBLE_RANGE(timeInMicroseconds, expectedValue - 0.001 * expectedValue, expectedValue + 0.001 * expectedValue);

		#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
        	return (ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_TimeStampDelayTick2) + 1);
		#endif
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Stub for function rbl_ImuCdd_GetCDDState */
rbl_ImuCdd_State_t rbl_ImuCdd_GetCDDState()
{
    REGISTER_CALL("rbl_ImuCdd_GetCDDState");

    IF_INSTANCE("default")
    {
        return (rbl_ImuCdd_State_t) 0;
    }

    IF_INSTANCE("runFilterSteps_GetCDDState_TS1")
    {
        return (rbl_ImuCdd_State_t) rbl_ImuCdd_Normal_e;
    }

    IF_INSTANCE("runFilterSteps_GetCDDState_TS2")
    {
        return (rbl_ImuCdd_State_t) rbl_ImuCdd_Error_e;
    }

    IF_INSTANCE("runFilterSteps_GetCDDState_TS3")
    {
        return (rbl_ImuCdd_State_t) rbl_ImuCdd_DevId_e;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return (rbl_ImuCdd_State_t) 0;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function rbl_SigChain_runFilterSteps */
int BEFORE_rbl_SigChain_runFilterSteps(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                       rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                       rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                       const rbl_SigChain_FilData_t * data)
{
    REGISTER_CALL("rbl_SigChain_runFilterSteps");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("SigChainSigFil_runFilterSteps_TS1")
    {
    	CHECK_MEMORY("Checking variable signalSetRaw", signalSetRaw, &global_signalSetRaw, sizeof(signalSetRaw));
    	CHECK_MEMORY("Checking variable signalSetFil", signalSetFil, &global_signalSetFil, sizeof(signalSetFil));
    	CHECK_MEMORY("Checking variable signalSetDer", signalSetDer, &global_signalSetDer, sizeof(signalSetDer));
    	CHECK_U_INT((uint16_t)data, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData));

		return REPLACE_WRAPPER;
    }

    IF_INSTANCE("SigChainSigFil_runFilterSteps_TS2")
    {
    	CHECK_MEMORY("Checking variable signalSetRaw", signalSetRaw, &global_signalSetRaw, sizeof(signalSetRaw));
    	CHECK_MEMORY("Checking variable signalSetFil", signalSetFil, &global_signalSetFil, sizeof(signalSetFil));
    	CHECK_MEMORY("Checking variable signalSetDer", signalSetDer, &global_signalSetDer, sizeof(signalSetDer));

		#if(RBFS_SigChainFilter2 != RBFS_SigChainFilter2_NoFilter)
			CHECK_U_INT((uint16_t)data, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, usedData2));
		#endif

		return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_runFilterSteps */
void AFTER_rbl_SigChain_runFilterSteps(struct cppsm_void_return cppsm_dummy,
                                       const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                       rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                       rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                       const rbl_SigChain_FilData_t * data){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_runFilterSteps */
void REPLACE_rbl_SigChain_runFilterSteps(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                         rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                         rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                         const rbl_SigChain_FilData_t * data)
{
    IF_INSTANCE("SigChainSigFil_runFilterSteps_TS1")
    {
		return;
    }
    IF_INSTANCE("SigChainSigFil_runFilterSteps_TS2")
    {
		return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_UpdateFilTab */
int BEFORE_rbl_SigChain_UpdateFilTab(rbl_SigChain_FilTabs_t * tabs,
                                     float32 filVal)
{
    REGISTER_CALL("rbl_SigChain_UpdateFilTab");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_UpdateFilTab_Acc")
    {
    	switch(global_AccCounter)
		{
    		case 1:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][0].value);
    			break;
    		case 2:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][0].value);
    			break;
    		case 3:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][0].value);
    			break;
    		case 4:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][0].value);
    			break;
    		case 5:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 6:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][1][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][1].value);
    			break;
    		case 7:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][1].value);
    			break;
    		case 8:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][1].value);
    			break;
    		case 9:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][2].value);
    			break;
    		case 10:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[0][2][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][2].value);
    			break;
    		case 11:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[0][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][2].value);
    			break;
    		case 12:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[0][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[0][2].value);
    			break;
			// End of first iteration
    		case 13:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 14:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 15:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 16:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 17:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][1].value);
    			break;
    		case 18:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][1][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][1].value);
    			break;
    		case 19:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[1][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][1].value);
    			break;
    		case 20:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[1][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][1].value);
    			break;
    		case 21:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][2].value);
    			break;
    		case 22:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[1][2][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][2].value);
    			break;
    		case 23:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[1][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][2].value);
    			break;
    		case 24:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[1][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[1][2].value);
    			break;
			// End of second iteration
    		case 25:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][0].value);
    			break;
    		case 26:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][0].value);
    			break;
    		case 27:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][0].value);
    			break;
    		case 28:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][0].value);
    			break;
    		case 29:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][1].value);
    			break;
    		case 30:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][1][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][1].value);
    			break;
    		case 31:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[2][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][1].value);
    			break;
    		case 32:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[2][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][1].value);
    			break;
    		case 33:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][2].value);
    			break;
    		case 34:
            	CHECK_U_INT(tabs, &(global_data.acc.steps->tabs[2][2][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][2].value);
    			break;
    		case 35:
            	CHECK_U_INT(tabs, &(global_data.acc.phaCorrn->tabs[2][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][2].value);
    			break;
    		case 36:
            	CHECK_U_INT(tabs, &(global_data.acc.derived->tabs[2][2]));
            	CHECK_U_INT(filVal, global_signalSetRaw.acc[2][2].value);
    			break;
			// End of third iteration
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_UpdateFilTab_Rate")
    {
    	switch(global_RateCounter)
		{
    		case 1:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[0][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[0][0].value);
    			break;
    		case 2:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[0][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[0][0].value);
    			break;
    		case 3:
            	CHECK_U_INT(tabs, &(global_data.rate.phaCorrn->tabs[0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[0][0].value);
    			break;
    		case 4:
            	CHECK_U_INT(tabs, &(global_data.rate.derived->tabs[0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[0][0].value);
    			break;
			// End of first iteration
    		case 5:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[1][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[1][0].value);
    			break;
    		case 6:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[1][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[1][0].value);
    			break;
    		case 7:
            	CHECK_U_INT(tabs, &(global_data.rate.phaCorrn->tabs[1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[1][0].value);
    			break;
    		case 8:
            	CHECK_U_INT(tabs, &(global_data.rate.derived->tabs[1][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[1][0].value);
    			break;
			// End of second iteration
    		case 9:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[2][0][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[2][0].value);
    			break;
    		case 10:
            	CHECK_U_INT(tabs, &(global_data.rate.steps->tabs[2][0][1]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[2][0].value);
    			break;
    		case 11:
            	CHECK_U_INT(tabs, &(global_data.rate.phaCorrn->tabs[2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[2][0].value);
    			break;
    		case 12:
            	CHECK_U_INT(tabs, &(global_data.rate.derived->tabs[2][0]));
            	CHECK_U_INT(filVal, global_signalSetRaw.rate[2][0].value);
    			break;
			// End of third iteration
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_UpdateFilTab */
void AFTER_rbl_SigChain_UpdateFilTab(struct cppsm_void_return cppsm_dummy,
                                     rbl_SigChain_FilTabs_t * tabs,
                                     float32 filVal){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_UpdateFilTab */
void REPLACE_rbl_SigChain_UpdateFilTab(rbl_SigChain_FilTabs_t * tabs,
                                       float32 filVal)
{

    IF_INSTANCE("runFilterSteps_UpdateFilTab_Acc")
    {
    	global_AccCounter += 1;	// Increase counter to be able to check variables properly in next function call
        return;
    }

    IF_INSTANCE("runFilterSteps_UpdateFilTab_Rate")
    {
    	global_RateCounter += 1;	// Increase counter to be able to check variables properly in next function call
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_ImuSigFil_UpdateStatus */
int BEFORE_rbl_ImuSigFil_UpdateStatus(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                      rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                      rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                      const rbl_SigChain_FilData_t * data)
{
    REGISTER_CALL("rbl_ImuSigFil_UpdateStatus");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_UpdateStatus")
    {
    	CHECK_MEMORY("Checking variable signalSetRaw", signalSetRaw, &global_signalSetRaw, sizeof(signalSetRaw));
    	CHECK_MEMORY("Checking variable signalSetFil", signalSetFil, &global_signalSetFil, sizeof(signalSetFil));
    	CHECK_MEMORY("Checking variable signalSetDer", signalSetDer, &global_signalSetDer, sizeof(signalSetDer));
    	CHECK_MEMORY("Checking variable data", data, &global_data, sizeof(data));
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_ImuSigFil_UpdateStatus */
void AFTER_rbl_ImuSigFil_UpdateStatus(struct cppsm_void_return cppsm_dummy,
                                      const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                      rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                      rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                      const rbl_SigChain_FilData_t * data){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_ImuSigFil_UpdateStatus */
void REPLACE_rbl_ImuSigFil_UpdateStatus(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                        rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                        rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                        const rbl_SigChain_FilData_t * data)
{

    IF_INSTANCE("runFilterSteps_UpdateStatus")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_UpdateFilter */
int BEFORE_rbl_SigChain_UpdateFilter(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                     const rbl_SigChain_FilData_t * data,
                                     rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    REGISTER_CALL("rbl_SigChain_UpdateFilter");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_UpdateFilter")
    {
    	CHECK_MEMORY("Checking variable signalSetRaw", signalSetRaw, &global_signalSetRaw, sizeof(signalSetRaw));
    	CHECK_MEMORY("Checking variable data", data, &global_data, sizeof(data));
    	CHECK_MEMORY("Checking variable tempSigSet", tempSigSet, &ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilSigSetEmpty), sizeof(tempSigSet));
    	return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_UpdateFilter */
void AFTER_rbl_SigChain_UpdateFilter(struct cppsm_void_return cppsm_dummy,
                                     const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                     const rbl_SigChain_FilData_t * data,
                                     rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_UpdateFilter */
void REPLACE_rbl_SigChain_UpdateFilter(const rbl_ImuStdTypes_ImuSignalSet_t * signalSetRaw,
                                       const rbl_SigChain_FilData_t * data,
                                       rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{

    IF_INSTANCE("runFilterSteps_UpdateFilter")
    {
    	return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_PhaseCorrection */
int BEFORE_rbl_SigChain_PhaseCorrection(rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                        const rbl_SigChain_FilData_t * data,
                                        const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    REGISTER_CALL("rbl_SigChain_PhaseCorrection");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_PhaseCorrection")
    {
    	CHECK_MEMORY("Checking variable signalSetFil", signalSetFil, &global_signalSetFil, sizeof(signalSetFil));
    	CHECK_MEMORY("Checking variable data", data, &global_data, sizeof(data));
    	CHECK_MEMORY("Checking variable tempSigSet", tempSigSet, &ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilSigSetEmpty), sizeof(tempSigSet));
    	return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_PhaseCorrection */
void AFTER_rbl_SigChain_PhaseCorrection(struct cppsm_void_return cppsm_dummy,
                                        rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                        const rbl_SigChain_FilData_t * data,
                                        const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_PhaseCorrection */
void REPLACE_rbl_SigChain_PhaseCorrection(rbl_ImuStdTypes_ImuSignalSet_t * signalSetFil,
                                          const rbl_SigChain_FilData_t * data,
                                          const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{

    IF_INSTANCE("runFilterSteps_PhaseCorrection")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_UpdateDerivation */
int BEFORE_rbl_SigChain_UpdateDerivation(rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                         const rbl_SigChain_FilData_t * data,
                                         const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{
    REGISTER_CALL("rbl_SigChain_UpdateDerivation");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("runFilterSteps_UpdateDerivation")
    {
    	CHECK_MEMORY("Checking variable signalSetDer", signalSetDer, &global_signalSetDer, sizeof(signalSetDer));
    	CHECK_MEMORY("Checking variable data", data, &global_data, sizeof(data));
    	CHECK_MEMORY("Checking variable tempSigSet", tempSigSet, &ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_FilSigSetEmpty), sizeof(tempSigSet));
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_UpdateDerivation */
void AFTER_rbl_SigChain_UpdateDerivation(struct cppsm_void_return cppsm_dummy,
                                         rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                         const rbl_SigChain_FilData_t * data,
                                         const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function rbl_SigChain_UpdateDerivation */
void REPLACE_rbl_SigChain_UpdateDerivation(rbl_ImuStdTypes_ImuSignalSet_t * signalSetDer,
                                           const rbl_SigChain_FilData_t * data,
                                           const rbl_ImuStdTypes_ImuSignalSet_t * tempSigSet)
{

    IF_INSTANCE("runFilterSteps_UpdateDerivation")
    {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function rbl_SigChain_CalcSecOrdSctn */
int BEFORE_rbl_SigChain_CalcSecOrdSctn(const rbl_SigChain_Filter_t * FilCoeff,
                                       rbl_SigChain_FilTabs_t * filTabsArray,
                                       float32 x)
 {
    REGISTER_CALL("rbl_SigChain_CalcSecOrdSctn");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("UpdateFilter_CalcSecOrdSctn_Acc")
    {
    	switch(global_AccCounter)
		{
    		case 1:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[0][0].value);
    			break;
    		case 2:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][0][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 3:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][1][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[0][1].value);
    			break;
    		case 4:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][1][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 5:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][2][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[0][2].value);
    			break;
    		case 6:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[0][2][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 7:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[1][0].value);
    			break;
    		case 8:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][0][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 9:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][1][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[1][1].value);
    			break;
    		case 10:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][1][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 11:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][2][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[1][2].value);
    			break;
    		case 12:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[1][2][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 13:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[2][0].value);
    			break;
    		case 14:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][0][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 15:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][1][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[2][1].value);
    			break;
    		case 16:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][1][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		case 17:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][2][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.acc[2][2].value);
    			break;
    		case 18:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.steps->tabs[2][2][1]);
            	CHECK_DOUBLE(x, global_AccCounter);
    			break;
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateFilter_CalcSecOrdSctn_Rate")
    {
    	switch(global_RateCounter)
		{
    		case 1:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[0][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.rate[0][0].value);
    			break;
    		case 2:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[0][0][1]);
            	CHECK_DOUBLE(x, global_RateCounter);
    			break;
    		case 3:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[1][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.rate[1][0].value);
    			break;
    		case 4:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[1][0][1]);
            	CHECK_DOUBLE(x, global_RateCounter);
    			break;
    		case 5:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[0]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[2][0][0]);
            	CHECK_DOUBLE(x, global_signalSetRaw.rate[2][0].value);
    			break;
    		case 6:
            	CHECK_U_INT((uint8_t)FilCoeff, (uint8_t)&global_data.filter->filVal[1]);
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.steps->tabs[2][0][1]);
            	CHECK_DOUBLE(x, global_RateCounter);
    			break;
    		default:
    			break;
		}
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateDerivation_CalcSecOrdSctn_Acc")
    {
    	CHECK_U_INT((uint16_t)FilCoeff, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_DerFilCfg));

    	switch(global_AccCounter)
		{
    		case 1:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[0][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][0].value);
    			break;
    		case 2:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[0][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][1].value);
    			break;
    		case 3:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[0][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][2].value);
    			break;
    		case 4:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[1][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][0].value);
    			break;
    		case 5:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[1][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][1].value);
    			break;
    		case 6:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[1][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][2].value);
    			break;
    		case 7:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[2][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][0].value);
    			break;
    		case 8:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[2][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][1].value);
    			break;
    		case 9:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.derived->tabs[2][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][2].value);
    			break;
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateDerivation_CalcSecOrdSctn_Rate")
	{
		CHECK_U_INT((uint16_t)FilCoeff, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_DerFilCfg));

			switch(global_RateCounter)
			{
				#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
					case 1:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[0][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[0][0].value);
						break;
					case 2:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[0][1]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[0][1].value);
						break;
					case 3:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[1][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[1][0].value);
						break;
					case 4:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[1][1]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[1][1].value);
						break;
					case 5:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[2][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[2][0].value);
						break;
					case 6:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[2][1]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[2][1].value);
						break;

				#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
					case 1:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[0][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[0][0].value);
						break;
					case 2:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[1][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[1][0].value);
						break;
					case 3:
						CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.derived->tabs[2][0]);
						CHECK_DOUBLE(x, global_tempSigSet.rate[2][0].value);
						break;
				#endif

				default:
					break;
			}

		return REPLACE_WRAPPER;
    }
//-----------------------------------------------
    IF_INSTANCE("PhaseCorrection_CalcSecOrdSctn_Acc")
	{
		CHECK_U_INT((uint16_t)FilCoeff, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_PhaseCorrnCfg));

		switch(global_AccCounter)
		{
			case 1:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[0][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][0].value);
				break;
			case 2:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[0][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][1].value);
				break;
			case 3:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[0][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[0][2].value);
				break;
			case 4:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[1][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][0].value);
				break;
			case 5:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[1][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][1].value);
				break;
			case 6:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[1][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[1][2].value);
				break;
			case 7:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[2][0]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][0].value);
				break;
			case 8:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[2][1]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][1].value);
				break;
			case 9:
            	CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.acc.phaCorrn->tabs[2][2]);
            	CHECK_DOUBLE(x, global_tempSigSet.acc[2][2].value);
				break;
			default:
				break;
		}
		return REPLACE_WRAPPER;
    }

    IF_INSTANCE("PhaseCorrection_CalcSecOrdSctn_Rate")
	{
		CHECK_U_INT((uint16_t)FilCoeff, (uint16_t)&ACCESS_VARIABLE(rbl_SigChain_SigFil, rbl_SigChain_PhaseCorrnCfg));

		switch(global_RateCounter)
		{
			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
				case 1:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[0][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[0][0].value);
					break;
				case 2:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[0][1]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[0][1].value);
					break;
				case 3:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[1][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[1][0].value);
					break;
				case 4:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[1][1]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[1][1].value);
					break;
				case 5:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[2][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[2][0].value);
					break;
				case 6:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[2][1]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[2][1].value);
					break;
			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
				case 1:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[0][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[0][0].value);
					break;
				case 2:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[1][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[1][0].value);
					break;
				case 3:
					CHECK_U_INT((uint8_t)filTabsArray, (uint8_t)&global_data.rate.phaCorrn->tabs[2][0]);
					CHECK_DOUBLE(x, global_tempSigSet.rate[2][0].value);
					break;
			#endif

			default:
				break;
		}
		return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_CalcSecOrdSctn */
float AFTER_rbl_SigChain_CalcSecOrdSctn(float cppsm_return_value,
                                        const rbl_SigChain_Filter_t * FilCoeff,
                                        rbl_SigChain_FilTabs_t * filTabsArray,
                                        float32 x){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_CalcSecOrdSctn */
float REPLACE_rbl_SigChain_CalcSecOrdSctn(const rbl_SigChain_Filter_t * FilCoeff,
                                          rbl_SigChain_FilTabs_t * filTabsArray,
                                          float32 x)
{

    IF_INSTANCE("UpdateFilter_CalcSecOrdSctn_Acc")
    {
        return ((global_AccCounter++) + 1);		// Value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateFilter_CalcSecOrdSctn_Rate")
    {
        return ((global_RateCounter++) + 1);	// Value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateDerivation_CalcSecOrdSctn_Acc")
    {
        return ((global_AccCounter++) + 1);		// Value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateDerivation_CalcSecOrdSctn_Rate")
    {
        return ((global_RateCounter++) + 1);	// Value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("PhaseCorrection_CalcSecOrdSctn_Acc")
    {
        return ((global_AccCounter++) + 1);		// Value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("PhaseCorrection_CalcSecOrdSctn_Rate")
    {
        return ((global_RateCounter++) + 1);	// Value returned so the variable's value changes and we can check it
    }


    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

/* Before-Wrapper for function rbl_SigChain_debounce */
int BEFORE_rbl_SigChain_debounce(uint8 mask,
                                 uint8 status,
                                 uint16 debounceSteps,
                                 uint16 * counter)
{
    REGISTER_CALL("rbl_SigChain_debounce");

    IF_INSTANCE("default")
    {
        return AFTER_WRAPPER;
    }

    IF_INSTANCE("UpdateStatus_debounce_Acc_FirstCall")
    {
    	CHECK_U_INT(mask, RBL_IMUSTDTYPES_STATUS_TMP_MASK);
    	CHECK_U_INT(debounceSteps, (*global_data.flush));

    	switch(global_AccCounter)
		{
    		case 1:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[0][0]);
    			break;
    		case 3:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[0][1]);
    			break;
    		case 5:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[0][2]);
    			break;
    		case 7:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[1][0]);
    			break;
    		case 9:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[1][1]);
    			break;
    		case 11:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[1][2]);
    			break;
    		case 13:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[2][0]);
    			break;
    		case 15:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[2][1]);
    			break;
    		case 17:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.Cnt->counter[2][2]);
    			break;
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateStatus_debounce_Acc_SecondCall")
    {
    	CHECK_U_INT(mask, RBL_IMUSTDTYPES_STATUS_INIT_MASK);
    	CHECK_U_INT(debounceSteps, (*global_data.flush));

    	switch(global_AccCounter)
		{
    		case 2:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[0][0]);
    			break;
    		case 4:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[0][1]);
    			break;
    		case 6:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[0][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[0][2]);
    			break;
    		case 8:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[1][0]);
    			break;
    		case 10:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[1][1]);
    			break;
    		case 12:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[1][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[1][2]);
    			break;
    		case 14:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][0].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[2][0]);
    			break;
    		case 16:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][1].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[2][1]);
    			break;
    		case 18:
    	    	CHECK_U_INT(status, global_signalSetRaw.acc[2][2].status);
    	    	CHECK_U_INT((uint16)counter, (uint16)&global_data.acc.initCnt->counter[2][2]);
    			break;
    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateStatus_debounce_Rate_FirstCall")
    {
    	CHECK_U_INT(mask, RBL_IMUSTDTYPES_STATUS_TMP_MASK);
    	CHECK_U_INT(debounceSteps, (*global_data.flush));

    	switch(global_RateCounter)
		{
			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
				case 1:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[0][0]);
					break;
				case 3:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[0][1]);
					break;
				case 5:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[1][0]);
					break;
				case 7:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[1][1]);
					break;
				case 9:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[2][0]);
					break;
				case 11:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[2][1]);
					break;

			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
				case 1:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[0][0]);
					break;
				case 3:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[1][0]);
					break;
				case 5:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.Cnt->counter[2][0]);
					break;
			#endif

    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("UpdateStatus_debounce_Rate_SecondCall")
    {
    	CHECK_U_INT(mask, RBL_IMUSTDTYPES_STATUS_INIT_MASK);
    	CHECK_U_INT(debounceSteps, (*global_data.flush));

    	switch(global_RateCounter)
		{
			#if (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 2)
				case 2:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[0][0]);
					break;
				case 4:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[0][1]);
					break;
				case 6:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[1][0]);
					break;
				case 8:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[1][1]);
					break;
				case 10:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[2][0]);
					break;
				case 12:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][1].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[2][1]);
					break;

			#elif (RBL_IMUSTDTYPES_NO_OF_ROT_PER_SMX == 1)
				case 2:
					CHECK_U_INT(status, global_signalSetRaw.rate[0][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[0][0]);
					break;
				case 4:
					CHECK_U_INT(status, global_signalSetRaw.rate[1][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[1][0]);
					break;
				case 6:
					CHECK_U_INT(status, global_signalSetRaw.rate[2][0].status);
					CHECK_U_INT((uint16)counter, (uint16)&global_data.rate.initCnt->counter[2][0]);
					break;

			#endif

    		default:
    			break;
		}

        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_SigChain_debounce */
uint8 AFTER_rbl_SigChain_debounce(uint8 cppsm_return_value,
                                  uint8 mask,
                                  uint8 status,
                                  uint16 debounceSteps,
                                  uint16 * counter){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_SigChain_debounce */
uint8 REPLACE_rbl_SigChain_debounce(uint8 mask,
                                    uint8 status,
                                    uint16 debounceSteps,
                                    uint16 * counter)
{
    IF_INSTANCE("default")
    {
        return 1;
    }

    IF_INSTANCE("UpdateStatus_debounce_Acc_FirstCall")
    {
    	global_AccCounter++;
        return 0xE5;		// "Random" value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateStatus_debounce_Acc_SecondCall")
    {
    	global_AccCounter++;
        return 0x2C;		// "Random" value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateStatus_debounce_Rate_FirstCall")
    {
    	global_RateCounter++;
        return 0xD7;		// "Random" value returned so the variable's value changes and we can check it
    }

    IF_INSTANCE("UpdateStatus_debounce_Rate_SecondCall")
    {
    	global_RateCounter++;
        return 0x9B;		// "Random" value returned so the variable's value changes and we can check it
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return 0;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
