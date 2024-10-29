#include "ac_t_zinnia1.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTZN1_actor_ct(ACTOR* actor, GAME* game);
static void aTZN1_actor_draw(ACTOR* actor, GAME* game);
static void aTZN1_actor_move(ACTOR* actor, GAME* game);
static void aTZN1_setupAction(ACTOR* actor, int action);

ACTOR_PROFILE T_Zinnia1_Profile = {
    mAc_PROFILE_T_ZINNIA1,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(ZINNIA1_ACTOR),
    &aTZN1_actor_ct,
    NONE_ACTOR_PROC,
    &aTZN1_actor_move,
    &aTZN1_actor_draw,
    NULL
};

extern Gfx crw_zinnia1_body_model[];

static void aTZN1_actor_ct(ACTOR* actor, GAME* game){
    aTZN1_setupAction(actor, 4);
}

static void aTZN1_destruct(ACTOR* actor){
    Actor_delete(actor);
}

static void aTZN1_setupAction(ACTOR* actor, int action){
    ZINNIA1_ACTOR* zinnia1 = (ZINNIA1_ACTOR*)actor;
    static ZINNIA1_PROC process[] = {
        (ZINNIA1_PROC)none_proc1, (ZINNIA1_PROC)none_proc1, (ZINNIA1_PROC)none_proc1, aTZN1_destruct,(ZINNIA1_PROC)none_proc1, NULL
    };
    
    zinnia1->proc = process[action];
    zinnia1->current_id = action;
    zinnia1->tools_class.work0 = action;
}

static void aTZN1_actor_move(ACTOR* actor, GAME* game){
    ZINNIA1_ACTOR* zinnia1 = (ZINNIA1_ACTOR*)actor;
    
    if(zinnia1->tools_class.work0 != zinnia1->current_id){
        aTZN1_setupAction(actor, zinnia1->tools_class.work0);
    }

    zinnia1->proc(actor);
}

static void aTZN1_actor_draw(ACTOR* actor, GAME* game){
    ZINNIA1_ACTOR* zinnia1 = (ZINNIA1_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(zinnia1->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&zinnia1->tools_class.matrix_work);
        Matrix_Position_Zero(&zinnia1->tools_class.actor_class.world.position);
        
        zinnia1->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_zinnia1_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }
}
