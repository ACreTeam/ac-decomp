#ifndef OS_MALLOC_H
#define OS_MALLOC_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "libultra/osThread.h"
#include "libultra/osMesg.h"
#include "libultra/ultratypes.h"

struct ArenaNode;

typedef struct Arena {
    /* 0x00 */ struct ArenaNode* head;
    /* 0x04 */ void* start;
    /* 0x08 */ OSMesgQueue lockQueue;
    /* 0x20 */ u8 unk_20;
    /* 0x21 */ u8 isInit;
    /* 0x22 */ u8 flag;
    /* 0x24 */ u8 pad[0x2C - 0x24];
} Arena; // size = 0x2C

typedef struct ArenaNode {
    /* 0x00 */ s16 magic;
    /* 0x02 */ s16 isFree;
    /* 0x04 */ u32 size;
    /* 0x08 */ struct ArenaNode* next;
    /* 0x0C */ struct ArenaNode* prev;
    /* 0x10 */ const char* filename;
    /* 0x14 */ s32 line;
    /* 0x18 */ OSId threadId;
    /* 0x1C */ Arena* arena;
    /* 0x20 */ OSTime time;
    /* 0x28 */ u8 unk_28[0x30 - 0x28]; // probably padding
} ArenaNode;                           // size = 0x30

void setDebugInfo(ArenaNode*, const char*, s32, Arena*);
void arena_lock_init(Arena*);
void arena_lock(Arena*);
void arena_unlock(Arena*);
ArenaNode* get_block_next(ArenaNode*);
ArenaNode* get_block_prev(ArenaNode*);
ArenaNode* search_last_block(Arena*);
void __osMallocInit(Arena*, void*, u32);
void __osMallocAddBlock(Arena*, void*, s32);
void destroy_all_block(Arena*);
void __osMallocCleanup(Arena*);
BOOL __osMallocIsInitialized(Arena*);
void __osMalloc_FreeBlockTest(Arena*, ArenaNode*);
void* __osMallocALign_NoLock(Arena*, u32, u32);
void* __osMalloc_NoLock(Arena*, u32);
void* __osMallocAlign(Arena*, u32, u32);
void* __osMalloc(Arena*, u32);
void* __osMallocR(Arena*, u32);
void __osFree_NoLock(Arena*, void*);
void __osFree(Arena*, void*);
void* __osRealloc(Arena*, void*, u32);
int __osAnalayzeArena(Arena*, u32*);
void __osGetFreeArena(Arena*, u32*, u32*, u32*);
u32 __osGetTotalFreeSize(Arena*);
u32 __osGetFreeSize(Arena*);
u32 __osGetMemBlockSize(Arena*, void*);
void __osDisplayArena(Arena*);
int __osCheckArena(Arena*);
extern int __osMallocIsInitalized(Arena*);

extern int __osMalloc_FreeBlockTest_Enable;

#endif
