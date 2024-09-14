#ifndef AICTRL_H
#define AICTRL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u32 UNIVERSAL_DACCOUNTER;
extern u32 JAC_VFRAME_COUNTER;

typedef enum _MixMode {
    MixMode_Mono,
    MixMode_MonoWide,
    MixMode_Extra,
    MixMode_Interleave,

    MixMode_Num
} MixMode;

typedef s16* (*MixCallback)(s32);

extern void Jac_HeapSetup(void* pHeap, s32 size);
extern void* OSAlloc2(u32 size);
extern void Jac_Init(void);
extern MixCallback Jac_GetMixcallback(u8* mixmode);
extern void Jac_RegisterMixcallback(MixCallback mixcallback, u8 mixmode);
extern void Jac_VframeWork(void);
extern void Jac_UpdateDAC(void);

#ifdef __cplusplus
}
#endif

#endif
