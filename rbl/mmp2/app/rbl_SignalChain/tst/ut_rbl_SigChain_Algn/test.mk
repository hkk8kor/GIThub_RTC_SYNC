#
# Generated makefile for test "ut_rbl_SigChain_Algn"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_rbl_SigChain_Algn

#
# Test script file
#
ut_rbl_SigChain_Algn_TESTOBJ := ut_rbl_SigChain_Algn

#
# Software under test
#
ut_rbl_SigChain_Algn_SUTOBJ := rbl_SigChain_Algn

#
# Compile and link as 'C' or 'CXX'
#
ut_rbl_SigChain_Algn_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_rbl_SigChain_Algn_EXTLIBS := 

#
# Additional object files to link
#
ut_rbl_SigChain_Algn_EXTOBJS := 

#
# Additional defines for this test
#
ut_rbl_SigChain_Algn_DEFINES := _lint 

#
# Additional includes for this test
#
ut_rbl_SigChain_Algn_INCLUDES := ../../../src_out/cgen \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack \
                                         ../../../../../ \
                                         ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Level0/api/HSW \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack/NvM \
                                         ../../../make \
                                         ../../../../../rb/as/core/hwp/hsw/esp/src/RBSUPPLYVLV/cfg \
                                         ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/cfg/Devices \
                                         ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/HUPLANT/cfg \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack/Fls/D3 \
                                         ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/TSI/cfg \
                                         ../../../src_out/rte \
                                         ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbecusupply/cfg \
                                         ../../../../../rb/as/core/app/dsm/rbenvMMP2/api \
                                         ../../../../../rb/as/core/hwp/hsw/rbaplplant/src/ePSW/cfg \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack/RBNVM/api \
                                         ../../../src_out/diamantpro/GEN93_gen \
                                         ../../../src_out/diamantpro \
                                         ../../../make/hdr_lnk \
                                         ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/cfg \
                                         ../../../../../rb/as/core/hwp/hsw/ecubase/functional/rbbandgap/cfg \
                                         ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Level0/api \
                                         ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbdma/api/HwAccess \
                                         ../../../../../rb/as/core/hwp/hsw/rbaplplant/cfg \
                                         ../../../../../rb/as/core/hwp/hsw/ucbase/functional/rbsys/rtaos/Renesas_P1x_SingleCore_SC1/api \
                                         ../../../src_out/bct/_out \
                                         ../../../../../rb/as/core/hwp/hsw/base/src/RBCMHSW/Leveln/cfg/scripts \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack/Eep \
                                         ../../../src_out/ice_gen \
                                         ../../../../../rb/as/core/hwp/hsw/ecubase/safety/rbgld/cfg \
                                         ../../../../../rb/as/core/hwp/cubas/MemStack/cfg/Ea \
                                         ../../../../../rbl/mmp2/ms/hswpr/src/RBProjectRuntimeConfig/api

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#
ut_rbl_SigChain_Algn/rbl_SigChain_Algn.o : $(realpath ../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Algn.c)
	$(MKDIR_CMD) -p ut_rbl_SigChain_Algn
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Algn.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_rbl_SigChain_Algn_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rbl_SigChain_Algn_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rbl_SigChain_Algn_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_rbl_SigChain_Algn/ut_rbl_SigChain_Algn.o : ut_rbl_SigChain_Algn/ut_rbl_SigChain_Algn.c
	$(MKDIR_CMD) -p ut_rbl_SigChain_Algn
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_rbl_SigChain_Algn/ut_rbl_SigChain_Algn.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_rbl_SigChain_Algn_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rbl_SigChain_Algn_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rbl_SigChain_Algn_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_rbl_SigChain_Algn_TEST_EXE) : \
	$(ut_rbl_SigChain_Algn_SUTOBJ_FILENAMES) \
	$(ut_rbl_SigChain_Algn_TESTOBJ_FILENAMES) \
	$(ut_rbl_SigChain_Algn_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_rbl_SigChain_Algn_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_rbl_SigChain_Algn_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_rbl_SigChain_Algn,$(subst %EXTOBJS%,$(ut_rbl_SigChain_Algn_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_rbl_SigChain_Algn successfully

#
# Rule for running the test executable
#
$(ut_rbl_SigChain_Algn_CTR_FILE) : $(ut_rbl_SigChain_Algn_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_rbl_SigChain_Algn_RUN) : $(ut_rbl_SigChain_Algn_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_rbl_SigChain_Algn_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rbl_SigChain_Algn_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Algn.c,$(DYNAMIC_THIS_TEST)/ut_rbl_SigChain_Algn.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_rbl_SigChain_Algn_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rbl_SigChain_Algn_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_rbl_SigChain_Algn_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_rbl_SigChain_Algn_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#


#
# Additional dependencies
#
ut_rbl_SigChain_Algn/rbl_SigChain_Algn.o : ../../ipg.cop
ut_rbl_SigChain_Algn/rbl_SigChain_Algn.o : ut_rbl_SigChain_Algn/ipg.cop
ut_rbl_SigChain_Algn/ut_rbl_SigChain_Algn.o : ../../ipg.cop
ut_rbl_SigChain_Algn/ut_rbl_SigChain_Algn.o : ut_rbl_SigChain_Algn/ipg.cop
