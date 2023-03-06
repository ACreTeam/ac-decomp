#include "libc64/osmalloc.h"

extern Arena malloc_arena;

void* malloc(size_t size) {
    return(__osMalloc(&malloc_arena, size));
}
void free(void* ptr){
    __osFree(&malloc_arena,ptr);
}

void DisplayArena(void){
    __osDisplayArena(&malloc_arena);
}

void GetFreeArena(u32* max, u32* free, u32* alloc){
    __osGetFreeArena(&malloc_arena, max, free, alloc);
}
void MallocInit(void* start, u32 size){
    __osMallocInit(&malloc_arena, start, size);
}

void MallocCleanup(void){
    __osMallocCleanup(&malloc_arena);
}
