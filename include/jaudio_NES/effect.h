#ifndef EFFECT_H
#define EFFECT_H

#include "types.h"
#include "jaudio_NES/audiowork.h"

extern void Nas_ChannelModInit(channel* ch);
extern void Nas_SweepInit(channel* ch);
extern void Nas_EnvInit(envp* env, envdat* data, s16* vol_out);
extern void Nas_ChannelModulation(channel* channel);
extern void Nas_MainCtrl(group* grp);
extern f32 Nas_EnvProcess(envp* process);

#endif
