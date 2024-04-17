#ifndef M_SUBMENU_OVL_H
#define M_SUBMENU_OVL_H

#include "types.h"
#include "m_submenu_ovl_h.h"
#include "m_submenu.h"
#include "graph.h"
#include "m_mail.h"
#include "PR/mbi.h"
#include "PreRender.h"
#include "m_map_ovl_h.h"
#include "m_bank_ovl_h.h"
#include "m_music_ovl_h.h"
#include "m_warning_ovl_h.h"
#include "m_editor_ovl_h.h"
#include "m_passwordChk_ovl_h.h"
#include "m_passwordMake_ovl_h.h"
#include "m_board_ovl_h.h"
#include "m_diary_ovl_h.h"
#include "m_address_ovl_h.h"
#include "m_editEndChk_h.h"
#include "m_haniwaPortrait_ovl_h.h"
#include "m_timeIn_ovl_h.h"
#include "m_repay_ovl_h.h"
#include "m_notice_ovl_h.h"
#include "m_birthday_ovl_h.h"
#include "m_tag_ovl_h.h"
#include "m_catalog_ovl_h.h"
#include "m_hand_ovl_h.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mSM_OVL_PROC_MOVE,
    mSM_OVL_PROC_PLAY,
    mSM_OVL_PROC_WAIT,
    mSM_OVL_PROC_OBEY,
    mSM_OVL_PROC_END,

    mSM_OVL_PROC_NUM
};

// TODO: fill this out
typedef struct submenu_segment_s {
    u8 _00[0x54];
} mSM_Segment_c;

typedef struct submenu_menu_info_s {
    int menu_type;
    int proc_status;

    int pre_menu_type;
    SUBMENU_PROC pre_move_func;
    SUBMENU_GAME_PROC pre_draw_func;

    int next_menu_type;

    f32 position[2];
    f32 speed[2];

    char* _28;
    int _2C;

    int next_proc_status;
    s16 move_drt;
    u16 _36;

    int data0;
    int data1;
    void* data2;
    int data3;
} mSM_MenuInfo_c;

typedef void (*mSM_HAND_MOVE_FUNC)(Submenu*);
typedef void (*mSM_HAND_DRAW_FUNC)(Submenu*, GAME*);
typedef void (*mSM_TAG_MOVE_FUNC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_TAG_DRAW_FUNC)(Submenu*, GAME*, int);

typedef struct submenu_control_s {
    SUBMENU_PROC menu_move_func;
    SUBMENU_GAME_PROC menu_draw_func;

    mSM_HAND_MOVE_FUNC hand_move_func;
    mSM_HAND_DRAW_FUNC hand_draw_func;

    mSM_TAG_MOVE_FUNC tag_move_func;
    mSM_TAG_DRAW_FUNC tag_draw_func;

    int stick_release;
    u32 trigger;
    u32 last_trigger;
    s16 repeat_timer;
    s16 texture_movement_angle;
    f32 texture_pos[2];
    int animation_flag;
} mSM_Control_c;

typedef void (*mSM_RETURN_FUNC_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_END_PROC)(Submenu*, mSM_MenuInfo_c*);
typedef void (*mSM_MOVE_CHG_BASE_PROC)(mSM_MenuInfo_c*, int);
typedef void (*mSM_SET_CHAR_MATRIX_PROC)(GRAPH*);
typedef void (*mSM_CBUF_COPY_PROC)(GRAPH*, PreRender*, int, int, int);
typedef void (*mSM_SET_DRAWMODE_PROC)(GRAPH*, PreRender*, f32, f32, s16);
typedef void (*mSM_DRAW_ITEM_PROC)(GRAPH*, f32, f32, f32, mActor_name_t, int, int, int);
typedef void (*mSM_DRAW_MAIL_PROC)(GRAPH*, f32, f32, f32, Mail_c*, int, int);
typedef void (*mSM_SETUP_VIEW_PROC)(Submenu*, GRAPH*, int);
typedef void (*mSM_CHANGE_VIEW_PROC)(GRAPH*, f32, f32, f32, f32, s16, int, int);

