#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include "types.h"
#include "game.h"
#include "m_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_save_menu_s) == 0x0228 */
typedef struct game_save_menu_s {
  /* 0x0000 */ GAME game;
  /* 0x00E0 */ View view;
  // TODO: finish this
  /* 0x0200 */ u8 _temp[0x28];
} GAME_SAVE_MENU;

extern void save_menu_init(GAME_SAVE_MENU* save_menu);
extern void save_menu_cleanup(GAME_SAVE_MENU* save_menu);

#ifdef __cplusplus
}
#endif

#endif
