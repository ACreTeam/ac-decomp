#ifndef M_MUSHROOM_H
#define M_MUSHROOM_H

#include "types.h"
#include "m_lib.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMsr_ACTIVE_HOUR 8
#define mMsr_NUM_MUSHROOMS 5

/* sizeof(mMsr_time_c) == 6 */
typedef struct mushroom_time_s {
  /* 0x00 */ u16 year:12;
  /* 0x01 */ u16 month:4;
  /* 0x02 */ u8 day:5;
  /* 0x02 */ u8 pad0:3;
  /* 0x03 */ u8 hour:5;
  /* 0x03 */ u8 pad1:3;
  /* 0x04 */ u8 hour_quarter:4;
  /* 0x04 */ u8 active:1; /* probably a better name for this */
  /* 0x04 */ u8 pad2:3;
} mMsr_time_c;

extern void mMsr_FirstClearMushroom();
extern void mMsr_SetMushroom(xyz_t player_pos);

#ifdef __cplusplus
}
#endif

#endif
