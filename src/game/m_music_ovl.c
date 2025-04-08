#include "m_music_ovl.h"

#include "m_tag_ovl.h"
#include "m_hand_ovl.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_font.h"
#include "m_msg.h"
#include "sys_matrix.h"

static mMU_Ovl_c music_ovl_data;

static void mMU_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mMU_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    if (!menu_info->open_flag) {
        submenu->overlay->tag_ovl->chg_tag_func_proc(submenu, mTG_TABLE_MUSIC_MAIN, mTG_TYPE_NONE, 0, 0.0f, 0.0f);
        submenu->overlay->hand_ovl->set_hand_func(submenu);
        submenu->overlay->hand_ovl->info.pos[0] += 4.0f;
        submenu->overlay->hand_ovl->info.pos[1] += 5.0f;
        menu_info->open_flag = TRUE;
    }

    submenu->overlay->menu_control.tag_move_func(submenu, menu_info);
}

static void mMU_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    mSM_MenuInfo_c* next_menu = &submenu->overlay->menu_info[menu_info->next_menu_type];
    
    if (next_menu->proc_status == mSM_OVL_PROC_MOVE && next_menu->next_proc_status == mSM_OVL_PROC_END) {
        submenu->overlay->tag_ovl->init_tag_data_item_win_proc(submenu);
        menu_info->proc_status = mSM_OVL_PROC_PLAY;
    }
}

static void mMU_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

static void mMU_music_ovl_move(Submenu* submenu) {
    static mSM_MOVE_PROC ovl_move_proc[] = {
        // clang-format off
        mMU_move_Move,
        mMU_move_Play,
        mMU_move_Wait,
        (mSM_MOVE_PROC)none_proc1,
        mMU_move_End,
        // clang-format on
    };
    
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MUSIC];
    mSM_Control_c* ctrl = &submenu->overlay->menu_control;

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        ctrl->animation_flag = TRUE;
    } else {
        ctrl->animation_flag = FALSE;
    }
}

static int mMU_check_music_collect_bit(mActor_name_t item) {
    int ret = FALSE;

    if (ChkRoomMusicBox((u32)(item - ITM_MINIDISK_START))) {
        ret = TRUE;
    }

    return ret;
}

static int mMU_check_mark_flg(Submenu* submenu, mActor_name_t item) {
    mMU_Ovl_c* music = submenu->overlay->music_ovl;
    u32 idx = item - ITM_MINIDISK_START;
    int ret = FALSE;

    if (((music->mark_flg[(idx / 32) & 1] >> (idx & 31)) & 1) != 0) {
        ret = TRUE;
    }

    return ret;
}

static mActor_name_t mMU_get_md_no(Submenu* submenu) {
    mTG_Ovl_c* tag_ovl = submenu->overlay->tag_ovl;
    int idx;

    if (tag_ovl != NULL) {
        idx = tag_ovl->get_table_idx_proc(&tag_ovl->tags[0]);
    } else {
        idx = 0;
    }

    return ITM_MINIDISK_START + idx;
}

extern Gfx mus_win_model_before[];
extern Gfx mus_win_model[];
extern Gfx mus_win_ueT_model[];
extern Gfx mus_win_ue2T_model[];
extern Gfx mus_tag_nes_model[];
extern Gfx mus_icon_model_before[];
extern Gfx mus_icon_model[];
extern Gfx mus_mark_before[];
extern Gfx mus_mark_model[];

