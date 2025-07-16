#ifndef DRIVER_H
#define DRIVER_H

#include "types.h"
#include "jaudio_NES/audiowork.h"

extern Acmd* Nas_smzAudioFrame(Acmd* cmds, s32* processed_cmds, s16* pSamples, s32 nSamples);
extern Acmd* Nas_DriveRsp(s16* aiBuf, s32 aiBufLen, Acmd* cmd, s32 updateIndex);

#endif
