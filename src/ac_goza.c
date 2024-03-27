#include "ac_goza.h"

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
    aGOZ_UNKNOWN,

    aGOZ_ACTION_NUM
};

static void aGOZ_actor_ct(ACTOR* actor, GAME* game);
static void aGOZ_actor_init(ACTOR* actor, GAME* game);
static void aGOZ_actor_draw(ACTOR* actor, GAME* game);

// clang-format off
ACTOR_PROFILE Goza_Profile = {
  mAc_PROFILE_GOZA,
  ACTOR_PART_ITEM,
  ACTOR_STATE_TA_SET,
  SAKURA_TABLE0,
  ACTOR_OBJ_BANK_KEEP,
  sizeof(STRUCTURE_ACTOR),
  &aGOZ_actor_ct,
  mActor_NONE_PROC1,
  &aGOZ_actor_init,
  &aGOZ_actor_draw,
  NULL
};
// clang-format on

// clang-format off
static u8 aGOZ_shadow_vtx_fix_flg_tableA[] = {
  TRUE, TRUE, FALSE, FALSE,
  FALSE, TRUE, TRUE, TRUE,
  FALSE, FALSE, FALSE, TRUE,
  TRUE, TRUE, FALSE, FALSE,
  FALSE, TRUE, TRUE, TRUE,
  FALSE, FALSE, FALSE, TRUE,
  TRUE, TRUE, TRUE, TRUE
};
// clang-format on

// clang-format off
static u8 aGOZ_shadow_vtx_fix_flg_tableB[] = {
  FALSE, TRUE, TRUE, FALSE,
  FALSE, TRUE, FALSE, TRUE,
  TRUE, FALSE, FALSE, TRUE,
  FALSE, TRUE, TRUE, FALSE,
  FALSE, TRUE, FALSE, TRUE,
  TRUE, FALSE, FALSE, TRUE,
  TRUE, TRUE, TRUE, TRUE
};
// clang-format on

extern Vtx obj_e_hfes_shadow_a_v[];
extern Gfx obj_e_hfes_shadow_a_modelT[];

// clang-format off
static bIT_ShadowData_c aGOZ_shadow_dataA = {
    28,
    aGOZ_shadow_vtx_fix_flg_tableA,
    20.0f,
    obj_e_hfes_shadow_a_v,
    obj_e_hfes_shadow_a_modelT
};
// clang-format on

extern Vtx obj_e_hfes_shadow_b_v[];
extern Gfx obj_e_hfes_shadow_b_modelT[];

// clang-format off
static bIT_ShadowData_c aGOZ_shadow_dataB = {
    28,
    aGOZ_shadow_vtx_fix_flg_tableB,
    20.0f,
    obj_e_hfes_shadow_b_v,
    obj_e_hfes_shadow_b_modelT
};
// clang-format on

static bIT_ShadowData_c* aGOZ_shadow_data_table[] = { &aGOZ_shadow_dataB, &aGOZ_shadow_dataA };

static void aGOZ_setup_action(STRUCTURE_ACTOR* goza, int action);
static void aGOZ_set_bgOffset(STRUCTURE_ACTOR* kamakura, int offs);

static void aGOZ_actor_ct(ACTOR* actor, GAME* game) {
    STRUCTURE_ACTOR* goza;

    goza = (STRUCTURE_ACTOR*)actor;

    goza->arg1 = (actor->npc_id - SAKURA_TABLE0) & 1;

    aGOZ_setup_action(goza, aGOZ_UNKNOWN);
    
    aGOZ_set_bgOffset(goza, 1);
}

#include "../src/ac_goza_move.c_inc"

#include "../src/ac_goza_draw.c_inc"
