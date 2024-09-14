#ifndef OS_MESG_H
#define OS_MESG_H

#include "types.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/os/OSMessage.h"

#define OS_MESG_NOBLOCK     0
#define OS_MESG_BLOCK       1

typedef void* OSMesg;

typedef struct OSMesgQueue_s {
    /* 0x00 */ OSThread* mtqueue;
    /* 0x04 */ OSThread* fullqueue;
    /* 0x08 */ volatile int validCount;
    /* 0x0C */ int first;
    /* 0x10 */ int msgCount;
    /* 0x14 */ OSMesg* msg;
} OSMesgQueue; // size = 0x18

extern void osCreateMesgQueue(OSMessageQueue* mq, OSMessage msg, int flags);
extern int osSendMesg(OSMessageQueue* mq, OSMessage msg, int flags);
extern int osRecvMesg(OSMessageQueue* mq, OSMessage* msg, int flags);

#endif