typedef void (*mSM_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

/* sizeof(struct submenu_overlay_s) == 0xA04 */
struct submenu_overlay_s {
    /* TODO: finish */
    /* 0x000 */ mSM_Segment_c segment;
    /* 0x054 */ mSM_MenuInfo_c menu_info[mSM_OVL_NUM];
    /* 0x90C */ mSM_Control_c menu_control;
    /* 0x940 */ mSM_RETURN_FUNC_PROC return_func_proc;
    /* 0x944 */ mSM_MOVE_MOVE_PROC move_Move_proc;
    /* 0x948 */ mSM_MOVE_END_PROC move_End_proc;
    /* 0x94C */ mSM_MOVE_CHG_BASE_PROC move_chg_base_proc;
    /* 0x950 */ mSM_SET_CHAR_MATRIX_PROC set_char_matrix_proc;
    /* 0x954 */ mSM_CBUF_COPY_PROC cbuf_copy_proc;
    /* 0x958 */ mSM_SET_DRAWMODE_PROC set_drawMode_proc;
    /* 0x95C */ mSM_DRAW_ITEM_PROC draw_item_proc;
    /* 0x960 */ mSM_DRAW_MAIL_PROC draw_mail_proc;
    /* 0x964 */ mSM_SETUP_VIEW_PROC setup_view_proc;
    /* 0x968 */ void* unused_func_968;
    /* 0x96C */ mSM_CHANGE_VIEW_PROC change_view_proc;
    /* 0x970 */ void* _970;
    /* 0x974 */ void* _974;
    /* 0x978 */ void* _978;
    /* 0x97C */ mTG_Ovl_c* tag_ovl;
    /* 0x980 */ mHD_Ovl_c* hand_ovl;
    /* 0x984 */ mHP_Ovl_c* hanwiaPortrait_ovl;
    /* 0x988 */ void* inventory_ovl;
    /* 0x98C */ mED_Ovl_c* editor_ovl;
    /* 0x990 */ mBD_Ovl_c* board_ovl;
    /* 0x994 */ mAD_Ovl_c* address_ovl;
    /* 0x998 */ void* _998;
    /* 0x99C */ void* _99C;
    /* 0x9A0 */ mTI_Ovl_c* timeIn_ovl;
    /* 0x9A4 */ mEE_Ovl_c* editEndChk_ovl;
    /* 0x9A8 */ mWR_Ovl_c* warning_ovl;
    /* 0x9AC */ mRP_Ovl_c* repay_ovl;
    /* 0x9B0 */ void* _9B0;
    /* 0x9B4 */ mMP_Overlay_c* map_ovl;
    /* 0x9B8 */ mNT_Ovl_c* notice_ovl;
    /* 0x9BC */ mBR_Ovl_c* birthday_ovl;
    /* 0x9C0 */ void* _9C0;
    /* 0x9C4 */ void* _9C4;
    /* 0x9C8 */ void* _9C8;
    /* 0x9CC */ mCL_Ovl_c* catalog_ovl;
    /* 0x9D0 */ mMU_Overlay_c* music_ovl;
    /* 0x9D4 */ mBN_Overlay_c* bank_ovl;
    /* 0x9D8 */ void* _9D8;
    /* 0x9DC */ void* _9DC;
    /* 0x9E0 */ void* _9E0;
    /* 0x9E4 */ void* _9E4;
    /* 0x9E8 */ mDI_Ovl_c* diary_ovl;
    /* 0x9EC */ void* _9EC;
    /* 0x9F0 */ mPM_Ovl_c* passwordMake_ovl;
    /* 0x9F4 */ mPC_Ovl_c* passwordChk_ovl;
    /* 0x9F8 */ u8 hboard_exists;
    /* 0x9F9 */ u8 le_exists;
    /* 0x9FA */ u8 _9FA;
    /* 0x9FB */ u8 _9FB;
    /* 0x9FC */ int _9FC;
    /* 0xA00 */ Mtx* projection_matrix;
};

extern void mSM_menu_ovl_init(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
