#ifndef _JSYSTEM_JKR_JKRTHREAD_H
#define _JSYSTEM_JKR_JKRTHREAD_H

#include <dolphin/os.h>
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "dolphin/os/OSMessage.h"
#include "types.h"

struct JKRThread;

struct JKRThreadName_
{
    s32 id;
    char *name;
};

typedef void (*JKRThreadSwitch_PreCallback)(OSThread *current, OSThread *next);
typedef void (*JKRThreadSwitch_PostCallback)(OSThread *current, OSThread *next);

class JKRThreadSwitch
{
public:
    JKRThreadSwitch(JKRHeap *);
    virtual void draw(JKRThreadName_ *param_1, JUTConsole *param_2);
    virtual void draw(JKRThreadName_ *param_1);
    virtual ~JKRThreadSwitch();

    static JKRThreadSwitch *createManager(JKRHeap *heap);

    JKRThread *enter(JKRThread *param_1, int param_2);
    static void callback(OSThread *param_1, OSThread *param_2);

    static u32 getTotalCount() { return sTotalCount; }

    static JKRThreadSwitch *getManager() { return sManager; }

private:
    static JKRThreadSwitch *sManager;
    static u32 sTotalCount;
    static u64 sTotalStart;
    static JKRThreadSwitch_PreCallback mUserPreCallback;
    static JKRThreadSwitch_PostCallback mUserPostCallback;

private:
    JKRHeap *mHeap;              // _04
    bool mSetNextHeap;           // _08
    u8 _09[3];                   // _09, padding?
    u32 _0C;                     // _0C
    u32 _10;                     // _10
    u8 _14[4];                   // _14 - unknown/padding
    s64 _18;                     // _18
    JUTConsole *mConsole;        // _20
    JKRThreadName_ *mThreadName; // _24
};

struct JKRThread : public JKRDisposer
{
    struct TLoad
    {
        inline TLoad()
        {
            mSwitchCount = 0;
            mCost = 0;
            mLastTick = 0;
            mIsValid = false;
            mThreadID = 0;
        }

        bool isValid() const { return mIsValid; }
        u32 getCost() const { return mCost; }
        u32 getCount() const { return mSwitchCount; }
        int getId() const { return mThreadID; }

        void setValid(bool valid) { mIsValid = valid; }
        void setId(int id) { mThreadID = id; }
        void setCurrentTime() { mLastTick = OSGetTick(); }

        void resetCost() { mCost = 0; }
        void resetCount() { mSwitchCount = 0; }

        void incCount() { mSwitchCount++; }
        void addCurrentCost() { mCost = mCost + (OSGetTick() - mLastTick); }

        void clear()
        {
            resetCount();
            resetCost();
            mLastTick = 0;
        }

        bool mIsValid;    // _00
        u32 mCost;        // _04
        u32 mSwitchCount; // _08
        u32 mLastTick;    // _0C
        int mThreadID;    // _10
    };

    JKRThread(u32 stackSize, int msgCount, int threadPriority);
    JKRThread(JKRHeap *, u32 stackSize, int msgCount, int threadPriority);
    JKRThread(OSThread *, int);

    virtual ~JKRThread();                   // _08
    virtual void *run(); // _0C

    void setCommon_mesgQueue(JKRHeap *, int);
    BOOL setCommon_heapSpecified(JKRHeap *, u32, int);
    static void *start(void *);
    static JSUList<JKRThread> &getList() { return (JSUList<JKRThread> &)sThreadList; }

    // unused/inlined:
    static JKRThread *searchThread(OSThread *);
    static TLoad *searchThreadLoad(OSThread *);
    void dump();

    OSThread *getThreadRecord() const { return mThreadRecord; }
    void *getStack() const { return mStackMemory; }
    TLoad *getLoadInfo() { return &mLoadInfo; }
    JKRHeap *getCurrentHeap() const { return mCurrentHeap; }
    s32 getCurrentHeapError() const { return mCurrentHeapError; }
    void resume() { OSResumeThread(mThreadRecord); }

    void setCurrentHeap(JKRHeap *heap)
    {
        /*
        JKRHeap *curHeap;
        if(heap) {
            curHeap = heap;
        }
        else {
            curHeap = JKRGetCurrentHeap();
        }
        mCurrentHeap = curHeap;
        */

        mCurrentHeap = heap ? heap : JKRGetCurrentHeap();
    }

    BOOL sendMessage(OSMessage msg)
    {
        return OSSendMessage(&mMessageQueue, msg, OS_MESSAGE_NOBLOCK);
    }

    OSMessage waitMessage(int *recieved)
    {
        OSMessage msg;
        BOOL recievedMsg = OSReceiveMessage(&mMessageQueue, &msg, OS_MESSAGE_NOBLOCK);
        if (recieved)
            *recieved = recievedMsg;

        return msg;
    }

    OSMessage waitMessageBlock()
    {
        OSMessage msg;
        OSReceiveMessage(&mMessageQueue, &msg, OS_MESSAGE_BLOCK);
        return msg;
    }

    void jamMessageBlock(OSMessage msg) {
        OSJamMessage(&mMessageQueue, msg, OS_MESSAGE_BLOCK);
    }

    static JSUList<JKRThread> sThreadList;

    // _00     = VTBL
    // _00-_18 = JKRDisposer
    JSULink<JKRThread> mThreadListLink; // _18
    JKRHeap *mHeap;                     // _28
    OSThread *mThreadRecord;            // _2C
    OSMessageQueue mMessageQueue;       // _30
    OSMessage *mMesgBuffer;             // _50
    s32 mMessageCount;                  // _54
    void *mStackMemory;                 // _58
    u32 mStackSize;                     // _5C
    TLoad mLoadInfo;                    // _60
    JKRHeap *mCurrentHeap;              // _74
    s32 mCurrentHeapError;              // _78
};

/**
 * @size{0x98}
 */
struct JKRTask : public JKRThread
{
    typedef void (*RequestCallback)(void *);

    /**
     * @fabricated
     * @size{0xC}
     */
    struct Request
    {
        RequestCallback mCb;
        void *mArg;
        void *mMsg;
    };

    JKRTask(int, int, u32); // unused/inlined

    virtual ~JKRTask();  // _08
    virtual void *run(); // _0C

    bool request(RequestCallback, void *, void *);

    static JKRTask *create(int, int, u32, JKRHeap *);

    // unused/inlined:
    Request *searchBlank();
    void requestJam(RequestCallback, void *, void *);
    void cancelAll();
    void createTaskEndMessageQueue(int, JKRHeap *);
    void destroyTaskEndMessageQueue();
    void waitQueueMessageBlock(OSMessageQueue *, int *);
    void waitQueueMessage(OSMessageQueue *, int *);

    static void destroy(JKRTask *);

    // Unused
    static OSMessage *sEndMesgBuffer;
    static u32 sEndMesgBufSize;

    // u32 _78;			 // _78
    JSULink<JKRTask> mTaskLink;    // _7C
    Request *mRequest;             // _8C - ptr to request array
    u32 mRequestCnt;               // _90 - amount of requests
    OSMessageQueue *mTaskMsgQueue; // _94

    static JSUList<JKRTask> sTaskList;
    static OSMessageQueue sEndMesgQueue; // Unused
};

/** @unused */
struct JKRIdleThread : JKRThread
{
    virtual ~JKRIdleThread(){}; // _08
    virtual void *run()         // _0C
    {
        while (true)
        {
        }
    }; 
    virtual void destroy() {} // 0x10

    static void create(JKRHeap *, int, u32);

    static JKRIdleThread *sThread;
};

#endif
