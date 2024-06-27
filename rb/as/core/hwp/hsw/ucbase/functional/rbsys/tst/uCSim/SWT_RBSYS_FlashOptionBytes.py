'''
/**
 * \TestCaseName SWT_RBSYS_FlashOptionBytes.py
 *
 * \Purpose Verify ECLK frequency
 *
 * \Reference Gen_SWCS_HSW_uC_Base_SYS-230, Gen_SWCS_HSW_uC_Base_SYS-283
 *
 * \Sequence
 * - Run system until init is done
 * - Check if Flash Option Bytes are initialized (e.g. by boundary check)
 *
 * \ExpectedResult
 * - Flash Option Bytes are initialized
 */
'''

import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import swt2.environment as env


app.execution_condition("ALWAYS")

tst.start()

# Run for some time to ensure that Test Environment is loaded
tgt.run(10, "ms")

if env.is_renesas_p1x_device():
  tst.eval(tgt.read_memory_uint32(0x0FF00040) != 0) # Option Bytes in HexFile shall be set (0x0FF00040 -> start address)
  tst.eval(tgt.read_memory_uint32(0x0FF000FC) != 0) # Option Bytes in HexFile shall be set (0x0FF000FC -> end address)
elif env.is_renesas_u2a_device() or env.is_renesas_u2c_device():
  tst.eval(tgt.read_memory_uint32(0xFF321380) == 0) # Option Bytes in HexFile shall be set (0xFF321300 -> start address)
  tst.eval(tgt.read_memory_uint32(0xFF3213FC) != 0) # Option Bytes in HexFile shall be set (0xFF32147C -> end address)

tst.end()
