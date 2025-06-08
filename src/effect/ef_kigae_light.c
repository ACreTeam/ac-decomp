#include "ef_effect_control.h"

#include "m_common_data.h"

static void eKigae_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKigae_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKigae_Light_mv(eEC_Effect_c* effect, GAME* game);
static void eKigae_Light_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kigae_light = {
    // clang-format off
    &eKigae_Light_init,
    &eKigae_Light_ct,
    &eKigae_Light_mv,
    &eKigae_Light_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKigae_Light_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    if (arg0 == 1) {
        pos.x += sin_s(angle) * 20.0f - cos_s(angle) * 20.0f;
        pos.y += 35.0f;
        pos.z += cos_s(angle) * 20.0f + sin_s(angle) * 20.0f;
    } else if (arg0 == 2) {
        pos.x += sin_s(angle) * 20.0f - cos_s(angle) * 20.0f;
        pos.y += 35.0f;
        pos.z += cos_s(angle) * 20.0f + sin_s(angle) * 20.0f;
    }

    eEC_CLIP->make_effect_proc(eEC_EFFECT_KIGAE_LIGHT, pos, NULL, game, NULL, item_name, prio, arg0, arg1);
}

static void eKigae_Light_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->timer = 30;
    effect->scale = ZeroVec;
    effect->velocity = ZeroVec;
    effect->acceleration = ZeroVec;

    if (effect->arg0 == 0) {
        effect->acceleration.y = -0.025f;
    }
}

static void eKigae_Light_mv(eEC_Effect_c* effect, GAME* game) {
    f32 scale;

    if (effect->timer > 20) {
        scale = eEC_CLIP->calc_adjust_proc(effect->timer, 20, 30, 0.009f, 0.0f);
        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;
    } else {
        scale = eEC_CLIP->calc_adjust_proc(effect->timer, 0, 20, 0.0f, 0.009f);
        effect->scale.x = scale;
        effect->scale.y = scale;
        effect->scale.z = scale;
    }

    xyz_t_add(&effect->velocity, &effect->acceleration, &effect->velocity);
    xyz_t_add(&effect->position, &effect->velocity, &effect->position);
}

extern Gfx ef_takurami01_normal_render_mode[];
extern Gfx ef_takurami01_kira_modelT[];

static void eKigae_Light_dw(eEC_Effect_c* effect, GAME* game) {
    OPEN_DISP(game->graph);

    eEC_CLIP->auto_matrix_xlu_proc(game, &effect->position, &effect->scale);
    gSPSegment(NEXT_POLY_XLU_DISP, ANIME_1_TXT_SEG, ef_takurami01_normal_render_mode);
    gDPSetPrimColor(NEXT_POLY_XLU_DISP, 0, 255, 255, 255, 255, 255);
    gSPDisplayList(NEXT_POLY_XLU_DISP, ef_takurami01_kira_modelT);

    CLOSE_DISP(game->graph);
}
