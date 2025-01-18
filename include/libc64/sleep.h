#ifndef SLEEP_H
#define SLEEP_H

#include "types.h"
#include <dolphin/os.h>

#ifdef __cplusplus
extern "C" {
#endif

void csleep(OSTime c);
void msleep(u32);

#ifdef __cplusplus
}
#endif

#endif
