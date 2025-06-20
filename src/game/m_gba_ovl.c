#include "m_gba_ovl.h"

#include "m_submenu_ovl.h"
#include "m_needlework_ovl.h"
#include "m_tag_ovl.h"
#include "sys_matrix.h"
#include "m_hand_ovl.h"
#include "m_common_data.h"
#include "m_malloc.h"

static u8 gb_ovl_change_flg = FALSE;

extern int mGB_get_change_flg(void) {
    return gb_ovl_change_flg;
}

extern int mGB_check_hide_flg(Submenu* submenu, int idx) {
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;

    if (idx < 0 || idx >= mNW_DESIGN_COUNT) {
        return FALSE;
    }

    return (gba_ovl->hide_flg & (u16)(1 << idx)) != 0;
}

extern int mGB_check_mark_flg(Submenu* submenu, int idx) {
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;

    if (idx < 0 || idx >= mNW_DESIGN_COUNT) {
        return FALSE;
    }

    return (gba_ovl->mark_flg & (u16)(1 << idx)) != 0;
}

extern void mGB_copy_image(Submenu* submenu, mActor_name_t rsv_gba, mActor_name_t rsv_nw) {
    int needlework_idx;
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;
    mNW_original_design_c* image_data;

    if (ITEM_IS_RSVNWORG(rsv_nw) == FALSE || ITEM_IS_RSVGBAORG(rsv_gba) == FALSE) {
        return;
    }

    needlework_idx = rsv_nw - RSV_NW_ORIGINAL0;
    image_data = mNW_get_image_data(submenu, needlework_idx);

    mNW_CopyOriginalTextureClass(image_data, &gba_ovl->original_p[rsv_gba - RSV_GBAORIGINAL0]);
    if (gba_ovl->original_design_table_no == needlework_idx) {
        gb_ovl_change_flg = TRUE;
    }
}

extern u8* mGB_get_image_name(Submenu* submenu, int idx) {
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;

    return gba_ovl->original_p[idx].name;
}

extern u16* mGB_get_image_pal(Submenu* submenu, int idx) {
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;
    int image_no = mNW_get_image_no(submenu, idx); // @cleanup - unused

    return mNW_PaletteIdx2Palette(gba_ovl->original_p[idx].palette);
}

extern u8* mGB_get_image_texture(Submenu* submenu, int idx) {
    mGB_Ovl_c* gba_ovl = submenu->overlay->gba_ovl;
    int image_no = mNW_get_image_no(submenu, idx); // @cleanup - unused

    return gba_ovl->original_p[idx].design.data;
}

extern Gfx inv_md_base_model_before[];
extern Gfx inv_md_base_model_a[];
extern Gfx inv_md_base_model_b[];

extern void mGB_draw_gba(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx, int shadow_flag) {
    if (scale < 0.05f) {
        return;
    }

    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mGB_get_image_texture(submenu, idx));
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mGB_get_image_pal(submenu, idx));

    if (shadow_flag) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 0, 0, 80);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 255, 255, 255);
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_before);
    gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_b);

    CLOSE_POLY_OPA_DISP(graph);
}

static void mGB_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mGB_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (!menu_info->open_flag) {
        menu_info->open_flag = TRUE;

        switch (menu_info->data0) {
            case mNW_OPEN_GBA:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_GBA, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
                break;
            case mNW_OPEN_CARD:
                submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_CARD, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
                break;
        }
    } else {
        submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
    }
}

static void mGB_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu_info->proc_status != mSM_OVL_PROC_MOVE) {
        return;
    }

    if (next_menu_info->next_proc_status != mSM_OVL_PROC_END) {
        return;
    }

    if (next_menu_info->menu_type != mSM_OVL_EDITENDCHK) {
        return;
    }

    if (next_menu_info->data1 == 0) {
        mNW_next_data(submenu);
        submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_LEFT);
    } else if (next_menu_info->data1 == 1) {
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    } else {
        submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_LEFT);
        gb_ovl_change_flg = FALSE;
    }
}

