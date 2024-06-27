#ifndef OS_TRUST_H__
#define OS_TRUST_H__

extern int OSSim_IsTrustedMode;

#define OS_RUNNING_CODE_IS_TRUSTED() (OSSim_IsTrustedMode)
#define OS_SET_TRUSTED_MODE() (OSSim_IsTrustedMode = TRUE)
#define OS_SET_UNTRUSTED_MODE() (OSSim_IsTrustedMode = FALSE)

#endif