#include "ac_my_house.h"

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
    aMHS_ACTION_WAIT,
    aMHS_ACTION_OPEN_DOOR_WAIT,
    aMHS_ACTION_OPEN_DOOR,
    aMHS_ACTION_GOTO_NEXT_SCEEN_WAIT,

    aMHS_ACTION_NUM
};

static void aMHS_actor_ct(ACTOR*, GAME*);
static void aMHS_actor_dt(ACTOR*, GAME*);
static void aMHS_actor_init(ACTOR*, GAME*);
static void aMHS_actor_draw(ACTOR*, GAME*);

static int aMHS_light_ctrl(STRUCTURE_ACTOR* my_house);
static void aMHS_setup_action(STRUCTURE_ACTOR* my_house, int action);
static void aMHS_setup_animation(STRUCTURE_ACTOR* my_house, f32 speed);
static void aMHS_set_bgOffset(ACTOR* actorx, int flag);

ACTOR_PROFILE MyHouse_Profile = {
    mAc_PROFILE_MYHOUSE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    HOUSE0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MY_HOUSE_ACTOR),
    &aMHS_actor_ct,
    &aMHS_actor_dt,
    &aMHS_actor_init,
    &aMHS_actor_draw,
    NULL,
};

static u8 aMHS_lv1_shadowE_vtx_fix_flg_table[] = {
    FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, TRUE,
};

static u8 aMHS_lv1_shadowW_vtx_fix_flg_table[] = {
    TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, FALSE, TRUE, FALSE, FALSE, TRUE, TRUE, FALSE, TRUE, TRUE, FALSE,
};

extern Vtx obj_myhome1_shadowE_v[];
extern Gfx obj_myhome1_shadowET_model[];

static bIT_ShadowData_c aMHS_lv1_shadowE_data = {
    18, aMHS_lv1_shadowE_vtx_fix_flg_table, 60.0f, obj_myhome1_shadowE_v, obj_myhome1_shadowET_model,
};

extern Vtx obj_myhome1_shadowW_v[];
extern Gfx obj_myhome1_shadowWT_model[];

static bIT_ShadowData_c aMHS_lv1_shadowW_data = {
    18, aMHS_lv1_shadowW_vtx_fix_flg_table, 60.0f, obj_myhome1_shadowW_v, obj_myhome1_shadowWT_model,
};

static bIT_ShadowData_c* aMHS_lv1_shadow_data[2] = { &aMHS_lv1_shadowW_data, &aMHS_lv1_shadowE_data };

extern Vtx obj_myhome2_shadowE_v[];
extern Gfx obj_myhome2_shadowET_model[];

static bIT_ShadowData_c aMHS_lv2_shadowE_data = {
    18, aMHS_lv1_shadowE_vtx_fix_flg_table, 60.0f, obj_myhome2_shadowE_v, obj_myhome2_shadowET_model,
};

extern Vtx obj_myhome2_shadowW_v[];
extern Gfx obj_myhome2_shadowWT_model[];

static bIT_ShadowData_c aMHS_lv2_shadowW_data = {
    18, aMHS_lv1_shadowW_vtx_fix_flg_table, 60.0f, obj_myhome2_shadowW_v, obj_myhome2_shadowWT_model,
};

static bIT_ShadowData_c* aMHS_lv2_shadow_data[2] = { &aMHS_lv2_shadowW_data, &aMHS_lv2_shadowE_data };

extern Vtx obj_myhome3_shadowE_v[];
extern Gfx obj_myhome3_shadowET_model[];

static bIT_ShadowData_c aMHS_lv3_shadowE_data = {
    18, aMHS_lv1_shadowE_vtx_fix_flg_table, 60.0f, obj_myhome3_shadowE_v, obj_myhome3_shadowET_model,
};

extern Vtx obj_myhome3_shadowW_v[];
extern Gfx obj_myhome3_shadowWT_model[];

static bIT_ShadowData_c aMHS_lv3_shadowW_data = {
    18, aMHS_lv1_shadowW_vtx_fix_flg_table, 60.0f, obj_myhome3_shadowW_v, obj_myhome3_shadowWT_model,
};

static bIT_ShadowData_c* aMHS_lv3_shadow_data[2] = { &aMHS_lv3_shadowW_data, &aMHS_lv3_shadowE_data };

extern Vtx obj_myhome4_shadowE_v[];
extern Gfx obj_myhome4_shadowET_model[];

static bIT_ShadowData_c aMHS_lv4_shadowE_data = {
    18, aMHS_lv1_shadowE_vtx_fix_flg_table, 60.0f, obj_myhome4_shadowE_v, obj_myhome4_shadowET_model,
};

extern Vtx obj_myhome4_shadowW_v[];
extern Gfx obj_myhome4_shadowWT_model[];

