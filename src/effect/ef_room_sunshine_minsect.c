#include "ef_room_sunshine_minsect.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"
#include "m_rcp.h"

void Ef_Room_Sunshine_Minsect_actor_ct(ACTOR* actor, GAME* play);
void Ef_Room_Sunshine_Minsect_actor_dt(ACTOR* actor, GAME* play);
void Ef_Room_Sunshine_MinsectL_actor_draw(ACTOR* actor, GAME* play);
void Ef_Room_Sunshine_MinsectL_actor_move(ACTOR* actor, GAME* play);
void Ef_Room_Sunshine_MinsectR_actor_draw(ACTOR* actor, GAME* play);
void Ef_Room_Sunshine_MinsectR_actor_move(ACTOR* actor, GAME* play);

extern Gfx rom_museum4_ue_model[];
extern Gfx rom_museum4_model[];
extern Gfx obj_museum4_shine_1T_model[];
extern Gfx obj_museum4_shine_2T_model[];

u8 draw_status;

ACTOR_PROFILE Room_Sunshine_Minsect_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE_MINSECT,
    ACTOR_PART_ITEM,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_EF_MINSECT,
    sizeof(ROOMSUNSHINEMINSECT_ACTOR),
    Ef_Room_Sunshine_Minsect_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_Sunshine_MinsectR_actor_move,
    Ef_Room_Sunshine_MinsectR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_Minsect_actor_ct(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEMINSECT_ACTOR* minsect = (ROOMSUNSHINEMINSECT_ACTOR*)actor;
    xyz_t pos;

    minsect->ef_sunshine_class.unk_174 = 0;
    draw_status = 0;
    if (minsect->ef_sunshine_class.actor_class.actor_specific == 0) {
        minsect->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_MinsectL_actor_move;
        minsect->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_MinsectL_actor_draw;
    } else {
        minsect->ef_sunshine_class.actor_class.world.position.x -= 1.0f;
    }

    minsect->ef_sunshine_class.actor_class.world.position.y =
        mCoBG_GetBgY_OnlyCenter_FromWpos(minsect->ef_sunshine_class.actor_class.world.position, 0.0f);

    minsect->ef_sunshine_class.actor_class.scale.x = 0.01f;
    minsect->ef_sunshine_class.actor_class.scale.y = 0.01f;
    minsect->ef_sunshine_class.actor_class.scale.z = 0.01f;
    minsect->ef_sunshine_class.actor_class.cull_radius = 10000.0f;

    switch (minsect->ef_sunshine_class.actor_class.actor_specific) {

        case 2:

            minsect->ef_sunshine_class.actor_class.mv_proc = Ef_Room_Sunshine_MinsectL_actor_move;
            minsect->ef_sunshine_class.actor_class.dw_proc = Ef_Room_Sunshine_MinsectL_actor_draw;
            minsect->ef_sunshine_class.actor_class.world.position.x += 5.0f;
            minsect->ef_sunshine_class.actor_class.world.position.x -= 6.0f;
            break;

        case 3:
            minsect->ef_sunshine_class.actor_class.world.position.x -= 5.0f;
            minsect->ef_sunshine_class.actor_class.world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine_Minsect(int flag, int sec) {

    if (flag == 0) {
        return 0.01f * (1.5f * sin_s((sec << 14) / 28800.0f));
    } else {
        return 0.01f * (1.5f * sin_s((sec << 14) / 14400.0f));
    }
}

static int calc_alpha_Ef_Room_SunshineMinsect() {
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

static void Ef_Room_Sunshine_MinsectL_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEMINSECT_ACTOR* minsect = (ROOMSUNSHINEMINSECT_ACTOR*)actor;

    if (Common_Get(time.now_sec) < 14400) {
        minsect->ef_sunshine_class.actor_class.scale.x =
            calc_scale_Ef_Room_Sunshine_Minsect(1, Common_Get(time.now_sec));
    } else if ((Common_Get(time.now_sec) >= 43200) && (Common_Get(time.now_sec) < 72000)) {
        minsect->ef_sunshine_class.actor_class.scale.x =
            calc_scale_Ef_Room_Sunshine_Minsect(0, Common_Get(time.now_sec) - 43200);
    } else {
        minsect->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }

    minsect->ef_sunshine_class.actor_class.world.position.y = minsect->ef_sunshine_class.actor_class.home.position.y;
    minsect->ef_sunshine_class.actor_class.world.position.y += 0.01f * GETREG(TAKREG, 64);
}

static void Ef_Room_Sunshine_MinsectR_actor_move(ACTOR* actor, GAME* game) {
    ROOMSUNSHINEMINSECT_ACTOR* minsect = (ROOMSUNSHINEMINSECT_ACTOR*)actor;

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 43200)) {
        minsect->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Minsect(0, 43200 - Common_Get(time.now_sec));
    } else if (Common_Get(time.now_sec) >= 72000) {
        minsect->ef_sunshine_class.actor_class.scale.x =
            -calc_scale_Ef_Room_Sunshine_Minsect(1, 86400 - Common_Get(time.now_sec));
    } else {
        minsect->ef_sunshine_class.actor_class.scale.x = 0.0f;
    }
    minsect->ef_sunshine_class.actor_class.world.position.y = minsect->ef_sunshine_class.actor_class.home.position.y;
    minsect->ef_sunshine_class.actor_class.world.position.y += 0.01f * GETREG(TAKREG, 64);
}

