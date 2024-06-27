@echo off
pushd %~dp0
echo Starting Variant Generator:
powershell .\VariantGenerator.ps1 -configfile ..\input\RBL_DAI_BR223_VMPS_Plant.xml
pause