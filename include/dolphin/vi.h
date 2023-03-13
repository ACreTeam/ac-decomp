#ifndef VI_H
#define VI_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void VISetBlack(BOOL);
extern void VIWaitForRetrace();

#ifdef __cplusplus
};
#endif

#endif
