import subprocess
import sys
import threading
import time

"""
ATTENTION: This file was copied from bauhaus tooling.
"""

buf = ''


class CallProcException(Exception):
    def __init__(self, message, output):
        super(CallProcException, self).__init__(message)

        self.output = output


# read by thread from async subprocess
# reason: call of read(1) blocks when no new data is available
def read_async_proc_output(proc):  # output-consuming thread
    global buf
    buf = ''
    while True:
        output = proc.stdout.read(1)
        if output == '' and proc.poll() is not None:
            # proc has terminated, end reading, close stdout
            break
        if output:
            buf += output
    proc.stdout.close()


# sleep time should be a multiple of print_interval
def dotted_sleep_ms(sleep_ms, print_str=".", print_interval_ms=1000):
    for i in range(int(sleep_ms / print_interval_ms)):
        sys.stdout.write(print_str)
        sys.stdout.flush()
        time.sleep(print_interval_ms / 1000)


def can_stdin_be_duplicated():
    # https://stackoverflow.com/questions/13442574/how-do-i-determine-if-sys-stdin-is-redirected-from-a-file-vs-piped-from-another
    import os
    import io

    if sys.stdin is None:
        # when RBHSWTESTS_PreBuild is called from within Bauhaus Starter, stdin is None
        print("INFO: stdin is None. Will specify PIPE for subprocess.")
        return False

    try:
        # if stdin can be accessed via fileno and fstat can be called on it:
        # assuming subprocess can duplicate handle
        fileno = sys.stdin.fileno()
        os.fstat(fileno)
        return True
    except OSError:
        # catch "[Error 6] The handle is invalid" if os.fstat() cannot be called on the file handle
        print("INFO: OSError Exception occurred during access of stdin. Will specify PIPE for subprocess.")
        return False
    except io.UnsupportedOperation:
        # catch access exception of sys.stdin.fileno()
        print("INFO: UnsupportedOperation Exception occurred during access of stdin. Will specify PIPE for subprocess.")
        return False


def call_proc(command, return_after_time_ms=-1, print_output=False, return_output=False, eval_returncode=True):
    global buf

    output = ''

    '''
    iae8fe: if stdin is not specified subprocess will try to duplicate the handle of the calling process.
            however if the calling process is already using a duplicated handle, or if stdin does not exist,
            this will result in "[Error 6] The handle is invalid" 
            
            See https://bugs.python.org/issue3905:
            "Note, however, that a process can create a duplicate console handle only for its own use".
    
    wre2abt: specification of stderr to .PIPE results in wrong return code of scm.exe in Python 2.7.12
    '''
    try:
        proc_stdout = subprocess.PIPE
        proc_stdin = None
        proc_stderr = None

        if not can_stdin_be_duplicated():
            proc_stdin = subprocess.PIPE
            proc_stderr = subprocess.PIPE

        proc = subprocess.Popen(command,
                                stdin=proc_stdin,
                                stdout=proc_stdout,
                                stderr=proc_stderr,
                                universal_newlines=True)

    except OSError as err:
        raise CallProcException(
            "Call of command '{}' failed (errno={}):\n{}".format(
                command, err.errno, str(err)), '')

    if return_after_time_ms == -1:
        # run until process is terminated AND no output is in stdout
        # proc.poll() sets proc.returncode when process is terminated
        while True:
            line = proc.stdout.readline()
            if line == '' and proc.poll() is not None:
                # proc has terminated, end reading, close stdout
                proc.stdout.close()
                break
            if line:
                if print_output:
                    sys.stdout.write(line)
                if return_output:
                    output += line

    else:
        # read from subprocess by thread because process runs async and read blocks
        read_thread = threading.Thread(target=read_async_proc_output, args=(proc,))
        read_thread.daemon = True
        read_thread.start()

        # wait some time, write current output to console and return proc, process is still running
        dotted_sleep_ms(return_after_time_ms)
        print("")

        sys.stdout.write(buf)

    sys.stdout.flush()

    # has executed command terminated successfully? (not for async call)
    if return_after_time_ms == -1:
        if eval_returncode and proc.returncode != 0:
            raise CallProcException(
                "Execution of command '{}' failed (exitcode={})".format(
                    command, proc.returncode), output)

    if return_output:
        return proc, output
    else:
        return proc
