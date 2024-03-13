#include "ac_needlework_shop.h"

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

enum {
    aNW_ACTION_WAIT,
    aNW_ACTION_OPEN_DOOR_WAIT,
    aNW_ACTION_OPEN_DOOR,
    aNW_ACTION_OPEN_UNKNOWN,

    aNW_ACTION_NUM
};

static void aNW_actor_ct(ACTOR* actor, GAME* game);
static void aNW_actor_dt(ACTOR* actor, GAME* game);
static void aNW_actor_init(ACTOR* actor, GAME* game);
static void aNW_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Needlework_Shop_Profile = {
    mAc_PROFILE_NEEDLEWORK_SHOP,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    NEEDLEWORK_SHOP,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aNW_actor_ct,
    &aNW_actor_dt,
    &aNW_actor_init,
    &aNW_actor_draw,
    NULL
};
// clang-format on

static u8 aNW_shadow_vtx_fix_flg_table[8] = { TRUE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, FALSE };

extern Vtx obj_s_tailor_shadow_v[];
extern Gfx obj_s_tailor_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aNW_shadow_data = {
    6,
    aNW_shadow_vtx_fix_flg_table,
    60.0f,
    obj_s_tailor_shadow_v,
    obj_s_tailor_shadowT_model
};
// clang-format on

static void aNW_set_bgOffset(STRUCTURE_ACTOR* shop, int idx);
static void aNW_setup_animation(STRUCTURE_ACTOR* shop, f32 speed);
static void aNW_setup_action(STRUCTURE_ACTOR* shop, int action);
static int aNW_ctrl_light(STRUCTURE_ACTOR* shop);

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_tailor;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_tailor;

static void aNW_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_tailor, &cKF_bs_r_obj_w_tailor };

    STRUCTURE_ACTOR* shop;

    shop = (STRUCTURE_ACTOR*)actor;
    shop->season = Common_Get(time.season);
    cKF_SkeletonInfo_R_ct(&shop->keyframe, skl[shop->season == mTM_SEASON_WINTER], NULL, shop->work_area,
                          shop->morph_area);

    aNW_set_bgOffset(shop, 1);

    actor->world.position.x = actor->world.position.x + -20.0f;
    actor->world.position.z = actor->world.position.z + 20.0f;
    actor->cull_height = 800.0f;
    actor->cull_radius = 400.0f;
    actor->cull_width = 450.0f;

    shop->request_type = 0;
    aNW_setup_animation(shop, 0.0f);
    aNW_setup_action(shop, aNW_ACTION_WAIT);

    shop->keyframe_state = cKF_SkeletonInfo_R_play(&shop->keyframe);
    shop->keyframe_saved_keyframe = 1;

    shop->arg0_f = aNW_ctrl_light(shop) != FALSE ? 1.0f : 0.0f;
}

static void aNW_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* shop;

    shop = (STRUCTURE_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&shop->keyframe);
    actor->world.position.x -= -20.0f;
    actor->world.position.z -= 20.0f;
}

#include "../src/ac_needlework_shop_move.c_inc"

#include "../src/ac_needlework_shop_draw.c_inc"
