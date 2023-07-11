#ifndef M_STRING_H
#define M_STRING_H

#include "types.h"
#include "lb_rtc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mString_ARTICLE_START 0x737

extern void mString_Load_StringFromRom(u8* buf, size_t buf_size, u32 str_no);
extern int mString_Load_MonthStringFromRom(u8* buf, lbRTC_month_t month);
extern int mString_Load_DayStringFromRom(u8* buf, lbRTC_day_t day);

#define mString_Load_ArticleFromRom(buf, buf_size, art) mString_Load_StringFromRom(buf, buf_size, mString_ARTICLE_START + art)

#ifdef __cplusplus
}
#endif

#endif
