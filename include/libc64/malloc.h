#ifndef OS_MALLOC_H
#define OS_MALLOC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* malloc(size_t size);
extern void free(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
