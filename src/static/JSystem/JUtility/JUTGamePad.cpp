#include "JSystem/JUtility/JUTGamePad.h"

#include <dolphin/pad.h>
#include "MSL_C/w_math.h"
#include "MSL_C/math.h"

static u32 channel_mask[PAD_MAX_CONTROLLERS] = { 0x80000000 >> 0, 0x80000000 >> 1, 0x80000000 >> 2, 0x80000000 >> 3 };

JUTGamePad::EStickMode JUTGamePad::sStickMode = Clamped;
u32 JUTGamePad::C3ButtonReset::sResetPattern = START | X | B;
f32 JUTGamePad::sPressPoint = 0.5f;
f32 JUTGamePad::sReleasePoint = 0.25f;
u32 JUTGamePad::C3ButtonReset::sResetMaskPattern = 0xFFFF;

JSUList<JUTGamePad> JUTGamePad::mPadList(false);
PADStatus JUTGamePad::mPadStatus[PAD_MAX_CONTROLLERS];
JUTGamePad::CButton JUTGamePad::mPadButton[PAD_MAX_CONTROLLERS];
JUTGamePad::CStick JUTGamePad::mPadMStick[PAD_MAX_CONTROLLERS];
JUTGamePad::CStick JUTGamePad::mPadSStick[PAD_MAX_CONTROLLERS];

bool JUTGamePad::mListInitialized = false;
u8 JUTGamePad::mPadAssign[PAD_MAX_CONTROLLERS];
u32 JUTGamePad::mSuppressPadReset = 0;
u32 JUTGamePad::sAnalogMode = 0;
u8 JUTGamePad::CRumble::mStatus[PAD_MAX_CONTROLLERS];
u32 JUTGamePad::CRumble::mEnabled = 0;
JUTResetBtnCb JUTGamePad::C3ButtonReset::sCallback = nullptr;
void* JUTGamePad::C3ButtonReset::sCallbackArg = nullptr;
OSTime JUTGamePad::C3ButtonReset::sThreshold = (OSTime)(OS_TIMER_CLOCK / 60) * 30;
bool JUTGamePad::C3ButtonReset::sResetSwitchPushing = false;
bool JUTGamePad::C3ButtonReset::sResetOccurred = false;
s32 JUTGamePad::C3ButtonReset::sResetOccurredPort = 0;

JUTGamePad::JUTGamePad(EPadPort port)
    : mButtons(), mMainStick(), mSubStick(), mRumble(this), mLink(this), mButtonReset() {
    this->mPortNum = port;
    mPadAssign[port]++;
    this->initList();
    JUTGamePad::mPadList.append(&this->mLink);
    this->update();
    this->mPadRecord = nullptr;
    this->mPadReplay = nullptr;
}

JUTGamePad::JUTGamePad() : mButtons(), mMainStick(), mSubStick(), mRumble(this), mLink(this), mButtonReset() {
    this->mPortNum = -1;
    this->initList();
    JUTGamePad::mPadList.append(&this->mLink);
    this->mPadRecord = nullptr;
    this->mPadReplay = nullptr;
    this->clear();
}

JUTGamePad::~JUTGamePad() {
    if (this->mPortNum != -1) {
        mPadAssign[this->mPortNum]--;
        this->mPortNum = -1;
    }

    JUTGamePad::mPadList.remove(&this->mLink);
}

void JUTGamePad::initList() {
    if (!JUTGamePad::mListInitialized) {
        JUTGamePad::mPadList.initiate();
        JUTGamePad::mListInitialized = true;
    }
}

void JUTGamePad::init() {
    PADSetSpec(5);
    JUTGamePad::sAnalogMode = 3;
    PADSetAnalogMode(3);
    PADInit();
}

void JUTGamePad::clear() {
    this->mButtonReset.mReset = false;
}

