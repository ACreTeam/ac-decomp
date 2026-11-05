#include "MSL_C/printf.h"
#include "types.h"
#include <string.h>

#include <dolphin/os.h>
#include <dolphin/vi.h>
#include "JSystem/J2D.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTVideo.h"

#define OUTPUT_NONE 0
#define OUTPUT_CONSOLE 1
#define OUTPUT_OSREPORT 2
#define OUTPUT_ALL (OUTPUT_OSREPORT | OUTPUT_CONSOLE)

JUTConsoleManager *JUTConsoleManager::sManager;

JUTConsole *JUTConsole::create(uint param_0, uint maxLines, JKRHeap *pHeap)
{
    JUTConsoleManager *const pManager = JUTConsoleManager::getManager();
#line 33
    JUT_ASSERT(pManager != 0);

    u8 *buffer = (u8*)JKRAllocFromHeap(pHeap, getObjectSizeFromBufferSize(param_0, maxLines), 0);

    JUTConsole *newConsole = new (buffer) JUTConsole(param_0, maxLines, true);
    newConsole->mBuf = buffer + sizeof(JUTConsole);
    newConsole->clear();

    pManager->appendConsole(newConsole);
    return newConsole;
}

JUTConsole *JUTConsole::create(uint param_0, void *buffer, u32 bufferSize)
{
    JUTConsoleManager *const pManager = JUTConsoleManager::getManager();
#line 59
    JUT_ASSERT(pManager != 0);
#line 62
    JUT_ASSERT(( (u32)buffer & 0x3 ) == 0);
    u32 maxLines = getLineFromObjectSize(bufferSize, param_0);

    JUTConsole *newConsole = new (buffer) JUTConsole(param_0, maxLines, false);
    newConsole->mBuf = (u8 *)buffer + sizeof(JUTConsole);
    newConsole->clear();

    pManager->appendConsole(newConsole);
    return newConsole;
}

// unused
void JUTConsole::destroy(JUTConsole *console) {
    JUT_ASSERT(console != 0);
    delete console;
}

JUTConsole::JUTConsole(uint p1, uint maxLines, bool p3)
{
    _2C = p3;
    _20 = p1;
    mMaxLines = maxLines;

    mPositionX = 30;
    mPositionY = 50;
    mHeight = 20;

    if (mHeight > mMaxLines)
    {
        mHeight = mMaxLines;
    }

    mFont = nullptr;
    mIsVisible = true;
    _69 = false;
    _6A = false;
    _6B = false;
    mOutput = 1;

    _5C = JUtility::TColor(0, 0, 0, 100);
    _60 = JUtility::TColor(0, 0, 0, 230);
    _64 = 8;
}

JUTConsole::~JUTConsole() {
#line 154
    JUT_ASSERT(JUTConsoleManager::getManager())
    JUTConsoleManager::getManager()->removeConsole(this);
}

#if DEBUG
CW_FORCE_STRINGS(JUtility_JUTConsole1, "S----------E");
#endif

size_t JUTConsole::getObjectSizeFromBufferSize(unsigned int param_0, unsigned int maxLines)
{
    int objSize = (param_0 + 2) * maxLines + sizeof(JUTConsole);
    return objSize;
}

size_t JUTConsole::getLineFromObjectSize(u32 bufferSize, unsigned int param_1)
{
    bufferSize -= sizeof(JUTConsole);
    int line = (bufferSize) / (param_1 + 2);
    return line;
}

void JUTConsole::clear()
{
    _30 = 0;
    _34 = 0;
    _38 = 0;
    _3C = 0;

    for (int i = 0; i < mMaxLines; i++)
    {
        setLineAttr(i, 0);
    }
    setLineAttr(0, -1);
    *getLinePtr(0) = 0;
}

