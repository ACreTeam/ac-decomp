#ifndef M_MAILBOX_OVL_H
#define M_MAILBOX_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mMB_mailbox_ovl_construct(Submenu* submenu);
extern void mMB_mailbox_ovl_destruct(Submenu* submenu);
extern void mMB_mailbox_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
