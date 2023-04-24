#ifndef M_NOTICE_H
#define M_NOTICE_H

#include "types.h"
#include "m_mail.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNtc_BOARD_POST_COUNT 15

/* sizeof(mNtc_board_post) == 0xC8 */
typedef struct notice_board_post_s {
  /* 0x00 */ u8 message[MAIL_BODY_LEN]; /* post contents */
  /* 0xC0 */ lbRTC_time_c post_time; /* date-time of post */
} mNtc_board_post_c;

#ifdef __cplusplus
}
#endif

#endif
