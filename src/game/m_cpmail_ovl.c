#include "m_cpmail_ovl.h"

#include "m_submenu_ovl.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_editEndChk_ovl.h"
#include "m_card.h"
#include "m_cpwarning_ovl.h"
#include "m_inventory_ovl.h"
#include "sys_matrix.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "m_common_data.h"
#include "m_malloc.h"

static mCM_Ovl_c cpmail_ovl_data;

typedef struct {
    Gfx* tag_gfx;
    Gfx* color_gfx;
    u16* pal_p;
    u8* tex_p;
    rgba_t title_color;
} mCM_disp_data_c;

extern Gfx ctl_win1_color_mode[];
extern Gfx ctl_win1_tagu1T_model[];
extern Gfx ctl_win1_tagu2T_model[];
extern Gfx ctl_win1_tagu3T_model[];
extern Gfx ctl_win1_tagu4T_model[];
extern Gfx ctl_win1_tagu5T_model[];
extern Gfx ctl_win1_tagu6T_model[];
extern Gfx ctl_win1_tagu7T_model[];
extern Gfx ctl_win1_tagu8T_model[];
extern Gfx ctl_win2_color_mode[];
extern Gfx ctl_win3_color_mode[];
extern Gfx ctl_win4_color_mode[];
extern Gfx ctl_win5_color_mode[];
extern Gfx ctl_win6_color_mode[];
extern Gfx ctl_win7_color_mode[];
extern Gfx ctl_win8_color_mode[];
extern u8 ctl_win_nuno1_tex_rgb_ci4[];
extern u16 ctl_win_nuno1_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno2_tex_rgb_ci4[];
extern u16 ctl_win_nuno2_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno3_tex_rgb_ci4[];
extern u16 ctl_win_nuno3_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno4_tex_rgb_ci4[];
extern u16 ctl_win_nuno4_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno5_tex_rgb_ci4[];
extern u16 ctl_win_nuno5_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno6_tex_rgb_ci4[];
extern u16 ctl_win_nuno6_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno7_tex_rgb_ci4[];
extern u16 ctl_win_nuno7_tex_rgb_ci4_pal[];
extern u8 ctl_win_nuno8_tex_rgb_ci4[];
extern u16 ctl_win_nuno8_tex_rgb_ci4_pal[];

static mCM_disp_data_c mCM_disp_data[8] = {
    {ctl_win1_tagu1T_model, ctl_win1_color_mode, ctl_win_nuno1_tex_rgb_ci4_pal, ctl_win_nuno1_tex_rgb_ci4, { 0x46, 0x28, 0x14, 0xFF } },
    {ctl_win1_tagu2T_model, ctl_win2_color_mode, ctl_win_nuno2_tex_rgb_ci4_pal, ctl_win_nuno2_tex_rgb_ci4, { 0x14, 0x3C, 0x5A, 0xFF } },
    {ctl_win1_tagu3T_model, ctl_win3_color_mode, ctl_win_nuno3_tex_rgb_ci4_pal, ctl_win_nuno3_tex_rgb_ci4, { 0x3C, 0x1E, 0x46, 0xFF } },
    {ctl_win1_tagu4T_model, ctl_win4_color_mode, ctl_win_nuno4_tex_rgb_ci4_pal, ctl_win_nuno4_tex_rgb_ci4, { 0x0A, 0x46, 0x32, 0xFF } },
    {ctl_win1_tagu5T_model, ctl_win5_color_mode, ctl_win_nuno5_tex_rgb_ci4_pal, ctl_win_nuno5_tex_rgb_ci4, { 0x46, 0x32, 0x14, 0xFF } },
    {ctl_win1_tagu6T_model, ctl_win6_color_mode, ctl_win_nuno6_tex_rgb_ci4_pal, ctl_win_nuno6_tex_rgb_ci4, { 0x3C, 0x32, 0x46, 0xFF } },
    {ctl_win1_tagu7T_model, ctl_win7_color_mode, ctl_win_nuno7_tex_rgb_ci4_pal, ctl_win_nuno7_tex_rgb_ci4, { 0x46, 0x14, 0x1E, 0xFF } },
    {ctl_win1_tagu8T_model, ctl_win8_color_mode, ctl_win_nuno8_tex_rgb_ci4_pal, ctl_win_nuno8_tex_rgb_ci4, { 0x32, 0x46, 0x0A, 0xFF } },
};

