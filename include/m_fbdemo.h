#ifndef FBDEMO_H
#define FBDEMO_H

#include "types.h"
#include "PR/mbi.h"
#include "m_lib.h"

typedef struct {
    /* 0x00 */ int cols;
    /* 0x04 */ int rows;
    /* 0x08 */ int frame;
    /* 0x0C */ xy_t* vtxData;
    /* 0x10 */ Vtx* vtxFrame1;
    /* 0x14 */ Vtx* vtxFrame2;
    /* 0x18 */ Mtx projection;
    /* 0x58 */ Mtx modelView1;
    /* 0x98 */ Mtx modelView2;
    /* 0xD8 */ Gfx* gfx; // "gfxtbl"
    /* 0xDC */ u16* zBuffer;
} fbdemo; // size = 0xE0


extern void fbdemo_init_gfx(fbdemo*);
extern void fbdemo_init_data(fbdemo*);
extern void fbdemo_cleanup(fbdemo*);
extern fbdemo* fbdemo_init(fbdemo*, int, int); 
extern void fbdemo_update(fbdemo*);
extern void fbdemo_draw(fbdemo*, Gfx**);
extern void fbdemo_move(fbdemo*);

#endif

