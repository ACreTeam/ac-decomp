#ifndef AUDIO_DEFS_H
#define AUDIO_DEFS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* audio is monophonic */
#define MONO(id) (id | 0x1000)

#define SE_COIN 0x4C
#define SE_REGISTER MONO(0x50)

#ifdef __cplusplus
}
#endif

#endif
