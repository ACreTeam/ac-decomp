#include "m_room_type.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "ac_my_room.h"
#include "m_melody.h"
#include "padmgr.h"
#include "game.h"
#include "m_house.h"
#include "dolphin/os/OSCache.h"
#include "jsyswrap.h"
#include "m_player_lib.h"

typedef struct ftr_place_data_s {
    u8 exist;
    s16 ofs_x;
    s16 ofs_z;
} mRmTp_FtrPlaceData_c;

/*
  x-
  --
*/
static mRmTp_FtrPlaceData_c mRmTp_size_s_data[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

/*
  x*
  --
*/
static mRmTp_FtrPlaceData_c mRmTp_size_m_data_south[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 1, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

/*
  -*
  -x
*/
static mRmTp_FtrPlaceData_c mRmTp_size_m_data_east[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 0, -1 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

/*
  --
  *x
*/
static mRmTp_FtrPlaceData_c mRmTp_size_m_data_north[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, -1, 0 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

/*
  x-
  *-
*/
static mRmTp_FtrPlaceData_c mRmTp_size_m_data_west[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 0, 1 }, { FALSE, 0, 0 }, { FALSE, 0, 0 }
};

static mRmTp_FtrPlaceData_c* mRmTp_size_m_data_table[mRmTp_DIRECT_NUM] = {
    mRmTp_size_m_data_south, mRmTp_size_m_data_east, mRmTp_size_m_data_north, mRmTp_size_m_data_west
};

/*
  x*
  **
*/
static mRmTp_FtrPlaceData_c mRmTp_size_l_data[mRmTp_FTR_UNIT_MAX] = {
    { TRUE, 0, 0 }, { TRUE, 1, 0 }, { TRUE, 1, 1 }, { TRUE, 0, 1 }
};

static u8 mRmTp_ftr_se_type[FTR_NUM] = {
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_TOILET_CHAIR,
    mRmTp_FTR_SE_TOILET_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_SOFT_CHAIR,   mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_BUBU_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_BUBU_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_HARD_CHAIR,   mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_SOFT_CHAIR,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_HARD_CHAIR, mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,       mRmTp_FTR_SE_NONE,
    mRmTp_FTR_SE_NONE,         mRmTp_FTR_SE_NONE
};

static void mRmTp_InitFtrPlaceInfo(mRmTp_FtrPlaceInfoOne_t* ftr_place_info) {
    int i;

    for (i = 0; i < mRmTp_FTR_UNIT_MAX; i++) {
        ftr_place_info->exists = FALSE;
        ftr_place_info->ut_x = 0;
        ftr_place_info->ut_z = 0;

        ftr_place_info++;
    }
}

extern int mRmTp_ItemNo2FtrSize(mActor_name_t item_no) {
    int unit = aMR_GetFurnitureUnit(item_no);

    if (unit == -1) {
        return mRmTp_FTRSIZE_1x1;
    }

    return unit;
}

static mRmTp_FtrPlaceData_c* mRmTp_GetFtrUnitPlaceData(int size, int direct) {
    switch (size) {
        case mRmTp_FTRSIZE_1x1:
            return mRmTp_size_s_data;
        case mRmTp_FTRSIZE_1x2:
            return mRmTp_size_m_data_table[direct];
        case mRmTp_FTRSIZE_2x2:
            return mRmTp_size_l_data;
        default:
            return mRmTp_size_s_data;
    }
}

extern int mRmTp_GetFurnitureData(mActor_name_t ftr, int ut_x, int ut_z, mRmTp_FtrPlaceInfoOne_t* place_info) {
    mRmTp_InitFtrPlaceInfo(place_info);

    if (ITEM_IS_FTR(ftr)) {
        int ftr_idx = mRmTp_FtrItemNo2FtrIdx(ftr);
        mRmTp_FtrPlaceData_c* unit_data = mRmTp_GetFtrUnitPlaceData(aMR_GetFurnitureUnit(ftr), FTR_GET_ROTATION(ftr));
        int i;

        for (i = 0; i < mRmTp_FTR_UNIT_MAX; i++) {
            place_info[i].exists = unit_data[i].exist;
            place_info[i].ut_x = ut_x + unit_data[i].ofs_x;
            place_info[i].ut_z = ut_z + unit_data[i].ofs_z;
        }

        return aMR_GetFurnitureUnit(ftr);
    }

    return mRmTp_FTRSIZE_NUM;
}

extern void mRmTp_MakeFtrNoTable(mActor_name_t* dst, mActor_name_t* src) {
    int i;
    int j;
    int k;

    for (k = 0; k < UT_TOTAL_NUM; k++) {
        dst[k] = EMPTY_NO;
    }

    for (i = 0; i < UT_Z_NUM; i++) {
        for (j = 0; j < UT_X_NUM; j++) {
            mRmTp_FtrPlaceInfoOne_t place_data[mRmTp_FTR_UNIT_MAX];
            mActor_name_t item = src[i * UT_X_NUM + j];

            if (ITEM_IS_FTR(item) && mRmTp_GetFurnitureData(item, j, i, place_data) != mRmTp_FTRSIZE_NUM) {
                mRmTp_FtrPlaceInfoOne_t* data_p = place_data;
                for (k = 0; k < mRmTp_FTR_UNIT_MAX; k++) {
                    if (data_p->exists) {
                        dst[data_p->ut_z * UT_X_NUM + data_p->ut_x] = item;
                    }

                    data_p++;
                }
            }
        }
    }
}

extern int mRmTp_GetFtrActionSE(int ftr_idx, int mode) {
    static int soft_chair_se_table[mRmTp_CHAIR_ACTION_NUM] = { 0x41F, 0x422 };
    static int hard_chair_se_table[mRmTp_CHAIR_ACTION_NUM] = { 0x420, 0x423 };
    static int bubu_chair_se_table[mRmTp_CHAIR_ACTION_NUM] = { 0x421, 0x429 };
    static int toile_chair_se_table[mRmTp_CHAIR_ACTION_NUM] = { 0x410, 0x072 };

    if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
        switch (mRmTp_ftr_se_type[ftr_idx]) {
            case mRmTp_FTR_SE_NONE:
                return -1;
            case mRmTp_FTR_SE_SOFT_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_NUM) {
                    return soft_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_HARD_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_NUM) {
                    return hard_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_BUBU_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_NUM) {
                    return bubu_chair_se_table[mode];
                }

                return -1;
            case mRmTp_FTR_SE_TOILET_CHAIR:
                if (mode >= mRmTp_CHAIR_ACTION_SIT && mode < mRmTp_CHAIR_ACTION_NUM) {
                    return toile_chair_se_table[mode];
                }

                return -1;
            default:
                return -1;
        }
    }

    return -1;
}

static u8 mRmTp_birth_type[FTR_NUM] = {
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_BIRTHDAY,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_HALLOWEEN_TRICK,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN_TRICK,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HALLOWEEN,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_HANIWA,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_FTR_CLOTH,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_INSECT,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_FISH,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_FTR_UMBRELLA,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_MY_ORIGINAL,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_FAMICOM_CODE,
    mRmTp_BIRTH_TYPE_FAMICOM_ISLAND,
    mRmTp_BIRTH_TYPE_FAMICOM_CODE,
    mRmTp_BIRTH_TYPE_FAMICOM_CODE,
    mRmTp_BIRTH_TYPE_FAMICOM_CODE,
    mRmTp_BIRTH_TYPE_FAMICOM_CODE,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_FAMICOM_ISLAND,
    mRmTp_BIRTH_TYPE_FAMICOM_EREADER,
    mRmTp_BIRTH_TYPE_FAMICOM_EREADER,
    mRmTp_BIRTH_TYPE_FAMICOM_EREADER,
    mRmTp_BIRTH_TYPE_FAMICOM_EREADER,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_SANTA,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_MULTI_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_SINGLE_FOSSIL,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_SNOWMAN,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_SONCHO_LIGHTHOUSE_QUEST,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_POST_OFFICE,
    mRmTp_BIRTH_TYPE_POST_OFFICE,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_POST_OFFICE,
    mRmTp_BIRTH_TYPE_MARK_ROOM,
    mRmTp_BIRTH_TYPE_MARK_ROOM,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_MUSEUM,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_JONASON,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO_LIGHTHOUSE_QUEST,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_FTR_DIARY,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_ISLAND,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_POST_OFFICE,
    mRmTp_BIRTH_TYPE_XMAS,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_HARVEST_FESTIVAL,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_NINTENDO_CODE,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_LOTTERY,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_A,
    mRmTp_BIRTH_TYPE_GRP_B,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_GRP_C,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_GROUNDHOG,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SUMMER_CAMPER,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_EVENT,
    mRmTp_BIRTH_TYPE_SONCHO,
    mRmTp_BIRTH_TYPE_KAMAKURA,
    mRmTp_BIRTH_TYPE_UNOBTAINABLE,
};

extern u8* mRmTp_CheckFtrBirthInfoTop() {
    return mRmTp_birth_type;
}

static void mRmTp_PrintFloorIndex(const char* name) {
    // STUBBED (probably only emitted for debug builds)
}

extern int mRmTp_GetFloorIdx() {
    int scene_no = Save_Get(scene_no);

    if (mSc_IS_SCENE_BASEMENT(scene_no)) {
        mRmTp_PrintFloorIndex("FLOOR_BASEMENT");
        return FLOOR_BASEMENT;
    } else if (Save_Get(scene_no) == SCENE_MY_ROOM_S || Save_Get(scene_no) == SCENE_MY_ROOM_M ||
               Save_Get(scene_no) == SCENE_MY_ROOM_L || Save_Get(scene_no) == SCENE_MY_ROOM_LL1 ||
               Save_Get(scene_no) == SCENE_MY_ROOM_LL2) {
        mActor_name_t field_id = mFI_GetFieldId();
        int floor_no = mFI_GetNowPlayerHouseFloorNo();
        int idx = field_id - mFI_FIELD_PLAYER0_ROOM;
        int floor;

        if (floor_no == -1) {
            return 0;
        }

        floor = Save_Get(homes[idx]).floors[floor_no].wall_floor.flooring_idx;

        if (floor >= 0 && floor < FLOOR_ETC_END) {
            return floor;
        }

        if (FLOOR_IS_MY_ORIG(floor)) {
            mRmTp_PrintFloorIndex("FLOOR_ORIGINAL_SE");
            return FLOOR_ORIGINAL_SE;
        }

        return 0;
    } else if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        return Save_Get(island).cottage.room.wall_floor.flooring_idx;
    } else {
        switch (Save_Get(scene_no)) {
            case SCENE_NPC_HOUSE:
            case SCENE_COTTAGE_NPC:
                return mNpc_GetNpcFloorNo();
            case SCENE_SHOP0:
                mRmTp_PrintFloorIndex("FLOOR_SHOP1");
                return FLOOR_SHOP1;
            case SCENE_CONVENI:
                mRmTp_PrintFloorIndex("FLOOR_SHOP2");
                return FLOOR_SHOP2;
            case SCENE_SUPER:
                mRmTp_PrintFloorIndex("FLOOR_SHOP3");
                return FLOOR_SHOP3;
            case SCENE_DEPART:
            case SCENE_DEPART_2:
                mRmTp_PrintFloorIndex("FLOOR_SHOP4_2");
                return FLOOR_SHOP4_2;
            case SCENE_POST_OFFICE:
                mRmTp_PrintFloorIndex("FLOOR_POST_OFFICE");
                return FLOOR_POST_OFFICE;
            case SCENE_POLICE_BOX:
                mRmTp_PrintFloorIndex("FLOOR_POLICE_BOX");
                return FLOOR_POLICE_BOX;
            case SCENE_BUGGY:
                mRmTp_PrintFloorIndex("FLOOR_BUGGY");
                return FLOOR_BUGGY;
            case SCENE_BROKER_SHOP:
                mRmTp_PrintFloorIndex("FLOOR_BROKER_SHOP");
                return FLOOR_BROKER_SHOP;
            case SCENE_KAMAKURA:
                mRmTp_PrintFloorIndex("FLOOR_KAMAKURA");
                return FLOOR_KAMAKURA;
            case SCENE_MUSEUM_ENTRANCE:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_ENTRANCE");
                return FLOOR_MUSEUM_ENTRANCE;
            case SCENE_MUSEUM_ROOM_FOSSIL:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_FOSSIL");
                return FLOOR_MUSEUM_FOSSIL;
            case SCENE_MUSEUM_ROOM_PAINTING:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_PICTURE");
                return FLOOR_MUSEUM_PICTURE;
            case SCENE_MUSEUM_ROOM_INSECT:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_INSECT");
                return FLOOR_MUSEUM_INSECT;
            case SCENE_MUSEUM_ROOM_FISH:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_FISH");
                return FLOOR_MUSEUM_FISH;
            case SCENE_NEEDLEWORK:
                mRmTp_PrintFloorIndex("FLOOR_MUSEUM_NEEDLEWORK"); // ??? Why MUSEUM_NEEDLEWORK?
                return FLOOR_MUSEUM_NEEDLEWORK;
            case SCENE_LIGHTHOUSE:
                mRmTp_PrintFloorIndex("FLOOR_LIGHTHOUSE_SE");
                return FLOOR_LIGHTHOUSE_SE;
            case SCENE_TENT:
                mRmTp_PrintFloorIndex("FLOOR_TENT_SE");
                return FLOOR_TENT_SE;
            default:
                return -1;
        }
    }
}

