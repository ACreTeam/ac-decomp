#ifndef _JSYSTEM_JUT_JUTXFB_H
#define _JSYSTEM_JUT_JUTXFB_H

#include <dolphin/gx.h>
#include <JSystem/JKernel/JKRHeap.h>
#include "types.h"

class JUTXfb
{
public:
    enum EXfbNumber
    {
        Unset = 0,
        SingleBuffer = 1,
        DoubleBuffer = 2,
        TripleBuffer = 3
    };

    void clearIndex();
    void common_init(int);
    JUTXfb(_GXRenderModeObj const *, JKRHeap *, JUTXfb::EXfbNumber);
    ~JUTXfb();
    void delXfb(int);
    static JUTXfb *createManager(JKRHeap *, JUTXfb::EXfbNumber);
    static void destroyManager();
    void initiate(u16, u16, JKRHeap *, JUTXfb::EXfbNumber);
    u32 accumeXfbSize();

    void setBufferNum(int num) { mBufferNum = num; }
    void* getXfb(int index) const { return mBuffer[index]; }
    int getBufferNum() const { return mBufferNum; }
    int getDrawnXfbIndex() const { return mDrawnXfbIndex; }
    s16 getDrawingXfbIndex() const { return mDrawingXfbIndex; }
    s16 getDisplayingXfbIndex() const { return mDisplayingXfbIndex; }
    int getSDrawingFlag() const { return mSDrawingFlag; }

    void *getDrawnXfb() const {
        return (mDrawnXfbIndex >= 0) ? mBuffer[mDrawnXfbIndex] : nullptr;
    }

    void *getDrawingXfb() const {
        return (mDrawingXfbIndex >= 0) ? mBuffer[mDrawingXfbIndex] : nullptr;
    }

    void *getDisplayingXfb() const {
        return (mDisplayingXfbIndex >= 0) ? mBuffer[mDisplayingXfbIndex] : nullptr;
    }

    void setDisplayingXfbIndex(s16 index) { mDisplayingXfbIndex = index; }
    void setSDrawingFlag(s32 flag) { mSDrawingFlag = flag; }
    void setDrawnXfbIndex(s16 index) { mDrawnXfbIndex = index; }
    void setDrawingXfbIndex(s16 index) { mDrawingXfbIndex = index; }

    static JUTXfb *getManager() { return sManager; }

private:
    static JUTXfb *sManager;

private:
    /* 0x00 */ void *mBuffer[3];
    /* 0x0C */ bool mXfbAllocated[3];
    /* 0x10 */ int mBufferNum;
    /* 0x14 */ s16 mDrawingXfbIndex;
    /* 0x16 */ s16 mDrawnXfbIndex;
    /* 0x18 */ s16 mDisplayingXfbIndex;
    /* 0x1C */ s32 mSDrawingFlag;
};

#endif
