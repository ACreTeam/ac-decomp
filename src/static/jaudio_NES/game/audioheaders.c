#include "jaudio_NES/audioheaders.h"

ArcHeader AudioseqHeaderStart ATTRIBUTE_ALIGN(1) = {
    249,                     /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000,           /* rom addr */
            0x000009A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 1 */
            0x000009A0,           /* rom addr */
            0x00000FC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 2 */
            0x00001960,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 3 */
            0x00002340,           /* rom addr */
            0x00000B80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 4 */
            0x00002EC0,           /* rom addr */
            0x000012C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 5 */
            0x00004180,           /* rom addr */
            0x00001420,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 6 */
            0x000055A0,           /* rom addr */
            0x000007E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 7 */
            0x00005D80,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 8 */
            0x00006540,           /* rom addr */
            0x00000880,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 9 */
            0x00006DC0,           /* rom addr */
            0x000014A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 10 */
            0x00008260,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 11 */
            0x00008D60,           /* rom addr */
            0x00001200,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 12 */
            0x00009F60,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 13 */
            0x0000AAA0,           /* rom addr */
            0x000007A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 14 */
            0x0000B240,           /* rom addr */
            0x00000820,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 15 */
            0x0000BA60,           /* rom addr */
            0x00000C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 16 */
            0x0000C6E0,           /* rom addr */
            0x00000BE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 17 */
            0x0000D2C0,           /* rom addr */
            0x00000C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 18 */
            0x0000DF40,           /* rom addr */
            0x00000840,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 19 */
            0x0000E780,           /* rom addr */
            0x00000CA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 20 */
            0x0000F420,           /* rom addr */
            0x000016E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 21 */
            0x00010B00,           /* rom addr */
            0x00000D80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 22 */
            0x00011880,           /* rom addr */
            0x000009C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 23 */
            0x00012240,           /* rom addr */
            0x00000980,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 24 */
            0x00012BC0,           /* rom addr */
            0x00000E60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 25 */
            0x00013A20,           /* rom addr */
            0x00000BE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 26 */
            0x00014600,           /* rom addr */
            0x00000D40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 27 */
            0x00015340,           /* rom addr */
            0x000010E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 28 */
            0x00016420,           /* rom addr */
            0x00000E20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 29 */
            0x00017240,           /* rom addr */
            0x00001100,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 30 */
            0x00018340,           /* rom addr */
            0x00001700,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 31 */
            0x00019A40,           /* rom addr */
            0x000009C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 32 */
            0x0001A400,           /* rom addr */
            0x00000C60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 33 */
            0x0001B060,           /* rom addr */
            0x00000BC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 34 */
            0x0001BC20,           /* rom addr */
            0x00001260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 35 */
            0x0001CE80,           /* rom addr */
            0x00000880,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 36 */
            0x0001D700,           /* rom addr */
            0x00001020,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 37 */
            0x0001E720,           /* rom addr */
            0x00000640,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 38 */
            0x0001ED60,           /* rom addr */
            0x00000E20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 39 */
            0x0001FB80,           /* rom addr */
            0x00000760,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 40 */
            0x000202E0,           /* rom addr */
            0x00000A40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 41 */
            0x00020D20,           /* rom addr */
            0x000011E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 42 */
            0x00021F00,           /* rom addr */
            0x00000C20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 43 */
            0x00022B20,           /* rom addr */
            0x00000AA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 44 */
            0x000235C0,           /* rom addr */
            0x00000BE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 45 */
            0x000241A0,           /* rom addr */
            0x00002380,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 46 */
            0x00026520,           /* rom addr */
            0x00000680,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 47 */
            0x00026BA0,           /* rom addr */
            0x00002180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 48 */
            0x00028D20,           /* rom addr */
            0x00000AE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 49 */
            0x00029800,           /* rom addr */
            0x00000FE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 50 */
            0x0002A7E0,           /* rom addr */
            0x000010C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 51 */
            0x0002B8A0,           /* rom addr */
            0x00001640,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 52 */
            0x0002CEE0,           /* rom addr */
            0x000006E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 53 */
            0x0002D5C0,           /* rom addr */
            0x00000960,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 54 */
            0x0002DF20,           /* rom addr */
            0x00000BA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 55 */
            0x0002EAC0,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 56 */
            0x0002F4A0,           /* rom addr */
            0x00000AC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 57 */
            0x0002FF60,           /* rom addr */
            0x00000A40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 58 */
            0x000309A0,           /* rom addr */
            0x00001080,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 59 */
            0x00031A20,           /* rom addr */
            0x00001620,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 60 */
            0x00033040,           /* rom addr */
            0x00000560,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 61 */
            0x000335A0,           /* rom addr */
            0x00000580,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 62 */
            0x00033B20,           /* rom addr */
            0x00000660,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 63 */
            0x00034180,           /* rom addr */
            0x000003A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 64 */
            0x00034520,           /* rom addr */
            0x00000560,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 65 */
            0x00000040,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 66 */
            0x00034A80,           /* rom addr */
            0x00000740,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 67 */
            0x000351C0,           /* rom addr */
            0x00000E20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 68 */
            0x00035FE0,           /* rom addr */
            0x00000420,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 69 */
            0x00036400,           /* rom addr */
            0x000004E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 70 */
            0x0000003E,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 71 */
            0x000368E0,           /* rom addr */
            0x00000460,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 72 */
            0x00036D40,           /* rom addr */
            0x00000200,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 73 */
            0x00036F40,           /* rom addr */
            0x000001A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 74 */
            0x000370E0,           /* rom addr */
            0x00000680,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 75 */
            0x00037760,           /* rom addr */
            0x000003E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 76 */
            0x00037B40,           /* rom addr */
            0x000003C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 77 */
            0x00037F00,           /* rom addr */
            0x00000640,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 78 */
            0x00038540,           /* rom addr */
            0x00000600,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 79 */
            0x00038B40,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 80 */
            0x00039680,           /* rom addr */
            0x00000360,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 81 */
            0x000399E0,           /* rom addr */
            0x00001C40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 82 */
            0x0003B620,           /* rom addr */
            0x00000720,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 83 */
            0x0003BD40,           /* rom addr */
            0x00000F20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 84 */
            0x0003CC60,           /* rom addr */
            0x00001140,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 85 */
            0x0003DDA0,           /* rom addr */
            0x000008A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 86 */
            0x0003E640,           /* rom addr */
            0x000011E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 87 */
            0x0003F820,           /* rom addr */
            0x00000C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 88 */
            0x000404A0,           /* rom addr */
            0x00001160,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 89 */
            0x00041600,           /* rom addr */
            0x00001A20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 90 */
            0x00043020,           /* rom addr */
            0x00000C20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 91 */
            0x00043C40,           /* rom addr */
            0x00000B80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 92 */
            0x000447C0,           /* rom addr */
            0x00000D80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 93 */
            0x00045540,           /* rom addr */
            0x00000CA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 94 */
            0x000461E0,           /* rom addr */
            0x000012A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 95 */
            0x00047480,           /* rom addr */
            0x00000D40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 96 */
            0x000481C0,           /* rom addr */
            0x000008C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 97 */
            0x00048A80,           /* rom addr */
            0x00000CA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 98 */
            0x00049720,           /* rom addr */
            0x000013A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 99 */
            0x0004AAC0,           /* rom addr */
            0x000012C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 100 */
            0x0004BD80,           /* rom addr */
            0x00000D80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 101 */
            0x0004CB00,           /* rom addr */
            0x000014E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 102 */
            0x0004DFE0,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 103 */
            0x0004E9C0,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 104 */
            0x0004F4C0,           /* rom addr */
            0x00000780,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 105 */
            0x0004FC40,           /* rom addr */
            0x00000580,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 106 */
            0x000501C0,           /* rom addr */
            0x00000080,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 107 */
            0x00050240,           /* rom addr */
            0x00000080,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 108 */
            0x000502C0,           /* rom addr */
            0x00000060,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 109 */
            0x00050320,           /* rom addr */
            0x00000080,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 110 */
            0x000503A0,           /* rom addr */
            0x00000060,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 111 */
            0x00050400,           /* rom addr */
            0x00000420,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 112 */
            0x00050820,           /* rom addr */
            0x00000400,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 113 */
            0x00050C20,           /* rom addr */
            0x00000600,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 114 */
            0x00051220,           /* rom addr */
            0x00001720,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 115 */
            0x00052940,           /* rom addr */
            0x00000880,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 116 */
            0x000531C0,           /* rom addr */
            0x00000A80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 117 */
            0x00053C40,           /* rom addr */
            0x00000480,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 118 */
            0x000540C0,           /* rom addr */
            0x00000800,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 119 */
            0x000548C0,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 120 */
            0x00055080,           /* rom addr */
            0x00000A00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 121 */
            0x00055A80,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 122 */
            0x00056040,           /* rom addr */
            0x00000460,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 123 */
            0x000564A0,           /* rom addr */
            0x00000820,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 124 */
            0x00056CC0,           /* rom addr */
            0x00000860,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 125 */
            0x00057520,           /* rom addr */
            0x000007E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 126 */
            0x00057D00,           /* rom addr */
            0x00000660,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 127 */
            0x00058360,           /* rom addr */
            0x00000680,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 128 */
            0x000589E0,           /* rom addr */
            0x00000A20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 129 */
            0x00059400,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 130 */
            0x00059E60,           /* rom addr */
            0x00000C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 131 */
            0x0005AAE0,           /* rom addr */
            0x00000C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 132 */
            0x0005B760,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 133 */
            0x0005C260,           /* rom addr */
            0x00000760,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 134 */
            0x0005C9C0,           /* rom addr */
            0x00000880,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 135 */
            0x0005D240,           /* rom addr */
            0x000007A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 136 */
            0x0005D9E0,           /* rom addr */
            0x00000740,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 137 */
            0x0005E120,           /* rom addr */
            0x00000640,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 138 */
            0x0005E760,           /* rom addr */
            0x00000AE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 139 */
            0x0005F240,           /* rom addr */
            0x00000500,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 140 */
            0x0005F740,           /* rom addr */
            0x00000EA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 141 */
            0x000605E0,           /* rom addr */
            0x00000620,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 142 */
            0x00060C00,           /* rom addr */
            0x000005A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 143 */
            0x000611A0,           /* rom addr */
            0x00000EE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 144 */
            0x00062080,           /* rom addr */
            0x00000660,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 145 */
            0x000626E0,           /* rom addr */
            0x00000760,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 146 */
            0x00062E40,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 147 */
            0x000638A0,           /* rom addr */
            0x00000880,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 148 */
            0x00064120,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 149 */
            0x00064B00,           /* rom addr */
            0x00000780,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 150 */
            0x00065280,           /* rom addr */
            0x00000300,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 151 */
            0x00065580,           /* rom addr */
            0x00000860,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 152 */
            0x00065DE0,           /* rom addr */
            0x00000EC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 153 */
            0x00066CA0,           /* rom addr */
            0x000004C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 154 */
            0x00067160,           /* rom addr */
            0x00000560,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 155 */
            0x000676C0,           /* rom addr */
            0x00000900,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 156 */
            0x00067FC0,           /* rom addr */
            0x00000D40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 157 */
            0x00068D00,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 158 */
            0x000694C0,           /* rom addr */
            0x00000C60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 159 */
            0x0006A120,           /* rom addr */
            0x00000620,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 160 */
            0x0006A740,           /* rom addr */
            0x000013C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 161 */
            0x0006BB00,           /* rom addr */
            0x000007A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 162 */
            0x0006C2A0,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 163 */
            0x0006CDE0,           /* rom addr */
            0x00000100,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 164 */
            0x0006CEE0,           /* rom addr */
            0x00000420,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 165 */
            0x0006D300,           /* rom addr */
            0x00001100,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 166 */
            0x0006E400,           /* rom addr */
            0x000004C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 167 */
            0x0006E8C0,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 168 */
            0x0006EE80,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 169 */
            0x0006F1C0,           /* rom addr */
            0x00000660,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 170 */
            0x0006F820,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 171 */
            0x0006FDE0,           /* rom addr */
            0x00000940,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 172 */
            0x00070720,           /* rom addr */
            0x00000740,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 173 */
            0x000000AC,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 174 */
            0x000000AC,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 175 */
            0x000000AC,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 176 */
            0x00070E60,           /* rom addr */
            0x000002C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 177 */
            0x00071120,           /* rom addr */
            0x00000160,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 178 */
            0x00071280,           /* rom addr */
            0x00000300,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 179 */
            0x00071580,           /* rom addr */
            0x00000140,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 180 */
            0x000716C0,           /* rom addr */
            0x00000780,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 181 */
            0x00071E40,           /* rom addr */
            0x00000520,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 182 */
            0x00072360,           /* rom addr */
            0x00000040,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 183 */
            0x000723A0,           /* rom addr */
            0x00000720,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 184 */
            0x00072AC0,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 185 */
            0x00072E00,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 186 */
            0x00073140,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 187 */
            0x00073480,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 188 */
            0x000737C0,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 189 */
            0x00073B00,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 190 */
            0x00073E40,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 191 */
            0x00074180,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 192 */
            0x000744C0,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 193 */
            0x00074800,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 194 */
            0x00074B40,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 195 */
            0x00074E80,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 196 */
            0x000751C0,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 197 */
            0x00075500,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 198 */
            0x00075840,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 199 */
            0x00075B80,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 200 */
            0x00075EC0,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 201 */
            0x00076200,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 202 */
            0x00076540,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 203 */
            0x00076880,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 204 */
            0x00076BC0,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 205 */
            0x00076E20,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 206 */
            0x00077080,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 207 */
            0x000772E0,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 208 */
            0x00077540,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 209 */
            0x000777A0,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 210 */
            0x00077A00,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 211 */
            0x00077C60,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 212 */
            0x00077EC0,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 213 */
            0x00078120,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 214 */
            0x00078380,           /* rom addr */
            0x00001220,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 215 */
            0x000795A0,           /* rom addr */
            0x00002940,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 216 */
            0x0007BEE0,           /* rom addr */
            0x000022E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 217 */
            0x0007E1C0,           /* rom addr */
            0x000008E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 218 */
            0x0007EAA0,           /* rom addr */
            0x00001280,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 219 */
            0x0007FD20,           /* rom addr */
            0x00001B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 220 */
            0x00081860,           /* rom addr */
            0x000028A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 221 */
            0x00084100,           /* rom addr */
            0x00001D20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 222 */
            0x00085E20,           /* rom addr */
            0x00000660,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 223 */
            0x00086480,           /* rom addr */
            0x00001480,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 224 */
            0x00087900,           /* rom addr */
            0x00001120,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 225 */
            0x00088A20,           /* rom addr */
            0x000024E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 226 */
            0x0008AF00,           /* rom addr */
            0x00005180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 227 */
            0x00090080,           /* rom addr */
            0x00004220,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 228 */
            0x000942A0,           /* rom addr */
            0x00003780,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 229 */
            0x00097A20,           /* rom addr */
            0x00002C40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 230 */
            0x0009A660,           /* rom addr */
            0x00002040,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 231 */
            0x0009C6A0,           /* rom addr */
            0x00000A40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 232 */
            0x0009D0E0,           /* rom addr */
            0x00000860,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 233 */
            0x0009D940,           /* rom addr */
            0x00000A40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 234 */
            0x0009E380,           /* rom addr */
            0x00000860,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 235 */
            0x0009EBE0,           /* rom addr */
            0x00000B60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 236 */
            0x0009F740,           /* rom addr */
            0x000013C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 237 */
            0x000A0B00,           /* rom addr */
            0x00001D20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 238 */
            0x000A2820,           /* rom addr */
            0x00001640,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 239 */
            0x000A3E60,           /* rom addr */
            0x00000EA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 240 */
            0x000A4D00,           /* rom addr */
            0x00000CE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 241 */
            0x000A59E0,           /* rom addr */
            0x00000720,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 242 */
            0x000A6100,           /* rom addr */
            0x00005960,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 243 */
            0x000ABA60,            /* rom addr */
            0x00000660,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000,                /* param0 */
            0x0000,                /* param1 */
            0x0000,                /* param2 */
        },
        {
            /* entry 244 */
            0x000AC0C0,            /* rom addr */
            0x00000480,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000,                /* param0 */
            0x0000,                /* param1 */
            0x0000,                /* param2 */
        },
        {
            /* entry 245 */
            0x000AC540,            /* rom addr */
            0x00000660,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000,                /* param0 */
            0x0000,                /* param1 */
            0x0000,                /* param2 */
        },
        {
            /* entry 246 */
            0x000ACBA0,           /* rom addr */
            0x000055C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 247 */
            0x000B2160,           /* rom addr */
            0x00000020,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 248 */
            0x000B2180,            /* rom addr */
            0x0001D580,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x0000,                /* param0 */
            0x0000,                /* param1 */
            0x0000,                /* param2 */
        },
    },
};