static void mCM_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mCM_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    
    if (menu_info->open_flag == FALSE) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_CPMAIL, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
        menu_info->open_flag = TRUE;
    } else if (cpmail_ovl->page_move_timer != 0) {   
        cpmail_ovl->page_move_timer--;
        menu_info->position[1] = 100.0f * sinf_table(cpmail_ovl->page_move_timer * DEG2RAD(4.5f));
        if (cpmail_ovl->page_move_timer == 20) {
            u8* page_order = cpmail_ovl->page_order;
            int i;
            
            for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++, page_order++) {
                if (*page_order == cpmail_ovl->next_page_id) {
                    break;
                }
            }

            for (i; i > 0; i--) {
                page_order[0] = page_order[-1];
                page_order--;
            }

            cpmail_ovl->page_order[0] = cpmail_ovl->next_page_id;
        } else if (cpmail_ovl->page_move_timer == 0) {
            menu_info->position[1] = 0.0f;
            submenu->overlay->hand_ovl->set_hand_func(submenu);
            submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        }
    } else {
        submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
    }
}

static void mCM_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu_info->proc_status == mSM_OVL_PROC_MOVE && next_menu_info->next_proc_status == mSM_OVL_PROC_END) {
        if (next_menu_info->menu_type == mSM_OVL_EDITENDCHK) {
            if (next_menu_info->data1 == 0) {
                mCD_save_data_main_to_aram(cpmail_ovl->card_mail, mCD_KEEP_MAIL_SIZE, mCD_ARAM_DATA_MAIL);
                submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
            } else if (next_menu_info->data1 == 1) {
                menu_info->proc_status = mSM_OVL_PROC_PLAY;
            } else {
                cpmail_ovl->_BB3 = 1;
                submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
            }
        } else if (next_menu_info->menu_type == mSM_OVL_EDITOR) {
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
        } else if (next_menu_info->menu_type == mSM_OVL_BOARD) {
            menu_info->proc_status = mSM_OVL_PROC_MOVE;
            menu_info->move_drt = mSM_MOVE_IN_LEFT;
            menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
        }
    }
}

static void mCM_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mCM_OVL_MOVE_PROC)(Submenu* submenu, mSM_MenuInfo_c* menu_info);

static void mCM_cpmail_ovl_move(Submenu* submenu) {
    static mCM_OVL_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mCM_move_Move,
        mCM_move_Play,
        mCM_move_Wait,
        (mCM_OVL_MOVE_PROC)none_proc1,
        mCM_move_End,
        // clang-format on
    };

    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_CPMAIL];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        ovl->menu_control.animation_flag = TRUE;
    } else {
        ovl->menu_control.animation_flag = FALSE;
    }
}

extern Gfx inv_item_mode[];

static void mCM_set_mail(Submenu* submenu, GRAPH* graph, float pos_x, float pos_y, int page_num) {
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    Mail_c* mail = cpmail_ovl->card_mail->mail[page_num];
    int i;
    int mark_bitfield = 0;
    int mark_flag;
    float pos[2];
    float scale;

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);

    CLOSE_POLY_OPA_DISP(graph);

    if (inv_ovl != NULL && inv_ovl->remove_timer > 0 && (tag->table == mTG_TABLE_CPMAIL || cpmail_ovl->mark_flag == TRUE)) {
        if (cpmail_ovl->mark_flag == TRUE) {
            mark_bitfield = cpmail_ovl->mark_bitfield;
        } else if (cpmail_ovl->mark_flag == FALSE) {
            mark_bitfield = 1 << submenu->overlay->tag_ovl->get_table_idx_proc(tag);
        }
    }

    for (i = 0; i < mCD_KEEP_MAIL_COUNT; i++) {
        if ((cpmail_ovl->mark_bitfield2 & (1 << i)) == 0 && mMl_check_not_used_mail(mail) != TRUE) {
            if ((mark_bitfield & (1 << i)) != 0) {
                scale = inv_ovl->remove_timer * (1.0f / 24.0f);
            } else {
                scale = 1.0f;
            }

            if ((cpmail_ovl->mark_bitfield & (1 << i)) != 0 && cpmail_ovl->mark_flag == FALSE) {
                mark_flag = TRUE;
            } else {
                mark_flag = FALSE;
            }

            submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, mTG_TABLE_CPMAIL, i);
            submenu->overlay->draw_mail_proc(graph, pos_x + pos[0], pos_y + pos[1], scale, mail, TRUE, FALSE, mark_flag);
        }

        mail++;
    }
}

