#ifndef MSL_PRINTF_H
#define MSL_PRINTF_H

#include "types.h"
#include "va_args.h"


extern void vprintf(const char*, va_list);
extern void printf(const char*, ...);

#endif
