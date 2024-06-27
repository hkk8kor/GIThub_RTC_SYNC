@echo off
pushd %~dp0
echo Starting Variant Generator:
powershell .\VariantGenerator.ps1 -configfile ..\input\RBL_RB_REF_VMPS_Int.xml
pause