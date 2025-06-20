#include "ac_t_pistol.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTPT_actor_ct(ACTOR* actor, GAME* game);
static void aTPT_actor_move(ACTOR* actor, GAME* game);
static void aTPT_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Pistol_Profile = {
    mAc_PROFILE_T_PISTOL,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TOOLS,
    sizeof(PISTOL_ACTOR),
    &aTPT_actor_ct,
    NONE_ACTOR_PROC,
    &aTPT_actor_move,
    &aTPT_actor_draw,
    NULL
};

static void aTPT_setupAction(ACTOR* actor, int idx);

extern Gfx tol_kenjyu_1T_model[];

static void aTPT_actor_ct(ACTOR* actor, GAME* game){
    aTPT_setupAction(actor, 1);
}

static void aTPT_calc_scale(ACTOR* actor, int idx){

    static f32 aim[] = {1.0f, 0.0f};
    f32 pistol_scale = actor->scale.x;
    
    chase_f(&pistol_scale, aim[idx],0.05f);

    actor->scale.x = pistol_scale;
    actor->scale.y = pistol_scale;
    actor->scale.z = pistol_scale;
    
}

static void aTPT_takeout(ACTOR* actor){

    aTPT_calc_scale(actor, 0);
}

static void aTPT_putaway(ACTOR* actor){

    aTPT_calc_scale(actor, 1);
}

static void aTPT_destruct(ACTOR* actor){

    Actor_delete(actor);
}

static void aTPT_setupAction(ACTOR* actor, int idx){
    PISTOL_ACTOR* pistol = (PISTOL_ACTOR*)actor;

    static PISTOL_PROC process[] = {(PISTOL_PROC)none_proc1, aTPT_takeout,aTPT_putaway,aTPT_destruct,
    (PISTOL_PROC)none_proc1,NULL};
    static f32 start_scale[] = {0.0f, 0.0f, 1.0f,1.0f,1.0f,0.0f,0.0f};
    f32 scale;

    pistol->proc = process[idx];
    pistol->current_id = idx; 
    pistol->tools_class.work0 = idx;

    scale = start_scale[idx];
    pistol->tools_class.actor_class.scale.x = scale;
    pistol->tools_class.actor_class.scale.y = scale;
    pistol->tools_class.actor_class.scale.z = scale;
    
}

static void aTPT_actor_move(ACTOR* actor, GAME* game){
    PISTOL_ACTOR* pistol = (PISTOL_ACTOR*)actor;
    
    int t = pistol->tools_class.work0;
    if(t!= pistol->current_id){
        aTPT_setupAction(actor, t);
    }
    pistol->proc(actor);
}

static void aTPT_actor_draw(ACTOR* actor, GAME* game){
    PISTOL_ACTOR* pistol = (PISTOL_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Gfx* gfxp;

    OPEN_DISP(graph);

    if(pistol->tools_class.init_matrix == 1){
        Matrix_put(&pistol->tools_class.matrix_work);
        Matrix_Position_Zero(&pistol->tools_class.actor_class.world.position);
        pistol->tools_class.init_matrix = 0;
    }
    else{
        Matrix_translate(pistol->tools_class.actor_class.world.position.x, pistol->tools_class.actor_class.world.position.y, 
            pistol->tools_class.actor_class.world.position.z, FALSE);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    Matrix_scale(pistol->tools_class.actor_class.scale.x, pistol->tools_class.actor_class.scale.y, pistol->tools_class.actor_class.scale.z, MTX_MULT);
   _texture_z_light_fog_prim_npc(graph); 

    gfxp = NOW_POLY_OPA_DISP;
    gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxp++, tol_kenjyu_1T_model);
    SET_POLY_OPA_DISP(gfxp);

    CLOSE_DISP(graph);
        
}
