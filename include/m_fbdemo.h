#ifndef FBDEMO_H
#define FBDEMO_H

#include "types.h"
#include "PR/mbi.h"

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
} TransitionTileVtxData; // size = 0x8

typedef struct {
    /* 0x00 */ int cols;
    /* 0x04 */ int rows;
    /* 0x08 */ int frame;
    /* 0x0C */ TransitionTileVtxData* vtxData;
    /* 0x10 */ Vtx* vtxFrame1;
    /* 0x14 */ Vtx* vtxFrame2;
    /* 0x18 */ Mtx projection;
    /* 0x58 */ Mtx modelView;
    /* 0x98 */ Mtx unk_98;
    /* 0xD8 */ Gfx* gfx; // "gfxtbl"
    /* 0xDC */ u16* zBuffer;
} TransitionTile; // size = 0xE0


extern void fbdemo_init_gfx(TransitionTile*);
extern void fbdemo_init_data(TransitionTile*);
extern void fbdemo_cleanup(TransitionTile*);
extern TransitionTile* fbdemo_init(TransitionTile*, int, int); 
extern void fbdemo_update(TransitionTile*);
extern void fbdemo_draw(TransitionTile*, Gfx**);
extern void fbdemo_move(void);

#endif

