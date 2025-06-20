#include "ac_t_hanabi.h"

#include "m_rcp.h"
#include "m_name_table.h"
#include "sys_matrix.h"

static void aTHB_actor_ct(ACTOR* actor, GAME* game);
static void aTHB_actor_dt(ACTOR* actor, GAME* game);
static void aTHB_actor_move(ACTOR* actor, GAME* game);
static void aTHB_actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE T_Hanabi_Profile = { mAc_PROFILE_T_HANABI,
                                   ACTOR_PART_BG,
                                   ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
                                   EMPTY_NO,
                                   ACTOR_OBJ_BANK_HANABI,
                                   sizeof(HANABI_ACTOR),
                                   &aTHB_actor_ct,
                                   &aTHB_actor_dt,
                                   &aTHB_actor_move,
                                   &aTHB_actor_draw,
                                   NULL };

static void aTHB_setupAction(ACTOR* actor, int idx);

extern Gfx main_utiwa1_model[];

static void aTHB_actor_ct(ACTOR* actor, GAME* game) {
    aTHB_setupAction(actor, 1);
}

static void aTHB_actor_dt(ACTOR* actor, GAME* game) {
}

static void aTHB_calc_scale(ACTOR* actor, int idx) {

    static f32 aim[] = { 1.0f, 0.0f };
    f32 hanabi_scale = actor->scale.x;

    chase_f(&hanabi_scale, aim[idx], 0.05f);

    actor->scale.x = hanabi_scale;
    actor->scale.y = hanabi_scale;
    actor->scale.z = hanabi_scale;
}

static void aTHB_takeout(ACTOR* actor) {

    aTHB_calc_scale(actor, 0);
}

static void aTHB_putaway(ACTOR* actor) {

    aTHB_calc_scale(actor, 1);
}

static void aTHB_destruct(ACTOR* actor) {

    Actor_delete(actor);
}

static void aTHB_setupAction(ACTOR* actor, int idx) {
    HANABI_ACTOR* hanabi = (HANABI_ACTOR*)actor;

    static HANABI_PROC process[] = { (HANABI_PROC)none_proc1, aTHB_takeout, aTHB_putaway, aTHB_destruct,
                                     (HANABI_PROC)none_proc1, NULL };
    static f32 start_scale[] = { 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f };
    f32 scale;

    hanabi->proc = process[idx];
    hanabi->current_id = idx;
    hanabi->tools_class.work0 = idx;

    scale = start_scale[idx];
    hanabi->tools_class.actor_class.scale.x = scale;
    hanabi->tools_class.actor_class.scale.y = scale;
    hanabi->tools_class.actor_class.scale.z = scale;
}

static void aTHB_actor_move(ACTOR* actor, GAME* game) {
    HANABI_ACTOR* hanabi = (HANABI_ACTOR*)actor;

    int t = hanabi->tools_class.work0;
    if (t != hanabi->current_id) {
        aTHB_setupAction(actor, t);
    }
    hanabi->proc(actor);
}

static void aTHB_actor_draw(ACTOR* actor, GAME* game) {
    HANABI_ACTOR* hanabi = (HANABI_ACTOR*)actor;

    GRAPH* graph = game->graph;
    Gfx* gfxp;

    OPEN_DISP(graph);

    if (hanabi->tools_class.init_matrix == 1) {
        Matrix_put(&hanabi->tools_class.matrix_work);
        Matrix_Position_Zero(&hanabi->tools_class.actor_class.world.position);
        hanabi->tools_class.init_matrix = 0;
    } else {
        Matrix_translate(hanabi->tools_class.actor_class.world.position.x,
                         hanabi->tools_class.actor_class.world.position.y,
                         hanabi->tools_class.actor_class.world.position.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    Matrix_scale(hanabi->tools_class.actor_class.scale.x, hanabi->tools_class.actor_class.scale.y,
                 hanabi->tools_class.actor_class.scale.z, MTX_MULT);
    _texture_z_light_fog_prim_npc(graph);

    gfxp = NOW_POLY_OPA_DISP;
    gSPMatrix(gfxp++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfxp++, main_utiwa1_model);
    SET_POLY_OPA_DISP(gfxp);

    CLOSE_DISP(graph);
}
