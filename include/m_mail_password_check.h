#ifndef M_MAIL_PASSWORD_CHECK_H
#define M_MAIL_PASSWORD_CHECK_H

#include "types.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMpswd_PASSWORD_KEY_IDX 1
#define mMpswd_PASSWORD_DATA_LEN 21
#define mMpswd_PASSWORD_STR_LEN 28

#define mMpswd_BITMIX_CODE_IDX 1
#define mMpswd_RSA_R_PRIME_IDX 5
#define mMpswd_RSA_INFO_IDX 15
#define mMpswd_RSA_KEYSAVE_IDX 20

#define mMpswd_SPECIAL_NPC_NUM 32

enum {
  mMpswd_CODETYPE_FAMICOM,
  mMpswd_CODETYPE_POPULAR,
  mMpswd_CODETYPE_CARD_E,
  mMpswd_CODETYPE_MAGAZINE,
  mMpswd_CODETYPE_USER,
  mMpswd_CODETYPE_CARD_E_MINI,

  mMpswd_CODETYPE_NUM
};

enum {
  mMpswd_NPCTYPE_NORMAL,
  mMpswd_NPCTYPE_SPECIAL,

  mMpswd_NPCTYPE_NUM
};

typedef struct mail_check_password_s {
  mActor_name_t item;
  u8 npc_type;
  u8 npc_code;
  u8 type;
  u8 hit_rate_index;
  u8 checksum;
  u8 str0[PLAYER_NAME_LEN];
  u8 str1[PLAYER_NAME_LEN];
} mMpswd_password_c;

extern u32 pswd_famicom_list_max;
extern u16 pswd_famicom_list[];

extern void mMpswd_make_password(
  u8* password_buf,
  int type,
  int hit_rate,
  u8* str0,
  u8* str1,
  mActor_name_t item,
  int npc_type,
  int npc_code
);

extern int mMpswd_decode_code(u8* password_data, u8* password_str);
extern int mMpswd_restore_code(u8* body, u8* password);
extern void mMpswd_password(u8* password_data, mMpswd_password_c* password);
extern int mMpswd_password_zuru_check(mMpswd_password_c* password);
extern int mMpswd_check_present_user(mActor_name_t item);
extern int mMpswd_check_present(mMpswd_password_c* password);
extern mActor_name_t mMpswd_get_sp_npc_num(int sp_npc);
extern int mMpswd_check_npc_code(mMpswd_password_c* password);
extern int mMpswd_check_name(mMpswd_password_c* password);

#ifdef __cplusplus
}
#endif

#endif
