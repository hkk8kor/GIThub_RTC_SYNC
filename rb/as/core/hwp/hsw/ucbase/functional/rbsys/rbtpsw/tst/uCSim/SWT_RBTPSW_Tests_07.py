'''
/**
 *
 * \Reference RBTPSW,
 * Gen_SWCS_HSW_uC_Base_SYS-236,
 * Gen_SWCS_HSW_uC_Base_SYS-237,
 * Gen_SWCS_HSW_uC_Base_SYS-281,
 * Gen_SWCS_HSW_uC_Base_SYS-290,
 * Gen_SWCS_HSW_uC_Base_SYS-299,
 * Gen_SWCS_HSW_uC_Base_SYS-344
 *
 * \Purpose
 * Check memory and runtime protection exceptions by third party SW
 *
 * \Sequence
 * Run test steps provided by rbtpsw_tests_hsw.py
 *
 * \ExpectedResult
 * - Exception are triggered for all prohibited memory accesses
 * - Allowed memory accesses cause no exception
 */
'''


import swt2.test as tst
import swt2.application as app
import swt2.software as sw


app.execution_condition(include_switches=["RBFS_TPSWTestsuite_ON"])

import rbtpsw_tests_hsw
import uCSimDbgInterface

tst.start("RBTPSW_.*", "RBTPSW_MyTPSW.*")

# Test Design

# stub guzzler to prevent taskoverruns
to_stub = [
    "RBGuzzler_x1H",   # guzzler + TPSW Testsuite cause TaskOverRun error
    "RBGuzzler_ASW_x1",
    "RBGuzzler_ASW_x2",
    "RBGuzzler_ASW_x4",
    "RBGuzzler_ASW_x8",
    "RBGuzzler_ASW_x24",
    "Spi_AsyncTransmit", # cause LockTooLong error
]

for function_name in to_stub:
    f = sw.get_function(function_name)
    if f:
        f.stub()

dbg = uCSimDbgInterface.SWTDbgInterface()
rbtpsw_tests_hsw.executeTests(dbg, start_testid=61, end_testid=70)


tst.end()
