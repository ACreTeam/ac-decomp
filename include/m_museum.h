#ifndef M_MUSEUM_H
#define M_MUSEUM_H

#include "types.h"
#include "m_actor_type.h"
#include "m_mail.h"
#include "m_museum_display.h"
#include "m_collision_bg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMsm_REMAIL_SLOTS 30
#define mMsm_MAX_MAIL 3
#define mMsm_DEPOSIT_FOSSIL_MAX 5

enum {
  mMsm_FOSSIL_TYPE_SINGLE,
  mMsm_FOSSIL_TYPE_MULTI,

  mMsm_FOSSIL_TYPE_NUM
};

enum {
  mMsm_REMAIL_KIND_CLEAR,
  mMsm_REMAIL_KIND_CANNOT_DONATE,
  mMsm_REMAIL_KIND_DONATED,
  mMsm_REMAIL_KIND_ALREADY_DONATED,
  mMsm_REMAIL_KIND_FOREIGNER,

  mMsm_REMAIL_KIND_NUM,
};

/* sizeof(mMsm_remail_info_c) == 0x4C */
typedef struct museum_remail_info_s {
  /* 0x00 */ u8 types[mMsm_REMAIL_SLOTS / 2]; /* display types for items */
  /* 0x10 */ mActor_name_t items[mMsm_REMAIL_SLOTS]; /* item storage */
} mMsm_remail_info_c;

/* sizeof(mMsm_record_c) == 0x4E */
typedef struct museum_record_s {
  u8 contacted:1; /* set to TRUE when the museum has contacted the player */
  u8 remail_pending:1; /* set to TRUE when the museum has non-fossil letters pending */
  u8 send_info_mail:1; /* if set to true, museum info mail will be sent */
  u8 stored_fossil_num:5; /* number of stored fossils */

  mMsm_remail_info_c remail_info; /* remail info */
} mMsm_record_c;

extern void mMsm_ClearRecord(mMsm_record_c* record);
extern void mMsm_GetMuseumMailName(Mail_nm_c* name);
extern void mMsm_SendInformationMail();
extern void mMsm_SendMuseumMail(Mail_c* mail);
extern int mMsm_GetDepositAbleNum(mActor_name_t* fg_items, mCoBG_Collision_u* col_data);
extern void mMsm_DepositItemBlock_cancel(mActor_name_t* fg_items, mActor_name_t deposit_item, mCoBG_Collision_u* col_data, u16* deposit, u16* cancel_ut, u8 valid_ut_count);
extern void mMsm_DepositItemBlock(mActor_name_t* fg_items, mActor_name_t item, int block_x, int block_z, u16* deposit, u8 valid_ut_count);
extern int mMsm_RecordDepositFossil(u8* record, mActor_name_t item, int block_x);
extern u8 mMsm_GetDepositBlockNum(u8 record);
extern void mMsm_DepositFossil(u8 deposit_record, int fossil_count, u16* cancel_ut, int send_order_info);
extern void mMsm_SetCompMail();
extern void mMsm_SendCompMail();

#ifdef __cplusplus
}
#endif

#endif
