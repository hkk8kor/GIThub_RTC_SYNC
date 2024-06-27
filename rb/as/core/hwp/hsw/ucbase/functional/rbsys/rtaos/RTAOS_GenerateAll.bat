pushd %~dp0

set GHS_LMHOST=rb-lic-ghs2.de.bosch.com
set GHS_LMWHICH=ghs

set RTAOS_BUILD_OPTIONS=--debug:compact_source --debug:assembler --debug:source --build:clean --debug:build_info --samples:[Includes]overwrite
set RTAOS_BUILD_OUTPUT_SUBFOLDER=out
set RTAOS_BUILD_OUTPUT_SUBFOLDER_LST=out\lst
set RTAOS_BUILD_REPORTS=--report:"Configuration Summary.txt" --report:"Configuration Summary.html" --report:"Misra Deviations.txt" --report:"Misra Deviations.html"
set RTAOS_BUILD_INCLUDES=.\out\Samples\Includes
set RTAOS_BUILD_COMMON_CONFIG=%~dp0\cfg\EcuC_EcucValues.arxml
REM --output:[*] needed so that rtaos_ccas_mcore_sc1_build_info.bat/log is in out folder, --output: needed so that Samples folder is in out folder
set RTAOS_BUILD_COMMON_OPTIONS=%RTAOS_BUILD_OPTIONS% --output:[*.lst].\%RTAOS_BUILD_OUTPUT_SUBFOLDER_LST% --output:[*].\%RTAOS_BUILD_OUTPUT_SUBFOLDER% --output:.\%RTAOS_BUILD_OUTPUT_SUBFOLDER% %RTAOS_BUILD_REPORTS% --include:%RTAOS_BUILD_INCLUDES%

set RTAOS_P1x_PORT_GEN_PATH=.\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsRH850GHS\rba_OsRH850GHS_5_0_32__Os_gen.bat
set GHS_RH850G3M_201517=C:\MTC10Tools\greenhills_rel\comp_201517_3fp
set GHS_RH850G3M_201815=C:\MTC10Tools\greenhills_rel\comp_201815_3fp_x64
set GHS_RH850G3M_202115=C:\MTC10Tools\greenhills_rel\comp_202115_2fp_x64

set RTAOS_U2A_PORT_GEN_PATH=.\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsRH850x2GHS\rba_OsRH850x2GHS_5_0_6__Os_gen.bat
set GHS_RH850G4M_201815=C:\MTC10Tools\greenhills_rel\comp_201815_1fp_x64
set GHS_RH850G4M_202115=C:\MTC10Tools\greenhills_rel\comp_202115_4fp_x64

set RTAOS_STELLAR_PORT_GEN_PATH=.\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsCentauriR52GHS\rba_OsCentauriR52GHS_5_0_4__Os_gen.bat
set GHS_STELLAR_202114=C:\toolbase\greenhills_arm\comp_202114_1fp_x64

set RTAOS_U2C_PORT_GEN_PATH=.\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsRH850x2GHS\rba_OsRH850x2GHS_5_0_6__Os_gen.bat
set GHS_RH850G4KH_202354=C:\toolbase\greenhills_rel\comp_202354_alpha1fp_x64

goto U2C

REM OS for P1x @ GHS 2015
@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC1 @ GHS 2015.1.7       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC1\201517
pushd RH850G3M\MultiCore_SC1\201517
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Customer compiler option set 1"=true --env:%GHS_RH850G3M_201517%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201517%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC4 @ GHS 2015.1.7       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC4\201517
pushd RH850G3M\MultiCore_SC4\201517
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Customer compiler option set 1"=true --env:%GHS_RH850G3M_201517%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201517%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC1 @ GHS 2015.1.7      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC1\201517
pushd RH850G3M\SingleCore_SC1\201517
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Customer compiler option set 1"=true --env:%GHS_RH850G3M_201517%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201517%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC4 @ GHS 2015.1.7      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC4\201517
pushd RH850G3M\SingleCore_SC4\201517
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Customer compiler option set 1"=true --env:%GHS_RH850G3M_201517%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201517%
popd

REM OS for P1x @ GHS 2018
@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC1 @ GHS 2018.1.5       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC1\201815
pushd RH850G3M\MultiCore_SC1\201815
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201815%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC4 @ GHS 2018.1.5       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC4\201815
pushd RH850G3M\MultiCore_SC4\201815
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201815%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC4 VMPS @ GHS 2018.1.5  -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC4_VMPS\201815
pushd RH850G3M\MultiCore_SC4_VMPS\201815
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc4_vmps.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201815%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC1 @ GHS 2018.1.5      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC1\201815
pushd RH850G3M\SingleCore_SC1\201815
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201815%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC4 @ GHS 2018.1.5      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC4\201815
pushd RH850G3M\SingleCore_SC4\201815
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_201815%
popd

