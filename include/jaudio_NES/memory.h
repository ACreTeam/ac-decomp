#ifndef JAUDIO_MEMORY_H
#define JAUDIO_MEMORY_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

extern void Nas_HeapInit(ALHeap* heap, u8* base, s32 len);
extern void* Nas_HeapAlloc(ALHeap* heap, s32 size);

#endif
