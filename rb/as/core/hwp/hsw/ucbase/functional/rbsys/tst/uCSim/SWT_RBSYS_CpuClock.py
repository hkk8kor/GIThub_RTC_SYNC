'''
/**
 * \TestCaseName SWT_RBSYS_CpuClock.py
 *
 * \Purpose Verify the CPU clock frequency configured in the SW matches all PEs in VLAB
 *
 * \Sequence
 * - Run system until init is done
 *
 * \ExpectedResult
 * - The frequencies of VLAB PE clocks match RBFS_CpuClock
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app


app.execution_condition("ALWAYS")

import vlab
import re

tst.start()

# Run until cyclic mode. The VLAB clock is set after a few micro seconds, so some time has to pass
tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")

# Check the CPU clock configured in SW
clockDict = {
  "RBFS_CpuClock_80MHz" :  80 * 1000 * 1000,
  "RBFS_CpuClock_160MHz": 160 * 1000 * 1000,
  "RBFS_CpuClock_240MHz": 240 * 1000 * 1000,
  "RBFS_CpuClock_320MHz": 320 * 1000 * 1000,
  "RBFS_CpuClock_400MHz": 400 * 1000 * 1000
}
CpuClockFs = app.get_function_switch_setting("RBFS_CpuClock")
CpuClock = clockDict[CpuClockFs]

# Get ports from CPU
cpuPorts = vlab.get_instance("RH850.CPUSS").ports
# Filter for PE clocks
peClockPorts = [port for port in cpuPorts.keys() if re.match("pe.*_clk", port)]
# Check frequency of all clocks
for peClockPort in peClockPorts:
  print("Checking %s" % peClockPort)
  peClock = tgt.get_port("RH850.CPUSS." + peClockPort).read()
  tst.eval_eq(peClock, CpuClock)

tst.end()
