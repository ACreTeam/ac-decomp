#ifndef M_CPORIGINAL_OVL_H
#define M_CPORIGINAL_OVL_H

#include "types.h"
#include "m_cporiginal_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_card.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCO_PAGE_NUM 8
#define mCO_ORIGINAL_NUM 12
#define mCO_FOLDER_NAME_LEN 12
#define mCO_FOLDER_NAME_MAX_WIDTH 120

/* TODO: find a better place for this */
// typedef struct card_original_s {
//     int count;
//     u8 folder_names[mCO_PAGE_NUM][mCO_FOLDER_NAME_LEN];
//     mNW_original_design_c original[mCO_PAGE_NUM][mCO_ORIGINAL_NUM];
//     int _CC80;
// } mCD_original_c;

struct cporiginal_s {
    mCD_keep_original_c* card_original;
    u8 page_order[mCO_PAGE_NUM];
    s16 timer;
    u8 up_folder;
    u8 change_flg;
    int _10;
    u16 mark_flg;
    u16 hide_flg[mCO_PAGE_NUM];
    u8 _26;
    u8 cloth_org_no;
    u8 cloth_org_idx;
    u8 image_order[104];
};

extern int mCO_get_change_flg(void);
extern void mCO_swap_image(Submenu* submenu, mActor_name_t item0, mActor_name_t item1);
extern int mCO_change_up_folder(Submenu* submenu, int idx);
extern int mCO_top_folder(Submenu* submenu);
extern u8* mCO_get_folder_name(Submenu* submenu, int folder);
extern u8* mCO_get_image_name(Submenu* submenu, int folder, int idx);
extern int mCO_check_mark_flg(Submenu* submenu, int idx);
extern void mCO_clear_mark_flg(Submenu* submenu);
extern int mCO_check_hide_flg(Submenu* submenu, int folder, int idx);
extern void mCO_on_hide_flg(Submenu* submenu, int folder, int idx);
extern void mCO_clear_hide_flg(Submenu* submenu);
extern void mCO_draw_cporiginal(Submenu* submenu, GRAPH* graph, f32 pos_x, f32 pos_y, f32 scale, int idx,
                                int color_flag);

extern void mCO_cporiginal_ovl_construct(Submenu* submenu);
extern void mCO_cporiginal_ovl_destruct(Submenu* submenu);
extern void mCO_cporiginal_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
