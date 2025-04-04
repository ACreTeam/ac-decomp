#include "m_field_make.h"
#include "m_random_field_h.h"
#include "m_name_table.h"

mFM_move_actor_data_c fd2_actable[8] = {
    {ETC_AIRPLANE, 1, 0, 8, 14, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_SNOWMAN_BALL_A, 3, 1, 10, 1, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_SNOWMAN_BALL_B, 3, 1, 9, 1, -1, -1, mRF_BLOCKKIND_NONE},
    {ETC_SNOWMAN_BALL_A, 0, 4, 5, 12, -1, -1, mRF_BLOCKKIND_NONE},
    {SP_NPC_POLICE, 0, 2, 6, 6, -1, -1, mRF_BLOCKKIND_NONE},
    {MISC_ACTOR_SAMPLE, 0, 2, 10, 10, -1, -1, mRF_BLOCKKIND_NONE},
    {NPC_ELMER, 1, 3, 3, 3, 11, 10, mRF_BLOCKKIND_NONE},
    {RSV_NO, 0, 0, 0, 0, 0, 0, mRF_BLOCKKIND_NONE}
};
