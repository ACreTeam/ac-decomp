#ifndef M_CPWARNING_OVL_H
#define M_CPWARNING_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mCW_cpwarning_ovl_construct(Submenu* submenu);
extern void mCW_cpwarning_ovl_destruct(Submenu* submenu);
extern void mCW_cpwarning_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
