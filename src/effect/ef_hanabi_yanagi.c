#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eHanabiYanagi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eHanabiYanagi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eHanabiYanagi_mv(eEC_Effect_c* effect, GAME* game);
static void eHanabiYanagi_dw(eEC_Effect_c* effect, GAME* game);

#define EFFECT_LIFETIME 110
#define CALC_EASE(x) (1.0f - sqrtf(1.0f - (x)))

eEC_PROFILE_c iam_ef_hanabi_yanagi = {
    // clang-format off
    &eHanabiYanagi_init,
    &eHanabiYanagi_ct,
    &eHanabiYanagi_mv,
    &eHanabiYanagi_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_IGNORE_DEATH_DIST,
    // clang-format on
};

static void eHanabiYanagi_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_HANABI_YANAGI, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eHanabiYanagi_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = EFFECT_LIFETIME;
    effect->scale.x = 0.01f;
    effect->scale.y = 0.01f;
    effect->scale.z = 0.01f;
    effect->effect_specific[0] = 0;
    effect->effect_specific[1] = 0;
    effect->effect_specific[2] = 0;
    effect->offset.x = 0.f;
    effect->offset.y = 0.f;
    effect->offset.z = 0.f;
}

static void eHanabiYanagi_mv(eEC_Effect_c* effect, GAME* game) {
    s16 alive_frames = EFFECT_LIFETIME - effect->timer;
    effect->effect_specific[0] += 0x300;
    effect->effect_specific[1] += 0x100;
    effect->effect_specific[2] += 0x80;
    effect->offset.x = sin_s(effect->effect_specific[2]) * 2.f;
    effect->offset.z = cos_s(-effect->effect_specific[2]) * 2.f;
    add_calc2(&effect->scale.x, 0.06f, CALC_EASE(0.2f), 5.f);
    if (alive_frames == 10) {
        rgba_t resultColor;
        static rgba_t yanagi_light = { 90, 90, 45, 255 };
        eEC_CLIP->decide_light_power_proc(&resultColor, yanagi_light, effect->position, game, 2.f, 0.f, 480.f);
        if (effect->arg0) {
            // `resultColor.r *= (4.f/3.f);` does not match
            resultColor.r = resultColor.r * (4.f / 3.f);
            resultColor.g = resultColor.g * (4.f / 3.f);
            resultColor.b = resultColor.b * (4.f / 3.f);
        }
        eEC_CLIP->regist_effect_light(resultColor, 20, 50, TRUE);
    }
    if (alive_frames == 72) {
        xyz_t p = effect->position;
        p.y += 200.f;
        sAdo_OngenTrgStart(NA_SE_HANABI3, &p);
    }
}
eEC_morph_data_c eHanabiYanagi_morph_data_out[] = {
    { 0, 0, FALSE, 255.f, 255.f }, { 34, 54, TRUE, 255.f, 200.f }, { 34, 54, TRUE, 50.f, 100.f },
    { 34, 54, TRUE, 150.f, 0.f },  { 5, 34, TRUE, 0.f, 255.f },    { 0, 0, FALSE, 255.f, 255.f },
    { 0, 0, FALSE, 0.f, 0.f },     { 0, 0, FALSE, 200.f, 200.f },  { 0, 0, FALSE, 255.f, 255.f },
};
eEC_morph_data_c eHanabiYanagi_morph_data_in[] = {
    { 0, 0, FALSE, 255.f, 255.f }, { 34, 49, TRUE, 255.f, 200.f }, { 34, 49, TRUE, 50.f, 100.f },
    { 34, 49, TRUE, 180.f, 0.f },  { 5, 34, TRUE, 0.f, 255.f },    { 0, 0, FALSE, 255.f, 255.f },
    { 0, 0, FALSE, 0.f, 0.f },     { 0, 0, FALSE, 200.f, 200.f },  { 0, 0, FALSE, 255.f, 255.f },
};

extern Gfx ef_hanabi_y_00_modelT[];
static void eHanabiYanagi_dw(eEC_Effect_c* effect, GAME* game) {
    u8 res1[9];
    u8 res2[9];
    s16 now_timer = EFFECT_LIFETIME - effect->timer;
    f32 v2;
    f32 v = (sin_s(effect->effect_specific[0]) + 1.f) * 0.5f * 0.14000005f + 0.93f;
    eEC_CLIP->morph_combine_proc(res1, eHanabiYanagi_morph_data_out, now_timer);
    eEC_CLIP->morph_combine_proc(res2, eHanabiYanagi_morph_data_in, now_timer);
    v2 = effect->scale.x + eEC_CLIP->calc_adjust_proc(now_timer, 0, EFFECT_LIFETIME - 1, 0.f, 0.01);
    OPEN_DISP(game->graph);
    _texture_z_light_fog_prim_xlu(game->graph);
    Matrix_translate(effect->position.x + effect->offset.x, effect->position.y + effect->offset.y,
                     effect->position.z + effect->offset.z, MTX_LOAD);
    Matrix_RotateX(DEG2SHORT_ANGLE2(270), MTX_MULT);
    Matrix_RotateZ(-effect->effect_specific[1], MTX_MULT);
    Matrix_scale(v, 1.f, 1.f, MTX_MULT);
    Matrix_RotateZ(effect->effect_specific[1], MTX_MULT);
    Matrix_push();
    Matrix_scale(v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f),
                 v2 * (GETREG(MYKREG, 0x1b) * 0.01f + 1.f), MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, res1[4], res1[0], res1[1], res1[2], res1[3]);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, res1[5], res1[6], res1[7], res1[8]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabi_y_00_modelT);
    Matrix_pull();
    Matrix_scale(v2 * 0.6f, v2 * 0.6f, v2 * 0.6f, MTX_MULT);
    gDPPipeSync(NEXT_POLY_XLU_DISP);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, res2[4], res2[0], res2[1], res2[2], res2[3]);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, res2[5], res2[6], res2[7], res2[8]);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_hanabi_y_00_modelT);
    CLOSE_DISP(game->graph);
}
