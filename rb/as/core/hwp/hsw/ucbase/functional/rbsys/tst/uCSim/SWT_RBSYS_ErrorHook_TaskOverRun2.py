'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-252, Gen_SWCS_HSW_uC_Base_SYS-352
  *
  * \Purpose Test the following failure words for every task:
  * 1. FW_RBSYS_TaskOverRun
  * 2. FW_RBSYS_OSErrorHook
  *
  * \Sequence
  * - For every task:
  *   - Run until the start of taskbody_prc_calls of the task
  *   - Force the task into an endless loop
  *   - Run the system for the duration of a complete cycle of the task (that is enough for the task to exceed its deadline and TaskOverRun fault happens)
  *   - If ErrorHook fault has not yet happened, run for another cycle (that is enough for the task to be activated again and ErrorHook fault happens)
  *   - Release the task from the endless loop
  *   - Reset test environment to test the next task
  *
  * \ExpectedResult
  * - Both TaskOverRun and OSErrorHook faults are set after one and two task cycles, respectively
  * - The BfmRecord debug values are as expected for the tested task
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS")

#############################################################################
#                             Helper functions                              #
#############################################################################

# return index of given task in the OS task array
def GetTaskIndex(task):
  numberOfTasks = sw.get_variable("Os_const_tasks").get_array_length()
  for taskIndex in range(numberOfTasks):
    entryFunction = sw.get_variable("Os_const_tasks[%d]->entry_function" % taskIndex).read()
    if(sw.get_function(task).get_address() == entryFunction & 0xFFFFFFFE):
      return taskIndex
  return None

# returns the core index a given task is running on
def GetCoreIndex(task):
  if(app.is_multi_core()):
    taskIndex = GetTaskIndex(task)
    return sw.get_variable("Os_const_tasks[%d]->core_id" % taskIndex).read()
  else:
    return 0

# runs the simulation until the start of taskbody_prc_calls of a given task
# procListPtr is needed to check that the correct call of the function was reached
def RunUntilStartOfTask(task, procListPtr):
  tgt.run_until(task)  # only here to speed up the test, can't rely on the next taskbody_prc_calls call to be in this task

  taskCoreIdx = GetCoreIndex(task)
  taskCore = tgt.get_core(taskCoreIdx)

  tgt.run_until("taskbody_prc_calls", core=taskCoreIdx)
  ptr = taskCore.get_parameter_values()[0]
  while(ptr != sw.get_variable(procListPtr).read()):
    tgt.run_until("taskbody_prc_calls", core=taskCoreIdx)
    ptr = taskCore.get_parameter_values()[0]

# check Bfm for TaskOverRun Record
def CheckBfmForTaskOverRun(task):
  if(task not in tasksNotCheckedForOverRun and app.get_event("RBSYS_TaskOverRun").is_failed()):
    # look whether BfmRecord exists, it might not as OSErrorHook has a higher priority and can occur "at the same time"
    records = app.get_bfm_records()
    for record in records:
      if(record.get_name() == "RBSYS_TaskOverRun"):
        taskIndex = GetTaskIndex(task)
        tst.eval_neq(record.get_debug0() & (1 << taskIndex), 0)
        tst.eval_eq(record.get_debug1(), sw.get_function(task).get_address())
        break

# check Bfm for OSErrorHook Record
def CheckBfmForOSErrorHook(task):
  if(app.get_event("RBSYS_OSErrorHook").is_failed()):
    tst.eval_eq(app.get_bfm_record("RBSYS_OSErrorHook").get_debug0(), 0x10004)
    tst.eval_eq(app.get_bfm_record("RBSYS_OSErrorHook").get_debug1(), sw.get_function(task).get_address())



#############################################################################
#                             Setup                                         #
#############################################################################

# task function name: function name of the task that will be tested
# cycle time: cycle time of the task, the time until the deadline of the task is definitely reached
# process list ptr: pointer name that contains the address to the array of pointers to all function executed in the task,
#                   its address is the parameter of taskbody_prc_calls and used to find and manipulate the right task
tasks = [
# ( task function name             , cycle time[ms] ,  process list ptr)
  ("Os_Entry_Task1ms"              ,               1, "prclist_task1ms"), # only checked for TaskOverRun if Task0p5ms is running
  ("Os_Entry_TaskBaseCtrlCycx1High",               5, "prclist_taskx1h"), # not checked for TaskOverRun
  ("Os_Entry_TaskBaseCtrlCycx1Low" ,               5, "prclist_taskx1l"),
  ("Os_Entry_TaskBaseCtrlCycx2"    ,              10, "prclist_taskx2" ),
  ("Os_Entry_TaskBaseCtrlCycx4"    ,              20, "prclist_taskx4" ),
  ("Os_Entry_TaskBaseCtrlCycx8"    ,              40, "prclist_taskx8" ),
  ("Os_Entry_TaskBaseCtrlCycx24"   ,             120, "prclist_taskx24")
]
tasksNotCheckedForOverRun = [
  "Os_Entry_TaskBaseCtrlCycx1High",
  "Os_Entry_Task0p5ms",
  "Os_Entry_TaskBaseCtrlCycx1Guest",
  "Os_Entry_TaskBaseCtrlCycx2Guest",
  "Os_Entry_TaskBaseCtrlCycx4Guest",
  "Os_Entry_TaskBaseCtrlCycx10Guest",
  "Os_Entry_TaskBaseCtrlCycx20Guest"
  ]


