#include "m_fuusen.h"

#include "m_name_table.h"
#include "m_play.h"
#include "m_field_assessment.h"
#include "m_private.h"
#include "m_event.h"
#include "m_common_data.h"

int fuusen_DEBUG_mode_flag;

extern void Balloon_init(GAME_PLAY* play) {
  Common_Set(balloon_state, Balloon_STATE_DEAD);
  Common_Set(balloon_last_spawn_min, 0);
  Common_Set(balloon_spawn_percent, 0.05f);
}

extern void Balloon_make_fuusen(GAME_PLAY* play) {
  ACTOR* balloon_actor = Actor_info_make_actor(&play->actor_info, (GAME*)play, mAc_PROFILE_FUUSEN, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1, -1, -1, EMPTY_NO, 0, -1, -1);
  if (balloon_actor != NULL) {
    Common_Set(balloon_state, Balloon_STATE_SPAWNED);
    Common_Set(balloon_spawn_percent, (1.0f - Common_Get(balloon_spawn_percent)) * 0.1f);
    fuusen_DEBUG_mode_flag = TRUE;
  }
  else {
    Common_Set(balloon_state, Balloon_STATE_PENDING_SPAWN);
  }
}

extern void Balloon_chk_make_fuusen(GAME_PLAY* play) {
  f32 rng = fqrand();
  f32 spawn_percent = Common_Get(balloon_spawn_percent);
  
  if (rng < spawn_percent) {
    Balloon_make_fuusen(play);
  }
  else {
    f32 goods_power_mod;
    f32 field_rank_mod;
    f32 balloon_spawn_percentage_inc;
    
    field_rank_mod = (f32)mFAs_GetFieldRank() / (f32)mFAs_FIELDRANK_SIX;
    goods_power_mod = (f32)mPr_GetGoodsPower() / (f32)mPr_GOODS_POWER_MAX;
    balloon_spawn_percentage_inc = 0.025f + goods_power_mod * 0.025f + field_rank_mod * 0.025f + RANDOM_F(0.025f);

    Common_Get(balloon_spawn_percent) += balloon_spawn_percentage_inc;
  }
}

extern void Balloon_move(GAME_PLAY* play) {
  s16 min;
    
  if (mFI_GET_TYPE(mFI_GetFieldId()) != mFI_FIELDTYPE_FG) {
    return;
  }

  if (mEv_CheckFirstIntro()) {
    return;
  }

  switch (Common_Get(balloon_state)) {
    case Balloon_STATE_DEAD:
    case Balloon_STATE_CHK_SPAWN:
    case Balloon_STATE_LOOK_UP:
      break;

    case Balloon_STATE_PENDING_SPAWN:
      Balloon_make_fuusen(play);
    /* Fallthrough */
    case Balloon_STATE_SPAWNED:
    default:
      return;
  }

  min = Common_Get(time.rtc_time.min);
  if ((min % 5) == 3 && min != Common_Get(balloon_last_spawn_min)) {
    Common_Set(balloon_last_spawn_min, min);
    
    if (Common_Get(balloon_state) == Balloon_STATE_LOOK_UP) {
      Common_Get(balloon_spawn_percent) += 0.25f;
    }

    Common_Set(balloon_state, Balloon_STATE_CHK_SPAWN);
    Balloon_chk_make_fuusen(play);
  }
}

extern void Balloon_kill() {
  Common_Set(balloon_state, Balloon_STATE_DEAD);
}

extern void Balloon_look_up() {
  Common_Set(balloon_state, Balloon_STATE_LOOK_UP);
}
