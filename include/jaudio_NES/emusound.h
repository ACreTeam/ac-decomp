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
extern void Sound_Read();
extern void Sound_SetC000();
extern void Sound_SetE000();
extern void Sound_SetMMC();
extern void Sound_PlayMENUPCM();

#ifdef __cplusplus
}
#endif

#endif
