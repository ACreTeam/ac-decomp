#ifndef M_STRING_DATA_H
#define M_STRING_DATA_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mString_AM 0x001
#define mString_PM 0x002
#define mString_WEEKDAY_START 0x009
#define mString_RESETTI_GOOD_WORD_START 0x484
#define mString_RESETTI_GOOD_WORD_END 0x493
#define mString_RESETTI_NG_WORD_START 0x4C0
#define mString_RESETTI_NG_WORD_END 0x4DF
#define mString_DAY_START 0x64E
#define mString_MONTH_START 0x66D
#define mString_SONCHO_EVENT_NAME_START 0x6F8
#define mString_ARTICLE_START 0x737
#define mString_HANIWA_MSG0 0x76A
#define mString_HANIWA_MSG1 0x76B
#define mString_HANIWA_MSG2 0x76C
#define mString_HANIWA_MSG3 0x76D
#define mString_MIKANBOX_START 0x77B
#define mString_MIKANBOX_END 0x7FE

// TODO: these should be in m_msg_data.h
#define mString_CARPETPEDDLER_START 0x48a
#define mString_TOTAKEKE_START 0x1b93
#define mString_SPEECH_SONCHO_START 0x3db5

#ifdef __cplusplus
}
#endif

#endif
