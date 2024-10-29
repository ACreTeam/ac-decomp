#include "m_cpedit_ovl.h"

#include "m_submenu_ovl.h"

static mCE_Ovl_c cpedit_ovl_data;

static void mCE_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_Move_proc(submenu, menu_info);
}

static void mCE_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    // empty
}

static void mCE_move_Wait(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    // empty
}

static void mCE_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    // empty
}

static void mCE_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_End_proc(submenu, menu_info);
}

typedef void (*mCE_OVL_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mCE_cpedit_ovl_move(Submenu* submenu) {
    static mCE_OVL_PROC ovl_move_proc[] = {
        &mCE_move_Move,
        &mCE_move_Play,
        &mCE_move_Wait,
        &mCE_move_Obey,
        &mCE_move_End,
    };
    
    mSM_Control_c* control = &submenu->overlay->menu_control;
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPEDIT];

    menu_info->pre_move_func(submenu);
    (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
    if (menu_info->proc_status == mSM_OVL_PROC_PLAY) {
        control->animation_flag = TRUE;
    } else {
        control->animation_flag = FALSE;
    }
}

static void mCE_cpedit_ovl_draw(Submenu* submenu, GAME* game) {
    mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_CPEDIT];

    menu_info->pre_draw_func(submenu, game);
}

extern void mCE_cpedit_ovl_set_proc(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;

    overlay->menu_control.menu_move_func = &mCE_cpedit_ovl_move;
    overlay->menu_control.menu_draw_func = &mCE_cpedit_ovl_draw;
}

static void mCE_cpedit_ovl_init(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
    submenu->overlay->move_chg_base_proc(menu_info, mSM_MOVE_IN_TOP);
}

extern void mCE_cpedit_ovl_construct(Submenu* submenu) {
    Submenu_Overlay_c* overlay = submenu->overlay;
    mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_CPEDIT];

    if (overlay->cpedit_ovl == NULL) {
        mem_clear((u8*)&cpedit_ovl_data, sizeof(cpedit_ovl_data), 0);
        overlay->cpedit_ovl = &cpedit_ovl_data;
    }

    mCE_cpedit_ovl_init(submenu, menu_info);
    mCE_cpedit_ovl_set_proc(submenu);
}

extern void mCE_cpedit_ovl_destruct(Submenu* submenu) {
    submenu->overlay->cpedit_ovl = NULL;
}
