#ifndef AUDIO_DEFS_H
#define AUDIO_DEFS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define VOICE_MODE_ANIMALESE 0
#define VOICE_MODE_CLICK 1
#define VOICE_MODE_SILENT 2

/* audio is monophonic */
#define MONO(id) (id | 0x1000)

#define SE_CURSOR_MOVE 0x01
#define SE_MENU_EXIT 0x02
#define SE_COIN 0x4C
#define SE_REGISTER MONO(0x50)

#ifdef __cplusplus
}
#endif

#endif