static float mCM_get_page_posY(Submenu* submenu, mSM_MenuInfo_c* menu_info, int page_num) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    
    if (cpmail_ovl->page_move_timer == 0 || page_num == cpmail_ovl->next_page_id) {
        return menu_info->position[1];
    } else {
        return -menu_info->position[1];
    }
}

extern Gfx ctl_tag_mode[];
extern Gfx ctl_win_mode[];
extern Gfx ctl_win_model[];
extern Gfx ctl_win1_kageT_model[];
extern Gfx ctl_sentaku_taguT_model[];

static void mCM_set_page_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game, GRAPH* graph, int page_num, int flag) {
    mCM_disp_data_c* disp_data_p = &mCM_disp_data[page_num];
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    float pos_x = menu_info->position[0];
    float pos_y = mCM_get_page_posY(submenu, menu_info, page_num);
    int tex_x;
    int tex_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, disp_data_p->color_gfx);

    if (flag) {
        gSPDisplayList(POLY_OPA_DISP++, ctl_win_mode);
        gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 14, 16, 1, disp_data_p->pal_p);
        gDPLoadTextureBlock_4b_Dolphin(POLY_OPA_DISP++, disp_data_p->tex_p, G_IM_FMT_CI, 32, 32, 14, GX_REPEAT, GX_REPEAT, 0, 0);
        gDPTileSync(POLY_OPA_DISP++);
        
        tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
        tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
        gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (u8)tex_x, (u8)tex_y, 32, 32);
        gSPDisplayList(POLY_OPA_DISP++, ctl_win_model);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, ctl_tag_mode);
    }

    gSPDisplayList(POLY_OPA_DISP++, disp_data_p->tag_gfx);

    if (flag) {
        gSPDisplayList(POLY_OPA_DISP++, ctl_win1_kageT_model);
    }

    if (cpmail_ovl->next_page_id == page_num) {
        Matrix_translate(97.0f, 51.0f - 15.0f * page_num, 0.0f, MTX_MULT);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, ctl_sentaku_taguT_model);
    }

    CLOSE_POLY_OPA_DISP(graph);

    if (flag) {
        float str_x;
        float str_y;
        int len;

        mCM_set_mail(submenu, graph, pos_x, pos_y, page_num);
        submenu->overlay->set_char_matrix_proc(graph);

        str_x = 160.0f + pos_x + 24.0f;

        if (menu_info->proc_status == mSM_OVL_PROC_WAIT && menu_info->next_menu_type == mSM_OVL_EDITOR) {
            mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
            
            len = mCD_KEEP_MAIL_FOLDER_NAME_LEN;
            if (editor_ovl != NULL) {
                str_x -= editor_ovl->line_width * 0.5f;
            }
        } else {
            len = mMl_strlen(cpmail_ovl->card_mail->folder_names[page_num], mCD_KEEP_MAIL_FOLDER_NAME_LEN, CHAR_SPACE);
            str_x -= mFont_GetStringWidth(cpmail_ovl->card_mail->folder_names[page_num], len, TRUE) * 0.5f;
        }

        str_y = 120.0f - ((pos_y + 84.0f) - 5.0f);
        mFont_SetLineStrings(
            // clang-format off
            game,
            cpmail_ovl->card_mail->folder_names[page_num], len,
            str_x, str_y,
            disp_data_p->title_color.r, disp_data_p->title_color.g, disp_data_p->title_color.b, 255,
            FALSE, TRUE,
            1.0f, 1.0f,
            mFont_MODE_POLY
            // clang-format on
        );

        if (menu_info->proc_status == mSM_OVL_PROC_WAIT && menu_info->next_menu_type == mSM_OVL_EDITOR) {
            mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
            
            if (editor_ovl != NULL) {
                editor_ovl->cursol_draw(submenu, game, str_x + editor_ovl->_26 + -6.0f, str_y);
            }
        }
    }
}

static void mCM_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    GRAPH* graph = game->graph;
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    int i;
    int flag;
    u8* page_order_p = &cpmail_ovl->page_order[mCD_KEEP_MAIL_PAGE_COUNT - 1];

    for (i = mCD_KEEP_MAIL_PAGE_COUNT - 1; i >= 0; i--, page_order_p--) {
        if (i == 0 || *page_order_p == cpmail_ovl->next_page_id || (i == 1 && page_order_p[-1] == cpmail_ovl->next_page_id)) {
            flag = TRUE;
        } else {
            flag = FALSE;
        }

        mCM_set_page_dl(submenu, menu_info, game, graph, *page_order_p, flag);
    }

    if (cpmail_ovl->page_move_timer == 0) {
        submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_CPMAIL);
    }
}

