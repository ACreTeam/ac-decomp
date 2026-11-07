#ifndef AUDIOWORK_H
#define AUDIOWORK_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/audiotable.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*VFRAME_CALLBACK)(void);
typedef u32 (*GRP_CALLBACK)(s8, group*);
typedef void* (*SOUND_CALLBACK)(smzwavetable*, s32, s8, s32);
typedef Acmd* (*DACOUT_CALLBACK)(Acmd*, s32, s32);

extern AudioGlobals AG;
extern VFRAME_CALLBACK NA_VFRAME_CALLBACK;
extern SequenceCallback NA_CALLBACK;
extern GRP_CALLBACK NA_GRP_CALLBACK;
extern SOUND_CALLBACK NA_SOUND_CALLBACK;
extern DACOUT_CALLBACK NA_DACOUT_CALLBACK;

#ifdef __cplusplus
}
#endif

#endif
