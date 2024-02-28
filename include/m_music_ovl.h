#ifndef M_MUSIC_OVL_H
#define M_MUSIC_OVL_H

#include "types.h"
#include "m_music_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

struct music_ovl_s;

extern void mMU_music_ovl_set_proc(Submenu* submenu);
extern void mMU_music_ovl_construct(Submenu* submenu);
extern void mMU_music_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
