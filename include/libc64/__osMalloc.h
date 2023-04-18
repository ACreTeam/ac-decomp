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
} Arena; // size = 0x24

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
    /* 0x28 */ u8 unk_28[0x30-0x28]; // probably padding
} ArenaNode; // size = 0x30

void* __osMalloc(Arena*, size_t);
void __osFree(Arena*, void*);
void __osDisplayArena(Arena*);
void __osGetFreeArena(Arena*, u32*, u32*, u32*);
void __osMallocInit(Arena*, void*, u32);
void __osMallocCleanup(Arena*);

#endif
