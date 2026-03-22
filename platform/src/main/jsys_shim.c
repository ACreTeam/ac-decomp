/* jsys_shim.c — Stub implementations for JSystem (JW_/JC_) wrapper functions
 * and other GameCube-specific symbols not needed on macOS/Metal.
 * All functions that return pointers return NULL (or a sentinel value);
 * all void functions are no-ops.
 */
#include "types.h"
#include "dolphin/pad.h"
#include "dolphin/gx.h"
#include "dolphin/os/OSContext.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/vi.h"
#include "dolphin/gx/GXFifo.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

/* ------------------------------------------------------------------ */
/* JW_ functions (JSystem wrapper)                                     */
/* ------------------------------------------------------------------ */

void  JW_BeginFrame(void)              {}
void  JW_EndFrame(void)                {}
void  JW_Init(void)                    {}
void  JW_Init2(void)                   {}
void  JW_Init3(void)                   {}
void  JW_Cleanup(void)                 {}

void* JW_Alloc(size_t size, int align) {
    (void)align;
    return malloc(size);
}
void  JW_Free(void* ptr)               { free(ptr); }

int   JW_setClearColor(u8 r, u8 g, u8 b) {
    /* Could forward to gx_state clearColor — left as no-op for now */
    (void)r; (void)g; (void)b;
    return 0;
}

u32   JW_GetAramAddress(int res_no)    { (void)res_no; return 0; }
u32   JW_GetResSizeFileNo(int res_no)  { (void)res_no; return 0; }

void  JW_SetProgressiveMode(int e)     { (void)e; }
void  JW_SetLowResoMode(int e)         { (void)e; }
void  JW_SetLogoMode(int e)            { (void)e; }
void  JW_SetFamicomMode(int e)         { (void)e; }
void  JW_UpdateVideoMode(void)         {}
void  JW_SetVideoPan(u16 ox, u16 oy, u16 w, u16 h) { (void)ox; (void)oy; (void)w; (void)h; }

void  JW_JUTGamePad_read(void)         {}
void  JW_getPadStatus(PADStatus* s)    { if (s) memset(s, 0, sizeof(*s)); }
int   JW_JUTGamepad_getErrorStatus(void) { return 0; }
u32   JW_JUTGamepad_getButton(void)    { return 0; }
u32   JW_JUTGamepad_getTrigger(void)   { return 0; }
float JW_JUTGamepad_getSubStickValue(void) { return 0.0f; }
short JW_JUTGamepad_getSubStickAngle(void) { return 0; }

void  JW_JUTReport(int x, int y, int n, const char* fmt, ...) {
    (void)x; (void)y; (void)n; (void)fmt;
}
void  JW_JUTXfb_clearIndex(void)       {}
u8*   _JW_GetResourceAram(u32 addr, u8* dst, u32 size) { (void)addr; (void)dst; (void)size; return NULL; }

/* ------------------------------------------------------------------ */
/* JC_ functions (JSystem C wrappers)                                  */
/* ------------------------------------------------------------------ */

/* Dummy sentinel — returned by functions that normally give a manager/heap */
static uint8_t s_dummy_obj[256];

void* JC_JUTVideo_getManager(void)                                  { return s_dummy_obj; }
u32   JC_JUTVideo_getFbWidth(void* m)                               { (void)m; return 640; }
u32   JC_JUTVideo_getEfbHeight(void* m)                             { (void)m; return 480; }
void  JC_JUTVideo_setRenderMode(void* m, GXRenderModeObj* r)        { (void)m; (void)r; }

void  JC_JKRAramHeap_dump(void* heap)                               { (void)heap; }
void* JC_JKRAram_getAramHeap(void)                                  { return s_dummy_obj; }

void  JC_JUTConsole_setVisible(void* c, BOOL v)                     { (void)c; (void)v; }
void  JC_JUTConsole_clear(void* c)                                  { (void)c; }
void  JC_JUTConsole_scroll(void* c, int n)                          { (void)c; (void)n; }
int   JC_JUTConsole_isVisible(void* c)                              { (void)c; return 0; }
int   JC_JUTConsole_getPositionX(void* c)                           { (void)c; return 0; }
void  JC_JUTConsole_setPosition(void* c, int x, int y)              { (void)c; (void)x; (void)y; }
int   JC_JUTConsole_getOutput(void* c)                              { (void)c; return 0; }
int   JC_JUTConsole_getLineOffset(void* c)                          { (void)c; return 0; }
void  JC_JUTConsole_dumpToTerminal(void* c, int n)                  { (void)c; (void)n; }
void  JC_JUTConsole_setOutput(void* c, int o)                       { (void)c; (void)o; }
void  JC_JUTConsole_print_f_va(void* c, const char* fmt, va_list a) { (void)c; (void)fmt; (void)a; }

