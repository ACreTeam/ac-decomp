#ifndef _JSYSTEM_JFW_JFWSYSTEM_H
#define _JSYSTEM_JFW_JFWSYSTEM_H

#include <dolphin/gx.h>
#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JKernel/JKRThread.h"
#include "JSystem/JUtility/JUTAssertion.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTFont.h"
#include "types.h"

// Maybe these are namespaces?
struct JFWSystem
{
    struct CSetUpParam
    {
        static int maxStdHeaps;
        static u32 sysHeapSize;
        static u32 fifoBufSize;
        static u32 aramAudioBufSize;
        static u32 aramGraphBufSize;
        static s32 streamPriority;
        static s32 decompPriority;
        static s32 aPiecePriority;
        static const ResFONT *systemFontRes;
        static const _GXRenderModeObj *renderMode;
        static u32 exConsoleBufferSize;
    };

    static void firstInit();
    static void init();

    static JKRHeap *rootHeap;
    static JKRHeap *systemHeap;
    static JKRThread *mainThread;
    static JUTDbPrint *debugPrint;
    static JUTFont *systemFont;
    static JUTConsoleManager *systemConsoleManager;
    static JUTConsole *systemConsole;
    static bool sInitCalled;


    
    // No idea how they formatted this lol
    static void setMaxStdHeap(int stdHeaps) { 
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::maxStdHeaps = stdHeaps; }
    static void setSysHeapSize(u32 heapSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::sysHeapSize = heapSize; }
    static void setFifoBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::fifoBufSize = bufSize; }
    
    // Inlines for Aram
    static void setAramAudioBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::aramAudioBufSize = bufSize; }
    static void setAramGraphBufSize(u32 bufSize) {
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::aramGraphBufSize = bufSize; }
    // probably some more inlines for other variables, not used by MKDD
    static void setRenderMode(const _GXRenderModeObj * rmode) {
#line 80
        JUT_ASSERT(sInitCalled == 0);
        CSetUpParam::renderMode = rmode; }
};

#endif
