#ifndef _JSYSTEM_J2D_J2DPRINT_H
#define _JSYSTEM_J2D_J2DPRINT_H

#include "types.h"
#include "JSystem/J2DGraph/J2DTypes.h"
#include "JSystem/JUtility/TColor.h"
#include "JSystem/JUtility/JUTFont.h"

struct J2DPrint {
    struct TSize {
        f32 mWidth;  // _00
        f32 mHeight; // _04
    };

    J2DPrint(JUTFont* font, f32 width);
    J2DPrint(JUTFont* font, JUtility::TColor charColor, JUtility::TColor gradColor);
    J2DPrint(JUTFont*, f32 width, f32 height, JUtility::TColor charColor, JUtility::TColor gradColor, JUtility::TColor blackColor,
             JUtility::TColor whiteColor);
    J2DPrint(JUTFont*, f32, f32);                                     // unused/inlined
    J2DPrint(JUTFont*, f32, f32, JUtility::TColor, JUtility::TColor); // unused/inlined

    virtual ~J2DPrint(); // _08

    void initiate();
    void private_initiate(JUTFont* font, f32 width, f32 height, JUtility::TColor charColor, JUtility::TColor gradColor,
                          JUtility::TColor blackColor, JUtility::TColor whiteColor, bool doUseFontHeight);
    JUTFont* setFont(JUTFont* font);
    void setFontSize();
    void locate(f32 x, f32 y);
    f32 print(f32 x, f32 y, const char* format, ...);
    f32 print(f32 x, f32 y, u8 alpha, const char* format, ...);
    f32 getWidth(const char* format, ...);
    void printReturn(const char* str, f32 x, f32 y, J2DTextBoxHBinding hbind, J2DTextBoxVBinding vbind, f32 x2, f32 y2, u8 alpha);
    f32 parse(const u8* str, int length, int x, u16* buffer, J2DPrint::TSize& size, u8 alpha, bool p7);
    void doCtrlCode(int code);
    u16 doEscapeCode(const u8** strPtr, u8 alpha);
    void initchar();
    s32 getNumberS32(const u8** strPtr, s32 min, s32 max, int base);
    f32 getNumberF32(const u8** strPtr, f32 min, f32 max, int base);

    static const u8* setBuffer(u32 size);

    // unused/inlined:
    void setBuffer(char*, u32);
    void putChar(int);
    void putChar(f32, f32, int);
    void print(const char*, ...);
    void print(u8, const char*, ...);
    void getSize(TSize&, const char*, ...);
    void getHeight(const char*, ...);

    /** @fabricated */
    inline void setFontSize(f32 width, f32 height)
    {
        mGlyphWidth  = (width > 0.0f) ? width : 0.0f;
        mGlyphHeight = (height > 0.0f) ? height : 0.0f;
    }

    inline void setWhiteColor(JUtility::TColor color) { mColorWhite = color; }

    inline void setCharColor(JUtility::TColor color) { mCharColor = color; }

    inline void setGradColor(JUtility::TColor color) { mGradientColor = color; }

    static const u8* mStrBuff;
    static size_t mStrBuffSize;
    static bool mHeapFlag;
    static bool mBufferNotEnough;

    // _00 VTBL
    JUTFont* mFont;                    // _04
    JUtility::TColor mActiveCharColor; // _08, all these "Active" values are just copies of stuff later in the struct
    JUtility::TColor mActiveGradColor; // _0C, they are copied to from the main ones in initchar
    f32 mActiveScaleX;                 // _10
    f32 mActiveScaleY;                 // _14
    f32 mActiveGlyphWidth;             // _18
    f32 mActiveGlyphHeight;            // _1C
    s16 mActiveFontWidth;              // _20
    bool mActiveIsGradient;            // _22, true: use grad color for top, char color for bottom; false: use char color for both
    f32 mPositionX;                    // _24
    f32 mPositionY;                    // _28
    f32 mCursorX;                      // _2C, same as position?
    f32 mCursorY;                      // _30
    f32 mRotation;                     // _34
    JUtility::TColor mColorBlack;      // _38
    JUtility::TColor mColorWhite;      // _3C
    JUtility::TColor mCharColor;       // _40
    JUtility::TColor mGradientColor;   // _44
    f32 mFontScaleX;                   // _48
    f32 mFontScaleY;                   // _4C
    f32 mGlyphWidth;                   // _50
    f32 mGlyphHeight;                  // _54
    s16 mFontWidth;                    // _58
    bool mIsGradient;                  // _5A
};

#endif
