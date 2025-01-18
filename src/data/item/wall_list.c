#include "m_name_table.h"
#include "m_shop.h"

mActor_name_t wall_listA[] = {
    0x2700,
    0x2703,
    0x2707,
    0x270B,
    0x270C,
    0x2714,
    0x2717,
    0x271A,
    0x271D,
    0x2720,
    0x2723,
    0x2726,
    0x2729,
    0x2732,
    0x2737,
    EMPTY_NO,
};

mActor_name_t wall_listB[] = {
    0x2701,
    0x2704,
    0x2708,
    0x270D,
    0x2715,
    0x2718,
    0x2721,
    0x2724,
    0x2727,
    0x272A,
    0x2733,
    0x273B,
    0x273D,
    0x273F,
    EMPTY_NO,
};

mActor_name_t wall_listC[] = {
    0x2702,
    0x2705,
    0x270A,
    0x2713,
    0x2716,
    0x271C,
    0x271E,
    0x271F,
    0x2722,
    0x2725,
    0x2728,
    0x272D,
    0x2736,
    0x273A,
    0x273E,
    EMPTY_NO,
};

mActor_name_t wall_listEvent[] = {
    0x2706,
    0x2709,
    0x270E,
    0x270F,
    0x2710,
    0x2712,
    0x271B,
    0x272B,
    0x272C,
    0x272E,
    0x2730,
    0x2731,
    0x2734,
    0x2735,
    0x2738,
    0x2739,
    0x273C,
    0x2741,
    EMPTY_NO,
};

mActor_name_t wall_listChristmas[] = {
    ITM_WALL47,
    EMPTY_NO,
};

mActor_name_t wall_listSnow[] = {
    ITM_WALL25,
    EMPTY_NO,
};

mActor_name_t wall_listHalloween[] = {
    ITM_WALL17,
    EMPTY_NO,
};

mActor_name_t wall_listHalloween2[] = {
    EMPTY_NO,
};

mActor_name_t wall_listHomePage[] = {
    ITM_WALL64,
    EMPTY_NO,
};

mActor_name_t wall_listHarvest[] = {
    ITM_WALL66,
    EMPTY_NO,
};

mActor_name_t* mSP_wall_list[mSP_LIST_NUM] = {
    wall_listA,
    wall_listB,
    wall_listC,
    wall_listEvent,
    NULL,
    NULL,
    wall_listHalloween,
    NULL,
    wall_listChristmas,
    wall_listSnow,
    wall_listHalloween2,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    wall_listHomePage,
    NULL,
    NULL,
    NULL,
    wall_listHarvest,
    NULL,
    NULL,
};
