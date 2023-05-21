#ifndef LIBULTRA_H
#define LIBULTRA_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/os/OSCache.h"

#define N64_SCREEN_HEIGHT 240
#define N64_SCREEN_WIDTH 320


#ifdef __cplusplus
extern "C" {
#endif

int bcmp (void *v1, void *v2, u32 size);
void bcopy(void *src, void *dst, size_t n);
void bzero(void *ptr, size_t size);
void osSyncPrintf(const char* fmt, ...);
void osWritebackDCache(void* vaddr, u32 nbytes);
u32 osGetCount(void);
OSTime osGetTime(void);

extern s32 osAppNMIBuffer[]; 
extern int osShutdown;


#ifdef __cplusplus
}
#endif

#endif
