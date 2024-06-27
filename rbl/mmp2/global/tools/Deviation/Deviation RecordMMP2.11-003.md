# Deviation Record

*If a coding rule is not followed in the source code, this is called a "violation".*
*This violation needs to be documented with this deviation record.*
*After it gets approved, it becomes a deviation.*
*See also "MISRA Compliance:2016" document: https://rb-normen.bosch.com/NormMaster/DirectLink.do?ACTION=VIEW_STANDARD&key=DITR45666236&sprache=EN&FILE=45666236.pdf*


|Topic        |        |
|:---         |  ---:  |
|Project      | MMP2.11                         |
|Deviation ID | MMP2.11-003  |
|Status       | see Alm Story 4451461                               |
|Rule         | MisraC2012-8.13 "Parameter can be declared as pointer/reference to const                               |
|Use-Case     | declaring parameter as const pointer                  |
|Reason       | Cannot change code as they are from CUBAS core component            |
|Scope        | SW components with function argument by DCM module  |
|Raised by    | see Alm Story 4451461    |
|Raised Date  | see Alm Story 4451461                                        |

|Approval     |        |
|:---         |  ---:  |
|Approved by  | see Alm Story 4451461                 |  
|Approval Date| see Alm Story 4451461 |


## Summary
Function argument expects 'const' for pointer

## Justification
The code is taken from cubas core component, therefore we cannot modify below warnings.

## Risk assessment
1. Conversion of a pointer to an const pointer may result in declaration and definition mismatch. Hence project end up with compilation error, which result  stops in project build.
No risk

