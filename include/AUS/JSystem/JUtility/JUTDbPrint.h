#ifndef JUTDBPPRINT_H
#define JUTDBPPRINT_H

#include "JSystem/JUtility/TColor.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JKernel/JKRHeap.h"

#include "types.h"

struct JUTDbPrintList
{
    JUTDbPrintList *mNext; // _00
    s16 mX;                // _04
    s16 mY;                // _06
    s16 mDuration;         // _08
    s16 mLen;              // _0A
    u8 mStr;               // _0C
};

struct JUTDbPrint
{
    JUTDbPrint(JUTFont *, JKRHeap *); // unused/inlined

    ~JUTDbPrint(); // unused/inlined

    JUTFont *changeFont(JUTFont *);
    void flush();
    void flush(int, int, int, int);
    void drawString(int, int, int, const u8 *);

    // Unused/inlined:
    void enter(int, int, int, const char *, int);
    void print(int, int, const char *, ...);
    void print(int, int, int, const char *, ...);
    void reset();

    bool isVisible() const { return mVisible; }
    void setVisible(bool visible) { mVisible = visible; }
    JUTFont *getFont() const { return mFont; }
    JUTDbPrintList *getList() const { return mList; }

    static JUTDbPrint *start(JUTFont *, JKRHeap *);
    static JUTDbPrint *getManager() { return sDebugPrint; }

    static JUTDbPrint *sDebugPrint;

    JUTDbPrintList *mList;   // _00
    JUTFont *mFont;          // _04
    JUtility::TColor mColor; // _08
    bool mVisible;         // _0C
    JKRHeap *mHeap;          // _10
};

void JUTReport(int, int, const char *, ...);
void JUTReport(int , int , int, const char *, ...);

#endif // !JUTDBPPRINT_H
