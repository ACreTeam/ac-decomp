#ifndef MEM_TRK_H
#define MEM_TRK_H
#include "types.h"

#ifdef __cplusplus
extern "C"{
#endif

void* TRK_memcpy(void* dst, const void* src, size_t size);
void* TRK_memset(void* dst, int val, size_t size);
void TRK_fill_mem(void*, int, size_t);


#ifdef __cplusplus
}
#endif
#endif
