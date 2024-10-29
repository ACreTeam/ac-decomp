#include "ac_shrine.h"

#include "m_msg.h"
#include "m_play.h"
#include "sys_matrix.h"

static void aSHR_actor_ct(ACTOR* actorx, GAME* game);
static void aSHR_actor_dt(ACTOR* actorx, GAME* game);
static void aSHR_actor_init(ACTOR* actorx, GAME* game);
static void aSHR_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Shrine_Profile = {
  mAc_PROFILE_SHRINE,
  ACTOR_PART_ITEM,
  ACTOR_STATE_NONE,
  WISHING_WELL,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(SHRINE_ACTOR),
  &aSHR_actor_ct,
  &aSHR_actor_dt,
  &aSHR_actor_init,
  &aSHR_actor_draw,
  NULL
};

static aSHR_Present_c aSHR_present;
static aSHR_Clip_c aSHR_clip;

enum {
  aSHR_ACTION_WAIT,
  aSHR_ACTION_TALK,
  aSHR_ACTION_TALK_GOMEN,
  aSHR_ACTION_MAKE_HEM,
  aSHR_ACTION_TALK_END,

  aSHR_ACTION_NUM
};

enum {
  aSHR_LEAF_TYPE_SUMMER,
  aSHR_LEAF_TYPE_WINTER,
  aSHR_LEAF_TYPE_CHRISTMAS,
  aSHR_LEAF_TYPE_CHERRY,
  
  aSHR_LEAF_TYPE_NUM
};

static u8 aSHR_shadow_vtx_fix_flg_table[16] = {
  TRUE, FALSE, FALSE, TRUE,
  TRUE, TRUE, FALSE, FALSE,
  TRUE, TRUE, FALSE, FALSE,
  TRUE, TRUE, FALSE, FALSE
};

extern Vtx obj_shrine_shadow_v[];
extern Gfx obj_shrine_shadow_model[];

static bIT_ShadowData_c aSHR_shadow_data = {
  16,
  aSHR_shadow_vtx_fix_flg_table,
  60.0f,
  obj_shrine_shadow_v,
  obj_shrine_shadow_model
};

static void aSHR_setup_action(SHRINE_ACTOR*, GAME_PLAY*, int);
static void aSHR_set_bgOffset(ACTOR*, int);
static void aSHR_Present_ct(aSHR_Present_c*);
static int aSHR_ctrl_light();
static void aSHR_init_clip_area();
static void aSHR_free_clip_area();

static int aSHR_getLeaftype(int winter) {
  if (Common_Get(time).term_idx == mTM_TERM_15) {
    return aSHR_LEAF_TYPE_CHRISTMAS;
  }

  if (Common_Get(time).term_idx == mTM_TERM_16) {
    return aSHR_LEAF_TYPE_CHRISTMAS;
  }

  if (Common_Get(time).term_idx == 4) {
    return aSHR_LEAF_TYPE_CHERRY;
  }

  return winter;
}

static void aSHR_actor_ct(ACTOR* actorx, GAME* game) {
  SHRINE_ACTOR* shrine = (SHRINE_ACTOR*)actorx;
  GAME_PLAY* play = (GAME_PLAY*)game;
  int winter;

  shrine->structure_class.season = Common_Get(time).season;
  winter = shrine->structure_class.season == mTM_SEASON_WINTER;

  aSHR_init_clip_area();
  aSHR_Present_ct(&aSHR_present);
  aSHR_set_bgOffset(actorx, 1);
  shrine->structure_class.arg2 = mEv_check_status(mEv_EVENT_NEW_YEARS_DAY, mEv_STATUS_ACTIVE);
  shrine->structure_class.arg1 = aSHR_getLeaftype(winter);
  actorx->world.position.x = actorx->world.position.x + 20.0f;
  actorx->world.position.z = actorx->world.position.z - 19.0f;
  actorx->talk_distance = 100.0f;
  aSHR_setup_action(shrine, play, aSHR_ACTION_WAIT);
  actorx->cull_radius = 900.0f;
  actorx->cull_height = 1400.0f;
  shrine->structure_class.arg0_f = aSHR_ctrl_light() ? 1.0f : 0.0f;
}

static void aSHR_actor_dt(ACTOR* actorx, GAME* game) {
  SHRINE_ACTOR* shrine = (SHRINE_ACTOR*)actorx;

  aSHR_free_clip_area();
  cKF_SkeletonInfo_R_dt(&shrine->structure_class.keyframe);
}

#include "../src/actor/ac_shrine_clip.c_inc"
#include "../src/actor/ac_shrine_move.c_inc"
#include "../src/actor/ac_shrine_draw.c_inc"
