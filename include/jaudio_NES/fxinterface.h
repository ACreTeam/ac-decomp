#ifndef _JAUDIO_FXINTERFACE_H
#define _JAUDIO_FXINTERFACE_H

#include "jaudio_NES/dspinterface.h"

typedef struct FxlineConfig_ FxlineConfig;

struct FxlineConfig_ {
	u8 enabled;             // _00
	u16 sendIdx0;           // _02
	s16 volume0;            // _04
	u16 sendIdx1;           // _06
	s16 volume1;            // _08
	s32 circularBufferSize; // _0C
	s16 filterCoeffs[8];    // _10
};

BOOL DFX_SetFxLine(u8 idx, s16* circularBufferBase, FxlineConfig* fxlineConfig);

#endif
