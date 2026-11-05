#ifndef DOLPHIN_LG_H
#define DOLPHIN_LG_H

#include <dolphin/types.h>

#ifdef __cplusplus
extern "C"
{
#endif // ifdef __cplusplus

// This file presumably was for a logitech steering wheel, as it is some sort of controller handler

struct LGPosition { // seems really similar to PADStatus but is slightly different
    u16 button;
    s8 _2;
    s8 steerDirection;
    u8 gasPedal;
    u8 brakePedal;
    u8 _6; // unknown, are there any other analog buttons?(start maybe)
    u8 analogL;
    u8 analogR;
    s8 err; // -1 probably means disconnected?
};

#ifdef __cplusplus
}
#endif

#endif