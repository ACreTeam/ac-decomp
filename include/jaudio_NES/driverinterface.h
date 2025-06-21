#ifndef _JAUDIO_DRIVERINTERFACE_H
#define _JAUDIO_DRIVERINTERFACE_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

/////////// JAUDIO DRIVER INTERFACE DEFINITIONS ///////////
// Global functions (all C++, so no extern C wrap).
void Channel_SetMixerLevel(f32);
jcs_* Get_GlobalHandle();
int List_CountChannel(jc_**);
int List_CutChannel(jc_*);
jc_* List_GetChannel(jc_**);
void List_AddChannelTail(jc_**, jc_*);
void List_AddChannel(jc_**, jc_*);
int FixAllocChannel(jcs_*, u32);
int FixReleaseChannel(jc_*);
int FixReleaseChannelAll(jcs_*);
int FixMoveChannelAll(jcs_*, jcs_*);
void InitJcs(jcs_*);
void Channel_Init(jc_*);
void InitGlobalChannel();
void UpdateJcToDSP(jc_*);
void UpdateEffecterParam(jc_*);
void DoEffectOsc(jc_*, u8, f32);
BOOL StopLogicalChannel(jc_*);
BOOL CheckLogicalChannel(jc_*);
BOOL PlayLogicalChannel(jc_*);
BOOL ResetInitialVolume(jc_*);
BOOL Add_WaitDSPChannel(jc_*);
BOOL Del_WaitDSPChannel(jc_*);
void __Entry_WaitChannel(u8);
void EntryCheck_WaitDSPChannel();
BOOL ForceStopLogicalChannel(jc_*);

///////////////////////////////////////////////////////////

#endif
