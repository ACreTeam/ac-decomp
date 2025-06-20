#include "ac_t_cracker.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTCR_actor_ct(ACTOR* actor, GAME* game);
static void aTCR_actor_move(ACTOR* actor, GAME* game);
static void aTCR_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Cracker_Profile = {
    mAc_PROFILE_T_CRACKER,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_CRACKER,
    sizeof(CRACKER_ACTOR),
    &aTCR_actor_ct,
    NONE_ACTOR_PROC,
    &aTCR_actor_move,
    &aTCR_actor_draw,
    NULL
};

static void aTCR_setupAction(ACTOR* actor, int idx);

extern Gfx tol_cracker_1T_model[];

static void aTCR_actor_ct(ACTOR* actor, GAME* game){
    aTCR_setupAction(actor, 1);
}

static void aTCR_calc_scale(ACTOR* actor, int idx){

    static f32 aim[] = {1.0f, 0.0f};
    f32 cracker_scale = actor->scale.x;
    
    chase_f(&cracker_scale, aim[idx],0.05f);

    actor->scale.x = cracker_scale;
    actor->scale.y = cracker_scale;
    actor->scale.z = cracker_scale;
    
}

static void aTCR_takeout(ACTOR* actor){

    aTCR_calc_scale(actor, 0);
}

static void aTCR_putaway(ACTOR* actor){

    aTCR_calc_scale(actor, 1);
}

static void aTCR_destruct(ACTOR* actor){

    Actor_delete(actor);
}

static void aTCR_setupAction(ACTOR* actor, int idx){
    CRACKER_ACTOR* cracker = (CRACKER_ACTOR*)actor;

    static CRACKER_PROC process[] = {(CRACKER_PROC)none_proc1, aTCR_takeout,aTCR_putaway,aTCR_destruct,
    (CRACKER_PROC)none_proc1,NULL};
    static f32 start_scale[] = {0.0f, 0.0f, 1.0f,1.0f,1.0f,0.0f,0.0f};
    f32 scale;

    cracker->proc = process[idx];
    cracker->current_id = idx; 
    cracker->tools_class.work0 = idx;

    scale = start_scale[idx];
    cracker->tools_class.actor_class.scale.x = scale;
    cracker->tools_class.actor_class.scale.y = scale;
    cracker->tools_class.actor_class.scale.z = scale;
    
}

static void aTCR_actor_move(ACTOR* actor, GAME* game){
    CRACKER_ACTOR* cracker = (CRACKER_ACTOR*)actor;
    
    int t = cracker->tools_class.work0;
    if(t!= cracker->current_id){
        aTCR_setupAction(actor, t);
    }
    cracker->proc(actor);
}

static void aTCR_actor_draw(ACTOR* actor, GAME* game){
    CRACKER_ACTOR* cracker = (CRACKER_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Gfx* gfxp;

    OPEN_DISP(graph);

    if(cracker->tools_class.init_matrix == 1){
        Matrix_put(&cracker->tools_class.matrix_work);
        Matrix_Position_Zero(&cracker->tools_class.actor_class.world.position);
        cracker->tools_class.init_matrix = 0;
    }
    else{
        Matrix_translate(cracker->tools_class.actor_class.world.position.x, cracker->tools_class.actor_class.world.position.y, 
            cracker->tools_class.actor_class.world.position.z, MTX_LOAD);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    Matrix_scale(cracker->tools_class.actor_class.scale.x, cracker->tools_class.actor_class.scale.y, cracker->tools_class.actor_class.scale.z, MTX_MULT);
   _texture_z_light_fog_prim_npc(graph); 

    gfxp = NOW_POLY_OPA_DISP;
    gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxp++, tol_cracker_1T_model);
    SET_POLY_OPA_DISP(gfxp);

    CLOSE_DISP(graph);
        
}
