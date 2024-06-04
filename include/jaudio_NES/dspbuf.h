#ifndef DSPBUF_H
#define DSPBUF_H

#include "types.h"
#include "jaudio_NES/audiocommon.h"

extern u32 DspbufProcess(DSPBUF_EVENTS event);
extern s16* MixDsp(s32 nSamples);
extern void UpdateDSP(void);
extern void DspFrameEnd(void);

#endif
