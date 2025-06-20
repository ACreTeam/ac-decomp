#include "m_cpwarning_ovl.h"

#include "m_submenu_ovl.h"
#include "sys_matrix.h"
#include "m_common_data.h"
#include "m_font.h"

static mCW_Ovl_c cpwarning_ovl_data;

static u8 mCW_mes0[18] = "Do you want to let";
static u8 mCW_mes1[27] = "anyone else see this diary?";
static u8 mCW_yes_mes[3] = "Yes";
static u8 mCW_no_mes[2] = "No";

enum {
    mCW_MOVE_OUT,
    mCW_MOVE_IN,

    mCW_MOVE_NUM
};

static void mCW_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCW_Ovl_c* cpwarning_ovl = submenu->overlay->cpwarning_ovl;

    if (cpwarning_ovl->move_dir == mCW_MOVE_IN) {
        cpwarning_ovl->scale += 0.2f;

        if (cpwarning_ovl->scale > 1.0f) {
            cpwarning_ovl->scale = 1.0f;
            menu_info->proc_status = menu_info->next_proc_status;
            cpwarning_ovl->_00 = 0;
            cpwarning_ovl->_01 = 0;
        }
    } else if (cpwarning_ovl->move_dir == mCW_MOVE_OUT) {
        cpwarning_ovl->scale -= 0.2f;

        if (cpwarning_ovl->scale < 0.0f) {
            cpwarning_ovl->scale = 0.0f;
            menu_info->proc_status = menu_info->next_proc_status;
            menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
        }
    }
}

static void mCW_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    u32 trigger = submenu->overlay->menu_control.trigger;
    mCW_Ovl_c* cpwarning_ovl = submenu->overlay->cpwarning_ovl;

    if ((trigger & BUTTON_A) != 0) {
        menu_info->next_proc_status = mSM_OVL_PROC_END;
        cpwarning_ovl->move_dir = mCW_MOVE_OUT;
        menu_info->proc_status = mSM_OVL_PROC_MOVE;
        cpwarning_ovl->scale = 1.0f;
        cpwarning_ovl->_0C = 1.0f;
        Now_Private->calendar.edit = cpwarning_ovl->diary_edit_mode;
    } else if ((trigger & BUTTON_CLEFT) != 0) {
        if (cpwarning_ovl->diary_edit_mode == 1) {
            cpwarning_ovl->diary_edit_mode = 0;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    } else if ((trigger & BUTTON_CRIGHT) != 0) {
        if (cpwarning_ovl->diary_edit_mode == 0) {
            cpwarning_ovl->diary_edit_mode = 1;
            sAdo_SysTrgStart(NA_SE_CURSOL);
        }
    }

    cpwarning_ovl->_00 = (cpwarning_ovl->_00 + 1) % 30;
    if (cpwarning_ovl->_00 < 15) {
        cpwarning_ovl->_01 = (int)(((f32)cpwarning_ovl->_00 * 255.0f) / 15.0f);
    } else {
        cpwarning_ovl->_01 = (int)(((f32)(30 - cpwarning_ovl->_00) * 255.0f) / 15.0f);
    }
}

static void mCW_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mCW_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mCW_cpwarning_ovl_move(Submenu* submenu) {
    static mCW_OVL_PROC ovl_move_proc[] = {
        &mCW_move_Move, &mCW_move_Play, (mCW_OVL_PROC)&none_proc1, (mCW_OVL_PROC)&none_proc1, &mCW_move_End,
    };

    mSM_Control_c* control = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPWARNING];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx dia_att_winT_model[];
extern Gfx dia_att_cursor_model[];

static void mCW_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    GRAPH* graph = game->graph;
    mCW_Ovl_c* cpwarning_ovl = submenu->overlay->cpwarning_ovl;

    Matrix_scale(16.0f * cpwarning_ovl->scale, 16.0f * cpwarning_ovl->scale, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetBlendColor(POLY_OPA_DISP++, 255, 255, 255, 40);
    gSPDisplayList(POLY_OPA_DISP++, dia_att_winT_model);

    if (cpwarning_ovl->diary_edit_mode) {
        Matrix_translate(19.0f, -29.0f, 0.0f, MTX_MULT);
    } else {
        Matrix_translate(-19.0f, -29.0f, 0.0f, MTX_MULT);
    }
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, dia_att_cursor_model);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mCW_set_character_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    static u8 color_table[2][3] = { { 30, 30, 215 }, { 110, 110, 140 } };

    GRAPH* graph = game->graph;
    mCW_Ovl_c* cpwarning_ovl = submenu->overlay->cpwarning_ovl;
    f32 scale = cpwarning_ovl->scale;
    f32 x = 160.0f - 112.0f * scale;
    f32 y = 120.0f - 56.0f * scale;
    u8* color;

    submenu->overlay->set_char_matrix_proc(game->graph);

    y += 28.0f * scale;
    mFont_SetLineStrings(game, mCW_mes0, sizeof(mCW_mes0), x + 54.0f * scale, y, 95, 20, 20, 255, FALSE, TRUE, scale,
                         scale, mFont_MODE_POLY);

    y += 24.0f * scale;
    mFont_SetLineStrings(game, mCW_mes1, sizeof(mCW_mes1), x + 30.0f * scale, y, 95, 20, 20, 255, FALSE, TRUE, scale,
                         scale, mFont_MODE_POLY);

    y += 24.0f * scale;
    color = color_table[cpwarning_ovl->diary_edit_mode];
    mFont_SetLineStrings(game, mCW_yes_mes, sizeof(mCW_yes_mes), x + 94.0f * scale, y, color[0], color[1], color[2],
                         255, FALSE, TRUE, scale, scale, mFont_MODE_POLY);
    color = color_table[!cpwarning_ovl->diary_edit_mode];
    mFont_SetLineStrings(game, mCW_no_mes, sizeof(mCW_no_mes), x + 133.0f * scale, y, color[0], color[1], color[2], 255,
                         FALSE, TRUE, scale, scale, mFont_MODE_POLY);
}

static void mCW_cpwarning_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPWARNING];

    menu_info->pre_draw_func(submenu, game);
    mCW_set_frame_dl(submenu, game, menu_info);
    mCW_set_character_dl(submenu, game, menu_info);
}

extern void mCW_cpwarning_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mCW_cpwarning_ovl_move;
    overlay->menu_control.menu_draw_func = &mCW_cpwarning_ovl_draw;
}

static void mCW_cpwarning_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCW_Ovl_c* cpwarning_ovl = submenu->overlay->cpwarning_ovl;

    submenu->overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    cpwarning_ovl->_06 = 30;
    cpwarning_ovl->scale = 0.0f;
    cpwarning_ovl->_0C = 0.0f;
    cpwarning_ovl->move_dir = mCW_MOVE_IN;
    sAdo_SysTrgStart(MONO(NA_SE_3));
    cpwarning_ovl->diary_edit_mode = Now_Private->calendar.edit;
}

extern void mCW_cpwarning_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_CPWARNING];

    if (overlay->cpwarning_ovl == NULL) {
        mem_clear((u8*)&cpwarning_ovl_data, sizeof(cpwarning_ovl_data), 0);
        overlay->cpwarning_ovl = &cpwarning_ovl_data;
    }

    mCW_cpwarning_ovl_init(submenu, menu_info);
    mCW_cpwarning_ovl_set_proc(submenu);
}

extern void mCW_cpwarning_ovl_destruct(Submenu* submenu) {
    submenu->overlay->cpwarning_ovl = NULL;
}
