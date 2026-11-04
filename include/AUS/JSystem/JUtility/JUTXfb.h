#ifndef _JSYSTEM_JUT_JUTXFB_H
#define _JSYSTEM_JUT_JUTXFB_H

#include <dolphin/gx.h>
#include <JSystem/JKernel/JKRHeap.h>
#include "types.h"

struct JUTExternalFB {
    JUTExternalFB(GXRenderModeObj*, GXGamma, void*, u32);

    GXRenderModeObj* mRenderModeObj; // _00
    u32 mSize;                       // _04
    u8 _08[4];                       // _08
    u16 _0C;                         // _0C
    u16 mGamma;                      // _0E, treat as GXGamma
    bool _10;                        // _10
};

class JUTXfb {
  public:
    enum EXfbNumber { Unset = 0, SingleBuffer = 1, DoubleBuffer = 2, TripleBuffer = 3 };

    void clearIndex();
    void common_init(int);
    JUTXfb(const GXRenderModeObj*, JKRHeap*, JUTXfb::EXfbNumber);
    ~JUTXfb();
    void delXfb(int);
    static JUTXfb* createManager(const GXRenderModeObj* rmode, JKRHeap*, JUTXfb::EXfbNumber);
    static void destroyManager();
    void initiate(u16, u16, JKRHeap*, JUTXfb::EXfbNumber);
    u32 accumeXfbSize();

    int getBufferNum() const {
        return mBufferNum;
    }
    int getDrawnXfbIndex() const {
        return mDrawnXfbIndex;
    }
    s16 getDrawingXfbIndex() const {
        return mDrawingXfbIndex;
    }
    s16 getDisplayingXfbIndex() const {
        return mDisplayingXfbIndex;
    }
    int getSDrawingFlag() const {
        return mSDrawingFlag;
    }

    void* getXfb(int index) const {
        return mBuffer[index];
    }

    void* getDrawnXfb() const {
        return (mDrawnXfbIndex >= 0) ? mBuffer[mDrawnXfbIndex] : nullptr;
    }

    void* getDrawingXfb() const {
        return (mDrawingXfbIndex >= 0) ? mBuffer[mDrawingXfbIndex] : nullptr;
    }

    void* getDisplayingXfb() const {
        return (mDisplayingXfbIndex >= 0) ? mBuffer[mDisplayingXfbIndex] : nullptr;
    }

    void setBufferNum(int num) {
        mBufferNum = num;
    }
    void setDisplayingXfbIndex(s16 index) {
        mDisplayingXfbIndex = index;
    }
    void setSDrawingFlag(s32 flag) {
        mSDrawingFlag = flag;
    }
    void setDrawnXfbIndex(s16 index) {
        mDrawnXfbIndex = index;
    }
    void setDrawingXfbIndex(s16 index) {
        mDrawingXfbIndex = index;
    }

    static JUTXfb* getManager() {
        return sManager;
    }

  private:
    static JUTXfb* sManager;

  private:
    void* mBuffer[3];        // 00
    bool mXfbAllocated[3];   // 0c
    int mBufferNum;          // 10
    s16 mDrawingXfbIndex;    // 14
    s16 mDrawnXfbIndex;      // 16
    s16 mDisplayingXfbIndex; // 18
    s32 mSDrawingFlag;       // 1a
};

#endif
