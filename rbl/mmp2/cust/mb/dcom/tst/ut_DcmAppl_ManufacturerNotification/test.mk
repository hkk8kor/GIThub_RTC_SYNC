#
# Generated makefile for test "ut_DcmAppl_ManufacturerNotification"
#

#
# Stop the MAKEFLAGS variable being exported.
# This is needed for sub-make processes to use different options.
#
unexport MAKEFLAGS

#
# The name of the test
#
THIS_TEST := ut_DcmAppl_ManufacturerNotification

#
# Test script file
#
ut_DcmAppl_ManufacturerNotification_TESTOBJ := ut_DcmAppl_ManufacturerNotification

#
# Software under test
#
ut_DcmAppl_ManufacturerNotification_SUTOBJ := DcmAppl_ManufacturerNotification

#
# Compile and link as 'C' or 'CXX'
#
ut_DcmAppl_ManufacturerNotification_C_OR_CPP_MODE := C

#
# Additional libraries to link
#
ut_DcmAppl_ManufacturerNotification_EXTLIBS := 

#
# Additional object files to link
#
ut_DcmAppl_ManufacturerNotification_EXTOBJS := 

#
# Additional defines for this test
#
ut_DcmAppl_ManufacturerNotification_DEFINES := _lint 

#
# Additional includes for this test
#
ut_DcmAppl_ManufacturerNotification_INCLUDES := 

#
# Include the test definitions makefile
#
include ../configuration/test_defs.mk