void* JC_JUTConsoleManager_getManager(void)                         { return s_dummy_obj; }
void  JC_JUTConsoleManager_drawDirect(void* m, int d)               { (void)m; (void)d; }

void* JC_JUTDbPrint_getManager(void)                                { return s_dummy_obj; }
void  JC_JUTDbPrint_setVisible(void* m, BOOL v)                     { (void)m; (void)v; }

void* JC_JUTProcBar_getManager(void)                                { return s_dummy_obj; }
void  JC_JUTProcBar_setVisible(void* m, BOOL v)                     { (void)m; (void)v; }
void  JC_JUTProcBar_setVisibleHeapBar(void* m, BOOL v)              { (void)m; (void)v; }

void* JC_JUTException_getManager(void)                              { return s_dummy_obj; }
void* JC_JUTException_getConsole(void)                              { return s_dummy_obj; }
int   JC_JUTException_readPad(void* m, u32* t, u32* b)             { (void)m; (void)t; (void)b; return 0; }
void  JC_JUTException_waitTime(u32 t)                               { (void)t; }
void  JC_JUTException_setPreUserCallback(void* cb)                  { (void)cb; }
void  JC_JUTException_setPostUserCallback(void* cb)                 { (void)cb; }

void  JC_JUTAssertion_changeDevice(int d)                           { (void)d; }

void  JC_JUTGamePad_read(void)                                      {}
PADStatus JC_JUTGamePad_getPadStatus(u32 port) {
    PADStatus s;
    memset(&s, 0, sizeof(s));
    (void)port;
    return s;
}
u8    JC_JUTGamePad_recalibrate(u32 port) { (void)port; return 0; }

void* JC_JFWDisplay_getManager(void)                                { return s_dummy_obj; }
int   JC_JFWDisplay_startFadeIn(void* m, int l)                     { (void)m; (void)l; return 0; }
void  JC_JFWDisplay_setFrameRate(void* m, u16 r)                    { (void)m; (void)r; }
int   JC_JFWDisplay_startFadeOut(void* m, int f)                    { (void)m; (void)f; return 0; }
void  JC_JFWDisplay_clearEfb(void* m, GXColor c)                    { (void)m; (void)c; }
const GXRenderModeObj* JC_JFWDisplay_getRenderMode(void* m)         { (void)m; return NULL; }
void* JC_JFWDisplay_changeToSingleXfb(void* m, int i)               { (void)m; (void)i; return NULL; }
void* JC_JFWDisplay_changeToDoubleXfb(void* m)                      { (void)m; return NULL; }

void* JC_JFWSystem_getSystemConsole(void)                           { return s_dummy_obj; }
void* JC_JFWSystem_getRootHeap(void)                                { return s_dummy_obj; }

void* JC__JKRGetResource(const char* name)                          { (void)name; return NULL; }
void  JC__JKRRemoveResource(void* r)                                { (void)r; }

int   JC_JKRHeap_dump(void* h)                                      { (void)h; return 0; }
int   JC_JKRHeap_getTotalFreeSize(void* h)                          { (void)h; return 0; }

void* JC__JKRAllocFromAram(size_t sz)                               { (void)sz; return NULL; }
u8*   JC__JKRAramToMainRam_block(void* ab, u8* rd, size_t sz)       { (void)ab; (void)rd; (void)sz; return NULL; }
void* JC__JKRMainRamToAram_block(u8* ra, void* ab, size_t sz)       { (void)ra; (void)ab; (void)sz; return NULL; }
u32   JC__JKRGetMemBlockSize(void* h, void* p)                      { (void)h; (void)p; return 0; }

/* ------------------------------------------------------------------ */
/* DC (data cache) operations — no-ops on macOS                        */
/* ------------------------------------------------------------------ */
void DCFlushRange(void* addr, u32 len)         { (void)addr; (void)len; }
void DCFlushRangeNoSync(void* addr, u32 len)   { (void)addr; (void)len; }
void DCInvalidateRange(void* addr, u32 len)    { (void)addr; (void)len; }
void DCStoreRange(void* addr, u32 len)         { (void)addr; (void)len; }
void DCStoreRangeNoSync(void* addr, u32 len)   { (void)addr; (void)len; }
void DCTouchRange(void* addr, u32 len)         { (void)addr; (void)len; }
void DCZeroRange(void* addr, u32 len)          { memset(addr, 0, len); }
void LCDisable(void)                            {}
void PPCSync(void)                              {}

