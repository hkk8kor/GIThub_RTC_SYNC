'''
/**
  * \Reference
  * Gen_SWFS_0979_HSW_OverallRequirements_3693, Gen_SWCS_HSW_uC_Base_SYS-352
  *
  * \Purpose
  * Prove that the task counters are existing and incremented by each task execution
  *
  * \Sequence
  * 1. Run until end of TaskX and get task counter (taskCnt_t0)
  * 2. Run until end of TaskX, get task counter (taskCnt_t1) and compare with previous one
  *
  * \ExpectedResult
  * Corresponding task counter must be incremented by one
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS")

tst.start()

taskCntMapping =  {"Os_Entry_Task1ms":               "RBMESG_RBMESG_Task1msCnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx1High": "RBMESG_RBMESG_TaskBaseCtrlx1Cnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx1Low":  "RBMESG_RBMESG_TaskBaseCtrlx1LowCnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx2":     "RBMESG_RBMESG_TaskBaseCtrlx2Cnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx4":     "RBMESG_RBMESG_TaskBaseCtrlx4Cnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx8":     "RBMESG_RBMESG_TaskBaseCtrlx8Cnt_u32",
                   "Os_Entry_TaskBaseCtrlCycx24":    "RBMESG_RBMESG_TaskBaseCtrlx24Cnt_u32"
                  }


if app.get_function_switch_setting("RBFS_SysTask0p5ms") == "RBFS_SysTask0p5ms_ON":
  taskCntMapping["Os_Entry_Task0p5ms"] = "RBMESG_RBMESG_Task0p5msCnt_u32"

if app.is_multi_core():
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx2p"] = "RBMESG_RBMESG_TaskBaseCtrlx2pCnt_u32"

if(app.get_function_switch_setting("RBFS_TaskSchemeExtension") == "RBFS_TaskSchemeExtension_HostCore0GuestCore1"):
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx1Guest"]  = "RBMESG_RBMESG_TaskBaseCtrlx1GuestCnt_u32"
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx2Guest"]  = "RBMESG_RBMESG_TaskBaseCtrlx2GuestCnt_u32"
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx4Guest"]  = "RBMESG_RBMESG_TaskBaseCtrlx4GuestCnt_u32"
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx10Guest"] = "RBMESG_RBMESG_TaskBaseCtrlx10GuestCnt_u32"
  taskCntMapping["Os_Entry_TaskBaseCtrlCycx20Guest"] = "RBMESG_RBMESG_TaskBaseCtrlx20GuestCnt_u32"

# Execute the test
for task in taskCntMapping:
  tgt.run_until_end_of(task)

  taskCnt_t0 = sw.get_variable(taskCntMapping[task]).read()

  tgt.run_until(task) # make sure that the next task cycle has started
  tgt.run_until_end_of(task)

  taskCnt_t1 = sw.get_variable(taskCntMapping[task]).read()
  # Task counter must be incremented by 1
  tst.eval_eq(taskCnt_t0, taskCnt_t1 - 1)

tst.end()