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

#ifdef __cplusplus
extern "C" {
#endif

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

typedef struct submenu_control_s {
  SUBMENU_PROC menu_move_func;
  SUBMENU_GAME_PROC menu_draw_func;

  void* hand_move_func;
  void* hand_draw_func;

  void* tag_move_func;
  void* tag_draw_func;

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
typedef void (*mSM_CHANGE_VIEW_PROC)(GRAPH*, f32, f32, f32, s16, int, int);

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
  /* 0x970 */ u8 _940[0x9B4 - 0x970];
  /* 0x9B4 */ mMP_Overlay_c* map_ovl;
  /* 0x9B8 */ u8 _9B8[0x9D0 - 0x9B8];
  /* 0x9D0 */ mMU_Overlay_c* music_ovl;
  /* 0x9D4 */ mBN_Overlay_c* bank_ovl;
  /* 0x9D8 */ u8 _9D8[0xA00 - 0x9D8];
  /* 0xA00 */ Mtx* projection_matrix;
};

#ifdef __cplusplus
}
#endif

#endif
