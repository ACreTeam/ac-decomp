#ifndef AUDIOCONST_H
#define AUDIOCONST_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

extern fxconfig NA_HALL_DELAY;

typedef struct _na_spec_config {
    u32 _00;
    u8 _04;
    u8 _05;
    u8 _06;
    u8 _07;
    u8 _08;
    u8 _09;
    u8 _0A;
    u8 _0B;
    fxconfig* _0C;
    u16 _10;
    u16 _12;
    u16 _14;
    u16 _16;
    s32 _18;
    s32 _1C;
    s32 _20;
    s32 _24;
    s32 _28;
    s32 _2C;
    s32 _30;
    s32 _34;
} na_spec_config;

extern na_spec_config NA_SPEC_CONFIG[1];
typedef struct ALGlobalsConst_ {
    s8 maxChan;
    s16 timeBase;
    s32 acmdBufSize;
    s32 fixSize;
    s32 ememSize;
} ALGlobalsConst;

extern ALGlobalsConst AGC;

#endif
