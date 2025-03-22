#ifndef EMUSOUND_HPP
#define EMUSOUND_HPP

#include "jaudio_NES/emusound.h"

s32 __GetWave_Pulse(s32, s32);
u32 __PitchTo32_VRC_C(u16);
u32 __PitchTo32_VRC_PULSE(u16);
u32 __PitchTo32_HVC(u16);
void __Sound_Write_VRC(u16, u8);
void __Sound_Write_MMC5(u16, u8);
void __Sound_Write_A(u16, u8);
int __ProcessSoundA();
void __Sound_Write_B(u16, u8);
int __ProcessSoundB();
int __PitchTo32_HVC_D(u16);
void __Sound_Write_D(u16, u8);
s8 __GetNoise(u32);
int __ProcessSoundD();
void MoveDeltaCounter(u8);
void MoveBias();
void WriteBias(u16);
int MoveVoltage();
u32 __PitchTo32_HVC_E(u16);
void __Sound_Write_E(u16, u8);
void StartE();
int __ProcessSoundE();
s8 __GetWave_Triangle(s32);
u32 __PitchTo32_HVC_C(u16);
void __Sound_Write_C(u16, u8);
int __ProcessSoundC();
void __CreateDiskSubWave();
void __CreateDiskSubWave();
u32 __PitchTo32_DISKFM(u16);
void __Sound_Write_Disk(u16, u8);

void HS_Event_Reset();
void HS_Event_Update();
void HS_Event_Write(u16, u8);
void ProcessPhaseCounter();
void ForceProcessPhaseCounter();
int Sound_Make_HVC(s32, s16*);
void Buffer_Reset();
void Sample_Copy(u16, s16*);
s16* __FrameCallback(s32);
void __Sound_Write_HVC(u16, u8);

#endif
