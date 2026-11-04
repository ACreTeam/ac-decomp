#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTDirectPrint.h"

namespace JUTAssertion {
namespace {
static u32 sMessageLife;
static u32 sMessageOwner;
static bool mSynchro;
static char sMessageFileLine[64];
static char sMessageString[96];

static u32 sDisplayTime = -1;
static u32 sDevice = 3;
static bool sVisible = true;
} // namespace

void create() {
}

u32 flush_subroutine() {
    if (sMessageLife == 0) {
        return 0;
    }
    if (sMessageLife != -1) {
        sMessageLife--;
    }
    if (sMessageLife < 5) {
        return 0;
    }
    return sMessageLife;
}

void flushMessage() {
    if (flush_subroutine() && sVisible == true) {
        JUTDirectPrint::getManager()->drawString(16, 16, sMessageFileLine);
        JUTDirectPrint::getManager()->drawString(16, 24, sMessageString);
    }
}

void flushMessage_dbPrint() {
    if (flush_subroutine() && sVisible == true && JUTDbPrint::getManager()) {
        JUTFont* font = JUTDbPrint::getManager()->getFont();
        if (font) {
            u8 tmp = ((VIGetRetraceCount() & 60) << 2) | 0xF;
            font->setGX();
            font->setCharColor(JUtility::TColor(255, tmp, tmp, 255));
            font->drawString(30, 36, sMessageFileLine, true);
            font->drawString(30, 54, sMessageString, true);
        }
    }
}

void changeDisplayTime(u32 time) {
    sDisplayTime = time;
}

void changeDevice(u32 device) {
    sDevice = device;
}
} // namespace JUTAssertion