extern int mRmTp_GetWallIdx() {
    int scene_no = Save_Get(scene_no);

    if (scene_no == SCENE_MY_ROOM_S || scene_no == SCENE_MY_ROOM_M || scene_no == SCENE_MY_ROOM_L ||
        scene_no == SCENE_MY_ROOM_LL1 || scene_no == SCENE_MY_ROOM_LL2) {
        mActor_name_t field_id = mFI_GetFieldId();
        int floor_no = mFI_GetNowPlayerHouseFloorNo();
        int idx = field_id - mFI_FIELD_PLAYER0_ROOM;

        if (floor_no == -1) {
            return -1;
        }

        return Save_Get(homes[idx]).floors[floor_no].wall_floor.wallpaper_idx;
    } else if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        return Save_Get(island).cottage.room.wall_floor.wallpaper_idx;
    } else if (Save_Get(scene_no) == SCENE_NPC_HOUSE || Save_Get(scene_no) == SCENE_COTTAGE_NPC) {
        return mNpc_GetNpcWallNo();
    } else {
        return -1;
    }
}

extern mActor_name_t mRmTp_Item1ItemNo2FtrItemNo_AtPlayerRoom(mActor_name_t item1_no, int no_convert_tools) {
    if (item1_no >= ITM_CLOTH_START && item1_no < ITM_CLOTH_END) {
        int is_valid = item1_no >= ITM_CLOTH_START && item1_no < ITM_CLOTH_END; // this is some kind of macro for sure

        return FTR_CLOTH_START + ((is_valid ? item1_no - ITM_CLOTH_START : 0) & 0x3FFF) * mRmTp_DIRECT_NUM;
    } else if (item1_no >= ITM_INSECT_START && item1_no < ITM_INSECT_END) {
        int is_valid = item1_no >= ITM_INSECT_START && item1_no < ITM_INSECT_END;

        return FTR_INSECT_START + (is_valid ? item1_no - ITM_INSECT_START : 0) * mRmTp_DIRECT_NUM;
    } else if (item1_no >= ITM_FISH_START && item1_no <= ITM_FISH_END) {
        int is_valid = item1_no >= ITM_FISH_START && item1_no <= ITM_FISH_END;

        return FTR_FISH_START + ((is_valid ? item1_no - ITM_FISH_START : 0) & 0x3FFF) * mRmTp_DIRECT_NUM;
    } else if (item1_no >= ITM_UMBRELLA_START && item1_no <= ITM_MY_ORG_UMBRELLA7) {
        int is_valid = item1_no >= ITM_UMBRELLA_START && item1_no <= ITM_MY_ORG_UMBRELLA7;

        return FTR_UMBRELLA_START + (is_valid ? item1_no - ITM_UMBRELLA_START : 0) * mRmTp_DIRECT_NUM;
    } else if (item1_no >= ITM_BALLOON_START && item1_no <= ITM_BUNNY_O_BALLOON) {
        return mRmTp_FtrIdx2FtrItemNo(FTR_NOG_BALLOON_COMMON0 + ((item1_no - ITM_BALLOON_START) & 7),
                                      mRmTp_DIRECT_SOUTH);
    }

    if (no_convert_tools == FALSE) {
        if (item1_no >= ITM_DIARY_START && item1_no <= ITM_DIARY15) {
            return FTR_START(FTR_NOG_COLLEGENOTE) + ((item1_no - ITM_DIARY_START) & 15) * mRmTp_DIRECT_NUM;
        } else if (item1_no >= ITM_BLUEBELL_FAN && item1_no <= ITM_LEAF_FAN) {
            return mRmTp_FtrIdx2FtrItemNo(FTR_UTIWA0 + ((item1_no - ITM_BLUEBELL_FAN) & 7), mRmTp_DIRECT_SOUTH);
        } else if (item1_no >= ITM_YELLOW_PINWHEEL && item1_no <= ITM_FANCY_PINWHEEL) {
            return mRmTp_FtrIdx2FtrItemNo(FTR_KAZAGURUMA0 + ((item1_no - ITM_YELLOW_PINWHEEL) & 7), mRmTp_DIRECT_SOUTH);
        } else if (item1_no >= ITM_GOLDEN_NET && item1_no <= ITM_GOLDEN_ROD) {
            return mRmTp_FtrIdx2FtrItemNo(FTR_GOLD_ITEM0 + ((item1_no - ITM_GOLDEN_NET) & 3), mRmTp_DIRECT_SOUTH);
        } else if (item1_no >= ITM_NET && item1_no <= ITM_ROD) {
            return mRmTp_FtrIdx2FtrItemNo(FTR_TOOL0 + ((item1_no - ITM_NET) & 3), mRmTp_DIRECT_SOUTH);
        } else if (item1_no >= ITM_AXE_USE_1 && item1_no <= ITM_AXE_USE_7) {
            return FTR_START(FTR_TOOL1);
        }
    }

    return item1_no;
}

