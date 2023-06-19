#ifndef PLAYER_SELECT_H
#define PLAYER_SELECT_H

#include "types.h"
#include "game.h"
#include "m_view.h"
#include "m_private.h"
#include "m_land.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct game_player_select_s GAME_PLAYER_SELECT;
typedef void (*PLAYER_SELECT_INIT_PROC)(GAME_PLAYER_SELECT*);

#define SELECT_PLAYER_NUM TOTAL_PLAYER_NUM
#define SELECT_PLAYER_NAME_EXTRA 10
#define SELECT_NAME_LEN PLAYER_NAME_LEN + SELECT_PLAYER_NAME_EXTRA

/* sizeof(struct game_player_select_s) == 0x0288 */
struct game_player_select_s {
  /* 0x0000 */ GAME game;
  /* 0x00E0 */ View view;
  /* 0x0200 */ PLAYER_SELECT_INIT_PROC init_procs[SELECT_PLAYER_NUM];
  /* 0x0214 */ int player_no;
  /* 0x0218 */ int err_no;
  /* 0x021C */ int mode;
  /* 0x0220 */ u8 player_names[SELECT_PLAYER_NUM][SELECT_NAME_LEN];
  /* 0x027A */ u8 player_types[SELECT_PLAYER_NUM];
  /* 0x027F */ u8 land_name[LAND_NAME_SIZE];
  /* 0x0287 */ u8 land_exist;
};

enum {
  PLAYER_SELECT_MODE_SELECTION,
  PLAYER_SELECT_MODE_PLAY,

  PLAYER_SELECT_MODE_NUM
};

enum {
  PLAYER_SELECT_PLAYER_MODE_NO_SAVE,
  PLAYER_SELECT_PLAYER_MODE_UNREGISTERED,
  PLAYER_SELECT_PLAYER_MODE_HOME,
  PLAYER_SELECT_PLAYER_MODE_OUT,

  PLAYER_SELECT_PLAYER_MODE_NUM
};

enum {
  PLAYER_SELECT_INIT_ERR_NONE,
  PLAYER_SELECT_INIT_ERR_SUCCESS,
  PLAYER_SELECT_INIT_ERR_2,
  PLAYER_SELECT_INIT_ERR_3,
  PLAYER_SELECT_INIT_ERR_SAVE,
  PLAYER_SELECT_INIT_ERR_5,
  PLAYER_SELECT_INIT_ERR_PAK,

  PLAYER_SELECT_INIT_ERR_NUM
};

extern void player_select_init(GAME* game);
extern void player_select_cleanup(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
