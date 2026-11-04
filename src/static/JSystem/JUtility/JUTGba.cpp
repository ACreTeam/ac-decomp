#include "JSystem/JUtility/JUTGba.h"
#include "JSystem/JUtility/JUTException.h"
#include "GBA/GBAPriv.h"
#include "dolphin/pad.h"
extern "C" {
#include "dolphin/si.h"
}
#include "_mem.h"

enum {
    JUT_GBA_CMD_NONE,
    JUT_GBA_CMD_JOYBOOT,
    JUT_GBA_CMD_INIT_PROBE,
    JUT_GBA_CMD_PROBE,
    JUT_GBA_CMD_RESET,
    JUT_GBA_CMD_READ,
    JUT_GBA_CMD_WRITE,
    JUT_GBA_CMD_GET_STATUS,

    JUT_GBA_CMD_NUM
};

#define JUTGba_CMD(name) ((OSMessage)JUT_GBA_CMD_##name)

JUTGba* JUTGba::sManager;

JUTGba* JUTGba::create(JUTGba* manager) {
    if (manager != NULL) {
        sManager = manager;
    } else {
        JUTGba* newManager = new JUTGba();
        sManager = newManager;
    }

    GBAInit();
    OSReport(":::GBA: Init()\n");

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        JUTGbaParam* param = &sManager->mParams[i];
        u8* dst = reinterpret_cast<u8*>(param);

        for (u32 j = 0; j < sizeof(JUTGbaParam); j++) {
            *dst++ = 0;
        }
        param->mChannel = i;
        param->mProgram = nullptr;
        param->mProgramLength = 0;
        param->mCommand = 0;
        OSInitMessageQueue(&param->mMessageQueue, &param->mMessageBuffer, 1);
    }

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        JUTGbaParam* param = &sManager->mParams[i];
        
        OSReport(":::GBA: Create Thread %d\n", i);
        OSCreateThread(&sManager->mThreads[i], gbaThreadMain, param, &sManager->mStacks[i][JUT_GBA_STACK_SIZE], JUT_GBA_STACK_SIZE, 8, 0);
        OSResumeThread(&sManager->mThreads[i]);
    }

    return sManager;
}

void JUTGba::doJoyBoot(int chan, s32 palColor, s32 palSpeed, u8* program, u32 programSize, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mProgram = program;
    param->mProgramLength = programSize;
    param->mPaletteColor = palColor;
    param->mPaletteSpeed = palSpeed;
    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(JOYBOOT), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultJoyBoot(int chan, u8* percentp) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(JOYBOOT)) {
        return -1;
    }

    if (!param->mIsDone) {
        if (param->mResult == 1) {
            if (percentp != nullptr) {
                *percentp = 0xFF;
            }
        } else {
            if (percentp != nullptr) {
                GBAGetProcessStatus(chan, percentp);
            }
        }

        return -2;
    }

    if (param->mResult == 0) {
        if (percentp != nullptr) {
            *percentp = 100;
        }
    } else {
        if (percentp != nullptr) {
            *percentp = 0;
        }
    }

    return param->mResult;
}

void JUTGba::doInitProbe(int chan, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(INIT_PROBE), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultInitProbe(int chan, u32* result) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(INIT_PROBE)) {
        return -1;
    }

    if (param->mIsDone != true) {
        *result = 0;
        return -2;
    }

    *result = param->mResult;
    return 0;
}

void JUTGba::doReset(int chan, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(RESET), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultReset(int chan, u8* status) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(RESET)) {
        return -1;
    }

    if (param->mIsDone != true) {
        return -2;
    }

    if (param->mResult == 0 && status != nullptr) {
        *status = param->mStatus;
    }

    return param->mResult;
}

void JUTGba::doRead(int chan, u8* data, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    param->mData = data;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(READ), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultRead(int chan, u8* status) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(READ)) {
        return -1;
    }

    if (param->mIsDone != true) {
        return -2;
    }

    if (param->mResult == 0 && status != nullptr) {
        *status = param->mStatus;
    }

    return param->mResult;
}

void JUTGba::doWrite(int chan, u8* data, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    param->mData = data;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(WRITE), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultWrite(int chan, u8* status) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(WRITE)) {
        return -1;
    }

    if (param->mIsDone != true) {
        return -2;
    }

    if (param->mResult == 0 && status != nullptr) {
        *status = param->mStatus;
    }

    return param->mResult;
}

void JUTGba::doGetStatus(int chan, JUTGbaCallback callback, void* callbackArg) {
    JUTGbaParam* param = &sManager->mParams[chan];

    param->mCallback = callback;
    param->mCallbackArg = callbackArg;
    param->mIsDone = false;
    OSSendMessage(&param->mMessageQueue, JUTGba_CMD(GET_STATUS), OS_MESSAGE_BLOCK);
}

s32 JUTGba::resultGetStatus(int chan, u8* status) {
    JUTGbaParam* param = &sManager->mParams[chan];

    if (param->mCommand != JUTGba_CMD(GET_STATUS)) {
        return -1;
    }

    if (param->mIsDone != true) {
        return -2;
    }

    if (param->mResult == 0 && status != nullptr) {
        *status = param->mStatus;
    }

    return param->mResult;
}

