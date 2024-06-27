The files which are under rbl\mmp2\cust\mb\rbl_dcom\src\cubas -> DcmAppl_*

This folder contains hook functions, that are derived 1:1 from templates in the folder “rba\CUBAS\Diagnosis\Dcm\template”
Those files are needed for compilation only, they have no functional impact.
If you need to adapt any of this functions, the file has to be removed from this folder and renamed according to the namespace.
------------------------------------------------------------------------------------------------------------------------
rba_DcmPmaAppl.h

This file contains hook functions, that are derived 1:1 from templates in the folder “rba\CUBAS\Diagnosis\rba_DcmPma\template” to
"rbl\mmp2\cust\mb\rbl_dcom\src\cubas\rba_pma". This file is needed for compilation only, and have no functional impact.
------------------------------------------------------------------------------------------------------------------------
DcmAppl.h

This file contains hook functions, that are derived 1:1 from templates in the folder “rba\CUBAS\Diagnosis\Dcm\template” to
"rbl\mmp2\cust\mb\rbl_dcom\api". This file is needed for compilation only, and have no functional impact.
Namespace of DcmAppl.h has been retained as header file would have been included in many c files.
According to namespace architecture, DcmAppl.h file has been renamed to rbl_dcom_DcmAppl.h
------------------------------------------------------------------------------------------------------------------------
According to namespace architecture, DcmAppl_DcmConfirmation.c file has been renamed to rbl_dcom_DcmConfirmation.c

This file contain hook function, that is modified according to diagnostic response and moved to
"rbl\mmp2\cust\mb\rbl_dcom\src\common". This file is needed for compilation and has functional impact on diagnostic responses.
------------------------------------------------------------------------------------------------------------------------
According to namespace architecture, DcmAppl_DcmModifyResponse.c file has been renamed to rbl_dcom_DcmModifyResponse.c

This file contain hook function, that is modified according to diagnostic response and moved to
"rbl\mmp2\cust\mb\rbl_dcom\src\common". This file is needed for compilation and has functional impact on diagnostic responses.