#ifndef SAVE_MENU_H
#define SAVE_MENU_H

#include "types.h"
#include "game.h"
#include "m_view.h"

#ifdef __cplusplus
extern "C" {
#endif

enum save_mode {
    SAVE_MODE_BEGIN,

    SAVE_MODE_FLASHROM = SAVE_MODE_BEGIN,
    SAVE_MODE_CPAK,

    SAVE_MODE_NUM
};

enum save_error {
    SAVE_ERROR_NONE,
    SAVE_ERROR_FLASHROM,
    SAVE_ERROR_CPAK,
    SAVE_ERROR_EXIT,

    SAVE_ERROR_NUM
};

/* sizeof(struct game_save_menu_s) == 0x0228 */
typedef struct game_save_menu_s {
    /* 0x0000 */ GAME game;
    /* 0x00E0 */ View view;
    /* 0x0200 */ u32 frame;
    /* 0x0204 */ int mode;
    /* 0x0208 */ int error;
    /* 0x020C */ int cursor_col[SAVE_MODE_NUM][3];
} GAME_SAVE_MENU;

extern void save_menu_draw_main(GAME_SAVE_MENU* save_menu);
extern void save_menu_cleanup(GAME* game);
extern void save_menu_init(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
