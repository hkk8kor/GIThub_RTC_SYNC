

set GHS_LMHOST=rb-lic-ghs2.de.bosch.com
set GHS_LMWHICH=ghs

set OS_TARGET_PORT=rba_OsRH850x2GHS_5_0_6__Os_startOsConfig.bat
set OS_CONFIG=rtaos_ccas_u2c_mcore_sc1.rtaos

call .\..\..\..\..\..\..\..\..\..\..\..\..\rba\CUBAS\EbOs\Os\rba_OsRH850x2GHS\%OS_TARGET_PORT% %OS_CONFIG%

