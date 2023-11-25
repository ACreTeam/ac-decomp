#ifndef MALLOC_H
#define MALLOC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* malloc(size_t size);
extern void free(void* ptr);

extern void MallocInit(void* base, size_t len);
extern void MallocCleanup();
extern int  MallocIsInitalized();
extern void GetFreeArena(size_t* max_size, size_t* free_size, size_t* alloc_size);
extern int CheckArena(); /* @unused */
extern void DisplayArena();

#ifdef __cplusplus
}
#endif

#endif
