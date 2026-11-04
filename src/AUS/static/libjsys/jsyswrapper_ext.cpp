extern void JC_JUTConsole_print_f_va(void* console, const char* fmt, va_list arg) {
    char buf[256];
    
    vsnprintf(buf, sizeof(buf), fmt, arg);
    reinterpret_cast<JUTConsole*>(console)->print(buf);
}

extern void JW_JUTReport(int x, int y, int show_count, const char* fmt, ...) {
    char buf[256];
    va_list arg;
    int len;
    int shown_len;

    va_start(arg, fmt);
    len = (int)vsnprintf(buf, sizeof(buf), fmt, arg);
    va_end(arg);

    if (len >= 0) {
        JUTDbPrint::sDebugPrint->enter(x, y, show_count, buf, len >= (int)sizeof(buf) ? sizeof(buf) - 1 : len);
    }
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
