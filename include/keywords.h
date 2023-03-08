#ifndef UCH_KEYWORDS_H
#define UCH_KEYWORDS_H

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
#include <stdnoreturn.h>
#elseif defined(__cplusplus) && __cplusplus >= 201103L
#define noreturn [[noreturn]]
#else
#define noreturn
#endif

#ifndef __has_attribute
#define __has_attribute 0
#endif

#if __has_attribute(warn_unused_result)
#define nodiscard __attribute__((warn_unused_result))
#else
#define nodiscard
#endif

#if __has_attribute(fallthrough)
#define fallthrough __attribute__((fallthrough))
#else
#define fallthrough
#endif

#endif //UCH_KEYWORDS_H
