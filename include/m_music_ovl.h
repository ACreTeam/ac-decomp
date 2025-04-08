#ifndef M_MUSIC_OVL_H
#define M_MUSIC_OVL_H

#include "types.h"
#include "m_music_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_item_name.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMU_COL_NUM 11
#define mMU_ROW_NUM 5

struct music_ovl_s {
    u8 title[mIN_ITEM_NAME_LEN];
    s16 title_width;
    mActor_name_t title_md_item;
    u32 mark_flg[2];
};

extern void mMU_music_ovl_set_proc(Submenu* submenu);
extern void mMU_music_ovl_construct(Submenu* submenu);
extern void mMU_music_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