ArcHeader AudiobankHeaderStart = {
    159,                     /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000,           /* rom addr */
            0x00003180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x00FF,               /* param0 */
            0x4800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 1 */
            0x00003180,           /* rom addr */
            0x00000B60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x01FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 2 */
            0x00003CE0,           /* rom addr */
            0x00004500,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x02FF,               /* param0 */
            0x6000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 3 */
            0x000081E0,           /* rom addr */
            0x00000820,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 4 */
            0x00008A00,           /* rom addr */
            0x00000DC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 5 */
            0x000097C0,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 6 */
            0x00009F80,           /* rom addr */
            0x00000DA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 7 */
            0x0000AD20,           /* rom addr */
            0x00000840,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 8 */
            0x0000B560,           /* rom addr */
            0x00000AA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 9 */
            0x0000C000,           /* rom addr */
            0x000008E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 10 */
            0x0000C8E0,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 11 */
            0x0000D340,           /* rom addr */
            0x000008A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 12 */
            0x0000DBE0,           /* rom addr */
            0x00000960,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 13 */
            0x0000E540,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 14 */
            0x0000F040,           /* rom addr */
            0x00000E00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 15 */
            0x0000FE40,           /* rom addr */
            0x000009A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 16 */
            0x000107E0,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 17 */
            0x000111C0,           /* rom addr */
            0x00000C00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 18 */
            0x00011DC0,           /* rom addr */
            0x00000740,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 19 */
            0x00012500,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 20 */
            0x00013040,           /* rom addr */
            0x00000800,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 21 */
            0x00013840,           /* rom addr */
            0x00000980,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 22 */
            0x000141C0,           /* rom addr */
            0x00000A00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0900,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 23 */
            0x00014BC0,           /* rom addr */
            0x00000A20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 24 */
            0x000155E0,           /* rom addr */
            0x00000A80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 25 */
            0x00016060,           /* rom addr */
            0x00000980,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 26 */
            0x000169E0,           /* rom addr */
            0x000010C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1038,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 27 */
            0x00017AA0,           /* rom addr */
            0x000005E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 28 */
            0x00018080,           /* rom addr */
            0x00000D40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1040,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 29 */
            0x00018DC0,           /* rom addr */
            0x00000B20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 30 */
            0x000198E0,           /* rom addr */
            0x00000680,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 31 */
            0x00019F60,           /* rom addr */
            0x00000480,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 32 */
            0x0001A3E0,           /* rom addr */
            0x000006E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0700,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 33 */
            0x0001AAC0,           /* rom addr */
            0x000003C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 34 */
            0x0001AE80,           /* rom addr */
            0x00000500,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 35 */
            0x0001B380,           /* rom addr */
            0x00000520,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 36 */
            0x0001B8A0,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 37 */
            0x0001BE60,           /* rom addr */
            0x00000700,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 38 */
            0x0001C560,           /* rom addr */
            0x000005E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 39 */
            0x0001CB40,           /* rom addr */
            0x00000340,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 40 */
            0x0001CE80,           /* rom addr */
            0x000000C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0100,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 41 */
            0x0001CF40,           /* rom addr */
            0x00000280,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 42 */
            0x0001D1C0,           /* rom addr */
            0x00000280,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 43 */
            0x0001D440,           /* rom addr */
            0x000009C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 44 */
            0x0001DE00,           /* rom addr */
            0x000009E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 45 */
            0x0001E7E0,           /* rom addr */
            0x00000BA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 46 */
            0x0001F380,           /* rom addr */
            0x00000960,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 47 */
            0x0001FCE0,           /* rom addr */
            0x00000940,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0A42,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 48 */
            0x00020620,           /* rom addr */
            0x00000360,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x001A,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 49 */
            0x00020980,           /* rom addr */
            0x00000360,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0019,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 50 */
            0x00020CE0,           /* rom addr */
            0x00000360,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x001A,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 51 */
            0x00021040,           /* rom addr */
            0x00000180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0100,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 52 */
            0x000211C0,           /* rom addr */
            0x000004C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0700,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 53 */
            0x00021680,           /* rom addr */
            0x000004C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0700,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 54 */
            0x00021B40,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 55 */
            0x000225A0,           /* rom addr */
            0x00000600,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 56 */
            0x00022BA0,           /* rom addr */
            0x00000CA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 57 */
            0x00023840,           /* rom addr */
            0x00000100,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0200,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 58 */
            0x00023940,           /* rom addr */
            0x00000220,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 59 */
            0x00023B60,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 60 */
            0x00023DC0,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0700,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 61 */
            0x00024380,           /* rom addr */
            0x00000280,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 62 */
            0x00024600,           /* rom addr */
            0x00000840,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 63 */
            0x00024E40,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A45,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 64 */
            0x00025980,           /* rom addr */
            0x00000D00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 65 */
            0x00026680,           /* rom addr */
            0x00000980,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 66 */
            0x00027000,           /* rom addr */
            0x00000560,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0700,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 67 */
            0x00027560,           /* rom addr */
            0x000004E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 68 */
            0x00027A40,           /* rom addr */
            0x000003E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 69 */
            0x00027E20,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 70 */
            0x00028880,           /* rom addr */
            0x000003E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 71 */
            0x00028C60,           /* rom addr */
            0x00000300,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 72 */
            0x00028F60,           /* rom addr */
            0x00000460,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 73 */
            0x000293C0,           /* rom addr */
            0x00000D80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 74 */
            0x0002A140,           /* rom addr */
            0x00000540,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 75 */
            0x0002A680,           /* rom addr */
            0x00000760,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 76 */
            0x0002ADE0,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 77 */
            0x0002B3A0,           /* rom addr */
            0x00000940,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 78 */
            0x0002BCE0,           /* rom addr */
            0x00000C00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A48,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 79 */
            0x0002C8E0,           /* rom addr */
            0x000000E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0100,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 80 */
            0x0002C9C0,           /* rom addr */
            0x00000440,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 81 */
            0x0002CE00,           /* rom addr */
            0x000009C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A48,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 82 */
            0x0002D7C0,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 83 */
            0x0002DF80,           /* rom addr */
            0x00000440,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 84 */
            0x0002E3C0,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 85 */
            0x0002EEC0,           /* rom addr */
            0x00000540,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 86 */
            0x0002F400,           /* rom addr */
            0x00000B60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 87 */
            0x0002FF60,           /* rom addr */
            0x00000760,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0B00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 88 */
            0x000306C0,           /* rom addr */
            0x00000AC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 89 */
            0x00031180,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 90 */
            0x00031C80,           /* rom addr */
            0x00000300,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 91 */
            0x00031F80,           /* rom addr */
            0x000003C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 92 */
            0x00032340,           /* rom addr */
            0x00000440,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 93 */
            0x00032780,           /* rom addr */
            0x00000260,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 94 */
            0x000329E0,           /* rom addr */
            0x000003E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 95 */
            0x00032DC0,           /* rom addr */
            0x000006A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 96 */
            0x00033460,           /* rom addr */
            0x00000CA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0B43,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 97 */
            0x00034100,           /* rom addr */
            0x000007C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x1000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 98 */
            0x000348C0,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 99 */
            0x00034E80,           /* rom addr */
            0x00000240,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0200,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 100 */
            0x000350C0,           /* rom addr */
            0x000006C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0900,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 101 */
            0x00035780,           /* rom addr */
            0x00000400,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 102 */
            0x00035B80,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 103 */
            0x000365E0,           /* rom addr */
            0x00000280,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0200,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 104 */
            0x00036860,           /* rom addr */
            0x00000180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 105 */
            0x000369E0,           /* rom addr */
            0x00000AE0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0C41,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 106 */
            0x000374C0,           /* rom addr */
            0x00000A20,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 107 */
            0x00037EE0,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 108 */
            0x000389E0,           /* rom addr */
            0x000009A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 109 */
            0x00039380,           /* rom addr */
            0x00000BA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 110 */
            0x00039F20,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 111 */
            0x0003AA20,           /* rom addr */
            0x00000F80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 112 */
            0x0003B9A0,           /* rom addr */
            0x00000620,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 113 */
            0x00000070,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 114 */
            0x00000070,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 115 */
            0x00000070,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 116 */
            0x0003BFC0,           /* rom addr */
            0x00000840,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 117 */
            0x0003C800,           /* rom addr */
            0x00000820,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0A48,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 118 */
            0x0003D020,           /* rom addr */
            0x000003A0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 119 */
            0x0003D3C0,           /* rom addr */
            0x000001C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 120 */
            0x0003D580,           /* rom addr */
            0x00000E00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x1048,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 121 */
            0x0003E380,           /* rom addr */
            0x00000460,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0500,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 122 */
            0x00000077,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0300,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 123 */
            0x0003E7E0,           /* rom addr */
            0x00000DC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 124 */
            0x0003F5A0,           /* rom addr */
            0x00000BA0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x04FF,               /* param0 */
            0x1000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 125 */
            0x00040140,           /* rom addr */
            0x000005E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 126 */
            0x00040720,           /* rom addr */
            0x00000860,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 127 */
            0x00040F80,           /* rom addr */
            0x000005C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 128 */
            0x00041540,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 129 */
            0x00042040,           /* rom addr */
            0x00000320,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 130 */
            0x00042360,           /* rom addr */
            0x00000A40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 131 */
            0x00042DA0,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0B40,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 132 */
            0x000438E0,           /* rom addr */
            0x00000C60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F48,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 133 */
            0x00044540,           /* rom addr */
            0x00000540,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0900,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 134 */
            0x00044A80,           /* rom addr */
            0x00000A60,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 135 */
            0x000454E0,           /* rom addr */
            0x000006C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0D00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 136 */
            0x00045BA0,           /* rom addr */
            0x00000900,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 137 */
            0x000464A0,           /* rom addr */
            0x000010C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1041,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 138 */
            0x00047560,           /* rom addr */
            0x00001180,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1040,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 139 */
            0x0000008A,           /* rom addr */
            0x00000000,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1040,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 140 */
            0x000486E0,           /* rom addr */
            0x00001040,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1044,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 141 */
            0x00049720,           /* rom addr */
            0x00000B40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 142 */
            0x0004A260,           /* rom addr */
            0x000004C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0900,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 143 */
            0x0004A720,           /* rom addr */
            0x00000EC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0E41,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 144 */
            0x0004B5E0,           /* rom addr */
            0x000008E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0C00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 145 */
            0x0004BEC0,           /* rom addr */
            0x00000A00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 146 */
            0x0004C8C0,           /* rom addr */
            0x00000920,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 147 */
            0x0004D1E0,           /* rom addr */
            0x000010C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1040,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 148 */
            0x0004E2A0,           /* rom addr */
            0x00000BC0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1000,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 149 */
            0x0004EE60,           /* rom addr */
            0x000010C0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x1040,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 150 */
            0x0004FF20,           /* rom addr */
            0x00000B00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0F00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 151 */
            0x00050A20,           /* rom addr */
            0x000003E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 152 */
            0x00050E00,           /* rom addr */
            0x00000620,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_TEMPORARY, /* cache type */
            0x03FF,               /* param0 */
            0x0800,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 153 */
            0x00051420,           /* rom addr */
            0x00005100,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x05FF,               /* param0 */
            0x7E00,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 154 */
            0x00056520,           /* rom addr */
            0x00003F00,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x05FF,               /* param0 */
            0x7600,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 155 */
            0x0005A420,           /* rom addr */
            0x00001E40,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x05FF,               /* param0 */
            0x3400,               /* param1 */
            0x0000,               /* param2 */
        },
        {
            /* entry 156 */
            0x0005C260,            /* rom addr */
            0x00004500,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x05FF,                /* param0 */
            0x7700,                /* param1 */
            0x0000,                /* param2 */
        },
        {
            /* entry 157 */
            0x00060760,            /* rom addr */
            0x00003020,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x05FF,                /* param0 */
            0x5300,                /* param1 */
            0x0000,                /* param2 */
        },
        {
            /* entry 158 */
            0x00063780,            /* rom addr */
            0x00004500,            /* size */
            MEDIUM_CART,           /* src medium */
            CACHE_LOAD_PERSISTENT, /* cache type */
            0x05FF,                /* param0 */
            0x7700,                /* param1 */
            0x0000,                /* param2 */
        },
    },
};

