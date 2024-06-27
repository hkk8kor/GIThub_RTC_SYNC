@echo off
pushd %~dp0

cd ..\..\..

CALL ..\..\..\tools\python\EnsurePython.cmd

call %python_exe% .\tools\StaticCodeAnalysis\AssertSwitchSettingChecker\AssertSwitchSettingParser.py

if %errorlevel% == 0 (
  echo No Deviations found!
)

pause

popd