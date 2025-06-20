#include "ef_effect_control.h"
#include "m_common_data.h"
#include "m_rcp.h"
#include "sys_matrix.h"
#include "m_debug.h"

static void eKamifubuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKamifubuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKamifubuki_mv(eEC_Effect_c* effect, GAME* game);
static void eKamifubuki_dw(eEC_Effect_c* effect, GAME* game);

#define EFFECT_LIFETIME 90

eEC_PROFILE_c iam_ef_kamifubuki = {
    // clang-format off
    &eKamifubuki_init,
    &eKamifubuki_ct,
    &eKamifubuki_mv,
    &eKamifubuki_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKamifubuki_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KAMIFUBUKI, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eKamifubuki_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    s16 d = DEG2SHORT_ANGLE2(RANDOM_F(35.f));
    s16 r = qrand();
    s16 a = *(s16*)ct_arg;
    static xyz_t unit_axis = { 0.f, 0.f, 1.f };
    xyz_t p;
    f32 s;
    s = sin_s(d) * 7.f;
    Matrix_RotateY(a, MTX_LOAD);
    Matrix_RotateX(effect->arg1, MTX_MULT);
    p.x = s * sin_s(r);
    p.y = cos_s(d) * 7.f;
    p.z = s * cos_s(r);
    Matrix_Position(&p, &effect->velocity);
    effect->scale = effect->position;
    d = DEG2SHORT_ANGLE2(RANDOM_F(40.f));
    r = qrand();
    s = sin_s(d) * 7.f;
    p.x = s * sin_s(r);
    p.y = cos_s(d) * 7.f;
    p.z = s * cos_s(r);
    Matrix_Position(&p, &effect->acceleration);
    effect->effect_specific[0] = qrand();
    effect->effect_specific[1] = DEG2SHORT_ANGLE2(RANDOM2_F(15.f) + 15.f);
    Matrix_rotateXYZ(qrand(), qrand(), qrand(), MTX_LOAD);
    Matrix_Position(&unit_axis, &effect->offset);
    effect->timer = EFFECT_LIFETIME - RANDOM(5.f);
}

static void eKamifubuki_mv(eEC_Effect_c* effect, GAME* game) {
    effect->position.x += effect->velocity.x;
    effect->position.y += effect->velocity.y;
    effect->position.z += effect->velocity.z;
    effect->velocity.y += -0.1f;
    xyz_t_mult_v(&effect->velocity, sqrtf(0.9f));
    effect->scale.x += effect->acceleration.x;
    effect->scale.y += effect->acceleration.y;
    effect->scale.z += effect->acceleration.z;
    effect->acceleration.y += -0.1f;
    xyz_t_mult_v(&effect->acceleration, sqrtf(0.9f));
    effect->velocity.x += RANDOM_F(0.15f) * sin_s(effect->effect_specific[0]);
    effect->acceleration.x += RANDOM_F(0.15f) * sin_s(effect->effect_specific[0]);
    effect->effect_specific[0] += effect->effect_specific[1];
}
extern Gfx ef_kamihubuki01_00_model[];
static void eKamifubuki_one_draw(eEC_Effect_c* effect, xyz_t* pos, GAME* game) {
    OPEN_DISP(game->graph);
    Matrix_translate(pos->x, pos->y, pos->z, MTX_LOAD);
    Matrix_RotateVector(effect->effect_specific[0], &effect->offset, MTX_MULT);
    Matrix_scale((GETREG(MYKREG, 0x1b) * 0.01f + 1.f) * 0.003f, (GETREG(MYKREG, 0x1b) * 0.01f + 1.f) * 0.003f,
                 (GETREG(MYKREG, 0x1b) * 0.01f + 1.f) * 0.003f, MTX_MULT);
    gSPMatrix(NEXT_POLY_XLU_DISP, _Matrix_to_Mtx_new(game->graph), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kamihubuki01_00_model);
    CLOSE_DISP(game->graph);
}

static void eKamifubuki_dw(eEC_Effect_c* effect, GAME* game) {
    int i;
    int v = (u8)eEC_CLIP->calc_adjust_proc(effect->timer, 0, 10, 0.f, 255.f);
    static rgb8_t rgb_tbl[4][2] = { { { 100, 20, 20 }, { 155, 30, 30 } },
                                    { { 20, 100, 20 }, { 30, 155, 30 } },
                                    { { 20, 20, 100 }, { 30, 30, 155 } },
                                    { { 100, 100, 100 }, { 155, 155, 155 } } };
    OPEN_DISP(game->graph);
    i = effect->arg0;
    _texture_z_light_fog_prim_xlu(game->graph);
    if (i > ARRAY_COUNT(rgb_tbl) - 1) {
        i = ARRAY_COUNT(rgb_tbl) - 1;
    }
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, rgb_tbl[i][0].r, rgb_tbl[i][0].g, rgb_tbl[i][0].b, (u8)v);
    gDPSetEnvColor(NEXT_POLY_XLU_DISP, rgb_tbl[i][1].r, rgb_tbl[i][1].g, rgb_tbl[i][1].b, 255);
    eKamifubuki_one_draw(effect, &effect->position, game);
    eKamifubuki_one_draw(effect, &effect->scale, game);
    CLOSE_DISP(game->graph);
}
