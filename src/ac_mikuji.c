#include "ac_mikuji.h"

#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_name_table.h"
#include "bg_item.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "m_demo.h"
#include "m_common_data.h"

static void aMIK_actor_ct(ACTOR* actor, GAME* game);
static void aMIK_actor_init(ACTOR* actor, GAME* game);
static void aMIK_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Mikuji_Profile = {
    mAc_PROFILE_MIKUJI,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    NEWYEAR_TABLE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(MIKUJI_ACTOR),
    &aMIK_actor_ct,
    NONE_ACTOR_PROC,
    &aMIK_actor_init,
    &aMIK_actor_draw,
    NULL
};

extern Vtx obj_e_mikuji_shadow_v[];
extern Gfx obj_e_mikuji_shadow_model[];

u8 aMIK_shadow_vtx_fix_flg_table[] = {1,0,0,1,0,1,1,0};
bIT_ShadowData_c aMIK_shadow_data = {
    8,
    aMIK_shadow_vtx_fix_flg_table,
    60.0f,
    obj_e_mikuji_shadow_v,
    obj_e_mikuji_shadow_model,
};

extern Gfx obj_e_mikuji_model[];

static void aMIK_set_bgOffset(MIKUJI_ACTOR* mikuji, int offs);

static void aMIK_actor_ct(ACTOR* actor, GAME* game)
{
    aMIK_set_bgOffset((MIKUJI_ACTOR*)actor, 1);
}

#include "../src/ac_mikuji_move.c_inc"
#include "../src/ac_mikuji_draw.c_inc"
