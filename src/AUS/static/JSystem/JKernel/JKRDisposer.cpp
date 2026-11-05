#include "types.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRHeap.h"

JKRDisposer::JKRDisposer()
    : mPointerLinks(this)
{
    mRootHeap = JKRHeap::findFromRoot(this);
    if (mRootHeap)
        mRootHeap->appendDisposer(this);
}

JKRDisposer::~JKRDisposer()
{
    if (mRootHeap)
        mRootHeap->removeDisposer(this);
}