void JUTGamePad::read() {
    PADRead(JUTGamePad::mPadStatus);
    PADClamp(JUTGamePad::mPadStatus);

    u32 mask;
    u32 resetControllerMask = 0;

    for (s32 i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        mask = 0x80000000 >> i;

        if (JUTGamePad::mPadStatus[i].err == 0) {
            PADStatus* status = &JUTGamePad::mPadStatus[i];
            u32 buttons;

            buttons = (JUTGamePad::mPadMStick[i].update(status->stickX, status->stickY, JUTGamePad::sStickMode,
                                                        WhichStick_MainStick)
                       << 24);
            buttons |= (JUTGamePad::mPadSStick[i].update(status->substickX, status->substickY, JUTGamePad::sStickMode,
                                                         WhichStick_SubStick)
                        << 16);
            JUTGamePad::mPadButton[i].update(status, buttons);
        } else if (JUTGamePad::mPadStatus[i].err == -1) {
            JUTGamePad::mPadMStick[i].update(0, 0, JUTGamePad::sStickMode, WhichStick_MainStick);
            JUTGamePad::mPadSStick[i].update(0, 0, JUTGamePad::sStickMode, WhichStick_SubStick);
            JUTGamePad::mPadButton[i].update(nullptr, 0);

            if ((JUTGamePad::mSuppressPadReset & mask) == 0) {
                resetControllerMask |= mask;
            }
        } else {
            JUTGamePad::mPadButton[i].mTrigger = 0;
            JUTGamePad::mPadButton[i].mRelease = 0;
            JUTGamePad::mPadButton[i].mRepeat = 0;
        }
    }

    JSUListIterator<JUTGamePad> it;
    for (it = JUTGamePad::mPadList.getFirst(); it != JUTGamePad::mPadList.getEnd(); it++) {
        if (it->getPadReplay() != nullptr) {
            PADStatus status;
            u32 buttons;

            it->getPadReplay()->read(&status);
            buttons = it->mMainStick.update(status.stickX, status.stickY, JUTGamePad::sStickMode, WhichStick_MainStick)
                      << 24;
            buttons |=
                it->mSubStick.update(status.substickX, status.substickY, JUTGamePad::sStickMode, WhichStick_SubStick)
                << 16;
            it->mButtons.update(&status, buttons);
        } else {
            if (it->mPortNum == -1) {
                it->assign();
            }

            it->update();
        }

        if (it->getPadRecord() != nullptr && it->mPortNum != -1) {
            int port = it->mPortNum;

            if (JUTGamePad::mPadStatus[port].err == 0) {
                it->getPadRecord()->write(&JUTGamePad::mPadStatus[port]);
            }
        }
    }

    if (resetControllerMask != 0) {
        PADReset(resetControllerMask);
    }

    JUTGamePad::checkResetSwitch();
}

void JUTGamePad::assign() {
    for (s32 i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if (JUTGamePad::mPadStatus[i].err == 0 && JUTGamePad::mPadAssign[i] == 0) {
            this->mPortNum = i;
            JUTGamePad::mPadAssign[i] = 1;
            JUTGamePad::mPadButton[i].setRepeat(this->mButtons.mRepeatMask, this->mButtons.mRepeatDelay,
                                                this->mButtons.mRepeatFrequency);
            this->mRumble.clear(this);
            break;
        }
    }
}

void JUTGamePad::checkResetCallback(OSTime time) {
    if (this->mPortNum != -1 && time >= JUTGamePad::C3ButtonReset::sThreshold) {
        JUTGamePad::C3ButtonReset::sResetOccurred = true;
        JUTGamePad::C3ButtonReset::sResetOccurredPort = this->mPortNum;

        if (JUTGamePad::C3ButtonReset::sCallback != NULL) {
            (*JUTGamePad::C3ButtonReset::sCallback)(this->mPortNum, JUTGamePad::C3ButtonReset::sCallbackArg);
        }
    }
}

void JUTGamePad::update() {
    if (this->mPortNum != -1) {
        this->mButtons = JUTGamePad::mPadButton[this->mPortNum];
        this->mMainStick = JUTGamePad::mPadMStick[this->mPortNum];
        this->mSubStick = JUTGamePad::mPadSStick[this->mPortNum];
        this->mErrorStatus = JUTGamePad::mPadStatus[this->mPortNum].err;

        if (JUTGamePad::C3ButtonReset::sResetOccurred == false) {
            if (JUTGamePad::C3ButtonReset::sResetPattern ==
                (JUTGamePad::C3ButtonReset::sResetPattern & this->mButtons.mButton)) {
                if (this->mButtonReset.mReset == true) {
                    this->checkResetCallback(OSGetTime() - this->mResetTime);
                } else {
                    this->mButtonReset.mReset = true;
                    this->mResetTime = OSGetTime();
                }
            } else {
                this->mButtonReset.mReset = false;
            }
        }

        this->mRumble.update(this->mPortNum);
    }
}

