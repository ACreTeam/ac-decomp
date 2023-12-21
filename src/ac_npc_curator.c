#include "ac_npc_curator.h"

#include "m_common_data.h"
#include "m_item_name.h"
#include "m_msg.h"

enum {
  aCR_ACTION_WAIT,
  aCR_ACTION_SLEEP_WAIT,
  aCR_ACTION_SLEEP,

  aCR_ACTION_NUM
};

enum {
  aCR_TALK_END_WAIT,
  aCR_TALK_AFTER_TALK_START_WAIT,
  aCR_TALK_CHK_REQUEST,
  aCR_TALK_CHK_DECIDE_TO_DONATE,
  aCR_TALK_CHK_DECIDE_TO_DONATE2,
  aCR_TALK_MENU_OPEN_WAIT,
  aCR_TALK_MSG_WIN_CLOSE_WAIT,
  aCR_TALK_MENU_CLOSE_WAIT,
  aCR_TALK_GET_DEMO_START_WAIT,
  aCR_TALK_GET_DEMO_END_WAIT,
  aCR_TALK_MSG_WIN_OPEN_WAIT,
  aCR_TALK_RETURN_DEMO_START_WAIT,
  aCR_TALK_RETURN_DEMO_START_WAIT2,
  aCR_TALK_RETURN_DEMO_END_WAIT,
  aCR_TALK_RETURN_DEMO_END_WAIT2,
  aCR_TALK_CHK_CONTINUE_TO_DONATE,
  aCR_TALK_CHK_CONTINUE_TO_DONATE2,
  aCR_TALK_CHK_CONTINUE_TO_DONATE3,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT2,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT3,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT4,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT5,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT6,
  aCR_TALK_PUTAWAY_DEMO_START_WAIT5_2,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT2,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT3,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT4,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT5,
  aCR_TALK_PUTAWAY_DEMO_END_WAIT6,
  aCR_TALK_AFTER_EXPLAIN_INSECT,
  aCR_TALK_THANKS_FOSSIL_MSG_END_WAIT,
  aCR_TALK_CHK_ALL_COMPLETE,

  aCR_TALK_NUM
};

static void aCR_actor_ct(ACTOR* actorx, GAME* game);
static void aCR_actor_dt(ACTOR* actorx, GAME* game);
static void aCR_actor_move(ACTOR* actorx, GAME* game);
static void aCR_actor_draw(ACTOR* actorx, GAME* game);
static void aCR_actor_init(ACTOR* actorx, GAME* game);
static void aCR_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Npc_Curator_Profile = {
  mAc_PROFILE_NPC_CURATOR,
  ACTOR_PART_NPC,
  ACTOR_STATE_NONE,
  SP_NPC_CURATOR,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(NPC_CURATOR_ACTOR),
  &aCR_actor_ct,
  &aCR_actor_dt,
  &aCR_actor_init,
  mActor_NONE_PROC1,
  &aCR_actor_save
};

static void aCR_talk_request(ACTOR* actorx, GAME* game);
static int aCR_talk_init(ACTOR* actorx, GAME* game);
static int aCR_talk_end_chk(ACTOR* actorx, GAME* game);

static void aCR_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int sched_idx);
static void aCR_setupTalkAction(NPC_CURATOR_ACTOR* curator, GAME_PLAY* play, int talk_act_idx);
static void aCR_setupAction(NPC_CURATOR_ACTOR* curator, GAME_PLAY* play, int action);

static void aCR_actor_ct(ACTOR* actorx, GAME* game) {
  static aNPC_ct_data_c ct_data = {
    &aCR_actor_move,
    &aCR_actor_draw,
    5,
    &aCR_talk_request,
    &aCR_talk_init,
    &aCR_talk_end_chk,
    0
  };

  NPC_CURATOR_ACTOR* curator = (NPC_CURATOR_ACTOR*)actorx;

  if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
    curator->npc_class.schedule.schedule_proc = &aCR_schedule_proc;
    (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
    actorx->status_data.weight = 255;
    actorx->world.position.x += 20.0f;
    curator->setupTalkAction_proc = &aCR_setupTalkAction;

    /* Clear 'first talk' flag if entering from a scene outside the museum */
    if (Common_Get(last_scene_no) >= SCENE_MY_ROOM_LL1 || Common_Get(last_scene_no) < SCENE_MUSEUM_ROOM_PAINTING) {
      aNPC_SPNPC_BIT_CLR(Common_Get(spnpc_first_talk_flags), aNPC_SPNPC_BIT_CURATOR);
    }
  }
}

static void aCR_actor_save(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aCR_actor_dt(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
}

static void aCR_actor_init(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aCR_actor_draw(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

#include "../src/ac_npc_curator_move.c_inc"
