#ifndef PLAYER_SELECT_H
#define PLAYER_SELECT_H

#include "types.h"
#include "game.h"
#include "m_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_player_select_s) == 0x0288 */
typedef struct game_player_select_s {
  /* 0x0000 */ GAME game;
  /* 0x00E0 */ View view;
  // TODO: finish this
  /* 0x0200 */ u8 _temp[0x88];
} GAME_PLAYER_SELECT;

extern void player_select_init(GAME_PLAYER_SELECT* player_select);
extern void player_select_cleanup(GAME_PLAYER_SELECT* player_select);

#ifdef __cplusplus
}
#endif

#endif
