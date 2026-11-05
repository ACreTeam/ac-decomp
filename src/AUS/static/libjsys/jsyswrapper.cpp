#include "libjsys/jsyswrapper.h"

#include "JSystem/JSystem.h"
#include "JSystem/JKernel/JKRExpHeap.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTFader.h"
#include "JSystem/J2D/J2DGrafContext.h"
#include "JSystem/JFramework/JFWDisplay.h"
#include "JSystem/JFramework/JFWSystem.h"
#include "JSystem/JKernel/JKRDecomp.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JKernel/JKRDvdRipper.h"
#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JUtility/JUTFsFont.h"
#include "JSystem/J2DGraph/J2DPrint.h"

#include "MSL_C/printf.h"

// Retain stripped wrappers needed for weak emission order; see DnM+'s static.map.

#include "libjsys/jsyswrapper_main.cpp"

static inline void enter_(int x, int y, int show_count, const char* fmt, va_list arg) {
    JUTDbPrint* manager = JUTDbPrint::getManager();
    if (!manager || !manager->isVisible()) return;
    char buf[256];
    int len = vsnprintf(buf, sizeof(buf), fmt, arg);
    if (len >= 0) manager->enter(x, y, show_count, buf, len >= (int)sizeof(buf) ? sizeof(buf) - 1 : len);
}

extern void JC_JUTConsole_print_f_va(void* console, const char* fmt, va_list arg) {
    reinterpret_cast<JUTConsole*>(console)->print_f_va(fmt, arg);
}

extern void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...) {
    va_list arg;
    va_start(arg, fmt);
    enter_(x, y, show_count, fmt, arg);
    va_end(arg);
}

extern void* JW_Alloc(size_t size, int align) {
    return JC_JKRHeap_alloc(JC_JFWSystem_getSystemHeap(), size, align);
}

extern s32 JW_Resize(void* ptr, size_t new_size) {
    return JC_JKRHeap_resize(JC_JFWSystem_getSystemHeap(), ptr, new_size);
}

extern void JW_Free(void* ptr) {
    JC_JKRHeap_free(JC_JFWSystem_getSystemHeap(), ptr);
}

extern size_t JW_GetMemBlockSize(void* ptr) {
    return JC_JKRHeap_getSize(JC_JFWSystem_getSystemHeap(), ptr);
}

extern void JW_JUTXfb_clearIndex(void) {
    JC_JUTXfb_clearIndex(JC_JUTXfb_getManager());
}


#include "libjsys/jsyswrapper_ext.cpp"
