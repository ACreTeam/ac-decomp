#ifndef XRINTF_H
#define XRINTF_H

#include "types.h"
#include "va_args.h"

#ifdef __cplusplus
extern "C"{
#endif

extern int _Printf(void* (*prout_func)(void*, const char*, int), char* buf, const char* fmt, va_list ap);

#ifdef __cplusplus
}
#endif
#endif
