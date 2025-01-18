#include "m_name_table.h"
#include "m_shop.h"

mActor_name_t carpet_listA[] = {
    0x2601,
    0x2602,
    0x2608,
    0x260A,
    0x2615,
    0x2616,
    0x261F,
    0x2621,
    0x2625,
    0x2627,
    0x262D,
    0x2633,
    0x263A,
    0x263B,
    0x263D,
    EMPTY_NO,
};

mActor_name_t carpet_listB[] = {
    0x2600,
    0x2605,
    0x2607,
    0x260C,
    0x2613,
    0x2617,
    0x261C,
    0x261D,
    0x2622,
    0x2623,
    0x2628,
    0x2629,
    0x2636,
    0x2637,
    0x263E,
    EMPTY_NO,
};

mActor_name_t carpet_listC[] = {
    0x2603,
    0x2604,
    0x260B,
    0x260D,
    0x2614,
    0x2618,
    0x261A,
    0x261E,
    0x2620,
    0x2624,
    0x2626,
    0x262A,
    0x2632,
    0x263F,
    EMPTY_NO,
};

mActor_name_t carpet_listEvent[] = {
    0x2606,
    0x2609,
    0x260E,
    0x260F,
    0x2610,
    0x2612,
    0x261B,
    0x262B,
    0x262C,
    0x262E,
    0x2630,
    0x2631,
    0x2634,
    0x2635,
    0x2638,
    0x2639,
    0x263C,
    0x2641,
    EMPTY_NO,
};

mActor_name_t carpet_listChristmas[] = {
    ITM_CARPET47,
    EMPTY_NO,
};

mActor_name_t carpet_listSnow[] = {
    ITM_CARPET25,
    EMPTY_NO,
};

mActor_name_t carpet_listHalloween[] = {
    ITM_CARPET17,
    EMPTY_NO,
};

mActor_name_t carpet_listHalloween2[] = {
    EMPTY_NO,
};

mActor_name_t carpet_listHomePage[] = {
    ITM_CARPET64,
    EMPTY_NO,
};

mActor_name_t carpet_listHarvest[] = {
    ITM_CARPET66,
    EMPTY_NO,
};

mActor_name_t* mSP_carpet_list[mSP_LIST_NUM] = {
    carpet_listA,
    carpet_listB,
    carpet_listC,
    carpet_listEvent,
    NULL,
    NULL,
    carpet_listHalloween,
    NULL,
    carpet_listChristmas,
    carpet_listSnow,
    carpet_listHalloween2,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    carpet_listHomePage,
    NULL,
    NULL,
    NULL,
    carpet_listHarvest,
    NULL,
    NULL,
};
