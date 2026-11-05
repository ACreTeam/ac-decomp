#include "types.h"
#ifndef JSYSTEM_JSUPPORT_H
#define JSYSTEM_JSUPPORT_H

#include <JSystem/JSupport/JSUList.h>
#include <JSystem/JSupport/JSUStream.h>

template <typename T>
T *JSUConvertOffsetToPtr(const void *ptr, u32 offset)
{
    if (offset == 0)
    {
        return NULL;
    }
    else
    {
        return (T *)((s32)ptr + (s32)offset);
    }
}

template <typename T>
T *JSUConvertOffsetToPtr(const void *ptr, const void *offset)
{
    if (offset == NULL)
    {
        return NULL;
    }
    else
    {
        return (T *)((s32)ptr + (s32)offset);
    }
}

inline u8 JSULoByte(u16 in) { return in & 0xff; }  // gets the lower 8 bits of a 16bit input
inline u8 JSUHiByte(u16 in) { return in >> 8; }    // gets the higher 8 bits of a 16bit input
inline u8 JSULoNibble(u8 in) { return in & 0x0f; } // gets the lower 4 bits of an 8bit input
inline u8 JSUHiNibble(u8 in) { return in >> 4; }   // gets the higher 4 bits of an 8bit input
inline u16 JSULoHalf(u32 inU32) { return inU32; }

#endif
