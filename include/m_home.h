#ifndef M_HOME_H
#define M_HOME_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HANIWA_ITEM_HOLD_NUM 4
#define HANIWA_MESSAGE_LEN 128

/* sizeof(mHm_rmsz_c) == 6 */
typedef struct home_size_info_s {
  /* 0x00 */ u8 day;
  /* 0x01 */ u8 month;
  /* 0x02 */ u8 year;

  /* 0x04 */ u8 size:3;
  /* 0x04 */ u8 next_size:3;
  /* 0x04 */ u8 statue_rank:2;
  /* 0x05 */ u8 renew:1;
  /* 0x05 */ u8 statue_ordered:1;
  /* 0x05 */ u8 basement_ordered:1;
  /* 0x05 */ u8 pad:5;
} mHm_rmsz_c;

/* sizeof(Haniwa_Item_c) == 8 */
typedef struct home_haniwa_item_s {
  /* 0x00 */ mActor_name_t item;
  /* 0x02 */ s16 exchange_type;
  /* 0x04 */ u32 extra_data;
} Haniwa_Item_c;

/* sizeof(Haniwa_c) == 0xA4 */
typedef struct home_haniwa_s {
  /* 0x00 */ Haniwa_Item_c items[HANIWA_ITEM_HOLD_NUM];
  /* 0x20 */ u8 message[HANIWA_MESSAGE_LEN];
  /* 0xA0 */ u32 bells;
} Haniwa_c;

/* sizeof(mHm_wf_c) == 2 */
typedef struct home_wall_floor_s {
  /* 0x00 */ u8 flooring_idx;
  /* 0x01 */ u8 wallpaper_idx;
} mHm_wf_c;

/* sizeof(mHm_goki_c) == 0xA */
typedef struct home_goki_s {
  /* 0x00 */ lbRTC_time_c time;
  /* 0x08 */ u8 num;
} mHm_goki_c;

extern void mHm_ClearAllHomeInfo();

#ifdef __cplusplus
}
#endif

#endif
