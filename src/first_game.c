#include "first_game.h"

#include "sys_romcheck.h"
#include "m_vibctl.h"
#include "m_bgm.h"
#include "m_card.h"
#include "m_common_data.h"
#include "second_game.h"
#include "Famicom/famicom.h"

static void exit_game(GAME* game) {
  famicom_setCallback_getSaveChan(&mCD_GetThisLandSlotNo_code);
  mBGM_ct();
  mVibctl_ct();
  common_data_init();
  GAME_GOTO_NEXT(game, second_game, SECOND);
}

extern void first_game_cleanup(GAME* game) { }

extern void first_game_init(GAME* game) {
  game->cleanup = &first_game_cleanup;
  sys_romcheck();
  mCD_save_data_aram_malloc();
  exit_game(game);
}
