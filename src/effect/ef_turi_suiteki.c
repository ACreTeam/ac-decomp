#include "ef_effect_control.h"

#include "m_common_data.h"
#include "sys_matrix.h"
#include "m_rcp.h"

static void eTS_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eTS_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eTS_mv(eEC_Effect_c* effect, GAME* game);
static void eTS_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_turi_suiteki = {
    // clang-format off
    &eTS_init,
    &eTS_ct,
    &eTS_mv,
    &eTS_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eTS_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_TURI_SUITEKI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eTS_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->scale.x = 0.0015f;
    effect->scale.y = 0.0015f;
    effect->scale.z = 0.0015f;

    effect->effect_specific[0] = (s16)(sin_s(DEG2SHORT_ANGLE(74.53125f)) * 10.0f / 0.75f + 2.0f);
    effect->effect_specific[0] *= 2;

    effect->acceleration.x = RANDOM_F(5.0f);
    effect->acceleration.z = RANDOM_F(5.0f);

    effect->timer = effect->effect_specific[0];
}

static void eTS_mv(eEC_Effect_c* effect, GAME* game) {
    u32 attribute = mCoBG_Wpos2Attribute(effect->velocity, NULL);
    f32 height;

    if (mCoBG_CheckWaterAttribute(attribute)) {
        height = mCoBG_GetWaterHeight_File(effect->velocity, __FILE__, 129);
        if (height >= effect->velocity.y && height < effect->position.y + 10.0f) {
            eEC_CLIP->effect_make_proc(eEC_EFFECT_TURI_HAMON, effect->velocity, 1, 0, game, EMPTY_NO, 3, 0);
            effect->timer = 0;
        }
    }
}

extern Gfx ef_turi_suiteki01_00_modelT[];

static void eTS_dw(eEC_Effect_c* effect, GAME* game) {
    xyz_t scale = effect->scale;
    f32 remain = effect->effect_specific[0] - effect->timer;
    f32 angle_f;
    int angle;

    if (effect->arg1 != 0) {
        angle_f = (f32)effect->arg0 * 360.0f / (f32)effect->arg1;
    } else {
        angle_f = 0.0f;
    }

    angle = DEG2SHORT_ANGLE2(angle_f);
    effect->velocity.x = effect->position.x + effect->acceleration.x * remain * cos_s(DEG2SHORT_ANGLE(74.53125f)) * sin_s(angle);
    effect->velocity.z = effect->position.z + effect->acceleration.z * remain * cos_s(DEG2SHORT_ANGLE(74.53125f)) * cos_s(angle);
    effect->velocity.y = (effect->position.y + (remain * 5.0f) * sin_s(DEG2SHORT_ANGLE(74.53125f))) - remain * (0.375f * remain);

    OPEN_DISP(game->graph);

    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->velocity.x, effect->velocity.y, effect->velocity.z, 0);
    Matrix_scale(scale.x, scale.y, scale.z, 1);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_turi_suiteki01_00_modelT);

    CLOSE_DISP(game->graph);
}
