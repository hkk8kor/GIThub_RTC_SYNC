#
# Generated makefile for test "ut_rbl_SigChain_Invalidate"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_rbl_SigChain_Invalidate

#
# Test script file
#
ut_rbl_SigChain_Invalidate_TESTOBJ := ut_rbl_SigChain_Invalidate

#
# Software under test
#
ut_rbl_SigChain_Invalidate_SUTOBJ := rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate

#
# Compile and link as 'C' or 'CXX'
#
ut_rbl_SigChain_Invalidate_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_rbl_SigChain_Invalidate_EXTLIBS := 

#
# Additional object files to link
#
ut_rbl_SigChain_Invalidate_EXTOBJS := 

#
# Additional defines for this test
#
ut_rbl_SigChain_Invalidate_DEFINES := _lint 

#
# Additional includes for this test
#
ut_rbl_SigChain_Invalidate_INCLUDES := 

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#
ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.o : ../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.c
	$(MKDIR_CMD) -p ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain/src
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_rbl_SigChain_Invalidate_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rbl_SigChain_Invalidate_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rbl_SigChain_Invalidate_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_rbl_SigChain_Invalidate/ut_rbl_SigChain_Invalidate.o : ut_rbl_SigChain_Invalidate/ut_rbl_SigChain_Invalidate.c
	$(MKDIR_CMD) -p ut_rbl_SigChain_Invalidate
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_rbl_SigChain_Invalidate/ut_rbl_SigChain_Invalidate.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_rbl_SigChain_Invalidate_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_rbl_SigChain_Invalidate_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_rbl_SigChain_Invalidate_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_rbl_SigChain_Invalidate_TEST_EXE) : \
	$(ut_rbl_SigChain_Invalidate_SUTOBJ_FILENAMES) \
	$(ut_rbl_SigChain_Invalidate_TESTOBJ_FILENAMES) \
	$(ut_rbl_SigChain_Invalidate_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_rbl_SigChain_Invalidate_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_rbl_SigChain_Invalidate_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_rbl_SigChain_Invalidate,$(subst %EXTOBJS%,$(ut_rbl_SigChain_Invalidate_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_rbl_SigChain_Invalidate successfully

#
# Rule for running the test executable
#
$(ut_rbl_SigChain_Invalidate_CTR_FILE) : $(ut_rbl_SigChain_Invalidate_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_rbl_SigChain_Invalidate_RUN) : $(ut_rbl_SigChain_Invalidate_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_rbl_SigChain_Invalidate_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rbl_SigChain_Invalidate_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.c,$(DYNAMIC_THIS_TEST)/ut_rbl_SigChain_Invalidate.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_rbl_SigChain_Invalidate_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_rbl_SigChain_Invalidate_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_rbl_SigChain_Invalidate_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_rbl_SigChain_Invalidate_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#
ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain/src : ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain
	-@$(MKDIR_CMD) $@
ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain : ut_rbl_SigChain_Invalidate/rbl/mmp2/app
	-@$(MKDIR_CMD) $@
ut_rbl_SigChain_Invalidate/rbl/mmp2/app : ut_rbl_SigChain_Invalidate/rbl/mmp2
	-@$(MKDIR_CMD) $@
ut_rbl_SigChain_Invalidate/rbl/mmp2 : ut_rbl_SigChain_Invalidate/rbl
	-@$(MKDIR_CMD) $@
ut_rbl_SigChain_Invalidate/rbl : 
	-@$(MKDIR_CMD) $@

#
# Additional dependencies
#
ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.o : ../../ipg.cop
ut_rbl_SigChain_Invalidate/rbl/mmp2/app/rbl_SignalChain/src/rbl_SigChain_Invalidate.o : ut_rbl_SigChain_Invalidate/ipg.cop
ut_rbl_SigChain_Invalidate/ut_rbl_SigChain_Invalidate.o : ../../ipg.cop
ut_rbl_SigChain_Invalidate/ut_rbl_SigChain_Invalidate.o : ut_rbl_SigChain_Invalidate/ipg.cop
