#ifndef SEQSETUP_H
#define SEQSETUP_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct seqp seqp; // TODO

void Jaq_Reset(void);
void Jaq_SetSeqData(seqp* seqp, u8* param_2, u32 param_3, int param_4);

#ifdef __cplusplus
}
#endif

#endif