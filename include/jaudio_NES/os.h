#ifndef OS_H
#define OS_H

#include "types.h"
#include "libultra/libultra.h"

extern void Z_osWritebackDCacheAll();
extern void osInvalDCache2(void* src, s32 size);
extern void osWritebackDCache2(void* src, s32 size);
extern void Z_osCreateMesgQueue(OSMesgQueue* mq, OSMesg* msg, s32 count);
extern s32 Z_osSendMesg(OSMesgQueue* mq, OSMesg msg, s32 flags);
extern s32 Z_osRecvMesg(OSMesgQueue* mq, OSMesg* msg, s32 flags);
extern s32 Z_osEPiStartDma(OSPiHandle* handler, OSIoMesg* msg, s32 dir);
extern void Z_bcopy(void* src, void* dst, size_t size);

#endif
