#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eGoki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eGoki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eGoki_mv(eEC_Effect_c* effect, GAME* game);
static void eGoki_dw(eEC_Effect_c* effect, GAME* game);

#define EFFECT_LIFETIME 190

#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))
#define CALC_EASE2(x) CALC_EASE(CALC_EASE(x))

extern EVW_ANIME_DATA ef_goki01_01_evw_anime[];
extern Gfx ef_goki01_01_modelT[];

eEC_PROFILE_c iam_ef_goki = {
    // clang-format off
    &eGoki_init,
    &eGoki_ct,
    &eGoki_mv,
    &eGoki_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eGoki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_GOKI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eGoki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = EFFECT_LIFETIME;
    effect->scale = ZeroVec;
    effect->velocity = ZeroVec;
    effect->acceleration = ZeroVec;

    effect->velocity.y = 2.25f;

    effect->acceleration.y = 0.075f;

    effect->effect_specific[0] = 0;

    effect->offset.y = 2.f;
    effect->offset.z = 2000.f;
}

static void eGoki_mv(eEC_Effect_c* effect, GAME* game) {
    s16 now_timer = effect->timer;
    if (effect->timer > 160) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0xa0, EFFECT_LIFETIME, 0.005f, 0.f);
        effect->scale.y = effect->scale.z = effect->scale.x;
    } else if (effect->timer < 60) {
        effect->scale.x = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 0x3c, 0.f, 0.005f);
        effect->scale.y = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 0x3c, 0.01f, 0.005f);
    }
    if (effect->timer < 80) {
        add_calc0(&effect->offset.y, CALC_EASE(0.06f), 0.5f);
        add_calc0(&effect->offset.z, CALC_EASE(0.06f), 50.f);
    }
    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
    effect->velocity.y *= sqrtf(0.65f);
    effect->effect_specific[1] += 1000;
    effect->offset.x = effect->offset.y * sin_s(effect->effect_specific[1]);
    effect->effect_specific[0] = -effect->offset.z * cos_s(effect->effect_specific[1]);
}

static void eGoki_dw(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    int opacity = (u8)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 20, 100.f, 255.f);
    _texture_z_light_fog_prim_xlu(game->graph);
    OPEN_DISP(game->graph);
    Matrix_translate(effect->position.x + effect->offset.x, effect->position.y, effect->position.z, MTX_LOAD);
    Matrix_scale(effect->scale.x * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.y * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 effect->scale.z * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), TRUE);
    Matrix_mult(&play->billboard_matrix, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[0], MTX_MULT);
    Evw_Anime_Set(play, ef_goki01_01_evw_anime);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, opacity);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_goki01_01_modelT);
    CLOSE_DISP(game->graph);
}