static void setup_mode_Ef_Room_Sunshine_Minsect(ACTOR* actor, GAME_PLAY* play) {
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

    calc = ((u8)calc_alpha_Ef_Room_SunshineMinsect() * mKK_windowlight_alpha_get());

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, calc, color[0], color[1], color[2], 75);
    CLOSE_DISP(graph);
}

static void setup_mode_Ef_Room_Sunshine_Minsect_decal(ACTOR* actor, GAME_PLAY* play) {
    ROOMSUNSHINE_ACTOR* sunshine = (ROOMSUNSHINE_ACTOR*)actor;
    u8* color;
    int calc;

    GRAPH* graph = play->game.graph;

    OPEN_DISP(graph);

    Matrix_translate(sunshine->actor_class.world.position.x, sunshine->actor_class.world.position.y,
                     sunshine->actor_class.world.position.z, 0);
    Matrix_scale(sunshine->actor_class.scale.x, sunshine->actor_class.scale.y, sunshine->actor_class.scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_OPA_DISP);

    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if ((Common_Get(time.now_sec) >= 14400) && (Common_Get(time.now_sec) < 72000)) {
        color = play->kankyo.base_light.sun_color_window;
    } else {
        color = play->kankyo.base_light.moon_color_window;
    }

    calc = ((u8)calc_alpha_Ef_Room_SunshineMinsect() * mKK_windowlight_alpha_get());

    gDPSetPrimColor(NEXT_POLY_OPA_DISP, 0, calc, color[0], color[1], color[2], 75);
    CLOSE_DISP(graph);
}

static void BG_draw_Minsect(ACTOR* actor, GAME_PLAY* play) {
    GRAPH* graph;

    if (!(draw_status & 4)) {
        draw_status |= 4;
    }

    if ((draw_status & 1) && (draw_status & 2)) {
        draw_status = 0;
    }

    graph = play->game.graph;
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_LOAD);
    Global_kankyo_set_room_prim((GAME*)play);
    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_museum4_ue_model);

    CLOSE_DISP(graph);
}

static void BG_draw_Minsect_niwa(ACTOR* actor, GAME_PLAY* play) {
    GRAPH* graph;

    graph = play->game.graph;
    Matrix_scale(0.0625f, 0.0625f, 0.0625f, MTX_LOAD);
    Global_kankyo_set_room_prim((GAME*)play);
    OPEN_DISP(graph);
    gSPMatrix(NEXT_POLY_OPA_DISP, _Matrix_to_Mtx_new(play->game.graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_OPA_DISP, rom_museum4_model);

    CLOSE_DISP(graph);
}

static void Ef_Room_Sunshine_MinsectL_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_shadow(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    draw_status |= 1;

    if (mKK_windowlight_alpha_get() < 9.99999974738e-05f) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
            BG_draw_Minsect(actor, (GAME_PLAY*)game);
        }
    } else if (0.0f == actor->scale.x) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
            BG_draw_Minsect(actor, (GAME_PLAY*)game);
        }
    } else {
        s16 reg;
        graph = game->graph;

        BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
        setup_mode_Ef_Room_Sunshine_Minsect(actor, (GAME_PLAY*)game);
        OPEN_DISP(graph);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_shine_1T_model);
        setup_mode_Ef_Room_Sunshine_Minsect_decal(actor, (GAME_PLAY*)game);

        if (REGADDR(TAKREG, 0) == 0) {
            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_museum4_shine_2T_model);
        }
        BG_draw_Minsect(actor, (GAME_PLAY*)game);

        CLOSE_DISP(graph);
    }
}

static void Ef_Room_Sunshine_MinsectR_actor_draw(ACTOR* actor, GAME* game) {
    GRAPH* graph;

    _texture_z_light_fog_prim(game->graph);
    _texture_z_light_fog_prim_shadow(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);

    draw_status |= 2;

    if (mKK_windowlight_alpha_get() < 9.99999974738e-05f) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
            BG_draw_Minsect(actor, (GAME_PLAY*)game);
        }
    } else if (0.0f == actor->scale.x) {
        if ((draw_status & 1) && (draw_status & 2) && !(draw_status & 4)) {
            BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
            BG_draw_Minsect(actor, (GAME_PLAY*)game);
        }
    } else {
        graph = game->graph;

        BG_draw_Minsect_niwa(actor, (GAME_PLAY*)game);
        setup_mode_Ef_Room_Sunshine_Minsect(actor, (GAME_PLAY*)game);
        OPEN_DISP(graph);

        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum4_shine_1T_model);
        setup_mode_Ef_Room_Sunshine_Minsect_decal(actor, (GAME_PLAY*)game);

        if (REGADDR(TAKREG, 0) == 0) {
            gSPDisplayList(NEXT_POLY_OPA_DISP, obj_museum4_shine_2T_model);
        }
        BG_draw_Minsect(actor, (GAME_PLAY*)game);

        CLOSE_DISP(graph);
    }
}
