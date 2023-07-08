#ifndef M_MUSEUM_H
#define M_MUSEUM_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMsm_REMAIL_SLOTS 30

/* sizeof(mMsm_remail_display_c) = 1 */
typedef struct museum_remail_display_s {
  u8 display_type_upper:4;
  u8 display_type_lower:4;
} mMsm_remail_display_c;

/* sizeof(mMsm_remail_info_c) == 0x4C */
typedef struct museum_remail_info_s {
  /* 0x00 */ mMsm_remail_display_c types[mMsm_REMAIL_SLOTS / 2]; /* display types for items */
  /* 0x10 */ mActor_name_t items[mMsm_REMAIL_SLOTS]; /* item storage */
} mMsm_remail_info_c;

/* sizeof(mMsm_mail_info_c) == 0x4E */
typedef struct museum_mail_info_s {
  u8 contacted:1; /* set to TRUE when the museum has contacted the player */
  u8 unused:1; /* unused where this is used, if at all */
  u8 send_info_mail:1; /* if set to true, museum info mail will be sent */
  u8 stored_item_num:5; /* number of stored items */

  mMsm_remail_info_c remail_info; /* remail info */
} mMsm_mail_info_c;

extern void mMsm_SendMuseumMail(Mail_c* mail);

#ifdef __cplusplus
}
#endif

#endif
