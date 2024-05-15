#ifndef M_CPMAIL_OVL_H
#define M_CPMAIL_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mCM_cpmail_ovl_construct(Submenu* submenu);
extern void mCM_cpmail_ovl_destruct(Submenu* submenu);
extern void mCM_cpmail_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