REM OS for P1x @ GHS 2021
@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC1 @ GHS 2021.1.5       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC1\202115
pushd RH850G3M\MultiCore_SC1\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC1 AB15 @ GHS 2021.1.5  -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC1_AB15\202115
pushd RH850G3M\MultiCore_SC1_AB15\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x MultiCore SC4 @ GHS 2021.1.5       -
@echo ------------------------------------------------
@mkdir RH850G3M\MultiCore_SC4\202115
pushd RH850G3M\MultiCore_SC4\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC1 @ GHS 2021.1.5      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC1\202115
pushd RH850G3M\SingleCore_SC1\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC1 AB15 @ GHS 2021.1.5 -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC1_AB15\202115
pushd RH850G3M\SingleCore_SC1_AB15\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS P1x SingleCore SC4 @ GHS 2021.1.5      -
@echo ------------------------------------------------
@mkdir RH850G3M\SingleCore_SC4\202115
pushd RH850G3M\SingleCore_SC4\202115
call %RTAOS_P1x_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_score_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Compiler option set 2"=true --env:%GHS_RH850G3M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G3M_202115%
popd

REM OS for U2A @ GHS 2018
@echo ------------------------------------------------
@echo - RTAOS U2A MultiCore SC1 @ GHS 2018.1.5       -
@echo ------------------------------------------------
@mkdir RH850G4M\MultiCore_SC1\201815
pushd RH850G4M\MultiCore_SC1\201815
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_201815%
popd

@echo ------------------------------------------------
@echo - RTAOS U2A MultiCore SC4 @ GHS 2018.1.5       -
@echo ------------------------------------------------
@mkdir RH850G4M\MultiCore_SC4\201815
pushd RH850G4M\MultiCore_SC4\201815
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_201815%
popd

@echo --------------------------------------------------------------
@echo - RTAOS U2A MultiCore SC4 HostCore0GuestCore1 @ GHS 2018.1.5 -
@echo --------------------------------------------------------------
@mkdir RH850G4M\MultiCore_SC4_HostCore0GuestCore1\201815
pushd RH850G4M\MultiCore_SC4_HostCore0GuestCore1\201815
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_201815%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_201815%
popd

REM OS for U2A @ GHS 2021
@echo ------------------------------------------------
@echo - RTAOS U2A MultiCore SC1 @ GHS 2021.1.5       -
@echo ------------------------------------------------
@mkdir RH850G4M\MultiCore_SC1\202115
pushd RH850G4M\MultiCore_SC1\202115
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_202115%
popd

@echo ------------------------------------------------
@echo - RTAOS U2A MultiCore SC4 @ GHS 2021.1.5       -
@echo ------------------------------------------------
@mkdir RH850G4M\MultiCore_SC4\202115
pushd RH850G4M\MultiCore_SC4\202115
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_202115%
popd

@echo --------------------------------------------------------------
@echo - RTAOS U2A MultiCore SC4 HostCore0GuestCore1 @ GHS 2021.1.5 -
@echo --------------------------------------------------------------
@mkdir RH850G4M\MultiCore_SC4_HostCore0GuestCore1\202115
pushd RH850G4M\MultiCore_SC4_HostCore0GuestCore1\202115
call %RTAOS_U2A_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2a_mcore_sc4.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4M_202115%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4M_202115%
popd

:U2C
REM OS for U2C @ GHS 2023
@echo ------------------------------------------------
@echo - RTAOS U2C MultiCore SC1 @ GHS 2023.5.4       -
@echo ------------------------------------------------
@mkdir RH850G4KH\MultiCore_SC1\202354
pushd RH850G4KH\MultiCore_SC1\202354
call %RTAOS_U2C_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_u2c_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --target_option:"Option set 1"=true --env:%GHS_RH850G4KH_202354%
call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_RH850G4KH_202354%
popd

goto EXIT

REM OS for Stellar @ GHS 2021
@echo ------------------------------------------------
@echo - RTAOS Stellar MultiCore SC1 @ GHS 2021.1.4   -
@echo ------------------------------------------------
@mkdir StellarR52\MultiCore_SC1\202114
pushd StellarR52\MultiCore_SC1\202114
call %RTAOS_STELLAR_PORT_GEN_PATH% %RTAOS_BUILD_COMMON_OPTIONS% .\..\cfg\rtaos_ccas_stellar_mcore_sc1.arxml %RTAOS_BUILD_COMMON_CONFIG% --env:%GHS_STELLAR_202114%

REM Special fix for building Stellar RTAOS
REM patch and run rtaos_ccas_stellar_mcore_sc1_build_info.bat
CALL %~dp0..\..\..\..\tools\python\EnsurePython.cmd

call %python_exe% ./../cfg/patchFile.py %GHS_STELLAR_202114%
cd out
call rtaos_ccas_stellar_mcore_sc1_build_info.bat
cd ..
REM Special fix done

call .\..\..\..\_copy_os.bat
call .\..\..\..\_remove_os_features.bat %GHS_STELLAR_202114%
popd

:EXIT

popd

echo Result Code: %errorlevel%