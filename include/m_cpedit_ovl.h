#ifndef M_CPEDIT_OVL_H
#define M_CPEDIT_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mCE_cpedit_ovl_construct(Submenu* submenu);
extern void mCE_cpedit_ovl_destruct(Submenu* submenu);
extern void mCE_cpedit_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
