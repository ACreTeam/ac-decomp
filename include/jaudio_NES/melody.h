#ifndef MELODY_H
#define MELODY_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void Na_Inst(u16, u8*);
extern void Na_FurnitureInst(int,s8,s32,u16,f32);
extern int Na_InstCountGet();



#ifdef __cplusplus
}
#endif

#endif