extern mActor_name_t mRmTp_FtrItemNo2Item1ItemNo(mActor_name_t ftr_no, int no_convert_tools) {
    int ftr_idx;

    if (ftr_no >= FTR_CLOTH_START && ftr_no <= FTR_CLOTH_END) {
        int is_valid = ftr_no >= FTR_CLOTH_START && ftr_no <= FTR_CLOTH_END; // this is some kind of macro for sure

        return ITM_CLOTH_START + (mActor_name_t)(is_valid ? (ftr_no - FTR_CLOTH_START) >> 2 : 0);
    } else if (ftr_no >= FTR_INSECT_START && ftr_no <= FTR_INSECT_END) {
        int is_valid = ftr_no >= FTR_INSECT_START && ftr_no <= FTR_INSECT_END;

        return ITM_INSECT_START + (is_valid ? (ftr_no - FTR_INSECT_START) >> 2 : 0);
    } else if (ftr_no >= FTR_FISH_START && ftr_no <= FTR_FISH_END) {
        int is_valid = ftr_no >= FTR_FISH_START && ftr_no <= FTR_FISH_END;

        return mNT_FishIdx2FishItemNo(is_valid ? (ftr_no - FTR_FISH_START) >> 2 : 0);
    } else if (ftr_no >= FTR_UMBRELLA_START && ftr_no <= FTR_UMBRELLA_END) {
        return ITM_UMBRELLA_START + ((ftr_no - FTR_UMBRELLA_START) >> 2);
    } else if (mRmTp_FtrItemNo2FtrIdx(ftr_no) >= FTR_NOG_BALLOON_COMMON0 && mRmTp_FtrItemNo2FtrIdx(ftr_no) <= 0x403) {
        return ITM_BALLOON_START + ((mRmTp_FtrItemNo2FtrIdx(ftr_no) - FTR_NOG_BALLOON_COMMON0) & 7);
    } else if (ftr_no >= FTR_START(FTR_NOG_COLLEGENOTE) && ftr_no <= FTR_END(FTR_IKE_NIKKI_WAFU1)) {
        return ITM_DIARY_START + (((ftr_no - FTR_START(FTR_NOG_COLLEGENOTE)) >> 2) & 15);
    } else if (mRmTp_FtrItemNo2FtrIdx(ftr_no) >= FTR_UTIWA0 && mRmTp_FtrItemNo2FtrIdx(ftr_no) <= 0x45A) {
        return ITM_BLUEBELL_FAN + ((mRmTp_FtrItemNo2FtrIdx(ftr_no) - FTR_UTIWA0) & 7);
    } else if (mRmTp_FtrItemNo2FtrIdx(ftr_no) >= FTR_KAZAGURUMA0 && mRmTp_FtrItemNo2FtrIdx(ftr_no) <= 0x462) {
        return ITM_YELLOW_PINWHEEL + ((mRmTp_FtrItemNo2FtrIdx(ftr_no) - FTR_KAZAGURUMA0) & 7);
    } else if (mRmTp_FtrItemNo2FtrIdx(ftr_no) >= FTR_GOLD_ITEM0 && mRmTp_FtrItemNo2FtrIdx(ftr_no) <= 0x452) {
        return ITM_GOLDEN_NET + ((mRmTp_FtrItemNo2FtrIdx(ftr_no) - FTR_GOLD_ITEM0) & 3);
    } else if (mRmTp_FtrItemNo2FtrIdx(ftr_no) >= FTR_TOOL0 && mRmTp_FtrItemNo2FtrIdx(ftr_no) <= 0x466) {
        return ITM_NET + ((mRmTp_FtrItemNo2FtrIdx(ftr_no) - FTR_TOOL0) & 3);
    }

    return ftr_no;
}

