#include "ac_train1.h"
#include "ac_train0.h"

#include "graph.h"
#include "m_name_table.h"
#include "m_rcp.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "sys_math3d.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_event.h"


static void aTR1_actor_ct(ACTOR* actor, GAME* game);
static void aTR1_actor_dt(ACTOR* actor, GAME* game);
static void aTR1_actor_move(ACTOR* actor, GAME* game);
static void aTR1_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Train1_Profile = {
  mAc_PROFILE_TRAIN1,
  ACTOR_PART_ITEM,
  ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | 1 << 11 | ACTOR_STATE_NO_MOVE_WHILE_CULLED, //figure out flag 0x800
  TRAIN1,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(TRAIN1_ACTOR),
  &aTR1_actor_ct,
  &aTR1_actor_dt,
  &aTR1_actor_move,
  &aTR1_actor_draw,
  NULL
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_train1_3;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_3_open;
extern cKF_Animation_R_c cKF_ba_r_obj_train1_3_close;


static void aTR1_setupAction(ACTOR*, int);

static void aTR1_actor_ct(ACTOR* actor, GAME* game){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;
    
    cKF_SkeletonInfo_R_ct(&train1->keyframe, &cKF_bs_r_obj_train1_3, NULL, train1->work, train1->morph);
    aTR1_setupAction((ACTOR*)train1, 5);
    train1->anim_state = cKF_SkeletonInfo_R_play(&train1->keyframe);
    actor->world.angle.y = 0x4000;
    train1->tr_speed = 1.0f;
}


static void aTR1_actor_dt(ACTOR* actor, GAME* game){
    TRAIN1_ACTOR* train1 = (TRAIN1_ACTOR*)actor;

    xyz_t tr_home_pos;

    tr_home_pos = train1->actor_class.home.position;

    mFI_SetFG_common(EMPTY_NO, tr_home_pos, FALSE);
    cKF_SkeletonInfo_R_dt(&train1->keyframe);
}

#include "../src/ac_train1_move.c_inc"

#include "../src/ac_train1_draw.c_inc"
