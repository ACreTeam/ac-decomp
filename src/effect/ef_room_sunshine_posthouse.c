#include "ef_room_sunshine_posthouse.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"
#include "libultra/libultra.h"

static void Ef_Room_Sunshine_Posthouse_actor_ct(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_Posthouse_actor_dt(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PosthouseL_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PosthouseL_actor_move(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PosthouseR_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PosthouseR_actor_move(ACTOR* actor, GAME* play);

extern Gfx obj_yubinkyoku_shine_modelT[];

ACTOR_PROFILE Room_Sunshine_Posthouse_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE_POSTHOUSE,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_POSTHOUSE,
    sizeof(ROOMSUNSHINEPOSTHOUSE_ACTOR),
    Ef_Room_Sunshine_Posthouse_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_Sunshine_PosthouseR_actor_move,
    Ef_Room_Sunshine_PosthouseR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_Posthouse_actor_ct(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOSTHOUSE_ACTOR* posthouse = (ROOMSUNSHINEPOSTHOUSE_ACTOR*)actor;
    xyz_t pos;
    xyz_t pos2;
    xyz_t pos3;

    posthouse->ef_sunshine_class.unk_174 = 0;

    if (posthouse->ef_sunshine_class.actor_class.actor_specific == 0) {
        posthouse->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_PosthouseL_actor_move;
        posthouse->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_PosthouseL_actor_draw;
    } else {
        posthouse->ef_sunshine_class.actor_class.world.position.x -= 1.0f;
    }

    posthouse->ef_sunshine_class.actor_class.world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos(posthouse->ef_sunshine_class.actor_class.world.position, 0.0f);

    posthouse->ef_sunshine_class.actor_class.scale.x = 0.05f;
    posthouse->ef_sunshine_class.actor_class.scale.y = 0.05f;
    posthouse->ef_sunshine_class.actor_class.scale.z = 0.05f;

    switch (posthouse->ef_sunshine_class.actor_class.actor_specific) {

        case 2:

            posthouse->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_PosthouseL_actor_move;
            posthouse->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_PosthouseL_actor_draw;
            posthouse->ef_sunshine_class.actor_class.world.position.x += 5.0f;
            posthouse->ef_sunshine_class.actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(posthouse->ef_sunshine_class.actor_class.world.position, 0.0f);
            posthouse->ef_sunshine_class.actor_class.world.position.x -= 6.0f;
            break;

        case 3:
            posthouse->ef_sunshine_class.actor_class.world.position.x -= 5.0f;
            posthouse->ef_sunshine_class.actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(posthouse->ef_sunshine_class.actor_class.world.position, 0.0f);
            posthouse->ef_sunshine_class.actor_class.world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine_Posthouse(int flag, int sec) {

    if (flag == 0) {
        return 0.05f * (1.5f * sin_s((sec << 14) / 28800.0f));
    } else {
        return 0.05f * (1.5f * sin_s((sec << 14) / 14400.0f));
    }
}

static int calc_alpha_Ef_Room_Sunshine_Posthouse() {
    f32 ret;
    int sec;

    if (Common_Get(time.now_sec) < 14400) {
        ret = 120.0f * ((14400 - Common_Get(time.now_sec)) / 14400.0f);
    } else if (Common_Get(time.now_sec) < 72000) {
        // any other number matches codegen, but 43200 breaks
        sec = (Common_Get(time.now_sec) - 43200) >= 0 ? (Common_Get(time.now_sec) - 43200U)
                                                      : -(Common_Get(time.now_sec) - 43200U);

        ret = 255.0f * ((28800 - sec) / 28800.0f);
    } else {
        ret = 120.0f * ((14400 - (86400 - Common_Get(time.now_sec))) / 14400.0f);
    }

    if ((Common_Get(weather) == 1) || (Common_Get(weather) == 2)) {
        ret *= 0.6f;
    }

    return (u8)ret;
}

static void Ef_Room_Sunshine_PosthouseL_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOSTHOUSE_ACTOR* posthouse = (ROOMSUNSHINEPOSTHOUSE_ACTOR*)actor;

    if (Common_Get(time.now_sec) < 14400) {
        posthouse->ef_sunshine_class.actor_class.scale.x =
            calc_scale_Ef_Room_Sunshine_Posthouse(1, Common_Get(time.now_sec));
    } else if ((Common_Get(time.now_sec) >= 43200) && (Common_Get(time.now_sec) < 72000)) {
        posthouse->ef_sunshine_class.actor_class.scale.x =
            calc_scale_Ef_Room_Sunshine_Posthouse(0, Common_Get(time.now_sec) - 43200);
    } else {
        posthouse->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }
}

static void Ef_Room_Sunshine_PosthouseR_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOSTHOUSE_ACTOR* posthouse = (ROOMSUNSHINEPOSTHOUSE_ACTOR*)actor;

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 43200)) {
        posthouse->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Posthouse(0, 43200 - Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= 72000) {
        posthouse->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Posthouse(1, 86400 - Common_Get(time.now_sec));
    } else {
        posthouse->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }
}

static void setup_mode_Ef_Room_Sunshine_Posthouse(ACTOR* actor, GAME_PLAY* play) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;
    u8* color;
    int calc;

    GRAPH* graph = play->game.graph;

    OPEN_DISP(graph);

    Matrix_translate(sunshine->actor_class.world.position.x, sunshine->actor_class.world.position.y,
                     sunshine->actor_class.world.position.z, 0);
    Matrix_scale(sunshine->actor_class.scale.x, sunshine->actor_class.scale.y, sunshine->actor_class.scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_XLU_DISP);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 72000)) {
        color = play->kankyo.base_light.sun_color_window;
    } else {
        color = play->kankyo.base_light.moon_color_window;
    }

    calc = ((u8)calc_alpha_Ef_Room_Sunshine_Posthouse() * mKK_windowlight_alpha_get());

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, calc, color[0], color[1], color[2], 255);
    CLOSE_DISP(graph);
}

static void Ef_Room_Sunshine_PosthouseL_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }
    graph = play->game.graph;
    setup_mode_Ef_Room_Sunshine_Posthouse(actor, play);

    OPEN_DISP(graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, obj_yubinkyoku_shine_modelT);

    CLOSE_DISP(graph);
}

static void Ef_Room_Sunshine_PosthouseR_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }

    graph = play->game.graph;
    setup_mode_Ef_Room_Sunshine_Posthouse(actor, play);

    OPEN_DISP(graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, obj_yubinkyoku_shine_modelT);

    CLOSE_DISP(graph);
}
