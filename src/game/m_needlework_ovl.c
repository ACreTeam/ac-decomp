#include "m_needlework_ovl.h"

#include "m_submenu_ovl.h"
#include "m_common_data.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"
#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_malloc.h"

static int mNW_with_cporiginal_check(Submenu* submenu) {
    switch (submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK].data0) {
        case mNW_OPEN_CPORIGINAL:
        case mNW_OPEN_GBA:
        case mNW_OPEN_CARD:
            return TRUE;
        default:
            return FALSE;
    }
}

extern int mNW_check_hide_flg(Submenu* submenu, int idx) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (idx < 0 || idx >= mNW_DESIGN_COUNT) {
        return FALSE;
    }

    return (needlework_ovl->hide_flg & (u16)(1 << idx)) != 0;
}

extern void mNW_on_hide_flg(Submenu* submenu, int idx) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (idx < 0 || idx >= mNW_DESIGN_COUNT) {
        return;
    }

    needlework_ovl->hide_flg |= (u16)(1 << idx);
}

extern void mNW_clear_hide_flg(Submenu* submenu) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    needlework_ovl->hide_flg = 0;
}

extern int mNW_check_mark_flg(Submenu* submenu, int idx) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (idx < 0 || idx >= mNW_DESIGN_COUNT) {
        return FALSE;
    }

    return (needlework_ovl->mark_flg & (u16)(1 << idx)) != 0;
}

extern void mNW_clear_mark_flg(Submenu* submenu) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    needlework_ovl->mark_flg = 0;
}

extern void mNW_swap_image_no(Submenu* submenu, int idx0, int idx1) {
    u8* org_table = Now_Private->my_org_no_table;
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    int temp_idx;

    if (idx0 < 0 || idx0 >= mNW_DESIGN_COUNT) {
        return;
    }

    if (idx1 < 0 || idx1 >= mNW_DESIGN_COUNT) {
        return;
    }

    if (mNW_with_cporiginal_check(submenu)) {
        org_table = needlework_ovl->my_org_no_table;
    }

    temp_idx = org_table[idx0];
    org_table[idx0] = org_table[idx1];
    org_table[idx1] = temp_idx;
}

extern u8 mNW_get_image_no(Submenu* submenu, int idx) {
    if (submenu->overlay != NULL) {
        if (submenu->overlay->needlework_ovl != NULL && mNW_with_cporiginal_check(submenu)) {
            return submenu->overlay->needlework_ovl->my_org_no_table[idx];
        }
    }

    return Now_Private->my_org_no_table[idx];
}

extern u16* mNW_get_image_pal(Submenu* submenu, int idx) {
    int image_no = mNW_get_image_no(submenu, idx);
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (mNW_with_cporiginal_check(submenu)) {
        return mNW_PaletteIdx2Palette(needlework_ovl->my_org[image_no].palette);
    }

    return mNW_PaletteIdx2Palette(Now_Private->my_org[image_no & 7].palette);
}

extern u8* mNW_get_image_texture(Submenu* submenu, int idx) {
    int image_no = mNW_get_image_no(submenu, idx);
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (mNW_with_cporiginal_check(submenu)) {
        return needlework_ovl->my_org[image_no].design.data;
    }

    return Now_Private->my_org[image_no & 7].design.data;
}

extern u8* mNW_get_image_name(Submenu* submenu, int idx) {
    int image_no = mNW_get_image_no(submenu, idx);
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (mNW_with_cporiginal_check(submenu)) {
        return needlework_ovl->my_org[image_no].name;
    }

    return Now_Private->my_org[image_no & 7].name;
}

extern mNW_original_design_c* mNW_get_image_data(Submenu* submenu, int idx) {
    int image_no = mNW_get_image_no(submenu, idx);
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;

    if (mNW_with_cporiginal_check(submenu)) {
        return &needlework_ovl->my_org[image_no];
    }

    return &Now_Private->my_org[image_no & 7];
}

extern Gfx inv_md_base_model_before[];
extern Gfx inv_md_base_model_a[];
extern Gfx inv_md_base_model_b[];

