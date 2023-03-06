#include "TRK/dolphin_trk.h"

__declspec(section ".init") void* TRK_memset(void* dst, int val, size_t size){
    TRK_fill_mem(dst, val, size);
    
    return dst;
}

__declspec(section ".init") void *TRK_memcpy(void *dst, const void *src, size_t n)
{
    const unsigned char *s = (const unsigned char *)src - 1;
    unsigned char *d = (unsigned char *)dst - 1;

    n++;
    while (--n != 0)
        *++d = *++s;
    return dst;
}
