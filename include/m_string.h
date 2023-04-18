#ifndef M_STRING_H
#define M_STRING_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mString_Load_StringFromRom(u8* buf, size_t buf_size, u32 str_no);

#ifdef __cplusplus
}
#endif

#endif