static void mGB_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mGB_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mGB_gba_ovl_move(Submenu* submenu) {
    static mGB_OVL_PROC ovl_move_proc[] = {
        &mGB_move_Move, &mGB_move_Play, &mGB_move_Wait, (mGB_OVL_PROC)&none_proc1, &mGB_move_End,
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_GBA];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx needlework_before_model[];
extern Gfx gba_win_w_before_model[];
extern Gfx gba_win_w1T_model[];
extern Gfx gba_win_w2T_model[];
extern Gfx gba_win_w3T_model[];
extern Gfx gba_win_w4T_model[];
extern Gfx gba_win_w5T_model[];
extern Gfx gba_win_w6T_model[];
extern Gfx gba_win_w7T_model[];
extern Gfx gba_win_w8T_model[];
extern Gfx gba_win_w9T_model[];
extern Gfx gba_win_w10T_model[];
extern Gfx gba_win_w11_model[];
extern Gfx gba_win_ueT_model[];
extern Gfx gba_win_waku_model[];
extern Gfx gba_win_mb_before_model[];
extern Gfx gba_win_f_model[];

extern Gfx gba_win_mb1_model[];
extern Gfx gba_win_mb2_model[];
extern Gfx gba_win_mb3_model[];
extern Gfx gba_win_mb4_model[];
extern Gfx gba_win_mb5_model[];
extern Gfx gba_win_mb6_model[];
extern Gfx gba_win_mb7_model[];
extern Gfx gba_win_mb8_model[];

extern Gfx agb_win_yajirushiT_model[];

static void mGB_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    static Gfx* gfx_table[] = {
        gba_win_mb1_model, gba_win_mb2_model, gba_win_mb3_model, gba_win_mb4_model,
        gba_win_mb5_model, gba_win_mb6_model, gba_win_mb7_model, gba_win_mb8_model,
    };
    GRAPH* graph = game->graph;
    int k;
    int idx;
    int j;
    int i;
    int tex_x;
    int tex_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, needlework_before_model);
    tex_x = 220.0f + -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = 360.0f + -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w_before_model);
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (u16)tex_x, (u16)tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w1T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w2T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w3T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w4T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w5T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w6T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w7T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w8T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w9T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w10T_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_w11_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_ueT_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_waku_model);
    gSPDisplayList(POLY_OPA_DISP++, gba_win_mb_before_model);

    for (k = 0; k < mNW_DESIGN_COUNT; k++) {
        if (!mGB_check_hide_flg(submenu, k)) {
            gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, mGB_get_image_pal(submenu, k));
            gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32,
                                       mGB_get_image_texture(submenu, k));
            gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, GX_CLAMP,
                               GX_CLAMP);
            gSPDisplayList(POLY_OPA_DISP++, gfx_table[k]);
        }
    }

    gSPDisplayList(POLY_OPA_DISP++, gba_win_f_model);

    if (menu_info->proc_status == mSM_OVL_PROC_WAIT || menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        gSPDisplayList(POLY_OPA_DISP++, agb_win_yajirushiT_model);
    }

    CLOSE_POLY_OPA_DISP(graph);

    mNW_draw_sav_mark_before(game);
    idx = 0;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 4; j++, idx++) {
            if (mGB_check_mark_flg(submenu, idx)) {
                Matrix_push();
                mNW_draw_sav_mark(game, -97 + j * 30, 6 + -i * 31);
                Matrix_pull();
            }
        }
    }
}

extern Gfx cad_win_mode[];
extern Gfx cad_win_model[];

static void mGB_set_card_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    GRAPH* graph = game->graph;
    int i;
    int tex_x;
    int tex_y;
    int idx;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, cad_win_mode);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (u16)tex_x, (u16)tex_y, 32, 32);
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mGB_get_image_pal(submenu, 0));
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mGB_get_image_texture(submenu, 0));
    gSPDisplayList(POLY_OPA_DISP++, cad_win_model);

    if (menu_info->proc_status == mSM_OVL_PROC_WAIT || menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        gSPDisplayList(POLY_OPA_DISP++, agb_win_yajirushiT_model);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

static void mGB_gba_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_GBA];

    (*menu_info->pre_draw_func)(submenu, game);

    switch (menu_info->data0) {
        case mNW_OPEN_GBA:
            mGB_set_frame_dl(submenu, game, menu_info);
            break;
        case mNW_OPEN_CARD:
            mGB_set_card_frame_dl(submenu, game, menu_info);
            break;
    }

    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_GBA);
}

extern void mGB_gba_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_GBA];

    overlay->menu_control.menu_move_func = &mGB_gba_ovl_move;
    overlay->menu_control.menu_draw_func = &mGB_gba_ovl_draw;
    if (overlay->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mGB_gba_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_GBA];
    mGB_Ovl_c* gba_ovl = overlay->gba_ovl;
    int i;
    int cloth_num;

    overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    menu_info->move_drt = mSM_MOVE_IN_LEFT;
    gba_ovl->original_design_table_no = 0xFF;
    gb_ovl_change_flg = FALSE;

    /* Only update if the player's shirt is a custom design */
    if (Now_Private->cloth.idx < 0x100) {
        return;
    }

    cloth_num = Now_Private->cloth.idx - 0x100;
    for (i = 0; i < mNW_DESIGN_COUNT; i++) {
        if (cloth_num == Now_Private->my_org_no_table[i]) {
            gba_ovl->original_design_table_no = i;
        }
    }
}

extern void mGB_gba_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    if (overlay->gba_ovl == NULL) {
        // @cleanup - why are we allocating 0xA20 bytes for the ovl when it's clearly only 0xC bytes?
        // maybe size is left over from an earlier iteration or scrapped content?
        overlay->gba_ovl = (mGB_Ovl_c*)zelda_malloc_align(0xA20, 32);
        mem_clear((u8*)overlay->gba_ovl, sizeof(mGB_Ovl_c), 0);
        overlay->gba_ovl->original_p = (mNW_original_design_c*)submenu->param2;
    }

    mGB_gba_ovl_init(submenu);
    mGB_gba_ovl_set_proc(submenu);
}

extern void mGB_gba_ovl_destruct(Submenu* submenu) {
    if (submenu->overlay->gba_ovl != NULL) {
        zelda_free(submenu->overlay->gba_ovl);
    }

    submenu->overlay->gba_ovl = NULL;
}
