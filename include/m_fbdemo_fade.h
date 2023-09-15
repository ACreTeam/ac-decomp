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
} fbdemo_fade; // size = 0x10


extern fbdemo_fade* fbdemo_fade_init(fbdemo_fade*);
extern void fbdemo_fade_move(fbdemo_fade*, int);
extern void fbdemo_fade_draw(fbdemo_fade* this, Gfx** gfxP);
extern void fbdemo_fade_startup(fbdemo_fade*);
extern void fbdemo_fade_settype(fbdemo_fade*, int);
extern void fbdemo_fade_setcolor_rgba8888(fbdemo_fade* this, u32 color);
extern u8 fbdemo_fade_is_finish(fbdemo_fade*);

#endif