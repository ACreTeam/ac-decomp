#include "m_home.h"

#include "m_common_data.h"
#include "m_house.h"
#include "m_string.h"
#include "m_font.h"
#include "m_mail.h"
#include "m_lib.h"
#include "m_name_table.h"
#include "m_field_make.h"
#include "libultra/libultra.h"
#include "m_cockroach.h"
#include "m_personal_id.h"
#include "m_private.h"

/* upstairs room base unit layout */
static mActor_name_t l_player_room_2_utinfo[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    DOOR0,       RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

/* basement room base unit layout */
static mActor_name_t l_player_room_bm_utinfo[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, DOOR0,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

/* small main room base unit layout */
static mActor_name_t l_proom_s_tmp[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, DOOR0,       EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_DOOR,
    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EXIT_DOOR,   EXIT_DOOR,   RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

/* medium main room base unit layout */
static mActor_name_t l_proom_m_tmp[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,
    RSV_WALL_NO, RSV_WALL_NO, DOOR0,       EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EXIT_DOOR,   EXIT_DOOR,   RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

/* large main room base unit layout */
static mActor_name_t l_proom_l_tmp[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    RSV_WALL_NO, DOOR1,       RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, DOOR0,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EXIT_DOOR,   EXIT_DOOR,   RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

/* island cottage base unit layout */
static mActor_name_t l_proom_cottage_tmp[UT_X_NUM * UT_Z_NUM] = {
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, RSV_DOOR,    RSV_DOOR,    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO,
    RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    RSV_WALL_NO, EXIT_DOOR,   EXIT_DOOR,   RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    RSV_WALL_NO,
    RSV_WALL_NO, RSV_WALL_NO, RSV_WALL_NO, EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,
    EMPTY_NO,    EMPTY_NO,    EMPTY_NO,    EMPTY_NO
};

#define HANIWA_MSG_LINES 4

// TODO: fix me

/**
 * @brief Clears the save data for a given home.
 *
 * @param home_no Index of the home which will be cleared (0-3).
 **/
extern void mHm_ClearHomeInfo(int home_no) {
    static int haniwa_msg[HANIWA_MSG_LINES] = { 0x76A, 0x76B, 0x76C,
                                                0x76D }; /* These are probably defines somewhere from auto-gen */

    int no;
    mHm_hs_c* home;
    u8 haniwa_msg_buf[HANIWA_MESSAGE_LEN];
    u16* item_p;
    u16* src_p;
    int i;
    u8* haniwa_msg_p;
    int j;

    no = home_no & 3;
    home = Save_GetPointer(homes[no]);
    bzero(home, sizeof(mHm_hs_c));
    mPr_ClearPersonalID(&home->ownerID);
    bcopy(l_proom_s_tmp, home->floors[mHm_ROOM_MAIN].layer_main.items, (UT_X_NUM * UT_Z_NUM) * sizeof(u16));
    home->floors[mHm_ROOM_MAIN].layer_main.ftr_switch = 0;
    *((u32*)&home->floors[mHm_ROOM_MAIN].layer_main.ftr_switch + 1) = 0; /* ftr_switch might be a union? */
    *((u32*)&home->floors[mHm_ROOM_MAIN].layer_main.ftr_switch + 0) = 0;

    item_p = (u16*)home->floors[mHm_ROOM_BASEMENT].layer_main.items;
    src_p = l_player_room_bm_utinfo;
    for (i = 0; i < UT_X_NUM * UT_Z_NUM; i++) {
        *item_p++ = *src_p++;
    }

    item_p = ((u16*)home->floors[mHm_ROOM_UPPER].layer_main.items);
    src_p = l_player_room_2_utinfo;
    for (i = 0; i < UT_X_NUM * UT_Z_NUM; i++) {
        *item_p++ = *src_p++;
    }

    mMl_clear_mail_box(home->mailbox, HOME_MAILBOX_SIZE);
    Save_Set(homes[no].outlook_pal, no);
    Save_Set(homes[no].next_outlook_pal, no);
    mCkRh_InitGokiSaveData_1Room_ByHomeData(home);
    mHm_SetDefaultPlayerRoomData(no);

    haniwa_msg_p = home->haniwa.message;
    for (j = 0; j < HANIWA_MSG_LINES; j++) {
        int len;

        mString_Load_StringFromRom(haniwa_msg_buf, HANIWA_MESSAGE_LEN, haniwa_msg[j]);
        len = mMl_strlen(haniwa_msg_buf, HANIWA_MESSAGE_LEN, CHAR_SPACE);
        haniwa_msg_buf[len] = CHAR_NEW_LINE;
        mem_copy(haniwa_msg_p, haniwa_msg_buf, len + 1);
        haniwa_msg_p += len + 1;
    }

    Save_Set(keep_house_size[no], 0);
    Save_Set(homes[no].door_original, 0xFF);
}

/**
 * @brief Clears save data for all homes.
 **/
extern void mHm_ClearAllHomeInfo() {
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        mHm_ClearHomeInfo(i);
    }
}

/**
 * @brief Sets common_data's 'now_home' pointer to the current player's home.
 **/
extern void mHm_SetNowHome() {
    mHm_hs_c* now_home = NULL;

    if (Common_Get(player_no) < PLAYER_NUM) {
        now_home = Save_GetPointer(homes[mHS_get_arrange_idx(Common_Get(player_no))]);
    }

    Common_Set(now_home, now_home);
}

/* sizeof(mHm_player_room_default_data_c) == 0x10 */
typedef struct {
    /* 0x00 */ u8 wall_num;
    /* 0x01 */ u8 floor_num;
    /* 0x04 */ int item_ut_x;
    /* 0x08 */ int item_ut_z;
    /* 0x0C */ mActor_name_t item;
} mHm_player_room_default_data_c;

/* list of default properties for each house */
static mHm_player_room_default_data_c l_mHm_player_room_default_data[PLAYER_NUM] = {
    { 3, 38, 4, 1, FTR_START(FTR_SUM_CASSE01) },  /* Top-left house, stone wall & old flooring */
    { 41, 42, 4, 1, FTR_START(FTR_SUM_CASSE01) }, /* Top-right house, wood panelling & steel flooring */
    { 55, 5, 4, 1, FTR_START(FTR_SUM_CASSE01) },  /* Bottom-left house, shanty wall & birch flooring */
    { 42, 34, 4, 1, FTR_START(FTR_SUM_CASSE01) }  /* Bottom-right house, concrete wall & charcoal tile */
};

/**
 * @brief Sets the default data for a given home.
 *
 * @param home_no Index of the home which will receive the default data
 **/
extern void mHm_SetDefaultPlayerRoomData(int home_no) {
    int i;

    int ut_x = l_mHm_player_room_default_data[home_no & 3].item_ut_x;
    int ut_z = l_mHm_player_room_default_data[home_no & 3].item_ut_z;

    Save_Set(homes[home_no & 3].floors[mHm_ROOM_MAIN].layer_main.items[ut_z][ut_x],
             l_mHm_player_room_default_data[home_no & 3].item);
    Save_Set(homes[home_no & 3].floors[mHm_ROOM_MAIN].layer_main.items[1][1], FTR_START(FTR_NOG_MIKANBOX));
    Save_Set(homes[home_no & 3].floors[mHm_ROOM_MAIN].layer_secondary.items[1][1], ITM_DIARY00);

    for (i = 0; i < mHm_ROOM_NUM; i++) {
        Save_Set(homes[home_no & 3].floors[i].wall_floor.flooring_idx,
                 l_mHm_player_room_default_data[home_no & 3].floor_num);
        Save_Set(homes[home_no & 3].floors[i].wall_floor.wallpaper_idx,
                 l_mHm_player_room_default_data[home_no & 3].wall_num);
    }
}

/**
 * @brief Initializes the home's owner id to the given player's id.
 *
 * @param home Pointer to the mHm_hs_c home which will be updated
 * @param player_no Index of the player whose id will be used
 **/
extern void mHm_InitHomeInfo(mHm_hs_c* home, int player_no) {
    mPr_CopyPersonalID(&home->ownerID, Save_GetPointer(private_data[player_no].player_ID));
}

/**
 * @brief Sets/clears the wall and door layout for a given room.
 *
 * @param dst Pointer to the room item actor data
 * @param roomtype Type of room to select correct room data (0-3)
 * @param set when TRUE copy data, when FALSE clear data
 **/
static void mHm_ChangeWallDoorFG(mActor_name_t* dst, int roomtype, int set) {
    static mActor_name_t* player_room_tmp_table[mHm_ROOMTYPE_NUM] = {
        l_proom_s_tmp,      /* small room layout (default) */
        l_proom_m_tmp,      /* medium room layout */
        l_proom_l_tmp,      /* large room layout */
        l_proom_cottage_tmp /* island cottage layout */
    };

    mActor_name_t* src;
    int i;

    if (roomtype < mHm_ROOMTYPE_SMALL || roomtype >= mHm_ROOMTYPE_NUM) {
        roomtype = mHm_ROOMTYPE_SMALL;
    }

    src = player_room_tmp_table[roomtype];
    for (i = 0; i < UT_X_NUM * UT_Z_NUM; i++) {
        if (*src != EMPTY_NO) {
            if (set == FALSE) {
                *dst = EMPTY_NO; /* clear */
            } else {
                *dst = *src; /* set */
            }
        }

        src++;
        dst++;
    }
}

/**
 * @brief Clears the wall & door data for a room.
 *
 * @param items Pointer to the room actor items
 * @param roomtype Type of room to clear
 **/
static void mHm_EraseWallDoor(mActor_name_t* items, int roomtype) {
    mHm_ChangeWallDoorFG(items, roomtype, FALSE);
}

/**
 * @brief Sets the wall & door data for a room.
 *
 * @param items Pointer to the room actor items
 * @param roomtype Type of room to clear
 **/
static void mHm_SetWallDoor(mActor_name_t* items, int roomtype) {
    mHm_ChangeWallDoorFG(items, roomtype, TRUE);
}

/**
 * @brief Updates the wall & door data for the main room.
 *
 * @param home Pointer to the mHm_hs_c home to update
 * @param home_size Size of the home (0-4, but only 1-4 should be used for this function)
 **/
static void mHm_RehouseWallDoor(mHm_hs_c* home, int home_size) {
    static int room_size[mHm_HOMESIZE_NUM] = {
        mHm_ROOMTYPE_SMALL,  /* mHm_HOMESIZE_SMALL */
        mHm_ROOMTYPE_MEDIUM, /* mHm_HOMESIZE_MEDIUM */
        mHm_ROOMTYPE_LARGE,  /* mHm_HOMESIZE_LARGE */
        mHm_ROOMTYPE_LARGE,  /* mHm_HOMESIZE_UPPER */
        mHm_ROOMTYPE_SMALL   /* mHm_HOMESIZE_STATUE */
    };

    int new_size;
    int old_size;

    if (home_size < mHm_HOMESIZE_MEDIUM || home_size >= mHm_HOMESIZE_NUM) {
        home_size = mHm_HOMESIZE_MEDIUM;
    }

    old_size = room_size[home_size - 1];
    new_size = room_size[home_size];

    mHm_EraseWallDoor((u16*)home->floors[mHm_ROOM_MAIN].layer_main.items, old_size);
    mHm_EraseWallDoor((u16*)home->floors[mHm_ROOM_MAIN].layer_secondary.items, old_size);
    mHm_SetWallDoor((u16*)home->floors[mHm_ROOM_MAIN].layer_main.items, new_size);
    mHm_SetWallDoor((u16*)home->floors[mHm_ROOM_MAIN].layer_secondary.items, new_size);
}

#define CHECK_ORDER_DATE(home, rtc_time)                                \
    ((home)->size_info.upgrade_order_date.day != (rtc_time)->day ||     \
     (home)->size_info.upgrade_order_date.month != (rtc_time)->month || \
     (home)->size_info.upgrade_order_date.year != (rtc_time)->year)

/**
 * @brief Check if any house should be updated, and if so, update it.
 **/
extern void mHm_CheckRehouseOrder() {
    mHm_hs_c* home = Save_Get(homes);
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int i;

    for (i = 0; i < PLAYER_NUM; i++) {
        if (mPr_NullCheckPersonalID(&home->ownerID) == FALSE) {
            if (home->outlook_pal != home->next_outlook_pal) {
                home->outlook_pal = home->next_outlook_pal;
            }

            if (home->size_info.size != home->size_info.next_size && home->size_info.next_size < mHm_HOMESIZE_STATUE) {
                if (CHECK_ORDER_DATE(home, rtc_time)) {
                    home->outlook_pal = home->ordered_outlook_pal;
                    home->next_outlook_pal = home->ordered_outlook_pal;
                    home->size_info.size = home->size_info.next_size;
                    home->size_info.renew = TRUE;
                    mHm_RehouseWallDoor(home, home->size_info.size);
                }
            } else {
                if (home->size_info.basement_ordered) {
                    if (CHECK_ORDER_DATE(home, rtc_time)) {
                        mHm_SetBasement(i);
                        home->size_info.renew = TRUE;
                    }
                } else if (home->size_info.statue_ordered == TRUE) {
                    if (CHECK_ORDER_DATE(home, rtc_time)) {
                        home->size_info.next_size = mHm_HOMESIZE_STATUE;
                    }
                }
            }
        }
        home++;
    }

    for (i = 0; i < PLAYER_NUM; i++) {
        u32* state_flags = Save_GetPointer(private_data[i].state_flags);
        *state_flags &= (~0x200); /* TODO: these need an enum/defines */
    }
}

/**
 * @brief Stores the player's current house size for later.
 *
 * @param player_no Index of the player whose house size will be saved
 * @return TRUE/FALSE house size was kept
 **/
extern int mHm_KeepHouseSize(u8 player_no) {
    int arrange_idx;
    mHm_hs_c* home;
    u8* keep_house_size;
    int res = FALSE;

    if (player_no < PLAYER_NUM) {
        arrange_idx = mHS_get_arrange_idx(player_no);
        home = Save_GetPointer(homes[arrange_idx]);
        keep_house_size = Save_GetPointer(keep_house_size[arrange_idx]);

        res = TRUE;

        /* I don't think this is a union or struct due to the unused first bit */
        /* But maybe... perhaps they used a pad bit for the topmost bit unlike other structs */
        *keep_house_size = 0;
        *keep_house_size |= home->size_info.size;
        *keep_house_size |= home->size_info.next_size << 3;
        *keep_house_size |= home->size_info.renew << 6;
    }

    return res;
}

/**
 * @brief Checks whether the kept house size for a player is the same as the actual size.
 *
 * @param player_no The index of the player whose house will be checked
 * @returns TRUE/FALSE house size and keep house size are the same
 **/
extern int mHm_CheckKeepHouseSize(u8 player_no) {
    int arrange_idx;
    mHm_hs_c* home;
    u8* keep_house_size;
    int res = FALSE;

    if (player_no < PLAYER_NUM) {
        arrange_idx = mHS_get_arrange_idx(player_no);
        keep_house_size = Save_GetPointer(keep_house_size[arrange_idx]);
        home = Save_Get(homes + arrange_idx);

        if ((*keep_house_size & 7) == home->size_info.size &&
            ((*keep_house_size >> 3) & 7) == home->size_info.next_size &&
            ((*keep_house_size >> 6) & 1) == home->size_info.renew) {
            res = TRUE;
        }
    }

    return res;
}

/**
 * @brief Updates player house flags to include basement
 *
 * @param home_no Index of the house whose basement flag will be enabled
 * @return TRUE/FALSE was flag set
 **/
extern int mHm_SetBasement(u8 home_no) {
    if (home_no < PLAYER_NUM) {
        mHm_flg_c* flags = Save_GetPointer(homes[home_no].flags);
        if (flags->has_basement == FALSE) {
            flags->has_basement = TRUE;
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * @brief Sets the default island cottage data
 *
 * @param cottage Pointer to the mHm_cottage_c cottage which will receive the default data
 **/
static void mHm_SetDefaultCottageData(mHm_cottage_c* cottage) {
    if (cottage == NULL) {
        return;
    }

    cottage->room.wall_floor.flooring_idx = FLOOR_NPC013;
    cottage->room.wall_floor.wallpaper_idx = WALL_NPC013;

    cottage->room.layer_main.items[3][3] = FTR_START(FTR_FMANEKIN026);
    cottage->room.layer_main.items[3][6] = FTR_START(FTR_FMANEKIN027);
    cottage->room.layer_main.items[6][3] = FTR_START(FTR_FMANEKIN026);
    cottage->room.layer_main.items[6][6] = FTR_START(FTR_FMANEKIN027);
}

/**
 * @brief Initialize an mHm_cottage_c cottage.
 *
 * @param cottage Pointer to the mHm_cottage_c which will be initialized
 **/
extern void mHm_InitCottage(mHm_cottage_c* cottage) {
    if (cottage != NULL) {
        bzero(cottage, sizeof(mHm_cottage_c));
        mHm_SetWallDoor((u16*)cottage->room.layer_main.items, mHm_ROOMTYPE_COTTAGE);
        mCkRh_InitGokiSaveData_IslandPlayerRoom();
        mHm_SetDefaultCottageData(cottage);
    }
}
