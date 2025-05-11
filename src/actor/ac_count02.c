#include "ac_count02.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_rcp.h"
#include "sys_matrix.h"

enum {
    aCOU_ACT_INIT,
    aCOU_ACT_WAIT,

    aCOU_ACT_NUM
};

static void aCOU_actor_ct(ACTOR* actorx, GAME* game);
static void aCOU_actor_draw(ACTOR* actorx, GAME* game);
static void aCOU_actor_dt(ACTOR* actorx, GAME* game);
static void aCOU_actor_init(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Count02_Profile = {
    // clang-format off
    mAc_PROFILE_COUNT02,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    NEWYEAR_COUNTDOWN1,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    aCOU_actor_ct,
    aCOU_actor_dt,
    aCOU_actor_init,
    aCOU_actor_draw,
    NULL,
    // clang-format on
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_count02_cl;
extern cKF_Animation_R_c cKF_ba_r_obj_e_count02_cl;

static void aCOU_setup_action(STRUCTURE_ACTOR* actor, int action);

static void aCOU_actor_ct(ACTOR* actorx, GAME* game) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    STRUCTURE_ACTOR* actor = (STRUCTURE_ACTOR*)actorx;

    cKF_SkeletonInfo_R_ct(&actor->keyframe, &cKF_bs_r_obj_e_count02_cl, NULL,
                          actor->work_area, actor->morph_area);
    
    if (rtc_time->month == lbRTC_DECEMBER && rtc_time->day == 31 && rtc_time->hour == 23 && rtc_time->min == 59) {
        actor->arg2_f = 1.0f;
    } else {
        actor->arg2_f = 0.0f;
    }

    aCOU_setup_action(actor, aCOU_ACT_INIT);
    actorx->world.position.z += mFI_UT_WORLDSIZE_Z_F;
    cKF_SkeletonInfo_R_play(&actor->keyframe);
}

static void aCOU_actor_dt(ACTOR* actorx, GAME* game) {
    STRUCTURE_ACTOR* actor = (STRUCTURE_ACTOR*)actorx;

    cKF_SkeletonInfo_R_dt(&actor->keyframe);
}

#include "../src/actor/ac_count02_move.c_inc"
#include "../src/actor/ac_count02_draw.c_inc"
