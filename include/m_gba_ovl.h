#ifndef M_GBA_OVL_H
#define M_GBA_OVL_H

#include "types.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

struct gba_ovl_s {
    u16 mark_flg;
    u16 hide_flg;
    mNW_original_design_c* original_p;
    u8 original_design_table_no;
};

extern int mGB_get_change_flg(void);
extern int mGB_check_hide_flg(Submenu* submenu, int idx);
extern int mGB_check_mark_flg(Submenu* submenu, int idx);
extern void mGB_copy_image(Submenu* submenu, mActor_name_t rsv_gba, mActor_name_t rsv_nw);
extern u8* mGB_get_image_name(Submenu* submenu, int idx);
extern u16* mGB_get_image_pal(Submenu* submenu, int idx);
extern u8* mGB_get_image_texture(Submenu* submenu, int idx);
extern void mGB_draw_gba(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx, int shadow_flag);
extern void mGB_gba_ovl_construct(Submenu* submenu);
extern void mGB_gba_ovl_destruct(Submenu* submenu);
extern void mGB_gba_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
