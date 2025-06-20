#include "m_passwordChk_ovl.h"

#include "audio.h"
#include "libultra/libultra.h"
#include "m_editor_ovl.h"
#include "m_font.h"
#include "sys_matrix.h"

mPC_Ovl_c pc_ovl_data;

static void mPC_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mPC_move_Obey(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  mPC_Ovl_c* passwordChk_ovl;

  if (submenu->overlay->menu_info[mSM_OVL_EDITOR].next_proc_status == mSM_PROCESS_END) {
    (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_PROCESS_END); // close this submenu overlay too
    sAdo_SysTrgStart(NA_SE_MENU_EXIT);
    passwordChk_ovl = submenu->overlay->passwordChk_ovl;
    mem_copy(               (u8*)menu_info->data2, passwordChk_ovl->line0, mPC_STR_SIZE);
    mem_copy((u8*)menu_info->data2 + mPC_STR_SIZE, passwordChk_ovl->line1, mPC_STR_SIZE);
  }
}

static void mPC_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

static void mPC_passwordChk_ovl_move(Submenu* submenu) {
  static mSM_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mPC_move_Move,
    (mSM_MOVE_PROC)none_proc1,
    (mSM_MOVE_PROC)none_proc1,
    &mPC_move_Obey,
    &mPC_move_End
  };
  
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDCHK];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx pwd_win_mode[];
extern Gfx pwd_win_model[];

static void mPC_set_frame_dl(Submenu* submenu, GRAPH* graph, f32 x, f32 y) {
  mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
  Gfx* gfx;
  u8 s;
  u8 t;

  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
  Matrix_translate(x, y, 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  /* Setup RDP settings */
  gSPDisplayList(gfx++, pwd_win_mode);

  /* Initialize position matrix */
  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

  /* Setup background tiling offset */
  s = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
  t = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
  gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, s, t, 32, 32);

  /* Draw background */
  gSPDisplayList(gfx++, pwd_win_model);

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);
}

static void mPC_set_character(Submenu* submenu, GAME* game, f32 x, f32 y) {
  static u8 title_str[20] = "Enter a secret code.";
  static f32 cursol_baseX[mPC_LINE_COUNT] = { 77.0f, 77.0f };
  static f32 cursol_baseY[mPC_LINE_COUNT] = { 81.0f, 99.0f };

  mPC_Ovl_c* passwordChk_ovl = submenu->overlay->passwordChk_ovl;
  mED_Ovl_c* editor_ovl = submenu->overlay->editor_ovl;
  int sel_line;
  u8* sel_line_p;
  f32 text_x;
  f32 cursor_x;
  f32 cursor_y;
  int width;

  /* Draw title text */
  mFont_SetLineStrings(
    game,
    title_str, sizeof(title_str),
    131.0f + x, 34.0f - y,
    255, 255, 255, 255,
    FALSE,
    TRUE,
    0.875f, 0.875f,
    mFont_MODE_POLY
  );

  text_x = 77.0f + x;

  /* Draw first line */
  mFont_SetLineStrings(
    game,
    passwordChk_ovl->line0, mPC_STR_SIZE,
    text_x, 81.0f - y,
    235, 235, 50, 255,
    FALSE,
    FALSE,
    1.0f, 1.0f,
    mFont_MODE_POLY
  );

  /* Draw second line */
  mFont_SetLineStrings(
    game,
    passwordChk_ovl->line1, mPC_STR_SIZE,
    text_x, 99.0f - y,
    235, 235, 50, 255,
    FALSE,
    FALSE,
    1.0f, 1.0f,
    mFont_MODE_POLY
  );

  /* Draw editor cursor */
  sel_line = passwordChk_ovl->selected_line;
  sel_line_p = passwordChk_ovl->line0;
  if (sel_line == 0) {
    sel_line_p = passwordChk_ovl->line1;
  }

  width = mFont_GetStringWidth(sel_line_p, editor_ovl->_22, FALSE);
  cursor_x = x + cursol_baseX[sel_line] + (f32)width + -7.0f;
  cursor_y = -y + cursol_baseY[sel_line];
  (*submenu->overlay->editor_ovl->cursol_draw)(submenu, game, cursor_x, cursor_y);
}

static void mPC_set_dl(Submenu* submenu, GAME* game, mSM_MenuInfo_c* menu_info) {
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];
  GRAPH* graph = game->graph;

  mPC_set_frame_dl(submenu, graph, x, y);
  (*submenu->overlay->set_char_matrix_proc)(graph);
  mPC_set_character(submenu, game, x, y);
}

static void mPC_passwordChk_ovl_draw(Submenu* submenu, GAME* game) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDCHK];

  (*menu_info->pre_draw_func)(submenu, game);
  mPC_set_dl(submenu, game, menu_info);
}

extern void mPC_passwordChk_ovl_set_proc(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->menu_control.menu_move_func = &mPC_passwordChk_ovl_move;
  overlay->menu_control.menu_draw_func = &mPC_passwordChk_ovl_draw;
}

static void mPC_passwordChk_ovl_init(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;
  mSM_MenuInfo_c* menu_info = &overlay->menu_info[mSM_OVL_PASSWORDCHK];
  mPC_Ovl_c* passwordChk_ovl = overlay->passwordChk_ovl;

  overlay->menu_control.animation_flag = FALSE;
  menu_info->proc_status = mSM_OVL_PROC_MOVE;
  menu_info->next_proc_status = mSM_OVL_PROC_OBEY;
  menu_info->move_drt = mSM_MOVE_IN_TOP;

  /* Open the editor overlay on top of this submenu */
  mSM_open_submenu_new2(submenu, mSM_OVL_EDITOR, mED_TYPE_PASSWORDCHK, 0, passwordChk_ovl->line0, 168);
}

extern void mPC_passwordChk_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->passwordChk_ovl == NULL) {
    bzero(&pc_ovl_data, sizeof(mPC_Ovl_c));
    overlay->passwordChk_ovl = &pc_ovl_data;
    mem_copy(overlay->passwordChk_ovl->line0, (u8*)overlay->menu_info[mSM_OVL_PASSWORDCHK].data2, mPC_STR_SIZE);
    mem_copy(overlay->passwordChk_ovl->line1, (u8*)overlay->menu_info[mSM_OVL_PASSWORDCHK].data2 + mPC_STR_SIZE, mPC_STR_SIZE);
  }

  mPC_passwordChk_ovl_init(submenu);
  mPC_passwordChk_ovl_set_proc(submenu);
}

extern void mPC_passwordChk_ovl_destruct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  overlay->passwordChk_ovl = NULL;
}
