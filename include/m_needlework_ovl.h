#ifndef M_NEEDLEWORK_OVL_H
#define M_NEEDLEWORK_OVL_H

#include "types.h"
#include "m_submenu.h"
#include "m_needlework_ovl_h.h"
#include "m_needlework.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNW_DESIGN_COUNT mPr_ORIGINAL_DESIGN_COUNT

enum {
    mNW_OPEN_DESIGN,
    mNW_OPEN_INV,
    mNW_OPEN_CPORIGINAL,
    mNW_OPEN_GBA,
    mNW_OPEN_CARD,

    mNW_OPEN_NUM
};

struct needlework_ovl_s {
    u16 mark_flg;
    u16 hide_flg;
    mNW_original_design_c my_org[mPr_ORIGINAL_DESIGN_COUNT];
    u8 my_org_no_table[mPr_ORIGINAL_DESIGN_COUNT];
};

extern int mNW_check_hide_flg(Submenu* submenu, int idx);
extern void mNW_on_hide_flg(Submenu* submenu, int idx);
extern void mNW_clear_hide_flg(Submenu* submenu);
extern int mNW_check_mark_flg(Submenu* submenu, int idx);
extern void mNW_clear_mark_flg(Submenu* submenu);
extern void mNW_swap_image_no(Submenu* submenu, int idx0, int idx1);
extern u8 mNW_get_image_no(Submenu* submenu, int idx);
extern u16* mNW_get_image_pal(Submenu* submenu, int idx);
extern u8* mNW_get_image_texture(Submenu* submenu, int idx);
extern u8* mNW_get_image_name(Submenu* submenu, int idx);
extern mNW_original_design_c* mNW_get_image_data(Submenu* submenu, int idx);
extern void mNW_draw_original(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx, int shadow_flag);
extern void mNW_next_data(Submenu* submenu);
extern void mNW_draw_sav_mark_before(GAME* game);
extern void mNW_draw_sav_mark(GAME* game, int x, int y);

extern void mNW_needlework_ovl_set_proc(Submenu* submenu);
extern void mNW_needlework_ovl_construct(Submenu* submenu);
extern void mNW_needlework_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
