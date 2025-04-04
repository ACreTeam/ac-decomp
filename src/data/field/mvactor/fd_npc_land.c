#include "m_field_make.h"
#include "m_random_field_h.h"
#include "m_name_table.h"

mFM_move_actor_data_c fd_npc_land_actable[4] = {
    {SP_NPC_POLICE, 0, 0, 8, 11, -1, -1, mRF_BLOCKKIND_POLICE},
    {SP_NPC_STATION_MASTER, 0, 0, 5, 4, -1, -1, mRF_BLOCKKIND_STATION},
    {SP_NPC_SONCHO, 0, 0, 10, 10, -1, -1, mRF_BLOCKKIND_SHRINE},
    {RSV_NO, 0, 0, 0, 0, 0, 0, mRF_BLOCKKIND_NONE}
};
