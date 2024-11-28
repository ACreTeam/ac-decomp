#include "ac_conveni.h"

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
    aCNV_ACTION_CLOSE_WAIT,
    aCNV_ACTION_OPEN_WAIT,
    aCNV_ACTION_CLOSE_DOOR,
    aCNV_ACTION_OPEN_DOOR,
    aCNV_ACTION_PL_INTO_WAIT,

    aCNV_ACTION_NUM
};
// clang-format on

static void aCNV_actor_ct(ACTOR* actorx, GAME* game);
static void aCNV_actor_dt(ACTOR* actorx, GAME* game);
static void aCNV_actor_init(ACTOR* actorx, GAME* game);
static void aCNV_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Conveni_Profile = {
    mAc_PROFILE_CONVENI,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SHOP1,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(CONVENI_ACTOR),
    &aCNV_actor_ct,
    &aCNV_actor_dt,
    &aCNV_actor_init,
    &aCNV_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aCNV_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, TRUE, FALSE,
};
// clang-format on

extern Vtx obj_shop2_shadow_v[];
extern Gfx obj_shop2_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aCNV_shadow_data = {
    ARRAY_COUNT(aCNV_shadow_vtx_fix_flg_table),
    aCNV_shadow_vtx_fix_flg_table,
    60.0f,
    obj_shop2_shadow_v,
    obj_shop2_shadowT_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop2;

static void aCNV_set_bgOffset(CONVENI_ACTOR* conveni, int offs);
static void aCNV_setup_action(CONVENI_ACTOR* conveni, int action);
static f32 aCNV_ctrl_light(CONVENI_ACTOR* conveni);

static void aCNV_actor_ct(ACTOR* actorx, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_shop2, &cKF_bs_r_obj_w_shop2 };

    GAME_PLAY* play;
    CONVENI_ACTOR* conveni;
    ACTOR* player;
    int winter;
    int action;
    int x;
    int z;

    conveni = (CONVENI_ACTOR*)actorx;
    play = (GAME_PLAY*)game;
    player = GET_PLAYER_ACTOR_ACTOR(play);

    conveni->struct_class.season = Common_Get(time.season);
    action = aCNV_ACTION_CLOSE_WAIT;
    winter = conveni->struct_class.season == mTM_SEASON_WINTER;

    cKF_SkeletonInfo_R_ct(&conveni->struct_class.keyframe, skl[winter], NULL, conveni->struct_class.work_area, conveni->struct_class.morph_area);

    aCNV_set_bgOffset(conveni, 1);

    actorx->world.position.x = actorx->world.position.x + -mFI_UT_WORLDSIZE_X_F;
    actorx->talk_distance = 100.0f;
    actorx->cull_width = 550.0f;
    actorx->cull_radius = 550.0f;

    x = (int)(conveni->struct_class.actor_class.world.position.x - 42.00f);
    z = (int)(conveni->struct_class.actor_class.world.position.z + 98.57f);
    if ((int)player->world.position.x == x && (int)player->world.position.z == z) {
        action = aCNV_ACTION_OPEN_WAIT;
    }

    aCNV_setup_action(conveni, action);
    conveni->struct_class.keyframe_state = cKF_SkeletonInfo_R_play(&conveni->struct_class.keyframe);
    conveni->struct_class.keyframe_saved_keyframe = cKF_STATE_STOPPED;
    conveni->struct_class.arg0_f = aCNV_ctrl_light(conveni);
}

static void aCNV_actor_dt(ACTOR* actorx, GAME* game) {
    CONVENI_ACTOR* conveni;
    conveni = (CONVENI_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&conveni->struct_class.keyframe);
    actorx->world.position.x -= -mFI_UT_WORLDSIZE_X_F;
}

#include "../src/actor/ac_conveni_move.c_inc"
#include "../src/actor/ac_conveni_draw.c_inc"
