#include "m_birthday_ovl.h"

#include "m_common_data.h"
#include "m_font.h"
#include "sys_matrix.h"

static mBR_Ovl_c birthday_ovl_data;

static void mBR_window_close(Submenu* submenu, mSM_MenuInfo_c* menu_info, mBR_Ovl_c* birthday_ovl) {
  u16* data_p = birthday_ovl->birthday_data;

  (*submenu->overlay->move_chg_base_proc)(menu_info, mSM_MOVE_OUT_TOP);
  Common_Get(now_private)->birthday.month = data_p[mBR_Ovl_IDX_MONTH];
  Common_Get(now_private)->birthday.day = data_p[mBR_Ovl_IDX_DAY];
  sAdo_SysTrgStart(NA_SE_MENU_EXIT);
}

static void mBR_move_Move(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_Move_proc)(submenu, menu_info);
}

static void mBR_move_Play(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  static lbRTC_time_c work_time = { 0, 0, 0, 1, lbRTC_SUNDAY, lbRTC_JANUARY, 2000 };
  mBR_Ovl_c* birthday_ovl = submenu->overlay->birthday_ovl;
  int* idx_p = &birthday_ovl->idx;
  u16* data_p = birthday_ovl->birthday_data;
  u32 trigger = submenu->overlay->menu_control.trigger;

  if ((trigger & (BUTTON_B | BUTTON_CLEFT))) {
    if (*idx_p != 0) {
      (*idx_p)--;
      sAdo_SysTrgStart(0x1003);
    }
  }
  else if ((trigger & BUTTON_START)) {
    mBR_window_close(submenu, menu_info, birthday_ovl);
  }
  else if ((trigger & (BUTTON_A | BUTTON_CRIGHT))) {
    if (*idx_p == mBR_Ovl_IDX_OK) {
      if ((trigger & BUTTON_CRIGHT) == 0) {
        mBR_window_close(submenu, menu_info, birthday_ovl);
      }
    }
    else {
      (*idx_p)++;
      sAdo_SysTrgStart(NA_SE_SENTAKU_KETTEI);
    }
  }
  else if ((trigger & (BUTTON_CUP | BUTTON_CDOWN))) {
    if (*idx_p != mBR_Ovl_IDX_OK) {
      if ((trigger & BUTTON_CDOWN)) {
        data_p[*idx_p]--;
      }
      else {
        data_p[*idx_p]++;
      }

      work_time.day = data_p[mBR_Ovl_IDX_DAY];
      work_time.month = data_p[mBR_Ovl_IDX_MONTH];
      if (!lbRTC_IsValidTime(&work_time)) {
        if (
          (
            *idx_p == mBR_Ovl_IDX_MONTH &&
            data_p[mBR_Ovl_IDX_MONTH] != 0 &&
            data_p[mBR_Ovl_IDX_MONTH] < 13
          ) || (
            (trigger & BUTTON_CDOWN) &&
            *idx_p == mBR_Ovl_IDX_DAY
          )
        ) {
          work_time.day = 31;
          while (!lbRTC_IsValidTime(&work_time)) {
            work_time.day--;
          }

          data_p[mBR_Ovl_IDX_DAY] = work_time.day;
        }
        else if ((trigger & BUTTON_CUP)) {
          data_p[*idx_p] = 1;
        }
        else {
          data_p[mBR_Ovl_IDX_MONTH] = lbRTC_DECEMBER;
        }
      }

      sAdo_SysTrgStart(NA_SE_CURSOL);
    }
  }
}

static void mBR_move_End(Submenu* submenu, mSM_MenuInfo_c* menu_info) {
  (*submenu->overlay->move_End_proc)(submenu, menu_info);
}

typedef void (*mBR_OVL_MOVE_PROC)(Submenu*, mSM_MenuInfo_c*);

static void mBR_birthday_ovl_move(Submenu* submenu) {
  static mBR_OVL_MOVE_PROC ovl_move_proc[mSM_OVL_PROC_NUM] = {
    &mBR_move_Move,
    &mBR_move_Play,
    (mBR_OVL_MOVE_PROC)none_proc1,
    (mBR_OVL_MOVE_PROC)none_proc1,
    &mBR_move_End
  };

  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_BIRTHDAY];

  (*menu_info->pre_move_func)(submenu);
  (*ovl_move_proc[menu_info->proc_status])(submenu, menu_info);
}

extern Gfx birthday_win_mode[];
extern Gfx birthday_win_model[];
extern Gfx brt_win_month_model[];

extern u8 tim_win_january_tex_rgb_i4[];
extern u8 tim_win_february_tex_rgb_i4[];
extern u8 tim_win_march_tex_rgb_i4[];
extern u8 tim_win_april_tex_rgb_i4[];
extern u8 tim_win_may_tex_rgb_i4[];
extern u8 tim_win_june_tex_rgb_i4[];
extern u8 tim_win_july_tex_rgb_i4[];
extern u8 tim_win_august_tex_rgb_i4[];
extern u8 tim_win_september_tex_rgb_i4[];
extern u8 tim_win_october_tex_rgb_i4[];
extern u8 tim_win_november_tex_rgb_i4[];
extern u8 tim_win_december_tex_rgb_i4[];

