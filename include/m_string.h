#ifndef M_STRING_H
#define M_STRING_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mString_Load_StringFromRom(u8* buf, size_t buf_size, u32 str_no);
extern int mString_Load_MonthStringFromRom(u8* buf, lbRTC_month_t month);
extern int mString_Load_DayStringFromRom(u8* buf, lbRTC_day_t day);

#ifdef __cplusplus
}
#endif

#endif
