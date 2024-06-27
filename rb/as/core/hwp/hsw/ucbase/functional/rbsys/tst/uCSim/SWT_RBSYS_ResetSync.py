'''
/**
  * \Reference Gen_SWCS_HSW_uC_Base_SYS-318, Gen_SWFS_0979_HSW_OverallRequirements_7365
  *
  * \Purpose Test the Reset Synchronization handling
  *
  * \Sequence
  * 1. Trigger RBSYS_uCReset_ApplResetSkipBootBlock on one core
  * 2. Check if the other cores are stuck in an endless loop
  * 3. Wait for the reset
  * 4. Repeat the previous steps for all cores
  *
  * \ExpectedResult
  * Cores that do not trigger the reset shall be stuck to prevent access to GRAM
  */
'''

import swt2.test as tst
import swt2.application as app
import swt2.target as tgt


app.execution_condition(include_switches=["RBFS_MCORE_ON"])


#######################

tst.start()

##################### PREPARE TEST ENVIRONMENT #####################

def logSuccessfulReset(coreIdx):
  print("""
-------------------------------------------
Reset from Core """+str(coreIdx)+""" was executed successfully
-------------------------------------------
""")


def logCoreStatus():
  print("Core0: " + str(tgt.get_core(0).get_current_function().get_name()))
  print("Core1: " + str(tgt.get_core(1).get_current_function().get_name()))

def logTestStatus(mesg):
  print("-------------------------------------------------------------")
  print("----- Test State: "             +str(mesg)                    )
  print("-------------------------------------------------------------")


######################### EXECUTE TEST #########################

for coreResetting in range(app.get_number_of_used_cores()):

  # Run until startup is done
  tgt.run_until("sys_general_idleloop", core=coreResetting) # Run Resetting core up to safe point: This is needed because currently executing
                                                            # instructions may change the manipulated program counter


  logTestStatus("Triggering RBSYS_uCReset_ApplResetSkipBootBlock")
  logCoreStatus()

  # Trigger Reset and run until cross-core ISR is executed
  tgt.trigger_execution_of_function("RBSYS_uCReset_ApplResetSkipBootBlock", core=coreResetting) # Parameters can be ignored

  logCoreStatus()
  logTestStatus("Running until RBSYS_RuntimeResetSyncBarrier")

  # Collect cores that reach Reset Sync
  cores_reached_reset_sync = set()
  bp = tgt.add_breakpoint("RBSYS_RuntimeResetSyncBarrier")
  while len(cores_reached_reset_sync) < app.get_number_of_used_cores():
    br = tgt.run()
    cores_reached_reset_sync.add(br.core)
  bp.remove()

  logCoreStatus()

  # this shall verify that we will never get back to lower priority tasks / isrs
  bp_shall_never_hit = tgt.add_breakpoint("_Os_demux_wrapper")

  # breakpoint shall be removed when an reset occurred
  bp_shall_hit = tgt.add_breakpoint(0x0, core=0)

  # Run until reset
  tgt.run(1, "ms")
  tst.eval(bp_shall_never_hit.hits == 0)
  tst.eval(bp_shall_hit.hits == 1)
  bp_shall_never_hit.remove()
  bp_shall_hit.remove()

  logSuccessfulReset(coreResetting)

app.run_until_bfm_was_updated()
ignoredFaults = ["RbmicQxMRAuCShortCircuitTestFailure"] # todo: remove when https://sbta.renesas.eu/mantis_bosch/view.php?id=8932 is fixed
tst.eval(app.is_system_fault_free(ignoredFaults))
tst.end()