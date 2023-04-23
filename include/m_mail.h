#ifndef M_MAIL_H
#define M_MAIL_H

#include "types.h"
#include "m_personal_id.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAIL_HEADER_LEN (32 - PLAYER_NAME_LEN)
#define MAIL_FOOTER_LEN 32
#define MAIL_BODY_LEN 192

enum {
  mMl_NAME_TYPE_PLAYER,
  mMl_NAME_TYPE_NPC,
  mMl_NAME_TYPE_MUSEUM,

  mMl_TYPE_CLEAR = 0xFF
};

/* sizeof(Mail_nm_c) == 0x16 */
typedef struct mail_nm_s {
  /* 0x00 */ PersonalID_c personalID;
  /* 0x14 */ u8 type;
} Mail_nm_c;

/* sizeof(mail_header_save_s) == 0x3A */
typedef struct mail_header_save_s {
  /* 0x00 */ s8 header_back_start;
  /* 0x01 */ u8 unknown;
  /* 0x02 */ u8 header[MAIL_HEADER_LEN];
  /* 0x1A */ u8 footer[MAIL_FOOTER_LEN];
} Mail_hs_c;

/* sizeof(Mail_hdr_c) == 0x2C */
typedef struct mail_header_s {
  /* 0x00 */ Mail_nm_c recipient;
  /* 0x16 */ Mail_nm_c sender;
} Mail_hdr_c;

/* sizeof(Mail_ct_c) == 0xFC */
typedef struct mail_content_s {
  /* 0x00 */ u8 font;
  /* 0x01 */ u8 header_back_start;
  /* 0x02 */ u8 mail_type;
  /* 0x03 */ u8 paper_type;
  /* 0x04 */ u8 header[MAIL_HEADER_LEN];
  /* 0x1C */ u8 body[MAIL_BODY_LEN];
  /* 0xDC */ u8 footer[MAIL_FOOTER_LEN];
} Mail_ct_c;

/* sizeof(Mail_c) == 0x12A */
typedef struct mail_s {
  /* 0x000 */ Mail_hdr_c header;
  /* 0x02C */ mActor_name_t present;
  /* 0x02E */ Mail_ct_c content;
} Mail_c;

#ifdef __cplusplus
}
#endif

#endif
