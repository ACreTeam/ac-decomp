#ifndef M_MAIL_CHECK_OVL_H
#define M_MAIL_CHECK_OVL_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mMck_CASE_LOWER,
  mMck_CASE_UPPER,

  mMck_CASE_NUM
};

enum {
  mMck_CHECK_KEY_TYPE_A,
  mMck_CHECK_KEY_TYPE_B,
  mMck_CHECK_KEY_TYPE_C,
  mMck_CHECK_KEY_TYPE_D,
  mMck_CHECK_KEY_TYPE_E,
  mMck_CHECK_KEY_TYPE_F,
  mMck_CHECK_KEY_TYPE_G,

  mMck_CHECK_KEY_TYPE_NUM
};

extern int mMck_check_key_hit(int* len, u8* str);
extern int mMck_check_key_hit_nes(u8* str);

#ifdef __cplusplus
}
#endif

#endif
