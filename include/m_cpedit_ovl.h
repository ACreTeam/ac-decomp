#ifndef M_CPEDIT_OVL_H
#define M_CPEDIT_OVL_H

#include "types.h"
#include "m_cpedit_ovl_h.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cpedit_ovl_s {
    u8 pad;
};

extern void mCE_cpedit_ovl_construct(Submenu* submenu);
extern void mCE_cpedit_ovl_destruct(Submenu* submenu);
extern void mCE_cpedit_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
