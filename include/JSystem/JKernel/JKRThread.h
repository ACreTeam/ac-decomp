#ifndef JKRTHREAD_H
#define JKRTHREAD_H

#include "types.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/os/OSTime.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRDisposer.h"

class JKRThread : public JKRDisposer {
public:
  JKRThread(u32 stackSize, int msgCount, int threadPrio);
  JKRThread(OSThread* osThread, int msgCount);

  virtual ~JKRThread();
  __declspec(weak) virtual void* run();

  static void* start(void* param);
  static JSUList<JKRThread>* getList() { return &JKRThread::sThreadList; }

  OSThread* getThreadRecord() const { return this->mThreadRecord; }
  void* getStack() const { return this->mStackMemory; }

  void resume() { OSResumeThread(this->mThreadRecord); }
  void jamMessageBlock(OSMessage msg) { OSJamMessage(&this->mMesgQueue, msg, OS_MESSAGE_BLOCK); }
  void sendMessage(OSMessage msg) { OSSendMessage(&this->mMesgQueue, msg, OS_MESSAGE_NOBLOCK); }

  OSMessage waitMessage(int* received) {
    OSMessage mesg;
    BOOL retrieved = OSReceiveMessage(&this->mMesgQueue, &mesg, OS_MESSAGE_NOBLOCK);
    if (received != nullptr) {
      *received = retrieved;
    }
    return mesg;
  }

  OSMessage waitMeessageBlock() {
    OSMessage mesg;
    OSReceiveMessage(&this->mMesgQueue, &mesg, OS_MESSAGE_BLOCK);
    return mesg;
  }

  static JSUList<JKRThread> sThreadList;

protected:
  JSULink<JKRThread> mLink;
  JKRHeap* mHeap;
  OSThread* mThreadRecord;
  OSMessageQueue mMesgQueue;
  OSMessage* mMesgBuffer;
  int mMesgCount;
  void* mStackMemory;
  u32 mStackSize;
};

#endif
