'''
/**
 * \TestCaseName SWT_RBSYS_TaskSync
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-225, Gen_SWCS_HSW_uC_Base_SYS-288
 *
 * \Purpose Verify the task synchronisation
 *
 * \Sequence
 * - Check the task period by calculating the delta of 2 task activations
 * - Adapt task schema with RBSYS_SRMS_test_advance_ticks and RBSYS_SRMS_test_retard_ticks
 *
 * \ExpectedResult
 * - The delta between two task activations differs accordingly
 */
'''


import swt2.test as tst
import swt2.software as sw
import swt2.target as tgt
import swt2.application as app


app.execution_condition(include_switches=["RBFS_TaskSync_ON"])

is500usTaskAvailable = app.get_function_switch_setting("RBFS_Task0p5ms") == "RBFS_Task0p5ms_ON"

nsPerStmTick = 12.5
acceptedTickDelta = 50


# stop task sync clients from calling RBSYS_SRMS_adapt_timebase
stackPointers = {}
def getStackPointer(br):
  core = br.core
  stackPointers[core] = core.get_stack_pointer_register().read()

def stubClientConditionally(br):
  core = br.core
  if (core.get_caller_function().get_name() == "RBSYS_PRC_SRMSCylicTest") or (core not in stackPointers) or (stackPointers[core] != core.get_stack_pointer_register().read()):
    core.get_program_counter_register().write(core.get_link_register().read())

tgt.add_breakpoint("RBSYS_PRC_SRMSCylicTest", action=getStackPointer)
tgt.add_breakpoint("RBSYS_SRMS_adapt_timebase", action=stubClientConditionally)
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
    if (task["entry_function"] & 0xFFFFFFFE) == function_address:
      return int(task["index"])
  return None

if is500usTaskAvailable:
  taskLengthInTicks = 500000 / nsPerStmTick
  taskStatsIndex = getTaskStatsIndex("Os_Entry_Task0p5ms")
else:
  taskLengthInTicks = 1000000 / nsPerStmTick
  taskStatsIndex = getTaskStatsIndex("Os_Entry_Task1ms")

taskActivationVariable = "RBSYS_taskstats_tasks[{}].ts_activation".format(taskStatsIndex)

lastTaskActivation = 0
lastTaskActivationDelta = 0
def calcTaskActivationDelta(br):
  global lastTaskActivation
  global lastTaskActivationDelta
  newActivation = sw.get_variable(taskActivationVariable).read()
  lastTaskActivationDelta = (newActivation - lastTaskActivation) & 0xFFFFFFFF
  lastTaskActivation = newActivation

tgt.add_data_breakpoint(taskActivationVariable, access='write', action=calcTaskActivationDelta)

#################### Test start ####################

def runTest(advanceTicks, retardTicks):
  adaptionBefore = sw.get_variable("RBSYS_SRMS_overall_adapted_ticks").read()
  sw.get_variable("RBSYS_SRMS_test_advance_ticks").write(advanceTicks)
  sw.get_variable("RBSYS_SRMS_test_retard_ticks").write(retardTicks)
  tgt.run_until_end_of("RBSYS_PRC_SRMSCylicTest") # RBSYS_SRMS_ticks_to_adapt will be set
  sw.get_variable("RBSYS_SRMS_test_advance_ticks").write(0)
  sw.get_variable("RBSYS_SRMS_test_retard_ticks").write(0)
  adaptionAfter = sw.get_variable("RBSYS_SRMS_overall_adapted_ticks").read()
  if adaptionBefore == adaptionAfter:
    tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation") # Task sees the requested adaption, not applied yet
    tst.eval_eq_f(lastTaskActivationDelta, taskLengthInTicks, 2)
  tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
  tst.eval_eq_f(lastTaskActivationDelta, taskLengthInTicks + retardTicks - advanceTicks, acceptedTickDelta)

tst.start()

# Run to cyclic mode
tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")

### Without adaption
for i in range(5):
  tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
  tst.eval_eq_f(lastTaskActivationDelta, taskLengthInTicks, 2)

### With adaption (positive)
# Adapt by 500 ticks
runTest(500, 0)

### Without adaption
for i in range(5):
  tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
  tst.eval_eq_f(lastTaskActivationDelta, taskLengthInTicks, 2)

### With adaption (negative)
# Adapt by -500 ticks
runTest(0, 500)

tgt.run_until_end_of("RBSYS_PRC_SRMSTimeBaseAdaptation")
tst.eval_eq_f(lastTaskActivationDelta, taskLengthInTicks, 2)


tst.end()
