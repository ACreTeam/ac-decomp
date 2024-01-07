#include "ac_ev_majin.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_demo.h"

extern void aEMJ_actor_ct(ACTOR*, GAME*);
extern void aEMJ_actor_dt(ACTOR*, GAME*);
extern void aEMJ_actor_init(ACTOR*, GAME*);
extern void aEMJ_actor_save(ACTOR*, GAME*);

ACTOR_PROFILE Ev_Majin_Profile = {
    mAc_PROFILE_EV_MAJIN,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_EV_MAJIN,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_NPCMAJIN_ACTOR),
    aEMJ_actor_ct,
    aEMJ_actor_dt,
    aEMJ_actor_init,
    NONE_ACTOR_PROC,
    aEMJ_actor_save,
};

extern void aEMJ_actor_move(ACTOR*, GAME*);
extern void aEMJ_actor_draw(ACTOR*, GAME*);

static int aEMJ_talk_init(ACTOR*, GAME*);
static int aEMJ_talk_end_chk(ACTOR*, GAME*);
static void aEMJ_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);

void aEMJ_actor_ct(ACTOR* actor, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aEMJ_actor_move,
        &aEMJ_actor_draw,
        5,
        mActor_NONE_PROC1,
        &aEMJ_talk_init,
        &aEMJ_talk_end_chk,
        0,
    };
    EV_NPCMAJIN_ACTOR* majin = (EV_NPCMAJIN_ACTOR*)actor;
    
    if(Common_Get(clip.npc_clip)->birth_check_proc(actor,game) == TRUE){
        majin->npc_class.schedule.schedule_proc = aEMJ_schedule_proc;
        Common_Get(clip.npc_clip)->ct_proc(actor,game,&ct_data);
        majin->npc_class.head.lock_flag = 1;
        majin->npc_class.talk_info.default_turn_animation = 0x4E;
        majin->npc_class.talk_info.default_animation = 0x4E;
        majin->npc_class.talk_info.turn = 2;
    }
}

void aEMJ_actor_save(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->save_proc(actor,game);
}

void aEMJ_actor_dt(ACTOR* actor, GAME* game) {
    
    if(Common_Get(clip.groundhog_control_clip) != NULL){
        Common_Get(clip.groundhog_control_clip)->groundhog_npc_actor = NULL;
    }
    Common_Get(clip.npc_clip)->dt_proc(actor,game);
    Common_Get(clip.effect_clip)->effect_kill_proc(0x5D, 0xFFFF);
    
}

void aEMJ_actor_init(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->init_proc(actor,game);
}

void aEMJ_set_animation(ACTOR* actor, int idx){
    static s16 animeSeqNo[] = {79,78,80};
    
    Common_Get(clip.npc_clip)->animation_init_proc(actor,animeSeqNo[idx],0);
}

void aEMJ_actor_move(ACTOR* actor, GAME* game){ 
    Common_Get(clip.npc_clip)->move_proc(actor,game);
    actor->shape_info.draw_shadow = 0;
}

void aEMJ_actor_draw(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->draw_proc(actor,game);
}

#include "../src/ac_ev_majin_move.c_inc"