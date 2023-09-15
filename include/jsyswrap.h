#ifndef JSYSWRAP_H
#define JSYSWRAP_H

#include "types.h"
#include "dolphin/gx.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void JW_JUTReport(int pos_x, int pos_y, int show_count, const char* fmt, ...);
extern void JC_JFWDisplay_startFadeOut(void*, int);
extern void* JC_JFWDisplay_getManager();
extern void JC_JFWDisplay_clearEfb(void*, GXColor*);
extern GXRenderModeObj* JC_JFWDisplay_getRenderMode(void*);
extern void* JC_JFWDisplay_changeToSingleXfb(void*, int);

extern void JC_JFWDisplay_startFadeIn(void*, int);
extern void JC_JFWDisplay_changeToDoubleXfb(void*);
extern u32 JC__JKRGetResource(char*);
extern int JC__JKRGetMemBlockSize(int, u32);

extern void JC__JKRRemoveResource(void*);

#ifdef __cplusplus
}
#endif

#endif
