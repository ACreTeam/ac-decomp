#include "ac_lotus.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"

#ifdef MUST_MATCH
#ifndef __INTELLISENSE__
/* Force assetrip to detect these assets. They're used in a .c_inc file. */
FORCESTRIP static u16 __hack_pal0[] = {
  #include "assets/aLOT_obj_01_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal1[] = {
  #include "assets/obj_02_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal3[] = {
  #include "assets/obj_03_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal4[] = {
  #include "assets/obj_04_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal5[] = {
  #include "assets/obj_05_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal6[] = {
  #include "assets/obj_06_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal7[] = {
  #include "assets/obj_07_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal8[] = {
  #include "assets/obj_08_lotus_pal.inc"
};
FORCESTRIP static u16 __hack_pal9[] = {
  #include "assets/obj_09_lotus_pal.inc"
};
#endif
#endif

enum {
  aLOT_ACTION_WAIT1,
  aLOT_ACTION_WAIT2,
  aLOT_ACTION_SHAKE,
};

static void aLOT_actor_ct(ACTOR* actor, GAME* game);
static void aLOT_actor_dt(ACTOR* actor, GAME* game);
static void aLOT_actor_init(ACTOR* actor, GAME* game);
static void aLOT_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Lotus_Profile = {
  mAc_PROFILE_LOTUS,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  LOTUS,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(LOTUS_ACTOR),
  &aLOT_actor_ct,
  &aLOT_actor_dt,
  &aLOT_actor_init,
  &aLOT_actor_draw,
  NULL
};

static StatusData_c lotus_StatusData = { 0, 0, 0, 0, 0x0A};
static ClObjPipeData_c lotus_CoInfoData = {
    {0x3D, 0x20, ClObj_TYPE_PIPE},  // collision data
    {1},                            // element data
    // Pipe specs
    {
        70, // radius
        6,  // height
        0,  // offset

        {0, 0, 0},  // center
    },
};

ClObjPipe_c pipeinfo;

extern cKF_Skeleton_R_c cKF_bs_r_obj_s_lotus;

static void aLOT_setup_action(LOTUS_ACTOR* lotus, int action);
static int aLOT_getPalNo();

static void aLOT_actor_ct(ACTOR* actor, GAME* game) {
    LOTUS_ACTOR* lotus;
    int pal_no;
    f32 water_height;

    lotus = (LOTUS_ACTOR*)actor;
    water_height = mCoBG_GetWaterHeight_File(actor->world.position, __FILE__, 265);
    cKF_SkeletonInfo_R_ct(&lotus->structure_class.keyframe, &cKF_bs_r_obj_s_lotus, NULL, lotus->structure_class.work_area, lotus->structure_class.morph_area);

    ClObjPipe_ct(game, &pipeinfo);
    ClObjPipe_set5(game, &pipeinfo,actor, &lotus_CoInfoData);
    CollisionCheck_Status_set3(&actor->status_data, &lotus_StatusData);

    actor->world.position.y = water_height;
    pal_no = aLOT_getPalNo();
    lotus->structure_class.arg0 = pal_no;
    aLOT_setup_action(lotus, aLOT_ACTION_WAIT1);
    cKF_SkeletonInfo_R_play(&lotus->structure_class.keyframe);
}

static void aLOT_actor_dt(ACTOR* actor, GAME* game) {
    LOTUS_ACTOR* lotus = (LOTUS_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&lotus->structure_class.keyframe);
}

#include "../src/ac_lotus_move.c_inc"

#include "../src/ac_lotus_draw.c_inc"
