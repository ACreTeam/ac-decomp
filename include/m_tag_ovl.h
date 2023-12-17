#ifndef M_TAG_OVL_H
#define M_TAG_OVL_H

#include "types.h"
#include "m_tag_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mTG_INIT_TAG_DATA_ITEM_WIN_PROC)(Submenu*);

/* TODO */
struct tag_ovl_s {
  /* 0x000 */ u8 _000[0x2E0 - 0x000];
  /* 0x2E0 */ mTG_INIT_TAG_DATA_ITEM_WIN_PROC init_tag_data_item_win_proc;
  /* 0x2E4 */ u8 _2E4[0x3C4 - 0x2E4];
};

#ifdef __cplusplus
}
#endif

#endif
