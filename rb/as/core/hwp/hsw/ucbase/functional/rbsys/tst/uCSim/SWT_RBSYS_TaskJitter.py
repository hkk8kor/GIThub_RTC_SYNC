'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-218
  *
  * \Purpose Test the x1 task jitter monitoring
  *
  * \Sequence
  * - for non release builds:
  *   - testing a too big positive task jitter:
  *     - run RBSYS_PRC_JitterMonitoring_x1 at least once so it is initialized
  *     - delay the beginning of RBSYS_PRC_JitterMonitoring_x1 for longer than
  *       the maximum allowed task jitter time
  *   - testing a too big negative task jitter:
  *     - run RBSYS_PRC_JitterMonitoring_x1 at least once so it is initialized
  *     - delay the beginning of RBSYS_PRC_JitterMonitoring_x1 in multiple
  *       consecutive executions for an increasing amount of time where the
  *       increase per execution is smaller than the allowed maximum task jitter
  *     - stop delaying when the delay is bigger than the maximum allowed task jitter
  * - for release builds:
  *   - run system for some time
  *   - check for multiple executions of the jitter monitoring whether jitter does
  *     not exceed maximum allowed jitter as defined in non series builds

  * \ExpectedResult
  * For non release builds:
  *   The too big positive task jitter should generate a fault in the jitter monitoring directly.
  *   Removing the delay should be registered as too big negative task jitter and a fault should be generated.
  * For release builds:
  *   All checked jitters are in the allowed range.
  */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS")

import ctypes

#############################################################################
#                             Setup                                         #
#############################################################################

# for non release builds maximum task jitter in ms is needed,
# for release builds maximum task jitter in system clock ticks is needed
maxTaskx1JitterDefine = app.get_function_switch_setting("RBFS_SysMaxTaskx1Jitter")
if(maxTaskx1JitterDefine == "RBFS_SysMaxTaskx1Jitter_15"):
  maxTaskx1Jitter = 5 * 0.15
elif(maxTaskx1JitterDefine == "RBFS_SysMaxTaskx1Jitter_5"):
  maxTaskx1Jitter = 5 * 0.05
elif(maxTaskx1JitterDefine == "RBFS_SysMaxTaskx1Jitter_SERIES"):
  # get allowed jitter percent
  RBFS_HydrActSystem = app.get_function_switch_setting("RBFS_HydrActSystem")
  RBFS_WssMounted = app.get_function_switch_setting("RBFS_WssMounted")
  if(RBFS_HydrActSystem == "RBFS_HydrActSystem_Unused" and RBFS_WssMounted == "RBFS_WssMounted_None"):
     maxTaskx1JitterPercent = 0.15
  else:
     maxTaskx1JitterPercent = 0.05

  # calculate allowed jitter ticks, the following variables are defines in production code
  C_BaseCtrlTaskCycx1_UL = 5
  RBSYS_STM_CLK_KHZ = 80000
  RBSYS_TIMERTICKS_PER_US = RBSYS_STM_CLK_KHZ / 1000
  maxTaskx1Jitter = (maxTaskx1JitterPercent * C_BaseCtrlTaskCycx1_UL * 1000.0 * RBSYS_TIMERTICKS_PER_US)
else:
  maxTaskx1Jitter = 5 * 0.05
  tst.eval(False)



#############################################################################
#                          Test start                                       #
#############################################################################
tst.start()
if(maxTaskx1JitterDefine != "RBFS_SysMaxTaskx1Jitter_SERIES"):

  #############################################################################
  #                    1. Test start for non release builds                   #
  #############################################################################

  # run until jitter monitoring runs the second time so it is initialized
  tgt.run_until("RBSYS_PRC_JitterMonitoring_x1")
  br = tgt.run_until("RBSYS_PRC_JitterMonitoring_x1", min_time=1)

  # get core on which the jitter monitoring is running
  core = br.core

  # GoodCheck -> Failure is not already set
  tst.eval(not app.get_event("RBSYS_TaskJitter").is_failed())

  # simulate jitter that is bigger than the maximum allowed task jitter by
  # sending the jitter monitoring into an endless loop for this time
  tgt.run_endless_loop(core, maxTaskx1Jitter * 2)

  # run until the jitter monitoring returns, here the fault should be set
  tgt.run_until_end_of("RBSYS_PRC_JitterMonitoring_x1")
  tst.eval(app.get_event("RBSYS_TaskJitter").is_failed())


  app.do_test_environment_reset()

  #############################################################################
  #                    2. Test start for non release builds                   #
  #############################################################################

  # run until jitter monitoring runs the second time so it is initialized
  tgt.run_until("RBSYS_PRC_JitterMonitoring_x1")
  tgt.run_until("RBSYS_PRC_JitterMonitoring_x1", min_time=1)

  # GoodCheck -> Failure is not already set
  tst.eval(not app.get_event("RBSYS_TaskJitter").is_failed())

  # simulate positive jitter for multiple executions by delaying the jitter monitoring for an
  # increasing amount of time, until this time is larger than the maximum allowed jitter time
  for i in range(2):
    # delay in the i-th execution of the jitter monitoring,
    # only increase with 2/3 of the maximum task jitter per execution
    increasingDelay = (i + 1) * (maxTaskx1Jitter * 2/3)
    tgt.run_endless_loop(core, increasingDelay)
    tgt.run_until("RBSYS_PRC_JitterMonitoring_x1", min_time=1)

    # small jitter should not trigger fault in jitter monitoring
    tst.eval(not app.get_event("RBSYS_TaskJitter").is_failed())

  # when not delaying the jitter monitoring anymore, a negative jitter bigger than the
  # maximum allowed task jitter is registered and a fault should be set after the jitter monitoring
  tgt.run_until_end_of("RBSYS_PRC_JitterMonitoring_x1")
  tst.eval(app.get_event("RBSYS_TaskJitter").is_failed())

else:

  #############################################################################
  #                    Test start for release builds                          #
  #############################################################################

  tgt.run(200)

  # for next 20 executions (100ms) of the jitter monitoring evaluate whether measured jitter is inside allowed range
  for i in range(20):
    tgt.run_until("RBSYS_PRC_JitterMonitoring_x1")
    tgt.run_until_end_of("RBSYS_PRC_JitterMonitoring_x1")

    jitter = ctypes.c_int32(sw.get_variable("RBSYS_JitterInfoTask_x1_s32").read()).value
    tst.eval_le(jitter, maxTaskx1Jitter)
    tst.eval_ge(jitter, -maxTaskx1Jitter)


tst.end()