/* ------------------------------------------------------------------ */
/* GX misc stubs                                                       */
/* ------------------------------------------------------------------ */
OSThread* GXGetCurrentGXThread(void) { return NULL; }

/* ------------------------------------------------------------------ */
/* Famicom (NES emulator) stubs — not supported on macOS               */
/* ------------------------------------------------------------------ */
void  famicom_mount_archive(void)           {}
int   famicom_mount_archive_end_check(void) { return 1; } /* done immediately */
int   famicom_rom_load_check(void)          { return 0; }
int   famicom_init(int id, void* alloc, void* player) {
    (void)id; (void)alloc; (void)player;
    return -1; /* failure */
}
int   famicom_cleanup(void)                 { return 0; }
void  famicom_1frame(void)                  {}
int   famicom_external_data_save(void* d)   { (void)d; return 0; }
int   famicom_external_data_save_check(void){ return 1; }
int   famicom_internal_data_load(void* d)   { (void)d; return 0; }
int   famicom_internal_data_save(void* d)   { (void)d; return 0; }
void  famicom_setCallback_getSaveChan(void* cb) { (void)cb; }
int   famicom_getErrorChan(void)            { return 0; }
int   famicom_get_disksystem_titles(void* buf, int n) { (void)buf; (void)n; return 0; }

/* ------------------------------------------------------------------ */
/* OS stubs not covered by os_shim.cpp                                 */
/* ------------------------------------------------------------------ */
OSContext* OSGetCurrentContext(void)                { return NULL; }
void       OSSetCurrentContext(OSContext* ctx)       { (void)ctx; }
void       OSClearContext(OSContext* ctx)             { (void)ctx; }
u32        OSGetStackPointer(void)                   { return 0; }
int        OSGetFontEncode(void)                     { return 0; }
int        OSGetProgressiveMode(void)                { return 0; }
void       OSSetProgressiveMode(int m)               { (void)m; }
int        OSGetSoundMode(void)                      { return 0; }
void       OSSetSoundMode(int m)                     { (void)m; }
int        OSGetResetSwitchState(void)               { return 0; }
void       OSRegisterResetFunction(void* fn)         { (void)fn; }
void       OSResetSystem(int r, u32 i, BOOL v)      { (void)r; (void)i; (void)v; }
void       OSInitAlarm(void)                         {}
long       OSCheckActiveThreads(void)                { return 1; }
void       HotResetIplMenu(void)                     {}

/* ------------------------------------------------------------------ */
/* SI (Serial Interface) stubs                                         */
/* ------------------------------------------------------------------ */
void  SIGetTypeAsync(u32 chan, void* cb)    { (void)chan; (void)cb; }
BOOL  SITransfer(u32 chan, void* out, u32 outLen, void* in, u32 inLen, void* cb, s32 us) {
    (void)chan; (void)out; (void)outLen; (void)in; (void)inLen; (void)cb; (void)us;
    return FALSE;
}
BOOL  PADRecalibrate(u32 mask)              { (void)mask; return FALSE; }

/* ------------------------------------------------------------------ */
/* VI stubs                                                            */
/* ------------------------------------------------------------------ */
void  VIConfigurePan(u16 x, u16 y, u16 w, u16 h) { (void)x; (void)y; (void)w; (void)h; }

/* ------------------------------------------------------------------ */
/* AI stubs not in dsp_shim.cpp                                        */
/* ------------------------------------------------------------------ */
u32   AIGetStreamSampleCount(void)          { return 0; }
void  AIResetStreamSampleCount(void)        {}
u32   AIGetStreamTrigger(void)              { return 0; }

/* ------------------------------------------------------------------ */
/* DSP stubs not in dsp_shim.cpp                                       */
/* ------------------------------------------------------------------ */
BOOL  DSPCheckMailFromDSP(void)             { return FALSE; }
BOOL  DSPCheckMailToDSP(void)               { return FALSE; }
u32   DSPReadMailFromDSP(void)              { return 0; }
void  DSPSendMailToDSP(u32 mail)            { (void)mail; }
