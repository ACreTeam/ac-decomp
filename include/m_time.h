#ifndef M_TIME_H
#define M_TIME_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mTM_MIN_YEAR 2001
#define mTM_MAX_YEAR 2030

enum {
  mTM_SEASON_BEGIN = 0,
  mTM_SEASON_SPRING = mTM_SEASON_BEGIN,
  mTM_SEASON_SUMMER,
  mTM_SEASON_AUTUMN,
  mTM_SEASON_WINTER,
  mTM_SEASON_NUM
};

enum {
  mTM_TERM_BEGIN = 0,
  mTM_TERM_0 = mTM_TERM_BEGIN,
  mTM_TERM_1,
  mTM_TERM_2,
  mTM_TERM_3,
  mTM_TERM_4,
  mTM_TERM_5,
  mTM_TERM_6,
  mTM_TERM_7,
  mTM_TERM_8,
  mTM_TERM_9,
  mTM_TERM_10,
  mTM_TERM_11,
  mTM_TERM_12,
  mTM_TERM_13,
  mTM_TERM_14,
  mTM_TERM_15,
  mTM_TERM_16,
  mTM_TERM_17,
  mTM_TERM_NUM
};

#define mTM_RENEW_TIME_NONE 0
#define mTM_RENEW_TIME_ALL 0xFF

enum {
  mTM_RENEW_TIME_BEGIN = 0,
  mTM_RENEW_TIME_WEATHER = mTM_RENEW_TIME_BEGIN,
  mTM_RENEW_TIME_DAILY
};

#define mTM_SECONDS_IN_MINUTE 60
#define mTM_SECONDS_IN_HOUR 60*60
#define mTM_SECONDS_IN_HALFDAY 12*60*60
#define mTM_SECONDS_IN_DAY 24*60*60

typedef struct time_calendar_term_s {
  lbRTC_month_t month;
  lbRTC_day_t day;
  u16 season;
  s16 bgitem_profile;
  s16 bgitem_bank;
} mTM_calendar_term_t;

extern const lbRTC_time_c mTM_rtcTime_clear_code;
extern const lbRTC_ymd_t mTM_rtcTime_ymd_clear_code;
extern const lbRTC_time_c mTM_rtcTime_default_code;

#ifdef __cplusplus
}
#endif

#endif
