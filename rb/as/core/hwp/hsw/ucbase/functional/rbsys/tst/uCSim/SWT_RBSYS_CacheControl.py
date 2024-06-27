'''
/**
 * \TestCaseName RBSYS_CacheControl
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-257
 *
 * \Purpose Check WT Buffer Errata handling
 *
 * \Sequence
 * - Run system until start of FSW
 * - Read out WT buffer configuration
 * - Run system until after WT Buffer Errata handling
 * - Read out WT buffer configuration
 *
 * \ExpectedResult
 * - Read out WT buffer configuration has been changed correctly on the affected devices
 */
'''

import swt2.test as tst
import swt2.application as app
import swt2.target as tgt
import swt2.environment as env


app.execution_condition(include_switches=["RBFS_RenesasP1xGRAM_ON"])

# Test Design

tst.start()
GRAMC_WTBCONFIG0_ADR = 0xFFFF7A04

tgt.add_breakpoint("RBSYS_StartupPreOSPhase1", core=0)
tgt.run()

GRAMC_WTBCONFIG0_1 = tgt.read_memory_uint32(GRAMC_WTBCONFIG0_ADR)    # Read GRAMC_WTBCONFIG0

tgt.add_breakpoint("RBSYS_StartupPreOSPhase2", core=0)
tgt.run()

GRAMC_WTBCONFIG0_2 = tgt.read_memory_uint32(GRAMC_WTBCONFIG0_ADR)    # Read GRAMC_WTBCONFIG0

# of supported devices, only D3 Rev0 and D5EDv2 are affected by this Erratum see Renesas Errata RB113 in https://sites.inside-share.bosch.com/sites/078359/_layouts/15/WopiFrame2.aspx?sourcedoc=/sites/078359/Documents/uC/CC-CubePlus/Technical%20Documentation/Common%20Documents/05_uC%20errata%20assessment%20list/Renesas_Cube_CubePlus_Errata_Assessment(1).xlsx
# but D3 product information is configured for D3 RevA, this leaves only D5EDv2
if env.get_device() == "D5EDv2":
  tst.eval_eq(GRAMC_WTBCONFIG0_1, 0x1)
  tst.eval_eq(GRAMC_WTBCONFIG0_2, 0x0)
else:
  # D3 RevA, D3ED RevB (derived from D5ED Rev B), D4 RevA, D5 and D5EDv3 are unaffected by the Erratum
  # WTBCONFIG0 will not be touched
  tst.eval_eq(GRAMC_WTBCONFIG0_1, 0x1)
  tst.eval_eq(GRAMC_WTBCONFIG0_2, 0x1)

tst.end()