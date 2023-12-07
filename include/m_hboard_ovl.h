#ifndef M_HBOARD_OVL_H
#define M_HBOARD_OVL_H

#include "types.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mHB_LINE_WIDTH_MAX 192
#define mHB_LINE_NUM 4

enum {
  mHB_LINE_CHECK_OK,
  mHB_LINE_CHECK_NEWLINE,
  mHB_LINE_CHECK_OVER_WIDTH,
  mHB_LINE_CHECK_OVER_STR_LEN,

  mHB_LINE_CHECK_NUM
};

extern void mHB_hboard_ovl_set_proc(Submenu* submenu);
extern void mHB_hboard_ovl_construct(Submenu* submenu);
extern void mHB_hboard_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
