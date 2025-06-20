#include "m_ledit_ovl.h"

#include "m_submenu_ovl.h"
#include "m_item_name.h"
#include "sys_matrix.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "m_common_data.h"
#include "m_debug.h"

static u8 mLE_player_title[16] = "Enter your name.";
static u8 mLE_country_title[18] = "Enter Destination.";
static u8 mLE_ephrase_title[16] = "Enter something!";
static u8 mLE_reset_title[7] = "Say it!";
static u8 mLE_request_title[15] = "Request a song!";
static u8 mLE_myoriginal_title[13] = "Enter a name.";
static u8 mLE_island_title[20] = "Enter a destination.";

typedef struct ledit_win_data_s {
    f32 edit_ofs[2];
    f32 edit_scale;
    f32 title_ofs[2];
    f32 title_scale;
    u8* title_str;
    int title_len;
    int edit_max;
    int edit_col_max;
    rgba_t edit_color;
    Gfx* gfx_mode;
    Gfx* gfx_model;
} mLE_win_data_c;

extern Gfx nam_win_mode[];
extern Gfx nam_win_model[];

extern Gfx mra_win_mode[];
extern Gfx mra_win_model[];

extern Gfx ephrase_win_mode[];
extern Gfx ephrase_win_model[];

extern Gfx rst_win_mode[];
extern Gfx rst_win_model[];

extern Gfx req_win_mode[];
extern Gfx req_win_model[];

extern Gfx dna_win_mode[];
extern Gfx dna_win_model[];

extern Gfx shi_win_mode[];
extern Gfx shi_win_model[];

// clang-format off
static mLE_win_data_c mLE_win_data[] = {
    {
        { 120.0f, 72.0f }, 1.0f,
        { 132.0f, 45.0f }, 0.875f,
        mLE_player_title, sizeof(mLE_player_title),
        PLAYER_NAME_LEN, 80, { 0, 0, 255, 255 },
        nam_win_mode, nam_win_model,
    },
    {
        { 118.0f, 74.0f }, 1.0f,
        { 134.0f, 43.0f }, 0.875f,
        mLE_country_title, sizeof(mLE_country_title),
        LAND_NAME_SIZE, 80, { 215, 15, 0, 255 },
        mra_win_mode, mra_win_model,
    },
    {
        { 100.0f, 76.0f }, 1.0f,
        { 134.0f, 45.0f }, 0.875f,
        mLE_ephrase_title, sizeof(mLE_ephrase_title),
        ANIMAL_CATCHPHRASE_LEN, 120, { 235, 75, 0, 255 },
        ephrase_win_mode, ephrase_win_model,
    },
    {
        { 79.0f, 79.0f }, 1.0f,
        { 154.0f, 43.0f }, 1.0f,
        mLE_reset_title, sizeof(mLE_reset_title),
        16, 160, { 85, 30, 235, 255 },
        rst_win_mode, rst_win_model,
    },
    {
        { 82.0f, 76.0f }, 1.0f,
        { 138.0f, 41.0f }, 0.875f,
        mLE_request_title, sizeof(mLE_request_title),
        mIN_ITEM_NAME_LEN, 160, { 50, 50, 235, 255 },
        req_win_mode, req_win_model,
    },
    {
        { 82.0f, 69.0f }, 1.0f,
        { 142.0f, 37.0f }, 0.875f,
        mLE_myoriginal_title, sizeof(mLE_myoriginal_title),
        mNW_ORIGINAL_DESIGN_NAME_LEN, 160, { 50, 40, 50, 255 },
        dna_win_mode, dna_win_model,
    },
    {
        { 118.0f, 75.0f }, 1.0f,
        { 121.0f, 40.0f }, 0.875f,
        mLE_island_title, sizeof(mLE_island_title),
        mISL_ISLAND_NAME_LEN, 80, { 175, 70, 40, 255 },
        shi_win_mode, shi_win_model,
    },
};
// clang-format on

static u8 mLE_md_name[MINIDISK_NUM][mIN_ITEM_NAME_LEN];
static u8 mLE_npc_end_word_edit[ANIMAL_CATCHPHRASE_LEN];

static void mLE_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mLE_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* editor_menu = &submenu->overlay->menu_info[mSM_OVL_EDITOR];
    Submenu_Item_c* item_p = submenu->item_p;

    if (editor_menu->next_proc_status == mSM_OVL_PROC_END) {
        submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_TOP);

        if (menu_info->data0 == mLE_TYPE_REQUEST) {
            mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
            u8* md_name_p = (u8*)mLE_md_name;
            int i;

            if (editor_ovl != NULL) {
                for (i = 0; i < MINIDISK_NUM; i++) {
                    if (mem_cmp(md_name_p, editor_ovl->input_str, mIN_ITEM_NAME_LEN)) {
                        item_p->item = ITM_MINIDISK_START + i;
                        break;
                    }

                    md_name_p += mIN_ITEM_NAME_LEN;
                }

                if (i == MINIDISK_NUM) {
                    item_p->item = ITM_MINIDISK_END; // @BUG - this is an invalid minidisk id!
                }
            } else {
                item_p->item = ITM_MINIDISK_END; // @BUG - this is an invalid minidisk id!
            }
        } else if (menu_info->data0 == mLE_TYPE_EPHRASE) {
            mem_copy((u8*)menu_info->data2, mLE_npc_end_word_edit, ANIMAL_CATCHPHRASE_LEN);
        }
    }
}

