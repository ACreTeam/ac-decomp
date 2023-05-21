#ifndef DVDERR_H
#define DVDERR_H

/* dvderr lives in dol, so dvderr.c is at src/dvderr.c */

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern BOOL dvderr_draw();
extern void dvderr_init();

#ifdef __cplusplus
};
#endif

#endif
