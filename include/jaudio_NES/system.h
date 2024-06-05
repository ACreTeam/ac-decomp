#ifndef SYSTEM_H
#define SYSTEM_H

#include "types.h"

extern void Nas_InitAudio(u64* acmdBuf, s32 acmdBufSize);
extern void Nas_FastCopy(u8* SrcAddr, u8* DestAdd, size_t size, s32 medium);

#endif
