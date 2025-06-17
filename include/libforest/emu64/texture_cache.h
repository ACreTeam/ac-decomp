#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include "types.h"
#include "libforest/gbi_extensions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define TEX_CACHE_ALIGNMENT (32 - 1) /* 32 byte alignment */
#define NUM_TEXTURE_CACHE_DATA 10
#define TEXTURE_CACHE_LIST_SIZE 256
#define TMEM_ENTRIES 128

#define TEX_CACHE_ALIGN(n) ((n + TEX_CACHE_ALIGNMENT) & ~TEX_CACHE_ALIGNMENT)

/* These would be initialized by the linker. TODO: Is there a better way to do this? */
extern void* _data_segment_start;
extern void* _sdata2_segment_end;

typedef struct {
    void* addr;
    Gloadblock loadblock;
    Gloadtile loadtile;
    Gsetimg2 setimg2;
} tmem_t;

typedef struct {
    void* start; /* Start RAM address of cache */
    void* end;   /* End RAM address of cache */
} texture_cache_data_entry_t;

typedef struct {
    void* original;  /* Original RAM address */
    void* converted; /* Converted RAM address */
} texture_cache_entry_t;

typedef struct texture_cache_s texture_cache_t;

typedef void* (*texture_cache_search_func)(void* addr);
typedef int (*texture_cache_entry_func)(void* original, void* converted);
typedef void* (*texture_cache_alloc_func)(texture_cache_t* cache, u32 size);

typedef struct {
    texture_cache_search_func search;
    texture_cache_entry_func entry;
    texture_cache_alloc_func alloc;
} texture_cache_funcs;

typedef struct texture_cache_s {
    texture_cache_funcs* funcs; /* Pointer to texture cache funcs */
    u8* buffer_start;           /* Start address of cache buffer */
    u8* buffer_end;             /* End address of cache buffer */
    u8* buffer_current;         /* Current write position of the cache buffer */
    u8* last_alloc_end;         /* Points to end address from last cache alloc */
    u8* last_alloc_start;       /* Points to the start address from last cache alloc */
    bool is_overflow;           /* Set to true when the cache is full */
    u32 buffer_pos;             /* Write index into cache buffer */
} texture_cache_t;

/* TMEM map */
// static tmem_t tmem_map[TMEM_ENTRIES];

#define TEX_BUFFER_DATA_SIZE 0xC000
#define TEX_BUFFER_BSS_SIZE 0x400

#ifdef __cplusplus
}
#endif

#endif
