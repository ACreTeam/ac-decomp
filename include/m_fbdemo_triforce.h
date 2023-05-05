#ifndef M_FBDEMO_TRIFORCE_H
#define M_FBDEMO_TRIFORCE_H

#include "types.h"
#include "PR/mbi.h"
#include "libu64/u64types.h"

typedef struct {
    /* 0x00 */ int txt;
    /* 0x04 */ int frame;
    /* 0x08 */ u8 direction;
    /* 0x09 */ u8 textureno;
    /* 0x0A */ s8 finished;
    /* 0x0B */ u8 tmp;
    /* 0x0C */ u16 normal;
    /* 0x0E*/  u8 temp2[2]; 
    /* 0x10 */ Mtx perspmtx;
    /* 0x50 */ Mtx lookatmtx;
} TransitionTriforce; // size = 0x90;

extern void fbdemo_triforce_startup(TransitionTriforce*);
extern TransitionTriforce* fbdemo_triforce_init(TransitionTriforce*);
extern void fbdemo_triforce_move(TransitionTriforce*, int);
extern void fbdemo_triforce_draw(TransitionTriforce*, Gfx**);
extern s8 fbdemo_triforce_is_finish(TransitionTriforce*);
extern void fbdemo_triforce_settype(TransitionTriforce*, int);
extern void fbdemo_fade_setcolor_rgba8888(void);


#endif