del out.zip

call c:\tools\zip.exe -9 -r -q -S out.zip .\out

xcopy /s /y ".\out\Configuration Summary.css"   .\doc\
xcopy /s /y ".\out\Configuration Summary.html"  .\doc\
xcopy /s /y ".\out\Configuration Summary.txt"   .\doc\

xcopy /s /y ".\out\Misra Deviations.css"        .\doc\
xcopy /s /y ".\out\Misra Deviations.html"       .\doc\
xcopy /s /y ".\out\Misra Deviations.txt"        .\doc\

xcopy /s /y .\out\Os.h                          .\api\
xcopy /s /y .\out\Os_Cfg.h                      .\api\
xcopy /s /y .\out\os_safe_cfg.h                 .\api\
xcopy /s /y .\out\os_target_cfg.h               .\api\
xcopy /s /y .\out\Os_ConfigInterrupts.h         .\api\
xcopy /s /y .\out\Samples\includes\Os_MemMap.h  .\api\

xcopy /s /y .\out\RTAOS.orti                    .\
xcopy /s /y .\out\RTAOS.a                       .\
xcopy /s /y .\out\RTAOS.dba                     .\

rmdir /s /q .\out\