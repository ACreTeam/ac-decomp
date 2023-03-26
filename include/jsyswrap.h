#ifndef JSYSWRAP_H
#define JSYSWRAP_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void JW_JUTReport(int pos_x, int pos_y, int show_count, const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
