#include "ac_set_manager.h"
#include "m_name_table.h"
#include "m_lib.h"
#include "m_field_info.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "ac_set_ovl_insect.h"
#include "ac_set_ovl_gyoei.h"

/**
 * @brief Gets the X & Z acre the player is currently in.
 * 
 * @param bx Out player X-acre
 * @param bz Out player Z-acre
 * @return TRUE/FALSE successfully updated the acre
 **/
static int aSetMgr_get_player_block(int* bx, int* bz, GAME_PLAY* play) {
  int res = FALSE;
  PLAYER_ACTOR* player_actor = get_player_actor_withoutCheck(play);

  if (player_actor != NULL) {
    res = mFI_Wpos2BlockNum(bx, bz, player_actor->actor_class.world.position);
  }

  return res;
}

/**
 * @brief Gets the next X & Z acre which the player is currently transitioning into.
 * 
 * @param next_bx Out next player X-acre
 * @param next_bz Out next player Z-acre
 * @return TRUE/FALSE successfully updated next acre
 **/
static int aSetMgr_renewal_player_next_pos(int* next_bx, int* next_bz) {
  int wade_end_pos_res;
  int wpos_2_blocknum_res;
  xyz_t endpos = { 0.0f, 0.0f, 0.0f };
  GAME_PLAY* play = (GAME_PLAY*)gamePT;

  wade_end_pos_res = get_player_actor_withoutCheck(play)->Get_WadeEndPos_proc((GAME*)play, &endpos); // maybe make this a macro like GET_PLAYER_ACTOR() ?
  wpos_2_blocknum_res = mFI_Wpos2BlockNum(next_bx, next_bz, endpos);
  return wpos_2_blocknum_res | wade_end_pos_res;
}

/**
 * @brief Updates the set manager's internal player acre and updates the previous player acre.
 * 
 * @param play GAME_PLAY pointer
 * @param player_pos Pointer to SET_MANAGER internal player position structure
 **/
static void aSetMgr_renewal_player_pos(GAME_PLAY* play, aSetMgr_player_pos_c* player_pos) {
  int bx, bz;
  
  player_pos->last_bx = player_pos->now_bx;
  player_pos->last_bz = player_pos->now_bz;

  if (aSetMgr_get_player_block(&bx, &bz, play) == TRUE) {
    player_pos->now_bx = bx;
    player_pos->now_bz = bz;
  }
}

/**
 * @brief Checks if the player's wade state is 'starting'.
 * 
 * @return TRUE when the player is beginning an acre transition, FALSE otherwise
 **/
static int aSetMgr_check_player_wade_start() {
  return mFI_CheckPlayerWade(mFI_WADE_START);
}

/**
 * @brief Checks if the player's wade state is 'ending'.
 * 
 * @return TRUE when the player is finishing an acre transition, FALSE otherwise
 **/
static int aSetMgr_check_player_wade_end() {
  return mFI_CheckPlayerWade(mFI_WADE_END);
}

/**
 * @brief Clears the set overlay buffer.
 * 
 * @param set_ovl Pointer to SET_MANAGER's internal aSetMgr_set_ovl_c overlay structure
 **/
static void aSetMgr_clear_set_ovl(aSetMgr_set_ovl_c* set_ovl) {
  bzero(set_ovl->buf, aSetMgr_SET_OVERLAY_BUF_SIZE);
  set_ovl->ovl_proc = NULL;
}

/**
 * @brief Updates the SET_MANAGER's current set overlay process.
 * 
 * @param set_ovl Pointer to SET_MANAGER's internal aSetMgr_set_ovl_c overlay structure
 * @param type The aSetMgr_OVERLAY_* type which will be executed
 * @return TRUE
 **/
static int aSetMgr_ovl(aSetMgr_set_ovl_c* set_ovl, int type) {
  static aSetMgr_ovl_proc proc_table[aSetMgr_OVERLAY_NUM] = { &aSOI_insect_set, &aSOG_gyoei_set };

  if (type < aSetMgr_OVERLAY_BEGIN || type >= aSetMgr_OVERLAY_NUM) {
    type = aSetMgr_OVERLAY_BEGIN;
  }

  set_ovl->ovl_proc = proc_table[type];
  return TRUE;
}

/**
 * @brief Clears the SET_MANAGER's "kept" data buffer.
 * 
 * @param keep Pointer to the SET_MANAGER's internal aSetMgr_keep_c structure
 **/
static void aSetMgr_clear_keep(aSetMgr_keep_c* keep) {
  bzero(keep, sizeof(aSetMgr_keep_c));
}

/**
 * @brief Check if the 'move' func state should be updated to 'check_wait'.
 * 
 * This check is succeeded by the player entering an acre transition state.
 * 
 * @param play GAME_PLAY pointer
 * @param set_manager SET_MANAGER pointer
 * @return TRUE when updated, FALSE otherwise
 **/
static int aSetMgr_move_check_set(GAME_PLAY* play, SET_MANAGER* set_manager) {
  int wading = FALSE;
  aSetMgr_renewal_player_pos(play, &set_manager->player_pos);

  /* update the next acre position if player is starting acre transition state */
  if (aSetMgr_check_player_wade_start() == TRUE) {
    aSetMgr_renewal_player_next_pos(&set_manager->player_pos.next_bx, &set_manager->player_pos.next_bz);
    set_manager->next_move_proc = aSetMgr_MOVE_move_check_wait;
    wading = TRUE;
  }

  return wading;
}