void JUTConsole::doDraw(JUTConsole::EConsoleType consoleType) const
{
    f32 font_yOffset;
    s32 changeLine_1;
    s32 changeLine_2;

    if (mIsVisible && (mFont || consoleType == CONSOLE_TYPE_2))
    {
        if (mHeight != 0)
        {
            bool isConsoleType0 = consoleType == CONSOLE_TYPE_0 ? true : false;
            font_yOffset = 2.0f + mFontSizeY;

            if (consoleType != CONSOLE_TYPE_2)
            {
                if (!JUTVideo::getManager())
                {
                    J2DOrthoGraph ortho(0.0f, 0.0f, 640.0f, 480.0f, -1.0f, 1.0f);
                    ortho.setPort();
                }
                else
                {
                    J2DOrthoGraph ortho(0.0f, 0.0f, JUTVideo::getManager()->getFbWidth(),
                                        JUTVideo::getManager()->getEfbHeight(), -1.0f, 1.0f);
                    ortho.setPort();
                }

                const JUtility::TColor *color;
                if (isConsoleType0)
                {
                    color = &_60;
                }
                else
                {
                    color = &_5C;
                }

                J2DFillBox(mPositionX - 2, (int)(mPositionY - font_yOffset),
                           (int)((mFontSizeX * _20) + 4.0f), (int)(font_yOffset * mHeight),
                           *color);
                mFont->setGX();

                if (isConsoleType0)
                {
                    s32 s = (diffIndex(_30, _38) - mHeight) + 1;
                    if (s <= 0)
                    {
                        mFont->setCharColor(JUtility::TColor(255, 255, 255, 255));
                    }
                    else if (_30 == _34)
                    {
                        mFont->setCharColor(JUtility::TColor(255, 230, 230, 255));
                    }
                    else
                    {
                        mFont->setCharColor(JUtility::TColor(230, 230, 255, 255));
                    }
                }
                else
                {
                    mFont->setCharColor(JUtility::TColor(230, 230, 230, 255));
                }
            }
            else
            {
                JUTDirectPrint::getManager()->erase(mPositionX - 3, mPositionY - 2,
                                                    (_20 * 6) + 6,
                                                    (int)(font_yOffset * mHeight) + 4);
                JUTDirectPrint::getManager()->setCharColor(JUtility::TColor(255, 255, 255, 255));
            }

            char *linePtr;
            s32 curLine = _30;
            s32 yFactor = 0;

            do
            {
                linePtr = (char *)getLinePtr(curLine);

                if ((u8)linePtr[-1] != 0)
                {
                    if (consoleType != CONSOLE_TYPE_2)
                    {
                        mFont->drawString_scale(mPositionX, ((yFactor * font_yOffset) + mPositionY),
                                                mFontSizeX, mFontSizeY, linePtr, true);
                    }
                    else
                    {
                        JUTDirectPrint::getManager()->drawString(
                            mPositionX, ((yFactor * font_yOffset) + mPositionY), linePtr);
                    }

                    changeLine_1 = curLine + 1;
                    changeLine_2 = ((((s32)changeLine_1 )>= (s32)mMaxLines)) ? 0 : changeLine_1;
                    yFactor += 1;
                    curLine = changeLine_2;
                }
                else
                {
                    break;
                }
            } while (yFactor < mHeight && changeLine_2 != _34);
        }
    }
}

void JUTConsole::print_f(char const *text, ...)
{
    va_list args;
    va_start(args, text);
    JUTConsole_print_f_va_(this, text, args);
    va_end(args);
}

void JUTConsole::print(char const *param_0)
{
    if (mOutput & OUTPUT_OSREPORT)
    {
        JUT_REPORT_MSG("%s", param_0);
    }
    if (mOutput & OUTPUT_CONSOLE)
    {
        const u8 *r29 = (const u8 *)param_0;
        u8 *r28 = getLinePtr(_38) + _3C;
        while (*r29 != 0)
        {
            if (_6A && _34 == nextIndex(_38))
            {
                break;
            }
            if (*r29 == '\n')
            {
                r29++;
                _3C = _20;
            }
            else if (*r29 == '\t')
            {
                r29++;
                while (_3C < _20)
                {
                    *(r28++) = ' ';
                    _3C++;
                    if (_3C % _64 == 0)
                    {
                        break;
                    }
                }
            }
            else if (mFont && mFont->isLeadByte(*r29))
            {
                if (_3C + 1 < _20)
                {
                    *(r28++) = *(r29++);
                    *(r28++) = *(r29++);
                    _3C++;
                    _3C++;
                }
                else
                {
                    *(r28++) = 0;
                    _3C++;
                }
            }
            else
            {
                *(r28++) = *(r29++);
                _3C++;
            }
            if (_3C < _20)
            {
                continue;
            }
            *r28 = 0;
            _38 = nextIndex(_38);
            _3C = 0;
            setLineAttr(_38, 0xff);
            r28 = getLinePtr(_38);
            *r28 = 0;
            int local_28 = diffIndex(_30, _38);
            if (local_28 == mHeight)
            {
                _30 = nextIndex(_30);
            }
            if (_38 == _34)
            {
                _34 = nextIndex(_34);
            }
            if (_38 == _30)
            {
                _30 = nextIndex(_30);
            }
            if (_6B)
            {
                break;
            }
        }
        *r28 = 0;
    }
}

