#ifndef AUDIOCONST_H
#define AUDIOCONST_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

typedef struct ALGlobalsConst_ {
    s8 maxChan;
    s16 timeBase;
    s32 acmdBufSize;
    s32 fixSize;
    s32 ememSize;
} ALGlobalsConst;

extern ALGlobalsConst AGC;

#endif