extern void mNW_draw_original(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx,
                              int shadow_flag) {
    if (scale < 0.05f) {
        return;
    }

    OPEN_POLY_OPA_DISP(graph);

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(pos_x, pos_y, 140.0f, MTX_MULT);
    Matrix_scale(scale, scale, 1.0f, MTX_MULT);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(POLY_OPA_DISP++, ANIME_1_TXT_SEG, mNW_get_image_texture(submenu, idx));
    gSPSegment(POLY_OPA_DISP++, ANIME_2_TXT_SEG, mNW_get_image_pal(submenu, idx));

    if (shadow_flag) {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 0, 0, 80);
    } else {
        gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 255, 255, 255, 255);
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_before);

    if (submenu->overlay->cporiginal_ovl == NULL) {
        gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_a);
    } else {
        gSPDisplayList(POLY_OPA_DISP++, inv_md_base_model_b);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

extern void mNW_next_data(Submenu* submenu) {
    mNW_Ovl_c* needlework_ovl = submenu->overlay->needlework_ovl;
    int i;

    bcopy(needlework_ovl->my_org_no_table, Now_Private->my_org_no_table, mNW_DESIGN_COUNT * sizeof(u8));
    for (i = 0; i < mNW_DESIGN_COUNT; i++) {
        mNW_CopyOriginalTextureClass(&Now_Private->my_org[i], &needlework_ovl->my_org[i]);
    }
}

static void mNW_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mNW_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (!menu_info->open_flag) {
        mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
        mTG_tag_c* tag = tag_ovl->tags;
        int i;

        for (i = 0; i < mTG_TAG_NUM; i++, tag++) {
            tag->type = mTG_TYPE_NONE;
        }

        tag_ovl->sel_tag_idx = -1;
        tag_ovl->ret_tag_idx = -1;

        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_NEEDLEWORK, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
        submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        if (menu_info->data0 == mNW_OPEN_INV) {
            submenu->overlay->hand_ovl->set_hand_func(submenu);
        }
        menu_info->open_flag = TRUE;
    }
    submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
}

static void mNW_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu_info = &submenu->overlay->menu_info[menu_info->next_menu_type];

    if (next_menu_info->proc_status != mSM_OVL_PROC_MOVE) {
        return;
    }

    if (next_menu_info->next_proc_status != mSM_OVL_PROC_END) {
        return;
    }

    switch (menu_info->next_menu_type) {
        case mSM_OVL_CPORIGINAL:
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_LEFT);
            break;
        case mSM_OVL_GBA:
            submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_OUT_RIGHT);
            break;
        case mSM_OVL_DESIGN:
        default:
            submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
            menu_info->proc_status = mSM_OVL_PROC_PLAY;
            break;
    }
}

static void mNW_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mNW_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mNW_needlework_ovl_move(Submenu* submenu) {
    static mNW_OVL_PROC ovl_move_proc[] = {
        &mNW_move_Move, &mNW_move_Play, &mNW_move_Wait, (mNW_OVL_PROC)&none_proc1, &mNW_move_End,
    };

    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK];

    (*menu_info->pre_move_func)(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx needlework_before_model[];
extern Gfx inv_original_w_model_before[];
extern Gfx inv_original_w1T_model[];
extern Gfx inv_original_w2T_model[];
extern Gfx inv_original_w3T_model[];
extern Gfx inv_original_w4T_model[];
extern Gfx inv_original_w5T_model[];
extern Gfx inv_original_w6T_model[];
extern Gfx inv_original_w7T_model[];
extern Gfx inv_original_w8T_model[];
extern Gfx inv_original_w9_model[];
extern Gfx inv_original_ueT_model[];
extern Gfx inv_original_waku_model[];
extern Gfx inv_original_mb_before_model[];
extern Gfx inv_original_f_model[];

extern Gfx inv_original_mb1_model[];
extern Gfx inv_original_mb2_model[];
extern Gfx inv_original_mb3_model[];
extern Gfx inv_original_mb4_model[];
extern Gfx inv_original_mb5_model[];
extern Gfx inv_original_mb6_model[];
extern Gfx inv_original_mb7_model[];
extern Gfx inv_original_mb8_model[];

static void mNW_set_frame_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    static Gfx* gfx_table[] = {
        inv_original_mb1_model, inv_original_mb2_model, inv_original_mb3_model, inv_original_mb4_model,
        inv_original_mb5_model, inv_original_mb6_model, inv_original_mb7_model, inv_original_mb8_model,
    };
    GRAPH* graph = game->graph;
    int i;
    int tex_y;
    int tex_x;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    if (menu_info->data0 == mNW_OPEN_INV) {
        Matrix_translate(46.0f, 0.0f, 0.0f, MTX_MULT);
    } else if (menu_info->data0 == mNW_OPEN_DESIGN) {
        Matrix_translate(10.0f, 0.0f, 0.0f, MTX_MULT);
    }

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, needlework_before_model);
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w_model_before);
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, tex_x, tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w1T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w2T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w3T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w4T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w5T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w6T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w7T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w8T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w9_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_ueT_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_waku_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_mb_before_model);

    for (i = 0; i < mNW_DESIGN_COUNT; i++) {
        if (!mNW_check_hide_flg(submenu, i)) {
            gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, mNW_get_image_pal(submenu, i));
            gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32,
                                       mNW_get_image_texture(submenu, i));
            gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, GX_CLAMP,
                               GX_CLAMP);
            gSPDisplayList(POLY_OPA_DISP++, gfx_table[i]);
        }
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_original_f_model);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx sav_mark_winT_before_model[];

