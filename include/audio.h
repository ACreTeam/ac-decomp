#ifndef AUDIO_H
#define AUDIO_H

#include "types.h"
#include "audio_defs.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(TempoBeat_c) == 2 */
typedef struct audio_tempo_beat_s {
  /* 0x00 */ u8 tempo;
  /* 0x01 */ s8 beat;
} TempoBeat_c;

extern void sAdo_GameFrame();
extern void sAdo_SoftReset();

extern void sAdo_SysLevStop(u8 id);
extern void sAdo_SysLevStart(u8 id);

extern void sAdo_SysTrgStart(u16 id);

/* Not sure about the last param name */
extern void sAdo_VoiceSe(u8 num, u8 num2, u8 num3, s16 character_idx, u8 scale, u8 mode);

#ifdef __cplusplus
}
#endif

#endif
