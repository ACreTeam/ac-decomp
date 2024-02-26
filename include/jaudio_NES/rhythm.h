#ifndef RHYTHM_H
#define RHYTHM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_RhythmStart(void*, u8,u8);
extern void Na_RhythmStop(void*);
extern void Na_RhythmAllStop();
extern f32 Na_GetRhythmAnimCounter(void*);
extern f32 Na_GetRhythmDelay(void*);
extern f32 Na_GetRhythmInfo(void*);
extern void Na_SetRhythmInfo(f32);

#ifdef __cplusplus
}
#endif

#endif