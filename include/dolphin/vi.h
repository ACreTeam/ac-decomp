#ifndef VI_H
#define VI_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void VISetBlack(BOOL);
void VIWaitForRetrace();
void VIConfigurePan(u16 x_origin, u16 y_origin, u16 width, u16 height);
u32 VIGetRetraceCount();

#ifdef __cplusplus
};
#endif

#endif
