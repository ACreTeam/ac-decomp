#ifndef M_MALLOC_H
#define M_MALLOC_H

#include "types.h"
#include "libc64/__osMalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern OSArena zelda_arena; 

extern void* zelda_malloc_align(size_t,u32);
extern void* zelda_malloc(size_t);
extern void* zelda_malloc_r(size_t);
extern void zelda_free(void*);
extern void zelda_GetFreeArena(size_t* max, size_t* free, size_t* alloc);
extern size_t zelda_GetTotalFreeSize(void);
extern size_t zelda_GetMemBlockSize(void*);
extern void zelda_InitArena(void*, size_t);
extern void zelda_AddBlockArena(void*, size_t);
extern void zelda_CleanupArena(void);
extern int zelda_MallocIsInitalized();

#ifdef __cplusplus
}
#endif

#endif
