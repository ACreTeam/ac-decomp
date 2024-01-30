#ifndef MSL_PRINTF_H
#define MSL_PRINTF_H

#include "types.h"
#include "va_args.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void vprintf(const char*, va_list);
extern void printf(const char*, ...);
int snprintf(char* s, size_t n, const char* format, ...);

#ifdef __cplusplus
}
#endif

#endif
