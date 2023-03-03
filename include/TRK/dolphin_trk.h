#ifndef DOLPHIN_TRK_H
#define DOLPHIN_TRK_H
#include "types.h"
#ifdef __cplusplus
extern "C"{
#endif

void InitMetroTRK(void);
void exit(void);

void* TRK_memcpy(void* dst, const void* src, size_t size);
void* TRK_memset(void* dst, int val, size_t size);
#ifdef __cplusplus
}
#endif
#endif