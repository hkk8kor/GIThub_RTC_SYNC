import re

import sys
import copy
from datetime import datetime

# Script to automatically run TPSW tests in a Multi or simulation debugger
#
# Basic test design:
#   The script basically controls a debugger and captures data if an exception in the Software under Test
#   (SUT) occurs. The SUT runs its test case list (see RBTPSW_MyTPSW1.c, TPSW1_TestExecution()) basically
#   in an automated fashion. The script catches the test results.
#   The end of a test run is detected if the test case id starts reoccurring.
#   Passed test cases as well as false positives/negatives are detected.
#   Also testcases which should reset but don't and those that shouldn't reset but do are detected.
#   For each test case the result is printed out.
#
#   The records the exception data in array captured_data[].
#
# Possible result stati:
# * PASSED             : For this test id captured and expected result have an
#                        exception. Captured exception data matches expected exception data.
# * FAILED             : For this test id captured and expected result have an
#                        exception. Captured exception data does NOT match expected exception data.
# * FALSE_NEG          : For this test id expected test results expect an
#                        exception. Captured data misses this exception.
# * FALSE_POS          : For this test id expected test results do not expect
#                        an exception. But captured data experiences an exception.
# * FAILED_NO_RESET    : For this test id a reset was expected but none occured
# * FAILED_FALSE_RESET : For this test id no reset was expected but a reset occured


# Usage:
#   In MULTI command pane run:
#
#     py -f run_tpsw_tests.py [<filename> [append]]
#
#   It will set the breakpoint in ProtectionHook(), record test results, end capturing if
#   testid is recycling to "1", dump the result.
#   If no <filename> is specified, it will dump to MULTI Cmd pane.
#   If <filename> is given:
#     <filename> will be opened for output. File contents will be overwritten unless "append" is
#     specified after <filename>. If "append" is given, test result will be appended to the contents.
#     If <filename> ends with ".csv", contents will be written as CSV (separated with ';')

# ------------------------------------------------------------------------------------------------
# ------------------------------------------------------------------------------------------------

class DbgInterface:
    """Abstract class defining an interface to the debugger."""
    def setNumVariableValue(self, varname, value):
        """Set the value of numerical variable with name "varname" to the value "value"."""
        pass

    def getNumVariableValue(self, varname):
        """Returns the value of numerical variable with name "varname"."""
        pass

    def isFunctionSwitchConfiguredAs(self, fs, fs_config):
        """Returns whether the value of function switch "fs" is equal to "fs_config"."""
        pass

    def getCPURegisterValue(self, regname):
        """Returns the value of register with name "regname"."""
        pass

    def addBreakpointAtEndOfFunction(self, symname):
        """Add a breakpoint at the end of function with name "symname"."""
        pass

    def setBreakpoint(self, address):
        """Sets an execution breakpoint to address "address". "address" can be a symbol name or a memory address."""
        pass

    def removeBreakpoint(self, address):
        """Removes a previous set execution breakpoint at address "address". "address" can be a symbol name or a memory address."""
        pass

    def setCurrentCore(self, core_index):
        """Sets the debugger interface command target to a CPU core with numerical index core_index.
        Methods setVariableValue(), getVariableValue(), setBreakpoint() and resume() are
        directed to the current core."""
        pass

    def resume(self):
        """Continues current CPU core."""
        pass

    def waitToStop(self):
        """Waits until any CPU runs into a breakpoint. The current core will be the core which ran into the breakpoint."""
        pass

    def evaluate(self, expression):
        """Calledback for testframework to register passed/failed of test cases"""
        pass

    def getNumberOfCores(self):
        """Gets the number of cores"""
        pass


# ------------------------------------------------------------------------------------------------


