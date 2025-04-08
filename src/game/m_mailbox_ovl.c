#include "m_mailbox_ovl.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_tag_ovl.h"
#include "m_player_lib.h"
#include "m_inventory_ovl.h"
#include "m_hand_ovl.h"

static mMB_Ovl_c mail_ovl_data;

static int mMB_get_last_mail_idx(void) {
    Mail_c* mail = &Common_Get(now_home)->mailbox[HOME_MAILBOX_SIZE];
    int idx = HOME_MAILBOX_SIZE;

    do {
        mail--;
        idx--;
    } while (mMl_check_not_used_mail(mail) && idx != 0);

    return idx;
}

static void mMB_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mMB_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (!menu_info->open_flag) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_MBOX, mTG_TYPE_NONE, mMB_get_last_mail_idx(), 0.0f, 0.0f);
        menu_info->open_flag = TRUE;
    }
    
    submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
}

static void mMB_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu = &submenu->overlay->menu_info[menu_info->next_menu_type];
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;

    if (next_menu->proc_status == mSM_OVL_PROC_MOVE && next_menu->next_proc_status == mSM_OVL_PROC_END) {
        if (next_menu->menu_type == mSM_OVL_BOARD) {
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_LEFT);
        } else if (next_menu->data1 == 0) {
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
            mailbox_ovl->open_flag = FALSE;
        } else {
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_LEFT);
            sAdo_SysTrgStart(SE_FLAG_15(NA_SE_ZOOMDOWN_SHORT));
        }
    }
}

static void mMB_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mPlib_request_main_mail_land_from_submenu();
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mMB_mailbox_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mMB_move_Move,
        mMB_move_Play,
        mMB_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mMB_move_End,
        // clang-format on
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MAILBOX];
    Submenu_Overlay_c* ovl = submenu->overlay;

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);

    switch (menu_info->proc_status) {
        case mSM_OVL_PROC_PLAY:
            ovl->menu_control.animation_flag = TRUE;
            break;
        case mSM_OVL_PROC_MOVE:
            ovl->menu_control.animation_flag = FALSE;
            break;
    }
}

extern Gfx pos_win_mode[];
extern Gfx pos_win_model[];
extern Gfx pos_yaji_wakuT_model[];

static void mMB_set_frame_dl(Submenu* submenu, GRAPH* graph, mSM_MenuInfo_c* menu_info, f32 pos_x, f32 pos_y) {
    int tex_x;
    int tex_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, 0);
    Matrix_translate(pos_x, pos_y, 140.0f, 1);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, pos_win_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPTileSync(POLY_OPA_DISP++);
    
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (u8)tex_x, (u8)tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, pos_win_model);
    
    if (submenu->overlay->mailbox_ovl->display_flag) {
        Matrix_translate(20.0f, 10.0f, 0.0f, 1);
        gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, pos_yaji_wakuT_model);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx inv_item_mode[];

static void mMB_set_mail(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y) {
    Mail_c* mail = Common_Get(now_home)->mailbox;
    mIV_Ovl_c* inv_ovl = submenu->overlay->inventory_ovl;
    mMB_Ovl_c* mailbox_ovl = submenu->overlay->mailbox_ovl;
    mTG_tag_c* tag = &submenu->overlay->tag_ovl->tags[0];
    int check;
    f32 scale;
    int i;
    u16 mark;
    int mark_flag;
    f32 pos[2];

    if (inv_ovl->remove_timer > 0 && (tag->table == mTG_TABLE_MBOX || mailbox_ovl->mark_flag == TRUE)) {
        if (mailbox_ovl->mark_flag == TRUE) {
            mark = mailbox_ovl->mark_bitfield;
        } else {
            mark = (1 << submenu->overlay->tag_ovl->get_table_idx_proc(tag));
        }
    } else {
        mark = 0;
    }

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, inv_item_mode);

    CLOSE_POLY_OPA_DISP(graph);

    for (i = 0; i < HOME_MAILBOX_SIZE; i++) {
        if (mMl_check_not_used_mail(mail) != TRUE) {
            if ((mark & (1 << i)) != 0) {
                scale = inv_ovl->remove_timer / 24.0f;
            } else {
                scale = 1.0f;
            }

            if ((mailbox_ovl->mark_bitfield & (1 << i)) != 0 && mailbox_ovl->mark_flag == FALSE) {
                mark_flag = TRUE;
            } else {
                mark_flag = FALSE;
            }

            submenu->overlay->tag_ovl->set_hand_pos_proc(submenu, pos, mTG_TABLE_MBOX, i);
            submenu->overlay->draw_mail_proc(graph, pos_x + pos[0], pos_y + pos[1], scale, mail, TRUE, FALSE, mark_flag);
        }

        mail++;
    }
}

static void mMB_set_dl(GRAPH* graph, mSM_MenuInfo_c* menu_info, Submenu* submenu, GAME* game) {
    f32 pos_x = menu_info->position[0];
    f32 pos_y = menu_info->position[1];

    mMB_set_frame_dl(submenu, graph, menu_info, pos_x, pos_y);
    mMB_set_mail(submenu, graph, pos_x, pos_y);
    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_MAILBOX);
}

static void mMB_mailbox_ovl_draw(Submenu* submenu, GAME* game) {
    GRAPH* graph = game->graph;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MAILBOX];

    menu_info->pre_draw_func(submenu, game);
    mMB_set_dl(graph, menu_info, submenu, game);
}

extern void mMB_mailbox_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_Control_c* ctrl = &ovl->menu_control;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MAILBOX];

    ctrl->menu_move_func = mMB_mailbox_ovl_move;
    ctrl->menu_draw_func = mMB_mailbox_ovl_draw;
    if (ovl->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mMB_mailbox_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MAILBOX];
    mMB_Ovl_c* mailbox_ovl = ovl->mailbox_ovl;

    ovl->menu_control.animation_flag = FALSE;
    mailbox_ovl->mark_bitfield = 0;
    mailbox_ovl->mark_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->move_drt = mSM_MOVE_IN_LEFT;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    ovl->mailbox_ovl->open_flag = TRUE;
}

static void mMB_mailbox_ovl_data_init(Submenu* submenu) {
    mem_clear((u8*)submenu->overlay->mailbox_ovl, sizeof(mMB_Ovl_c), 0);
}

extern void mMB_mailbox_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;

    if (ovl->mailbox_ovl == NULL) {
        mem_clear((u8*)&mail_ovl_data, sizeof(mail_ovl_data), 0);
        ovl->mailbox_ovl = &mail_ovl_data;
        mMB_mailbox_ovl_data_init(submenu);
        submenu->overlay->mailbox_ovl->get_last_mail_idx_proc = mMB_get_last_mail_idx;
    }

    mMB_mailbox_ovl_init(submenu);
    mMB_mailbox_ovl_set_proc(submenu);
}

extern void mMB_mailbox_ovl_destruct(Submenu* submenu) {
    submenu->overlay->mailbox_ovl = NULL;
}
