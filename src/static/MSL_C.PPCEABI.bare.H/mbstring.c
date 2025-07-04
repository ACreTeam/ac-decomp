#include "MSL_C/mbstring.h"
#include "MSL_C/string.h"

#pragma dont_inline on
size_t unicode_to_UTF8(char* r3, wchar_t r4) {
    const char lut[] = { 0, 0, 0xC0, 0xE0 };
    int r5;
    char* r6;

    if (!r3)
        return 0;

    if (r4 < 0x80)
        r5 = 1;
    else if (r4 < 0x800)
        r5 = 2;
    else
        r5 = 3;

    r6 = r3 + r5;
    switch (r5) {
        case 3:
            *--r6 = (r4 & 0x3F) | 0x80;
            r4 >>= 6;
        case 2:
            *--r6 = (r4 & 0x3F) | 0x80;
            r4 >>= 6;
        case 1:
            *--r6 = r4 | lut[r5];
    }
    return r5;
}
#pragma dont_inline off

size_t wctomb(char* s, wchar_t wchar) {
    return unicode_to_UTF8(s, wchar);
}

size_t wcstombs(char* s, const wchar_t* pwcs, size_t n) {
    char decoded[4];
    wchar_t w;
    size_t num;
    int i = 0;
    const wchar_t* p;

    if (!s || !pwcs)
        return 0;

    p = pwcs;
    while (i <= n) {
        w = *p;

        if (!w) {
            s[i] = 0;
            break;
        }
        ++p;
        num = wctomb(decoded, w);

        if (i + num > n)
            break;

        strncpy(s + i, decoded, num);
        i += num;
    }
    return i;
}
