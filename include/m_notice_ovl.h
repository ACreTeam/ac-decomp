#ifndef M_NOTICE_OVL_H
#define M_NOTICE_OVL_H

#include "types.h"
#include "m_notice_ovl_h.h"
#include "m_submenu_ovl.h"
#include "m_notice.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNT_MAX_WIDTH 192
#define mNT_MAX_LINES 6

enum {
  mNT_PLAY_PAGE_READ,
  mNT_PLAY_PAGE_MOVE,
  mNT_PLAY_PAGE_TO_WRITE,
  mNT_PLAY_PAGE_TO_READ,

  mNT_PLAY_PAGE_NUM
};

enum {
  mNT_LINE_CHECK_OK,
  mNT_LINE_CHECK_NEWLINE,
  mNT_LINE_CHECK_OVERLINE,
  mNT_LINE_CHECK_OVERSTRING,

  mNT_LINE_CHECK_NUM
};

struct notice_ovl_s {
  u8 mode;
  u8 stick_area;
  u8 page_center;
  u8 page_count;
  u8 now_page;
  u8 disp_page;
  u8 move_time;
  mNtc_board_post_c post;
  f32 control_position;
};

extern void mNT_notice_ovl_set_proc(Submenu* submenu);
extern void mNT_notice_ovl_construct(Submenu* submenu);
extern void mNT_notice_ovl_destruct(Submenu* submenu);

#ifdef __cplusplus
}
#endif

#endif
