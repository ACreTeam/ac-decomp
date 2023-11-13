#ifndef M_WARNING_OVL_H
#define M_WARNING_OVL_H

#include "types.h"
#include "m_warning_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mWR_STATE_OUT,
  mWR_STATE_IN,

  mWR_STATE_NUM
};

struct warning_ovl_s {
  u8 selected;
  u8 state;
  f32 scale;
};

extern void mWR_warning_ovl_set_proc(Submenu* submenu);
extern void mWR_warning_ovl_init(Submenu* submenu);
extern void mWR_warning_ovl_construct(Submenu* submenu);
extern void mWR_warning_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
