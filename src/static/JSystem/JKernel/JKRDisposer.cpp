#include "JSystem/JKernel/JKRDisposer.h"

#include "JSystem/JKernel/JKRHeap.h"

JKRDisposer::JKRDisposer() : mPointerLinks(this) {
    this->mRootHeap = JKRHeap::findFromRoot(this);
    if (this->mRootHeap != nullptr) {
        this->mRootHeap->appendDisposer(this);
    }
}

JKRDisposer::~JKRDisposer() {
    if (this->mRootHeap != nullptr) {
        this->mRootHeap->removeDisposer(this);
    }
}
