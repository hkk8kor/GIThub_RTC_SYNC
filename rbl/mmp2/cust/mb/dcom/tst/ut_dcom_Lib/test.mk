#
# Generated makefile for test "ut_dcom_Lib"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_dcom_Lib

#
# Test script file
#
ut_dcom_Lib_TESTOBJ := ut_dcom_Lib

#
# Software under test
#
ut_dcom_Lib_SUTOBJ := dcom_Lib

#
# Compile and link as 'C' or 'CXX'
#
ut_dcom_Lib_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_dcom_Lib_EXTLIBS := 

#
# Additional object files to link
#
ut_dcom_Lib_EXTOBJS := 

#
# Additional defines for this test
#
ut_dcom_Lib_DEFINES := _lint  

#
# Additional includes for this test
#

 ut_dcom_Lib_INCLUDES := / \
													../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#

ut_dcom_Lib/dcom_Lib.o : $(realpath ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/dcom_Lib.c)
	$(MKDIR_CMD) -p ut_dcom_Lib
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/dcom_Lib.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_dcom_Lib_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_dcom_Lib_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_dcom_Lib_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_dcom_Lib/ut_dcom_Lib.o : ut_dcom_Lib/ut_dcom_Lib.c
	$(MKDIR_CMD) -p ut_dcom_Lib
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_dcom_Lib/ut_dcom_Lib.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_dcom_Lib_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_dcom_Lib_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_dcom_Lib_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_dcom_Lib_TEST_EXE) : \
	$(ut_dcom_Lib_SUTOBJ_FILENAMES) \
	$(ut_dcom_Lib_TESTOBJ_FILENAMES) \
	$(ut_dcom_Lib_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_dcom_Lib_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_dcom_Lib_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_dcom_Lib,$(subst %EXTOBJS%,$(ut_dcom_Lib_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_dcom_Lib successfully

#
# Rule for running the test executable
#
$(ut_dcom_Lib_CTR_FILE) : $(ut_dcom_Lib_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_dcom_Lib_RUN) : $(ut_dcom_Lib_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_dcom_Lib_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_dcom_Lib_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/common/dcom_Lib.c,$(DYNAMIC_THIS_TEST)/ut_dcom_Lib.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_dcom_Lib_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_dcom_Lib_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_dcom_Lib_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_dcom_Lib_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#
ut_dcom_Lib/dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ../../ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ut_dcom_Lib/ipg.cop
ut_dcom_Lib/ut_dcom_Lib.o : ut_dcom_Lib/ipg.cop
