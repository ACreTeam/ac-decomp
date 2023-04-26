#ifndef M_CALENDAR_H
#define M_CALENDAR_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(mCD_player_calendar_c) == 0x68 */
typedef struct calendar_player_info_s {
  /* 0x00 */ u32 played_days[lbRTC_MONTHS_MAX]; /* bitfield of days where 1 bit represents a day played */
  /* 0x30 */ u32 event_days[lbRTC_MONTHS_MAX]; /* bitfield of events where 1 bit represents an event was on that day */
  /* 0x60 */ u16 event_flags; /* flags for specific event days the player played on */
  /* 0x62 */ u8 edit; /* unsure, might have something to do with saving an edit */
  /* 0x64 */ lbRTC_year_t year; /* year calendar was last updated */
  /* 0x66 */ lbRTC_month_t month; /* month calendar was last updated */
} mCD_player_calendar_c;

#ifdef __cplusplus
}
#endif

#endif
