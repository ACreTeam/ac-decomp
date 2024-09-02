#ifndef AC_SHOP_GOODS_H
#define AC_SHOP_GOODS_H

#include "types.h"
#include "m_actor.h"
#include "ac_shop_goods_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSG_SINGLE_DRAW_NUM 9

typedef struct ac_shop_goods_s SHOP_GOODS_ACTOR;

typedef struct ac_shop_good_single_draw_s {
    mActor_name_t item;
    s16 layer;
    xyz_t target_pos;
    xyz_t current_pos;
    xyz_t start_pos;
    f32 scale;
    u16 counter;
    s_xyz angle;
    f32 velocity_y;
    f32 _38;
    f32 acceleration_y;
    s16 _40;
    u16 flags;
    int delay_timer;
} aSG_single_draw_c;

struct ac_shop_goods_s {
    ACTOR actor_class;
    int picture_count;
    int bx;
    int bz;
    f32 bx_pos;
    f32 bz_pos;
    s16 mode;
    s16 _18A;
    aSG_single_draw_c single_draw[aSG_SINGLE_DRAW_NUM];
};

extern ACTOR_PROFILE Shop_Goods_Profile;

#ifdef __cplusplus
}
#endif

#endif
