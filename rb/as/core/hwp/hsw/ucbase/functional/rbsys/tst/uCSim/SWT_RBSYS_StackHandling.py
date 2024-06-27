'''
/**
 * \TestCaseName SWT_RBSYS_StackHandling.py
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose Check that StackOver- and UnderFlow is detected during runtime for each Stack
 *
 * \Sequence
 * - Collect all addresses of check patterns on all stacks
 * - For every check pattern:
 *   - Run system until after RBSYS_PRC_StackCheck
 *   - Overwrite check pattern
 *   - Run system until after RBSYS_PRC_StackCheck
 *   - Reset test environment to test the next check pattern
 *
 * \ExpectedResult
 * - DEM report of RBSYS_StackOverUnderFlow only after the check pattern was overwritten
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.software as sw
import swt2.application as app


app.execution_condition("ALWAYS")


#############################################################################
#                             Setup                                         #
#############################################################################

# Get number of stacks that are being checked
stackCount = sw.get_variable("rba_MultiStackTrace_ConstStackTable").get_array_length()

# For every stack get the addresses of the check patterns
checkPatternAddresses = []
for i in range(stackCount):
  # 2 words check pattern at the end of the stack, lowest address
  limitAddress = sw.get_variable("rba_MultiStackTrace_ConstStackTable[%d].LimitTable[0]" % i).read()
  expectedDbg0 = 1 << (i*3)
  checkPatternAddresses.append((limitAddress    , expectedDbg0))
  checkPatternAddresses.append((limitAddress + 1, expectedDbg0))

  # 2 words check pattern 20 words before the end of the stack
  limitAddress = sw.get_variable("rba_MultiStackTrace_ConstStackTable[%d].LimitTable[1]" % i).read()
  expectedDbg0 = 1 << (1 + i*3)
  checkPatternAddresses.append((limitAddress    , expectedDbg0))
  checkPatternAddresses.append((limitAddress + 1, expectedDbg0))

  # 2 words check pattern at the start of the stack, highest address
  limitAddress = sw.get_variable("rba_MultiStackTrace_ConstStackTable[%d].LimitTable[2]" % i).read()
  expectedDbg0 = 1 << (2 + i*3)
  checkPatternAddresses.append((limitAddress    , expectedDbg0))
  checkPatternAddresses.append((limitAddress + 1, expectedDbg0))



#############################################################################
#                             Test start                                    #
#############################################################################
tst.start()

# Check for every check pattern individually, whether a wrong pattern is detected and reported
for (checkPatternAddress, expectedDbg0) in checkPatternAddresses:
  # Check that the error that will be triggered is not yet reported
  tgt.run_until_end_of("RBSYS_PRC_StackCheck")



#############################################################################
#              GoodCheck -> Failure is not already set                      #
#############################################################################

  tst.eval(not app.get_event("RBSYS_StackOverUnderFlow").is_failed())



#############################################################################
#                             Manipulation                                  #
#############################################################################

  # Overwrite check pattern
  tgt.write_memory_uint32(checkPatternAddress, 0xDEADBEEF)

  # Run until check pattern was checked
  tgt.run_until("RBSYS_PRC_StackCheck")
  tgt.run_until_end_of("RBSYS_PRC_StackCheck")



#############################################################################
#                             Failure must be set                           #
#############################################################################

  # Check for expected reported error
  tst.eval(app.get_event("RBSYS_StackOverUnderFlow").is_failed())
  app.run_until_bfm_was_updated()
  tst.eval_eq(app.get_bfm_record("RBSYS_StackOverUnderFlow").get_debug0(), expectedDbg0)

  # Reset test environment to check the next check pattern
  app.do_test_environment_reset()

tst.end()