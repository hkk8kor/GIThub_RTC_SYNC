#
# Generated makefile for test "ut_rba_DcmPmaAppl_FillPlantModeResponse"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_rba_DcmPmaAppl_FillPlantModeResponse

#
# Test script file
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_TESTOBJ := ut_rba_DcmPmaAppl_FillPlantModeResponse

#
# Software under test
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_SUTOBJ := rba_DcmPmaAppl_FillPlantModeResponse

#
# Compile and link as 'C' or 'CXX'
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_EXTLIBS := 

#
# Additional object files to link
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_EXTOBJS := 

#
# Additional defines for this test
#
ut_rba_DcmPmaAppl_FillPlantModeResponse_DEFINES := _lint  

#
# Additional includes for this test
#

 ut_rba_DcmPmaAppl_FillPlantModeResponse_INCLUDES := / \
													../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#

ut_rba_DcmPmaAppl_FillPlantModeResponse/rba_DcmPmaAppl_FillPlantModeResponse.o : $(realpath ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/rba_DcmPmaAppl_FillPlantModeResponse.c)
	$(MKDIR_CMD) -p ut_rba_DcmPmaAppl_FillPlantModeResponse
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/rba_DcmPmaAppl_FillPlantModeResponse.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rba_DcmPmaAppl_FillPlantModeResponse_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_rba_DcmPmaAppl_FillPlantModeResponse/ut_rba_DcmPmaAppl_FillPlantModeResponse.o : ut_rba_DcmPmaAppl_FillPlantModeResponse/ut_rba_DcmPmaAppl_FillPlantModeResponse.c
	$(MKDIR_CMD) -p ut_rba_DcmPmaAppl_FillPlantModeResponse
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_rba_DcmPmaAppl_FillPlantModeResponse/ut_rba_DcmPmaAppl_FillPlantModeResponse.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rba_DcmPmaAppl_FillPlantModeResponse_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_TEST_EXE) : \
	$(ut_rba_DcmPmaAppl_FillPlantModeResponse_SUTOBJ_FILENAMES) \
	$(ut_rba_DcmPmaAppl_FillPlantModeResponse_TESTOBJ_FILENAMES) \
	$(ut_rba_DcmPmaAppl_FillPlantModeResponse_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_rba_DcmPmaAppl_FillPlantModeResponse_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_rba_DcmPmaAppl_FillPlantModeResponse,$(subst %EXTOBJS%,$(ut_rba_DcmPmaAppl_FillPlantModeResponse_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_rba_DcmPmaAppl_FillPlantModeResponse successfully

#
# Rule for running the test executable
#
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_CTR_FILE) : $(ut_rba_DcmPmaAppl_FillPlantModeResponse_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_RUN) : $(ut_rba_DcmPmaAppl_FillPlantModeResponse_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rba_DcmPmaAppl_FillPlantModeResponse_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/rba_DcmPmaAppl_FillPlantModeResponse.c,$(DYNAMIC_THIS_TEST)/ut_rba_DcmPmaAppl_FillPlantModeResponse.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rba_DcmPmaAppl_FillPlantModeResponse_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_rba_DcmPmaAppl_FillPlantModeResponse_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_rba_DcmPmaAppl_FillPlantModeResponse_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#
ut_rba_DcmPmaAppl_FillPlantModeResponse/rba_DcmPmaAppl_FillPlantModeResponse.o : ../../ipg.cop
ut_rba_DcmPmaAppl_FillPlantModeResponse/rba_DcmPmaAppl_FillPlantModeResponse.o : ut_rba_DcmPmaAppl_FillPlantModeResponse/ipg.cop
ut_rba_DcmPmaAppl_FillPlantModeResponse/ut_rba_DcmPmaAppl_FillPlantModeResponse.o : ../../ipg.cop
ut_rba_DcmPmaAppl_FillPlantModeResponse/ut_rba_DcmPmaAppl_FillPlantModeResponse.o : ut_rba_DcmPmaAppl_FillPlantModeResponse/ipg.cop
