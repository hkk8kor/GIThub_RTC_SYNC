
  echo.
  echo ### RBSYS_PostBuild.mk is executing $(DATE_TIME) ###

#--------------------------------------------------------------------#

  echo Creating WinRTM (RTMO) filter file in out folder ...
  if exist $(RBSYS_PATH)\tools\DynamicDefsParser\dynamic_defs_parser.exe   \
    if exist $(MERGEPROC_PATH)\RBSYS_DYN_MP.c                              \
      $(RBSYS_PATH)\tools\DynamicDefsParser\dynamic_defs_parser.exe $(MERGEPROC_PATH)\RBSYS_DYN_MP.c $(OUT_PATH)\WinRTM_PrcFilterList.rty

  echo Copying WinRTM_PrcFilterList.rty file to build folder ...
  if exist $(OUT_PATH)\WinRTM_PrcFilterList.rty  echo $(OUT_PATH)\WinRTM_PrcFilterList.rty >> $(BUILDXXX_COPY_FILES_LIST)

#--------------------------------------------------------------------#

  echo Copying RBSYS_DYN_MP.c into ApplContainer ...
  if exist $(MERGEPROC_PATH)\RBSYS_DYN_MP.c  echo $(MERGEPROC_PATH)\RBSYS_DYN_MP.c >> $(APPL_CONTAINER_COPY_FILES_LIST)

  echo Copying RBSYS_DYN_MP.c to build folder ...
  if exist $(MERGEPROC_PATH)\RBSYS_DYN_MP.c  echo $(MERGEPROC_PATH)\RBSYS_DYN_MP.c >> $(BUILDXXX_COPY_FILES_LIST)

#--------------------------------------------------------------------#

  echo Copying RTAOS.orti into ApplContainer ...
  if exist $(RBSYS_OS_PATH)\RTAOS.orti  echo $(RBSYS_OS_PATH)\RTAOS.orti >> $(APPL_CONTAINER_COPY_FILES_LIST)

#--------------------------------------------------------------------#
  echo.
  echo ### End of user specific post-build $(DATE_TIME) ###
