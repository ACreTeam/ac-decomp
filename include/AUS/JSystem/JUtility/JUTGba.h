#ifndef JUTGBA_H
#define JUTGBA_H

#include <dolphin/os.h>
#include "types.h"

#define JUT_GBA_STACK_SIZE 0x1000

struct JUTGbaAlarm {
    OSAlarm alarm;
    OSThread* thread;
};

struct JUTGbaParam;

typedef void (*JUTGbaCallback)(JUTGbaParam*, void*);

void JUTGBAThreadAlarmHandler(OSAlarm*, OSContext*);

/**
 * @size{0x5C}
 */
struct JUTGbaParam {
    OSMessageQueue mMessageQueue; // _00
    OSMessage mMessageBuffer;     // _20
    OSMessage mCommand;           // _24
    s32 mChannel;                 // _28
    u8* mProgram;                 // _2C
    u32 mProgramLength;           // _30
    s32 mPaletteColor;            // _34
    s32 mPaletteSpeed;            // _38
    bool mIsDone;                 // _3C
    u8 _3D[3];                    // _3D
    s32 mResult;                  // _40
    u8 mStatus;                   // _44
    u8 _45[3];                    // _45
    u8* mData;                    // _48
    JUTGbaCallback mCallback;     // _4C
    void* mCallbackArg;           // _50
    u8 mIsActive;                 // _54
    u8 _55[3];                    // _55
    s32 _58;                      // _58
};

/**
 * @size{0x20}
 * @note Fabricated from the stack frame of JUTGba::gbaThreadMain.
 */
struct JUTGbaThreadVar {
    JUTGbaParam* mParam;     // _00
    u32 _04;                 // _04
    OSTime mStartTime;       // _08
    OSMessage mCommand;      // _10
    OSMessage mNextCommand;  // _14
    u32 mRetryDelay;         // _18
    BOOL mMessageReceived;   // _1C
};

class JUTGba {
public:
    static JUTGba* create(JUTGba*);
    static JUTGba* getManager() { return sManager; }

    void doJoyBoot(int, s32, s32, u8*, u32, JUTGbaCallback, void*);
    s32 resultJoyBoot(int, u8*);
    void doInitProbe(int, JUTGbaCallback, void*);
    s32 resultInitProbe(int, u32*);
    void doReset(int, JUTGbaCallback, void*);
    s32 resultReset(int, u8*);
    void doRead(int, u8*, JUTGbaCallback, void*);
    s32 resultRead(int, u8*);
    void doWrite(int, u8*, JUTGbaCallback, void*);
    s32 resultWrite(int, u8*);
    void doGetStatus(int, JUTGbaCallback, void*);
    s32 resultGetStatus(int, u8*);

private:
    static void* gbaThreadMain(void*);
    void gbaThread_sleep(OSTime);
    void gbaThread_Destroy(JUTGbaThreadVar*);
    s32 gbaThread_JoyBoot(JUTGbaThreadVar*);
    s32 gbaThread_InitProbe(JUTGbaThreadVar*);
    s32 gbaThread_Probe(JUTGbaThreadVar*);
    s32 gbaThread_Reset(JUTGbaThreadVar*);
    s32 gbaThread_Read(JUTGbaThreadVar*);
    s32 gbaThread_Write(JUTGbaThreadVar*);
    s32 gbaThread_GetStatus(JUTGbaThreadVar*);

    static JUTGba* sManager;

    OSThread mThreads[4];       // _0000
    u8 mStacks[4][JUT_GBA_STACK_SIZE] ATTRIBUTE_ALIGN(32);     // _0C60
    JUTGbaParam mParams[4];    // _4C60
} ATTRIBUTE_ALIGN(32);

#endif // JUTGBA_H
