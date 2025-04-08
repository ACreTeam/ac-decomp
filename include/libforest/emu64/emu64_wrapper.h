#ifndef EMU64_WRAPPER_H
#define EMU64_WRAPPER_H

#include "types.h"
#include "sys_ucode.h"

#ifdef __cplusplus
extern "C" {
#endif

extern u8 FrameCansel;

extern void emu64_set_ucode_info(int count, ucode_info* ucode_info);
extern void emu64_set_first_ucode(void* ucode);
extern void emu64_taskstart(Gfx* gfx);
extern void emu64_init();
extern void emu64_refresh();
extern void emu64_cleanup();

extern void emu64_texture_cache_data_entry_set(void* begin, void* end);

#ifdef __cplusplus
}
#endif

#endif
