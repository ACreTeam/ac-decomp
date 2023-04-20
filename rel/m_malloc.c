#include "m_malloc.h"

extern Arena zelda_arena; 

void zelda_malloc_align(u32 size, u32 align){
    __osMallocAlign(&zelda_arena, size, align);
}

void zelda_malloc(u32 size){
    __osMalloc(&zelda_arena,size);
}

void zelda_malloc_r(u32 size){
    __osMallocR(&zelda_arena, size);
}

void zelda_free(void* ptr){
    __osFree(&zelda_arena, ptr);
}

void zelda_GetFreeArena(size_t* max, size_t* free, size_t* alloc){
    __osGetFreeArena(&zelda_arena,max,free,alloc);
}

size_t zelda_GetTotalFreeSize(void){
    return __osGetTotalFreeSize(&zelda_arena);
}

size_t zelda_GetMemBlockSize(void* ptr){
    return __osGetMemBlockSize(&zelda_arena, ptr);
}

void zelda_InitArena(void* start, u32 size){
    __osMallocInit(&zelda_arena, start, size);
}
void zelda_AddBlockArena(void* start, u32 size){
    __osMallocAddBlock(&zelda_arena,start, size);
}

void zelda_CleanupArena(void){
    __osMallocCleanup(&zelda_arena);
}

void zelda_MallocIsInitalized(void){
     __osMallocIsInitalized(&zelda_arena);
}