void* JUTGba::gbaThreadMain(void* arg) {
    JUTGbaParam* param = static_cast<JUTGbaParam*>(arg);
    JUTGbaThreadVar threadVar;
    threadVar.mParam = param;

    while (true) {
        threadVar.mMessageReceived = OSReceiveMessage(&param->mMessageQueue, &threadVar.mCommand, OS_MESSAGE_NOBLOCK);
        if (threadVar.mMessageReceived == FALSE) {
            param->mIsActive = false;
            OSReceiveMessage(&param->mMessageQueue, &threadVar.mCommand, OS_MESSAGE_BLOCK);
        }

        param->mIsActive = true;
        param->mResult = 0;
        param->mCommand = threadVar.mCommand;
        threadVar.mStartTime = OSGetTime();
        threadVar.mNextCommand = JUTGba_CMD(NONE);
        threadVar.mRetryDelay = 0;

        if (threadVar.mCommand == (OSMessage)8) {
            sManager->gbaThread_Destroy(&threadVar);
            param->mIsDone = true;
            return nullptr;
        }

        while (true) {
            if (param->_58 != 0) {
                break;
            }

            if (OSGetTime() - threadVar.mStartTime > OSMillisecondsToTicks(4000)) {
                if (param->mResult != 3) {
                    param->mResult = 1;
                    param->mIsDone = true;
                }
                break;
            }

            switch ((u32)threadVar.mCommand) {
            case JUT_GBA_CMD_JOYBOOT:
                sManager->gbaThread_JoyBoot(&threadVar);
                break;
            case JUT_GBA_CMD_INIT_PROBE:
                sManager->gbaThread_InitProbe(&threadVar);
                break;
            case JUT_GBA_CMD_PROBE:
                sManager->gbaThread_Probe(&threadVar);
                break;
            case JUT_GBA_CMD_RESET:
                sManager->gbaThread_Reset(&threadVar);
                break;
            case JUT_GBA_CMD_READ:
                sManager->gbaThread_Read(&threadVar);
                break;
            case JUT_GBA_CMD_WRITE:
                sManager->gbaThread_Write(&threadVar);
                break;
            case JUT_GBA_CMD_GET_STATUS:
                sManager->gbaThread_GetStatus(&threadVar);
                break;
            default:
                JUTException::panic("JUTGba.cpp", 625, "UNKNOWN GBA COMMAND.");
                break;
            }

            if (threadVar.mNextCommand != NULL) {
                if (threadVar.mRetryDelay != 0) {
                    sManager->gbaThread_sleep(threadVar.mRetryDelay);
                }
                threadVar.mCommand = threadVar.mNextCommand;
                threadVar.mNextCommand = NULL;
            } else {
                if (param->mCallback != NULL) {
                    param->mCallback(param, param->mCallbackArg);
                }
                break;
            }
        }
    }
}

void JUTGBAThreadAlarmHandler(OSAlarm* alarm, OSContext* context) {
    JUTGbaAlarm* gba_alarm = reinterpret_cast<JUTGbaAlarm*>(alarm);
    OSResumeThread(gba_alarm->thread);
}

void JUTGba::gbaThread_sleep(OSTime length) {
    JUTGbaAlarm alarm;
    BOOL enable;

    OSCreateAlarm(&alarm.alarm);
    alarm.thread = OSGetCurrentThread();
    enable = OSDisableInterrupts();
    OSSetAlarm(&alarm.alarm, length, JUTGBAThreadAlarmHandler);
    OSSuspendThread(alarm.thread);
    OSRestoreInterrupts(enable);
}

void JUTGba::gbaThread_Destroy(JUTGbaThreadVar* threadVar) {
    threadVar->mParam->mResult = 0;
}

s32 JUTGba::gbaThread_JoyBoot(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = GBAJoyBoot(param->mChannel, param->mPaletteColor, param->mPaletteSpeed, param->mProgram, param->mProgramLength, &param->mStatus);
    if (param->mResult == 0) {
        param->mIsDone = true;
    } else if (param->mResult == 1 || param->mResult == 3) {
        threadVar->mNextCommand = threadVar->mCommand;
        threadVar->mRetryDelay = OSMillisecondsToTicks(15);
    }

    return param->mResult;
}

s32 JUTGba::gbaThread_InitProbe(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = SIProbe(param->mChannel);
    if (OSGetTime() - threadVar->mStartTime > OSMillisecondsToTicks(1000)) {
        param->mResult = 8;
        param->mIsDone = true;
    } else if (param->mResult == 0x80) {
        threadVar->mNextCommand = threadVar->mCommand;
        threadVar->mRetryDelay = OSMillisecondsToTicks(15);
    } else if (param->mResult == 8) {
        threadVar->mNextCommand = threadVar->mCommand;
        threadVar->mRetryDelay = OSMillisecondsToTicks(50);
    } else {
        param->mIsDone = true;
    }

    return param->mResult;
}

s32 JUTGba::gbaThread_Probe(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = SIProbe(param->mChannel);
    if (param->mResult == 128) {
        threadVar->mNextCommand = threadVar->mCommand;
        threadVar->mRetryDelay = OSMillisecondsToTicks(15);
    } else {
        param->mIsDone = true;
    }

    return param->mResult;
}

s32 JUTGba::gbaThread_Reset(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = GBAReset(param->mChannel, &param->mStatus);
    param->mIsDone = true;
    return param->mResult;
}

s32 JUTGba::gbaThread_Read(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = GBARead(param->mChannel, param->mData, &param->mStatus);
    param->mIsDone = true;
    return param->mResult;
}

s32 JUTGba::gbaThread_Write(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = GBAWrite(param->mChannel, param->mData, &param->mStatus);
    param->mIsDone = true;
    return param->mResult;
}

s32 JUTGba::gbaThread_GetStatus(JUTGbaThreadVar* threadVar) {
    JUTGbaParam* param = threadVar->mParam;

    param->mResult = GBAGetStatus(param->mChannel, &param->mStatus);
    param->mIsDone = true;
    return param->mResult;
}
