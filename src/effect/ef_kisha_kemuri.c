#include "ef_effect_control.h"

#include "m_common_data.h"

extern Gfx ef_kisha_kemuri01_modelT[];

static void eKishaK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKishaK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKishaK_mv(eEC_Effect_c* effect, GAME* game);
static void eKishaK_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kisha_kemuri = {
    // clang-format off
    &eKishaK_init,
    &eKishaK_ct,
    &eKishaK_mv,
    &eKishaK_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKishaK_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KISHA_KEMURI, pos, NULL, game, NULL, item_name, prio, arg0, angle);
}

static void eKishaK_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    f32 x, y;

    effect->scale.x = 0.0f;
    effect->scale.y = 0.0f;
    effect->scale.z = 0.0f;

    effect->timer = 80;

    x = RANDOM_F(5.0f) - 2.5f;
    y = RANDOM_F(5.0f) - 2.5f;
    effect->position.x += x;
    effect->position.z += y;

    if (effect->arg0 == 1) {
        effect->acceleration.x = sin_s(effect->arg1) * 0.2f;
        effect->acceleration.z = cos_s(effect->arg1) * 0.2f;
    }
}

static void eKishaK_mv(eEC_Effect_c* effect, GAME* game) {
    effect->position.y += eEC_CLIP->calc_adjust_proc(80 - effect->timer, 0, 20, 2.2f, 0.5f);
    if (effect->arg0 == 1) {
        effect->position.x += effect->acceleration.x;
        effect->position.z += effect->acceleration.z;
    }
}

static void eKishaK_dw(eEC_Effect_c* effect, GAME* game) {
    s16 timer = 80 - effect->timer;
    xyz_t* scale = &effect->scale;
    u8 alpha = (int)eEC_CLIP->calc_adjust_proc(timer, 40, 80, 200.0f, 4.0f);
    f32 new_scale = eEC_CLIP->calc_adjust_proc(timer, 0, 40, 0.003f, 0.027f);

    scale->x = new_scale;
    scale->y = new_scale;
    scale->z = new_scale;

    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, scale);

    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 128, 30, 30, 30, alpha);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_kisha_kemuri01_modelT);

    CLOSE_DISP(game->graph);
}
