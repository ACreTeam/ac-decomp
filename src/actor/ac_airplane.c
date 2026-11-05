#include "ac_airplane.h"

#include "m_collision_bg.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "sys_matrix.h"
#include "sys_math3d.h"
#include "sys_math.h"
#include "libc64/qrand.h"
#include "m_controller.h"
#include "m_name_table.h"
#include "m_common_data.h"
#include "m_actor_shadow.h"
#include "m_rcp.h"

static void Airplane_Actor_ct(ACTOR* actor, GAME* game);
static void Airplane_Actor_dt(ACTOR* actor, GAME* game);
static void Airplane_Actor_move(ACTOR* actor, GAME* game);
static void Airplane_Actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE Airplane_Profile = {
    mAc_PROFILE_AIRPLANE,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    ETC_AIRPLANE,
    ACTOR_OBJ_BANK_AIRPLANE,
    sizeof(AIRPLANE_ACTOR),
    &Airplane_Actor_ct,
    &Airplane_Actor_dt,
    &Airplane_Actor_move,
    &Airplane_Actor_draw,
    NULL,
};

static void Airplane_Actor_ct(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;

    Shape_Info_init(actor, 0.0f, &mAc_ActorShadowEllipse, 6.5f, 6.5f);
    airplane->status = 5;

    airplane->speed = 6.2f;
    airplane->y_speed = 0.0f;
    airplane->actor_class.speed = airplane->speed;

    airplane->rotY = RAD2DEG(SHORTANGLE2RAD((f32)actor->world.angle.y));
    airplane->rotY_goal = airplane->rotY;
    airplane->rotY_min = airplane->rotY;
    airplane->rotZ = 0.0f;
    airplane->rotX = 0.0f;

    airplane->ground_timer = 0;
    airplane->wind_frame = 0;
    airplane->wind_change_frame = 0;
    airplane->wind = NULL;

    actor->world.position.y = mCoBG_GetBgY_AngleS_FromWpos(NULL, actor->world.position, -5.5f);
}

static void Airplane_Actor_dt(ACTOR* actor, GAME* game) {
}

extern Gfx glider_model[];

static void Airplane_Actor_draw(ACTOR* actor, GAME* game) {
    AIRPLANE_ACTOR* airplane = (AIRPLANE_ACTOR*)actor;

    if (airplane->status != aAp_STATUS_PLAYER_CATCH && airplane->status != aAp_STATUS_START_FLY_MOVE) {
        GRAPH* g = game->graph;

        _texture_z_light_fog_prim(g);
        Matrix_RotateX(RAD2SHORTANGLE(DEG2RAD(airplane->rotX)), MTX_MULT);
        Matrix_RotateZ(RAD2SHORTANGLE(DEG2RAD(airplane->rotZ)), MTX_MULT);
        Matrix_scale(50.0f, 50.0f, 50.0f, MTX_MULT);

        OPEN_DISP(g);
        gSPMatrix(NOW_POLY_OPA_DISP++, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(NOW_POLY_OPA_DISP++, glider_model);
        CLOSE_DISP(g);
    }
}

#include "../src/actor/ac_airplane_move.c_inc"