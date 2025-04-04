#include "m_field_make.h"
#include "m_random_field_h.h"
#include "m_name_table.h"

mFM_move_actor_data_c fd1_actable[11] = {
    {ETC_AIRPLANE, 1, 0, 8, 14, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_MBG, 1, 2, 6, 9, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_MBG, 1, 2, 4, 10, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_MBG, 1, 2, 6, 11, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_MBG, 1, 2, 9, 6, -1, -1, mRF_BLOCKKIND_NONE},
    {NPC_CURLY, 0, 2, 7, 7, 10, -1, mRF_BLOCKKIND_NONE},
    {NPC_BETTY, 0, 2, 9, 7, 11, -1, mRF_BLOCKKIND_NONE},
    {NPC_SAMSON, 1, 1, 2, 5, 12, -1, mRF_BLOCKKIND_NONE},
    {NPC_LOBO, 1, 1, 3, 5, 13, -1, mRF_BLOCKKIND_NONE},
    {NPC_FREYA, 1, 1, 4, 5, 14, -1, mRF_BLOCKKIND_NONE},
    {RSV_NO, 0, 0, 0, 0, 0, 0, mRF_BLOCKKIND_NONE}
};