static void mCM_cpmail_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPMAIL];

    if (submenu->overlay->cpmail_ovl != NULL) {
        menu_info->pre_draw_func(submenu, game);
        mCM_set_dl(submenu, menu_info, game);
    }
}

static void mCM_cpmail_draw_init(mSM_MenuInfo_c* menu_info) {
#if VERSION < VER_GAFU01_00
    mCM_disp_data_c* disp_data_p = &mCM_disp_data[0];
    int i;

    for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++) {
        disp_data_p->color_gfx = (Gfx*)disp_data_p->color_gfx;
        disp_data_p->pal_p = (u16*)disp_data_p->pal_p;
        disp_data_p->tex_p = (u8*)disp_data_p->tex_p;
        disp_data_p++;
    }
#endif
}

extern void mCM_cpmail_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_Control_c* ctrl = &ovl->menu_control;

    ctrl->menu_move_func = mCM_cpmail_ovl_move;
    ctrl->menu_draw_func = mCM_cpmail_ovl_draw;
    if (ovl->hand_ovl != NULL && ovl->menu_info[mSM_OVL_CPMAIL].next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mCM_cpmail_load_memory(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    
    mCD_save_data_aram_to_main(cpmail_ovl->card_mail, mCD_KEEP_MAIL_SIZE, mCD_ARAM_DATA_MAIL);
}

static void mCM_cpmail_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    Mail_c* player_mail = cpmail_ovl->player_mail;
    Mail_c* mail = Now_Private->mail;
    u8* page_order_p;
    u8* title_p;
    int i;

    for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
        mMl_copy_mail(player_mail, mail);
        player_mail++;
        mail++;
    }

    page_order_p = cpmail_ovl->page_order;
    for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++, page_order_p++) {
        *page_order_p = i;
    }

    mail = cpmail_ovl->card_mail->mail[0];
    for (i = 0; i < mCD_KEEP_MAIL_COUNT * mCD_KEEP_MAIL_PAGE_COUNT; i++) {
        mMl_clear_mail(mail);
        mail++;
    }

    title_p = cpmail_ovl->card_mail->folder_names[0];
    for (i = 0; i < mCD_KEEP_MAIL_PAGE_COUNT; i++) {
        mem_clear(title_p, mCD_KEEP_MAIL_FOLDER_NAME_LEN, CHAR_SPACE);
        title_p += mCD_KEEP_MAIL_FOLDER_NAME_LEN;
    }

    cpmail_ovl->_BB3 = 0;
    mCM_cpmail_load_memory(submenu, menu_info);
    submenu->item_p->slot_no = 1;
    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_RIGHT);
}

extern void mCM_cpmail_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_CPMAIL];

    if (ovl->cpmail_ovl == NULL) {
        mem_clear((u8*)&cpmail_ovl_data, sizeof(cpmail_ovl_data), 0);
        ovl->cpmail_ovl = &cpmail_ovl_data;
        cpmail_ovl_data.card_mail = (mCD_keep_mail_c*)zelda_malloc_align(mCD_KEEP_MAIL_SIZE, 32);
        mem_clear((u8*)cpmail_ovl_data.card_mail, mCD_KEEP_MAIL_SIZE, 0);
        mCM_cpmail_draw_init(menu_info);
    }

    mCM_cpmail_ovl_init(submenu, menu_info);
    mCM_cpmail_ovl_set_proc(submenu);
}

extern void mCM_cpmail_ovl_destruct(Submenu* submenu) {
    mCM_Ovl_c* cpmail_ovl = submenu->overlay->cpmail_ovl;
    Mail_c* player_mail;
    Mail_c* mail;
    int i;

    if (cpmail_ovl->_BB3 != 0) {
        mail = Now_Private->mail;
        player_mail = cpmail_ovl->player_mail;
        for (i = 0; i < mPr_INVENTORY_MAIL_COUNT; i++) {
            mMl_copy_mail(mail, player_mail);
            player_mail++;
            mail++;
        }
    }

    if (cpmail_ovl_data.card_mail != NULL) {
        zelda_free(cpmail_ovl_data.card_mail);
        cpmail_ovl_data.card_mail = NULL;
    }

    submenu->overlay->cpmail_ovl = NULL;
}
