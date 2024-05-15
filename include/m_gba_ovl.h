#ifndef M_GBA_OVL_H
#define M_GBA_OVL_H

#include "types.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mGB_copy_image(Submenu*, mActor_name_t, mActor_name_t);
extern void mGB_draw_gba(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx, int color_flag);

extern void mGB_gba_ovl_construct(Submenu* submenu);
extern void mGB_gba_ovl_destruct(Submenu* submenu);
extern void mGB_gba_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
