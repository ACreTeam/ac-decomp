#ifndef OSFONT_H
#define OSFONT_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OS_FONT_ANSI 0u
#define OS_FONT_SJIS 1u

u16 OSGetFontEncode();

#ifdef __cplusplus
}
#endif

#endif
