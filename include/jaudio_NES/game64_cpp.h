#ifndef GAME64_CPP_H
#define GAME64_CPP_H

#include "types.h"
#include "jaudio_NES/game64.h"

/* C++ linkage */
extern u8 angle2pan(u16 angle, f32 dist);
extern f32 distance2vol(f32 distance);

#endif
