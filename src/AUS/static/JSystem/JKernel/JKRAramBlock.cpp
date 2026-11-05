#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JSupport/JSUList.h"
#include "types.h"


JKRAramBlock::JKRAramBlock(u32 address, u32 size, u32 freeSize, u8 groupID, bool isTempMem)
    : mLink(this), mAddress(address), mSize(size), mFreeSize(freeSize), mGroupID(groupID), mIsTempMemory(isTempMem)
{
}

JKRAramBlock::~JKRAramBlock()
{
    JSUList<JKRAramBlock> *list = mLink.getSupervisor();
    JSULink<JKRAramBlock> *prev = mLink.getPrev();
    if (prev)
    {
        prev->getObject()->mFreeSize += mSize + mFreeSize;
        list->remove(&mLink);
    }
    else
    {
        mFreeSize += mSize;
        mSize = 0;
    }
}

JKRAramBlock *JKRAramBlock::allocHead(u32 newSize, u8 newGroupID, JKRAramHeap *heap)
{
    u32 newAddress = mAddress + mSize;
    u32 newFreeSize = mFreeSize - newSize;
    JKRAramBlock *block = new (heap->getMgrHeap(), 0) JKRAramBlock(newAddress, newSize, newFreeSize, newGroupID, false);
    mFreeSize = 0;
    mLink.getList()->insert(mLink.getNext(), &block->mLink);
    return block;
}

JKRAramBlock *JKRAramBlock::allocTail(u32 newSize, u8 newGroupID, JKRAramHeap *heap)
{
    u32 newAddress = mAddress + mSize + mFreeSize - newSize;
    JKRAramBlock *block = new (heap->getMgrHeap(), 0) JKRAramBlock(newAddress, newSize, 0, newGroupID, true);
    mFreeSize -= newSize;
    mLink.getList()->insert(mLink.getNext(), &block->mLink);
    return block;
}