# Deviation Record

*If a coding rule is not followed in the source code, this is called a "violation".*
*This violation needs to be documented with this deviation record.*
*After it gets approved, it becomes a deviation.*
*See also "MISRA Compliance:2016" document: https://rb-normen.bosch.com/NormMaster/DirectLink.do?ACTION=VIEW_STANDARD&key=DITR45666236&sprache=EN&FILE=45666236.pdf*


|Topic        |        |
|:---         |  ---:  |
|Project      | MMP2.11                         |
|Deviation ID | MMP2.11-002  |
|Status       | see Alm Story 4091583                               |
|Rule         | MisraC2012-8.3 "Parameter type "uint16" (unsigned short) is not the same as RTE typedefinition based on (unsigned short)"                                |
|Use-Case     | function decleration with basetype instead of redefined type                  |
|Reason       | function decleration can only be done before type is redefined            |
|Scope        | SW components with typedefinitions by RTE  |
|Raised by    | see Alm Story 4091583    |
|Raised Date  | see Alm Story 4091583                                        |

|Approval     |        |
|:---         |  ---:  |
|Approved by  | see Alm Story 4091583                 |  
|Approval Date| see Alm Story 4091583 |


## Summary
Function decleration can not be generated automaticly with RTE generator, but must be declared in RTE context. 
Therefore function gets declared in Rte_UserCfg_Project.h file. The Type definition for the parameters can not be done
before function declearation due to include order of generated header files.

## Justification
Same base datatype (unsigned short) is used for both function decleration and definiton.

## Risk assessment
As same base datatype is used, the compiler will create the same code out of both type.
In case Basetype gets changed on one side, a compiler error for incompatible decleration will be raised.
Therfore no risk. 

