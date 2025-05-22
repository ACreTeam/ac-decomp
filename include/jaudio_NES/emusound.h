#ifndef EMUSOUND_H
#define EMUSOUND_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void EmuSound_Start(u8* noise_data);
extern void EmuSound_Exit();
extern void Sound_Write(u16 event, u8 value, u16 maybe_frames);

extern void Sound_Reset();
extern u8 Sound_Read(u16 reg_addr);
extern void Sound_SetC000(u8* romTop);
extern void Sound_SetE000(u8* romTop);
extern void Sound_SetMMC(u8 mmcMode);
extern void Sound_PlayMENUPCM(u8 v);

#ifdef __cplusplus
}
#endif

#endif
