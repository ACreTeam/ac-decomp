#ifndef SPRINTF_H
#define SPRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __APPLE__
int sprintf(char* dst, const char* fmt, ...);
#else
#include <stdio.h>
#endif

#ifdef __cplusplus
}
#endif

#endif