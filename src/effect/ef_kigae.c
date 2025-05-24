#include "ef_effect_control.h"

#include "m_common_data.h"

static void eKigae_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1);
static void eKigae_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg);
static void eKigae_mv(eEC_Effect_c* effect, GAME* game);
static void eKigae_dw(eEC_Effect_c* effect, GAME* game);

eEC_PROFILE_c iam_ef_kigae = {
    // clang-format off
    &eKigae_init,
    &eKigae_ct,
    &eKigae_mv,
    &eKigae_dw,
    eEC_IGNORE_DEATH,
    eEC_NO_CHILD_ID,
    eEC_DEFAULT_DEATH_DIST,
    // clang-format on
};

static void eKigae_init(xyz_t pos, int prio, s16 angle, GAME* game, u16 item_name, s16 arg0, s16 arg1) {
    eEC_CLIP->make_effect_proc(eEC_EFFECT_KIGAE, pos, NULL, game, &angle, item_name, prio, arg0, arg1);
}

static void eKigae_ct(eEC_Effect_c* effect, GAME* game, void* ct_arg) {
    effect->effect_specific[0] = *(s16*)ct_arg + DEG2SHORT_ANGLE2(90.0f);
    effect->timer = 60;
}

static void eKigae_mv(eEC_Effect_c* effect, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    xyz_t pos = effect->position;

    effect->effect_specific[0] -= DEG2SHORT_ANGLE2(9.0f);
    if ((play->game_frame & 1) == 0) {
        pos.x += (sin_s(effect->effect_specific[0]) * 22.0f) + RANDOM2_F(5.0f);
        pos.y += eEC_CLIP->calc_adjust_proc(effect->timer, 0, 60, 10.0f, -25.0f) + RANDOM2_F(5.0f);
        pos.z += (cos_s(effect->effect_specific[0]) * 22.0f) + RANDOM2_F(5.0f);

        eEC_CLIP->effect_make_proc(eEC_EFFECT_KIGAE_LIGHT, pos, effect->prio, 0, game, effect->item_name, 0, 0);
    }
}

static void eKigae_dw(eEC_Effect_c* effect, GAME* game) {
    return;
}
