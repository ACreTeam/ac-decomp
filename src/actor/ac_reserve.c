#include "ac_reserve.h"
#include "bg_item_h.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_rcp.h"

static void aRSV_actor_ct(ACTOR* actor, GAME* game);
static void aRSV_actor_init(ACTOR* actor, GAME* game);
static void aRSV_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Reserve_Profile = {
    mAc_PROFILE_RESERVE,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    SIGN00,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RESERVE_ACTOR),
    aRSV_actor_ct,
    NONE_ACTOR_PROC,
    aRSV_actor_init,
    aRSV_actor_draw,
};

extern Gfx reserve_DL_model[];
extern Gfx reserve_winter_DL_model[];
extern Gfx obj_s_attentionT_model[];
extern Gfx obj_w_attentionT_model[];

static void aRSV_set_bgOffset(ACTOR*, int);
static void aRSV_setup_action(ACTOR* actor, int type);

static void aRSV_actor_ct(ACTOR* actor, GAME* game) {
    RESERVE_ACTOR* reserve = (RESERVE_ACTOR*)actor;
    mActor_name_t id;

    reserve->structure_class.season = Common_Get(time.season);

    reserve->structure_class.arg0 = actor->npc_id - SIGN00;

    aRSV_setup_action(actor, 0);
    aRSV_set_bgOffset(actor, 1);
}

extern Vtx reserve_shadow_v[];
extern Gfx reserve_shadow_model[];
extern Vtx obj_attention_shadow_v[];
extern Gfx obj_attention_shadowT_model[];

static u8 aRSV_shadow_vtx_fix_flg_table[] = { TRUE, FALSE, FALSE, TRUE };

static bIT_ShadowData_c aRSV_shadow_data = {
    4, aRSV_shadow_vtx_fix_flg_table, 60.0f, reserve_shadow_v, reserve_shadow_model,
};

static bIT_ShadowData_c aRSV_kappa_shadow_data = {
    4, aRSV_shadow_vtx_fix_flg_table, 60.0f, obj_attention_shadow_v, obj_attention_shadowT_model,
};

#include "../src/actor/ac_reserve_move.c_inc"
#include "../src/actor/ac_reserve_draw.c_inc"
