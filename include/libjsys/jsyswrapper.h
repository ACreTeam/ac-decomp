#ifndef JSYSWRAPPER_H
#define JSYSWRAPPER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void JW_BeginFrame();
extern void JW_EndFrame();
extern void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...);
extern void JW_SetLowResoMode(BOOL enable);
extern void JW_SetProgressiveMode(BOOL enable);

extern void* JC_JFWSystem_getSystemConsole();
extern void* JC_JFWSystem_getRootHeap();

extern int JC_JKRHeap_dump(void* heap);
extern s32 JC_JKRHeap_getTotalFreeSize(void* heap);

extern int JC_JUTConsole_isVisible(void* console);
extern void JC_JUTConsole_setVisible(void* console, BOOL visible);
extern void JC_JUTConsole_clear(void* console);
extern void JC_JUTConsole_scroll(void* console, int scroll);
extern int JC_JUTConsole_getPositionX(void* console);
extern void JC_JUTConsole_setPosition(void* console, int x, int y);
extern int JC_JUTConsole_getOutput(void* console);
extern int JC_JUTConsole_getLineOffset(void* console);
extern void JC_JUTConsole_dumpToTerminal(void* console, int lines);
extern void JC_JUTConsole_setOutput(void* console, int output);

extern void* JC_JUTDbPrint_getManager();
extern void JC_JUTDbPrint_setVisible(void* dbprint, BOOL visible);

extern void* JC_JUTProcBar_getManager();
extern void JC_JUTProcBar_setVisible(void* procbar, BOOL visible);
extern void JC_JUTProcBar_setVisibleHeapBar(void* procbar, BOOL visible);

#ifdef __cplusplus
}
#endif

#endif
