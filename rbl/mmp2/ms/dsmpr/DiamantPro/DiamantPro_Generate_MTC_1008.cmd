@echo off
setlocal
:: title of console
title run DiamantPro generation
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
SET MAKE_FOLDER=Gen\%TARGET_CONFIG%\make


:: set output path for generated files
SET GENERATOR_OUTPUT_PATH=rb\as\ms\hwref\dsmpr\gen\DSW

:: set path for log file
SET DIAMANT_LOG=%MAKE_FOLDER%\DiamantPro.log

::set diamant pro plugin to generate ARXML file path 
SET GEN_ECUC_PLUGIN=rb\as\core\hwp\cubas\Diagnosis\tools\DiamantPro_Adapter\DiamantPro_Plugins\Diamant2EcucGeneration\Diamant_Generate_Dem_ARXML.dpp

:: +----------------------------------------------------------+
:: | Check whether tool is installed                          |
:: +----------------------------------------------------------+

IF NOT EXIST C:\MTC10Tools\DiamantPro\V%DIAMANTPRO_VERSION%\DiamantProGUI.exe GOTO ERR_DIAMANTPRO_NOT_EXIST

:: +-----------------------------------------------------------+
:: | Check whether build required                              |
:: +----------------------------------------------------------+ 
:CHECK_MAKE_EXISTS
:: if make folder already exists it should be deleted to be sure the have the actual file list
IF EXIST %MAKE_FOLDER% del /q %MAKE_FOLDER%

:RUN_MAKE
Powershell C:\MTC10Base\StartMTC\Start-MTC.ps1 -RootDir . -Config %TARGET_CONFIG% -GenerateMakefile

IF ERRORLEVEL 1 GOTO ERROR_LEVEL

:RUN_DIAMANTPRO	
:: call DiamantPro with file list generated from make
:: set generated path
:: call file generator with  m= EVO17 (mode), f (output flat)
:: call plugin for Diamant2Ecuc generation
:: generate log in make folder

@echo on
C:\MTC10Tools\DiamantPro\V%DIAMANTPRO_VERSION%\DiamantProCLI.exe  --READSPLITTER=%MAKE_FOLDER%\Cfg_DBFiles_GenMake.csv --GENPATH=%GENERATOR_OUTPUT_PATH% --PROJECTBB="PROJECT" --GENERATEFILES=  -m='GEN93' -f --RUNPLUGIN=%GEN_ECUC_PLUGIN% --LOG=%DIAMANT_LOG%
@echo off
IF ERRORLEVEL 1 GOTO ERROR_LEVEL


GOTO END
:ERR_DIAMANTPRO_NOT_EXIST
echo +-------------------------------------------------------------------------------------+
echo the Diamantpro version V%DIAMANTPRO_VERSION% does not exists and is not installed. 
echo Please install MTC version 10.0.9.0 (or higher) first, to get the right version.
echo +-------------------------------------------------------------------------------------+
pause
GOTO END

:ERROR_LEVEL

echo +------------------------------------------------------------------------------+
echo   A problem occured during generation, check output and DiamantPro Log file!!
echo +------------------------------------------------------------------------------+
pause


:END

:: restore original path.
popd


:: to be able to evaluate ERRORLEVEL on Jenkins 
exit /b %ERRORLEVEL%
