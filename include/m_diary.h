#ifndef M_DIARY_H
#define M_DIARY_H

#include "types.h"
#include "m_personal_id.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mDI_ENTRY_SIZE 992

typedef struct diary_entry_s {
  u8 text[mDI_ENTRY_SIZE];
} mDi_entry_c;

typedef struct diary_data_s {
  u16 checksum;
  mDi_entry_c entries[PLAYER_NUM][lbRTC_MONTHS_MAX];
} mDi_data_c;

extern int mDi_strlen(u8* str, int max_len, u8 end_char);

#ifdef __cplusplus
}
#endif

#endif