###################################################################################
# Implementation of DbgInterface for Multi
###################################################################################
class GHSDbgInterface(DbgInterface):
    def __init__(self, debug_window):
        self.dw = debug_window

    def setNumVariableValue(self, varname, value):
        """Set the value of numerical variable with name "varname" to the value "value"."""
        status = self.dw.RunCmd('%s = %d' % (varname, value), True, False)

    def getNumVariableValue(self, varname):
        """Returns the value of numerical variable with name "varname"."""
        status = self.dw.RunCmd('mprintf("%%u", %s)' % varname, True, False)
        return int(self.dw.cmdExecOutput)

    def isFunctionSwitchConfiguredAs(self, fs, fs_config):
      self.dw.RunCmd('e main', True, False) # without this, values can sometimes not be fetched
      self.dw.RunCmd('mprintf("%%u", %s)' % fs, True, False)
      fs_value = int(self.dw.cmdExecOutput)
      self.dw.RunCmd('mprintf("%%u", %s)' % fs_config, True, False)
      fs_config_value = int(self.dw.cmdExecOutput)
      return fs_value == fs_config_value

    def getCPURegisterValue(self, regname):
        """Returns the value of register with name "regname"."""
        status = self.dw.RunCmd('mprintf("%%u", $%s)' % regname, True, False)
        return int(self.dw.cmdExecOutput)

    def addBreakpointAtEndOfFunction(self, symname):
        """Add a breakpoint at the end of function with name "symname"."""
        address = self.getFunctionReturnAddress(symname)
        self.setBreakpoint(address)

    def getFunctionReturnAddress(self, symname):
        """Returns the return address of function with name "symname"."""
        status = self.dw.RunCmd('mprintf("%%u", $retadr(%s))' % symname, True, False)
        return int(self.dw.cmdExecOutput)

    def setBreakpoint(self, address):
        """Sets an execution breakpoint to address "address". "address" can be a symbol name or a memory address."""
        if type(address) in [int, long]:
            address = "0x%x" % address
        status = self.dw.RunCmd('b %s' % address, True, False)

    def removeBreakpoint(self, address):
        """Removes a previous set execution breakpoint at address "address". "address" can be a symbol name or a memory address."""
        if type(address) == int:
            address = "0x%x" % address
        status = self.dw.RunCmd('d %s' % address, True, False)

    def setCurrentCore(self, core_index):
        """Sets the debugger interface command target to a CPU core with numerical index core_index.
        Methods setVariableValue(), getVariableValue(), setBreakpoint() and resume() are
        directed to the current core."""
        if core_index != 0 and core_index != 1:
            # only 0 and 1 are allowed!
            return
        #sets the desired core my matching "Core %d" to the first possible expression (works for both targets)
        status = self.dw.RunCmd('switch -item "Core %d"' % core_index, True, False)
        return

    def resume(self):
        """Continues current CPU core."""
        status = self.dw.Resume(True, False)

    def waitToStop(self):
        """Waits until any CPU runs into a breakpoint. The current core will be the core which ran into the breakpoint."""
        status = self.dw.WaitToStop()

    def getNumberOfCores(self):
        self.dw.RunCmd("P", True, False)
        num = len(self.dw.cmdExecOutput.splitlines()) - 1 #Remove header line
        num = min(num, 2) #Limit to 2 cores as we don't use more
        return num


app_status = { 0: "ACTIVE (0)", 1: "NOT_ACTIVE (1)"}
debugapp_status = { 0: "DEBUG_ACTIVE (0)", 1: "DEBUG_EXC_ABORTED (1)", 2: "DEBUG_SW_ABORTED (2)", 3: "DEBUG_TIMING_ABORTED (3)" }
result_status = { 0:"PASSED", 1: "FAILED", 2: "FALSE_NEG", 3: "FALSE_POS", 4: "FAILED_NO_RESET", 5: "FAILED_FALSE_RESET"}

printHexKeys = ['feic', 'CallCoreFnPtr', 'rh850_fepc', 'rh850_mei', 'rh850_mea', 'rh850_fepsw', 'rh850_fpsr', 'rh850_fpepc', 'core'] #Keys to print in hex

resultKeys = ['feic', 'userInfo', 'osStatus', 'debugStatus'] #Checked keys
auxKeys = ['CallCoreFnPtr', 'rh850_fepc', 'rh850_mei', 'rh850_mea', 'rh850_fepsw', 'rh850_fpsr', 'rh850_fpepc'] # unchecked auxiliary information

# prefix of all expected data column names
EXP_PREFIX = 'exp_'

def mergeDictonaries(*dicts):
    res = {}
    for d in dicts:
        res.update(d)
    return res

def getAppResult(dbg, testResultVariable):
    res = {}
    res['feic']        = dbg.getNumVariableValue(testResultVariable + '.feic')
    res['userInfo']    = dbg.getNumVariableValue(testResultVariable + '.userInfo')
    res['osStatus']    = dbg.getNumVariableValue(testResultVariable + '.osStatus')
    res['debugStatus'] = dbg.getNumVariableValue(testResultVariable + '.debugStatus')
    return res

