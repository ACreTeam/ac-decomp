#ifndef RHYTHM_H
#define RHYTHM_H

#include "types.h"
#include "audio.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_RhythmStart(u32, s8, s8);
extern void Na_RhythmStop(u32);
extern void Na_RhythmAllStop();
extern f32 Na_GetRhythmAnimCounter(u32);
extern s8 Na_GetRhythmDelay(u32);
extern void Na_GetRhythmInfo(TempoBeat_c* rhythm);
extern void Na_SetRhythmInfo(TempoBeat_c* rhythm);

#ifdef __cplusplus
}
#endif

#endif
