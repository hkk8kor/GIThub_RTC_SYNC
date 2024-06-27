REM This batch removes not allowed OS features for CC-AS; mainly not allowed interrupt locks and resources
REM (which are unsafe for multi-core systems)
REM OS spinlocks are removed as well (even if file is empty when no lock is configured in the OS) -> CC-AS specific spinlocks used

REM CC org: DisableAllInterrupts.obj EnableAllInterrupts.obj ResumeAllInterrupts.obj ResumeOSInterrupts.obj SuspendAllInterrupts.obj SuspendOSInterrupts.obj Os_ExceptionVectors.obj
REM keep OS resources - required for RTE

del RTAOS_new.txt
del RTAOS_old.txt

%1\ax.exe -tv .\RTAOS.a >> RTAOS_old.txt
%1\ax.exe -d .\RTAOS.a   DisableAllInterrupts.o  EnableAllInterrupts.o  SuspendAllInterrupts.o ResumeAllInterrupts.o SuspendOSInterrupts.o ResumeOSInterrupts.o GetSpinlock.o ReleaseSpinlock.o
%1\ax.exe -tv .\RTAOS.a >> RTAOS_new.txt

call c:\tools\zip.exe -9 -q -u out.zip RTAOS_new.txt
call c:\tools\zip.exe -9 -q -u out.zip RTAOS_old.txt

del RTAOS_new.txt
del RTAOS_old.txt