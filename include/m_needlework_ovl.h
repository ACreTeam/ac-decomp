#ifndef M_NEEDLEWORK_OVL_H
#define M_NEEDLEWORK_OVL_H

#include "types.h"
#include "m_submenu.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u8 mNW_get_image_no(Submenu* submenu, int slot_no);
extern int mNW_check_hide_flg(Submenu* submenu, int idx);
extern void mNW_on_hide_flg(Submenu* submenu, int idx);
extern void mNW_clear_hide_flg(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