# append additional tasks depending on function switches/uC etc.
if(app.get_function_switch_setting("RBFS_SysTask0p5ms") == "RBFS_SysTask0p5ms_ON"):
  tasks.append(("Os_Entry_Task0p5ms", 1, "prclist_task0p5ms")) # not checked for TaskOverRun
else:
  tasksNotCheckedForOverRun.append("Os_Entry_Task1ms")

if(app.is_multi_core()):
  tasks.append(("Os_Entry_TaskBaseCtrlCycx2p", 10, "prclist_taskx2p"))

if(app.get_function_switch_setting("RBFS_TaskSchemeExtension") == "RBFS_TaskSchemeExtension_HostCore0GuestCore1"):
  tasks.append(("Os_Entry_TaskBaseCtrlCycx1Guest" ,   5, "prclist_taskx1guest" ))
  tasks.append(("Os_Entry_TaskBaseCtrlCycx2Guest" ,  10, "prclist_taskx2guest" ))
  tasks.append(("Os_Entry_TaskBaseCtrlCycx4Guest" ,  20, "prclist_taskx4guest" ))
  tasks.append(("Os_Entry_TaskBaseCtrlCycx10Guest",  50, "prclist_taskx10guest"))
  tasks.append(("Os_Entry_TaskBaseCtrlCycx20Guest", 100, "prclist_taskx20guest"))


# turn off time adaption interface so that timing is not disturbed by flexray synchronization
if(app.get_fsw_elf_image().does_symbol_exist("RBSYS_SRMS_adapt_timebase")):
  sw.get_function("RBSYS_SRMS_adapt_timebase").stub()



#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

for (task, time, procListPtr) in tasks:
  # check whether task does exist
  if(app.get_fsw_elf_image().does_symbol_exist(task) == False):
    continue

  print("Currently testing {}".format(task))

  # get core on which the task is running
  taskCoreIdx = GetCoreIndex(task)
  taskCore = tgt.get_core(taskCoreIdx)

  # run until the task starts to execute registered functions
  # special case for 0p5ms and 1ms tasks: first task must finish before x5 task start, otherwise RBTaskMon trigger reset, so run until second task
  if task in ["Os_Entry_Task0p5ms", "Os_Entry_Task1ms"]:
    tgt.run_until_end_of(task)
  RunUntilStartOfTask(task, procListPtr)



#############################################################################
#              GoodCheck -> Failure is not already set                      #
#############################################################################
  tst.eval(not app.get_event("RBSYS_TaskOverRun").is_failed())
  tst.eval(not app.get_event("RBSYS_OSErrorHook").is_failed())



#############################################################################
#                             Manipulation                                  #
#############################################################################

  # send task into endless loop for a complete cycle time
  tgt.trigger_execution_of_endless_loop(taskCore) # endless loop will be left via Application Reset



#############################################################################
#                             Failure must be set                           #
#############################################################################



  if(task in tasksNotCheckedForOverRun): # Task should detect OSErrorHook first

    app.run_until_end_of_event_report("RBSYS_OSErrorHook", report_status=app.FAILED, timeout=1, timeout_unit="s")
    tst.eval(app.get_event("RBSYS_OSErrorHook").is_failed())

  else:                                  # Task should detect TaskOverrun first

    app.run_until_end_of_event_report("RBSYS_TaskOverRun", report_status=app.FAILED, timeout=1, timeout_unit="s")
    tst.eval(app.get_event("RBSYS_TaskOverRun").is_failed())



#############################################################################
#                Epilogue, check BfmRecord debug values and reset           #
#############################################################################

  # run until error entries are written and then check them
  app.run_until_bfm_was_updated()

  if(task in tasksNotCheckedForOverRun): # Task should detect OSErrorHook first
    CheckBfmForOSErrorHook(task)
  else:                                  # Task should detect TaskOverrun first
    CheckBfmForTaskOverRun(task)

  # reset test environment for the next task
  app.do_test_environment_reset()

tst.end()