#include "ef_room_sunshine.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"

void Ef_Room_Sunshine_actor_ct(ACTOR* actor, GAME* play);
void Ef_Room_SunshineL_actor_move(ACTOR* actor, GAME* play);
void Ef_Room_SunshineL_actor_draw(ACTOR* actor, GAME* play);
void Ef_Room_SunshineR_actor_move(ACTOR* actor, GAME* play);
void Ef_Room_SunshineR_actor_draw(ACTOR* actor, GAME* play);

extern Gfx light_floor01_mode[];
extern Vtx light_floorL01_vtx[];
extern Vtx light_floorR01_vtx[];
extern Gfx light_shine01_mode[];
extern Vtx light_shineL01_vtx[];
extern Vtx light_shineR01_vtx[];

ACTOR_PROFILE Room_Sunshine_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_ROOM_SUNSHINE,
    sizeof(ROOMSUNSHINE_ACTOR),
    Ef_Room_Sunshine_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_SunshineR_actor_move,
    Ef_Room_SunshineR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_actor_ct(ACTOR* actor, GAME* game) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;
    xyz_t pos;
    xyz_t pos2;
    xyz_t pos3;

    sunshine->unk_174 = 0;

    if (sunshine->actor_class.actor_specific == 0) {
        sunshine->actor_class.mv_proc = Ef_Room_SunshineL_actor_move;
        sunshine->actor_class.dw_proc = Ef_Room_SunshineL_actor_draw;
    } else {
        sunshine->actor_class.world.position.x -= 1.0f;
    }

    sunshine->actor_class.world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos(sunshine->actor_class.world.position, 0.0f);

    sunshine->actor_class.scale.x = 1.0f;
    sunshine->actor_class.scale.y = 1.0f;
    sunshine->actor_class.scale.z = 1.0f;

    switch (sunshine->actor_class.actor_specific) {

        case 2:

            sunshine->actor_class.mv_proc = Ef_Room_SunshineL_actor_move;
            sunshine->actor_class.dw_proc = Ef_Room_SunshineL_actor_draw;
            sunshine->actor_class.world.position.x += 5.0f;
            sunshine->actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(sunshine->actor_class.world.position, 0.0f);
            sunshine->actor_class.world.position.x -= 6.0f;
            break;

        case 3:
            sunshine->actor_class.world.position.x -= 5.0f;
            sunshine->actor_class.world.position.y =
                1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(sunshine->actor_class.world.position, 0.0f);
            sunshine->actor_class.world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine(int flag, int sec) {

    if (flag == 0) {
        return 1.5f * sin_s((sec << 14) / 28800.0f);
    } else {
        return 1.5f * sin_s((sec << 14) / 14400.0f);
    }
}

static int calc_alpha_Ef_Room_Sunshine() {
    f32 ret;
    int sec;

    if (Common_Get(time.now_sec) < 14400) {
        ret = (120.0f + GETREG(TAKREG, 30)) * ((14400 - Common_Get(time.now_sec)) / 14400.0f);
    } else if (Common_Get(time.now_sec) < 72000) {
        sec = (Common_Get(time.now_sec) - 43200) >= 0 ? (Common_Get(time.now_sec) - 43200U)
                                                      : -(Common_Get(time.now_sec) - 43200U);

        ret = 255.0f * ((28800 - sec) / 28800.0f);
    } else {
        ret = (120.0f + GETREG(TAKREG, 30)) * ((14400 - (86400 - Common_Get(time.now_sec))) / 14400.0f);
    }

    if ((Common_Get(weather) == 1) || (Common_Get(weather) == 2)) {
        ret *= 0.6f;
    }

    return (u8)ret;
}

static void Ef_Room_SunshineL_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;

    if (Common_Get(time.now_sec) < 14400) {
        sunshine->actor_class.scale.x = calc_scale_Ef_Room_Sunshine(1, Common_Get(time.now_sec));
    } else if ((Common_Get(time.now_sec) >= 43200) && (Common_Get(time.now_sec) < 72000)) {
        sunshine->actor_class.scale.x = calc_scale_Ef_Room_Sunshine(0, Common_Get(time.now_sec) - 43200);
    } else {
        sunshine->actor_class.scale.x = 0.0f;
    }
}

static void Ef_Room_SunshineR_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 43200)) {
        sunshine->actor_class.scale.x = calc_scale_Ef_Room_Sunshine(0, 43200 - Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= 72000) {
        sunshine->actor_class.scale.x = calc_scale_Ef_Room_Sunshine(1, 86400 - Common_Get(time.now_sec));
    } else {
        sunshine->actor_class.scale.x = 0.0f;
    }
}

static void setup_mode_Ef_Room_Sunshine(ACTOR* actor, GAME_PLAY* play) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;
    u8* color;
    f32 alpha;

    GRAPH* graph = play->game.graph;

    OPEN_DISP(graph);

    Matrix_translate(sunshine->actor_class.world.position.x, 0.1f + sunshine->actor_class.world.position.y,
                     sunshine->actor_class.world.position.z, MTX_LOAD);
    Matrix_scale(sunshine->actor_class.scale.x, sunshine->actor_class.scale.y, sunshine->actor_class.scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_XLU_DISP);

    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 72000)) {
        color = play->kankyo.base_light.sun_color_window;
    } else {
        color = play->kankyo.base_light.moon_color_window;
    }

    alpha = (u8)calc_alpha_Ef_Room_Sunshine() * mKK_windowlight_alpha_get();

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 0, color[0], color[1], color[2], (int)(alpha));
    CLOSE_DISP(graph);
}

static void Ef_Room_SunshineL_actor_draw(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    GRAPH* graph;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }
    graph = play->game.graph;
    setup_mode_Ef_Room_Sunshine(actor, play);

    OPEN_DISP(graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, light_floor01_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_floorL01_vtx);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_shine01_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_shineL01_vtx);

    CLOSE_DISP(graph);
}

static void Ef_Room_SunshineR_actor_draw(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    GRAPH* graph;

    if ((mKK_windowlight_alpha_get() < 9.99999974738e-05f) || (actor->scale.x == 0.0f)) {
        return;
    }
    graph = play->game.graph;
    setup_mode_Ef_Room_Sunshine(actor, play);

    OPEN_DISP(graph);

    gSPDisplayList(NEXT_POLY_XLU_DISP, light_floor01_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_floorR01_vtx);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_shine01_mode);
    gSPDisplayList(NEXT_POLY_XLU_DISP, light_shineR01_vtx);

    CLOSE_DISP(graph);
}
