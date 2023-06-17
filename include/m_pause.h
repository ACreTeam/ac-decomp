#ifndef M_PAUSE_H
#define M_PAUSE_H

#include "types.h"
#include "libu64/pad.h"
#ifdef __cplusplus
extern "C" {
#endif


typedef struct pause_t{
   int enabled;
   int timer;
} pause_t; // size = 0x8


void Pause_ct(pause_t* pause);
int Pause_proc(pause_t* pause, pad_t* pad);

#ifdef __cplusplus
}
#endif

#endif