static void mMU_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    GRAPH* graph = game->graph;
    int i;
    int j;
    int frame;
    mActor_name_t md_item2;
    int k;
    mActor_name_t md_item;
    f32 tex_x;
    f32 tex_y;

    Matrix_scale(16.0f, 16.0f, 1.0f, 0);
    Matrix_translate(menu_info->position[0], menu_info->position[1], 140.0f, 1);

    OPEN_POLY_OPA_DISP(graph);
    
    gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, mus_win_model_before);
    
    // apply G_TEXTURE_IMAGE_FRAC
    tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
    tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
    i = (int)tex_x;
    j = (int)tex_y;
    gDPSetTileSize_Dolphin(POLY_OPA_DISP++, G_TX_RENDERTILE, (int)i & 0xFF, (int)j & 0xFF, 32, 32);
    
    gSPDisplayList(POLY_OPA_DISP++, mus_win_model);
    gSPDisplayList(POLY_OPA_DISP++, mus_win_ueT_model);
    gSPDisplayList(POLY_OPA_DISP++, mus_win_ue2T_model);
    gSPDisplayList(POLY_OPA_DISP++, mus_tag_nes_model);

    gSPDisplayList(POLY_OPA_DISP++, mus_icon_model_before);
    Matrix_scale(16.0f, 16.0f, 1.0f, 0);
    Matrix_translate(menu_info->position[0] - 100.0f, menu_info->position[1] + 28.0f, 140.0f, 1);

    for (j = 0, md_item = ITM_MINIDISK_START; j < mMU_ROW_NUM; j++) {
        for (i = 0; i < mMU_COL_NUM; i++) {
            if (mMU_check_music_collect_bit(md_item)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, mus_icon_model);
            }

            Matrix_translate(20.0f, 0.0f, 0.0f, 1);
            md_item++;
        }

        Matrix_translate(-220.0f, -20.0f, 0.0f, 1);
    }
    
    gSPDisplayList(POLY_OPA_DISP++, mus_mark_before);

    frame = game->frame_counter % 20;
    if (frame > 10) {
        frame = 20 - frame;
    }

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 255, 0, 95 + frame * 9, 0, 255);
    gDPSetEnvColor(POLY_OPA_DISP++, frame * 6, 210 + (frame * 9) / 2, frame * 6, 255);

    Matrix_scale(16.0f, 16.0f, 1.0f, 0);
    Matrix_translate(menu_info->position[0] - 100.0f, menu_info->position[1] + 28.0f, 140.0f, 1);

    for (j = 0, md_item2 = ITM_MINIDISK_START; j < mMU_ROW_NUM; j++) {
        for (i = 0; i < mMU_COL_NUM; i++) {
            if (mMU_check_mark_flg(submenu, md_item2)) {
                gSPMatrix(POLY_OPA_DISP++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_OPA_DISP++, mus_mark_model);
            }

            Matrix_translate(20.0f, 0.0f, 0.0f, 1);
            md_item2++;
        }

        Matrix_translate(-220.0f, -20.0f, 0.0f, 1);
    }

    CLOSE_POLY_OPA_DISP(graph);
}

static void mMU_set_title_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
    GRAPH* graph = game->graph;
    mMU_Ovl_c* music = submenu->overlay->music_ovl;
    mActor_name_t md_item = mMU_get_md_no(submenu);
    int len;

    if (md_item != music->title_md_item) {
        music->title_md_item = md_item;
        mem_clear(music->title, sizeof(music->title), CHAR_SPACE);
        if (mMU_check_music_collect_bit(md_item)) {
            mIN_copy_name_str(music->title, md_item);
        } else {
            mem_clear(music->title, 5, CHAR_QUESTIONMARK);
        }

        len = mMsg_Get_Length_String(music->title, sizeof(music->title));
        music->title_width = mFont_GetStringWidth(music->title, len, TRUE);
    }

    submenu->overlay->set_char_matrix_proc(graph);
    // clang-format off
    mFont_SetLineStrings(
        game,
        music->title, sizeof(music->title),
        menu_info->position[0] + (320 - music->title_width) * 0.5f, menu_info->position[1] + 55.0f,
        55, 255, 255, 255,
        FALSE, TRUE,
        1.0f, 1.0f,
        mFont_MODE_POLY
    );
    // clang-format on
}

static void mMU_music_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_MUSIC];

    menu_info->pre_draw_func(submenu, game);
    mMU_set_dl(submenu, menu_info, game);
    mMU_set_title_dl(submenu, menu_info, game);
    submenu->overlay->menu_control.tag_draw_func(submenu, game, mSM_OVL_MUSIC);
}

static void mMU_music_draw_init(mSM_MenuInfo_c* menu_info) {
    menu_info->proc_status = mSM_OVL_PROC_PLAY;
}

extern void mMU_music_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_Control_c* ctrl = &ovl->menu_control;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MUSIC];

    ctrl->menu_move_func = mMU_music_ovl_move;
    ctrl->menu_draw_func = mMU_music_ovl_draw;
    if (ovl->hand_ovl != NULL && menu_info->next_proc_status != mSM_OVL_PROC_END) {
        submenu->overlay->hand_ovl->set_hand_func(submenu);
    }
}

static void mMU_music_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_LEFT);
}

extern void mMU_music_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* ovl = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &ovl->menu_info[mSM_OVL_MUSIC];

    if (ovl->music_ovl == NULL) {
        mem_clear((u8*)&music_ovl_data, sizeof(music_ovl_data), 0);
        ovl->music_ovl = &music_ovl_data;
        mMU_music_draw_init(menu_info);
    }

    mMU_music_ovl_init(submenu, menu_info);
    mMU_music_ovl_set_proc(submenu);
}

extern void mMU_music_ovl_destruct(Submenu* submenu) {
    submenu->overlay->music_ovl = NULL;
}
