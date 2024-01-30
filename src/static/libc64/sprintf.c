#include "libc64/sprintf.h"

#include "libultra/xprintf.h"
#include "_mem.h"


static void* proutPrintf(void* dst, const char* fmt, int size) {
    return (void*)((u8*)memcpy(dst, fmt, size) + size);
}

int sprintf(char* dst, const char* fmt, ...) {
    int ret;
    va_list args;
    va_start(args, fmt);

    ret = _Printf(&proutPrintf, dst, fmt, args);
    if (ret >= 0) {
        dst[ret] = '\0';
    }

    va_end(args);

    return ret;
}
