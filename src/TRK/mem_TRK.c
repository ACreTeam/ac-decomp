#include "TRK/dolphin_trk.h"

__declspec(section ".init") void* TRK_memset(void* dst, int val, size_t size){
    TRK_fill_mem(dst, val, size);
    
    return dst;
}

__declspec(section ".init") void* TRK_memcpy(void* dst, const void* src, size_t size){
    const u8* s = (const u8*)src -1;
    u8* d = (u8*)dst -1;

    size++;
    while(--size != 0){
        *++d = *++s;
    return dst;
    }
}