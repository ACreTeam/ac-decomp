#ifndef JKRTHREAD_H
#define JKRTHREAD_H

#include "types.h"
#include "dolphin/os/OSMessage.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/os/OSTime.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JUtility/JUTConsole.h"

#ifdef __cplusplus
struct JKRThread;
// class JUTConsole;

struct JKRThreadName_ {
    s32 id;
    char* name;
};

typedef void (*JKRThreadSwitch_PreCallback)(OSThread* current, OSThread* next);
typedef void (*JKRThreadSwitch_PostCallback)(OSThread* current, OSThread* next);

class JKRThreadSwitch {
  public:
    JKRThreadSwitch(JKRHeap*);
    virtual void draw(JKRThreadName_* param_1, JUTConsole* param_2);
    virtual void draw(JKRThreadName_* param_1);
    virtual ~JKRThreadSwitch();

    static JKRThreadSwitch* createManager(JKRHeap* heap);

    JKRThread* enter(JKRThread* param_1, int param_2);
    static void callback(OSThread* param_1, OSThread* param_2);

    static u32 getTotalCount() {
        return sTotalCount;
    }

  private:
    static JKRThreadSwitch* sManager;
    static u32 sTotalCount;
    static u64 sTotalStart;
    static JKRThreadSwitch_PreCallback mUserPreCallback;
    static JKRThreadSwitch_PostCallback mUserPostCallback;

  private:
    JKRHeap* mHeap;              // _04
    bool mSetNextHeap;           // _08
    u8 _09[3];                   // _09, padding?
    u32 _0C;                     // _0C
    u32 _10;                     // _10
    u8 _14[4];                   // _14 - unknown/padding
    s64 _18;                     // _18
    JUTConsole* mConsole;        // _20
    JKRThreadName_* mThreadName; // _24
};

class JKRThread : public JKRDisposer {
  public:
    JKRThread(u32 stackSize, int msgCount, int threadPrio);
    JKRThread(OSThread* osThread, int msgCount);

    virtual ~JKRThread();
    virtual void* run() {
        return nullptr;
    }

    static void* start(void* param);
    static JSUList<JKRThread>* getList() {
        return &JKRThread::sThreadList;
    }

    OSThread* getThreadRecord() const {
        return this->mThreadRecord;
    }
    void* getStack() const {
        return this->mStackMemory;
    }

    void resume() {
        OSResumeThread(this->mThreadRecord);
    }
    void jamMessageBlock(OSMessage msg) {
        OSJamMessage(&this->mMesgQueue, msg, OS_MESSAGE_BLOCK);
    }
    void sendMessage(OSMessage msg) {
        OSSendMessage(&this->mMesgQueue, msg, OS_MESSAGE_NOBLOCK);
    }

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

// Unused class, function definitions from Sunshine and MKDD
class JKRTask : public JKRThread {
    typedef void (*RequestCallback)(void*);

    /**
     * @fabricated
     * @size{0xC}
     */
    struct Request {
        RequestCallback mCb;
        void* mArg;
        void* mMsg;
    };

    JKRTask(); // unused/inlined

    virtual ~JKRTask();  // _08
    virtual void* run(); // _0C

    bool request(RequestCallback, void*, void*);

    static JKRTask* create();

    // unused/inlined:
    Request* searchBlank();
    void requestJam(RequestCallback, void*, void*);
    void cancelAll();
    void createTaskEndMessageQueue(int, JKRHeap*);
    void destroyTaskEndMessageQueue();
    void waitQueueMessageBlock(OSMessageQueue*, int*);
    void waitQueueMessage(OSMessageQueue*, int*);

    OSMessage waitMessageBlock() {
        OSMessage msg;
        OSReceiveMessage(&mMesgQueue, &msg, OS_MESSAGE_BLOCK);
        return msg;
    }

    void destroy();

    // Unused
    static OSMessage* sEndMesgBuffer;
    static u32 sEndMesgBufSize;

    // u32 _78;			 // _78
    // JSULink<JKRTask> mTaskLink;    // _7C, this didn't exist yet
    Request* mRequest;             // _8C - ptr to request array
    u32 mRequestCnt;               // _90 - amount of requests
    OSMessageQueue* mTaskMsgQueue; // _94

    static JSUList<JKRTask> sTaskList;
    static u8 sEndMesgQueue[32]; // Unused
};

/** @unused */
struct JKRIdleThread : public JKRThread {
    virtual ~JKRIdleThread() {}; // _08
    virtual void* run()          // _0C
    {
        while (true) {}
    };
    virtual void destroy() {
    } // 0x10

    static void create(JKRHeap*, int, u32);

    static JKRIdleThread* sThread;
};

#endif
#endif
