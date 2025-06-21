#ifndef _JAUDIO_DSP_CARDUNLOCK_H
#define _JAUDIO_DSP_CARDUNLOCK_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

int __CARDUnlock(int chan, u8 flashID[12]);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
