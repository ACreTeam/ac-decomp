#ifndef _JSYSTEM_JUT_JUTGRAPHFIFO_H
#define _JSYSTEM_JUT_JUTGRAPHFIFO_H

#include "types.h"
#include <dolphin/gx.h>

struct JUTGraphFifo {
    JUTGraphFifo(u32);

    virtual ~JUTGraphFifo(); // _08

    void becomeCurrent();
    void setBreakPt();

    void getGpStatus() {
        GXGetGPStatus((GXBool*)&mGpStatus[0], (GXBool*)&mGpStatus[1], (GXBool*)&mGpStatus[2], (GXBool*)&mGpStatus[3],
                      (GXBool*)&mGpStatus[4]);
    }

    bool isGPActive() {
        getGpStatus();
        return mGpStatus[2] == false;
    }

    void save() {
        GXSaveCPUFifo(this->mFifo);
    }

    static JUTGraphFifo* sCurrentFifo;
    static GXBool mGpStatus[5];
    static bool sInitiated;

    // _00 = VTBL
    GXFifoObj* mFifo; // _04
    void* mBase;      // _08
    u32 mSize;        // _0C
    u8 _10[0xC];      // _10
};

inline void JUTCreateFifo(u32 bufSize) {
    new JUTGraphFifo(bufSize);
}

#endif
