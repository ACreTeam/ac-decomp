#ifndef M_HOME_H
#define M_HOME_H

#include "types.h"
#include "m_field_make.h"
#include "m_actor_type.h"
#include "m_personal_id.h"
#include "audio.h"
#include "lb_rtc.h"
#include "m_mail.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HOME_MAILBOX_SIZE 10
#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 128

/* sizeof(mHm_rmsz_c) == 6 */
typedef struct home_size_info_s {
  /* 0x00 */ struct {
    /* 0x00 */ u8 day;
    /* 0x01 */ u8 month;
    /* 0x02 */ u16 year;
  } upgrade_order_date; /* date you ordered an upgrade, seems to be a struct */

  /* 0x04 */ u8 size:3; /* current house size */
  /* 0x04 */ u8 next_size:3; /* next house size when upgrade is ordered */
  /* 0x04 */ u8 statue_rank:2; /* statue ranking, 0 = gold, 1 = silver, 2 = bronze, 3 = jade */
  /* 0x05 */ u8 renew:1; /* refresh house size & 'outlook' palette */
  /* 0x05 */ u8 statue_ordered:1; /* set when statue is ordered from Nook */
  /* 0x05 */ u8 basement_ordered:1; /* set when basement has been ordered */
  /* 0x05 */ u8 pad:5; /* unused? */
} mHm_rmsz_c;

/* sizeof(Haniwa_Item_c) == 8 */
typedef struct home_haniwa_item_s {
  /* 0x00 */ mActor_name_t item; /* held item */
  /* 0x02 */ s16 exchange_type; /* type of exchange (sale, free, trade) */
  /* 0x04 */ u32 extra_data; /* trade related data */
} Haniwa_Item_c;

/* sizeof(Haniwa_c) == 0xA4 */
typedef struct home_haniwa_s {
  /* 0x00 */ Haniwa_Item_c items[HANIWA_ITEM_HOLD_NUM]; /* held items */
  /* 0x20 */ u8 message[HANIWA_MESSAGE_LEN]; /* message for visitors */
  /* 0xA0 */ u32 bells; /* held bells from selling items */
} Haniwa_c;

/* sizeof(mHm_wf_c) == 2 */
typedef struct home_wall_floor_s {
  /* 0x00 */ u8 flooring_idx;
  /* 0x01 */ u8 wallpaper_idx;
} mHm_wf_c;

/* sizeof(mHm_goki_c) == 0xA */
typedef struct home_goki_s {
  /* 0x00 */ lbRTC_time_c time; /* last time updated */
  /* 0x08 */ u8 num; /* number of cockroaches in the house */
} mHm_goki_c;

/* sizeof(mHm_lyr_c) == 0x228 */
typedef struct home_layer_s {
  /* 0x000 */ mActor_name_t items[UT_Z_NUM][UT_X_NUM]; /* Furniture item actors */
  /* 0x200 */ u64 ftr_switch; /* Bitfield for controlling which furniture items are active, max of 64 */
  /* 0x208 */ u32 unk_208[8]; /* Only referenced in mISL_gc_to_agb_layer */
} mHm_lyr_c;

/* sizeof(mHm_flr_c) == 0x8A8 */
typedef struct home_floor_s {
  /* 0x000 */ mHm_lyr_c layer_main;
  /* 0x228 */ mHm_lyr_c layer_secondary; /* Also storage layer 0 */
  /* 0x450 */ mHm_lyr_c layer_storage1;
  /* 0x678 */ mHm_lyr_c layer_storage2;
  /* 0x8A0 */ mHm_wf_c wall_floor;
  /* 0x8A2 */ TempoBeat_c tempo_beat;
  /* 0x8A4 */ struct {
    u8 wall_original:1; /* is wallpaper a pattern (original)? */
    u8 floor_original:1; /* is flooring a pattern (original)? */
    u8 bit_2_7:6; /* unused? */
  } fllot_bit; /* Name exposed? by mISL_gc_to_agb_fllot_bit */
} mHm_flr_c;

/* sizeof(mHm_hs_c) == 0x26B0 */
typedef struct home_s {
  /* 0x0000 */ PersonalID_c ownerID; /* owner player's ID */
  /* 0x0014 */ u8 unk_14[6];
  /* 0x001A */ u8 haniwa_tempo[2]; /* unsure about this */
  /* 0x001C */ lbRTC_ymd_t hra_mark_time; /* last HRA judge date */
  /* 0x0020 */ u32 hra_mark_info; /* bitfield of HRA info pulled when HRA mails letter */
  /* 0x0024 */ struct {
    u8 house_updated:1; /* signals HRA to re-score house */
    u8 has_saved:1; /* whether or not the player has saved at this house before */
    u8 hra_member:1; /* whether or not the house has been setup for HRA membership */
    u8 has_basement:1; /* set when the basement is built */
    u8 bit_4:1; /* unused */
    u8 bit_5:1; /* unused */
    u8 bit_6:1; /* unused */
    u8 bit_7:1; /* unused */
  } flags;
  /* 0x0026 */ mHm_rmsz_c size_info; /* home size info */
  /* 0x002C */ u8 outlook_pal; /* current house palette */
  /* 0x002D */ u8 ordered_outlook_pal; /* house palette ordered at Nook's via upgrade */
  /* 0x002E */ u8 next_outlook_pal; /* next house palette set via all other means (villager, Wisp, paint @ Nook's, ...) */
  /* 0x002F */ u8 door_original; /* player design shown on door, apparently called 'original', maybe 'original design'? */
  /* 0x0030 */ u8 unk_30[8]; /* unused? */
  /* 0x0038 */ mHm_flr_c main_floor; /* main floor */
  /* 0x08E0 */ mHm_flr_c upper_floor; /* second floor */
  /* 0x1188 */ mHm_flr_c basement; /* basement floor */
  /* 0x1A30 */ Mail_c mailbox[HOME_MAILBOX_SIZE]; /* mailbox */
  /* 0x25D4 */ Haniwa_c haniwa; /* gyroid info */
  /* 0x2678 */ mHm_goki_c goki; /* cockroach info */
  /* 0x2684 */ u32 music_box[2]; /* bitfield of inserted music */
  /* 0x268C */ u8 unk_286C[36]; /* unused? */
} mHm_hs_c;

extern void mHm_ClearAllHomeInfo();

#ifdef __cplusplus
}
#endif

#endif
