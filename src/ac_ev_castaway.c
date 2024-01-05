#include "ac_ev_castaway.h"

#include "m_common_data.h"

static void aECST_actor_ct(ACTOR* actorx, GAME* game);
static void aECST_actor_dt(ACTOR* actorx, GAME* game);
static void aECST_actor_init(ACTOR* actorx, GAME* game);
static void aECST_actor_move(ACTOR* actorx, GAME* game);
static void aECST_actor_draw(ACTOR* actorx, GAME* game);
static void aECST_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Castaway_Profile = {
  mAc_PROFILE_EV_CASTAWAY,
  ACTOR_PART_NPC,
  ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(EV_CASTAWAY_ACTOR),
  &aECST_actor_ct,
  &aECST_actor_dt,
  &aECST_actor_init,
  mActor_NONE_PROC1,
  &aECST_actor_save
};

static void aECST_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int type);

static void aECST_actor_ct(ACTOR* actorx, GAME* game) {
  static aNPC_ct_data_c ct_data = {
    &aECST_actor_move,
    &aECST_actor_draw,
    5,
    NULL,
    NULL,
    NULL,
    0
  };

  static xyz_t def_pos = { 3580.0f, 0.0f, 4670.0f }; // 'G-5' @ 9-4
  
  EV_CASTAWAY_ACTOR* castaway = (EV_CASTAWAY_ACTOR*)actorx;

  if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
    castaway->npc_class.schedule.schedule_proc = &aECST_schedule_proc;
    (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
    castaway->npc_class.condition_info.demo_flg = ~aNPC_COND_DEMO_SKIP_MOVE_Y; // is this a mistake?
    castaway->npc_class.condition_info.hide_request = FALSE;
    castaway->npc_class.palActorIgnoreTimer = -1;
    aNPC_SPNPC_BIT_SET(Common_Get(spnpc_first_talk_flags), aNPC_SPNPC_BIT_DOZAEMON);
    actorx->status_data.weight = 254;
    actorx->gravity = 0.0f;
    actorx->max_velocity_y = 0.0f;
    actorx->shape_info.rotation.y = DEG2SHORT_ANGLE(68.027344f); // 0x3060
    actorx->world.angle.y = DEG2SHORT_ANGLE(68.027344f); // 0x3060
    castaway->npc_class.movement.mv_angl = DEG2SHORT_ANGLE(68.027344f); // 0x3060
    actorx->world.position = def_pos;
    actorx->home.position = def_pos;
  }
}

static void aECST_actor_save(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aECST_actor_dt(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
}

static void aECST_actor_init(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aECST_schedule_main_proc(NPC_ACTOR* actorx, GAME_PLAY* play) {
  if (actorx->draw.animation_id != 116) {
    (*Common_Get(clip).npc_clip->animation_init_proc)((ACTOR*)actorx, 116, 0);
  }
}

static void aECST_schedule_proc(NPC_ACTOR* actorx, GAME_PLAY* play, int type) {
  static aNPC_SUB_PROC sched_proc[2] = {
    (aNPC_SUB_PROC)&none_proc1,
    aECST_schedule_main_proc
  };

  (*sched_proc[type])(actorx, play);
}

static void aECST_actor_move(ACTOR* actorx, GAME* game) {
  EV_CASTAWAY_ACTOR* castaway = (EV_CASTAWAY_ACTOR*)actorx;
  s16 cycle = castaway->bobbing_cycle;

  cycle += 512;
  actorx->position_speed.y = (actorx->home.position.y + 4.0f + sin_s(cycle) * 4.0f) - actorx->world.position.y;
  castaway->bobbing_cycle = cycle;
  (*Common_Get(clip).npc_clip->move_proc)(actorx, game);
}

static void aECST_actor_draw(ACTOR* actorx, GAME* game) {
  (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}