def getAuxInfo(dbg, testResultVariable):
    res = {}
    res['CallCoreFnPtr'] = dbg.getNumVariableValue(testResultVariable + '.callCoreFnPtr')
    res['rh850_fepc']    = dbg.getNumVariableValue(testResultVariable + '.rh850_fepc')
    res['rh850_mei']     = dbg.getNumVariableValue(testResultVariable + '.rh850_mei')
    res['rh850_mea']     = dbg.getNumVariableValue(testResultVariable + '.rh850_mea')
    res['rh850_fepsw']   = dbg.getNumVariableValue(testResultVariable + '.rh850_fepsw')
    res['rh850_fpsr']    = dbg.getNumVariableValue(testResultVariable + '.rh850_fpsr')
    res['rh850_fpepc']   = dbg.getNumVariableValue(testResultVariable + '.rh850_fpepc')
    return res
    
def getTPSWResult(dbg):
    res = {}
    numberOfCores = dbg.getNumberOfCores()
    for i in range(10):
        appEntry = {}
        testResultVar = 'RBTPSW_result[%d]'%i
        appEntry['expectedAppStatus'] = dbg.getNumVariableValue(testResultVar + '.expectedAppStatus')
        appEntry['actualAppStatus'] = dbg.getNumVariableValue(testResultVar + '.actualAppStatus')
        appEntry['coreResult'] = []
        for core in range(numberOfCores):
            testResultVarCore = testResultVar + '.coreResult[%i]'%core
            status = dbg.getNumVariableValue(testResultVarCore + '.status')
            expectedValues = getAppResult(dbg, testResultVarCore + '.expectedResult')
            actualValues = getAppResult(dbg, testResultVarCore + '.actualResult')
            auxInfo = getAuxInfo(dbg, testResultVarCore + '.auxInfo')
            resultEntry = {'expected': expectedValues, 'actual': actualValues, 'aux': auxInfo, 'status': status}
            appEntry['coreResult'].append(resultEntry)
        res['MYTPSW%d'%(i+1)] = appEntry
    return res

def stringify(data):
    cpy = copy.deepcopy(data)
    for key in cpy:
        if key == 'appStatus':
            cpy[key] = 'NOT_ACTIVE (1)' if cpy[key] == 1 else 'ACTIVE (0)'
        elif key == 'debugStatus':
            cpy[key] = debugapp_status[cpy[key]]
        elif key in printHexKeys:
            cpy[key] = '0x%08x'%cpy[key]
        else:
            cpy[key] = str(cpy[key])
    return cpy

def test_dump(dbg, results, outstream, sep = '\t', eol = '\n'):
    """Walks captured data and compares expected and actual results. 
    Based on the result a line for each result is dumped."""
    #Write header
    outstream.write('Result, testid, app, ')
    outstream.write('appStatus, ')
    outstream.write(', '.join(resultKeys) + ', ')
    outstream.write(EXP_PREFIX + 'appStatus, ')
    outstream.write(', '.join([EXP_PREFIX + x for x in resultKeys]) + ', ')
    outstream.write(', '.join(auxKeys) + ', ')
    outstream.write('core\n')
    numberOfCores = dbg.getNumberOfCores()
    #Go through executed testcases
    for testid, testCaseResult in results.items():
        printedAppResult = False
        #Go through the results of all apps
        for app, appResult in testCaseResult.items():
            for core in range(numberOfCores):
                result = appResult['coreResult'][core]
                status = result['status']
                if status == 0 and appResult['expectedAppStatus'] == 0:
                    #We don't print non failed Apps which don' expect an exception
                    continue
                actual = stringify(result['actual'])
                expected = stringify(result['expected'])
                aux = stringify(result['aux'])
                dbg.evaluate(status == 0) #Inform the testframework about the result
                printedAppResult = True
                resultString = result_status[status]
                outstream.write('{resultString}, {testid}, {app}, {appStatus}, '.format(resultString=resultString, testid=testid, app=app, appStatus=app_status[appResult['expectedAppStatus']]))
                outstream.write(', '.join([actual[key] for key in resultKeys]) + ', ')
                outstream.write(app_status[appResult['actualAppStatus']] + ', ')
                outstream.write(', '.join([expected[key] for key in resultKeys]) + ', ')
                outstream.write(', '.join([aux[key] for key in auxKeys]) + ', ')
                outstream.write(str(core))
                outstream.write('\n')
        if not printedAppResult:
            dbg.evaluate(True)
            outstream.write('PASSED,{testid}\n'.format(testid=testid))

