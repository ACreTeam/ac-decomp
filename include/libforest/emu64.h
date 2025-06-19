#ifndef EMU64_H
#define EMU64_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u8 FrameCansel;

/* These might be signed */
extern void emu64_set_aflags(int idx, int value);
extern int emu64_get_aflags(int idx);

#ifdef __cplusplus
}
#endif

#endif
