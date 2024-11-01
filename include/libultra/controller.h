#ifndef LIBULTRA_CONTROLLER_H
#define LIBULTRA_CONTROLLER_H

#include "libultra/osContPad.h"
#include "libultra/libultra.h"


extern u8 __osMaxControllers;
extern int __osContinitialized;

void __osContGetInitData(u8* p, OSContStatus* s);


#endif