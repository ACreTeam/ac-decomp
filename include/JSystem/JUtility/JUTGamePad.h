#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include "types.h"
#include "dolphin/os.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/pad.h"
#include "JSystem/JKernel/JKRDisposer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*JUTResetBtnCb)(int, void*);
class JUTGamePad : public JKRDisposer
{
public:
    enum EPadPort
    {
        Port_unknown = -999,
        Port_Invalid = -1,
        Port1 = 0,
        Port2,
        Port3,
        Port4,
        PortRecorder
    };

    enum EButtons
    {
        MAINSTICK_UP = 0x8000000,
        MAINSTICK_DOWN = 0x4000000,
        MAINSTICK_RIGHT = 0x2000000,
        MAINSTICK_LEFT = 0x1000000,
        CSTICK_UP = 0x80000,
        CSTICK_DOWN = 0x40000,
        CSTICK_RIGHT = 0x20000,
        CSTICK_LEFT = 0x10000,
        START = 0x1000,
        Y = 0x800,
        X = 0x400,
        B = 0x200,
        A = 0x100,
        L = 0x40,
        R = 0x20,
        Z = 0x10,
        DPAD_UP = 0x8,
        DPAD_DOWN = 0x4,
        DPAD_RIGHT = 0x2,
        DPAD_LEFT = 0x1
    };

    enum EStickMode
    {
        NonClamped,
        Clamped
    };

    enum EWhichStick
    {
        WhichStick_MainStick,
        WhichStick_SubStick
    };

    JUTGamePad();
    JUTGamePad(EPadPort port);
    virtual ~JUTGamePad();

    void assign();
    void checkResetSwitch();
    void clearForReset();
    static void init();
    void initList();
    void read();
    static bool recalibrate(u32);
    void setButtonRepeat(u32, u32, u32);
    void update();

    static void setResetCallback(JUTResetBtnCb callback, void *param_0)
    {
        C3ButtonReset::sCallback = callback;
        C3ButtonReset::sCallbackArg = param_0;
    }


    bool testButton(u32 mask) const {
        return mButtons.mButton & mask;
    }

    bool testTrigger(u32 mask) const {
        return mButtons.mTrigger & mask;
    }

    class CButton
    {
    public:
        CButton();

        void clear();
        void update(const PADStatus*, u32);
        void setRepeat(u32, u32, u32);

        u32 mButton; // _0
        u32 mTrigger;
        u32 mRelease;
        u8 mAnalogA;  // _C
        u8 mAnalogB;  // _D
        u8 mAnalogL; // _E
        u8 mAnalogR; // _F
        f32 mAnalogLf; // _10
        f32 mAnalogRf; // _14
        u32 mRepeat;
        u32 _1C;
        u32 _20;
        u32 _24;
        u32 _28;
        u32 _2C;
    };

    class CStick
    {
    public:
        CStick();

        void clear();
        u32 update(s8 x, s8 y, JUTGamePad::EStickMode, JUTGamePad::EWhichStick);
        u32 update(s8 x, s8 y, JUTGamePad::EStickMode, JUTGamePad::EWhichStick, u32);
        u32 getButton();

        f32 mStickX;
        f32 mStickY;
        f32 mValue;
        s16 mAngle;
    };

    class CRumble
    {
    public:
        void clear(JUTGamePad*);
        static void stopMotor(s32);
        static void stopMotorHard(s32);
        void update(u16);
        void setEnable(u32);

        u32 _0;
        u32 _4;
        u32 _8;
        u32 _C;
    };

    class C3ButtonReset {
    public:
        C3ButtonReset() { mReset = false; }

        static u32 sResetPattern;
        static u32 sResetMaskPattern;
        static JUTResetBtnCb sCallback;
        static void *sCallbackArg;
        static OSTime sThreshold;
        static s32 sResetOccurredPort;
        static bool sResetOccurred;
        static bool sResetSwitchPushing;

    private:
        bool mReset;
    };

    static bool isPadOk() { // fabricated
        bool ret = false;
        switch(mPadStatus[0].err) {
        case -1:
        case 0:
            ret = true;
            break;
        }
        return ret;        
    }

    static PADStatus *getPadStatus(int idx) { return &mPadStatus[idx]; }

    static EStickMode sStickMode;

    static PADStatus mPadStatus[4];

    CButton mButtons;     // _18
    CStick mMainStick; // _48
    CStick mSubStick;       // _58
    CRumble mRumble;      // _68
    u16 mPort;            // _78
    s8 mErrorStatus;      // _7A
    JSULink<JUTGamePad> mPtrLink;  // _7C
    u32 _8C;
    u32 _90;
    u32 _94;
    C3ButtonReset mButtonReset;     // _98
    u8 _99;
    u8 _9A;
    u8 _9B;
    u8 _9C;
    u8 _9D;            // padding?
    u8 _9E;            // ^^
    u8 _9F;            // ^^
    OSTime mResetTime; // _A0
};

#ifdef __cplusplus
}
#endif

#endif
