'''
/**
 * \Purpose Verify correct configuration of FPU and CPU exception failure is reported if an FPU exception occurs.
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-174, Renesas HW Erratum 128
 *
 * \Sequence
 * - Per core:
 *   - Per FPU exception cause:
 *     - Run system until cyclic mode
 *     - Execute code that produces an FPU exception
 *     - Run system until reset occurred and the failure entry was done
 *     - Reset test environment for next loop iteration
 *   - If restrictedSPID feature is active, test all exceptions again, with SPID set to restrictedSPID
 *
 * \ExpectedResult
 * - PSW and FPSR are correctly configured
 * - FW_RBCPUException for every code injection occurred
 */
'''

import swt2.test as tst
import swt2.application as app
import swt2.target as tgt
import swt2.software as sw
import swt2.environment as env


app.execution_condition("ALWAYS")

tst.start()

exceptions = [
  (
    [  # +inf * 0.0f => (V) Invalid operation
      sw.create_instruction("RH850", "mov 0x7f800000, r6"), # r6 = +inf
      sw.create_instruction("RH850", "mulf.s r0, r6, r10"), # r10 = r6 * r0
      sw.create_instruction("RH850", "br 0x0")              # br: endless loop
    ],
    6,   # offset of exception triggering instruction in instruction list
    0x10 # expected XC bits in FPSR
  ),
  (
    [  # 1.0f/0.0f => (Z) Division by zero
      sw.create_instruction("RH850", "mov 0x3f800000, r6"), # r6 = 1.0f
      sw.create_instruction("RH850", "divf.s r0, r6, r10"), # r10 = r6 / r0
      sw.create_instruction("RH850", "br 0x0")              # br: endless loop
    ],
    6,
    0x08
  ),
]


# Test start
for coreIdx in range(2 if app.is_multi_core() else 1):
  core = tgt.get_core(coreIdx)

  # Run until init is done
  tgt.run_until("Os_Entry_TaskBaseCtrlCycx1High")

  # Check that FPU is activated
  psw = core.get_register("PSW").read()
  tst.eval((psw & 0x00010000) != 0)

  # Check FPU configuration bits FN=0 (see Renesas HW Erratum 128), PEM=1, RM=00, FS=1 and XE=11000
  fpsr = core.get_register("FPSR").read()
  tst.eval((fpsr & 0xAE03E0) == ((1 << 8) | (1 << 9) | (1 << 17) | (1 << 21)))

  # If restricted SPID feature is active, additionaly test all exceptions with restrictedSPID set
  if app.get_function_switch_setting("RBFS_SysExclusiveSPID") == "RBFS_SysExclusiveSPID_Used":
    overwriteSPIDs = [False, True]
  else:
    overwriteSPIDs = [False]

  for overwriteSPID in overwriteSPIDs:
    # Test exceptions
    for instructions, exceptionOffset, xcBits in exceptions:
      # Run until cyclic mode.
      tgt.run_until("Os_Entry_TaskBaseCtrlCycx4")

      # Goodcheck
      tst.eval(not app.get_event("RBCPUException").is_failed())

      # Manipulation
      # Currently an empty breakpoint is needed so that code at the injection location is re-fetched instead of used from VLAB's instruction cache.
      # See Mantis 8905: https://sbta.renesas.eu/mantis_bosch/view.php?id=8905
      bp = tgt.add_breakpoint(env.get_start_address_for_code_injection(), action=lambda br: None)
      tgt.run_until("RBSYS_PRC_LockMonitoring", coreIdx)
      tgt.inject_and_trigger_execution_of_instructions(instructions, env.get_start_address_for_code_injection(), coreIdx)

      # Overwrite core SPID with restrictedSPID (4) to test RBSYS_TRAP_PERMISSION_ENTRY
      if overwriteSPID:
        mcfg0 = (core.get_register("MCFG0").read() & ~(0x1F << 16)) | (0x4 << 16)
        core.get_register("MCFG0").write(mcfg0)

      # Reset should occur
      hit = tgt.is_breakpoint_hit(tgt.run_until(0x0))
      bp.remove()
      tst.eval(hit)

      if(hit):
        # Run until BFM was updated and check debug values for correctness
        app.run_until_bfm_was_updated()
        tst.eval(app.get_event("RBCPUException").is_failed())
        tst.eval_eq_x(app.get_bfm_record("RBCPUException").get_debug0(), (xcBits << 20) | (coreIdx << 16) | 0x71)
        tst.eval_eq_x(app.get_bfm_record("RBCPUException").get_debug1(), env.get_start_address_for_code_injection() + exceptionOffset)

      # Reset for next iteration
      app.do_test_environment_reset()

tst.end()
