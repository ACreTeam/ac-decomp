#include "ac_t_rei1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTRI1_actor_ct(ACTOR* actor, GAME* game);
static void aTRI1_actor_draw(ACTOR* actor, GAME* game);
static void aTRI1_actor_move(ACTOR* actor, GAME* game);
static void aTRI1_setupAction(ACTOR* actor, int action);

ACTOR_PROFILE T_Rei1_Profile = {
    mAc_PROFILE_T_REI1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(REI1_ACTOR),
    &aTRI1_actor_ct,
    NONE_ACTOR_PROC,
    &aTRI1_actor_move,
    &aTRI1_actor_draw,
    NULL
};

extern Gfx crw_rei1_body_model[];

static void aTRI1_actor_ct(ACTOR* actor, GAME* game){
    aTRI1_setupAction(actor, 4);
}

static void aTRI1_destruct(ACTOR* actor){
    Actor_delete(actor);
}

static void aTRI1_setupAction(ACTOR* actor, int action){
    REI1_ACTOR* rei1 = (REI1_ACTOR*)actor;
    static REI1_PROC process[] = {
        (REI1_PROC)none_proc1, (REI1_PROC)none_proc1, (REI1_PROC)none_proc1, aTRI1_destruct,(REI1_PROC)none_proc1, NULL
    };
    
    rei1->proc = process[action];
    rei1->current_id = action;
    rei1->tools_class.work0 = action;
}

static void aTRI1_actor_move(ACTOR* actor, GAME* game){
    REI1_ACTOR* rei1 = (REI1_ACTOR*)actor;
    
    if(rei1->tools_class.work0 != rei1->current_id){
        aTRI1_setupAction(actor, rei1->tools_class.work0);
    }

    rei1->proc(actor);
}

static void aTRI1_actor_draw(ACTOR* actor, GAME* game){
    REI1_ACTOR* rei1 = (REI1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(rei1->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&rei1->tools_class.matrix_work);
        Matrix_Position_Zero(&rei1->tools_class.actor_class.world.position);
        
        rei1->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_rei1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }
}
