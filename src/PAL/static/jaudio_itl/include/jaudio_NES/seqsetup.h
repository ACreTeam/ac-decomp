#ifndef _JAUDIO_SEQSETUP_H
#define _JAUDIO_SEQSETUP_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

typedef struct seqp_ seqp_;

void Jaq_Reset(void);
void Jaq_GetRemainFreeTracks(void);
seqp_* Jaq_HandleToSeq(u32 handle);
BOOL Jaq_StopSeq(s32 index);
s32 Jaq_SetSeqData(seqp_*, u8*, u32, u32);
s32 Jaq_SetSeqData_Limit(seqp_*, u8*, u32, u32, u8);
BOOL Jaq_SetBankNumber(seqp_* track, u8 bankNum);
BOOL Jaq_StartSeq(u32);
s32 Jaq_OpenTrack(seqp_*, u32, u32);
u32 Jaq_CloseTrack(seqp_*);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
