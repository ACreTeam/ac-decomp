#ifndef M_BOARD_OVL_H
#define M_BOARD_OVL_H

#include "types.h"
#include "m_board_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mBD_MAX_WIDTH 192
#define mBD_BODY_LINE_NUM 6

enum {
  mBD_FIELD_HEADER,
  mBD_FIELD_BODY,
  mBD_FIELD_FOOTER,

  mBD_FIELD_NUM
};

enum {
  mBD_LINE_CHECK_OK,
  mBD_LINE_CHECK_NEWLINE,
  mBD_LINE_CHECK_OVERLINE,
  mBD_LINE_CHECK_OVERSTRING,

  mBD_LINE_CHECK_NUM
};

enum {
  mBD_HEADER_POS_PRE_NAME,
  mBD_HEADER_POS_ON_NAME,
  mBD_HEADER_POS_POST_NAME,

  mBD_HEADER_POS_NUM
};

struct board_ovl_s {
  u8 field;
  u8 center_line;
  u8 header_pos;
  u8 header_name_len;
  u8 first;
  u8 lengths[mBD_FIELD_NUM];
  Mail_c mail;
  Mail_c* dst_p;
  f32 ofs_x;
  f32 ofs_y;
  int _140;
  int _144;
};

extern void mBD_board_ovl_set_proc(Submenu* submenu);
extern void mBD_board_ovl_construct(Submenu* submenu);
extern void mBD_board_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