static u8 mRmTp_melody[16];

extern void mRmTp_MakeMelodyData() {
    mMld_TransformMelodyData_u64_2_u8(mRmTp_melody, Save_Get(melody));
}

extern u8* mRmTp_GetMelodyData() {
    return mRmTp_melody;
}

static int mRmTp_famicom_idx = 0;

extern void mRmTp_DrawFamicomInfo(gfxprint_t* gfxprint) {
    if ((gamePT->pads[PAD1].on.button & BUTTON_START) == BUTTON_START) {
        mRmTp_famicom_idx++;
    }

    if (mRmTp_famicom_idx < 0) {
        mRmTp_famicom_idx = 20;
    }

    if (mRmTp_famicom_idx >= 21) {
        mRmTp_famicom_idx = 0;
    }

    gfxprint_color(gfxprint, 200, 200, 250, 255);
    gfxprint_locate8x8(gfxprint, 3, 26);
    gfxprint_printf(gfxprint, "ﾌｧﾐｺﾝ %d", mRmTp_famicom_idx); // "Famicom %d"
}

extern void mRmTp_MakeFamicom_Fdebug() {
    u16 ftr_idx;
    int res;
    Clip_c* clip;
    GAME* game = gamePT;

    if ((gamePT->pads[PAD1].on.button & BUTTON_Z) == BUTTON_Z && game != NULL) {
        clip = Common_GetPointer(clip);

        if (clip->my_room_clip != NULL) {
            int ut_x;
            int ut_z;
            u16 direct;
            int ofs;
            int layer;

            ftr_idx = 0x3EF;
            if (mRmTp_famicom_idx != 20) {
                ftr_idx = 0x36A + mRmTp_famicom_idx;
            }

            res = (*clip->my_room_clip->judge_breed_new_ftr_proc)(game, ftr_idx, &ut_x, &ut_z, &direct, &ofs, &layer);

            if (res >= 0) {
                (*clip->my_room_clip->reserve_ftr_proc)(game, ftr_idx, res, ut_x, ut_z, direct, ofs, layer);
            }
        }
    }
}

