#include "ac_ev_dokutu.h"

#include "m_common_data.h"

#include "../src/actor/ac_ev_dokutu_talk.c_inc"

static void aEVD_actor_ct(ACTOR* actorx, GAME* game);
static void aEVD_actor_dt(ACTOR* actorx, GAME* game);
static void aEVD_actor_init(ACTOR* actorx, GAME* game);
static void aEVD_actor_save(ACTOR* actorx, GAME* game);
static void aEVD_actor_move(ACTOR* actorx, GAME* game);
static void aEVD_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Dokutu_Profile = {
  mAc_PROFILE_EV_DOKUTU,
  ACTOR_PART_NPC,
  0,
  SP_NPC_EV_DOKUTU,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(EVENT_DOKUTU_ACTOR),
  &aEVD_actor_ct,
  &aEVD_actor_dt,
  &aEVD_actor_init,
  mActor_NONE_PROC1,
  &aEVD_actor_save
};

static aNPC_ct_data_c ct_data = {
  &aEVD_actor_move,
  &aEVD_actor_draw,
  3,
  &aEVD_talk_request,
  &aEVD_talk_init,
  &aEVD_talk_end_chk,
  0
};

static void aEVD_actor_ct(ACTOR* actorx, GAME* game) {
  if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
    (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
  }
}

static void aEVD_actor_save(ACTOR* actorx, GAME* game) {
  mNpc_RenewalSetNpc(actorx);
}

static void aEVD_actor_dt(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
}

static void aEVD_actor_init(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aEVD_actor_move(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->move_proc)(actorx, game);
}

static void aEVD_actor_draw(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}
