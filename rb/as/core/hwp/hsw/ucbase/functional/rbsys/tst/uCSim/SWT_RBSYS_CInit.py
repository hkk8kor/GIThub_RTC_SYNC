'''
/**
 * \TestCaseName SWT_RBSYS_CInit.py
 *
 * \Purpose Verify CInit routine
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-186, Gen_SWCS_HSW_uC_Base_SYS-187, Gen_SWCS_HSW_uC_Base_SYS-188, Gen_SWCS_HSW_uC_Base_SYS-189
 *
 * \Sequence
 * - (Do this for each Core)
 * - Run system until _start (directly before)
 * - Initialize a CInit-Zero-Initialized RAM variable (only for C0)
 * - Initialize a CInit-Initialized RAM variable      (only for C0)
 * - Initialize the Global Pointer and Text Pointer registers with 0
 * - Run system until main (directly before)
 *
 * \ExpectedResult
 * - Initialized variables shall be initialized by CInit routine
 * - GP, TP shall be initialized
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS")

tst.start()

for coreId in range(app.get_number_of_used_cores()):
    if( coreId >= 2 ):
        continue # Only 2 Cores are currently supported by SW, therefore the CPU registers will not be initialized for the others

    print("CoreId = "+str(coreId))
    tgt.run_until("_start", core=coreId)

    if(coreId == 0):
        sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx1Cnt_u32").write(0x1337)  # zero-initialized variable
        sw.get_variable("RBSYS_timer_freq_mhz").write(0)  # non-zero-initialized variable

    tgt.get_core(coreId).get_register("r4").write(0)
    tgt.get_core(coreId).get_register("r5").write(0)

    tgt.run_until("main", core=coreId)

    if (coreId == 0):
        tst.eval(sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx1Cnt_u32").read() == 0)
        tst.eval(sw.get_variable("RBSYS_timer_freq_mhz").read() != 0)


    tst.eval(tgt.get_core(coreId).get_register("r4").read() != 0)
    tst.eval(tgt.get_core(coreId).get_register("r5").read() != 0)

    app.do_hardware_reset()

tst.end()