extern mActor_name_t mRmTp_GetPlayerRoomCollisionIdx(mActor_name_t field_id, mActor_name_t bg_idx) {
    if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
        int has_basement = Save_Get(homes[(field_id - mFI_FIELD_PLAYER0_ROOM) & 3]).flags.has_basement;

        switch (Save_Get(scene_no)) {
            case SCENE_MY_ROOM_M:
                if (has_basement) {
                    return 0x11E;
                } else {
                    return 0x104;
                }
            case SCENE_MY_ROOM_L:
                if (has_basement) {
                    return 0x11F;
                } else {
                    return 0x0F2;
                }
            case SCENE_MY_ROOM_LL1:
                if (has_basement) {
                    return 0x120;
                } else {
                    return 0x11B;
                }
            case SCENE_MY_ROOM_LL2:
                return 0x11C;
            case SCENE_MY_ROOM_BASEMENT_S:
            case SCENE_MY_ROOM_BASEMENT_M:
            case SCENE_MY_ROOM_BASEMENT_L:
            case SCENE_MY_ROOM_BASEMENT_LL1:
                return 0x121;

            default:
                return bg_idx;
        }
    }

    return bg_idx;
}

extern int mRmTp_FurnitureIdx2FurnitureKind(int ftr_idx) {
    if (ftr_idx >= 0 && ftr_idx < FTR_NUM) {
        return mRmTp_birth_type[ftr_idx];
    }

    return mRmTp_BIRTH_TYPE_UNOBTAINABLE;
}

static int mRmTp_GetPlayerRoomIdx() {
    mActor_name_t field_id = mFI_GetFieldId();

    return mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM ? (field_id - mFI_FIELD_PLAYER0_ROOM) & 3 : 0;
}

