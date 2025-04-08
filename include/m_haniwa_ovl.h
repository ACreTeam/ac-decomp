#ifndef M_HANIWA_OVL_H
#define M_HANIWA_OVL_H

#include "types.h"
#include "m_haniwa_ovl_h.h"
#include "m_tag_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mHW_OVL_MSG_SIZE 22

enum {
    mHW_MSG_IKAGA,
    mHW_MSG_DONO,
    mHW_MSG_DONO2,
    mHW_MSG_OIKURA,
    mHW_MSG_KASIKO,
    mHW_MSG_DOREWO,
    mHW_MSG_MOU, // @unused - not actually set anywhere
    mHW_MSG_OKANE,
    mHW_MSG_MAIDO,
    mHW_MSG_TADA,
    mHW_MSG_TADA2,
    mHW_MSG_MISE,
    mHW_MSG_BERU2,

    mHW_MSG_NUM
};

typedef void (*mHW_SET_INTERRUPT_MESSAGE_PROC)(Submenu*, mTG_tag_c*, int);

struct haniwa_ovl_s {
    int msg_idx;
    int msg_interrupt_idx;
    int table_idx;
    int sub_idx;
    int msg_time;
    int msg_counter;
    u32 msg_price;
    u32 price;
    u8 msg[mHW_OVL_MSG_SIZE];
    mHW_SET_INTERRUPT_MESSAGE_PROC set_interrupt_message_proc;
};

extern void mHW_haniwa_ovl_construct(Submenu* submenu);
extern void mHW_haniwa_ovl_destruct(Submenu* submenu);
extern void mHW_haniwa_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
