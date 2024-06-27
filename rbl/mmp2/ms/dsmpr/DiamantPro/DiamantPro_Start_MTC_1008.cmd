@echo off
setlocal
:: title of console
title start DiamantPro
cls

:: jump to root directory of project
pushd ..\..\..\..\..\..\

:: +----------------------------------------------------------+
:: | GENERAL SETTINGS...                                      |
:: +----------------------------------------------------------+ 
:: CURRENT DIR where batch is located
::SET CURRENT_DIR=%~dp0
SET DIAMANTPRO_VERSION=3_3_r1588
                    
:: +----------------------------------------------------------+
:: | PROJECT SETTINGS...                                      |
:: +----------------------------------------------------------+ 
:: set the config for the make file generation
SET TARGET_CONFIG=HWRefDiamantGen

:: select corresponding make folder

:: if make folder already exists it should be deleted to be sure the have the actual file list
IF EXIST %MAKE_FOLDER% del /q %MAKE_FOLDER% 
::
SET MAKE_FOLDER=%CD%\Gen\%TARGET_CONFIG%\make

:: +----------------------------------------------------------+
:: | Check whether build required                              |
:: +----------------------------------------------------------+

IF NOT EXIST C:\MTC10Tools\DiamantPro\V%DIAMANTPRO_VERSION%\DiamantProGUI.exe GOTO ERR_DIAMANTPRO_NOT_EXIST




:: +----------------------------------------------------------+
:: | Check whether build required                              |
:: +----------------------------------------------------------+ 
:CHECK_MAKE_EXISTS
:: if make folder already exists it should be deleted to be sure the have the actual file list
IF EXIST %MAKE_FOLDER% del /q %MAKE_FOLDER%

:RUN_MAKE
Powershell C:\MTC10Base\StartMTC\Start-MTC.ps1 -RootDir . -Config %TARGET_CONFIG% -GenerateMakefile

:RUN_DIAMANTPRO	
::start diamant pro by giving the file list from make and the path for generated items
@echo on
C:\MTC10Tools\DiamantPro\V%DIAMANTPRO_VERSION%\DiamantProGUI.exe  --READSPLITTER=%MAKE_FOLDER%\Cfg_DBFiles_GenMake.csv --SETCAPTION="Failure word used information captured now with Diamant__FWUsed*.txt files"
@echo off
GOTO END

:ERR_DIAMANTPRO_NOT_EXIST
echo +-------------------------------------------------------------------------------------+
echo the Diamantpro version V%DIAMANTPRO_VERSION% does not exists and is not installed. 
echo Please install MTC version 10.0.9.0 (or higher) first, to get the right version.
echo +-------------------------------------------------------------------------------------+
set ERRORLEVEL=1
pause

:END


