#include "libultra/libultra.h"
#include <string.h>
#include "dolphin/os.h"
#include "dolphin/os/OSTime.h"

extern OSTime __osTimeOffset;

void bcopy(void* __src, void* __dst, size_t __n) {
    memmove(__dst, __src, __n);
}


int bcmp(void* __s1, void* __s2, size_t __n) {
    return memcmp(__s1, __s2, __n);
}

void bzero(void* __s, size_t __n) {
    memset(__s, 0, __n);
}
void osSyncPrintf(const char* format, ...){
    va_list arg;
    va_start(arg, format);
    OSVReport(format, arg);
    va_end(arg);

}
void osWritebackDCache(void* buf, u32 len){
	 DCStoreRange(buf, len);
}

u32 osGetCount(void){
	return OSGetTick();
}