static bIT_ShadowData_c aMHS_lv4_shadowW_data = {
    18, aMHS_lv1_shadowW_vtx_fix_flg_table, 60.0f, obj_myhome4_shadowW_v, obj_myhome4_shadowWT_model,
};

static bIT_ShadowData_c* aMHS_lv4_shadow_data[2] = { &aMHS_lv4_shadowW_data, &aMHS_lv4_shadowE_data };

static f32 aMHS_posX_table[2] = { 20.0f, -20.0f };

static int aMHS_door_closed_flag[mHm_HOMESIZE_NUM - 1];

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome1;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome1;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome2;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome2;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome3;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome3;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_myhome4;
extern cKF_Skeleton_R_c cKF_bs_r_obj_w_myhome4;

static void aMHS_actor_ct(ACTOR* actorx, GAME* game) {
    static cKF_Skeleton_R_c* skl[mHm_HOMESIZE_NUM - 1][2] = {
        { &cKF_bs_r_obj_s_myhome1, &cKF_bs_r_obj_w_myhome1 },
        { &cKF_bs_r_obj_s_myhome2, &cKF_bs_r_obj_w_myhome2 },
        { &cKF_bs_r_obj_s_myhome3, &cKF_bs_r_obj_w_myhome3 },
        { &cKF_bs_r_obj_s_myhome4, &cKF_bs_r_obj_w_myhome4 },
    };

    static s16 angle_table[2] = { DEG2SHORT_ANGLE(90.0f), DEG2SHORT_ANGLE(0.0f) };

    STRUCTURE_ACTOR* my_house = (STRUCTURE_ACTOR*)actorx;
    int house_idx = actorx->npc_id - HOUSE0;
    int side_idx = house_idx & 1;
    int size = Save_Get(homes[house_idx]).size_info.size;
    int season;
    s16 param_2 = 50;

    my_house->season = Common_Get(time.season);
    season = my_house->season == mTM_SEASON_WINTER;

    if (size != mHm_HOMESIZE_UPPER) {
        param_2 = 5 + size;
    }

    cKF_SkeletonInfo_R_ct(&my_house->keyframe, skl[size][season], NULL, my_house->work_area, my_house->morph_area);
    my_house->action = house_idx;
    my_house->arg0 = size;
    my_house->arg2 = param_2;
    my_house->arg1 = Save_Get(homes[house_idx]).outlook_pal;
    my_house->arg1 += aSTR_PAL_MYHOME_A;
    actorx->world.position.x += aMHS_posX_table[side_idx];
    actorx->world.position.z += 20.0f;

    // arg0_f = x pos + 2 * posX_table, arg1_f = z pos + 40.0f
    my_house->arg0_f = actorx->world.position.x;
    my_house->arg0_f += aMHS_posX_table[side_idx];
    my_house->arg1_f = actorx->world.position.z + 20.0f;

    my_house->arg3 = mEv_CheckFirstIntro() != FALSE;

    if (aMHS_light_ctrl(my_house) != FALSE) {
        actorx->world.angle.x = DEG2SHORT_ANGLE(90.0f) - 1; // 0x3FFF
    } else {
        actorx->world.angle.x = DEG2SHORT_ANGLE(0.0f);
    }

    actorx->shape_info.rotation.y = angle_table[side_idx];
    actorx->world.angle.z = DEG2SHORT_ANGLE(0.0f);
    actorx->cull_width = 450.0f;
    actorx->cull_radius = 450.0f;

    if (mPr_CheckFishCompleteTalk(mHS_get_pl_no(house_idx))) {
        actorx->speed = TRUE; // Store fish weathervane bool as... speed?
    }

    if (mPr_CheckInsectCompleteTalk(mHS_get_pl_no(house_idx))) {
        actorx->gravity = TRUE; // Store insect plaque bool as... gravity?
    }

    aMHS_setup_action(my_house, aMHS_ACTION_WAIT);
    aMHS_setup_animation(my_house, 0.0f);
    cKF_SkeletonInfo_R_play(&my_house->keyframe);
    aMHS_set_bgOffset(actorx, 1);
    aMHS_door_closed_flag[my_house->arg0] = TRUE;
}

static void aMHS_actor_dt(ACTOR* actorx, GAME* game) {
    STRUCTURE_ACTOR* my_house = (STRUCTURE_ACTOR*)actorx;
    int house_idx = actorx->npc_id - HOUSE0;

    cKF_SkeletonInfo_R_dt(&my_house->keyframe);
    actorx->world.position.x -= aMHS_posX_table[house_idx & 1];
    actorx->world.position.z -= 20.0f;
}

#include "../src/ac_my_house_move.c_inc"
#include "../src/ac_my_house_draw.c_inc"
