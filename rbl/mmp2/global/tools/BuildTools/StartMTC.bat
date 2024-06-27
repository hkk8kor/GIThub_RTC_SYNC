set BV=%1
set OPTION=%2
powershell -command "C:\MTC10Base\StartMTC\Start-MTC.ps1 -RootDir . -BuildTarget BUILD -Config %BV% %OPTION%