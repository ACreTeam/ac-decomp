#include "dolphin/dvd.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "JSystem/JKernel/JKRAram.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "JSystem/JUtility/JUTGraphFifo.h"
#include "JSystem/JUtility/JUTVideo.h"
#include "JSystem/JFramework/JFWSystem.h"

int JFWSystem::CSetUpParam::maxStdHeaps = 2;
u32 JFWSystem::CSetUpParam::sysHeapSize = 0x400000;
u32 JFWSystem::CSetUpParam::fifoBufSize = 0x40000;
u32 JFWSystem::CSetUpParam::aramAudioBufSize = 0x800000;
u32 JFWSystem::CSetUpParam::aramGraphBufSize = 0x600000;
s32 JFWSystem::CSetUpParam::streamPriority = 8;
s32 JFWSystem::CSetUpParam::decompPriority = 7;
s32 JFWSystem::CSetUpParam::aPiecePriority = 6;
const ResFONT *JFWSystem::CSetUpParam::systemFontRes = &JUTResFONT_Ascfont_fix12;
const _GXRenderModeObj *JFWSystem::CSetUpParam::renderMode = &GXNtsc480IntDf;
u32 JFWSystem::CSetUpParam::exConsoleBufferSize = 0x24FC;

JKRHeap *JFWSystem::rootHeap;
JKRHeap *JFWSystem::systemHeap;
JKRThread *JFWSystem::mainThread;
JUTDbPrint *JFWSystem::debugPrint;
JUTFont *JFWSystem::systemFont;
JUTConsoleManager *JFWSystem::systemConsoleManager;
JUTConsole *JFWSystem::systemConsole;
bool JFWSystem::sInitCalled;

void JFWSystem::firstInit()
{
#line 80
    JUT_ASSERT(rootHeap == 0);
    OSInit();
    DVDInit();
    rootHeap = JKRExpHeap::createRoot(CSetUpParam::maxStdHeaps, false);
    systemHeap = JKRExpHeap::create(CSetUpParam::sysHeapSize, rootHeap, false);
}

void JFWSystem::init()
{
#line 101
    JUT_ASSERT(sInitCalled == false);

    if (rootHeap == 0)
        firstInit();

    sInitCalled = true;
    JKRAram::create(CSetUpParam::aramAudioBufSize, CSetUpParam::aramGraphBufSize, CSetUpParam::streamPriority, CSetUpParam::decompPriority,
                    CSetUpParam::aPiecePriority);

    mainThread = new JKRThread(OSGetCurrentThread(), 4);    
    JUTVideo::createManager(CSetUpParam::renderMode);
    JUTCreateFifo(CSetUpParam::fifoBufSize);
    JUTGamePad::init();
    JUTDirectPrint *directPrint = JUTDirectPrint::start();
    JUTAssertion::create();
    JUTException::create(directPrint);
    systemFont = new JUTResFont(CSetUpParam::systemFontRes, nullptr);
    debugPrint = JUTDbPrint::start(nullptr, nullptr);
    debugPrint->changeFont(systemFont);
    systemConsoleManager = JUTConsoleManager::createManager(nullptr);
    systemConsole = JUTConsole::create(60, 200, nullptr);
    systemConsole->setFont(systemFont);

    if (CSetUpParam::renderMode->efbHeight < 300)
    {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight() * 0.5f);
        systemConsole->setPosition(20, 25);
    }
    else
    {
        systemConsole->setFontSize(systemFont->getWidth() * 0.85f, systemFont->getHeight());
        systemConsole->setPosition(20, 50);
    }
    systemConsole->setHeight(25);
    systemConsole->setVisible(false);
    systemConsole->setOutput(JUTConsole::OUTPUT_OSREPORT | JUTConsole::OUTPUT_CONSOLE);
    JUTSetReportConsole(systemConsole);
    JUTSetWarningConsole(systemConsole);
    void *mem = systemHeap->alloc(CSetUpParam::exConsoleBufferSize, 4);
    JUTException::createConsole(mem, CSetUpParam::exConsoleBufferSize);
}