ArcHeader AudiowaveHeaderStart ATTRIBUTE_ALIGN(1) = {
    6,                       /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        {
            /* entry 0 */
            0x00000000,               /* rom addr */
            0x0003A940,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
        {
            /* entry 1 */
            0x0003A940,               /* rom addr */
            0x0000DF00,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
        {
            /* entry 2 */
            0x00048840,               /* rom addr */
            0x0006A080,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
        {
            /* entry 3 */
            0x000B28C0,               /* rom addr */
            0x001226E0,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
        {
            /* entry 4 */
            0x001D4FA0,               /* rom addr */
            0x000F0E20,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
        {
            /* entry 5 */
            0x002C5DC0,               /* rom addr */
            0x003ED620,               /* size */
            MEDIUM_CART,              /* src medium */
            CACHE_LOAD_EITHER_NOSYNC, /* cache type */
            0x0000,                   /* param0 */
            0x0000,                   /* param1 */
            0x0000,                   /* param2 */
        },
    },
};

ArcHeader AudiodataHeaderStart ATTRIBUTE_ALIGN(1) = {
    3,                       /* entries */
    0,                       /* unk param */
    nullptr,                 /* data start pointer */
    0,                       /* copy */
    { 0, 0, 0, 0, 0, 0, 0 }, /* pad */
    /* entries */
    {
        /* Audioseq */
        {
            /* entry 0 */
            0x00000000,           /* rom addr */
            0x000CF700,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        /* Audiobank */
        {
            /* entry 1 */
            0x000CF700,           /* rom addr */
            0x00067C80,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
        /* Audiowave */
        {
            /* entry 2 */
            0x00137380,           /* rom addr */
            0x006B33E0,           /* size */
            MEDIUM_CART,          /* src medium */
            CACHE_LOAD_PERMANENT, /* cache type */
            0x0000,               /* param0 */
            0x0000,               /* param1 */
            0x0000,               /* param2 */
        },
    },
};

// clang-format off
u8 AudiomapHeaderStart[] ATTRIBUTE_ALIGN(1) = {
    /* Absolute offsets into AudiomapHeaderStart of the info for each bank */
    0x01, 0xF2,  // seq 0 (0x01F2)
    0x01, 0xF4,  // seq 1 (0x01F4)
    0x01, 0xF6,  // seq 2 (0x01F6)
    0x01, 0xF8,  // seq 3 (0x01F8)
    0x01, 0xFA,  // seq 4 (0x01FA)
    0x01, 0xFC,  // seq 5 (0x01FC)
    0x01, 0xFE,  // seq 6 (0x01FE)
    0x02, 0x00,  // seq 7 (0x0200)
    0x02, 0x02,  // seq 8 (0x0202)
    0x02, 0x04,  // seq 9 (0x0204)
    0x02, 0x06,  // seq 10 (0x0206)
    0x02, 0x08,  // seq 11 (0x0208)
    0x02, 0x0A,  // seq 12 (0x020A)
    0x02, 0x0C,  // seq 13 (0x020C)
    0x02, 0x0E,  // seq 14 (0x020E)
    0x02, 0x10,  // seq 15 (0x0210)
    0x02, 0x12,  // seq 16 (0x0212)
    0x02, 0x14,  // seq 17 (0x0214)
    0x02, 0x16,  // seq 18 (0x0216)
    0x02, 0x18,  // seq 19 (0x0218)
    0x02, 0x1A,  // seq 20 (0x021A)
    0x02, 0x1C,  // seq 21 (0x021C)
    0x02, 0x1E,  // seq 22 (0x021E)
    0x02, 0x20,  // seq 23 (0x0220)
    0x02, 0x22,  // seq 24 (0x0222)
    0x02, 0x24,  // seq 25 (0x0224)
    0x02, 0x26,  // seq 26 (0x0226)
    0x02, 0x28,  // seq 27 (0x0228)
    0x02, 0x2A,  // seq 28 (0x022A)
    0x02, 0x2C,  // seq 29 (0x022C)
    0x02, 0x2E,  // seq 30 (0x022E)
    0x02, 0x30,  // seq 31 (0x0230)
    0x02, 0x32,  // seq 32 (0x0232)
    0x02, 0x34,  // seq 33 (0x0234)
    0x02, 0x36,  // seq 34 (0x0236)
    0x02, 0x38,  // seq 35 (0x0238)
    0x02, 0x3A,  // seq 36 (0x023A)
    0x02, 0x3C,  // seq 37 (0x023C)
    0x02, 0x3E,  // seq 38 (0x023E)
    0x02, 0x40,  // seq 39 (0x0240)
    0x02, 0x42,  // seq 40 (0x0242)
    0x02, 0x44,  // seq 41 (0x0244)
    0x02, 0x46,  // seq 42 (0x0246)
    0x02, 0x48,  // seq 43 (0x0248)
    0x02, 0x4A,  // seq 44 (0x024A)
    0x02, 0x4C,  // seq 45 (0x024C)
    0x02, 0x4E,  // seq 46 (0x024E)
    0x02, 0x50,  // seq 47 (0x0250)
    0x02, 0x52,  // seq 48 (0x0252)
    0x02, 0x54,  // seq 49 (0x0254)
    0x02, 0x56,  // seq 50 (0x0256)
    0x02, 0x58,  // seq 51 (0x0258)
    0x02, 0x5A,  // seq 52 (0x025A)
    0x02, 0x5C,  // seq 53 (0x025C)
    0x02, 0x5E,  // seq 54 (0x025E)
    0x02, 0x60,  // seq 55 (0x0260)
    0x02, 0x62,  // seq 56 (0x0262)
    0x02, 0x64,  // seq 57 (0x0264)
    0x02, 0x66,  // seq 58 (0x0266)
    0x02, 0x68,  // seq 59 (0x0268)
    0x02, 0x6A,  // seq 60 (0x026A)
    0x02, 0x6C,  // seq 61 (0x026C)
    0x02, 0x6E,  // seq 62 (0x026E)
    0x02, 0x70,  // seq 63 (0x0270)
    0x02, 0x72,  // seq 64 (0x0272)
    0x02, 0x74,  // seq 65 (0x0274)
    0x02, 0x76,  // seq 66 (0x0276)
    0x02, 0x78,  // seq 67 (0x0278)
    0x02, 0x7A,  // seq 68 (0x027A)
    0x02, 0x7C,  // seq 69 (0x027C)
    0x02, 0x7E,  // seq 70 (0x027E)
    0x02, 0x80,  // seq 71 (0x0280)
    0x02, 0x82,  // seq 72 (0x0282)
    0x02, 0x84,  // seq 73 (0x0284)
    0x02, 0x86,  // seq 74 (0x0286)
    0x02, 0x88,  // seq 75 (0x0288)
    0x02, 0x8A,  // seq 76 (0x028A)
    0x02, 0x8C,  // seq 77 (0x028C)
    0x02, 0x8E,  // seq 78 (0x028E)
    0x02, 0x90,  // seq 79 (0x0290)
    0x02, 0x92,  // seq 80 (0x0292)
    0x02, 0x94,  // seq 81 (0x0294)
    0x02, 0x96,  // seq 82 (0x0296)
    0x02, 0x98,  // seq 83 (0x0298)
    0x02, 0x9A,  // seq 84 (0x029A)
    0x02, 0x9C,  // seq 85 (0x029C)
    0x02, 0x9E,  // seq 86 (0x029E)
    0x02, 0xA0,  // seq 87 (0x02A0)
    0x02, 0xA2,  // seq 88 (0x02A2)
    0x02, 0xA4,  // seq 89 (0x02A4)
    0x02, 0xA6,  // seq 90 (0x02A6)
    0x02, 0xA8,  // seq 91 (0x02A8)
    0x02, 0xAA,  // seq 92 (0x02AA)
    0x02, 0xAC,  // seq 93 (0x02AC)
    0x02, 0xAE,  // seq 94 (0x02AE)
    0x02, 0xB0,  // seq 95 (0x02B0)
    0x02, 0xB2,  // seq 96 (0x02B2)
    0x02, 0xB4,  // seq 97 (0x02B4)
    0x02, 0xB6,  // seq 98 (0x02B6)
    0x02, 0xB8,  // seq 99 (0x02B8)
    0x02, 0xBA,  // seq 100 (0x02BA)
    0x02, 0xBC,  // seq 101 (0x02BC)
    0x02, 0xBE,  // seq 102 (0x02BE)
    0x02, 0xC0,  // seq 103 (0x02C0)
    0x02, 0xC2,  // seq 104 (0x02C2)
    0x02, 0xC4,  // seq 105 (0x02C4)
    0x02, 0xC6,  // seq 106 (0x02C6)
    0x02, 0xC8,  // seq 107 (0x02C8)
    0x02, 0xCA,  // seq 108 (0x02CA)
    0x02, 0xCC,  // seq 109 (0x02CC)
    0x02, 0xCE,  // seq 110 (0x02CE)
    0x02, 0xD0,  // seq 111 (0x02D0)
    0x02, 0xD2,  // seq 112 (0x02D2)
    0x02, 0xD4,  // seq 113 (0x02D4)
    0x02, 0xD6,  // seq 114 (0x02D6)
    0x02, 0xD8,  // seq 115 (0x02D8)
    0x02, 0xDA,  // seq 116 (0x02DA)
    0x02, 0xDC,  // seq 117 (0x02DC)
    0x02, 0xDE,  // seq 118 (0x02DE)
    0x02, 0xE0,  // seq 119 (0x02E0)
    0x02, 0xE2,  // seq 120 (0x02E2)
    0x02, 0xE4,  // seq 121 (0x02E4)
    0x02, 0xE6,  // seq 122 (0x02E6)
    0x02, 0xE8,  // seq 123 (0x02E8)
    0x02, 0xEA,  // seq 124 (0x02EA)
    0x02, 0xEC,  // seq 125 (0x02EC)
    0x02, 0xEE,  // seq 126 (0x02EE)
    0x02, 0xF0,  // seq 127 (0x02F0)
    0x02, 0xF2,  // seq 128 (0x02F2)
    0x02, 0xF4,  // seq 129 (0x02F4)
    0x02, 0xF6,  // seq 130 (0x02F6)
    0x02, 0xF8,  // seq 131 (0x02F8)
    0x02, 0xFA,  // seq 132 (0x02FA)
    0x02, 0xFC,  // seq 133 (0x02FC)
    0x02, 0xFE,  // seq 134 (0x02FE)
    0x03, 0x00,  // seq 135 (0x0300)
    0x03, 0x02,  // seq 136 (0x0302)
    0x03, 0x04,  // seq 137 (0x0304)
    0x03, 0x06,  // seq 138 (0x0306)
    0x03, 0x08,  // seq 139 (0x0308)
    0x03, 0x0A,  // seq 140 (0x030A)
    0x03, 0x0C,  // seq 141 (0x030C)
    0x03, 0x0E,  // seq 142 (0x030E)
    0x03, 0x10,  // seq 143 (0x0310)
    0x03, 0x12,  // seq 144 (0x0312)
    0x03, 0x14,  // seq 145 (0x0314)
    0x03, 0x16,  // seq 146 (0x0316)
    0x03, 0x18,  // seq 147 (0x0318)
    0x03, 0x1A,  // seq 148 (0x031A)
    0x03, 0x1C,  // seq 149 (0x031C)
    0x03, 0x1E,  // seq 150 (0x031E)
    0x03, 0x20,  // seq 151 (0x0320)
    0x03, 0x22,  // seq 152 (0x0322)
    0x03, 0x24,  // seq 153 (0x0324)
    0x03, 0x26,  // seq 154 (0x0326)
    0x03, 0x28,  // seq 155 (0x0328)
    0x03, 0x2A,  // seq 156 (0x032A)
    0x03, 0x2C,  // seq 157 (0x032C)
    0x03, 0x2E,  // seq 158 (0x032E)
    0x03, 0x30,  // seq 159 (0x0330)
    0x03, 0x32,  // seq 160 (0x0332)
    0x03, 0x34,  // seq 161 (0x0334)
    0x03, 0x36,  // seq 162 (0x0336)
    0x03, 0x38,  // seq 163 (0x0338)
    0x03, 0x3A,  // seq 164 (0x033A)
    0x03, 0x3C,  // seq 165 (0x033C)
    0x03, 0x3E,  // seq 166 (0x033E)
    0x03, 0x40,  // seq 167 (0x0340)
    0x03, 0x42,  // seq 168 (0x0342)
    0x03, 0x44,  // seq 169 (0x0344)
    0x03, 0x46,  // seq 170 (0x0346)
    0x03, 0x48,  // seq 171 (0x0348)
    0x03, 0x4A,  // seq 172 (0x034A)
    0x03, 0x4C,  // seq 173 (0x034C)
    0x03, 0x4E,  // seq 174 (0x034E)
    0x03, 0x50,  // seq 175 (0x0350)
    0x03, 0x52,  // seq 176 (0x0352)
    0x03, 0x54,  // seq 177 (0x0354)
    0x03, 0x56,  // seq 178 (0x0356)
    0x03, 0x58,  // seq 179 (0x0358)
    0x03, 0x5A,  // seq 180 (0x035A)
    0x03, 0x5C,  // seq 181 (0x035C)
    0x03, 0x5E,  // seq 182 (0x035E)
    0x03, 0x60,  // seq 183 (0x0360)
    0x03, 0x62,  // seq 184 (0x0362)
    0x03, 0x64,  // seq 185 (0x0364)
    0x03, 0x66,  // seq 186 (0x0366)
    0x03, 0x68,  // seq 187 (0x0368)
    0x03, 0x6A,  // seq 188 (0x036A)
    0x03, 0x6C,  // seq 189 (0x036C)
    0x03, 0x6E,  // seq 190 (0x036E)
    0x03, 0x70,  // seq 191 (0x0370)
    0x03, 0x72,  // seq 192 (0x0372)
    0x03, 0x74,  // seq 193 (0x0374)
    0x03, 0x76,  // seq 194 (0x0376)
    0x03, 0x78,  // seq 195 (0x0378)
    0x03, 0x7A,  // seq 196 (0x037A)
    0x03, 0x7C,  // seq 197 (0x037C)
    0x03, 0x7E,  // seq 198 (0x037E)
    0x03, 0x80,  // seq 199 (0x0380)
    0x03, 0x82,  // seq 200 (0x0382)
    0x03, 0x84,  // seq 201 (0x0384)
    0x03, 0x86,  // seq 202 (0x0386)
    0x03, 0x88,  // seq 203 (0x0388)
    0x03, 0x8A,  // seq 204 (0x038A)
    0x03, 0x8C,  // seq 205 (0x038C)
    0x03, 0x8E,  // seq 206 (0x038E)
    0x03, 0x90,  // seq 207 (0x0390)
    0x03, 0x92,  // seq 208 (0x0392)
    0x03, 0x94,  // seq 209 (0x0394)
    0x03, 0x96,  // seq 210 (0x0396)
    0x03, 0x98,  // seq 211 (0x0398)
    0x03, 0x9A,  // seq 212 (0x039A)
    0x03, 0x9C,  // seq 213 (0x039C)
    0x03, 0x9E,  // seq 214 (0x039E)
    0x03, 0xA0,  // seq 215 (0x03A0)
    0x03, 0xA2,  // seq 216 (0x03A2)
    0x03, 0xA4,  // seq 217 (0x03A4)
    0x03, 0xA6,  // seq 218 (0x03A6)
    0x03, 0xA8,  // seq 219 (0x03A8)
    0x03, 0xAA,  // seq 220 (0x03AA)
    0x03, 0xAC,  // seq 221 (0x03AC)
    0x03, 0xAE,  // seq 222 (0x03AE)
    0x03, 0xB0,  // seq 223 (0x03B0)
    0x03, 0xB2,  // seq 224 (0x03B2)
    0x03, 0xB4,  // seq 225 (0x03B4)
    0x03, 0xB6,  // seq 226 (0x03B6)
    0x03, 0xB8,  // seq 227 (0x03B8)
    0x03, 0xBA,  // seq 228 (0x03BA)
    0x03, 0xBC,  // seq 229 (0x03BC)
    0x03, 0xBE,  // seq 230 (0x03BE)
    0x03, 0xC0,  // seq 231 (0x03C0)
    0x03, 0xC2,  // seq 232 (0x03C2)
    0x03, 0xC4,  // seq 233 (0x03C4)
    0x03, 0xC6,  // seq 234 (0x03C6)
    0x03, 0xC8,  // seq 235 (0x03C8)
    0x03, 0xCA,  // seq 236 (0x03CA)
    0x03, 0xCC,  // seq 237 (0x03CC)
    0x03, 0xCE,  // seq 238 (0x03CE)
    0x03, 0xD0,  // seq 239 (0x03D0)
    0x03, 0xD2,  // seq 240 (0x03D2)
    0x03, 0xD4,  // seq 241 (0x03D4)
    0x03, 0xD6,  // seq 242 (0x03D6)
    0x03, 0xDB,  // seq 243 (0x03DB)
    0x03, 0xDD,  // seq 244 (0x03DD)
    0x03, 0xDF,  // seq 245 (0x03DF)
    0x03, 0xE1,  // seq 246 (0x03E1)
    0x03, 0xE4,  // seq 247 (0x03E4)
    0x03, 0xE6,  // seq 248 (0x03E6)

    /* Bank info: num banks (1 byte) followed by bank IDs (1 byte each) */
    1, 0x01, // seq 0
    1, 0x01, // seq 1
    1, 0x01, // seq 2
    1, 0x01, // seq 3
    1, 0x01, // seq 4
    1, 0x01, // seq 5
    1, 0x01, // seq 6
    1, 0x01, // seq 7
    1, 0x01, // seq 8
    1, 0x01, // seq 9
    1, 0x01, // seq 10
    1, 0x01, // seq 11
    1, 0x01, // seq 12
    1, 0x01, // seq 13
    1, 0x01, // seq 14
    1, 0x01, // seq 15
    1, 0x01, // seq 16
    1, 0x01, // seq 17
    1, 0x01, // seq 18
    1, 0x01, // seq 19
    1, 0x01, // seq 20
    1, 0x01, // seq 21
    1, 0x01, // seq 22
    1, 0x01, // seq 23
    1, 0x01, // seq 24
    1, 0x01, // seq 25
    1, 0x01, // seq 26
    1, 0x01, // seq 27
    1, 0x01, // seq 28
    1, 0x01, // seq 29
    1, 0x01, // seq 30
    1, 0x01, // seq 31
    1, 0x01, // seq 32
    1, 0x01, // seq 33
    1, 0x01, // seq 34
    1, 0x01, // seq 35
    1, 0x01, // seq 36
    1, 0x01, // seq 37
    1, 0x01, // seq 38
    1, 0x01, // seq 39
    1, 0x01, // seq 40
    1, 0x01, // seq 41
    1, 0x01, // seq 42
    1, 0x01, // seq 43
    1, 0x01, // seq 44
    1, 0x01, // seq 45
    1, 0x01, // seq 46
    1, 0x01, // seq 47
    1, 0x01, // seq 48
    1, 0x01, // seq 49
    1, 0x01, // seq 50
    1, 0x01, // seq 51
    1, 0x01, // seq 52
    1, 0x01, // seq 53
    1, 0x01, // seq 54
    1, 0x01, // seq 55
    1, 0x01, // seq 56
    1, 0x01, // seq 57
    1, 0x1C, // seq 58
    1, 0x1E, // seq 59
    1, 0x1F, // seq 60
    1, 0x20, // seq 61
    1, 0x21, // seq 62
    1, 0x22, // seq 63
    1, 0x23, // seq 64
    1, 0x23, // seq 65
    1, 0x24, // seq 66
    1, 0x25, // seq 67
    1, 0x1D, // seq 68
    1, 0x26, // seq 69
    1, 0x21, // seq 70
    1, 0x27, // seq 71
    1, 0x28, // seq 72
    1, 0x29, // seq 73
    1, 0x2A, // seq 74
    1, 0x2B, // seq 75
    1, 0x2B, // seq 76
    1, 0x2C, // seq 77
    1, 0x2D, // seq 78
    1, 0x2E, // seq 79
    1, 0x2F, // seq 80
    1, 0x0E, // seq 81
    1, 0x07, // seq 82
    1, 0x10, // seq 83
    1, 0x14, // seq 84
    1, 0x12, // seq 85
    1, 0x16, // seq 86
    1, 0x17, // seq 87
    1, 0x08, // seq 88
    1, 0x15, // seq 89
    1, 0x05, // seq 90
    1, 0x19, // seq 91
    1, 0x0D, // seq 92
    1, 0x18, // seq 93
    1, 0x13, // seq 94
    1, 0x04, // seq 95
    1, 0x06, // seq 96
    1, 0x0C, // seq 97
    1, 0x0A, // seq 98
    1, 0x1A, // seq 99
    1, 0x11, // seq 100
    1, 0x0B, // seq 101
    1, 0x0F, // seq 102
    1, 0x09, // seq 103
    1, 0x03, // seq 104
    1, 0x1B, // seq 105
    1, 0x30, // seq 106
    1, 0x30, // seq 107
    1, 0x31, // seq 108
    1, 0x31, // seq 109
    1, 0x32, // seq 110
    1, 0x33, // seq 111
    1, 0x34, // seq 112
    1, 0x35, // seq 113
    1, 0x36, // seq 114
    1, 0x37, // seq 115
    1, 0x38, // seq 116
    1, 0x39, // seq 117
    1, 0x3A, // seq 118
    1, 0x3B, // seq 119
    1, 0x3C, // seq 120
    1, 0x3D, // seq 121
    1, 0x3E, // seq 122
    1, 0x3F, // seq 123
    1, 0x40, // seq 124
    1, 0x41, // seq 125
    1, 0x42, // seq 126
    1, 0x43, // seq 127
    1, 0x44, // seq 128
    1, 0x45, // seq 129
    1, 0x46, // seq 130
    1, 0x47, // seq 131
    1, 0x48, // seq 132
    1, 0x49, // seq 133
    1, 0x4A, // seq 134
    1, 0x4B, // seq 135
    1, 0x4C, // seq 136
    1, 0x4D, // seq 137
    1, 0x4E, // seq 138
    1, 0x4F, // seq 139
    1, 0x50, // seq 140
    1, 0x51, // seq 141
    1, 0x52, // seq 142
    1, 0x53, // seq 143
    1, 0x54, // seq 144
    1, 0x55, // seq 145
    1, 0x56, // seq 146
    1, 0x57, // seq 147
    1, 0x58, // seq 148
    1, 0x59, // seq 149
    1, 0x5A, // seq 150
    1, 0x5B, // seq 151
    1, 0x5C, // seq 152
    1, 0x5D, // seq 153
    1, 0x5E, // seq 154
    1, 0x5F, // seq 155
    1, 0x60, // seq 156
    1, 0x61, // seq 157
    1, 0x62, // seq 158
    1, 0x63, // seq 159
    1, 0x64, // seq 160
    1, 0x65, // seq 161
    1, 0x66, // seq 162
    1, 0x67, // seq 163
    1, 0x68, // seq 164
    1, 0x69, // seq 165
    1, 0x6A, // seq 166
    1, 0x6B, // seq 167
    1, 0x6C, // seq 168
    1, 0x6D, // seq 169
    1, 0x6E, // seq 170
    1, 0x6F, // seq 171
    1, 0x70, // seq 172
    1, 0x70, // seq 173
    1, 0x70, // seq 174
    1, 0x70, // seq 175
    1, 0x74, // seq 176
    1, 0x75, // seq 177
    1, 0x76, // seq 178
    1, 0x77, // seq 179
    1, 0x78, // seq 180
    1, 0x79, // seq 181
    1, 0x7A, // seq 182
    1, 0x7B, // seq 183
    1, 0x7C, // seq 184
    1, 0x7C, // seq 185
    1, 0x7C, // seq 186
    1, 0x7C, // seq 187
    1, 0x7C, // seq 188
    1, 0x7C, // seq 189
    1, 0x7C, // seq 190
    1, 0x7C, // seq 191
    1, 0x7C, // seq 192
    1, 0x7C, // seq 193
    1, 0x7C, // seq 194
    1, 0x7C, // seq 195
    1, 0x7C, // seq 196
    1, 0x7C, // seq 197
    1, 0x7C, // seq 198
    1, 0x7C, // seq 199
    1, 0x7C, // seq 200
    1, 0x7C, // seq 201
    1, 0x7C, // seq 202
    1, 0x7C, // seq 203
    1, 0x7C, // seq 204
    1, 0x7C, // seq 205
    1, 0x7C, // seq 206
    1, 0x7C, // seq 207
    1, 0x7C, // seq 208
    1, 0x7C, // seq 209
    1, 0x7C, // seq 210
    1, 0x7C, // seq 211
    1, 0x7C, // seq 212
    1, 0x7C, // seq 213
    1, 0x7D, // seq 214
    1, 0x7E, // seq 215
    1, 0x7F, // seq 216
    1, 0x80, // seq 217
    1, 0x81, // seq 218
    1, 0x82, // seq 219
    1, 0x83, // seq 220
    1, 0x84, // seq 221
    1, 0x85, // seq 222
    1, 0x86, // seq 223
    1, 0x87, // seq 224
    1, 0x88, // seq 225
    1, 0x89, // seq 226
    1, 0x8A, // seq 227
    1, 0x8B, // seq 228
    1, 0x8C, // seq 229
    1, 0x8D, // seq 230
    1, 0x8E, // seq 231
    1, 0x8F, // seq 232
    1, 0x90, // seq 233
    1, 0x91, // seq 234
    1, 0x92, // seq 235
    1, 0x93, // seq 236
    1, 0x94, // seq 237
    1, 0x95, // seq 238
    1, 0x96, // seq 239
    1, 0x97, // seq 240
    1, 0x98, // seq 241
    4, 0x02, 0x9B, 0x9A, 0x99, // seq 242
    1, 0x9C, // seq 243
    1, 0x9D, // seq 244
    1, 0x9E, // seq 245
    2, 0x02, 0x00, // seq 246
    1, 0x99, // seq 247
    1, 0x02, // seq 248

    /* Padding */
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
    0x00,
};
// clang-format on
