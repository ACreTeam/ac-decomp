#ifndef M_REPAY_OVL_H
#define M_REPAY_OVL_H

#include "types.h"
#include "m_repay_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    mRP_CURSOR_100000,
    mRP_CURSOR_10000,
    mRP_CURSOR_1000,
    mRP_CURSOR_100,
    mRP_CURSOR_10,
    mRP_CURSOR_1,
    mRP_CURSOR_OK,

    mRP_CURSOR_NUM
};

struct repay_ovl_s {
    u32 money;
    u32 loan;
    u32 repay_amount;
    u32 max_money;
    u32 max_repay;
    int cursor_idx;
};

extern void mRP_repay_ovl_set_proc(Submenu* submenu);
extern void mRP_repay_ovl_construct(Submenu* submenu);
extern void mRP_repay_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
