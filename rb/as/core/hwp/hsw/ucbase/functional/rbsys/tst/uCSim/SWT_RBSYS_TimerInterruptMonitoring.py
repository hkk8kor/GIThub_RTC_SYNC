'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-326
  *
  * \Purpose Test reaction of Timer Interrupt Monitoring to too short or too long time interval between interrupt signals
  *
  * \Sequence
  *   - for upper and lower limit of monitoring:
  *     - run until Timer Interrupt Monitoring is initialized and running
  *     - increasingly shift the INTTPTMU00 signal by manipulating write operations to TPTM0UCMP00
  *
  * \ExpectedResult
  *   - monitoring must trigger latest when 1% (plus possibly flexray) deviation from the normal interrupt interval is reached or RBTaskMon triggers even before that due to too early activation of a task
  */
'''


import swt2.test as tst
import swt2.application as app
import swt2.target as tgt
import swt2.environment as env


app.execution_condition(include_switches=["RBFS_uCFamily_RenesasU2A"])

#############################################################################
#                          Setup                                            #
#############################################################################
# Calculate maximum allowed deviation from normal system timer interval
if (app.get_function_switch_setting("RBFS_SysTask0p5ms") == "RBFS_SysTask0p5ms_ON"):
  INTERRUPT_INTERVAL_US = 500.0
else:
  INTERRUPT_INTERVAL_US = 1000.0

# Flexray adaptions
if (app.get_function_switch_setting("RBFS_FlxrTaskSync") == "RBFS_FlxrTaskSync_ON"):
  RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT = 2.0
  MAX_FLEXRAY_DEVIATION_US = ((RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT * INTERRUPT_INTERVAL_US) / 100)
  DEVIATION_THRESHOLD_US = ((INTERRUPT_INTERVAL_US / 100) + MAX_FLEXRAY_DEVIATION_US)
else:
  DEVIATION_THRESHOLD_US = (INTERRUPT_INTERVAL_US / 100)

TPTM_TICKS_PER_US = 80
DEVIATION_THRESHOLD_TPTM_TICKS = int(DEVIATION_THRESHOLD_US * TPTM_TICKS_PER_US)

# The corresponding amount of deviation has to be detected by the monitoring
cmpOffsets = [DEVIATION_THRESHOLD_TPTM_TICKS, -DEVIATION_THRESHOLD_TPTM_TICKS]

# Stores simulation time of last rising edge on INTTPTMU00 signal for calculation of elapsed time between rising edges
interruptTime = 0
def getInterruptTime(br):
  global interruptTime
  if(tgt.get_port("RH850.CPUSS.SCHEAPG4.NSMVRH850V02.G4SS.TPTM.INTTPTMU00").read()):
    interruptTime = env.get_time("ns")

# Current manipulation of the TPTM0UCMP00 register
manipulateOffset = 0
def manipulateCmpOnWrite(br):
  br.overwrite_data(br.data + manipulateOffset)

tgt.add_port_breakpoint("RH850.CPUSS.SCHEAPG4.NSMVRH850V02.G4SS.TPTM.INTTPTMU00", action=getInterruptTime)
tgt.add_register_breakpoint("RH850.CPUSS.SCHEAPG4.NSMVRH850V02.G4SS.TPTM.TPTM0UCMP00", access="write", action=manipulateCmpOnWrite)

#############################################################################
#                          Test start                                       #
#############################################################################
tst.start()

for maxOffset in cmpOffsets:
  manipulateOffset = 0
  tgt.run_until_end_of("RBSYS_PRC_TimerInterruptMonitoring") # First run initializes PIC1 and TAUD0
  tgt.run_until_end_of("RBSYS_PRC_TimerInterruptMonitoring") # Second run ignores captured value as it is invalid
  tgt.run_until_end_of("RBSYS_PRC_TimerInterruptMonitoring") # Third run is the first that monitors

  #############################################################################
  #                          Good Check                                       #
  #############################################################################
  tst.eval(not app.get_event("RBSYS_SYSErrorHook").is_failed())

  #############################################################################
  #                          Manipulation                                     #
  #############################################################################
  # The next interrupt is already scheduled by VLAB, start overwriting CMP from the next TPTM ISR on
  manipulateOffset = int(maxOffset * 0.99)
  step = 1 if maxOffset >= 0 else -1
  tgt.run_until_end_of("RBSYS_PRC_TimerInterruptMonitoring") # run once again, so that the next Timer ISR was executed and CMP has been manipulated the first time

  # Start manipulation a little bit below threshold, increment every loop, monitoring has to trigger before time reaches threshold
  while(not app.get_event("RBSYS_SYSErrorHook").is_failed() and abs(manipulateOffset) <= (DEVIATION_THRESHOLD_TPTM_TICKS + TPTM_TICKS_PER_US)):
    # Slowly approach theshold
    manipulateOffset += step # this offset is used in the next Timer ISR, so it will influence the Monitoring another Timer ISR later => evaluation of the next loop iteration

  #############################################################################
  #                          Evaluation                                       #
  #############################################################################
    lastInterruptTime = interruptTime
    tgt.run_until_end_of("RBSYS_PRC_TimerInterruptMonitoring")
    duration = interruptTime - lastInterruptTime

    tst.eval(
        (     duration <= ((INTERRUPT_INTERVAL_US + DEVIATION_THRESHOLD_US) * 1000)
          and duration >= ((INTERRUPT_INTERVAL_US - DEVIATION_THRESHOLD_US) * 1000) )
        or app.get_event("RBSYS_SYSErrorHook").is_failed() or app.get_event("RBOSTaskSchemeError").is_failed())
    if(duration > ((INTERRUPT_INTERVAL_US + DEVIATION_THRESHOLD_US) * 1000) or duration < ((INTERRUPT_INTERVAL_US - DEVIATION_THRESHOLD_US) * 1000)):
        break

  tst.eval(app.get_event("RBSYS_SYSErrorHook").is_failed() or app.get_event("RBOSTaskSchemeError").is_failed())
  app.do_test_environment_reset()

tst.end()