extern void mNW_draw_sav_mark_before(GAME* game) {
    GRAPH* graph = game->graph;
    int g;
    int prim_g;
    int env_g;

    OPEN_POLY_OPA_DISP(graph);

    gSPDisplayList(POLY_OPA_DISP++, sav_mark_winT_before_model);
    g = game->frame_counter % 40;
    if (g > 20) {
        g = 40 - g;
    }

    prim_g = g * 9;
    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 95 + prim_g / 2, 0, 255);
    env_g = g * 3;
    gDPSetEnvColor(POLY_OPA_DISP++, env_g, 210 + g * 2, env_g, 255);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx sav_mark_winT_model[];

extern void mNW_draw_sav_mark(GAME* game, int x, int y) {
    GRAPH* graph = game->graph;
    int g;

    OPEN_POLY_OPA_DISP(graph);

    Matrix_translate((f32)x, (f32)y, 0.0f, MTX_MULT);
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, sav_mark_winT_model);

    CLOSE_POLY_OPA_DISP(graph);
}

extern Gfx inv_original2_w1T_model[];
extern Gfx inv_original2_w2T_model[];
extern Gfx inv_original2_w3T_model[];
extern Gfx inv_original2_w4T_model[];
extern Gfx inv_original2_w5T_model[];
extern Gfx inv_original2_w6T_model[];
extern Gfx inv_original2_w7T_model[];
extern Gfx inv_original2_w8T_model[];
extern Gfx inv_original2_w9_model[];
extern Gfx inv_original2_ueT_model[];
extern Gfx inv_original2_waku_model[];
extern Gfx inv_original2_f_model[];

extern Gfx inv_original2_mb1_model[];
extern Gfx inv_original2_mb2_model[];
extern Gfx inv_original2_mb3_model[];
extern Gfx inv_original2_mb4_model[];
extern Gfx inv_original2_mb5_model[];
extern Gfx inv_original2_mb6_model[];
extern Gfx inv_original2_mb7_model[];
extern Gfx inv_original2_mb8_model[];

static void mNW_set_frame_dl_cpo(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
    static Gfx* gfx_table[] = {
        inv_original2_mb1_model, inv_original2_mb2_model, inv_original2_mb3_model, inv_original2_mb4_model,
        inv_original2_mb5_model, inv_original2_mb6_model, inv_original2_mb7_model, inv_original2_mb8_model,
    };
    static s16 mark_table_x[] = { -88, -56, -88, -56, -88, -56, -88, -56 };
    static s16 mark_table_y[] = { 45, 45, 16, 16, -13, -13, -42, -42 };
    GRAPH* graph = game->graph;
    int i;
    int tex_y;
    int tex_x;
    int j;

    Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, MTX_MULT);

    switch (menu_info->data0) {
        case mNW_OPEN_GBA:
        case mNW_OPEN_CARD:
            Matrix_translate(136.0f, -5.0f, 0.0f, MTX_MULT);
            break;
    }

    OPEN_POLY_OPA_DISP(graph);

    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, needlework_before_model);
    tex_x = (int)(-submenu->overlay->menu_control.texture_pos[0] * 4.0f);
    tex_y = (int)(-submenu->overlay->menu_control.texture_pos[1] * 4.0f);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_w_model_before);
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, tex_x, tex_y, 32, 32);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w1T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w2T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w3T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w4T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w5T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w6T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w7T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w8T_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_w9_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_ueT_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original2_waku_model);
    gSPDisplayList(POLY_OPA_DISP++, inv_original_mb_before_model);

    for (i = 0; i < mNW_DESIGN_COUNT; i++) {
        if (!mNW_check_hide_flg(submenu, i)) {
            gDPLoadTLUT_Dolphin(POLY_OPA_DISP++, 15, 16, 1, mNW_get_image_pal(submenu, i));
            gDPSetTextureImage_Dolphin(POLY_OPA_DISP++, G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32,
                                       mNW_get_image_texture(submenu, i));
            gDPSetTile_Dolphin(POLY_OPA_DISP++, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, GX_CLAMP,
                               GX_CLAMP);
            gSPDisplayList(POLY_OPA_DISP++, gfx_table[i]);
        }
    }

    gSPDisplayList(POLY_OPA_DISP++, inv_original2_f_model);

    CLOSE_POLY_OPA_DISP(graph);

    mNW_draw_sav_mark_before(game);
    for (j = 0; j < mNW_DESIGN_COUNT; j++) {
        if (mNW_check_mark_flg(submenu, j)) {
            Matrix_push();
            mNW_draw_sav_mark(game, mark_table_x[j], mark_table_y[j]);
            Matrix_pull();
        }
    }
}

