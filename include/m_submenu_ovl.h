#ifndef M_SUBMENU_OVL_H
#define M_SUBMENU_OVL_H

#include "types.h"
#include "m_submenu_ovl_h.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct submenu_overlay_s) == 0xA04 */
struct submenu_overlay_s {
  /* TODO: finish */
  /* 0x000 */ u8 _000[0xA00 - 0x000];
  /* 0xA00 */ Mtx* projection_matrix;
};

#ifdef __cplusplus
}
#endif

#endif