static void mBR_set_dl(Submenu* submenu, mSM_MenuInfo_c* menu_info, GAME* game) {
  static u8 chr_table[21] = "When's your birthday?";
  static u8 close_table[2] = "OK";
  static u8* month_tex[lbRTC_MONTHS_MAX] = {
    tim_win_january_tex_rgb_i4,
    tim_win_february_tex_rgb_i4,
    tim_win_march_tex_rgb_i4,
    tim_win_april_tex_rgb_i4,
    tim_win_may_tex_rgb_i4,
    tim_win_june_tex_rgb_i4,
    tim_win_july_tex_rgb_i4,
    tim_win_august_tex_rgb_i4,
    tim_win_september_tex_rgb_i4,
    tim_win_october_tex_rgb_i4,
    tim_win_november_tex_rgb_i4,
    tim_win_december_tex_rgb_i4
  };
  static int color_type[2][3] = {
    { 195,   0,   0 },
    {  70, 145, 225 }
  };

  GRAPH* graph = game->graph;
  mBR_Ovl_c* birthday_ovl = submenu->overlay->birthday_ovl;
  f32 x = menu_info->position[0];
  f32 y = menu_info->position[1];
  f32 tex_x;
  f32 tex_y;
  u8 str[2];
  int* color_p;
  u8 s;
  u8 t;
  Gfx* gfx;

  Matrix_scale(16.0f, 16.0f, 1.0f, MTX_LOAD);
  Matrix_translate(x, y, 140.0f, MTX_MULT);

  OPEN_DISP(graph);
  gfx = NOW_POLY_OPA_DISP;

  gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
  gSPDisplayList(gfx++, birthday_win_mode);
  
  tex_x = -submenu->overlay->menu_control.texture_pos[0] * 4.0f;
  tex_y = -submenu->overlay->menu_control.texture_pos[1] * 4.0f;
  s = (int)tex_x & 0xFF;
  t = (int)tex_y & 0xFF;
  gDPSetTileSize_Dolphin(gfx++, G_TX_RENDERTILE, s, t, 32, 32);
  gSPDisplayList(gfx++, birthday_win_model);

  color_p = color_type[birthday_ovl->idx != mBR_Ovl_IDX_MONTH];

  gDPSetPrimColor(gfx++, 0, 255, color_p[0], color_p[1], color_p[2], 255);

  gSPSegment(gfx++, G_MWO_SEGMENT_8, month_tex[birthday_ovl->birthday_data[mBR_Ovl_IDX_MONTH] - 1]);

  gSPDisplayList(gfx++, brt_win_month_model);

  SET_POLY_OPA_DISP(gfx);
  CLOSE_DISP(graph);

  (*submenu->overlay->set_char_matrix_proc)(graph);
  mFont_SetLineStrings(
    game,
    chr_table, sizeof(chr_table),
    x + 119.0f, -y + 88.0f,
    255, 255, 255, 255,
    FALSE,
    TRUE,
    0.875f, 0.875f,
    mFont_MODE_POLY
  );

  mFont_UnintToString(str, 2, birthday_ovl->birthday_data[mBR_Ovl_IDX_DAY], 2, FALSE, TRUE, TRUE);

  color_p = color_type[birthday_ovl->idx != mBR_Ovl_IDX_DAY];
  mFont_SetLineStrings(
    game,
    str, sizeof(str),
    x + 171.0f, -y + 124.0f,
    color_p[0], color_p[1], color_p[2], 255,
    FALSE,
    TRUE,
    1.0f, 1.0f,
    mFont_MODE_POLY
  );

  color_p = color_type[birthday_ovl->idx != mBR_Ovl_IDX_OK];
  mFont_SetLineStrings(
    game,
    close_table, sizeof(close_table),
    x + 198.0f, -y + 124.0f,
    color_p[0], color_p[1], color_p[2], 255,
    FALSE,
    TRUE,
    1.0f, 1.0f,
    mFont_MODE_POLY
  );
}

static void mBR_birthday_ovl_draw(Submenu* submenu, GAME* game) {
  mSM_MenuInfo_c* menu_info = &submenu->overlay->menu_info[mSM_OVL_BIRTHDAY];

  (*menu_info->pre_draw_func)(submenu, game);
  mBR_set_dl(submenu, menu_info, game);
}

extern void mBR_birthday_ovl_set_proc(Submenu* submenu) {
  mSM_Control_c* control = &submenu->overlay->menu_control;

  control->menu_move_func = &mBR_birthday_ovl_move;
  control->menu_draw_func = &mBR_birthday_ovl_draw;
}

static void mBR_birthday_ovl_init(Submenu* submenu) {
  mBR_Ovl_c* birthday_ovl = submenu->overlay->birthday_ovl;
  (*submenu->overlay->move_chg_base_proc)(&submenu->overlay->menu_info[mSM_OVL_BIRTHDAY], mSM_MOVE_IN_TOP);
  submenu->overlay->menu_control.animation_flag = FALSE;
  
  birthday_ovl->birthday_data[mBR_Ovl_IDX_MONTH] = lbRTC_JANUARY;
  birthday_ovl->birthday_data[mBR_Ovl_IDX_DAY] = 1;
  sAdo_SysTrgStart(0x17C);
}

extern void mBR_birthday_ovl_construct(Submenu* submenu) {
  Submenu_Overlay_c* overlay = submenu->overlay;

  if (overlay->birthday_ovl == NULL) {
    mem_clear((u8*)&birthday_ovl_data, sizeof(mBR_Ovl_c), 0);
    overlay->birthday_ovl = &birthday_ovl_data;
  }

  mBR_birthday_ovl_init(submenu);
  mBR_birthday_ovl_set_proc(submenu);
}

extern void mBR_birthday_ovl_destruct(Submenu* submenu) {
  submenu->overlay->birthday_ovl = NULL;
}
