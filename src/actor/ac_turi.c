#include "ac_turi.h"

#include "ac_turi_clip.h"
#include "m_name_table.h"
#include "bg_item_h.h"
#include "m_fishrecord.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"
#include "m_event_map_npc.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "m_rcp.h"

enum {
    aTUR_ACT_WAIT,

    aTUR_ACT_NUM
};

static void aTUR_actor_ct(ACTOR* actorx, GAME* game);
static void aTUR_actor_dt(ACTOR* actorx, GAME* game);
static void aTUR_actor_init(ACTOR* actorx, GAME* game);
static void aTUR_actor_move(ACTOR* actorx, GAME* game);
static void aTUR_actor_draw(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Turi_Profile = {
    mAc_PROFILE_TURI,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    FISHCHECK_STAND0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TURI_ACTOR),
    &aTUR_actor_ct,
    &aTUR_actor_dt,
    &aTUR_actor_init,
    &aTUR_actor_draw,
    NULL,
};
// clang-format on

extern Vtx obj_e_turi_l_shadow_v[];
extern Gfx obj_e_turi_l_shadow_model[];

extern Vtx obj_e_turi_r_shadow_v[];
extern Gfx obj_e_turi_r_shadow_model[];

static u8 aTUR_shadow_vtx_fix_flg_table[] = { TRUE, FALSE, FALSE, TRUE, FALSE, TRUE };
static bIT_ShadowData_c aTUR_shadow_data_l = { 6, aTUR_shadow_vtx_fix_flg_table, 60.0f, obj_e_turi_l_shadow_v, obj_e_turi_l_shadow_model, };
static bIT_ShadowData_c aTUR_shadow_data_r = { 6, aTUR_shadow_vtx_fix_flg_table, 60.0f, obj_e_turi_r_shadow_v, obj_e_turi_r_shadow_model, };

static void aTRC_clip_ct(void);
static void aTRC_clip_dt(void);
static void aTUR_set_bgOffset(ACTOR* actorx, int type);
static void aTUR_setup_action(TURI_ACTOR* turi, int act_idx);

#include "../src/actor/ac_turi_clip.c_inc"
#include "../src/actor/ac_turi_move.c_inc"
#include "../src/actor/ac_turi_draw.c_inc"

static void aTUR_actor_ct(ACTOR* actorx, GAME* game) {
    TURI_ACTOR* turi = (TURI_ACTOR*)actorx;

    turi->structure_class.arg0 = actorx->npc_id - FISHCHECK_STAND0;
    turi->structure_class.structure_type = aSTR_TYPE_TURI + turi->structure_class.arg0;
    turi->structure_class.structure_pal = aSTR_PAL_TURI + turi->structure_class.arg0;
    aTUR_setup_action(turi, aTUR_ACT_WAIT);
    aTUR_set_bgOffset(actorx, turi->structure_class.arg0 + 2);
    aTRC_clip_ct();
}

static void aTUR_actor_dt(ACTOR* actorx, GAME* game) {
    aTRC_clip_dt();
}
