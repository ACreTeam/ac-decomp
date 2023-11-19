#ifndef M_BOARD_OVL_H
#define M_BOARD_OVL_H

#include "types.h"
#include "m_board_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mBD_BODY_LINE_NUM 6

enum {
  mBD_FIELD_HEADER,
  mBD_FIELD_BODY,
  mBD_FIELD_FOOTER,

  mBD_FIELD_NUM
};

struct board_ovl_s {
  u8 field;
  u8 _01;
  u8 _02;
  u8 _03;
  u8 _04;
  u8 lengths[mBD_FIELD_NUM];
  Mail_c mail;
  Mail_c* dst_p;
  f32 ofs_x;
  f32 ofs_y;
  int _140;
  int _144;
};

#ifdef __cplusplus
}
#endif

#endif
