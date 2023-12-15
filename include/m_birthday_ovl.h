#ifndef M_BIRTHDAY_OVL_H
#define M_BIRTHDAY_OVL_H

#include "types.h"
#include "m_birthday_ovl_h.h"
#include "m_submenu_ovl.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mBR_Ovl_IDX_MONTH,
  mBR_Ovl_IDX_DAY,
  mBR_Ovl_IDX_DATE_NUM,

  mBR_Ovl_IDX_OK = mBR_Ovl_IDX_DATE_NUM,
  mBR_Ovl_IDX_NUM
};

struct birthday_ovl_s {
  u16 birthday_data[mBR_Ovl_IDX_DATE_NUM];
  int idx;
};

extern void mBR_birthday_ovl_set_proc(Submenu* submenu);
extern void mBR_birthday_ovl_construct(Submenu* submenu);
extern void mBR_birthday_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