void JUTConsole_print_f_va_(JUTConsole *console, const char *text, va_list args)
{
    char buf[1024];
#line 563
    JUT_ASSERT(console!=0);
    vsnprintf(buf, sizeof(buf), text, args);
    console->print(buf);
}

#if DEBUG
CW_FORCE_STRINGS(JUtility_JUTConsole2,
                 "\n:::dump of console[%x]--------------------------------\n",
                 "[%03d] %s\n",
                 ":::dump of console[%x] END----------------------------\n",
                 "console != this && console != 0",
                 "\n:::dump of console[%x]----------------\n",
                 ":::dump of console[%x] END------------\n");
#endif

void JUTConsole::dumpToTerminal(unsigned int n) {
    if (n == 0) {
        return;
    }

    int lineNo = _34;
    if (n != 0xffffffff) {
        lineNo = _38;
        while (n--) {
            int prevIdx = prevIndex(lineNo);
            if (!getLineAttr(prevIdx)) {
                break;
            }
            lineNo = prevIdx;
            if (prevIdx == _34) {
                break;
            }
        }
    }
    // OSReport("\n:::dump of console[%x]--------------------------------\n", this);
    int i = 0;
    do {
        u8* line = getLinePtr(lineNo);
        if ((u8)line[-1] == 0) {
            break;
        }
        if (_69) {
            OSReport("[%03d] %s\n", i, line);
        } else {
            OSReport("%s\n", line);
        }
        lineNo = nextIndex(lineNo);
        i++;
    } while (lineNo != _34);

    // OSReport(":::dump of console[%x] END----------------------------\n", this);
}

void JUTConsole::scroll(int scrollAmnt)
{
    if (scrollAmnt < 0)
    {
        int diff = diffIndex(_34, _30);
        if (scrollAmnt < -diff)
        {
            scrollAmnt = -diff;
        }
    }
    else
    {
        if (scrollAmnt > 0)
        {
            if (diffIndex(_34, _38) + 1 <= mHeight)
            {
                scrollAmnt = 0;
            }
            else
            {
                int diff = diffIndex(_30, _38) - mHeight + 1;
                if (scrollAmnt > diff)
                {
                    scrollAmnt = diff;
                }
            }
        }
    }

    _30 += scrollAmnt;
    if (_30 < 0)
    {
        _30 += mMaxLines;
    }

    if (_30 >= mMaxLines)
    {
        _30 -= mMaxLines;
    }
}

int JUTConsole::getUsedLine() const
{
    int usedLine = diffIndex(_34, _38);
    return usedLine;
}

int JUTConsole::getLineOffset() const
{
    int offset = diffIndex(_34, _30);
    return offset;
}

JUTConsoleManager::JUTConsoleManager()
{
    mActiveConsole = nullptr;
    mDirectConsole = nullptr;
}

JUTConsoleManager *JUTConsoleManager::createManager(JKRHeap *pHeap)
{
#line 924
    JUT_ASSERT(sManager == 0);
    if (pHeap == nullptr)
    {
        pHeap = JKRGetCurrentHeap();
    }
    sManager = new (pHeap, 0) JUTConsoleManager();
    return sManager;
}

#if DEBUG
CW_FORCE_STRINGS(JUtility_JUTConsole3, "consoleManager != 0 && sManager == consoleManager");
#endif

void JUTConsoleManager::appendConsole(JUTConsole *const console)
{
#line 961
    JUT_ASSERT(sManager != 0 && console != 0);

    // not sure why this assert was 3 lines later
    JUT_ASSERT(soLink_.Find( console ) == soLink_.end());
    soLink_.Push_back(console);
    if (mActiveConsole == nullptr)
    {
        mActiveConsole = console;
    }
}