void JUTGamePad::checkResetSwitch() {
    if (!JUTGamePad::C3ButtonReset::sResetOccurred) {
        if (OSGetResetSwitchState() != 0) {
            JUTGamePad::C3ButtonReset::sResetSwitchPushing = true;
        } else {
            if (JUTGamePad::C3ButtonReset::sResetSwitchPushing == true) {
                JUTGamePad::C3ButtonReset::sResetOccurred = true;
                JUTGamePad::C3ButtonReset::sResetOccurredPort = -1;

                if (*JUTGamePad::C3ButtonReset::sCallback != nullptr) {
                    (*JUTGamePad::C3ButtonReset::sCallback)(-1, JUTGamePad::C3ButtonReset::sCallbackArg);
                }
            }

            JUTGamePad::C3ButtonReset::sResetSwitchPushing = false;
        }
    }
}

void JUTGamePad::CButton::clear() {
    this->mButton = 0;
    this->mTrigger = 0;
    this->mRelease = 0;
    this->mRepeat = 0;
    this->mAnalogA = 0;
    this->mAnalogB = 0;
    this->mAnalogL = 0;
    this->mAnalogR = 0;
    this->mRepeatTimer = 0;
    this->mRepeatLastButton = 0;
    this->mRepeatMask = 0;
    this->mRepeatDelay = 0;
    this->mRepeatFrequency = 0;
}

void JUTGamePad::CButton::update(const PADStatus* padStatus, u32 stick_buttons) {
    u32 tempButtons;
    u32 buttons;

    if (padStatus != nullptr) {
        tempButtons = padStatus->button;
    } else {
        tempButtons = 0;
    }

    buttons = stick_buttons | tempButtons;
    this->mRepeat = 0;

    if (this->mRepeatDelay != 0) {
        if (this->mRepeatMask != 0) {
            u32 repeatButtons = buttons & this->mRepeatMask;
            this->mRepeat = 0;

            if (repeatButtons == 0) {
                this->mRepeatLastButton = 0;
                this->mRepeatTimer = 0;
            } else if (this->mRepeatLastButton == repeatButtons) {
                this->mRepeatTimer++;
                if (this->mRepeatTimer == this->mRepeatDelay ||
                    (this->mRepeatTimer > this->mRepeatDelay &&
                     ((this->mRepeatTimer - this->mRepeatDelay) % this->mRepeatFrequency) == 0)) {
                    this->mRepeat = repeatButtons;
                }
            } else {
                this->mRepeat = repeatButtons & (this->mRepeatLastButton ^ 0xFFFFFFFF);
                this->mRepeatLastButton = repeatButtons;
                this->mRepeatTimer = 0;
            }
        }
    }

    this->mTrigger = buttons & (buttons ^ this->mButton);
    this->mRelease = this->mButton & (buttons ^ this->mButton);
    this->mButton = buttons;
    this->mRepeat |= (this->mRepeatMask ^ 0xFFFFFFFF) & this->mTrigger;

    if (padStatus != nullptr) {
        this->mAnalogA = padStatus->analogA;
        this->mAnalogB = padStatus->analogB;
        this->mAnalogL = padStatus->triggerLeft;
        this->mAnalogR = padStatus->triggerRight;
    } else {
        this->mAnalogA = 0;
        this->mAnalogB = 0;
        this->mAnalogL = 0;
        this->mAnalogR = 0;
    }

    this->mAnalogLf = (f32)(int)this->mAnalogL / 150.0f;
    this->mAnalogRf = (f32)(int)this->mAnalogR / 150.0f;
}

void JUTGamePad::CStick::clear() {
    this->mX = 0.0f;
    this->mY = 0.0f;
    this->mValue = 0.0f;
    this->mAngle = 0;
}

u32 JUTGamePad::CStick::update(s8 x, s8 y, EStickMode stickMode, EWhichStick whichStick) {
    int stickMax = whichStick == WhichStick_MainStick ? 54 : 42;

    this->mX = (f32)x / (f32)stickMax;
    this->mY = (f32)y / (f32)stickMax;
    this->mValue = sqrtf(this->mX * this->mX + this->mY * this->mY);

    if (this->mValue > 1.0f) {
        if (stickMode == Clamped) {
            this->mX /= this->mValue;
            this->mY /= this->mValue;
        }

        this->mValue = 1.0f;
    }

    if (this->mValue > 0.0f) {
        if (this->mY == 0.0f) {
            if (this->mX > 0.0f) {
                this->mAngle = 0x4000;
            } else {
                this->mAngle = -0x4000;
            }
        } else {
            f32 angle = atan2(this->mX, -this->mY);
            this->mAngle = angle * 10430.379f; //((f32)0x8000 / F_PI);
        }
    }

    return this->getButton();
}