static void mLE_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mLE_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mLE_ledit_ovl_move(Submenu* submenu) {
    static mLE_OVL_PROC ovl_move_proc[] = {
        &mLE_move_Move,
        (mLE_OVL_PROC)&none_proc1,
        &mLE_move_Wait,
        (mLE_OVL_PROC)&none_proc1,
        &mLE_move_End,
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_LEDIT];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx ledit_common_mode[];
extern Gfx lat_sousa_spT_model[];

static void mLE_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
    mLE_win_data_c* data_p = &mLE_win_data[menu_info->data0];
    GRAPH* graph = game->graph;
    f32 pos_x = menu_info->position[0];
    f32 pos_y = menu_info->position[1];
    f32 edit_pos_x = data_p->edit_ofs[0] + pos_x;
    f32 edit_pos_y = data_p->edit_ofs[1] - pos_y;
    int tex_x;
    int tex_y;
    f32 text_pos_x;
    f32 text_pos_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, ledit_common_mode);
    gSPDisplayList(POLY_OPA_DISP++, data_p->gfx_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    gDPTileSync(POLY_OPA_DISP++);
    tex_x = (int)(-submenu->overlay->menu_control.texture_pos[0] * 2.0f) & 0x7F;
    tex_y = (int)(-submenu->overlay->menu_control.texture_pos[1] * 2.0f) & 0x7F;
    gDPSetTileSize(POLY_OPA_DISP++, G_TX_RENDERTILE, tex_x, tex_y, 124 + tex_x, 124 + tex_y);
    gSPDisplayList(POLY_OPA_DISP++, data_p->gfx_model);

    if (editor_ovl != NULL) {
        int i;

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, data_p->edit_color.r, data_p->edit_color.g, data_p->edit_color.b, 255);
        for (i = 0; i < editor_ovl->now_str_len; i++) { 
            if (editor_ovl->input_str[i] == CHAR_SPACE_3) {
                int width = mFont_GetStringWidth(editor_ovl->input_str, i, TRUE);

                Matrix_push();
                Matrix_translate(6.0f + (edit_pos_x - 160.0f) + (f32)width, -(8.0f + (edit_pos_y - 120.0f)), 0.0f, MTX_MULT);
                Matrix_scale(0.625f, 1.0f, 1.0f, MTX_MULT);
                
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, lat_sousa_spT_model);

                Matrix_pull();
            }
        }

        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    }

    CLOSE_POLY_OPA_DISP(graph);

    if (editor_ovl != NULL) {
        submenu->overlay->set_char_matrix_proc(graph);

        // clang-format off
        mFont_SetLineStrings(
            game,
            data_p->title_str, data_p->title_len,
            data_p->title_ofs[0] + pos_x, data_p->title_ofs[1] - pos_y,
            255, 255, 255, 255,
            FALSE,
            TRUE,
            data_p->title_scale, data_p->title_scale,
            mFont_MODE_POLY
        );
        // clang-format on

        // clang-format off
        mFont_SetLineStrings(
            game,
            editor_ovl->input_str, editor_ovl->input_length,
            edit_pos_x, edit_pos_y,
            data_p->edit_color.r, data_p->edit_color.g, data_p->edit_color.b, 255,
            FALSE,
            TRUE,
            data_p->edit_scale, data_p->edit_scale,
            mFont_MODE_POLY
        );
        // clang-format on

        // clang-format off
        edit_pos_x += ((f32)(int)GETREG(TAKREG, 10) - 7.0f) + (f32)(int)editor_ovl->_26 * data_p->edit_scale;
        submenu->overlay->editor_ovl->cursol_draw(
            submenu, game,
            edit_pos_x, edit_pos_y
        );
        // clang-format on
    }
}

static void mLE_ledit_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_LEDIT];

    menu_info->pre_draw_func(submenu, game);
    mLE_set_dl(submenu, game, menu_info);
}

extern void mLE_ledit_ovl_set_proc(Submenu* submenu) {
    mSM_Control_c* control = &submenu->overlay->menu_control;

    control->menu_move_func = &mLE_ledit_ovl_move;
    control->menu_draw_func = &mLE_ledit_ovl_draw;
}

static void mLE_ledit_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_LEDIT];
    int max;
    u8* str;

    overlay->menu_control.animation_flag = FALSE;
    if (menu_info->data0 == mLE_TYPE_PLAYER_NAME) {
        str = Now_Private->player_ID.player_name;
    } else if (menu_info->data0 == mLE_TYPE_COUNTRY_NAME) {
        str = Save_Get(land_info).name;
    } else if (menu_info->data0 == mLE_TYPE_EPHRASE) {
        str = mLE_npc_end_word_edit;
    } else {
        str = (u8*)menu_info->data2;

        if (menu_info->data0 == mLE_TYPE_REQUEST) {
            mem_copy((u8*)mLE_md_name, itemName_minidisk, sizeof(mLE_md_name));
        }
    }

    max = mLE_win_data[menu_info->data0].edit_max;
    mem_clear(str, max, CHAR_SPACE);
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
    menu_info->move_drt = mSM_MOVE_IN_TOP;
    
    mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_LEDIT, max, str, mLE_win_data[menu_info->data0].edit_col_max);
}

extern void mLE_ledit_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->le_exists == FALSE) {
        overlay->le_exists = TRUE;
    }

    mLE_ledit_ovl_init(submenu);
    mLE_ledit_ovl_set_proc(submenu);
}

extern void mLE_ledit_ovl_destruct(Submenu* submenu) {
    submenu->overlay->le_exists = FALSE;
}
