#ifndef DSPPROC_H
#define DSPPROC_H

#include "types.h"

extern s32 DSPSendCommands(u32* commands, u32 count);
extern u32 DSPReleaseHalt();
extern void DSPWaitFinish();
extern void DsetupTable(u32 arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4);
extern void DsyncFrame(u32 subframes, u32 dspbuf_start, u32 dspbuf_end);
extern void DwaitFrame();
extern void DiplSec(u32 arg0);
extern void DagbSec(u32 arg0);

#endif
