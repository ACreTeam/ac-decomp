#ifndef M_STRING_H
#define M_STRING_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mString_MAX_STR 0x7FF

#define mString_AM 0x001
#define mString_PM 0x002
#define mString_WEEKDAY_START 0x009
#define mString_DAY_START 0x64E
#define mString_MONTH_START 0x66D
#define mString_ARTICLE_START 0x737
#define mString_HANIWA_MSG0 0x76A
#define mString_HANIWA_MSG1 0x76B
#define mString_HANIWA_MSG2 0x76C
#define mString_HANIWA_MSG3 0x76D


extern void mString_aram_init();
extern void mString_Load_StringFromRom(u8* dst, int dst_len, int str_no);
extern int mString_Load_YearStringFromRom(u8* dst, lbRTC_year_t year);
extern int mString_Load_MonthStringFromRom(u8* dst, lbRTC_month_t month);
extern int mString_Load_WeekStringFromRom(u8* dst, lbRTC_weekday_t weekday);
extern int mString_Load_DayStringFromRom(u8* dst, lbRTC_day_t day);
extern int mString_Load_HourStringFromRom(u8* dst, lbRTC_hour_t hour);
extern int mString_Load_HourStringFromRom2(u8* dst, lbRTC_hour_t hour);
extern int mString_Load_MinStringFromRom(u8* dst, lbRTC_min_t min);
extern int mString_Load_SecStringFromRom(u8* dst, lbRTC_sec_t sec);
extern int mString_Load_NumberStringAddUnitFromRom(u8* dst, u16 num, int str_no);

#define mString_Load_ArticleFromRom(buf, buf_size, art) mString_Load_StringFromRom(buf, buf_size, mString_ARTICLE_START + art)

#ifdef __cplusplus
}
#endif

#endif
