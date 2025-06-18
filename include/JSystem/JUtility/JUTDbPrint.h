#ifndef _JSYSTEM_JUT_JUTDBPRINT_H
#define _JSYSTEM_JUT_JUTDBPRINT_H

#ifdef __cplusplus

#include "JSystem/JUtility/TColor.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JKernel/JKRHeap.h"

struct JUTDbPrintList {
    JUTDbPrintList* mNext; // _00
    s16 mX;                // _04
    s16 mY;                // _06
    s16 mDuration;         // _08
    s16 mLen;              // _0A
    u8 mStr;               // _0C
};

struct JUTDbPrint {
    JUTDbPrint(JUTFont*, JKRHeap*); // unused/inlined

    ~JUTDbPrint(); // unused/inlined

    JUTFont* changeFont(JUTFont*);
    void flush();
    void flush(int, int, int, int);
    void drawString(int, int, int, const u8*);

    // Unused/inlined:
    void enter(int, int, int, const char*, int);
    void print(int, int, const char*, ...);
    void print(int, int, int, const char*, ...);
    void reset();

    void setVisible(bool visible) {
        mVisible = visible;
    }
    JUTFont* getFont() const {
        return mFont;
    }
    JUTDbPrintList* getList() const {
        return mList;
    }

    static JUTDbPrint* start(JUTFont*, JKRHeap*);
    static JUTDbPrint* getManager() {
        return sDebugPrint;
    }

    static JUTDbPrint* sDebugPrint;

    JUTDbPrintList* mList;   // _00
    JUTFont* mFont;          // _04
    JUtility::TColor mColor; // _08
    bool mVisible;           // _0C
    JKRHeap* mHeap;          // _10
};

void JUTReport(int x, int y, int show_count, const char* fmt, ...);

extern "C" {
#endif

void* JC_JUTDbPrint_getManager(void);
void JC_JUTDbPrint_setVisible(void*, int); // I know these are C++ but these were used to match a c function so I'll fix
                                           // these when I need them or fix zurumode update.

#ifdef __cplusplus
}
#endif

#endif
