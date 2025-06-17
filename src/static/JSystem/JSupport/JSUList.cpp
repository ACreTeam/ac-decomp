#include "JSystem/JSupport/JSUList.h"

JSUPtrLink::JSUPtrLink(void* pData) {
    mPtrList = 0;
    mData = pData;
    mPrev = 0;
    mNext = 0;
}

JSUPtrLink::~JSUPtrLink() {
    if (mPtrList) {
        mPtrList->remove(this);
    }
}

JSUPtrList::JSUPtrList(bool doInitialize) {
    if (doInitialize) {
        initiate();
    }
}

JSUPtrList::~JSUPtrList() {
    JSUPtrLink* curHead = mHead;

    for (int i = 0; i < mLinkCount; i++) {
        curHead->mPtrList = 0;
        curHead = curHead->mNext;
    }
}

void JSUPtrList::initiate() {
    mHead = 0;
    mTail = 0;
    mLinkCount = 0;
}

void JSUPtrList::setFirst(JSUPtrLink* pLink) {
    pLink->mPtrList = this;
    pLink->mPrev = 0;
    pLink->mNext = 0;
    mTail = pLink;
    mHead = pLink;
    mLinkCount = 1;
}

bool JSUPtrList::append(JSUPtrLink* pLink) {
    bool validity = (pLink->mPtrList == 0);

    if (!validity) {
        validity = pLink->mPtrList->remove(pLink);
    }

    if (validity) {
        if (!mLinkCount) {
            setFirst(pLink);
        } else {
            pLink->mPtrList = this;
            pLink->mPrev = mTail;
            pLink->mNext = 0;
            mTail->mNext = pLink;
            mTail = pLink;
            mLinkCount = mLinkCount + 1;
        }
    }

    return validity;
}

bool JSUPtrList::prepend(JSUPtrLink* pLink) {
    bool validity = (pLink->mPtrList == 0);

    if (!validity) {
        validity = pLink->mPtrList->remove(pLink);
    }

    if (validity) {
        if (!mLinkCount) {
            setFirst(pLink);
        } else {
            pLink->mPtrList = this;
            pLink->mPrev = 0;
            pLink->mNext = mHead;
            mHead->mPrev = pLink;
            mHead = pLink;
            mLinkCount = mLinkCount + 1;
        }
    }

    return validity;
}

bool JSUPtrList::insert(JSUPtrLink* pLink_1, JSUPtrLink* pLink_2) {
    if (pLink_1 == mHead) {
        return prepend(pLink_2);
    }
    if (!pLink_1) {
        return append(pLink_2);
    }
    if (pLink_1->mPtrList != this) {
        return false;
    }

    JSUPtrList* link2PtrList = pLink_2->mPtrList;

    bool validity = (link2PtrList == 0);

    if (!validity) {
        validity = link2PtrList->remove(pLink_2);
    }

    if (validity) {
        JSUPtrLink* prev = pLink_1->mPrev;
        pLink_2->mPtrList = this;
        pLink_2->mPrev = prev;
        pLink_2->mNext = pLink_1;
        prev->mNext = pLink_2;
        pLink_1->mPrev = pLink_2;
        mLinkCount++;
    }

    return validity;
}

bool JSUPtrList::remove(JSUPtrLink* pLink) {
    bool isSameList = (pLink->mPtrList == this);

    if (isSameList) {
        if (mLinkCount == 1) {
            mHead = 0;
            mTail = 0;
        } else if (pLink == mHead) {
            pLink->mNext->mPrev = 0;
            mHead = pLink->mNext;
        } else if (pLink == mTail) {
            pLink->mPrev->mNext = 0;
            mTail = pLink->mPrev;
        } else {
            pLink->mPrev->mNext = pLink->mNext;
            pLink->mNext->mPrev = pLink->mPrev;
        }

        pLink->mPtrList = 0;
        mLinkCount--;
    }

    return isSameList;
}

JSUPtrLink* JSUPtrList::getNthLink(u32 n) const {
    if (n >= mLinkCount) {
        return nullptr;
    }
    JSUPtrLink* curHead = mHead;
    for (int i = 0; i < n; i++) {
        curHead = curHead->mNext;
    }
    return curHead;
}
