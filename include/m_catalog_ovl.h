#ifndef M_CATALOG_OVL_H
#define M_CATALOG_OVL_H

#include "types.h"
#include "m_catalog_ovl_h.h"
#include "m_submenu_ovl.h"
#include "ac_furniture.h"
#include "m_item_name.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCL_MENU_ITEM_MAX 742
#define mCL_MENU_PAGE_SIZE 7
#define mCL_ITEM_DATA_NUM 2
#define mCL_TAG_STR_SIZE 10

enum {
    mCL_MENU_FTR,
    mCL_MENU_WALL,
    mCL_MENU_CARPET,
    mCL_MENU_CLOTH,
    mCL_MENU_UMBRELLA,
    mCL_MENU_PAPER,
    mCL_MENU_HANIWA,
    mCL_MENU_FOSSIL,
    mCL_MENU_MUSIC,

    mCL_MENU_NUM
};

typedef struct catalog_item_s {
    FTR_ACTOR ftr_actor;
    u8* seg0;
    u8* seg1;
    u8 segment_data[0x4820];
    aFTR_PROFILE* profile;
    int seg_ofs;
    s16 gfx_type;
    s16 timer;
    u32 price;
    f32 scale;
    f32 pos_y;
    mActor_name_t item_no;
    u16 _509A;
    u16 _509C;
} mCL_Item_c;

typedef struct catalog_menu_s {
    s16 item_count;
    s16 top_idx;
    s16 y_idx;
    u8 completed_flag;
    mActor_name_t item_list[mCL_MENU_ITEM_MAX];
    u8 item_name[mCL_MENU_PAGE_SIZE][mIN_ITEM_NAME_LEN];
} mCL_Menu_c;

struct catalog_ovl_s {
    u8 item_data_idx;
    u8 page_no;
    s16 page_timer;
    int _0004;
    mCL_Item_c item_data[mCL_ITEM_DATA_NUM];
    mCL_Menu_c menu_data[mCL_MENU_NUM];
    u8 _D9AC[72];
    u8 page_order[mCL_MENU_NUM];
    u8 change_flag;
    u8 counter;
    u8 alpha;
};

extern void mCL_catalog_ovl_set_proc(Submenu* submenu);
extern void mCL_catalog_ovl_construct(Submenu* submenu);
extern void mCL_catalog_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
