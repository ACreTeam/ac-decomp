#ifndef M_TAG_OVL_H
#define M_TAG_OVL_H

#include "types.h"
#include "m_tag_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTG_TAG_NUM 4

typedef void (*mTG_INIT_TAG_DATA_ITEM_WIN_PROC)(Submenu*);
typedef void (*mTG_CHG_TAG_FUNC_PROC)(Submenu*, int, int, int, f32, f32);

/* sizeof(mTG_tag_c) == 0xB4 */
typedef struct tag_s {
    u8 type;
    u8 _01[0x40 - 0x01];
    int _40;
    u8 _44[0xB4 - 0x44];
} mTG_tag_c;

/* TODO */
struct tag_ovl_s {
    /* 0x000 */ int sel_tag_idx;
    /* 0x004 */ int ret_tag_idx;
    /* 0x008 */ mTG_tag_c tags[mTG_TAG_NUM];
    /* 0x2D8 */ void* _2D8;
    /* 0x2DC */ void* _2DC;
    /* 0x2E0 */ mTG_INIT_TAG_DATA_ITEM_WIN_PROC init_tag_data_item_win_proc;
    /* 0x2E4 */ mTG_CHG_TAG_FUNC_PROC chg_tag_func_proc;
    /* 0x2E8 */ u8 _2E8[0x3C4 - 0x2E8];
};

#ifdef __cplusplus
}
#endif

#endif
