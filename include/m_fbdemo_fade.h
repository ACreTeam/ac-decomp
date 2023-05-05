#ifndef M_FBDEMO_FADE_H
#define M_FBDEMO_FADE_H

#include "types.h"
#include "PR/mbi.h"
#include "libu64/u64types.h"

typedef struct {
    /* 0x000 */ u8 type;
    /* 0x001 */ u8 isDone;
    /* 0x002 */ u8 direction;
    /* 0x004 */ Color_RGBA8_u32 color;
    /* 0x008 */ s16 frame;
    /* 0x00A */ u16 unkA;
    /* 0x00C */ u16 timer;
} TransitionFade; // size = 0x10


extern TransitionFade* fbdemo_fade_init(TransitionFade*);
extern void fbdemo_fade_move(TransitionFade*, int);
extern void fbdemo_fade_startup(TransitionFade*);
extern void fbdemo_fade_settype(TransitionFade*, int);
extern void fbdemo_fade_setcolor_rgba8888(TransitionFade*, u32);
extern u8 fbdemo_fade_is_finish(TransitionFade*);

#endif