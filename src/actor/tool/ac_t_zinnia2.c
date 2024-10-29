#include "ac_t_zinnia2.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTZN2_actor_ct(ACTOR* actor, GAME* game);
static void aTZN2_actor_draw(ACTOR* actor, GAME* game);
static void aTZN2_actor_move(ACTOR* actor, GAME* game);
static void aTZN2_setupAction(ACTOR* actor, int action);

ACTOR_PROFILE T_Zinnia2_Profile = {
    mAc_PROFILE_T_ZINNIA2,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(ZINNIA2_ACTOR),
    &aTZN2_actor_ct,
    NONE_ACTOR_PROC,
    &aTZN2_actor_move,
    &aTZN2_actor_draw,
    NULL
};

extern Gfx crw_zinnia2_body_model[];

static void aTZN2_actor_ct(ACTOR* actor, GAME* game){
    aTZN2_setupAction(actor, 4);
}

static void aTZN2_destruct(ACTOR* actor){
    Actor_delete(actor);
}

static void aTZN2_setupAction(ACTOR* actor, int action){
    ZINNIA2_ACTOR* zinnia2 = (ZINNIA2_ACTOR*)actor;
    static ZINNIA2_PROC process[] = {
        (ZINNIA2_PROC)none_proc1, (ZINNIA2_PROC)none_proc1, (ZINNIA2_PROC)none_proc1, aTZN2_destruct,(ZINNIA2_PROC)none_proc1, NULL
    };
    
    zinnia2->proc = process[action];
    zinnia2->current_id = action;
    zinnia2->tools_class.work0 = action;
}

static void aTZN2_actor_move(ACTOR* actor, GAME* game){
    ZINNIA2_ACTOR* zinnia2 = (ZINNIA2_ACTOR*)actor;
    
    if(zinnia2->tools_class.work0 != zinnia2->current_id){
        aTZN2_setupAction(actor, zinnia2->tools_class.work0);
    }

    zinnia2->proc(actor);
}

static void aTZN2_actor_draw(ACTOR* actor, GAME* game){
    ZINNIA2_ACTOR* zinnia2 = (ZINNIA2_ACTOR*)actor;

    GRAPH* graph;
    Gfx* gfxp;

    if(zinnia2->tools_class.init_matrix == 1){
        graph = game->graph;
        
        OPEN_DISP(graph);
        
        Matrix_put(&zinnia2->tools_class.matrix_work);
        Matrix_Position_Zero(&zinnia2->tools_class.actor_class.world.position);
        
        zinnia2->tools_class.init_matrix = 0;
    
        _texture_z_light_fog_prim_npc(graph); 

        gfxp = NOW_POLY_OPA_DISP;
        gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfxp++, crw_zinnia2_body_model);
        SET_POLY_OPA_DISP(gfxp);
        
        CLOSE_DISP(graph);
    }
}
