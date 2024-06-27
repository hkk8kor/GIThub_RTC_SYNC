@echo off
pushd %~dp0
echo Starting Variant Generator:
powershell ..\..\MPSP_FeatureModel\scripts\VariantGenerator.ps1 -configfile ..\..\FeatureExamples\input\Example.xml
pause