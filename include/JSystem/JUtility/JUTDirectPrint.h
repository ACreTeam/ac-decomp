#ifndef JUTDIRECTPRINT_H
#define JUTDIRECTPRINT_H

#include "types.h"
// #include "va_args.h"
#include "JSystem/JUtility/TColor.h"

#ifdef __cplusplus
class JUTDirectPrint
{
private:
    JUTDirectPrint();

public:
    static JUTDirectPrint *start();
    void erase(int x, int y, int w, int h);
    void setCharColor(JUtility::TColor color);
    void setCharColor(u8 r, u8 g, u8 b);
    void drawChar(int, int, int);
    void drawString(u16 x, u16 y, char *text);
    void drawString_f(u16 x, u16 y, const char * text, ...);
    void changeFrameBuffer(void *framebuffer, u16 w, u16 h );

    // Inline/Unused
    void printSub(u16, u16, const char *, va_list *, bool);
    void print(u16, u16, const char *, ...);

    bool isActive() const { return mFramebuffer != nullptr; }
    void *getFrameBuffer() { return mFramebuffer; }
    JUtility::TColor getCharColor() const { return mCharColor; }

    static JUTDirectPrint *getManager() { return sDirectPrint; }

private:
    static u8 sAsciiTable[128];
    static u32 sFontData[64];
    static u32 sFontData2[77];
    static JUTDirectPrint *sDirectPrint;

    void *mFramebuffer;          // _00
    u16 mFbWidth;                // _04
    u16 mFbHeight;               // _06
    u16 mStride;                 // _08
    size_t mFbSize;              // _0C
    u8 _10[0x4];                 // _10 - unknown
    u16 *mFrameMemory;           // _14
    JUtility::TColor mCharColor; // _18, Color in RGBA format
    u16 mCharColorY;             // _1C, 1C-2C = color in YCbCr
    u16 mCharColorCb;            // _1E
    u16 mCharColorCb2;           // _20
    u16 mCharColorCb4;           // _22
    u16 mCharColorCr;            // _24
    u16 mCharColorCr2;           // _26
    u16 mCharColorCr4;           // _28
    u16 _2A;                     // _2A
};

inline void JUTChangeFrameBuffer(void *buffer, u16 height, u16 width)
{
    JUTDirectPrint::getManager()->changeFrameBuffer(buffer, width, height);
}
#endif

#endif
