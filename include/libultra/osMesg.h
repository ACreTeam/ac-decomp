#ifndef OS_MESG_H
#define OS_MESG_H

#include "types.h"
#include "dolphin/os/OSThread.h"

typedef void* OSMesg;

typedef struct OSMesgQueue {
    /* 0x00 */ OSThread* mtqueue;
    /* 0x04 */ OSThread* fullqueue;
    /* 0x08 */ s32 validCount;
    /* 0x0C */ s32 first;
    /* 0x10 */ s32 msgCount;
    /* 0x14 */ OSMesg* msg;
} OSMesgQueue; // size = 0x18

#endif
