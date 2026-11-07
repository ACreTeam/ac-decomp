#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H
// from Super Mario Eclipse
#include "types.h"
#include <dolphin/os.h>
#include <dolphin/pad.h>
#include "JSystem/Logitech/Wheels.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JKernel/JKRDisposer.h"

// this currently is need to match testButton and testTrigger, if the entire file uses o4,p is unknown to me
#pragma push
#pragma optimize_for_size off
class JUTGamePadRecordBase
{
public:
    JUTGamePadRecordBase();
    virtual ~JUTGamePadRecordBase();
    virtual void read(PADStatus *status) = 0;
    virtual void write(PADStatus *) = 0;

    bool mActive;
    /* more that are unknown */

    bool isActive() const { return this->mActive; }
};

struct JUTGamePadLongPress
{
    static JSUList<JUTGamePadLongPress> sPatternList;
    void checkCallback(int port, u32 timer);

    u32 getMaskPattern() const { return mMaskPattern; }
    u32 getPattern() const { return mPattern; }
    bool isValid() const { return mValid; }

    u8 _0[0x10];
    bool mValid;
    bool _11;
    u32 mPattern;
    u32 mMaskPattern;
    u32 _1C;
    bool _20[PAD_MAX_CONTROLLERS];
    OSTime mTimer[PAD_MAX_CONTROLLERS];
    bool _48[PAD_MAX_CONTROLLERS];
    void (*mCallback)(int, JUTGamePadLongPress *, int);
    int _50;
};

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

    enum EClampMode
    {
        NoClamp,
        Clamp,
        ClampCircle
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
    void checkResetCallback(OSTime time);
    void clearForReset();
    static void init();
    void initList();
    static u32 read();
    static bool recalibrate(u32);
    void setButtonRepeat(u32, u32, u32);
    void update();
    void clear();

    static void checkResetSwitch();

    static bool mListInitialized;
    static u8 mPadAssign[PAD_MAX_CONTROLLERS];
    static u32 sSuppressPadReset;
    static bool sErrorReport;
    static u32 sAnalogMode;
    static u32 sRumbleSupported;
    static s32 msaSIType[PAD_MAX_CONTROLLERS]; // check type?

    static void setAnalogMode(u32 mode)
    {
        JUTGamePad::sAnalogMode = mode;
        PADSetAnalogMode(mode);
    }

    static void setResetCallback(JUTResetBtnCb callback, void *arg)
    {
        C3ButtonReset::sCallback = callback;
        C3ButtonReset::sCallbackArg = arg;
    }

    static void clearResetOccurred()
    {
        C3ButtonReset::sResetOccurred = false;
    }

    static EClampMode getClampMode()
    {
        return JUTGamePad::sClampMode;
    }

    static LGWheels *getLGWheels() { return mspLGWheels; }
    static const PADStatus *getPadStatus(EPadPort port)
    {
#line 363
        JUT_ASSERT(port < 4);
        return &mPadStatus[port];
    }

    static s8 getPortStatus(EPadPort port)
    {
        JUT_ASSERT(0 <= port && port < 4);
        return mPadStatus[port].err;
    }

    static s32 getSIType(u8 port) {
#line 528
        JUT_ASSERT(port < 4);
        return msaSIType[port];
    }

    static const LGPosition &getLGPosition(u8 port)
    {
#line 535
        JUT_ASSERT(port < 4);
        JUT_ASSERT(mspLGWheels);
        return mspLGWheels->getPosition(port);
    }

    bool isPushing3ButtonReset() const
    {
        bool pushing = false;

        if (this->mPortNum != -1 && this->mButtonReset.mReset != false)
        {
            pushing = true;
        }

        return pushing;
    }

    void checkReset() // fabricated
    {
        if (C3ButtonReset::sResetOccurred)
        {
            if (!isPushing3ButtonReset())
                clearResetOccurred();
        }
    }

    s8 getErrorStatus() const
    {
        return this->mErrorStatus;
    }

    u8 getAnalogR() const
    {
        return this->mButtons.mAnalogR;
    }

    f32 getAnalogRf() const
    {
        return this->mButtons.mAnalogRf;
    }

    u8 getAnalogL() const
    {
        return this->mButtons.mAnalogL;
    }

    f32 getAnalogLf() const
    {
        return this->mButtons.mAnalogLf;
    }

    u8 getAnalogB() const
    {
        return this->mButtons.mAnalogB;
    }

    u8 getAnalogA() const
    {
        return this->mButtons.mAnalogA;
    }

    s16 getSubStickAngle() const
    {
        return this->mSubStick.mAngle;
    }

    f32 getSubStickValue() const
    {
        return this->mSubStick.mValue;
    }

    f32 getSubStickY() const
    {
        return this->mSubStick.mY;
    }

    f32 getSubStickX() const
    {
        return this->mSubStick.mX;
    }

    int getMainStickAngle() const
    {
        return this->mMainStick.mAngle;
    }

    f32 getMainStickValue() const
    {
        return this->mMainStick.mValue;
    }

    f32 getMainStickY() const
    {
        return this->mMainStick.mY;
    }

    f32 getMainStickX() const
    {
        return this->mMainStick.mX;
    }

    u32 getTrigger() const
    {
        return this->mButtons.mTrigger;
    }

    u32 getButton() const
    {
        return this->mButtons.mButton;
    }

    u32 getRelease() const
    {
        return this->mButtons.mRelease;
    }

    u32 getRepeat() const
    {
        return this->mButtons.mRepeat;
    }

    bool testButton(u32 mask) const
    {
        return this->mButtons.mButton & mask;
    }

    bool testTrigger(u32 mask) const
    {
        return this->mButtons.mTrigger & mask;
    }

    bool testRepeat(u32 mask) const
    {
        return this->mButtons.mRepeat & mask;
    }

    int getPortNum() const
    {
        return this->mPortNum;
    }

    JUTGamePadRecordBase *getPadRecord() const
    {
        return this->mPadRecord;
    }

    JUTGamePadRecordBase *getPadReplay() const
    {
        return this->mPadReplay;
    }

    inline void stopMotorHard() {
        CRumble::stopMotorHard(this->mPortNum);
    }

    class CButton
    {
    public:
        CButton() { this->clear(); };

        void clear();
        void update(const PADStatus *padStatus, u32 buttons);
        void update(const LGPosition *padStatus, u32 buttons);
        void setRepeat(u32 mask, u32 delay, u32 frequency);

        u32 mButton;           // buttons held down
        u32 mTrigger;          // buttons newly pressed this frame
        u32 mRelease;          // buttons released this frame
        u8 mAnalogA;           //
        u8 mAnalogB;           //
        u8 mAnalogL;           // left trigger percent
        u8 mAnalogR;           // right trigger percent
        f32 mAnalogLf;         // left trigger analog percent
        f32 mAnalogRf;         // right trigger analog percent
        u32 mRepeat;           // buttons currently marked as "repeated" triggers when held
        u32 mRepeatTimer;      // frames since current button combo has been held
        u32 mRepeatLastButton; // last buttons pressed
        u32 mRepeatMask;       // button mask to allow repeating trigger inputs
        u32 mRepeatDelay;      // delay before beginning repeated input
        u32 mRepeatFrequency;  // repeat input every X frames
    };

    class CStick
    {
    public:
        CStick() {
            clear();
        }

        void clear();
        u32 update(s8 x, s8 y, JUTGamePad::EStickMode, JUTGamePad::EWhichStick); // old or non mkdd version?
        u32 update(s8 x, s8 y, JUTGamePad::EStickMode, JUTGamePad::EWhichStick, u32);
        u32 update(s8, u32);
        u32 getButton(u32);

        f32 mX;
        f32 mY;
        f32 mValue;
        s16 mAngle;
        s8 mAnalogX;
        s8 mAnalogY;
    };

    class CRumble
    {
    public:
        enum ERumble
        {
            Rumble0,
            Rumble1,
            Rumble2
        };

        CRumble(JUTGamePad *gamePad) { this->clear(gamePad); }

        static u8 mStatus[PAD_MAX_CONTROLLERS];
        static u32 mEnabled;

        static void startMotor(int port);
        static void stopMotor(int port, bool hard);
        static void stopMotorHard(int port)
        {
            stopMotor(port, true);
        }

        static bool isEnabledPort(int port) {
            return (0 <= port && port < 4) ? isEnabled(sChannelMask[port]) : false;
        } 
        static bool isEnabled(u32 channel)
        {
            return (JUTGamePad::CRumble::mEnabled & channel) ? true : false;
        }

        void clear();
        void clear(JUTGamePad *gamePad);
        void update(s16);
        void setEnable(u32);

        static u32 sChannelMask[4];

        u32 mFrame;
        u32 mLength;
        u8 *mData;
        u32 mFrameCount;
        u8 *_10;
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

        bool mReset;
    };

    static CButton& getPadButton(EPadPort port) {
        return mPadButton[port];
    }

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

    static LGWheels *mspLGWheels;
    static JSUList<JUTGamePad> mPadList;
    static CButton mPadButton[PAD_MAX_CONTROLLERS];
    static CStick mPadMStick[PAD_MAX_CONTROLLERS];
    static CStick mPadSStick[PAD_MAX_CONTROLLERS];
    static EStickMode sStickMode;
    static EClampMode sClampMode;
    static f32 sPressPoint;
    static f32 sReleasePoint;
    static PADStatus mPadStatus[PAD_MAX_CONTROLLERS];

    CButton mButtons;          // _18
    CStick mMainStick;         // _48
    CStick mSubStick;          // _58
    CRumble mRumble;           // _68
    s16 mPortNum;              // _7C
    s8 mErrorStatus;           // _7E
    JSULink<JUTGamePad> mLink; // _80
    JUTGamePadRecordBase *mPadRecord;
    JUTGamePadRecordBase *mPadReplay;
    C3ButtonReset mButtonReset; // _98
    OSTime mResetTime;          // _A0
    bool mResetEnabled;         // _A8
};
#pragma pop
#endif