extern void mRmTp_CopyWallData(u8* dst, int wall_no) {
    if (dst != NULL) {
        if (!WALL_IS_MY_ORIG(wall_no) && !(wall_no >= 0 && wall_no < WALL_ETC_END)) {
            wall_no = 0;
        }

        if (WALL_IS_MY_ORIG(wall_no)) {
            int valid = WALL_IS_MY_ORIG(wall_no);
            int tex_idx = valid ? (wall_no - WALL_MY_ORIG_START) & 7 : -1;
            int room_idx = mRmTp_GetPlayerRoomIdx();
            int valid2 = mHS_get_pl_no_detail(room_idx) >= 0 && mHS_get_pl_no_detail(room_idx) < PLAYER_NUM;
            int player_no = valid2 ? mHS_get_pl_no_detail(room_idx) : 0;
            mNW_original_design_c* original = &Save_Get(private_data[player_no]).my_org[tex_idx & 7];

            mNW_CopyOriginalPalette(dst, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE + 0x800, original);
            DCStoreRangeNoSync(dst, mNW_PALETTE_SIZE + 0x1000);
        } else if (wall_no >= 0 && wall_no < WALL_ETC_END) {
            u32 base_addr = JW_GetAramAddress(RESOURCE_PLAYER_ROOM_WALL);

            _JW_GetResourceAram(base_addr + wall_no * 0x1020, dst, 0x1020);
            DCStoreRangeNoSync(dst, mNW_PALETTE_SIZE + 0x1000);
        }
    }
}

extern void mRmTp_CopyFloorData(u8* dst, int floor_no) {
    if (dst != NULL) {
        if (!FLOOR_IS_MY_ORIG(floor_no) && !(floor_no >= 0 && floor_no < FLOOR_PLAYER_ROOM_END)) {
            floor_no = 0;
        }

        if (FLOOR_IS_MY_ORIG(floor_no)) {
            int valid = FLOOR_IS_MY_ORIG(floor_no);
            int tex_idx = valid ? (floor_no - FLOOR_MY_ORIG_START) & 7 : -1;
            int room_idx = mRmTp_GetPlayerRoomIdx();
            int valid2 = mHS_get_pl_no_detail(room_idx) >= 0 && mHS_get_pl_no_detail(room_idx) < PLAYER_NUM;
            int player_no = valid2 ? mHS_get_pl_no_detail(room_idx) : 0;
            mNW_original_design_c* original = &Save_Get(private_data[player_no]).my_org[tex_idx & 7];

            mNW_CopyOriginalPalette(dst, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE + 0x0800, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE + 0x1000, original);
            mNW_CopyOriginalTexture(dst + mNW_PALETTE_SIZE + 0x1800, original);
            DCStoreRangeNoSync(dst, mNW_PALETTE_SIZE + 0x2000);
        } else if (floor_no >= 0 && floor_no < FLOOR_PLAYER_ROOM_END) {
            u32 base_addr = JW_GetAramAddress(RESOURCE_PLAYER_ROOM_FLOOR);

            _JW_GetResourceAram(base_addr + floor_no * 0x2020, dst, 0x2020);
            DCStoreRangeNoSync(dst, mNW_PALETTE_SIZE + 0x2000);
        }
    }
}

extern int mRmTp_CheckTalkAble(s16* rot, xyz_t* pos, int required_dir, f32 max_dist, GAME_PLAY* play) {
    static int direct_table[16] = { mRmTp_DIRECT_NORTH, -1, -1, mRmTp_DIRECT_WEST,
                                    mRmTp_DIRECT_WEST,  -1, -1, mRmTp_DIRECT_SOUTH,
                                    mRmTp_DIRECT_SOUTH, -1, -1, mRmTp_DIRECT_EAST,
                                    mRmTp_DIRECT_EAST,  -1, -1, mRmTp_DIRECT_NORTH };

    PLAYER_ACTOR* player = get_player_actor_withoutCheck(play);
    u16 player_rot_y = player->actor_class.shape_info.rotation.y;

    rot[0] = 0;

    if ((required_dir & 3) == direct_table[player_rot_y / 0x1000]) {
        f32 dx = pos->x - player->actor_class.world.position.x;
        f32 dz = pos->z - player->actor_class.world.position.z;
        f32 dist = sqrtf(dx * dx + dz * dz);

        rot[0] = atans_table(dz, dx);

        if (dist < max_dist) {
            return TRUE;
        }

        return FALSE;
    }

    return FALSE;
}

extern int mRmTp_CheckWallIsMyOriginalInThisScene() {
    int room_idx = mRmTp_GetPlayerRoomIdx();
    int floor_no = mFI_GetNowPlayerHouseFloorNo();

    if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        int idx = Save_Get(island).cottage.room.wall_floor.wallpaper_idx;

        if (WALL_IS_MY_ORIG(idx)) {
            return TRUE;
        }
    } else if (floor_no != -1) {
        int idx = Save_Get(homes[room_idx]).floors[floor_no].wall_floor.wallpaper_idx;

        if (WALL_IS_MY_ORIG(idx)) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mRmTp_CheckFloorIsMyOriginalInThisScene() {
    int room_idx = mRmTp_GetPlayerRoomIdx();
    int floor_no = mFI_GetNowPlayerHouseFloorNo();

    if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        int idx = Save_Get(island).cottage.room.wall_floor.flooring_idx;

        if (FLOOR_IS_MY_ORIG(idx)) {
            return TRUE;
        }
    } else if (floor_no != -1) {
        int idx = Save_Get(homes[room_idx]).floors[floor_no].wall_floor.flooring_idx;

        if (FLOOR_IS_MY_ORIG(idx)) {
            return TRUE;
        }
    }

    return FALSE;
}

