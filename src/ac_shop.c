#include "ac_shop.h"

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
    aSHOP_ACTION_CLOSE_WAIT,
    aSHOP_ACTION_OPEN_WAIT,
    aSHOP_ACTION_CLOSE_DOOR,
    aSHOP_ACTION_OPEN_DOOR,
    aSHOP_ACTION_PL_INTO_WAIT,

    aSHOP_ACTION_NUM
};
// clang-format on

static void aSHOP_actor_ct(ACTOR* actor, GAME* game);
static void aSHOP_actor_dt(ACTOR* actor, GAME* game);
static void aSHOP_actor_init(ACTOR* actor, GAME* game);
static void aSHOP_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Shop_Profile = {
    mAc_PROFILE_SHOP,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SHOP0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aSHOP_actor_ct,
    &aSHOP_actor_dt,
    &aSHOP_actor_init,
    &aSHOP_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aSHOP_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, TRUE, FALSE,
    TRUE, FALSE, FALSE, TRUE
};
// clang-format on

extern Vtx obj_shop1_shadow_v[];
extern Gfx obj_shop1_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aSHOP_shadow_data = {
    8,
    aSHOP_shadow_vtx_fix_flg_table,
    60.0f,
    obj_shop1_shadow_v,
    obj_shop1_shadowT_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_shop1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_shop1;

static void aSHOP_set_bgOffset(STRUCTURE_ACTOR* shop, int offs);
static void aSHOP_setup_action(STRUCTURE_ACTOR* shop, int action);
static int aSHOP_ctrl_light(STRUCTURE_ACTOR* shop);

static void aSHOP_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_shop1, &cKF_bs_r_obj_w_shop1 };

    STRUCTURE_ACTOR* shop;
    GAME_PLAY* play;
    PLAYER_ACTOR* player;
    int winter;
    int action;
    int x;
    int z;

    shop = (STRUCTURE_ACTOR*)actor;
    play = (GAME_PLAY*)game;
    player = GET_PLAYER_ACTOR(play);

    shop->season = Common_Get(time.season);
    action = aSHOP_ACTION_OPEN_WAIT;
    winter = shop->season == mTM_SEASON_WINTER;

    cKF_SkeletonInfo_R_ct(&shop->keyframe, skl[winter], NULL, shop->work_area, shop->morph_area);

    aSHOP_set_bgOffset(shop, 1);

    actor->world.position.x = actor->world.position.x + -20.0f;
    actor->world.position.z = actor->world.position.z + 20.0f;
    actor->talk_distance = 80.0f;
    actor->cull_width = 550.0f;
    actor->cull_radius = 550.0f;

    if (mSP_ShopOpen() != 2) {
        action = aSHOP_ACTION_CLOSE_WAIT;
    }

    x = (int)(shop->actor_class.world.position.x - 68.29f);
    z = (int)(shop->actor_class.world.position.z + 68.29f);
    if ((int)player->actor_class.world.position.x == x && (int)player->actor_class.world.position.z == z) {
        action = aSHOP_ACTION_OPEN_WAIT;
    }

    aSHOP_setup_action(shop, action);

    if (aSHOP_ctrl_light(shop)) {
        shop->arg0 = DEG2SHORT_ANGLE(90.0f) - 1;
    } else {
        shop->arg0 = DEG2SHORT_ANGLE(0.0f);
    }

    shop->keyframe_state = cKF_SkeletonInfo_R_play(&shop->keyframe);
    shop->keyframe_saved_keyframe = 1;
}

static void aSHOP_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* shop;
    shop = (STRUCTURE_ACTOR*)actor;

    cKF_SkeletonInfo_R_dt(&shop->keyframe);
    actor->world.position.x = actor->world.position.x - -20.0f;
    actor->world.position.z = actor->world.position.z - 20.0f;
}

#include "../src/ac_shop_move.c_inc"

#include "../src/ac_shop_draw.c_inc"
