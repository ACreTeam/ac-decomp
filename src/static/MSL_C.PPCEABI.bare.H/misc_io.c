void __close_all();
extern void (*__stdio_exit)();

void __stdio_atexit(void) {
    __stdio_exit = __close_all;
}
