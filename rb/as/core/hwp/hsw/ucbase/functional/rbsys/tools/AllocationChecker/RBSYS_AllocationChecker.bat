SET BIN_PATH=%1
SET GHS_PATH=%2
SET DEVICE=%3

CALL rb\as\core\hwp\hsw\tools\python\EnsurePython.cmd

call %python_exe% -B rb\as\core\hwp\hsw\ucbase\functional\rbsys\tools\AllocationChecker\RBSYS_AllocationChecker.py %BIN_PATH% %GHS_PATH% %DEVICE%