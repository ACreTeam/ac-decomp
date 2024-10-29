#include "ac_ev_gypsy.h"

#include "m_choice.h"
#include "m_common_data.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_play.h"
#include "m_string.h"

enum {
  aEGPS_ACTION_TALK_END_WAIT,
  aEGPS_ACTION_CALL_IN,
  aEGPS_ACTION_DECIDE_RESULT,
  aEGPS_ACTION_DECIDE_RESULT2,

  aEGPS_ACTION_NUM
};

enum {
  aEGPS_STR_TYPE_ADJECTIVE,
  aEGPS_STR_TYPE_NOUN,
  aEGPS_STR_TYPE_VERB,
  aEGPS_STR_TYPE_PLACE,

  aEGPS_STR_TYPE_NUM
};

static void aEGPS_actor_ct(ACTOR*, GAME*);
static void aEGPS_actor_dt(ACTOR*, GAME*);
static void aEGPS_actor_move(ACTOR*, GAME*);
static void aEGPS_actor_draw(ACTOR*, GAME*);
static void aEGPS_actor_save(ACTOR*, GAME*);
static void aEGPS_actor_init(ACTOR*, GAME*);

ACTOR_PROFILE Ev_Gypsy_Profile = {
  mAc_PROFILE_EV_GYPSY,
  ACTOR_PART_NPC,
  ACTOR_STATE_NONE,
  SP_NPC_GYPSY,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(EV_GYPSY_ACTOR),
  &aEGPS_actor_ct,
  &aEGPS_actor_dt,
  &aEGPS_actor_init,
  mActor_NONE_PROC1,
  &aEGPS_actor_save
};

static void aEGPS_talk_request(ACTOR* actorx, GAME* game);
static int aEGPS_talk_init(ACTOR* actorx, GAME* game);
static int aEGPS_talk_end_chk(ACTOR* actorx, GAME* game);
static void aEGPS_setupAction(EV_GYPSY_ACTOR* gypsy, GAME_PLAY* play, int action);

static void aEGPS_actor_ct(ACTOR* actorx, GAME* game) {
  static aNPC_ct_data_c ct_data = {
    &aEGPS_actor_move,
    &aEGPS_actor_draw,
    2,
    &aEGPS_talk_request,
    &aEGPS_talk_init,
    &aEGPS_talk_end_chk,
    0
  };

  EV_GYPSY_ACTOR* gypsy = (EV_GYPSY_ACTOR*)actorx;

  if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
    (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
    actorx->talk_distance = 80.0f;
    actorx->status_data.weight = 255;
    actorx->world.position.x += 20.0f;
    gypsy->setup_talk_proc = &aEGPS_setupAction;
  }
}

static void aEGPS_actor_save(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aEGPS_actor_dt(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
  mEv_actor_dying_message(mEv_EVENT_GYPSY, actorx);
}

static void aEGPS_actor_init(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aEGPS_actor_draw(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

#include "../src/actor/ac_ev_gypsy_move.c_inc"
