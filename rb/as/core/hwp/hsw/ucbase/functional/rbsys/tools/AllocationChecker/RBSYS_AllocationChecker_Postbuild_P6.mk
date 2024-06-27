  echo.
  echo ### RBSYS_AllocationChecker_PostBuild.mk is executing $(DATE_TIME) ###

  if exist $(BIN_FILE) \
    if exist $(GHS_PATH) \
      $(RBSYS_PATH)\tools\AllocationChecker\RBSYS_AllocationChecker.bat "$(BIN_FILE)" "$(GHS_PATH)" P6

  echo.
  echo ### End of user specific post-build $(DATE_TIME) ###