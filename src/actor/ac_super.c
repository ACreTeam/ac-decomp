#include "ac_super.h"

#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_player_lib.h"
#include "m_demo.h"
#include "ac_intro_demo.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libforest/gbi_extensions.h"

// clang-format off
enum {
    aSPR_ACTION_CLOSE_WAIT,
    aSPR_ACTION_OPEN_WAIT,
    aSPR_ACTION_CLOSE_DOOR,
    aSPR_ACTION_OPEN_DOOR,
    aSPR_ACTION_PL_INTO_WAIT,

    aSPR_ACTION_NUM
};
// clang-format on

static void aSPR_actor_ct(ACTOR* actorx, GAME* game);
static void aSPR_actor_dt(ACTOR* actorx, GAME* game);
static void aSPR_actor_init(ACTOR* actorx, GAME* game);
static void aSPR_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Super_Profile = {
    mAc_PROFILE_SUPER,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SHOP2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SUPER_ACTOR),
    &aSPR_actor_ct,
    &aSPR_actor_dt,
    &aSPR_actor_init,
    &aSPR_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aSPR_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, TRUE, FALSE,
};
// clang-format on

extern Vtx obj_shop3_shadow_v[];
extern Gfx obj_shop3_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aSPR_shadow_data = {
    ARRAY_COUNT(aSPR_shadow_vtx_fix_flg_table),
    aSPR_shadow_vtx_fix_flg_table,
    60.0f,
    obj_shop3_shadow_v,
    obj_shop3_shadowT_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop3;

static void aSPR_set_bgOffset(SUPER_ACTOR* super, int offs);
static void aSPR_setup_action(SUPER_ACTOR* super, int action);
static f32 aSPR_ctrl_light(SUPER_ACTOR* super);

static void aSPR_actor_ct(ACTOR* actorx, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_shop3, &cKF_bs_r_obj_w_shop3 };

    GAME_PLAY* play;
    SUPER_ACTOR* super;
    ACTOR* player;
    int winter;
    int action;
    int x;
    int z;

    super = (SUPER_ACTOR*)actorx;
    play = (GAME_PLAY*)game;
    player = GET_PLAYER_ACTOR_ACTOR(play);

    super->struct_class.season = Common_Get(time.season);
    action = aSPR_ACTION_CLOSE_WAIT;
    winter = super->struct_class.season == mTM_SEASON_WINTER;

    cKF_SkeletonInfo_R_ct(&super->struct_class.keyframe, skl[winter], NULL, super->struct_class.work_area, super->struct_class.morph_area);

    aSPR_set_bgOffset(super, 1);

    actorx->world.position.x = actorx->world.position.x + -mFI_UT_WORLDSIZE_HALF_X_F;
    actorx->world.position.z = actorx->world.position.z + -mFI_UT_WORLDSIZE_HALF_Z_F;
    actorx->talk_distance = 120.0f;
    actorx->cull_width = 600.0f;
    actorx->cull_radius = 600.0f;

    x = (int)(super->struct_class.actor_class.world.position.x - 62.00f);
    z = (int)(super->struct_class.actor_class.world.position.z + 118.57f);
    if ((int)player->world.position.x == x && (int)player->world.position.z == z) {
        action = aSPR_ACTION_OPEN_WAIT;
    }

    aSPR_setup_action(super, action);
    super->struct_class.keyframe_state = cKF_SkeletonInfo_R_play(&super->struct_class.keyframe);
    super->struct_class.keyframe_saved_keyframe = cKF_STATE_STOPPED;
    super->struct_class.arg0_f = aSPR_ctrl_light(super);
}

static void aSPR_actor_dt(ACTOR* actorx, GAME* game) {
    SUPER_ACTOR* super;
    super = (SUPER_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&super->struct_class.keyframe);
    actorx->world.position.x -= -mFI_UT_WORLDSIZE_HALF_X_F;
}

#include "../src/actor/ac_super_move.c_inc"
#include "../src/actor/ac_super_draw.c_inc"
