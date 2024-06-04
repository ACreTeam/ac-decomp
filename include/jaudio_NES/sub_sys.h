#ifndef SUB_SYS_H
#define SUB_SYS_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

extern s32 CreateAudioTask(Acmd* cmds, s16* pSamples, u32 nSamples, s32 param_4);

#endif
