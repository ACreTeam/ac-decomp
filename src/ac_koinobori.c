#include "ac_koinobori.h"

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
  #include "assets/aKOI_obj_e_koinobori_a_pal.inc"
};
FORCESTRIP static u16 __hack_pal1[] = {
  #include "assets/obj_e_koinobori_b_pal.inc"
};
#endif
#endif

enum {
  aKOI_ACTION_WAIT,
};

static void aKOI_actor_ct(ACTOR* actor, GAME* game);
static void aKOI_actor_dt(ACTOR* actor, GAME* game);
static void aKOI_actor_init(ACTOR* actor, GAME* game);
static void aKOI_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Koinobori_Profile = {
  mAc_PROFILE_KOINOBORI,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  KOINOBORI_WINDSOCK,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(KOINOBORI_ACTOR),
  &aKOI_actor_ct,
  &aKOI_actor_dt,
  &aKOI_actor_init,
  &aKOI_actor_draw,
  NULL
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_koinobori;
extern Vtx obj_e_koinobori_shadow_v[];
extern Gfx obj_e_koinobori_shadowT_model[];
extern cKF_Animation_R_c cKF_ba_r_obj_e_koinobori;

u8 aKOI_shadow_vtx_fix_flg_table[8] = {
    1, 0, 0, 1,
    1, 0, 0, 1
};

bIT_ShadowData_c aKOI_shadow_data = {
    8,
    aKOI_shadow_vtx_fix_flg_table,
    60.0f,
    obj_e_koinobori_shadow_v,
    obj_e_koinobori_shadowT_model,
};

static void aKOI_setup_action(KOINOBORI_ACTOR* actor, int action);

static void aKOI_actor_ct(ACTOR* actor, GAME* game) {
    KOINOBORI_ACTOR* koinobori = (KOINOBORI_ACTOR*)actor;

    actor->cull_height = 830.0f;
    actor->cull_radius = 480.0f;

    cKF_SkeletonInfo_R_ct(&koinobori->structure_class.keyframe, &cKF_bs_r_obj_e_koinobori, NULL, koinobori->structure_class.work_area, koinobori->structure_class.morph_area);
    aKOI_setup_action(koinobori, aKOI_ACTION_WAIT);
    cKF_SkeletonInfo_R_play(&koinobori->structure_class.keyframe);
}

static void aKOI_actor_dt(ACTOR* actor, GAME* game) {
    KOINOBORI_ACTOR* koinobori = (KOINOBORI_ACTOR*)actor;
    cKF_SkeletonInfo_R_dt(&koinobori->structure_class.keyframe);
}

#include "../src/ac_koinobori_move.c_inc"

#include "../src/ac_koinobori_draw.c_inc"
