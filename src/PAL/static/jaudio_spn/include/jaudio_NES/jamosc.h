#ifndef _JAUDIO_JAMOSC_H
#define _JAUDIO_JAMOSC_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

typedef struct seqp_ seqp_;

void Osc_Update_Param(seqp_* track, u8 id, f32 val);
void Osc_Setup_Simple(seqp_* track, u8);
void Osc_Clear_Overwrite(seqp_* track);
void Osc_Init_Env(seqp_* track);
void Osc_Setup_SimpleEnv(seqp_* track, u8, u32);
void Osc_Setup_ADSR(seqp_* track, s16*);
void Osc_Setup_Full(seqp_* track, u8, u32, u32);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
