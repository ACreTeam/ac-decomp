#ifndef M_SELECT_H
#define M_SELECT_H

#include "types.h"
#include "game.h"
#include "m_view.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct game_select_s) == 0x0238 */
typedef struct game_select_s {
  /* 0x0000 */ GAME game;
  /* 0x00E0 */ View view;
  /* 0x0200 */ int status;
  /* 0x0204 */ int cursor_x;
  /* 0x0208 */ int cursor_y;
  /* 0x020C */ int step;
  /* 0x0210 */ int step_add;
  /* 0x0214 */ int selected_course;
  /* 0x0218 */ int top_course; /* course at top of screen it seems */
  /* 0x021C */ u32 unk_21C;
  /* 0x0220 */ int button_step;
  /* 0x0224 */ u8 name[8];
  /* 0x0228 */ int unk_228[3];
} GAME_SELECT;

extern void select_init(GAME_SELECT* select);
extern void select_cleanup(GAME_SELECT* select);

#ifdef __cplusplus
}
#endif

#endif
