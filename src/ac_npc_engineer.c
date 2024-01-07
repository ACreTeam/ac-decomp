#include "ac_npc_engineer.h"
#include "m_name_table.h"
#include "m_common_data.h"

extern void aNEG_actor_ct(ACTOR* actor, GAME* game);
extern void aNEG_actor_dt(ACTOR* actor, GAME* game);
extern void aNEG_actor_init(ACTOR* actor, GAME* game);
extern void aNEG_actor_save(ACTOR* actor, GAME* game);

ACTOR_PROFILE Npc_Engineer_Profile = {
    mAc_PROFILE_NPC_ENGINEER,
    ACTOR_PART_NPC,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPCENGINEER_ACTOR),
    aNEG_actor_ct,
    aNEG_actor_dt,
    aNEG_actor_init,
    mActor_NONE_PROC1,
    aNEG_actor_save,
};

void aNEG_actor_move(ACTOR*, GAME*);
void aNEG_actor_draw(ACTOR*, GAME*);

void aNEG_actor_ct(ACTOR* actor, GAME* game){
    static aNPC_ct_data_c ct_data = {
        &aNEG_actor_move,
        &aNEG_actor_draw,
        5,
        NULL,
        NULL,
        NULL,
        0,
    };
    NPCENGINEER_ACTOR* engineer = (NPCENGINEER_ACTOR*)actor;
    if(Common_Get(clip.npc_clip)->birth_check_proc(actor,game) == TRUE){
        engineer->npc_class.schedule.schedule_proc = (aNPC_SCHEDULE_PROC)mActor_NONE_PROC1;
        Common_Get(clip.npc_clip)->ct_proc(actor,game,&ct_data);
        engineer->npc_class.condition_info.demo_flg = -1;
        engineer->npc_class.condition_info.hide_request = 0;
        engineer->npc_class.palActorIgnoreTimer = -1;
        engineer->npc_class.actor_class.status_data.weight = MASSTYPE_HEAVY;
        engineer->npc_class.actor_class.shape_info.rotation.y = 0x4000;
        engineer->npc_class.actor_class.world.angle.y = 0x4000;
        engineer->npc_class.movement.mv_angl = 0x4000;
        engineer->npc_class.request.act_priority = 4;
        engineer->npc_class.request.act_idx = 0;
        engineer->npc_class.request.act_type = 0;
    }
}

void aNEG_actor_save(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->save_proc(actor,game);
}

void aNEG_actor_dt(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->dt_proc(actor,game);
}

void aNEG_actor_init(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->init_proc(actor,game);
}

void aNEG_actor_move(ACTOR* actor, GAME* game){ 
    Common_Get(clip.npc_clip)->move_proc(actor,game);
}

void aNEG_actor_draw(ACTOR* actor, GAME* game) {
    Common_Get(clip.npc_clip)->draw_proc(actor,game);
}
