

set GHS_LMHOST=rb-lic-ghs2.de.bosch.com
set GHS_LMWHICH=ghs

set OS_TARGET_PORT=rba_OsRH850GHS_5_0_32__Os_startOsConfig.bat
set OS_CONFIG=rtaos_ccas_mcore_sc4_vmps.rtaos

call .\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsRH850GHS\%OS_TARGET_PORT% %OS_CONFIG%

