#ifndef M_MSCORE_OVL_H
#define M_MSCORE_OVL_H

#include "types.h"
#include "m_mscore_ovl_h.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mscore_ovl_s {
    u8 melody[16];
    int cursor_idx;
    int anim_frame;
    int wait_timer;
    s16 menu_idx;
    s16 scale_dir;
    f32 scale;
    u8* unused_segment_p; // only used in DnM
};

extern void mMS_mscore_ovl_construct(Submenu* submenu);
extern void mMS_mscore_ovl_destruct(Submenu* submenu);
extern void mMS_mscore_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
