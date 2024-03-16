#include "ac_fallSESW.h"
#include "m_name_table.h"
#include "evw_anime.h"
#include "m_common_data.h"
#include "m_lib.h"
#include "audio.h"
#include "sys_math3d.h"
#include "sys_matrix.h"
#include "m_rcp.h"

extern Gfx obj_fallSESW_model[];
extern Gfx obj_fallSE_rainbowT_model[];
extern EVW_ANIME_DATA obj_fallSE_evw_anime;

static void aFLEW_actor_move(ACTOR* actor, GAME* game);
static void aFLEW_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE FallSESW_Profile = {
    mAc_PROFILE_FALLSESW,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    WATERFALL_EAST,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(FALLSESW_ACTOR),
    NONE_ACTOR_PROC,
    NONE_ACTOR_PROC,
    aFLEW_actor_move,
    aFLEW_actor_draw,
    NULL,
};

#include "../src/ac_fallSESW_move.c_inc"

#include "../src/ac_fallSESW_draw.c_inc"
