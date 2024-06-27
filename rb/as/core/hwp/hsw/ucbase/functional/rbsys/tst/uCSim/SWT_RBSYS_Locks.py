'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-220, Gen_SWCS_HSW_uC_Base_SYS-352
  *
  * \Purpose Test unbalanced lock detection
  *
  * \Sequence
  * - for every enter or exit lock function and every task:
  *   - run until system is initialized
  *   - run until the beginning of the task
  *   - inject the lock function
  *   - run until RBSYS_SYSErrorHook is called
  *   - reset the test environment
  *
  * \ExpectedResult
  * - FW_SYSErrorHook occurred or system froze
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS", test_suite="nightly")

#############################################################################
#                             Setup                                         #
#############################################################################

# all enter and exit lock functions
lockFunctions = [
  "RBSYS_EnterCommonLock_intern"             , "RBSYS_ExitCommonLock_intern"             ,
  "RBSYS_EnterCommonLockSysfast_intern"      , "RBSYS_ExitCommonLockSysfast_intern"      ,
  "RBSYS_EnterCorelocalIntlock_intern"       , "RBSYS_ExitCorelocalIntlock_intern"       ,
  "RBSYS_EnterCorelocalIntlockSysfast_intern", "RBSYS_ExitCorelocalIntlockSysfast_intern"
]

# tasks in which the lock functions are injected
tasks = [
  "Os_Entry_Task1ms",
  "Os_Entry_TaskBaseCtrlCycx1High",
  "Os_Entry_TaskBaseCtrlCycx1Low",
  "Os_Entry_TaskBaseCtrlCycx2",
  "Os_Entry_TaskBaseCtrlCycx4",
  "Os_Entry_TaskBaseCtrlCycx8",
  "Os_Entry_TaskBaseCtrlCycx24"
]

# append additional tasks depending on function switches/uC etc.
if(app.get_function_switch_setting("RBFS_SysTask0p5ms") == "RBFS_SysTask0p5ms_ON"):
  tasks.append("Os_Entry_Task0p5ms")
if(app.is_multi_core()):
  tasks.append("Os_Entry_TaskBaseCtrlCycx2p")
if(app.get_function_switch_setting("RBFS_TaskSchemeExtension") == "RBFS_TaskSchemeExtension_HostCore0GuestCore1"):
  tasks.append("Os_Entry_TaskBaseCtrlCycx1Guest")
  tasks.append("Os_Entry_TaskBaseCtrlCycx2Guest")
  tasks.append("Os_Entry_TaskBaseCtrlCycx4Guest")
  tasks.append("Os_Entry_TaskBaseCtrlCycx10Guest")
  tasks.append("Os_Entry_TaskBaseCtrlCycx20Guest")




#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

for lockFunction in lockFunctions:
  if not app.get_fsw_elf_image().does_symbol_exist(lockFunction):
    continue

  for task in tasks:
    if not app.get_fsw_elf_image().does_symbol_exist(task):
      continue

    # run system until initialization is done
    tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")



#############################################################################
#              GoodCheck -> Failure is not already set                      #
#############################################################################

    # check that fault is not yet set
    tst.eval(not app.get_event("RBSYS_SYSErrorHook").is_failed())



#############################################################################
#                             Manipulation                                  #
#############################################################################

    # execute the lock function at the beginning of the task
    br = tgt.run_until(task)
    tgt.run_function(lockFunction, parameters=[], core=br.core)


    # run the system until unbalanced lock check happened
    tgt.run_until("RBSYS_setSYSErrorHook", timeout=240)
    tgt.run(1)



#############################################################################
#                             Failure must be set                           #
#############################################################################

    # it is possible that no fault is set as the system can (partially) freeze,
    # not reaching lock monitoring in x2 (and x2p) tasks
    if(not app.get_event("RBSYS_SYSErrorHook").is_failed()):
      # store current x2 and x2p task counter
      taskx2cnt  = sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32").read()
      if(app.is_multi_core()):
        taskx2pcnt = sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx2pCnt_u32").read()

      # run system long enough so that x2 and x2p counter should have been incremented
      tgt.run(20)

      # check that x2 or x2p counter have not been incremented, indicating a system freeze
      if(app.is_multi_core()):
        tst.eval(taskx2cnt == sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32").read() or taskx2pcnt == sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx2pCnt_u32").read())
      else:
        tst.eval(taskx2cnt == sw.get_variable("RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32").read())
    else:
      # otherwise check for fault
      tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed())

    # reset environment to test the next lock function
    app.do_test_environment_reset()


tst.end()