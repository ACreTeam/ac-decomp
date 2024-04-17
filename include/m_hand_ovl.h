#ifndef M_HAND_OVL_H
#define M_HAND_OVL_H

#include "types.h"
#include "m_hand_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*mHD_OVL_NOP_HAND_FUNC)(Submenu*);
typedef void (*mHD_OVL_SET_HAND_FUNC)(Submenu*);

/* sizeof(struct hand_ovl_s) == 0x378 */
struct hand_ovl_s {
    u8 _000[0x370 - 0x000]; /* TODO */
    mHD_OVL_NOP_HAND_FUNC nop_hand_func;
    mHD_OVL_SET_HAND_FUNC set_hand_func;
};

#ifdef __cplusplus
}
#endif

#endif
