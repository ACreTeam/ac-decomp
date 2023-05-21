#ifndef GAME64_H
#define GAME64_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_InitAudio(void (*fatal_callback)(), u8* load_addr, size_t load_size, u8* bootsound, size_t bootsound_size, BOOL cut_flag);
extern void Na_GameFrame();
extern u8 Na_CheckNeosBoot();

#ifdef __cplusplus
}
#endif

#endif