extern int mRmTp_GetEntranceBasePosition(xyz_t* pos) {
    if (Save_Get(scene_no) == SCENE_MUSEUM_ENTRANCE) {
        pos->x = 80.0f;
        pos->y = 40.0f;
        pos->z = 0.0f;

        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_GetNowSceneLightSwitchIndex() {
    int scene = Save_Get(scene_no);
    mActor_name_t field_id = mFI_GetFieldId();

    if (scene == SCENE_LIGHTHOUSE) {
        return mRmTp_LIGHT_SWITCH_LIGHTHOUSE;
    } else if (scene == SCENE_TENT) {
        return mRmTp_LIGHT_SWITCH_TENT;
    } else if (scene == SCENE_COTTAGE_MY) {
        return mRmTp_LIGHT_SWITCH_COTTAGE_MY;
    } else if (scene == SCENE_NPC_HOUSE || scene == SCENE_COTTAGE_NPC) {
        return mRmTp_LIGHT_SWITCH_NPC;
    } else if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
        int idx = ((field_id - mFI_FIELD_PLAYER0_ROOM) & 3);
        int base = mFI_GetNowPlayerHouseFloorNo() == 2 ? mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT
                                                       : mRmTp_LIGHT_SWITCH_HOUSE0_MAIN_UPPER;

        return base + idx * 2;
    }

    return -1;
}

extern int mRmTp_PleaseDrawLightSwitch() {
    static u8 z_bottun_data[mRmTp_LIGHT_SWITCH_NUM] = {
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE0_MAIN_UPPER
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE0_BASEMENT
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE1_MAIN_UPPER
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE1_BASEMENT
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE2_MAIN_UPPER
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE2_BASEMENT
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE3_MAIN_UPPER
        TRUE,  // mRmTp_LIGHT_SWITCH_HOUSE3_BASEMENT
        TRUE,  // mRmTp_LIGHT_SWITCH_COTTAGE_MY
        FALSE, // mRmTp_LIGHT_SWITCH_9
        FALSE, // mRmTp_LIGHT_SWITCH_NPC
        FALSE, // mRmTp_LIGHT_SWITCH_LIGHTHOUSE
        FALSE  // mRmTp_LIGHT_SWITCH_TENT
    };

    int switch_index = mRmTp_GetNowSceneLightSwitchIndex();

    if (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) {
        return z_bottun_data[switch_index];
    }

    return FALSE;
}

static int l_mRmTp_switch_data = 0;

extern int mRmTp_NowSceneLightSwitchON() {
    int switch_index = mRmTp_GetNowSceneLightSwitchIndex();

    if (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) {
        l_mRmTp_switch_data |= (1 << switch_index);
        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_IndexLightSwitchON(int switch_index) {
    if (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) {
        l_mRmTp_switch_data |= (1 << switch_index);
        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_NowSceneLightSwitchOFF() {
    int switch_index = mRmTp_GetNowSceneLightSwitchIndex();

    if (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) {
        l_mRmTp_switch_data &= ~(1 << switch_index);
        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_IndexLightSwitchOFF(int switch_index) {
    if (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) {
        l_mRmTp_switch_data &= ~(1 << switch_index);
        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_Index2LightSwitchStatus(int switch_index) {
    return (switch_index >= 0 && switch_index < mRmTp_LIGHT_SWITCH_NUM) ? ((l_mRmTp_switch_data >> switch_index) & 1)
                                                                        : TRUE;
}

static int mRmTp_CheckExistMyRoomOwner(int house_no) {
    return mPr_NullCheckPersonalID(&Save_Get(homes[house_no & 3]).ownerID) != TRUE;
}

static int mRmTp_CheckMyRoomLightON(int house_idx, int check_owned) {
    int now_sec = Common_Get(time.now_sec);

    if (check_owned == TRUE) {
        if (mRmTp_CheckExistMyRoomOwner(house_idx) &&
            (now_sec >= (18 * mTM_SECONDS_IN_HOUR) || now_sec < (5 * mTM_SECONDS_IN_HOUR))) {
            return TRUE;
        }
    } else if (now_sec >= (18 * mTM_SECONDS_IN_HOUR) || now_sec < (5 * mTM_SECONDS_IN_HOUR)) {
        return TRUE;
    }

    return FALSE;
}

extern int mRmTp_SetDefaultLightSwitchData(int state) {
    int i;

    if (state == 0) {

        l_mRmTp_switch_data = 0;
        for (i = 0; i < PLAYER_NUM; i++) {
            int now_sec = Common_Get(time.now_sec);

            if (now_sec >= (18 * mTM_SECONDS_IN_HOUR) || now_sec < (5 * mTM_SECONDS_IN_HOUR)) {
                l_mRmTp_switch_data |= (1 << (i * 2));
            }
        }

        return TRUE;
    } else if (state == 1) {
        l_mRmTp_switch_data = 0;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (mRmTp_CheckMyRoomLightON(i, TRUE)) {
                l_mRmTp_switch_data |= (1 << (i * 2));
            }
        }

        return TRUE;
    } else if (state == 2) {
        l_mRmTp_switch_data = 0;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (mRmTp_CheckMyRoomLightON(i, TRUE)) {
                l_mRmTp_switch_data |= (1 << (i * 2));
            }
        }

        return TRUE;
    } else if (state == 3) {
        int our_house = mHS_get_arrange_idx(Common_Get(player_no) & 3);

        l_mRmTp_switch_data = 0;
        for (i = 0; i < PLAYER_NUM; i++) {
            if (i != our_house && mRmTp_CheckMyRoomLightON(i, TRUE)) {
                l_mRmTp_switch_data |= (1 << (i * 2));
            }
        }

        return TRUE;
    }

    return FALSE;
}

extern void mRmTp_DecideCottageDefaultLightSwitch() {
    int now_sec = Common_Get(time.now_sec);

    if (now_sec >= (18 * mTM_SECONDS_IN_HOUR) || now_sec < (5 * mTM_SECONDS_IN_HOUR)) {
        mRmTp_IndexLightSwitchON(mRmTp_LIGHT_SWITCH_COTTAGE_MY);
    } else {
        mRmTp_IndexLightSwitchOFF(mRmTp_LIGHT_SWITCH_COTTAGE_MY);
    }
}

static mHm_fllot_bit_c* mRmTp_GetNowSceneFloorBitInfoP() {
    mActor_name_t field_id = mFI_GetFieldId();

    if (Save_Get(scene_no) == SCENE_COTTAGE_MY) {
        return &Save_Get(island).cottage.room.floor_bit_info;
    } else if (mFI_GET_TYPE(field_id) == mFI_FIELD_PLAYER0_ROOM) {
        int idx = (field_id - mFI_FIELD_PLAYER0_ROOM) & 3;
        int floor_no = mFI_GetPlayerHouseFloorNo(Save_Get(scene_no));

        if (floor_no != -1) {
            return &Save_Get(homes[idx]).floors[floor_no].floor_bit_info;
        }
    }

    return NULL;
}

extern int mRmTp_GetNowSceneOriginalWallStatus() {
    mHm_fllot_bit_c* floor_bit_info = mRmTp_GetNowSceneFloorBitInfoP();

    if (floor_bit_info != NULL) {
        return floor_bit_info->wall_original;
    }

    return FALSE;
}

extern int mRmTp_GetNowSceneOriginalFloorStatus() {
    mHm_fllot_bit_c* floor_bit_info = mRmTp_GetNowSceneFloorBitInfoP();

    if (floor_bit_info != NULL) {
        return floor_bit_info->floor_original;
    }

    return FALSE;
}

extern void mRmTp_SetNowSceneOriginalWallStatus(int enabled) {
    mHm_fllot_bit_c* floor_bit_info = mRmTp_GetNowSceneFloorBitInfoP();

    if (floor_bit_info != NULL) {
        floor_bit_info->wall_original = enabled;
    }
}

extern void mRmTp_SetNowSceneOriginalFloorStatus(int enabled) {
    mHm_fllot_bit_c* floor_bit_info = mRmTp_GetNowSceneFloorBitInfoP();

    if (floor_bit_info != NULL) {
        floor_bit_info->floor_original = enabled;
    }
}

extern int mRmTp_FtrItemNo2FtrIdx(mActor_name_t ftr_item_no) {
    if (ITEM_IS_FTR(ftr_item_no)) {
        if (ITEM_NAME_GET_TYPE(ftr_item_no) == NAME_TYPE_FTR0) {
            return (ftr_item_no - FTR0_START) >> 2;
        } else {
            return 0x400 + ((ftr_item_no - FTR1_START) >> 2);
        }
    }

    return 0;
}

extern mActor_name_t mRmTp_FtrIdx2FtrItemNo(int ftr_idx, int direct) {
    mActor_name_t ftr_item_no;
    int real_direct = direct & 3;

    if (ftr_idx < 0) {
        return FTR0_START;
    }

    ftr_item_no = FTR1_START + ((ftr_idx - 0x400) << 2) + real_direct;
    if (ftr_idx < 0x400) {
        ftr_item_no = FTR0_START + (ftr_idx << 2) + real_direct;
    }

    return ftr_item_no;
}

extern int mRmTp_SoundStepWalkSE(xyz_t* wpos) {
    switch (Save_Get(scene_no)) {
        case SCENE_MY_ROOM_S: {
            if (wpos->z > 200.0f) {
                return TRUE;
            }

            break;
        }

        case SCENE_MY_ROOM_M:
        case SCENE_MY_ROOM_LL2: {
            if (wpos->z > 280.0f) {
                return TRUE;
            }

            break;
        }

        case SCENE_MY_ROOM_L:
        case SCENE_MY_ROOM_LL1:
        case SCENE_MY_ROOM_BASEMENT_S:
        case SCENE_MY_ROOM_BASEMENT_M:
        case SCENE_MY_ROOM_BASEMENT_L:
        case SCENE_MY_ROOM_BASEMENT_LL1: {
            if (wpos->z > 360.0f) {
                return TRUE;
            }

            break;
        }

        default:
            return FALSE;
    }

    return FALSE;
}
