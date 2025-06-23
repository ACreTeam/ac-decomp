#ifndef MSL_PRINTF_H
#define MSL_PRINTF_H

#include "stddef.h"
#include "libc/stdarg.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int vprintf(const char*, va_list);
extern int vsprintf(char*, const char*, va_list);
extern int vsnprintf(char*, size_t, const char*, va_list);
extern int printf(const char*, ...);
int snprintf(char* s, size_t n, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
