#include "ac_radio.h"

#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_name_table.h"
#include "bg_item.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "m_demo.h"
#include "m_common_data.h"

static void aRAD_actor_ct(ACTOR*, GAME*);
static void aRAD_actor_init(ACTOR*, GAME*);
static void aRAD_actor_draw(ACTOR*, GAME*);

ACTOR_PROFILE Radio_Profile = {
    mAc_PROFILE_RADIO,
    ACTOR_PART_ITEM,
    ACTOR_STATE_TA_SET,
    AEROBICS_RADIO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RADIO_ACTOR),
    aRAD_actor_ct,
    NONE_ACTOR_PROC,
    aRAD_actor_init,
    aRAD_actor_draw,
    NULL,
};

extern Vtx obj_e_radio_shadow_v[];
extern Gfx obj_e_radio_shadowT_model[];

u8 aRAD_shadow_vtx_fix_flg_table[] = {1,0,0,1,0,1,1,0};
bIT_ShadowData_c aRAD_shadow_data = {
    8,
    aRAD_shadow_vtx_fix_flg_table,
    60.0f,
    obj_e_radio_shadow_v,
    obj_e_radio_shadowT_model,
};

extern Gfx radio_DL_model[];

static void aRAD_setup_action(RADIO_ACTOR*, int);
static void aRAD_set_bgOffset(RADIO_ACTOR*, int);

static void aRAD_actor_ct(ACTOR* actor, GAME* game){
    RADIO_ACTOR* radio = (RADIO_ACTOR*)actor;
    
    aRAD_setup_action(radio, 0); 
    radio->next_action = 0;
    aRAD_set_bgOffset(radio, 1);
}

#include "../src/actor/ac_radio_move.c_inc"

#include "../src/actor/ac_radio_draw.c_inc"
