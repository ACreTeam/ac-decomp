#include "ef_room_sunshine_museum.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_debug.h"
#include "m_collision_bg.h"
#include "sys_matrix.h"

void Ef_Room_Sunshine_Museum_actor_ct(ACTOR* actorx, GAME* game);
void Ef_Room_Sunshine_MuseumL_actor_draw(ACTOR* actorx, GAME* game);
void Ef_Room_Sunshine_MuseumL_actor_move(ACTOR* actorx, GAME* game);
void Ef_Room_Sunshine_MuseumR_actor_draw(ACTOR* actorx, GAME* game);
void Ef_Room_Sunshine_MuseumR_actor_move(ACTOR* actorx, GAME* game);

extern Gfx obj_museum1_shine_model[];
extern Gfx obj_museum1_shine_modelT[];

ACTOR_PROFILE Room_Sunshine_Museum_Profile = {
    mAc_PROFILE_ROOM_SUNSHINE_MUSEUM,
    ACTOR_PART_EFFECT,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_EF_MUSEUM,
    sizeof(ROOMSUNSHINEMUSEUM_ACTOR),
    Ef_Room_Sunshine_Museum_actor_ct,
    NONE_ACTOR_PROC,
    Ef_Room_Sunshine_MuseumR_actor_move,
    Ef_Room_Sunshine_MuseumR_actor_draw,
    NULL,
};

static void Ef_Room_Sunshine_Museum_actor_ct(ACTOR* actorx, GAME* game) {
    ROOMSUNSHINEMUSEUM_ACTOR* museum = (ROOMSUNSHINEMUSEUM_ACTOR*)actorx;

    museum->ef_sunshine_class.unk_174 = 0;
    if (actorx->actor_specific == Ef_Room_Sunshine_Museum_TOP_RIGHT) {
        actorx->mv_proc = Ef_Room_Sunshine_MuseumL_actor_move;
        actorx->dw_proc = Ef_Room_Sunshine_MuseumL_actor_draw;
    } else {
        actorx->world.position.x -= 1.0f;
    }

    actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f);

    actorx->scale.x = 0.01f;
    actorx->scale.y = 0.01f;
    actorx->scale.z = 0.01f;

    switch (actorx->actor_specific) {
        case Ef_Room_Sunshine_Museum_BOTTOM_RIGHT:
            actorx->mv_proc = Ef_Room_Sunshine_MuseumL_actor_move;
            actorx->dw_proc = Ef_Room_Sunshine_MuseumL_actor_draw;
            actorx->world.position.x += 5.0f;
            actorx->world.position.y = 1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f) - 40.0f;
            actorx->world.position.x -= 6.0f;
            break;
        case Ef_Room_Sunshine_Museum_BOTTOM_LEFT:
            actorx->world.position.x -= 5.0f;
            actorx->world.position.y = 1.0f + mCoBG_GetBgY_OnlyCenter_FromWpos(actorx->world.position, 0.0f) - 40.0f;
            actorx->world.position.x += 6.0f;
            break;
    }
}

static f32 calc_scale_Ef_Room_Sunshine_Museum(int flag, int sec) {
    if (flag == 0) {
        return 0.01f * (1.5f * sin_s((sec * DEG2SHORT_ANGLE2(90.0f)) / (f32)mTM_TIME2SEC(8, 0, 0)));
    } else {
        return 0.01f * (1.5f * sin_s((sec * DEG2SHORT_ANGLE2(90.0f)) / (f32)mTM_TIME2SEC(4, 0, 0)));
    }
}

static u8 calc_alpha_Ef_Room_SunshineMuseum(void) {
    int sec = Common_Get(time.now_sec);
    f32 alpha;

    if (sec < mTM_TIME2SEC(4, 0, 0)) {
        alpha = 120.0f * ((mTM_TIME2SEC(4, 0, 0) - sec) / (f32)mTM_TIME2SEC(4, 0, 0));
    } else if (sec < mTM_TIME2SEC(20, 0, 0)) {
        alpha = 255.0f * ((mTM_TIME2SEC(8, 0, 0) - ABS(sec - mTM_TIME2SEC(12, 0, 0))) / (f32)mTM_TIME2SEC(8, 0, 0));
    } else {
        alpha = 120.0f * ((mTM_TIME2SEC(4, 0, 0) - (mTM_TIME2SEC(24, 0, 0) - sec)) / (f32)mTM_TIME2SEC(4, 0, 0));
    }

    if ((Common_Get(weather) == mEnv_WEATHER_RAIN) || (Common_Get(weather) == mEnv_WEATHER_SNOW)) {
        alpha *= 0.6f;
    }

    return (int)alpha;
}

