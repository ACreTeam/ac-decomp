#ifndef M_FISHRECORD_H
#define M_FISHRECORD_H

#include "types.h"
#include "m_personal_id.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mEv_fishRecord_holder(PersonalID_c* winner_pid, u32* winning_size, lbRTC_ymd_t* contest_date);
extern int mEv_fishday(lbRTC_ymd_t* dates, lbRTC_time_c* now_time);
extern void mFR_fishmail();

#ifdef __cplusplus
}
#endif

#endif
