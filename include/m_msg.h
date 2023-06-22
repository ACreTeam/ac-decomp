#ifndef M_MSG_H
#define M_MSG_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: fill out message struct */
typedef struct message_window_s mMsg_Window_c;

extern int mMsg_Get_Length_String(u8* buf, size_t buf_size);
extern mMsg_Window_c* mMsg_Get_base_window_p();
extern void mMsg_Set_free_str(mMsg_Window_c* msg, int free_str_no, u8* str, int str_size);
extern void mMsg_debug_draw(gfxprint_t* gfxprint);
extern void mMsg_aram_init();
extern int mMsg_Check_MainHide(mMsg_Window_c* msg);
extern void mMsg_Set_item_str(mMsg_Window_c* msg_win, int str_no, u8* item_str, int str_len);
extern void mMsg_Set_mail_str(mMsg_Window_c* msg_win, int str_no, u8* str, int str_len);

#ifdef __cplusplus
}
#endif

#endif
