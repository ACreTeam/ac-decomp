#ifndef M_MALLOC_H
#define M_MALLOC_H

#include "types.h"
#include "libc64/__osMalloc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Arena zelda_arena; 

extern void zelda_malloc_align(u32,u32);
extern void zelda_malloc(u32);
extern void zelda_malloc_r(u32);
extern void zelda_free(void*);
extern void zelda_GetFreeArena(size_t* max, size_t* free, size_t* alloc);
extern u32 zelda_GetTotalFreeSize(void);
extern u32 zelda_GetMemBlockSize(void*);
extern void zelda_InitArena(void*, u32);
extern void zelda_AddBlockArena(void*, u32);
extern void zelda_CleanupArena(void);
extern int zelda_MallocIsInitalized();

#ifdef __cplusplus
}
#endif

#endif
