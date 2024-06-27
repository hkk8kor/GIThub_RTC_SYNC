'''
/**
 * \TestCaseName SWT_RBSYS_TaskSync
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-225, Gen_SWCS_HSW_uC_Base_SYS-288
 *
 * \Purpose Verify the task synchronisation
 *
 * \Sequence
 * - Block RBSYS_SRMS_adapt_timebase interface to prevent external sync requests
 * - Check the task period by calculating the delta of 2 task activations
 * - Adapt task schema with RBSYS_SRMS_ticks_to_adapt (RBSYS_SRMS_adapt_timebase)
 *
 * \ExpectedResult
 * - The delta between two task activations differs accordingly
 * - If an adaption beyond the max allowed tick adaption is requested,
 *   the sync is done over multiple cycles
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app
import swt2.environment as env


app.execution_condition(include_switches=["RBFS_TaskSync_ON"])

is500usTaskAvailable = app.get_function_switch_setting("RBFS_Task0p5ms") == "RBFS_Task0p5ms_ON"

# RBSYS_timer_freq_mhz
if env.is_stm_stellar_device():
  nsPerStmTick = 10
  acceptedTickDelta = 60
else:
  nsPerStmTick = 12.5
  acceptedTickDelta = 60

# Stop adaption via interface
sw.get_function("RBSYS_SRMS_adapt_timebase").stub(lambda x: 0)
app.run_until_end_of_init()

def getTaskStatsIndex(task_function_name):
  os_const_task0 = sw.get_variable("Os_const_tasks0").read()
  fsw_image = app.get_fsw_elf_image()
  if fsw_image.does_symbol_exist("Os_const_tasks1"):
    os_const_task1 = sw.get_variable("Os_const_tasks1").read()
  else:
    os_const_task1 = []
  task_list = os_const_task0 + os_const_task1
  function_address = sw.get_function(task_function_name).get_address()

  for task in task_list:
    if (task["entry_function"] & 0xFFFFFFFE)== function_address:
      return int(task["index"])
  return None

if is500usTaskAvailable:
  taskLengthInTicks = 500000 / nsPerStmTick
  taskStatsIndex = getTaskStatsIndex("Os_Entry_Task0p5ms")
else:
  taskLengthInTicks = 1000000 / nsPerStmTick
  taskStatsIndex = getTaskStatsIndex("Os_Entry_Task1ms")

taskActivationVariable = sw.get_variable("RBSYS_taskstats_tasks[{}].ts_activation".format(taskStatsIndex))
ticksToAdaptVariable = sw.get_variable("RBSYS_SRMS_ticks_to_adapt")
maxTicksPerCycle = taskLengthInTicks * 0.02

lastTaskActivation = None
def getNewTaskLength():
  global lastTaskActivation
  tgt.run_until("RBSYS_PRC_SRMSTimeBaseAdaptation")
  newTaskStart = taskActivationVariable.read()
  timeDiff = (newTaskStart - lastTaskActivation) & 0xFFFFFFFF
  lastTaskActivation = newTaskStart
  return timeDiff

#################### Test start ####################

tst.start()


# Run to cyclic mode
tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
lastTaskActivation = taskActivationVariable.read()


### Without adaption

for i in range(5):
  timeDiff = getNewTaskLength()
  tst.eval_eq_f(timeDiff, taskLengthInTicks, 2)


### With adaption (positive)

# Adapt by maxAdaption/2 ticks
ticksToAdapt = int(maxTicksPerCycle/2)
ticksToAdaptVariable.write(ticksToAdapt)
tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks - ticksToAdapt, acceptedTickDelta)


### Without adaption

for i in range(5):
  timeDiff = getNewTaskLength()
  tst.eval_eq_f(timeDiff, taskLengthInTicks, 2)


### With adaption (negative)

# Adapt by negative maxAdaption/2 ticks
ticksToAdapt = int(-maxTicksPerCycle/2)
ticksToAdaptVariable.write(ticksToAdapt)
tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks - ticksToAdapt, acceptedTickDelta)


### Adaption over multiple cycles (positive)

numberOfCycles = 3
# Sync the max value for 3 cycle and then the rest in the 4th cycle
ticksToAdapt = int(maxTicksPerCycle * numberOfCycles + maxTicksPerCycle/2)
ticksToAdaptVariable.write(ticksToAdapt)
for i in range(3):
  tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks - maxTicksPerCycle, acceptedTickDelta)
# Some ticks are may lost by stopping and starting the timer, so the allowed deviation is increased
tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks - maxTicksPerCycle/2, numberOfCycles * acceptedTickDelta)


### Without adaption

for i in range(5):
  timeDiff = getNewTaskLength()
  tst.eval_eq_f(timeDiff, taskLengthInTicks, 2)


### Adaption over multiple cycles (negative)

numberOfCycles = 3
# Sync the max value for 3 cycle and then the rest in the 4th cycle
ticksToAdapt = int(-(maxTicksPerCycle * numberOfCycles + maxTicksPerCycle/2))
ticksToAdaptVariable.write(ticksToAdapt)
for i in range(3):
  tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks + maxTicksPerCycle, acceptedTickDelta)
# Some ticks are may lost by stopping and starting the timer, so the allowed deviation is increased
tst.eval_eq_f(getNewTaskLength(), taskLengthInTicks + maxTicksPerCycle/2, numberOfCycles * acceptedTickDelta)


### Without adaption

for i in range(5):
  timeDiff = getNewTaskLength()
  tst.eval_eq_f(timeDiff, taskLengthInTicks, 2)

tst.end()
