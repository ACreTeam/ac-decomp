#ifndef M_DIARY_OVL_H
#define M_DIARY_OVL_H

#include "types.h"
#include "m_submenu.h"
#include "m_diary_ovl_h.h"
#include "m_diary.h"
#include "m_card.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mDI_FIELD_BODY,

    mDI_FIELD_NUM
};

struct diary_ovl_s {
    mCD_keep_diary_c* data;
    u8 field;
    u8 _05;
    s16 entry_len[mDI_FIELD_NUM];
    mDi_entry_c* current_entry;
    u32 _0C;
    u8 _10;
    u8 _11;
    u8 _12;
    int _14;
    int _18;
    s16 move_proc;
    s16 _1E;
    s16 _20;
    s16 _22;
    s16 _24;
    f32 _28;
    s16 _2C;
    s16 _2E;
    s16 _30;
    s16 _32;
    u32 trigger;
    u32 button;
    u32 last_button;
    u16 _40;
    u16 _42;
    s16 cursor_idx;
    s16 _46;
    s16 _48;
};

extern void mDI_diary_ovl_construct(Submenu* submenu);
extern void mDI_diary_ovl_destruct(Submenu* submenu);
extern void mDI_diary_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
