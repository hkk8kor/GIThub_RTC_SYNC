#
# Generated makefile for test "ut_DcmAppl_EnableDTCSetting"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_DcmAppl_EnableDTCSetting

#
# Test script file
#
ut_DcmAppl_EnableDTCSetting_TESTOBJ := ut_DcmAppl_EnableDTCSetting

#
# Software under test
#
ut_DcmAppl_EnableDTCSetting_SUTOBJ := rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting

#
# Compile and link as 'C' or 'CXX'
#
ut_DcmAppl_EnableDTCSetting_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_DcmAppl_EnableDTCSetting_EXTLIBS := 

#
# Additional object files to link
#
ut_DcmAppl_EnableDTCSetting_EXTOBJS := 

#
# Additional defines for this test
#
ut_DcmAppl_EnableDTCSetting_DEFINES := _lint 

#
# Additional includes for this test
#
ut_DcmAppl_EnableDTCSetting_INCLUDES := ../../../src_out/rte \
                                        ../../../src_out/ice_gen \
                                        ../../../src_out/cgen \
                                        ../../../src_out/diamantpro/GEN93_gen \
                                        ../../../src_out/diamantpro \
                                        ../../../src_out/bct/_out \
                                        ../../../make/hdr_lnk \
                                        ../../../make \
                                        ../../../../../ \
                                        ../../../../../rb/as/core/app/asw/aswif/api \
                                        ../../../../../rb/as/core/app/dsm/api \
                                        ../../../../../rb/as/core/app/dsm/rbcdb/api \
                                        ../../../../../rb/as/core/app/dsm/rbcdb/src/CM \
                                        ../../../../../rb/as/core/app/dsm/rbcdb/src/DIA_CDB \
                                        ../../../../../rb/as/core/app/dsm/rbdem/api \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/client \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/deb \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/evbuff \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/event \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/main \
                                        ../../../../../rb/as/core/app/dsm/rbdem/src/nvm \
                                        ../../../../../rb/as/core/app/dsm/rbdembfm/api \
                                        ../../../../../rb/as/core/app/dsm/rbdet/api \
                                        ../../../../../rb/as/core/app/dsm/rbemm/RBEMM/api \
                                        ../../../../../rb/as/core/app/dsm/rbenv/api \
                                        ../../../../../rb/as/core/app/dsm/rbmsi/api \
                                        ../../../../../rb/as/core/app/dsm/rbsmm/api \
                                        ../../../../../rb/as/core/app/dsm/RBSMM_ProductLine/api \
                                        ../../../../../rb/as/core/app/dsm/rbstm/api \
                                        ../../../../../rb/as/core/app/dsm/rbstm/src \
                                        ../../../../../rb/as/core/app/dsm/rbwrapper/api \
                                        ../../../../../rb/as/core/app/dsm/rbwrapper/src \
                                        ../../../../../rb/as/core/app/dsm/rbwrapper/src/iumpr \
                                        ../../../../../rb/as/core/app/epsw/api \
                                        ../../../../../rb/as/core/app/epsw/cfg \
                                        ../../../../../rb/as/core/app/net/api \
                                        ../../../../../rb/as/core/app/net/RBCAN/api \
                                        ../../../../../rb/as/core/app/net/RBDebugTxInterface/api \
                                        ../../../../../rb/as/core/app/net/RBMON/api \
                                        ../../../../../rb/as/core/app/net/RBPduHandler/api \
                                        ../../../../../rb/as/core/app/net/RBXCP/api \
                                        ../../../../../rb/as/core/app/sec/security/api \
                                        ../../../../../rb/as/core/arch/api \
                                        ../../../../../rb/as/core/global/rbpdmdb \
                                        ../../../../../rb/as/core/hwp/cubas/BSMM/Cubas_Stubs \
                                        ../../../../../rb/as/core/hwp/cubas/BswLib \
                                        ../../../../../rb/as/core/hwp/cubas/BswLib/rba_BswSrv \
                                        ../../../../../rb/as/core/hwp/cubas/BswLib/rba_BswSrv/api \
                                        ../../../../../rb/as/core/hwp/cubas/CanStack \
                                        ../../../../../rb/as/core/hwp/cubas/CanStack/api \
                                        ../../../../../rb/as/core/hwp/cubas/CanStack/Modules \
                                        ../../../../../rb/as/core/hwp/cubas/CanStack/Modules/Can \
                                        ../../../../../rb/as/core/hwp/cubas/cfg/EbOs/SchM/api \
                                        ../../../../../rb/as/core/hwp/cubas/cfg/Mcu/api \
                                        ../../../../../rb/as/core/hwp/cubas/cfg/MemMap/api \
                                        ../../../../../rb/as/core/hwp/cubas/ComServices \
                                        ../../../../../rb/as/core/hwp/cubas/ComServices/Xcp \
                                        ../../../../../rb/as/core/hwp/cubas/CUCEL/api \
                                        ../../../../../rb/as/core/hwp/cubas/CUCEL/cfg/Compiler \
                                        ../../../../../rb/as/core/hwp/cubas/Diagnosis/api \
                                        ../../../../../rb/as/core/hwp/cubas/Diagnosis/src \
                                        ../../../../../rb/as/core/hwp/cubas/Diagnosis/src/rbaObdExtended \
                                        ../../../../../rb/as/core/hwp/cubas/E2EServices/Crc \
                                        ../../../../../rb/as/core/hwp/cubas/E2EServices/E2E \
                                        ../../../../../rb/as/core/hwp/cubas/EbOs/cfg/rba_MultiStackTrace/api \
                                        ../../../../../rb/as/core/hwp/cubas/EbOs/cfg/rba_Runtime/api \
                                        ../../../../../rb/as/core/hwp/cubas/ESM/Cubas_Stubs \
                                        ../../../../../rb/as/core/hwp/cubas/Mcal_RH850/api \
                                        ../../../../../rb/as/core/hwp/cubas/Mcal_RH850/cfg \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/api \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/api/Ea \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/api/Eep \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/api/Fls/Common \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/cfg \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/cfg/Fee \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/cfg/Fls \
                                        ../../../../../rb/as/core/hwp/cubas/MemStack/cfg/rba_MemLib \
                                        ../../../../../rb/as/core/hwp/cubas/Rte/api \
                                        ../../../../../rb/as/core/hwp/cubas/SrvLibs \
                                        ../../../../../rb/as/core/hwp/hsw/base/api \
                                        ../../../../../rb/as/core/hwp/hsw/base/api/arch \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Global/api \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Global/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveld/api \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveld/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/api \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/api/legacy \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbbandgap/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbecusupply/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbecusupply/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbecusupply/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbmicbase/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbmicsys/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbmicsys/api/BLDR \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbmicsys/api/RBMICSYS \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbwau/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbfsl/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbfsl/api/BSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbfsl/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbfsl/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbfsl/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbgld/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbgld/api/ASW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbgld/api/DAT \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbgld/api/Support \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbsupplybase/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbsupplybase/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbsupplybase/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbsupplybase/api/SUPPLY \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbwdh/api \
                                        ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbwdh/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYESP/api \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYESP/api/BSW \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYVLV/api \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYVLV/api/BSW \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYVLV/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYVLV/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/library/rbcbaselib/api \
                                        ../../../../../rb/as/core/hwp/hsw/library/rbmesg/api \
                                        ../../../../../rb/as/core/hwp/hsw/library/rbrcfg/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/api/AlternativeFunctionality \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/api/ExternalServices \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/api/ISW \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/HUPLANT/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/TestComplete/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/TSI/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/TSI/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/rbbootblockhsw/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbdeco/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbhswtests/HSWFT/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbpdm/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbpdm/api/ASW \
                                        ../../../../../rb/as/core/hwp/hsw/rbpdm/api/mon \
                                        ../../../../../rb/as/core/hwp/hsw/rbpdm/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/rbtex/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbtex/Extensions/0C_ePSWFinalization/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbtex/Extensions/api \
                                        ../../../../../rb/as/core/hwp/hsw/rbtex/Scheduler/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbadc/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbadc/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbapplif/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbcrc/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdio/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdio/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdma/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdma/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdma/api/deprecated \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbgtm/api/config \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rblcf/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rblcf/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rblcf/api/csw \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbport/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbport/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsent/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsent/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsent/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbspi/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbspi/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbspi/api/HWP \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api/csw \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api/hsw \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api/hwp \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/api/legacy \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/lib_ghs/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/lib_renesas/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/rtaos/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/rtaos/RTAOS_RH850G3M_201815/Renesas_P1x_SingleCore_SC1/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/src \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbclma/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbclma/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbclma/api/hsw \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbcvm/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbcvm/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbecm/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbecm/api/config \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbecm/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbhwbist/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbhwbist/api/config \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbramsafety/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbramsafety/api/cfg \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbromsafety/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbromsafety/api/config \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbromsafety/api/CSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbromsafety/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbswbist/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbswbist/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbtaskmon/api \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbtaskmon/api/config \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbtaskmon/api/HSW \
                                        ../../../../../rb/as/core/hwp/hsw/ucbase/safety/rbuctemp/api \
                                        ../../../../../rbl/mmp2/app/rbl_ImuGenFunc/api \
                                        ../../../../../rbl/mmp2/app/rbl_ImuPlaData/api \
                                        ../../../../../rbl/mmp2/app/rbl_ImuPlaSrv/api \
                                        ../../../../../rbl/mmp2/app/rbl_ImuStdTypes/api \
                                        ../../../../../rbl/mmp2/app/rbl_SignalChain/api \
                                        ../../../../../rbl/mmp2/app/rbl_SignalChain/cfg \
                                        ../../../../../rbl/mmp2/cdd/rbl_ImuCddImu/api \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_CustIf/api \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_CustIf/cfg \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/TimeSync \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_dcom/api \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_dcom/cfg \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/rba_pma \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_net/api \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_net/cfg \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_net/ComScl_Appl/PostProcessing \
                                        ../../../../../rbl/mmp2/cust/mb/rbl_net/ComScl_Appl/Project \
                                        ../../../../../rbl/mmp2/global/rbpdmdb \
                                        ../../../../../rbl/mmp2/ms/app/asw/aswif/api \
                                        ../../../../../rbl/mmp2/ms/app/asw/aswif/Src_gen \
                                        ../../../../../rbl/mmp2/ms/app/dsm/DemVar/api \
                                        ../../../../../rbl/mmp2/ms/app/dsm/RBEnv/api \
                                        ../../../../../rbl/mmp2/ms/cswpr/cfg \
                                        ../../../../../rbl/mmp2/ms/dcompr/cfg \
                                        ../../../../../rbl/mmp2/ms/dsmpr/cfg/Cubas \
                                        ../../../../../rbl/mmp2/ms/dsmpr/cfg/RBSMM \
                                        ../../../../../rbl/mmp2/ms/dsmpr/cfg/RBVoltageHandler \
                                        ../../../../../rbl/mmp2/ms/dsmpr/cfg/STM \
                                        ../../../../../rbl/mmp2/ms/dsmpr/RBEMM/api \
                                        ../../../../../rbl/mmp2/ms/dsmpr/RBEMM/src \
                                        ../../../../../rbl/mmp2/ms/dsmpr/tst/ct/api \
                                        ../../../../../rbl/mmp2/ms/dsmpr/tst/Sim/FeatureTest/Hdr \
                                        ../../../../../rbl/mmp2/ms/hswpr/src/RBDiagVariance/api \
                                        ../../../../../rbl/mmp2/ms/netpr/api \
                                        ../../../../../rbl/mmp2/ms/secpr/cfg/EcuCybSec/ecy_hsm_DAx4xABS20/ecy_hsm \
                                        ../../../../../rbl/mmp2/ms/secpr/cfg/EcuCybSec/ecy_hsm_DAx4xABS20/ecy_hsm/FeatureCfg_01 \
                                        ../../../../../rbl/mmp2/ms/secpr/cfg/EcuCybSec/ecy_hsm_DAx4xABS20/ecy_hsm_RH850_D3 \
                                        ../../../../../rbl/mmp2/ms/secpr/cfg/SecServices \
                                        ../../../../../rbl/mmp2/ms/secpr/cfg/security

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.o : ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.c
	$(MKDIR_CMD) -p ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src/cubas
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_DcmAppl_EnableDTCSetting_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_DcmAppl_EnableDTCSetting_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_DcmAppl_EnableDTCSetting_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_DcmAppl_EnableDTCSetting/ut_DcmAppl_EnableDTCSetting.o : ut_DcmAppl_EnableDTCSetting/ut_DcmAppl_EnableDTCSetting.c
	$(MKDIR_CMD) -p ut_DcmAppl_EnableDTCSetting
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_DcmAppl_EnableDTCSetting/ut_DcmAppl_EnableDTCSetting.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_DcmAppl_EnableDTCSetting_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_DcmAppl_EnableDTCSetting_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_DcmAppl_EnableDTCSetting_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_DcmAppl_EnableDTCSetting_TEST_EXE) : \
	$(ut_DcmAppl_EnableDTCSetting_SUTOBJ_FILENAMES) \
	$(ut_DcmAppl_EnableDTCSetting_TESTOBJ_FILENAMES) \
	$(ut_DcmAppl_EnableDTCSetting_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_DcmAppl_EnableDTCSetting_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_DcmAppl_EnableDTCSetting_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_DcmAppl_EnableDTCSetting,$(subst %EXTOBJS%,$(ut_DcmAppl_EnableDTCSetting_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_DcmAppl_EnableDTCSetting successfully

#
# Rule for running the test executable
#
$(ut_DcmAppl_EnableDTCSetting_CTR_FILE) : $(ut_DcmAppl_EnableDTCSetting_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_DcmAppl_EnableDTCSetting_RUN) : $(ut_DcmAppl_EnableDTCSetting_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_DcmAppl_EnableDTCSetting_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_DcmAppl_EnableDTCSetting_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.c,$(DYNAMIC_THIS_TEST)/ut_DcmAppl_EnableDTCSetting.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_DcmAppl_EnableDTCSetting_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_DcmAppl_EnableDTCSetting_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_DcmAppl_EnableDTCSetting_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_DcmAppl_EnableDTCSetting_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src/cubas : ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src : ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom : ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb : ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust : ut_DcmAppl_EnableDTCSetting/rbl/mmp2
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl/mmp2 : ut_DcmAppl_EnableDTCSetting/rbl
	-@$(MKDIR_CMD) $@
ut_DcmAppl_EnableDTCSetting/rbl : 
	-@$(MKDIR_CMD) $@

#
# Additional dependencies
#
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.o : ../../ipg.cop
ut_DcmAppl_EnableDTCSetting/rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_EnableDTCSetting.o : ut_DcmAppl_EnableDTCSetting/ipg.cop
ut_DcmAppl_EnableDTCSetting/ut_DcmAppl_EnableDTCSetting.o : ../../ipg.cop
ut_DcmAppl_EnableDTCSetting/ut_DcmAppl_EnableDTCSetting.o : ut_DcmAppl_EnableDTCSetting/ipg.cop
