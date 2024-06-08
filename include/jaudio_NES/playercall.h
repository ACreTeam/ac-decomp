#ifndef PLAYERCALL_H
#define PLAYERCALL_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void ResetPlayerCallback();
extern s32 Jac_RegisterDspPlayerCallback(PlayerCallBack callback, void* arg);
extern s32 Jac_RegisterPlayerCallback(PlayerCallBack callback, void* arg);


#ifdef __cplusplus
}
#endif

extern void PlayerCallback();
extern void DspPlayerCallback();

#endif
