#include "save_menu.h"

#include "m_npc.h"
#include "m_private.h"
#include "m_cpak.h"
#include "m_land.h"
#include "m_font.h"
#include "m_trademark.h"
#include "m_controller.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_common_data.h"

static void save_menu_set_cursor_col(GAME_SAVE_MENU* save_menu) {
    /* this was likely meant to be static */
    int cursor_col[10][3] = {
        { 192, 120, 120 }, { 224, 130, 130 }, { 240, 150, 150 }, { 255, 180, 180 }, { 240, 150, 150 },
        { 224, 130, 130 }, { 192, 120, 120 }, { 128, 80, 80 },   { 64, 64, 64 },    { 128, 80, 80 },
    };

    int(*dst)[3] = &save_menu->cursor_col[save_menu->mode];
    int(*color)[3] = &cursor_col[(u32)save_menu->frame / 4];
    int i;
    for (i = 0; i < 3; i++) {
        (*dst)[i] = (*color)[i];
    }
}

static void save_menu_reset_cursor_col(int (*color)[3]) {
    int default_color[3] = { 40, 40, 40 };
    int i;

    for (i = 0; i < 3; i++) {
        (*color)[i] = default_color[i];
    }
}

typedef void (*SAVE_MENU_PROC)(GAME_SAVE_MENU*);

static void save_menu_data_save_from(GAME_SAVE_MENU* save_menu) {
    if ((int)Common_Get(player_no) != mPr_FOREIGNER) {
        Common_Get(now_private)->exists = TRUE;
        save_menu->error = SAVE_ERROR_EXIT; // OK
    } else {
        save_menu->error = SAVE_ERROR_FLASHROM; // Player is foriegner
    }
}

static void save_menu_data_save_pak(GAME_SAVE_MENU* save_menu) {
    Private_c* private = Common_Get(now_private);
    if ((int)Common_Get(player_no) == mPr_FOREIGNER) {
        AnmPersonalID_c* foriegn_id = mNpc_GetOtherAnimalPersonalID(NULL, 0);
        if (foriegn_id != NULL) {
            mNpc_CopyAnimalPersonalID(&private->stored_anm_id, foriegn_id);
        }
    }

    mCPk_PakOpen(mCPk_get_pkinfo(), 0);
    if (mCPk_SavePak(Save_Get(private_data), Save_Get(animals), mCPk_get_pkinfo()) == TRUE) {
        if (mLd_PlayerManKindCheck() == FALSE) {
            Common_Get(now_private)->exists = FALSE;
        }

        save_menu->error = SAVE_ERROR_EXIT; // OK
    } else {
        save_menu->error = SAVE_ERROR_CPAK; // Failed to save to CPak
    }
}

static void save_menu_move_do_save(GAME_SAVE_MENU* save_menu) {
    static SAVE_MENU_PROC save_proc[SAVE_MODE_NUM] = { &save_menu_data_save_from, &save_menu_data_save_pak };

    int mode = save_menu->mode;

    /* Check and save to select location */
    if (chkTrigger(BUTTON_A)) {
        (*save_proc[mode])(save_menu);
    }

    /* Check and change selected save mode */
    if (chkTrigger(BUTTON_R) || chkTrigger(BUTTON_DUP) || chkTrigger(BUTTON_DDOWN)) {
        save_menu->frame = 0;
        save_menu_reset_cursor_col(save_menu->cursor_col + mode);
        save_menu->mode++;

        if (save_menu->mode >= SAVE_MODE_NUM) {
            save_menu->mode = SAVE_MODE_BEGIN;
        }
    }

    /* Check if should exit menu */
    if (chkTrigger(BUTTON_B)) {
        save_menu->error = SAVE_ERROR_EXIT; // OK
    }
}

static void save_menu_move_finish(GAME_SAVE_MENU* save_menu) {
    GAME_GOTO_NEXT((GAME*)save_menu, trademark, TRADEMARK);
}

static void save_menu_move_err(GAME_SAVE_MENU* save_menu) {
    save_menu->error = SAVE_ERROR_NONE; // cleared
}

static void save_menu_move_main(GAME_SAVE_MENU* save_menu) {
    static SAVE_MENU_PROC sub_proc[SAVE_ERROR_NUM] = { &save_menu_move_do_save, &save_menu_move_err,
                                                       &save_menu_move_err, &save_menu_move_finish };

    int error = save_menu->error;

    if (error >= SAVE_ERROR_NONE && error < SAVE_ERROR_NUM) {
        (*sub_proc[error])(save_menu);
    }

    save_menu_set_cursor_col(save_menu);
    save_menu->frame++;

    if (save_menu->frame == 40) {
        save_menu->frame = 0;
    }
}

static void save_menu_draw_title(GAME_SAVE_MENU* save_menu) {
    /* This translates to 'セーブ メニュー' (save menu), the devs didn't bother translating it */
    u8 title[] = { 0x9E, 0x90, 0xDF, CHAR_SPACE, 0xB2, 0xA6, 0x8D, 0x90 };

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace((GAME*)save_menu, title, ARRAY_SIZE(title, u8), 110.0f, 30.0f, 200, 50, 50, 255,
                                  FALSE, TRUE, FALSE, 1.1f, 1.1f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);
}

static void save_menu_draw_push_a(GAME_SAVE_MENU* save_menu) {
    /* Push A Button */
    u8 push_a[] = { CHAR_P, CHAR_u, CHAR_s, CHAR_h, CHAR_SPACE, CHAR_A, CHAR_SPACE,
                    CHAR_B, CHAR_u, CHAR_t, CHAR_t, CHAR_o,     CHAR_n };

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace((GAME*)save_menu, push_a, ARRAY_SIZE(push_a, u8), 95.0f, 175.0f, 200, 200, 200, 255,
                                  FALSE, TRUE, FALSE, 0.8f, 0.8f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);
}

