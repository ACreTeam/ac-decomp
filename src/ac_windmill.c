#include "ac_windmill.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"
#include "m_common_data.h"
#include "m_player_lib.h"

static void aWIN_actor_dt(ACTOR* actor, GAME* game);
static void aWIN_actor_init(ACTOR* actor, GAME* game);
static void aWIN_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Windmill_Profile = {
    mAc_PROFILE_WINDMILL,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NONE,
    WINDMILL0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    NONE_ACTOR_PROC,
    &aWIN_actor_dt,
    &aWIN_actor_init,
    &aWIN_actor_draw,
    NULL
};

u8 aWIN_shadow_vtx_fix_flg_table[] = { TRUE, FALSE, FALSE, TRUE, FALSE, TRUE, FALSE, TRUE };

static void aWIN_set_bgOffset(STRUCTURE_ACTOR* yatai, int idx);

static void aWIN_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* windmill = (STRUCTURE_ACTOR*)actor;

    aWIN_set_bgOffset(windmill, 0);
    cKF_SkeletonInfo_R_dt(&windmill->keyframe);
}

#include "../src/ac_windmill_move.c_inc"

#include "../src/ac_windmill_draw.c_inc"
