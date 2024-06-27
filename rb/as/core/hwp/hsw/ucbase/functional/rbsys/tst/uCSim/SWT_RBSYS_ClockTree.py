'''
/**
 * \TestCaseName SWT_RBSYS_ClockTree.py
 *
 * \Purpose Verify clock tree
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-268
 *
 * \Sequence
 * - Run system until init is done
 *
 * \ExpectedResult
 * - HSB Clock is 80 MHz
 * - LSB Clock is 40 MHz
 * - CLKP_H1 is 80 MHz
 * - CLKP_H2 is 80 MHz
 * - CLKP_L is 40 MHz
 * - CLK_CPU matches (RBFS_CpuClock)
 * - CLKP_C depends on RBFS_CpuClock and is 80 MHz or 160 MHz (for 160 and 240 MHz CPU)
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app


app.execution_condition(include_switches=["RBFS_uCFamily_RenesasP1x"])

tst.start()

# Run until cyclic mode to make sure everything is correctly initialized
tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")


cpuClockDict = {
  "RBFS_CpuClock_80MHz" :  80 * 1000 * 1000,
  "RBFS_CpuClock_160MHz": 160 * 1000 * 1000,
  "RBFS_CpuClock_240MHz": 240 * 1000 * 1000
}
c_clkDict = { # CSIH peripheral clock CLKP_C (frequency depends on the CPU Clock speed)
  "RBFS_CpuClock_80MHz" :  80 * 1000 * 1000,
  "RBFS_CpuClock_160MHz": 160 * 1000 * 1000,
  "RBFS_CpuClock_240MHz": 160 * 1000 * 1000
}
CpuClockFs = app.get_function_switch_setting("RBFS_CpuClock")


clocks = {
  "RH850.PFRH850.SYSCTL.CLK_HSB": 80 * 1000 * 1000,
  "RH850.PFRH850.SYSCTL.CLK_LSB": 40 * 1000 * 1000,
  "RH850.PFRH850.SYSCTL.CLKP_H1": 80 * 1000 * 1000,
  "RH850.PFRH850.SYSCTL.CLKP_H2": 80 * 1000 * 1000,
  "RH850.PFRH850.SYSCTL.CLKP_L": 40 * 1000 * 1000
}

clocks["RH850.PFRH850.SYSCTL.CLK_CPU"] = cpuClockDict[CpuClockFs]
clocks["RH850.PFRH850.SYSCTL.CLKP_C"] = c_clkDict[CpuClockFs]



for clock in clocks:
  print("Checking %s" % clock)
  tst.eval_eq(tgt.get_port(clock).read(), clocks[clock])


tst.end()