u32 JUTGamePad::CStick::getButton() {
    u32 button = 0;

    if (-0.25f < this->mX && this->mX < 0.25f) {
        button &= ~(DPAD_LEFT | DPAD_RIGHT);
    } else if (this->mX <= -0.5f) {
        button |= DPAD_LEFT;
    } else if (this->mX >= 0.5f) {
        button |= DPAD_RIGHT;
    }

    if (-0.25f < this->mY && this->mY < 0.25f) {
        button &= ~(DPAD_DOWN | DPAD_UP);
    } else if (this->mY <= -0.5f) {
        button |= DPAD_DOWN;
    } else if (this->mY >= 0.5f) {
        button |= DPAD_UP;
    }

    return button;
}

void JUTGamePad::CRumble::clear() {
    this->mFrame = 0;
    this->mLength = 0;
    this->mData = nullptr;
    this->mFrameCount = 0;
    JUTGamePad::CRumble::mEnabled = 0xF0000000;
}

void JUTGamePad::CRumble::clear(JUTGamePad* gamePad) {
    if (0 <= gamePad->getPortNum() && gamePad->getPortNum() < PAD_MAX_CONTROLLERS) {
        JUTGamePad::CRumble::mStatus[gamePad->getPortNum()] = 0;
        this->stopMotorHard(gamePad->getPortNum());
    }

    this->clear();
}

void JUTGamePad::CRumble::startMotor(int port) {
    if (JUTGamePad::CRumble::isEnabled(channel_mask[port])) {
        PADControlMotor(port, PAD_MOTOR_RUMBLE);
        JUTGamePad::CRumble::mStatus[port] = 1;
    }
}

void JUTGamePad::CRumble::stopMotor(int port) {
    if (JUTGamePad::CRumble::isEnabled(channel_mask[port])) {
        PADControlMotor(port, PAD_MOTOR_STOP);
        JUTGamePad::CRumble::mStatus[port] = 0;
    }
}

void JUTGamePad::CRumble::stopMotorHard(int port) {
    if (JUTGamePad::CRumble::isEnabled(channel_mask[port])) {
        PADControlMotor(port, PAD_MOTOR_STOP_HARD);
        JUTGamePad::CRumble::mStatus[port] = 0;
    }
}

static inline u8 getNumBit(const u8* data, int bit) {
    return (((0x80 >> (bit & 7)) & data[(u32)bit >> 3]) & 0xFF);
}

void JUTGamePad::CRumble::update(s16 port) {
    if (!JUTGamePad::CRumble::isEnabled(channel_mask[port])) {
        this->mFrame = 0;
        this->mLength = 0;
        this->mData = nullptr;
        this->mFrameCount = 0;
    }

    if (this->mLength != 0) {
        if (this->mFrame >= this->mLength) {
            JUTGamePad::CRumble::stopMotorHard(port);
            this->mLength = 0;
        } else {
            if (this->mFrameCount == 0) {
                if (JUTGamePad::CRumble::mStatus[port] == 0) {
                    JUTGamePad::CRumble::startMotor(port);
                }

                return;
            }

            u8 bit = getNumBit(this->mData, this->mFrame % this->mFrameCount);
            if (bit != 0 && JUTGamePad::CRumble::mStatus[port] == 0) {
                JUTGamePad::CRumble::startMotor(port);
            } else if (bit == 0 && JUTGamePad::CRumble::mStatus[port] != 0) {
                JUTGamePad::CRumble::stopMotorHard(port);
            }
        }

        this->mFrame++;
    }
}

void JUTGamePad::CButton::setRepeat(u32 repeatMask, u32 repeatDelay, u32 repeatFreq) {
    this->mRepeatLastButton = 0;
    this->mRepeatTimer = 0;
    this->mRepeatMask = repeatMask;
    this->mRepeatDelay = repeatDelay;
    this->mRepeatFrequency = repeatFreq;
}

bool JUTGamePad::recalibrate(u32 channels) {
    u32 channelMasks[PAD_MAX_CONTROLLERS] = { 0x80000000 >> 0, 0x80000000 >> 1, 0x80000000 >> 2, 0x80000000 >> 3 };

    for (int i = 0; i < PAD_MAX_CONTROLLERS; i++) {
        if ((JUTGamePad::mSuppressPadReset & channelMasks[i]) != 0) {
            channels &= channelMasks[i] ^ 0xFFFFFFFF;
        }
    }

    return PADRecalibrate(channels);
}
