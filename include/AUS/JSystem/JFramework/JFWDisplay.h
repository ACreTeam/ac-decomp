#ifndef _JSYSTEM_JFW_JFWDISPLAY_H
#define _JSYSTEM_JFW_JFWDISPLAY_H

#include <dolphin/gx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/JUtility/JUTProcBar.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JUtility/JUTXfb.h"
#include "JSystem/JUtility/TColor.h"
#include "types.h"

typedef void (*JFWDisplayUnkFunc)(void);

extern Mtx34 e_mtx;

class JFWAlarm : public OSAlarm { // everything here seems to be auto inlined or unused
public:
    // Contructor and Destructor are both present in map but unused, not sure if it belongs here
    JFWAlarm() : mLink(this) {}
    ~JFWAlarm() {}
    void createAlarm() { OSCreateAlarm(this); }
    void cancelAlarm() { OSCancelAlarm(this); }
    void removeLink() { sList.remove(&mLink); }
    void appendLink() { sList.append(&mLink); }
    OSThread *getThread() const { return mThread; }
    void setThread(OSThread *thread) { mThread = thread; }

    static JSUList<JFWAlarm> sList;//

public:
    /* 0x28 */ OSThread *mThread;
    /* 0x2C */ JSULink<JFWAlarm> mLink;
};

class JFWDisplay
{
public:
    enum EDrawDone
    {
        /* 0x0 */ UNK_METHOD_0 = 0,
        /* 0x1 */ UNK_METHOD_1 = 1
    };

    static JFWDisplay *createManager(const _GXRenderModeObj *, JKRHeap *, JUTXfb::EXfbNumber, bool); // 0x80015bfc
    void waitBlanking(int);                      // 0x8001684c
    void threadSleep(s64);                       // 0x800169fc
    void clearEfb_init();                        // 0x80016ab8
    void clearEfb();                             // 0x80016b2c
    void clearEfb(_GXColor);                     // 0x80016b58
    void clearEfb(int, int, int, int, _GXColor); // 0x80016b9c
    void calcCombinationRatio();                 // 0x80016f0c

    // auto inlined / unused functions
    void ctor_subroutine(bool);
    JFWDisplay(JKRHeap *, JUTXfb::EXfbNumber, bool);
    // JFWDisplay(void *, bool);
    // JFWDisplay(void *, void *, bool);
    // JFWDisplay(void *, void *, void *, bool);
    // void createManager(const _GXRenderModeObj *, void *, bool);
    // void createManager(const _GXRenderModeObj *, void *, void *, bool);
    // void createManager(const _GXRenderModeObj *, void *, void *, void *, bool);
    static JFWDisplay* createManager(JKRHeap* heap, JUTXfb::EXfbNumber number, bool alpha) {
        return createManager(nullptr, heap, number, alpha);
    }
    static void destroyManager();
    void prepareCopyDisp();
    void drawendXfb_single();
    void exchangeXfb_double();
    void exchangeXfb_triple();
    void copyXfb_triple();
    void preGX();
    void endGX();
    void* changeToSingleXfb(int);
    void* changeToDoubleXfb();
    // void deleteToSingleXfb(int);
    // void deleteToSingleXfb(void *);
    // void addToDoubleXfb(void *, bool);
    // void addToDoubleXfb(JKRHeap *);
    // void clearAllXfb();
    s32 frameToTick(float);
    static void setForOSResetSystem();

    // Virtual functions
    virtual void beginRender(); // 0x80015e0c
    virtual void endRender();   // 0x8001633c
    virtual void endFrame();    // 0x8001669c
    virtual ~JFWDisplay();      // 0x80015b80

    static JFWDisplay *getManager() { return sManager; }

    const GXRenderModeObj* getRenderMode() const {
        return JUTVideo::getManager()->getRenderMode();
    }

    int getEfbHeight() const {
        return JUTVideo::getManager()->getEfbHeight();
    }

    int getEfbWidth() const {
        return JUTVideo::getManager()->getFbWidth();
    }

    JUTFader *getFader() const { return mFader; }
    void setFader(JUTFader * fader) { mFader = fader; }

    void set_38(int val) {
        _38 = val;
    }

    bool startFadeOut(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeOut(duration);
        }
        return true;
    }

    bool startFadeIn(int duration) {
        if (mFader != nullptr) {
            return mFader->startFadeIn(duration);
        }
        return true;
    }

    void setGamma(GXGamma gamma) { mGamma = gamma; }

    void setFrameRate(u16 rate) {
        mFrameRate = rate;
        mTickRate = 0;
    }

    void setTickRate(u32 rate) {
        mTickRate = rate;
        mFrameRate = 0;
    }
    JUtility::TColor getClearColor() const {
        return mClearColor;
    }

    void setClearColor(u8 r, u8 g, u8 b, u8 a) {
        mClearColor.set(r, g, b, a);
    }

    void setClearColor(JUtility::TColor color)
    {
        mClearColor = color;
    }

    void setFBAlpha(bool enable) {
        mEnableAlpha = enable;
    }

    bool getFBAlpha()
    {
        return mEnableAlpha;
    }

    bool isWaiting() { return mIsWaiting; }

    static JFWDisplay *sManager; // 0x80415718

private:
    /* 0x04 */ JUTFader *mFader;
    /* 0x08 */ JUtility::TColor mClearColor;
    /* 0x0C */ u32 mZClear;
    /* 0x10 */ JUTXfb *mXfb;
    /* 0x14 */ u16 mGamma;
    /* 0x18 */ EDrawDone mDrawDoneMethod;
    /* 0x1C */ u16 mFrameRate;
    /* 0x20 */ u32 mTickRate;
    /* 0x24 */ bool mEnableAlpha;
    /* 0x26 */ u16 mClamp;
    /* 0x28 */ f32 mCombinationRatio;
    /* 0x2C */ u32 _2C;
    /* 0x30 */ u32 _30;
    /* 0x34 */ u32 _34;
    /* 0x38 */ int _38;
    /* 0x3C */ int _3C;
    /* 0x40 */ bool mIsWaiting;
    /* 0x44 */ JFWDisplayUnkFunc _44;
    /* 0x48 */ s16 _48;
    /* 0x4A */ u8 _4a;
};

#endif
