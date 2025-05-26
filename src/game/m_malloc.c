#include "m_malloc.h"

OSArena zelda_arena;

extern void* zelda_malloc_align(size_t size, u32 align) {
  return __osMallocAlign(&zelda_arena, size, align);
}

extern void* zelda_malloc(size_t size) {
  return __osMalloc(&zelda_arena,size);
}

extern void* zelda_malloc_r(size_t size) {
  return __osMallocR(&zelda_arena, size);
}

extern void zelda_free(void* ptr) {
  __osFree(&zelda_arena, ptr);
}

extern void zelda_GetFreeArena(size_t* max, size_t* free, size_t* alloc) {
  __osGetFreeArena(&zelda_arena,max,free,alloc);
}

extern size_t zelda_GetTotalFreeSize(void) {
  return __osGetTotalFreeSize(&zelda_arena);
}

extern size_t zelda_GetMemBlockSize(void* ptr) {
  return __osGetMemBlockSize(&zelda_arena, ptr);
}

extern void zelda_InitArena(void* start, size_t size) {
  __osMallocInit(&zelda_arena, start, size);
}
extern void zelda_AddBlockArena(void* start, size_t size) {
  __osMallocAddBlock(&zelda_arena,start, size);
}

extern void zelda_CleanupArena() {
  __osMallocCleanup(&zelda_arena);
}

extern int zelda_MallocIsInitalized() {
  return __osMallocIsInitalized(&zelda_arena);
}
