#ifndef JUTENUM_H
#define JUTENUM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum EButtons {
    MAINSTICK_UP = 0x8000000,
    MAINSTICK_DOWN = 0x4000000,
    MAINSTICK_RIGHT = 0x2000000,
    MAINSTICK_LEFT = 0x1000000,
    CSTICK_UP = 0x80000,
    CSTICK_DOWN = 0x40000,
    CSTICK_RIGHT = 0x20000,
    CSTICK_LEFT = 0x10000,
    START = 0x1000,
    Y = 0x800,
    X = 0x400,
    B = 0x200,
    A = 0x100,
    L = 0x40,
    R = 0x20,
    Z = 0x10,
    DPAD_UP = 0x8,
    DPAD_DOWN = 0x4,
    DPAD_RIGHT = 0x2,
    DPAD_LEFT = 0x1
};

#ifdef __cplusplus
}
#endif

#endif
