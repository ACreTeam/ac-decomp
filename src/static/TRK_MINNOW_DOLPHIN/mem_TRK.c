#include "TRK/_mem_trk.h"

__declspec(section ".init") void *TRK_memcpy(void *dst, const void *src, size_t n)
{
    const unsigned char *s = (const unsigned char *)src - 1;
    unsigned char *d = (unsigned char *)dst - 1;

    n++;
    while (--n != 0)
        *++d = *++s;
    return dst;
}

__declspec(section ".init") void* TRK_memset(void* dst, int val, size_t size){
    TRK_fill_mem(dst, val, size);
    
    return dst;
}

void TRK_fill_mem(void *dst, int val, u32 length) {
    u32    v = (u8)val;
    u32    i;

    union
    {
        u8 *cpd;
        u32 *lpd;
    } dstu;

    dstu.cpd = (((u8 *)dst) - 1);

    if (length >= 32)
    {
        i = ((~ (u32)dstu.cpd) & 3);

        if (i)
        {
            length -= i;

            do
                *++(dstu.cpd) = (u8)v;
            while (--i);
        }

        if (v)
            v |= ((v << 24) | (v << 16) | (v <<  8));

        dstu.lpd = (((u32 *)(dstu.cpd + 1)) - 1);

        i = (length >> 5);

        if (i)
        {
            do
            {
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
                *++(dstu.lpd) = v;
            } while (--i);
        }

        i = ((length & 31) >> 2);

        if (i)
        {
            do
                *++(dstu.lpd) = v;
            while (--i);
        }

        dstu.cpd = (((u8 *)(dstu.lpd + 1)) - 1);

        length &= 3;
    }

    if (length)
    {
        do
            *++(dstu.cpd) = (u8)v;
        while (--length);
    }
}
