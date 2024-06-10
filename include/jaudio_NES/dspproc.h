#ifndef DSPPROC_H
#define DSPPROC_H

#include "types.h"

extern u32 DSPReleaseHalt(void);
extern void DsyncFrame(u32 subframes, u32 dspbuf_start, u32 dspbuf_end);

#endif
