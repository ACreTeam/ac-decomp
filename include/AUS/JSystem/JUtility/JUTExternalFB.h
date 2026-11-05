#ifndef _JSYSTEM_JUT_JUTEXTERNALFB_H
#define _JSYSTEM_JUT_JUTEXTERNALFB_H

#include <dolphin/gx.h>
#include "types.h"

struct JUTExternalFB
{
    JUTExternalFB(GXRenderModeObj *, GXGamma, void *, u32);

    GXRenderModeObj *mRenderModeObj; // _00
    u32 mSize;                       // _04
    u8 _08[4];                       // _08
    u16 _0C;                         // _0C
    u16 mGamma;                      // _0E, treat as GXGamma
    bool _10;                        // _10
};

#endif