void JUTConsoleManager::removeConsole(JUTConsole *const console)
{
#line 984
    JUT_ASSERT(sManager != 0 && console != 0);
    
    // not sure why this assert was 3 lines later
    JUT_ASSERT(soLink_.Find( console ) != soLink_.end());
    
    if (mActiveConsole == console)
    {
        if(soLink_.size() <= 1) {
            mActiveConsole = nullptr;
        }
        else {
            mActiveConsole = console != &soLink_.back() ? soLink_.Element_toValue(console->mListNode.getNext()) : &soLink_.front();
        }
    }
    if (JUTGetWarningConsole() == console)
        JUTSetWarningConsole(nullptr);
    if (JUTGetReportConsole() == console)
        JUTSetReportConsole(nullptr);
    
    soLink_.Remove(console);
}

void JUTConsoleManager::draw() const
{
    // this cast is needed to match release, luckily doesn't affect tp debug either, so maybe there's another temp or cast somewhere?
    JGadget::TLinkList<JUTConsole, -24>::const_iterator it = ((const JUTConsoleManager *)this)->soLink_.begin();
    JGadget::TLinkList<JUTConsole, -24>::const_iterator itEnd = soLink_.end();

    for (; it != itEnd; ++it)
    {
        const JUTConsole &console = *it;
        if (&console != mActiveConsole)
        {
            console.doDraw(JUTConsole::CONSOLE_TYPE_1);
        }
    }

    if (mActiveConsole)
        mActiveConsole->doDraw(JUTConsole::CONSOLE_TYPE_0);
}


void JUTConsoleManager::drawDirect(bool waitRetrace) const {
    if(mDirectConsole) {
        if(waitRetrace) {
            BOOL interrupt = OSEnableInterrupts();
            u32 retrace_count = VIGetRetraceCount();
            do
            {
            } while (retrace_count == VIGetRetraceCount());
            OSRestoreInterrupts(interrupt);
        }
        mDirectConsole->doDraw(JUTConsole::CONSOLE_TYPE_2);
    }
}

void JUTConsoleManager::setDirectConsole(JUTConsole *console) {
    if (mDirectConsole != nullptr) {
        appendConsole(mDirectConsole);
    }
    if(console != nullptr) {
        removeConsole(console);
    }
    mDirectConsole = console;
}

static JUTConsole *sReportConsole;
static JUTConsole *sWarningConsole;

// C Functions
void JUTSetReportConsole(JUTConsole *console) {
    sReportConsole = console;
}

JUTConsole *JUTGetReportConsole() {
    return sReportConsole;
}

void JUTSetWarningConsole(JUTConsole *console) {
    sWarningConsole = console;
}

JUTConsole *JUTGetWarningConsole() {
    return sWarningConsole;
}

void JUTReportConsole_f_va(const char *text, va_list args) {
    char buf[256];
    if(!JUTGetReportConsole()) {
        vsnprintf(buf, sizeof(buf), text, args);
        JUT_REPORT_MSG("%s", buf);
    }
    else if (JUTGetReportConsole()->getOutput() & OUTPUT_ALL) {
        vsnprintf(buf, sizeof(buf), text, args);
        JUTGetReportConsole()->print(buf);
    }
}

void JUTReportConsole_f(const char *text, ...)
{
    va_list vl;
    va_start(vl, text);
    JUTReportConsole_f_va(text, vl);
    va_end(vl);
}

void JUTReportConsole(const char *text) {
    JUTReportConsole_f("%s", text);
}

void JUTWarningConsole_f_va(const char *text, va_list args)
{
    char buf[256];
    if (!JUTGetWarningConsole())
    {
        vsnprintf(buf, sizeof(buf), text, args);
        OSReport("%s", buf);
    }
    else if (JUTGetWarningConsole()->getOutput() & OUTPUT_ALL)
    {
        vsnprintf(buf, sizeof(buf), text, args);
        JUTGetWarningConsole()->print(buf);
    }
}

void JUTWarningConsole_f(const char *text, ...)
{
    va_list vl;
    va_start(vl, text);
    JUTReportConsole_f_va(text, vl);
    va_end(vl);
}

void JUTWarningConsole(const char *text) {
    JUTReportConsole_f("%s", text);
}

