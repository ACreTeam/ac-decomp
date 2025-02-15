#include "m_name_table.h"
#include "m_shop.h"

mActor_name_t cloth_listA[] = {
// any season
    0x2400,
    0x2403,
    0x240C,
    0x2437,
    0x243D,
    0x2440,
    0x2443,
    0x2446,
    0x2449,
    0x2450,
    0x245E,
    0x2461,
    0x2464,
    0x246F,
    0x2474,
    0x2478,
    0x247B,
    0x2494,
    0x2498,
    0x249D,
    0x24A2,
    0x24A7,
    0x24A9,
    0x24AA,
    0x24AD,
    0x24B0,
    0x24B3,
    0x24BF,
    0x24C3,
    0x24D3,
    0x24D6,
    0x24E3,
// spring
    0x2426,
    0x242A,
    0x2468,
    0x247A,
    0x2485,
    0x24B4,
    0x24C9,
    0x24CD,
    0x24E8,
    0x24F1,
// summer
    0x2433,
    0x2435,
    0x2480,
    0x2488,
    0x248D,
    0x249C,
    0x24A5,
    0x24B9,
    0x24C5,
    0x24CB,
    0x24D7,
// fall
    0x240D,
    0x242B,
    0x2430,
    0x2455,
    0x2462,
    0x2470,
    0x24C2,
    0x24D2,
    0x24F6,
// winter
    0x2408,
    0x2431,
    0x246B,
    0x2482,
    0x2490,
    0x24A8,
    0x24DC,
    0x24E5,
    0x24E9,

    EMPTY_NO,
};

mActor_name_t cloth_listB[] = {
// any season
    0x2404,
    0x2406,
    0x240B,
    0x241D,
    0x2438,
    0x243B,
    0x243E,
    0x2441,
    0x2444,
    0x2447,
    0x244A,
    0x244D,
    0x2453,
    0x2465,
    0x2469,
    0x2471,
    0x2475,
    0x2479,
    0x247F,
    0x2491,
    0x249E,
    0x24AB,
    0x24AE,
    0x24B1,
    0x24B6,
    0x24B7,
    0x24BA,
    0x24BD,
    0x24C1,
    0x24D4,
    0x24D8,
    0x24E1,
// spring
    0x240E,
    0x2454,
    0x245B,
    0x2473,
    0x247D,
    0x2486,
    0x24C7,
    0x24EC,
    0x24FC,
    0x24FE,
// summer
    0x243A,
    0x244C,
    0x244E,
    0x2466,
    0x247C,
    0x2481,
    0x248A,
    0x2497,
    0x24B5,
    0x24F2,
    0x24F5,
// fall
    0x2402,
    0x242F,
    0x2457,
    0x2463,
    0x2483,
    0x2496,
    0x24A0,
    0x24C4,
    0x24D9,
// winter
    0x241C,
    0x2451,
    0x246C,
    0x248E,
    0x2499,
    0x24A3,
    0x24E6,
    0x24EA,
    0x24F4,

    EMPTY_NO,
};

mActor_name_t cloth_listC[] = {
// any season
    0x2401,
    0x2405,
    0x240F,
    0x242D,
    0x2439,
    0x243C,
    0x243F,
    0x2442,
    0x2445,
    0x2448,
    0x244B,
    0x244F,
    0x2452,
    0x2456,
    0x2458,
    0x245D,
    0x2460,
    0x246A,
    0x2472,
    0x2476,
    0x2484,
    0x248C,
    0x249A,
    0x249F,
    0x24A4,
    0x24AC,
    0x24AF,
    0x24B2,
    0x24D0,
    0x24D5,
    0x24DA,
    0x24E2,
// spring
    0x2409,
    0x241E,
    0x2467,
    0x2477,
    0x247E,
    0x24A6,
    0x24C0,
    0x24C8,
    0x24CE,
    0x24EF,
// summer
    0x2407,
    0x2427,
    0x2429,
    0x2459,
    0x248B,
    0x2492,
    0x24BE,
    0x24CA,
    0x24D1,
    0x24EE,
    0x24FB,
// fall
    0x240A,
    0x245A,
    0x246E,
    0x2487,
    0x2493,
    0x2495,
    0x24A1,
    0x24CF,
    0x24EB,
// winter
    0x2428,
    0x246D,
    0x248F,
    0x249B,
    0x24C6,
    0x24E4,
    0x24E7,
    0x24ED,
    0x24F9,

    EMPTY_NO,
};

mActor_name_t cloth_listEvent[] = {
    0x241F,
    0x2420,
    0x2421,
    0x2422,
    0x2423,
    0x2424,
    0x242C,
    0x242E,
    0x2432,
    0x2434,
    0x2436,
    0x245C,
    0x245F,
    0x2489,
    0x24B8,
    0x24BB,
    0x24BC,
    0x24CC,
    0x24DB,
    0x24DD,
    0x24DE,
    0x24DF,
    0x24E0,
    0x24F0,
    0x24F3,
    0x24F7,
    0x24F8,
    0x24FA,
    0x24FD,
    EMPTY_NO,
};

mActor_name_t cloth_listChristmas[] = {
    ITM_CLOTH037,
    EMPTY_NO,
};

mActor_name_t* mSP_cloth_list[mSP_LIST_NUM] = {
    cloth_listA,
    cloth_listB,
    cloth_listC,
    cloth_listEvent,
    NULL,
    NULL,
    NULL,
    NULL,
    cloth_listChristmas,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

u8 cloth_season_cnt[] = { 32, 10, 11, 9, 9 };
