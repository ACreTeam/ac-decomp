#include "m_field_make.h"
#include "m_random_field_h.h"
#include "m_name_table.h"

mFM_move_actor_data_c broker_shop_actable[3] = {
    {ETC_SHOP_GOODS, 0, 0, 1, 1, -1, 0, mRF_BLOCKKIND_NONE},
    {SP_NPC_EV_BROKER2, 0, 0, 4, 4, -1, -1, mRF_BLOCKKIND_NONE},
    {RSV_NO, 0, 0, 0, 0, 0, 0, mRF_BLOCKKIND_NONE}
};
