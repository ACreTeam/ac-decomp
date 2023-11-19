#ifndef M_EDITOR_OVL_H
#define M_EDITOR_OVL_H

#include "types.h"
#include "m_editor_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mED_COLUMNS 10
#define mED_ROWS 4

#define mED_NG_WORD_START 0x74A
#define mED_NG_WORD_NUM 14

enum {
  mED_TYPE_BOARD,
  mED_TYPE_HBOARD,
  mED_TYPE_NOTICE,
  mED_TYPE_LEDIT,
  mED_TYPE_CP_TITLE,
  mED_TYPE_DIARY,
  mED_TYPE_PASSWORDMAKE,
  mED_TYPE_PASSWORDCHK,

  mED_TYPE_NUM
};

enum {
  mED_STICK_AREA_LEFT,
  mED_STICK_AREA_TOP_LEFT,
  mED_STICK_AREA_TOP,
  mED_STICK_AREA_TOP_RIGHT,
  mED_STICK_AREA_RIGHT,
  mED_STICK_AREA_BOTTOM_RIGHT,
  mED_STICK_AREA_BOTTOM,
  mED_STICK_AREA_BOTTOM_LEFT,
  mED_STICK_AREA_CENTER,

  mED_STICK_AREA_NUM
};

enum {
  mED_COMMAND_NONE,
  mED_COMMAND_CURSOL_RIGHT,
  mED_COMMAND_CURSOL_LEFT,
  mED_COMMAND_CURSOL_UPPER,
  mED_COMMAND_CURSOL_LOWER,
  mED_COMMAND_END_EDIT,
  mED_COMMAND_BACKSPACE,
  mED_COMMAND_EXCHANGE_CODE,
  mED_COMMAND_OUTPUT_CODE,
  mED_COMMAND_9,

  mED_COMMAND_NUM
};

enum {
  mED_SHIFT_LOWER,
  mED_SHIFT_UPPER,

  mED_SHIFT_NUM
};

enum {
  mED_ARRANGE_QWERTY,
  mED_ARRANGE_ALPHA,

  mED_ARRANGE_NUM
};

enum {
  mED_INPUT_MODE_LETTER,
  mED_INPUT_MODE_SIGN,
  mED_INPUT_MODE_MARK,

  mED_INPUT_MODE_NUM
};

enum {
  mED_LINETYPE_SINGLE,
  mED_LINETYPE_MULTI,
  mED_LINETYPE_PW,

  mED_LINETYPE_NUM
};

enum {
  mED_LINE_OK,
  mED_LINE_NEWLINE,
  mED_LINE_WIDTH_OVER,
  mED_LINE_NUM_OVER,

  mED_LINE_NUM
};

typedef void (*mED_ENDCODE_DRAW_PROC)(Submenu*, GAME*, f32, f32);
typedef void (*mED_CURSOL_DRAW_PROC)(Submenu*, GAME*, f32, f32);

struct editor_ovl_s {
  u8 stick_area;
  u8 stick_area_changed;
  u8 select_col;
  u8 select_row;
  u8 stick_area_held_frames;
  u8 input_mode;
  u8 shift_mode;
  u8 arrange;
  int last_buttons;
  s16 cursol_opacity_step;
  u8 _0E;
  u8 _0F;
  u8 _10;
  u8 command;
  u8 _12;
  u8 now_code;
  u8 _14;
  u8 command_processed;
  s16 cursor_idx;
  s16 input_length;
  s16 max_line_no;
  s16 line_width;
  s16 now_str_len;
  s16 exchange_code;
  s16 _22;
  s16 _24;
  s16 _26;
  u8* input_str;
  mED_ENDCODE_DRAW_PROC end_code_draw;
  mED_CURSOL_DRAW_PROC cursol_draw;
  u8 _34;
};

extern void mED_editor_ovl_set_proc(Submenu* submenu);
extern void mED_editor_ovl_construct(Submenu* submenu);
extern void mED_editor_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