def test_setup(dbg):
    """Run to main() to let RAM be initialized, set up ProtectionHook() breakpoint"""

    # select core
    dbg.setCurrentCore(0)
    # set breakpoint at main
    dbg.setBreakpoint("main")

    # Set breakpoints for all cores
    for core in range(dbg.getNumberOfCores()):
        # select core
        dbg.setCurrentCore(core)
        # set breakpoint at RBTPWS_CheckTestResult()
        dbg.addBreakpointAtEndOfFunction("RBTPSW_CheckTestResultFailed")
        # run core (continue)
        dbg.resume()
    # wait for main() breakpoint in order to let RAM (global variables) be set up
    dbg.waitToStop()
    # remove breakpoint at main, required by SVP reset tests
    dbg.setCurrentCore(0)
    dbg.removeBreakpoint("main")


def test_record(dbg, start_testid, end_testid):
    # initialize test
    testid = 0
    doublecount = 0
    capturedData = {}
    # initialize test id to start_testid-1
    dbg.setNumVariableValue("TPSW2_TestCaseId", start_testid-1)

    # ensure we have testid == start_testid after hitting breakpoint the first time
    while testid != start_testid:
        dbg.resume()
        dbg.waitToStop()
        newtestid = dbg.getNumVariableValue("TPSW2_TestCaseId")
        if newtestid == testid:
            doublecount += 1
            if doublecount == 5:
                print('Aborting because testid is repeating(%d).' % testid)
                return capturedData
        else:
            doublecount = 0
        testid = newtestid

    # We have confirmed expected start conditions.
    # Now loop through all tests until testid restarts from start_testid-1.
    while testid > 0:
        # At the top of the loop we are halted by a breakpoint and we have a valid testid.

        # Get Test results
        data = getTPSWResult(dbg)
        # add testid number to test data set
        capturedData[testid] = data
        print('Catched testcase %d' % testid)

        if testid == end_testid:
            #This was the last test we wanted to execute
            break
        # resume execution
        dbg.resume()
        # wait until next breakpoint
        dbg.waitToStop()
        # retrieve current testid
        newtestid = dbg.getNumVariableValue("TPSW2_TestCaseId")
        if newtestid == testid:
            # this is an exit criteria if test execution is not following expectation
            # to prevent test from looping infinitely
            doublecount += 1
            if doublecount == 10:
                # abort on 10 breaks with the same testid.
                print('Aborting because testid is repeating(%d).' % testid)
                return capturedData
        else:
            doublecount = 0
        #Check for wrap around of tests and abort
        if newtestid < testid:
            break
        testid = newtestid
    return capturedData


def executeTests(dbg, filename=None, filemode="w", outstream=sys.stdout, sep='\t', eol='\n', start_testid = 1, end_testid = 0):
    t_start = datetime.now()

    test_setup(dbg)
    # run tests
    results = test_record(dbg, start_testid, end_testid)
    # dump result
    test_dump(dbg, results, outstream, sep, eol)
    t_delta = datetime.now() - t_start

    # close file, if filename given
    if filename:
        outstream.close()

    # write finish statement to Cmd pane
    stmt = 'TPSW test script finished. Runtime (h:m:s) %s.' % str(t_delta).split('.')[0]
    if filename:
        stmt += " Result written to '%s'." % filename
    stmt += '\n'
    print(stmt)


# ------------------------------------------------------------------
# script main
# ------------------------------------------------------------------
if __name__ == '__main__':

    # default output stream is stdout
    outstream = sys.stdout
    sep = '\t'
    eol = '\n'
    filename = None
    filemode = None
    start_testid = 1
    count = 0
    end_testid = 0

    debugger = 'multi'
    # parse script parameters
    while len(sys.argv) > 1:
        opt = sys.argv.pop(1)
        if opt == '-o':
            # filename given
            filename = sys.argv.pop(1)
            filemode = "w"
        elif opt == '-a':
            # append file
            filemode = 'a'
        elif opt == '-d':
            # select debugger
            debugger = sys.argv.pop(1)
        elif opt == '-S':
            # set startID of test run
            start_testid = int(sys.argv.pop(1))
        elif opt == '-C':
            # set count of test runs
            count = int(sys.argv.pop(1))

    if count > 0:
        end_testid = start_testid + count

    if filename:
        if filename.lower().endswith('.csv'):
            # file is a CSV, use ";" as column separator
            sep = ';'
        # open file
        outstream = open(filename, filemode)

    # set up debugger
    if debugger == 'multi':
        dbg = GHSDbgInterface(self_dbw)
    elif debugger == 'vlab':
        pass

    executeTests(dbg, filename, filemode, outstream, sep, eol, start_testid, end_testid)

