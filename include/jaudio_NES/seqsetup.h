#ifndef SEQSETUP_H
#define SEQSETUP_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct seqp seqp; // TODO

void Jaq_Reset(void);
s32 Jaq_SetSeqData(seqp* seqp, u8* param_2, u32 param_3, int param_4);
s32 Jaq_StartSeq(u8);

#ifdef __cplusplus
}
#endif

#endif