#
# Rules for compiling the software under test
#
ut_DcmAppl_ManufacturerNotification/DcmAppl_ManufacturerNotification.o : $(realpath ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_ManufacturerNotification.c)
	$(MKDIR_CMD) -p ut_DcmAppl_ManufacturerNotification
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_ManufacturerNotification.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	-@$(QAC_CMD)
	$(subst %DEFINES%, $(foreach define,$(ut_DcmAppl_ManufacturerNotification_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_DcmAppl_ManufacturerNotification_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_DcmAppl_ManufacturerNotification_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for compiling the test script
#
ut_DcmAppl_ManufacturerNotification/ut_DcmAppl_ManufacturerNotification.o : ut_DcmAppl_ManufacturerNotification/ut_DcmAppl_ManufacturerNotification.c
	$(MKDIR_CMD) -p ut_DcmAppl_ManufacturerNotification
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,0,0 >> $(CANTPP_TOP_LEVEL_LOG)
	-@$(ECHO_CMD_MED) ut_DcmAppl_ManufacturerNotification/ut_DcmAppl_ManufacturerNotification.c > $(DYNAMIC_THIS_TEST)/filelist.lst
	$(subst %DEFINES%, $(foreach define,$(ut_DcmAppl_ManufacturerNotification_ALL_DEFINES),$(DEFINE_OPT)$(define)), $(subst %INCLUDES%, $(foreach include,$(ut_DcmAppl_ManufacturerNotification_ALL_INCLUDES),$(subst %s,$(include),$(INCLUDE_PATH_OPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/$(ut_DcmAppl_ManufacturerNotification_SUTOBJ),$(COMPILE_CC_CMD))))

#
# Rule for linking the test executable
#
$(ut_DcmAppl_ManufacturerNotification_TEST_EXE) : \
	$(ut_DcmAppl_ManufacturerNotification_SUTOBJ_FILENAMES) \
	$(ut_DcmAppl_ManufacturerNotification_TESTOBJ_FILENAMES) \
	$(ut_DcmAppl_ManufacturerNotification_EXTRA_DEPENDS)
	@$(RM_CMD) $(DYNAMIC_THIS_TEST)/*.cov $(DYNAMIC_THIS_TEST)/*.ctr $(DYNAMIC_THIS_TEST)/*.ctg
	@$(ECHO_CMD_MED) ",,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),1,0,0,1,0" >> $(CANTPP_TOP_LEVEL_LOG)
	$(subst %EXTLIBS%, $(foreach extlib,$(ut_DcmAppl_ManufacturerNotification_ALL_EXTLIBS),$(subst %s,$(extlib),$(ut_DcmAppl_ManufacturerNotification_LINK_EXTLIBOPT))), $(subst %n,$(DYNAMIC_THIS_TEST)/ut_DcmAppl_ManufacturerNotification,$(subst %EXTOBJS%,$(ut_DcmAppl_ManufacturerNotification_EXTOBJS),$(CC_LINK_CMD))))
	@$(ECHO_CMD_MED) Built ut_DcmAppl_ManufacturerNotification successfully

#
# Rule for running the test executable
#
$(ut_DcmAppl_ManufacturerNotification_CTR_FILE) : $(ut_DcmAppl_ManufacturerNotification_TEST_EXE)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,1,0,1,0 >> $(CANTPP_TOP_LEVEL_LOG)
	@$(RUN_CMD)
	@$(ECHO_CMD_MED) ,,$(NUMBER_OF_TESTS),$(firstword $(subst /, ,$(dir $@))),0,0,1,0,0 >> $(CANTPP_TOP_LEVEL_LOG)

#
# Rule for ensuring nothing is built/run unless the ctr file is out of date
#
$(ut_DcmAppl_ManufacturerNotification_RUN) : $(ut_DcmAppl_ManufacturerNotification_CTR_FILE)

#
# Rule for controlling the building and running of the test executable
#
ifeq ($(EXECUTE),1)
ifeq ($(PUSH_TO_SERVER),1)
$(ut_DcmAppl_ManufacturerNotification_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_DcmAppl_ManufacturerNotification_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Uploading test results to Cantata Server...
	@$(JAVA_CMD) -cp "$(CANTATA_INSTALL_DIR)/bin/client.jar" com.qas.cantata.client.control.CCLC filesToLoad=$(DYNAMIC_THIS_TEST)/.*.ctr,$(DYNAMIC_THIS_TEST)/.*.ctg,$(DYNAMIC_THIS_TEST)/.*.cov,../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_ManufacturerNotification.c,$(DYNAMIC_THIS_TEST)/ut_DcmAppl_ManufacturerNotification.c optionsFiles=../../ipg.cop,$(DYNAMIC_THIS_TEST)/ipg.cop 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
else
$(ut_DcmAppl_ManufacturerNotification_BUILD_AND_RUN) : 
	-@$(MAKE) $(ut_DcmAppl_ManufacturerNotification_RUN) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(CTR_STATE_CMD)
endif
else
$(ut_DcmAppl_ManufacturerNotification_BUILD_AND_RUN) : 
	@$(MAKE) $(ut_DcmAppl_ManufacturerNotification_TEST_EXE) --warn-undefined-variables -s -f $(DYNAMIC_THIS_TEST)/test.mk 2>&1 | tee -a $(DYNAMIC_THIS_TEST)/$($(DYNAMIC_THIS_TEST)_LOG)
	@$(ECHO_CMD_MED) Finished $(DYNAMIC_THIS_TEST)
endif

#
# Rules for generating the required folder structure
#
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/cust/mb/rbl_dcom/src/cubas : ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom/Cubas42/src
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom/Cubas42/src : ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom/Cubas42
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom/Cubas42 : ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms/dcom : ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/ms : ut_DcmAppl_ManufacturerNotification/rbl/mmp2
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl/mmp2 : ut_DcmAppl_ManufacturerNotification/rbl
	-@$(MKDIR_CMD) $@
ut_DcmAppl_ManufacturerNotification/rbl : 
	-@$(MKDIR_CMD) $@

#
# Additional dependencies
#
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_ManufacturerNotification.o : ../../ipg.cop
ut_DcmAppl_ManufacturerNotification/rbl/mmp2/cust/mb/rbl_dcom/src/cubas/DcmAppl_ManufacturerNotification.o : ut_DcmAppl_ManufacturerNotification/ipg.cop
ut_DcmAppl_ManufacturerNotification/ut_DcmAppl_ManufacturerNotification.o : ../../ipg.cop
ut_DcmAppl_ManufacturerNotification/ut_DcmAppl_ManufacturerNotification.o : ut_DcmAppl_ManufacturerNotification/ipg.cop
