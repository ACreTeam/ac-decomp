#include "ac_t_utiwa.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_lib.h"
#include "m_rcp.h"

static void aTUT_actor_ct(ACTOR* actor, GAME* game);
static void aTUT_actor_move(ACTOR* actor, GAME* game);
static void aTUT_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Utiwa_Profile = {
    mAc_PROFILE_T_UTIWA,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_HANABI,
    sizeof(UTIWA_ACTOR),
    &aTUT_actor_ct,
    NONE_ACTOR_PROC,
    &aTUT_actor_move,
    &aTUT_actor_draw,
    NULL
};

extern Gfx main_utiwa1_model[];

static void aTUT_setupAction(ACTOR* actor, int idx);

static void aTUT_actor_ct(ACTOR* actor, GAME* game) {
    aTUT_setupAction(actor, 1);
}

static void aTUT_calc_scale(ACTOR* actor, int idx) {
    static f32 aim[] = {1.0f, 0.0f};
    f32 utiwa_scale = actor->scale.x;

    chase_f(&utiwa_scale, aim[idx], 0.05f);

    actor->scale.x = utiwa_scale;
    actor->scale.y = utiwa_scale;
    actor->scale.z = utiwa_scale;
}

static void aTUT_takeout(ACTOR* actor) {
    aTUT_calc_scale(actor, 0);
}

static void aTUT_putaway(ACTOR* actor) {
    aTUT_calc_scale(actor, 1);
}

static void aTUT_destruct(ACTOR* actor) {
    Actor_delete(actor);
}

static void aTUT_setupAction(ACTOR* actor, int idx) {
    static UTIWA_PROC process[] = {(UTIWA_PROC)none_proc1, aTUT_takeout, aTUT_putaway, aTUT_destruct,
    (UTIWA_PROC)none_proc1, NULL};

    static f32 start_scale[] = {0.0f, 0.0f, 1.0f,1.0f,1.0f,0.0f,0.0f};

    UTIWA_ACTOR* utiwa = (UTIWA_ACTOR*)actor;
    f32 scale;

    utiwa->proc = process[idx];
    utiwa->current_id = idx;
    utiwa->tools_class.work0 = idx;

    scale = start_scale[idx];
    utiwa->tools_class.actor_class.scale.x = scale;
    utiwa->tools_class.actor_class.scale.y = scale;
    utiwa->tools_class.actor_class.scale.z = scale;
}

static void aTUT_actor_move(ACTOR* actor, GAME* game) {
    UTIWA_ACTOR* utiwa = (UTIWA_ACTOR*)actor;

    int idx = utiwa->tools_class.work0;
    if (idx != utiwa->current_id) {
        aTUT_setupAction(actor, idx);
    }

    utiwa->proc(actor);
}

static void aTUT_actor_draw(ACTOR* actor, GAME* game) {
    UTIWA_ACTOR* utiwa = (UTIWA_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Gfx* gfxp;

    OPEN_DISP(graph);

    if(utiwa->tools_class.init_matrix == 1){
        Matrix_put(&utiwa->tools_class.matrix_work);
        Matrix_Position_Zero(&utiwa->tools_class.actor_class.world.position);
        utiwa->tools_class.init_matrix = 0;
    }
    else{
        Matrix_translate(utiwa->tools_class.actor_class.world.position.x, utiwa->tools_class.actor_class.world.position.y, 
            utiwa->tools_class.actor_class.world.position.z, FALSE);
            Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    Matrix_scale(utiwa->tools_class.actor_class.scale.x, utiwa->tools_class.actor_class.scale.y, utiwa->tools_class.actor_class.scale.z, MTX_MULT);
   _texture_z_light_fog_prim_npc(graph); 

    gfxp = NOW_POLY_OPA_DISP;
    gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph),G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxp++, main_utiwa1_model);
    SET_POLY_OPA_DISP(gfxp);

    CLOSE_DISP(graph);
}
