#ifndef CPUBUF_H
#define CPUBUF_H

#include "types.h"
#include "jaudio_NES/audiocommon.h"

extern u32 CpubufProcess(DSPBUF_EVENTS event);
extern void CpuFrameEnd(void);
extern s16* MixCpu(s32 nSamples);

#endif
