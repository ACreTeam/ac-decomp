#include "ac_post_office.h"

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
    aPOFF_ACTION_WAIT,
    aPOFF_ACTION_OPEN_DOOR_WAIT,
    aPOFF_ACTION_OPEN_DOOR,
    aPOFF_ACTION_OPEN_UNKNOWN,

    aPOFF_ACTION_NUM
};

static void aPOFF_actor_ct(ACTOR* actor, GAME* game);
static void aPOFF_actor_dt(ACTOR* actor, GAME* game);
static void aPOFF_actor_init(ACTOR* actor, GAME* game);
static void aPOFF_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Post_Office_Profile = {
    mAc_PROFILE_POST_OFFICE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    POST_OFFICE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aPOFF_actor_ct,
    &aPOFF_actor_dt,
    &aPOFF_actor_init,
    &aPOFF_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aPOFF_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, FALSE, TRUE, 
    FALSE, TRUE, FALSE, TRUE,
    TRUE, FALSE, TRUE,  FALSE,
    FALSE, TRUE, FALSE, FALSE
};
// clang-format on

extern Vtx obj_s_yubinkyoku_shadow_v[];
extern Gfx obj_s_yubinkyoku_shadow_2_model[];

// clang-format off
static bIT_ShadowData_c aPOFF_shadow_data = {
    14,
    aPOFF_shadow_vtx_fix_flg_table,
    60.0f,
    obj_s_yubinkyoku_shadow_v,
    obj_s_yubinkyoku_shadow_2_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_yubinkyoku;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_yubinkyoku;

static void aPOFF_set_bgOffset(STRUCTURE_ACTOR* office, int idx);
static void aPOFF_setup_animation(STRUCTURE_ACTOR* office, f32 speed);
static void aPOFF_setup_action(STRUCTURE_ACTOR* office, int action);
static int aPOFF_ctrl_light(STRUCTURE_ACTOR* office);

static void aPOFF_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_yubinkyoku, &cKF_bs_r_obj_w_yubinkyoku };

    STRUCTURE_ACTOR* office;

    office = (STRUCTURE_ACTOR*)actor;
    office->season = Common_Get(time.season);
    cKF_SkeletonInfo_R_ct(&office->keyframe, skl[office->season == mTM_SEASON_WINTER], NULL, office->work_area,
                          office->morph_area);

    aPOFF_set_bgOffset(office, 1);

    actor->world.position.x = actor->world.position.x + -20.0f;
    actor->world.position.z = actor->world.position.z + 20.0f;
    actor->cull_width = 500.0f;
    actor->cull_distance = 500.0f;

    office->request_type = 0;
    aPOFF_setup_animation(office, 0.0f);
    aPOFF_setup_action(office, aPOFF_ACTION_WAIT);

    office->keyframe_state = cKF_SkeletonInfo_R_play(&office->keyframe);
    office->keyframe_saved_keyframe = 1;

    if (aPOFF_ctrl_light(office)) {
        office->action = DEG2SHORT_ANGLE(90.0f) - 1; // 0x3FFF
    } else {
        office->action = DEG2SHORT_ANGLE(0.0f);
    }
}

static void aPOFF_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* office;

    office = (STRUCTURE_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&office->keyframe);
    actor->world.position.x -= -20.0f;
    actor->world.position.z -= 20.0f;
}

#include "../src/ac_post_office_move.c_inc"

#include "../src/ac_post_office_draw.c_inc"
