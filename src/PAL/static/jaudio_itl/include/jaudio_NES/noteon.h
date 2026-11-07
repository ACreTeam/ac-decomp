#ifndef _JAUDIO_NOTEON_H
#define _JAUDIO_NOTEON_H

#include "types.h"

typedef struct seqp_ seqp_;

s32 NoteON(seqp_*, s32, s32, s32, s32);
s32 NoteOFF_R(seqp_*, u8, u16);
s32 NoteOFF(seqp_*, u8);
s32 GateON(seqp_*, s32, s32, s32, s32);
void ProgramChange(s32);
BOOL CheckNoteStop(seqp_*, s32);

#endif
