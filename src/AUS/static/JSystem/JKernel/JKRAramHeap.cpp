#include "types.h"
#include <dolphin/os.h>
#include <JSystem/JKernel/JKRAram.h>

JSUList<JKRAramBlock> JKRAramHeap::sAramList;

JKRAramHeap::JKRAramHeap(u32 startAddress, u32 size)
{
    OSInitMutex(&mMutex);

    mHeap = JKRHeap::findFromRoot(this);
    mSize = ALIGN_PREV(size, 0x20);
    mHeadAddress = ALIGN_NEXT(startAddress, 0x20);
    mTailAddress = mHeadAddress + mSize;
    mGroupID = -1;

    JKRAramBlock *block = new (mHeap, 0) JKRAramBlock(mHeadAddress, 0, mSize, -1, false);
    sAramList.append(&block->mLink);
}

JKRAramHeap::~JKRAramHeap()
{
    JSUListIterator<JKRAramBlock> iterator(sAramList.getFirst());
    while (iterator != sAramList.getEnd())
    {
        JSUListIterator<JKRAramBlock> next = iterator++;
        delete next.getObject();
    }
}

JKRAramBlock *JKRAramHeap::alloc(u32 size, JKRAramHeap::EAllocMode allocationMode)
{
    lock();

    JKRAramBlock *block;
    if (allocationMode == JKRAramHeap::AM_Head)
        block = allocFromHead(size);
    else
        block = allocFromTail(size);

    unlock();
    return block;
}

JKRAramBlock *JKRAramHeap::allocFromHead(u32 size)
{
    u32 alignedSize = ALIGN_NEXT(size, 0x20);
    u32 bestFreeSize = 0xFFFFFFFFUL;
    JKRAramBlock *bestBlock = nullptr;

    for (JSUListIterator<JKRAramBlock> iterator = sAramList.getFirst(); iterator != sAramList.getEnd(); ++iterator)
    {
        JKRAramBlock *block = iterator.getObject();
        if (block->mFreeSize < alignedSize)
            continue;
        if (bestFreeSize <= block->mFreeSize)
            continue;

        bestFreeSize = block->mFreeSize;
        bestBlock = block;

        if (block->mFreeSize == alignedSize)
        {
            break;
        }
    }

    if (bestBlock)
    {
        return bestBlock->allocHead(alignedSize, mGroupID, this);
    }

    return nullptr;
}

JKRAramBlock *JKRAramHeap::allocFromTail(u32 size)
{
    u32 alignedSize = ALIGN_NEXT(size, 0x20);
    JKRAramBlock *tailBlock = nullptr;

    for (JSUListIterator<JKRAramBlock> iterator = sAramList.getLast(); iterator != sAramList.getEnd(); --iterator)
    {
        JKRAramBlock *block = iterator.getObject();
        if (block->mFreeSize >= alignedSize)
        {
            tailBlock = block;
            break;
        }
    }

    if (tailBlock)
    {
        return tailBlock->allocTail(alignedSize, mGroupID, this);
    }

    return nullptr;
}

/*u32 JKRAramHeap::getFreeSize(void)
{
    u32 maxFreeSize = 0;

    lock();

    JSUList<JKRAramBlock> *list = &sAramList;
    JSUListIterator<JKRAramBlock> iterator = list;
    for (; iterator != list->getEnd(); ++iterator)
    {
        if (iterator->mFreeSize > maxFreeSize)
        {
            maxFreeSize = iterator->mFreeSize;
        }
    }

    unlock();
    return maxFreeSize;
}*/

/*u32 JKRAramHeap::getTotalFreeSize()
{
    u32 totalFreeSize = 0;

    lock();

    JSUList<JKRAramBlock> *list = &sAramList;
    JSUListIterator<JKRAramBlock> iterator = list;
    for (; iterator != list->getEnd(); ++iterator)
    {
        totalFreeSize += iterator->mFreeSize;
    }

    unlock();
    return totalFreeSize;
}*/

/*void JKRAramHeap::dump()
{
    lock();

    JSUList<JKRAramBlock> *list = &sAramList;
    JSUListIterator<JKRAramBlock> iterator = list;
    for (; iterator != list->getEnd(); ++iterator)
    {
    }

    unlock();
}*/
void JKRAramHeap::dump() {
    lock();
    for (JSUListIterator<JKRAramBlock> it = sAramList.getFirst(); it != sAramList.getEnd(); ++it) {}
    unlock();
}
