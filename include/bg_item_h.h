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

typedef int (*bIT_FRUIT_SET_PROC)(mActor_name_t item, int ut_x, int ut_z, s16 p0, s16 p1);
typedef void (*bIT_ITEM_TREE_FRUIT_DROP_PROC)(mActor_name_t item, int ut_x, int ut_z, xyz_t* pos);


typedef struct background_item_clip_s {
  void* _00;
  bIT_SHADOW_DRAW_PROC draw_shadow_proc;
  void* _08[(0x30 - 0x08) / sizeof(void*)];
  bIT_FRUIT_SET_PROC fruit_set_proc;
  void* _34;
  bIT_ITEM_TREE_FRUIT_DROP_PROC item_tree_fruit_drop_proc;
  void* _3C[(0x54 - 0x3C) / sizeof(void*)];
} bIT_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