typedef int (*aSetMgr_move_proc)(GAME_PLAY*, SET_MANAGER*);

/**
 * @brief Checks whether or not to update the move proc to 'set'.
 * 
 * The SET_MANAGER's internal wait timer must be zero to pass this check.
 * 
 * @param play GAME_PLAY pointer
 * @param set_manager SET_MANAGER pointer
 * @return TRUE when updated, FALSE otherwise
 **/
static int aSetMgr_move_check_wait(GAME_PLAY* play, SET_MANAGER* set_manager) {
  int wait_timer;
  int res = FALSE;

  if (set_manager->next_move_proc == aSetMgr_MOVE_move_check_wait) {
    if (set_manager->wait_timer == 0) {
      wait_timer = 0;
    }
    else {
      wait_timer = --set_manager->wait_timer;
    }

    if (wait_timer == 0) {
      set_manager->next_move_proc = aSetMgr_MOVE_move_set;
      set_manager->wait_timer = aSetMgr_WAIT_TIME;
      res = TRUE;
    }
  }
  return res;
}

/**
 * @brief Processes SET_MANAGER's overlay actors & checks whether to update move func state.
 * 
 * All SET_MANAGER overlay processes must have been executed OR the player must
 * finish transitioning between acres for this check to pass.
 * 
 * @param play GAME_PLAY pointer
 * @param set_manager SET_MANAGER pointer
 * @return TRUE when updated, FALSE otherwise
 **/
static int aSetMgr_move_set(GAME_PLAY* play, SET_MANAGER* set_manager) {
  int res = FALSE;

  if (aSetMgr_ovl(&set_manager->set_overlay, set_manager->set_ovl_type) == TRUE &&
      set_manager->set_overlay.ovl_proc != NULL) {
      set_manager->set_overlay.ovl_proc(set_manager, play);
      set_manager->set_ovl_type++;
  }
  else {
    set_manager->set_ovl_type++;
  }

  if (set_manager->set_ovl_type >= aSetMgr_OVERLAY_NUM) {
    set_manager->next_move_proc = aSetMgr_MOVE_move_check_set;
    set_manager->set_ovl_type = aSetMgr_OVERLAY_BEGIN;
    res = TRUE;
  }

  if (aSetMgr_check_player_wade_end() == TRUE) {
    set_manager->next_move_proc = aSetMgr_MOVE_move_check_set;
    set_manager->set_ovl_type = aSetMgr_OVERLAY_BEGIN;
    res = TRUE;
  }

  return res;
}

/**
 * @brief SET_MANAGER move process.
 * 
 * @param actor Pointer to the SET_MANAGER actor
 * @param game GAME pointer
 **/
static void aSetMgr_move(ACTOR* actor, GAME* game) {
  static aSetMgr_move_proc move[aSetMgr_MOVE_PROC_NUM] = {
    &aSetMgr_move_check_set,
    &aSetMgr_move_check_wait,
    &aSetMgr_move_set
  };

  SET_MANAGER* set_manager = (SET_MANAGER*)actor;
  GAME_PLAY* play = (GAME_PLAY*)game;

  if ((*move[set_manager->move_proc])(play, set_manager) == TRUE) {
    set_manager->move_proc = set_manager->next_move_proc;
  }
}

/**
 * @brief SET_MANAGER constructor.
 * 
 * @param actor Pointer to the SET_MANAGER actor
 * @param game GAME pointer
 **/
static void aSetMgr_ct(ACTOR* actor, GAME* game) {
  SET_MANAGER* set_manager = (SET_MANAGER*)actor;
  GAME_PLAY* play = (GAME_PLAY*)game;

  set_manager->move_proc = aSetMgr_MOVE_move_check_set;
  set_manager->next_move_proc = aSetMgr_MOVE_move_check_set;
  set_manager->set_ovl_type = aSetMgr_OVERLAY_BEGIN;

  aSetMgr_clear_set_ovl(&set_manager->set_overlay);

  set_manager->player_pos.next_bx = 0;
  set_manager->player_pos.next_bz = 0;
  set_manager->player_pos.now_bx = 0;
  set_manager->player_pos.now_bz = 0;
  set_manager->player_pos.last_bx = 0;
  set_manager->player_pos.last_bz = 0;

  set_manager->wait_timer = aSetMgr_WAIT_TIME;

  aSetMgr_clear_keep(&set_manager->keep);
}

/**
 * @brief SET_MANAGER destructor.
 * 
 * @param actor Pointer to the SET_MANAGER actor
 * @param game GAME pointer
 **/
static void aSetMgr_dt(ACTOR* actor, GAME* game) { }

/* actor profile for SET_MANAGER */ 
ACTOR_PROFILE Set_Manager_Profile = {
  mAc_PROFILE_SET_MANAGER,
  ACTOR_PART_CONTROL, /* control actor type */
  ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES,
  EMPTY_NO,
  ACTOR_OBJ_BANK_3,
  sizeof(SET_MANAGER),
  aSetMgr_ct,
  aSetMgr_dt,
  aSetMgr_move,
  mActor_NONE_PROC1,
  NULL
};
