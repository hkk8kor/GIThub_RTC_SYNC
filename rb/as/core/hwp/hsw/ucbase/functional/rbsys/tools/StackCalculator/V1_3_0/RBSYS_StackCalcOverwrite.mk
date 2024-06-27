#####################################################
# -- overwrite only if StackCalculator is enabled --#
#####################################################
!IF "$(CALL_STACK_CALCULATOR)"=="Y"

  echo.
  echo ### RBSYS_StackCalcOverwrite.mk is executing $(DATE_TIME) ###

  echo ### Update MTC 10.1 StackCalculator.jar from V1.2.0 to V1.3.0...

  if exist $(RBSYS_PATH)\tools\StackCalculator\V1_3_0\StackCalculator.jar         \
    if exist $(STACK_CALCULATOR_PATH)                                             \
      copy /Y $(RBSYS_PATH)\tools\StackCalculator\V1_3_0\StackCalculator.jar $(STACK_CALCULATOR_PATH)

  echo.
  echo ### End of user specific post-build $(DATE_TIME) ###

!ENDIF