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

typedef int (*bIT_DRAW_BF_PROC)(Gfx**, rgba_t*);
typedef int (*bIT_DRAW_AF_PROC)(Gfx**, rgba_t*);

typedef struct bg_common_s bg_item_common_c;
typedef struct drop_s bg_item_drop_c;
typedef struct hole_s bg_item_hole_c;

typedef void (*bIT_SHADOW_DRAW_PROC)(GAME*, bIT_ShadowData_c*, int);
typedef void (*bIT_SINGLE_DRAW_PROC)(GAME* game, mActor_name_t fg_no, xyz_t* pos, f32 scale_f, bIT_DRAW_BF_PROC draw_bf,
                                     bIT_DRAW_AF_PROC draw_af, rgba_t* col);
typedef int (*bIT_TREE_CUTCOUNT_CHECK_PROC)(GAME* game, int ut_x, int ut_z);
typedef int (*bIT_DIG_HOLE_EFFECT_ENTRY_PROC)(mActor_name_t fg_item, xyz_t* pos, u16 frames, u16 wait_frames);
typedef void (*bIT_BURY_HOLE_EFFECT_ENTRY_PROC)(mActor_name_t fg_item, xyz_t* pos, u16 frames);
typedef int (*bIT_PIT_FALL_PROC)(mActor_name_t pit_fg_item, int ut_x, int ut_z, mActor_name_t fg_item_in_pit);
typedef int (*bIT_PIT_FALL_STOP_PROC)(mActor_name_t pit_fg_item, int ut_x, int ut_z, mActor_name_t fg_item_in_pit);
typedef int (*bIT_PIT_EXIT_PROC)(mActor_name_t pit_fg_item, int ut_x, int ut_z, mActor_name_t fg_item_in_pit);
typedef int (*bIT_RAND_POS_GET_PROC)(xyz_t* pos, const xyz_t* check_pos);
typedef int (*bIT_TEN_COIN_ENTRY_EX_PROC)(xyz_t* pos, s16 angle);
typedef int (*bIT_FRUIT_SET_PROC)(mActor_name_t fg_item, int ut_x, int ut_z, s16 count, int type);
typedef void (*bIT_FLY_ENTRY_PROC)(mActor_name_t fg_item, xyz_t* pos, s16 angle_y);
typedef void (*bIT_ITEM_TREE_FRUIT_DROP_PROC)(mActor_name_t item, int ut_x, int ut_z, xyz_t* pos);
typedef int (*bIT_PLAYER_DROP_ENTRY_PROC)(GAME* game, mActor_name_t fg_item, int ut_x, int ut_z, s16 layer);
typedef int (*bIT_DROP_ENTRY_V1_PROC)(mActor_name_t fg_item, xyz_t* pos, xyz_t* target_pos);
typedef int (*bIT_FADE_ENTRY_PROC)(mActor_name_t fg_name, xyz_t* pos);

typedef struct background_item_clip_s {
    bg_item_common_c* bg_item_common_p;
    bIT_SHADOW_DRAW_PROC draw_shadow_proc;
    bIT_SINGLE_DRAW_PROC single_draw_proc;
    bIT_TREE_CUTCOUNT_CHECK_PROC tree_cutcount_check_proc;
    bIT_DIG_HOLE_EFFECT_ENTRY_PROC dig_hole_effect_entry_proc;
    bIT_BURY_HOLE_EFFECT_ENTRY_PROC bury_hole_effect_entry_proc;
    bIT_PIT_FALL_PROC pit_fall_proc;
    bIT_PIT_FALL_STOP_PROC pit_fall_stop_proc;
    bIT_PIT_EXIT_PROC pit_exit_proc;
    void* _24;
    bIT_RAND_POS_GET_PROC rand_pos_get_proc;
    bIT_TEN_COIN_ENTRY_EX_PROC ten_coin_entry_ex_proc;
    bIT_FRUIT_SET_PROC fruit_set_proc;
    bIT_FLY_ENTRY_PROC fly_entry_proc;
    bIT_ITEM_TREE_FRUIT_DROP_PROC item_tree_fruit_drop_proc;
    bIT_PLAYER_DROP_ENTRY_PROC player_drop_entry_proc;
    bIT_DROP_ENTRY_V1_PROC drop_entry_v1_proc;
    void* _44;
    void* _48;
    ACTOR* bg_item_actorx;
    bIT_FADE_ENTRY_PROC fade_entry_proc;
} bIT_Clip_c;

#ifdef __cplusplus
}
#endif

#endif
