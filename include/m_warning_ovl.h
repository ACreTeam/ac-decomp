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

enum {
  mWR_WARNING_MAILBOX,
  mWR_WARNING_PR_LEAVE,
  mWR_WARNING_MONEY,
  mWR_WARNING_PR_FOOD,
  mWR_WARNING_PR_QUEST,
  mWR_WARNING_5,
  mWR_WARNING_6,
  mWR_WARNING_7,
  mWR_WARNING_8,
  mWR_WARNING_PUT_MAX_FURNITURE,
  mWR_WARNING_PUT_FURNITURE,
  mWR_WARNING_PUT_ITEM,
  mWR_WARNING_PUT_PLANT,
  mWR_WARNING_HUKUBUKURO_OPEN,
  mWR_WARNING_PRESENT_MAIL,
  mWR_WARNING_WRITE,
  mWR_WARNING_MUSIC,
  mWR_WARNING_MUSIC2,
  mWR_WARNING_ORIGINAL,
  mWR_WARNING_PUT_SIGN,
  mWR_WARNING_PUT_SIGN_OTHER,
  mWR_WARNING_PUT_SIGN_ISLAND,
  mWR_WARNING_PR_CARD,
  mWR_WARNING_LOCK_DIARY,
  mWR_WARNING_PUT_FAMI,
  mWR_WARNING_WORD_OVER,
  mWR_WARNING_PW_CHK,
  mWR_WARNING_PR_FORK,

  mWR_WARNING_NUM
};

extern void mWR_warning_ovl_set_proc(Submenu* submenu);
extern void mWR_warning_ovl_init(Submenu* submenu);
extern void mWR_warning_ovl_construct(Submenu* submenu);
extern void mWR_warning_ovl_destruct(Submenu* submenu);

#define mWR_SHOW_WARNING(submenu, warning) \
  mSM_open_submenu(submenu, mSM_OVL_WARNING, warning, 0)

#ifdef __cplusplus
}
#endif

#endif
