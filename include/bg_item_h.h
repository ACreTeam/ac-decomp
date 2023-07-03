#ifndef BG_ITEM_H_H
#define BG_ITEM_H_H

#include "types.h"
#include "PR/mbi.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct background_item_shadow_s {
  u32 vtx_num;
  u8* vtx_fix_flags;
  f32 size;
  Vtx* vtx;
  Gfx* gfx;
} bIT_ShadowData_c;

typedef void (*bIT_SHADOW_DRAW_PROC)(GAME*, bIT_ShadowData_c*, int);

typedef struct background_item_clip_s {
  void* _00;
  bIT_SHADOW_DRAW_PROC draw_shadow_proc;
  void* _08[(0x54 - 0x08) / sizeof(void*)];
} bIT_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