static void save_menu_draw_select_r(GAME_SAVE_MENU* save_menu) {
    /* Select R Button */
    u8 select_r[] = { CHAR_S,     CHAR_e, CHAR_l, CHAR_e, CHAR_c, CHAR_t, CHAR_SPACE, CHAR_R,
                      CHAR_SPACE, CHAR_B, CHAR_u, CHAR_t, CHAR_t, CHAR_o, CHAR_n };

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace((GAME*)save_menu, select_r, ARRAY_SIZE(select_r, u8), 76.0f, 185.0f, 200, 200, 200,
                                  255, FALSE, TRUE, FALSE, 0.8f, 0.8f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);
}

static void save_menu_draw_push_b(GAME_SAVE_MENU* save_menu) {
    /* Push B Button to EXIT */
    u8 push_b[] = { CHAR_P, CHAR_u, CHAR_s,     CHAR_h, CHAR_SPACE, CHAR_B, CHAR_SPACE,
                    CHAR_B, CHAR_u, CHAR_t,     CHAR_t, CHAR_o,     CHAR_n, CHAR_SPACE,
                    CHAR_t, CHAR_o, CHAR_SPACE, CHAR_E, CHAR_X,     CHAR_I, CHAR_T };

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace((GAME*)save_menu, push_b, ARRAY_SIZE(push_b, u8), 50.0f, 210.0f, 200, 200, 200, 255,
                                  FALSE, TRUE, FALSE, 0.8f, 0.8f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);
}

static void save_menu_draw_select_mode(GAME_SAVE_MENU* save_menu) {
    /*

    [0] = 'FlashRom にセーブ'     "Save to FlashRom"
    [1] = 'パック にセーブ     '  "Save to Pak"

    */
    u8 select_mode[SAVE_MODE_NUM][13] = {
        { CHAR_F, CHAR_l, CHAR_a, CHAR_s, CHAR_h, CHAR_R, CHAR_o, CHAR_m, CHAR_SPACE, 0x15, 0x9E, 0x90, 0xDF },
        { 0xE2, 0x8F, 0x98, CHAR_SPACE, 0x15, 0x9E, 0x90, 0xDF, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE, CHAR_SPACE,
          CHAR_SPACE },
    };

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace(
        (GAME*)save_menu, select_mode[SAVE_MODE_FLASHROM], ARRAY_SIZE(select_mode[SAVE_MODE_FLASHROM], u8), 60.0f,
        85.0f, save_menu->cursor_col[SAVE_MODE_FLASHROM][0], save_menu->cursor_col[SAVE_MODE_FLASHROM][1],
        save_menu->cursor_col[SAVE_MODE_FLASHROM][2], 255, FALSE, TRUE, FALSE, 1.2f, 1.2f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);

    mFont_SetMatrix(save_menu->game.graph, mFont_MODE_FONT);
    mFont_SetLineStrings_AndSpace(
        (GAME*)save_menu, select_mode[SAVE_MODE_CPAK], ARRAY_SIZE(select_mode[SAVE_MODE_CPAK], u8), 100.0f, 125.0f,
        save_menu->cursor_col[SAVE_MODE_CPAK][0], save_menu->cursor_col[SAVE_MODE_CPAK][1],
        save_menu->cursor_col[SAVE_MODE_CPAK][2], 255, FALSE, TRUE, FALSE, 1.2f, 1.2f, mFont_MODE_FONT);
    mFont_UnSetMatrix(save_menu->game.graph, mFont_MODE_FONT);
}

extern void save_menu_draw_main(GAME_SAVE_MENU* save_menu) {
    GRAPH* g = save_menu->game.graph;

    OPEN_DISP(g);

    gSPSegment(NOW_POLY_OPA_DISP++, G_MWO_SEGMENT_0, 0);
    DisplayList_initialize(g, 0, 0, 0, NULL);
    gDPPipeSync(NOW_POLY_OPA_DISP++);

    CLOSE_DISP(g);

    showView(&save_menu->view, VIEW_UPDATE_ALL);
    save_menu_draw_title(save_menu);
    save_menu_draw_push_a(save_menu);
    save_menu_draw_select_r(save_menu);
    save_menu_draw_push_b(save_menu);
    save_menu_draw_select_mode(save_menu);
}

static void save_menu_main(GAME* game) {
    GRAPH* g;
    GAME_SAVE_MENU* save_menu = (GAME_SAVE_MENU*)game;
    save_menu_move_main(save_menu);
    save_menu_draw_main(save_menu);

    g = game->graph;
    game_debug_draw_last(game, g);
    game_draw_last(g);
}

extern void save_menu_cleanup(GAME* game) {
}

extern void save_menu_init(GAME* game) {
    GAME_SAVE_MENU* save_menu = (GAME_SAVE_MENU*)game;
    View* view = &save_menu->view;
    GRAPH* g = game->graph;
    int i;

    game->exec = &save_menu_main;
    game->cleanup = &save_menu_cleanup;

    initView(view, g);
    view->flag = VIEW_UPDATE_ORTHOGRAPHIC;
    
    new_Matrix(game);
    SetGameFrame(1);

    save_menu->frame = 0;
    save_menu->mode = SAVE_MODE_BEGIN;
    save_menu->error = SAVE_ERROR_NONE;

    for (i = 0; i < SAVE_MODE_NUM; i++) {
        save_menu_reset_cursor_col(save_menu->cursor_col + i);
    }
}
