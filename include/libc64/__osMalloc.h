#ifndef OS_MALLOC_H
#define OS_MALLOC_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "libultra/osThread.h"
#include "libultra/osMesg.h"
#include "libultra/ultratypes.h"

#ifdef __cplusplus
extern "C" {
#endif // !__cplusplus

#define OSArena_FLAG_CLEAR_MEM_ON_ALLOC (1 << 0)
#define OSArena_FLAG_CLEAR_MEM_ON_FREE (1 << 1)
#define OSArena_FLAG_FREE_BLOCK_TEST (1 << 2)

typedef struct OSMemBlock_ {
    /* 0x00 */ s16 magic;
    /* 0x02 */ s16 free;
    /* 0x04 */ s32 size;
    /* 0x08 */ struct OSMemBlock_* next;
    /* 0x0C */ struct OSMemBlock_* prev;
    /* 0x10 */ const char* file;
    /* 0x14 */ s32 line;
    /* 0x18 */ OSId threadId;
    /* 0x1C */ struct OSArena_* arena;
    /* 0x20 */ OSTime time;
    /* 0x28 */ u8 pad[0x30 - 0x28];
} OSMemBlock;                           // size = 0x30

typedef struct OSArena_ {
    /* 0x00 */ OSMemBlock* head;
    /* 0x04 */ u8* base;
    /* 0x08 */ OSMessageQueue lockQueue;
    /* 0x20 */ u8 _28;
    /* 0x21 */ u8 initialized;
    /* 0x22 */ u8 flags;
} OSArena; // size = 0x2C

extern void __osMallocInit(OSArena* arena, u8* base, s32 size);
extern void __osMallocAddBlock(OSArena* arena, u8* base, s32 size);
extern void __osMallocCleanup(OSArena* arena);
extern BOOL __osMallocIsInitalized(OSArena* arena);
extern void* __osMallocAlign(OSArena* arena, u32 size, u32 align);
extern void* __osMalloc(OSArena* arena, u32 size);
extern void* __osMallocR(OSArena* arena, u32 size);
extern void __osFree(OSArena* arena, void* ptr);
extern void* __osRealloc(OSArena* arena, void* ptr, u32 size);
extern void __osGetFreeArena(OSArena* arena, u32* max_free_block_size, u32* free_blocks_size, u32* used_blocks_size);
extern u32 __osGetTotalFreeSize(OSArena* arena);
extern u32 __osGetFreeSize(OSArena* arena);
extern s32 __osGetMemBlockSize(OSArena* arena, void* ptr);
extern void __osDisplayArena(OSArena* arena);
extern int __osCheckArena(OSArena* arena);

extern int __osMalloc_FreeBlockTest_Enable;

#ifdef __cplusplus
}
#endif // !__cplusplus

#endif
