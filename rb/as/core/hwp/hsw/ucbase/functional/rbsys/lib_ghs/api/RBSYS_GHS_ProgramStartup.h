#ifndef RBSYS_GHS_PROGRAMSTARTUP_H__
#define RBSYS_GHS_PROGRAMSTARTUP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Interface providing GHS start-up functions
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_CompilationLanguage,
                          RBFS_CompilationLanguage_PureC,
                          RBFS_CompilationLanguage_PureCPP,
                          RBFS_CompilationLanguage_MixedCandCPP);





/* GHS intention of cinit routine is that _start is called directly from reset vector
 * and therefore no prototype will be provided.
 * Our approach is different, because we have a potentially destructive SW RAM test before
 * cinit  and therefore an own basic initialization (register & stack init).
 * This means we call _start from C and must declare the prototype by our own. */
extern void _start(void);

#if( (RBFS_CompilationLanguage == RBFS_CompilationLanguage_PureCPP) \
  || (RBFS_CompilationLanguage == RBFS_CompilationLanguage_MixedCandCPP) )
  extern void _main(void); //< definition of _main is provided by GHS
#endif



/* -------------------------------------------------------------------------- */
/* QAC|DEV xxxx: main() function with 3 arguments (freestanding environment)  */
/* -------------------------------------------------------------------------- */
/* Msg 0601: Function 'main()' is not of type 'int (void)' or                 */
/*           'int (int, char *[])                                             */
/* In a freestanding environment the name and type of the function called     */
/* at program startup are implementation-defined. (according C Standard)      */
/* -------------------------------------------------------------------------- */
#ifdef __QAC__
  #pragma PRQA_MESSAGES_OFF 601
#endif

/* GHS does not want to provide a specific prototype for main because it may differ dependent on the application
 * (different set of parameters may be required for different applications) -> see also: task 9375 */
extern int main (int argc, char **argv, char **envp);

#ifdef __QAC__
  #pragma PRQA_MESSAGES_ON 601
#endif


/* Macro usable as function attribute, that instructs the compiler to omit register save/restore code 
 * and return instruction, using GHS specific pragma */
#define RBSYS_ATTR_NO_PROLOGUE _Pragma("ghs noprologue")


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
