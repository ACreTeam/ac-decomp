#ifndef M_FISHRECORD_H
#define M_FISHRECORD_H

#include "types.h"
#include "m_personal_id.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mFR_RECORD_NUM 5

typedef struct fishrecord_s {
  PersonalID_c pid;
  lbRTC_time_c time;
  int size;
} mFR_record_c;

enum {
  mFR_SIZE_SMALL,
  mFR_SIZE_MEDIUM,
  mFR_SIZE_LARGE,

  mFR_SIZE_NUM
};

extern void mEv_fishRecord_holder(PersonalID_c* winner_pid, u32* winning_size, lbRTC_ymd_c* contest_date);
extern int mEv_fishday(lbRTC_ymd_c* dates, lbRTC_time_c* now_time);
extern void mFR_fishmail();

#ifdef __cplusplus
}
#endif

#endif
