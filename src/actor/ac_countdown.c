#include "ac_countdown.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

enum {
    aCOU_ACT_WAIT,
    aCOU_ACT_MOVE,
    aCOU_ACT_HAPPY_NEW_YEAR,

    aCOU_ACT_NUM
};

static void aCOU_actor_ct(ACTOR* actorx, GAME* game);
static void aCOU_actor_dt(ACTOR* actorx, GAME* game);
static void aCOU_actor_draw(ACTOR* actorx, GAME* game);
static void aCOU_actor_init(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Count_Profile = {
    // clang-format off
    mAc_PROFILE_COUNT,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    NEWYEAR_COUNTDOWN0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(COUNT_ACTOR),
    aCOU_actor_ct,
    aCOU_actor_dt,
    aCOU_actor_init,
    aCOU_actor_draw,
    NULL,
    // clang-format on
};

// @ 8056df2c
static u8 aCOU_shadow_vtx_fix_flg_table[4] = { 0x00, 0x01, 0x01, 0x00 };

extern Vtx obj_e_count_shadow_v[];
extern Gfx obj_e_count_shadow_model[];

static bIT_ShadowData_c aCOU_shadow_data = { ARRAY_COUNT(aCOU_shadow_vtx_fix_flg_table), aCOU_shadow_vtx_fix_flg_table,
                                             60.0f, obj_e_count_shadow_v, obj_e_count_shadow_model };

static aCOU_Clip_c aCOU_clip;

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_count01;
extern cKF_Animation_R_c cKF_ba_r_obj_e_count01;

static void aCOU_set_bgOffset(ACTOR* actorx, int idx);
static void aCOU_init_clip_area(void);
static void aCOU_free_clip_area(void);
static void aCOU_setup_action(COUNT_ACTOR* actor, int action);

static void aCOU_actor_ct(ACTOR* actorx, GAME* game) {
    COUNT_ACTOR* actor = (COUNT_ACTOR*)actorx;

    cKF_SkeletonInfo_R_ct(&actor->structure_class.keyframe, &cKF_bs_r_obj_e_count01, NULL,
                          actor->structure_class.work_area, actor->structure_class.morph_area);
    aCOU_set_bgOffset(actorx, 1);
    aCOU_setup_action(actor, aCOU_ACT_WAIT);
    cKF_SkeletonInfo_R_play(&actor->structure_class.keyframe);
    actor->structure_class.arg1 = 0;
    actor->structure_class.arg2 = 0;
    aCOU_init_clip_area();
}

static void aCOU_actor_dt(ACTOR* actorx, GAME* game) {
    COUNT_ACTOR* actor = (COUNT_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&actor->structure_class.keyframe);
    aCOU_free_clip_area();
}

#include "../src/actor/ac_countdown_clip.c_inc"
#include "../src/actor/ac_countdown_move.c_inc"
#include "../src/actor/ac_countdown_draw.c_inc"
