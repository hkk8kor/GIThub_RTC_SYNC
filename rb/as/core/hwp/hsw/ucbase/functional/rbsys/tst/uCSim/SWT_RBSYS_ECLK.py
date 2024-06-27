'''
/**
 * \TestCaseName SWT_RBSYS_ECLK.py
 *
 * \Purpose Verify ECLK frequency
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-206
 *
 * \Sequence
 * - Run system until init is done
 *
 * \ExpectedResult
 * - ECLK is configured with 4 MHz
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app


app.execution_condition("ALWAYS")

tst.start()

# Run until cyclic mode to make sure everything is correctly initialized
tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")

eClk = tgt.get_port("RH850.EXTCLK0O").read()
tst.eval_eq(eClk, 4 * 1000 * 1000)

tst.end()