static void mNW_needlework_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK];

    (*menu_info->pre_draw_func)(submenu, game);

    switch (menu_info->data0) {
        case mNW_OPEN_CPORIGINAL:
        case mNW_OPEN_GBA:
        case mNW_OPEN_CARD:
            mNW_set_frame_dl_cpo(submenu, game, menu_info);
            break;
        default:
            mNW_set_frame_dl(submenu, game, menu_info);
            break;
    }

    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_NEEDLEWORK);
}

extern void mNW_needlework_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK];

    overlay->menu_control.menu_move_func = &mNW_needlework_ovl_move;
    overlay->menu_control.menu_draw_func = &mNW_needlework_ovl_draw;
    if (submenu->param0 != 1 && overlay->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mNW_needlework_ovl_init(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_NEEDLEWORK];
    int i;

    overlay->menu_control.animation_flag = FALSE;
    menu_info->proc_status = mSM_OVL_PROC_MOVE;
    menu_info->next_proc_status = mSM_OVL_PROC_PLAY;
    mem_clear((u8*)overlay->needlework_ovl, sizeof(mNW_Ovl_c), 0);
    bcopy(Now_Private->my_org, overlay->needlework_ovl->my_org, sizeof(Now_Private->my_org));

    for (i = 0; i < mNW_DESIGN_COUNT; i++) {
        DCStoreRangeNoSync(overlay->needlework_ovl->my_org[i].design.data, mNW_DESIGN_TEX_SIZE);
    }

    bcopy(Now_Private->my_org_no_table, overlay->needlework_ovl->my_org_no_table, mNW_DESIGN_COUNT * sizeof(u8));

    switch (menu_info->data0) {
        case mNW_OPEN_CPORIGINAL:
            menu_info->move_drt = mSM_MOVE_IN_LEFT;
            menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
            mSM_open_submenu(submenu, mSM_OVL_CPORIGINAL, 2, 0);
            break;
        case mNW_OPEN_GBA:
            menu_info->move_drt = mSM_MOVE_IN_RIGHT;
            menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
            mSM_open_submenu_new(submenu, mSM_OVL_GBA, 3, 0, submenu->param2);
            break;
        case mNW_OPEN_CARD:
            menu_info->move_drt = mSM_MOVE_IN_RIGHT;
            menu_info->next_proc_status = mSM_OVL_PROC_WAIT;
            mSM_open_submenu_new(submenu, mSM_OVL_GBA, 4, 0, submenu->param2);
            break;
        default:
            menu_info->move_drt = mSM_MOVE_IN_RIGHT;
            break;
    }
}

extern void mNW_needlework_ovl_construct(Submenu* submenu) {
    mNW_Ovl_c** nw_ovl_p = &submenu->overlay->needlework_ovl;

    if (*nw_ovl_p == NULL) {
        *nw_ovl_p = (mNW_Ovl_c*)zelda_malloc_align(sizeof(mNW_Ovl_c), 32);
    }

    mNW_needlework_ovl_init(submenu);
    mNW_needlework_ovl_set_proc(submenu);
}

extern void mNW_needlework_ovl_destruct(Submenu* submenu) {
    mNW_Ovl_c* nw_ovl = submenu->overlay->needlework_ovl;

    if (nw_ovl != NULL) {
        zelda_free(nw_ovl);
    }

    submenu->overlay->needlework_ovl = NULL;
}
