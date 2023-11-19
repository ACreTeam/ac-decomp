#ifndef M_MSG_H
#define M_MSG_H

#include "types.h"
#include "libu64/gfxprint.h"
#include "m_choice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMsg_MSG_BUF_SIZE 1600
#define mMsg_FREE_STRING_LEN 16
#define mMsg_MAIL_STRING_LEN 132

enum {
  mMsg_INDEX_HIDE,
  mMsg_INDEX_APPEAR,
  mMsg_INDEX_NORMAL,
  mMsg_INDEX_CURSOL,
  mMsg_INDEX_DISAPPEAR,
  mMsg_INDEX_APPEAR_WAIT,
  mMsg_INDEX_WAIT,
  mMsg_INDEX_DISAPPEAR_WAIT,

  mMsg_INDEX_NUM
};

enum {
  mMsg_FREE_STR0,
  mMsg_FREE_STR1,
  mMsg_FREE_STR2,
  mMsg_FREE_STR3,
  mMsg_FREE_STR4,
  mMsg_FREE_STR5,
  mMsg_FREE_STR6,
  mMsg_FREE_STR7,
  mMsg_FREE_STR8,
  mMsg_FREE_STR9,
  mMsg_FREE_STR10,
  mMsg_FREE_STR11,
  mMsg_FREE_STR12,
  mMsg_FREE_STR13,
  mMsg_FREE_STR14,
  mMsg_FREE_STR15,
  mMsg_FREE_STR16,
  mMsg_FREE_STR17,
  mMsg_FREE_STR18,
  mMsg_FREE_STR19,

  mMsg_FREE_STR_NUM
};

enum {
  mMsg_ITEM_STR0,
  mMsg_ITEM_STR1,
  mMsg_ITEM_STR2,
  mMsg_ITEM_STR3,
  mMsg_ITEM_STR4,

  mMsg_ITEM_STR_NUM
};

enum {
  mMsg_MAIL_STR0,

  mMsg_MAIL_STR_NUM
};

typedef struct message_window_s mMsg_Window_c;
typedef struct message_data_s mMsg_Data_c;

/* These are hinted at due to the 8-byte alignment forced onto these structs */

typedef struct {
  int saved_main_index;
} mMsg_MainAppearWait_Data_c;

typedef struct {
  int saved_main_index;
} mMsg_MainDisappearWait_Data_c;

typedef struct {
  int saved_main_index;
} mMsg_MainWait_Data_c;

typedef union {
  mMsg_MainAppearWait_Data_c main_appear_wait;
  mMsg_MainDisappearWait_Data_c main_disappear_wait;
  mMsg_MainWait_Data_c main_wait;
  u64 align;
} mMsg_Main_Data_c;

typedef struct {
  ACTOR* speaker_actor;
  int msg_no;
  int name_shown_flag;
  rgba_t window_color;
} mMsg_Request_MainAppear_Data_c;

typedef struct {
  int saved_main_index;
  int init_flags;
} mMsg_Request_MainAppearWait_Data_c;

typedef struct {
  int init_flags;
} mMsg_Request_MainCursor_Data_c;

typedef struct {
  int init_flags;
} mMsg_Request_MainDisappearWait_Data_c;

typedef struct {
  int init_flags;
} mMsg_Request_MainNormal_Data_c;

typedef struct {
  int saved_main_index;
} mMsg_Request_MainWait_Data_c;

typedef union {
  mMsg_Request_MainAppear_Data_c request_main_appear;
  mMsg_Request_MainAppearWait_Data_c request_main_appear_wait;
  mMsg_Request_MainCursor_Data_c request_main_cursor;
  mMsg_Request_MainDisappearWait_Data_c request_main_disappear_wait;
  mMsg_Request_MainNormal_Data_c request_main_normal;
  mMsg_Request_MainWait_Data_c request_main_wait;
  u64 align;
} mMsg_Request_Data_c;

typedef union {
  u8 data[mMsg_MSG_BUF_SIZE];
  u64 align;
} mMsg_MsgBuf_c;

struct message_data_s {
  int data_loaded;
  int msg_no;
  int msg_len;
  int cut;

  mMsg_MsgBuf_c text_buf;
};

struct message_window_s {
  int data_loaded;
  int msg_no;
  int _008;
  mMsg_Data_c* msg_data;
  f32 center_x;
  f32 center_y;
  f32 width;
  f32 height;
  
  ACTOR* talk_actor;
  int show_actor_name;
  int actor_name_len;
  int nameplate_x;
  int nameplay_y;

  int show_continue_button;

