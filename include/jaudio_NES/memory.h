#ifndef JAUDIO_MEMORY_H
#define JAUDIO_MEMORY_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

extern void Nas_HeapInit(ALHeap* heap, u8* base, s32 len);
extern void* Nas_HeapAlloc(ALHeap* heap, s32 size);
extern void Nas_SzStayDelete(s32 type);

extern void Nas_SetDelayLineParam(s32 delayIdx, s32 param_type, s32 param_value, s32 init);

extern void Nas_SetBPFilter(s16* filter, s32 lowpass_cutoff, s32 highpass_cutoff);

extern s32 Nas_SpecChange(void);

#endif
