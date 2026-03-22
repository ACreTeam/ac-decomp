/* malloc_shim.c — Replaces the game's libc64/malloc.c on macOS.
 *
 * The game's original malloc.c uses an OSArena with u32 pointer arithmetic,
 * which truncates 64-bit macOS addresses and causes crashes/infinite blocks.
 * This shim routes malloc()/free() directly to the macOS default malloc zone,
 * avoiding both the 32-bit address issue and infinite recursion.
 */
#include "libc64/__osMalloc.h"
#include "libc64/malloc.h"
#include <malloc/malloc.h>  /* malloc_default_zone, malloc_zone_malloc/free */
#include <stdio.h>
#include <string.h>

/* Dummy arena — only malloc_arena.initialized is ever checked externally */
OSArena malloc_arena;

void* malloc(size_t size) {
    return malloc_zone_malloc(malloc_default_zone(), size);
}

void free(void* ptr) {
    malloc_zone_free(malloc_default_zone(), ptr);
}

void DisplayArena(void) {}

void GetFreeArena(size_t* max, size_t* free_bytes, size_t* alloc) {
    if (max)        *max        = 32u * 1024u * 1024u;
    if (free_bytes) *free_bytes = 16u * 1024u * 1024u;
    if (alloc)      *alloc      = 0;
}

void MallocInit(void* start, size_t size) {
    (void)start; (void)size;
    /* Mark arena as initialized so __osMallocIsInitalized() returns TRUE */
    malloc_arena.initialized = TRUE;
    fprintf(stderr, "[malloc] MallocInit: using system allocator (macOS 64-bit)\n");
}

void MallocCleanup(void) {}
