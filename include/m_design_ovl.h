#ifndef M_DESIGN_OVL_H
#define M_DESIGN_OVL_H

#include "types.h"
#include "m_mask_cat.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mDE_maskcat_init(MaskCat_c* mask_cat);

extern void mDE_design_ovl_construct(Submenu* submenu);
extern void mDE_design_ovl_destruct(Submenu* submenu);
extern void mDE_design_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
