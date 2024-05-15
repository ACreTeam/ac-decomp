#ifndef M_MSCORE_OVL_H
#define M_MSCORE_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mMS_mscore_ovl_construct(Submenu* submenu);
extern void mMS_mscore_ovl_destruct(Submenu* submenu);
extern void mMS_mscore_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
