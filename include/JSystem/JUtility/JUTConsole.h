#ifndef _JSYSTEM_JUT_JUTCONSOLE_H
#define _JSYSTEM_JUT_JUTCONSOLE_H

// #include "va_args.h"
#include "JSystem/JGadget/linklist.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTFont.h"

#ifdef __cplusplus
inline s32 colorCheck(s32 diff, s32 t) {
    s32 ret = diff - t;
    return ret + 1;
}

class JUTConsole : JKRDisposer {
  public:
    enum EConsoleType {
        CONSOLE_TYPE_0 = 0,
        CONSOLE_TYPE_1 = 1,
        CONSOLE_TYPE_2 = 2,
    };

    enum OutputFlag {
        /* 0x0 */ OUTPUT_NONE,
        /* 0x1 */ OUTPUT_OSREPORT,
        /* 0x2 */ OUTPUT_CONSOLE,
        /* 0x3 */ OUTPUT_OSR_AND_CONSOLE,
    };

    virtual ~JUTConsole(); // _08

    // _00 VTBL

    static JUTConsole* create(uint, uint, JKRHeap*);
    static JUTConsole* create(uint, void*, u32);
    static void destroy(JUTConsole*); // UNUSED
    JUTConsole(uint, uint, bool);
    static size_t getObjectSizeFromBufferSize(uint, uint);
    static size_t getLineFromObjectSize(u32, uint);
    void clear();
    void doDraw(JUTConsole::EConsoleType) const;
    void print_f(char const*, ...);
    void print(char const*);
    void dumpToTerminal(uint);
    void scroll(int);
    int getUsedLine() const;
    int getLineOffset() const;

    void setOutput(uint output) {
        mOutput = output;
    }
    void setPosition(int x, int y) {
        mPositionX = x;
        mPositionY = y;
    }
    void setFontSize(f32 x, f32 y) {
        mFontSizeX = x;
        mFontSizeY = y;
    }
    void setHeight(u32 height) {
        mHeight = height;
        if (mHeight > mMaxLines) {
            mHeight = mMaxLines;
        }
    }

    void setFont(JUTFont* p_font) {
        mFont = p_font;
        setFontSize(p_font->getWidth(), p_font->getHeight());
    }

    int nextIndex(int index) const {
        return ++index >= (int)mMaxLines ? 0 : index;
    }

    u32 getOutput() const {
        return mOutput;
    }
    int getPositionY() const {
        return mPositionY;
    }
    int getPositionX() const {
        return mPositionX;
    }
    u32 getHeight() const {
        return mHeight;
    }

    bool isVisible() const {
        return mIsVisible;
    }
    void setVisible(bool visible) {
        mIsVisible = visible;
    }

    void setLineAttr(int param_0, u8 param_1) {
        mBuf[(_20 + 2) * param_0] = param_1;
    }
    u8* getLinePtr(int param_0) const {
        return &mBuf[(_20 + 2) * param_0] + 1;
    }
    int diffIndex(int param_0, int param_1) const {
        int diff = param_1 - param_0;
        if (diff >= 0) {
            return diff;
        }
        return diff += mMaxLines;
    }

    u8 getLineAttr(int i) const {
        return mBuf[(_20 + 2) * i];
    }

    int prevIndex(int n) const {
        return (--n < 0) ? mMaxLines - 1 : n;
    }

    void scrollToLastLine() {
        scroll(mMaxLines);
    }
    void scrollToFirstLine() {
        scroll(-mMaxLines);
    }

    // _00     = VTBL
    // _00-_18 = JKRDisposer
    JGadget::TLinkListNode mNode; // _18
    u32 _20;                      // _20
    u32 mMaxLines;                // _24, might be int
    u8* mBuf;                     // _28
    bool _2C;                     // _2C
    int _30;                      // _30
    int _34;                      // _34
    int _38;                      // _38
    int _3C;                      // _3C
    int mPositionX;               // _40
    int mPositionY;               // _44
    u32 mHeight;                  // _48
    JUTFont* mFont;               // _4C
    f32 mFontSizeX;               // _50
    f32 mFontSizeY;               // _54
    u32 mOutput;                  // _58
    JUtility::TColor _5C;         // _5C
    JUtility::TColor _60;         // _60
    bool mIsVisible;              // _64
    bool _65;                     // _65
    bool _66;                     // _66
}; // Size: 0x6C

class JUTConsoleManager {
  public:
    JUTConsoleManager();
    static JUTConsoleManager* createManager(JKRHeap*);
    void appendConsole(JUTConsole* console);
    void removeConsole(JUTConsole* console);
    void draw() const;
    void drawDirect(bool) const;
    void setDirectConsole(JUTConsole*);

    static JUTConsoleManager* getManager() {
        return sManager;
    }

    static JUTConsoleManager* sManager;

  private:
    JGadget::TLinkList<JUTConsole, -24> soLink_; // _00
    JUTConsole* mActiveConsole;                  // _0C
    JUTConsole* mDirectConsole;                  // _10
}; // Size: 0x14

extern "C" {
void JUTConsole_print_f_va_(JUTConsole*, const char*, va_list);
JUTConsole* JUTGetReportConsole();
void JUTSetReportConsole(JUTConsole*);
JUTConsole* JUTGetWarningConsole();
void JUTSetWarningConsole(JUTConsole*);
void JUTReportConsole(const char*);
void JUTReportConsole_f(const char*, ...);
void JUTReportConsole_f_va(const char*, va_list);
void JUTWarningConsole(const char*);
void JUTWarningConsole_f(const char*, ...);
void JUTWarningConsole_f_va(const char*, va_list);
};

#endif

#endif
