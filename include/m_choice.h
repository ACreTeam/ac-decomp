#ifndef M_CHOICE_H
#define M_CHOICE_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mChoice_CHOICE_STRING_LEN 16
#define mChoice_SELECT_STR_NUM 607

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
    /* 0x00 */ f32 center_x;
    /* 0x04 */ f32 center_y;

    /* Initial XY position */
    /* 0x08 */ f32 center_x_begin;
    /* 0x0C */ f32 center_y_begin;

    /* Target XY position */
    /* 0x10 */ f32 center_x_target;
    /* 0x14 */ f32 center_y_target;

    /* Text settings */
    /* 0x18 */ rgba_t text_color;
    /* 0x1C */ f32 text_scale_x;
    /* 0x20 */ f32 text_scale_y;
    /* 0x24 */ f32 text_x;
    /* 0x28 */ f32 text_y;

    /* Window scaling XY */
    /* 0x2C */ f32 scale_x;
    /* 0x30 */ f32 scale_y;

    /* Text related data */
    /* 0x34 */ mChoice_Data_c data;

    /* 0xC8 */ int selected_choice_idx;
    /* 0xCC */ rgba_t selected_choice_text_color;

    /* 0xD0 */ rgba_t background_color;

    /* 0xD4 */ f32 _D4;
    /* 0xD8 */ f32 _D8;

    /* 0xDC */ f32 scale; // total choice window scaling percentage

    /* 0xE0 */ int main_index;
    /* 0xE4 */ int requested_main_index;

    /* 0xE8 */ int window_visible_flag;
    /* 0xEC */ int font_visible_flag;

    /* 0xF0 */ int choice_automove_type;
    /* 0xF4 */ f32 choice_automove_timer;

    /* 0xF8 */ f32 timer;

    /* 0xFC */ u8 no_b_flag;     // can't press B to select last option
    /* 0xFD */ u8 no_close_flag; // pressing B won't auto-cancel the choice selection?
};

extern void mChoice_Main(mChoice_c* choice, GAME* game);
extern void mChoice_Draw(mChoice_c* choice, GAME* game, int mode);
extern void mChoice_aram_init();
extern void mChoice_ct(mChoice_c* choice, GAME* game);
extern void mChoice_dt(mChoice_c* choice, GAME* game);
extern mChoice_c* mChoice_Get_base_window_p();
extern void mChoice_Change_request_main_index(mChoice_c* choice, int request_main_index);
extern int mChoice_check_main_index(mChoice_c* choice);
extern int mChoice_check_main_normal(mChoice_c* choice);
extern void mChoice_Set_choice_data(mChoice_c* choice, u8* str0, int str0_len, u8* str1, int str1_len, u8* str2,
                                    int str2_len, u8* str3, int str3_len, u8* str4, int str4_len, u8* str5,
                                    int str5_len);
extern int mChoice_Get_ChoseNum(mChoice_c* choice);
extern void mChoice_Clear_ChoseNum(mChoice_c* choice);
extern void mChoice_Load_ChoseStringFromRom(mChoice_c* choice, u8* str, int str_no, ACTOR* actor);
extern void mChoice_no_b_set(mChoice_c* choice);
extern void mChoice_no_b_close_set(mChoice_c* choice);

/* Macros */
#define mChoice_CHECK_MAIN_NORMAL() mChoice_check_main_normal(mChoice_Get_base_window_p())

#define mChoice_GET_CHOSENUM() mChoice_Get_ChoseNum(mChoice_Get_base_window_p())
#define mChoice_CLEAR_CHOSENUM() mChoice_Clear_ChoseNum(mChoice_Get_base_window_p())
#define mChoice_NO_B_SET() mChoice_no_b_set(mChoice_Get_base_window_p())
#define mChoice_NO_B_CLOSE_SET() mChoice_no_b_close_set(mChoice_Get_base_window_p())

#ifdef __cplusplus
}
#endif

#endif
