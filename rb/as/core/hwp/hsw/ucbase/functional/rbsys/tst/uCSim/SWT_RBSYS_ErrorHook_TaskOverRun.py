'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-252
  *
  * \Purpose Test the following failure words:
  * 1. FW_RBSYS_TaskOverRun
  * 2. FW_RBSYS_OSErrorHook
  *
  * \Sequence
  * 1. Run until the start of the x2 task
  * 2. Slowly increase the load in that task (by using the guzzler module)
  *    until a RBSYS_TaskOverRun failure occurs.
  * 3. Run another 100 ms.
  *
  * \ExpectedResult
  * - The debug data of RBSYS_TaskOverRun indicates an overrun from x2 task or slower.
  *   (A high load on a task delays all slower task.)
  * - A RBSYS_OSErrorHook accurs and indicates the address of the failed task
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


# This test is deactivated as SWT_RBSYS_ErrorHook_TaskOverRun2.py tests the failure words in a more robust manner.
app.execution_condition("NEVER")

#######################

tst.start()

#############################################################################
#                             1. Test (Failed)                              #
#############################################################################
#                      _________________                                    #
# |                   |   TASK RUNNING  |                 |                 #
# |                   |_________________|                 |                 #
# |                   .                 .                 |                 #
# |                   .                 .                 |                 #
# |                   .                 .                 |                 #
# ts_activation_n     ts_start_n        ts_end_n          ts_activation_n+1 #
#                                                                           #
# Details:                                                                  #
#   # ts_activation_n = virtual activation time in ISR                      #
#   # ts_start_n      = in Os_Cbk_TaskStart                                 #
#   # ts_end_n        = in Os_Cbk_TaskEnd                                   #
#   # gross_n         = ts_end_n          - ts_start_n                      #
#   # resp_time_n     = ts_end_n          - ts_activation_n                 #
#   # slack_time_n    = ts_activation_n+1 - ts_end_n                        #
#                                                                           #
# FW_RBSYS_TaskOverRun will be set in case                                  #
# that the corresponding task is still active at ts_activation_n+1          #
#############################################################################

tgt.run_until("Os_Entry_TaskBaseCtrlCycx2")

failedTaskDebugId = 0
max_load = 100
load = sw.get_variable("guzzle_ASWx2.InputDataSet.Load_perc").read()

# Increase load in Taskx2 stepwise to avoid other failures being set
while(load < max_load):
  load += 5
  sw.get_variable("guzzle_ASWx2.IsOutputCalculated").write(0)
  sw.get_variable("guzzle_ASWx2.InputDataSet.Load_perc").write(load)
  sw.get_variable("guzzle_ASWx2.InputDataSet.IsGuzzlingAllowedFunction").write(0x0)
  tgt.run(50)

  if(app.get_event("RBSYS_TaskOverRun").is_failed()):
    tgt.run(20) # get failure into failure memory
    app.print_system_info()
    # Debug 0x10: overrun at Task x2, 0x8: x2p, 0x4: x4, 0x2: x8, 0x1: x24
    failedTaskDebugId = app.get_bfm_record("RBSYS_TaskOverRun").get_debug0() & 0x1F
    # If the x2 has increase load, all slower task can be affected, so one of those should fail.
    tst.eval_neq(app.get_bfm_record("RBSYS_TaskOverRun").get_debug0() & 0x1F, 0)
    break
else: # Will be executed if while condition is false (skipped by break)
  app.print_system_info()
  tst.eval(False)       # In case that the error was not set

#############################################################################
#                             2. Test (Failed)                              #
#############################################################################

# A load of 100 will cause the not finished task to be restarted
sw.get_variable("guzzle_ASWx2.IsOutputCalculated").write(0)
sw.get_variable("guzzle_ASWx2.InputDataSet.Load_perc").write(100)
sw.get_variable("guzzle_ASWx2.InputDataSet.IsGuzzlingAllowedFunction").write(0x0)

tgt.run(100)

addrOfTaskByDebugId = {}
addrOfTaskByDebugId[0x1] = sw.get_function("Os_Entry_TaskBaseCtrlCycx24").get_address()
addrOfTaskByDebugId[0x2] = sw.get_function("Os_Entry_TaskBaseCtrlCycx8").get_address()
addrOfTaskByDebugId[0x4] = sw.get_function("Os_Entry_TaskBaseCtrlCycx4").get_address()
addrOfTaskByDebugId[0x8] = sw.get_function("Os_Entry_TaskBaseCtrlCycx2p").get_address()
addrOfTaskByDebugId[0x10] = sw.get_function("Os_Entry_TaskBaseCtrlCycx2").get_address()

tst.eval(app.get_event("RBSYS_OSErrorHook").is_failed())
app.run_until_bfm_was_updated()
tst.eval_eq(app.get_bfm_record("RBSYS_OSErrorHook").get_debug0(), 0x10004)

# It is possible, that an overrun occurred for more than one task, so multiple bits in failedTaskDebugId can be set.
# But debug 1 of RBSYS_OSErrorHook only stores the address of one task, so we need to check whether this address
# corresponds to one of the tasks for which an overrun occurred
foundMatch = False
for i in range(len(addrOfTaskByDebugId)):
  failedTaskId = failedTaskDebugId & (1<<i) # check whether i-th bit is set in debug value of task overrun
  if( failedTaskId != 0 ):
    if(app.get_bfm_record("RBSYS_OSErrorHook").get_debug1() == addrOfTaskByDebugId[failedTaskId]): # if bit is set compare task address with debug value of errorhook
      foundMatch = True
      break
tst.eval(foundMatch)

tst.end()
