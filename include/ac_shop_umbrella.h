#ifndef AC_SHOP_UMBRELLA_H
#define AC_SHOP_UMBRELLA_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aShopUmbrella_STATE_WAIT,
    aShopUmbrella_STATE_DELETE,
    aShopUmbrella_STATE_NONE,

    aShopUmbrella_STATE_NUM
};

typedef struct shop_umbrella_actor_s SHOP_UMBRELLA_ACTOR;

typedef void (*aShopUmbrella_UMBRELLA_DMA_AGAIN_PROC)();
typedef void (*aShopUmbrella_DELETE_UMBRELLA_PROC)(int ut_x, int ut_z);

typedef struct shop_umbrella_actor_clip_s {
  ACTOR* shop_umbrella_actor_p;
  aShopUmbrella_UMBRELLA_DMA_AGAIN_PROC umbrella_dma_again_proc;
  aShopUmbrella_DELETE_UMBRELLA_PROC delete_umbrella_proc;
} aShopUmbrella_Clip_c;

typedef struct umbrella_actor_s {
  xyz_t wpos;
  int ut_x;
  int ut_z;
  mActor_name_t item;
  int umbrella_idx;
  int _1C;
  mCoBG_bg_regist_c bg_regist;
  int move_bg_idx;
  int _4C;
  s16 state;
  f32 scale;
} aShopUmbrella_umbrella_c;

struct shop_umbrella_actor_s {
  ACTOR actor_class;
  int umbrella_num;
  aShopUmbrella_umbrella_c* umbrellas;
  int bx;
  int bz;
  aShopUmbrella_Clip_c clip;
};

extern ACTOR_PROFILE Shop_Umbrella_Profile;

#ifdef __cplusplus
}
#endif

#endif
