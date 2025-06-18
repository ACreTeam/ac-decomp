#ifndef JUTGAMEPAD_H
#define JUTGAMEPAD_H

#include "types.h"
#include <dolphin/os.h>
#include <dolphin/pad.h>
#include "JSystem/JKernel/JKRDisposer.h"
#include "JSystem/JUtility/JUTAssertion.h"

#ifdef __cplusplus
extern "C" {

class JUTGamePadRecordBase {
  public:
    JUTGamePadRecordBase();
    virtual ~JUTGamePadRecordBase();
    virtual void read(PADStatus* status) = 0;
    virtual void write(PADStatus* status) = 0;

    bool mActive;
    /* more that are unknown */

    bool isActive() {
        return this->mActive;
    }
};

typedef void (*JUTResetBtnCb)(int, void*);
class JUTGamePad : public JKRDisposer {
  public:
    enum EPadPort { Port_unknown = -999, Port_Invalid = -1, Port1 = 0, Port2, Port3, Port4, PortRecorder };

    enum EButtons {
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

    enum EStickMode { NonClamped, Clamped };

    enum EClampMode { NoClamp, Clamp, ClampCircle };

    enum EWhichStick { WhichStick_MainStick, WhichStick_SubStick };

    JUTGamePad();
    JUTGamePad(EPadPort port);
    virtual ~JUTGamePad();

    void assign();
    void checkResetCallback(OSTime time);
    void clearForReset();
    static void init();
    void initList();
    static void read();
    static bool recalibrate(u32);
    void setButtonRepeat(u32, u32, u32);
    void update();
    void clear();

    static void checkResetSwitch();

    static bool mListInitialized;
    static u8 mPadAssign[PAD_MAX_CONTROLLERS];
    static u32 mSuppressPadReset;
    static u32 sAnalogMode;

    static void setAnalogMode(u32 mode) {
        JUTGamePad::sAnalogMode = mode;
        PADSetAnalogMode(mode);
    }

    static void setResetCallback(JUTResetBtnCb callback, void* arg) {
        C3ButtonReset::sCallback = callback;
        C3ButtonReset::sCallbackArg = arg;
    }

    static void clearResetOccurred() {
        C3ButtonReset::sResetOccurred = false;
    }

    static EClampMode getClampMode() {
        return JUTGamePad::sClampMode;
    }

    /* @HACK - This gets inlined when defined -- JSystem might have precompiled headers */
    
    static s8 getPortStatus(EPadPort port)
    {
        JUT_ASSERT(0 <= port && port < 4);
        return mPadStatus[port].err;
    }

    bool isPushing3ButtonReset() const {
        bool pushing = false;

        if (this->mPortNum != -1 && this->mButtonReset.mReset != false) {
            pushing = true;
        }

        return pushing;
    }

    int getErrorStatus() const {
        return this->mErrorStatus;
    }

    u8 getAnalogR() const {
        return this->mButtons.mAnalogR;
    }

    f32 getAnalogRf() const {
        return this->mButtons.mAnalogRf;
    }

    u8 getAnalogL() const {
        return this->mButtons.mAnalogL;
    }

    f32 getAnalogLf() const {
        return this->mButtons.mAnalogLf;
    }

    u8 getAnalogB() const {
        return this->mButtons.mAnalogB;
    }

    u8 getAnalogA() const {
        return this->mButtons.mAnalogA;
    }

    int getSubStickAngle() const {
        return this->mSubStick.mAngle;
    }

    f32 getSubStickValue() const {
        return this->mSubStick.mValue;
    }

    f32 getSubStickY() const {
        return this->mSubStick.mY;
    }

    f32 getSubStickX() const {
        return this->mSubStick.mX;
    }

    int getMainStickAngle() const {
        return this->mMainStick.mAngle;
    }

    f32 getMainStickValue() const {
        return this->mMainStick.mValue;
    }

    f32 getMainStickY() const {
        return this->mMainStick.mY;
    }

    f32 getMainStickX() const {
        return this->mMainStick.mX;
    }

    u32 getTrigger() const {
        return this->mButtons.mTrigger;
    }

    u32 getButton() const {
        return this->mButtons.mButton;
    }

    u32 getRelease() const {
        return this->mButtons.mRelease;
    }

    u32 getRepeat() const {
        return this->mButtons.mRepeat;
    }

    bool testButton(u32 mask) const {
        return this->mButtons.mButton & mask;
    }

    bool testTrigger(u32 mask) const {
        return this->mButtons.mTrigger & mask;
    }

    s16 getPortNum() const {
        return this->mPortNum;
    }

    JUTGamePadRecordBase* getPadRecord() const {
        return this->mPadRecord;
    }

    JUTGamePadRecordBase* getPadReplay() const {
        return this->mPadReplay;
    }

    class CButton {
      public:
        CButton() {
            this->clear();
        };

        void clear();
        void update(const PADStatus* padStatus, u32 buttons);
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

    class CStick {
      public:
        CStick() {
            this->clear();
        }

        void clear();
        u32 update(s8 x, s8 y, JUTGamePad::EStickMode, JUTGamePad::EWhichStick);
        u32 getButton();

        f32 mX;
        f32 mY;
        f32 mValue;
        s16 mAngle;
    };

    class CRumble {
      public:
        enum ERumble { Rumble0, Rumble1, Rumble2 };

        CRumble(JUTGamePad* gamePad) {
            this->clear(gamePad);
        }

        static u8 mStatus[PAD_MAX_CONTROLLERS];
        static u32 mEnabled;

        static void startMotor(int port);
        static void stopMotor(int port);
        static void stopMotorHard(int port);

        static bool isEnabled(u32 channel) {
            return (JUTGamePad::CRumble::mEnabled & channel) != 0;
        }

        void clear();
        void clear(JUTGamePad* gamePad);
        void update(s16);
        void setEnable(u32);

        u32 mFrame;
        u32 mLength;
        u8* mData;
        u32 mFrameCount;
    };

    class C3ButtonReset {
      public:
        C3ButtonReset() {
            mReset = false;
        }

        static u32 sResetPattern;
        static u32 sResetMaskPattern;

        static JUTResetBtnCb sCallback;
        static void* sCallbackArg;
        static OSTime sThreshold;
        static bool sResetSwitchPushing;
        static bool sResetOccurred;
        static s32 sResetOccurredPort;

        bool mReset;
    };

    static PADStatus* getPadStatus(int idx) {
        return &mPadStatus[idx];
    }

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
    s16 mPortNum;              // _78
    s8 mErrorStatus;           // _7A
    JSULink<JUTGamePad> mLink; // _7C
    JUTGamePadRecordBase* mPadRecord;
    JUTGamePadRecordBase* mPadReplay;
    u32 _94;
    C3ButtonReset mButtonReset; // _98
    OSTime mResetTime;          // _A0
};
}
#endif

#endif