  u8 free_str[mMsg_FREE_STR_NUM][mMsg_FREE_STRING_LEN];
  int free_str_article[mMsg_FREE_STR_NUM];

  u8 item_str[mMsg_ITEM_STR_NUM][mMsg_FREE_STRING_LEN];
  int item_str_article[mMsg_ITEM_STR_NUM];

  u8 mail_str[mMsg_MAIL_STR_NUM][mMsg_MAIL_STRING_LEN];

  rgba_t name_text_color;
  rgba_t name_background_color;

  rgba_t window_background_color;
  rgba_t font_color[4];

  rgba_t continue_button_color;

  f32 font_scale_x;
  f32 font_scale_y;

  int _2D8;
  int _2DC;

  int text_lines;
  int current_line;

  mChoice_c choice_window;

  int _3E8;

  u16 end_timer;
  s16 animal_voice_idx;
  int voice_sfx_idx;
  u8 voice_idx;
  u8 voice2_idx;
  u8 voice3_idx;
  s8 hide_choice_window_timer;
  int spec;
  u8 free_str_color_idx[4];
  u8 _404[8]; // unused?
  u32 status_flags;

  f32 timer;
  f32 cursor_timer;
  f32 continue_button_timer;

  int start_text_cursor_idx;
  int end_text_cursor_idx;
  f32 window_scale;
  f32 text_scale;

  int requested_main_index;
  int requested_priority;

  int main_index;
  int draw_flag;
  int cancel_flag;
  int cancelable_flag;
  int continue_msg_no;
  int continue_cancel_flag;
  int force_next;
  int lock_continue;
  s8 now_utter;

  mMsg_Main_Data_c main_data;
  mMsg_Request_Data_c request_data;
};

extern int mMsg_Get_Length_String(u8* buf, size_t buf_size);
extern mMsg_Window_c* mMsg_Get_base_window_p();
extern void mMsg_Set_free_str(mMsg_Window_c* msg, int free_str_no, u8* str, int str_size);
extern void mMsg_Set_free_str_art(mMsg_Window_c* msg, int free_str_no, u8* str, int str_size, int article_no);
extern void mMsg_Set_item_str_art(mMsg_Window_c* msg, int free_str_no, u8* str, int str_size, int article_no);
extern void mMsg_ct(GAME_PLAY*);
extern void mMsg_dt(GAME_PLAY*);
extern void mMsg_Main(GAME_PLAY*);
extern void mMsg_Draw(GAME_PLAY*);
extern void mMsg_debug_draw(gfxprint_t* gfxprint);
extern void mMsg_aram_init();
extern void mMsg_aram_init2();
extern int mMsg_Check_MainHide(mMsg_Window_c* msg);
extern void mMsg_Set_item_str(mMsg_Window_c* msg_win, int str_no, u8* item_str, int str_len);
extern void mMsg_Set_mail_str(mMsg_Window_c* msg_win, int str_no, u8* str, int str_len);
extern void mMsg_Set_continue_msg_num(mMsg_Window_c* msg_win, int continue_msg_num);
extern int mMsg_Check_MainNormalContinue(mMsg_Window_c* msg_win);
extern int mMsg_Check_main_wait(mMsg_Window_c* msg_win);
extern int mMsg_ChangeMsgData(mMsg_Window_c* msg_win, int msg_no);
extern void mMsg_Set_ForceNext(mMsg_Window_c* msg_win);
extern int mMsg_Check_not_series_main_wait(mMsg_Window_c* msg_win);
extern int mMsg_Check_MainDisappear(mMsg_Window_c* msg_win);
extern void mMsg_request_main_disappear_wait_type1(mMsg_Window_c* msg_win);
extern void mMsg_request_main_appear_wait_type1(mMsg_Window_c* msg_win);
extern void mMsg_Get_BodyParam(u32 table_rom_start, u32 data_rom_start, int entry_no, u32* data_addr, u32* data_size);
extern void mMsg_Set_LockContinue(mMsg_Window_c* msg_win);
extern void mMsg_Unset_LockContinue(mMsg_Window_c* msg_win);
extern int mMsg_Get_msg_num(mMsg_Window_c* msg_win);
extern int mMsg_Check_main_index(mMsg_Window_c* msg_win, int index);
extern int mMsg_request_main_appear(mMsg_Window_c* msg_win, ACTOR* other_actor, int display_name, rgba_t* window_color_p, int msg_no, int request_priority);
extern int mMsg_Check_main_hide(mMsg_Window_c* msg_win);
extern int mMsg_sound_voice_get_for_editor(int code);

#ifdef __cplusplus
}
#endif

#endif
