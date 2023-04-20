#ifndef M_MALLOC_H
#define M_MALLOC_H
#include "libc64/__osMalloc.h"

Arena zelda_arena; 


void zelda_malloc_align(u32,u32);
void zelda_malloc(u32);
void zelda_malloc_r(u32);
void zelda_free(void*);
void zelda_GetFreeArena(u32*,u32*,u32*);
u32 zelda_GetTotalFreeSize(void);
u32 zelda_GetMemBlockSize(void*);
void zelda_InitArena(void*, u32);
void zelda_AddBlockArena(void*, u32);
void zelda_CleanupArena(void);
void zelda_MallocIsInitialized(void);
#endif