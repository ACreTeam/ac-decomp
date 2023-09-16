#ifndef M_CALENDAR_H
#define M_CALENDAR_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mCD_FLAG_MOTHERS_DAY (1 << 0)
#define mCD_FLAG_TOWN_DAY (1 << 1)
#define mCD_FLAG_METEOR_SHOWER (1 << 2)
#define mCD_FLAG_FOUNDERS_DAY (1 << 3)
#define mCD_FLAG_HARVEST_MOON_9 (1 << 4)
#define mCD_FLAG_HARVEST_MOON_10 (1 << 5)
#define mCD_FLAG_OFFICERS_DAY (1 << 6)

/* sizeof(mCD_player_calendar_c) == 0x68 */
typedef struct calendar_player_info_s {
  /* 0x00 */ u32 played_days[lbRTC_MONTHS_MAX]; /* bitfield of days where 1 bit represents a day played */
  /* 0x30 */ u32 event_days[lbRTC_MONTHS_MAX]; /* bitfield of events where 1 bit represents an event was on that day */
  /* 0x60 */ u16 event_flags; /* flags for specific event days the player played on */
  /* 0x62 */ u8 edit; /* unsure, might have something to do with saving an edit */
  /* 0x63 */ u8 pad_63; /* only checked in save data validation? */
  /* 0x64 */ lbRTC_year_t year; /* year calendar was last updated */
  /* 0x66 */ lbRTC_month_t month; /* month calendar was last updated */
} mCD_player_calendar_c;

extern void mCD_calendar_clear(int player_no);
extern void mCD_calendar_check_delete(int player_no, lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day);
extern void mCD_calendar_wellcome_on();
extern void mCD_calendar_event_on(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, u8 event);
extern int mCD_calendar_event_check(lbRTC_year_t year, lbRTC_month_t month, lbRTC_day_t day, int player_no, u8 event);

#ifdef __cplusplus
}
#endif

#endif
