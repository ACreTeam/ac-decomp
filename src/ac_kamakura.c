#include "ac_kamakura.h"

#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_house.h"
#include "m_player_lib.h"
#include "m_demo.h"
#include "ac_intro_demo.h"
#include "m_bgm.h"
#include "sys_matrix.h"
#include "m_rcp.h"
#include "libforest/gbi_extensions.h"

enum {
    aKKR_ACTION_WAIT,
    aKKR_ACTION_DELETED1,
    aKKR_ACTION_DELETED2,
    aKKR_ACTION_DELETED3,
    aKKR_ACTION_DELETED4,
    aKKR_ACTION_DELETED5,
    aKKR_ACTION_DELETED6,
    aKKR_ACTION_DELETED7,

    aKKR_ACTION_NUM
};

static void aKKR_actor_ct(ACTOR* actor, GAME* game);
static void aKKR_actor_dt(ACTOR* actor, GAME* game);
static void aKKR_actor_init(ACTOR* actor, GAME* game);
static void aKKR_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Kamakura_Profile = {
    mAc_PROFILE_KAMAKURA,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    KAMAKURA,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(STRUCTURE_ACTOR),
    &aKKR_actor_ct,
    &aKKR_actor_dt,
    &aKKR_actor_init,
    &aKKR_actor_draw,
    NULL
};
// clang-format on

// clang-format off
static u8 aKKR_shadow_vtx_fix_flg_table[] = {
    TRUE, FALSE, FALSE, TRUE,
    TRUE, FALSE, FALSE, TRUE,
    FALSE, TRUE, TRUE, FALSE,
    TRUE, FALSE, TRUE, FALSE,
    FALSE, TRUE, TRUE, FALSE
};
// clang-format on

extern Vtx obj_w_kamakura_shadow_v[];
extern Gfx obj_e_kamakura_shadow_model[];

// clang-format off
static bIT_ShadowData_c aKKR_shadow_data = {
    20,
    aKKR_shadow_vtx_fix_flg_table,
    60.0f,
    obj_w_kamakura_shadow_v,
    obj_e_kamakura_shadow_model
};
// clang-format on

static void change_FGUnit(STRUCTURE_ACTOR* kamakura, int type);
static void aKKR_setup_action(STRUCTURE_ACTOR* kamakura, int action);
static void aKKR_set_bgOffset(STRUCTURE_ACTOR* kamakura, int offs);
static int aKKR_ctrl_light(STRUCTURE_ACTOR* kamakura);

static void aKKR_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* kamakura;

    kamakura = (STRUCTURE_ACTOR*)actor;
    change_FGUnit(kamakura, 1);

    aKKR_setup_action(kamakura, aKKR_ACTION_WAIT);
    aKKR_set_bgOffset(kamakura, 1);

    kamakura->arg0_f = aKKR_ctrl_light(kamakura) ? 1.0f : 0.0f;
}

static void aKKR_actor_dt(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* kamakura;

    kamakura = (STRUCTURE_ACTOR*)actor;
    change_FGUnit(kamakura, 0);
}

#include "../src/ac_kamakura_move.c_inc"

#include "../src/ac_kamakura_draw.c_inc"
