'''
/**
 * \TestCaseName SWT_RBSYS_ClockHandling.py
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-208
 *
 * \Purpose Check that Renesas microcontroller errata RB095 "Updating failure of ECLK" is handled as recommended
 *
 * \Sequence
 *  - Let system run until initialization is done and record all relevant register accesses
 *  - Check that recorded accesses comply with the recommended procedure for CLKD2 and CLKD3:
 *    Step 0: CLKDxDIV  is written
 *    Step 1: CLKDxDIV  is read
 *    Step 2: CLKDxSTAT is read until it becomes 0x3
 *    Step 3: CLKDxSTAT is read at least 4 more times
 *    Step 4: CLKDxDIV  is written again with the same value
 *    Step 5: CLKDxDIV  is read
 *    Step 6: CLKDxSTAT is read until it becomes 0x3
 *
 * \ExpectedResult
 * - CLKD2 and CLKD3 registers are written to and read from in the recommended sequence
 */
'''


import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import re


app.execution_condition(include_switches=["RBFS_uCFamily_RenesasP1x"])

#############################################################################
#                        Helper Functions                                   #
#############################################################################

# callback for recording write operations
def RegisterAccess(br):
  # calculate register index from register name
  index = int(re.search(r"([0-9])[A-Z]*$", br.register.get_path()).group(1)) - 2
  records[index].append((br.register.get_path(), br.data, br.access))



#############################################################################
#                             Setup                                         #
#############################################################################

# get references to relevant registers
regCLKDxDIV  = [0,0]
regCLKDxSTAT = [0,0]
regCKSCxC    = [0,0]
regCKSCxS    = [0,0]
for i in range(0,2):
  regCLKDxDIV[i]  = "RH850.PFRH850.SYSCTL.CLKCTL_CCC.CLKD%dDIV" % (i+2)
  regCLKDxSTAT[i] = "RH850.PFRH850.SYSCTL.CLKCTL_CCC.CLKD%dSTAT" % (i+2)
  regCKSCxC[i]    = "RH850.PFRH850.SYSCTL.CLKCTL_CCC.CKSC%dC" % (i+2)
  regCKSCxS[i]    = "RH850.PFRH850.SYSCTL.CLKCTL_CCC.CKSC%dS" % (i+2)

# stores all register accesses in the order they happen
records = [[],[]]

# add breakpoints for register accesses in order to record them
for i in range(0,2):
  tgt.add_register_breakpoint(regCLKDxDIV[i],  "write", RegisterAccess)
  tgt.add_register_breakpoint(regCKSCxC[i],    "write", RegisterAccess)
  tgt.add_register_breakpoint(regCLKDxDIV[i],  "read",  RegisterAccess)
  tgt.add_register_breakpoint(regCLKDxSTAT[i], "read",  RegisterAccess)

# list that stores the order in which registers are expected to be accesses
steps = [[],[]]
for i in range(0,2):
  steps[i] = [
    (regCLKDxDIV[i],  "write"),
    (regCLKDxDIV[i],  "read"),
    (regCLKDxSTAT[i], "read"), # until value is 0x3
    (regCLKDxSTAT[i], "read"), # at least 4 times
    (regCLKDxDIV[i],  "write"),
    (regCLKDxDIV[i],  "read"),
    (regCLKDxSTAT[i], "read")  # until value is 0x3
  ]



#############################################################################
#                             Test start                                    #
#############################################################################

tst.start()

# run until initialization is done and all clock configurations should be done
tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")

# check that recorded register accesses comply with recommended procedure
# this is done with a state machine that handles the next record according to the current step it is in
for i in range(0,2):
  # stores the current step the state machine is in
  step = 0
  # stores the value of first the write operation on CLKDxDIV
  CLKDxDIVFirstWrite = 0
  # stores the last value written to CKSCxC
  CKSCxCLastWrite = 0
  # stores the number of read operations on CLKDxSTAT after the clock has become active
  CLKDxSTATReadCounter = 0

  for (register, data, operation) in records[i]:

    # Step 0: CLKDxDIV is written
    if(step == 0 and register == regCLKDxDIV[i] and operation == "write"):
      CLKDxDIVFirstWrite = data
      step = step + 1

    #Step 1: CLKDxDIV is read
    elif(step == 1 and register == regCLKDxDIV[i] and operation == "read"):
      tst.eval_eq(CLKDxDIVFirstWrite, data)
      step = step + 1

    # Step 2: CLKDxSTAT is read until it becomes 0x3
    elif(step == 2 and register == regCLKDxSTAT[i] and operation == "read"):
      if(data == 0x3):
        step = step + 1

    # Step 3: CLKDxSTAT is read at least 4 more times
    elif(step == 3 and register == regCLKDxSTAT[i] and operation == "read"):
      CLKDxSTATReadCounter = CLKDxSTATReadCounter + 1
      if(CLKDxSTATReadCounter >= 4):
        step = step + 1

    # Step 4: CLKDxDIV is written again with the same value
    elif(step == 4 and register == regCLKDxDIV[i] and operation == "write"):
      tst.eval_eq(CLKDxDIVFirstWrite, data)
      if(CLKDxDIVFirstWrite == data):
        step = step + 1

    # Step 5: CLKDxDIV is read
    elif(step == 5 and register == regCLKDxDIV[i] and operation == "read"):
      tst.eval_eq(CLKDxDIVFirstWrite, data)
      step = step + 1

    # Step 6: CLKDxSTAT is read until it becomes 0x3
    elif(step == 6 and register == regCLKDxSTAT[i] and operation == "read"):
      if(data == 0x3):
        step = 0
        CLKDxDIVFirstWrite = 0
        CKSCxCLastWrite = 0
        CLKDxSTATReadCounter = 0
    else:
      # unexpected operation on register, okay if read operation, might be bad on write operation
      if(operation == "write"):
        # writes to CKSCxC are okay before waiting that the clock is active or if the value of the register is not changed
        if(register == regCKSCxC[i] and (step <= 2 or CKSCxCLastWrite == data)):
          CKSCxCLastWrite = data
          continue
        else:
          # throw error with expected operation
          tst.eval_eq(steps[i][step], (register, operation))

  # in the end the state machine has to be in step 0 again,
  # either there were no operation recorded or the procedure was executed correctly, possibly multiple times
  tst.eval_eq(step, 0)

tst.end()