# Deviation Record

*If a coding rule is not followed in the source code, this is called a "violation".*
*This violation needs to be documented with this deviation record.*
*After it gets approved, it becomes a deviation.*
*See also "MISRA Compliance:2016" document: https://rb-normen.bosch.com/NormMaster/DirectLink.do?ACTION=VIEW_STANDARD&key=DITR45666236&sprache=EN&FILE=45666236.pdf*


|Topic        |        |
|:---         |  ---:  |
|Project      | MMP2.11                         |
|Deviation ID | MMP2.11-001  |
|Status       | see Alm Story 4030922                               |
|Rule         | MisraC2012-11.4 "Conversion between pointer type and integer type."                                |
|Use-Case     | assigning the structure pointer to integer address                  |
|Reason       | Needs to read the data from Bootloader            |
|Scope        | SW parts, that need pointers to the bootloader  |
|Raised by    | see Alm Story 4030922    |
|Raised Date  | see Alm Story 4030922                                        |

|Approval     |        |
|:---         |  ---:  |
|Approved by  | see Alm Story 4030922                 |  
|Approval Date| see Alm Story 4030922 |


## Summary
Conversion of an integer into a pointer to object, may result in a pointer that is not correctly aligned, resulting in undefined behavior.

## Justification
the conversion of integer pointer to object pointer is made, is to read the data from Bootloader for Diagnostics identification services. The needed address is not in the linker file, so there is no other way to get the pointer.

## Risk assessment
The Risk is incorrect address may use, while accessing bootloader Address with structure pointer.
The address of bootloader should verify.

## Actions to Control Reporting
The Bootloader address can be verify with common DID's used in Bootloader and Diagnostic, both should give common data for bootloader.
DID list
1. F153
2. F121
3. F151
4. F10D