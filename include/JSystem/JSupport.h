#ifndef JSYSTEM_JSUPPORT_H
#define JSYSTEM_JSUPPORT_H

#include "types.h"

inline u8 JSULoByte(u16 in) {
    return in & 0xff;
}
inline u8 JSUHiByte(u16 in) {
    return in >> 8;
}

#endif
