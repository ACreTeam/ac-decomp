#ifndef AUDIO_H
#define AUDIO_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void sAdo_GameFrame();
extern void sAdo_SoftReset();

/* Not sure about the last param name */
extern void sAdo_VoiceSe(u8 num, u8 num2, u8 num3, s16 character_idx, u8 scale, u8 mode);

#ifdef __cplusplus
}
#endif

#endif
