#ifndef EMU64_H
#define EMU64_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u8 FrameCansel;

/* These might be signed */
extern void emu64_set_aflags(u32 idx, u32 value);
extern int emu64_get_aflags(u32 idx);

#ifdef __cplusplus
}
#endif

#endif
