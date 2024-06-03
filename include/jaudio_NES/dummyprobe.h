#ifndef DUMMYPROBE_H
#define DUMMYPROBE_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Probe_Start(s32 id, const char* label);
extern void Probe_Finish(s32 id);

#ifdef __cplusplus
}
#endif

#endif
