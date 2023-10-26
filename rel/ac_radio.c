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

static void aRAD_set_bgOffset(RADIO_ACTOR* radio, int offs){
    offs = offs == 0 ? 3 : 3;

    mCoBG_SetPlussOffset(radio->actor_class.home.position, offs, 100);
}

static void aRAD_wait(RADIO_ACTOR* radio, GAME_PLAY* play){
    xyz_t def = {2.0f, 0.0f, -10.0f};
    xyz_t newPos;
    
    if(radio->next_action >= 0x24){
        radio->next_action = 0;
        Matrix_push();
        Matrix_translate(radio->actor_class.world.position.x,radio->actor_class.world.position.y, radio->actor_class.world.position.z, 0);
        Matrix_Position(&def, &newPos);
        Matrix_pull();

        Common_Get(clip.effect_clip->effect_make_proc)(32, newPos, 1, 0x6000, &play->game, AEROBICS_RADIO, 1,0);
    }

    radio->next_action++;
}

static void aRAD_setup_action(RADIO_ACTOR* radio, int action){
    static RADIO_PROC proc[] = {aRAD_wait}; 

    radio->proc = proc[action];
    radio->current_action = action;
    
}

static void aRAD_actor_move(ACTOR* actor, GAME* game){
    GAME_PLAY* play = (GAME_PLAY*)game;
    RADIO_ACTOR* radio = (RADIO_ACTOR*)actor;
    PLAYER_ACTOR* player;

    int rbx;
    int rbz;
    int pbx;
    int pbz;

    player = GET_PLAYER_ACTOR(play);
    mFI_Wpos2BlockNum(&rbx,&rbz, radio->actor_class.world.position);
    mFI_Wpos2BlockNum(&pbx,&pbz, player->actor_class.world.position);

    if(!mDemo_Check(mDemo_TYPE_SCROLL, &player->actor_class) && !mDemo_Check(mDemo_TYPE_SCROLL2, &player->actor_class)
        && !mDemo_Check(mDemo_TYPE_SCROLL3, &player->actor_class) && ((rbx != pbx) || (rbz != pbz))){

        Actor_delete(&radio->actor_class);
    }
    else{
        radio->proc(radio, play); 
    }
}

static void aRAD_actor_init(ACTOR* actor, GAME* game){
    RADIO_ACTOR* radio = (RADIO_ACTOR*)actor;
    xyz_t pos = radio->actor_class.home.position;

    mFI_SetFG_common(DUMMY_RADIO, pos, 0); 
    aRAD_actor_move(actor, game);
    radio->actor_class.mv_proc = aRAD_actor_move;
}

static void aRAD_actor_draw(ACTOR* actor, GAME* game){
    RADIO_ACTOR* radio = (RADIO_ACTOR*)actor;
 
    Mtx* cur;
    GRAPH* graph = game->graph;
    u16* pal;
    Gfx* gfx;

    OPEN_DISP(graph);
    pal = Common_Get(clip.structure_clip)->get_pal_segment_proc(aSTR_PAL_RADIO);
    
    cur = _Matrix_to_Mtx_new(graph);

    if(cur != NULL){ 
        _texture_z_light_fog_prim_npc(graph);
        gfx = NOW_POLY_OPA_DISP;
        gSPSegment(gfx++, 0x8, pal); 
        gSPMatrix(gfx++, cur,G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++,radio_DL_model);
        SET_POLY_OPA_DISP(gfx);
        Common_Get(clip.bg_item_clip)->draw_shadow_proc(game, &aRAD_shadow_data, 0);
    }

    CLOSE_DISP(graph);
}