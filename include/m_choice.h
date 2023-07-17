#ifndef M_CHOICE_H
#define M_CHOICE_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mChoice_CHOICE_STRING_LEN 16

typedef struct choice_s mChoice_c;
typedef struct choice_data_s mChoice_Data_c;

enum choice {
  mChoice_CHOICE0,
  mChoice_CHOICE1,
  mChoice_CHOICE2,
  mChoice_CHOICE3,
  mChoice_CHOICE4,
  mChoice_CHOICE5,

  mChoice_CHOICE_NUM
};

enum {
  mChoice_AUTOMOVE_STOPPED,
  mChoice_AUTOMOVE_INCREMENT_WAIT,
  mChoice_AUTOMOVE_INCREMENT,
  mChoice_AUTOMOVE_DECREMENT_WAIT,
  mChoice_AUTOMOVE_DECREMENT,

  mChoice_AUTOMOVE_NUM
};

enum {
  mChoice_MAIN_HIDE,
  mChoice_MAIN_APPEAR,
  mChoice_MAIN_NORMAL,
  mChoice_MAIN_DISAPPEAR,

  mChoice_MAIN_INDEX_NUM
};

struct choice_data_s {
  u8 strings[mChoice_CHOICE_NUM][mChoice_CHOICE_STRING_LEN];
  int string_lens[mChoice_CHOICE_NUM];
  u8 determination_string[mChoice_CHOICE_STRING_LEN];
  int determination_len;
  int choice_num;
  int selected_choice_idx;
};

struct choice_s {
  /* Current XY position (centered) */
  f32 center_x;
  f32 center_y;

  /* Initial XY position */
  f32 center_x_begin;
  f32 center_y_begin;

  /* Target XY position */
  f32 center_x_target;
  f32 center_y_target;

  /* Text settings */
  rgba_t text_color;
  f32 text_scale_x;
  f32 text_scale_y;
  f32 text_x;
  f32 text_y;

  /* Window scaling XY */
  f32 scale_x;
  f32 scale_y;

  /* Text related data */
  mChoice_Data_c data;

  int selected_choice_idx;
  rgba_t selected_choice_text_color;
  
  rgba_t background_color;

  f32 _D4;
  f32 _D8;

  f32 scale; // total choice window scaling percentage

  int main_index;
  int requested_main_index;

  int window_visible_flag;
  int font_visible_flag;

  int choice_automove_type;
  f32 choice_automove_timer;

  f32 timer;

  u8 no_b_flag; // can't press B to select last option
  u8 no_close_flag; // pressing B won't auto-cancel the choice selection?
};

extern mChoice_c* mChoice_Get_base_window_p();
extern int mChoice_Get_ChoseNum(mChoice_c* choice);

#ifdef __cplusplus
}
#endif

#endif
