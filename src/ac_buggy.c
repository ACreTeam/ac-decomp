#include "ac_buggy.h"

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
    aBGY_ACTION_WAIT,
    aBGY_ACTION_OPEN_WAIT,
    aBGY_ACTION_CLOSE_DOOR,
    aBGY_ACTION_OPEN_DOOR,

    aBGY_ACTION_NUM
};
// clang-format on

static void aBGY_actor_ct(ACTOR* actor, GAME* game);
static void aBGY_actor_dt(ACTOR* actor, GAME* game);
static void aBGY_actor_init(ACTOR* actor, GAME* game);
static void aBGY_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Buggy_Profile = {
    mAc_PROFILE_BUGGY,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    FORTUNE_TENT,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aBGY_actor_ct,
    &aBGY_actor_dt,
    &aBGY_actor_init,
    &aBGY_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aBGY_shadow_vtx_fix_flg_table[] = {
    TRUE, TRUE, FALSE, TRUE,
    FALSE, FALSE, TRUE, FALSE,
    FALSE, TRUE, TRUE, FALSE,
    TRUE, FALSE, FALSE, FALSE
};
// clang-format on

extern Vtx obj_uranai_shadow_v[];
extern Gfx obj_uranai_shadowT_model[];

// clang-format off
static bIT_ShadowData_c aBGY_shadow_data = {
    14,
    aBGY_shadow_vtx_fix_flg_table,
    60.0f,
    obj_uranai_shadow_v,
    obj_uranai_shadowT_model
};
// clang-format on

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_uranai;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_uranai;

static void change_FGUnit(STRUCTURE_ACTOR* buggy, int type);
static void aBGY_set_bgOffset(STRUCTURE_ACTOR* buggy, int offs);
static void aBGY_setup_action(STRUCTURE_ACTOR* buggy, int action);
static int aBGY_ctrl_light(STRUCTURE_ACTOR* buggy);

static void aBGY_actor_ct(ACTOR* actor, GAME* game) {
    static cKF_Skeleton_R_c* skl[] = { &cKF_bs_r_obj_s_uranai, &cKF_bs_r_obj_w_uranai };

    STRUCTURE_ACTOR* buggy;
    GAME_PLAY* play;
    PLAYER_ACTOR* player;
    int winter;
    int action;
    int x;
    int z;
    f32 speed;

    buggy = (STRUCTURE_ACTOR*)actor;
    play = (GAME_PLAY*)game;
    player = get_player_actor_withoutCheck(play);

    buggy->season = Common_Get(time.season);
    winter = buggy->season == mTM_SEASON_WINTER;

    cKF_SkeletonInfo_R_ct(&buggy->keyframe, skl[winter], NULL, buggy->work_area, buggy->morph_area);

    aBGY_set_bgOffset(buggy, 1);
    change_FGUnit(buggy, 1);

    x = (int)buggy->actor_class.world.position.x;
    z = (int)(buggy->actor_class.world.position.z + 100.0f);
    
    action = aBGY_ACTION_WAIT;

    if ((int)player->actor_class.world.position.x == x && (int)player->actor_class.world.position.z == z) {
        action = aBGY_ACTION_OPEN_WAIT;
    }

    aBGY_setup_action(buggy, action);

    buggy->actor_class.talk_distance = 80.0;

    cKF_SkeletonInfo_R_play(&buggy->keyframe);

    buggy->arg0_f = aBGY_ctrl_light(buggy) ? 1.0f : 0.0f;
}

static void aBGY_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* buggy;
    buggy = (STRUCTURE_ACTOR*)actor;

    change_FGUnit(buggy, 0);
    cKF_SkeletonInfo_R_dt(&buggy->keyframe);
}

#include "../src/ac_buggy_move.c_inc"

#include "../src/ac_buggy_draw.c_inc"
