#ifndef MSL_PRINTF_H
#define MSL_PRINTF_H

#include "types.h"
#include "va_args.h"


void vprintf(const char*, va_list);
void print(const char*, ...);

#endif