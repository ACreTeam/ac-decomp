#ifndef AC_SHOP_GOODS_H_H
#define AC_SHOP_GOODS_H_H

#include "types.h"
#include "m_actor_type.h"
#include "game_h.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*aSG_SINGLE_DRAW_PROC)(GAME*, mActor_name_t, xyz_t*, f32, s16, int);
typedef int (*aSG_PLAYER_DROP_ENTRY_PROC)(GAME*, mActor_name_t, int, int, int, int);
typedef s16 (*aSG_SINGLE_GET_ANGLE_Y_PROC)(int, int, int);
typedef void (*aSG_SINGLE_SET_ANGLE_Y_PROC)(int, int, int, s16);

typedef struct shop_goods_clip_s {
    aSG_SINGLE_DRAW_PROC single_draw_proc;
    aSG_PLAYER_DROP_ENTRY_PROC player_drop_entry_proc;
    aSG_SINGLE_GET_ANGLE_Y_PROC single_get_angle_y_proc;
    aSG_SINGLE_SET_ANGLE_Y_PROC single_set_angle_y_proc;
} aSG_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
