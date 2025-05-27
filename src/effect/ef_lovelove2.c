#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_lovelove02_00_modelT[];

static void eLL2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eLL2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eLL2_mv(eEC_Effect_c* effect, GAME* game);
static void eLL2_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_lovelove2 = {
    // clang-format off
    &eLL2_init,
    &eLL2_ct,
    &eLL2_mv,
    &eLL2_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eLL2_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    pos.y += 16.0f;
    eEC_CLIP->make_effect_proc(eEC_EFFECT_LOVELOVE2, pos, NULL, game, &angle, item_name, prio, 0, 0);
}

static void eLL2_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[0] = *(s16*)ct_arg;
    effect->timer = 112;
    effect->scale = ZeroVec;
    effect->offset = ZeroVec;
    effect->effect_specific[1] = 0;
    effect->acceleration = ZeroVec;

    sAdo_OngenTrgStart(0x118, &effect->position);
}

static void eLL2_mv(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 112 - effect->timer;
    effect->effect_specific[1] += DEG2SHORT_ANGLE(10.55f);
    effect->position.y += eEC_CLIP->calc_adjust_proc(timer, 0, 28, 1.0f, 0.1f);
}

static void eLL2_dw(eEC_Effect_c* effect, GAME* game) {
    f32 temp1, temp2, temp3;
    u8 alpha;

    xyz_t* scale = &effect->scale;
    s16 timer = 112 - effect->timer;
    s16 angle = effect->effect_specific[1];
    f32 sin = sin_s(angle);
    f32 cos = cos_s(angle);

    temp1 = eEC_CLIP->calc_adjust_proc(timer, 0, 30, 0.003f, 0.014f);
    temp2 = eEC_CLIP->calc_adjust_proc(timer, 0, 30, 1.0125f, 0.6375f);
    temp3 = eEC_CLIP->calc_adjust_proc(timer, 0, 30, 0.037499964f, 0.412499964f);
    alpha = (s8)eEC_CLIP->calc_adjust_proc(timer, 96, 112, 255.0f, 0.0f);

    scale->x = temp1 * (temp3 + ((sin + 1.0f) * 0.5f * (temp2 - temp3)));
    scale->y = temp1 * (temp3 + ((cos + 1.0f) * 0.5f * (temp2 - temp3)));
    scale->z = temp1;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_offset_proc(game, &effect->position, scale, &effect->offset);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_lovelove02_00_modelT);

    CLOSE_DISP(game->graph);
}
