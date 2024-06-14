#ifndef EFFECT_H
#define EFFECT_H

#include "types.h"
#include "jaudio_NES/audiowork.h"

extern void Nas_ChannelModInit(channel* ch);
extern void Nas_SweepInit(channel* ch);

extern void Nas_MainCtrl(group* grp);

#endif
