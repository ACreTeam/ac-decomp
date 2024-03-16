#include "ac_fallS.h"
#include "m_name_table.h"
#include "evw_anime.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "audio.h"
#include "sys_math3d.h"
#include "sys_matrix.h"
#include "m_rcp.h"

extern Gfx obj_fallS_model[];
extern Gfx obj_fallS_rainbowT_model[];
extern EVW_ANIME_DATA obj_fallS_evw_anime;

static void aFLS_actor_move(ACTOR* actor, GAME* game);
static void aFLS_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE FallS_Profile = {
    mAc_PROFILE_FALLS,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    WATERFALL_SOUTH,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(FALLS_ACTOR),
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    aFLS_actor_move,
    aFLS_actor_draw,
    NULL,
};

#include "../src/ac_fallS_move.c_inc"

#include "../src/ac_fallS_draw.c_inc"
