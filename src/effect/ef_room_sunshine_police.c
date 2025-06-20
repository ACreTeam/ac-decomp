#include "ef_room_sunshine_police.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"

static void Ef_Room_Sunshine_Police_actor_ct(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_Police_actor_dt(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PoliceL_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PoliceL_actor_move(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PoliceR_actor_draw(ACTOR* actor, GAME* play);
static void Ef_Room_Sunshine_PoliceR_actor_move(ACTOR* actor, GAME* play);

extern Gfx obj_koban_shine_modelT[];

ACTOR_PROFILE Room_Sunshine_Police_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE_POLICE,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_EF_POLICE,
    sizeof(ROOMSUNSHINEPOLICE_ACTOR),
    Ef_Room_Sunshine_Police_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_Sunshine_PoliceR_actor_move,
    Ef_Room_Sunshine_PoliceR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_Police_actor_ct(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOLICE_ACTOR* police = (ROOMSUNSHINEPOLICE_ACTOR*)actor;
    xyz_t pos;
    xyz_t pos2;
    xyz_t pos3;

    police->ef_sunshine_class.unk_174 = 0;

    if (police->ef_sunshine_class.actor_class.actor_specific == 0) {
        police->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_PoliceL_actor_move;
        police->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_PoliceL_actor_draw;
    } else {
        police->ef_sunshine_class.actor_class.world.position.x -= 1.0f;
    }

    police->ef_sunshine_class.actor_class.world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos(police->ef_sunshine_class.actor_class.world.position, 0.0f);

    police->ef_sunshine_class.actor_class.scale.x = 0.01f;
    police->ef_sunshine_class.actor_class.scale.y = 0.01f;
    police->ef_sunshine_class.actor_class.scale.z = 0.01f;

    switch (police->ef_sunshine_class.actor_class.actor_specific) {

        case 2:

            police->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_PoliceL_actor_move;
            police->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_PoliceL_actor_draw;
            police->ef_sunshine_class.actor_class.world.position.x += 5.0f;
            police->ef_sunshine_class.actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(police->ef_sunshine_class.actor_class.world.position, 0.0f) -
                40.0f;
            police->ef_sunshine_class.actor_class.world.position.x -= 6.0f;
            break;

        case 3:
            police->ef_sunshine_class.actor_class.world.position.x -= 5.0f;
            police->ef_sunshine_class.actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(police->ef_sunshine_class.actor_class.world.position, 0.0f) -
                40.0f;
            police->ef_sunshine_class.actor_class.world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine_Police(int flag, int sec) {

    if (flag == 0) {
        return 0.01f * (1.5f * sin_s((sec << 14) / 28800.0f));
    } else {
        return 0.01f * (1.5f * sin_s((sec << 14) / 14400.0f));
    }
}

static int calc_alpha_Ef_Room_SunshinePolice() {
    f32 ret;
    int sec;

    if (Common_Get(time.now_sec) < 14400) {
        ret = 120.0f * ((14400 - Common_Get(time.now_sec)) / 14400.0f);
    } else if (Common_Get(time.now_sec) < 72000) {
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

static void Ef_Room_Sunshine_PoliceL_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOLICE_ACTOR* police = (ROOMSUNSHINEPOLICE_ACTOR*)actor;

    if (Common_Get(time.now_sec) < 14400) {
        police->ef_sunshine_class.actor_class.scale.x = calc_scale_Ef_Room_Sunshine_Police(1, Common_Get(time.now_sec));
    } else if ((Common_Get(time.now_sec) >= 43200) && (Common_Get(time.now_sec) < 72000)) {
        police->ef_sunshine_class.actor_class.scale.x =
            calc_scale_Ef_Room_Sunshine_Police(0, Common_Get(time.now_sec) - 43200);
    } else {
        police->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }
}

static void Ef_Room_Sunshine_PoliceR_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEPOLICE_ACTOR* police = (ROOMSUNSHINEPOLICE_ACTOR*)actor;

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 43200)) {
        police->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Police(0, 43200 - Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= 72000) {
        police->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Police(1, 86400 - Common_Get(time.now_sec));
    } else {
        police->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }
}

static int cull_check_from_camera(ACTOR* actor, GAME_PLAY* play, int flag) {

    if (((play->camera.lookat.eye.x >= actor->world.position.x) && (flag == 1)) ||
        (play->camera.lookat.eye.x <= actor->world.position.x) && (flag == 0)) {
        return 1;
    }
    return 0;
}

static void setup_mode_Ef_Room_Sunshine_Police(ACTOR* actor, GAME_PLAY* play) {
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

    calc = ((u8)calc_alpha_Ef_Room_SunshinePolice() * mKK_windowlight_alpha_get());

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, calc, color[0], color[1], color[2], 255);
    CLOSE_DISP(graph);
}

static void Ef_Room_Sunshine_PoliceL_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }

    if (cull_check_from_camera(actor, play, 0) == 0) {
        graph = play->game.graph;
        setup_mode_Ef_Room_Sunshine_Police(actor, play);

        OPEN_DISP(graph);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_koban_shine_modelT);

        CLOSE_DISP(graph);
    }
}

static void Ef_Room_Sunshine_PoliceR_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;
    GAME_PLAY* play = (GAME_PLAY*)game;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }

    if (cull_check_from_camera(actor, play, 1) == 0) {
        graph = play->game.graph;
        setup_mode_Ef_Room_Sunshine_Police(actor, play);

        OPEN_DISP(graph);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_koban_shine_modelT);

        CLOSE_DISP(graph);
    }
}
