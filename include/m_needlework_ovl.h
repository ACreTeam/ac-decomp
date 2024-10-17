#ifndef M_NEEDLEWORK_OVL_H
#define M_NEEDLEWORK_OVL_H

#include "types.h"
#include "m_submenu.h"
#include "m_needlework_ovl_h.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

struct needlework_ovl_s {
    u16 mark_flg;
    u16 hide_flg;
    mNW_original_design_c my_org[mPr_ORIGINAL_DESIGN_COUNT];
    u8 my_org_no_table[mPr_ORIGINAL_DESIGN_COUNT];
};

extern u8 mNW_get_image_no(Submenu* submenu, int slot_no);
extern u8* mNW_get_image_name(Submenu* submenu, int idx);
extern int mNW_check_hide_flg(Submenu* submenu, int idx);
extern void mNW_on_hide_flg(Submenu* submenu, int idx);
extern void mNW_clear_hide_flg(Submenu* submenu);
extern void mNW_draw_original(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx, int color_flag);

extern void mNW_needlework_ovl_construct(Submenu* submenu);
extern void mNW_needlework_ovl_destruct(Submenu* submenu);
extern void mNW_needlework_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
