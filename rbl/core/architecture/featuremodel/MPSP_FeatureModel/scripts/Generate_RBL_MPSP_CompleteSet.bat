@echo off
pushd %~dp0
echo Starting Variant Generator:
powershell .\VariantGenerator.ps1 -configfile ..\input\RBL_MPSP_CompleteSet.xml
pause