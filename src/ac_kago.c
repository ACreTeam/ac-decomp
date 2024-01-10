#include "ac_kago.h"

#include "m_name_table.h"
#include "m_common_data.h"
#include "m_field_info.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"
#include "m_player_lib.h"

static void aKAG_actor_ct(ACTOR*,GAME*);
static void aKAG_actor_init(ACTOR*,GAME*);
static void aKAG_actor_draw(ACTOR*,GAME*);


ACTOR_PROFILE Kago_Profile = {
    mAc_PROFILE_KAGO,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SPORTSFAIR_BASKET_RED,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(KAGO_ACTOR),
    &aKAG_actor_ct,
    NONE_ACTOR_PROC,
    &aKAG_actor_init,
    &aKAG_actor_draw,
    NULL
};

extern Vtx obj_e_kago_shadow_v[];
extern Gfx obj_e_kago_shadow_model[];

u8 aKAG_shadow_vtx_fix_flg_table[] = {1,0,0,1,1,0,0,1,0,1,0,0,1};
bIT_ShadowData_c aKAG_shadow_data = {
    13,
    aKAG_shadow_vtx_fix_flg_table,
    60.0f,
    obj_e_kago_shadow_v,
    obj_e_kago_shadow_model,
};

void aKAG_set_bgOffset(KAGO_ACTOR*, int);
void aKAG_setup_action(KAGO_ACTOR*, int);

void aKAG_actor_ct(ACTOR* actor, GAME*){
    KAGO_ACTOR* kago = (KAGO_ACTOR*)actor;

    kago->structure_class.action = actor->npc_id - SPORTSFAIR_BASKET_RED;
    kago->structure_class.structure_type = kago->structure_class.action + aSTR_TYPE_SPORTSFAIR_A;
    kago->structure_class.structure_pal = kago->structure_class.action + aSTR_PAL_KAGO_R;
    aKAG_setup_action(kago,0);
    aKAG_set_bgOffset(kago,1);
}

#include "../src/ac_kago_move.c_inc"

#include "../src/ac_kago_draw.c_inc"