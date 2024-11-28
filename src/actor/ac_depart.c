#include "ac_depart.h"

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
    aDPT_ACTION_CLOSE_WAIT,
    aDPT_ACTION_OPEN_WAIT,
    aDPT_ACTION_CLOSE_DOOR,
    aDPT_ACTION_OPEN_DOOR,
    aDPT_ACTION_PL_INTO_WAIT,

    aDPT_ACTION_NUM
};
// clang-format on

static void aDPT_actor_ct(ACTOR* actorx, GAME* game);
static void aDPT_actor_dt(ACTOR* actorx, GAME* game);
static void aDPT_actor_init(ACTOR* actorx, GAME* game);
static void aDPT_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Depart_Profile = {
    mAc_PROFILE_DEPART,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SHOP3,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(DEPART_ACTOR),
    &aDPT_actor_ct,
    &aDPT_actor_dt,
    &aDPT_actor_init,
    &aDPT_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aDPT_shadow_vtx_fix_flg_table[] = {
    FALSE, TRUE, TRUE, FALSE,
    TRUE, FALSE, TRUE, FALSE,
    FALSE, TRUE, TRUE, FALSE,
};
// clang-format on

extern Vtx obj_shop4_shadow_v[];
extern Gfx obj_shop4_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aDPT_shadow_data = {
    ARRAY_COUNT(aDPT_shadow_vtx_fix_flg_table),
    aDPT_shadow_vtx_fix_flg_table,
    60.0f,
    obj_shop4_shadow_v,
    obj_shop4_shadowT_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop4;

static void aDPT_set_bgOffset(DEPART_ACTOR* depart, int offs);
static void aDPT_setup_action(DEPART_ACTOR* depart, int action);
static f32 aDPT_ctrl_light(DEPART_ACTOR* depart);

static void aDPT_actor_ct(ACTOR* actorx, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_shop4, &cKF_bs_r_obj_w_shop4 };

    GAME_PLAY* play;
    DEPART_ACTOR* depart;
    ACTOR* player;
    int winter;
    int action;
    int x;
    int z;

    depart = (DEPART_ACTOR*)actorx;
    play = (GAME_PLAY*)game;
    player = GET_PLAYER_ACTOR_ACTOR(play);

    depart->struct_class.season = Common_Get(time.season);
    action = aDPT_ACTION_CLOSE_WAIT;
    winter = depart->struct_class.season == mTM_SEASON_WINTER;

    cKF_SkeletonInfo_R_ct(&depart->struct_class.keyframe, skl[winter], NULL, depart->struct_class.work_area, depart->struct_class.morph_area);

    aDPT_set_bgOffset(depart, 1);

    actorx->world.position.x = actorx->world.position.x + -mFI_UT_WORLDSIZE_HALF_X_F;
    actorx->world.position.z = actorx->world.position.z + -mFI_UT_WORLDSIZE_HALF_Z_F;
    actorx->talk_distance = 120.0f;
    actorx->cull_width = 600.0f;
    actorx->cull_radius = 600.0f;

    x = (int)(depart->struct_class.actor_class.world.position.x - 62.00f);
    z = (int)(depart->struct_class.actor_class.world.position.z + 118.57f);
    if ((int)player->world.position.x == x && (int)player->world.position.z == z) {
        action = aDPT_ACTION_OPEN_WAIT;
    }

    aDPT_setup_action(depart, action);
    depart->struct_class.keyframe_state = cKF_SkeletonInfo_R_play(&depart->struct_class.keyframe);
    depart->struct_class.keyframe_saved_keyframe = cKF_STATE_STOPPED;
    depart->struct_class.arg0_f = aDPT_ctrl_light(depart);
}

static void aDPT_actor_dt(ACTOR* actorx, GAME* game) {
    DEPART_ACTOR* depart;
    depart = (DEPART_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&depart->struct_class.keyframe);
    actorx->world.position.x -= -mFI_UT_WORLDSIZE_HALF_X_F;
}

#include "../src/actor/ac_depart_move.c_inc"
#include "../src/actor/ac_depart_draw.c_inc"
