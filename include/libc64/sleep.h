#ifndef SLEEP_H
#define SLEEP_H

#include "types.h"
#include "dolphin/os/OSTime.h"

void csleep(OSTime c);
void msleep(int);
#endif