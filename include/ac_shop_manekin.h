#ifndef AC_SHOP_MANEKIN_H
#define AC_SHOP_MANEKIN_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct manekin_actor_s {
  xyz_t wpos;
  int ut_x;
  int ut_z;
  mActor_name_t item;
  u8* tex_p;
  u8* palette_p;
  mCoBG_bg_regist_c bg_regist;
  int move_bg_num;
  int _4C;
  int naked;
} MANEKIN_ACTOR;

typedef struct shop_manekin_actor_s SHOP_MANEKIN_ACTOR;

typedef void (*aSM_MANEKIN_DMA_AGAIN_PROC)();
typedef void (*aSM_CHANGE2NAKEDMANEKIN_PROC)(int ut_x, int ut_z);
typedef void (*aSM_NAKED2CLOTH_PROC)(int ut_x, int ut_z);

typedef struct shop_manekin_clip_s {
  ACTOR* shop_manekin_actor_p;
  aSM_MANEKIN_DMA_AGAIN_PROC manekin_dma_again_proc;
  aSM_CHANGE2NAKEDMANEKIN_PROC change2naked_manekin_proc;
  aSM_NAKED2CLOTH_PROC naked2cloth_proc;
} aSM_Clip_c;

struct shop_manekin_actor_s {
  ACTOR actor_class;
  int current_block_manekin_num;
  MANEKIN_ACTOR* manekin_actors;
  int now_block_x;
  int now_block_z;
  aSM_Clip_c clip;
  u8* naked_tex_p;
  u8* naked_pal_p;
  int _19C;
};

extern ACTOR_PROFILE Shop_Manekin_Profile;

#ifdef __cplusplus
}
#endif

#endif
