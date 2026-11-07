#ifndef _JAUDIO_DSPDRIVER_H
#define _JAUDIO_DSPDRIVER_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

/////////// JAUDIO DSP DRIVER DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).

dspch_* GetDSPchannelHandle(u32 idx);
void InitDSPchannel();
dspch_* AllocDSPchannel(u32, u32);
int DeAllocDSPchannel(dspch_*, u32);
dspch_* GetLowerDSPchannel();
dspch_* GetLowerActiveDSPchannel();
BOOL ForceStopDSPchannel(dspch_*);
BOOL BreakLowerDSPchannel(u8);
BOOL BreakLowerActiveDSPchannel(u8);
void UpdateDSPchannelAll();

/////////////////////////////////////////////////////

#endif
