#include "JSystem/JKernel/JKRThread.h"

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRMacro.h"

JSUList<JKRThread> JKRThread::sThreadList;

JKRThread::JKRThread(u32 stackSize, int msgCount, int threadPrio)
    : JKRDisposer(), mLink(this) {
  this->mHeap = JKRHeap::findFromRoot(this);
  if (this->mHeap == nullptr) {
    this->mHeap = JKRHeap::sSystemHeap;
  }

  this->mStackSize = JKR_ALIGN32(stackSize);
  this->mStackMemory = JKRHeap::alloc(this->mStackSize, 32, this->mHeap);
  this->mThreadRecord =
      (OSThread *)JKRHeap::alloc(sizeof(OSThread), 32, this->mHeap);
  OSCreateThread(this->mThreadRecord, &JKRThread::start, this,
                 (void *)((u32)this->mStackMemory + this->mStackSize),
                 this->mStackSize, threadPrio, OS_THREAD_ATTR_DETACH);
  this->mMesgCount = msgCount;
  this->mMesgBuffer = (OSMessage *)JKRHeap::alloc(
      mMesgCount * sizeof(OSMessage), 0, this->mHeap);
  OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, this->mMesgCount);
  JKRThread::sThreadList.append(&this->mLink);
}

JKRThread::JKRThread(OSThread *threadRecord, int msgCount)
    : JKRDisposer(), mLink(this) {
  this->mHeap = nullptr;
  this->mThreadRecord = threadRecord;
  this->mStackSize = (u32)threadRecord->stackEnd - (u32)threadRecord->stackBase;
  this->mStackMemory = threadRecord->stackBase;
  this->mMesgCount = msgCount;
  this->mMesgBuffer = (OSMessage *)JKRHeap::sSystemHeap->alloc(
      mMesgCount * sizeof(OSMessage), 4);
  OSInitMessageQueue(&this->mMesgQueue, this->mMesgBuffer, this->mMesgCount);
  JKRThread::sThreadList.append(&this->mLink);
}

JKRThread::~JKRThread() {
  JKRThread::sThreadList.remove(&this->mLink);

  if (this->mHeap != nullptr) {
    if (!OSIsThreadTerminated(this->mThreadRecord)) {
      OSDetachThread(this->mThreadRecord);
      OSCancelThread(this->mThreadRecord);
    }

    JKRHeap::free(this->mStackMemory, this->mHeap);
    JKRHeap::free(this->mThreadRecord, this->mHeap);
  }

  JKRHeap::free(this->mMesgBuffer, nullptr);
}

void *JKRThread::start(void *thread) {
 return static_cast<JKRThread*>(thread)->run();
}
