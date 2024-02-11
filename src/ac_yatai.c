#include "ac_yatai.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"

static void aYAT_actor_ct(ACTOR* actor, GAME* game);
static void aYAT_actor_init(ACTOR* actor, GAME* game);
static void aYAT_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Yatai_Profile = {
  mAc_PROFILE_YATAI,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  FIREWORKS_STALL0,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(YATAI_ACTOR),
  &aYAT_actor_ct,
  NONE_ACTOR_PROC,
  &aYAT_actor_init,
  &aYAT_actor_draw,
  NULL
};

static u8 aYAT_shadow_vtx_fix_flg_table[] = {
  TRUE, FALSE, TRUE, FALSE,
  FALSE, FALSE, TRUE, FALSE
};

extern Vtx obj_e_yatai_shadow_l_v[];
extern Gfx obj_e_yatai_shadow_l_modelT[];
static bIT_ShadowData_c aYAT_shadow_data_l = {
  7, aYAT_shadow_vtx_fix_flg_table,
  60.0f, 
  obj_e_yatai_shadow_l_v,
  obj_e_yatai_shadow_l_modelT
};

extern Vtx obj_e_yatai_shadow_r_v[];
extern Gfx obj_e_yatai_shadow_r_modelT[];
static bIT_ShadowData_c aYAT_shadow_data_r = {
  10, aYAT_shadow_vtx_fix_flg_table,
  60.0f, 
  obj_e_yatai_shadow_r_v,
  obj_e_yatai_shadow_r_modelT
};

static void aYAT_set_bgOffset(STRUCTURE_ACTOR* yatai, int idx);

static void aYAT_actor_ct(ACTOR* actor, GAME* game)
{
  STRUCTURE_ACTOR* yatai = (STRUCTURE_ACTOR*)actor;

  yatai->arg0 = actor->npc_id - FIREWORKS_STALL0;
  aYAT_set_bgOffset(yatai, yatai->arg0 + 2);
}

 #include "../src/ac_yatai_move.c_inc"

 #include "../src/ac_yatai_draw.c_inc"
