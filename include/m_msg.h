#ifndef M_MSG_H
#define M_MSG_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* TODO: fill out message struct */
typedef struct message_window_s M_MSG_WINDOW;

extern int mMsg_Get_Length_String(u8* buf, size_t buf_size);

extern M_MSG_WINDOW* mMsg_Get_base_window_p();

extern void mMsg_Set_free_str(M_MSG_WINDOW* msg, int free_str_no, u8* str, size_t str_size);

extern void mMsg_debug_draw(gfxprint_t* gfxprint);

extern void mMsg_aram_init();

#ifdef __cplusplus
}
#endif

#endif
