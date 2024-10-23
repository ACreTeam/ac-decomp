#ifndef M_CPWARNING_OVL_H
#define M_CPWARNING_OVL_H

#include "types.h"
#include "m_cpwarning_ovl_h.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

struct cpwarning_ovl_s {
    u8 _00;
    u8 _01;
    u8 move_dir;
    u8 _03;
    u8 _04;
    u8 diary_edit_mode;
    s16 _06;
    f32 scale;
    f32 _0C;
};

extern void mCW_cpwarning_ovl_construct(Submenu* submenu);
extern void mCW_cpwarning_ovl_destruct(Submenu* submenu);
extern void mCW_cpwarning_ovl_set_proc(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
