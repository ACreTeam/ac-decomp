#ifndef PLAYERCALL_H
#define PLAYERCALL_H

#include "types.h"
#include "jaudio_NES/audiostruct.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef s32 (*PlayerCallBack)(void*);

typedef struct PLAYER_CALL_ {
	PlayerCallBack callback; // _00
	void* arg;               // _04
	u32 DSP_mode;            // _08
} PLAYER_CALL;

extern void ResetPlayerCallback();
extern s32 Jac_RegisterDspPlayerCallback(PlayerCallBack callback, void* arg);
extern s32 Jac_RegisterPlayerCallback(PlayerCallBack callback, void* arg);

#ifdef __cplusplus
}
#endif

/* C++ linkage, should these go in a different header file? */
extern void PlayerCallback();
extern void DspPlayerCallback();

#endif
