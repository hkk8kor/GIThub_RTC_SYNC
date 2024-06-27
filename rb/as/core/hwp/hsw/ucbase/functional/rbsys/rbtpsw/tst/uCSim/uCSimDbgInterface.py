import swt2.target as tgt
import swt2.test as tst
import swt2.application as app
import swt2.software as sw
import swt2.environment as env

import rbtpsw_tests_hsw

###################################################################################
# Implementation of DbgInterface for VLAB
###################################################################################
class SWTDbgInterface(rbtpsw_tests_hsw.DbgInterface):
    def __init__(self):
        self.core = tgt.get_core()
        self.stoppedCore = tgt.get_core()
        self.breakpoints = []

    def setNumVariableValue(self, varname, value):
        """Set the value of numerical variable with name "varname" to the value "value"."""
        # print("-------> setNumVariableValue %s <- %d" % (varname, value))
        sw.get_variable(varname).write(value)

    def getNumVariableValue(self, varname):
        """Returns the value of numerical variable with name "varname"."""
        # print("-------> getNumVariableValue %s" % (varname))
        return sw.get_variable(varname).read()

    def isFunctionSwitchConfiguredAs(self, fs, fs_config):
      return app.get_function_switch_setting(fs) == fs_config

    def getCPURegisterValue(self, regname):
        """Returns the value of register with name "regname"."""
        registerPath = self.stoppedCore + "."
        try:
            value = tgt.get_register(registerPath + regname.upper().read())
        except ValueError:
            value = tgt.get_register(registerPath + regname).read()
        return value

    def addBreakpointAtEndOfFunction(self, address):
        """Add a breakpoint at the end of function with name "symname"."""
        def breakpointAction(br):
          self.stoppedCore = br.core
          br.breakpoint.interrupt()

        bp = tgt.add_breakpoint_at_end_of(address, core=self.core, action=breakpointAction)
        bp_and_id = {"address": str(address), "core": self.core, "bp": bp}
        self.breakpoints.append(bp_and_id)
        

    def setBreakpoint(self, address):
        """Sets an execution breakpoint to address "address". "address" can be a symbol name or a memory address."""
        # print("-------> setBreakpoint %s for core %s" % (str(address), self.core))

        def breakpointAction(br):
          self.stoppedCore = br.core
          br.breakpoint.interrupt()

        bp = tgt.add_breakpoint(address, core=self.core, action=breakpointAction)
        bp_and_id = {"address": str(address), "core": self.core, "bp": bp}
        self.breakpoints.append(bp_and_id)

    def removeBreakpoint(self, address):
        """Removes a previous set execution breakpoint at address "address". "address" can be a symbol name or a memory address."""
        # print("-------> removeBreakpoint %s for core %s" % (str(address), self.core))

        bps_to_remove = list(filter(lambda item: item["address"] == str(address) and item["core"] == self.core, self.breakpoints))
        for bp in bps_to_remove:
            bp["bp"].remove()
            self.breakpoints.remove(bp)

    def setCurrentCore(self, core_index):
        """Sets the debugger interface command target to a CPU core with numerical index core_index.
        Methods setVariableValue(), getVariableValue(), setBreakpoint() and resume() are
        directed to the current core."""
        # print("-------> setCurrentCore %d" % (core_index))
        if core_index >= app.get_number_of_used_cores():
          print("Invalid core index %d" % core_index)
          return None
        self.core = tgt.get_core(core_index)

    def resume(self):
        """Continues current CPU core."""
        # print("-------> resume")
        pass

    def waitToStop(self):
        """Waits until any CPU runs into a breakpoint. The current core will be the core which ran into the breakpoint."""
        # print("-------> waitToStop")
        tgt.run()

    def evaluate(self, expression):
        """Calledback for testframework to register passed/failed of test cases"""
        tst.eval(expression)

    def getNumberOfCores(self):
        return app.get_number_of_used_cores()
