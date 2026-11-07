#ifndef _JAUDIO_CPUBUF_H
#define _JAUDIO_CPUBUF_H

#include "types.h"
#include "jaudio_NES/dspbuf.h"

/////////// JAUDIO CPU BUFFER DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).
s16* CpubufProcess(DSPBUF_EVENTS event);
void CpuFrameEnd();
s16* MixCpu(s32 n_samples);

/////////////////////////////////////////////////////

#endif
