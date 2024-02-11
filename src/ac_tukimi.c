#include "ac_tukimi.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"

static void aTUK_actor_ct(ACTOR* actor, GAME* game);
static void aTUK_actor_dt(ACTOR* actor, GAME* game);
static void aTUK_actor_init(ACTOR* actor, GAME* game);
static void aTUK_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Tukimi_Profile = {
  mAc_PROFILE_TUKIMI,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  NEWYEAR_SHRINE0,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(STRUCTURE_ACTOR),
  &aTUK_actor_ct,
  &aTUK_actor_dt,
  &aTUK_actor_init,
  &aTUK_actor_draw,
  NULL
};

u8 aTUK_shadow_vtx_fix_flg_table[8] = {
    TRUE, TRUE, FALSE, FALSE,
    TRUE, FALSE, TRUE, FALSE
};

extern Vtx obj_e_tukimi_l_shadow_v[];
extern Gfx obj_e_tukimi_l_shadow_model[];
static bIT_ShadowData_c aTUK_shadow_data_l = {
  8, aTUK_shadow_vtx_fix_flg_table,
  60.0f,
  obj_e_tukimi_l_shadow_v,
  obj_e_tukimi_l_shadow_model
};

extern Vtx obj_e_tukimi_r_shadow_v[];
extern Gfx obj_e_tukimi_r_shadow_model[];
static bIT_ShadowData_c aTUK_shadow_data_r = {
  8, aTUK_shadow_vtx_fix_flg_table,
  60.0f,
  obj_e_tukimi_r_shadow_v,
  obj_e_tukimi_r_shadow_model
};

extern cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_l;
extern cKF_Skeleton_R_c cKF_bs_r_obj_e_tukimi_r;

static void aTUK_set_bgOffset(STRUCTURE_ACTOR* tukimi, int idx);
static void aTUK_setup_action(ACTOR* actor);

static void aTUK_actor_ct(ACTOR* actor, GAME* game) {
  static cKF_Skeleton_R_c* skl[2] = { &cKF_bs_r_obj_e_tukimi_l, &cKF_bs_r_obj_e_tukimi_r };

  STRUCTURE_ACTOR* tukimi = (STRUCTURE_ACTOR*)actor;

  tukimi->arg0 = actor->npc_id - NEWYEAR_SHRINE0;
  tukimi->structure_pal = tukimi->arg0 + aSTR_PAL_TUKIMI;
  tukimi->structure_type = tukimi->arg0 + aSTR_TYPE_TUKIMI;

  cKF_SkeletonInfo_R_ct(&tukimi->keyframe, skl[tukimi->arg0], NULL, tukimi->work_area, tukimi->morph_area);
  aTUK_set_bgOffset(tukimi, tukimi->arg0 + 1);
  aTUK_setup_action(actor);
  cKF_SkeletonInfo_R_play(&tukimi->keyframe);
}

static void aTUK_actor_dt(ACTOR* actor, GAME* game) {
  STRUCTURE_ACTOR* tukimi = (STRUCTURE_ACTOR*)actor;
  cKF_SkeletonInfo_R_dt(&tukimi->keyframe);
}

#include "../src/ac_tukimi_move.c_inc"

#include "../src/ac_tukimi_draw.c_inc"
