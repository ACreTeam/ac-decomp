#include "m_huusui_room.h"

#include "m_huusui_room_ovl.h"
#include "game.h"
#include "m_private.h"
#include "m_event.h"
#include "m_common_data.h"

/**
 * @brief Main Feng Shui scoring entrypoint. Originally meant to live in code always.
 * 
 * @param game Unused GAME pointer
 * @param player_no The index of the player whose house will be scored for Feng Shui
 **/
extern void mHsRm_GetHuusuiRoom(GAME* game, int player_no) {
  /* Do not calculate Feng Shui if the player is doing chores or is from another town */
  if (mEv_CheckFirstJob() == FALSE && player_no != mPr_FOREIGNER) {
    mHsRm_HuusuiRoomOvl(player_no);
  }
  else {
    Common_Set(money_power, 0);
    Common_Set(goods_power, 0);
  }
}
