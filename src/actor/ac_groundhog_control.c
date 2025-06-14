#include "ac_groundhog_control.h"

#include "m_bgm.h"
#include "m_name_table.h"
#include "m_common_data.h"

static void aGHC_actor_ct(ACTOR* actor, GAME* game);
static void aGHC_actor_dt(ACTOR* actor, GAME* game);
static void aGHC_actor_move(ACTOR* actor, GAME* game);

ACTOR_PROFILE Groundhog_Control_Profile = {
  mAc_PROFILE_GROUNDHOG_CONTROL,
  ACTOR_PART_CONTROL,
  ACTOR_STATE_NO_MOVE_WHILE_CULLED,
  EMPTY_NO,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(GROUNDHOG_CONTROL_ACTOR),
  &aGHC_actor_ct,
  &aGHC_actor_dt,
  &aGHC_actor_move,
  mActor_NONE_PROC1,
  NULL
};

static int aGHC_get_now_term();
static void aGHC_setupAction(GROUNDHOG_CONTROL_ACTOR* groundhog_control, int action);

static void aGHC_actor_ct(ACTOR* actor, GAME* game) {
  GROUNDHOG_CONTROL_ACTOR* groundhog_control = (GROUNDHOG_CONTROL_ACTOR*)actor;
  int action = aGHC_ACTION_BEFORE_800;
  aGHC_event_area_c* event_area;

  if (aGHC_TIME_CHECK(8, 0, 0)) {
    action = aGHC_ACTION_AFTER_800;
  }

  if (Common_Get(clip).groundhog_control_clip == NULL) {
    Common_Get(clip).groundhog_control_clip = &groundhog_control->clip;
    Common_Get(clip).groundhog_control_clip->now_term = aGHC_get_now_term();
  }

  event_area = (aGHC_event_area_c*)mEv_get_common_area(mEv_EVENT_GROUNDHOG_DAY, 0);

  if (event_area == NULL) {
    event_area = (aGHC_event_area_c*)mEv_reserve_common_area(mEv_EVENT_GROUNDHOG_DAY, 0);
  }
  else if (event_area->awaiting_birth == TRUE) {
    action = aGHC_ACTION_BIRTH_RESET_WAIT;
    groundhog_control->timer = 600;
  }

  groundhog_control->event_area_p = event_area;
  aGHC_setupAction(groundhog_control, action);
}

static void aGHC_actor_dt(ACTOR* actor, GAME* game) {
  Common_Get(clip).groundhog_control_clip = NULL;
  mEv_actor_dying_message(mEv_EVENT_GROUNDHOG_DAY, actor);
}

static int aGHC_get_now_term() {
  int res;

  if (aGHC_TIME_CHECK(8, 0, 0)) {
    res = aGHC_TERM_EVENT_TIME;
  }
  else if (aGHC_TIME_CHECK(7, 59, 0)) {
    res = aGHC_TERM_1_MIN;
  }
  else if (aGHC_TIME_CHECK(7, 55, 0)) {
    res =  aGHC_TERM_5_MIN;
  }
  else if (aGHC_TIME_CHECK(7, 45, 0)) {
    res =  aGHC_TERM_15_MIN;
  }
  else if (aGHC_TIME_CHECK(7, 30, 0)) {
    res = aGHC_TERM_30_MIN;
  }
  else {
    res =  aGHC_TERM_1_HOUR;
  }

  return res;
}

static void aGHC_search_soncho(GAME_PLAY* play) {
  if (Common_Get(clip).groundhog_control_clip->attention_target_actor == NULL) {
    Common_Get(clip).groundhog_control_clip->attention_target_actor = Actor_info_fgName_search(&play->actor_info, SP_NPC_EV_SPEECH_SONCHO, ACTOR_PART_NPC);
  }
}

static void aGHC_set_attention_request(int groundhog_is_target) {
  ACTOR* attention_target = NULL;

  if (groundhog_is_target == FALSE) {
    if (Common_Get(clip).groundhog_control_clip->attention_target_actor != NULL) {
      attention_target = Common_Get(clip).groundhog_control_clip->attention_target_actor;
    }
  }
  else if (Common_Get(clip).groundhog_control_clip->groundhog_npc_actor != NULL) {
    attention_target = Common_Get(clip).groundhog_control_clip->groundhog_npc_actor;
  }

  if (attention_target != NULL) {
    (*Common_Get(clip).npc_clip->set_attention_request_proc)(aNPC_ATTENTION_TYPE_ACTOR, attention_target, NULL);
  }
}

static void aGHC_before_800(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  if (aGHC_TIME_CHECK(8, 0, 0) && Common_Get(clip).event_manager_clip != NULL) {
    EVENT_MANAGER_ACTOR* event_manager = Common_Get(clip).event_manager_clip->event_manager_actor;
    Common_Get(clip).groundhog_control_clip->fading_title = TRUE;

    if ((*Common_Get(clip).event_manager_clip->title_fade_proc)(event_manager, mEv_EVENT_GROUNDHOG_DAY, 1, aEvMgr_EVENT_PLACE_SHRINE)) {
      Common_Get(clip).groundhog_control_clip->fading_title = FALSE;
      groundhog_control->event_area_p->awaiting_birth = TRUE;
    }
  }
}

