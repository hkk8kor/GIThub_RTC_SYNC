REM create new "Gen" directory if it doesn't exists
mkdir ..\..\..\..\..\..\..\..\..\..\Gen

REM Doxygen can be installed via ISM profiler (ism_doxygen_18x)
C:\tools\doxygen\1.8.9.1\bin\doxygen.exe RBSYS_doxygen_config.dxc

pause