static void Ef_Room_Sunshine_MuseumL_actor_move(ACTOR* actorx, GAME* game) {
    int now_sec = Common_Get(time.now_sec);

    if (now_sec < mTM_TIME2SEC(4, 0, 0)) {
        actorx->scale.x = calc_scale_Ef_Room_Sunshine_Museum(1, now_sec);
    } else if (now_sec >= mTM_TIME2SEC(12, 0, 0) && now_sec < mTM_TIME2SEC(20, 0, 0)) {
        actorx->scale.x = calc_scale_Ef_Room_Sunshine_Museum(0, now_sec - mTM_TIME2SEC(12, 0, 0));
    } else {
        actorx->scale.x = 0.0f;
    }
}

static void Ef_Room_Sunshine_MuseumR_actor_move(ACTOR* actorx, GAME* game) {
    int now_sec = Common_Get(time.now_sec);

    if (now_sec >= mTM_TIME2SEC(4, 0, 0) && now_sec < mTM_TIME2SEC(12, 0, 0)) {
        actorx->scale.x = -calc_scale_Ef_Room_Sunshine_Museum(0, mTM_TIME2SEC(12, 0, 0) - now_sec);
    } else if (now_sec >= mTM_TIME2SEC(20, 0, 0)) {
        actorx->scale.x = -calc_scale_Ef_Room_Sunshine_Museum(1, mTM_TIME2SEC(24, 0, 0) - now_sec);
    } else {
        actorx->scale.x = 0.0f;
    }
}

static void setup_mode_Ef_Room_Sunshine_Museum(ACTOR* actorx, GAME* game) {
    u8* color;
    u8 prim_l;

    OPEN_DISP(game->graph);

    Matrix_translate(actorx->world.position.x + GETREG(TAKREG, 20), actorx->world.position.y + GETREG(TAKREG, 21),
                     actorx->world.position.z + GETREG(TAKREG, 22), MTX_LOAD);
    Matrix_scale(actorx->scale.x, actorx->scale.y, actorx->scale.z, MTX_MULT);

    gDPPipeSync(NEXT_POLY_XLU_DISP);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if ((Common_Get(time.now_sec) >= mTM_TIME2SEC(4, 0, 0)) && (Common_Get(time.now_sec) < mTM_TIME2SEC(20, 0, 0))) {
        color = ((GAME_PLAY*)game)->kankyo.base_light.sun_color_window;
    } else {
        color = ((GAME_PLAY*)game)->kankyo.base_light.moon_color_window;
    }

    prim_l = calc_alpha_Ef_Room_SunshineMuseum() * mKK_windowlight_alpha_get();
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, prim_l, color[0], color[1], color[2], 75);
    CLOSE_DISP(game->graph);
}

static void Ef_Room_Sunshine_MuseumL_actor_draw(ACTOR* actorx, GAME* game) {
    if (!(mKK_windowlight_alpha_get() < 0.0001f) && (actorx->scale.x != 0.0f)) {
        OPEN_DISP(game->graph);

        setup_mode_Ef_Room_Sunshine_Museum(actorx, game);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum1_shine_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum1_shine_modelT);

        CLOSE_DISP(game->graph);
    }
}

static void Ef_Room_Sunshine_MuseumR_actor_draw(ACTOR* actorx, GAME* game) {
    if (!(mKK_windowlight_alpha_get() < 0.0001f) && (actorx->scale.x != 0.0f)) {
        OPEN_DISP(game->graph);

        setup_mode_Ef_Room_Sunshine_Museum(actorx, game);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum1_shine_model);
        gSPDisplayList(NEXT_POLY_XLU_DISP, obj_museum1_shine_modelT);

        CLOSE_DISP(game->graph);
    }
}
