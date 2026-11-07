#ifndef JAUDIO_RANDOM_H
#define JAUDIO_RANDOM_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/audiowork.h"

#ifdef __cplusplus
extern "C" {
#endif

extern s32 GetRandom_s32(void);
extern f32 GetRandom_sf32(void);

#ifdef __cplusplus
}
#endif

#endif
