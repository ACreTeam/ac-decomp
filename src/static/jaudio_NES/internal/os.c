#include "jaudio_NES/os.h"
#include "dolphin/os.h"
#include "jaudio_NES/dummyrom.h"
#include "jaudio_NES/sample.h"

extern void Z_osWritebackDCacheAll() {
}

extern void osInvalDCache2(void* src, s32 size) {
    DCInvalidateRange(src, size);
}

extern void osWritebackDCache2(void* src, s32 size) {
    DCStoreRange(src, size);
}

extern void Z_osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 count) {
    mq->msg = msg;
    mq->msgCount = count;
    mq->validCount = 0;
    mq->first = 0;
}

extern s32 Z_osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags) {
    if (!mq) return -1;
    if (mq->validCount == mq->msgCount) {
        return -1;
    }

    int count = mq->first + mq->validCount;

    if (count >= mq->msgCount) {
        count -= mq->msgCount;
    }

    /* Store as 32-bit: all jaudio messages are 32-bit integers, and callers
     * receive via (OSMesg*)&s32_var.  Using u32* avoids an 8-byte write into
     * a 4-byte slot that would corrupt adjacent stack/saved registers on
     * 64-bit macOS (where OSMesg = void* = 8 bytes). */
    ((u32*)mq->msg)[count] = (u32)(uintptr_t)msg;

    mq->validCount++;

    return 0;
}

extern s32 Z_osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags) {
    if (!mq) { if (msg) *msg = NULL; return -1; }
    if (flags == OS_MESG_BLOCK) {
        while (!mq->validCount) {};
    }

    if (mq->validCount == 0) {
        if (msg != NULL) {
            *msg = NULL;
        }
        return -1;
    }

    mq->validCount -= 1;

    if (msg != NULL) {
        /* Read as 32-bit and zero-extend; matches the 32-bit write in Z_osSendMesg
         * and the s32 variables callers use to hold the received message. */
        *(u32*)msg = ((u32*)mq->msg)[mq->first];
    }

    mq->first++;

    if (mq->first == mq->msgCount) {
        mq->first = 0;
    }

    return 0;
}

extern s32 Z_osEPiStartDma(OSPiHandle* handler, OSIoMesg* msg, s32 dir) {
    ARAMStartDMAmesg(1, (uintptr_t)msg->dramAddr, msg->devAddr, msg->size, 0, msg->hdr.retQueue);
    return 0;
}

void Z_bcopy(void* src, void* dst, size_t size) {
    Jac_bcopy(src, dst, size);
}
