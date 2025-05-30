#include "m_name_table.h"
#include "m_shop.h"

mActor_name_t binsen_listA[] = {
    0x20C0,
    0x20C3,
    0x20C7,
    0x20CA,
    0x20CD,
    0x20D1,
    0x20D4,
    0x20D7,
    0x20DB,
    0x20E0,
    0x20E1,
    0x20E4,
    0x20E8,
    0x20EB,
    0x20EE,
    0x20F1,
    0x20F4,
    0x20F7,
    0x20FA,
    0x20FD,
    EMPTY_NO,
};

mActor_name_t binsen_listB[] = {
    0x20C1,
    0x20C4,
    0x20C8,
    0x20CB,
    0x20CE,
    0x20D0,
    0x20D2,
    0x20D5,
    0x20D8,
    0x20DC,
    0x20DE,
    0x20E2,
    0x20E6,
    0x20E9,
    0x20EC,
    0x20EF,
    0x20F2,
    0x20F5,
    0x20F8,
    0x20FB,
    EMPTY_NO,
};

mActor_name_t binsen_listC[] = {
    0x20C2,
    0x20C5,
    0x20C6,
    0x20C9,
    0x20CC,
    0x20CF,
    0x20D3,
    0x20DA,
    0x20DD,
    0x20DF,
    0x20E3,
    0x20E5,
    0x20E7,
    0x20EA,
    0x20ED,
    0x20F0,
    0x20F6,
    0x20F9,
    0x20FC,
    0x20FF,
    EMPTY_NO,
};

mActor_name_t binsen_listTrain[] = {
    EMPTY_NO,
};

mActor_name_t* mSP_binsen_list[mSP_LIST_NUM] = {
    binsen_listA,
    binsen_listB,
    binsen_listC,
    NULL,
    binsen_listTrain,
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
    NULL,
    NULL,
    NULL,
    NULL,
};