static void aGHC_birth_reset_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  groundhog_control->timer--;

  if (groundhog_control->timer <= 0) {
    aGHC_setupAction(groundhog_control, aGHC_ACTION_BIRTH_RESET);
  }
}

static void aGHC_birth_reset(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  int bx;
  int bz;

  if (Common_Get(clip).npc_clip != NULL && Common_Get(clip).npc_clip->setupActor_proc != NULL && mFI_BlockKind2BkNum(&bx, &bz, mRF_BLOCKKIND_SHRINE) == TRUE) {
    int spawned_actor = (*Common_Get(clip).npc_clip->setupActor_proc)(play, SP_NPC_EV_MAJIN, -1, -1, -1, bx, bz, 5, 8);

    if (spawned_actor == TRUE) {
      ACTOR* groundhog_actor = Actor_info_fgName_search(&play->actor_info, SP_NPC_EV_MAJIN, ACTOR_PART_NPC);

      groundhog_actor->parent_actor = (ACTOR*)groundhog_control;
      Common_Get(clip).groundhog_control_clip->groundhog_npc_actor = groundhog_actor;
      groundhog_control->event_area_p->awaiting_birth = FALSE;
      groundhog_control->attention_mode = aGHC_ATTENTION_GROUNDHOG;
      mBGMPsComp_make_ps_quietField(360);
      groundhog_control->timer = 240;
      aGHC_setupAction(groundhog_control, aGHC_ACTION_RESET_SPEECH_BGM_START_WAIT);
    }
  }
}

static void aGHC_reset_speech_bgm_start_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  groundhog_control->timer--;

  if (groundhog_control->timer <= 0) {
    mBGMPsComp_make_ps_demo(252, 360);
    aGHC_setupAction(groundhog_control, aGHC_ACTION_RETIRE_RESET_WAIT);
  }
}

static void aGHC_retire_reset_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  if (groundhog_control->event_state == aGHC_EVENT_STATE_MAJIN_DONE) {
    groundhog_control->timer = 60;
    Camera2_Inter_set_reverse_mode(play);
    mBGMPsComp_delete_ps_demo(252, 360);
    groundhog_control->attention_mode = aGHC_ATTENTION_SONCHO;
    aGHC_setupAction(groundhog_control, aGHC_ACTION_SONCHO_SPEECH_START_WAIT);
  }
}

static void aGHC_soncho_speech_start_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  groundhog_control->timer--;

  if (groundhog_control->timer <= 0) {
    aGHC_setupAction(groundhog_control, aGHC_ACTION_SONCHO_SPEECH_END_WAIT);
  }
}

static void aGHC_soncho_speech_end_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  if (groundhog_control->event_state == aGHC_EVENT_STATE_SONCHO_DONE) {
    groundhog_control->timer = 20;
    aGHC_setupAction(groundhog_control, aGHC_ACTION_FADE_OUT_START_WAIT);
  }
}

static void aGHC_fade_out_start_wait(GROUNDHOG_CONTROL_ACTOR* groundhog_control, GAME_PLAY* play) {
  groundhog_control->timer--;

  if (groundhog_control->timer <= 0) {
    Common_Set(event_title_fade_in_progress, TRUE);
    mBGMPsComp_delete_ps_quietField();
    mBGMPsComp_make_ps_co_quiet(360, 60);
    aGHC_setupAction(groundhog_control, aGHC_ACTION_AFTER_800);
  }
}

static void aGHC_setupAction(GROUNDHOG_CONTROL_ACTOR* groundhog_control, int action) {
  static aGHC_ACTION_PROC process[aGHC_ACTION_NUM] = {
    &aGHC_before_800,
    &aGHC_birth_reset_wait,
    &aGHC_birth_reset,
    &aGHC_retire_reset_wait,
    &aGHC_reset_speech_bgm_start_wait,
    &aGHC_soncho_speech_start_wait,
    &aGHC_soncho_speech_end_wait,
    &aGHC_fade_out_start_wait,
    (aGHC_ACTION_PROC)&none_proc1
  };

  groundhog_control->action_proc = process[action];
  groundhog_control->action = action;
}

static void aGHC_actor_move(ACTOR* actor, GAME* game) {
  GROUNDHOG_CONTROL_ACTOR* groundhog_control = (GROUNDHOG_CONTROL_ACTOR*)actor;
  GAME_PLAY* play = (GAME_PLAY*)game;

  Common_Get(clip).groundhog_control_clip->now_term = aGHC_get_now_term();
  aGHC_search_soncho(play);
  aGHC_set_attention_request(groundhog_control->attention_mode);
  (*groundhog_control->action_proc)(groundhog_control, play);
  groundhog_control->event_state = aGHC_EVENT_STATE_NONE;
}
