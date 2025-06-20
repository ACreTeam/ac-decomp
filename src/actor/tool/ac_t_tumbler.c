#include "ac_t_tumbler.h"

#include "m_name_table.h"
#include "sys_matrix.h"
#include "m_rcp.h"

ACTOR_PROFILE T_Tumbler_Profile = {
    mAc_PROFILE_T_TUMBLER,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_TUMBLER,
    sizeof(TOOL_TUMBLER_ACTOR),
    &aTTB_actor_ct,
    NONE_ACTOR_PROC,
    &aTTB_actor_move,
    &aTTB_actor_draw,
    NULL,
};

static void aTTB_setupAction(TOOL_TUMBLER_ACTOR* tumbler_actor, int action);

extern void aTTB_actor_ct(ACTOR* actorx, GAME* game) {
    TOOL_TUMBLER_ACTOR* tumbler = (TOOL_TUMBLER_ACTOR*)actorx;

    aTTB_setupAction(tumbler, 1);
}

static void aTTB_calc_scale(TOOL_TUMBLER_ACTOR* tumbler_actor, int goal_idx) {
    static f32 aim[] = { 1.0f, 0.0f };

    f32 scale = tumbler_actor->tools_class.actor_class.scale.x;

    chase_f(&scale, aim[goal_idx], 0.05f);
    tumbler_actor->tools_class.actor_class.scale.x = scale;
    tumbler_actor->tools_class.actor_class.scale.y = scale;
    tumbler_actor->tools_class.actor_class.scale.z = scale;
}

static void aTTB_takeout(TOOL_TUMBLER_ACTOR* tumbler_actor) {
    aTTB_calc_scale(tumbler_actor, 0);
}

static void aTTB_putaway(TOOL_TUMBLER_ACTOR* tumbler_actor) {
    aTTB_calc_scale(tumbler_actor, 1);
}

static void aTTB_destruct(TOOL_TUMBLER_ACTOR* tumbler_actor) {
    Actor_delete((ACTOR*)tumbler_actor);
}

static void aTTB_setupAction(TOOL_TUMBLER_ACTOR* tumbler_actor, int action) {
    static aTTB_ACTION_PROC process[] = { (aTTB_ACTION_PROC)&none_proc1, &aTTB_takeout, &aTTB_putaway, &aTTB_destruct,
                                          (aTTB_ACTION_PROC)&none_proc1, NULL };

    static f32 start_scale[] = { 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };

    f32 scale;

    tumbler_actor->action_proc = process[action];
    tumbler_actor->action = action;

    scale = start_scale[action];
    tumbler_actor->tools_class.actor_class.scale.x = scale;
    tumbler_actor->tools_class.actor_class.scale.y = scale;
    tumbler_actor->tools_class.actor_class.scale.z = scale;
}

extern void aTTB_actor_move(ACTOR* actorx, GAME* game) {
    TOOL_TUMBLER_ACTOR* tumbler = (TOOL_TUMBLER_ACTOR*)actorx;

    if (tumbler->tools_class.work0 != tumbler->action) {
        aTTB_setupAction(tumbler, tumbler->tools_class.work0);
    }

    (*tumbler->action_proc)(tumbler);
}

extern Gfx tol_kamicup_1T_model[];

extern void aTTB_actor_draw(ACTOR* actorx, GAME* game) {
    TOOL_TUMBLER_ACTOR* tumbler = (TOOL_TUMBLER_ACTOR*)actorx;
    GRAPH* graph = game->graph;

    Gfx* gfx;

    if (tumbler->tools_class.init_matrix == TRUE) {
        Matrix_put(&tumbler->tools_class.matrix_work);
        Matrix_Position_Zero(&actorx->world.position);
        tumbler->tools_class.init_matrix = FALSE;
    } else {
        Matrix_translate(actorx->world.position.x, actorx->world.position.y, actorx->world.position.z, MTX_LOAD);
        Matrix_scale(0.01f, 0.01f, 0.01f, MTX_MULT);
    }

    Matrix_scale(actorx->scale.x, actorx->scale.y, actorx->scale.z, MTX_MULT);
    _texture_z_light_fog_prim_npc(graph);

    OPEN_DISP(graph);
    gfx = NOW_POLY_OPA_DISP;

    gSPMatrix(gfx++, _Matrix_to_Mtx_new(graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, tol_kamicup_1T_model);

    SET_POLY_OPA_DISP(gfx);
    CLOSE_DISP(graph);
}
