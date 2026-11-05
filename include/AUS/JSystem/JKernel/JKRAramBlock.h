#ifndef JKRARAMBLOCK_H
#define JKRARAMBLOCK_H

#include "JSystem/JSupport/JSUList.h"
#include "types.h"

class JKRAramHeap;

class JKRAramBlock
{
public:
    JKRAramBlock(u32, u32, u32, u8, bool);

    virtual ~JKRAramBlock(); // _08

    JKRAramBlock *allocHead(u32, u8, JKRAramHeap *);
    JKRAramBlock *allocTail(u32, u8, JKRAramHeap *);

    void newGroupID(u8 newID) { mGroupID = newID; }
    u32 getAddress() const { return mAddress; }
    u32 getSize() const { return mSize; }

    // _00 = VTBL
    JSULink<JKRAramBlock> mLink; // _04
    u32 mAddress;                // _14
    u32 mSize;                   // _18
    u32 mFreeSize;               // _1C
    u8 mGroupID;                 // _20
    bool mIsTempMemory;          // _21
};

#endif
